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
     * of different platform specific APIs; make sure to take note of any details in this
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
         * @note Since the signals can be raised on different threads, it is important
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
             * but can also be user signals sent via the systems signal command
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
             * @note Since the signals can be raised on different threads, it is important
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
             * @note Since the signals can be raised on different threads, it is important
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
             * A static library function is registered to the std::atexit library function 
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

        /** The enum template */
        class run_type
        {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    NONE = 0,
                    EXIT_WITH_WORK_THREAD = 1, 
                    KILL_WORKER_ON_SIGNAL = 2
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return NONE;
                }
                
                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, run_type& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, run_type& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                run_type() :
                    OMNI_CTOR_FW(omni::application::run_type)
                    m_val(DEFAULT_VALUE())
                { }

                run_type(const run_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                run_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::application::run_type)
                    m_val(val)
                { }

                run_type(int val) : 
                    OMNI_CTOR_FW(omni::application::run_type)
                    m_val(static_cast<enum_t>(val))
                { }

                ~run_type()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }
                
                unsigned short count()
                {
                    return COUNT();
                }
                
                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const run_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                run_type& operator=(const run_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                run_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                run_type& operator=(int32_t val)
                {
                    if (!run_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                run_type operator|(const run_type& val)
                {
                    return run_type(static_cast<enum_t>(this->m_val | val.m_val));
                }

                run_type operator|(enum_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val | val));
                }

                run_type operator|(int32_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val | val));
                }

                run_type& operator|=(const run_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                run_type& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                run_type& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                run_type operator&(const run_type& val)
                {
                    return run_type(static_cast<enum_t>(this->m_val & val.m_val));
                }

                run_type operator&(enum_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val & val));
                }

                run_type operator&(int32_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val & val));
                }

                run_type& operator&=(const run_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                run_type& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                run_type& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                run_type& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                run_type operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    run_type ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                run_type& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                run_type operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    run_type ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                run_type operator~()
                {
                    return run_type(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                run_type operator^(const run_type& val)
                {
                    return run_type(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                run_type operator^(enum_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val ^ val));
                }

                run_type operator^(int32_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val ^ val));
                }

                run_type& operator^=(const run_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                run_type& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                run_type& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                run_type operator<<(const run_type& val)
                {
                    return run_type(static_cast<enum_t>(this->m_val << val.m_val));
                }

                run_type operator<<(enum_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val << val));
                }

                run_type operator<<(int32_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val << val));
                }

                run_type& operator<<=(const run_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                run_type& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                run_type& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                run_type operator>>(const run_type& val)
                {
                    return run_type(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                run_type operator>>(enum_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val >> val));
                }

                run_type operator>>(int32_t val)
                {
                    return run_type(static_cast<enum_t>(this->m_val >> val));
                }

                run_type& operator>>=(const run_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                run_type& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                run_type& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const run_type& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const run_type& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const run_type& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::application::run_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::application::run_type)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    OMNI_ERR_FW("invalid enum parse", omni::exceptions::invalid_enum())
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, run_type& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(NONE)
                        OMNI_S2E_FW(EXIT_WITH_WORK_THREAD)
                        OMNI_S2E_FW(KILL_WORKER_ON_SIGNAL)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(EXIT_WITH_WORK_THREAD);
                        OMNI_E2SS_FW(KILL_WORKER_ON_SIGNAL);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        NONE ||
                        EXIT_WITH_WORK_THREAD ||
                        KILL_WORKER_ON_SIGNAL
                    );
                }
        };
        
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
         * @brief Gets the current applications bit width (i.e. 32/64-bit)
         * 
         * @details Gets the current application context bit width by retrieving
         * the size of a pointer and multiplying by CHAR_BIT; returns the following
         * code <code>(sizeof(char*) * CHAR_BIT)</code>. This does not affirm if a
         * processor type is a specific bit width, e.g. a 32-bit application calling
         * this function would return 32 even if run on a 64-bit machine.
         * 
         * @return An unsigned integer value of the current bit width.
         */
        inline uint32_t bit_width()
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
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         */
        int run();

        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         */
        int run(const int& argc, const char** argv);

        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         */
        int run(const int& argc, const wchar_t** argv);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         */
        int run(const omni::sync::thread_start& start_func);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         */
        int run(const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         * @param kill_worker_on_signal     If this is @c true and the background application thread is
         *                                  still active when a signal is received, it is forcefully
         *                                  killed. If this happens, the application will be in an
         *                                  undefined state as forcefully killing a thread is not
         *                                  guaranteed to stop the thread.
         */
        int run(const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const omni::sync::thread_start& start_func, const omni::application::run_type& run_type)
        {
            return omni::application::run(start_func,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         */
        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         * @param kill_worker_on_signal     If this is @c true and the background application thread is
         *                                  still active when a signal is received, it is forcefully
         *                                  killed. If this happens, the application will be in an
         *                                  undefined state as forcefully killing a thread is not
         *                                  guaranteed to stop the thread.
         */
        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        inline int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         */
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         * @param kill_worker_on_signal     If this is @c true and the background application thread is
         *                                  still active when a signal is received, it is forcefully
         *                                  killed. If this happens, the application will be in an
         *                                  undefined state as forcefully killing a thread is not
         *                                  guaranteed to stop the thread.
         */
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started. A null value will be passed
         *                                  to the start function on invocation.
         */
        int run(const omni::sync::parameterized_thread_start& start_func);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         */
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         */
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         * @param kill_worker_on_signal     If this is @c true and the background application thread is
         *                                  still active when a signal is received, it is forcefully
         *                                  killed. If this happens, the application will be in an
         *                                  undefined state as forcefully killing a thread is not
         *                                  guaranteed to stop the thread.
         */
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        inline int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, const omni::application::run_type& run_type)
        {
            return omni::application::run(start_func, targs,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         */
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         * @param kill_worker_on_signal     If this is @c true and the background application thread is
         *                                  still active when a signal is received, it is forcefully
         *                                  killed. If this happens, the application will be in an
         *                                  undefined state as forcefully killing a thread is not
         *                                  guaranteed to stop the thread.
         */
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func, targs,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         */
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        /**
         * @brief Starts the main application thread loop.
         * 
         * @details This function is part of the application framework that allows you to
         * hook in to certain system level functionality, as well as have access to other
         * long running application contexts. This function will pause the main application
         * until one of either omni::application::exit or omni::application::stop are called,
         * or an exception is thrown and not caught. Along with the other variants of the
         * run function, you can simplify argument and main program loop handling for global
         * and multi-threaded environments in a more simplified way.
         * 
         * @return The exit code set by omni::application::set_return_code, or 0 if none is set.
         * 
         * @exception Since run need only be called once, if it is called again after being called
         * at program start, it will throw an omni::exceptions::invalid_application_state as calling
         * run more than once will cause the system to get into an undefined state.
         * 
         * @warning You cannot utilize the signal or application handlers unless this or one of its
         * variants are called in the main function of your code or library initialization routine.
         * 
         * @note If OMNI_NO_BASE_SETLOCALE is not defined, then the setlocale function is called
         * with a category LC_ALL and an empty locale. If you wish to specify which category and
         * locale to utilize, you can define OMNI_BASE_LOCALE_CATEGORY and OMNI_BASE_LOCALE
         * 
         * @param argc                      Passes the argument count from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param argv                      Passes the argument array from the command line to the
         *                                  underlying omni::application::argparser instance.
         * @param start_func                An omni::sync::parameterized_thread_start function object
         *                                  that will be called after the application context has been
         *                                  successfully created and started.
         * @param targs                     The arguments to pass to the thread start function.
         * @param exit_with_work_thread     If this is @c true then the main application loop will exit
         *                                  when the user function passed in has completed. If this
         *                                  is @c false then the main application loop will not exit until
         *                                  it is signaled via the system (i.e. SIGINT, etc.), or until
         *                                  omni::application::exit or omni::application::stop are called.
         * @param kill_worker_on_signal     If this is @c true and the background application thread is
         *                                  still active when a signal is received, it is forcefully
         *                                  killed. If this happens, the application will be in an
         *                                  undefined state as forcefully killing a thread is not
         *                                  guaranteed to stop the thread.
         */
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func, targs,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }
        
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
         * @exception It is undefined behaviour if @c argc is less than
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
        void set_args(int argc, const char** argv);
        
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
         * @exception It is undefined behaviour if @c argc is less than
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
        void set_args(int argc, const wchar_t** argv);
        
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
