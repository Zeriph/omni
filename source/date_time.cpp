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
#define OMNI_MAX_MILLIS_FW static_cast<int64_t>(OMNI_MILLISECONDS_TO_10000AD)
#define OMNI_MAX_TICKS_FW OMNI_TICKS_TO_10000AD
#define OMNI_TS_NULL_OFF_FW omni::chrono::time_span::min_value()

#define OMNI_MAX_DATE_OFFSET_FW 504000000000 // OMNI_TICKS_PER_HOUR * 14 
#define OMNI_MIN_DATE_OFFSET_FW -OMNI_MAX_DATE_OFFSET_FW

#define OMNI_DATE_ERA_FW "A.D."
#define OMNI_DATE_ERA_ABBR_FW "AD"
#define OMNI_DATE_FORMAT_INFO_AM_FW "AM"
#define OMNI_DATE_FORMAT_INFO_PM_FW "PM"
#define OMNI_DATE_ZULU_NAME_FW "Z"

#define OMNI_DATE_DATA_HXX_FW
#include <omni/xx/date_data.hxx>
#undef OMNI_DATE_DATA_HXX_FW

static std::string omni_date_time_format_day_of_week(int32_t day_of_week, int32_t repeat)
{
    if (repeat == 3) {
        return omni::cstring::to_title_case(
            omni::chrono::day_of_week::get_abbreviated_name(static_cast<omni::chrono::day_of_week::enum_t>(day_of_week))
        );
    }
    return omni::cstring::to_title_case(
        omni::chrono::day_of_week::to_string(static_cast<omni::chrono::day_of_week::enum_t>(day_of_week))
    );
}

static std::string omni_date_time_format_month(int32_t month, int32_t repeat)
{
    if (repeat == 3) {
        return omni::cstring::to_title_case(
            omni::chrono::month_of_year::get_abbreviated_name(static_cast<omni::chrono::month_of_year::enum_t>(month))
        );
    }
    return omni::cstring::to_title_case(
        omni::chrono::month_of_year::to_string(static_cast<omni::chrono::month_of_year::enum_t>(month))
    );
}

// The pos should point to a quote character. This method will get the std::string enclosed by the quote character.
static int32_t omni_date_time_format_parse_quote_str(const std::string& format, int32_t pos, std::stringstream& result)
{
    // DEV_NOTE: pos will be the index of the quote character in the 'format' string.
    int32_t begin = pos;
    char quote = format[static_cast<std::size_t>(pos++)]; // Get the character used to quote the following string.
    bool found = false;
    char next;
    while (static_cast<std::size_t>(pos) < format.size()) {
        next = format[static_cast<std::size_t>(pos++)];        
        if (next == quote) {
            found = true;
            break;
        } else if (next == '\\') {
            // The following are used to support escaped character.
            // Escaped character is also supported in the quoted string.
            // Therefore, someone can use a format like "'minute:' mm\"" to display:
            // minute: 45"
            // because the second double quote is escaped.
            if (static_cast<std::size_t>(pos) < format.size()) {
                result << format[static_cast<std::size_t>(pos++)];
            } else {
                // This means that '\' is at the end of the formatting string.
                OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
            }                    
        } else {
            result << next;
        }
    }
    if (!found) {
        // Here we can't find the matching quote.
        OMNI_ERR_RETV_FW("Invalid string format: bad quote", omni::exceptions::invalid_string_format(), std::string())
    }
    // Return the character count including the begin/end quote characters and enclosed string.
    return (pos - begin);
}

/*
    Get the next character at the index of 'pos' in the 'format' string.
    Return value of -1 means 'pos' is already at the end of the 'format' string.
    Otherwise, return value is the int32_t value of the next character.
*/
static int32_t omni_date_time_format_parse_next_char(const std::string& format, int32_t pos)
{
    if (static_cast<std::size_t>(pos) >= format.size() - 1) {
        return -1;
    }
    return static_cast<int32_t>(format[static_cast<std::size_t>(pos+1)]);
}

static void omni_date_time_format_digits(std::stringstream& output, int32_t value, int32_t len, bool override_length_limit)
{
    // Limit the use of this function to be two-digits, so that we have the same behaviour as RTM bits.
    if (!override_length_limit && len > 2) {
        len = 2;
    }
    char* buffer = new char[16];
    char* p = buffer + 16;
    int32_t n = value;
    do {
        *--p = static_cast<char>(n % 10 + '0');
        n /= 10;
    } while ((n != 0) && (p > buffer));
    
    /*
        If the repeat count is greater than 0, we're trying
        to emulate the "00" format, so we have to prepend
        a zero if the string only has one character.
    */
    int32_t digits = static_cast<int32_t>(buffer + 16 - p);
    while ((digits < len) && (p > buffer)) {
        *--p = '0';
        ++digits;
    }
    for (n = 0; n < digits; ++n) {
        output << *p;
        ++p;
    }
    delete[] buffer;
}

/* 
    FORMAT the positive integer value to a std::string and prefix with assigned 
    length of leading zero.

    Parameters:
    value: The value to format
    len: The maximum length for leading zero.  
    If the digits of the value is greater than len, no leading zero is added.

    Notes: 
    The function can format to Int32.MaxValue.
*/
static void omni_date_time_format_digits(std::stringstream& output, int32_t value, int32_t len)
{
    omni_date_time_format_digits(output, value, len, false);
}

static int32_t omni_date_time_format_parse_repeat_pattern(const std::string& format, int32_t pos, char pattern)
{
    int32_t index = pos + 1;
    while ((static_cast<std::size_t>(index) < format.size()) && (format[static_cast<std::size_t>(index)] == pattern)) {
        ++index;
    }    
    return (index - pos);
}

static bool omni_date_time_internal_offset_from_utc(double* offset)
{
    bool is_dst = false;
    #if defined(OMNI_OS_WIN)
        TIME_ZONE_INFORMATION tz_info;
        DWORD err = ::GetTimeZoneInformation(&tz_info);
        is_dst = (err == TIME_ZONE_ID_DAYLIGHT);
        if (err == TIME_ZONE_ID_INVALID) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }

        FILETIME utc, curr;
        ::GetSystemTimeAsFileTime(&utc);
        SYSTEMTIME local;
        ::GetLocalTime(&local);
        if (::SystemTimeToFileTime(&local, &curr) == 0) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }
        *offset = (tz_info.Bias * 60);
        if (is_dst) {
            *offset -= 3600;
            if (::CompareFileTime(&curr, &utc) < 0) {
                *offset = -*offset;
            }
        }
    #else
        time_t curr;
        if (::time(&curr) == static_cast<time_t>(-1)) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }
        struct tm* timeinfo = ::gmtime(&curr);
        if (timeinfo == NULL) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }
        time_t utc = ::mktime(timeinfo);
        if (utc == static_cast<time_t>(-1)) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }
        timeinfo = ::localtime(&curr);
        if (timeinfo == NULL) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }
        time_t local = ::mktime(timeinfo);
        if (local == static_cast<time_t>(-1)) {
            OMNI_ERRV_RETV_FW("An error occurred getting the time zone info: ", OMNI_GLE, omni::exceptions::clock_exception(OMNI_GLE), false)
        }
        *offset = ::difftime(local, utc);
        if (timeinfo->tm_isdst) {
            // if DST subtract 1 hour. If offset < 0, we need to "add" to have it subtract
            if (*offset > 0) {
                *offset -= 3600;
            } else {
                *offset += 3600;
            }
            is_dst = true;
        }
    #endif
    return is_dst;
}

// output the 'z' family of formats, which output a the offset from UTC, e.g. "-07:30"
static void omni_date_time_format_customized_timezone(const omni::chrono::date_time& dt, const std::string& format, int32_t token_len, bool time_only, std::stringstream& result)
{
    omni::chrono::time_span offset;
    OMNI_UNUSED(format);
    // No offset. The instance is a DateTime and the output should be the local time zone
    if (time_only && dt.ticks() < OMNI_TICKS_PER_DAY) {
        // For time only format and a time only input, the time offset on 0001/01/01 is less 
        // accurate than the system's current offset because of daylight saving time.
        double offset_utc = 0;
        omni_date_time_internal_offset_from_utc(&offset_utc);
        offset = static_cast<omni::chrono::time_span::span_t>(offset_utc * OMNI_TICKS_PER_SECOND);
    } else if (dt.kind() == omni::chrono::date_time_kind::UTC) {
        offset = omni::chrono::time_span::zero();
    } else {
        double offset_utc = 0;
        omni_date_time_internal_offset_from_utc(&offset_utc);
        offset = static_cast<omni::chrono::time_span::span_t>(offset_utc * OMNI_TICKS_PER_SECOND);
    }
    
    if (offset >= omni::chrono::time_span::zero()) {
        result << '+';
    } else {
        result << '-';
        // get a positive offset, so that you don't need a separate code path for the negative numbers.
        offset = offset.negate();
    }

    if (token_len <= 1) {
        // 'z' format e.g "-7"
        result << offset.hours();
    } else {
        // 'zz' or longer format e.g "-07"
        if (offset.hours() < 10) {
            result << "0";
        }
        result << offset.hours();
        if (token_len >= 3) {
            // 'zzz*' or longer format e.g "-07:30"
            result << ":";
            if (offset.minutes() < 10) {
                result << "0";
            }
            result << offset.minutes();
        }
    }        
}

// output the 'K' format, which is for round-tripping the data
static void omni_date_time_format_customized_roundtrip_timezone(const omni::chrono::date_time& dt, std::stringstream& result)
{
    /*
        The objective of this format is to round trip the data in the type
        For DateTime it should round-trip the Kind value and preserve the time zone. 
        DateTimeOffset instance, it should do so by using the time zone.
    */
    
    omni::chrono::time_span offset;
    // source is a date time, so behaviour depends on the kind.
    if (dt.kind() == omni::chrono::date_time_kind::LOCAL) {
        // This should output the local offset, e.g. "-07:30"
        double offset_utc = 0;
        omni_date_time_internal_offset_from_utc(&offset_utc);
        offset = omni::chrono::time_span::from_seconds(offset_utc);
    } else if (dt.kind() == omni::chrono::date_time_kind::UTC) {
        // The 'Z' constant is a marker for a UTC date
        result << OMNI_DATE_ZULU_NAME_FW;
    }
    if (offset >= omni::chrono::time_span::zero()) {
        result << '+';
    } else {
        result << '-';
        // get a positive offset, so that you don't need a separate code path for the negative numbers.
        offset = offset.negate();
    }

    omni::chrono::time_span::span_t hours = offset.hours();
    omni::chrono::time_span::span_t minutes = offset.minutes();
    if (hours < 10) {
        result << "0";
    }
    result << hours;
    result << ":";
    if (minutes < 10) {
        result << "0";
    }
    result << minutes;
}

