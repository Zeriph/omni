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
    #error "invalid preprocessor directive detected"
#endif

#define OMNI_DATE_INTERNAL_MAX_DATE_TIME_NUMBER_DIGITS_FW 8
#define OMNI_DATE_INTERNAL_MAX_OFFSET_FW (OMNI_TICKS_PER_HOUR * 14)
#define OMNI_DATE_INTERNAL_MIN_OFFSET_FW -OMNI_DATE_INTERNAL_MAX_OFFSET_FW
#define OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW 199
#define OMNI_DATE_INTERNAL_SECOND_PRIME_FW 197
#define OMNI_DATE_INTERNAL_MAX_SECONDS_FRACTION_DIGITS_FW 7
#define OMNI_DATE_INTERNAL_GMT_NAME_FW "GMT"
#define OMNI_DATE_INTERNAL_ORDER_YMD_FW 0  // The order of date is Year/Month/Day.   
#define OMNI_DATE_INTERNAL_ORDER_MDY_FW 1  // The order of date is Month/Day/Year.
#define OMNI_DATE_INTERNAL_ORDER_DMY_FW 2  // The order of date is Day/Month/Year.
#define OMNI_DATE_INTERNAL_ORDER_YDM_FW 3  // The order of date is Year/Day/Month
#define OMNI_DATE_INTERNAL_ORDER_YM_FW 4   // Year/Month order.
#define OMNI_DATE_INTERNAL_ORDER_MY_FW 5   // Month/Year order.
#define OMNI_DATE_INTERNAL_ORDER_MD_FW 6   // Month/Day order.
#define OMNI_DATE_INTERNAL_ORDER_DM_FW 7   // Day/Month order.
#define OMNI_DATE_INTERNAL_DATE_SEP_OR_TZ_OFFSET_FW "-"
#define OMNI_DATE_INTERNAL_INV_DATE_SEP_FW "/"
#define OMNI_DATE_INTERNAL_INV_TIME_SEP_FW ":"
// Common Ignorable Symbols
#define OMNI_DATE_INTERNAL_IGNORABLE_PERIOD_FW "."
#define OMNI_DATE_INTERNAL_IGNORABLE_COMMA_FW ","
#define OMNI_DATE_INTERNAL_LOCAL_TIME_MARK_FW "T"

// TODO: this whole file is a jumbled mess .. the C# code was basically this way too :/ .. need to clean this whole file up

// TODO: The calendar/locale impl's are not going to be added to this version of Omni.
// for now we only support Gregorian calendars and no unicode stuff (e.g. Japanese symbols/etc.)

// TODO: need a "zone info" DB/locale info/calendar/A.D./ C.E./ J.T. .. other calendar "eras"

// DEV_NOTE: if/when it comes time to implement the above (calendar/locale/etc.), `svn up -r 23` has the "old" notes and code/logic for all of that
// to that, a lot of the names in here have been largely kept the same if only turned into snake_case, for posterity.

// DEV_NOTE: there are quite a few duplicated `_insert_hash` .. presumably this is due to the calendars (that are not in omni) and how the hash "map"
// is laid out. It could likely be a single list, but we're keeping it "as-is" because it works .. not to mention this is a massive parsing file
// and parsing is very O(n*n) type of complexity, so it's cool for now (oh C# .. :|)

namespace omni { namespace internal {
    namespace date_time_format {

        // -- start enums --

        // DEV_NOTE: we're keeping the enums in namespaces instead of using classes for 2 reasons:
        // 1 - avoids collision, 2 - using the Omni enum template consumes memory and is pointless
        // for these internal enum types. Maybe might switch to C++11 class enum's but likely not

        // DEV_NOTE: some enum value names (e.g. parse_state::D_Nd) will remain CamelCase for easier differentiation
        namespace parse_state {
            typedef enum enum_t {
                BEGIN   = 0,
                N       = 1,    // have one number
                NN      = 2,    // have two numbers

                // The following are known to be part of a date
                D_Nd    = 3,    // date string: have number followed by date separator
                D_NN    = 4,    // date string: have two numbers
                D_NNd   = 5,    // date string: have two numbers followed by date separator

                D_M     = 6,    // date string: have a month
                D_MN    = 7,    // date string: have a month and a number
                D_NM    = 8,    // date string: have a number and a month
                D_MNd   = 9,    // date string: have a month and number followed by date separator
                D_NDS   = 10,   // date string: have one number followed a date suffix.

                D_Y     = 11,   // date string: have a year.
                D_YN    = 12,   // date string: have a year and a number
                D_YNd   = 13,   // date string: have a year and a number and a date separator
                D_YM    = 14,   // date string: have a year and a month
                D_YMd   = 15,   // date string: have a year and a month and a date separator
                D_S     = 16,   // have numbers followed by a date suffix.
                T_S     = 17,   // have numbers followed by a time suffix.

                // The following are known to be part of a time
                T_Nt    = 18,   // have num followed by time separator
                T_NNt   = 19,   // have two numbers followed by time separator

                ERR   = 20, // this WAS `ERROR` but Windoes doesn't like names like that :|

                // The following are terminal states. These all have an action
                // associated with them; and transition back to BEGIN.
                DX_NN   = 21,   // day from two numbers
                DX_NNN  = 22,   // day from three numbers
                DX_MN   = 23,   // day from month and one number
                DX_NM   = 24,   // day from month and one number
                DX_MNN  = 25,   // day from month and two numbers
                DX_DS   = 26,   // a set of date suffixed numbers.
                DX_DSN  = 27,   // day from date suffixes and one number.
                DX_NDS  = 28,   // day from one number and date suffixes.
                DX_NNDS = 29,   // day from one number and date suffixes.

                DX_YNN  = 30,   // date string: have a year and two number
                DX_YMN  = 31,   // date string: have a year, a month, and a number.
                DX_YN   = 32,   // date string: have a year and one number
                DX_YM   = 33,   // date string: have a year, a month.
                TX_N    = 34,   // time from one number (must have ampm)
                TX_NN   = 35,   // time from two numbers
                TX_NNN  = 36,   // time from three numbers
                TX_TS   = 37,   // a set of time suffixed numbers.
                DX_NNY  = 38
            } enum_t;
        }

        namespace parse_flags {
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
        }
        
        namespace token_type {
            typedef enum enum_t {
                // The valid token should start from 1.
                // Regular tokens. The range is from 0x00 ~ 0xff.
                NUMBER_TOKEN        = 1,        // The number.  E.g. "12"
                YEAR_NUMBER_TOKEN   = 2,        // The number which is considered as year number, which has 3 or more digits.  E.g. "2003"
                AM                  = 3,        // AM time mark. E.g. "AM"
                PM                  = 4,        // PM time mark. E.g. "PM"
                MONTH_TOKEN         = 5,        // A word (or words) that represents a month name.  E.g. "Microsoft"
                END_OF_STRING       = 6,        // End of string
                DAY_OF_WEEK_TOKEN   = 7,        // A word (or words) that represents a day of week name.  E.g. "Monday" or "Mon"
                TIME_ZONE_TOKEN     = 8,        // A word that represents a timezone name. E.g. "GMT"
                ERA_TOKEN           = 9,        // A word that represents a era name. E.g. "A.D."
                DATE_WORD_TOKEN     = 10,       // A word that can appear in a DateTime string, but serves no parsing semantics.  E.g. "de" in Spanish culture.
                UNKNOWN_TOKEN       = 11,       // An unknown word, which signals an error in parsing.
                HEBREW_NUMBER       = 12,       // A number that is composed of Hebrew text.  Hebrew calendar uses Hebrew digits for year values, month values, and day values.
                JAPANESE_ERA_TOKEN  = 13,       // Era name for JapaneseCalendar
                TAIWAN_ERA_TOKEN    = 14,       // Era name for TaiwanCalendar
                IGNORABLE_SYMBOL    = 15,       // A separator like "," that is equivalent to whitespace
                // Separator tokens.
                SEP_UNK             = 0x100,     // Unknown separator.
                SEP_END             = 0x200,     // The end of the parsing string.
                SEP_SPACE           = 0x300,     // Whitespace (including comma).
                SEP_AM              = 0x400,     // AM time mark. E.g. "AM"
                SEP_PM              = 0x500,     // PM time mark. E.g. "PM"
                SEP_Date            = 0x600,     // date separator. E.g. "/"
                SEP_TIME            = 0x700,     // time separator. E.g. ":"
                SEP_YEAR_SUFFIX     = 0x800,     // Chinese/Japanese/Korean year suffix.
                SEP_MONTH_SUFFIX    = 0x900,     // Chinese/Japanese/Korean month suffix.
                SEP_DAY_SUFFIX      = 0xa00,     // Chinese/Japanese/Korean day suffix.
                SEP_HOUR_SUFFIX     = 0xb00,     // Chinese/Japanese/Korean hour suffix.
                SEP_MINUTE_SUFFIX   = 0xc00,     // Chinese/Japanese/Korean minute suffix.
                SEP_SECOND_SUFFIX   = 0xd00,     // Chinese/Japanese/Korean second suffix.
                SEP_LOCAL_TIME_MARK = 0xe00,  // 'T', used in ISO 8601 format.
                SEP_DATE_OR_OFFSET  = 0xf00,   // '-' which could be a date separator or start of a time zone offset

                REGULAR_TOKEN_MASK  = 0x00ff,
                SEPARATOR_TOKEN_MASK= 0xff00
            } enum_t;
        }

        namespace token {
            typedef enum enum_t {
                END                 = 0,    // '\0'
                NUM_END             = 1,    // Num[ ]*[\0]
                NUM_AM_PM           = 2,    // Num[ ]+AmPm
                NUM_SPACE           = 3,    // Num[ ]+^[Dsep|Tsep|'0\']
                NUM_DATE_SEP        = 4,    // Num[ ]*Dsep
                NUM_TIME_SEP        = 5,    // Num[ ]*Tsep
                MONTH_END           = 6,    // Month[ ]*'\0'
                MONTH_SPACE         = 7,    // Month[ ]+^[Dsep|Tsep|'\0']
                MONTH_DATE_SEP      = 8,    // Month[ ]*Dsep
                NUM_DATE_SUFFIX     = 9,    // Month[ ]*DSuff
                NUM_TIME_SUFFIX     = 10,   // Month[ ]*TSuff
                DAY_OF_WEEK         = 11,   // Day of week name
                YEAR_SPACE          = 12,   // Year+^[Dsep|Tsep|'0\']
                YEAR_DATE_SEP       = 13,   // Year+Dsep
                YEAR_END            = 14,   // Year+['\0']
                TIME_ZONE           = 15,   // timezone name
                ERA                 = 16,   // era name
                NUM_UTC_TIME_MARK   = 17,   // Num + 'Z'
                // When you add a new token which will be in the
                // state table, add it after NUM_LOCAL_TIME_MARK.
                UNKNOWN             = 18,   // unknown
                NUM_LOCAL_TIME_MARK = 19,   // Num + 'T'
                MAX                 = 20    // marker
            } enum_t;
        }

        namespace time_mark {
            typedef enum enum_t {
                NOT_SET = -1,
                AM      = 0,
                PM      = 1
            } enum_t;
        }

        namespace format_flags {
            typedef enum enum_t {
                NONE                        = 0x00000000,
                USE_GENITIVE_MONTH          = 0x00000001,
                USE_LEAP_YEAR_MONTH         = 0x00000002,
                USE_SPACE_IN_MONTH_NAMES    = 0x00000004, // Has spaces or non-breaking space in the month names.
                USE_HEBREW_RULE             = 0x00000008, // Format/Parse using the Hebrew calendar rule.
                USE_SPACE_IN_DAY_NAMES      = 0x00000010, // Has spaces or non-breaking space in the day names.
                USE_DIGIT_PREFIX_IN_TOKENS  = 0x00000020, // Has token starting with numbers.
                NOT_INITIALIZED             = -1
            } enum_t;
        }

        namespace found_date_pattern {
            typedef enum enum_t {
                NONE                = 0x0000,
                FOUND_YEAR_PATTERN  = 0x0001,
                FOUND_MONTH_PATTERN = 0x0002,
                FOUND_DAY_PATTERN   = 0x0004,
                FOUND_YMD_PATTERN   = 0x0007 // FOUND_YEAR_PATTERN | FOUND_MONTH_PATTERN | FOUND_DAY_PATTERN;
            } enum_t;
        }

        namespace dt_substring_type {
            typedef enum enum_t {
                UNKNOWN = 0,
                INVALID = 1,
                NUMBER = 2,
                END = 3,
                OTHER = 4
            } enum_t;
        }

        // -- end enums --

        namespace compare_info {
            inline int32_t compare(const std::string& string1, std::size_t offset1, std::size_t length1, const std::string& string2, std::size_t offset2, std::size_t length2)
            {
                return omni::string::util::compare(string1, offset1, length1, string2, offset2, length2, omni::string::compare_options::IGNORE_CASE);
            }

            inline int32_t compare_ordinal(const std::string& string1, std::size_t offset1, std::size_t length1, const std::string& string2, std::size_t offset2, std::size_t length2)
            {
                int32_t result  = omni::string::util::compare(string1, offset1, string2, offset2, (length1 < length2 ? length1 : length2), omni::string::compare_options::IGNORE_CASE);
                if ((length1 != length2) && result == 0) {
                    return (length1 > length2 ? 1 : -1);
                }
                return result;
            }
        }

        class parse_result
        {
            public:
                int16_t year;
                int16_t month;
                int16_t day;
                int16_t hour; // Set time default to 00:00:00.
                int16_t minute;
                int16_t second;
                double fraction;
                int16_t era;

                date_time_format::parse_flags::enum_t flags;
                omni::chrono::time_span time_zone_offset;
                omni::chrono::date_time parsed_date;
                omni::chrono::date_time_parse_failure failure;
                std::string failure_message;

                parse_result() :
                    year(-1), month(-1), day(-1),
                    hour(0), minute(0), second(0),
                    fraction(-1), era(-1),
                    flags(),
                    time_zone_offset(),
                    parsed_date(0),
                    failure(),
                    failure_message()
                {
                }

                parse_result(const parse_result& cp) :
                    year(cp.year),
                    month(cp.month),
                    day(cp.day),
                    hour(cp.hour),
                    minute(cp.minute),
                    second(cp.second),
                    fraction(cp.fraction),
                    era(cp.era),
                    flags(cp.flags),
                    time_zone_offset(cp.time_zone_offset),
                    parsed_date(cp.parsed_date),
                    failure(cp.failure),
                    failure_message(cp.failure_message)
                {
                }

                ~parse_result() {}

                parse_result& operator=(const parse_result& cp)
                {
                    this->year = cp.year;
                    this->month = cp.month;
                    this->day = cp.day;
                    this->hour = cp.hour;
                    this->minute = cp.minute;
                    this->second = cp.second;
                    this->fraction = cp.fraction;
                    this->era = cp.era;
                    this->flags = cp.flags;
                    this->time_zone_offset = cp.time_zone_offset;
                    this->parsed_date = cp.parsed_date;
                    this->failure = cp.failure;
                    this->failure_message = cp.failure_message;
                    return *this;
                }

                void set_date(int16_t new_year, int16_t new_month, int16_t new_day)
                {
                    this->year = new_year;
                    this->month = new_month;
                    this->day = new_day;
                }
                
                void set_failure(const omni::chrono::date_time_parse_failure& new_failure, const std::string& new_failure_message)
                {
                    this->failure = new_failure;
                    this->failure_message = new_failure_message;
                }
        };

        class token_hash_value
        {
            public:
                std::string token_string;
                token_type::enum_t token_type;
                int64_t token_value;
                bool empty;

                token_hash_value() :
                    token_string(),
                    token_type(token_type::UNKNOWN_TOKEN),
                    token_value(0),
                    empty(true)
                {}

                token_hash_value(const token_hash_value& cp) :
                    token_string(cp.token_string),
                    token_type(cp.token_type),
                    token_value(cp.token_value),
                    empty(cp.empty)
                {}

                token_hash_value(const std::string& _tokenString, token_type::enum_t _tokenType, int64_t _tokenValue) :
                    token_string(_tokenString),
                    token_type(_tokenType),
                    token_value(_tokenValue),
                    empty(false)
                {
                }
                
                token_hash_value& operator=(const token_hash_value& cp)
                {
                    this->token_string = cp.token_string;
                    this->token_type = cp.token_type;
                    this->token_value = cp.token_value;
                    this->empty = cp.empty;
                    return *this;
                }
        };

        class __dt_string; // forward declaration for format_info class

        class format_info
        {
            public:
                std::string am_designator;
                std::string pm_designator;
                std::string short_date_pattern;
                std::string long_date_pattern;
                std::string full_date_time_pattern;
                std::string general_short_time_pattern;
                std::string general_long_time_pattern;
                std::string month_day_pattern;
                std::string rfc_1123_pattern;
                std::string sortable_date_time_pattern;
                std::string short_time_pattern;
                std::string long_time_pattern;
                std::string universal_sortable_date_time_pattern;
                std::string year_month_pattern;
                std::string time_separator;
                std::string date_separator;
                omni::internal::date_time_format::format_flags::enum_t fmt_flags;
                volatile bool has_year_month_adjustment;
                volatile bool has_force_two_digit_years;

                format_info() :
                    am_designator(OMNI_DATE_FORMAT_INFO_AM_FW),
                    pm_designator(OMNI_DATE_FORMAT_INFO_PM_FW),
                    short_date_pattern("MM/dd/yyyy"),
                    long_date_pattern("dddd, dd MMMM yyyy"),
                    full_date_time_pattern("dddd, dd MMMM yyyy HH:mm:ss"),
                    general_short_time_pattern("MM/dd/yyyy HH:mm"),
                    general_long_time_pattern("MM/dd/yyyy HH:mm:ss"),
                    month_day_pattern("MMMM dd"),
                    rfc_1123_pattern("ddd, dd MMM yyyy HH':'mm':'ss 'GMT'"),
                    sortable_date_time_pattern("yyyy'-'MM'-'dd'T'HH':'mm':'ss"),
                    short_time_pattern("HH:mm"),
                    long_time_pattern("HH:mm:ss"),
                    universal_sortable_date_time_pattern("yyyy'-'MM'-'dd HH':'mm':'ss'Z'"),
                    year_month_pattern("yyyy MMMM"),
                    time_separator(":"),
                    date_separator("/"),
                    fmt_flags(format_flags::NONE),
                    has_year_month_adjustment(false),
                    has_force_two_digit_years(false),
                    m_dtfs(),
                    m_dtfi_token_hash()
                {
                }
                
                format_info(const format_info& cp) :
                    am_designator(cp.am_designator),
                    pm_designator(cp.pm_designator),
                    short_date_pattern(cp.short_date_pattern),
                    long_date_pattern(cp.long_date_pattern),
                    full_date_time_pattern(cp.full_date_time_pattern),
                    general_short_time_pattern(cp.general_short_time_pattern),
                    general_long_time_pattern(cp.general_long_time_pattern),
                    month_day_pattern(cp.month_day_pattern),
                    rfc_1123_pattern(cp.rfc_1123_pattern),
                    sortable_date_time_pattern(cp.sortable_date_time_pattern),
                    short_time_pattern(cp.short_time_pattern),
                    long_time_pattern(cp.long_time_pattern),
                    universal_sortable_date_time_pattern(cp.universal_sortable_date_time_pattern),
                    year_month_pattern(cp.year_month_pattern),
                    time_separator(cp.time_separator),
                    date_separator(cp.date_separator),
                    fmt_flags(cp.fmt_flags),
                    has_year_month_adjustment(cp.has_year_month_adjustment),
                    has_force_two_digit_years(cp.has_force_two_digit_years),
                    m_dtfs(cp.m_dtfs),
                    m_dtfi_token_hash(cp.m_dtfi_token_hash)
                {}

                ~format_info() {}

                format_info& operator=(const format_info& cp)
                {
                    this->am_designator = cp.am_designator;
                    this->pm_designator = cp.pm_designator;
                    this->short_date_pattern = cp.short_date_pattern;
                    this->long_date_pattern = cp.long_date_pattern;
                    this->full_date_time_pattern = cp.full_date_time_pattern;
                    this->general_short_time_pattern = cp.general_short_time_pattern;
                    this->general_long_time_pattern = cp.general_long_time_pattern;
                    this->month_day_pattern = cp.month_day_pattern;
                    this->rfc_1123_pattern = cp.rfc_1123_pattern;
                    this->sortable_date_time_pattern = cp.sortable_date_time_pattern;
                    this->short_time_pattern = cp.short_time_pattern;
                    this->long_time_pattern = cp.long_time_pattern;
                    this->universal_sortable_date_time_pattern = cp.universal_sortable_date_time_pattern;
                    this->year_month_pattern = cp.year_month_pattern;
                    this->time_separator = cp.time_separator;
                    this->date_separator = cp.date_separator;
                    this->fmt_flags = cp.fmt_flags;
                    this->has_year_month_adjustment = cp.has_year_month_adjustment;
                    this->has_force_two_digit_years = cp.has_force_two_digit_years;
                    this->m_dtfs = cp.m_dtfs;
                    this->m_dtfi_token_hash = cp.m_dtfi_token_hash;
                    return *this;
                }

                std::vector<std::string> get_all_date_time_patterns(char format)
                {
                    std::vector<std::string> result;
                    switch (format)
                    {
                        case 'd':
                            result.push_back("MM/dd/yyyy");
                            result.push_back("yyyy-MM-dd");
                            break;
                        case 'D':
                            result.push_back("dddd, dd MMMM yyyy");
                            break;
                        case 't':
                            result.push_back("HH:mm");
                            result.push_back("hh:mm tt");
                            result.push_back("H:mm");
                            result.push_back("h:mm tt");
                            break;
                        case 'T':
                            result.push_back("HH:mm:ss");
                            break;
                        case 'y': case 'Y':
                            result.push_back("yyyy MMMM");
                            break;
                        /*
                            DEV_NOTE: in the C# impl, it accounts for a few more format options, however ..
                            they don't seem to be actually used in the code?? Could be a calendar thing ??
                            The following are the cases we don't account for because they're literally not
                            called elsewhere in code:
                            
                            case 'f': result = GetCombinedPatterns(AllLongDatePatterns, AllShortTimePatterns, " "); break;
                            case 'F':
                            case 'U': result = GetCombinedPatterns(AllLongDatePatterns, AllLongTimePatterns, " "); break;
                            case 'g': result = GetCombinedPatterns(AllShortDatePatterns, AllShortTimePatterns, " "); break;
                            case 'G': result = GetCombinedPatterns(AllShortDatePatterns, AllLongTimePatterns, " "); break;
                            case 'm':
                            case 'M': result = new String[] {month_day_pattern}; break;
                            case 'o':
                            case 'O': result = new String[] {DateTimeFormat.RoundtripFormat}; break;
                            case 'r':
                            case 'R': result = new String[] {rfc1123Pattern}; break;
                            case 's': result = new String[] {sortableDateTimePattern}; break;
                            case 'u': result = new String[] {universal_sortable_date_time_pattern}; break;
                        */
                        default:
                            // This will NEVER get called since this is in our own code .. if someone outside of our code is calling this function, more power to them ;)
                            break;
                    }
                    return result;
                }

                bool has_spaces_in_month_names()
                {
                    return (this->fmt_flags & format_flags::USE_SPACE_IN_MONTH_NAMES) != 0;
                }

                bool has_spaces_in_day_names()
                {
                    return (this->fmt_flags & format_flags::USE_SPACE_IN_DAY_NAMES) != 0;
                }

                bool tokenize
                (
                    const omni::internal::date_time_format::token_type::enum_t& token_mask,
                    omni::internal::date_time_format::token_type::enum_t& token_type,
                    int64_t& token_value,
                    __dt_string& str
                );

                std::vector<std::string> internal_get_leap_year_names()
                {
                    std::vector<std::string> vals;
                    vals.push_back("January");
                    vals.push_back("February");
                    vals.push_back("March");
                    vals.push_back("April");
                    vals.push_back("May");
                    vals.push_back("June");
                    vals.push_back("July");
                    vals.push_back("August");
                    vals.push_back("September");
                    vals.push_back("October");
                    vals.push_back("November");
                    vals.push_back("December");
                    vals.push_back("");
                    return vals;
                }

                void reset()
                {
                    this->am_designator = OMNI_DATE_FORMAT_INFO_AM_FW;
                    this->pm_designator = OMNI_DATE_FORMAT_INFO_PM_FW;
                    this->short_date_pattern = "MM/dd/yyyy";
                    this->long_date_pattern = "dddd, dd MMMM yyyy";
                    this->short_time_pattern = "HH:mm";
                    this->long_time_pattern = "HH:mm:ss";
                    this->general_short_time_pattern = this->short_date_pattern + " " + this->short_time_pattern;
                    this->general_long_time_pattern = this->short_date_pattern + " " + this->long_time_pattern;
                    this->full_date_time_pattern = this->long_date_pattern + " " + this->long_time_pattern;
                    this->rfc_1123_pattern = "ddd, dd MMM yyyy HH':'mm':'ss 'GMT'";
                    this->sortable_date_time_pattern = "yyyy'-'MM'-'dd'T'HH':'mm':'ss";
                    this->universal_sortable_date_time_pattern = "yyyy'-'MM'-'dd HH':'mm':'ss'Z'";

                    this->month_day_pattern = "MMMM dd";
                    this->year_month_pattern = "yyyy MMMM";
                    this->time_separator = ":";
                    this->date_separator = "/";
                    this->has_year_month_adjustment = false;
                    this->has_force_two_digit_years = false;
                    this->fmt_flags = omni::internal::date_time_format::format_flags::NONE;

                    this->m_dtfi_token_hash.clear();
                }

            private:

                class date_time_format_scanner {
                    public:
                        date_time_format_scanner() : m_scanner_date_words() {}
                        date_time_format_scanner(const date_time_format_scanner& cp) : m_scanner_date_words(cp.m_scanner_date_words) {}
                        ~date_time_format_scanner() {}
                        date_time_format_scanner& operator=(const date_time_format_scanner& cp)
                        {
                            this->m_scanner_date_words = cp.m_scanner_date_words;
                            return *this;
                        }

                        std::vector<std::string> m_scanner_date_words;

                        std::size_t skip_white_space_and_non_letters(const std::string& pattern, std::size_t idx)
                        {
                            while (idx < pattern.size())
                            {
                                char ch = pattern[idx];
                                if (ch == '\\')
                                {
                                    // Escaped character. Look ahead one character.
                                    idx++;
                                    if (idx < pattern.size())
                                    {
                                        ch = pattern[idx];
                                        if (ch == '\'')
                                        {
                                            // Skip the leading single quote.  We will
                                            // stop at the first letter.
                                            continue;
                                        }
                                        // Fall thru to check if this is a letter.
                                    } else
                                    {
                                        // End of string
                                        break;
                                    }
                                }
                                if (omni::char_util::is_letter(ch) || ch == '\'' || ch == '.')
                                {                
                                    break;
                                }
                                // Skip the current char since it is not a letter.
                                ++idx;
                            }
                            return idx;
                        }

                        void add_ignorable_symbols(const std::string& text)
                        {
                            // Add the ignorable symbol into the ArrayList.

                            // DEV_NOTE: this is what was in the C#: std::string temp = '\xe001' + text; // IgnorableSymbolChar + text;
                            // but that's a unicode (or wchar_t) and we're not handling that right now.
                            if (std::find(this->m_scanner_date_words.begin(), this->m_scanner_date_words.end(), text) == this->m_scanner_date_words.end()) {
                                this->m_scanner_date_words.push_back(text);
                            }
                        }

                        bool known_words_try_get_value(const std::string& key)
                        {
                            return (key == "/" || key == "-" || key == ".");
                        }

                        void add_date_words_or_postfix(const std::string& format_postfix, const std::string& str)
                        {
                            if (!str.empty()) {
                                // Some cultures use . like an abbreviation
                                if (str == ".") {
                                    this->add_ignorable_symbols(".");
                                    return;
                                }
                                if (!this->known_words_try_get_value(str)) {
                                    if (format_postfix == "MMMM") {
                                        // Add the word into the ArrayList as "\xfffe" + real month postfix.

                                        // DEV_NOTE: this is what was in the C#: std::string temp = '\xe000' + str; // MonthPostfixChar + str;
                                        // but that's a unicode (or wchar_t) and we're not handling that right now.
                                        if (std::find(this->m_scanner_date_words.begin(), this->m_scanner_date_words.end(), str) == this->m_scanner_date_words.end()) {
                                            this->m_scanner_date_words.push_back(str);
                                        }
                                    } else {
                                        if (std::find(this->m_scanner_date_words.begin(), this->m_scanner_date_words.end(), str) == this->m_scanner_date_words.end()) {
                                            this->m_scanner_date_words.push_back(str);
                                        }
                                        if (str[str.size() - 1] == '.') {
                                            // Old version ignore the trialing dot in the date words. Support this as well.
                                            std::string without_dot = str.substr(0, str.size() - 1);
                                            if (std::find(this->m_scanner_date_words.begin(), this->m_scanner_date_words.end(), without_dot) == this->m_scanner_date_words.end()) {
                                                this->m_scanner_date_words.push_back(without_dot);                                
                                            }
                                        }
                                    }
                                }
                            }
                            
                        }

                        std::size_t add_date_words(const std::string& pattern, std::size_t index, std::string format_postfix)
                        {
                            // Skip any whitespaces so we will start from a letter.
                            std::size_t new_index = this->skip_white_space_and_non_letters(pattern, index);
                            if (new_index != index && !format_postfix.empty()) {
                                // There are whitespaces. This will not be a postfix.
                                format_postfix.clear();
                            }
                            index = new_index;

                            // This is the first char added into date_word.  
                            // Skip all non-letter character.  We will add the first letter into DateWord.
                            std::string date_word;
                            // We assume that date words should start with a letter. 
                            // Skip anything until we see a letter.
                            
                            while (index < pattern.size()) {
                                char ch = pattern[index];
                                if (ch == '\'') {
                                    // We have seen the end of quote.  Add the word if we do not see it before, 
                                    // and break the while loop.                    
                                    this->add_date_words_or_postfix(format_postfix, date_word);
                                    ++index;
                                    break;
                                } else if (ch == '\\') {
                                    // Escaped character.  Look ahead one character
                                    // Skip escaped backslash.
                                    ++index;
                                    if (index < pattern.size()) {
                                        date_word += pattern[index];
                                        ++index;
                                    }
                                } else if (omni::char_util::is_white_space(ch)) {
                                    // Found a whitespace.  We have to add the current date word/postfix.
                                    this->add_date_words_or_postfix(format_postfix, date_word);
                                    if (!format_postfix.empty()) {
                                        // Done with postfix.  The rest will be regular date word.
                                        format_postfix.clear();
                                    }
                                    // Reset the date_word.
                                    date_word.clear();
                                    ++index;
                                } else {
                                    date_word += ch;                                        
                                    ++index;
                                }
                            }  
                            return index;
                        }

                        std::size_t scan_repeat_char(const std::string& pattern, char ch, std::size_t index, std::size_t& count)
                        {
                            count = 1;
                            while (++index < pattern.size() && pattern[index] == ch) {
                                ++count;
                            }
                            // Return the updated position.
                            return index;
                        }

                        void scan_date_word(const std::string& pattern)
                        {
                            // Check if we have found all of the year/month/day pattern.
                            uint64_t ymd_flags = omni::internal::date_time_format::found_date_pattern::NONE;

                            std::size_t i = 0;
                            while (i < pattern.size()) {
                                char ch = pattern[i];  
                                std::size_t char_count = 0;
                                
                                switch (ch) {
                                    case '\'':
                                        // Find a beginning quote.  Search until the end quote.
                                        i = this->add_date_words(pattern, i+1, "");
                                        break;
                                    case 'M':
                                        i = this->scan_repeat_char(pattern, 'M', i, char_count);
                                        if (char_count >= 4) {
                                            if (i < pattern.size() && pattern[i] == '\'') {
                                                i = this->add_date_words(pattern, i+1, "MMMM");
                                            }
                                        }
                                        ymd_flags |= omni::internal::date_time_format::found_date_pattern::FOUND_MONTH_PATTERN;
                                        break;
                                    case 'y':
                                        i = this->scan_repeat_char(pattern, 'y', i, char_count);
                                        ymd_flags |= omni::internal::date_time_format::found_date_pattern::FOUND_YEAR_PATTERN;
                                        break;
                                    case 'd':
                                        i = this->scan_repeat_char(pattern, 'd', i, char_count);
                                        if (char_count <= 2) {
                                            // Only count "d" & "dd".
                                            // ddd, dddd are day names.  Do not count them.
                                            ymd_flags |= omni::internal::date_time_format::found_date_pattern::FOUND_DAY_PATTERN;
                                        }
                                        break;
                                    case '\\':
                                        // Found a escaped char not in a quoted string.  Skip the current backslash
                                        // and its next character.
                                        i += 2;
                                        break;
                                    case '.':
                                        if (ymd_flags == omni::internal::date_time_format::found_date_pattern::FOUND_YMD_PATTERN) {
                                            // If we find a dot immediately after the we have seen all of the y, m, d pattern.
                                            // treat it as a ignorable symbol.  Check for comments in add_ignorable_symbols for
                                            // more details.
                                            this->add_ignorable_symbols(".");
                                            ymd_flags = omni::internal::date_time_format::found_date_pattern::NONE;
                                        }
                                        ++i;
                                        break;
                                    default:
                                        if (ymd_flags == omni::internal::date_time_format::found_date_pattern::FOUND_YMD_PATTERN && !omni::char_util::is_white_space(ch)) {
                                            // We are not seeing "." after YMD. Clear the flag.
                                            ymd_flags = omni::internal::date_time_format::found_date_pattern::NONE;
                                        }
                                        // We are not in quote.  Skip the current character.
                                        ++i;
                                        break;
                                }
                            }
                        }

                        std::vector<std::string> get_date_words_of_dtfi(omni::internal::date_time_format::format_info& dtfi)
                        {
                            // Enumerate all LongDatePatterns, and get the DateWords and scan for month postfix.
                            std::vector<std::string> date_patterns = dtfi.get_all_date_time_patterns('D');
                            std::size_t i = 0;
                            
                            // Scan the long date patterns
                            for (i = 0; i < date_patterns.size(); ++i) {
                                this->scan_date_word(date_patterns[i]);
                            }

                            // Scan the short date patterns
                            date_patterns = dtfi.get_all_date_time_patterns('d');
                            for (i = 0; i < date_patterns.size(); ++i) {
                                this->scan_date_word(date_patterns[i]);
                            }
                            // Scan the YearMonth patterns.
                            date_patterns = dtfi.get_all_date_time_patterns('y');
                            for (i = 0; i < date_patterns.size(); ++i) {
                                this->scan_date_word(date_patterns[i]);
                            }

                            // Scan the month/day pattern
                            this->scan_date_word(dtfi.month_day_pattern);
                            
                            // Scan the long time patterns.
                            date_patterns = dtfi.get_all_date_time_patterns('T');
                            for (i = 0; i < date_patterns.size(); ++i) {
                                this->scan_date_word(date_patterns[i]);
                            }

                            // Scan the short time patterns.
                            date_patterns = dtfi.get_all_date_time_patterns('t');
                            for (i = 0; i < date_patterns.size(); ++i) {
                                this->scan_date_word(date_patterns[i]);
                            }

                            std::vector<std::string> result;
                            if (!this->m_scanner_date_words.empty()) {
                                result = this->m_scanner_date_words;
                            }

                            return result;
                        }
                };

                date_time_format_scanner m_dtfs;
                std::vector<omni::internal::date_time_format::token_hash_value> m_dtfi_token_hash;

                void _insert_at_current_hash_node(std::vector<omni::internal::date_time_format::token_hash_value>& hash_table, const std::string& str, char ch, omni::internal::date_time_format::token_type::enum_t token_type, int64_t token_value, std::size_t pos, int64_t hash_code, int64_t hash_probe)
                {
                    // Remember the current slot.
                    omni::internal::date_time_format::token_hash_value prev = hash_table[static_cast<std::size_t>(hash_code)];
                    // Insert the new node into the current slot.
                    hash_table[static_cast<std::size_t>(hash_code)] = omni::internal::date_time_format::token_hash_value(str, token_type, token_value);

                    while (++pos < OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW) {
                        hash_code += hash_probe;
                        if (hash_code >= OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW) {
                            hash_code -= OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW;
                        }

                        // Remember this slot
                        omni::internal::date_time_format::token_hash_value temp = hash_table[static_cast<std::size_t>(hash_code)];
                        if (omni::char_util::to_lower(temp.token_string[0]) != ch) {
                            continue;
                        }

                        // Put the previous slot into this slot.
                        hash_table[static_cast<std::size_t>(hash_code)] = prev;
                        if (temp.token_string.empty()) {
                            // Done
                            return;
                        }
                        prev = temp;
                    }
                }

                // DEV_NOTE: have `str` be a copied object because it gets edited in this function
                void _insert_hash(std::vector<omni::internal::date_time_format::token_hash_value>& hash_table, std::string str, omni::internal::date_time_format::token_type::enum_t token_type, int64_t token_value)
                {
                    // The month of the 13th month is allowed to be empty, so make sure that we ignore empty value here.
                    if (str.empty()) {
                        return;
                    }
                    omni::internal::date_time_format::token_hash_value value;
                    std::size_t i = 0;
                    // If there is whitespace characters in the beginning and end of the string, trim them since whitespaces are skipped by
                    // DateTime.Parse().
                    if (omni::char_util::is_white_space(str[0]) || omni::char_util::is_white_space(str[str.size() - 1])) {
                        str = omni::string::util::trim(str);   // Trim white space characters.
                        // Could have space for separators
                        if (str.size() == 0)
                            return;
                        }
                    char ch = omni::char_util::to_lower(str[0]); // Char.ToLower(str[0], this->Culture);
                    int64_t hash_code = ch % OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW;
                    int64_t hash_probe = 1 + ch % OMNI_DATE_INTERNAL_SECOND_PRIME_FW;
                    do {
                        value = hash_table[static_cast<std::size_t>(hash_code)];
                        if (value.token_string.empty()) {
                            hash_table[static_cast<std::size_t>(hash_code)] = omni::internal::date_time_format::token_hash_value(str, token_type, token_value);
                            return;
                        } else {
                            // Collision happens. Find another slot.
                            if (str.size() >= value.token_string.size()) {
                                // If there are two tokens with the same prefix, we have to make sure that the longer token should be at the front of
                                // the shorter ones.
                                if (omni::string::util::compare(str, 0, value.token_string, 0, value.token_string.size(), omni::string::compare_options::IGNORE_CASE) == 0) {
                                    if (str.size() > value.token_string.size()) {
                                        // The str to be inserted has the same prefix as the current token, and str is longer.
                                        // Insert str into this node, and shift every node behind it.
                                        _insert_at_current_hash_node(hash_table, str, ch, token_type, token_value, i, hash_code, hash_probe);
                                        return;
                                    } else {
                                        // Same token.  If they have different types (regular token vs separator token).  Add them.
                                        // If we have the same regular token or separator token in the hash already, do NOT update the hash.
                                        // Therefore, the order of inserting token is significant here regarding what token_type will be kept in the hash.

                                        // Check the current value of RegularToken (stored in the lower 8-bit of token_type) , and insert the token_type into the hash ONLY when we don't have a RegularToken yet.
                                        // Also check the current value of SeparatorToken (stored in the upper 8-bit of token), and insert the token_type into the hash ONLY when we don't have the SeparatorToken yet.
                                        omni::internal::date_time_format::token_type::enum_t tok = token_type;
                                        omni::internal::date_time_format::token_type::enum_t curr_hash_tok = value.token_type;
                                        if (
                                            (((curr_hash_tok & omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK) == 0) && ((tok & omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK) != 0)) ||
                                            (((curr_hash_tok & omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK) == 0) && ((tok & omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK) != 0))
                                        ) {
                                            value.token_type = static_cast<omni::internal::date_time_format::token_type::enum_t>(value.token_type | token_type);
                                            if (token_value != 0) {
                                                value.token_value = token_value;
                                            }
                                        }
                                        // The token to be inserted is already in the table.  Skip it.
                                    }
                                }
                            }
                        }
                        ++i;
                        hash_code += hash_probe;
                        if (hash_code >= OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW) {
                            hash_code -= OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW;
                        }
                    } while (i < OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW);
                }

