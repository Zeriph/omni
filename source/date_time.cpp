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
#include <omni/chrono/date_time.hpp>

#if defined(OMNI_SAFE_DATETIME)
    #define OMNI_SAFE_DTTMMTX_FW ,m_mtx()
    #define OMNI_DTTM_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> uuid12345(&this->m_mtx);
    #define OMNI_DTTM_OLOCK_FW(o) omni::sync::scoped_lock<omni::sync::basic_lock> uuid54321(&o.m_mtx);
    #define OMNI_DTTM_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_DTTM_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_DTTMMTX_FW
    #define OMNI_DTTM_ALOCK_FW
    #define OMNI_DTTM_OLOCK_FW(o)
    #define OMNI_DTTM_MLOCK_FW
    #define OMNI_DTTM_ULOCK_FW
#endif

// These are local defines
#define OMNI_MAX_MILLIS_FW static_cast<int64_t>(omni::chrono::MILLISECONDS_TO_10000AD)
#define OMNI_MAX_TICKS_FW omni::chrono::TICKS_TO_10000AD
#define OMNI_TS_NULL_OFF_FW omni::chrono::time_span::min_value()

///// start date_time_format code /////

// TODO: this causes docugen errors (to be expected)
namespace date_time_format {

    typedef void* object;

    /** The enum template */
    class ParseFailureKind
    {
        public:
            /** The underlying enum type expected */
            typedef enum enum_t {
                None = 0,
                ArgumentNull = 1,
                Format = 2,
                FormatWithParameter = 3,
                FormatBadDateTimeCalendar = 4,  // FormatException when ArgumentOutOfRange is thrown by a Calendar.TryToDateTime().
            } enum_t;

            /** Defines the number of elements in the enum */
            static inline unsigned short COUNT()
            {
                return 5;
            }

            /** The default value for this enum instance */
            static inline enum_t DEFAULT_VALUE()
            {
                return None;
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
            static bool try_parse(const std::string& val, ParseFailureKind& out)
            {
                return _try_parse(val, out);
            }

            /** Tries parsing a wide string value into its enum representation */
            static bool try_parse(const std::wstring& val, ParseFailureKind& out)
            {
                return _try_parse(val, out);
            }

            /** Returns true if the integer value specified is a valid enum value */
            static bool is_valid(int32_t val)
            {
                return _valid(val);
            }
            
            ParseFailureKind() :
                OMNI_CTOR_FW(date_time_format::ParseFailureKind)
                m_val(DEFAULT_VALUE())
            { }

            ParseFailureKind(const ParseFailureKind& cp) :
                OMNI_CPCTOR_FW(cp)
                m_val(cp.m_val)
            { }

            ParseFailureKind(enum_t val) : 
                OMNI_CTOR_FW(date_time_format::ParseFailureKind)
                m_val(val)
            { }

            ~ParseFailureKind()
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

            bool operator!=(const ParseFailureKind& val) const
            {
                return !(*this == val);
            }
            
            bool operator!=(enum_t val) const
            {
                return (this->m_val != val);
            }
            
            ParseFailureKind& operator=(const ParseFailureKind& val)
            {
                if (this != &val) {
                    OMNI_ASSIGN_FW(val)
                    this->m_val = val.m_val;
                }
                return *this;
            }

            ParseFailureKind& operator=(enum_t val)
            {
                this->m_val = val;
                return *this;
            }

            ParseFailureKind& operator=(int32_t val)
            {
                if (!ParseFailureKind::is_valid(val)) {
                    OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                } else {
                    this->m_val = static_cast<enum_t>(val);
                }
                return *this;
            }

            bool operator<(const ParseFailureKind& val) const
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

            bool operator>(const ParseFailureKind& val) const
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

            bool operator==(const ParseFailureKind& val) const
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

            OMNI_MEMBERS_FW(date_time_format::ParseFailureKind) // disposing,name,type(),hash()

            OMNI_OSTREAM_FW(date_time_format::ParseFailureKind)
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
            static bool _try_parse(const S& val, ParseFailureKind& out)
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
                    OMNI_S2E_FW(None)
                    OMNI_S2E_FW(ArgumentNull)
                    OMNI_S2E_FW(Format)
                    OMNI_S2E_FW(FormatWithParameter)
                    OMNI_S2E_FW(FormatBadDateTimeCalendar)
                }
                return false;
            }

            template < typename S >
            static std::basic_string< typename S::char_type > _to_val(enum_t v)
            {
                S ss;
                switch (v) {
                    OMNI_E2SS_FW(None);
                    OMNI_E2SS_FW(ArgumentNull);
                    OMNI_E2SS_FW(Format);
                    OMNI_E2SS_FW(FormatWithParameter);
                    OMNI_E2SS_FW(FormatBadDateTimeCalendar);
                    default:
                        ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                        break;
                }
                return ss.str();
            }