static std::string omni_date_time_format_customized(const omni::chrono::date_time& dt_val, const std::string& format)
{
    // the default is `M/d/yyyy h:mm:ss tt`
    
    std::stringstream result;
    // This is a flag to indicate if we are formatting hour/minute/second only.
    bool time_only = true;
    int32_t i = 0, token_len = 0, hour12 = 0;
    int32_t month = dt_val.month();
    int32_t year = dt_val.year();
    int32_t next_char;
    while (static_cast<std::size_t>(i) < format.size()) {
        char ch = format[static_cast<std::size_t>(i)];
        std::stringstream enquoted_str;
        switch (ch) {
            case 'g':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                result << OMNI_DATE_ERA_FW;
                break;
            case 'h':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                hour12 = dt_val.hour() % 12;
                if (hour12 == 0) {
                    hour12 = 12;
                }
                omni_date_time_format_digits(result, hour12, token_len);
                break;
            case 'H':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                omni_date_time_format_digits(result, dt_val.hour(), token_len);
                break;
            case 'm':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                omni_date_time_format_digits(result, dt_val.minute(), token_len);
                break;
            case 's':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                omni_date_time_format_digits(result, dt_val.second(), token_len);
                break;
            case 'f': case 'F':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                if (token_len <= 7) { // 7 = MAX_SECONDS_FRACTION_DIGIT
                    // const std::string fixed_num_formats[] = { "0", "00", "000", "0000", "00000", "000000", "0000000" };
                    int64_t fraction = static_cast<int64_t>(dt_val.ticks() % OMNI_TICKS_PER_SECOND);
                    fraction = fraction / static_cast<int64_t>(std::pow(static_cast<double>(10), static_cast<double>(7 - token_len)));
                    if (ch == 'f') {
                        result << omni::cstring::pad_left(omni::cstring::to_string(fraction), '0', static_cast<std::size_t>(token_len));
                    } else {
                        int32_t effective_digits = token_len;
                        while (effective_digits > 0) {
                            if (fraction % 10 == 0) {
                                fraction = fraction / 10;
                                --effective_digits;
                            } else {
                                break;
                            }
                        }
                        if (effective_digits > 0) {
                            result << omni::cstring::pad_left(omni::cstring::to_string(fraction), '0', static_cast<std::size_t>(effective_digits - 1));
                        } else {
                            // No fraction to emit, so see if we should remove decimal also.
                            if (result.str().size() > 0 && result.str()[result.str().size() - 1] == '.') {
                                std::string str = result.str();
                                result.str(str.substr(0, str.size() - 1));
                            }
                        }
                    }
                } else {
                    OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                }
                break;
            case 't':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                if (token_len == 1) {
                    result << (dt_val.hour() < 12 ? "A" : "P");
                } else {
                    result << (dt_val.hour() < 12 ? OMNI_DATE_FORMAT_INFO_AM_FW : OMNI_DATE_FORMAT_INFO_PM_FW);
                }
                break;
            case 'd':
                /*
                    token_len == 1 : Day of month as digits with no leading zero.
                    token_len == 2 : Day of month as digits with leading zero for single-digit months.
                    token_len == 3 : Day of week as a three-letter abbreviation.
                    token_len >= 4 : Day of week as its full name.
                */
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                if (token_len <= 2) {
                    omni_date_time_format_digits(result, dt_val.day(), token_len);
                }  else {
                    result << (omni_date_time_format_day_of_week(dt_val.day_of_week(), token_len));
                }
                time_only = false;
                break;
            case 'M':
                /* 
                    token_len == 1 : Month as digits with no leading zero.
                    token_len == 2 : Month as digits with leading zero for single-digit months.
                    token_len == 3 : Month as a three-letter abbreviation.
                    token_len >= 4 : Month as its full name.
                */
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                if (token_len <= 2) {
                    omni_date_time_format_digits(result, month, token_len);
                } else {
                    result << (omni_date_time_format_month(month, token_len));
                }
                time_only = false;
                break;
            case 'y':
                /*
                    Notes about OS behaviour:
                    y: Always print (year % 100). No leading zero.
                    yy: Always print (year % 100) with leading zero.
                    yyy/yyyy/yyyyy/... : Print year value.  No leading zero.
                */
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                if (token_len <= 2) {
                    omni_date_time_format_digits(result, year % 100, token_len);
                } else {
                    // std::string fmtPattern = "D" + token_len; <- C# format D means decimal (e.g. 12345)
                    // result << (year.ToString(fmtPattern, CultureInfo.InvariantCulture));
                    result << omni::cstring::pad_left(omni::cstring::to_string(year), '0', static_cast<std::size_t>(token_len));
                }
                time_only = false;
                break;
            case 'z':
                token_len = omni_date_time_format_parse_repeat_pattern(format, i, ch);
                omni_date_time_format_customized_timezone(dt_val, format, token_len, time_only, result);
                break;
            case 'K':
                token_len = 1;
                omni_date_time_format_customized_roundtrip_timezone(dt_val, result);
                break;
            case ':':
                result << ":";
                token_len = 1;
                break;
            case '/':
                result << "/";
                token_len = 1;
                break;
            case '\'': case '\"':
                token_len = omni_date_time_format_parse_quote_str(format, i, enquoted_str); 
                result << enquoted_str.str();
                break;
            case '%':
                /*
                    Optional format character.
                    For example, format std::string "%d" will print day of month 
                    without leading zero.  Most of the cases, "%" can be ignored.
                */
                next_char = omni_date_time_format_parse_next_char(format, i);
                // next_char will be -1 if we already reach the end of the format string. Besides, we will not allow "%%" appear in the pattern.
                if (next_char >= 0 && next_char != static_cast<int32_t>('%')) {
                    result << (omni_date_time_format_customized(dt_val, omni::string_util::to_string(static_cast<char>(next_char))));
                    token_len = 2;
                } else {
                    // This means that '%' is at the end of the format std::string or "%%" appears in the format string.
                    OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                }
                break;
            case '\\':
                /*
                    Escaped character.  Can be used to insert character into the format string.
                    For example, "\d" will insert the character 'd' into the string.
                    DEV_NOTE : we can remove this format character if we enforce the enforced quote character rule.
                    That is, we ask everyone to use single quote or double quote to insert characters,
                    then we can remove this character.
                */
                next_char = omni_date_time_format_parse_next_char(format, i);
                if (next_char >= 0) {
                    result << ((static_cast<char>(next_char)));
                    token_len = 2;
                } else {
                    // This means that '\' is at the end of the formatting string.
                    OMNI_ERR_RETV_FW("Invalid string format", omni::exceptions::invalid_string_format(), std::string())
                }
                break;
            default:
                /*
                    DEV_NOTE : we can remove this rule if we enforce the enforced quote character rule.
                    That is, if we ask everyone to use single quote or double quote to insert characters,
                    then we can remove this default block.
                */
                result << ch;
                token_len = 1;
                break;
        }
        i += token_len;
    }
    return result.str();
}

/*
    // Formats
    invariant.saShortDates          = new String[] { "MM/dd/yyyy", "yyyy-MM-dd" };          // short date format
    invariant.saLongDates           = new String[] { "dddd, dd MMMM yyyy"};                 // long date format
    invariant.saYearMonths          = new String[] { "yyyy MMMM" };                         // year month format
    invariant.sMonthDay             = "MMMM dd";                                            // Month day pattern
    invariant.sAM1159 = "AM";                   // AM designator
    invariant.sPM2359 = "PM";                   // PM designator
    invariant.saLongTimes = new String[] { "HH:mm:ss" };                             // time format
    invariant.saShortTimes = new String[] { "HH:mm", "hh:mm tt", "H:mm", "h:mm tt" }; // short time format
    invariant.saDurationFormats = new String[] { "HH:mm:ss" };                             // time duration format

    internal const String rfc1123Pattern   = "ddd, dd MMM yyyy HH':'mm':'ss 'GMT'";

    // The sortable pattern is based on ISO 8601.
    internal const String sortableDateTimePattern = "yyyy'-'MM'-'dd'T'HH':'mm':'ss";
    internal const String universalSortableDateTimePattern = "yyyy'-'MM'-'dd HH':'mm':'ss'Z'";

    internal const String RoundtripFormat = "yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK";
    internal const String RoundtripDateTimeUnfixed = "yyyy'-'MM'-'ddTHH':'mm':'ss zzz";
*/
static std::string omni_date_time_get_real_format(char format)
{
    switch (format) {
        case 'd': // Short Date
            return "M/d/yyyy"; // "yyyy-MM-dd" for other "calendars"
        case 'D': // Long Date
            return "dddd, MMMM d, yyyy";
        case 'f': // Full (long date + short time)
            return "dddd, MMMM d, yyyy h:mm tt";
        case 'F': // Full (long date + long time)
            return "dddd, MMMM d, yyyy h:mm:ss tt";
        case 'g': // General (short date + short time)
            return "M/d/yyyy h:mm";
        case 'G': // General (short date + long time)
            return "M/d/yyyy h:mm:ss tt";
        case 'm': case 'M': // Month/Day Date
            return "MMMM d";
        case 'o': case 'O': // RoundtripFormat;
            return "yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK";
        case 'r': case 'R': // RFC 1123 Standard
            return "ddd, dd MMM yyyy HH':'mm':'ss 'GMT'";
        case 's': // Sortable without Time Zone Info
            return "yyyy'-'MM'-'dd'T'HH':'mm':'ss";
        case 't': // Short Time
            return "h:mm tt";
        case 'T': // Long Time
            return "h:mm:ss tt";
        case 'u': // Universal with Sortable format
            return "yyyy'-'MM'-'dd HH':'mm':'ss'Z'";
        case 'U': // Universal with Full (long date + long time) format
            return "dddd, MMMM d, yyyy H:mm:ss tt";
        case 'y': case 'Y': // Year/Month Date
            return "MMMM yyyy";
        default: // error
            OMNI_ERR_RETV_FW("Invalid string format for date_time", omni::exceptions::invalid_string_format(), std::string())
    }
    return "";
}

