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
#if !defined(OMNI_DATE_T_HPP)
#define OMNI_DATE_T_HPP 1
#include <omni/defs/date_def.hpp>
#include <omni/chrono/span.hpp>

namespace omni {
    namespace chrono {
        typedef omni::chrono::span<int64_t> time_span;

        #if !defined(OMNI_NO_CONSTS)
        
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_YEAR OMNI_EXT_ASSN_FW(OMNI_DAYS_PER_YEAR); // non-leap
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_LEAP_YEAR OMNI_EXT_ASSN_FW(OMNI_DAYS_PER_LEAP_YEAR);
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_4_YEARS OMNI_EXT_ASSN_FW(OMNI_DAYS_PER_4_YEARS); // 365 * 4 + 1 leap day

        // DEV_NOTE: from https://www.grc.nasa.gov/www/k-12/Numbers/Math/Mathematical_Thinking/calendar_calculations.htm
        OMNI_CONSTEXT_FW const double DAYS_PER_TROPICAL_YEAR OMNI_EXT_ASSN_FW(OMNI_DAYS_PER_TROPICAL_YEAR);

        // DEV_NOTE: These values are to keep in line with the .NET library
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_100_YEARS OMNI_EXT_ASSN_FW(OMNI_DAYS_PER_100_YEARS); // DAYS_PER_4_YEARS * 25 - 1
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_400_YEARS OMNI_EXT_ASSN_FW(OMNI_DAYS_PER_400_YEARS); // DAYS_PER_100_YEARS * 4 + 1
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_1601AD OMNI_EXT_ASSN_FW(OMNI_DAYS_TO_1601AD); // Number of days from 1/1/0001 to 12/31/1600 -> DAYS_PER_400_YEARS * 4
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_1899AD OMNI_EXT_ASSN_FW(OMNI_DAYS_TO_1899AD); // Number of days from 1/1/0001 to 12/30/1899 -> DAYS_PER_400_YEARS * 4 + DAYS_PER_100_YEARS * 3 - 367;
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_1970AD OMNI_EXT_ASSN_FW(OMNI_DAYS_TO_1970AD); // Number of days from 1/1/0001 to 12/31/1969 ->  DAYS_PER_400_YEARS * 4 + DAYS_PER_100_YEARS * 3 + OMNI_DAYS_PER_4_YEARS * 17 + OMNI_DAYS_PER_YEAR
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_EPOCH OMNI_EXT_ASSN_FW(OMNI_DAYS_TO_EPOCH); // Alias to DAYS_TO_1970AD
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_10000AD OMNI_EXT_ASSN_FW(OMNI_DAYS_TO_10000AD); // Number of days from 1/1/0001 to 12/31/9999 -> DAYS_PER_400_YEARS * 25 - 366
        OMNI_CONSTEXT_FW const int64_t TICKS_TO_10000AD OMNI_EXT_ASSN_FW(OMNI_TICKS_TO_10000AD); // DAYS_TO_10000AD * TICKS_PER_DAY - 1;
        OMNI_CONSTEXT_FW const int64_t MILLISECONDS_TO_10000AD OMNI_EXT_ASSN_FW(OMNI_MILLISECONDS_TO_10000AD); // DAYS_TO_10000AD * MILLISECONDS_PER_DAY;
        OMNI_CONSTEXT_FW const int64_t FILE_TIME_OFFSET OMNI_EXT_ASSN_FW(OMNI_FILE_TIME_OFFSET); // DAYS_TO_1601AD * TICKS_PER_DAY;
        OMNI_CONSTEXT_FW const int64_t DOUBLE_DATE_OFFSET OMNI_EXT_ASSN_FW(OMNI_DOUBLE_DATE_OFFSET); // DAYS_TO_1899AD * TICKS_PER_DAY;
        OMNI_CONSTEXT_FW const int64_t EPOCH_OFFSET OMNI_EXT_ASSN_FW(OMNI_EPOCH_OFFSET); // DAYS_TO_EPOCH * TICKS_PER_DAY;
        // The minimum OA date is 0100/01/01 (Note it is year 100).
        // The maximum OA date is 9999/12/31
        OMNI_CONSTEXT_FW const int64_t OA_DATE_MIN_AS_TICKS OMNI_EXT_ASSN_FW(OMNI_OA_DATE_MIN_AS_TICKS); // (DAYS_PER_100_YEARS - DAYS_PER_YEAR) * TICKS_PER_DAY;
        OMNI_CONSTEXT_FW const double  OA_DATE_MIN_AS_DOUBLE OMNI_EXT_ASSN_FW(OMNI_OA_DATE_MIN_AS_DOUBLE); // All OA dates must be greater than (not >=) OA_DATE_MIN_AS_DOUBLE
        OMNI_CONSTEXT_FW const double  OA_DATE_MAX_AS_DOUBLE OMNI_EXT_ASSN_FW(OMNI_OA_DATE_MAX_AS_DOUBLE); // All OA dates must be less than (not <=) OA_DATE_MAX_AS_DOUBLE