            static bool _valid(int32_t val)
            {
                return (val == 
                    None ||
                    ArgumentNull ||
                    Format ||
                    FormatWithParameter ||
                    FormatBadDateTimeCalendar
                );
            }
    };

    /** The enum template */
    class ParseFlags
    {
        public:
            /** The underlying enum type expected */
            typedef enum enum_t {
                HaveYear        = 0x00000001,
                HaveMonth       = 0x00000002,
                HaveDay         = 0x00000004,
                HaveHour        = 0x00000008,
                HaveMinute      = 0x00000010,
                HaveSecond      = 0x00000020,
                HaveTime        = 0x00000040,
                HaveDate        = 0x00000080,
                TimeZoneUsed    = 0x00000100,
                TimeZoneUtc     = 0x00000200,
                ParsedMonthName = 0x00000400,
                CaptureOffset   = 0x00000800,
                YearDefault     = 0x00001000,
                Rfc1123Pattern  = 0x00002000,
                UtcSortPattern  = 0x00004000
            } enum_t;

            /** Defines the number of elements in the enum */
            static inline unsigned short COUNT()
            {
                return 15;
            }

            /** The default value for this enum instance */
            static inline enum_t DEFAULT_VALUE()
            {
                return HaveYear;
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
            static bool try_parse(const std::string& val, ParseFlags& out)
            {
                return _try_parse(val, out);
            }

            /** Tries parsing a wide string value into its enum representation */
            static bool try_parse(const std::wstring& val, ParseFlags& out)
            {
                return _try_parse(val, out);
            }

            /** Returns true if the integer value specified is a valid enum value */
            static bool is_valid(int32_t val)
            {
                return _valid(val);
            }
            
            ParseFlags() :
                OMNI_CTOR_FW(date_time_format::ParseFlags)
                m_val(DEFAULT_VALUE())
            { }

            ParseFlags(const ParseFlags& cp) :
                OMNI_CPCTOR_FW(cp)
                m_val(cp.m_val)
            { }

            ParseFlags(enum_t val) : 
                OMNI_CTOR_FW(date_time_format::ParseFlags)
                m_val(val)
            { }

            ~ParseFlags()
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

            bool operator!=(const ParseFlags& val) const
            {
                return !(*this == val);
            }
            
            bool operator!=(enum_t val) const
            {
                return (this->m_val != val);
            }
            
            ParseFlags& operator=(const ParseFlags& val)
            {
                if (this != &val) {
                    OMNI_ASSIGN_FW(val)
                    this->m_val = val.m_val;
                }
                return *this;
            }

            ParseFlags& operator=(enum_t val)
            {
                this->m_val = val;
                return *this;
            }

            ParseFlags& operator=(int32_t val)
            {
                if (!ParseFlags::is_valid(val)) {
                    OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                } else {
                    this->m_val = static_cast<enum_t>(val);
                }
                return *this;
            }

            bool operator<(const ParseFlags& val) const
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

            bool operator>(const ParseFlags& val) const
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

            bool operator==(const ParseFlags& val) const
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

            OMNI_MEMBERS_FW(date_time_format::ParseFlags) // disposing,name,type(),hash()

            OMNI_OSTREAM_FW(date_time_format::ParseFlags)
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
            static bool _try_parse(const S& val, ParseFlags& out)
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
                    OMNI_S2E_FW(HaveYear)
                    OMNI_S2E_FW(HaveMonth)
                    OMNI_S2E_FW(HaveDay)
                    OMNI_S2E_FW(HaveHour)
                    OMNI_S2E_FW(HaveMinute)
                    OMNI_S2E_FW(HaveSecond)
                    OMNI_S2E_FW(HaveTime)
                    OMNI_S2E_FW(HaveDate)
                    OMNI_S2E_FW(TimeZoneUsed)
                    OMNI_S2E_FW(TimeZoneUtc)
                    OMNI_S2E_FW(ParsedMonthName)
                    OMNI_S2E_FW(CaptureOffset)
                    OMNI_S2E_FW(YearDefault)
                    OMNI_S2E_FW(Rfc1123Pattern)
                    OMNI_S2E_FW(UtcSortPattern)
                }
                return false;
            }

            template < typename S >
            static std::basic_string< typename S::char_type > _to_val(enum_t v)
            {
                S ss;
                switch (v) {
                    OMNI_E2SS_FW(HaveYear);
                    OMNI_E2SS_FW(HaveMonth);
                    OMNI_E2SS_FW(HaveDay);
                    OMNI_E2SS_FW(HaveHour);
                    OMNI_E2SS_FW(HaveMinute);
                    OMNI_E2SS_FW(HaveSecond);
                    OMNI_E2SS_FW(HaveTime);
                    OMNI_E2SS_FW(HaveDate);
                    OMNI_E2SS_FW(TimeZoneUsed);
                    OMNI_E2SS_FW(TimeZoneUtc);
                    OMNI_E2SS_FW(ParsedMonthName);
                    OMNI_E2SS_FW(CaptureOffset);
                    OMNI_E2SS_FW(YearDefault);
                    OMNI_E2SS_FW(Rfc1123Pattern);
                    OMNI_E2SS_FW(UtcSortPattern);
                    default:
                        ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                        break;
                }
                return ss.str();
            }

            static bool _valid(int32_t val)
            {
                return (val == 
                    HaveYear ||
                    HaveMonth ||
                    HaveDay ||
                    HaveHour ||
                    HaveMinute ||
                    HaveSecond ||
                    HaveTime ||
                    HaveDate ||
                    TimeZoneUsed ||
                    TimeZoneUtc ||
                    ParsedMonthName ||
                    CaptureOffset ||
                    YearDefault ||
                    Rfc1123Pattern ||
                    UtcSortPattern
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

            date_time_format::ParseFlags flags;

            omni::chrono::time_span timeZoneOffset;

            //Calendar calendar;

            omni::chrono::date_time parsedDate;

            date_time_format::ParseFailureKind failure;
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
            
            void SetFailure(const ParseFailureKind& failure, const std::string& failureMessageID, object failureMessageFormatArgument) {
                this->failure = failure;
                this->failureMessageID = failureMessageID;
                this->failureMessageFormatArgument = failureMessageFormatArgument;
            }

            void SetFailure(const ParseFailureKind& failure, const std::string& failureMessageID, object failureMessageFormatArgument, const std::string& failureArgumentName) {
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
                result.SetFailure(date_time_format::ParseFailureKind::Format, "Format_BadDateTime", NULL);
                return false;
            }
            if (format.empty()) {
                result.SetFailure(date_time_format::ParseFailureKind::Format, "Format_BadFormatSpecifier", NULL);
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
         Exceptions: None.
        

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
            if (timeOnly && dateTime.ticks() < omni::chrono::TICKS_PER_DAY) { // TODO: CAL -> Calendar.omni::chrono::TICKS_PER_DAY) {
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
            // source is a date time, so behavior depends on the kind.
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
        // Limit the use of this function to be two-digits, so that we have the same behavior
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
        Format the positive integer value to a std::string and perfix with assigned 
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
        
        Actions: Format the DateTime instance using the specified format.
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
            int year = 2020; // TODO: with CAL -> cal.GetYear(dateTime);
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
                        fraction = fraction / (long)std::pow(10, 7 - tokenLen);
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
                    // Notes about OS behavior:
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

    static std::string format(const omni::chrono::date_time& dt, std::string format, DateTimeFormatInfo& dtfi, const omni::chrono::time_span& offset)
    {
        if (format.empty()) {
            bool timeOnlySpecialCase = false;
            /*
            TODO: finish when Calendar class is done
            if (dt.Ticks < Calendar.omni::chrono::TICKS_PER_DAY) {
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
            }
            else {
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

/////  end date_time_format code  /////

// --- start private ctors ---

// not 'user' accessable as it's used to construct empty (min) DT objects
omni::chrono::date_time::date_time() :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(bool is_ambiguous_dst, const omni::chrono::date_time_kind& kind, uint64_t ticks, const std::string& non_op) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range())
    }
    if (kind != omni::chrono::date_time_kind::LOCAL) {
        OMNI_ERR_FW("Invalid enum specified for private constructor", omni::exceptions::invalid_enum())
    }
    this->m_date = (ticks | (is_ambiguous_dst ? OMNI_KIND_LOCAL_AMBIGUOUS_DST_FW : OMNI_KIND_LOCAL_FW));
    OMNI_D5_FW("created");
}

// --- end private ctors ---

omni::chrono::date_time::date_time(const omni::chrono::date_time& cp) :
    OMNI_CPCTOR_FW(cp)
    m_date(cp.m_date)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_D5_FW("copied");
}

omni::chrono::date_time::date_time(uint64_t ticks) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range())
    }
    this->m_date = ticks;
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint64_t ticks, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range())
    }
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum())
    }
    this->m_date = (ticks | (static_cast<uint64_t>(kind.value()) << OMNI_KIND_SHIFT_FW));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    this->m_date = static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    this->m_date = static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
                   static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum())
    }
    this->m_date =
    (
        (
            static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
            static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
        ) // ticks
        | // OR'd
        ( // with kind
            static_cast<uint64_t>(kind.value()) << OMNI_KIND_SHIFT_FW
        )
    );
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if ((millisecond < 0) || (millisecond >= omni::chrono::MILLISECONDS_PER_SECOND)) {
        OMNI_ERR_FW("Invalid milliseconds specified", omni::exceptions::invalid_range())
    }
    uint64_t ticks = (
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
        static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
    ) + (millisecond * omni::chrono::TICKS_PER_MILLISECOND);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range())
    }
    this->m_date = ticks;
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if ((millisecond < 0) || (millisecond >= omni::chrono::MILLISECONDS_PER_SECOND)) {
        OMNI_ERR_FW("Invalid milliseconds specified", omni::exceptions::invalid_range())
    }
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum())
    }
    uint64_t ticks = (
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
        static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
    ) + (millisecond * omni::chrono::TICKS_PER_MILLISECOND);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range())
    }
    this->m_date = (ticks | (static_cast<uint64_t>(kind.value()) << OMNI_KIND_SHIFT_FW));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::~date_time()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

omni::chrono::date_time omni::chrono::date_time::add(const omni::chrono::time_span& value)
{
    return this->add_ticks(value.ticks());
}

omni::chrono::date_time omni::chrono::date_time::add_days(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, omni::chrono::MILLISECONDS_PER_DAY);
}

omni::chrono::date_time omni::chrono::date_time::add_hours(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, omni::chrono::MILLISECONDS_PER_HOUR);
}

omni::chrono::date_time omni::chrono::date_time::add_milliseconds(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, 1);
}

omni::chrono::date_time omni::chrono::date_time::add_minutes(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, omni::chrono::MILLISECONDS_PER_MINUTE);
}

omni::chrono::date_time omni::chrono::date_time::add_months(uint32_t months)
{
    OMNI_DTTM_ALOCK_FW
    if ((months < -120000) || (months > 120000)) {
        OMNI_ERR_RETV_FW("Invalid months specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    int64_t y = omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW);
    int64_t m = omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW);
    int64_t d = omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW);
    int64_t i = m - 1 + months;
    if (i >= 0) {
        m = i % 12 + 1;
        y = y + i / 12;
    } else {
        m = 12 + (i + 1) % 12;
        y = y + (i - 11) / 12;
    }
    if (y < 1 || y > 9999) {
        OMNI_ERR_RETV_FW("Invalid months specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    int days = omni::chrono::date_time::days_in_month(y, m);
    if (d > days) {
        d = days;
    }
    return omni::chrono::date_time(
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(y, m, d) + (this->_ticks() % omni::chrono::TICKS_PER_DAY))
        | this->_internal_kind()
    );
}

omni::chrono::date_time omni::chrono::date_time::add_seconds(double value)
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, omni::chrono::MILLISECONDS_PER_SECOND);
}

omni::chrono::date_time omni::chrono::date_time::add_ticks(int64_t value)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    if ((value > (OMNI_MAX_TICKS_FW - ticks)) || (value < (-ticks)) ) {
        OMNI_ERR_RETV_FW("Invalid ticks specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks + value) | this->_internal_kind());
}

omni::chrono::date_time omni::chrono::date_time::add_years(int16_t value)
{
    if ((value < -10000) || (value > 10000)) {
        OMNI_ERR_RETV_FW("Invalid years specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    return this->add_months(value * 12);
}

bool omni::chrono::date_time::is_dst() const
{
    OMNI_DTTM_ALOCK_FW
    if (this->_kind() == omni::chrono::date_time_kind::UTC) {
        return false;
    }
    // TOOD: more TimeZoneInfo that needs to be implemented
    //return TimeZoneInfo.Local.IsDaylightSavingTime(this, TimeZoneInfoOptions.NoThrowOnInvalidTime);
    return false;
}

int64_t omni::chrono::date_time::to_binary() const
{
    if (this->kind() == omni::chrono::date_time_kind::UTC) {
        // Local times need to be adjusted as you move from one time zone to another, 
        // just as they are when serializing in text. As such the format for local times
        // changes to store the ticks of the UTC time, but with flags that look like a 
        // local date.
    
        // To match serialization in text we need to be able to handle cases where
        // the UTC value would be out of range. Unused parts of the ticks range are
        // used for this, so that values just past max value are stored just past the
        // end of the maximum range, and values just below minimum value are stored
        // at the end of the ticks area, just below 2^62.

        omni::chrono::time_span offset;// TODO: = TimeZoneInfo.GetLocalUtcOffset(this, TimeZoneInfoOptions.NoThrowOnInvalidTime);
        int64_t ticks = this->_ticks();
        int64_t stored = ticks - offset.ticks();
        if (stored < 0) {
            stored = OMNI_TICKS_CEILING_FW + stored;
        }
        return stored | static_cast<int64_t>(OMNI_LOCAL_MASK_FW);
    }
    return static_cast<int64_t>(this->m_date);
}

omni::chrono::date_time omni::chrono::date_time::date() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - ticks % omni::chrono::TICKS_PER_DAY) | this->_internal_kind());
}

// Returns the day-of-month part of this DateTime. The returned
// value is an integer between 1 and 31.
uint8_t omni::chrono::date_time::day() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW);
}

omni::chrono::day_of_week omni::chrono::date_time::day_of_week() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::day_of_week(
        static_cast<omni::chrono::day_of_week::enum_t>((this->_ticks() / omni::chrono::TICKS_PER_DAY + 1) % 7)
    );
}

uint16_t omni::chrono::date_time::day_of_year() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_OF_YEAR_FW);
}

int32_t omni::chrono::date_time::hash_code() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    return static_cast<int32_t>(ticks) ^ static_cast<int32_t>(ticks >> 32);
}

uint8_t omni::chrono::date_time::hour() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint8_t>((this->_ticks() / omni::chrono::TICKS_PER_HOUR) % 24);
}

omni::chrono::date_time_kind omni::chrono::date_time::kind() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_kind();
}

uint16_t omni::chrono::date_time::millisecond() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ omni::chrono::TICKS_PER_MILLISECOND) % 1000); 
}

uint8_t omni::chrono::date_time::minute() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ omni::chrono::TICKS_PER_MINUTE) % 60); 
}

uint8_t omni::chrono::date_time::month() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW);
}

uint8_t omni::chrono::date_time::second() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ omni::chrono::TICKS_PER_SECOND) % 60); 
}

uint64_t omni::chrono::date_time::ticks() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_ticks();
}

omni::chrono::time_span omni::chrono::date_time::time_of_day() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() % omni::chrono::TICKS_PER_DAY); 
}

uint16_t omni::chrono::date_time::year() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW);
}

omni::chrono::time_span omni::chrono::date_time::subtract(const omni::chrono::date_time& value) const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() - value._ticks());
}

omni::chrono::date_time omni::chrono::date_time::subtract(const omni::chrono::time_span& value) const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();            
    int64_t vticks = value.ticks();
    if (ticks < vticks || ticks - OMNI_MAX_TICKS_FW > vticks) {
        OMNI_ERR_RETV_FW("Invalid time span specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
}

double omni::chrono::date_time::to_oa_date() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_ticks_to_oa_date(this->_ticks());
}

uint64_t omni::chrono::date_time::to_file_time() const
{
    // Treats the input as local if it is not specified
    return this->to_universal_time().to_file_time_utc();
}

uint64_t omni::chrono::date_time::to_file_time_utc() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = (((this->_internal_kind() & OMNI_LOCAL_MASK_FW) != 0) ?
                        this->to_universal_time()._ticks() :
                        this->_ticks()) -
                    omni::chrono::FILE_TIME_OFFSET;
    if (ticks < 0) {
        OMNI_ERR_RETV_FW("Invalid file time specified", omni::exceptions::invalid_range(), 0)
    }
    return ticks;
}

omni::chrono::date_time omni::chrono::date_time::to_local_time() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_to_local_time(false);
}

std::string omni::chrono::date_time::to_long_date_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "D");
}

std::wstring omni::chrono::date_time::to_long_date_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "D"));
}

std::string omni::chrono::date_time::to_long_time_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "T");
}

std::wstring omni::chrono::date_time::to_long_time_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "T"));
}

std::string omni::chrono::date_time::to_short_date_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "d");
}

std::wstring omni::chrono::date_time::to_short_date_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "d"));
}

std::string omni::chrono::date_time::to_short_time_string() const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, "t");
}

std::wstring omni::chrono::date_time::to_short_time_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, "t"));
}

std::string omni::chrono::date_time::to_string(const std::string& format) const
{
    OMNI_DTTM_ALOCK_FW
    return date_time_format::format(*this, format);
}

std::wstring omni::chrono::date_time::to_wstring(const std::wstring& format) const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(date_time_format::format(*this, omni::string_util::to_string(format)));
}

omni::chrono::date_time omni::chrono::date_time::to_universal_time() const
{
    if (this->kind() == omni::chrono::date_time_kind::UTC) {
        return omni::chrono::date_time(*this);
    }
    OMNI_DTTM_ALOCK_FW
    // TODO: finish this
    //return TimeZoneInfo.ConvertTimeToUtc(this, TimeZoneInfoOptions.NoThrowOnInvalidTime);
    return omni::chrono::date_time(*this);
}

omni::sequence::string_t omni::chrono::date_time::get_date_time_formats() const
{
    OMNI_DTTM_ALOCK_FW
    // TODO: finish
    // return (GetDateTimeFormats(CultureInfo.CurrentCulture));
    return omni::sequence::string_t();
}

omni::sequence::string_t omni::chrono::date_time::get_date_time_formats(char format) const
{
    OMNI_DTTM_ALOCK_FW
    // TODO: finish
    // return (GetDateTimeFormats(format, CultureInfo.CurrentCulture));
    return omni::sequence::string_t();
}

void omni::chrono::date_time::swap(omni::chrono::date_time& other)
{
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    OMNI_XOR_SWAP(this->m_date, other.m_date);
}

omni::string_t omni::chrono::date_time::to_string_t() const
{
    #if defined(OMNI_UNICODE)
        return this->to_wstring();
    #else
        return this->to_string();
    #endif
}

std::string omni::chrono::date_time::to_string() const
{
    return this->to_string(std::string());
}

std::wstring omni::chrono::date_time::to_wstring() const
{
    return this->to_wstring(std::wstring());
}

omni::chrono::date_time& omni::chrono::date_time::operator=(const omni::chrono::date_time& ap)
{

    if (this != &ap) {
        OMNI_DTTM_ALOCK_FW
        OMNI_DTTM_OLOCK_FW(ap)
        OMNI_ASSIGN_FW(ap)
        this->m_date = ap.m_date;
    }
    return *this;
}

omni::chrono::date_time omni::chrono::date_time::operator+(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((vticks > (OMNI_MAX_TICKS_FW - ticks)) || (vticks < (0 - ticks))) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), *this)
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks + vticks) | this->_internal_kind());
}

omni::chrono::date_time omni::chrono::date_time::operator-(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), *this)
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
}

omni::chrono::date_time& omni::chrono::date_time::operator+=(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((vticks > (OMNI_MAX_TICKS_FW - ticks)) || (vticks < (0 - ticks))) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), *this)
    }
    this->m_date = (static_cast<uint64_t>(ticks + vticks) | this->_internal_kind());
    return *this;
}

omni::chrono::date_time& omni::chrono::date_time::operator-=(const omni::chrono::time_span& t)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = t.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), *this)
    }
    this->m_date = (static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
    return *this;
}

omni::chrono::time_span omni::chrono::date_time::operator-(const omni::chrono::date_time& d2)
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() - d2.ticks());
}

omni::chrono::time_span omni::chrono::date_time::operator+(const omni::chrono::date_time& d2)
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() + d2.ticks());
}

bool omni::chrono::date_time::operator==(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (
        this->m_date == d2.m_date
    )
    OMNI_EQUAL_FW(d2);
}

bool omni::chrono::date_time::operator!=(const omni::chrono::date_time& d2) const
{
    return !(*this == d2);
}

bool omni::chrono::date_time::operator<(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return false; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date < d2.m_date);
}

bool omni::chrono::date_time::operator<=(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date <= d2.m_date);
}

bool omni::chrono::date_time::operator>(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return false; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date > d2.m_date);
}

bool omni::chrono::date_time::operator>=(const omni::chrono::date_time& d2) const
{
    if (this == &d2) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(d2)
    return (this->m_date >= d2.m_date);
}

// -- start private methods --

omni::chrono::date_time omni::chrono::date_time::_add(double value, int64_t scale)
{
    int64_t millis = static_cast<uint64_t>((value * scale) + (value >= 0.0 ? 0.5 : -0.5));
    if (millis <= -OMNI_MAX_MILLIS_FW || millis >= OMNI_MAX_MILLIS_FW) {
        OMNI_ERR_RETV_FW("Invalid value/scale specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    return this->add_ticks(millis * omni::chrono::TICKS_PER_MILLISECOND);
}

omni::chrono::date_time_kind omni::chrono::date_time::_kind() const
{
    switch (this->_internal_kind()) {
        case OMNI_KIND_UNSPECIFIED_FW:
            return omni::chrono::date_time_kind::UNSPECIFIED;
        case OMNI_KIND_UTC_FW:
            return omni::chrono::date_time_kind::UTC;
        default:
            return omni::chrono::date_time_kind::LOCAL;                    
    }
}

int64_t omni::chrono::date_time::_to_binary_raw() const
{
    return static_cast<int64_t>(this->m_date);
}

int64_t omni::chrono::date_time::_get_date_part(uint8_t part) const
{
    const int32_t* days = OMNI_NULL;
    int64_t n, y400, y100, y4, y1, m;
    int64_t ticks = this->_ticks();
    // n = number of days since 1/1/0001
    n = (ticks / omni::chrono::TICKS_PER_DAY);
    // y400 = number of whole 400-year periods since 1/1/0001
    y400 = n / omni::chrono::DAYS_PER_400_YEARS;
    // n = day number within 400-year period
    n -= y400 * omni::chrono::DAYS_PER_400_YEARS;
    // y100 = number of whole 100-year periods within 400-year period
    y100 = n / omni::chrono::DAYS_PER_100_YEARS;
    // Last 100-year period has an extra day, so decrement result if 4
    if (y100 == 4) { y100 = 3; }
    // n = day number within 100-year period
    n -= y100 * omni::chrono::DAYS_PER_100_YEARS;
    // y4 = number of whole 4-year periods within 100-year period
    y4 = n / omni::chrono::DAYS_PER_4_YEARS;
    // n = day number within 4-year period
    n -= y4 * omni::chrono::DAYS_PER_4_YEARS;
    // y1 = number of whole years within 4-year period
    y1 = n / omni::chrono::DAYS_PER_YEAR;
    // Last year has an extra day, so decrement result if 4
    if (y1 == 4) y1 = 3;
    // If year was requested, compute and return it
    if (part == OMNI_DATE_PART_YEAR_FW) {
        return y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1;
    }
    // n = day number within year
    n -= y1 * omni::chrono::DAYS_PER_YEAR;
    // If day-of-year was requested, return it
    if (part == OMNI_DATE_PART_YEAR_FW) {
        return n + 1;
    }
    // Leap year calculation looks different from IsLeapYear since y1, y4,
    // and y100 are relative to year 1, not year 0
    m = (n >> 5) + 1;

    // All months have less than 32 days, so n >> 5 is a good conservative
    // estimate for the month
    // m = 1-based month number
    if ((y1 == 3) && (y4 != 24 || y100 == 3)) {
        days = &omni::chrono::DAYS_TO_MONTH_366[0];
    } else {
        days = &omni::chrono::DAYS_TO_MONTH_365[0];
    }

    while (n >= days[m]) {
        m++;
    }
    // If month was requested, return it
    if (part == OMNI_DATE_PART_MONTH_FW) {
        return m;
    }
    // Return 1-based day-of-month
    return n - days[m - 1] + 1;
}

bool omni::chrono::date_time::_is_ambiguous_daylight_saving_time() const
{
    OMNI_DTTM_ALOCK_FW
    return (this->_internal_kind() == OMNI_KIND_LOCAL_AMBIGUOUS_DST_FW);
}

omni::chrono::date_time omni::chrono::date_time::_to_local_time(bool throw_on_overflow) const
{
    //OMNI_DTTM_ALOCK_FW
    
    if (this->kind() == omni::chrono::date_time_kind::LOCAL) {
        return omni::chrono::date_time(*this);
    }
    bool isDaylightSavings = false;
    bool isAmbiguousLocalDst = false;
    int64_t offset = 0; // TODO: finish -> TimeZoneInfo.GetUtcOffsetFromUtc(this, TimeZoneInfo.Local, out isDaylightSavings, out isAmbiguousLocalDst).Ticks;
    int64_t tick = this->_ticks() + offset;
    if (tick > OMNI_MAX_TICKS_FW) {
        if (throw_on_overflow) {
            OMNI_ERR_RETV_FW("Invalid ticks for local time", omni::exceptions::invalid_range(), omni::chrono::date_time())
        } else {
            return omni::chrono::date_time(OMNI_MAX_TICKS_FW, omni::chrono::date_time_kind::LOCAL);
        }
    }
    if (tick < 0) {
        if (throw_on_overflow) {
            OMNI_ERR_RETV_FW("Invalid local time", omni::exceptions::invalid_range(), omni::chrono::date_time())
        } else {
            return omni::chrono::date_time(0, omni::chrono::date_time_kind::LOCAL);
        }
    }
    return omni::chrono::date_time(isAmbiguousLocalDst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(tick), std::string(""));
}

// -- start static methods --

uint16_t omni::chrono::date_time::days_in_month(uint16_t year, uint8_t month)
{
    if ((month < 1) || (month > 12)) {
        OMNI_ERR_RETV_FW("Invalid month specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    if (omni::chrono::is_leap_year(year)) {
        // check the year argument
        return omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1];
    }
    return omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1];
}

omni::chrono::date_time omni::chrono::date_time::from_binary(int64_t date_data)
{
    if ((date_data & static_cast<int64_t>(OMNI_LOCAL_MASK_FW)) != 0) {
        // Local times need to be adjusted as you move from one time zone to another, 
        // just as they are when serializing in text. As such the format for local times
        // changes to store the ticks of the UTC time, but with flags that look like a 
        // local date.
        bool ambig_dst = false;
        int64_t offset = 0;
        int64_t ticks = (date_data & static_cast<int64_t>(OMNI_TICKS_MASK_FW));
        // Negative ticks are stored in the top part of the range and should be converted back into a negative number
        if (ticks > OMNI_TICKS_CEILING_FW - omni::chrono::TICKS_PER_DAY) {
            ticks = ticks - OMNI_TICKS_CEILING_FW;
        }
        // Convert the ticks back to local. If the UTC ticks are out of range, we need to default to
        // the UTC offset from MinValue and MaxValue to be consistent with Parse. 
        

        // TODO: need to work on TimeZoneInfo
        /*
        if (ticks < 0) {
            offset = TimeZoneInfo.GetLocalUtcOffset(omni::chrono::date_time::min_value(), TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
        } else if (ticks > OMNI_MAX_TICKS_FW) {
            offset = TimeZoneInfo.GetLocalUtcOffset(omni::chrono::date_time::max_value(), TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
        } else {                    
            // Because the ticks conversion between UTC and local is lossy, we need to capture whether the 
            // time is in a repeated hour so that it can be passed to the DateTime constructor.
            omni::chrono::date_time utcDt(ticks, omni::chrono::date_time_kind::UTC);
            bool isDaylightSavings = false;
            offset = TimeZoneInfo.GetUtcOffsetFromUtc(utcDt, TimeZoneInfo.Local, out isDaylightSavings, out ambig_dst).Ticks;
        }
        */

        ticks += offset;
        // Another behaviour of parsing is to cause small times to wrap around, so that they can be used
        // to compare times of day
        if (ticks < 0) {
            ticks += omni::chrono::TICKS_PER_DAY;
        }                
        if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
            OMNI_ERR_RETV_FW("Invalid binary tick count specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
        }
        return omni::chrono::date_time(ambig_dst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(ticks), std::string(""));
    }
    return omni::chrono::date_time::_from_binary_raw(date_data);
}

omni::chrono::date_time omni::chrono::date_time::from_file_time(int64_t file_time)
{
    return omni::chrono::date_time::from_file_time_utc(file_time).to_local_time();
}

omni::chrono::date_time omni::chrono::date_time::from_file_time_utc(int64_t file_time)
{
    if (file_time < 0 || file_time > OMNI_MAX_TICKS_FW - omni::chrono::FILE_TIME_OFFSET) {
        OMNI_ERR_RETV_FW("Invalid file time specified", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    // This is the ticks in Universal time for this file_time.
    int64_t uticks = file_time + omni::chrono::FILE_TIME_OFFSET;            
    return omni::chrono::date_time(static_cast<uint64_t>(uticks), omni::chrono::date_time_kind::UTC);
}

omni::chrono::date_time omni::chrono::date_time::from_oa_date(double d)
{
    return omni::chrono::date_time(omni::chrono::date_time::_double_date_to_ticks(d), omni::chrono::date_time_kind::UNSPECIFIED);
}

omni::chrono::date_time omni::chrono::date_time::specify_kind(const date_time& value, const omni::chrono::date_time_kind& kind)
{
    return omni::chrono::date_time(value._ticks(), kind);
}

omni::chrono::date_time omni::chrono::date_time::now()
{
    omni::chrono::date_time utc = omni::chrono::date_time::utc_now(); 
    bool isAmbiguousLocalDst = false;
    int64_t offset = 0; // TODO: finish -> TimeZoneInfo.GetDateTimeNowUtcOffsetFromUtc(utc, out isAmbiguousLocalDst).Ticks;
    int64_t tick = utc.ticks() + offset;
    if (tick > OMNI_MAX_TICKS_FW) {
        return omni::chrono::date_time(OMNI_MAX_TICKS_FW, omni::chrono::date_time_kind::LOCAL);
    }
    if (tick < 0) {
        return omni::chrono::date_time(0, omni::chrono::date_time_kind::LOCAL);
    }
    return omni::chrono::date_time(isAmbiguousLocalDst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(tick), std::string(""));
}

omni::chrono::date_time omni::chrono::date_time::utc_now()
{
    // following code is tuned for speed. Don't change it without running benchmark.
    int64_t ticks = 0;
    #if defined(OMNI_OS_WIN)
        FILETIME ft;
        ticks = ::GetSystemTimeAsFileTime(&ft);
        ULARGE_INTEGER tm;
        tm.LowPart = ft.dwLowDateTime;
        tm.HighPart = ft.dwHighDateTime;
        ticks = static_cast<int64_t>(tm.QuadPart);
        /*
            DEV_NOTE: this is from the .NET source, but mathematically doesn't make sense ...

            if (CompatibilitySwitches.IsAppEarlierThanWindowsPhone8) {
                // Windows Phone 7.0/7.1 return the ticks up to millisecond, not up to the 100th nanosecond.

                long ticksms = ticks / TicksPerMillisecond; <- here .. ticksms now == (ticks / TicksPerMillisecond)
                ticks = ticksms * TicksPerMillisecond;      <- so right here, doing ticks = ticksms * TicksPerMillisecond
            }

            that code is like saying this:
            
            ticks = (ticks / TicksPerMillisecond) * TicksPerMillisecond;
            
            and since the multiplication cancels out the division, it's
            just doing this:

            ticks = ticks;

            huh??
        */
        ticks += omni::chrono::FILE_TIME_OFFSET;
    #else
        #if defined(OMNI_OS_APPLE)
            struct timeval tv;
            if (::gettimeofday(&tv, NULL) != 0) {
                OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
            }
            ticks = (tv.tv_sec * omni::chrono::TICKS_PER_SECOND) + (tv.tv_usec * omni::chrono::TICKS_PER_MICROSECOND);
        #else
            struct timespec tm;
            if (::clock_gettime(CLOCK_REALTIME, &tm) != 0) {
                OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
            }
            ticks = (tv.tv_sec * omni::chrono::TICKS_PER_SECOND) + (tv.tv_nsec * omni::chrono::TICKS_PER_NANOSECOND);
        #endif
        ticks += omni::chrono::EPOCH_OFFSET;
    #endif
    return omni::chrono::date_time(static_cast<uint64_t>(ticks) | OMNI_KIND_UTC_FW);
}

omni::chrono::date_time omni::chrono::date_time::today()
{
    return omni::chrono::date_time::now().date();
}

bool omni::chrono::date_time::is_leap_year(uint16_t year)
{
    if ((year < 1) || (year > 9999)) {
        OMNI_ERR_RETV_FW("Invalid year specified", omni::exceptions::invalid_range(), false)
    }
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

omni::chrono::date_time omni::chrono::date_time::parse(const std::string& s)
{
    return date_time_format::DateTimeParse::Parse(s,
        date_time_format::DateTimeFormatInfo::CurrentInfo,
        omni::chrono::date_time_styles::NONE);
}

/*
    Constructs a DateTime from a string. The string must specify a
    date and optionally a time in a culture-specific or universal format.
    Leading and trailing whitespace characters are allowed.
*/
omni::chrono::date_time omni::chrono::date_time::parse_exact(const std::string& s, const std::string& format)
{
    date_time_format::DateTimeFormatInfo dtfi(date_time_format::DateTimeFormatInfo::GetInstance(/*provider*/));
    return date_time_format::DateTimeParse::ParseExact(s, format,
        dtfi,
        omni::chrono::date_time_styles::NONE);
}

bool omni::chrono::date_time::try_parse(const std::string& s, omni::chrono::date_time& result)
{
    return date_time_format::DateTimeParse::TryParse(s,
        date_time_format::DateTimeFormatInfo::CurrentInfo,
        omni::chrono::date_time_styles::NONE, result);
}

bool omni::chrono::date_time::try_parse_exact(const std::string& s, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result)
{
    date_time_format::DateTimeFormatInfo dtfi(date_time_format::DateTimeFormatInfo::GetInstance(/*provider*/));
    return date_time_format::DateTimeParse::TryParseExact(s, format, dtfi, style, result);
}

// -- start private static methods --

int64_t omni::chrono::date_time::_date_to_ticks(uint16_t year, uint8_t month, uint8_t day)
{
    if ((year >= 1) && (year <= 9999) && (month >= 1) && (month <= 12)) {
        const int32_t* days = omni::chrono::is_leap_year(year) ?
                        &omni::chrono::DAYS_TO_MONTH_365[0]:
                        &omni::chrono::DAYS_TO_MONTH_366[0];
        if ((day >= 1) && (day <= (days[month] - days[month - 1]))) {
            int32_t y = year - 1;
            return ((y * 365) + (y / 4) - (y / 100) + (y / 400) + days[month - 1] + day - 1) * omni::chrono::TICKS_PER_DAY;
        }
    }
    OMNI_ERR_RETV_FW("Invalid year/month/day specified", omni::exceptions::invalid_range(), 0)
}

int64_t omni::chrono::date_time::_time_to_ticks(uint8_t hour, uint8_t minute, uint8_t second)
{
    //omni::chrono::time_span.TimeToTicks is a family access function which does no error checking, so
    //we need to put some error checking out here.
    if ((hour >= 0) && (hour < 24) && (minute >= 0) && (minute < 60) && (second >=0) && (second < 60)) {
        return omni::chrono::time_span::from_time(hour, minute, second).ticks();
    }
    OMNI_ERR_RETV_FW("Invalid hour/minute/second specified", omni::exceptions::invalid_range(), 0)
}

int64_t omni::chrono::date_time::_double_date_to_ticks(double value)
{
    // DEV_NOTE: the comments are from the .NET source .. thanks to you whomever you were
    // The check done this way will take care of NaN
    if (!(value < omni::chrono::OA_DATE_MAX_AS_DOUBLE) || !(value > omni::chrono::OA_DATE_MIN_AS_DOUBLE)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), 0)
    }
    // Conversion to long will not cause an overflow here, as at this point the "value" is in between OADateMinAsDouble and OADateMaxAsDouble
    int64_t millis = static_cast<int64_t>(value * omni::chrono::MILLISECONDS_PER_DAY + (value >= 0? 0.5: -0.5));
    // The interesting thing here is when you have a value like 12.5 it all positive 12 days and 12 hours from 01/01/1899
    // However if you a value of -12.25 it is minus 12 days but still positive 6 hours, almost as though you meant -11.75 all negative
    // This line below fixes up the millis in the negative case
    if (millis < 0) {
        millis -= (millis % omni::chrono::MILLISECONDS_PER_DAY) * 2;
    }
    millis += omni::chrono::DOUBLE_DATE_OFFSET / omni::chrono::TICKS_PER_MILLISECOND;
    if (millis < 0 || millis >= OMNI_MAX_MILLIS_FW) {
        OMNI_ERR_RETV_FW("Invalid OLE milliseconds specified", omni::exceptions::invalid_range(), 0)
    }
    return millis * omni::chrono::TICKS_PER_MILLISECOND;
}

omni::chrono::date_time omni::chrono::date_time::_from_binary_raw(int64_t date_data)
{
    int64_t ticks = (date_data & static_cast<int64_t>(OMNI_TICKS_MASK_FW));
    if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_RETV_FW("Invalid binary tick value", omni::exceptions::invalid_range(), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(date_data));
}

double omni::chrono::date_time::_ticks_to_oa_date(int64_t value)
{
    // DEV_NOTE: the notes are from the .NET source code
    if (value == 0) {
        return 0.0;  // Returns OleAut's zero'ed date value.
    }
    if (value < omni::chrono::TICKS_PER_DAY) { // This is a fix for VB. They want the default day to be 1/1/0001 rather then 12/30/1899.
        value += omni::chrono::DOUBLE_DATE_OFFSET; // We could have moved this fix down but we would like to keep the bounds check.
    }
    if (value < omni::chrono::OA_DATE_MIN_AS_TICKS) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range(), 0)
    }
    // Currently, our max date == OA's max date (12/31/9999), so we don't 
    // need an overflow check in that direction.
    int64_t ms = (value  - omni::chrono::DOUBLE_DATE_OFFSET) / omni::chrono::TICKS_PER_MILLISECOND;
    if (ms < 0) {
        int64_t frac = ms % omni::chrono::MILLISECONDS_PER_DAY;
        if (frac != 0) {
            ms -= (omni::chrono::MILLISECONDS_PER_DAY + frac) * 2;
        }
    }
    return static_cast<double>(ms) / omni::chrono::MILLISECONDS_PER_DAY;
}

bool omni::chrono::date_time::_try_create(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, omni::chrono::date_time& result)
{
    result = omni::chrono::date_time::min_value();
    if (year < 1 || year > 9999 || month < 1 || month > 12) {
        return false;
    }
    if (omni::chrono::date_time::is_leap_year(year)) {
        if (day < 1 || day > omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1]) {
            return false;
        }
    } else {
        if (day < 1 || day > omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1]) {
            return false;
        }
    }            
    if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60 || second < 0 || second >= 60) {
        return false;
    }                
    if (millisecond < 0 || millisecond >= omni::chrono::MILLISECONDS_PER_SECOND) {
        return false;
    }
    int64_t ticks = omni::chrono::date_time::_date_to_ticks(year, month, day) + omni::chrono::date_time::_time_to_ticks(hour, minute, second);
    
    ticks += millisecond * omni::chrono::TICKS_PER_MILLISECOND;
    if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
        return false;
    }
    result = omni::chrono::date_time(ticks, omni::chrono::date_time_kind::UNSPECIFIED);
    return true;
}
