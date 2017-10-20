/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
#if !defined(OMNI_THREAD_T_HPP)
#define OMNI_THREAD_T_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/thread_def.hpp>
#include <omni/types/string_t.hpp>
#include <omni/util/bits.hpp>
#include <omni/generic_ptr.hpp>
#include <omni/chrono/tick.hpp>
#include <omni/delegate/0.hpp>
#include <omni/delegate/1.hpp>
#include <omni/delegate/2.hpp>
#include <omni/defs/consts.hpp>

namespace omni {
    namespace sync {
        /** The priority structure defines enum values for the scheduling priority of a process or thread. */
        typedef struct thread_priority {
            /** The underlying enum type exposed via the parent priority structure */
            typedef enum enum_t {
                /** Defines an idle thread priority */
                IDLE = -15,
                /** Defines a low thread priority */
                LOWEST = -2,
                /** Defines a below normal thread priority */
                BELOW_NORMAL = -1,
                /** Defines a normal thread priority */
                NORMAL = 0,
                /** Defines an above normal thread priority */
                ABOVE_NORMAL = 1,
                /** Defines a highest thread priority */
                HIGHEST = 2,
                /** Defines a real time thread priority */
                REAL_TIME = 15
            } enum_t;
            /** Defines the number of elements in the priority enum */
            static const unsigned short COUNT = 7;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(IDLE);
                    OMNI_E2S_FW(LOWEST);
                    OMNI_E2S_FW(BELOW_NORMAL);
                    OMNI_E2S_FW(NORMAL);
                    OMNI_E2S_FW(ABOVE_NORMAL);
                    OMNI_E2S_FW(HIGHEST);
                    OMNI_E2S_FW(REAL_TIME);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(IDLE);
                    OMNI_E2WS_FW(LOWEST);
                    OMNI_E2WS_FW(BELOW_NORMAL);
                    OMNI_E2WS_FW(NORMAL);
                    OMNI_E2WS_FW(ABOVE_NORMAL);
                    OMNI_E2WS_FW(HIGHEST);
                    OMNI_E2WS_FW(REAL_TIME);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } thread_priority;
        
        /** The thread start type (immediate or user) */
        typedef struct thread_start_type {
            /** The underlying enum type expected */
            typedef enum enum_t {
                /** Defines the thread will start when the user calls the start method */
                USER = 0,
                /** Defines the thread will start after construction is complete */
                NOW = 1
            } enum_t;
            /** Defines the number of elements in the start_type enum */
            static const unsigned short COUNT = 2;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(USER);
                    OMNI_E2S_FW(NOW);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(USER);
                    OMNI_E2WS_FW(NOW);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } thread_start_type;
        
