/*
 * Copyright (c), Zeriph Enterprises
 * All rights reserved.
 * 
 * Contributor(s):
 * Zechariah Perez, omni (at) zeriph (dot) com
 * 
 * THIS SOFTWARE IS PROVIDED BY ZERIPH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ZERIPH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <omni/defs/global.hpp>
#if defined(OMNI_OS_WIN)
    #include <windows.h>
    #if !defined(OMNI_SIGCALL)
        #define OMNI_SIGCALL __cdecl // for signal
    #endif
#endif
#if !defined(OMNI_SIGCALL)
    #define OMNI_SIGCALL
#endif
#include <cerrno>
#include <signal.h>
#include <errno.h>
#include <clocale>
#include <cstdlib>
#include <cstring>
#include <omni/application.hpp>
#include <omni/strings.hpp>
#include <omni/system.hpp>
#include <omni/defs/consts.hpp>
#include <omni/sync/conditional.hpp>
#include <omni/sync/thread.hpp>
#include <omni/chrono/tick.hpp>

//============================START BASE METHODS============================/

#if defined(OMNI_SAFE_APPLICATION)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_APP_LOCK_FW omni::application::mtx_().lock();
    #define OMNI_SAFE_APP_UNLOCK_FW omni::application::mtx_().unlock();
#else
    #define OMNI_SAFE_APP_LOCK_FW 
    #define OMNI_SAFE_APP_UNLOCK_FW 
#endif

namespace omni {
    namespace application {
        #if defined(OMNI_SAFE_APPLICATION)
        
        static omni::sync::basic_lock& mtx_()
        {
            static omni::sync::basic_lock* m_ret = new omni::sync::basic_lock();
            return *m_ret;
        }
        
        #endif
        
        static omni::event1<void, int>& sig_()
        {
            static omni::event1<void, int>* m_ret = new omni::event1<void, int>();
            return *m_ret;
        }
        
        static omni::action& exit_()
        {
            static omni::action* m_ret = new omni::action();
            return *m_ret;
        }
        
        static omni::action& start_()
        {
            static omni::action* m_ret = new omni::action();
            return *m_ret;
        }
        
        static omni::action& shut_()
        {
            static omni::action* m_ret = new omni::action();
            return *m_ret;
        }
        
        static omni::action& terminate_()
        {
            static omni::action* m_ret = new omni::action();
            return *m_ret;
        }
        
        static omni::application::argparser& args_()
        {
            static omni::application::argparser* m_ret = new omni::application::argparser();
            return *m_ret;
        }
        
        static omni::sync::conditional& wait_()
        {
            static omni::sync::conditional* m_ret = new omni::sync::conditional();
            return *m_ret;
        }
        
        class base_thread
        {
            public:
                ~base_thread() {}
                
                void reset()
                {
                    this->m_bt.unbind();
                    this->m_btargs = omni::generic_ptr::null();
                }
                
                void spawn(const omni::sync::thread_start& start_func, bool exit_with_work_thread)
                {
                    this->m_btargs = omni::generic_ptr::null();
                    this->m_bt.bind(start_func);
                    if (exit_with_work_thread) {
                        this->m_bt.completed += &omni::application::base_thread::completed;
                    }
                }

                void spawn(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread)
                {
                    this->m_btargs = targs;
                    this->m_bt.bind(start_func);
                    if (exit_with_work_thread) {
                        this->m_bt.completed += &omni::application::base_thread::completed;
                    }
                }
                
                void start()
                {
                    if (this->m_bt.is_bound()) {
                        if (this->m_bt.is_parameter_bound()) {
                            this->m_bt.start(this->m_btargs);
                        } else {
                            this->m_bt.start();
                        }
                    }
                }
                
                void wait(bool kill_worker_on_signal)
                {
                    if (kill_worker_on_signal) {
                        if (this->m_bt.is_alive()) { this->m_bt.kill(); }
                    } else {
                        this->m_bt.join(); // wait on worker thread
                    }
                }
                
                static base_thread& instance()
                {
                    static omni::application::base_thread* m_ret = new omni::application::base_thread();
                    return *m_ret;
                }
                
            private:
                omni::generic_ptr m_btargs;
                omni::sync::thread m_bt;
                
                static void completed(const omni::sync::thread& sender)
                {
                    OMNI_UNUSED(sender);
                    OMNI_SAFE_APP_LOCK_FW
                    omni::application::wait_().signal();
                    OMNI_SAFE_APP_UNLOCK_FW
                }
                
                base_thread() : m_btargs(), m_bt()
                {
                    this->m_bt.set_option(omni::sync::thread_option::DETACH_ON_DESTROY, false);
                }
                
                base_thread(const base_thread& cp); // = delete;
                base_thread& operator=(const base_thread& cp); // = delete;
        };
        
        static volatile bool m_isrun; // is omni::app running?
        static volatile bool m_igsig; // user cancel signal request
        static int m_sig; // the last signal received
        static int m_ret; // the value returned from run
    }
}

OMNI_CLINKO_FW // extern "C"

/* DEV_NOTE: Signal handlers are expected to have C linkage and, in general, only 
use the features from the common subset of C and C++. It is implementation-defined 
if a function with C++ linkage can be used as a signal handler. */