                void _add_month_names(std::vector<omni::internal::date_time_format::token_hash_value>& temp, const std::string& month_postfix)
                {
                    for (std::size_t i = 1; i < omni::chrono::month::COUNT(); ++i) {
                        // We have to call public methods here to work with inherited DTFI.
                        // Insert the month name first, so that they are at the front of abbreviated month names.
                        if (!month_postfix.empty()) {
                            // Insert the month name with the postfix first, so it can be matched first.
                            this->_insert_hash(temp, (omni::chrono::month::get_name(i) + month_postfix), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                        } else
                        {
                            this->_insert_hash(temp, omni::chrono::month::get_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                        }
                        this->_insert_hash(temp, omni::chrono::month::get_abbreviated_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                    }
                }

                std::vector<omni::internal::date_time_format::token_hash_value> _create_token_hash_table()
                {
                    // DEV_NOTE: this function adds values into the list multiple times .. I haven't gone through the areas of this "hash" function
                    // fully to make sure "why" it does this; I'm assuming it has to do with how the C# version uses calendars and thus "hashes" it
                    // in certain areas, thus returning the "value" at that "hash" ... either way "it works (tm)", so not going to futz with it for now.
                    std::vector<omni::internal::date_time_format::token_hash_value> temp = m_dtfi_token_hash;
                    if (temp.capacity() == 0) {
                        for (std::size_t i = 0; i < OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW; ++i) {
                            temp.push_back(omni::internal::date_time_format::token_hash_value());
                        }

                        std::string sep = omni::string::util::trim(this->time_separator);

                        if (OMNI_DATE_INTERNAL_IGNORABLE_COMMA_FW != sep) {
                            this->_insert_hash(temp, OMNI_DATE_INTERNAL_IGNORABLE_COMMA_FW, omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL, 0);
                        }
                        if (OMNI_DATE_INTERNAL_IGNORABLE_PERIOD_FW != sep) {
                            this->_insert_hash(temp, OMNI_DATE_INTERNAL_IGNORABLE_PERIOD_FW, omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL, 0);
                        }

                        this->_insert_hash(temp, OMNI_DATE_FORMAT_INFO_AM_FW, static_cast<omni::internal::date_time_format::token_type::enum_t>(omni::internal::date_time_format::token_type::SEP_AM | omni::internal::date_time_format::token_type::AM), 0);
                        this->_insert_hash(temp, OMNI_DATE_FORMAT_INFO_PM_FW, static_cast<omni::internal::date_time_format::token_type::enum_t>(omni::internal::date_time_format::token_type::SEP_PM | omni::internal::date_time_format::token_type::PM), 1);
                        this->_insert_hash(temp, OMNI_DATE_INTERNAL_DATE_SEP_OR_TZ_OFFSET_FW, omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET, 0);

                        std::vector<std::string> date_words = m_dtfs.get_date_words_of_dtfi(*this);
                        // Ensure the format flags is initialized.
                        // omni::internal::date_time_format::format_flags::enum_t flag = fmt_flags;

                        // For some cultures, the date separator works more like a comma, being allowed before or after any date part.
                        // In these cultures, we do not use normal date separator since we disallow date separator after a date terminal state.
                        // This is determined in DateTimeFormatInfoScanner.  Use this flag to determine if we should treat date separator as ignorable symbol.
                        bool use_date_sep_as_ignorable_symbol = false;

                        std::string month_postfix;
                        if (!date_words.empty()) {
                            // There are DateWords.  It could be a real date word (such as "de"), or a month_postfix.
                            // The month_postfix starts with '\xfffe' (MonthPostfixChar), followed by the real month_postfix.
                            for (std::size_t i = 0; i < date_words.size(); ++i) {
                                char val1 = date_words[i][0];
                                if (val1 == '\xe0') {
                                    if ((date_words[i].size() > 1) && ((date_words[i][1] == '\x00') || (date_words[i][1] == '\x01'))) {
                                        if (date_words[i][1] == '\x00') {
                                            // Get the real month postfix.
                                            month_postfix = date_words[i].substr(1);
                                            // Add the month name + postfix into the token.
                                            this->_add_month_names(temp, month_postfix);
                                        } else {
                                            std::string symbol = date_words[i].substr(1);
                                            this->_insert_hash(temp, symbol, omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL, 0);
                                            if (omni::string::util::trim(this->date_separator) == symbol) {
                                                // The date separator is the same as the ignorable symbol.
                                                use_date_sep_as_ignorable_symbol = true;
                                            }
                                        }
                                    } else {
                                        this->_insert_hash(temp, date_words[i], omni::internal::date_time_format::token_type::DATE_WORD_TOKEN, 0);    
                                    }
                                } else {
                                    this->_insert_hash(temp, date_words[i], omni::internal::date_time_format::token_type::DATE_WORD_TOKEN, 0);
                                }
                            }
                        }

                        if (!use_date_sep_as_ignorable_symbol) {
                            // Use the normal date separator.
                            this->_insert_hash(temp, this->date_separator, omni::internal::date_time_format::token_type::SEP_Date, 0);
                        }
                        // Add the regular month names.
                        this->_add_month_names(temp, "");

                        // Add the abbreviated month names.
                        for (std::size_t i = 1; i <= omni::chrono::month::COUNT(); ++i) {
                            this->_insert_hash(temp, omni::chrono::month::get_abbreviated_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                        }

                        if ((fmt_flags & format_flags::USE_GENITIVE_MONTH) != 0) {
                            for (std::size_t i = 1; i < omni::chrono::month::COUNT(); ++i) {
                                this->_insert_hash(temp, omni::chrono::month::get_abbreviated_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                            }
                            this->_insert_hash(temp, "", omni::internal::date_time_format::token_type::MONTH_TOKEN, 13);
                        }

                        if ((fmt_flags & format_flags::USE_LEAP_YEAR_MONTH) != 0) {
                            for (std::size_t i = 1; i < omni::chrono::month::COUNT(); ++i) {
                                this->_insert_hash(temp, omni::chrono::month::get_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                            }
                            this->_insert_hash(temp, "", omni::internal::date_time_format::token_type::MONTH_TOKEN, 13);
                        }

                        for (std::size_t i = 0; i < omni::chrono::day::COUNT(); ++i) {
                            // We have to call public methods here to work with inherited DTFI.
                            this->_insert_hash(temp, omni::chrono::day::get_name(i), omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN, static_cast<int64_t>(i));
                            this->_insert_hash(temp, omni::chrono::day::get_abbreviated_name(i), omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN, static_cast<int64_t>(i));
                        }

                        this->_insert_hash(temp, OMNI_DATE_ERA_FW, omni::internal::date_time_format::token_type::ERA_TOKEN, 1);
                        this->_insert_hash(temp, OMNI_DATE_ERA_ABBR_FW, omni::internal::date_time_format::token_type::ERA_TOKEN, 1);
                        this->_insert_hash(temp, OMNI_DATE_FORMAT_INFO_AM_FW, static_cast<omni::internal::date_time_format::token_type::enum_t>(omni::internal::date_time_format::token_type::SEP_AM | omni::internal::date_time_format::token_type::AM), 0);
                        this->_insert_hash(temp, OMNI_DATE_FORMAT_INFO_PM_FW, static_cast<omni::internal::date_time_format::token_type::enum_t>(omni::internal::date_time_format::token_type::SEP_PM | omni::internal::date_time_format::token_type::PM), 1);

                        // Add invariant month names and day names.
                        for (std::size_t i = 1; i < omni::chrono::month::COUNT(); ++i) {
                            // We have to call public methods here to work with inherited DTFI.
                            // Insert the month name first, so that they are at the front of abbreviated month names.
                            this->_insert_hash(temp, omni::chrono::month::get_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                            this->_insert_hash(temp, omni::chrono::month::get_abbreviated_name(i), omni::internal::date_time_format::token_type::MONTH_TOKEN, static_cast<int64_t>(i));
                        }

                        for (std::size_t i = 0; i < omni::chrono::day::COUNT(); ++i) {
                            // We have to call public methods here to work with inherited DTFI.
                            this->_insert_hash(temp, omni::chrono::day::get_name(i), omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN, static_cast<int64_t>(i));
                            this->_insert_hash(temp, omni::chrono::day::get_abbreviated_name(i), omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN, static_cast<int64_t>(i));
                        }

                        this->_insert_hash(temp, OMNI_DATE_ERA_ABBR_FW, omni::internal::date_time_format::token_type::ERA_TOKEN, 1);

                        this->_insert_hash(temp, OMNI_DATE_INTERNAL_LOCAL_TIME_MARK_FW, omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK, 0);
                        this->_insert_hash(temp, OMNI_DATE_INTERNAL_GMT_NAME_FW, omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN, 0);
                        this->_insert_hash(temp, OMNI_DATE_ZULU_NAME_FW, omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN, 0);

                        this->_insert_hash(temp, OMNI_DATE_INTERNAL_INV_DATE_SEP_FW, omni::internal::date_time_format::token_type::SEP_Date, 0);
                        this->_insert_hash(temp, OMNI_DATE_INTERNAL_INV_TIME_SEP_FW, omni::internal::date_time_format::token_type::SEP_TIME, 0);

                        m_dtfi_token_hash = temp;
                    }
                    return temp;
                }
        };

        class date_time_token
        {
            public:
                omni::internal::date_time_format::token::enum_t dtt; // Store the token
                omni::internal::date_time_format::token_type::enum_t suffix; // Store the CJK Year/Month/Day suffix (if any)
                int64_t num;    // Store the number that we are parsing (if any)

                date_time_token() :
                    dtt(omni::internal::date_time_format::token::UNKNOWN),
                    suffix(omni::internal::date_time_format::token_type::SEP_UNK),
                    num(0)
                {}

                date_time_token(const date_time_token& cp) :
                    dtt(cp.dtt),
                    suffix(cp.suffix),
                    num(cp.num)
                {}

                ~date_time_token()
                {
                }

                date_time_token& operator=(const date_time_token& cp)
                {
                    this->dtt = cp.dtt;
                    this->suffix = cp.suffix;
                    this->num = cp.num;
                    return *this;
                }
        };

        // The buffer to store temporary parsing information.
        class date_time_raw_info
        {
            public:
                int64_t* num;
                int64_t num_count;
                int64_t month;
                int64_t year;
                int64_t day_of_week;
                int64_t era;
                omni::internal::date_time_format::time_mark::enum_t time_mark;
                double fraction;
                bool has_same_date_and_time_separators;
                bool time_zone;

                explicit date_time_raw_info(int64_t* buff) :
                    num(buff),
                    num_count(0),
                    month(-1),
                    year(-1),
                    day_of_week(-1),
                    era(-1),
                    time_mark(omni::internal::date_time_format::time_mark::NOT_SET),
                    fraction(-1),
                    has_same_date_and_time_separators(false),
                    time_zone(false)
                {
                }

                ~date_time_raw_info() {}

                void add_number(int64_t value)
                {
                    this->num[this->num_count++] = value;
                }

                int64_t get_number(int64_t index)
                {
                    return this->num[index];
                }

            private:
                // making these not user accessible because it should only be the "buffer" constructor that's used
                // so don't implicitly create any extra code
                date_time_raw_info();
                date_time_raw_info(const date_time_raw_info& cp);
                date_time_raw_info& operator=(const date_time_raw_info& cp);
        };

        class dt_sub_string
        {
            public:
                std::string s;
                int32_t index;
                int32_t length;
                omni::internal::date_time_format::dt_substring_type::enum_t type;
                int32_t value;

                dt_sub_string() :
                    s(),
                    index(0),
                    length(0),
                    type(dt_substring_type::UNKNOWN),
                    value(0)
                {}

                dt_sub_string(const dt_sub_string& cp) :
                    s(cp.s),
                    index(cp.index),
                    length(cp.length),
                    type(cp.type),
                    value(cp.value)
                {}

                ~dt_sub_string() {}

                dt_sub_string& operator=(const dt_sub_string& cp)
                {
                    this->s = cp.s;
                    this->index = cp.index;
                    this->length = cp.length;
                    this->type = cp.type;
                    this->value = cp.value;
                    return *this;
                }

                char operator[](int32_t relative_index)
                {
                    return this->s[static_cast<std::size_t>(this->index + relative_index)];
                }
        };

        // DEV_NOTE: keeping the `__` in the name for posterity since that's how it is in the C# impl
        class __dt_string
        {
            public:
                // this->value property: stores the real string to be parsed.
                std::string value;

                // this->index property: points to the character that we are currently parsing.
                int64_t index;

                // The length of this->value string.
                int64_t len;

                // The current character to be looked at.
                char current_char;

                // Flag to indicate if we encounter an digit, we should check for token or not.
                // In some cultures, such as mn-MN, it uses "\x0031\x00a0\x0434\x04af\x0433\x044d\x044d\x0440\x00a0\x0441\x0430\x0440" in month names.
                bool check_digit_token;

                __dt_string(const std::string& str, omni::internal::date_time_format::format_info& dtfi) :
                    value(str),
                    index(-1),
                    len(static_cast<int64_t>(str.length())),
                    current_char('\0'),
                    check_digit_token(((dtfi.fmt_flags & format_flags::USE_DIGIT_PREFIX_IN_TOKENS) != 0))
                {
                }

                __dt_string(const std::string& str, omni::internal::date_time_format::format_info& dtfi, bool check_token) :
                    value(str),
                    index(-1),
                    len(static_cast<int64_t>(str.length())),
                    current_char('\0'),
                    check_digit_token(check_token)
                {
                    OMNI_UNUSED(dtfi);
                }

                __dt_string(const __dt_string& cp) :
                    value(cp.value),
                    index(cp.index),
                    len(cp.len),
                    current_char(cp.current_char),
                    check_digit_token(cp.check_digit_token)
                {
                }

                ~__dt_string() {}

                __dt_string& operator=(const __dt_string& cp)
                {
                    this->value = cp.value;
                    this->index = cp.index;
                    this->len = cp.len;
                    this->current_char = cp.current_char;
                    this->check_digit_token = cp.check_digit_token;
                    return *this;
                }

                /*
                    advance the this->index.
                    Return true if this->index is NOT at the end of the string.

                    Typical usage:
                    while (str.get_next()) {
                        char ch = str.get_char()
                    }
                */
                bool get_next()
                {
                    this->index++;
                    if (this->index < len) {
                        this->current_char = this->value[static_cast<std::size_t>(this->index)];
                        return true;
                    }
                    return false;
                }

                bool at_end()
                {
                    return this->index < this->len ? false : true;
                }

                bool advance(int64_t count)
                {
                    this->index += count;
                    if (this->index < this->len) {
                        this->current_char = this->value[static_cast<std::size_t>(this->index)];
                        return true;
                    }
                    return false;
                }

                // Used by DateTime.Parse() to get the next token.
                void get_regular_token(
                    omni::internal::date_time_format::token_type::enum_t& token_type,
                    int64_t& token_value,
                    omni::internal::date_time_format::format_info& dtfi,
                    bool recurse
                ) {
                    if (!recurse) {
                        token_value = 0;
                        if (this->index >= len) {
                            token_type = omni::internal::date_time_format::token_type::END_OF_STRING;
                            return;
                        }
                        token_type = omni::internal::date_time_format::token_type::UNKNOWN_TOKEN;
                    }

                    // Start:
                    if (omni::char_util::is_digit(this->current_char)) {
                        // This is a digit.
                        int64_t char_val = 0;
                        int64_t start = this->index;
                        token_value = this->current_char - '0';

                        // Collect other digits.
                        while (++this->index < len) {
                            this->current_char = this->value[static_cast<std::size_t>(this->index)];
                            char_val = this->current_char - '0';
                            if (char_val >= 0 && char_val <= 9) {
                                token_value = token_value * 10 + char_val;
                            } else {
                                break;
                            }
                        }

                        if (this->index - start > OMNI_DATE_INTERNAL_MAX_DATE_TIME_NUMBER_DIGITS_FW) {
                            token_type = omni::internal::date_time_format::token_type::NUMBER_TOKEN;
                            token_value = -1;
                        } else if (this->index - start < 3) {
                            token_type = omni::internal::date_time_format::token_type::NUMBER_TOKEN;
                        } else {
                            // If there are more than 3 digits, assume that it's a year value.
                            token_type = omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN;
                        }

                        if (this->check_digit_token) {
                            omni::internal::date_time_format::token_type::enum_t temp_type = omni::internal::date_time_format::token_type::SEP_UNK;
                            int64_t temp_val = 0;
                            int64_t save = this->index;
                            char save_ch = this->current_char;
                            // Re-scan using the staring this->index to see if this is a token.
                            this->index = start;  // To include the first digit.
                            this->current_char = this->value[static_cast<std::size_t>(this->index)];
                            // This DTFI has tokens starting with digits.
                            // E.g. mn-MN has month name like "\x0031\x00a0\x0434\x04af\x0433\x044d\x044d\x0440\x00a0\x0441\x0430\x0440"
                            if (dtfi.tokenize(omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK, temp_type, temp_val, *this)) {
                                token_type = temp_type;
                                token_value = temp_val;
                                // This is a token, so the this->index has been advanced properly in DTFI.Tokenizer().
                            } else {
                                // Use the number token value.
                                // Restore the index.
                                this->index = save;
                                this->current_char = save_ch;
                            }
                        }
                    } else if (omni::char_util::is_white_space(this->current_char)) {
                        // Just skip to the next character.
                        bool eof = true;
                        while (++this->index < this->len) {
                            this->current_char = this->value[static_cast<std::size_t>(this->index)];
                            if (!(omni::char_util::is_white_space(this->current_char))) {
                                // goto Start;
                                get_regular_token(token_type, token_value, dtfi, true);
                                eof = false;
                                break;
                            }
                        }
                        if (eof) {
                            // We have reached the end of string.
                            token_type = omni::internal::date_time_format::token_type::END_OF_STRING;
                        }
                    } else {
                        dtfi.tokenize(omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK, token_type, token_value, *this);
                    }
                }
                
                omni::internal::date_time_format::token_type::enum_t get_separator_token(omni::internal::date_time_format::format_info& dtfi, int64_t& index_before_sep, char& char_before_sep)
                {
                    index_before_sep = this->index;
                    char_before_sep = this->current_char;
                    if (!this->skip_white_space_current()) {
                        // Reach the end of the string.
                        return omni::internal::date_time_format::token_type::SEP_END;
                    }

                    if (!omni::char_util::is_digit(this->current_char)) {
                        // Not a digit.  tokenize it.
                        omni::internal::date_time_format::token_type::enum_t token_type = omni::internal::date_time_format::token_type::SEP_UNK;
                        int64_t token_value = 0;
                        if (!dtfi.tokenize(omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK, token_type, token_value, *this)) {
                            return omni::internal::date_time_format::token_type::SEP_SPACE;
                        }
                        return token_type;
                    }

                    // Do nothing here.  If we see a number, it will not be a separator. There is no need wasting time trying to find the separator token.
                    return omni::internal::date_time_format::token_type::SEP_SPACE;
                }

                bool match_specified_word(const std::string& target, int64_t end_idx)
                {
                    int64_t count = end_idx - this->index;
                    if (static_cast<std::size_t>(count) != target.size()) {
                        return false;
                    }
                    if ((this->index + count) > this->len) {
                        return false;
                    }
                    return (omni::internal::date_time_format::compare_info::compare(this->value, static_cast<std::size_t>(this->index), static_cast<std::size_t>(count), target, 0, static_cast<std::size_t>(count)) == 0);
                }

                bool match_specified_word(const std::string& target)
                {
                    return this->match_specified_word(target, static_cast<int64_t>(target.size() + static_cast<std::size_t>(this->index)));
                }

                bool match_specified_words(const std::string& target, bool check_word_boundary, std::size_t& match_len)
                {
                    const char* WS_CHECKS = " ";
                    std::size_t val_remaining = this->value.size() - static_cast<std::size_t>(this->index);
                    match_len = target.size();

                    if ((match_len > val_remaining) || (omni::internal::date_time_format::compare_info::compare(this->value, static_cast<std::size_t>(this->index), match_len, target, 0, match_len) != 0)) {
                        // Check word by word
                        std::size_t target_pos = 0; // Where we are in the target string
                        std::size_t this_pos = static_cast<std::size_t>(this->index); // Where we are in this string
                        std::size_t ws_idx = target.find_first_of(WS_CHECKS, target_pos);
                        if (ws_idx == std::string::npos) {
                            return false;
                        }
                        do {
                            std::size_t segment_len = ws_idx - target_pos;
                            if (this_pos >= this->value.size() - segment_len) { // Subtraction to prevent overflow.
                                return false;
                            }
                            if (segment_len == 0) {
                                // If segment_len == 0, it means that we have leading space in the target string.
                                // In that case, skip the leading spaces in the target and this string.
                                match_len--;
                            } else {
                                // Make sure we also have whitespace in the input string
                                if (!omni::char_util::is_white_space(this->value[this_pos + segment_len])) {
                                    return false;
                                }
                                if (omni::internal::date_time_format::compare_info::compare(this->value, this_pos, segment_len, target, target_pos, segment_len) !=0) {
                                    return false;
                                }
                                // advance the input string
                                this_pos = this_pos + segment_len + 1;
                            }
                            // advance our target string
                            target_pos = ws_idx + 1;


                            // Skip past multiple whitespace
                            while (this_pos < this->value.size() && omni::char_util::is_white_space(this->value[this_pos])) {
                                this_pos++;
                                match_len++;
                            }
                        } while ((ws_idx = target.find_first_of(WS_CHECKS, target_pos)) != std::string::npos);
                        // now check the last segment;
                        if (target_pos < target.size()) {
                            std::size_t segment_len = target.size() - target_pos;
                            if (this_pos > this->value.size() - segment_len) {
                                return false;
                            }
                            if (omni::internal::date_time_format::compare_info::compare(this->value, this_pos, segment_len, target, target_pos, segment_len) !=0) {
                                return false;
                            }
                        }
                    }

                    if (check_word_boundary) {
                        std::size_t next_char_idx = static_cast<std::size_t>(this->index) + match_len;
                        if (next_char_idx < this->value.size()) {
                            if (omni::char_util::is_letter(this->value[next_char_idx])) {
                                return false;
                            }
                        }
                    }
                    return true;
                }

                // Check to see if the string starting from this->index is a prefix of str.
                // If a match is found, true value is returned and this->index is updated to the next character to be parsed.
                // Otherwise, this->index is unchanged.
                bool match(const std::string& str)
                {
                    if (++this->index >= this->len) {
                        return false;
                    }

                    if (str.size() > (this->value.size() - static_cast<std::size_t>(this->index))) {
                        return false;
                    }

                    if (omni::internal::date_time_format::compare_info::compare_ordinal(this->value, static_cast<std::size_t>(this->index), str.size(), str, 0, str.size()) == 0) {
                        // Update the this->index to the end of the matching string.
                        // So the following get_next()/match() operation will get
                        // the next character to be parsed.
                        this->index += (str.size() - 1);
                        return true;
                    }
                    return false;
                }

                bool match(char ch)
                {
                    if (++this->index >= this->len) {
                        return false;
                    }
                    if (this->value[static_cast<std::size_t>(this->index)] == ch) {
                        this->current_char = ch;
                        return true;
                    }
                    this->index--;
                    return false;
                }

                int64_t match_longest_words(const std::vector<std::string>& words, int64_t& max_match_str_len)
                {
                    int64_t result = -1;
                    std::size_t match_len = 0;
                    for (std::size_t i = 0; i < words.size(); ++i) {
                        match_len = words[i].size();
                        if (this->match_specified_words(words[i], false, match_len)) {
                            if (match_len > static_cast<std::size_t>(max_match_str_len)) {
                                max_match_str_len = static_cast<int64_t>(match_len);
                                result = static_cast<int64_t>(i);
                            }
                        }
                    }
                    return result;
                }

                // Get the number of repeat character after the current character.
                // For a string "hh:mm:ss" at this->index of 3. get_repeat_count() = 2, and this->index
                // will point to the second ':'.
                std::size_t get_repeat_count()
                {
                    char repeatChar = this->value[static_cast<std::size_t>(this->index)];
                    std::size_t pos = static_cast<std::size_t>(this->index) + 1;
                    while ((pos < static_cast<std::size_t>(len)) && (this->value[pos] == repeatChar)) {
                        pos++;
                    }
                    std::size_t repeat_count = (pos - static_cast<std::size_t>(this->index));
                    // Update the this->index to the end of the repeated characters.
                    // So the following get_next() operation will get
                    // the next character to be parsed.
                    this->index = static_cast<int64_t>(pos - 1);
                    return repeat_count;
                }

                // Return false when end of string is encountered or a non-digit character is found.
                bool get_next_digit()
                {
                    if (++this->index >= this->len) {
                        return false;
                    }
                    return omni::char_util::is_digit(this->value[static_cast<std::size_t>(this->index)]);
                }

                // Get the current character.
                char get_char()
                {
                    return this->value[static_cast<std::size_t>(this->index)];
                }

                // Convert the current character to a digit, and return it.
                std::size_t get_digit()
                {
                    return static_cast<std::size_t>((this->value[static_cast<std::size_t>(this->index)] - '0'));
                }

                // Eat White Space ahead of the current position
                // Return false if end of string is encountered.
                void skip_white_spaces()
                {
                    // Look ahead to see if the next character is a whitespace.
                    while (this->index+1 < this->len) {
                        if (!omni::char_util::is_white_space(this->value[static_cast<std::size_t>(this->index)+1])) {
                            return;
                        }
                        this->index++;
                    }
                }

                // Skip white spaces from the current position
                // Return false if end of string is encountered.
                bool skip_white_space_current()
                {
                    if (this->index >= this->len) {
                        return false;
                    }
                    if (!omni::char_util::is_white_space(this->current_char)) {
                        return true;
                    }
                    while (++this->index < this->len) {
                        this->current_char = this->value[static_cast<std::size_t>(this->index)];
                        if (!omni::char_util::is_white_space(this->current_char)) {
                            return true;
                        }
                        // Nothing here.
                    }
                    return false;
                }

                void trim_tail()
                {
                    int64_t i = this->len - 1;
                    while (i >= 0 && omni::char_util::is_white_space(this->value[static_cast<std::size_t>(i)])) {
                        --i;
                    }
                    this->value = this->value.substr(0, static_cast<std::size_t>(i) + 1);
                    this->len = static_cast<int64_t>(this->value.size());
                }

                // Trim the trailing spaces within a quoted string.
                // Call this after trim_tail() is done.
                void remove_trailing_in_quote_spaces()
                {
                    int64_t i = this->len - 1;
                    if (i <= 1) {
                        return;
                    }
                    char ch = this->value[static_cast<std::size_t>(i)];
                    // Check if the last character is a quote.
                    if (ch == '\'' || ch == '\"') {
                        if (omni::char_util::is_white_space(this->value[static_cast<std::size_t>(i - 1)])) {
                            --i;
                            while (i >= 1 && omni::char_util::is_white_space(this->value[static_cast<std::size_t>(i - 1)])) {
                                --i;
                            }
                            this->value = this->value.erase(static_cast<std::size_t>(i), this->value.size() - 1 - static_cast<std::size_t>(i));
                            this->len = static_cast<int64_t>(this->value.size());
                        }
                    }
                }

                // Trim the leading spaces within a quoted string.
                // Call this after the leading spaces before quoted string are trimmed.
                void remove_leading_in_quote_spaces()
                {
                    if (this->len <= 2) {
                        return;
                    }
                    int64_t i = 0;
                    char ch = this->value[static_cast<std::size_t>(i)];
                    // Check if the last character is a quote.
                    if (ch == '\'' || ch == '\"') {
                        while ((i + 1) < this->len && omni::char_util::is_white_space(this->value[static_cast<std::size_t>(i + 1)])) {
                            ++i;
                        }
                        if (i != 0) {
                            this->value = this->value.erase(1, static_cast<std::size_t>(i));
                            this->len = static_cast<int64_t>(this->value.size());
                        }
                    }
                }

                omni::internal::date_time_format::dt_sub_string get_sub_string()
                {
                    omni::internal::date_time_format::dt_sub_string sub;
                    sub.index = static_cast<int32_t>(this->index);
                    sub.s = this->value;
                    while (this->index + sub.length < this->len) {
                        omni::internal::date_time_format::dt_substring_type::enum_t current_type;
                        char ch = this->value[static_cast<std::size_t>(this->index + sub.length)];
                        if (omni::char_util::is_digit(ch)) {
                            current_type = dt_substring_type::NUMBER;
                        } else {
                            current_type = dt_substring_type::OTHER;
                        }

                        if (sub.length == 0) {
                            sub.type = current_type;
                        } else {
                            if (sub.type != current_type) {
                                break;
                            }
                        }
                        sub.length++;
                        if (current_type == dt_substring_type::NUMBER) {
                            // Incorporate the number into the value
                            // Limit the digits to prevent overflow
                            if (sub.length > OMNI_DATE_INTERNAL_MAX_DATE_TIME_NUMBER_DIGITS_FW) {
                                sub.type = dt_substring_type::INVALID;
                                return sub;
                            }
                            int32_t number = ch - '0';
                            sub.value = sub.value * 10 + number;
                        } else {
                            // For non numbers, just return this length 1 token. This should be expanded
                            // to more types of thing if this parsing approach is used for things other
                            // than numbers and single characters
                            break;
                        }
                    }
                    if (sub.length == 0) {
                        sub.type = dt_substring_type::END;
                    }
                    return sub;
                }

                void consume_sub_string(const omni::internal::date_time_format::dt_sub_string& sub)
                {
                    this->index = sub.index + sub.length;
                    if (this->index < this->len) {
                        this->current_char = this->value[static_cast<std::size_t>(this->index)];
                    }
                }
        };

        // DEV_NOTE: Have to move this -after- class __dt_string because of the forward declaration
        bool format_info::tokenize
        (
            const omni::internal::date_time_format::token_type::enum_t& token_mask,
            omni::internal::date_time_format::token_type::enum_t& token_type,
            int64_t& token_value,
            omni::internal::date_time_format::__dt_string& str
        ) {
            token_type = omni::internal::date_time_format::token_type::UNKNOWN_TOKEN;
            token_value = 0;

            omni::internal::date_time_format::token_hash_value value;
            char ch = str.current_char;
            bool is_letter = omni::char_util::is_letter(ch);
            if (is_letter) {
                ch = omni::char_util::to_lower(ch);
            }

            std::size_t hash_code = static_cast<std::size_t>(ch % OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW);
            std::size_t hash_probe = static_cast<std::size_t>(1 + (ch % OMNI_DATE_INTERNAL_SECOND_PRIME_FW));
            std::size_t remaining = static_cast<std::size_t>(str.len - str.index);
            std::size_t i = 0;

            std::vector<omni::internal::date_time_format::token_hash_value> hash_table = this->m_dtfi_token_hash;
            if (hash_table.capacity() == 0) {
                hash_table = this->_create_token_hash_table();
            }
            do {
                value = hash_table[static_cast<std::size_t>(hash_code)];
                if (value.empty) {
                    // Not found.
                    break;
                }
                // Check this value has the right category (regular token or separator token) that we are looking for.
                if (((value.token_type & token_mask) > 0) && (value.token_string.size() <= remaining)) {
                    if (omni::string::util::compare(str.value, static_cast<std::size_t>(str.index), value.token_string, 0, value.token_string.size(), omni::string::compare_options::IGNORE_CASE) == 0) {
                        if (is_letter) {
                            // If this token starts with a letter, make sure that we won't allow partial match.  So you can't tokenize "MarchWed" separately.
                            std::size_t next_char_idx = static_cast<std::size_t>(str.index) + value.token_string.size();
                            if (next_char_idx < static_cast<std::size_t>(str.len)) {
                                // Check word boundary.  The next character should NOT be a letter.
                                if (omni::char_util::is_letter(str.value[next_char_idx])) {
                                    return false;
                                }
                            }
                        }
                        token_type = static_cast<omni::internal::date_time_format::token_type::enum_t>(value.token_type & token_mask);
                        token_value = value.token_value;
                        str.advance(static_cast<int64_t>(value.token_string.size()));
                        return true;
                    }  else if (value.token_type == omni::internal::date_time_format::token_type::MONTH_TOKEN && this->has_spaces_in_month_names()) {
                        // For month token, we will match the month names which have spaces.
                        std::size_t match_str_len = 0;
                        if (str.match_specified_words(value.token_string, true, match_str_len)) {
                            token_type = static_cast<omni::internal::date_time_format::token_type::enum_t>(value.token_type & token_mask);
                            token_value = value.token_value;
                            str.advance(static_cast<int64_t>(match_str_len));
                            return true;
                        }
                    }  else if (value.token_type == omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN && has_spaces_in_day_names()) {
                        // For month token, we will match the month names which have spaces.
                        std::size_t match_str_len = 0;
                        if (str.match_specified_words(value.token_string, true, match_str_len)) {
                            token_type = static_cast<omni::internal::date_time_format::token_type::enum_t>(value.token_type & token_mask);
                            token_value = value.token_value;
                            str.advance(static_cast<int64_t>(match_str_len));
                            return true;
                        }
                    }
                }
                ++i;
                hash_code += hash_probe;
                if (hash_code >= OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW) {
                    hash_code -= OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW;
                }
            } while (i < OMNI_DATE_INTERNAL_TOKEN_HASH_SIZE_FW);

            return false;
        }

        bool parse_fraction(omni::internal::date_time_format::__dt_string& str, double& result)
        {
            double base = 0.1;
            std::size_t digits = 0;
            char ch;
            result = 0;
            while (str.get_next() && omni::char_util::is_digit(ch = str.current_char)) {
                result += (ch - '0') * base;
                base *= 0.1;
                ++digits;
            }
            return (digits > 0);
        }

        bool parse_time_zone(omni::internal::date_time_format::__dt_string& str, omni::chrono::time_span& result)
        {
            // The hour/minute offset for timezone.
            int32_t hour_offset = 0;
            int32_t minute_offset = 0;
            omni::internal::date_time_format::dt_sub_string sub = str.get_sub_string();

            // Consume the +/- character that has already been read
            if (sub.length != 1) {
                return false;
            }

            char offset_char = sub[0];
            if ((offset_char != '+') && (offset_char != '-')) {
                return false;
            }
            str.consume_sub_string(sub);

            sub = str.get_sub_string();
            if (sub.type != dt_substring_type::NUMBER) {
                return false;
            }

            if (sub.length == 1 || sub.length == 2) {
                // Parsing "+8" or "+08"
                hour_offset = sub.value;
                str.consume_sub_string(sub);
                // See if we have minutes
                sub = str.get_sub_string();
                if (sub.length == 1 && sub[0] == ':') {
                    // Parsing "+8:00" or "+08:00"
                    str.consume_sub_string(sub);
                    sub = str.get_sub_string();
                    if (sub.type != dt_substring_type::NUMBER || sub.length < 1 || sub.length > 2) {
                        return false;
                    }
                    minute_offset = sub.value;
                    str.consume_sub_string(sub);
                }
            } else if (sub.length == 3 || sub.length == 4) {
                // Parsing "+800" or "+0800"
                hour_offset = sub.value / 100;
                minute_offset = sub.value % 100;
                str.consume_sub_string(sub);
            } else {
                // Wrong number of digits
                return false;
            }

            if (minute_offset < 0 || minute_offset >= 60) {
                return false;
            }

            result = omni::chrono::time_span(hour_offset, minute_offset, 0);
            if (offset_char == '-') {
                result = result.negate();
            }
            return true;
        }

        bool handle_time_zone(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::parse_result& result)
        {
            if ((str.index < str.len - 1)) {
                char next_ch = str.value[static_cast<std::size_t>(str.index)];
                // Skip whitespace, but don't update the index unless we find a time zone marker
                std::size_t ws_count = 0;
                while (omni::char_util::is_white_space(next_ch) && ((str.index + static_cast<int64_t>(ws_count)) < (str.len - 1))) {
                    ++ws_count;
                    next_ch = str.value[static_cast<std::size_t>(str.index) + ws_count];
                }
                if (next_ch == '+' || next_ch == '-') {
                    str.index += ws_count;
                    if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0) {
                        // Should not have two timezone offsets.
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                    if (!omni::internal::date_time_format::parse_time_zone(str, result.time_zone_offset)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                }
            }
            return true;
        }

        omni::chrono::date_time get_date_time_now(const omni::internal::date_time_format::parse_result& result, const omni::chrono::date_time_styles& styles)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) {
                if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0) {
                    // use the supplied offset to calculate 'Now'
                    return omni::chrono::date_time(
                        static_cast<uint64_t>(static_cast<int64_t>(omni::chrono::date_time::utc_now().ticks()) + result.time_zone_offset.ticks()),
                        omni::chrono::date_time_kind::UNSPECIFIED
                    );
                }
                else if ((styles & omni::chrono::date_time_styles::ASSUME_UNIVERSAL) != 0) {
                    // assume the offset is Utc
                    return omni::chrono::date_time::utc_now();
                }
            }

            // assume the offset is Local
            return omni::chrono::date_time::now();
        }

        void get_default_year(omni::internal::date_time_format::parse_result& result, omni::chrono::date_time_styles& styles)
        {
            result.year = static_cast<int16_t>(omni::internal::date_time_format::get_date_time_now(result, styles).year());
            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::YEAR_DEFAULT);
        }

        bool get_year_month_day_order(const std::string& date_pattern, const omni::internal::date_time_format::format_info& dtfi, int64_t& order)
        {
            int64_t year_order   = -1;
            int64_t month_order  = -1;
            int64_t day_order    = -1;
            int64_t order_count  =  0;
            bool in_quote = false;
            char ch;
            OMNI_UNUSED(dtfi);

            for (std::size_t i = 0; i < date_pattern.size() && order_count < 3; ++i) {
                ch = date_pattern[i];
                if (ch == '\\' || ch == '%') {
                    ++i;
                    continue;  // Skip next character that is escaped by this backslash
                }

                if (ch == '\'' || ch == '"') {
                    in_quote = !in_quote;
                }

                if (!in_quote) {
                    if (ch == 'y') {
                        year_order = order_count++;
                        // Skip all year pattern characters.
                        for(; i+1 < date_pattern.size() && date_pattern[i+1] == 'y'; ++i) {
                            // Do nothing here.
                        }
                    } else if (ch == 'M') {
                        month_order = order_count++;
                        // Skip all month pattern characters.
                        for(; i+1 < date_pattern.size() && date_pattern[i+1] == 'M'; ++i) {
                            // Do nothing here.
                        }
                    } else if (ch == 'd') {
                        std::size_t pattern_count = 1;
                        // Skip all day pattern characters.
                        for(; i+1 < date_pattern.size() && date_pattern[i+1] == 'd'; ++i) {
                            ++pattern_count;
                        }
                        // Make sure this is not "ddd" or "dddd", which means day of week.
                        if (pattern_count <= 2) {
                            day_order = order_count++;
                        }
                    }
                }
            }

            if (year_order == 0 && month_order == 1 && day_order == 2) {
                order = OMNI_DATE_INTERNAL_ORDER_YMD_FW;
                return true;
            }
            if (month_order == 0 && day_order == 1 && year_order == 2) {
                order = OMNI_DATE_INTERNAL_ORDER_MDY_FW;
                return true;
            }
            if (day_order == 0 && month_order == 1 && year_order == 2) {
                order = OMNI_DATE_INTERNAL_ORDER_DMY_FW;
                return true;
            }
            if (year_order == 0 && day_order == 1 && month_order == 2) {
                order = OMNI_DATE_INTERNAL_ORDER_YDM_FW;
                return true;
            }
            order = -1;
            return false;
        }

        bool get_year_month_order(const std::string& pattern, const omni::internal::date_time_format::format_info& dtfi, int64_t& order)
        {
            int64_t year_order   = -1;
            int64_t month_order  = -1;
            int64_t order_count  =  0;
            bool in_quote = false;
            char ch;
            OMNI_UNUSED(dtfi);

            for (std::size_t i = 0; i < pattern.size() && order_count < 2; ++i) {
                ch = pattern[i];
                if (ch == '\\' || ch == '%') {
                    ++i;
                    continue;  // Skip next character that is escaped by this backslash
                }

                if (ch == '\'' || ch == '"') {
                    in_quote = !in_quote;
                }

                if (!in_quote) {
                    if (ch == 'y') {
                        year_order = order_count++;
                        // Skip all year pattern characters.
                        for(; i+1 < pattern.size() && pattern[i+1] == 'y'; ++i) {
                            // do nothing
                        }
                    } else if (ch == 'M') {
                        month_order = order_count++;
                        // Skip all month pattern characters.
                        for(; i+1 < pattern.size() && pattern[i+1] == 'M'; ++i) {
                            // do nothing
                        }
                    }
                }
            }

            if (year_order == 0 && month_order == 1) {
                order = OMNI_DATE_INTERNAL_ORDER_YM_FW;
                return true;
            }
            if (month_order == 0 && year_order == 1) {
                order = OMNI_DATE_INTERNAL_ORDER_MY_FW;
                return true;
            }
            order = -1;
            return false;
        }

        bool get_month_day_order(const std::string& pattern, const omni::internal::date_time_format::format_info& dtfi, int64_t& order)
        {
            int64_t month_order  = -1;
            int64_t day_order    = -1;
            int64_t order_count  =  0;
            bool in_quote = false;
            char ch;
            OMNI_UNUSED(dtfi);

            for (std::size_t i = 0; i < pattern.size() && order_count < 2; ++i) {
                ch = pattern[i];
                if (ch == '\\' || ch == '%') {
                    ++i;
                    continue;  // Skip next character that is escaped by this backslash
                }

                if (ch == '\'' || ch == '"') {
                    in_quote = !in_quote;
                }

                if (!in_quote) {
                    if (ch == 'd') {
                        std::size_t pattern_count = 1;
                        // Skip all day pattern characters.
                        for(; i+1 < pattern.size() && pattern[i+1] == 'd'; ++i) {
                            ++pattern_count;
                        }
                        // Make sure this is not "ddd" or "dddd", which means day of week.
                        if (pattern_count <= 2) {
                            day_order = order_count++;
                        }
                    } else if (ch == 'M') {
                        month_order = order_count++;
                        // Skip all month pattern characters.
                        for(; i+1 < pattern.size() && pattern[i+1] == 'M'; ++i) {
                            // do nothing
                        }
                    }
                }
            }

            if (month_order == 0 && day_order == 1) {
                order = OMNI_DATE_INTERNAL_ORDER_MD_FW;
                return true;
            }
            if (day_order == 0 && month_order == 1) {
                order = OMNI_DATE_INTERNAL_ORDER_DM_FW;
                return true;
            }
            order = -1;
            return false;
        }

        // Adjust the two-digit year if necessary.
        bool try_adjust_year(omni::internal::date_time_format::parse_result& result, int16_t year, int16_t& adjusted_year)
        {
            OMNI_UNUSED(result);
            if (year < 100) {
                /*
                    DEV_NOTE: the following note is from the C# code .. there -was- a try..catch
                    in the code below, but it was replaced with a proper check of invalid years.
                    This C# note is just here for posterity.

                    // the Calendar classes need some real work.  Many of the calendars that throw
                    // don't implement a fast/non-allocating (and non-throwing) IsValid{Year|Day|Month} method.
                    // we are making a targeted try/catch fix in the in-place release but will revisit this code
                    // in the next side-by-side release.

                */

                if ((year < 1) || (year > OMNI_DATE_MAX_YEAR)) {
                    adjusted_year = -1;
                    return false;
                }
                year = static_cast<int16_t>(omni::chrono::date_time::to_four_digit_year(static_cast<uint16_t>(year)));
            }
            adjusted_year = year;
            return true;
        }

        bool set_date_ymd(omni::internal::date_time_format::parse_result& result, uint16_t year, uint16_t month, uint16_t day)
        {
            // Note, longer term these checks should be done at the end of the parse. This current
            // way of checking creates order dependence with parsing the era name.
            if (omni::chrono::date_time::is_valid_day(year, month, day)) {
                result.set_date(static_cast<int16_t>(year), static_cast<int16_t>(month), static_cast<int16_t>(day)); // YMD
                return true;
            }
            return false;
        }

        bool set_date_mdy(omni::internal::date_time_format::parse_result& result, uint16_t month, uint16_t day, uint16_t year)
        {
            return omni::internal::date_time_format::set_date_ymd(result, year, month, day);
        }

        bool set_date_dmy(omni::internal::date_time_format::parse_result& result, uint16_t day, uint16_t month, uint16_t year)
        {
            return omni::internal::date_time_format::set_date_ymd(result, year, month, day);
        }

        bool set_date_ydm(omni::internal::date_time_format::parse_result& result, uint16_t year, uint16_t day, uint16_t month)
        {
            return omni::internal::date_time_format::set_date_ymd(result, year, month, day);
        }

        // Processing terminal case: DS.DX_NN
        bool get_day_of_nn(omni::internal::date_time_format::parse_result& result, omni::chrono::date_time_styles& styles, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {

            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            int64_t n1 = raw.get_number(0);
            int64_t n2 = raw.get_number(1);

            omni::internal::date_time_format::get_default_year(result, styles);

            int64_t order;
            if (!omni::internal::date_time_format::get_month_day_order(dtfi.month_day_pattern, dtfi, order)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                return false;
            }

            if (order == OMNI_DATE_INTERNAL_ORDER_MD_FW) {
                if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(result.year), static_cast<uint16_t>(n1), static_cast<uint16_t>(n2))) { // MD
                    result.flags = static_cast<omni::internal::date_time_format::parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            } else {
                if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(result.year), static_cast<uint16_t>(n2), static_cast<uint16_t>(n1))) { // DM
                    result.flags = static_cast<omni::internal::date_time_format::parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            }
            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        // Processing terminal case: DS.DX_NNN
        bool get_day_of_nnn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            int64_t n1 = raw.get_number(0);
            int64_t n2 = raw.get_number(1);;
            int64_t n3 = raw.get_number(2);

            int64_t order;
            if (!omni::internal::date_time_format::get_year_month_day_order(dtfi.short_date_pattern, dtfi, order)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                return false;
            }
            
            int16_t year;
            if (order == OMNI_DATE_INTERNAL_ORDER_YMD_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result,  static_cast<int16_t>(n1), year) && omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(year), static_cast<uint16_t>(n2), static_cast<uint16_t>(n3))) { // YMD
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            } else if (order == OMNI_DATE_INTERNAL_ORDER_MDY_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result,  static_cast<int16_t>(n3), year) && omni::internal::date_time_format::set_date_mdy(result, static_cast<uint16_t>(n1), static_cast<uint16_t>(n2), static_cast<uint16_t>(year))) { // MDY
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            } else if (order == OMNI_DATE_INTERNAL_ORDER_DMY_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result,  static_cast<int16_t>(n3), year) && omni::internal::date_time_format::set_date_dmy(result, static_cast<uint16_t>(n1), static_cast<uint16_t>(n2), static_cast<uint16_t>(year))) { // DMY
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            } else if (order == OMNI_DATE_INTERNAL_ORDER_YDM_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result,  static_cast<int16_t>(n1), year) && omni::internal::date_time_format::set_date_ydm(result, static_cast<uint16_t>(year), static_cast<uint16_t>(n2), static_cast<uint16_t>(n3))) { // YDM
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            }
            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_day_of_mn(omni::internal::date_time_format::parse_result& result, omni::chrono::date_time_styles& styles, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {

            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            // The interpretation is based on the month_day_pattern and year_month_pattern
            //
            //    month_day_pattern   year_month_pattern  Interpretation
            //    ---------------   ----------------  ---------------
            //    MMMM dd           MMMM yyyy         Day
            //    MMMM dd           yyyy MMMM         Day
            //    dd MMMM           MMMM yyyy         Year
            //    dd MMMM           yyyy MMMM         Day
            //
            // In the first and last cases, it could be either or neither, but a day is a better default interpretation
            // than a 2 digit year.

            int64_t month_day_order;
            if (!omni::internal::date_time_format::get_month_day_order(dtfi.month_day_pattern, dtfi, month_day_order)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                return false;
            }
            if (month_day_order == OMNI_DATE_INTERNAL_ORDER_DM_FW) {
                int64_t year_month_order;
                if (!omni::internal::date_time_format::get_year_month_order(dtfi.year_month_pattern, dtfi, year_month_order)) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                    return false;
                }
                if (year_month_order == OMNI_DATE_INTERNAL_ORDER_MY_FW) {
                    int16_t year;
                    if (!omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(raw.get_number(0)), year) || !omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), 1)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    return true;
                }
            }

