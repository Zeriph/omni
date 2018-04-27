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
#if !defined(OMNI_APPLICATION_HPP)
#define OMNI_APPLICATION_HPP 1
#include <omni/types/char_t.hpp>
#include <omni/delegate/0.hpp>
#include <omni/delegate/1.hpp>
#include <omni/argparser.hpp>
#include <omni/exception.hpp>
#include <omni/sync/threadpool.hpp> // #include <omni/thread.hpp>
#include <string>
#include <csignal>

namespace omni {
    /**
     * @brief The @c application namespace contains functionality that can
     * be used application wide, to include signal handling or application run contexts.
     * 
     * @details The @c application namespace can be utilized to block the main
     * thread to avoid early program termination, attach and detach signal handlers as well
     * as startup and shutdown handlers. The namespace contains functionality that applies
     * to an application wide context, such as the bit size (32/64 bit), arguments passed
     * in or the last signal received on the application.
     * 
     * @warning Some functions within the namespace will only work if you have explicitly
     * called one of the omni::application::run functions to block the main thread until
     * program completion.
     * 
     * @attention Certain functions within the @c application namespace make use
     * of different platform specific API's; make sure to take note of any details in this
     * section when targeting specific platforms if things are not as expected.
     */ 
    namespace application {
        /**
         * @brief The @c signal_handler namespace is used to facilitate receiving
         * system signals in the application.
         * 
         * @details The @c signal_handler namespace contains functions and
         * definitions that can be used to attach and detach application wide
         * signal handlers to receive signals (like @c SIGABRT, @c SIGSEGV, or
         * @c SIGINT). The signal handler function must return a @c void type and
         * take a single @c int parameter, that is, it must adhere to the function
         * signature of an  omni::application::signal_handler::callback.
         * 
         * @exception If an exception occurs on an attached delegate, it will be handled according
         * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion.
         * 
         * @attention On Windows based platforms, this will listen for the system
         * signal events (as described), as well as set the console control handler,
         * which can handle other signals as well (such as the @c CTRL_LOGOFF_EVENT
         * or @c CTRL_SHUTDOWN_EVENT).
         * 
         * @note Since the signals can be raised on different threads, it's important
         * to take care of any multi-threaded issues that might arise when using any
         * of the signal handlers.
         */
        namespace signal_handler {
            /**
             * @brief Defines the signal handler function signature; that of <code>void signal_handler(int sig)</code>
             * 
             * @details The callback function handler can be used to bind directly to a signal handler
             * function, or you can simply pass the address of a static function to the handler functions.
             * 
             * @exception If an exception occurs on an attached delegate, it will be handled according
             * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
             */
            typedef omni::delegate1<void, int> callback;
            
            /**
             * @brief Attaches a delegate to the underlying system signal handler.
             * 
             * @details Attaching to the application signal handler will allow you to
             * listen for signals sent by the system. These can be signals like
             * @c SIGABRT, @c SIGSEGV, or @c SIGINT,
             * but can also be user signals sent via the system's signal command
             * (some platforms can issue specific signals). When a delegate is attached
             * it will be invoked in the order it was attached.
             *
             * @exception If an exception occurs on an attached delegate, it will be handled according
             * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @attention On Windows based platforms, this will listen for the
             * system signal events (as described), as well as set the console
             * control handler, which can handle other signals as well (such as the
             * @c CTRL_LOGOFF_EVENT or @c CTRL_SHUTDOWN_EVENT).
             * 
             * @note Since the signals can be raised on different threads, it's important
             * to take care of any multi-threaded issues that might arise when using any
             * of the signal handlers. Ensure the functions are re-entrant.
             * 
             * @param sig_func  The omni::application::signal_handler::callback function
             *                  delegate to attach to the signal handler event.
             */
            void attach(const omni::application::signal_handler::callback& sig_func);
            
            /**
             * @brief Detaches a delegate from the underlying system signal handler.
             * 
             * @details Detaching a specific delegate will stop that function from
             * receiving system signal events. Detaching a delegate that has not
             * been initially attached has no effect.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @attention On Windows based platforms, this will also detach from the
             * system signal events (as described), as well as the console control handler.
             * 
             * @param sig_func  The omni::application::signal_handler::callback function
             *                  delegate to detach from the signal handler event.
             */
            void detach(const omni::application::signal_handler::callback& sig_func);
            
            /**
             * @brief If set, the application will ignore any subsequent signals sent.
             * 
             * @details If @c ignore is called with value of @c true then all signals
             * sent to the application will be ignored until the function is called
             * again with a value of @c false passed in. If a signal is sent while
             * @c ignore is true, the last signal sent will still be set but no handlers
             * will be invoked.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Since the signals can be raised on different threads, it's important
             * to take care of any multi-threaded issues that might arise when using any
             * of the signal handlers.
             * 
             * @param doignore  If true, application will ignore subsequent signals sent.
             *                  A value of @c false will resume normal capture operations.
             */
            void ignore(bool doignore);
        }
        