static void OMNI_SIGCALL omni_application_base_msg_pump(int sig)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::m_sig = sig;
    OMNI_DV1_FW("signal received: ", sig);
    if (omni::application::sig_()) {
        if (!omni::application::m_igsig) {
            OMNI_SAFE_APP_UNLOCK_FW
            OMNI_THREAD_TRY_FW
            omni::application::sig_()(sig);
            OMNI_THREAD_CATCH_FW
            OMNI_SAFE_APP_LOCK_FW
        }
    } else {
        switch (sig) {
            // SIGINT is caught by the console handler in windows
            case SIGINT:  // signal interrupt: typically occurs when user interrupts the program (like when pressing CTRL+C)
            case SIGABRT: // signal abort: abnormal termination
            case SIGFPE:  // signal floating point exception: occurs on erroneous arithmetic operations (like division by 0)
            case SIGILL:  // signal illegal instruction: typically occurs with code corruption
            case SIGSEGV: // signal segmentation violation: typically occurs when the program tries to read/write invalid memory
            case SIGTERM: // signal terminate: termination request sent to the program
            default:      // other/unknown signal
                break;
        }
    }
    omni::application::wait_().signal();
    OMNI_SAFE_APP_UNLOCK_FW
}

#if defined(OMNI_WIN_API)
static BOOL WINAPI omni_application_base_win_ctrl_handler(DWORD sig)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::m_sig = sig;
    OMNI_DV1_FW("signal received: ", sig);
    if (omni::application::sig_()) {
        if (!omni::application::m_igsig) {
            OMNI_SAFE_APP_UNLOCK_FW
            OMNI_THREAD_TRY_FW
            omni::application::sig_()(sig);
            OMNI_THREAD_CATCH_FW
            OMNI_SAFE_APP_LOCK_FW
        }
    } else {
        // Here you can handle special cases before the callback gets raised
        switch (sig) {
            case CTRL_C_EVENT:        // signal when CTRL+C received
            case CTRL_BREAK_EVENT:    // signal when CTRL+BREAK received
            case CTRL_CLOSE_EVENT:    // signal when console window being closed
            case CTRL_LOGOFF_EVENT:   // signal when user being logged off
            case CTRL_SHUTDOWN_EVENT: // signal when system is shutting down
            default:                  // other/unknown signal
                break;
        }
    }
    omni::application::wait_().signal();
    OMNI_SAFE_APP_UNLOCK_FW
    /* Tell WinAPI this handler succeeded, do not call other installed 
    handlers (there should not be if this function is called) */
    return TRUE;
}
#endif

#if !defined(OMNI_NO_EXCEPT)
static void omni_application_base_terminate_handler()
{
    #if defined(OMNI_SAFE_APPLICATION)   
        OMNI_SAFE_APP_LOCK_FW
        if (omni::application::terminate_()) {
            OMNI_SAFE_APP_UNLOCK_FW
            OMNI_THREAD_TRY_FW
            omni::application::terminate_()();
            OMNI_THREAD_CATCH_FW
        } else {
            OMNI_SAFE_APP_UNLOCK_FW
        }
    #else
        if (omni::application::terminate_()) {
            OMNI_THREAD_TRY_FW
            omni::application::terminate_()();
            OMNI_THREAD_CATCH_FW
        }
    #endif
    std::abort(); // default behaviour on terminate, or call app:exit
}
#endif

static void omni_application_base_app_exit()
{
    #if defined(OMNI_SAFE_APPLICATION)   
        OMNI_SAFE_APP_LOCK_FW
        if (omni::application::exit_()) {
            OMNI_SAFE_APP_UNLOCK_FW
            OMNI_THREAD_TRY_FW
            omni::application::exit_()();
            OMNI_THREAD_CATCH_FW
        } else {
            OMNI_SAFE_APP_UNLOCK_FW
        }
    #else
        if (omni::application::exit_()) {
            OMNI_THREAD_TRY_FW
            omni::application::exit_()();
            OMNI_THREAD_CATCH_FW
        }
    #endif
}