            omni::internal::date_time_format::get_default_year(result, styles);
            if (!omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(result.year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(raw.get_number(0)))) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            return true;
        }

        bool get_day_of_nm(omni::internal::date_time_format::parse_result& result, omni::chrono::date_time_styles& styles, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            // The interpretation is based on the month_day_pattern and year_month_pattern
            //
            //    month_day_pattern   year_month_pattern  Interpretation
            //    ---------------   ----------------  ---------------
            //    MMMM dd           MMMM yyyy         Day
            //    MMMM dd           yyyy MMMM         Year
            //    dd MMMM           MMMM yyyy         Day
            //    dd MMMM           yyyy MMMM         Day
            //
            // In the first and last cases, it could be either or neither, but a day is a better default interpretation
            // than a 2 digit year.

            int64_t month_day_order;
            if (!omni::internal::date_time_format::get_month_day_order(dtfi.month_day_pattern, dtfi, month_day_order)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                return false;
            }
            if (month_day_order == OMNI_DATE_INTERNAL_ORDER_MD_FW) {
                int64_t year_month_order;
                if (!omni::internal::date_time_format::get_year_month_order(dtfi.year_month_pattern, dtfi, year_month_order)) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                    return false;
                }
                if (year_month_order == OMNI_DATE_INTERNAL_ORDER_YM_FW) {
                    int16_t year;
                    if (!omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(raw.get_number(0)), year) || !omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), 1)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    return true;
                }
            }

            omni::internal::date_time_format::get_default_year(result, styles);
            if (!omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(result.year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(raw.get_number(0)))) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            return true;
        }

        bool get_day_of_mnn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            int64_t n1 = raw.get_number(0);
            int64_t n2 = raw.get_number(1);

            int64_t order;
            if (!omni::internal::date_time_format::get_year_month_day_order(dtfi.short_date_pattern, dtfi, order)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                return false;
            }

            int16_t year;
            if (order == OMNI_DATE_INTERNAL_ORDER_MDY_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(n2), year) && omni::chrono::date_time::is_valid_day(static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(n1))) {
                    result.set_date(year, static_cast<int16_t>(raw.month), static_cast<int16_t>(n1));      // MDY
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                } else if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(n1), year) && omni::chrono::date_time::is_valid_day(static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(n2))) {
                    result.set_date(year, static_cast<int16_t>(raw.month), static_cast<int16_t>(n2));      // YMD
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            } else if (order == OMNI_DATE_INTERNAL_ORDER_YMD_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(n1), year) && omni::chrono::date_time::is_valid_day(static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(n2))) {
                    result.set_date(year, static_cast<int16_t>(raw.month), static_cast<int16_t>(n2));      // YMD
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                } else if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(n2), year) && omni::chrono::date_time::is_valid_day(static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(n1))) {
                    result.set_date(year, static_cast<int16_t>(raw.month), static_cast<int16_t>(n1));      // DMY
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            } else if (order == OMNI_DATE_INTERNAL_ORDER_DMY_FW) {
                if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(n2), year) && omni::chrono::date_time::is_valid_day(static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(n1))) {
                    result.set_date(year, static_cast<int16_t>(raw.month), static_cast<int16_t>(n1));      // DMY
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                } else if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(n1), year) && omni::chrono::date_time::is_valid_day(static_cast<uint16_t>(year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(n2))) {
                    result.set_date(year, static_cast<int16_t>(raw.month), static_cast<int16_t>(n2));      // YMD
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true;
                }
            }

            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_day_of_ynn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {

            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            int64_t n1 = raw.get_number(0);
            int64_t n2 = raw.get_number(1);
            std::string pattern = dtfi.short_date_pattern;

            // For compatibility, don't throw if we can't determine the order, but default to YMD instead
            int64_t order;
            if (omni::internal::date_time_format::get_year_month_day_order(pattern, dtfi, order) && order == OMNI_DATE_INTERNAL_ORDER_YDM_FW) {
                if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(n2), static_cast<uint16_t>(n1))) {
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true; // Year + DM
                }
            } else {
                if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(n1), static_cast<uint16_t>(n2))) {
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true; // Year + MD
                }
            }
            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_day_of_nny(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {

            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            int64_t n1 = raw.get_number(0);
            int64_t n2 = raw.get_number(1);

            int64_t order = 0;
            if (!omni::internal::date_time_format::get_year_month_day_order(dtfi.short_date_pattern, dtfi, order)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                return false;
            }

            if (order == OMNI_DATE_INTERNAL_ORDER_MDY_FW || order == OMNI_DATE_INTERNAL_ORDER_YMD_FW) {
                if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(n1), static_cast<uint16_t>(n2))) {
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true; // MD + Year
                }
            } else {
                if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(n2), static_cast<uint16_t>(n1))) {
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                    return true; // DM + Year
                }
            }
            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_day_of_ymn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            OMNI_UNUSED(dtfi);
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(raw.month), static_cast<uint16_t>(raw.get_number(0)))) {
                result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                return true;
            }
            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_day_of_yn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            OMNI_UNUSED(dtfi);
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(raw.get_number(0)), 1)) {
                result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                return true;
            }

            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_day_of_ym(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            OMNI_UNUSED(dtfi);
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DATE) != 0) {
                // Multiple dates in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            if (omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(raw.year), static_cast<uint16_t>(raw.month), 1)) {
                result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DATE);
                return true;
            }

            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool get_time_of_n(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_TIME) != 0) {
                // Multiple times in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            // In this case, we need a time mark. Check if so.
            if (raw.time_mark == omni::internal::date_time_format::time_mark::NOT_SET) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            result.hour = static_cast<int16_t>(raw.get_number(0));
            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_TIME);
            return true;
        }

        bool get_time_of_nn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_TIME) != 0) {
                // Multiple times in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            result.hour = static_cast<int16_t>(raw.get_number(0));
            result.minute = static_cast<int16_t>(raw.get_number(1));
            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_TIME);
            return true;
        }

        bool get_time_of_nnn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_TIME) != 0) {
                // Multiple times in the input string
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            result.hour = static_cast<int16_t>(raw.get_number(0));
            result.minute = static_cast<int16_t>(raw.get_number(1));
            result.second = static_cast<int16_t>(raw.get_number(2));
            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_TIME);
            return true;
        }

        bool get_date_of_dsn(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw)
        {
            if (raw.num_count != 1 || result.day != -1) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            result.day = static_cast<int16_t>(raw.get_number(0));
            return true;
        }

        bool get_date_of_nds(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw)
        {
            if (result.month == -1) {
                //Should have a month suffix
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            if (result.year != -1) {
                // Already has a year suffix
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            if (!omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(raw.get_number(0)), result.year)) {
                // the year value is of range
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            result.day = 1;
            return true;
        }

        bool get_date_of_nnds(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            // For partial CJK Dates, the only valid formats are with a specified year, followed by two numbers, which
            // will be the Month and Day, and with a specified Month, when the numbers are either the year and day or
            // day and year, depending on the short date pattern.

            if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_YEAR) != 0) {
                if (((result.flags & omni::internal::date_time_format::parse_flags::HAVE_MONTH) == 0) && ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DAY) == 0)) {
                    if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(raw.year), result.year) && omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(result.year), static_cast<uint16_t>(raw.get_number(0)), static_cast<uint16_t>(raw.get_number(1)))) {
                        return true;
                    }
                }
            } else if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_MONTH) != 0) {
                if (((result.flags & omni::internal::date_time_format::parse_flags::HAVE_YEAR) == 0) && ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DAY) == 0)) {
                    int64_t order;
                    if (!omni::internal::date_time_format::get_year_month_day_order(dtfi.short_date_pattern, dtfi, order)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadDatePattern");
                        return false;
                    }
                    int16_t year;
                    if (order == OMNI_DATE_INTERNAL_ORDER_YMD_FW) {
                        if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(raw.get_number(0)), year) && omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(year), static_cast<uint16_t>(result.month), static_cast<uint16_t>(raw.get_number(1)))) {
                            return true;
                        }
                    } else {
                        if (omni::internal::date_time_format::try_adjust_year(result, static_cast<int16_t>(raw.get_number(1)), year) && omni::internal::date_time_format::set_date_ymd(result, static_cast<uint16_t>(year), static_cast<uint16_t>(result.month), static_cast<uint16_t>(raw.get_number(0)))){
                            return true;
                        }
                    }
                }
            }
            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
            return false;
        }

        bool process_terminal_t_state(omni::internal::date_time_format::parse_state::enum_t dps, omni::internal::date_time_format::parse_result& result, omni::chrono::date_time_styles& styles, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::format_info& dtfi)
        {
            bool passed = true;
            switch (dps) {
                case omni::internal::date_time_format::parse_state::DX_NN:
                    passed = omni::internal::date_time_format::get_day_of_nn(result, styles, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_NNN:
                    passed = omni::internal::date_time_format::get_day_of_nnn(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_MN:
                    passed = omni::internal::date_time_format::get_day_of_mn(result, styles, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_NM:
                    passed = omni::internal::date_time_format::get_day_of_nm(result, styles, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_MNN:
                    passed = omni::internal::date_time_format::get_day_of_mnn(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_DS:
                    // The result has got the correct value. No need to process.
                    passed = true;
                    break;
                case omni::internal::date_time_format::parse_state::DX_YNN:
                    passed = omni::internal::date_time_format::get_day_of_ynn(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_NNY:
                    passed = omni::internal::date_time_format::get_day_of_nny(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_YMN:
                    passed = omni::internal::date_time_format::get_day_of_ymn(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_YN:
                    passed = omni::internal::date_time_format::get_day_of_yn(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::DX_YM:
                    passed = omni::internal::date_time_format::get_day_of_ym(result, raw, dtfi);
                    break;
                case omni::internal::date_time_format::parse_state::TX_N:
                    passed = omni::internal::date_time_format::get_time_of_n(result, raw);
                    break;
                case omni::internal::date_time_format::parse_state::TX_NN:
                    passed = omni::internal::date_time_format::get_time_of_nn(result, raw);
                    break;
                case parse_state::TX_NNN:
                    passed = omni::internal::date_time_format::get_time_of_nnn(result, raw);
                    break;
                case omni::internal::date_time_format::parse_state::TX_TS:
                    // The result has got the correct value. Nothing to do.
                    passed = true;
                    break;
                case omni::internal::date_time_format::parse_state::DX_DSN:
                    passed = omni::internal::date_time_format::get_date_of_dsn(result, raw);
                    break;
                case omni::internal::date_time_format::parse_state::DX_NDS:
                    passed = omni::internal::date_time_format::get_date_of_nds(result, raw);
                    break;
                case omni::internal::date_time_format::parse_state::DX_NNDS:
                    passed = omni::internal::date_time_format::get_date_of_nnds(result, raw, dtfi);
                    break;

                // explicit handling (avoid warnings)
                case omni::internal::date_time_format::parse_state::BEGIN:
                case omni::internal::date_time_format::parse_state::N:
                case omni::internal::date_time_format::parse_state::NN:
                case omni::internal::date_time_format::parse_state::D_Nd:
                case omni::internal::date_time_format::parse_state::D_NN:
                case omni::internal::date_time_format::parse_state::D_NNd:
                case omni::internal::date_time_format::parse_state::D_M:
                case omni::internal::date_time_format::parse_state::D_MN:
                case omni::internal::date_time_format::parse_state::D_NM:
                case omni::internal::date_time_format::parse_state::D_MNd:
                case omni::internal::date_time_format::parse_state::D_NDS:
                case omni::internal::date_time_format::parse_state::D_Y:
                case omni::internal::date_time_format::parse_state::D_YN:
                case omni::internal::date_time_format::parse_state::D_YNd:
                case omni::internal::date_time_format::parse_state::D_YM:
                case omni::internal::date_time_format::parse_state::D_YMd:
                case omni::internal::date_time_format::parse_state::D_S:
                case omni::internal::date_time_format::parse_state::T_S:
                case omni::internal::date_time_format::parse_state::T_Nt:
                case omni::internal::date_time_format::parse_state::T_NNt:
                case omni::internal::date_time_format::parse_state::ERR:
                default: break;
            }
            
            if (!passed) {
                return false;
            }

            if (dps > omni::internal::date_time_format::parse_state::ERR) {
                // We have reached a terminal state. Reset the raw num count.
                raw.num_count = 0;
            }
            return true;
        }

        bool verify_valid_punctuation(omni::internal::date_time_format::__dt_string& str)
        {
            // Compatibility Behavior. Allow trailing NULLs and surrounding hashes
            char ch = str.value[static_cast<std::size_t>(str.index)];
            if (ch == '#') {
                bool found_start = false;
                bool found_end = false;
                for (std::size_t i = 0; i < static_cast<std::size_t>(str.len); ++i) {
                    ch = str.value[i];
                    if (ch == '#') {
                        if (found_start) {
                            if (found_end) {
                                // Having more than two hashes is invalid
                                return false;
                            } else {
                                found_end = true;
                            }
                        } else {
                            found_start = true;
                        }
                    } else if (ch == '\0') {
                        // Allow NULLs only at the end
                        if (!found_end) {
                            return false;
                        }
                    } else if ((!omni::char_util::is_white_space(ch))) {
                        // Anything other than whitespace outside hashes is invalid
                        if (!found_start || found_end) {
                            return false;
                        }
                    }
                }
                if (!found_end) {
                    // The has was un-paired
                    return false;
                }
                // Valid Hash usage: eat the hash and continue.
                str.get_next();
                return true;
            } else if (ch == '\0') {
                for (std::size_t i = static_cast<std::size_t>(str.index); i < static_cast<std::size_t>(str.len); ++i) {
                    if (str.value[i] != '\0') {
                        // NULLs are only valid if they are the only trailing character
                        return false;
                    }
                }
                // Move to the end of the string
                str.index = str.len;
                return true;
            }
            return false;
        }

        #if defined(OMNI_DATE_TIME_PARSE_USE_STATE_ARRAY)
            omni::internal::date_time_format::parse_state::enum_t date_parsing_state_tokens[][18] = {
                // BEGIN
                {
                    omni::internal::date_time_format::parse_state::BEGIN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::TX_N,
                    omni::internal::date_time_format::parse_state::N,
                    omni::internal::date_time_format::parse_state::D_Nd,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_M,
                    omni::internal::date_time_format::parse_state::D_M,
                    omni::internal::date_time_format::parse_state::D_S,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::BEGIN,
                    omni::internal::date_time_format::parse_state::D_Y,
                    omni::internal::date_time_format::parse_state::D_Y,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::BEGIN,
                    omni::internal::date_time_format::parse_state::BEGIN,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // N
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::NN,
                    omni::internal::date_time_format::parse_state::D_NNd,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NM,
                    omni::internal::date_time_format::parse_state::D_NM,
                    omni::internal::date_time_format::parse_state::D_MNd,
                    omni::internal::date_time_format::parse_state::D_NDS,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::N,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::D_YNd,
                    omni::internal::date_time_format::parse_state::DX_YN,
                    omni::internal::date_time_format::parse_state::N,
                    omni::internal::date_time_format::parse_state::N,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // NN
                {
                    omni::internal::date_time_format::parse_state::DX_NN,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::TX_N,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::NN,
                    omni::internal::date_time_format::parse_state::DX_NNY,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NNY,
                    omni::internal::date_time_format::parse_state::NN,
                    omni::internal::date_time_format::parse_state::NN,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_Nd
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NN,
                    omni::internal::date_time_format::parse_state::D_NNd,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NM,
                    omni::internal::date_time_format::parse_state::D_MN,
                    omni::internal::date_time_format::parse_state::D_MNd,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_Nd,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::D_YNd,
                    omni::internal::date_time_format::parse_state::DX_YN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_Nd,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_NN
                {
                    omni::internal::date_time_format::parse_state::DX_NN,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::TX_N,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_DS,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::D_NN,
                    omni::internal::date_time_format::parse_state::DX_NNY,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NNY,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NN,
                    omni::internal::date_time_format::parse_state::ERR
                } ,
                // D_NNd
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::DX_NNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_DS,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NNd,
                    omni::internal::date_time_format::parse_state::DX_NNY,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_NNY,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NNd,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_M
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_MN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_MN,
                    omni::internal::date_time_format::parse_state::D_MNd,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_M,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::D_YMd,
                    omni::internal::date_time_format::parse_state::DX_YM,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_M,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_MN
                {
                    omni::internal::date_time_format::parse_state::DX_MN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_DS,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::D_MN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_MN,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_NM
                {
                    omni::internal::date_time_format::parse_state::DX_NM,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_DS,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::D_NM,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NM,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_MNd
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_MNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_MNd,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_MNd,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_NDS
                {
                    omni::internal::date_time_format::parse_state::DX_NDS,
                    omni::internal::date_time_format::parse_state::DX_NNDS,
                    omni::internal::date_time_format::parse_state::DX_NNDS,
                    omni::internal::date_time_format::parse_state::DX_NNDS,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NDS,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::D_NDS,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_NDS,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_Y
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::D_YNd,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YM,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::D_YMd,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_Y,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_Y,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_YN
                {
                    omni::internal::date_time_format::parse_state::DX_YN,
                    omni::internal::date_time_format::parse_state::DX_YNN,
                    omni::internal::date_time_format::parse_state::DX_YNN,
                    omni::internal::date_time_format::parse_state::DX_YNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_YNd
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YNN,
                    omni::internal::date_time_format::parse_state::DX_YNN,
                    omni::internal::date_time_format::parse_state::DX_YNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YN,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_YM
                {
                    omni::internal::date_time_format::parse_state::DX_YM,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_YMd
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::DX_YMN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_YM,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // D_S
                {
                    omni::internal::date_time_format::parse_state::DX_DS,
                    omni::internal::date_time_format::parse_state::DX_DSN,
                    omni::internal::date_time_format::parse_state::TX_N,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_S,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::D_S,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_S,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // T_S
                {
                    omni::internal::date_time_format::parse_state::TX_TS,
                    omni::internal::date_time_format::parse_state::TX_TS,
                    omni::internal::date_time_format::parse_state::TX_TS,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::D_Nd,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::D_S,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::ERR
                },
                // T_Nt
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::TX_NN,
                    omni::internal::date_time_format::parse_state::TX_NN,
                    omni::internal::date_time_format::parse_state::TX_NN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_NNt,
                    omni::internal::date_time_format::parse_state::DX_NM,
                    omni::internal::date_time_format::parse_state::D_NM,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::T_Nt,
                    omni::internal::date_time_format::parse_state::TX_NN
                },
                // T_NNt
                {
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::TX_NNN,
                    omni::internal::date_time_format::parse_state::TX_NNN,
                    omni::internal::date_time_format::parse_state::TX_NNN,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_S,
                    omni::internal::date_time_format::parse_state::T_NNt,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::ERR,
                    omni::internal::date_time_format::parse_state::T_NNt,
                    omni::internal::date_time_format::parse_state::T_NNt,
                    omni::internal::date_time_format::parse_state::TX_NNN
                },
            };
        #endif

        omni::internal::date_time_format::parse_state::enum_t date_parsing_state(const omni::internal::date_time_format::parse_state::enum_t& state, const omni::internal::date_time_format::token::enum_t& token)
        {
            /*
                DEV_NOTE: using the switch versus the array uses less static memory and also has built in error handling by having a default
                case if the values passed in are larger than one of the 2D array elements. Considering that this is entire code chunk is for
                a very large string parser for dates, one would likely be alright with the exceedingly small CPU cache hit the switch statement
                uses over the static memory.
                
                -- BUT --
                
                That's what the OMNI_DATE_TIME_PARSE_USE_STATE_ARRAY define is for .. let the user decide!
            */
            #if defined(OMNI_DATE_TIME_PARSE_USE_STATE_ARRAY)
                return omni::internal::date_time_format::date_parsing_state_tokens[static_cast<std::size_t>(state)][static_cast<std::size_t>(token)];
            #else
                switch (state) {
                    case omni::internal::date_time_format::parse_state::BEGIN: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::BEGIN;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_N;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::N;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::D_Nd;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::D_M;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::D_M;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::D_S;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::BEGIN;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::D_Y;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::D_Y;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::BEGIN;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::BEGIN;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::N: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_NN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::NN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::D_NNd;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_NM;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::D_NM;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::D_MNd;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::D_NDS;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::N;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::D_YNd;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_YN;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::N;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::N;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::NN: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_NN;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_N;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::NN;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::DX_NNY;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_NNY;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::NN;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::NN;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_Nd: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_NN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::D_NN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::D_NNd;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_NM;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::D_MN;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::D_MNd;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_Nd;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::D_YNd;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_YN;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_Nd;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_NN: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_NN;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_N;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::DX_DS;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_NN;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::DX_NNY;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_NNY;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_NN;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_NNd: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_NNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::DX_DS;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_NNd;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::DX_NNY;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_NNY;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_NNd;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_M: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_MN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::D_MN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::D_MNd;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_M;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::D_YMd;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_YM;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_M;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_MN: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_MN;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::DX_DS;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_MN;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_MN;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_NM: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_NM;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::DX_DS;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_NM;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_NM;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_MNd: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_MNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_MNd;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_MNd;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_NDS: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_NDS;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_NNDS;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_NNDS;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_NNDS;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::D_NDS;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_NDS;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_NDS;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_Y: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_YN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::D_YNd;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_YM;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::D_YMd;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_Y;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_Y;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_YN: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_YN;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_YNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_YNN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_YNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_YNd: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_YNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_YNN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_YNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_YN;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_YM: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_YM;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_YMd: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::DX_YMN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_YM;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::D_S: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::DX_DS;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::DX_DSN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_N;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::D_S;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::D_S;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::D_S;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::T_S: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::TX_TS;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::TX_TS;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_TS;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::D_Nd;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::D_S;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::T_Nt: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::TX_NN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_NN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::TX_NN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::T_NNt;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::DX_NM;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::D_NM;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::T_Nt;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK: return omni::internal::date_time_format::parse_state::TX_NN;
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;
                    case omni::internal::date_time_format::parse_state::T_NNt: {
                        switch (token) {
                            case omni::internal::date_time_format::token::END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_END: return omni::internal::date_time_format::parse_state::TX_NNN;
                            case omni::internal::date_time_format::token::NUM_AM_PM: return omni::internal::date_time_format::parse_state::TX_NNN;
                            case omni::internal::date_time_format::token::NUM_SPACE: return omni::internal::date_time_format::parse_state::TX_NNN;
                            case omni::internal::date_time_format::token::NUM_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::MONTH_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_DATE_SUFFIX: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::NUM_TIME_SUFFIX: return omni::internal::date_time_format::parse_state::T_S;
                            case omni::internal::date_time_format::token::DAY_OF_WEEK: return omni::internal::date_time_format::parse_state::T_NNt;
                            case omni::internal::date_time_format::token::YEAR_SPACE: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_DATE_SEP: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::YEAR_END: return omni::internal::date_time_format::parse_state::ERR;
                            case omni::internal::date_time_format::token::TIME_ZONE: return omni::internal::date_time_format::parse_state::T_NNt;
                            case omni::internal::date_time_format::token::ERA: return omni::internal::date_time_format::parse_state::T_NNt;
                            case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK: return omni::internal::date_time_format::parse_state::TX_NNN;
                            case omni::internal::date_time_format::token::UNKNOWN:
                            case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token::MAX:
                            default: return omni::internal::date_time_format::parse_state::ERR;
                        }
                    } break;

                    case omni::internal::date_time_format::parse_state::ERR:
                    case omni::internal::date_time_format::parse_state::DX_NN:
                    case omni::internal::date_time_format::parse_state::DX_NNN:
                    case omni::internal::date_time_format::parse_state::DX_MN:
                    case omni::internal::date_time_format::parse_state::DX_NM:
                    case omni::internal::date_time_format::parse_state::DX_MNN:
                    case omni::internal::date_time_format::parse_state::DX_DS:
                    case omni::internal::date_time_format::parse_state::DX_DSN:
                    case omni::internal::date_time_format::parse_state::DX_NDS:
                    case omni::internal::date_time_format::parse_state::DX_NNDS:
                    case omni::internal::date_time_format::parse_state::DX_YNN:
                    case omni::internal::date_time_format::parse_state::DX_YMN:
                    case omni::internal::date_time_format::parse_state::DX_YN:
                    case omni::internal::date_time_format::parse_state::DX_YM:
                    case omni::internal::date_time_format::parse_state::TX_N:
                    case omni::internal::date_time_format::parse_state::TX_NN:
                    case omni::internal::date_time_format::parse_state::TX_NNN:
                    case omni::internal::date_time_format::parse_state::TX_TS:
                    case omni::internal::date_time_format::parse_state::DX_NNY:
                    default: break;
                }
                return omni::internal::date_time_format::parse_state::ERR;
            #endif
        }

        // This is the lexer. Check the character at the current index, and put the found token in dtok and
        // some raw date/time information in raw.
        bool lex
        (
            omni::internal::date_time_format::parse_state::enum_t dps,
            omni::internal::date_time_format::__dt_string& str,
            omni::internal::date_time_format::date_time_token& dtok,
            omni::internal::date_time_format::date_time_raw_info& raw,
            omni::internal::date_time_format::parse_result& result,
            omni::internal::date_time_format::format_info& dtfi,
            omni::chrono::date_time_styles& styles
        ) {
            // https://learn.microsoft.com/en-us/dotnet/framework/configure-apps/file-schema/runtime/enableampmparseadjustment-element
            // enabled by default -- e.g. 4/10 6am == April 10, YYYY @ 6am
            bool enable_am_pm_parse_adjustment = true;
            omni::internal::date_time_format::token_type::enum_t token_type = omni::internal::date_time_format::token_type::SEP_UNK;
            int64_t token_value = 0;
            int64_t index_before_sep = 0;
            char char_before_sep = '\0';

            omni::internal::date_time_format::token_type::enum_t sep = omni::internal::date_time_format::token_type::SEP_UNK;
            dtok.dtt = omni::internal::date_time_format::token::UNKNOWN; // Assume the token is unkown.

            str.get_regular_token(token_type, token_value, dtfi, false);

            // Look at the regular token.
            switch (token_type) {
                case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN: {
                    if (raw.num_count == 3 || token_value == -1) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    /*
                        This is a digit.

                        If the previous parsing state is omni::internal::date_time_format::parse_state::T_NNt (like 12:01), and we got another number,
                        so we will have a terminal state omni::internal::date_time_format::parse_state::TX_NNN (like 12:01:02).
                        If the previous parsing state is omni::internal::date_time_format::parse_state::T_Nt (like 12:), and we got another number,
                        so we will have a terminal state omni::internal::date_time_format::parse_state::TX_NN (like 12:01).

                        Look ahead to see if the following character is a decimal point or timezone offset.
                        This enables us to parse time in the forms of: "11:22:33.1234" or "11:22:33-08".
                    */
                    if (dps == omni::internal::date_time_format::parse_state::T_NNt) {
                        if ((str.index < str.len - 1)) {
                            char next_ch = str.value[static_cast<std::size_t>(str.index)];
                            if (next_ch == '.') {
                                // While parse_fraction can fail, it just means that there were no digits after
                                // the dot. In this case parse_fraction just removes the dot. This is actually
                                // valid for cultures like Albanian, that join the time marker to the time with
                                // with a dot: e.g. "9:03.MD"
                                omni::internal::date_time_format::parse_fraction(str, raw.fraction);
                            }
                        }
                    }
                    if (dps == omni::internal::date_time_format::parse_state::T_NNt || dps == omni::internal::date_time_format::parse_state::T_Nt) {
                        if ((str.index < str.len - 1)) {
                            if (!omni::internal::date_time_format::handle_time_zone(str, result)) {
                                return false;
                            }
                        }
                    }

                    dtok.num = token_value;
                    if (token_type == omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN) {
                        if (raw.year == -1) {
                            raw.year = token_value;
                            // If we have number which has 3 or more digits (like "001" or "0001"), we assume this number is a year. Save the current raw.num_count in raw.year
                            switch (sep = str.get_separator_token(dtfi, index_before_sep, char_before_sep)) {
                                case omni::internal::date_time_format::token_type::SEP_END: {
                                    dtok.dtt = omni::internal::date_time_format::token::YEAR_END;
                                } break;
                                case omni::internal::date_time_format::token_type::SEP_AM:
                                case omni::internal::date_time_format::token_type::SEP_PM: {
                                    if (raw.time_mark == omni::internal::date_time_format::time_mark::NOT_SET) {
                                        raw.time_mark = (sep == omni::internal::date_time_format::token_type::SEP_AM ? time_mark::AM : time_mark::PM);
                                        dtok.dtt = omni::internal::date_time_format::token::YEAR_SPACE;
                                    } else {
                                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    }
                                } break;
                                case omni::internal::date_time_format::token_type::SEP_SPACE:
                                    dtok.dtt = omni::internal::date_time_format::token::YEAR_SPACE;
                                    break;
                                case omni::internal::date_time_format::token_type::SEP_Date:
                                    dtok.dtt = omni::internal::date_time_format::token::YEAR_DATE_SEP;
                                    break;
                                case omni::internal::date_time_format::token_type::SEP_TIME: {
                                    if (!raw.has_same_date_and_time_separators) {
                                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                        return false;
                                    }
                                    // we have the date and time separators are same and getting a year number, then change the token to YEAR_DATE_SEP as
                                    // we are sure we are not parsing time.
                                    dtok.dtt = omni::internal::date_time_format::token::YEAR_DATE_SEP;
                                } break;
                                case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET: {
                                    // The separator is either a date separator or the start of a time zone offset. If the token will complete the date then
                                    // process just the number and roll back the index so that the outer loop can attempt to parse the time zone offset.
                                    if ((omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::YEAR_DATE_SEP) == omni::internal::date_time_format::parse_state::ERR) &&
                                        (omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::YEAR_SPACE) > omni::internal::date_time_format::parse_state::ERR))
                                    {
                                        str.index = index_before_sep;
                                        str.current_char = char_before_sep;
                                        dtok.dtt = omni::internal::date_time_format::token::YEAR_SPACE;
                                    } else {
                                        dtok.dtt = omni::internal::date_time_format::token::YEAR_DATE_SEP;
                                    }
                                } break;
                                case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX:
                                    dtok.dtt    = omni::internal::date_time_format::token::NUM_DATE_SUFFIX;
                                    dtok.suffix = sep;
                                    break;
                                case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX:
                                    dtok.dtt    = omni::internal::date_time_format::token::NUM_TIME_SUFFIX;
                                    dtok.suffix = sep;
                                    break;
                                case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                                case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN:
                                case omni::internal::date_time_format::token_type::AM:
                                case omni::internal::date_time_format::token_type::PM:
                                case omni::internal::date_time_format::token_type::MONTH_TOKEN:
                                case omni::internal::date_time_format::token_type::END_OF_STRING:
                                case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN:
                                case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN:
                                case omni::internal::date_time_format::token_type::ERA_TOKEN:
                                case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                                case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN:
                                case omni::internal::date_time_format::token_type::HEBREW_NUMBER:
                                case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN:
                                case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN:
                                case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL:
                                case omni::internal::date_time_format::token_type::SEP_UNK:
                                case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                                case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                                case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                                default:
                                    // Invalid separator after number number.
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                            }
                            // Found the token already. Return now.
                            return true;
                        }
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }

                    switch (sep = str.get_separator_token(dtfi, index_before_sep, char_before_sep)) {
                        /*
                            Note here we check if the num_count is less than three.
                            When we have more than three numbers, it will be caught as error in the state machine.
                        */
                        case omni::internal::date_time_format::token_type::SEP_END:
                            dtok.dtt = omni::internal::date_time_format::token::NUM_END;
                            raw.add_number(dtok.num);
                            break;
                        case omni::internal::date_time_format::token_type::SEP_AM:
                        case omni::internal::date_time_format::token_type::SEP_PM: {
                            if (raw.time_mark == omni::internal::date_time_format::time_mark::NOT_SET) {
                                raw.time_mark = (sep == omni::internal::date_time_format::token_type::SEP_AM ? time_mark::AM : time_mark::PM);
                                dtok.dtt = omni::internal::date_time_format::token::NUM_AM_PM;
                                // Fix AM/PM parsing case, e.g. "1/10 5 AM"
                                if (dps == omni::internal::date_time_format::parse_state::D_NN && enable_am_pm_parse_adjustment) {
                                    if (!omni::internal::date_time_format::process_terminal_t_state(omni::internal::date_time_format::parse_state::DX_NN, result, styles, raw, dtfi)) {
                                        return false;
                                    }
                                }
                                raw.add_number(dtok.num);
                            } else {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                break;
                            }
                            if (dps == omni::internal::date_time_format::parse_state::T_NNt || dps == omni::internal::date_time_format::parse_state::T_Nt) {
                                if (!omni::internal::date_time_format::handle_time_zone(str, result)) {
                                    return false;
                                }
                            }
                        } break;
                        case omni::internal::date_time_format::token_type::SEP_SPACE:
                            dtok.dtt = omni::internal::date_time_format::token::NUM_SPACE;
                            raw.add_number(dtok.num);
                            break;
                        case omni::internal::date_time_format::token_type::SEP_Date:
                            dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SEP;
                            raw.add_number(dtok.num);
                            break;
                        case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET:
                            // The separator is either a date separator or the start of a time zone offset. If the token will complete the date then
                            // process just the number and roll back the index so that the outer loop can attempt to parse the time zone offset.
                            if ((omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::NUM_DATE_SEP) == omni::internal::date_time_format::parse_state::ERR)
                                && (omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::NUM_SPACE) > omni::internal::date_time_format::parse_state::ERR)) {
                                str.index = index_before_sep;
                                str.current_char = char_before_sep;
                                dtok.dtt = omni::internal::date_time_format::token::NUM_SPACE;
                            } else {
                                dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SEP;
                            }
                            raw.add_number(dtok.num);
                            break;
                        case omni::internal::date_time_format::token_type::SEP_TIME:
                            if (raw.has_same_date_and_time_separators &&
                                (dps == omni::internal::date_time_format::parse_state::D_Y || dps == omni::internal::date_time_format::parse_state::D_YN || dps == omni::internal::date_time_format::parse_state::D_YNd || dps == omni::internal::date_time_format::parse_state::D_YM || dps == omni::internal::date_time_format::parse_state::D_YMd))
                            {
                                // we are parsing a date and we have the time separator same as date separator, so we mark the token as date separator
                                dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SEP;
                                raw.add_number(dtok.num);
                                break;
                            }
                            dtok.dtt = omni::internal::date_time_format::token::NUM_TIME_SEP;
                            raw.add_number(dtok.num);
                            break;
                        case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX: {
                            if ((token_value < 1) || (token_value > OMNI_DATE_MAX_YEAR)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                            dtok.num = omni::chrono::date_time::to_four_digit_year(static_cast<uint16_t>(token_value));
                            dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SUFFIX;
                            dtok.suffix = sep;
                        } break;
                        case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX:
                        case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX:
                            dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SUFFIX;
                            dtok.suffix = sep;
                            break;
                        case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX:
                        case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX:
                        case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX:
                            dtok.dtt = omni::internal::date_time_format::token::NUM_TIME_SUFFIX;
                            dtok.suffix = sep;
                            break;
                        case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                            dtok.dtt = omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK;
                            raw.add_number(dtok.num);
                            break;
                        case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                        case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN:
                        case omni::internal::date_time_format::token_type::AM:
                        case omni::internal::date_time_format::token_type::PM:
                        case omni::internal::date_time_format::token_type::MONTH_TOKEN:
                        case omni::internal::date_time_format::token_type::END_OF_STRING:
                        case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN:
                        case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN:
                        case omni::internal::date_time_format::token_type::ERA_TOKEN:
                        case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                        case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN:
                        case omni::internal::date_time_format::token_type::HEBREW_NUMBER:
                        case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN:
                        case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN:
                        case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL:
                        case omni::internal::date_time_format::token_type::SEP_UNK:
                        case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                        case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                        default:
                            // Invalid separator after number number.
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::HEBREW_NUMBER: {
                    if (token_value >= 100) {
                        // This is a year number
                        if (raw.year == -1) {
                            raw.year = token_value;
                            //
                            // If we have number which has 3 or more digits (like "001" or "0001"),
                            // we assume this number is a year. Save the current raw.num_count in
                            // raw.year.
                            //
                            switch (sep = str.get_separator_token(dtfi, index_before_sep, char_before_sep)) {
                                case omni::internal::date_time_format::token_type::SEP_END:
                                    dtok.dtt = omni::internal::date_time_format::token::YEAR_END;
                                    break;
                                case omni::internal::date_time_format::token_type::SEP_SPACE:
                                    dtok.dtt = omni::internal::date_time_format::token::YEAR_SPACE;
                                    break;
                                case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET: {
                                    // The separator is either a date separator or the start of a time zone offset. If the token will complete the date then
                                    // process just the number and roll back the index so that the outer loop can attempt to parse the time zone offset.
                                    if (omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::YEAR_SPACE) > omni::internal::date_time_format::parse_state::ERR) {
                                        str.index = index_before_sep;
                                        str.current_char = char_before_sep;
                                        dtok.dtt = omni::internal::date_time_format::token::YEAR_SPACE;
                                        break;
                                    }
                                    return false;
                                } break;
                                case omni::internal::date_time_format::token_type::SEP_AM:
                                case omni::internal::date_time_format::token_type::SEP_PM:
                                case omni::internal::date_time_format::token_type::SEP_Date:
                                case omni::internal::date_time_format::token_type::SEP_TIME:
                                case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX:
                                case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                                case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                                case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN:
                                case omni::internal::date_time_format::token_type::AM:
                                case omni::internal::date_time_format::token_type::PM:
                                case omni::internal::date_time_format::token_type::MONTH_TOKEN:
                                case omni::internal::date_time_format::token_type::END_OF_STRING:
                                case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN:
                                case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN:
                                case omni::internal::date_time_format::token_type::ERA_TOKEN:
                                case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                                case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN:
                                case omni::internal::date_time_format::token_type::HEBREW_NUMBER:
                                case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN:
                                case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN:
                                case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL:
                                case omni::internal::date_time_format::token_type::SEP_UNK:
                                case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                                case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                                default:
                                    // Invalid separator after number number.
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                            }
                        } else {
                            // Invalid separator after number number.
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    } else {
                        // This is a day number
                        dtok.num = token_value;
                        raw.add_number(dtok.num);

                        switch (sep = str.get_separator_token(dtfi, index_before_sep, char_before_sep)) {
                            // Note here we check if the num_count is less than three.
                            // When we have more than three numbers, it will be caught as error in the state machine.
                            case omni::internal::date_time_format::token_type::SEP_END:
                                dtok.dtt = omni::internal::date_time_format::token::NUM_END;
                                break;
                            case omni::internal::date_time_format::token_type::SEP_SPACE:
                            case omni::internal::date_time_format::token_type::SEP_Date:
                                dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SEP;
                                break;
                            case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET: {
                                // The separator is either a date separator or the start of a time zone offset. If the token will complete the date then
                                // process just the number and roll back the index so that the outer loop can attempt to parse the time zone offset.
                                if ((omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::NUM_DATE_SEP) == omni::internal::date_time_format::parse_state::ERR)
                                    && (omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::NUM_SPACE) > omni::internal::date_time_format::parse_state::ERR)) {
                                    str.index = index_before_sep;
                                    str.current_char = char_before_sep;
                                    dtok.dtt = omni::internal::date_time_format::token::NUM_SPACE;
                                } else {
                                    dtok.dtt = omni::internal::date_time_format::token::NUM_DATE_SEP;
                                }
                            } break;

                            case omni::internal::date_time_format::token_type::SEP_AM:
                            case omni::internal::date_time_format::token_type::SEP_PM:
                            case omni::internal::date_time_format::token_type::SEP_TIME:
                            case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                            case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN:
                            case omni::internal::date_time_format::token_type::AM:
                            case omni::internal::date_time_format::token_type::PM:
                            case omni::internal::date_time_format::token_type::MONTH_TOKEN:
                            case omni::internal::date_time_format::token_type::END_OF_STRING:
                            case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN:
                            case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN:
                            case omni::internal::date_time_format::token_type::ERA_TOKEN:
                            case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                            case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN:
                            case omni::internal::date_time_format::token_type::HEBREW_NUMBER:
                            case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN:
                            case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN:
                            case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL:
                            case omni::internal::date_time_format::token_type::SEP_UNK:
                            case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                            case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                            default:
                                // Invalid separator after number number.
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                        }
                    }
                } break;
                case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN: {
                    if (raw.day_of_week == -1) {
                        // This is a day of week name.
                        raw.day_of_week = token_value;
                        dtok.dtt = omni::internal::date_time_format::token::DAY_OF_WEEK;
                    } else {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::MONTH_TOKEN: {
                    if (raw.month == -1) {
                        // This is a month name
                        sep = str.get_separator_token(dtfi, index_before_sep, char_before_sep);
                        switch (sep) {
                            case omni::internal::date_time_format::token_type::SEP_END: {
                                dtok.dtt = omni::internal::date_time_format::token::MONTH_END;
                            } break;
                            case omni::internal::date_time_format::token_type::SEP_SPACE: {
                                dtok.dtt = omni::internal::date_time_format::token::MONTH_SPACE;
                            } break;
                            case omni::internal::date_time_format::token_type::SEP_Date: {
                                dtok.dtt = omni::internal::date_time_format::token::MONTH_DATE_SEP;
                            } break;
                            case omni::internal::date_time_format::token_type::SEP_TIME: {
                                if (!raw.has_same_date_and_time_separators) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                                // we have the date and time separators are same and getting a Month name, then change the token to MONTH_DATE_SEP as
                                // we are sure we are not parsing time.
                                dtok.dtt = omni::internal::date_time_format::token::MONTH_DATE_SEP;
                            } break;
                            case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET: {
                                // The separator is either a date separator or the start of a time zone offset. If the token will complete the date then
                                // process just the number and roll back the index so that the outer loop can attempt to parse the time zone offset.
                                if ((omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::MONTH_DATE_SEP) == omni::internal::date_time_format::parse_state::ERR)
                                    && (omni::internal::date_time_format::date_parsing_state(dps, omni::internal::date_time_format::token::MONTH_SPACE) > omni::internal::date_time_format::parse_state::ERR)) {
                                    str.index = index_before_sep;
                                    str.current_char = char_before_sep;
                                    dtok.dtt = omni::internal::date_time_format::token::MONTH_SPACE;
                                } else {
                                    dtok.dtt = omni::internal::date_time_format::token::MONTH_DATE_SEP;
                                }
                            } break;

                            case omni::internal::date_time_format::token_type::SEP_AM:
                            case omni::internal::date_time_format::token_type::SEP_PM:
                            case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX:
                            case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                            case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                            case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN:
                            case omni::internal::date_time_format::token_type::AM:
                            case omni::internal::date_time_format::token_type::PM:
                            case omni::internal::date_time_format::token_type::MONTH_TOKEN:
                            case omni::internal::date_time_format::token_type::END_OF_STRING:
                            case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN:
                            case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN:
                            case omni::internal::date_time_format::token_type::ERA_TOKEN:
                            case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                            case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN:
                            case omni::internal::date_time_format::token_type::HEBREW_NUMBER:
                            case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN:
                            case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN:
                            case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL:
                            case omni::internal::date_time_format::token_type::SEP_UNK:
                            case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                            case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                            default:
                                //Invalid separator after month name
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                        }
                        raw.month = token_value;
                    }  else {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime"); 
                        return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::ERA_TOKEN: {
                    if (result.era != -1) {
                        result.era = static_cast<int16_t>(token_value);
                        dtok.dtt = omni::internal::date_time_format::token::ERA;
                    } else {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN: {
                    // Special case for Japanese.  We allow Japanese era name to be used even if the calendar is not Japanese Calendar.
                    if (result.era != -1) {
                        result.era = static_cast<int16_t>(token_value);
                        dtok.dtt = omni::internal::date_time_format::token::ERA;
                    } else {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN: {
                    if (result.era != -1) {
                        result.era = static_cast<int16_t>(token_value);
                        dtok.dtt = omni::internal::date_time_format::token::ERA;
                    } else {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        
                        return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN: {
                    // This is a timezone designator
                    // DEV_NOTE : for now, we only support "GMT" and "Z" (for Zulu time).
                    if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0) {
                        // Should not have two timezone offsets.
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    dtok.dtt = omni::internal::date_time_format::token::TIME_ZONE;
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                    result.time_zone_offset = omni::chrono::time_span(0);
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_UTC);
                } break;
                case omni::internal::date_time_format::token_type::END_OF_STRING: {
                    dtok.dtt = omni::internal::date_time_format::token::END;
                } break;
                case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL: {
                    // Date words and ignorable symbols can just be skipped over
                } break;
                case omni::internal::date_time_format::token_type::AM:
                case omni::internal::date_time_format::token_type::PM: {
                    if (raw.time_mark == omni::internal::date_time_format::time_mark::NOT_SET) {
                        raw.time_mark = static_cast<omni::internal::date_time_format::time_mark::enum_t>(token_value);
                    } else {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                } break;
                case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN: {
                    if (omni::char_util::is_letter(str.current_char)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_UnknowDateTimeWord");
                        return false;
                    }
                    if (((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) == 0)) {
                        str.get_next();
                        return true;
                    }

                    if ((str.current_char == '-' || str.current_char == '+') && ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) == 0)) {
                        int32_t originalIndex = static_cast<int32_t>(str.index);
                        if (omni::internal::date_time_format::parse_time_zone(str, result.time_zone_offset)) {
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                            return true;
                        }
                        else {
                            // Time zone parse attempt failed. Fall through to punctuation handling.
                            str.index = originalIndex;
                        }
                    }
                    if (omni::internal::date_time_format::verify_valid_punctuation(str)) {
                        return true;
                    }

                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                    return false;
                } break;

                // explicit handling (avoid warnings)
                case omni::internal::date_time_format::token_type::SEP_UNK:
                case omni::internal::date_time_format::token_type::SEP_END:
                case omni::internal::date_time_format::token_type::SEP_SPACE:
                case omni::internal::date_time_format::token_type::SEP_AM:
                case omni::internal::date_time_format::token_type::SEP_PM:
                case omni::internal::date_time_format::token_type::SEP_Date:
                case omni::internal::date_time_format::token_type::SEP_TIME:
                case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX:
                case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX:
                case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX:
                case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX:
                case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX:
                case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX:
                case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET:
                case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                default: break;
            }

            
            return true;
        }

        // A date suffix is found, use this method to put the number into the result.
        bool process_date_time_suffix(omni::internal::date_time_format::parse_result& result, omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::date_time_token& dtok)
        {
            switch (dtok.suffix) {
                case omni::internal::date_time_format::token_type::SEP_YEAR_SUFFIX: {
                    if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_YEAR) != 0) {
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_YEAR);
                    result.year = static_cast<int16_t>(dtok.num);
                    raw.year = dtok.num;
                } break;
                case omni::internal::date_time_format::token_type::SEP_MONTH_SUFFIX: {
                    if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_MONTH) != 0) {
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_MONTH);
                    result.month = static_cast<int16_t>(dtok.num);
                    raw.month = dtok.num;
                } break;
                case omni::internal::date_time_format::token_type::SEP_DAY_SUFFIX: {
                    if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_DAY) != 0) {
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_DAY);
                    result.day = static_cast<int16_t>(dtok.num);
                } break;
                case omni::internal::date_time_format::token_type::SEP_HOUR_SUFFIX: {
                    if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_HOUR) != 0) {
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_HOUR);
                    result.hour = static_cast<int16_t>(dtok.num);
                } break;
                case omni::internal::date_time_format::token_type::SEP_MINUTE_SUFFIX: {
                    if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_MINUTE) != 0) {
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_MINUTE);
                    result.minute = static_cast<int16_t>(dtok.num);
                } break;
                case omni::internal::date_time_format::token_type::SEP_SECOND_SUFFIX: {
                    if ((result.flags & omni::internal::date_time_format::parse_flags::HAVE_SECOND) != 0) {
                        return false;
                    }
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::HAVE_SECOND);
                    result.second = static_cast<int16_t>(dtok.num);
                } break;

                // explicitly handle these (avoid warnings)
                case omni::internal::date_time_format::token_type::NUMBER_TOKEN:
                case omni::internal::date_time_format::token_type::YEAR_NUMBER_TOKEN:
                case omni::internal::date_time_format::token_type::AM:
                case omni::internal::date_time_format::token_type::PM:
                case omni::internal::date_time_format::token_type::MONTH_TOKEN:
                case omni::internal::date_time_format::token_type::END_OF_STRING:
                case omni::internal::date_time_format::token_type::DAY_OF_WEEK_TOKEN:
                case omni::internal::date_time_format::token_type::TIME_ZONE_TOKEN:
                case omni::internal::date_time_format::token_type::ERA_TOKEN:
                case omni::internal::date_time_format::token_type::DATE_WORD_TOKEN:
                case omni::internal::date_time_format::token_type::UNKNOWN_TOKEN:
                case omni::internal::date_time_format::token_type::HEBREW_NUMBER:
                case omni::internal::date_time_format::token_type::JAPANESE_ERA_TOKEN:
                case omni::internal::date_time_format::token_type::TAIWAN_ERA_TOKEN:
                case omni::internal::date_time_format::token_type::IGNORABLE_SYMBOL:
                case omni::internal::date_time_format::token_type::SEP_UNK:
                case omni::internal::date_time_format::token_type::SEP_END:
                case omni::internal::date_time_format::token_type::SEP_SPACE:
                case omni::internal::date_time_format::token_type::SEP_AM:
                case omni::internal::date_time_format::token_type::SEP_PM:
                case omni::internal::date_time_format::token_type::SEP_Date:
                case omni::internal::date_time_format::token_type::SEP_TIME:
                case omni::internal::date_time_format::token_type::SEP_LOCAL_TIME_MARK:
                case omni::internal::date_time_format::token_type::SEP_DATE_OR_OFFSET:
                case omni::internal::date_time_format::token_type::REGULAR_TOKEN_MASK:
                case omni::internal::date_time_format::token_type::SEPARATOR_TOKEN_MASK:
                default: break;
            }
            return true;
        }

        void adjust_time_mark(omni::internal::date_time_format::format_info& dtfi, omni::internal::date_time_format::date_time_raw_info& raw)
        {
            // Special case for culture which uses AM as empty string.
            // E.g. af-ZA (0x0436)
            //    S1159                  \x0000
            //    S2359                  nm
            // In this case, if we are parsing a string like "2005/09/14 12:23", we will assume this is in AM.

            if (raw.time_mark == omni::internal::date_time_format::time_mark::NOT_SET) {
                if (!dtfi.am_designator.empty() && !dtfi.pm_designator.empty()) {
                    if (dtfi.am_designator.size() == 0 && dtfi.pm_designator.size() != 0) {
                        raw.time_mark = omni::internal::date_time_format::time_mark::AM;
                    }
                    if (dtfi.pm_designator.size() == 0 && dtfi.am_designator.size() != 0) {
                        raw.time_mark = omni::internal::date_time_format::time_mark::PM;
                    }
                }
            }
        }

        bool check_default_date_time(omni::internal::date_time_format::parse_result& result, const omni::chrono::date_time_styles& styles)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) {
                /*
                    DateTimeOffset.Parse should allow dates without a year, but only if there is also no time zone marker;
                    e.g. "May 1 5pm" is OK, but "May 1 5pm -08:30" is not.  This is somewhat pragmatic, since we would
                    have to re-architect parsing completely to allow this one case to correctly handle things like leap
                    years and leap months.  Is is an extremely corner case, and DateTime is basically incorrect in that
                    case today.
                    
                    values like "11:00Z" or "11:00 -3:00" are also acceptable
                    
                    if ((month or day is set) and (year is not set and time zone is set))
                */
                if (((result.month != -1) || (result.day != -1))
                    && ((result.year == -1 || ((result.flags & omni::internal::date_time_format::parse_flags::YEAR_DEFAULT) != 0)) && (result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0))
                {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_MissingIncompleteDate");
                    return false;
                }
            }

            if ((result.year == -1) || (result.month == -1) || (result.day == -1)) {
                /*
                    The following table describes the behaviors of getting the default value
                    when a certain year/month/day values are missing.

                    An "X" means that the value exists.  And "--" means that value is missing.

                    Year    Month   Day =>  ResultYear  ResultMonth     ResultDay       Note

                    X       X       X       Parsed year Parsed month    Parsed day
                    X       X       --      Parsed Year Parsed month    First day       If we have year and month, assume the first day of that month.
                    X       --      X       Parsed year First month     Parsed day      If the month is missing, assume first month of that year.
                    X       --      --      Parsed year First month     First day       If we have only the year, assume the first day of that year.

                    --      X       X       CurrentYear Parsed month    Parsed day      If the year is missing, assume the current year.
                    --      X       --      CurrentYear Parsed month    First day       If we have only a month value, assume the current year and current day.
                    --      --      X       CurrentYear First month     Parsed day      If we have only a day value, assume current year and first month.
                    --      --      --      CurrentYear Current month   Current day     So this means that if the date string only contains time, you will get current date.

                */

                omni::chrono::date_time now = omni::internal::date_time_format::get_date_time_now(result, styles);
                if (result.month == -1 && result.day == -1) {
                    if (result.year == -1) {
                        if ((styles & omni::chrono::date_time_styles::NO_CURRENT_DATE_DEFAULT) != 0) {
                            // If there is no year/month/day values, and NoCurrentDateDefault flag is used,
                            // set the year/month/day value to the beginning year/month/day of DateTime().
                            // Note we should be using Gregorian for the year/month/day.
                            // cal = GregorianCalendar.GetDefaultInstance();
                            result.year = result.month = result.day = 1;
                        } else {
                            // Year/Month/Day are all missing.
                            result.year = static_cast<int16_t>(now.year()); // cal.GetYear(now);
                            result.month = static_cast<int16_t>(now.month()); // cal.GetMonth(now);
                            result.day = static_cast<int16_t>(now.day()); // cal.GetDayOfMonth(now);
                        }
                    } else {
                        // Month/Day are both missing.
                        result.month = 1;
                        result.day = 1;
                    }
                } else {
                    if (result.year == -1) {
                        result.year = static_cast<int16_t>(now.year()); // cal.GetYear(now);
                    }
                    if (result.month == -1) {
                        result.month = 1;
                    }
                    if (result.day == -1) {
                        result.day = 1;
                    }
                }
            }
            // Set Hour/Minute/Second to zero if these value are not in str.
            if (result.hour   == -1) { result.hour = 0; }
            if (result.minute == -1) { result.minute = 0; }
            if (result.second == -1) { result.second = 0; }
            if (result.era == -1) { result.era = 0; }
            return true;
        }

        // Adjust the specified time to universal time based on the supplied timezone.
        // E.g. when parsing "2001/06/08 14:00-07:00",
        // the time is 2001/06/08 14:00, and time_zone_offset = -07:00.
        // The result will be "2001/06/08 21:00"
        bool adjust_time_zone_to_universal(omni::internal::date_time_format::parse_result& result)
        {
            int64_t result_ticks = static_cast<int64_t>(result.parsed_date.ticks());
            result_ticks -= result.time_zone_offset.ticks();
            if (result_ticks < 0) {
                result_ticks += OMNI_TICKS_PER_DAY; // OMNI_TICKS_PER_DAY;
            }

            if (static_cast<uint64_t>(result_ticks) < omni::chrono::date_time::min_ticks() || static_cast<uint64_t>(result_ticks) > omni::chrono::date_time::max_ticks()) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_DateOutOfRange");
                return false;
            }
            result.parsed_date = omni::chrono::date_time(static_cast<uint64_t>(result_ticks), omni::chrono::date_time_kind::UTC);
            return true;
        }

        bool adjust_time_zone_to_local(omni::internal::date_time_format::parse_result& result, bool is_time_only)
        {
            int64_t result_ticks = static_cast<int64_t>(result.parsed_date.ticks());
            // Convert to local ticks
            // TimeZoneInfo tz = TimeZoneInfo.Local;
            // bool isAmbiguousLocalDst = false;
            if (result_ticks < OMNI_TICKS_PER_DAY) {
                // This is time of day.

                // Adjust timezone.
                result_ticks -= result.time_zone_offset.ticks();
                // If the time is time of day, use the current timezone offset.
                result_ticks += (is_time_only ? omni::chrono::date_time::now() : result.parsed_date).ticks();

                if (result_ticks < 0) {
                    result_ticks += OMNI_TICKS_PER_DAY;
                }
            } else {
                // Adjust timezone to GMT.
                result_ticks -= result.time_zone_offset.ticks();
                if (static_cast<uint64_t>(result_ticks) < omni::chrono::date_time::min_ticks() || static_cast<uint64_t>(result_ticks) > omni::chrono::date_time::max_ticks()) {
                    // If the result ticks is greater than DateTime.MaxValue, we can not create a DateTime from this ticks.
                    // In this case, keep using the old code.
                    result_ticks += result.parsed_date.utc_offset().ticks();
                } else {
                    // Convert the GMT time to local time.
                    omni::chrono::date_time utc_dt(static_cast<uint64_t>(result_ticks), omni::chrono::date_time_kind::LOCAL);
                    result_ticks += utc_dt.utc_offset().ticks();
                    if (utc_dt.is_dst()) {
                        result_ticks += OMNI_TICKS_PER_HOUR;
                    }
                }
            }
            if (static_cast<uint64_t>(result_ticks) < omni::chrono::date_time::min_ticks() || static_cast<uint64_t>(result_ticks) > omni::chrono::date_time::max_ticks()) {
                result.parsed_date = omni::chrono::date_time::min_value();
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_DateOutOfRange");
                return false;
            }
            result.parsed_date = omni::chrono::date_time(static_cast<uint64_t>(result_ticks), omni::chrono::date_time_kind::LOCAL); //, isAmbiguousLocalDst);
            return true;
        }

        // Apply validation and adjustments specific to DateTimeOffset
        bool date_time_offset_time_zone_post_processing(omni::internal::date_time_format::parse_result& result, const omni::chrono::date_time_styles& styles)
        {
            // For DateTimeOffset, default to the Utc or Local offset when an offset was not specified by the input string.
            if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) == 0) {
                if ((styles & omni::chrono::date_time_styles::ASSUME_UNIVERSAL) != 0) {
                    // AssumeUniversal causes the offset to default to zero (0)
                    result.time_zone_offset = omni::chrono::time_span::zero();
                }
                else {
                    // AssumeLocal causes the offset to default to Local.  This flag is on by default for DateTimeOffset.
                    result.time_zone_offset = result.parsed_date.utc_offset();
                }
            }

            int64_t offset_ticks = result.time_zone_offset.ticks();
            // there should be no overflow, because the offset can be no more than -+100 hours and the date already fits within a DateTime.
            int64_t utc_ticks = static_cast<int64_t>(result.parsed_date.ticks()) - offset_ticks;

            // For DateTimeOffset, both the parsed time and the corresponding UTC value must be within the boundaries of a DateTime instance.
            if (static_cast<uint64_t>(utc_ticks) < omni::chrono::date_time::min_ticks() || static_cast<uint64_t>(utc_ticks) > omni::chrono::date_time::max_ticks()) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_UTCOutOfRange");
                return false;
            }

            // the offset must be within +- 14:00 hours.
            if (offset_ticks < OMNI_DATE_INTERNAL_MIN_OFFSET_FW || offset_ticks > OMNI_DATE_INTERNAL_MAX_OFFSET_FW) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_OffsetOutOfRange");
                return false;
            }

            // DateTimeOffset should still honor the AdjustToUniversal flag for consistency with DateTime. It means you
            // want to return an adjusted UTC value, so store the utc_ticks in the DateTime and set the offset to zero
            if ((styles & omni::chrono::date_time_styles::ADJUST_TO_UNIVERSAL) != 0) {
                if (((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) == 0) && ((styles & omni::chrono::date_time_styles::ASSUME_UNIVERSAL) == 0)) {
                    // Handle the special case where the time_zone_offset was defaulted to Local
                    bool toUtcResult = omni::internal::date_time_format::adjust_time_zone_to_universal(result);
                    result.time_zone_offset = omni::chrono::time_span::zero();
                    return toUtcResult;
                }

                // The constructor should always succeed because of the range check earlier in the function
                // Although it is UTC, internally DateTimeOffset does not use this flag
                result.parsed_date = omni::chrono::date_time(static_cast<uint64_t>(utc_ticks), omni::chrono::date_time_kind::UTC);
                result.time_zone_offset = omni::chrono::time_span::zero();
            }

            return true;
        }

        // Handles time zone adjustments and sets DateTimeKind values as required by the styles
        bool determine_time_zone_adjustments(omni::internal::date_time_format::parse_result& result, const omni::chrono::date_time_styles& styles, bool is_time_only)
        {
            if ((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) {
                // This is a DateTimeOffset parse, so the offset will actually be captured directly, and no adjustment is required in most cases
                return omni::internal::date_time_format::date_time_offset_time_zone_post_processing(result, styles);
            } else {
                int64_t offset_ticks = result.time_zone_offset.ticks();
                // the DateTime offset must be within +- 14:00 hours.
                if (offset_ticks < OMNI_DATE_INTERNAL_MIN_OFFSET_FW || offset_ticks > OMNI_DATE_INTERNAL_MAX_OFFSET_FW) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_OffsetOutOfRange");
                    return false;
                }
            }

            // The flags AssumeUniversal and AssumeLocal only apply when the input does not have a time zone
            if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) == 0) {

                // If AssumeLocal or AssumeLocal is used, there will always be a kind specified. As in the
                // case when a time zone is present, it will default to being local unless AdjustToUniversal
                // is present. These comparisons determine whether setting the kind is sufficient, or if a
                // time zone adjustment is required. For consistency with the rest of parsing, it is desirable
                // to fall through to the Adjust methods below, so that there is consist handling of boundary
                // cases like wrapping around on time-only dates and temporarily allowing an adjusted date
                // to exceed DateTime.MaxValue
                if ((styles & omni::chrono::date_time_styles::ASSUME_LOCAL) != 0) {
                    if ((styles & omni::chrono::date_time_styles::ADJUST_TO_UNIVERSAL) != 0) {
                        result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                        result.time_zone_offset = result.parsed_date.utc_offset();
                    } else {
                        result.parsed_date = omni::chrono::date_time::specify_kind(result.parsed_date, omni::chrono::date_time_kind::LOCAL);
                        return true;
                    }
                } else if ((styles & omni::chrono::date_time_styles::ASSUME_UNIVERSAL) != 0) {
                    if ((styles & omni::chrono::date_time_styles::ADJUST_TO_UNIVERSAL) != 0) {
                        result.parsed_date = omni::chrono::date_time::specify_kind(result.parsed_date, omni::chrono::date_time_kind::UTC);
                        return true;
                    } else {
                        result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                        result.time_zone_offset = omni::chrono::time_span::zero();
                    }
                } else {
                    // No time zone and no Assume flags, so DateTimeKind.Unspecified is fine
                    return true;
                }
            }
            if (((styles & omni::chrono::date_time_styles::ROUNDTRIP_KIND) != 0) && ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_UTC) != 0)) {
                result.parsed_date = omni::chrono::date_time::specify_kind(result.parsed_date, omni::chrono::date_time_kind::UTC);
                return true;
            }

            if ((styles & omni::chrono::date_time_styles::ADJUST_TO_UNIVERSAL) != 0) {
                return (omni::internal::date_time_format::adjust_time_zone_to_universal(result));
            }
            return (omni::internal::date_time_format::adjust_time_zone_to_local(result, is_time_only));
        }

        bool parse_digits(omni::internal::date_time_format::__dt_string& str, int64_t min_digit_len, int64_t max_digit_len, int64_t& result)
        {
            int64_t start_index = str.index;
            int64_t tok_len = 0;
            result = 0;
            while (tok_len < max_digit_len) {
                if (!str.get_next_digit()) {
                    --str.index;
                    break;
                }
                result = result * 10 + static_cast<int64_t>(str.get_digit());
                ++tok_len;
            }
            if (tok_len < min_digit_len) {
                str.index = start_index;
                return false;
            }
            return true;
        }

        bool parse_digits(omni::internal::date_time_format::__dt_string& str, int64_t digit_len, int64_t& result)
        {
            if (digit_len == 1) {
                // 1 really means 1 or 2 for this call
                return omni::internal::date_time_format::parse_digits(str, 1, 2, result);
            }
            else {
                return omni::internal::date_time_format::parse_digits(str, digit_len, digit_len, result);
            }
        }

        bool parse_iso_8601(omni::internal::date_time_format::date_time_raw_info& raw, omni::internal::date_time_format::__dt_string& str, const omni::chrono::date_time_styles& styles, omni::internal::date_time_format::parse_result& result)
        {
            int64_t hour, minute;
            int64_t second = 0;
            double part_second = 0;
            --str.index;

            str.skip_white_spaces();
            if (!omni::internal::date_time_format::parse_digits(str, 2, hour)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            str.skip_white_spaces();
            if (!str.match(':')) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            str.skip_white_spaces();
            if (!omni::internal::date_time_format::parse_digits(str, 2, minute)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }
            str.skip_white_spaces();
            if (str.match(':')) {
                str.skip_white_spaces();
                if (!omni::internal::date_time_format::parse_digits(str, 2, second)) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                    return false;
                }
                if (str.match('.')) {
                    if (!omni::internal::date_time_format::parse_fraction(str, part_second)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    --str.index;
                }
                str.skip_white_spaces();
            }
            if (str.get_next()) {
                char ch = str.get_char();
                if (ch == '+' || ch == '-') {
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                    if (!omni::internal::date_time_format::parse_time_zone(str, result.time_zone_offset)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                } else if (ch == 'Z' || ch == 'z') {
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                    result.time_zone_offset = omni::chrono::time_span::zero();
                    result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_UTC);
                } else {
                    --str.index;
                }
                str.skip_white_spaces();
                if (str.match('#')) {
                    if (!omni::internal::date_time_format::verify_valid_punctuation(str)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    str.skip_white_spaces();
                }
                if (str.match('\0')) {
                    if (!omni::internal::date_time_format::verify_valid_punctuation(str)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                }
                if (str.get_next()) {
                    // If this is true, there were non-white space characters remaining in the DateTime
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                    return false;
                }
            }

            omni::chrono::date_time time = omni::chrono::date_time::min_value();
            //Calendar calendar = GregorianCalendar.GetDefaultInstance();
            if (!omni::chrono::date_time::try_create(static_cast<uint16_t>(raw.year), static_cast<uint16_t>(raw.get_number(0)), static_cast<uint16_t>(raw.get_number(1)), static_cast<uint16_t>(hour), static_cast<uint16_t>(minute), static_cast<uint16_t>(second), 0, time)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_BAD_DATE_TIME_CALENDAR, "Format_BadDateTimeCalendar");
                return false;
            }

            time = time.add_ticks(static_cast<int64_t>(omni::math::round(part_second * OMNI_TICKS_PER_SECOND)));
            result.parsed_date = time;
            if (!omni::internal::date_time_format::determine_time_zone_adjustments(result, styles, false)) {
                return false;
            }
            return true;
        }

        bool adjust_hour(int16_t& hour, omni::internal::date_time_format::time_mark::enum_t time_mark)
        {
            if (time_mark != omni::internal::date_time_format::time_mark::NOT_SET) {
                if (time_mark == omni::internal::date_time_format::time_mark::AM) {
                    if (hour < 0 || hour > 12) {
                        return false;
                    }
                    hour = (hour == 12) ? 0 : hour;
                } else {
                    if (hour < 0 || hour > 23) {
                        return false;
                    }
                    if (hour < 12) {
                        hour += 12;
                    }
                }
            }
            return true;
        }

        // This is the real method to do the parsing work.
        bool try_parse
        (
            const std::string& date_str,
            omni::internal::date_time_format::format_info& dtfi,
            omni::chrono::date_time_styles& styles,
            omni::internal::date_time_format::parse_result& result
        ) {
            if (date_str.empty()) {
                return false;
            }

            omni::chrono::date_time time = omni::chrono::date_time::min_value();
            // First try the predefined format.
            omni::internal::date_time_format::parse_state::enum_t dps = omni::internal::date_time_format::parse_state::BEGIN;
            bool is_terminal_state = false;

            omni::internal::date_time_format::date_time_token dtok; // The buffer to store the parsing token
            dtok.suffix = omni::internal::date_time_format::token_type::SEP_UNK;

            int64_t number_pointer[3] = {0};
            omni::internal::date_time_format::date_time_raw_info raw(&number_pointer[0]); // The buffer to store temporary parsing information.

            raw.has_same_date_and_time_separators = (dtfi.date_separator == dtfi.time_separator);

            // result.calendar = dtfi.Calendar;
            result.era = 0; // Calendar.CurrentEra;

            // The string to be parsed. Use a __dt_string wrapper so that we can trace the index which
            // indicates the beginning of next token
            omni::internal::date_time_format::__dt_string str(date_str, dtfi);
            str.get_next();

            // The following loop will break when we reach the end of the str.
            do {
                // Call the lexer to get the next token
                // If we find a era in lex(), the era value will be in raw.era.
                if (!omni::internal::date_time_format::lex(dps, str, dtok, raw, result, dtfi, styles)) {
                    return false;
                }

                // If the token is not unknown, process it.
                // Otherwise, just discard it.
                if (dtok.dtt != omni::internal::date_time_format::token::UNKNOWN) {
                    // Check if we got any CJK Date/Time suffix.
                    // Since the Date/Time suffix tells us the number belongs to year/month/day/hour/minute/second,
                    // store the number in the appropriate field in the result.
                    if (dtok.suffix != omni::internal::date_time_format::token_type::SEP_UNK) {
                        if (!omni::internal::date_time_format::process_date_time_suffix(result, raw, dtok)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }

                        dtok.suffix = omni::internal::date_time_format::token_type::SEP_UNK;  // Reset suffix to SEP_UNK;
                    }

                    if (dtok.dtt == omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK) {
                        if (dps == omni::internal::date_time_format::parse_state::D_YNd || dps == omni::internal::date_time_format::parse_state::D_YN) {
                            // Consider this as ISO 8601 format:
                            // "yyyy-MM-dd'T'HH:mm:ss"                 1999-10-31T02:00:00
                            return (omni::internal::date_time_format::parse_iso_8601(raw, str, styles, result));
                        } else {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    }

                    if (raw.has_same_date_and_time_separators) {
                        if (dtok.dtt == omni::internal::date_time_format::token::YEAR_END || dtok.dtt == omni::internal::date_time_format::token::YEAR_SPACE || dtok.dtt == omni::internal::date_time_format::token::YEAR_DATE_SEP) {
                            // When time and date separators are same and we are hitting a year number while the first parsed part of the string was recognized
                            // as part of time (and not a date) omni::internal::date_time_format::parse_state::T_Nt, omni::internal::date_time_format::parse_state::T_NNt then change the state to be a date so we try to parse it as a date instead
                            if (dps == omni::internal::date_time_format::parse_state::T_Nt) {
                                dps = omni::internal::date_time_format::parse_state::D_Nd;
                            } else if (dps == omni::internal::date_time_format::parse_state::T_NNt) {
                                dps = omni::internal::date_time_format::parse_state::D_NNd;
                            }
                        }

                        bool atEnd = str.at_end();
                        if (omni::internal::date_time_format::date_parsing_state(dps, dtok.dtt) == omni::internal::date_time_format::parse_state::ERR || atEnd) {
                            switch (dtok.dtt) {
                                // we have the case of Serbia have dates in forms 'd.M.yyyy.' so we can expect '.' after the date parts.
                                // changing the token to end with space instead of Date Separator will avoid failing the parsing.
                                case omni::internal::date_time_format::token::YEAR_DATE_SEP:  dtok.dtt = atEnd ? omni::internal::date_time_format::token::YEAR_END  : omni::internal::date_time_format::token::YEAR_SPACE;  break;
                                case omni::internal::date_time_format::token::NUM_DATE_SEP:   dtok.dtt = atEnd ? omni::internal::date_time_format::token::NUM_END   : omni::internal::date_time_format::token::NUM_SPACE;   break;
                                case omni::internal::date_time_format::token::NUM_TIME_SEP:   dtok.dtt = atEnd ? omni::internal::date_time_format::token::NUM_END   : omni::internal::date_time_format::token::NUM_SPACE;   break;
                                case omni::internal::date_time_format::token::MONTH_DATE_SEP: dtok.dtt = atEnd ? omni::internal::date_time_format::token::MONTH_END : omni::internal::date_time_format::token::MONTH_SPACE; break;

                                // handle these explicitly (avoid warnings)
                                case omni::internal::date_time_format::token::END:
                                case omni::internal::date_time_format::token::NUM_END:
                                case omni::internal::date_time_format::token::NUM_AM_PM:
                                case omni::internal::date_time_format::token::NUM_SPACE:
                                case omni::internal::date_time_format::token::MONTH_END:
                                case omni::internal::date_time_format::token::MONTH_SPACE:
                                case omni::internal::date_time_format::token::NUM_DATE_SUFFIX:
                                case omni::internal::date_time_format::token::NUM_TIME_SUFFIX:
                                case omni::internal::date_time_format::token::DAY_OF_WEEK:
                                case omni::internal::date_time_format::token::YEAR_SPACE:
                                case omni::internal::date_time_format::token::YEAR_END:
                                case omni::internal::date_time_format::token::TIME_ZONE:
                                case omni::internal::date_time_format::token::ERA:
                                case omni::internal::date_time_format::token::NUM_UTC_TIME_MARK:
                                case omni::internal::date_time_format::token::UNKNOWN:
                                case omni::internal::date_time_format::token::NUM_LOCAL_TIME_MARK:
                                case omni::internal::date_time_format::token::MAX:
                                default: break;
                            }
                        }
                    }

                    // advance to the next state, and continue
                    dps = omni::internal::date_time_format::date_parsing_state(dps, dtok.dtt);

                    if (dps == omni::internal::date_time_format::parse_state::ERR) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    } else if (dps > omni::internal::date_time_format::parse_state::ERR) {
                        if ((dtfi.fmt_flags & format_flags::USE_HEBREW_RULE) != 0) {
                            return false;
                        } else {
                            if (!omni::internal::date_time_format::process_terminal_t_state(dps, result, styles, raw, dtfi)) {
                                return false;
                            }
                        }
                        is_terminal_state = true;

                        // If we have reached a terminal state, start over from omni::internal::date_time_format::parse_state::BEGIN again.
                        // For example, when we parsed "1999-12-23 13:30", we will reach a terminal state at "1999-12-23",
                        // and we start over so we can continue to parse "12:30".
                        dps = omni::internal::date_time_format::parse_state::BEGIN;
                    }
                }
            } while (dtok.dtt != omni::internal::date_time_format::token::END && dtok.dtt != omni::internal::date_time_format::token::NUM_END && dtok.dtt != omni::internal::date_time_format::token::MONTH_END);

            if (!is_terminal_state) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            omni::internal::date_time_format::adjust_time_mark(dtfi, raw);
            if (!omni::internal::date_time_format::adjust_hour(result.hour, raw.time_mark)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                return false;
            }

            // Check if the parsed string only contains hour/minute/second values.
            bool is_time_only = (result.year == -1 && result.month == -1 && result.day == -1);

            // Check if any year/month/day is missing in the parsing string.
            // If yes, get the default value from today's date.
            if (!omni::internal::date_time_format::check_default_date_time(result, styles)) {
                return false;
            }

            if (!omni::chrono::date_time::try_create(static_cast<uint16_t>(result.year), static_cast<uint16_t>(result.month), static_cast<uint16_t>(result.day), static_cast<uint16_t>(result.hour), static_cast<uint16_t>(result.minute), static_cast<uint16_t>(result.second), 0, time)) {
                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_BAD_DATE_TIME_CALENDAR, "Format_BadDateTimeCalendar");
                return false;
            }
            if (raw.fraction > 0) {
                time = time.add_ticks(static_cast<int64_t>(omni::math::round(raw.fraction * OMNI_TICKS_PER_SECOND)));
            }

            // We have to check day of week before we adjust to the time zone.
            // Otherwise, the value of day of week may change after adjusting to the time zone.
            if (raw.day_of_week != -1) {
                // Check if day of week is correct.
                if (raw.day_of_week != static_cast<int64_t>(time.day_of_week())) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDayOfWeek");
                    return false;
                }
            }

            result.parsed_date = time;

            if (!omni::internal::date_time_format::determine_time_zone_adjustments(result, styles, is_time_only)) {
                return false;
            }

            return true;
        }

        bool try_parse(const std::string& date_str, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& styles, omni::chrono::date_time& result)
        {
            omni::chrono::date_time_styles style_data = styles;
            omni::internal::date_time_format::parse_result data;
            if (omni::internal::date_time_format::try_parse(date_str, dtfi, style_data, data)) {
                result = data.parsed_date;
                return true;
            }
            return false;
        }

        bool try_parse(const std::string& date_str, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& styles, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason)
        {
            omni::chrono::date_time_styles style_data = styles;
            omni::internal::date_time_format::parse_result data;
            fail_reason = omni::chrono::date_time_parse_failure::NONE;
            if (omni::internal::date_time_format::try_parse(date_str, dtfi, style_data, data)) {
                result = data.parsed_date;
                return true;
            }
            fail_reason = data.failure;
            return false;
        }

        omni::chrono::date_time parse(const std::string& date_str, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& styles)
        {
            omni::chrono::date_time_styles style_data = styles;
            omni::internal::date_time_format::parse_result result;
            if (omni::internal::date_time_format::try_parse(date_str, dtfi, style_data, result)) {
                return result.parsed_date;
            }
            OMNI_ERR_RETV_FW("Invalid date time string detected", omni::exceptions::invalid_parse(), omni::chrono::date_time())
        }

        namespace date_time_parse
        {
            struct parsing_info
            {
                // Calendar calendar;
                int16_t day_of_week;
                date_time_format::time_mark::enum_t time_mark;

                bool use_hour_12;
                bool use_two_digit_year;
                bool allow_inner_ws;
                bool allow_trailing_ws;
                bool custom_number_parser;

                void init()
                {
                    this->day_of_week = -1;
                    this->time_mark = date_time_format::time_mark::NOT_SET;
                    this->use_hour_12 = false;
                    this->use_two_digit_year = false;
                    this->allow_inner_ws = false;
                    this->allow_trailing_ws = false;
                    this->custom_number_parser = false;
                }
            };

            std::string get_real_format(const std::string& format, const omni::internal::date_time_format::format_info& dtfi)
            {
                std::string real_format;
                switch (format[0]) {
                    case 'd':       // Short Date
                        real_format = dtfi.short_date_pattern;
                        break;
                    case 'D':       // Long Date
                        real_format = dtfi.long_date_pattern;
                        break;
                    case 'f':       // Full (long date + short time)
                        real_format = dtfi.long_date_pattern + " " + dtfi.short_time_pattern;
                        break;
                    case 'F':       // Full (long date + long time)
                        real_format = dtfi.full_date_time_pattern;
                        break;
                    case 'g':       // General (short date + short time)
                        real_format = dtfi.general_short_time_pattern;
                        break;
                    case 'G':       // General (short date + long time)
                        real_format = dtfi.general_long_time_pattern;
                        break;
                    case 'm':
                    case 'M':       // Month/Day Date
                        real_format = dtfi.month_day_pattern;
                        break;
                    case 'o':
                    case 'O':
                        real_format = "yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK"; // RoundtripFormat;
                        break;
                    case 'r':
                    case 'R':       // RFC 1123 Standard
                        real_format = dtfi.rfc_1123_pattern;
                        break;
                    case 's':       // Sortable without Time Zone Info
                        real_format = dtfi.sortable_date_time_pattern;
                        break;
                    case 't':       // Short Time
                        real_format = dtfi.short_time_pattern;
                        break;
                    case 'T':       // Long Time
                        real_format = dtfi.long_time_pattern;
                        break;
                    case 'u':       // Universal with Sortable format
                        real_format = dtfi.universal_sortable_date_time_pattern;
                        break;
                    case 'U':       // Universal with Full (long date + long time) format
                        real_format = dtfi.full_date_time_pattern;
                        break;
                    case 'y':
                    case 'Y':       // Year/Month Date
                        real_format = dtfi.year_month_pattern;
                        break;
                    default:
                        OMNI_ERR_RETV_FW("Invalid format specified", omni::exceptions::invalid_string_format(), std::string())
                }
                return real_format;
            }

            std::string expand_predefined_format(const std::string& format, omni::internal::date_time_format::format_info& dtfi, omni::internal::date_time_format::date_time_parse::parsing_info& parse_info, omni::internal::date_time_format::parse_result& result)
            {
                OMNI_UNUSED(parse_info);
                // Check the format to see if we need to override the dtfi to be invariant info,
                // and see if we need to set up the userUniversalTime flag.
                switch (format[0]) {
                    case 'o':
                    case 'O':       // Round Trip Format
                        // parseInfo.calendar = GregorianCalendar.GetDefaultInstance();
                        dtfi.reset();
                        break;
                    case 'r':
                    case 'R':       // RFC 1123 Standard.  (in Universal time)
                        // parseInfo.calendar = GregorianCalendar.GetDefaultInstance();
                        dtfi.reset();

                        if ((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) {
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::RFC1123_PATTERN);
                        }
                        break;
                    case 's':       // Sortable format (in local time)
                        dtfi.reset();
                        // parseInfo.calendar = GregorianCalendar.GetDefaultInstance();
                        break;
                    case 'u':       // Universal time format in sortable format.
                        // parseInfo.calendar = GregorianCalendar.GetDefaultInstance();
                        dtfi.reset();

                        if ((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) {
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::UTC_SORT_PATTERN);
                        }
                        break;
                    case 'U':       // Universal time format with culture-dependent format.
                        // parseInfo.calendar = GregorianCalendar.GetDefaultInstance();
                        result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                        result.time_zone_offset = omni::chrono::time_span::zero();
                        result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_UTC);
                        break;
                    default: break;
                }

                // Expand the pre-defined format character to the real format from DateTimeFormatInfo.
                return omni::internal::date_time_format::date_time_parse::get_real_format(format, dtfi);
            }

            bool check_new_value(int16_t& current_val, int16_t new_val, omni::internal::date_time_format::parse_result& result)
            {
                if (current_val == -1) {
                    current_val = new_val;
                    return true;
                } else {
                    if (new_val != current_val) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                        return false;
                    }
                }
                return true;
            }
            
            bool match_abbreviated_month_name(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, int64_t& result) 
            {
                int64_t max_match_str_len = 0;
                result = -1;
                if (str.get_next()) {
                    // Scan the month names (note that some calendars has 13 months) and find the matching month name which has the max string length.
                    // We need to do this because some cultures (e.g. "cs-CZ") which have abbreviated month names with the same prefix.
                    for (std::size_t i = 1; i < omni::chrono::month::COUNT(); ++i) {
                        std::string search_str = omni::chrono::month::get_abbreviated_name(i);
                        std::size_t match_str_len = search_str.size();
                        if ( dtfi.has_spaces_in_month_names()
                                ? str.match_specified_words(search_str, false, match_str_len)
                                : str.match_specified_word(search_str)) {
                            if (static_cast<int64_t>(match_str_len) > max_match_str_len) {
                                max_match_str_len = static_cast<int64_t>(match_str_len);
                                result = static_cast<int64_t>(i);
                            }
                        }
                    }

                    // Search leap year form.
                    if ((dtfi.fmt_flags & omni::internal::date_time_format::format_flags::USE_LEAP_YEAR_MONTH) != 0) {
                        int64_t temp_res = str.match_longest_words(dtfi.internal_get_leap_year_names(), max_match_str_len);
                        // We found a longer match in the leap year month name.  Use this as the result.
                        // The result from match_longest_words is 0 ~ length of word array.
                        // So we increment the result by one to become the month value.
                        if (temp_res >= 0) {
                            result = temp_res + 1;
                        }
                    }
                }
                if (result > 0) {
                    str.index += (max_match_str_len - 1);
                    return true;
                }
                return false;
            }

            bool match_month_name(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, int64_t& result)
            {
                int64_t max_match_str_len = 0;
                result = -1;
                if (str.get_next()) {
                    // Scan the month names (note that some calendars has 13 months) and find the matching month name which has the max string length.
                    // We need to do this because some cultures (e.g. "vi-VN") which have month names with the same prefix.
                    for (std::size_t i = 1; i < omni::chrono::month::COUNT(); ++i) {
                        std::string search_str = omni::chrono::month::get_name(i);
                        std::size_t match_str_len = search_str.size();
                        if ( dtfi.has_spaces_in_month_names()
                                ? str.match_specified_words(search_str, false, match_str_len)
                                : str.match_specified_word(search_str)) {
                            if (static_cast<int64_t>(match_str_len) > max_match_str_len) {
                                max_match_str_len = static_cast<int64_t>(match_str_len);
                                result = static_cast<int64_t>(i);
                            }
                        }
                    }

                    // Search genitive form.
                    if ((dtfi.fmt_flags & format_flags::USE_GENITIVE_MONTH) != 0) {
                        int64_t temp_res = str.match_longest_words(dtfi.internal_get_leap_year_names(), max_match_str_len);
                        // We found a longer match in the genitive month name.  Use this as the result.
                        // The result from match_longest_words is 0 ~ length of word array.
                        // So we increment the result by one to become the month value.
                        if (temp_res >= 0) {
                            result = temp_res + 1;
                        }
                    }

                    // Search leap year form.
                    if ((dtfi.fmt_flags & format_flags::USE_LEAP_YEAR_MONTH) != 0) {
                        int64_t temp_res = str.match_longest_words(dtfi.internal_get_leap_year_names(), max_match_str_len);
                        // We found a longer match in the leap year month name.  Use this as the result.
                        // The result from match_longest_words is 0 ~ length of word array.
                        // So we increment the result by one to become the month value.
                        if (temp_res >= 0) {
                            result = temp_res + 1;
                        }
                    }
                }

                if (result > 0) {
                    str.index += (max_match_str_len - 1);
                    return true;
                }
                return false;
            }

            bool match_abbreviated_day_name(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, int64_t& result)
            {
                int64_t max_match_str_len = 0;
                result = -1;
                if (str.get_next()) {
                    for (std::size_t i = omni::chrono::day_of_week::SUNDAY; i <= omni::chrono::day_of_week::SATURDAY; ++i) {
                        std::string search_str = omni::chrono::day::get_abbreviated_name(i);
                        std::size_t match_str_len = search_str.size();
                        if ( dtfi.has_spaces_in_day_names()
                                ? str.match_specified_words(search_str, false, match_str_len)
                                : str.match_specified_word(search_str)) {
                            if (static_cast<int64_t>(match_str_len) > max_match_str_len) {
                                max_match_str_len = static_cast<int64_t>(match_str_len);
                                result = static_cast<int64_t>(i);
                            }
                        }
                    }
                }
                if (result >= 0) {
                    str.index += max_match_str_len - 1;
                    return true;
                }
                return false;
            }

            bool match_day_name(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, int64_t& result)
            {
                // Turkish (tr-TR) got day names with the same prefix.
                int64_t max_match_str_len = 0;
                result = -1;
                if (str.get_next()) {
                    for (std::size_t i = omni::chrono::day_of_week::SUNDAY; i <= omni::chrono::day_of_week::SATURDAY; ++i) {
                        std::string search_str = omni::chrono::day::get_name(i);
                        std::size_t match_str_len = search_str.size();
                        if ( dtfi.has_spaces_in_day_names()
                                ? str.match_specified_words(search_str, false, match_str_len)
                                : str.match_specified_word(search_str)) {
                            if (static_cast<int64_t>(match_str_len) > max_match_str_len) {
                                max_match_str_len = static_cast<int64_t>(match_str_len);
                                result = static_cast<int64_t>(i);
                            }
                        }
                    }
                }
                if (result >= 0) {
                    str.index += max_match_str_len - 1;
                    return true;
                }
                return false;
            }

            bool match_era_name(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, int16_t& result)
            {
                OMNI_UNUSED(dtfi);
                if (str.get_next()) {
                    std::string search_str = OMNI_DATE_ERA_FW;
                    if (str.match_specified_word(search_str)) {
                        str.index += (search_str.size() - 1);
                        result = 0;
                        return true;
                    }
                    search_str = OMNI_DATE_ERA_ABBR_FW;
                    if (str.match_specified_word(search_str)) {
                        str.index += (search_str.size() - 1);
                        result = 0;
                        return true;
                    }
                }
                return false;
            }

            bool match_time_mark(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, time_mark::enum_t& result)
            {
                result = omni::internal::date_time_format::time_mark::NOT_SET;
                // In some cultures have empty strings in AM/PM mark. E.g. af-ZA (0x0436), the AM mark is "", and PM mark is "nm".
                if (dtfi.am_designator.size() == 0) {
                    result = omni::internal::date_time_format::time_mark::AM;
                }
                if (dtfi.pm_designator.size() == 0) {
                    result = omni::internal::date_time_format::time_mark::PM;
                }

                if (str.get_next()) {
                    std::string search_str = dtfi.am_designator;
                    if (search_str.size() > 0) {
                        if (str.match_specified_word(search_str)) {
                            // Found an AM time mark with length > 0.
                            str.index += (search_str.size() - 1);
                            result = omni::internal::date_time_format::time_mark::AM;
                            return true;
                        }
                    }
                    search_str = dtfi.pm_designator;
                    if (search_str.size() > 0) {
                        if (str.match_specified_word(search_str)) {
                            // Found a PM time mark with length > 0.
                            str.index += (search_str.size() - 1);
                            result = omni::internal::date_time_format::time_mark::PM;
                            return true;
                        }
                    }
                    --str.index; // Undo the get_next call.
                }
                if (result != omni::internal::date_time_format::time_mark::NOT_SET) {
                    // If one of the AM/PM marks is empty string, return the result.
                    return true;
                }
                return false;
            }

            bool match_abbreviated_time_mark(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::format_info& dtfi, time_mark::enum_t& result)
            {
                // DEV_NOTE : the assumption here is that abbreviated time mark is the first
                // character of the AM/PM designator.  If this invariant changes, we have to
                // change the code below.
                if (str.get_next()) {
                    if (str.get_char() == dtfi.am_designator[0]) {
                        result = omni::internal::date_time_format::time_mark::AM;
                        return true;
                    }
                    if (str.get_char() == dtfi.pm_designator[0]) {
                        result = omni::internal::date_time_format::time_mark::PM;
                        return true;
                    }
                }
                return false;
            }

            bool parse_fraction_exact(omni::internal::date_time_format::__dt_string& str, std::size_t max_len, double& result)
            {
                if (!str.get_next_digit()) {
                    --str.index;
                    return false;
                }
                result = static_cast<double>(str.get_digit());

                std::size_t digit_len = 1;
                for (; digit_len < max_len; ++digit_len) {
                    if (!str.get_next_digit()) {
                        --str.index;
                        break;
                    }
                    result = result * 10 + static_cast<double>(str.get_digit());
                }

                result = (result / std::pow(10, digit_len));
                return (digit_len == max_len);
            }

            bool parse_sign(omni::internal::date_time_format::__dt_string& str, bool& result)
            {
                if (!str.get_next()) {
                    // A sign symbol ('+' or '-') is expected. However, end of string is encountered.
                    return false;
                }
                char ch = str.get_char();
                if (ch == '+') {
                    result = true;
                    return true;
                } else if (ch == '-') {
                    result = false;
                    return true;
                }
                // A sign symbol ('+' or '-') is expected.
                return false;
            }

            bool parse_time_zone_offset(omni::internal::date_time_format::__dt_string& str, std::size_t len, omni::chrono::time_span& result)
            {
                bool is_positive = true;
                int64_t hour_offset;
                int64_t minute_offset = 0;

                switch (len) {
                    case 1:
                    case 2:
                        if (!omni::internal::date_time_format::date_time_parse::parse_sign(str, is_positive)) {
                            return false;
                        }
                        if (!omni::internal::date_time_format::parse_digits(str, static_cast<int64_t>(len), hour_offset)) {
                            return false;
                        }
                        break;
                    default:
                        if (!omni::internal::date_time_format::date_time_parse::parse_sign(str, is_positive)) {
                            return false;
                        }

                        // Parsing 1 digit will actually parse 1 or 2.
                        if (!omni::internal::date_time_format::parse_digits(str, 1, hour_offset)) {
                            return false;
                        }
                        // ':' is optional.
                        std::string col = ":";
                        if (str.match(col)) {
                            // Found ':'
                            if (!omni::internal::date_time_format::parse_digits(str, 2, minute_offset)) {
                                return false;
                            }
                        } else {
                            // Since we can not match ':', put the char back.
                            str.index--;
                            if (!omni::internal::date_time_format::parse_digits(str, 2, minute_offset)) {
                                return false;
                            }
                        }
                        break;
                }
                if (minute_offset < 0 || minute_offset >= 60) {
                    return false;
                }

                result = omni::chrono::time_span(hour_offset, minute_offset, 0);
                if (!is_positive) {
                    result = result.negate();
                }
                return true;
            }

            bool match_Word(omni::internal::date_time_format::__dt_string& str, const std::string& target)
            {
                std::size_t length = target.size();
                if (length > (str.value.size() - static_cast<std::size_t>(str.index))) {
                    return false;
                }

                if (omni::string::util::compare(str.value, static_cast<std::size_t>(str.index), length, target, 0, length, omni::string::compare_options::IGNORE_CASE) != 0) {
                    return false;
                }

                std::size_t next_char_index = static_cast<std::size_t>(str.index) + target.size();

                if (next_char_index < str.value.size()) {
                    char next_ch = str.value[next_char_index];
                    if (omni::char_util::is_letter(next_ch)) {
                        return false;
                    }
                }
                str.index = static_cast<int64_t>(next_char_index);
                if (str.index < str.len) {
                    str.current_char = str.value[static_cast<std::size_t>(str.index)];
                }

                return true;
            }

            bool get_time_zone_name(omni::internal::date_time_format::__dt_string& str)
            {
                return (omni::internal::date_time_format::date_time_parse::match_Word(str, OMNI_DATE_INTERNAL_GMT_NAME_FW) || omni::internal::date_time_format::date_time_parse::match_Word(str, OMNI_DATE_ZULU_NAME_FW));
            }

            bool try_parse_quote_string(const std::string format, std::size_t pos, std::stringstream& result, int64_t& return_value)
            {
                // DEV_NOTE : pos will be the index of the quote character in the 'format' string.
                std::size_t format_len = format.size();
                std::size_t begin_pos = pos;
                char quote_char = format[pos++]; // Get the character used to quote the following string.
                return_value = 0;

                bool found_quote = false;
                while (pos < format_len) {
                    char ch = format[pos++];
                    if (ch == quote_char) {
                        found_quote = true;
                        break;
                    } else if (ch == '\\') {
                        // The following are used to support escaped character.
                        // Escaped character is also supported in the quoted string.
                        // Therefore, someone can use a format like "'minute:' mm\"" to display:
                        //  minute: 45"
                        // because the second double quote is escaped.
                        if (pos < format_len) {
                            result << format[pos++];
                            // result.Append(format[pos++]);
                        } else {
                            // This means that '\' is at the end of the formatting string.
                            return false;
                        }
                    } else {
                        result << ch;
                    }
                }

                if (!found_quote) {
                    // Here we can't find the matching quote.
                    return false;
                }

                // Return the character count including the begin/end quote characters and enclosed string.
                return_value = static_cast<int64_t>(pos - begin_pos);
                return true;
            }

            bool parse_by_format(omni::internal::date_time_format::__dt_string& str, omni::internal::date_time_format::__dt_string& format, omni::internal::date_time_format::date_time_parse::parsing_info& parseInfo, omni::internal::date_time_format::format_info& dtfi, omni::internal::date_time_format::parse_result& result)
            {
                int64_t token_len = 0;
                int64_t temp_year = 0;
                int64_t temp_month = 0;
                int64_t temp_day = 0;
                int64_t temp_dow = 0;
                int64_t temp_hour = 0;
                int64_t temp_minute = 0;
                int64_t temp_second = 0;
                double temp_fraction = 0;
                omni::internal::date_time_format::time_mark::enum_t tempTimeMark = omni::internal::date_time_format::time_mark::NOT_SET;

                char ch = format.get_char();

                switch (ch) {
                    case 'y': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        bool parseResult;
                        if (dtfi.has_force_two_digit_years) {
                            parseResult = omni::internal::date_time_format::parse_digits(str, 1, 4, temp_year);
                        } else {
                            if (token_len <= 2) {
                                parseInfo.use_two_digit_year = true;
                            }
                            parseResult = omni::internal::date_time_format::parse_digits(str, token_len, temp_year);
                        }
                        if (!parseResult && parseInfo.custom_number_parser) {
                            parseResult = false;
                        }
                        if (!parseResult) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                        if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.year, static_cast<int16_t>(temp_year), result)) {
                            return false;
                        }
                    } break;
                    case 'M': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (token_len <= 2) {
                            if (!omni::internal::date_time_format::parse_digits(str, token_len, temp_month)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                        } else {
                            if (token_len == 3) {
                                if (!omni::internal::date_time_format::date_time_parse::match_abbreviated_month_name(str, dtfi, temp_month)) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                            } else {
                                if (!omni::internal::date_time_format::date_time_parse::match_month_name(str, dtfi, temp_month)) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                            }
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::PARSED_MONTH_NAME);
                        }
                        if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.month, static_cast<int16_t>(temp_month), result)) {
                            return false;
                        }
                    } break;
                    case 'd': {
                        // Day & Day of week
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (token_len <= 2) {
                            // "d" & "dd"
                            if (!omni::internal::date_time_format::parse_digits(str, token_len, temp_day)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                            if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.day, static_cast<int16_t>(temp_day), result)) {
                                return false;
                            }
                        } else {
                            if (token_len == 3) {
                                // "ddd"
                                if (!omni::internal::date_time_format::date_time_parse::match_abbreviated_day_name(str, dtfi, temp_dow)) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                            } else {
                                // "dddd*"
                                if (!omni::internal::date_time_format::date_time_parse::match_day_name(str, dtfi, temp_dow)) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                            }
                            if (!omni::internal::date_time_format::date_time_parse::check_new_value(parseInfo.day_of_week, static_cast<int16_t>(temp_dow), result)) {
                                return false;
                            }
                        }
                    } break;
                    case 'g': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        // Put the era value in result.era.
                        if (!omni::internal::date_time_format::date_time_parse::match_era_name(str, dtfi, result.era)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    } break;
                    case 'h': {
                        parseInfo.use_hour_12 = true;
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (!omni::internal::date_time_format::parse_digits(str, (token_len < 2? 1 : 2), temp_hour)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                        if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.hour, static_cast<int16_t>(temp_hour), result)) {
                            return false;
                        }
                    } break;
                    case 'H': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (!omni::internal::date_time_format::parse_digits(str, (token_len < 2? 1 : 2), temp_hour)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                        if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.hour, static_cast<int16_t>(temp_hour), result)) {
                            return false;
                        }
                    } break;
                    case 'm': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (!omni::internal::date_time_format::parse_digits(str, (token_len < 2? 1 : 2), temp_minute)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                        if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.minute, static_cast<int16_t>(temp_minute), result)) {
                            return false;
                        }
                    } break;
                    case 's': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (!omni::internal::date_time_format::parse_digits(str, (token_len < 2? 1 : 2), temp_second)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                        if (!omni::internal::date_time_format::date_time_parse::check_new_value(result.second, static_cast<int16_t>(temp_second), result)) {
                            return false;
                        }
                    } break;
                    case 'f':
                    case 'F': {
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (token_len <= OMNI_DATE_INTERNAL_MAX_SECONDS_FRACTION_DIGITS_FW) {
                            if (!omni::internal::date_time_format::date_time_parse::parse_fraction_exact(str, static_cast<std::size_t>(token_len), temp_fraction)) {
                                if (ch == 'f') {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                            }
                            if (result.fraction < 0) {
                                result.fraction = temp_fraction;
                            } else {
                                if (!omni::math::are_equal(temp_fraction, result.fraction)) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                                    return false;
                                }
                            }
                        } else {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    } break;
                    case 't': {
                        // AM/PM designator
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        if (token_len == 1) {
                            if (!omni::internal::date_time_format::date_time_parse::match_abbreviated_time_mark(str, dtfi, tempTimeMark)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                        } else {
                            if (!omni::internal::date_time_format::date_time_parse::match_time_mark(str, dtfi, tempTimeMark)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                        }

                        if (parseInfo.time_mark == time_mark::NOT_SET) {
                            parseInfo.time_mark = tempTimeMark;
                        }
                        else {
                            if (parseInfo.time_mark != tempTimeMark) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                                return false;
                            }
                        }
                    } break;
                    case 'z': {
                        // timezone offset
                        token_len = static_cast<int64_t>(format.get_repeat_count());
                        {
                            omni::chrono::time_span tempTimeZoneOffset = omni::chrono::time_span::zero();
                            if (!omni::internal::date_time_format::date_time_parse::parse_time_zone_offset(str, static_cast<std::size_t>(token_len), tempTimeZoneOffset)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                            if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0 && tempTimeZoneOffset != result.time_zone_offset) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                                return false;
                            }
                            result.time_zone_offset = tempTimeZoneOffset;
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                        }
                    } break;
                    case 'Z': {
                        if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0 && result.time_zone_offset != omni::chrono::time_span::zero()) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                            return false;
                        }

                        result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                        result.time_zone_offset = omni::chrono::time_span::zero();
                        result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_UTC);

                        // The updating of the indexes is to reflect that parse_exact MatchXXX methods assume that
                        // they need to increment the index and Parse GetXXX do not. Since we are calling a Parse
                        // method from inside parse_exact we need to adjust this. Long term, we should try to
                        // eliminate this discrepancy.
                        str.index++;
                        if (!omni::internal::date_time_format::date_time_parse::get_time_zone_name(str)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                        str.index--;
                    } break;
                    case 'K': {
                        // This should parse either as a blank, the 'Z' character or a local offset like "-07:00"
                        if (str.match('Z')) {
                            if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0 && result.time_zone_offset != omni::chrono::time_span::zero()) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                                return false;
                            }

                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                            result.time_zone_offset = omni::chrono::time_span::zero();
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_UTC);
                        }
                        else if (str.match('+') || str.match('-')) {
                            --str.index; // Put the character back for the parser
                            omni::chrono::time_span tempTimeZoneOffset = omni::chrono::time_span::zero();
                            if (!omni::internal::date_time_format::date_time_parse::parse_time_zone_offset(str, 3, tempTimeZoneOffset)) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                            if ((result.flags & omni::internal::date_time_format::parse_flags::TIMEZONE_USED) != 0 && tempTimeZoneOffset != result.time_zone_offset) {
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_RepeatDateTimePattern");
                                return false;
                            }
                            result.time_zone_offset = tempTimeZoneOffset;
                            result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                        }
                        // Otherwise it is unspecified and we consume no characters
                    } break;
                    case ':': {
                        // We match the separator in time pattern with the character in the time string if both equal to ':' or the date separator is matching the characters in the date string
                        // We have to exclude the case when the time separator is more than one character and starts with ':' something like "::" for instance.
                        if (((dtfi.time_separator.size() > 1 && dtfi.time_separator[0] == ':') || !str.match(':')) &&
                            !str.match(dtfi.time_separator)) {
                            // A time separator is expected.
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    } break;
                    case '/': {
                        // We match the separator in date pattern with the character in the date string if both equal to '/' or the date separator is matching the characters in the date string
                        // We have to exclude the case when the date separator is more than one character and starts with '/' something like "//" for instance.
                        if (((dtfi.date_separator.size() > 1 && dtfi.date_separator[0] == '/') || !str.match('/')) &&
                            !str.match(dtfi.date_separator))
                        {
                            // A date separator is expected.
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    } break;
                    case '\"':
                    case '\'': {
                        std::stringstream enquotedString;
                        // Use ParseQuoteString so that we can handle escape characters within the quoted string.
                        if (!omni::internal::date_time_format::date_time_parse::try_parse_quote_string(format.value, static_cast<std::size_t>(format.index), enquotedString, token_len)) {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_WITH_PARAMETER, "Format_BadQuote");
                            return false;
                        }
                        format.index += token_len - 1;

                        // Some cultures uses space in the quoted string.  E.g. Spanish has long date format as:
                        // "dddd, dd' de 'MMMM' de 'yyyy".  When inner spaces flag is set, we should skip whitespaces if there is space
                        // in the quoted string.
                        std::string quotedStr = enquotedString.str();

                        for (std::size_t i = 0; i < quotedStr.size(); ++i) {
                            if (quotedStr[i] == ' ' && parseInfo.allow_inner_ws) {
                                str.skip_white_spaces();
                            } else if (!str.match(quotedStr[i])) {
                                // Can not find the matching quoted string.
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                        }

                        // The "r" and "u" formats incorrectly quoted 'GMT' and 'Z', respectively.  We cannot
                        // correct this mistake for DateTime.parse_exact for compatibility reasons, but we can
                        // fix it for DateTimeOffset.parse_exact as DateTimeOffset has not been publicly released
                        // with this issue.
                        if ((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) {
                            if ((result.flags & omni::internal::date_time_format::parse_flags::RFC1123_PATTERN) != 0 && quotedStr == OMNI_DATE_INTERNAL_GMT_NAME_FW) {
                                result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                                result.time_zone_offset = omni::chrono::time_span::zero();
                            }
                            else if ((result.flags & omni::internal::date_time_format::parse_flags::UTC_SORT_PATTERN) != 0 && quotedStr == OMNI_DATE_ZULU_NAME_FW) {
                                result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                                result.time_zone_offset = omni::chrono::time_span::zero();
                            }
                        }

                    } break;
                    case '%': {
                        // Skip this so we can get to the next pattern character.
                        // Used in case like "%d", "%y"

                        // Make sure the next character is not a '%' again.
                        if (static_cast<std::size_t>(format.index) >= format.value.size() - 1 || format.value[static_cast<std::size_t>(format.index + 1)] == '%') {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadFormatSpecifier");
                            return false;
                        }
                    } break;
                    case '\\': {
                        // Escape character. For example, "\d".
                        // Get the next character in format, and see if we can
                        // find a match in str.
                        if (format.get_next()) {
                            if (!str.match(format.get_char())) {
                                // Can not find a match for the escaped character.
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                        } else {
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadFormatSpecifier");
                            return false;
                        }
                    } break;
                    case '.': {
                        if (!str.match(ch)) {
                            if (format.get_next()) {
                                // If we encounter the pattern ".F", and the dot is not present, it is an optional
                                // second fraction and we can skip this format.
                                if (format.match('F')) {
                                    format.get_repeat_count();
                                    break;
                                }
                            }
                            result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                            return false;
                        }
                    } break;
                    default: {
                        if (ch == ' ') {
                            if (parseInfo.allow_inner_ws) {
                                // Skip whitespaces if AllowInnerWhite.
                                // Do nothing here.
                            } else {
                                if (!str.match(ch)) {
                                    // If the space does not match, and trailing space is allowed, we do
                                    // one more step to see if the next format character can lead to
                                    // successful parsing.
                                    // This is used to deal with special case that a empty string can match
                                    // a specific pattern.
                                    // The example here is af-ZA, which has a time format like "hh:mm:ss tt".  However,
                                    // its AM symbol is "" (empty string).  If allow_trailing_ws is used, and time is in
                                    // the AM, we will trim the whitespaces at the end, which will lead to a failure
                                    // when we are trying to match the space before "tt".
                                    if (parseInfo.allow_trailing_ws) {
                                        if (format.get_next()) {
                                            if (omni::internal::date_time_format::date_time_parse::parse_by_format(str, format, parseInfo, dtfi, result)) {
                                                return true;
                                            }
                                        }
                                    }
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                                // Found a match.
                            }
                        } else {
                            std::string gmnm = OMNI_DATE_INTERNAL_GMT_NAME_FW;
                            if (format.match_specified_word(gmnm)) {
                                format.index += (gmnm.size() - 1);
                                // Found GMT string in format.  This means the DateTime string
                                // is in GMT timezone.
                                result.flags = static_cast<parse_flags::enum_t>(result.flags | omni::internal::date_time_format::parse_flags::TIMEZONE_USED);
                                result.time_zone_offset = omni::chrono::time_span::zero();
                                if (!str.match(gmnm)) {
                                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                    return false;
                                }
                            } else if (!str.match(ch)) {
                                // ch is expected.
                                result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                                return false;
                            }
                        }
                    } break;
                } // switch
                return true;
            }

            bool do_string_parse(const std::string& s, std::string format_param, const omni::chrono::date_time_styles& styles, omni::internal::date_time_format::format_info& dtfi, omni::internal::date_time_format::parse_result& result)
            {
                omni::internal::date_time_format::date_time_parse::parsing_info parseInfo;
                parseInfo.init();

                // parseInfo.calendar = dtfi.Calendar;
                parseInfo.allow_inner_ws = ((styles & omni::chrono::date_time_styles::ALLOW_INNER_WHITE) != 0);
                parseInfo.allow_trailing_ws = ((styles & omni::chrono::date_time_styles::ALLOW_TRAILING_WHITE) != 0);

                // We need the original values of the following two below.
                std::string originalFormat = format_param;

                if (format_param.size() == 1) {
                    if (((result.flags & omni::internal::date_time_format::parse_flags::CAPTURE_OFFSET) != 0) && format_param[0] == 'U') {
                        // The 'U' format is not allowed for DateTimeOffset
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadFormatSpecifier");
                        return false;
                    }
                    format_param = omni::internal::date_time_format::date_time_parse::expand_predefined_format(format_param, dtfi, parseInfo, result);
                }

                bool is_time_only = false;

                // Reset these values to negative one so that we could throw exception
                // if we have parsed every item twice.
                result.hour = result.minute = result.second = -1;

                omni::internal::date_time_format::__dt_string format(format_param, dtfi, false);
                omni::internal::date_time_format::__dt_string str(s, dtfi, false);

                if (parseInfo.allow_trailing_ws) {
                    // Trim trailing spaces if AllowTrailingWhite.
                    format.trim_tail();
                    format.remove_trailing_in_quote_spaces();
                    str.trim_tail();
                }

                if ((styles & omni::chrono::date_time_styles::ALLOW_LEADING_WHITE) != 0) {
                    format.skip_white_spaces();
                    format.remove_leading_in_quote_spaces();
                    str.skip_white_spaces();
                }

                //
                // Scan every character in format and match the pattern in str.
                //
                while (format.get_next()) {
                    // We trim inner spaces here, so that we will not eat trailing spaces when
                    // AllowTrailingWhite is not used.
                    if (parseInfo.allow_inner_ws) {
                        str.skip_white_spaces();
                    }
                    if (!omni::internal::date_time_format::date_time_parse::parse_by_format(str, format, parseInfo, dtfi, result)) {
                        return false;
                    }
                }

                if (static_cast<std::size_t>(str.index) < str.value.size() - 1) {
                    // There are still remaining character in str.
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                    return false;
                }

                if (parseInfo.use_two_digit_year && ((dtfi.fmt_flags & format_flags::USE_HEBREW_RULE) == 0)) {
                    // A two digit year value is expected. Check if the parsed year value is valid.
                    if (result.year >= 100) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    if ((result.year < 1) || (result.year > OMNI_DATE_MAX_YEAR)) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    result.year = static_cast<int16_t>(omni::chrono::date_time::to_four_digit_year(static_cast<uint16_t>(result.year)));
                }

                
                if (parseInfo.use_hour_12) {
                    if (parseInfo.time_mark == date_time_format::time_mark::NOT_SET) {
                        // hh is used, but no AM/PM designator is specified.
                        // Assume the time is AM.
                        // Don't throw exceptions in here because it is very confusing for the caller.
                        // I always got confused myself when I use "hh:mm:ss" to parse a time string,
                        // and parse_exact() throws on me (because I didn't use the 24-hour clock 'HH').
                        parseInfo.time_mark = date_time_format::time_mark::AM;
                    }
                    if (result.hour > 12) {
                        // AM/PM is used, but the value for HH is too big.
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                    if (parseInfo.time_mark == date_time_format::time_mark::AM) {
                        if (result.hour == 12) {
                            result.hour = 0;
                        }
                    } else {
                        result.hour = (result.hour == 12) ? 12 : result.hour + 12;
                    }
                } else {
                    // Military (24-hour time) mode
                    //
                    // AM cannot be set with a 24-hour time like 17:15.
                    // PM cannot be set with a 24-hour time like 03:15.
                    if ((parseInfo.time_mark == date_time_format::time_mark::AM && result.hour >= 12) ||
                        (parseInfo.time_mark == date_time_format::time_mark::PM && result.hour <  12))
                    {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                        return false;
                    }
                }


                // Check if the parsed string only contains hour/minute/second values.
                is_time_only = (result.year == -1 && result.month == -1 && result.day == -1);
                if (!omni::internal::date_time_format::check_default_date_time(result, styles)) {
                    return false;
                }

                if (!omni::chrono::date_time::try_create(static_cast<uint16_t>(result.year), static_cast<uint16_t>(result.month), static_cast<uint16_t>(result.day), static_cast<uint16_t>(result.hour), static_cast<uint16_t>(result.minute), static_cast<uint16_t>(result.second), 0, result.parsed_date)) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT_BAD_DATE_TIME_CALENDAR, "Format_BadDateTimeCalendar");
                    return false;
                }
                if (result.fraction > 0) {
                    result.parsed_date = result.parsed_date.add_ticks(static_cast<int64_t>(omni::math::round(result.fraction * OMNI_TICKS_PER_SECOND)));
                }

                // We have to check day of week before we adjust to the time zone.
                // It is because the value of day of week may change after adjusting
                // to the time zone.
                if (parseInfo.day_of_week != -1) {
                    // Check if day of week is correct.
                    if (parseInfo.day_of_week != static_cast<int64_t>(result.parsed_date.day_of_week())) {
                        result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDayOfWeek");
                        return false;
                    }
                }


                if (!omni::internal::date_time_format::determine_time_zone_adjustments(result, styles, is_time_only)) {
                    return false;
                }
                return true;
            }

            bool try_parse_exact(const std::string& s, const std::string& format, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& style, omni::internal::date_time_format::parse_result& result)
            {
                if (s.empty()) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadDateTime");
                    return false;
                }
                if (format.empty()) {
                    result.set_failure(omni::chrono::date_time_parse_failure::FORMAT, "Format_BadFormatSpecifier");
                    return false;
                }
                return omni::internal::date_time_format::date_time_parse::do_string_parse(s, format, style, dtfi, result);
            }

            bool try_parse_exact(const std::string& s, const std::string& format, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result)
            {
                omni::internal::date_time_format::parse_result result_data; // The buffer to store the parsing result.
                if (omni::internal::date_time_format::date_time_parse::try_parse_exact(s, format, dtfi, style, result_data)) {
                    result = result_data.parsed_date;
                    return true;
                }
                result = omni::chrono::date_time::min_value();
                return false;
            }

            bool try_parse_exact(const std::string& s, const std::string& format, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason)
            {
                omni::internal::date_time_format::parse_result result_data; // The buffer to store the parsing result.
                fail_reason = omni::chrono::date_time_parse_failure::NONE;
                if (omni::internal::date_time_format::date_time_parse::try_parse_exact(s, format, dtfi, style, result_data)) {
                    result = result_data.parsed_date;
                    return true;
                }
                fail_reason = result_data.failure;
                result = omni::chrono::date_time::min_value();
                return false;
            }
            
            omni::chrono::date_time parse_exact(const std::string& s, const std::string& format, omni::internal::date_time_format::format_info& dtfi, const omni::chrono::date_time_styles& style)
            {
                omni::internal::date_time_format::parse_result result; // The buffer to store the parsing result.
                if (omni::internal::date_time_format::date_time_parse::try_parse_exact(s, format, dtfi, style, result)) {
                    return result.parsed_date;
                }
                OMNI_ERR_RETV_FW("Invalid date time string detected", omni::exceptions::invalid_parse(), omni::chrono::date_time())
            }
        }
    }
} }