static std::string omni_date_time_format(const omni::chrono::date_time& dt, const std::string& format)
{
    std::string new_format = format;
    if (new_format.empty()) {
        if (dt.ticks() < OMNI_TICKS_PER_DAY) {
            // If the time is less than 1 day, consider it as time of day; just print out the short time format.
            new_format = "s";
        } else {
            new_format = "G";
        }
    }
    bool is_utc = false;
    if (new_format.size() == 1) {
        if (new_format[0] == 'U') {
            is_utc = true;
        }
        new_format = omni_date_time_get_real_format(new_format[0]);
    }
    return is_utc ?
        omni_date_time_format_customized(dt.to_universal_time(), new_format) :
        omni_date_time_format_customized(dt, new_format);
}

static omni::chrono::date_time omni_chrono_date_time_internal_offset(omni::chrono::date_time& obj, const omni::chrono::span_t& offset)
{
    if (offset.ticks() != 0) {
        obj += offset;
    }
    return obj;
}

static uint64_t omni_date_time_internal_get_ticks()
{
    #if defined(OMNI_OS_WIN)
        FILETIME ft;
        ::GetSystemTimeAsFileTime(&ft);
        ULARGE_INTEGER tm;
        tm.LowPart = ft.dwLowDateTime;
        tm.HighPart = ft.dwHighDateTime;
        return static_cast<uint64_t>(tm.QuadPart) + OMNI_FILE_TIME_OFFSET;
        /*
            DEV_NOTE: this is from the .NET source

            if (CompatibilitySwitches.IsAppEarlierThanWindowsPhone8) {
                // Windows Phone 7.0/7.1 return the ticks up to millisecond, not up to the 100th nanosecond.
                long ticksms = ticks / TicksPerMillisecond; <- here .. ticksms now == (ticks / TicksPerMillisecond)
                ticks = ticksms * TicksPerMillisecond;      <- so right here, doing ticks = ticksms * TicksPerMillisecond
            }

            this essentially truncates the nanoseconds, but given that Omni will never target Windows Phone, this code is inconsequential
        */
    #else
        struct timespec tm;
        if (::clock_gettime(CLOCK_REALTIME, &tm) != 0) {
            OMNI_ERRV_RETV_FW("An error occurred getting the clock time: ", errno, omni::exceptions::clock_exception(errno), false)
        }
        return static_cast<uint64_t>(
            static_cast<uint64_t>(tm.tv_sec * OMNI_TICKS_PER_SECOND) +
            static_cast<uint64_t>((static_cast<double>(tm.tv_nsec) * OMNI_TICKS_PER_NANOSECOND)) +
            OMNI_EPOCH_OFFSET
        );
    #endif
}

static bool omni_date_time_internal_is_leap_year(uint64_t year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

static bool omni_date_time_internal_check_day_range(uint16_t year, uint16_t month, uint16_t day)
{
    /*
        DEV_NOTE: the C# version throws an exception for Julian days under 1/1/3 .. we'll just return false
    */
    if ((year == 1) && (month == 1) && (day < 3)) {
        return false;
    }
    if ((month < 1) || (month > 12) || (day == 0) || (day > 32)) {
        // only Jan-Dec and there are not months with 32 days (or 0)
        return false;
    }
    /*
        DEV_NOTE: the C# version throws an exception for invalid day range, we'll just return false
    */
    if (omni_date_time_internal_is_leap_year(year)) {
        // leap year
        return day <= (omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1]);
    } else {
        return day <= (omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1]);
    }
    return false;
}

// --- start private ctors ---

// not 'user' accessible as it's used to construct empty (min) DT objects
omni::chrono::date_time::date_time() :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint64_t ticks, const char* non_op) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(ticks)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_UNUSED(non_op);
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(bool is_ambiguous_dst, const omni::chrono::date_time_kind& kind, uint64_t ticks, const char* non_op) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    OMNI_UNUSED(non_op);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    if (kind != omni::chrono::date_time_kind::LOCAL) {
        OMNI_ERR_FW("Invalid enum specified for private constructor", omni::exceptions::invalid_enum())
    }
    this->m_date = (ticks | (is_ambiguous_dst ? OMNI_DATE_KIND_LOCAL_DST_FW : OMNI_DATE_KIND_LOCAL_FW));
    OMNI_D5_FW("created");
}

// --- end private ctors ---

omni::chrono::date_time::date_time(const omni::chrono::date_time& cp) :
    OMNI_CPCTOR_FW(cp)
    m_date(cp._date_value())
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
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
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
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum("Invalid date kind specified"))
    }
    this->m_date = (ticks | (static_cast<uint64_t>(kind.value()) << OMNI_DATE_KIND_SHIFT_FW));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint16_t month, uint16_t day) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    this->m_date = static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    this->m_date = static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
                   static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum("Invalid date kind specified"))
    }
    this->m_date =
    (
        (
            static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
            static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
        ) // ticks
        | // OR'd
        ( // with kind
            static_cast<uint64_t>(kind.value()) << OMNI_DATE_KIND_SHIFT_FW
        )
    );
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (millisecond >= OMNI_MILLISECONDS_PER_SECOND) {
        OMNI_ERR_FW("Invalid milliseconds specified", omni::exceptions::invalid_range("Invalid milliseconds specified"))
    }
    uint64_t ticks = (
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
        static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
    ) + (millisecond * OMNI_TICKS_PER_MILLISECOND);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    this->m_date = ticks;
    OMNI_D5_FW("created");
}

omni::chrono::date_time::date_time(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::date_time_kind& kind) :
    OMNI_CTOR_FW(omni::chrono::date_time)
    m_date(0)
    OMNI_SAFE_DTTMMTX_FW
{
    if (millisecond >= OMNI_MILLISECONDS_PER_SECOND) {
        OMNI_ERR_FW("Invalid milliseconds specified", omni::exceptions::invalid_range("Invalid milliseconds specified"))
    }
    if (!omni::chrono::date_time_kind::is_valid(static_cast<int32_t>(kind.value()))) {
        OMNI_ERR_FW("Invalid date kind specified", omni::exceptions::invalid_enum("Invalid date kind specified"))
    }
    uint64_t ticks = (
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(year, month, day)) +
        static_cast<uint64_t>(omni::chrono::date_time::_time_to_ticks(hour, minute, second))
    ) + (millisecond * OMNI_TICKS_PER_MILLISECOND);
    if (ticks > OMNI_MAX_TICKS_FW) {
        OMNI_ERR_FW("Invalid tick count specified", omni::exceptions::invalid_range("Invalid tick count specified"))
    }
    this->m_date = (ticks | (static_cast<uint64_t>(kind.value()) << OMNI_DATE_KIND_SHIFT_FW));
    OMNI_D5_FW("created");
}

omni::chrono::date_time::~date_time()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

omni::chrono::date_time omni::chrono::date_time::add(const omni::chrono::time_span& value) const
{
    return this->add_ticks(value.ticks());
}

omni::chrono::date_time omni::chrono::date_time::add_days(double value) const
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_DAY);
}

omni::chrono::date_time omni::chrono::date_time::add_hours(double value) const
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_HOUR);
}

omni::chrono::date_time omni::chrono::date_time::add_milliseconds(double value) const
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, 1);
}

omni::chrono::date_time omni::chrono::date_time::add_minutes(double value) const
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_MINUTE);
}

omni::chrono::date_time omni::chrono::date_time::add_months(int32_t months) const
{
    OMNI_DTTM_ALOCK_FW
    if ((months < -120000) || (months > 120000)) {
        OMNI_ERR_RETV_FW("Invalid months specified", omni::exceptions::invalid_range("Invalid months specified"), omni::chrono::date_time())
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
    if (y < 1 || y > OMNI_DATE_MAX_YEAR) {
        OMNI_ERR_RETV_FW("Invalid months specified", omni::exceptions::invalid_range("Invalid months specified"), omni::chrono::date_time())
    }
    int64_t days = omni::chrono::date_time::days_in_month(static_cast<uint16_t>(y), static_cast<uint16_t>(m));
    if (d > days) {
        d = days;
    }
    return omni::chrono::date_time(
        static_cast<uint64_t>(omni::chrono::date_time::_date_to_ticks(static_cast<uint16_t>(y), static_cast<uint16_t>(m), static_cast<uint16_t>(d)) + (this->_ticks() % OMNI_TICKS_PER_DAY))
        | this->_internal_kind()
    );
}

omni::chrono::date_time omni::chrono::date_time::add_seconds(double value) const
{
    OMNI_DTTM_ALOCK_FW
    return this->_add(value, OMNI_MILLISECONDS_PER_SECOND);
}

omni::chrono::date_time omni::chrono::date_time::add_ticks(int64_t value) const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    if ((value > (OMNI_MAX_TICKS_FW - ticks)) || (value < (-ticks)) ) {
        OMNI_ERR_RETV_FW("Invalid ticks specified", omni::exceptions::invalid_range("Invalid ticks specified"), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks + value) | this->_internal_kind());
}

omni::chrono::date_time omni::chrono::date_time::add_years(int16_t value) const
{
    if ((value < -10000) || (value > 10000)) {
        OMNI_ERR_RETV_FW("Invalid years specified", omni::exceptions::invalid_range("Invalid years specified"), omni::chrono::date_time())
    }
    return this->add_months(value * 12);
}