OMNI_CLINKC_FW // end extern "C"

namespace omni {
    namespace application {
        namespace base {

            void set_signal_handlers()
            {
                OMNI_D5_FW("attaching signal handlers");
                // We attach the signal handlers but do not die or throw an error because we want
                // to at least allow program execution even if we cannot catch external signals
                
                // DEV_NOTE: might get warning about old-style cast with std::signal and the
                // SIG_ERR def (could be defined as (void (*)(int))-1 .. C-style cast in #def)
                if (std::signal(SIGABRT, &omni_application_base_msg_pump) == SIG_ERR) {
                    OMNI_DBGE("error attaching SIGABRT");
                }
                if (std::signal(SIGFPE, &omni_application_base_msg_pump) == SIG_ERR) {
                    OMNI_DBGE("error attaching SIGFPE");
                }
                if (std::signal(SIGILL, &omni_application_base_msg_pump) == SIG_ERR) {
                    OMNI_DBGE("error attaching SIGILL");
                }
                if (std::signal(SIGSEGV, &omni_application_base_msg_pump) == SIG_ERR) {
                    OMNI_DBGE("error attaching SIGSEGV");
                }
                if (std::signal(SIGTERM, &omni_application_base_msg_pump) == SIG_ERR) {
                    OMNI_DBGE("error attaching SIGTERM");
                }
                if (std::signal(SIGINT, &omni_application_base_msg_pump) == SIG_ERR) {
                    OMNI_DBGE("error attaching SIGINT");
                }
            }
            
            void set_handlers()
            {
                omni::application::base::set_signal_handlers();
                #if defined(OMNI_WIN_API)
                    if (::SetConsoleCtrlHandler(omni_application_base_win_ctrl_handler, TRUE) != 0) {
                        OMNI_DBGEV("Could not set the console control handler: ", OMNI_GLE)
                    }
                #endif
                std::atexit(&omni_application_base_app_exit);
                // std::at_quick_exit
                #if !defined(OMNI_NO_EXCEPT)
                    std::set_terminate(&omni_application_base_terminate_handler);
                #endif
            }

            bool init()
            {
                OMNI_SAFE_APP_LOCK_FW
                if (omni::application::m_isrun) {
                    OMNI_ERR_RETV_FW("An omni::application context is already running", omni::exceptions::invalid_application_state(), false)
                }
                omni::application::m_ret = 0;
                omni::application::m_isrun = false;
                omni::application::base_thread::instance().reset();
                #if !defined(OMNI_NO_BASE_SETLOCALE)
                    // set the locale to accept all (for proper println-ing and string handling)
                    std::setlocale(OMNI_BASE_LOCALE_CATEGORY, OMNI_BASE_LOCALE);
                #endif
                omni::application::base::set_handlers();
                OMNI_SAFE_APP_UNLOCK_FW
                omni::chrono::monotonic::initialize();
                return true;
            }

            void spawn(const omni::sync::thread_start& start_func, bool exit_with_work_thread)
            {
                OMNI_SAFE_APP_LOCK_FW
                OMNI_D2_FW("spawning app thread...");
                if (start_func) {
                    omni::application::base_thread::instance().spawn(start_func, exit_with_work_thread);
                }
                OMNI_SAFE_APP_UNLOCK_FW
            }

            void spawn(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread)
            {
                OMNI_SAFE_APP_LOCK_FW
                OMNI_D2_FW("spawning app thread...");
                if (start_func) {
                    omni::application::base_thread::instance().spawn(start_func, targs, exit_with_work_thread);
                }
                OMNI_SAFE_APP_UNLOCK_FW
            }
            