        /**
         * @brief The @c exit_handler namespace facilitates functions that
         * allow invoking a delegate before the main program terminates.
         * 
         * @details If an omni::application::run function is called, the std::atexit
         * standard library function is bound to an internal function which in turn
         * calls any attached exit handler delegates. The exit handler delegates are called
         * after omni::application::shutdown_handler and before the program terminates.
         * 
         * @exception If an exception occurs on an attached delegate, it will be handled according
         * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion.
         * 
         * @note This handler is called before the main program exits whereas the
         * omni::application::shutdown_handler is called before the function
         * omni::application::run return.
         */
        namespace exit_handler {
            /**
             * @brief Attach a delegate function to the exit handler event.
             * 
             * @details When a delegate is attached to the underlying exit handler,
             * the delegate will be invoked before the application terminates in the
             * order it was attached. 
             * 
             * A static framework function is registered to the std::atexit library function 
             * when omni::application::run is called; this underlying function is responsible
             * for invoking any delegates attached to the exit event handler in the order they
             * were attached.
             * 
             * Since the exit handler will be invoked when the main function of the program
             * is returning, a call to @c attach can be made before or after the @c run context
             * has been invoked and the handlers will be called accordingly.
             * 
             * @exception If an exception occurs on an attached delegate, it will be handled according
             * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Be aware that the std::atexit function will call any functions
             * in the reverse order registered. So if omni::application::run is called
             * after any other calls to register a function with std::atexit
             * in user code, then the underlying exit handler event will be called
             * accordingly in the order attached; in other words, if you were to call
             * @c std::atexit(&some_function) then attach an exit handler
             * and call omni::application::run, the Omni exit handler will be called
             * first, then @c some_function last.
             * 
             * @param exit_func The omni::callback delegate function to attach.
             */
            void attach(const omni::callback& exit_func);
            
            /**
             * @brief Detach a delegate function from the exit handler event.
             * 
             * @details Detaches a delegate function from the exit handler event.
             * Detaching a delegate that has not been initially attached has no effect.
             * 
             * Since the exit handler will be invoked when the main function of the program
             * is returning, a call to @c detach can be made before or after the @c run
             * context has been invoked and the handlers will be called accordingly.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @param exit_func The omni::callback delegate function to attach.
             */
            void detach(const omni::callback& exit_func);
        }
        
        /**
         * @brief The @c startup_handler namespace facilitates functions that
         * allow invoking a delegate before the main application thread blocks.
         * 
         * @details If an omni::application::run function is called and a startup handler
         * is attached, the handlers are invoked in the order they are attached during the
         * omni::application::run invocation. The startup handlers are called immediately
         * before any user supplied thread functions and before the underlying base application
         * loop runs. The run context is blocked and will not continue until the startup handlers
         * have been invoked and return.
         * 
         * @exception If an exception occurs on an attached delegate, it will be handled according
         * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion.
         */
        namespace startup_handler {
            /**
             * @brief Attaches an omni::callback delegate to the application startup handler.
             * 
             * @details Attaching an omni::callback will register the delegate with the
             * application startup event. The startup event is called immediately before
             * any user supplied thread functions and before the underlying base application
             * loop runs. The run context is blocked and will not continue (thus not calling
             * the user thread functions or main loop) until all attached handlers have
             * been invoked and return.
             * 
             * @exception If an exception occurs on an attached delegate, it will be handled according
             * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Calling this function after the run context has entered the main
             * application loop will have no effect on the startup handler since
             * it will have already been called.
             * 
             * @param start_func    The omni::callback to attach to the startup event.
             */
            void attach(const omni::callback& start_func);
            
            /**
             * @brief Detaches an omni::callback delegate from the application startup handler.
             * 
             * @details Detaches an omni::callback that was first attached via the
             * omni::application::startup_handler::attach function. If the @c callback
             * was never first attached, this function has no effect.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Calling this function after the run context has entered the main
             * application loop will have no effect on the startup handler since
             * it will have already been called.
             * 
             * @param start_func    The omni::callback to detach from the startup event.
             */
            void detach(const omni::callback& start_func);
        }
        