bool omni::chrono::date_time::is_dst() const
{
    OMNI_DTTM_ALOCK_FW
    if (this->_kind() == omni::chrono::date_time_kind::LOCAL_DST) {
        return true;
    }

    /*
        DEV_NOTE: The C# way of handling DST (e.g. Getis_dst/CheckIsDst) seems somewhat convoluted and uses
        the system's timezone info database to more appropriately get whether a date/time is actually DST.
        We're not going "full hog" on the date time class with calendars/zone info etc. right now, so instead
        we're going to implement the "lazy-man's DST calculator" that only looks at US times. If the date falls
        in a "range" of what the US DST standard is, then we just return true.

        There are some carved out exceptions since DST in the US didn't "start" til 1966, but had some odd moments.
        --- see notes/comments below
    */

    uint16_t year = static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW));
    uint16_t month = static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW));
    uint16_t day = static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW));

    if (year < 1966) {
        // summer DST to begin on March 31, 1918 (reverting October 27) .. only during this year
        if (year == 1918) {
            if (((month == 3) && (day == 31)) || ((month > 3) && ((month <= 10) && (day < 27)))) {
                // < 27 because it ENDED the 27th, so does not include the 27th
                return true;
            }
            return false;
        }
        // Feb 9, 1942 -> Sep 30, 1945 == permanent DST
        if (((year >= 1942) && (month >= 2) && (day >= 9)) && ((year <= 1945) && (month <= 9) && (day < 30))) {
            // < 30 because it ENDED the 30th, so does not include the 30th
            return true;
        }
        return false;
    }

    // Jan 6, 1974 -> Apr 27, 1975 == permanent DST
    if (((year >= 1974) && (month >= 1) && (day >= 6)) && ((year <= 1975) && (month <= 4) && (day < 27))) {
        // < 27 because it ENDED the 27th, so does not include the 27th
        return true;
    }

    if (year >= 2007) {
        // Starting 2007, DST begins on the second Sunday of March and ends on the first Sunday of November

        // Jan, Feb, Dec are NOT part of DST
        if ((month <= 2) || (month == 12)) { return false; }
        // Apr -> Oct are
        if ((month >= 4) && (month <= 10)) { return true; }

        // March and November are the "ambiguous" months
    } else {
        // 1986 - 2006, DST started first Sunday in April and to the last Sunday in October
        // 1966 - 1986, DST started last Sunday in April to last Sunday in October

        // Jan, Feb, Mar, Nov, Dec are NOT part of DST
        if ((month <= 3) || (month >= 11)) { return false; }
        // May -> Jul are
        if ((month >= 5) && (month <= 7)) { return true; }

        // April and October are the "ambiguous" months
    }
    
    // dow (day of week): sunday = 0, mon = 1 .. sat = 6
    int16_t prev_sun_date = static_cast<int16_t>(day - static_cast<uint16_t>((this->_ticks() / OMNI_TICKS_PER_DAY + 1) % 7));
    uint16_t hour = static_cast<uint16_t>((this->_ticks() / OMNI_TICKS_PER_HOUR) % 24);

    /*
        2AM            3AM                        1AM              2AM
        |      +1 hr     |                        |       -1 hr      |
        | <invalid time> |                        | <ambiguous time> |
                        [========== DST ========>)
        
        3AM -starts- DST because at 2, the clock rolls up, so there is no 2AM
        
        1AM is -ambiguous- because at 2 the clock rolls back, so it *could* be 1:30 and -not- DST
    */

    if (year >= 2007) {
        // Starting 2007, DST begins on the second Sunday of March and ends on the first Sunday of November
        
        // 2nd Sunday in March can be 8th - 14th
        if ((month == 3) && (prev_sun_date >= 8) && (hour > 3)) {
            return true;
        }

        // 1st Sunday in Nov can be 1st - 7th
        if ((month == 11) && (prev_sun_date <= 7)) {
            // if OMNI_DATE_TIME_AMBIGUOUS_DST_1AM is defined then DST -stops- at 1am
            #if defined(OMNI_DATE_TIME_AMBIGUOUS_DST_1AM)
                if (hour <= 1) { return true; }
            #else
                if (hour == 0) { return true; }
            #endif
        }
    } else if ((year >= 1986) && (year <= 2006)) {
        // 1986 - 2006, DST started first Sunday in April and to the last Sunday in October

        // 1st Sunday in April can be 1st - 7th
        if ((month == 4) && (prev_sun_date <= 7) && (hour > 3)) {
            return true;
        }

        // Last Sunday in Oct can be 25th - 31st
        if ((month == 10) && (prev_sun_date >= 25)) {
            // if OMNI_DATE_TIME_AMBIGUOUS_DST_1AM is defined then DST -stops- at 1am
            #if defined(OMNI_DATE_TIME_AMBIGUOUS_DST_1AM)
                if (hour <= 1) { return true; }
            #else
                if (hour == 0) { return true; }
            #endif
        }
    } else {
        // 1966 - 1986, DST started last Sunday in April to last Sunday in October

        // Last Sunday in April can be 24th - 30th
        if ((month == 4) && (prev_sun_date >= 24) && (hour > 3)) {
            return true;
        }

        // Last Sunday in Oct can be 25th - 31st
        if ((month == 10) && (prev_sun_date >= 25)) {
            // if OMNI_DATE_TIME_AMBIGUOUS_DST_1AM is defined then DST -stops- at 1am
            #if defined(OMNI_DATE_TIME_AMBIGUOUS_DST_1AM)
                if (hour <= 1) { return true; }
            #else
                if (hour == 0) { return true; }
            #endif
        }
    }
    
    return false;
}

bool omni::chrono::date_time::is_ambiguous_dst() const
{
    OMNI_DTTM_ALOCK_FW

    uint16_t year = static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW));
    uint16_t month = static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW));
    uint16_t day = static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW));
    // dow (day of week): sunday = 0, mon = 1 .. sat = 6
    int16_t prev_sun_date = static_cast<int16_t>(day - static_cast<uint16_t>((this->_ticks() / OMNI_TICKS_PER_DAY + 1) % 7));
    uint16_t hour = static_cast<uint16_t>((this->_ticks() / OMNI_TICKS_PER_HOUR) % 24);

    /*
        2AM            3AM                        1AM              2AM
        |      +1 hr     |                        |       -1 hr      |
        | <invalid time> |                        | <ambiguous time> |
                        [========== DST ========>)
        
        3AM -starts- DST because at 2, the clock rolls up, so there is no 2AM
        
        1AM is -ambiguous- because at 2 the clock rolls back, so it *could* be 1:30 and -not- DST
    */

    if (year >= 2007) {
        if ((month == 11) && (prev_sun_date <= 7)) {
            return ((hour >= 1) && (hour <= 2));
        }
    } else if ((year >= 1986) && (year <= 2006)) {
        if ((month == 10) && (prev_sun_date >= 25)) {
            return ((hour >= 1) && (hour <= 2));
        }
    } else {
        if ((month == 10) && (prev_sun_date >= 25)) {
            return ((hour >= 1) && (hour <= 2));
        }
    }
    
    return false;
}

bool omni::chrono::date_time::is_leap_year() const
{
    return omni::chrono::date_time::is_leap_year(*this);
}

bool omni::chrono::date_time::is_leap_day() const
{
    return omni::chrono::date_time::is_leap_day(*this);
}

int64_t omni::chrono::date_time::to_binary() const
{
    if (this->kind() == omni::chrono::date_time_kind::LOCAL) {
        /*
            Local times need to be adjusted as you move from one time zone to another, 
            just as they are when serializing in text. As such the format for local times
            changes to store the ticks of the UTC time, but with flags that look like a 
            local date.
        
            To match serialization in text we need to be able to handle cases where
            the UTC value would be out of range. Unused parts of the ticks range are
            used for this, so that values just past max value are stored just past the
            end of the maximum range, and values just below minimum value are stored
            at the end of the ticks area, just below 2^62.
        */
        omni::chrono::time_span offset(0, 0, static_cast<omni::chrono::time_span::span_t>(omni::chrono::date_time::offset_from_utc()));
        int64_t ticks = this->_ticks();
        int64_t stored = ticks - offset.ticks();
        if (stored < 0) {
            stored = OMNI_TICKS_CEILING_FW + stored;
        }
        return stored | static_cast<int64_t>(OMNI_DATE_LOCAL_MASK_FW);
    }
    return static_cast<int64_t>(this->m_date);
}

omni::chrono::date_time omni::chrono::date_time::date() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - ticks % OMNI_TICKS_PER_DAY) | this->_internal_kind(), "");
}

// Returns the day-of-month part of this DateTime. The returned value is an integer between 1 and 31.
uint16_t omni::chrono::date_time::day() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_FW));
}

omni::chrono::day_of_week omni::chrono::date_time::day_of_week() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::day_of_week(
        static_cast<omni::chrono::day_of_week::enum_t>(
            ((this->_ticks() / OMNI_TICKS_PER_DAY + 1) % 7)
        )
    );
}

uint16_t omni::chrono::date_time::day_of_year() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_DAY_OF_YEAR_FW));
}

int32_t omni::chrono::date_time::hash_code() const
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    return static_cast<int32_t>(ticks) ^ static_cast<int32_t>(ticks >> 32);
}

uint16_t omni::chrono::date_time::hour() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks() / OMNI_TICKS_PER_HOUR) % 24);
}

omni::chrono::date_time_kind omni::chrono::date_time::kind() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_kind();
}

uint16_t omni::chrono::date_time::millisecond() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ OMNI_TICKS_PER_MILLISECOND) % 1000); 
}

uint16_t omni::chrono::date_time::minute() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ OMNI_TICKS_PER_MINUTE) % 60); 
}

uint16_t omni::chrono::date_time::month() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_MONTH_FW));
}

uint16_t omni::chrono::date_time::second() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>((this->_ticks()/ OMNI_TICKS_PER_SECOND) % 60); 
}

uint64_t omni::chrono::date_time::ticks() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint64_t>(this->_ticks());
}

omni::chrono::time_span omni::chrono::date_time::time_of_day() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() % OMNI_TICKS_PER_DAY); 
}