            int run(bool kill_worker_on_signal)
            {
                OMNI_D2_FW("application start");
                OMNI_SAFE_APP_LOCK_FW
                omni::application::m_isrun = true;
                if (omni::application::start_()) {
                    OMNI_SAFE_APP_UNLOCK_FW
                    OMNI_THREAD_TRY_FW
                    omni::application::start_()();
                    OMNI_THREAD_CATCH_FW
                    OMNI_SAFE_APP_LOCK_FW
                }
                omni::application::base_thread::instance().start();
                OMNI_D2_FW("entering base application loop...");
                do {
                    OMNI_SAFE_APP_UNLOCK_FW
                    omni::application::wait_().wait();
                    OMNI_SAFE_APP_LOCK_FW
                    // if user set cancel signal request, loop until they unset it
                    if (omni::application::m_igsig) {
                        omni::application::wait_().reset();
                        /* std::signal specifies that the signal handlers can be reset back to the default handler
                        so we must re-install the signal handlers to be able to continue to catch; note that we
                        do not need to re-install the WinAPI omni_application_base_win_ctrl_handler. */
                        omni::application::base::set_signal_handlers();
                    }
                } while (omni::application::m_igsig);
                OMNI_SAFE_APP_UNLOCK_FW
                omni::application::base_thread::instance().wait(kill_worker_on_signal);
                OMNI_SAFE_APP_LOCK_FW
                if (omni::application::shut_()) {
                    OMNI_SAFE_APP_UNLOCK_FW
                    OMNI_THREAD_TRY_FW
                    omni::application::shut_()();
                    OMNI_THREAD_CATCH_FW
                    OMNI_SAFE_APP_LOCK_FW
                }
                int ret = omni::application::m_ret;
                omni::application::m_isrun = false;
                OMNI_SAFE_APP_UNLOCK_FW
                OMNI_DV2_FW("base application thread complete, returning ", ret);
                return ret;
            }

            int spawn_and_run(const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal)
            {
                if (omni::application::base::init()) {
                    omni::application::base::spawn(start_func, exit_with_work_thread);
                    return omni::application::base::run(kill_worker_on_signal);
                }
                return -1;
            }

            int spawn_and_run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal)
            {
                if (omni::application::base::init()) {
                    omni::application::set_args(argc, argv);
                    omni::application::base::spawn(start_func, exit_with_work_thread);
                    return omni::application::base::run(kill_worker_on_signal);
                }
                return -1;
            }

            int spawn_and_run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal)
            {
                if (omni::application::base::init()) {
                    omni::application::set_args(argc, argv);
                    omni::application::base::spawn(start_func, exit_with_work_thread);
                    return omni::application::base::run(kill_worker_on_signal);
                }
                return -1;
            }

            int spawn_and_run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal)
            {
                if (omni::application::base::init()) {
                    omni::application::base::spawn(start_func, targs, exit_with_work_thread);
                    return omni::application::base::run(kill_worker_on_signal);
                }
                return -1;
            }

            int spawn_and_run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal)
            {
                if (omni::application::base::init()) {
                    omni::application::set_args(argc, argv);
                    omni::application::base::spawn(start_func, targs, exit_with_work_thread);
                    return omni::application::base::run(kill_worker_on_signal);
                }
                return -1;
            }

            int spawn_and_run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal)
            {
                if (omni::application::base::init()) {
                    omni::application::set_args(argc, argv);
                    omni::application::base::spawn(start_func, targs, exit_with_work_thread);
                    return omni::application::base::run(kill_worker_on_signal);
                }
                return -1;
            }
            
            int spawn_and_run(const int& argc, const char** argv)
            {
                if (omni::application::base::init()) {
                    omni::application::set_args(argc, argv);
                    return omni::application::base::run(false);
                }
                return -1;
            }
            
            int spawn_and_run(const int& argc, const wchar_t** argv)
            {
                if (omni::application::base::init()) {
                    omni::application::set_args(argc, argv);
                    return omni::application::base::run(false);
                }
                return -1;
            }
            
            int spawn_and_run(const omni::sync::parameterized_thread_start& start_func)
            {
                if (omni::application::base::init()) {
                    omni::application::base::spawn(start_func, omni::generic_ptr(), false);
                    return omni::application::base::run(false);
                }
                return -1;
            }
            
            int spawn_and_run()
            {
                if (omni::application::base::init()) {
                    return omni::application::base::run(false);
                }
                return -1;
            }
        }
    }
}

//=============================END BASE METHODS=============================/

//============================START APP_NS METHODS============================/

void omni::application::exit_handler::attach(const omni::callback& exit_func)
{
    OMNI_SAFE_APP_LOCK_FW 
    omni::application::exit_().attach(exit_func);
    OMNI_SAFE_APP_UNLOCK_FW 
}