        /**
         * @brief The @c shutdown_handler namespace facilitates functions that
         * allow invoking a function before the omni::application::run context returns.
         * 
         * @details If an omni::application::run function is called, any attached shutdown
         * handler delegates will be called in the order attached. The handler is called
         * immediately before omni::application::run returns, allowing you to preform any
         * actions needed (like adjust the return signal) before hand.
         * 
         * @exception If an exception occurs on an attached delegate, it will be handled according
         * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion.
         * 
         * @note This handler is called before the omni::application::run function returns
         * whereas the omni::application::exit_handler is called before the program exits.
         */
        namespace shutdown_handler {
            /**
             * @brief Attach an omni::callback delegate to the application shutdown event.
             * 
             * @details When a delegate is attached to the underlying shutdown handler,
             * the delegate will be invoked before the omni::application::run function
             * returns in the order it was attached.
             * 
             * Calling this function after an omni::application::run context has returned
             * will have no effect since the @c run function will have already returned
             * thus calling the delegates.
             * 
             * @exception If an exception occurs on an attached delegate, it will be handled according
             * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Be aware that the std::atexit function will call any functions
             * in the reverse order registered. So if omni::application::run is called
             * after any other calls to register a function with std::atexit
             * in user code, then the underlying exit handler event will be called
             * accordingly in order attached; in other words, if you were to call
             * @c std::atexit(&some_function) then @c shutdown_handler::attach(&some_func)
             * and call omni::application::run, the Omni exit handler will be called
             * first, then @c some_function last. Calling this function after the shutdown
             * handler has been called will have no effect on the handler since it will
             * have already been called.
             * 
             * @param shutdown_func The omni::callback delegate function to attach.
             */
            void attach(const omni::callback& shutdown_func);
            
            /**
             * @brief Detach an omni::callback delegate from the application shutdown event.
             * 
             * @details Detaches an omni::callback that was first attached via the
             * omni::application::shutdown_handler::attach function. If the @c callback
             * was never first attached, this function has no effect.
             * 
             * Calling this function after an omni::application::run context has returned
             * will have no effect since the @c run function will have already returned
             * thus calling the delegates.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Calling this function after the shutdown handler has been called will
             * have no effect on the handler since it will have already been called.
             * 
             * @param shutdown_func The omni::callback delegate function to detach.
             */
            void detach(const omni::callback& shutdown_func);
        }
        
        /**
         * @brief The @c terminate_handler namespace facilitates functions that
         * allow invoking a function when std::terminate has been called.
         * 
         * @details If an omni::application::run function is executed and std::terminate is
         * invoked, any terminate handler delegates will be called in the order they were
         * attached. The handler delegates are called before any exit handlers attached
         * via omni::application::exit_handler are invoked.
         * 
         * @exception If an exception occurs on an attached delegate, it will be handled according
         * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion.
         */
        namespace terminate_handler {
            /**
             * @brief Attach an omni::callback delegate to the terminate handler.
             * 
             * @details If std::terminate is invoked after having called an
             * omni::application::run context, any attached delegates will be invoked
             * in the order they were attached.
             * 
             * Since the terminate handler deals specifically with handling the
             * invocation of std::terminate, a call to @c attach can be made before
             * or after the @c run context has been invoked and the handlers will be
             * called accordingly.
             * 
             * @exception If an exception occurs on an attached delegate, it will be handled according
             * to omni::sync::user_thread_exception and omni::sync::unhandled_thread_exception.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @note Be aware that the std::atexit function will call any functions
             * in the reverse order registered. So if omni::application::run is called
             * after any other calls to register a function with std::atexit
             * in user code, then the underlying exit handler event will be called
             * accordingly in order attached; in other words, if you were to call
             * @c std::atexit(&some_function) then @c shutdown_handler::attach(&some_func)
             * and call omni::application::run, the Omni exit handler will be called
             * first, then @c some_function last.
             * 
             * @param terminate_func The omni::callback delegate function to attach.
             */
            void attach(const omni::callback& terminate_func);
            
            /**
             * @brief Detach a delegate function from the terminate handler event.
             * 
             * @details Detaches a delegate function from the terminate handler event.
             * Detaching a delegate that has not been initially attached has no effect.
             * 
             * Since the terminate handler deals specifically with handling the
             * invocation of std::terminate, a call to @c attach can be made before
             * or after the @c run context has been invoked and the handlers will be
             * called accordingly.
             * 
             * @warning This function will only have an effect if you have explicitly
             * called one of the omni::application::run functions to block the main
             * thread until program completion.
             * 
             * @param terminate_func    The omni::callback delegate function to attach.
             */
            void detach(const omni::callback& terminate_func);
        }
        
        /**
         * @brief Gets the application wide argument parser set via
         * either an omni::application::run context or directly via
         * omni::application::set_args.
         * 
         * @details If omni::application::run or omni::application::set_args
         * is called passing in the command line arguments from the main
         * function, the reference returned has a copy of same arguments.
         * 
         * @warning The value returned is a direct reference to the underlying
         * @c argparser object, so any modifications done to the reference after
         * it has be retrieved cannot be guaranteed to be thread safe.
         * 
         * @return A reference to the application wide omni::application::argparser
         */
        omni::application::argparser& args();
        
