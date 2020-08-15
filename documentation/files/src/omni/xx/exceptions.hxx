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
 
/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. do not #include <omni/xxx_impl.hxx> and do not compile this source directly.
 this file is included directly in other source. 
 
 This file is specifically to contain the various exceptions the library can throw
 and is directly included in omni/exception.hpp so this file should not be included
 in any other code, library or user.
*/

// so as not to accidentally build this file with the source this macro defined in exception.hpp
#if !defined(OMNI_ERR_APPEND_FW)
    #error invalid preprocessor directive detected
#endif

namespace omni {
    namespace exceptions {
        class application_exception : public omni::exception
        {
            public:
                application_exception() : omni::exception(OMNI_ERR_APPEX_STR) {}
                application_exception(const char* msg, int er) : omni::exception(msg, er) {}
                application_exception(const char* msg, long er) : omni::exception(msg, er) {}
                explicit application_exception(const char* msg) : omni::exception(msg) {}
                explicit application_exception(int er) : omni::exception(OMNI_ERR_APPEX_STR, ": ", er) {}
                explicit application_exception(long er) : omni::exception(OMNI_ERR_APPEX_STR, ": ", er) {}
        };
        
        class environment_exception : public omni::exception
        {
            public:
                environment_exception() : omni::exception(OMNI_ERR_ENVEX_STR) {}
                explicit environment_exception(std::size_t err) : omni::exception(OMNI_ERR_ENVEX_STR, ": ", err) {}
                explicit environment_exception(const char* msg) : omni::exception(msg) {}
        };
        
        class mutex_system_exception : public omni::exception
        {
            public:
                mutex_system_exception() : omni::exception(OMNI_ERR_MUTEX_STR) {}
                explicit mutex_system_exception(int er) : omni::exception(OMNI_ERR_MUTEX_STR, ": ", er) {}
                explicit mutex_system_exception(long er) : omni::exception(OMNI_ERR_MUTEX_STR, ": ", er) {}
                explicit mutex_system_exception(const char* msg) : omni::exception(msg) {}
                mutex_system_exception(const char* msg, int er) : omni::exception(msg, er) {}
                mutex_system_exception(const char* msg, long er) : omni::exception(msg, er) {}
        };
        
        class semaphore_system_exception : public omni::exception
        {
            public:
                semaphore_system_exception() : omni::exception(OMNI_ERR_SEMAPHORE_STR) {}
                explicit semaphore_system_exception(int er) : omni::exception(OMNI_ERR_SEMAPHORE_STR, ": ", er) {}
                explicit semaphore_system_exception(long er) : omni::exception(OMNI_ERR_SEMAPHORE_STR, ": ", er) {}
                explicit semaphore_system_exception(const char* msg) : omni::exception(msg) {}
                semaphore_system_exception(const char* msg, int er) : omni::exception(msg, er) {}
                semaphore_system_exception(const char* msg, long er) : omni::exception(msg, er) {}
        };
        
        class string_exception : public omni::exception
        {
            public:
                string_exception() : omni::exception(OMNI_ERR_STROBJ_STR) {}
                explicit string_exception(const char* msg) : omni::exception(msg) {}
        };
        
        class thread_exception : public omni::exception
        {
            public:
                thread_exception() : omni::exception(OMNI_ERR_THREAD_STR) {}
                thread_exception(std::string msg, int perr) : omni::exception(msg, perr) {}
                thread_exception(std::string msg, std::size_t perr) : omni::exception(msg, perr) {}
                thread_exception(const char* msg, int perr) : omni::exception(msg, perr) {}
                thread_exception(const char* msg, std::size_t perr) : omni::exception(msg, perr) {}
                thread_exception(const char* msg, const char* extra, int perr) : omni::exception(msg, extra, perr) {}
                thread_exception(const char* msg, const char* extra, std::size_t perr) : omni::exception(msg, extra, perr) {}
                explicit thread_exception(const std::string& msg) : omni::exception(msg) {}
                explicit thread_exception(const char* msg) : omni::exception(msg) {}
                explicit thread_exception(int perr) : omni::exception(OMNI_ERR_THREAD_STR, ": ", perr) {}
                explicit thread_exception(std::size_t perr) : omni::exception(OMNI_ERR_THREAD_STR, ": ", perr) {}
        };
        
        class threadpool_exception : public omni::exception
        {
            public:
                threadpool_exception() : omni::exception(OMNI_ERR_THREADPOOL_STR) {}
                explicit threadpool_exception(const std::string& msg) : omni::exception(msg) {}
                explicit threadpool_exception(const char* msg) : omni::exception(msg) {}
        };
        
