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
#include <omni/sync/threadpool.hpp>
#include <string>
#include <csignal>

namespace omni {
    namespace application {
        namespace signal_handler {
            typedef omni::delegate1<void, int> callback;
            
            void attach(const omni::application::signal_handler::callback& sig_func);
            
            void detach(const omni::application::signal_handler::callback& sig_func);
            
            void ignore(bool doignore);
        }
        
        namespace exit_handler {
            void attach(const omni::callback& exit_func);
            
            void detach(const omni::callback& exit_func);
        }
        
        namespace startup_handler {
            void attach(const omni::callback& start_func);
            
            void detach(const omni::callback& start_func);
        }
        
        namespace shutdown_handler {
            void attach(const omni::callback& shutdown_func);
            
            void detach(const omni::callback& shutdown_func);
        }
        
        namespace terminate_handler {
            void attach(const omni::callback& terminate_func);
            
            void detach(const omni::callback& terminate_func);
        }
        
        omni::application::argparser& args();
        
        inline uint32_t bit_width()
        { return OMNI_SIZEOF_BITS(char*); }
        
        void exit(int exit_status);
        
        inline void exit()
        { omni::application::exit(0); }
        
        int last_signal();
        
        int run();

        int run(const int& argc, const char** argv);

        int run(const int& argc, const wchar_t** argv);
        
        int run(const omni::sync::thread_start& start_func);
        
        int run(const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);

        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);

        int run(const omni::sync::parameterized_thread_start& start_func);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        void set_return_code(int return_code);
        
        void set_args(int argc, const char** argv);
        
        void set_args(int argc, const wchar_t** argv);
        
        void stop();
    }
}

#endif // OMNI_APPLICATION_HPP