        #if defined(OMNI_NO_EXTERN_CONSTS)
            const int32_t DAYS_TO_MONTH_365[] = OMNI_DAYS_TO_MONTH_365;
            const int32_t DAYS_TO_MONTH_366[] = OMNI_DAYS_TO_MONTH_366;
        #else
            extern const int32_t DAYS_TO_MONTH_365[13];
            extern const int32_t DAYS_TO_MONTH_366[13];
        #endif

        #endif

        class date_time_kind
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = 0,
                    UTC = 1,
                    LOCAL = 2,
                    LOCAL_DST = 3
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 4;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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

                static bool try_parse(const std::string& val, date_time_kind& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, date_time_kind& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                date_time_kind() :
                    OMNI_CTOR_FW(omni::chrono::date_time_kind)
                    m_val(DEFAULT_VALUE())
                { }

                date_time_kind(const date_time_kind& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                date_time_kind(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::date_time_kind)
                    m_val(val)
                { }

                ~date_time_kind()
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

                bool operator!=(const date_time_kind& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                date_time_kind& operator=(const date_time_kind& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                date_time_kind& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                date_time_kind& operator=(int32_t val)
                {
                    if (!date_time_kind::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const date_time_kind& val) const
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

                bool operator>(const date_time_kind& val) const
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

                bool operator==(const date_time_kind& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::date_time_kind) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::date_time_kind)
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
                static bool _try_parse(const S& val, date_time_kind& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(UTC)
                        OMNI_S2E_FW(LOCAL)
                        OMNI_S2E_FW(LOCAL_DST)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(UTC);
                        OMNI_E2SS_FW(LOCAL);
                        OMNI_E2SS_FW(LOCAL_DST);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(UNSPECIFIED) ||
                        OMNI_I2EV_FW(UTC) ||
                        OMNI_I2EV_FW(LOCAL) ||
                        OMNI_I2EV_FW(LOCAL_DST)
                    );
                }
        };

        class date_time_parse_failure
        {
            public:
                typedef enum enum_t {
                    NONE = 0,
                    ARGUMENT_NULL = 1,
                    FORMAT = 2,
                    FORMAT_WITH_PARAMETER = 3,
                    FORMAT_BAD_DATE_TIME_CALENDAR = 4
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 5;
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

                static bool try_parse(const std::string& val, date_time_parse_failure& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, date_time_parse_failure& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                date_time_parse_failure() :
                    OMNI_CTOR_FW(omni::chrono::date_time_parse_failure)
                    m_val(DEFAULT_VALUE())
                { }

                date_time_parse_failure(const date_time_parse_failure& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                date_time_parse_failure(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::date_time_parse_failure)
                    m_val(val)
                { }

                ~date_time_parse_failure()
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

                bool operator!=(const date_time_parse_failure& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                date_time_parse_failure& operator=(const date_time_parse_failure& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                date_time_parse_failure& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                date_time_parse_failure& operator=(int32_t val)
                {
                    if (!date_time_parse_failure::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const date_time_parse_failure& val) const
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

                bool operator>(const date_time_parse_failure& val) const
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

                bool operator==(const date_time_parse_failure& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::date_time_parse_failure) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::date_time_parse_failure)
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
                static bool _try_parse(const S& val, date_time_parse_failure& out)
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
                        OMNI_S2E_FW(ARGUMENT_NULL)
                        OMNI_S2E_FW(FORMAT)
                        OMNI_S2E_FW(FORMAT_WITH_PARAMETER)
                        OMNI_S2E_FW(FORMAT_BAD_DATE_TIME_CALENDAR)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(ARGUMENT_NULL);
                        OMNI_E2SS_FW(FORMAT);
                        OMNI_E2SS_FW(FORMAT_WITH_PARAMETER);
                        OMNI_E2SS_FW(FORMAT_BAD_DATE_TIME_CALENDAR);
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
                        OMNI_I2EV_FW(ARGUMENT_NULL) ||
                        OMNI_I2EV_FW(FORMAT) ||
                        OMNI_I2EV_FW(FORMAT_WITH_PARAMETER) ||
                        OMNI_I2EV_FW(FORMAT_BAD_DATE_TIME_CALENDAR)
                    );
                }
        };

        class date_time_styles
        {
            public:
                typedef enum enum_t {
                    NONE                    = 0x00000000,
                    ALLOW_LEADING_WHITE     = 0x00000001, 
                    ALLOW_TRAILING_WHITE    = 0x00000002, // Bitflag indicating trailing whitespace is allowed.
                    ALLOW_INNER_WHITE       = 0x00000004,
                    ALLOW_WHITE_SPACES      = 0x00000001 | 0x00000004 | 0x00000002,    
                    NO_CURRENT_DATE_DEFAULT = 0x00000008,
                    ADJUST_TO_UNIVERSAL     = 0x00000010,
                    ASSUME_LOCAL            = 0x00000020,
                    ASSUME_UNIVERSAL        = 0x00000040,
                    ROUNDTRIP_KIND          = 0x00000080
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 10;
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

                static bool try_parse(const std::string& val, date_time_styles& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, date_time_styles& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                date_time_styles() :
                    OMNI_CTOR_FW(omni::chrono::date_time_styles)
                    m_val(DEFAULT_VALUE())
                { }

                date_time_styles(const date_time_styles& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                date_time_styles(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::date_time_styles)
                    m_val(val)
                { }

                ~date_time_styles()
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

                bool operator!=(const date_time_styles& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                date_time_styles& operator=(const date_time_styles& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                date_time_styles& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                date_time_styles& operator=(int32_t val)
                {
                    if (!date_time_styles::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                date_time_styles operator|(const date_time_styles& val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val | val.m_val));
                }

                date_time_styles operator|(enum_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val | val));
                }

                date_time_styles operator|(int32_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val | val));
                }

                date_time_styles& operator|=(const date_time_styles& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                date_time_styles& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                date_time_styles& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                date_time_styles operator&(const date_time_styles& val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val & val.m_val));
                }

                date_time_styles operator&(enum_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val & val));
                }

                date_time_styles operator&(int32_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val & val));
                }

                date_time_styles& operator&=(const date_time_styles& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                date_time_styles& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                date_time_styles& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                date_time_styles& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                date_time_styles operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    date_time_styles ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                date_time_styles& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                date_time_styles operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    date_time_styles ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                date_time_styles operator~()
                {
                    return date_time_styles(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                date_time_styles operator^(const date_time_styles& val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                date_time_styles operator^(enum_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val ^ val));
                }

                date_time_styles operator^(int32_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val ^ val));
                }

                date_time_styles& operator^=(const date_time_styles& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                date_time_styles& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                date_time_styles& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                date_time_styles operator<<(const date_time_styles& val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val << val.m_val));
                }

                date_time_styles operator<<(enum_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val << val));
                }