        /**
         * @brief Gets the current application's bit width (i.e. 32 or 64 bit)
         * 
         * @details Gets the current application context bit width by retrieving
         * the size of a pointer and multiplying by CHAR_BIT; returns the following
         * code <code>(sizeof(char*) * CHAR_BIT)</code>. This does not affirm if a
         * processor type is a specific bit width, e.g. a 32-bit application calling
         * this function would return 32 even if run on a 64-bit machine.
         * 
         * @return An unsigned integer value of the current bit width.
         */
        inline unsigned int bit_width()
        { return OMNI_SIZEOF_BITS(char*); }
        
        /**
         * @brief Exits the main application with a specified return value.
         * 
         * @details If omni::application::run has been called and is blocking, @c exit will
         * signal the underlying @c run function to continue thus calling any shutdown handlers
         * attached via omni::application::shutdown_handler::attach, after which the delegates
         * registered with the omni::application::exit_handler will be invoked finally calling
         * std::exit after all handlers have been invoked, passing in the @c exit_status value.
         * 
         * @param exit_status   The exit status value to pass to the underlying
         *                      exit function system call.
         */
        void exit(int exit_status);
        
        /**
         * @brief Exits the main application with a return value of 0.
         * 
         * @details Invokes omni::application::exit passing a 0 value
         * for the exit status.
         */
        inline void exit()
        { omni::application::exit(0); }
        
        /**
         * @brief Gets the last signal received by this application.
         * 
         * @details If a call to an omni::application::run context has been made
         * and a signal is received (e.g. @c SIGABRT or @c SIGSEGV), this function
         * will return the last signal received.
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion.
         * 
         * @attention The number value returned can vary between platforms for the
         * different signals. For example, @c SIGINT on Windows has the value of 0
         * while on some *nix systems, the value is 2, which might lead to confusion
         * expecting a 0 value to mean a @c SUCCESS value. To this, if you are checking
         * the signal value for a specific value, be sure to check against the specific
         * signal itself, i.e. <code>if (omni::application::last_signal() == SIGINT)</code>
         * 
         * @return The integer value of the last signal received.
         */
        int last_signal();
        
        int run();
        
        int run(const omni::sync::parameterized_thread_start& start_func);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const char** argv);
        
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const wchar_t** argv);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const omni::sync::thread_start& start_func);
        
        /**
         * @brief Sets the value returned from an omni::application::run function
         * or the exit status passed if omni::application::stop is called.
         * 
         * @details The return value of the omni::application::run functions can be
         * explicitly set via @c set_return_code as well this function set the exit
         * status code returned should omni::application::stop be called. 
         * 
         * @warning This function will only have an effect if you have explicitly
         * called one of the omni::application::run functions to block the main
         * thread until program completion or explicitly call omni::application::stop.
         * 
         * @param return_code   The integer value to return.
         */
        void set_return_code(int return_code);
        
        /**
         * @brief Sets the command line arguments passed in to
         * the underlying omni::application::argparser instance.
         * 
         * @details If you wish to retrieve the arguments passed
         * to your application via the command line through the
         * omni::application::args function, you will need to call
         * this function passing in the argument count and a pointer
         * to the argument array.
         * 
         * @exception It is undefined behavior if @c argc is less than
         * the actual number of elements in the argument array.
         * 
         * @warning Care needs to be taken with argument handling as neither
         * this function nor any functions in the @c argparser class do any
         * argument validation (i.e. user input validation).
         * 
         * @param argc  The argument count passed in to the application.
         * @param argv  A pointer to the array of @c char arguments passed to 
         *              application via command line.
         */
        void set_args(const int& argc, const char** argv);
        
        /**
         * @brief Sets the command line arguments passed in to
         * the underlying omni::application::argparser instance.
         * 
         * @details If you wish to retrieve the arguments passed
         * to your application via the command line through the
         * omni::application::args function, you will need to call
         * this function passing in the argument count and a pointer
         * to the argument array.
         * 
         * @exception It is undefined behavior if @c argc is less than
         * the actual number of elements in the argument array.
         * 
         * @warning Care needs to be taken with argument handling as neither
         * this function nor any functions in the @c argparser class do any
         * argument validation (i.e. user input validation).
         * 
         * @param argc  The argument count passed in to the application.
         * @param argv  A pointer to the array of @c wchar_t arguments
         *              passed to application via command line.
         */
        void set_args(const int& argc, const wchar_t** argv);
        
        /**
         * @brief Exits the main application with a return value specified
         * by omni::application::set_return_code.
         * 
         * @details Invokes omni::application::exit passing in the value
         * retrieved from omni::application::set_return_code as the @c exit_status
         * for the @c exit function.
         */
        void stop();
    }
}

#endif // OMNI_APPLICATION_HPP
