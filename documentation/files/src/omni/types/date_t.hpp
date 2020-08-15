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
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_YEAR OMNI_EXT_ASSN_FW(365); // non-leap
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_4_YEARS OMNI_EXT_ASSN_FW(1461); // 365 * 4 + 1 leap day
        
        // DEV_NOTE: These values are to keep in line with the .NET library
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_100_YEARS OMNI_EXT_ASSN_FW(36524); // DAYS_PER_4_YEARS * 25 - 1
        OMNI_CONSTEXT_FW const int64_t DAYS_PER_400_YEARS OMNI_EXT_ASSN_FW(146097); // DAYS_PER_100_YEARS * 4 + 1
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_1601AD OMNI_EXT_ASSN_FW(584388); // Number of days from 1/1/0001 to 12/31/1600 -> DAYS_PER_400_YEARS * 4
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_EPOCH OMNI_EXT_ASSN_FW(719527); // Number of days from 1/1/0001 to 12/31/1969 -> DAYS_TO_1601AD + (DAYS_PER_100_YEARS * 3) + (DAYS_PER_4_YEARS * 17) + (DAYS_PER_YEAR * 2)
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_1899AD OMNI_EXT_ASSN_FW(693593); // Number of days from 1/1/0001 to 12/30/1899 -> DAYS_PER_400_YEARS * 4 + DAYS_PER_100_YEARS * 3 - 367;
        OMNI_CONSTEXT_FW const int64_t DAYS_TO_10000AD OMNI_EXT_ASSN_FW(3652059); // Number of days from 1/1/0001 to 12/31/9999 -> DAYS_PER_400_YEARS * 25 - 366
        OMNI_CONSTEXT_FW const int64_t TICKS_TO_10000AD OMNI_EXT_ASSN_FW(3155378975999999999); // DAYS_TO_10000AD * TICKS_PER_DAY - 1;
        OMNI_CONSTEXT_FW const int64_t MILLISECONDS_TO_10000AD OMNI_EXT_ASSN_FW(315537897600000); // DAYS_TO_10000AD * MILLISECONDS_PER_DAY;

        OMNI_CONSTEXT_FW const int64_t FILE_TIME_OFFSET OMNI_EXT_ASSN_FW(504911232000000000); // DAYS_TO_1601AD * TICKS_PER_DAY;
        OMNI_CONSTEXT_FW const int64_t EPOCH_OFFSET OMNI_EXT_ASSN_FW(621671328000000000); // DAYS_TO_EPOCH * TICKS_PER_DAY;
        OMNI_CONSTEXT_FW const int64_t DOUBLE_DATE_OFFSET OMNI_EXT_ASSN_FW(599264352000000000); // DAYS_TO_1899AD * TICKS_PER_DAY;
        // The minimum OA date is 0100/01/01 (Note it is year 100).
        // The maximum OA date is 9999/12/31
        OMNI_CONSTEXT_FW const int64_t OA_DATE_MIN_AS_TICKS OMNI_EXT_ASSN_FW(31241376000000000); // (DAYS_PER_100_YEARS - DAYS_PER_YEAR) * TICKS_PER_DAY;
        OMNI_CONSTEXT_FW const double  OA_DATE_MIN_AS_DOUBLE OMNI_EXT_ASSN_FW(-657435.0); // All OA dates must be greater than (not >=) OA_DATE_MIN_AS_DOUBLE
        OMNI_CONSTEXT_FW const double  OA_DATE_MAX_AS_DOUBLE OMNI_EXT_ASSN_FW(2958466.0); // All OA dates must be less than (not <=) OA_DATE_MAX_AS_DOUBLE

        #if defined(OMNI_NO_EXTERN_CONSTS)
            const int32_t DAYS_TO_MONTH_365[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
            const int32_t DAYS_TO_MONTH_366[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
        #else
            extern const int32_t DAYS_TO_MONTH_365[13];
            extern const int32_t DAYS_TO_MONTH_366[13];
        #endif

        class date_time_kind
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = 0,
                    UTC = 1,
                    LOCAL = 2
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 3;
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
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        UTC ||
                        LOCAL
                    );
                }
        };

        class date_time_styles {
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
                    OMNI_CTOR_FW(omni::sync::date_time_styles)
                    m_val(DEFAULT_VALUE())
                { }

                date_time_styles(const date_time_styles& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                date_time_styles(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::date_time_styles)
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                    return (val == 
                        NONE ||
                        ALLOW_LEADING_WHITE ||
                        ALLOW_TRAILING_WHITE ||
                        ALLOW_INNER_WHITE ||
                        ALLOW_WHITE_SPACES ||
                        NO_CURRENT_DATE_DEFAULT ||
                        ADJUST_TO_UNIVERSAL ||
                        ASSUME_LOCAL ||
                        ASSUME_UNIVERSAL ||
                        ROUNDTRIP_KIND
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
                    }
                    return "Unknown";
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
                    return (val == 
                        SUNDAY ||
                        MONDAY ||
                        TUESDAY ||
                        WEDNESDAY ||
                        THURSDAY ||
                        FRIDAY ||
                        SATURDAY
                    );
                }
        };

        typedef omni::chrono::span<int64_t> time_span;
    }
}

#endif // OMNI_DATE_T_HPP