        /** The state structure defines enum values for the execution status of thread types */
        typedef struct thread_state {
            /** The underlying enum type exposed via the parent state structure */
            typedef enum enum_t {
                /** Defines a thread as unstarted (default when created) */
                UNSTARTED = 0,
                /** Defines a thread is attempting to spawn */
                START_REQUESTED = 1,
                /** Defines a thread is running (method has been called) */
                RUNNING = 2,
                /** Defines a thread has completed its function (method complete) */
                COMPLETED = 4,
                /** Defines a thread has a stop request (kill request) */
                STOP_REQUESTED = 8,
                /** Defines a thread is stopped (killed) */
                STOPPED = 16,
                /** Defines a thread has an abort request */
                ABORT_REQUESTED = 32,
                /** Defines a thread has been aborted */
                ABORTED = 64,
                /** Defines a thread has a state that can not be determined (when creating threads from handles for instance) */
                UNKNOWN = 255
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 9;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(UNSTARTED);
                    OMNI_E2S_FW(START_REQUESTED);
                    OMNI_E2S_FW(RUNNING);
                    OMNI_E2S_FW(COMPLETED);
                    OMNI_E2S_FW(STOP_REQUESTED);
                    OMNI_E2S_FW(STOPPED);
                    OMNI_E2S_FW(ABORT_REQUESTED);
                    OMNI_E2S_FW(ABORTED);
                    OMNI_E2S_FW(UNKNOWN); // pedant
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(UNSTARTED);
                    OMNI_E2WS_FW(START_REQUESTED);
                    OMNI_E2WS_FW(RUNNING);
                    OMNI_E2WS_FW(COMPLETED);
                    OMNI_E2WS_FW(STOP_REQUESTED);
                    OMNI_E2WS_FW(STOPPED);
                    OMNI_E2WS_FW(ABORT_REQUESTED);
                    OMNI_E2WS_FW(ABORTED);
                    OMNI_E2WS_FW(UNKNOWN); // pedant
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } thread_state;
        
        /** Defines the thread options structure allowing finer control of a thread object */
        typedef struct thread_option {
            /** The underlying enum type exposed via the parent thread_option structure */
            typedef enum enum_t {
                /** Defines the option to set if the thread shall allow reuse of the thread */
                ALLOW_THREAD_REUSE = 1,
                /** Defines the option to auto join a thread on destruction */
                AUTO_JOIN = 2,
                DETACH_ON_DESTROY = 4, // default
                ABORT_ON_DESTROY = 8,
                KILL_ON_DESTROY = 16,
                DETACH_ON_ASSIGN = 32, // default
                ABORT_ON_ASSIGN = 64,
                KILL_ON_ASSIGN = 128,
                /** Defines the option to set if the thread shall have a specified stack size */
                STACK_SIZE = 256,
                /** Defines the option to set if the thread timeout for join operation on kill_on_eop */
                AUTO_JOIN_TIMEOUT = 512
            } enum_t;
            
            /** Defines the number of elements in the thread_option enum */
            static const unsigned short COUNT = 10;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(ALLOW_THREAD_REUSE);
                    OMNI_E2S_FW(AUTO_JOIN);
                    OMNI_E2S_FW(DETACH_ON_DESTROY);
                    OMNI_E2S_FW(ABORT_ON_DESTROY);
                    OMNI_E2S_FW(KILL_ON_DESTROY);
                    OMNI_E2S_FW(DETACH_ON_ASSIGN);
                    OMNI_E2S_FW(ABORT_ON_ASSIGN);
                    OMNI_E2S_FW(KILL_ON_ASSIGN);
                    OMNI_E2S_FW(STACK_SIZE);
                    OMNI_E2S_FW(AUTO_JOIN_TIMEOUT);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(ALLOW_THREAD_REUSE);
                    OMNI_E2WS_FW(AUTO_JOIN);
                    OMNI_E2WS_FW(DETACH_ON_DESTROY);
                    OMNI_E2WS_FW(ABORT_ON_DESTROY);
                    OMNI_E2WS_FW(KILL_ON_DESTROY);
                    OMNI_E2WS_FW(DETACH_ON_ASSIGN);
                    OMNI_E2WS_FW(ABORT_ON_ASSIGN);
                    OMNI_E2WS_FW(KILL_ON_ASSIGN);
                    OMNI_E2WS_FW(STACK_SIZE);
                    OMNI_E2WS_FW(AUTO_JOIN_TIMEOUT);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } thread_option;
        
        /** Defines the union type used to set specific thread options. */
        typedef union thread_option_union {
            /** Defines the std::size_t value of this union */
            std::size_t s_val;
            /** Defines the boolean value of this union */
            bool b_val;
            
            /**
             * This constructor is templated to avoid ambiguous name resolution errors
             * with the more specialized bool/std::size_t constructors. A compile error 
             * will be generated if this template constructor is utilized since it's
             * an error to initialize both members of a union in a constructor.
             * 
             * @param val   Not used
             * @tparam T    Not used
             */
            // TODO: this generates an error in clang, regardless of the fact that it's not utilized
            // template < typename T > thread_option_union(T val) : s_val(0), b_val(false) {}
            
            /**
             * Create a new union based on the specified numeric value.
             * 
             * @param val   The value to set to this union
             */
            thread_option_union(int val) : s_val(static_cast<std::size_t>(val)) {}
            
            /**
             * Create a new union based on the specified numeric value.
             * 
             * @param val   The value to set to this union
             */
            thread_option_union(long val) : s_val(static_cast<std::size_t>(val)) {}
            
            /**
             * Create a new union based on the specified numeric value.
             * 
             * @param val   The value to set to this union
             */
            thread_option_union(std::size_t val) : s_val(val) {}
            
            /**
             * Create a new union based on the specified boolean value.
             * 
             * @param val   The value to set to this union
             */
            thread_option_union(bool val) : b_val(val) {}
        } thread_option_union;
        
        /** Defines the thread option flag structure allowing finer control of a thread object */
        typedef struct thread_flags {
            public:
                /** The default constructor */
                thread_flags() : m_stack(0), m_timeout(0), m_flags(0) { }
                
                /**
                 * The copy constructor
                 *
                 * @param cp    The other structure to copy
                 */
                thread_flags(const omni::sync::thread_flags &cp) :
                    m_stack(cp.m_stack),
                    m_timeout(cp.m_timeout),
                    m_flags(cp.m_flags)
                { }
                
                /**
                 * Stack size constructor; initializes the structure with specified stack size
                 * (specifically non-explicit constructor)
                 *
                 * @param stack    The stack size to set
                 */
                thread_flags(std::size_t stack) :
                    m_stack(stack),
                    m_timeout(0),
                    m_flags(0)
                { }
                
                /**
                 * Initializes the class with specified stack size and timeout
                 * 
                 * @param stack    The stack size to set
                 * @param timeout  The timeout on auto-join
                 */
                thread_flags(std::size_t stack, std::size_t timeout) :
                    m_stack(stack),
                    m_timeout(timeout),
                    m_flags(0)
                { }
                
                /**
                 * Initializes the class with specified stack size and timeout
                 * 
                 * @param stack     The stack size to set
                 * @param timeout   The timeout on auto-join
                 * @param flags     The flag bit mask to set
                 */
                thread_flags(std::size_t stack, std::size_t timeout, unsigned char flags) :
                    m_stack(stack),
                    m_timeout(timeout),
                    m_flags(flags)
                { }
                
                /**
                 * Initializes the class with specified stack size and timeout
                 * 
                 * @param stack     The stack size to set
                 * @param timeout   The timeout on auto-join
                 * @param flag      The flag bit to set
                 */
                thread_flags(std::size_t stack, std::size_t timeout, omni::sync::thread_option::enum_t flag) :
                    m_stack(stack),
                    m_timeout(timeout),
                    m_flags(0)
                {
                    this->set_flag(flag, true);
                }
                
                inline bool allow_reuse() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::ALLOW_THREAD_REUSE);
                }
                
