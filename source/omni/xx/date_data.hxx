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
*/

// so as not to accidentally build this file with the source
// these macros are defined in chrono
#if !defined(OMNI_DATE_DATA_HXX_FW)
    #error invalid preprocessor directive detected
#endif

namespace date_time_format {

    typedef void* object;

    /** The enum template */
    class parse_failure_kind
    {
        public:
            /** The underlying enum type expected */
            typedef enum enum_t {
                NONE = 0,
                ARGUMENT_NULL = 1,
                FORMAT = 2,
                FORMAT_WITH_PARAMETER = 3,
                FORMAT_BAD_DATE_TIME_CALENDAR = 4,  // FormatException when ArgumentOutOfRange is thrown by a Calendar.TryToDateTime().
            } enum_t;

            /** Defines the number of elements in the enum */
            static inline unsigned short COUNT()
            {
                return 5;
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
            static bool try_parse(const std::string& val, parse_failure_kind& out)
            {
                return _try_parse(val, out);
            }

            /** Tries parsing a wide string value into its enum representation */
            static bool try_parse(const std::wstring& val, parse_failure_kind& out)
            {
                return _try_parse(val, out);
            }

            /** Returns true if the integer value specified is a valid enum value */
            static bool is_valid(int32_t val)
            {
                return _valid(val);
            }
            
            parse_failure_kind() :
                OMNI_CTOR_FW(date_time_format::parse_failure_kind)
                m_val(DEFAULT_VALUE())
            { }

            parse_failure_kind(const parse_failure_kind& cp) :
                OMNI_CPCTOR_FW(cp)
                m_val(cp.m_val)
            { }

            parse_failure_kind(enum_t val) : 
                OMNI_CTOR_FW(date_time_format::parse_failure_kind)
                m_val(val)
            { }

            ~parse_failure_kind()
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

            bool operator!=(const parse_failure_kind& val) const
            {
                return !(*this == val);
            }
            
            bool operator!=(enum_t val) const
            {
                return (this->m_val != val);
            }
            
            parse_failure_kind& operator=(const parse_failure_kind& val)
            {
                if (this != &val) {
                    OMNI_ASSIGN_FW(val)
                    this->m_val = val.m_val;
                }
                return *this;
            }

            parse_failure_kind& operator=(enum_t val)
            {
                this->m_val = val;
                return *this;
            }

            parse_failure_kind& operator=(int32_t val)
            {
                if (!parse_failure_kind::is_valid(val)) {
                    OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                } else {
                    this->m_val = static_cast<enum_t>(val);
                }
                return *this;
            }

            bool operator<(const parse_failure_kind& val) const
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

            bool operator>(const parse_failure_kind& val) const
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

            bool operator==(const parse_failure_kind& val) const
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

            OMNI_MEMBERS_FW(date_time_format::parse_failure_kind) // disposing,name,type(),hash()

            OMNI_OSTREAM_FW(date_time_format::parse_failure_kind)
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
            static bool _try_parse(const S& val, parse_failure_kind& out)
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
                return (val == 
                    NONE ||
                    ARGUMENT_NULL ||
                    FORMAT ||
                    FORMAT_WITH_PARAMETER ||
                    FORMAT_BAD_DATE_TIME_CALENDAR
                );
            }
    };

    /** The enum template */
    class parse_flags
    {
        public:
            /** The underlying enum type expected */
            typedef enum enum_t {
                HAVE_YEAR         = 0x00000001,
                HAVE_MONTH        = 0x00000002,
                HAVE_DAY          = 0x00000004,
                HAVE_HOUR         = 0x00000008,
                HAVE_MINUTE       = 0x00000010,
                HAVE_SECOND       = 0x00000020,
                HAVE_TIME         = 0x00000040,
                HAVE_DATE         = 0x00000080,
                TIMEZONE_USED     = 0x00000100,
                TIMEZONE_UTC      = 0x00000200,
                PARSED_MONTH_NAME = 0x00000400,
                CAPTURE_OFFSET    = 0x00000800,
                YEAR_DEFAULT      = 0x00001000,
                RFC1123_PATTERN   = 0x00002000,
                UTC_SORT_PATTERN  = 0x00004000
            } enum_t;

            /** Defines the number of elements in the enum */
            static inline unsigned short COUNT()
            {
                return 15;
            }

            /** The default value for this enum instance */
            static inline enum_t DEFAULT_VALUE()
            {
                return HAVE_YEAR;
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
            static bool try_parse(const std::string& val, parse_flags& out)
            {
                return _try_parse(val, out);
            }

            /** Tries parsing a wide string value into its enum representation */
            static bool try_parse(const std::wstring& val, parse_flags& out)
            {
                return _try_parse(val, out);
            }

            /** Returns true if the integer value specified is a valid enum value */
            static bool is_valid(int32_t val)
            {
                return _valid(val);
            }
            
            parse_flags() :
                OMNI_CTOR_FW(date_time_format::parse_flags)
                m_val(DEFAULT_VALUE())
            { }

            parse_flags(const parse_flags& cp) :
                OMNI_CPCTOR_FW(cp)
                m_val(cp.m_val)
            { }

            parse_flags(enum_t val) : 
                OMNI_CTOR_FW(date_time_format::parse_flags)
                m_val(val)
            { }

            ~parse_flags()
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

            bool operator!=(const parse_flags& val) const
            {
                return !(*this == val);
            }
            
            bool operator!=(enum_t val) const
            {
                return (this->m_val != val);
            }
            
            parse_flags& operator=(const parse_flags& val)
            {
                if (this != &val) {
                    OMNI_ASSIGN_FW(val)
                    this->m_val = val.m_val;
                }
                return *this;
            }

            parse_flags& operator=(enum_t val)
            {
                this->m_val = val;
                return *this;
            }

            parse_flags& operator=(int32_t val)
            {
                if (!parse_flags::is_valid(val)) {
                    OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                } else {
                    this->m_val = static_cast<enum_t>(val);
                }
                return *this;
            }

            bool operator<(const parse_flags& val) const
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

            bool operator>(const parse_flags& val) const
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

            bool operator==(const parse_flags& val) const
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

            OMNI_MEMBERS_FW(date_time_format::parse_flags) // disposing,name,type(),hash()

            OMNI_OSTREAM_FW(date_time_format::parse_flags)
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
            static bool _try_parse(const S& val, parse_flags& out)
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
                    OMNI_S2E_FW(HAVE_YEAR)
                    OMNI_S2E_FW(HAVE_MONTH)
                    OMNI_S2E_FW(HAVE_DAY)
                    OMNI_S2E_FW(HAVE_HOUR)
                    OMNI_S2E_FW(HAVE_MINUTE)
                    OMNI_S2E_FW(HAVE_SECOND)
                    OMNI_S2E_FW(HAVE_TIME)
                    OMNI_S2E_FW(HAVE_DATE)
                    OMNI_S2E_FW(TIMEZONE_USED)
                    OMNI_S2E_FW(TIMEZONE_UTC)
                    OMNI_S2E_FW(PARSED_MONTH_NAME)
                    OMNI_S2E_FW(CAPTURE_OFFSET)
                    OMNI_S2E_FW(YEAR_DEFAULT)
                    OMNI_S2E_FW(RFC1123_PATTERN)
                    OMNI_S2E_FW(UTC_SORT_PATTERN)
                }
                return false;
            }