uint16_t omni::chrono::date_time::year() const
{
    OMNI_DTTM_ALOCK_FW
    return static_cast<uint16_t>(omni::chrono::date_time::_get_date_part(OMNI_DATE_PART_YEAR_FW));
}

omni::chrono::time_span omni::chrono::date_time::utc_offset() const
{
    OMNI_DTTM_ALOCK_FW
    if (this->_kind() == omni::chrono::date_time_kind::UTC) {
        return omni::chrono::time_span::zero();
    }
    double offset_utc = 0;
    omni_date_time_internal_offset_from_utc(&offset_utc);
    return omni::chrono::time_span::from_seconds(offset_utc);
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
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid time span specified", omni::exceptions::invalid_range("Invalid time span specified"), omni::chrono::date_time())
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
    int64_t ticks = (
        ((this->_internal_kind() & OMNI_DATE_LOCAL_MASK_FW) != 0) ?
        this->to_universal_time()._ticks() :
        this->_ticks()
    ) - OMNI_FILE_TIME_OFFSET;
    if (ticks < 0) {
        OMNI_ERR_RETV_FW("Invalid file time specified", omni::exceptions::invalid_range("Invalid file time specified"), 0)
    }
    return static_cast<uint64_t>(ticks);
}

omni::chrono::date_time omni::chrono::date_time::to_local_time() const
{
    OMNI_DTTM_ALOCK_FW
    return this->_to_local_time(false);
}

std::string omni::chrono::date_time::to_long_date_string() const
{
    OMNI_DTTM_ALOCK_FW
    return omni_date_time_format(*this, "D");
}

std::wstring omni::chrono::date_time::to_long_date_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(omni_date_time_format(*this, "D"));
}

std::string omni::chrono::date_time::to_long_time_string() const
{
    OMNI_DTTM_ALOCK_FW
    return omni_date_time_format(*this, "T");
}

std::wstring omni::chrono::date_time::to_long_time_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(omni_date_time_format(*this, "T"));
}

std::string omni::chrono::date_time::to_short_date_string() const
{
    OMNI_DTTM_ALOCK_FW
    return omni_date_time_format(*this, "d");
}

std::wstring omni::chrono::date_time::to_short_date_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(omni_date_time_format(*this, "d"));
}

std::string omni::chrono::date_time::to_short_time_string() const
{
    OMNI_DTTM_ALOCK_FW
    return omni_date_time_format(*this, "t");
}

std::wstring omni::chrono::date_time::to_short_time_wstring() const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(omni_date_time_format(*this, "t"));
}

std::string omni::chrono::date_time::to_string(const std::string& format) const
{
    OMNI_DTTM_ALOCK_FW
    return omni_date_time_format(*this, format);
}

std::wstring omni::chrono::date_time::to_wstring(const std::wstring& format) const
{
    OMNI_DTTM_ALOCK_FW
    return omni::string_util::to_wstring(omni_date_time_format(*this, omni::string_util::to_string(format)));
}

omni::chrono::date_time omni::chrono::date_time::to_universal_time() const
{
    if (this->kind() == omni::chrono::date_time_kind::UTC) {
        return omni::chrono::date_time(*this);
    }
    omni::chrono::span_t offset(0, 0, static_cast<omni::chrono::span_t::span_t>(omni::chrono::date_time::offset_from_utc()));
    #if defined(OMNI_SAFE_DATETIME)
        this->m_mtx.lock();
    #endif
    omni::chrono::date_time obj(omni::chrono::date_time::specify_kind(*this, omni::chrono::date_time_kind::UTC));
    #if defined(OMNI_SAFE_DATETIME)
        this->m_mtx.unlock();
    #endif
    // DEV_NOTE: we negate the offset since we want to get to UTC, and if the offset is
    // negative, adding a negative will subtract; instead of using std::abs, negate is quicker
    return omni_chrono_date_time_internal_offset(obj, offset.negate());
}

std::string omni::chrono::date_time::to_military_dtg_string() const
{
    // DD HH MM SS Z mmm YY
    std::string zulu = this->to_string("ddHHmmss");
    int64_t offset = this->utc_offset().ticks() / OMNI_TICKS_PER_HOUR;
    switch (offset) {
        case -12: zulu += "Y"; break;
        case -11: zulu += "X"; break;
        case -10: zulu += "W"; break;
        case -9: zulu += "V"; break;
        case -8: zulu += "U"; break;
        case -7: zulu += "T"; break;
        case -6: zulu += "S"; break;
        case -5: zulu += "R"; break;
        case -4: zulu += "Q"; break;
        case -3: zulu += "P"; break;
        case -2: zulu += "O"; break;
        case -1: zulu += "N"; break;
        case 0: zulu += "Z"; break;
        case 1: zulu += "A"; break;
        case 2: zulu += "B"; break;
        case 3: zulu += "C"; break;
        case 4: zulu += "D"; break;
        case 5: zulu += "E"; break;
        case 6: zulu += "F"; break;
        case 7: zulu += "G"; break;
        case 8: zulu += "H"; break;
        case 9: zulu += "I"; break;
        case 10: zulu += "K"; break;
        case 11: zulu += "L"; break;
        case 12: zulu += "M"; break;
        default: zulu += " "; break;
    }
    zulu += omni::chrono::month_of_year::get_abbreviated_name(static_cast<omni::chrono::month_of_year::enum_t>(this->month())) + this->to_string("yy");
    return zulu;
}

std::wstring omni::chrono::date_time::to_military_dtg_wstring() const
{
    // DD HH MM SS Z mmm YY
    std::wstring zulu = this->to_wstring(L"ddHHmmss");
    int64_t offset = this->utc_offset().ticks() / OMNI_TICKS_PER_HOUR;
    switch (offset) {
        case -12: zulu += L"Y"; break;
        case -11: zulu += L"X"; break;
        case -10: zulu += L"W"; break;
        case -9: zulu += L"V"; break;
        case -8: zulu += L"U"; break;
        case -7: zulu += L"T"; break;
        case -6: zulu += L"S"; break;
        case -5: zulu += L"R"; break;
        case -4: zulu += L"Q"; break;
        case -3: zulu += L"P"; break;
        case -2: zulu += L"O"; break;
        case -1: zulu += L"N"; break;
        case 0: zulu += L"Z"; break;
        case 1: zulu += L"A"; break;
        case 2: zulu += L"B"; break;
        case 3: zulu += L"C"; break;
        case 4: zulu += L"D"; break;
        case 5: zulu += L"E"; break;
        case 6: zulu += L"F"; break;
        case 7: zulu += L"G"; break;
        case 8: zulu += L"H"; break;
        case 9: zulu += L"I"; break;
        case 10: zulu += L"K"; break;
        case 11: zulu += L"L"; break;
        case 12: zulu += L"M"; break;
        default: zulu += L" "; break;
    }
    zulu += omni::chrono::month_of_year::get_abbreviated_wname(static_cast<omni::chrono::month_of_year::enum_t>(this->month())) + this->to_wstring(L"yy");
    return zulu;
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

omni::chrono::date_time& omni::chrono::date_time::operator=(const omni::chrono::date_time& other)
{

    if (this != &other) {
        OMNI_DTTM_ALOCK_FW
        OMNI_DTTM_OLOCK_FW(other)
        OMNI_ASSIGN_FW(other)
        this->m_date = other.m_date;
    }
    return *this;
}

omni::chrono::date_time omni::chrono::date_time::operator+(const omni::chrono::time_span& span)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = span.ticks();
    if ((vticks > (OMNI_MAX_TICKS_FW - ticks)) || (vticks < (0 - ticks))) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks + vticks) | this->_internal_kind());
}

omni::chrono::date_time omni::chrono::date_time::operator-(const omni::chrono::time_span& span)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = span.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    return omni::chrono::date_time(static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
}

omni::chrono::date_time& omni::chrono::date_time::operator+=(const omni::chrono::time_span& span)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = span.ticks();
    if ((vticks > (OMNI_MAX_TICKS_FW - ticks)) || (vticks < (0 - ticks))) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    this->m_date = (static_cast<uint64_t>(ticks + vticks) | this->_internal_kind());
    return *this;
}

omni::chrono::date_time& omni::chrono::date_time::operator-=(const omni::chrono::time_span& span)
{
    OMNI_DTTM_ALOCK_FW
    int64_t ticks = this->_ticks();
    int64_t vticks = span.ticks();
    if ((ticks < vticks) || ((ticks - OMNI_MAX_TICKS_FW) > vticks)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), *this)
    }
    this->m_date = (static_cast<uint64_t>(ticks - vticks) | this->_internal_kind());
    return *this;
}

omni::chrono::time_span omni::chrono::date_time::operator-(const omni::chrono::date_time& other)
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() - static_cast<int64_t>(other.ticks()));
}

omni::chrono::time_span omni::chrono::date_time::operator+(const omni::chrono::date_time& other)
{
    OMNI_DTTM_ALOCK_FW
    return omni::chrono::time_span(this->_ticks() + static_cast<int64_t>(other.ticks()));
}

bool omni::chrono::date_time::operator==(const omni::chrono::date_time& other) const
{
    if (this == &other) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    return (
        this->m_date == other.m_date
    )
    OMNI_EQUAL_FW(other);
}

bool omni::chrono::date_time::operator!=(const omni::chrono::date_time& other) const
{
    return !(*this == other);
}