                inline bool auto_join() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::AUTO_JOIN);
                }
                
                inline std::size_t auto_join_timeout() const
                {
                    return this->m_timeout;
                }
                
                inline bool abort_on_assign() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::ABORT_ON_ASSIGN);
                }
                
                inline bool abort_on_destroy() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::ABORT_ON_DESTROY);
                }
                
                inline bool detach_on_destroy() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::DETACH_ON_DESTROY);
                }
                
                inline bool detach_on_assign() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::DETACH_ON_ASSIGN);
                }
                
                inline bool kill_on_destroy() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::KILL_ON_DESTROY);
                }
                
                inline bool kill_on_assign() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::KILL_ON_ASSIGN);
                }
                
                void set_flag(omni::sync::thread_option::enum_t flag, bool val)
                {
                    switch (flag) {
                        case omni::sync::thread_option::ALLOW_THREAD_REUSE:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::ALLOW_THREAD_REUSE, val);
                            break;
                        case omni::sync::thread_option::AUTO_JOIN:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::AUTO_JOIN, val);
                            break;
                        case omni::sync::thread_option::DETACH_ON_DESTROY:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::DETACH_ON_DESTROY, val);
                            break;
                        case omni::sync::thread_option::ABORT_ON_DESTROY:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::ABORT_ON_DESTROY, val);
                            break;
                        case omni::sync::thread_option::KILL_ON_DESTROY:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::KILL_ON_DESTROY, val);
                            break;
                        case omni::sync::thread_option::DETACH_ON_ASSIGN:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::DETACH_ON_ASSIGN, val);
                            break;
                        case omni::sync::thread_option::ABORT_ON_ASSIGN:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::ABORT_ON_ASSIGN, val);
                            break;
                        case omni::sync::thread_option::KILL_ON_ASSIGN:
                            OMNI_VAL_SET_FLAG_BOOL_T(unsigned char, this->m_flags, omni::sync::thread_option::KILL_ON_ASSIGN, val);
                            break;
                        case omni::sync::thread_option::STACK_SIZE:
                        case omni::sync::thread_option::AUTO_JOIN_TIMEOUT:
                        default:
                            OMNI_ERRV_FW("invalid option: ", flag, omni::exceptions::invalid_thread_option(static_cast<std::size_t>(flag)))
                            break;
                    }
                }
                
                inline std::size_t stack_size() const
                {
                    return this->m_stack;
                }
                
                inline void set_auto_join_timeout(std::size_t timeout)
                {
                    this->m_timeout = timeout;
                }
                
                inline void set_stack_size(std::size_t stack)
                {
                    this->m_stack = stack;
                }
                
                /**
                 * Equality operator tests if objects are equal
                 * 
                 * @param o     The other structure to test
                 */
                bool operator==(const omni::sync::thread_flags& o) const
                {
                    return
                    (this->m_stack == o.m_stack &&
                    this->m_timeout == o.m_timeout &&
                    this->m_flags == o.m_flags);
                }
                
                /**
                 * Assignment operator sets values from the other object
                 * 
                 * @param o     The other structure to assign from
                 */
                omni::sync::thread_flags& operator=(const omni::sync::thread_flags& o)
                {
                    if (this != &o) {
                        this->m_stack = o.m_stack;
                        this->m_timeout = o.m_timeout;
                        this->m_flags = o.m_flags;
                    }
                    return *this;
                }
                
            private:
                /**
                 * The threads stack size. If the thread is in running state,
                 * the new stack size will not take effect until the next run.
                 */
                std::size_t m_stack;
                /**
                 * If timeout_on_eop is >0 and kill_on_eop has been set for a thread,
                 * when an external operation is being applied, the thread will attempt
                 * to abort and join for the specified timeout before killing the thread
                 */
                std::size_t m_timeout;
                /**
                 * The underlying bit mask for the flags of this structure. A bit
                 * mask on an unsigned type is used to conserve space instead of
                 * using 9 bool types, we use 1 size type, additionally, the checks
                 * for the various flags should not be called in any sort of loop.
                 */
                std::size_t m_flags;
        } thread_flags;
        
        // Types
        /** Defines the platform infinite time out value */
        const unsigned long INFINITE_TIMEOUT = OMNI_INFINITE_TIMEOUT;
        /** Defines the thread argument parameter type (i.e. void* or omni::generic_ptr) */
        typedef OMNI_THREAD_ARGS_T thread_arg_t;
        /** Defines the platform thread type */
        typedef OMNI_THREAD_T thread_t;
        /** Defines the platform thread handle type */
        typedef OMNI_THREAD_HANDLE_T thread_handle_t;
        /** Defines the platform thread function pointer type (void* / int, etc) */
        typedef OMNI_THREAD_FNPTR_T thread_fnptr_t;
        /** Defines the platform thread function return type */
        typedef OMNI_THREAD_RET_T thread_ret_t;
        /** Defines an alias to the priority enum type */
        typedef omni::sync::thread_priority::enum_t thread_priority_t;
        /** Defines an alias to the start_type enum type */
        typedef omni::sync::thread_start_type::enum_t thread_start_type_t;
        /** Defines an alias to the state enum type */
        typedef omni::sync::thread_state::enum_t thread_state_t;
        /** Defines an alias to the thread_option enum type */
        typedef omni::sync::thread_option::enum_t thread_option_t;
        /** An alias type to the omni::thread_option_union */
        typedef omni::sync::thread_option_union thread_union_t;
        /** Defines the signature for a thread start delegate taking no arguments */
        typedef omni::delegate<void> thread_start;
        /** Defines the signature for a thread start delegate taking the default void* argument */
        typedef omni::delegate1<void, omni::sync::thread_arg_t> parameterized_thread_start;
        
        #if defined(OMNI_THROW)
            extern omni::action unhandled_thread_exception;
            extern omni::event1<void, const omni::exception&> user_thread_exception;
        #endif
        
        /**
         * Blocks the calling thread until the thread passed in has finished
         * executing (by normal means or cancellation) or the specified timeout
         * has been reached, which ever happens first.
         * 
         * @param timeout   The timeout (in milliseconds) to wait for a thread to finish
         * 
         * @return True if the thread has been joined successfully, false if the operation
         *         times out or there was an error
         */
        inline bool join_thread(omni::sync::thread_handle_t handle, unsigned long timeout)
        {
            if (handle == 0) { 
                OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle(), false)
            }
            #if defined(OMNI_OS_WIN)
                return (::WaitForSingleObject(OMNI_WIN_TOHNDL_FW(handle), timeout) == 0); // Returns 0 on success
            #else
                /* There is not a portable mechanism with pthreads to wait on a specific thread without
                implementing a timed_wait condition variable. We don't want the user to have to implement
                a seperate variable based on system, so we implement a 'timeout' loop*/
                if (timeout != omni::sync::INFINITE_TIMEOUT) {
                    omni::chrono::tick_t ts = omni::chrono::monotonic_tick();
                    OMNI_SLEEP_INIT();
                    volatile bool iav = true;
                    //iav = (::pthread_kill(handle, 0) != ESRCH); // == "alive"
                    while ((iav = (::pthread_kill(handle, 0) != ESRCH)) && (omni::chrono::elapsed_ms(ts) < timeout)) {
                        OMNI_SLEEP1();
                    }
                    return (::pthread_kill(handle, 0) == ESRCH); // == "dead"
                }
                return (::pthread_join(handle, NULL) == 0); // Returns 0 on success
            #endif
        }
        
        /**
         * Blocks the calling thread until the thread passed in has finished
         * executing (by normal means or cancellation).
         * 
         * @return True on success, false otherwise
         */
        inline bool join_thread(omni::sync::thread_handle_t handle)
        {
            if (handle == 0) {
                OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle(), false)
            }
            #if defined(OMNI_OS_WIN)
                return (::WaitForSingleObject(OMNI_WIN_TOHNDL_FW(handle), INFINITE) == 0); // Returns 0 on success
            #else
                return (::pthread_join(handle, NULL) == 0); // Returns 0 on success
            #endif
        }
        
        template < void (*fnptr)() >
        static omni::sync::thread_start bind()
        {
            return omni::sync::thread_start::bind<fnptr>();
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread_start bind(T& obj)
        {
            return omni::sync::thread_start::bind<T, fnptr>(obj);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread_start bind(const T& obj)
        {
            return omni::sync::thread_start::bind<T, fnptr>(obj);
        }

        template < class T, void (T::*fnptr)() >
        static omni::sync::thread_start bind(const T *const obj)
        {
            return omni::sync::thread_start::bind<T, fnptr>(obj);
        }
        
        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread_start bind_const(const T& obj)
        {
            return omni::sync::thread_start::bind<T, fnptr>(obj);
        }

        template < class T, void (T::*fnptr)() const >
        static omni::sync::thread_start bind_const(const T *const obj)
        {
            return omni::sync::thread_start::bind<T, fnptr>(obj);
        }
        
        template < void (*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::parameterized_thread_start bind_param()
        {
            return omni::sync::parameterized_thread_start::bind<fnptr>();
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::parameterized_thread_start bind_param(T& obj)
        {
            return omni::sync::parameterized_thread_start::bind<T, fnptr>(obj);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::parameterized_thread_start bind_param(const T& obj)
        {
            return omni::sync::parameterized_thread_start::bind<T, fnptr>(obj);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) >
        static omni::sync::parameterized_thread_start bind_param(const T *const obj)
        {
            return omni::sync::parameterized_thread_start::bind<T, fnptr>(obj);
        }
        
        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::parameterized_thread_start bind_param_const(const T& obj)
        {
            return omni::sync::parameterized_thread_start::bind<T, fnptr>(obj);
        }

        template < class T, void (T::*fnptr)(omni::sync::thread_arg_t) const >
        static omni::sync::parameterized_thread_start bind_param_const(const T *const obj)
        {
            return omni::sync::parameterized_thread_start::bind<T, fnptr>(obj);
        }
    }
}

#endif // OMNI_THREAD_T_HPP