            template < typename S >
            static std::basic_string< typename S::char_type > _to_val(enum_t v)
            {
                S ss;
                switch (v) {
                    OMNI_E2SS_FW(HAVE_YEAR);
                    OMNI_E2SS_FW(HAVE_MONTH);
                    OMNI_E2SS_FW(HAVE_DAY);
                    OMNI_E2SS_FW(HAVE_HOUR);
                    OMNI_E2SS_FW(HAVE_MINUTE);
                    OMNI_E2SS_FW(HAVE_SECOND);
                    OMNI_E2SS_FW(HAVE_TIME);
                    OMNI_E2SS_FW(HAVE_DATE);
                    OMNI_E2SS_FW(TIMEZONE_USED);
                    OMNI_E2SS_FW(TIMEZONE_UTC);
                    OMNI_E2SS_FW(PARSED_MONTH_NAME);
                    OMNI_E2SS_FW(CAPTURE_OFFSET);
                    OMNI_E2SS_FW(YEAR_DEFAULT);
                    OMNI_E2SS_FW(RFC1123_PATTERN);
                    OMNI_E2SS_FW(UTC_SORT_PATTERN);
                    default:
                        ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                        break;
                }
                return ss.str();
            }

            static bool _valid(int32_t val)
            {
                return (val == 
                    HAVE_YEAR ||
                    HAVE_MONTH ||
                    HAVE_DAY ||
                    HAVE_HOUR ||
                    HAVE_MINUTE ||
                    HAVE_SECOND ||
                    HAVE_TIME ||
                    HAVE_DATE ||
                    TIMEZONE_USED ||
                    TIMEZONE_UTC ||
                    PARSED_MONTH_NAME ||
                    CAPTURE_OFFSET ||
                    YEAR_DEFAULT ||
                    RFC1123_PATTERN ||
                    UTC_SORT_PATTERN
                );
            }
    };

    class DateTimeResult
    {
        public:
            int Year;
            int Month;
            int Day;
            int Hour; // Set time defualt to 00:00:00.
            int Minute;
            int Second;
            double fraction;
            int era;

            date_time_format::parse_flags flags;

            omni::chrono::time_span timeZoneOffset;

            //Calendar calendar;

            omni::chrono::date_time parsedDate;

            date_time_format::parse_failure_kind failure;
            std::string failureMessageID;
            date_time_format::object failureMessageFormatArgument;
            std::string failureArgumentName;

            DateTimeResult() :
                Year(-1), Month(-1), Day(-1), fraction(-1), era(-1),
                flags(),
                timeZoneOffset(),
                parsedDate(0),
                failure(),
                failureMessageID(),
                failureMessageFormatArgument(),
                failureArgumentName()
            {
            }

            DateTimeResult(const DateTimeResult& cp) :
                Year(cp.Year),
                Month(cp.Month),
                Day(cp.Day),
                fraction(cp.fraction),
                era(cp.era),
                flags(cp.flags),
                timeZoneOffset(cp.timeZoneOffset),
                parsedDate(cp.parsedDate),
                failure(cp.failure),
                failureMessageID(cp.failureMessageID),
                failureMessageFormatArgument(cp.failureMessageFormatArgument),
                failureArgumentName(cp.failureArgumentName)
            {
            }

            ~DateTimeResult() {}

            DateTimeResult& operator=(const DateTimeResult& cp)
            {
                Year = cp.Year;
                Month = cp.Month;
                Day = cp.Day;
                fraction = cp.fraction;
                era = cp.era;
                flags = cp.flags;
                timeZoneOffset = cp.timeZoneOffset;
                parsedDate = cp.parsedDate;
                failure = cp.failure;
                failureMessageID = cp.failureMessageID;
                failureMessageFormatArgument = cp.failureMessageFormatArgument;
                failureArgumentName = cp.failureArgumentName;
                return *this;
            }

            void SetDate(int year, int month, int day)
            {
                Year = year;
                Month = month;
                Day = day;
            }
            
            void SetFailure(const parse_failure_kind& failure, const std::string& failureMessageID, object failureMessageFormatArgument) {
                this->failure = failure;
                this->failureMessageID = failureMessageID;
                this->failureMessageFormatArgument = failureMessageFormatArgument;
            }

            void SetFailure(const parse_failure_kind& failure, const std::string& failureMessageID, object failureMessageFormatArgument, const std::string& failureArgumentName) {
                this->failure = failure;
                this->failureMessageID = failureMessageID;
                this->failureMessageFormatArgument = failureMessageFormatArgument;
                this->failureArgumentName = failureArgumentName;
            }
    };

    class DateTimeFormatInfo
    {
        public:
            DateTimeFormatInfo() {}
            
            DateTimeFormatInfo(const DateTimeFormatInfo& cp) :
                AMDesignator(cp.AMDesignator),
                PMDesignator(cp.PMDesignator),
                ShortDatePattern(cp.ShortDatePattern),
                LongDatePattern(cp.LongDatePattern),
                FullDateTimePattern(cp.FullDateTimePattern),
                GeneralShortTimePattern(cp.GeneralShortTimePattern),
                GeneralLongTimePattern(cp.GeneralLongTimePattern),
                MonthDayPattern(cp.MonthDayPattern),
                RFC1123Pattern(cp.RFC1123Pattern),
                SortableDateTimePattern(cp.SortableDateTimePattern),
                ShortTimePattern(cp.ShortTimePattern),
                LongTimePattern(cp.LongTimePattern),
                UniversalSortableDateTimePattern(cp.UniversalSortableDateTimePattern),
                YearMonthPattern(cp.YearMonthPattern),
                TimeSeparator(cp.TimeSeparator),
                DateSeparator(cp.DateSeparator),
                FormatFlags(cp.FormatFlags),
                HasYearMonthAdjustment(cp.HasYearMonthAdjustment),
                HasForceTwoDigitYears(cp.HasForceTwoDigitYears)
            {}

            ~DateTimeFormatInfo() {}

            DateTimeFormatInfo& operator=(const DateTimeFormatInfo& cp)
            {
                AMDesignator = cp.AMDesignator;
                PMDesignator = cp.PMDesignator;
                ShortDatePattern = cp.ShortDatePattern;
                LongDatePattern = cp.LongDatePattern;
                FullDateTimePattern = cp.FullDateTimePattern;
                GeneralShortTimePattern = cp.GeneralShortTimePattern;
                GeneralLongTimePattern = cp.GeneralLongTimePattern;
                MonthDayPattern = cp.MonthDayPattern;
                RFC1123Pattern = cp.RFC1123Pattern;
                SortableDateTimePattern = cp.SortableDateTimePattern;
                ShortTimePattern = cp.ShortTimePattern;
                LongTimePattern = cp.LongTimePattern;
                UniversalSortableDateTimePattern = cp.UniversalSortableDateTimePattern;
                YearMonthPattern = cp.YearMonthPattern;
                TimeSeparator = cp.TimeSeparator;
                DateSeparator = cp.DateSeparator;
                FormatFlags = cp.FormatFlags;
                HasYearMonthAdjustment = cp.HasYearMonthAdjustment;
                HasForceTwoDigitYears = cp.HasForceTwoDigitYears;
                return *this;
            }

            static DateTimeFormatInfo CurrentInfo;
            static DateTimeFormatInfo InvariantInfo;

            std::string AMDesignator;
            std::string PMDesignator;
            std::string ShortDatePattern;
            std::string LongDatePattern;
            std::string FullDateTimePattern;
            std::string GeneralShortTimePattern;
            std::string GeneralLongTimePattern;
            std::string MonthDayPattern;
            std::string RFC1123Pattern;
            std::string SortableDateTimePattern;
            std::string ShortTimePattern;
            std::string LongTimePattern;
            std::string UniversalSortableDateTimePattern;
            std::string YearMonthPattern;
            std::string TimeSeparator;
            std::string DateSeparator;
            // TODO: these three need to be redone from the CS
            uint64_t FormatFlags;
            volatile bool HasYearMonthAdjustment;
            volatile bool HasForceTwoDigitYears;

            static DateTimeFormatInfo GetInstance() /*IFormatProvider provider*/
            {
                // TODO: need to get from CS
                return CurrentInfo;
            }

            std::string DateTimeOffsetPattern() const {
                // TODO: need to get from CS
                return "";
            }

            std::string GetAbbreviatedDayName(omni::chrono::day_of_week dayofweek) const
            {
                return omni::chrono::day_of_week::get_abbreviated_name(dayofweek.value());
                // TODO: need to get from CS
            }

            std::string GetDayName(omni::chrono::day_of_week dayofweek) const
            {
                return dayofweek.to_string();
            }

            std::string GetAbbreviatedMonthName(int month) const
            {
                if (month < 1 || month > 13) {
                    OMNI_ERR_RETV_FW("Invalid range for month", omni::exceptions::invalid_range(), std::string())
                }
                return _get_mo(month, true);
            }

            std::string GetMonthName(int month) const
            {
                if (month < 1 || month > 13) {
                    OMNI_ERR_RETV_FW("Invalid range for month", omni::exceptions::invalid_range(), std::string())
                }
                return _get_mo(month, false);
            }

        private:
            std::string _get_mo(int mo, bool abb) const
            {
                switch (mo) {
                    case 1: return (abb ? "JAN" : "JANUARY");
                    case 2: return (abb ? "FEB" : "FEBRUARY");
                    case 3: return (abb ? "MAR" : "MARCH");
                    case 4: return (abb ? "APR" : "APRIL");
                    case 5: return (abb ? "MAY" : "MAY");
                    case 6: return (abb ? "JUN" : "JUNE");
                    case 7: return (abb ? "JUL" : "JULY");
                    case 8: return (abb ? "AUG" : "AUGUST");
                    case 9: return (abb ? "SEP" : "SEPTEMBER");
                    case 10: return (abb ? "OCT" : "OCTOBER");
                    case 11: return (abb ? "NOV" : "NOVEMBER");
                    case 12: return (abb ? "DEC" : "DECEMBER");
                }
                return "UNK";
            }
    };

    namespace DateTimeParse
    {
        // This is the real method to do the parsing work.
        static bool TryParse(const std::string& s, DateTimeFormatInfo& dtfi, const omni::chrono::date_time_styles& styles, DateTimeResult& result)
        {
            // TODO: finish this
            return true;
        }

        static bool DoStrictParse(const std::string& s, std::string formatParam, const omni::chrono::date_time_styles& styles, DateTimeFormatInfo& dtfi, DateTimeResult& result)
        {
            // TODO: finish this
            return false;
        }

        static bool TryParseExact(const std::string& s, std::string format, DateTimeFormatInfo& dtfi, const omni::chrono::date_time_styles& style, DateTimeResult& result)
        {
            if (s.empty()) {
                result.SetFailure(date_time_format::parse_failure_kind::FORMAT, "Format_BadDateTime", NULL);
                return false;
            }
            if (format.empty()) {
                result.SetFailure(date_time_format::parse_failure_kind::FORMAT, "Format_BadFormatSpecifier", NULL);
                return false;
            }
            return DoStrictParse(s, format, style, dtfi, result);
        }

        static bool TryParseExact(const std::string& s, std::string format, DateTimeFormatInfo& dtfi, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result)
        {
            DateTimeResult resultData;       // The buffer to store the parsing result.
            if (TryParseExact(s, format, dtfi, style, resultData)) {
                result = resultData.parsedDate;
                return true;
            }
            result = omni::chrono::date_time::min_value();
            return false;
        }

        static bool TryParse(const std::string& s, DateTimeFormatInfo& dtfi, const omni::chrono::date_time_styles& styles, omni::chrono::date_time& result)
        {
            DateTimeResult resultData;       // The buffer to store the parsing result.
            if (TryParse(s, dtfi, styles, resultData)) {
                result = resultData.parsedDate;
                return true;
            }
            result = omni::chrono::date_time::min_value();
            return false;
        }

        static omni::chrono::date_time Parse(const std::string& s, DateTimeFormatInfo& dtfi, const omni::chrono::date_time_styles& styles)
        {
            DateTimeResult result;       // The buffer to store the parsing result.
            if (TryParse(s, dtfi, styles, result)) {
                return result.parsedDate;
            } else {
                OMNI_ERR_RETV_FW("Invalid date time string detected", omni::exceptions::invalid_parse(), omni::chrono::date_time())
            }
        }

        static omni::chrono::date_time ParseExact(const std::string& s, const std::string& format, DateTimeFormatInfo& dtfi, const omni::chrono::date_time_styles& style)
        {
            DateTimeResult result;       // The buffer to store the parsing result.
            if (TryParseExact(s, format, dtfi, style, result)) {
                return result.parsedDate;
            } else {
                OMNI_ERR_RETV_FW("Invalid date time string detected", omni::exceptions::invalid_parse(), omni::chrono::date_time())
            }
        }
    }
    
    static void HebrewFormatDigits(std::stringstream& outputBuffer, int digits)
    {
        // TODO: need to finish this
        //outputBuffer.Append(HebrewNumber.ToString(digits));
    }

    /*
        FormatHebrewMonthName

        Action: Return the Hebrew month name for the specified DateTime.
        Returns: The month name std::string for the specified DateTime.
            Arguments: 
               time   the time to format
               month  The month is the value of HebrewCalendar.GetMonth(time).         
               repeat Return abbreviated month name if repeat=3, or full month name if repeat=4
               dtfi    The DateTimeFormatInfo which uses the Hebrew calendars as its calendar.
         Exceptions: NONE.
        

        Note:
        If DTFI is using Hebrew calendar, GetMonthName()/GetAbbreviatedMonthName() will return month names like this:            
        1   Hebrew 1st Month
        2   Hebrew 2nd Month
        ..  ...
        6   Hebrew 6th Month
        7   Hebrew 6th Month II (used only in a leap year)
        8   Hebrew 7th Month
        9   Hebrew 8th Month
        10  Hebrew 9th Month
        11  Hebrew 10th Month
        12  Hebrew 11th Month
        13  Hebrew 12th Month

        Therefore, if we are in a regular year, we have to increment the month name if moth is greater or eqaul to 7.            
    */
    static std::string FormatHebrewMonthName(const omni::chrono::date_time& time, int month, int repeatCount, DateTimeFormatInfo& dtfi)
    {
        // TODO: need to finish this
        return "";
    }

    /*
        This is an MDA for cases when the user is using a local format with
        a Utc DateTime.
    */
    static void InvalidFormatForUtc(std::string format, const omni::chrono::date_time& dateTime)
    {
        //#if MDA_SUPPORTED
        //    Mda.DateTimeInvalidLocalFormat();
        //#endif
    }

    // This is a placeholder for an MDA to detect when the user is using a
    // local DateTime with a format that will be interpreted as UTC.
    static void InvalidFormatForLocal(std::string format, const omni::chrono::date_time& dateTime)
    {
    }

    /*
        is_use_genitive_form
        Actions: Check the format to see if we should use genitive month in the formatting.
        Starting at the position (index) in the (format) string, look back and look ahead to
        see if there is "d" or "dd".  In the case like "d MMMM" or "MMMM dd", we can use 
        genitive form.  Genitive form is not used if there is more than two "d".
        Arguments:
        format      The format std::string to be scanned.
        index       Where we should start the scanning.  This is generally where "M" starts.
        tokenLen    The len of the current pattern character.  This indicates how many "M" that we have.
        patternToMatch  The pattern that we want to search. This generally uses "d"
    */
    static bool is_use_genitive_form(std::string format, int index, int tokenLen, char patternToMatch)
    {
        int i;
        int repeat = 0;
        //
        // Look back to see if we can find "d" or "ddd"
        //
        
        // Find first "d".
        for (i = index - 1; i >= 0 && format[i] != patternToMatch; i--) { };
    
        if (i >= 0) {
            // Find a "d", so look back to see how many "d" that we can find.
            while (--i >= 0 && format[i] == patternToMatch) {
                repeat++;
            }
            //
            // repeat == 0 means that we have one (patternToMatch)
            // repeat == 1 means that we have two (patternToMatch)
            //
            if (repeat <= 1) {
                return (true);
            }
            // Note that we can't just stop here.  We may find "ddd" while looking back, and we have to look
            // ahead to see if there is "d" or "dd".
        }

        //
        // If we can't find "d" or "dd" by looking back, try look ahead.
        //

        // Find first "d"
        for (i = index + tokenLen; i < format.size() && format[i] != patternToMatch; i++) { /* Do nothing here */ };

        if (i < format.size()) {
            repeat = 0;
            // Find a "d", so contine the walk to see how may "d" that we can find.
            while (++i < format.size() && format[i] == patternToMatch) {
                repeat++;
            }
            //
            // repeat == 0 means that we have one (patternToMatch)
            // repeat == 1 means that we have two (patternToMatch)
            //
            if (repeat <= 1) {
                return (true);
            }
        }
        return (false);
    }

    // output the 'z' famliy of formats, which output a the offset from UTC, e.g. "-07:30"
    static void format_customized_timezone(const omni::chrono::date_time& dateTime, omni::chrono::time_span offset, std::string format, int32_t tokenLen, bool timeOnly, std::stringstream& result)
    {
        // See if the instance already has an offset
        bool dateTimeFormat = (offset == OMNI_TS_NULL_OFF_FW);
        if (dateTimeFormat) {
            // No offset. The instance is a DateTime and the output should be the local time zone
            if (timeOnly && dateTime.ticks() < OMNI_TICKS_PER_DAY) { // TODO: CAL -> Calendar.omni::chrono::TICKS_PER_DAY) {
                // For time only format and a time only input, the time offset on 0001/01/01 is less 
                // accurate than the system's current offset because of daylight saving time.
                // TODO: -> offset = TimeZoneInfo.GetLocalUtcOffset(DateTime.Now, TimeZoneInfoOptions.NoThrowOnInvalidTime);
            } else if (dateTime.kind() == omni::chrono::date_time_kind::UTC) {
                //#if FEATURE_CORECLR
                    offset = omni::chrono::time_span::zero();
                //#else // FEATURE_CORECLR
                    // This code path points to a bug in user code. It would make sense to return a 0 offset in this case.
                    // However, because it was only possible to detect this in Whidbey, there is user code that takes a 
                    // dependency on being serialize a UTC DateTime using the 'z' format, and it will work almost all the
                    // time if it is offset by an incorrect conversion to local time when parsed. Therefore, we need to 
                    // explicitly emit the local time offset, which we can do by removing the UTC flag.
                    //InvalidFormatForUtc(format, dateTime);
                    //dateTime = DateTime.SpecifyKind(dateTime, omni::chrono::date_time_kind::LOCAL);
                    //offset = TimeZoneInfo.GetLocalUtcOffset(dateTime, TimeZoneInfoOptions.NoThrowOnInvalidTime);
                //#endif // FEATURE_CORECLR
            } else {
                // TODO: -> offset = TimeZoneInfo.GetLocalUtcOffset(dateTime, TimeZoneInfoOptions.NoThrowOnInvalidTime);
            }
        }
        if (offset >= omni::chrono::time_span::zero()) {
            result << '+';
        } else {
            result << '-';
            // get a positive offset, so that you don't need a separate code path for the negative numbers.
            offset = offset.negate();
        }

        if (tokenLen <= 1) {
            // 'z' format e.g "-7"
            // TODO: -> result.AppendFormat(CultureInfo.InvariantCulture, "{0:0}", offset.Hours);
        } else {
            // 'zz' or longer format e.g "-07"
            // TODO: -> result.AppendFormat(CultureInfo.InvariantCulture, "{0:00}", offset.Hours);
            if (tokenLen >= 3) {
                // 'zzz*' or longer format e.g "-07:30"
                // TODO: -> result.AppendFormat(CultureInfo.InvariantCulture, ":{0:00}", offset.Minutes);
            }
        }        
    }

    // output the 'K' format, which is for round-tripping the data
    static void format_customized_roundtrip_timezone(const omni::chrono::date_time& dateTime, omni::chrono::time_span offset, std::stringstream& result)
    {
        // The objective of this format is to round trip the data in the type
        // For DateTime it should round-trip the Kind value and preserve the time zone. 
        // DateTimeOffset instance, it should do so by using the time zone.
        if (offset == OMNI_TS_NULL_OFF_FW) {
            // source is a date time, so behaviour depends on the kind.
            switch (dateTime.kind()) {
                case omni::chrono::date_time_kind::LOCAL: 
                    // This should output the local offset, e.g. "-07:30"
                    // TODO: -> offset = TimeZoneInfo.GetLocalUtcOffset(dateTime, TimeZoneInfoOptions.NoThrowOnInvalidTime);
                    // fall through to shared time zone output code
                    break;
                case omni::chrono::date_time_kind::UTC:
                    // The 'Z' constant is a marker for a UTC date
                    result << "Z";
                    return;
                default:
                    // If the kind is unspecified, we output nothing here
                    return;
            }            
        }
        if (offset >= omni::chrono::time_span::zero()) {
            result << '+';
        } else {
            result << '-';
            // get a positive offset, so that you don't need a separate code path for the negative numbers.
            offset = offset.negate();
        }
        // TODO: -> result.AppendFormat(CultureInfo.InvariantCulture, "{0:00}:{1:00}", offset.Hours, offset.Minutes);
    }
    
    static std::string format_day_of_week(int dayOfWeek, int repeat, DateTimeFormatInfo& dtfi)
    {
        //Contract.Assert(dayOfWeek >= 0 && dayOfWeek <= 6, "dayOfWeek >= 0 && dayOfWeek <= 6");
        if (repeat == 3) {
            return (dtfi.GetAbbreviatedDayName(omni::chrono::day_of_week(static_cast<omni::chrono::day_of_week::enum_t>(dayOfWeek))));
        }
        // Call dtfi.GetDayName() here, instead of accessing DayNames property, because we don't
        // want a clone of DayNames, which will hurt perf.
        return (dtfi.GetDayName(omni::chrono::day_of_week(static_cast<omni::chrono::day_of_week::enum_t>(dayOfWeek))));
    }

    static std::string format_month(int month, int repeatCount, DateTimeFormatInfo& dtfi)
    {
        //Contract.Assert(month >=1 && month <= 12, "month >=1 && month <= 12");
        if (repeatCount == 3) {
            return (dtfi.GetAbbreviatedMonthName(month));
        }
        // Call GetMonthName() here, instead of accessing MonthNames property, because we don't
        // want a clone of MonthNames, which will hurt perf.
        return (dtfi.GetMonthName(month));
    }

    /*
        The pos should point to a quote character. This method will
        get the std::string encloed by the quote character.
    */
    static int parse_quote_str(std::string format, int pos, std::stringstream& result)
    {
        // NOTE : pos will be the index of the quote character in the 'format' string.
        int formatLen = format.size();
        int beginPos = pos;
        char quoteChar = format[pos++]; // Get the character used to quote the following string.
        bool foundQuote = false;
        while (pos < formatLen) {
            char ch = format[pos++];        
            if (ch == quoteChar) {
                foundQuote = true;
                break;
            } else if (ch == '\\') {
                // The following are used to support escaped character.
                // Escaped character is also supported in the quoted string.
                // Therefore, someone can use a format like "'minute:' mm\"" to display:
                //  minute: 45"
                // because the second double quote is escaped.
                if (pos < formatLen) {
                    result << format[pos++];
                } else {
                    // This means that '\' is at the end of the formatting string.
                    OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                }                    
            } else {
                result << ch;
            }
        }
        if (!foundQuote) {
            // Here we can't find the matching quote.
            OMNI_ERR_RETV_FW("Invalid string format: bad quote", omni::exceptions::invalid_string_format(), std::string())
        }
        // Return the character count including the begin/end quote characters and enclosed string.
        return (pos - beginPos);
    }

    /*
        Get the next character at the index of 'pos' in the 'format' string.
        Return value of -1 means 'pos' is already at the end of the 'format' string.
        Otherwise, return value is the int value of the next character.
    */
    static int parse_next_char(std::string format, int pos)
    {
        if (pos >= format.size() - 1) {
            return -1;
        }
        return (int)format[pos+1];
    }

    static void format_digits(std::stringstream& outputBuffer, int value, int len, bool overrideLengthLimit)
    {
        // Limit the use of this function to be two-digits, so that we have the same behaviour
        // as RTM bits.
        if (!overrideLengthLimit && len > 2) {
            len = 2;
        }
        char* buffer = new char[16];
        char* p = buffer + 16;
        int n = value;
        do {
            *--p = (char)(n % 10 + '0');
            n /= 10;
        } while ((n != 0) && (p > buffer));
        
        int digits = (int)(buffer + 16 - p);
        //If the repeat count is greater than 0, we're trying
        //to emulate the "00" format, so we have to prepend
        //a zero if the std::string only has one character.
        while ((digits < len) && (p > buffer)) {
            *--p = '0';
            digits++;
        }
        for (n = 0; n < digits; ++n) {
            outputBuffer << *p;
            ++p;
        }
    }

    /* 
        FORMAT the positive integer value to a std::string and perfix with assigned 
        length of leading zero.

        Parameters:
        value: The value to format
        len: The maximum length for leading zero.  
        If the digits of the value is greater than len, no leading zero is added.

        Notes: 
        The function can format to Int32.MaxValue.
    */
    static void format_digits(std::stringstream& outputBuffer, int value, int len)
    {
        date_time_format::format_digits(outputBuffer, value, len, false);
    }
    
    static int parse_repeat_pattern(std::string format, int pos, char patternChar)
    {
        int len = format.size();
        int index = pos + 1;
        while ((index < len) && (format[index] == patternChar)) {
            index++;
        }    
        return (index - pos);
    }

    /*
        format_customized
        
        Actions: FORMAT the DateTime instance using the specified format.
    */
    static std::string format_customized(const omni::chrono::date_time& dateTime, std::string format, DateTimeFormatInfo& dtfi, const omni::chrono::time_span& offset)
    {
        const std::string fixedNumberFormats[] = { "0", "00", "000", "0000", "00000", "000000", "0000000" };
        const int MaxSecondsFractionDigits = 7;
        // Calendar cal = dtfi.Calendar;
        std::stringstream result;// = StringBuilderCache.Acquire();
        // This is a flag to indicate if we are format the dates using Hebrew calendar.
        bool isHebrewCalendar = false; //(cal.ID == Calendar.CAL_HEBREW);
        // This is a flag to indicate if we are formating hour/minute/second only.
        bool bTimeOnly = true;
        int i = 0;
        int tokenLen, hour12;
        while (i < format.size()) {
            char ch = format[i];
            int nextChar;
            int month = 1; // TODO: with CAL -> cal.GetMonth(dateTime);
            int year = 2021; // TODO: with CAL -> cal.GetYear(dateTime);
            std::stringstream enquotedString;
            switch (ch) {
                case 'g':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    // TODO: finish with calendar
                    //result << dtfi.GetEraName(cal.GetEra(dateTime));
                    break;
                case 'h':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    hour12 = dateTime.hour() % 12;
                    if (hour12 == 0) {
                        hour12 = 12;
                    }
                    date_time_format::format_digits(result, hour12, tokenLen);
                    break;
                case 'H':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    date_time_format::format_digits(result, dateTime.hour(), tokenLen);
                    break;
                case 'm':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    date_time_format::format_digits(result, dateTime.minute(), tokenLen);
                    break;
                case 's':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    date_time_format::format_digits(result, dateTime.second(), tokenLen);
                    break;
                case 'f': case 'F':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    if (tokenLen <= MaxSecondsFractionDigits) {
                        long fraction = 0; // TODO: with CAL -> (dateTime.ticks() % Calendar.TicksPerSecond);
                        fraction = fraction / (long)std::pow((double)10, (double)(7 - tokenLen));
                        if (ch == 'f') {
                            result << fraction; // TODO: -> (((int)fraction).ToString(fixedNumberFormats[tokenLen - 1], CultureInfo.InvariantCulture));
                        } else {
                            int effectiveDigits = tokenLen;
                            while (effectiveDigits > 0) {
                                if (fraction % 10 == 0) {
                                    fraction = fraction / 10;
                                    effectiveDigits--;
                                } else {
                                    break;
                                }
                            }
                            if (effectiveDigits > 0) {
                                result << fraction; // TODO: -> (((int)fraction).ToString(fixedNumberFormats[effectiveDigits - 1], CultureInfo.InvariantCulture));
                            } else {
                                // No fraction to emit, so see if we should remove decimal also.
                                if (result.str().size() > 0 && result.str()[result.str().size() - 1] == '.') {
                                    // TODO: stringstream remove??
                                    //result.Remove(result.size() - 1, 1);
                                }
                            }
                        }
                    } else {
                        OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                    }
                    break;
                case 't':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    if (tokenLen == 1) {
                        if (dateTime.hour() < 12) {
                            if (dtfi.AMDesignator.size() >= 1) {
                                result << (dtfi.AMDesignator[0]);
                            }
                        } else {
                            if (dtfi.PMDesignator.size() >= 1) {
                                result << (dtfi.PMDesignator[0]);
                            }
                        }
                    } else {
                        result << (dateTime.hour() < 12 ? dtfi.AMDesignator : dtfi.PMDesignator);
                    }
                    break;
                case 'd':
                    // tokenLen == 1 : Day of month as digits with no leading zero.
                    // tokenLen == 2 : Day of month as digits with leading zero for single-digit months.
                    // tokenLen == 3 : Day of week as a three-letter abbreviation.
                    // tokenLen >= 4 : Day of week as its full name.
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    if (tokenLen <= 2) {
                        int day = 1; // TODO: with CAL -> cal.GetDayOfMonth(dateTime);
                        if (isHebrewCalendar) {
                            // For Hebrew calendar, we need to convert numbers to Hebrew text for yyyy, MM, and dd values.
                            date_time_format::HebrewFormatDigits(result, day);
                        } else {
                            date_time_format::format_digits(result, day, tokenLen);
                        }
                    }  else {
                        int dayOfWeek = 1; // TODO: with CAL -> (int)cal.GetDayOfWeek(dateTime);
                        result << (date_time_format::format_day_of_week(dayOfWeek, tokenLen, dtfi));
                    }
                    bTimeOnly = false;
                    break;
                case 'M':
                    // 
                    // tokenLen == 1 : Month as digits with no leading zero.
                    // tokenLen == 2 : Month as digits with leading zero for single-digit months.
                    // tokenLen == 3 : Month as a three-letter abbreviation.
                    // tokenLen >= 4 : Month as its full name.
                    //
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    if (tokenLen <= 2) {
                        if (isHebrewCalendar) {
                            // For Hebrew calendar, we need to convert numbers to Hebrew text for yyyy, MM, and dd values.
                            date_time_format::HebrewFormatDigits(result, month);
                        } else {
                            date_time_format::format_digits(result, month, tokenLen);
                        }
                    } else {
                        if (isHebrewCalendar) {
                            result << (date_time_format::FormatHebrewMonthName(dateTime, month, tokenLen, dtfi));
                        } else {
                            if (false /*(dtfi.FormatFlags & DateTimeFormatFlags.UseGenitiveMonth) != 0 && tokenLen >= 4*/) {
                                /* TODO: ->
                                result << (
                                    dtfi.internalGetMonthName(
                                        month, 
                                        date_time_format::is_use_genitive_form(format, i, tokenLen, 'd')? MonthNameStyles.Genitive : MonthNameStyles.Regular, 
                                        false));
                                */
                            } else {
                                result << (date_time_format::format_month(month, tokenLen, dtfi));
                            }
                        }
                    }
                    bTimeOnly = false;
                    break;
                case 'y':
                    // Notes about OS behaviour:
                    // y: Always print (year % 100). No leading zero.
                    // yy: Always print (year % 100) with leading zero.
                    // yyy/yyyy/yyyyy/... : Print year value.  No leading zero.
                    tokenLen = parse_repeat_pattern(format, i, ch);
                    if (dtfi.HasForceTwoDigitYears) {
                        date_time_format::format_digits(result, year, tokenLen <= 2 ? tokenLen : 2);
                        // TODO: with CAL -> } else if (cal.ID == Calendar.CAL_HEBREW) {
                        //    date_time_format::HebrewFormatDigits(result, year);
                    } else {
                        if (tokenLen <= 2) {
                            date_time_format::format_digits(result, year % 100, tokenLen);
                        } else {
                            //std::string fmtPattern = "D" + tokenLen;
                            // TODO: -> result << (year.ToString(fmtPattern, CultureInfo.InvariantCulture));
                        }
                    }
                    bTimeOnly = false;
                    break;
                case 'z':
                    tokenLen = date_time_format::parse_repeat_pattern(format, i, ch);
                    date_time_format::format_customized_timezone(dateTime, offset, format, tokenLen, bTimeOnly, result);
                    break;
                case 'K':
                    tokenLen = 1;
                    date_time_format::format_customized_roundtrip_timezone(dateTime, offset, result);
                    break;
                case ':':
                    result << (dtfi.TimeSeparator);
                    tokenLen = 1;
                    break;
                case '/':
                    result << (dtfi.DateSeparator);
                    tokenLen = 1;
                    break;
                case '\'': case '\"':
                    tokenLen = date_time_format::parse_quote_str(format, i, enquotedString); 
                    result << enquotedString.str();
                    break;
                case '%':
                    // Optional format character.
                    // For example, format std::string "%d" will print day of month 
                    // without leading zero.  Most of the cases, "%" can be ignored.
                    nextChar = date_time_format::parse_next_char(format, i);
                    // nextChar will be -1 if we already reach the end of the format string.
                    // Besides, we will not allow "%%" appear in the pattern.
                    if (nextChar >= 0 && nextChar != (int)'%') {
                        result << (date_time_format::format_customized(dateTime, omni::string_util::to_string((char)nextChar), dtfi, offset));
                        tokenLen = 2;
                    } else {
                        // This means that '%' is at the end of the format std::string or
                        // "%%" appears in the format string.
                        OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                    }
                    break;
                case '\\':
                    // Escaped character.  Can be used to insert character into the format string.
                    // For exmple, "\d" will insert the character 'd' into the string.
                    
                    // NOTENOTE : we can remove this format character if we enforce the enforced quote 
                    // character rule.
                    // That is, we ask everyone to use single quote or double quote to insert characters,
                    // then we can remove this character.
                    nextChar = date_time_format::parse_next_char(format, i);
                    if (nextChar >= 0) {
                        result << (((char)nextChar));
                        tokenLen = 2;
                    } else {
                        // This means that '\' is at the end of the formatting string.
                        OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                    }
                    break;
                default:
                    // NOTENOTE : we can remove this rule if we enforce the enforced quote
                    // character rule.
                    // That is, if we ask everyone to use single quote or double quote to insert characters,
                    // then we can remove this default block.
                    result << ch;
                    tokenLen = 1;
                    break;
            }
            i += tokenLen;
        }
        return result.str();
    }

    static std::string get_real_format(std::string format, DateTimeFormatInfo& dtfi)
    {
        std::string fmt;
        switch (format[0])
        {
            // Short Date
            case 'd': fmt = dtfi.ShortDatePattern; break;
            // Long Date
            case 'D': fmt = dtfi.LongDatePattern; break; 
            // Full (long date + short time)
            case 'f': fmt = dtfi.LongDatePattern + " " + dtfi.ShortTimePattern; break;
            // Full (long date + long time)
            case 'F': fmt = dtfi.FullDateTimePattern; break;
            // General (short date + short time)
            case 'g': fmt = dtfi.GeneralShortTimePattern; break;
            // General (short date + long time)
            case 'G': fmt = dtfi.GeneralLongTimePattern; break;
            // Month/Day Date
            case 'm': case 'M': fmt = dtfi.MonthDayPattern; break;
            // RoundtripFormat;
            case 'o': case 'O': fmt = "yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK"; break;
            // RFC 1123 Standard                    
            case 'r': case 'R': fmt = dtfi.RFC1123Pattern; break;
            // Sortable without Time Zone Info
            case 's': fmt = dtfi.SortableDateTimePattern; break;
            // Short Time
            case 't': fmt = dtfi.ShortTimePattern; break;
            // Long Time
            case 'T': fmt = dtfi.LongTimePattern; break;
            // Universal with Sortable format
            case 'u': fmt = dtfi.UniversalSortableDateTimePattern; break;
            // Universal with Full (long date + long time) format
            case 'U': fmt = dtfi.FullDateTimePattern; break;
            // Year/Month Date
            case 'y': case 'Y': fmt = dtfi.YearMonthPattern; break;
            // error
            default: OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
        }
        return fmt;
    }
    
    /*
        Expand a pre-defined format std::string (like "D" for long date) to the real format that
        we are going to use in the date time parsing.
        This method also convert the dateTime if necessary (e.g. when the format is in Universal time),
        and change dtfi if necessary (e.g. when the format should use invariant culture).
    */
    static std::string expand_predefined_format(std::string format, omni::chrono::date_time dateTime, DateTimeFormatInfo& dtfi, const omni::chrono::time_span& offset)
    {
        switch (format[0]) {
            case 'o': case 'O': // Round trip format
                dtfi = DateTimeFormatInfo::InvariantInfo;
                break;
            case 'r': case 'R': // RFC 1123 Standard
                if (offset != OMNI_TS_NULL_OFF_FW) {
                    // Convert to UTC invariants mean this will be in range
                    dateTime = dateTime - offset;
                } else if (dateTime.kind() == omni::chrono::date_time_kind::LOCAL) {
                    date_time_format::InvalidFormatForLocal(format, dateTime);
                }
                dtfi = DateTimeFormatInfo::InvariantInfo;
                break;
            case 's': // Sortable without Time Zone Info
                dtfi = DateTimeFormatInfo::InvariantInfo;
                break;                    
            case 'u': // Universal time in sortable format.
                if (offset != OMNI_TS_NULL_OFF_FW) {
                    // Convert to UTC invariants mean this will be in range
                    dateTime = dateTime - offset;
                } else if (dateTime.kind() == omni::chrono::date_time_kind::LOCAL) {
                    date_time_format::InvalidFormatForLocal(format, dateTime);
                }
                dtfi = DateTimeFormatInfo::InvariantInfo;
                break;
            case 'U': // Universal time in culture dependent format.
                if (offset != OMNI_TS_NULL_OFF_FW) {
                    // This format is not supported by DateTimeOffset
                    OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                }
                // Universal time is always in Greogrian calendar.
                // Change the Calendar to be Gregorian Calendar.
                /*dtfi = (DateTimeFormatInfo)dtfi.Clone();
                if (dtfi.Calendar.GetType() != typeof(GregorianCalendar)) {
                    dtfi.Calendar = GregorianCalendar.GetDefaultInstance();
                }*/
                dateTime = dateTime.to_universal_time();
                break;
        }
        return date_time_format::get_real_format(format, dtfi);
    }

    /*
    static String FORMAT(DateTime dateTime, String format, DateTimeFormatInfo dtfi, TimeSpan offset)
    */
    static std::string format(const omni::chrono::date_time& dt, std::string format, DateTimeFormatInfo& dtfi, const omni::chrono::time_span& offset)
    {
        if (format.empty()) {
            bool timeOnlySpecialCase = false;
            /*
                TODO: finish when Calendar class is done
                if (dt.ticks() < Calendar.omni::chrono::TICKS_PER_DAY) {
                    // If the time is less than 1 day, consider it as time of day.
                    // Just print out the short time format.
                    //
                    // This is a workaround for VB, since they use ticks less then one day to be 
                    // time of day.  In cultures which use calendar other than Gregorian calendar, these
                    // alternative calendar may not support ticks less than a day.
                    // For example, Japanese calendar only supports date after 1868/9/8.
                    // This will pose a problem when people in VB get the time of day, and use it
                    // to call ToString(), which will use the general format (short date + long time).
                    // Since Japanese calendar does not support Gregorian year 0001, an exception will be
                    // thrown when we try to get the Japanese year for Gregorian year 0001.
                    // Therefore, the workaround allows them to call ToString() for time of day from a DateTime by
                    // formatting as ISO 8601 format.
                    switch (dtfi.Calendar.ID) {
                        case Calendar.CAL_JAPAN: 
                        case Calendar.CAL_TAIWAN:
                        case Calendar.CAL_HIJRI:
                        case Calendar.CAL_HEBREW:
                        case Calendar.CAL_JULIAN:
                        case Calendar.CAL_UMALQURA:
                            timeOnlySpecialCase = true;
                            dtfi = DateTimeFormatInfo.InvariantInfo;
                            break;                        
                    }                     
                }
            */
            if (offset == OMNI_TS_NULL_OFF_FW) {
                // Default DateTime.ToString case.
                if (timeOnlySpecialCase) {
                    format = "s";
                } else {
                    format = "G";
                }
            } else {
                // Default DateTimeOffset.ToString case.
                if (timeOnlySpecialCase) {
                    format = "yyyy'-'MM'-'ddTHH':'mm':'ss zzz"; // RoundtripDateTimeUnfixed;
                } else {
                    format = dtfi.DateTimeOffsetPattern();
                }
            }
        }
        if (format.size() == 1) {
            format = date_time_format::expand_predefined_format(format, dt, dtfi, offset);
        }
        return date_time_format::format_customized(dt, format, dtfi, offset);
    }

    static std::string format(const omni::chrono::date_time& dt, std::string format)
    {
        return date_time_format::format(dt, format, DateTimeFormatInfo::CurrentInfo, OMNI_TS_NULL_OFF_FW);
    }

    static std::string format(const omni::chrono::date_time& dt, std::string format, DateTimeFormatInfo& dtfi)
    {
        return date_time_format::format(dt, format, dtfi, OMNI_TS_NULL_OFF_FW);
    }
}

date_time_format::DateTimeFormatInfo date_time_format::DateTimeFormatInfo::CurrentInfo;
date_time_format::DateTimeFormatInfo date_time_format::DateTimeFormatInfo::InvariantInfo;
