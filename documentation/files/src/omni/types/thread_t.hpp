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
#if !defined(OMNI_THREAD_T_HPP)
#define OMNI_THREAD_T_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/thread_def.hpp>
#include <omni/string/util.hpp>
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
        class thread_priority
        {
            public:
                typedef enum enum_t {
                    IDLE = -15,
                    LOWEST = -2,
                    BELOW_NORMAL = -1,
                    NORMAL = 0,
                    ABOVE_NORMAL = 1,
                    HIGHEST = 2,
                    REAL_TIME = 15
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 7;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return NORMAL;
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

                static bool try_parse(const std::string& val, thread_priority& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, thread_priority& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                thread_priority() :
                    OMNI_CTOR_FW(omni::sync::thread_priority)
                    m_val(DEFAULT_VALUE())
                { }

                thread_priority(const thread_priority& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                thread_priority(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::thread_priority)
                    m_val(val)
                { }

                ~thread_priority()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
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

                bool operator!=(const thread_priority& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                thread_priority& operator=(const thread_priority& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                thread_priority& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                thread_priority& operator=(int32_t val)
                {
                    if (!thread_priority::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const thread_priority& val) const
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

                bool operator>(const thread_priority& val) const
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

                bool operator==(const thread_priority& val) const
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

                OMNI_MEMBERS_FW(omni::sync::thread_priority) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::sync::thread_priority)
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
                static bool _try_parse(const S& val, thread_priority& out)
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
                        OMNI_S2E_FW(IDLE)
                        OMNI_S2E_FW(LOWEST)
                        OMNI_S2E_FW(BELOW_NORMAL)
                        OMNI_S2E_FW(NORMAL)
                        OMNI_S2E_FW(ABOVE_NORMAL)
                        OMNI_S2E_FW(HIGHEST)
                        OMNI_S2E_FW(REAL_TIME)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(IDLE);
                        OMNI_E2SS_FW(LOWEST);
                        OMNI_E2SS_FW(BELOW_NORMAL);
                        OMNI_E2SS_FW(NORMAL);
                        OMNI_E2SS_FW(ABOVE_NORMAL);
                        OMNI_E2SS_FW(HIGHEST);
                        OMNI_E2SS_FW(REAL_TIME);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        IDLE ||
                        LOWEST ||
                        BELOW_NORMAL ||
                        NORMAL ||
                        ABOVE_NORMAL ||
                        HIGHEST ||
                        REAL_TIME
                    );
                }
        };
        
        class thread_start_type
        {
            public:
                typedef enum enum_t {
                    USER = 0,
                    NOW = 1
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 2;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return USER;
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

                static bool try_parse(const std::string& val, thread_start_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, thread_start_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                thread_start_type() :
                    OMNI_CTOR_FW(omni::sync::thread_start_type)
                    m_val(DEFAULT_VALUE())
                { }

                thread_start_type(const thread_start_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                thread_start_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::thread_start_type)
                    m_val(val)
                { }

                ~thread_start_type()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
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

                bool operator!=(const thread_start_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                thread_start_type& operator=(const thread_start_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                thread_start_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                thread_start_type& operator=(int32_t val)
                {
                    if (!thread_start_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const thread_start_type& val) const
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

                bool operator>(const thread_start_type& val) const
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

                bool operator==(const thread_start_type& val) const
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

                OMNI_MEMBERS_FW(omni::sync::thread_start_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::sync::thread_start_type)
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
                static bool _try_parse(const S& val, thread_start_type& out)
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
                        OMNI_S2E_FW(USER)
                        OMNI_S2E_FW(NOW)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(USER);
                        OMNI_E2SS_FW(NOW);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        USER ||
                        NOW
                    );
                }
        };
        
        class thread_state
        {
            public:
                typedef enum enum_t {
                    UNSTARTED = 0,
                    START_REQUESTED = 1,
                    RUNNING = 2,
                    COMPLETED = 4,
                    STOP_REQUESTED = 8,
                    STOPPED = 16,
                    ABORT_REQUESTED = 32,
                    ABORTED = 64,
                    UNKNOWN = 255
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 9;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSTARTED;
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

                static bool try_parse(const std::string& val, thread_state& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, thread_state& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                thread_state() :
                    OMNI_CTOR_FW(omni::sync::thread_state)
                    m_val(DEFAULT_VALUE())
                { }

                thread_state(const thread_state& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                thread_state(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::thread_state)
                    m_val(val)
                { }

                ~thread_state()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
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

                bool operator!=(const thread_state& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                thread_state& operator=(const thread_state& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                thread_state& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                thread_state& operator=(int32_t val)
                {
                    if (!thread_state::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const thread_state& val) const
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

                bool operator>(const thread_state& val) const
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

                bool operator==(const thread_state& val) const
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

                OMNI_MEMBERS_FW(omni::sync::thread_state) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::sync::thread_state)
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
                static bool _try_parse(const S& val, thread_state& out)
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
                        OMNI_S2E_FW(UNSTARTED)
                        OMNI_S2E_FW(START_REQUESTED)
                        OMNI_S2E_FW(RUNNING)
                        OMNI_S2E_FW(COMPLETED)
                        OMNI_S2E_FW(STOP_REQUESTED)
                        OMNI_S2E_FW(STOPPED)
                        OMNI_S2E_FW(ABORT_REQUESTED)
                        OMNI_S2E_FW(ABORTED)
                        OMNI_S2E_FW(UNKNOWN)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSTARTED);
                        OMNI_E2SS_FW(START_REQUESTED);
                        OMNI_E2SS_FW(RUNNING);
                        OMNI_E2SS_FW(COMPLETED);
                        OMNI_E2SS_FW(STOP_REQUESTED);
                        OMNI_E2SS_FW(STOPPED);
                        OMNI_E2SS_FW(ABORT_REQUESTED);
                        OMNI_E2SS_FW(ABORTED);
                        OMNI_E2SS_FW(UNKNOWN);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSTARTED ||
                        START_REQUESTED ||
                        RUNNING ||
                        COMPLETED ||
                        STOP_REQUESTED ||
                        STOPPED ||
                        ABORT_REQUESTED ||
                        ABORTED ||
                        UNKNOWN
                    );
                }
        };
        
        class thread_option
        {
            public:
                typedef enum enum_t {
                    NONE = 0,
                    ALLOW_THREAD_REUSE = 1,
                    AUTO_JOIN = 2,
                    DETACH_ON_DESTROY = 4, // default
                    ABORT_ON_DESTROY = 8,
                    KILL_ON_DESTROY = 16,
                    DETACH_ON_ASSIGN = 32, // default
                    ABORT_ON_ASSIGN = 64,
                    KILL_ON_ASSIGN = 128,
                    STACK_SIZE = 256,
                    AUTO_JOIN_TIMEOUT = 512
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 11;
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

                static bool try_parse(const std::string& val, thread_option& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, thread_option& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                thread_option() :
                    OMNI_CTOR_FW(omni::sync::thread_option)
                    m_val(DEFAULT_VALUE())
                { }

                thread_option(const thread_option& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                thread_option(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::thread_option)
                    m_val(val)
                { }

                ~thread_option()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
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

                bool operator!=(const thread_option& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                thread_option& operator=(const thread_option& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                thread_option& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                thread_option& operator=(int32_t val)
                {
                    if (!thread_option::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const thread_option& val) const
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

                bool operator>(const thread_option& val) const
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

                bool operator==(const thread_option& val) const
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

                OMNI_MEMBERS_FW(omni::sync::thread_option) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::sync::thread_option)
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
                static bool _try_parse(const S& val, thread_option& out)
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
                        OMNI_S2E_FW(ALLOW_THREAD_REUSE)
                        OMNI_S2E_FW(AUTO_JOIN)
                        OMNI_S2E_FW(DETACH_ON_DESTROY)
                        OMNI_S2E_FW(ABORT_ON_DESTROY)
                        OMNI_S2E_FW(KILL_ON_DESTROY)
                        OMNI_S2E_FW(DETACH_ON_ASSIGN)
                        OMNI_S2E_FW(ABORT_ON_ASSIGN)
                        OMNI_S2E_FW(KILL_ON_ASSIGN)
                        OMNI_S2E_FW(STACK_SIZE)
                        OMNI_S2E_FW(AUTO_JOIN_TIMEOUT)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(ALLOW_THREAD_REUSE);
                        OMNI_E2SS_FW(AUTO_JOIN);
                        OMNI_E2SS_FW(DETACH_ON_DESTROY);
                        OMNI_E2SS_FW(ABORT_ON_DESTROY);
                        OMNI_E2SS_FW(KILL_ON_DESTROY);
                        OMNI_E2SS_FW(DETACH_ON_ASSIGN);
                        OMNI_E2SS_FW(ABORT_ON_ASSIGN);
                        OMNI_E2SS_FW(KILL_ON_ASSIGN);
                        OMNI_E2SS_FW(STACK_SIZE);
                        OMNI_E2SS_FW(AUTO_JOIN_TIMEOUT);
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
                        ALLOW_THREAD_REUSE ||
                        AUTO_JOIN ||
                        DETACH_ON_DESTROY ||
                        ABORT_ON_DESTROY ||
                        KILL_ON_DESTROY ||
                        DETACH_ON_ASSIGN ||
                        ABORT_ON_ASSIGN ||
                        KILL_ON_ASSIGN ||
                        STACK_SIZE ||
                        AUTO_JOIN_TIMEOUT
                    );
                }
        };
        
        class thread_flags
        {
            public:
                thread_flags() : m_stack(0), m_timeout(0), m_flags(0) { }
                
                thread_flags(const omni::sync::thread_flags &cp) :
                    m_stack(cp.m_stack),
                    m_timeout(cp.m_timeout),
                    m_flags(cp.m_flags)
                { }
                
                thread_flags(std::size_t stack) :
                    m_stack(stack),
                    m_timeout(0),
                    m_flags(0)
                { }
                
                thread_flags(std::size_t stack, std::size_t timeout) :
                    m_stack(stack),
                    m_timeout(timeout),
                    m_flags(0)
                { }
                
                thread_flags(std::size_t stack, std::size_t timeout, unsigned char flags) :
                    m_stack(stack),
                    m_timeout(timeout),
                    m_flags(flags)
                { }
                
                thread_flags(std::size_t stack, std::size_t timeout, omni::sync::thread_option::enum_t flag) :
                    m_stack(stack),
                    m_timeout(timeout),
                    m_flags(0)
                {
                    this->set_flag(flag, true);
                }
                
                bool allow_reuse() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::ALLOW_THREAD_REUSE);
                }
                
                bool auto_join() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::AUTO_JOIN);
                }
                
                std::size_t auto_join_timeout() const
                {
                    return this->m_timeout;
                }
                
                bool abort_on_assign() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::ABORT_ON_ASSIGN);
                }
                
                bool abort_on_destroy() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::ABORT_ON_DESTROY);
                }
                
                bool detach_on_destroy() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::DETACH_ON_DESTROY);
                }
                
                bool detach_on_assign() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::DETACH_ON_ASSIGN);
                }
                
                bool kill_on_destroy() const
                {
                    return OMNI_VAL_HAS_FLAG_BIT(this->m_flags, omni::sync::thread_option::KILL_ON_DESTROY);
                }
                
                bool kill_on_assign() const
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
                        case omni::sync::thread_option::NONE:
                        default:
                            OMNI_ERRV_FW("invalid option: ", flag, omni::exceptions::invalid_thread_option(static_cast<std::size_t>(flag)))
                            break;
                    }
                }
                
                std::size_t stack_size() const
                {
                    return this->m_stack;
                }
                
                void set_auto_join_timeout(std::size_t timeout)
                {
                    this->m_timeout = timeout;
                }
                
                void set_stack_size(std::size_t stack)
                {
                    this->m_stack = stack;
                }
                
                bool operator==(const omni::sync::thread_flags& o) const
                {
                    return
                    (this->m_stack == o.m_stack &&
                    this->m_timeout == o.m_timeout &&
                    this->m_flags == o.m_flags);
                }
                
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
                // DEV_NOTE: since the thread union has a std::size_t type, the flags are also size_t

                std::size_t m_stack;
                std::size_t m_timeout;
                std::size_t m_flags;
        };

        typedef union thread_option_union {
            std::size_t s_val;
            bool b_val;
            
            thread_option_union(int32_t val) : s_val(static_cast<std::size_t>(val)) {}
            
            thread_option_union(long val) : s_val(static_cast<std::size_t>(val)) {}
            
            thread_option_union(std::size_t val) : s_val(val) {}
            
            thread_option_union(bool val) : b_val(val) {}
        } thread_option_union;
        
        // Types
        const uint32_t INFINITE_TIMEOUT = OMNI_INFINITE_TIMEOUT;
        typedef OMNI_THREAD_ARGS_T thread_arg_t;
        typedef OMNI_THREAD_T thread_t;
        typedef OMNI_THREAD_HANDLE_T thread_handle_t;
        typedef OMNI_THREAD_FNPTR_T thread_fnptr_t;
        typedef OMNI_THREAD_RET_T thread_ret_t;
        typedef omni::sync::thread_option_union thread_union_t;
        typedef omni::delegate<void> thread_start;
        typedef omni::delegate1<void, omni::sync::thread_arg_t> parameterized_thread_start;
        
        #if defined(OMNI_THROW)
            extern omni::action unhandled_thread_exception;
            extern omni::event1<void, const omni::exception&> user_thread_exception;
        #endif

        inline omni::sync::thread_handle_t thread_handle()
        {
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    return ::GetCurrentThread();
                #else
                    return reinterpret_cast<omni::sync::thread_handle_t>(::GetCurrentThread());
                #endif
            #else
                return ::pthread_self();
            #endif
        }
        
        inline omni::sync::thread_t thread_id()
        {
            #if defined(OMNI_OS_WIN)
                return ::GetCurrentThreadId();
            #else
                return ::pthread_self();
            #endif
        }
        
        inline bool join_thread(omni::sync::thread_handle_t handle, unsigned long timeout)
        {
            if (handle == 0) { 
                OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_HANDLE_STR, omni::exceptions::invalid_thread_handle(), false)
            }
            if (handle == omni::sync::thread_handle()) {
                OMNI_ERR_RETV_FW(OMNI_INVALID_THREAD_OWNER, omni::exceptions::invalid_thread_owner(), false)
            }
            #if defined(OMNI_OS_WIN)
                return (::WaitForSingleObject(OMNI_WIN_TOHNDL_FW(handle), timeout) == 0) ? true :
                    #if !defined(OMNI_DBG_L1)
                        false
                    #else
                        !(OMNI_DBGEV_FW("error while waiting for thread handle: ", OMNI_GLE_PRNT))
                    #endif
                ;
            #else
                /* There is not a portable mechanism with pthreads to wait on a specific thread without
                implementing a timed_wait condition variable. We do not want the user to have to implement
                a seperate variable based on system, so we implement a timeout loop*/
                if (timeout != omni::sync::INFINITE_TIMEOUT) {
                    #if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
                        omni::chrono::monotonic::initialize();
                    #endif
                    omni::chrono::tick_t ts = omni::chrono::monotonic_tick();
                    OMNI_SLEEP_INIT();
                    volatile bool iav = true;
                    //iav = (::pthread_kill(handle, 0) != ESRCH); // == "alive"
                    while ((iav = (::pthread_kill(handle, 0) != ESRCH)) && (omni::chrono::elapsed_ms(ts) < timeout)) {
                        OMNI_SLEEP1();
                    }
                    return (::pthread_kill(handle, 0) == ESRCH); // == "dead"
                }
                return (
                    (::pthread_join(handle, NULL) == 0) ? true :
                    #if !defined(OMNI_DBG_L1)
                        false
                    #else
                        !(OMNI_DBGEV_FW("error while waiting for thread handle: ", OMNI_GLE_PRNT))
                    #endif
                );
            #endif
        }
        
        inline bool join_thread(omni::sync::thread_handle_t handle)
        {
            return omni::sync::join_thread(handle, omni::sync::INFINITE_TIMEOUT);
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