                date_time_styles operator<<(int32_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val << val));
                }

                date_time_styles& operator<<=(const date_time_styles& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                date_time_styles& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                date_time_styles& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                date_time_styles operator>>(const date_time_styles& val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                date_time_styles operator>>(enum_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val >> val));
                }

                date_time_styles operator>>(int32_t val)
                {
                    return date_time_styles(static_cast<enum_t>(this->m_val >> val));
                }

                date_time_styles& operator>>=(const date_time_styles& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                date_time_styles& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                date_time_styles& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const date_time_styles& val) const
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

                bool operator>(const date_time_styles& val) const
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

                bool operator==(const date_time_styles& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::date_time_styles) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::date_time_styles)
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
                static bool _try_parse(const S& val, date_time_styles& out)
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
                        OMNI_S2E_FW(ALLOW_LEADING_WHITE)
                        OMNI_S2E_FW(ALLOW_TRAILING_WHITE)
                        OMNI_S2E_FW(ALLOW_INNER_WHITE)
                        OMNI_S2E_FW(ALLOW_WHITE_SPACES)
                        OMNI_S2E_FW(NO_CURRENT_DATE_DEFAULT)
                        OMNI_S2E_FW(ADJUST_TO_UNIVERSAL)
                        OMNI_S2E_FW(ASSUME_LOCAL)
                        OMNI_S2E_FW(ASSUME_UNIVERSAL)
                        OMNI_S2E_FW(ROUNDTRIP_KIND)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(ALLOW_LEADING_WHITE);
                        OMNI_E2SS_FW(ALLOW_TRAILING_WHITE);
                        OMNI_E2SS_FW(ALLOW_INNER_WHITE);
                        OMNI_E2SS_FW(ALLOW_WHITE_SPACES);
                        OMNI_E2SS_FW(NO_CURRENT_DATE_DEFAULT);
                        OMNI_E2SS_FW(ADJUST_TO_UNIVERSAL);
                        OMNI_E2SS_FW(ASSUME_LOCAL);
                        OMNI_E2SS_FW(ASSUME_UNIVERSAL);
                        OMNI_E2SS_FW(ROUNDTRIP_KIND);
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
                        OMNI_I2EV_FW(ALLOW_LEADING_WHITE) ||
                        OMNI_I2EV_FW(ALLOW_TRAILING_WHITE) ||
                        OMNI_I2EV_FW(ALLOW_INNER_WHITE) ||
                        OMNI_I2EV_FW(ALLOW_WHITE_SPACES) ||
                        OMNI_I2EV_FW(NO_CURRENT_DATE_DEFAULT) ||
                        OMNI_I2EV_FW(ADJUST_TO_UNIVERSAL) ||
                        OMNI_I2EV_FW(ASSUME_LOCAL) ||
                        OMNI_I2EV_FW(ASSUME_UNIVERSAL) ||
                        OMNI_I2EV_FW(ROUNDTRIP_KIND)
                    );
                }
        };

        class day_of_week
        {
            public:
                typedef enum enum_t {
                    SUNDAY = 0,
                    MONDAY = 1,
                    TUESDAY = 2,
                    WEDNESDAY = 3,
                    THURSDAY = 4,
                    FRIDAY = 5,
                    SATURDAY = 6
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 7;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return SUNDAY;
                }

                static inline std::string get_name(size_t dow)
                {
                    switch (dow) {
                        case 0: return "Sunday";
                        case 1: return "Monday";
                        case 2: return "Tuesday";
                        case 3: return "Wednesday";
                        case 4: return "Thursday";
                        case 5: return "Friday";
                        case 6: return "Saturday";
                        default: break;
                    }
                    return "";
                }

                static inline std::wstring get_wname(size_t dow)
                {
                    switch (dow) {
                        case 0: return L"Sunday";
                        case 1: return L"Monday";
                        case 2: return L"Tuesday";
                        case 3: return L"Wednesday";
                        case 4: return L"Thursday";
                        case 5: return L"Friday";
                        case 6: return L"Saturday";
                        default: break;
                    }
                    return L"";
                }

                static inline std::string get_abbreviated_name(size_t dow)
                {
                    switch (dow) {
                        case 0: return "Sun";
                        case 1: return "Mon";
                        case 2: return "Tue";
                        case 3: return "Wed";
                        case 4: return "Thu";
                        case 5: return "Fri";
                        case 6: return "Sat";
                        default: break;
                    }
                    return "";
                }

                static inline std::wstring get_abbreviated_wname(size_t dow)
                {
                    switch (dow) {
                        case 0: return L"Sun";
                        case 1: return L"Mon";
                        case 2: return L"Tue";
                        case 3: return L"Wed";
                        case 4: return L"Thu";
                        case 5: return L"Fri";
                        case 6: return L"Sat";
                        default: break;
                    }
                    return L"";
                }

                static std::string get_abbreviated_name(enum_t v)
                {
                    switch (v) {
                        case SUNDAY: return "SUN";
                        case MONDAY: return "MON";
                        case TUESDAY: return "TUE";
                        case WEDNESDAY: return "WED";
                        case THURSDAY: return "THU";
                        case FRIDAY: return "FRI";
                        case SATURDAY: return "SAT";
                        default: break;
                    }
                    return "UNK";
                }

                static std::wstring get_abbreviated_wname(enum_t v)
                {
                    switch (v) {
                        case SUNDAY: return L"SUN";
                        case MONDAY: return L"MON";
                        case TUESDAY: return L"TUE";
                        case WEDNESDAY: return L"WED";
                        case THURSDAY: return L"THU";
                        case FRIDAY: return L"FRI";
                        case SATURDAY: return L"SAT";
                        default: break;
                    }
                    return L"UNK";
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

                static bool try_parse(const std::string& val, day_of_week& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, day_of_week& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                day_of_week() :
                    OMNI_CTOR_FW(omni::chrono::day_of_week)
                    m_val(DEFAULT_VALUE())
                { }

                day_of_week(const day_of_week& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                day_of_week(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::day_of_week)
                    m_val(val)
                { }

                ~day_of_week()
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

                bool operator!=(const day_of_week& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                day_of_week& operator=(const day_of_week& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                day_of_week& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                day_of_week& operator=(int32_t val)
                {
                    if (!day_of_week::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const day_of_week& val) const
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

                bool operator>(const day_of_week& val) const
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

                bool operator==(const day_of_week& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::day_of_week) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::day_of_week)
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
                static bool _try_parse(const S& val, day_of_week& out)
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
                        OMNI_S2E_FW(SUNDAY)
                        OMNI_S2E_FW(MONDAY)
                        OMNI_S2E_FW(TUESDAY)
                        OMNI_S2E_FW(WEDNESDAY)
                        OMNI_S2E_FW(THURSDAY)
                        OMNI_S2E_FW(FRIDAY)
                        OMNI_S2E_FW(SATURDAY)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(SUNDAY);
                        OMNI_E2SS_FW(MONDAY);
                        OMNI_E2SS_FW(TUESDAY);
                        OMNI_E2SS_FW(WEDNESDAY);
                        OMNI_E2SS_FW(THURSDAY);
                        OMNI_E2SS_FW(FRIDAY);
                        OMNI_E2SS_FW(SATURDAY);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(SUNDAY) ||
                        OMNI_I2EV_FW(MONDAY) ||
                        OMNI_I2EV_FW(TUESDAY) ||
                        OMNI_I2EV_FW(WEDNESDAY) ||
                        OMNI_I2EV_FW(THURSDAY) ||
                        OMNI_I2EV_FW(FRIDAY) ||
                        OMNI_I2EV_FW(SATURDAY)
                    );
                }
        };

        class day_of_week_iso_8601
        {
            public:
                typedef enum enum_t {
                    MONDAY = 0,
                    TUESDAY = 1,
                    WEDNESDAY = 2,
                    THURSDAY = 3,
                    FRIDAY = 4,
                    SATURDAY = 5,
                    SUNDAY = 6
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 7;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return MONDAY;
                }

                static inline std::string get_name(size_t dow)
                {
                    switch (dow) {
                        case 0: return "Monday";
                        case 1: return "Tuesday";
                        case 2: return "Wednesday";
                        case 3: return "Thursday";
                        case 4: return "Friday";
                        case 5: return "Saturday";
                        case 6: return "Sunday";
                        default: break;
                    }
                    return "";
                }

                static inline std::wstring get_wname(size_t dow)
                {
                    switch (dow) {
                        case 0: return L"Monday";
                        case 1: return L"Tuesday";
                        case 2: return L"Wednesday";
                        case 3: return L"Thursday";
                        case 4: return L"Friday";
                        case 5: return L"Saturday";
                        case 6: return L"Sunday";
                        default: break;
                    }
                    return L"";
                }

                static inline std::string get_abbreviated_name(size_t dow)
                {
                    switch (dow) {
                        case 0: return "Mon";
                        case 1: return "Tue";
                        case 2: return "Wed";
                        case 3: return "Thu";
                        case 4: return "Fri";
                        case 5: return "Sat";
                        case 6: return "Sun";
                        default: break;
                    }
                    return "";
                }

                static inline std::wstring get_abbreviated_wname(size_t dow)
                {
                    switch (dow) {
                        case 0: return L"Mon";
                        case 1: return L"Tue";
                        case 2: return L"Wed";
                        case 3: return L"Thu";
                        case 4: return L"Fri";
                        case 5: return L"Sat";
                        case 6: return L"Sun";
                        default: break;
                    }
                    return L"";
                }

                static std::string get_abbreviated_name(enum_t v)
                {
                    switch (v) {
                        case MONDAY: return "MON";
                        case TUESDAY: return "TUE";
                        case WEDNESDAY: return "WED";
                        case THURSDAY: return "THU";
                        case FRIDAY: return "FRI";
                        case SATURDAY: return "SAT";
                        case SUNDAY: return "SUN";
                        default: break;
                    }
                    return "UNK";
                }

                static std::wstring get_abbreviated_wname(enum_t v)
                {
                    switch (v) {
                        case MONDAY: return L"MON";
                        case TUESDAY: return L"TUE";
                        case WEDNESDAY: return L"WED";
                        case THURSDAY: return L"THU";
                        case FRIDAY: return L"FRI";
                        case SATURDAY: return L"SAT";
                        case SUNDAY: return L"SUN";
                        default: break;
                    }
                    return L"UNK";
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

                static bool try_parse(const std::string& val, day_of_week_iso_8601& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, day_of_week_iso_8601& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                day_of_week_iso_8601() :
                    OMNI_CTOR_FW(omni::chrono::day_of_week_iso_8601)
                    m_val(DEFAULT_VALUE())
                { }

                day_of_week_iso_8601(const day_of_week_iso_8601& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                day_of_week_iso_8601(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::day_of_week_iso_8601)
                    m_val(val)
                { }

                ~day_of_week_iso_8601()
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

                bool operator!=(const day_of_week_iso_8601& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                day_of_week_iso_8601& operator=(const day_of_week_iso_8601& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                day_of_week_iso_8601& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                day_of_week_iso_8601& operator=(int32_t val)
                {
                    if (!day_of_week_iso_8601::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const day_of_week_iso_8601& val) const
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

                bool operator>(const day_of_week_iso_8601& val) const
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

                bool operator==(const day_of_week_iso_8601& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::day_of_week_iso_8601) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::day_of_week_iso_8601)
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
                static bool _try_parse(const S& val, day_of_week_iso_8601& out)
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
                        OMNI_S2E_FW(MONDAY)
                        OMNI_S2E_FW(TUESDAY)
                        OMNI_S2E_FW(WEDNESDAY)
                        OMNI_S2E_FW(THURSDAY)
                        OMNI_S2E_FW(FRIDAY)
                        OMNI_S2E_FW(SATURDAY)
                        OMNI_S2E_FW(SUNDAY)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(SUNDAY);
                        OMNI_E2SS_FW(MONDAY);
                        OMNI_E2SS_FW(TUESDAY);
                        OMNI_E2SS_FW(WEDNESDAY);
                        OMNI_E2SS_FW(THURSDAY);
                        OMNI_E2SS_FW(FRIDAY);
                        OMNI_E2SS_FW(SATURDAY);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(MONDAY) ||
                        OMNI_I2EV_FW(TUESDAY) ||
                        OMNI_I2EV_FW(WEDNESDAY) ||
                        OMNI_I2EV_FW(THURSDAY) ||
                        OMNI_I2EV_FW(FRIDAY) ||
                        OMNI_I2EV_FW(SATURDAY) ||
                        OMNI_I2EV_FW(SUNDAY)
                    );
                }
        };

        class month_of_year
        {
            public:
                typedef enum enum_t {
                    UNKNOWN = 0,
                    JANUARY = 1,
                    FEBRUARY = 2,
                    MARCH = 3,
                    APRIL = 4,
                    MAY = 5,
                    JUNE = 6,
                    JULY = 7,
                    AUGUST = 8,
                    SEPTEMBER = 9,
                    OCTOBER = 10,
                    NOVEMBER = 11,
                    DECEMBER = 12
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 13;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return UNKNOWN;
                }

                static inline std::string get_name(size_t month)
                {
                    switch (month) {
                        case 1: return "January";
                        case 2: return "February";
                        case 3: return "March";
                        case 4: return "April";
                        case 5: return "May";
                        case 6: return "June";
                        case 7: return "July";
                        case 8: return "August";
                        case 9: return "September";
                        case 10: return "October";
                        case 11: return "November";
                        case 12: return "December";
                        default: break;
                    }
                    return "";
                }

                static inline std::wstring get_wname(size_t month)
                {
                    switch (month) {
                        case 1: return L"January";
                        case 2: return L"February";
                        case 3: return L"March";
                        case 4: return L"April";
                        case 5: return L"May";
                        case 6: return L"June";
                        case 7: return L"July";
                        case 8: return L"August";
                        case 9: return L"September";
                        case 10: return L"October";
                        case 11: return L"November";
                        case 12: return L"December";
                        default: break;
                    }
                    return L"";
                }

                static inline std::string get_abbreviated_name(size_t month)
                {
                    switch (month) {
                        case 1: return "Jan";
                        case 2: return "Feb";
                        case 3: return "Mar";
                        case 4: return "Apr";
                        case 5: return "May";
                        case 6: return "Jun";
                        case 7: return "Jul";
                        case 8: return "Aug";
                        case 9: return "Sep";
                        case 10: return "Oct";
                        case 11: return "Nov";
                        case 12: return "Dec";
                        default: break;
                    }
                    return "";
                }

                static inline std::wstring get_abbreviated_wname(size_t month)
                {
                    switch (month) {
                        case 1: return L"Jan";
                        case 2: return L"Feb";
                        case 3: return L"Mar";
                        case 4: return L"Apr";
                        case 5: return L"May";
                        case 6: return L"Jun";
                        case 7: return L"Jul";
                        case 8: return L"Aug";
                        case 9: return L"Sep";
                        case 10: return L"Oct";
                        case 11: return L"Nov";
                        case 12: return L"Dec";
                        default: break;
                    }
                    return L"";
                }

                static inline std::string get_abbreviated_name(enum_t v)
                {
                    switch (v) {
                        case JANUARY: return "JAN";
                        case FEBRUARY: return "FEB";
                        case MARCH: return "MAR";
                        case APRIL: return "APR";
                        case MAY: return "MAY";
                        case JUNE: return "JUN";
                        case JULY: return "JUL";
                        case AUGUST: return "AUG";
                        case SEPTEMBER: return "SEP";
                        case OCTOBER: return "OCT";
                        case NOVEMBER: return "NOV";
                        case DECEMBER: return "DEC";
                        case UNKNOWN: default: break;
                    }
                    return "UNK";
                }

                static inline std::wstring get_abbreviated_wname(enum_t v)
                {
                    switch (v) {
                        case JANUARY: return L"JAN";
                        case FEBRUARY: return L"FEB";
                        case MARCH: return L"MAR";
                        case APRIL: return L"APR";
                        case MAY: return L"MAY";
                        case JUNE: return L"JUN";
                        case JULY: return L"JUL";
                        case AUGUST: return L"AUG";
                        case SEPTEMBER: return L"SEP";
                        case OCTOBER: return L"OCT";
                        case NOVEMBER: return L"NOV";
                        case DECEMBER: return L"DEC";
                        case UNKNOWN: default: break;
                    }
                    return L"UNK";
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

                static bool try_parse(const std::string& val, month_of_year& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, month_of_year& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                month_of_year() :
                    OMNI_CTOR_FW(omni::chrono::month_of_year)
                    m_val(DEFAULT_VALUE())
                { }

                month_of_year(const month_of_year& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                month_of_year(enum_t val) : 
                    OMNI_CTOR_FW(omni::chrono::month_of_year)
                    m_val(val)
                { }

                ~month_of_year()
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

                bool operator!=(const month_of_year& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                month_of_year& operator=(const month_of_year& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                month_of_year& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                month_of_year& operator=(int32_t val)
                {
                    if (!month_of_year::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const month_of_year& val) const
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

                bool operator>(const month_of_year& val) const
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

                bool operator==(const month_of_year& val) const
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

                OMNI_MEMBERS_FW(omni::chrono::month_of_year) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::chrono::month_of_year)
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
                static bool _try_parse(const S& val, month_of_year& out)
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
                        OMNI_S2E_FW(UNKNOWN)
                        OMNI_S2E_FW(JANUARY)
                        OMNI_S2E_FW(FEBRUARY)
                        OMNI_S2E_FW(MARCH)
                        OMNI_S2E_FW(APRIL)
                        OMNI_S2E_FW(MAY)
                        OMNI_S2E_FW(JUNE)
                        OMNI_S2E_FW(JULY)
                        OMNI_S2E_FW(AUGUST)
                        OMNI_S2E_FW(SEPTEMBER)
                        OMNI_S2E_FW(OCTOBER)
                        OMNI_S2E_FW(NOVEMBER)
                        OMNI_S2E_FW(DECEMBER)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(JANUARY);
                        OMNI_E2SS_FW(FEBRUARY);
                        OMNI_E2SS_FW(MARCH);
                        OMNI_E2SS_FW(APRIL);
                        OMNI_E2SS_FW(MAY);
                        OMNI_E2SS_FW(JUNE);
                        OMNI_E2SS_FW(JULY);
                        OMNI_E2SS_FW(AUGUST);
                        OMNI_E2SS_FW(SEPTEMBER);
                        OMNI_E2SS_FW(OCTOBER);
                        OMNI_E2SS_FW(NOVEMBER);
                        OMNI_E2SS_FW(DECEMBER);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(UNKNOWN) ||
                        OMNI_I2EV_FW(JANUARY) ||
                        OMNI_I2EV_FW(FEBRUARY) ||
                        OMNI_I2EV_FW(MARCH) ||
                        OMNI_I2EV_FW(APRIL) ||
                        OMNI_I2EV_FW(MAY) ||
                        OMNI_I2EV_FW(JUNE) ||
                        OMNI_I2EV_FW(JULY) ||
                        OMNI_I2EV_FW(AUGUST) ||
                        OMNI_I2EV_FW(SEPTEMBER) ||
                        OMNI_I2EV_FW(OCTOBER) ||
                        OMNI_I2EV_FW(NOVEMBER) ||
                        OMNI_I2EV_FW(DECEMBER)
                    );
                }
        };

        typedef day_of_week day;
        typedef day_of_week_iso_8601 day_iso_8601;
        typedef month_of_year month;
    }
}

#endif // OMNI_DATE_T_HPP
