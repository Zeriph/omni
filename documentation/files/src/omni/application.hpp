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

        class run_type
        {
            public:
                typedef enum enum_t {
                    NONE = 0,
                    EXIT_WITH_WORK_THREAD = 1, 
                    KILL_WORKER_ON_SIGNAL = 2
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 3;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return NONE;
                }
                
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::string& val, run_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, run_type& out)
                {
                    return _try_parse(val, out);
                }

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
                    return (
                        OMNI_I2EV_FW(NONE) ||
                        OMNI_I2EV_FW(EXIT_WITH_WORK_THREAD) ||
                        OMNI_I2EV_FW(KILL_WORKER_ON_SIGNAL)
                    );
                }
        };
        
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

        inline int run(const omni::sync::thread_start& start_func, const omni::application::run_type& run_type)
        {
            return omni::application::run(start_func,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        inline int run(const int& argc, const char** argv, const omni::sync::thread_start& start_func, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const int& argc, const wchar_t** argv, const omni::sync::thread_start& start_func, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        int run(const omni::sync::parameterized_thread_start& start_func);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);
        
        inline int run(const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, const omni::application::run_type& run_type)
        {
            return omni::application::run(start_func, targs,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }

        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const int& argc, const char** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func, targs,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread);
        
        int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, bool exit_with_work_thread, bool kill_worker_on_signal);

        inline int run(const int& argc, const wchar_t** argv, const omni::sync::parameterized_thread_start& start_func, omni::generic_ptr targs, const omni::application::run_type& run_type)
        {
            return omni::application::run(argc, argv, start_func, targs,
                (run_type & omni::application::run_type::EXIT_WITH_WORK_THREAD),
                (run_type & omni::application::run_type::KILL_WORKER_ON_SIGNAL)
            );
        }
        
        void set_return_code(int return_code);
        
        void set_args(int argc, const char** argv);
        
        void set_args(int argc, const wchar_t** argv);
        
        void stop();
    }
}

#endif // OMNI_APPLICATION_HPP
