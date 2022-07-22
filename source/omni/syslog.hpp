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
#if !defined(OMNI_SYSLOG_HPP)
#define OMNI_SYSLOG_HPP
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/strings.hpp>
#include <streambuf>
#if defined(OMNI_OS_WIN)
#else
    #include <syslog.h>
#endif

// TODO: finish this
namespace omni {
    namespace logging {
        /** The enum template */
        class log_level
        {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    #if defined(OMNI_OS_WIN)
                        EMERGENCY,
                        ALERT,
                        CRITICAL,
                        ERROR,
                        WARNING,
                        NOTICE,
                        INFO,
                        DEBUG
                    #else
                        EMERGENCY = LOG_EMERG,
                        ALERT = LOG_ALERT,
                        CRITICAL = LOG_CRIT,
                        ERROR = LOG_ERR,
                        WARNING = LOG_WARNING,
                        NOTICE = LOG_NOTICE,
                        INFO = LOG_INFO,
                        DEBUG = LOG_DEBUG
                    #endif
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 8;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return INFO;
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
                static bool try_parse(const std::string& val, log_level& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, log_level& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                log_level() :
                    OMNI_CTOR_FW(omni::sync::log_level)
                    m_val(DEFAULT_VALUE())
                { }

                log_level(const log_level& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                log_level(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::log_level)
                    m_val(val)
                { }

                ~log_level()
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

                bool operator!=(const log_level& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                log_level& operator=(const log_level& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                log_level& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                log_level& operator=(int32_t val)
                {
                    if (!log_level::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const log_level& val) const
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

                bool operator>(const log_level& val) const
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

                bool operator==(const log_level& val) const
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

                OMNI_MEMBERS_FW(omni::system::log_level) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::system::log_level)
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
                static bool _try_parse(const S& val, log_level& out)
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
                        OMNI_S2E_FW(EMERGENCY)
                        OMNI_S2E_FW(ALERT)
                        OMNI_S2E_FW(CRITICAL)
                        OMNI_S2E_FW(ERROR)
                        OMNI_S2E_FW(WARNING)
                        OMNI_S2E_FW(NOTICE)
                        OMNI_S2E_FW(INFO)
                        OMNI_S2E_FW(DEBUG)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(EMERGENCY);
                        OMNI_E2SS_FW(ALERT);
                        OMNI_E2SS_FW(CRITICAL);
                        OMNI_E2SS_FW(ERROR);
                        OMNI_E2SS_FW(WARNING);
                        OMNI_E2SS_FW(NOTICE);
                        OMNI_E2SS_FW(INFO);
                        OMNI_E2SS_FW(DEBUG);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        EMERGENCY ||
                        ALERT ||
                        CRITICAL ||
                        ERROR ||
                        WARNING ||
                        NOTICE ||
                        INFO ||
                        DEBUG
                    );
                }
        };

        /*
            #include <ostream>
#include <streambuf>
#include <string>

#include <syslog.h>

namespace log
{

enum level
{
    emergency = LOG_EMERG,
    alert     = LOG_ALERT,
    critical  = LOG_CRIT,
    error     = LOG_ERR,
    warning   = LOG_WARNING,
    notice    = LOG_NOTICE,
    info      = LOG_INFO,
    debug     = LOG_DEBUG,
};

enum type
{
    auth   = LOG_AUTH,
    cron   = LOG_CRON,
    daemon = LOG_DAEMON,
    local0 = LOG_LOCAL0,
    local1 = LOG_LOCAL1,
    local2 = LOG_LOCAL2,
    local3 = LOG_LOCAL3,
    local4 = LOG_LOCAL4,
    local5 = LOG_LOCAL5,
    local6 = LOG_LOCAL6,
    local7 = LOG_LOCAL7,
    print  = LOG_LPR,
    mail   = LOG_MAIL,
    news   = LOG_NEWS,
    user   = LOG_USER,
    uucp   = LOG_UUCP,
};

}
*/
        
        class syslog : public std::basic_streambuf<char>
        {
            public:
                explicit syslog(const std::string& name, log::type type) :
                    std::basic_streambuf<char>()
                {
                    ::openlog(name.size() ? name.data() : nullptr, LOG_PID, type);
                }
                ~syslog() {
                    ::closelog();
                }

            protected:
                int_type overflow(int_type c = traits_type::eof())
                {
                    if (traits_type::eq_int_type(c, traits_type::eof())) {
                        sync();
                    } else {
                        buffer += traits_type::to_char_type(c);
                    }
                    return c;
                }

                int sync()
                {
                    if (buffer.size()) {
                        ::syslog(level, "%s", buffer.data());
                        buffer.clear();
                        level = ini_level;
                    }
                    return 0;
                }

                void set_level(log::level new_level) noexcept { level = new_level; }

            private:
                static constexpr log::level ini_level = log::info;
                log::level level = ini_level;

                std::string buffer;
        };
    }
}

#endif // OMNI_SYSLOG_HPP