        class active_wait_exception : public omni::exception
        {
            public:
                active_wait_exception() : omni::exception(OMNI_ERR_WAIT_STR) {}
        };
        
        class clock_exception : public omni::exception
        {
            public:
                clock_exception() : omni::exception(OMNI_ERR_GET_TIME_STR) {}
                explicit clock_exception(int err) : omni::exception(OMNI_ERR_GET_TIME_STR, ": ", err) {}
        };
        
        class conditional_exception : public omni::exception
        {
            public:
                conditional_exception() : omni::exception(OMNI_ERR_COND_OBJ_STR) {}
                conditional_exception(int err) : omni::exception(OMNI_ERR_COND_OBJ_STR, ": ", err) {}
        };

        class nan_error : public omni::exception
        {
            public:
                nan_error() : omni::exception(OMNI_NAN_ERR_STR) {}
                explicit nan_error(const char* var) : omni::exception(OMNI_NAN_ERR_STR) {
                    if (var) {
                        this->m_what.append(": ");
                        this->m_what.append(var);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit nan_error(const std::string& var) : omni::exception(OMNI_NAN_ERR_STR) {
                    this->m_what.append(": ");
                    this->m_what.append(var);
                }
        };

        class overflow_error : public omni::exception
        {
            public:
                overflow_error() : omni::exception(OMNI_OVERFLOW_STR) {}
                explicit overflow_error(const char* var) : omni::exception(OMNI_OVERFLOW_STR) {
                    if (var) {
                        this->m_what.append(": ");
                        this->m_what.append(var);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit overflow_error(const std::string& var) : omni::exception(OMNI_OVERFLOW_STR) {
                    this->m_what.append(": ");
                    this->m_what.append(var);
                }
        };

        class underflow_error : public omni::exception
        {
            public:
                underflow_error() : omni::exception(OMNI_UNDERFLOW_STR) {}
                explicit underflow_error(const char* var) : omni::exception(OMNI_UNDERFLOW_STR) {
                    if (var) {
                        this->m_what.append(": ");
                        this->m_what.append(var);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit underflow_error(const std::string& var) : omni::exception(OMNI_UNDERFLOW_STR) {
                    this->m_what.append(": ");
                    this->m_what.append(var);
                }
        };
        
        class index_out_of_range : public omni::exception
        {
            public:
                index_out_of_range() : omni::exception(OMNI_INDEX_OOR_STR) {}
                index_out_of_range(const char* msg, std::size_t idx) : omni::exception(msg, idx) {}
                index_out_of_range(const std::string& msg, std::size_t idx) : omni::exception(msg, idx) {}
                explicit index_out_of_range(const char* var) : omni::exception(OMNI_INDEX_OOR_STR) {
                    if (var) {
                        this->m_what.append(": ");
                        this->m_what.append(var);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit index_out_of_range(const std::string& var) : omni::exception(OMNI_INDEX_OOR_STR) {
                    this->m_what.append(": ");
                    this->m_what.append(var);
                }
                explicit index_out_of_range(std::size_t idx) : omni::exception(OMNI_INDEX_OOR_STR) {
                    this->m_what.append(": ");
                    OMNI_ERR_APPEND_FW(idx);
                }
        };
        
        class invalid_application_state : public omni::exceptions::application_exception
        {
            public:
                invalid_application_state() : omni::exceptions::application_exception(OMNI_APP_RUNNING_STR) {}
        };
        
        class invalid_binary_format : public omni::exceptions::string_exception
        {
            public:
                invalid_binary_format() : omni::exceptions::string_exception(OMNI_STRING_INVALID_BINARY_FORMAT_STR) {}
        };
        
        class invalid_binary_size : public omni::exceptions::string_exception
        {
            public:
                invalid_binary_size() : omni::exceptions::string_exception(OMNI_STRING_INVALID_SIZE_STR) {}
        };
        
        class invalid_delegate : public omni::exception
        {
            public:
                invalid_delegate() : omni::exception(OMNI_INVALID_DELEGATE_FUNC_STR) {}
        };
        
        class invalid_delegate_invoke : public omni::exception
        {
            public:
                invalid_delegate_invoke() : omni::exception(OMNI_INVALID_DELEGATE_INVOKE_STR) {}
        };
        
        class invalid_environment_variable : public omni::exceptions::environment_exception
        {
            public:
                invalid_environment_variable() : omni::exceptions::environment_exception(OMNI_ERR_NAME_STR) {}
        };

        class invalid_enum : public omni::exception
        {
            public:
                invalid_enum() : omni::exception(OMNI_INVALID_ENUM) {}
                explicit invalid_enum(const char* name) : omni::exception(OMNI_INVALID_ENUM) {
                    if (name) {
                        this->m_what.append(": ");
                        this->m_what.append(name);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit invalid_enum(const std::string& name) : omni::exception(OMNI_INVALID_ENUM) {
                    this->m_what.append(": ");
                    this->m_what.append(name);
                }
                explicit invalid_enum(int val) : omni::exception(OMNI_INVALID_ENUM, ": ", val) { }
                explicit invalid_enum(uint32_t val) : omni::exception(OMNI_INVALID_ENUM, ": ", static_cast<std::size_t>(val)) { }
        };

        class invalid_parse : public omni::exception
        {
            public:
                invalid_parse() : omni::exception(OMNI_ERR_PARSE_STR) {}
                explicit invalid_parse(const char* msg) : omni::exception(msg) {}
        };
        
        class invalid_mutex_state : public omni::exceptions::mutex_system_exception
        {
            public:
                invalid_mutex_state() : omni::exceptions::mutex_system_exception(OMNI_ERR_MTX_STATE_STR) {}
        };
        
        class invalid_release_count : public omni::exceptions::semaphore_system_exception
        {
            public:
                invalid_release_count() : omni::exceptions::semaphore_system_exception(OMNI_ERR_RELEASE_STR) {}
        };

        class invalid_base : public omni::exception
        {
            public:
                invalid_base() : omni::exception(OMNI_ERR_BASE_STR) {}
                explicit invalid_base(const char* msg) : omni::exception(msg) {}
        };

        class invalid_range : public omni::exception
        {
            public:
                invalid_range() : omni::exception(OMNI_ERR_RANGE_STR) {}
                explicit invalid_range(const char* msg) : omni::exception(msg) {}
        };
        
        class invalid_size : public omni::exception
        {
            public:
                invalid_size() : omni::exception(OMNI_ERR_SIZE_STR) {}
        };
        
        class invalid_string_format : public omni::exceptions::string_exception
        {
            public:
                invalid_string_format() : omni::exceptions::string_exception(OMNI_STRING_INVALID_FORMAT_STR) {}
        };
        
        class invalid_template_type : public omni::exception
        {
            public:
                invalid_template_type() : omni::exception(OMNI_INVALID_TEMPLATE_STR) {}
        };
        
        class invalid_thread_state : public omni::exceptions::thread_exception
        {
            public:
               invalid_thread_state() : omni::exceptions::thread_exception(OMNI_INVALID_THREAD_STATE_STR) {}
        };
        
        class invalid_thread_handle : public omni::exceptions::thread_exception
        {
            public:
                invalid_thread_handle() : omni::exceptions::thread_exception(OMNI_INVALID_THREAD_HANDLE_STR) {}
        };
        
        class invalid_thread_option : public omni::exceptions::thread_exception
        {
            public:
                invalid_thread_option() : omni::exceptions::thread_exception(OMNI_INVALID_OPTION_STR) {}
                explicit invalid_thread_option(std::size_t var) : omni::exceptions::thread_exception(OMNI_INVALID_OPTION_STR, ": ", var) {}
        };
        
        class invalid_thread_owner : public omni::exceptions::thread_exception
        {
            public:
                invalid_thread_owner() : omni::exceptions::thread_exception(OMNI_INVALID_THREAD_OWNER) {}
        };
        
        class invalid_thread_start_type : public omni::exceptions::thread_exception
        {
            public:
                invalid_thread_start_type() : omni::exceptions::thread_exception(OMNI_INVALID_THREAD_START_TYPE_STR) {}
        };
        
        class invalid_threadpool_size : public omni::exceptions::threadpool_exception
        {
            public:
                invalid_threadpool_size() : omni::exceptions::threadpool_exception(OMNI_INVALID_SIZE_STR) {}
        };
        
        class invalid_type_cast : public omni::exception
        {
            public:
                invalid_type_cast() : omni::exception(OMNI_INVALID_CAST_STR) {}
        };
        
        class invalid_version : public omni::exception
        {
            public:
                invalid_version() : omni::exception(OMNI_INVALID_VERSION_STR) {}
        };
        
        class mutex_unlock_exception : public omni::exceptions::mutex_system_exception
        {
            public:
                mutex_unlock_exception() : omni::exceptions::mutex_system_exception(OMNI_ERR_MTX_UNLOCKED_STR) {}
        };
        
        class null_pointer_exception : public omni::exception
        {
            public:
                null_pointer_exception() : omni::exception(OMNI_NULL_REF_STR) {}
                explicit null_pointer_exception(const char* variable) : omni::exception(OMNI_NULL_REF_STR) {
                    if (variable) {
                        this->m_what.append(" on ");
                        this->m_what.append(variable);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit null_pointer_exception(const std::string& variable) : omni::exception(OMNI_NULL_REF_STR) {
                    this->m_what.append(" on ");
                    this->m_what.append(variable);
                }
        };
        
        class path_exception : public omni::exception
        {
            public:
                path_exception() : omni::exception(OMNI_PATH_ERROR) {}
                explicit path_exception(const char* path) : omni::exception(OMNI_PATH_ERROR) {
                    if (path) {
                        this->m_what.append(" on ");
                        this->m_what.append(path);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit path_exception(const std::string& path) : omni::exception(OMNI_PATH_ERROR) {
                    this->m_what.append(" on ");
                    this->m_what.append(path);
                }
        };

        class file_not_found : public omni::exception
        {
            public:
                file_not_found() : omni::exception(OMNI_FILE_NOT_FOUND_STR) {}
                explicit file_not_found(const char* path) : omni::exception(OMNI_FILE_NOT_FOUND_STR) {
                    if (path) {
                        this->m_what.append(": ");
                        this->m_what.append(path);
                    } else {
                        OMNI_DBGE(OMNI_NULL_PTR_STR);
                        OMNI_EXCEPTION_TERMINATE
                    }
                }
                explicit file_not_found(const std::string& path) : omni::exception(OMNI_FILE_NOT_FOUND_STR) {
                    this->m_what.append(": ");
                    this->m_what.append(path);
                }
        };

        class pipe_exception : public omni::exceptions::environment_exception
        {
            public:
                pipe_exception() : omni::exceptions::environment_exception(OMNI_ERR_PIPE_STR) {}
        };
        
        class semaphore_release_exception : public omni::exceptions::semaphore_system_exception
        {
            public:
                semaphore_release_exception() : omni::exceptions::semaphore_system_exception(OMNI_ERR_SEM_STATE_STR) {}
        };
        
        class spin_lock_exception : public omni::exception
        {
            public:
                spin_lock_exception() : omni::exception(OMNI_ERR_SPIN_OBJ_STR) {}
                spin_lock_exception(int err) : omni::exception(OMNI_ERR_SPIN_OBJ_STR, ": ", err) {}
        };
        
        class stopwatch_exception : public omni::exception
        {
            public:
                stopwatch_exception() : omni::exception(OMNI_ERR_STOPWATCH_STR) {}
                stopwatch_exception(const char* msg, int er) : omni::exception(msg, er) {}
                stopwatch_exception(const char* msg, long er) : omni::exception(msg ,er) {}
                explicit stopwatch_exception(const char* msg) : omni::exception(msg) {}
                explicit stopwatch_exception(int er) : omni::exception(OMNI_ERR_STOPWATCH_STR, ": ", er) {}
                explicit stopwatch_exception(long er) : omni::exception(OMNI_ERR_STOPWATCH_STR, ": ", er) {}
        };
        
        class thread_running_exception : public omni::exceptions::thread_exception
        {
            public:
                thread_running_exception() : omni::exceptions::thread_exception(OMNI_THREAD_STARTED_STR) {}
        };
        
        class threadpool_state_exception : public omni::exceptions::threadpool_exception
        {
            public:
                threadpool_state_exception() : omni::exceptions::threadpool_exception(OMNI_ERR_STATE_STR) {}
        };
        
        class threadpool_thread_exception : public omni::exceptions::threadpool_exception
        {
            public:
                threadpool_thread_exception() : omni::exceptions::threadpool_exception(OMNI_ERR_ACQUIRE_STR) {}
        };

        class socket_exception : public omni::exception
        {
            public:
                socket_exception() : omni::exception(OMNI_ERR_SOCKET_STR) {}
                socket_exception(const char* msg, int er) : omni::exception(msg, er) {}
                socket_exception(const char* msg, long er) : omni::exception(msg ,er) {}
                socket_exception(const char* msg, size_t er) : omni::exception(msg ,er) {}
                explicit socket_exception(const char* msg) : omni::exception(msg) {}
                explicit socket_exception(int er) : omni::exception(OMNI_ERR_SOCKET_STR, ": ", er) {}
                explicit socket_exception(long er) : omni::exception(OMNI_ERR_SOCKET_STR, ": ", er) {}
                explicit socket_exception(size_t er) : omni::exception(OMNI_ERR_SOCKET_STR, ": ", er) {}
        };
    } // namespace exceptions    
} // namespace omni