bool omni::chrono::date_time::operator<(const omni::chrono::date_time& other) const
{
    if (this == &other) { return false; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    return (this->m_date < other.m_date);
}

bool omni::chrono::date_time::operator<=(const omni::chrono::date_time& other) const
{
    if (this == &other) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    return (this->m_date <= other.m_date);
}

bool omni::chrono::date_time::operator>(const omni::chrono::date_time& other) const
{
    if (this == &other) { return false; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    return (this->m_date > other.m_date);
}

bool omni::chrono::date_time::operator>=(const omni::chrono::date_time& other) const
{
    if (this == &other) { return true; }
    OMNI_DTTM_ALOCK_FW
    OMNI_DTTM_OLOCK_FW(other)
    return (this->m_date >= other.m_date);
}

// -- start private methods --

omni::chrono::date_time omni::chrono::date_time::_add(double value, int64_t scale) const
{
    int64_t millis = static_cast<int64_t>(
        (value * static_cast<double>(scale)) + ((value >= 0.0) ? 0.5 : -0.5)
    );
    if ((millis <= -OMNI_MAX_MILLIS_FW) || (millis >= OMNI_MAX_MILLIS_FW)) {
        OMNI_ERR_RETV_FW("Invalid value/scale specified", omni::exceptions::invalid_range("Invalid value/scale specified"), omni::chrono::date_time())
    }
    return this->add_ticks(millis * OMNI_TICKS_PER_MILLISECOND);
}

omni::chrono::date_time_kind omni::chrono::date_time::_kind() const
{
    switch (this->_internal_kind()) {
        case OMNI_DATE_KIND_UNSPECIFIED_FW:
            return omni::chrono::date_time_kind::UNSPECIFIED;
        case OMNI_DATE_KIND_UTC_FW:
            return omni::chrono::date_time_kind::UTC;
        case OMNI_DATE_KIND_LOCAL_DST_FW:
            return omni::chrono::date_time_kind::LOCAL_DST;
        default: break;
    }
    return omni::chrono::date_time_kind::LOCAL;                    
}

int64_t omni::chrono::date_time::_to_binary_raw() const
{
    return static_cast<int64_t>(this->m_date);
}

int64_t omni::chrono::date_time::_get_date_part(uint16_t part) const
{
    #if defined(OMNI_NO_CONSTS)
        const int32_t DT365[] = OMNI_DAYS_TO_MONTH_365;
        const int32_t DT366[] = OMNI_DAYS_TO_MONTH_366;
    #endif
    const int32_t* days = OMNI_NULL_PTR;
    int64_t n, y400, y100, y4, y1, m;
    int64_t ticks = this->_ticks();
    // n = number of days since 1/1/0001
    n = (ticks / OMNI_TICKS_PER_DAY);
    // y400 = number of whole 400-year periods since 1/1/0001
    y400 = n / OMNI_DAYS_PER_400_YEARS;
    // n = day number within 400-year period
    n -= y400 * OMNI_DAYS_PER_400_YEARS;
    // y100 = number of whole 100-year periods within 400-year period
    y100 = n / OMNI_DAYS_PER_100_YEARS;
    // Last 100-year period has an extra day, so decrement result if 4
    if (y100 == 4) { y100 = 3; }
    // n = day number within 100-year period
    n -= y100 * OMNI_DAYS_PER_100_YEARS;
    // y4 = number of whole 4-year periods within 100-year period
    y4 = n / OMNI_DAYS_PER_4_YEARS;
    // n = day number within 4-year period
    n -= y4 * OMNI_DAYS_PER_4_YEARS;
    // y1 = number of whole years within 4-year period
    y1 = n / OMNI_DAYS_PER_YEAR;
    // Last year has an extra day, so decrement result if 4
    if (y1 == 4) y1 = 3;
    // If year was requested, compute and return it
    if (part == OMNI_DATE_PART_YEAR_FW) {
        return (y400 * 400) + (y100 * 100) + (y4 * 4) + y1 + 1;
    }
    // n = day number within year
    n -= y1 * OMNI_DAYS_PER_YEAR;
    // If day-of-year was requested, return it
    if (part == OMNI_DATE_PART_DAY_OF_YEAR_FW) {
        return n + 1;
    }
    // Leap year calculation looks different from IsLeapYear since y1, y4,
    // and y100 are relative to year 1, not year 0
    m = (n >> 5) + 1;

    // All months have less than 32 days, so n >> 5 is a good conservative
    // estimate for the month
    // m = 1-based month number
    if ((y1 == 3) && (y4 != 24 || y100 == 3)) {
        #if defined(OMNI_NO_CONSTS)
            days = &DT366[0];
        #else
            days = &omni::chrono::DAYS_TO_MONTH_366[0];
        #endif
    } else {
        #if defined(OMNI_NO_CONSTS)
            days = &DT365[0];
        #else
            days = &omni::chrono::DAYS_TO_MONTH_365[0];
        #endif
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

omni::chrono::date_time omni::chrono::date_time::_to_local_time(bool throw_on_overflow) const
{
    //OMNI_DTTM_ALOCK_FW
    if (this->kind() == omni::chrono::date_time_kind::LOCAL) {
        return omni::chrono::date_time(*this);
    }
    // bool is_dst = false;
    bool is_ambiguous_local_dst = false;
    int64_t offset = (omni::chrono::span_t(0, 0, static_cast<omni::chrono::span_t::span_t>(omni::chrono::date_time::offset_from_utc()))).ticks();
    int64_t tick = this->_ticks() + offset;
    if (tick > OMNI_MAX_TICKS_FW) {
        if (throw_on_overflow) {
            OMNI_ERR_RETV_FW("Invalid ticks for local time", omni::exceptions::invalid_range("Invalid ticks for local time"), omni::chrono::date_time())
        } else {
            return omni::chrono::date_time(OMNI_MAX_TICKS_FW, omni::chrono::date_time_kind::LOCAL);
        }
    }
    if (tick < 0) {
        if (throw_on_overflow) {
            OMNI_ERR_RETV_FW("Invalid local time", omni::exceptions::invalid_range("Invalid local time"), omni::chrono::date_time())
        } else {
            return omni::chrono::date_time(0, omni::chrono::date_time_kind::LOCAL);
        }
    }
    return omni::chrono::date_time(is_ambiguous_local_dst, omni::chrono::date_time_kind::LOCAL, static_cast<uint64_t>(tick), "");
}

// -- start static methods --

uint16_t omni::chrono::date_time::days_in_month(uint16_t year, uint16_t month)
{
    if ((month < 1) || (month > 12)) {
        OMNI_ERR_RETV_FW("Invalid month specified", omni::exceptions::invalid_range("Invalid month specified"), omni::chrono::date_time())
    }
    #if defined(OMNI_NO_CONSTS)
        if (omni::chrono::is_leap_year(year)) {
            // check the year argument
            const int32_t d366[] = OMNI_DAYS_TO_MONTH_366;
            return d366[month] - d366[month - 1];
        }
        const int32_t d365[] = OMNI_DAYS_TO_MONTH_365;
        return d365[month] - d365[month - 1];
    #else
        if (omni::chrono::is_leap_year(year)) {
            // check the year argument
            return static_cast<uint16_t>(omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1]);
        }
        return static_cast<uint16_t>(omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1]);
    #endif
}

omni::chrono::date_time omni::chrono::date_time::from_binary(int64_t date_data)
{
    if ((date_data & static_cast<int64_t>(OMNI_DATE_LOCAL_MASK_FW)) != 0) {
        /*
            Local times need to be adjusted as you move from one time zone to another, 
            just as they are when serializing in text. As such the format for local times
            changes to store the ticks of the UTC time, but with flags that look like a 
            local date.
        */
        int64_t offset = 0;
        int64_t ticks = (date_data & static_cast<int64_t>(OMNI_TICKS_MASK_FW));
        // Negative ticks are stored in the top part of the range and should be converted back into a negative number
        if (ticks > OMNI_TICKS_CEILING_FW - OMNI_TICKS_PER_DAY) {
            ticks -= OMNI_TICKS_CEILING_FW;
        }
        // Convert the ticks back to local. If the UTC ticks are out of range, we need to default to
        // the UTC offset from MinValue and MaxValue to be consistent with Parse. 
        if (ticks < 0) {
            // offsetTicks = TimeZoneInfo.GetLocalUtcOffset(DateTime.MinValue, TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
            offset = (omni::chrono::span_t(0, 0, static_cast<omni::chrono::span_t::span_t>(omni::chrono::date_time::offset_from_utc()))).ticks();
        } else if (ticks > OMNI_MAX_TICKS_FW) {
            // offsetTicks = TimeZoneInfo.GetLocalUtcOffset(DateTime.MaxValue, TimeZoneInfoOptions.NoThrowOnInvalidTime).Ticks;
            offset = (omni::chrono::span_t(0, 0, (OMNI_MAX_TICKS_FW / OMNI_TICKS_PER_SECOND))).ticks();
        } else {
            // Because the ticks conversion between UTC and local is lossy, we need to capture whether the
            // time is in a repeated hour so that it can be passed to the DateTime constructor.
            offset = (omni::chrono::span_t(0, 0, static_cast<omni::chrono::span_t::span_t>(omni::chrono::date_time::offset_from_utc()))).ticks();
        }

        ticks += offset;
        // Another behaviour of parsing is to cause small times to wrap around, so that they can be used
        // to compare times of day
        if (ticks < 0) {
            ticks += OMNI_TICKS_PER_DAY;
        }                
        if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
            OMNI_ERR_RETV_FW("Invalid binary tick count specified", omni::exceptions::invalid_range("Invalid binary tick count specified"), omni::chrono::date_time())
        }
        return omni::chrono::date_time(static_cast<uint64_t>(ticks), omni::chrono::date_time_kind::LOCAL);
    }
    return omni::chrono::date_time::_from_binary_raw(date_data);
}

omni::chrono::date_time omni::chrono::date_time::from_file_time(int64_t file_time)
{
    return omni::chrono::date_time::from_file_time_utc(file_time).to_local_time();
}

omni::chrono::date_time omni::chrono::date_time::from_file_time_utc(int64_t file_time)
{
    if ((file_time < 0) || (file_time > (OMNI_MAX_TICKS_FW - OMNI_FILE_TIME_OFFSET))) {
        OMNI_ERR_RETV_FW("Invalid file time specified", omni::exceptions::invalid_range("Invalid file time specified"), omni::chrono::date_time())
    }
    // This is the ticks in Universal time for this file_time.
    int64_t uticks = file_time + OMNI_FILE_TIME_OFFSET;
    return omni::chrono::date_time(static_cast<uint64_t>(uticks), omni::chrono::date_time_kind::UTC);
}

omni::chrono::date_time omni::chrono::date_time::from_oa_date(double oa_val)
{
    return omni::chrono::date_time(static_cast<uint64_t>(omni::chrono::date_time::_double_date_to_ticks(oa_val)), omni::chrono::date_time_kind::UNSPECIFIED);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(const omni::chrono::date_time& other, const omni::chrono::span_t& offset)
{
    omni::chrono::date_time obj(omni::chrono::date_time::specify_kind(other, omni::chrono::date_time_kind::LOCAL));
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(const omni::chrono::date_time& other, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
{
    omni::chrono::date_time obj(omni::chrono::date_time::specify_kind(other, kind));
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(uint64_t ticks, const omni::chrono::span_t& offset)
{
    omni::chrono::date_time obj(ticks, omni::chrono::date_time_kind::LOCAL);
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(uint64_t ticks, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
{
    omni::chrono::date_time obj(ticks, kind);
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::span_t& offset)
{
    omni::chrono::date_time obj(year, month, day, hour, minute, second, omni::chrono::date_time_kind::LOCAL);
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
{
    omni::chrono::date_time obj(year, month, day, hour, minute, second, kind);
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::span_t& offset)
{
    omni::chrono::date_time obj(year, month, day, hour, minute, second, millisecond, omni::chrono::date_time_kind::LOCAL);
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::chrono::date_time omni::chrono::date_time::from_offset(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
{
    omni::chrono::date_time obj(year, month, day, hour, minute, second, millisecond, kind);
    return omni_chrono_date_time_internal_offset(obj, offset);
}

omni::sequence::string_t omni::chrono::date_time::get_date_time_formats()
{
    omni::sequence::string_t result;
    // case 'd':
    result.push_back(omni::string::to_string_t("MM/dd/yyyy"));
    result.push_back(omni::string::to_string_t("yyyy-MM-dd"));
    // case 'D':
    result.push_back(omni::string::to_string_t("dddd, dd MMMM yyyy"));
    // case 't':
    result.push_back(omni::string::to_string_t("HH:mm"));
    result.push_back(omni::string::to_string_t("hh:mm tt"));
    result.push_back(omni::string::to_string_t("H:mm"));
    result.push_back(omni::string::to_string_t("h:mm tt"));
    // case 'T':
    result.push_back(omni::string::to_string_t("HH:mm:ss"));
    // case 'y': case 'Y':
    result.push_back(omni::string::to_string_t("yyyy MMMM"));
    // case 'f': case 'F':
    result.push_back(omni::string::to_string_t("dddd, dd MMMM yyyy"));
    result.push_back(omni::string::to_string_t("HH:mm"));
    result.push_back(omni::string::to_string_t("hh:mm tt"));
    result.push_back(omni::string::to_string_t("H:mm"));
    result.push_back(omni::string::to_string_t("h:mm tt"));
    // case 'U':
    result.push_back(omni::string::to_string_t("dddd, dd MMMM yyyy"));
    result.push_back(omni::string::to_string_t("HH:mm:ss"));
    // case 'g':
    result.push_back(omni::string::to_string_t("MM/dd/yyyy"));
    result.push_back(omni::string::to_string_t("yyyy-MM-dd"));
    result.push_back(omni::string::to_string_t("HH:mm"));
    result.push_back(omni::string::to_string_t("hh:mm tt"));
    result.push_back(omni::string::to_string_t("H:mm"));
    result.push_back(omni::string::to_string_t("h:mm tt"));
    // case 'G':
    result.push_back(omni::string::to_string_t("MM/dd/yyyy"));
    result.push_back(omni::string::to_string_t("yyyy-MM-dd"));
    result.push_back(omni::string::to_string_t("HH:mm:ss"));
    // case 'm': case 'M':
    result.push_back(omni::string::to_string_t("MMMM dd"));
    // case 'o': case 'O':
    result.push_back(omni::string::to_string_t("yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK"));
    // case 'r': case 'R':
    result.push_back(omni::string::to_string_t("ddd, dd MMM yyyy HH':'mm':'ss 'GMT'"));
    // case 's':
    result.push_back(omni::string::to_string_t("yyyy'-'MM'-'dd'T'HH':'mm':'ss"));
    // case 'u':
    result.push_back(omni::string::to_string_t("yyyy'-'MM'-'dd HH':'mm':'ss'Z'"));
    return result;
}

omni::sequence::string_t omni::chrono::date_time::get_date_time_formats(char format)
{
    omni::sequence::string_t result;
    switch (format)
    {
        case 'd':
            result.push_back(omni::string::to_string_t("MM/dd/yyyy"));
            result.push_back(omni::string::to_string_t("yyyy-MM-dd"));
            break;
        case 'D':
            result.push_back(omni::string::to_string_t("dddd, dd MMMM yyyy"));
            break;
        case 't':
            result.push_back(omni::string::to_string_t("HH:mm"));
            result.push_back(omni::string::to_string_t("hh:mm tt"));
            result.push_back(omni::string::to_string_t("H:mm"));
            result.push_back(omni::string::to_string_t("h:mm tt"));
            break;
        case 'T':
            result.push_back(omni::string::to_string_t("HH:mm:ss"));
            break;
        case 'y': case 'Y':
            result.push_back(omni::string::to_string_t("yyyy MMMM"));
            break;
        case 'f': case 'F':
            result.push_back(omni::string::to_string_t("dddd, dd MMMM yyyy"));
            result.push_back(omni::string::to_string_t("HH:mm"));
            result.push_back(omni::string::to_string_t("hh:mm tt"));
            result.push_back(omni::string::to_string_t("H:mm"));
            result.push_back(omni::string::to_string_t("h:mm tt"));
            break;
        case 'U':
            result.push_back(omni::string::to_string_t("dddd, dd MMMM yyyy"));
            result.push_back(omni::string::to_string_t("HH:mm:ss"));
            break;
        case 'g':
            result.push_back(omni::string::to_string_t("MM/dd/yyyy"));
            result.push_back(omni::string::to_string_t("yyyy-MM-dd"));
            result.push_back(omni::string::to_string_t("HH:mm"));
            result.push_back(omni::string::to_string_t("hh:mm tt"));
            result.push_back(omni::string::to_string_t("H:mm"));
            result.push_back(omni::string::to_string_t("h:mm tt"));
            break;
        case 'G':
            result.push_back(omni::string::to_string_t("MM/dd/yyyy"));
            result.push_back(omni::string::to_string_t("yyyy-MM-dd"));
            result.push_back(omni::string::to_string_t("HH:mm:ss"));
            break;
        case 'm': case 'M':
            result.push_back(omni::string::to_string_t("MMMM dd"));
            break;
        case 'o': case 'O':
            result.push_back(omni::string::to_string_t("yyyy'-'MM'-'dd'T'HH':'mm':'ss.fffffffK"));
            break;
        case 'r': case 'R':
            result.push_back(omni::string::to_string_t("ddd, dd MMM yyyy HH':'mm':'ss 'GMT'"));
            break;
        case 's':
            result.push_back(omni::string::to_string_t("yyyy'-'MM'-'dd'T'HH':'mm':'ss"));
            break;
        case 'u':
            result.push_back(omni::string::to_string_t("yyyy'-'MM'-'dd HH':'mm':'ss'Z'"));
            break;
        default:
            OMNI_ERR_RETV_FW("Invalid format specified", omni::exceptions::invalid_string_format(), omni::sequence::string_t())
    }
    return result;
}

double omni::chrono::date_time::offset_from_utc()
{
    double offset_seconds = 0;
    omni_date_time_internal_offset_from_utc(&offset_seconds);
    return offset_seconds;
}

omni::chrono::date_time omni::chrono::date_time::specify_kind(const omni::chrono::date_time& value, const omni::chrono::date_time_kind& kind)
{
    return omni::chrono::date_time(static_cast<uint64_t>(value._ticks()), kind);
}

omni::chrono::date_time omni::chrono::date_time::now()
{
    double offset_seconds = 0;
    bool dst = omni_date_time_internal_offset_from_utc(&offset_seconds);
    omni::chrono::date_time obj((omni_date_time_internal_get_ticks() | (dst ? OMNI_DATE_KIND_LOCAL_DST_FW : OMNI_DATE_KIND_LOCAL_FW)), "");
    return omni_chrono_date_time_internal_offset(obj, omni::chrono::span_t(0, 0, static_cast<omni::chrono::span_t::span_t>(offset_seconds)));
}

omni::chrono::date_time omni::chrono::date_time::utc_now()
{
    return omni::chrono::date_time((omni_date_time_internal_get_ticks() | OMNI_DATE_KIND_UTC_FW), "");
}

omni::chrono::date_time omni::chrono::date_time::today()
{
    return omni::chrono::date_time::now().date();
}

bool omni::chrono::date_time::is_leap_year(uint16_t year)
{
    if ((year < 1) || (year > OMNI_DATE_MAX_YEAR)) {
        OMNI_ERR_RETV_FW("Invalid year specified", omni::exceptions::invalid_range("Invalid year specified"), false)
    }
    return omni_date_time_internal_is_leap_year(year);
}

bool omni::chrono::date_time::is_leap_year(const omni::chrono::date_time& date)
{
    return omni::chrono::date_time::is_leap_year(date.year());
}

bool omni::chrono::date_time::is_leap_day(uint16_t year, uint16_t month, uint16_t day)
{
    if (omni::chrono::date_time::is_leap_year(year)) {
        if ((month < 1) || (month > 12)) {
            OMNI_ERR_RETV_FW("Invalid month specified", omni::exceptions::invalid_range("Invalid month specified"), false)
        }
        if ((day < 1) || (day > 32)) {
            OMNI_ERR_RETV_FW("Invalid day specified", omni::exceptions::invalid_range("Invalid day specified"), false)
        }
        if (omni_date_time_internal_check_day_range(year, month, day)) {
            OMNI_ERR_RETV_FW("Invalid day specified for the year and month", omni::exceptions::invalid_range("Invalid day specified for the year and month"), false)
        }
        return ((month == 2) && (day == 29));
    }
    return false;
}

bool omni::chrono::date_time::is_leap_day(const omni::chrono::date_time& date)
{
    return omni::chrono::date_time::is_leap_day(date.year(), date.month(), date.day());
}

bool omni::chrono::date_time::is_valid_day(uint16_t year, uint16_t month, uint16_t day)
{
    return omni_date_time_internal_check_day_range(year, month, day);
}

uint16_t omni::chrono::date_time::to_four_digit_year(uint16_t year, uint16_t two_digit_year_max)
{
    if ((year < 1) || (year > OMNI_DATE_MAX_YEAR)) {
        OMNI_ERR_RETV_FW("Invalid year specified", omni::exceptions::invalid_range("Invalid year specified"), false)
    }
    if (year >= 100) {
        // if it's 100 or higher, no need to do the 2 digit year comparison
        return year;
    }
    return static_cast<uint16_t>((((two_digit_year_max / 100) - ((year > (two_digit_year_max % 100)) ? 1 : 0)) * 100) + year);
}

uint16_t omni::chrono::date_time::to_four_digit_year(uint16_t year)
{
    return omni::chrono::date_time::to_four_digit_year(year, omni::chrono::date_time::now().year() + OMNI_DATE_TWO_DIGIT_YEAR_MAX);
}

bool omni::chrono::date_time::try_create(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, omni::chrono::date_time& result)
{
    return omni::chrono::date_time::_try_create(year, month, day, hour, minute, second, millisecond, result);
}

omni::chrono::date_time omni::chrono::date_time::parse(const std::string& date_string)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::parse(date_string, current_info, omni::chrono::date_time_styles::NONE);
}

bool omni::chrono::date_time::try_parse(const std::string& date_string, omni::chrono::date_time& result)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::try_parse(date_string, current_info, omni::chrono::date_time_styles::NONE, result);
}

bool omni::chrono::date_time::try_parse(const std::string& date_string, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::try_parse(date_string, current_info, omni::chrono::date_time_styles::NONE, result, fail_reason);
}

omni::chrono::date_time omni::chrono::date_time::parse_exact(const std::string& date_string, const std::string& format)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::date_time_parse::parse_exact(date_string, format, current_info, omni::chrono::date_time_styles::NONE);
}

omni::chrono::date_time omni::chrono::date_time::parse_exact(const std::string& date_string, const std::string& format, const omni::chrono::date_time_styles& style)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::date_time_parse::parse_exact(date_string, format, current_info, style);
}

bool omni::chrono::date_time::try_parse_exact(const std::string& date_string, const std::string& format, omni::chrono::date_time& result)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::date_time_parse::try_parse_exact(date_string, format, current_info, omni::chrono::date_time_styles::NONE, result);
}

bool omni::chrono::date_time::try_parse_exact(const std::string& date_string, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::date_time_parse::try_parse_exact(date_string, format, current_info, style, result);
}

bool omni::chrono::date_time::try_parse_exact(const std::string& date_string, const std::string& format, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::date_time_parse::try_parse_exact(date_string, format, current_info, omni::chrono::date_time_styles::NONE, result, fail_reason);
}

bool omni::chrono::date_time::try_parse_exact(const std::string& date_string, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason)
{
    omni::internal::date_time_format::format_info current_info;
    return omni::internal::date_time_format::date_time_parse::try_parse_exact(date_string, format, current_info, style, result, fail_reason);
}

// -- start private static methods --

int64_t omni::chrono::date_time::_date_to_ticks(uint16_t year, uint16_t month, uint16_t day)
{
    if ((year >= 1) && (year <= OMNI_DATE_MAX_YEAR) && (month >= 1) && (month <= 12)) {
        #if defined(OMNI_NO_CONSTS)
            const int32_t d365[] = OMNI_DAYS_TO_MONTH_365;
            const int32_t d366[] = OMNI_DAYS_TO_MONTH_366;
            const int32_t* days = omni::chrono::is_leap_year(year) ? &d366[0]: &d365[0];
        #else
            const int32_t* days = omni::chrono::is_leap_year(year) ?
                                &omni::chrono::DAYS_TO_MONTH_366[0]:
                                &omni::chrono::DAYS_TO_MONTH_365[0];
        #endif

        if ((day >= 1) && (day <= (days[month] - days[month - 1]))) {
            int32_t y = year - 1;
            return ((y * 365) + (y / 4) - (y / 100) + (y / 400) + days[month - 1] + day - 1) * OMNI_TICKS_PER_DAY;
        }
    }
    OMNI_ERR_RETV_FW("Invalid year/month/day specified", omni::exceptions::invalid_range("Invalid year/month/day specified"), 0)
}

int64_t omni::chrono::date_time::_time_to_ticks(uint16_t hour, uint16_t minute, uint16_t second)
{
    //omni::chrono::time_span.TimeToTicks is a family access function which does no error checking, so
    //we need to put some error checking out here.
    if ((hour < 24) && (minute < 60) && (second < 60)) {
        return omni::chrono::time_span::from_time(hour, minute, second).ticks();
    }
    OMNI_ERR_RETV_FW("Invalid hour/minute/second specified", omni::exceptions::invalid_range("Invalid hour/minute/second specified"), 0)
}

int64_t omni::chrono::date_time::_double_date_to_ticks(double value)
{
    // DEV_NOTE: the comments are from the .NET source .. thanks to you whomever you were
    // The check done this way will take care of NaN
    if (!(value < OMNI_OA_DATE_MAX_AS_DOUBLE) || !(value > OMNI_OA_DATE_MIN_AS_DOUBLE)) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), 0)
    }
    // Conversion to long will not cause an overflow here, as at this point the "value" is in between OADateMinAsDouble and OADateMaxAsDouble
    int64_t millis = static_cast<int64_t>(value * OMNI_MILLISECONDS_PER_DAY + (value >= 0? 0.5: -0.5));
    // The interesting thing here is when you have a value like 12.5 it all positive 12 days and 12 hours from 01/01/1899
    // However if you a value of -12.25 it is minus 12 days but still positive 6 hours, almost as though you meant -11.75 all negative
    // This line below fixes up the millis in the negative case
    if (millis < 0) {
        millis -= (millis % OMNI_MILLISECONDS_PER_DAY) * 2;
    }
    millis += OMNI_DOUBLE_DATE_OFFSET / OMNI_TICKS_PER_MILLISECOND;
    if (millis < 0 || millis >= OMNI_MAX_MILLIS_FW) {
        OMNI_ERR_RETV_FW("Invalid OLE milliseconds specified", omni::exceptions::invalid_range(), 0)
    }
    return millis * OMNI_TICKS_PER_MILLISECOND;
}

omni::chrono::date_time omni::chrono::date_time::_from_binary_raw(int64_t date_data)
{
    int64_t ticks = (date_data & static_cast<int64_t>(OMNI_TICKS_MASK_FW));
    if ((ticks < 0) || (ticks > OMNI_MAX_TICKS_FW)) {
        OMNI_ERR_RETV_FW("Invalid binary tick value", omni::exceptions::invalid_range("Invalid binary tick value"), omni::chrono::date_time())
    }
    return omni::chrono::date_time(static_cast<uint64_t>(date_data));
}

double omni::chrono::date_time::_ticks_to_oa_date(int64_t value)
{
    // DEV_NOTE: the notes are from the .NET source code
    if (value == 0) {
        return 0.0;  // Returns OleAut's zero'ed date value.
    }
    if (value < OMNI_TICKS_PER_DAY) { // This is a fix for VB. They want the default day to be 1/1/0001 rather then 12/30/1899.
        value += OMNI_DOUBLE_DATE_OFFSET; // We could have moved this fix down but we would like to keep the bounds check.
    }
    if (value < OMNI_OA_DATE_MIN_AS_TICKS) {
        OMNI_ERR_RETV_FW("Invalid OLE date specified", omni::exceptions::invalid_range("Invalid OLE date specified"), 0)
    }
    // Currently, our max date == OA's max date (12/31/9999), so we don't 
    // need an overflow check in that direction.
    int64_t ms = (value  - OMNI_DOUBLE_DATE_OFFSET) / OMNI_TICKS_PER_MILLISECOND;
    if (ms < 0) {
        int64_t frac = ms % OMNI_MILLISECONDS_PER_DAY;
        if (frac != 0) {
            ms -= (OMNI_MILLISECONDS_PER_DAY + frac) * 2;
        }
    }
    return static_cast<double>(ms) / OMNI_MILLISECONDS_PER_DAY;
}

bool omni::chrono::date_time::_try_create(uint16_t year, uint16_t month, uint16_t day, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, omni::chrono::date_time& result)
{
    result = omni::chrono::date_time::min_value();
    if (year < 1 || year > OMNI_DATE_MAX_YEAR || month < 1 || month > 12) {
        return false;
    }
    if (omni::chrono::date_time::is_leap_year(year)) {
        #if defined(OMNI_NO_CONSTS)
            const int32_t d366[] = OMNI_DAYS_TO_MONTH_366;
            if (day < 1 || day > d366[month] - d366[month - 1]) {
                return false;
            }
        #else
            if (day < 1 || day > omni::chrono::DAYS_TO_MONTH_366[month] - omni::chrono::DAYS_TO_MONTH_366[month - 1]) {
                return false;
            }
        #endif
    } else {
        #if defined(OMNI_NO_CONSTS)
            const int32_t d365[] = OMNI_DAYS_TO_MONTH_365;
            if (day < 1 || day > d365[month] - d365[month - 1]) {
                return false;
            }
        #else
            if (day < 1 || day > omni::chrono::DAYS_TO_MONTH_365[month] - omni::chrono::DAYS_TO_MONTH_365[month - 1]) {
                return false;
            }
        #endif
    }            
    if (hour >= 24 || minute >= 60 || second >= 60) {
        return false;
    }                
    if (millisecond >= OMNI_MILLISECONDS_PER_SECOND) {
        return false;
    }
    int64_t ticks = omni::chrono::date_time::_date_to_ticks(year, month, day) + omni::chrono::date_time::_time_to_ticks(hour, minute, second);
    
    ticks += millisecond * OMNI_TICKS_PER_MILLISECOND;
    if (ticks < 0 || ticks > OMNI_MAX_TICKS_FW) {
        return false;
    }
    result = omni::chrono::date_time(static_cast<uint64_t>(ticks), omni::chrono::date_time_kind::UNSPECIFIED);
    return true;
}