void omni::application::exit_handler::detach(const omni::callback& exit_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::exit_().detach(exit_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::startup_handler::attach(const omni::callback& start_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::start_().attach(start_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::startup_handler::detach(const omni::callback& start_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::start_().detach(start_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::shutdown_handler::attach(const omni::callback& shutdown_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::shut_().attach(shutdown_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::shutdown_handler::detach(const omni::callback& shutdown_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::shut_().detach(shutdown_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::signal_handler::attach(const omni::application::signal_handler::callback& sig_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::sig_().attach(sig_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::signal_handler::detach(const omni::application::signal_handler::callback& sig_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::sig_().detach(sig_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::signal_handler::ignore(bool doignore)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::m_igsig = doignore;
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::terminate_handler::attach(const omni::callback& terminate_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::terminate_().attach(terminate_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::terminate_handler::detach(const omni::callback& terminate_func)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::terminate_().detach(terminate_func);
    OMNI_SAFE_APP_UNLOCK_FW
}

omni::application::argparser& omni::application::args()
{
    #if defined(OMNI_SAFE_APPLICATION)
        OMNI_SAFE_APP_LOCK_FW
        omni::application::argparser& ret = omni::application::args_();
        OMNI_SAFE_APP_UNLOCK_FW
        return ret;
    #else
        return omni::application::args_();
    #endif
}

void omni::application::exit(int exit_status)
{
    OMNI_SAFE_APP_LOCK_FW
    if (omni::application::m_isrun) {
        omni::application::m_igsig = false;
        omni::application::wait_().signal();
    }
    OMNI_SAFE_APP_UNLOCK_FW
    #if defined(OMNI_WIN_API)
        omni_application_base_app_exit();
        OMNI_D4_FW("base exited, calling system exit");
        ::ExitProcess(exit_status);
    #else
        std::exit(exit_status);
    #endif
}

int omni::application::last_signal()
{
    #if defined(OMNI_SAFE_APPLICATION)
        OMNI_SAFE_APP_LOCK_FW
        int ret = omni::application::m_sig;
        OMNI_SAFE_APP_UNLOCK_FW
        return ret;
    #else
        return omni::application::m_sig;
    #endif
}

int omni::application::run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, targs, exit_with_work_thread, false);
}

int omni::application::run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, targs, exit_with_work_thread, kill_worker_on_signal);
}

int omni::application::run(const int& argc, const char** argv)
{
    return omni::application::base::spawn_and_run(argc, argv);
}

int omni::application::run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, targs, exit_with_work_thread, false);
}

int omni::application::run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, targs, exit_with_work_thread, kill_worker_on_signal);
}

int omni::application::run(const int& argc, const wchar_t** argv)
{
    return omni::application::base::spawn_and_run(argc, argv);
}

int omni::application::run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread)
{
    return omni::application::base::spawn_and_run(start_func, targs, exit_with_work_thread, false);
}

int omni::application::run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal)
{
    return omni::application::base::spawn_and_run(start_func, targs, exit_with_work_thread, kill_worker_on_signal);
}

int omni::application::run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs)
{
    return omni::application::base::spawn_and_run(start_func, targs, false, false);
}

int omni::application::run(const omni::sync::parameterized_thread_start& start_func)
{
    return omni::application::base::spawn_and_run(start_func);
}

int omni::application::run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, exit_with_work_thread, false);
}

int omni::application::run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, exit_with_work_thread, kill_worker_on_signal);
}

int omni::application::run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, exit_with_work_thread, false);
}

int omni::application::run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal)
{
    return omni::application::base::spawn_and_run(argc, argv, start_func, exit_with_work_thread, kill_worker_on_signal);
}

int omni::application::run(const omni::sync::thread_start& start_func, bool exit_with_work_thread)
{
    return omni::application::base::spawn_and_run(start_func, exit_with_work_thread, false);
}

int omni::application::run(const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal)
{
    return omni::application::base::spawn_and_run(start_func, exit_with_work_thread, kill_worker_on_signal);
}

int omni::application::run(const omni::sync::thread_start& start_func)
{
    return omni::application::base::spawn_and_run(start_func, false, false);
}

int omni::application::run()
{
    return omni::application::base::spawn_and_run();
}

void omni::application::set_return_code(int return_code)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::m_ret = return_code;
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::set_args(int argc, const char** argv)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::args_().set(static_cast<uint32_t>(argc), argv);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::set_args(int argc, const wchar_t** argv)
{
    OMNI_SAFE_APP_LOCK_FW
    omni::application::args_().set(static_cast<uint32_t>(argc), argv);
    OMNI_SAFE_APP_UNLOCK_FW
}

void omni::application::stop()
{
    #if defined(OMNI_SAFE_APPLICATION)
        OMNI_SAFE_APP_LOCK_FW
        int ret = omni::application::m_ret;
        OMNI_SAFE_APP_UNLOCK_FW
        omni::application::exit(ret);
    #else
        omni::application::exit(omni::application::m_ret);
    #endif
}

//=============================END APP_NS METHODS=============================/
