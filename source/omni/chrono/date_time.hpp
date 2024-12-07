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
#if !defined(OMNI_DATETIME_HPP)
#define OMNI_DATETIME_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/date_t.hpp>
#include <omni/sequence.hpp>
#include <omni/ostream.hpp>
#if defined(OMNI_SAFE_DATETIME)
    #include <omni/sync/basic_lock.hpp>
    #include <omni/sync/scoped_lock.hpp>
#endif

namespace omni {
    namespace chrono {
        /**
         * Represents a date/time object that counts 100-nanosecond intervals starting
         * at 1/1/0001 12:00am and going until 12/31/9999 23:59:59.9999999 (for a total
         * of 3155378975999999999 ticks).
         */
        class date_time
        {
            public:
                date_time(const omni::chrono::date_time& cp);
                /**
                 * @brief Constructs a date_time object from a tick value representing 100-nanosecond intervals.
                 * 
                 * @details Constructs a date_time from a tick count. The tick count specified is the date as a
                 * number of 100-nanosecond intervals that have elapsed since 1/1/0001 12:00am (or 0 ticks), and
                 * go up to a maximum value of 3155378975999999999 ticks (which is 12/31/9999 23:59:59.9999999).
                 */
                OMNI_EXPLICIT date_time(uint64_t ticks);
                date_time(uint64_t ticks, const omni::chrono::date_time_kind& kind);
                date_time(uint16_t year, uint16_t month_val, uint16_t day_val);
                date_time(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second);
                date_time(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::date_time_kind& kind);
                date_time(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond);
                date_time(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::date_time_kind& kind);
                ~date_time();
                
                omni::chrono::date_time add(const omni::chrono::time_span& value) const;
                omni::chrono::date_time add_days(double value) const;
                omni::chrono::date_time add_hours(double value) const;
                omni::chrono::date_time add_milliseconds(double value) const;
                omni::chrono::date_time add_minutes(double value) const;
                omni::chrono::date_time add_months(int32_t months) const;
                omni::chrono::date_time add_seconds(double value) const;
                omni::chrono::date_time add_ticks(int64_t value) const;
                omni::chrono::date_time add_years(int16_t value) const;
                bool is_dst() const;
                inline bool is_daylight_saving_time() const { return this->is_dst(); }
                bool is_ambiguous_dst() const;
                inline bool is_ambiguous_daylight_saving_time() const { return this->is_ambiguous_dst(); }
                bool is_leap_year() const;
                bool is_leap_day() const;
                int64_t to_binary() const;
                omni::chrono::date_time date() const;
                uint16_t day() const;
                omni::chrono::day_of_week day_of_week() const;
                uint16_t day_of_year() const;
                int32_t hash_code() const;
                uint16_t hour() const;
                omni::chrono::date_time_kind kind() const;
                uint16_t millisecond() const;
                uint16_t minute() const;
                uint16_t month() const;
                uint16_t second() const;
                uint64_t ticks() const;
                omni::chrono::time_span time_of_day() const;
                uint16_t year() const;
                omni::chrono::time_span utc_offset() const;
                omni::chrono::time_span subtract(const omni::chrono::date_time& value) const;
                omni::chrono::date_time subtract(const omni::chrono::time_span& value) const;
                double to_oa_date() const;
                uint64_t to_file_time() const;
                uint64_t to_file_time_utc() const;
                omni::chrono::date_time to_local_time() const;
                std::string to_long_date_string() const;
                std::wstring to_long_date_wstring() const;
                std::string to_long_time_string() const;
                std::wstring to_long_time_wstring() const;
                std::string to_short_date_string() const;
                std::wstring to_short_date_wstring() const;
                std::string to_short_time_string() const;
                std::wstring to_short_time_wstring() const;
                /*
                    Format specifier 	Description 	Examples
                    "d" 	The day of the month, from 1 to 31.
                    "dd" 	The day of the month, from 01 to 31.
                    "ddd" 	The abbreviated name of the day of the week.
                    "dddd" 	The full name of the day of the week.
                    "f" 	The tenths of a second in a date and time value.
                    "ff" 	The hundredths of a second in a date and time value.
                    "fff" 	The milliseconds in a date and time value.
                    "ffff" 	The ten thousandths of a second in a date and time value.
                    "fffff" 	The hundred thousandths of a second in a date and time value.
                    "ffffff" 	The millionths of a second in a date and time value.
                    "fffffff" 	The ten millionths of a second in a date and time value.
                    "F" 	If non-zero, the tenths of a second in a date and time value.
                    "FF" 	If non-zero, the hundredths of a second in a date and time value.
                    "FFF" 	If non-zero, the milliseconds in a date and time value.
                    "FFFF" 	If non-zero, the ten thousandths of a second in a date and time value.
                    "FFFFF" 	If non-zero, the hundred thousandths of a second in a date and time value.
                    "FFFFFF" 	If non-zero, the millionths of a second in a date and time value.
                    "FFFFFFF" 	If non-zero, the ten millionths of a second in a date and time value.
                    "g", "gg" 	The period or era (e.g. A.D.).
                    "h" 	The hour, using a 12-hour clock from 1 to 12.
                    "hh" 	The hour, using a 12-hour clock from 01 to 12.
                    "H" 	The hour, using a 24-hour clock from 0 to 23.
                    "HH" 	The hour, using a 24-hour clock from 00 to 23.
                    "K" 	Time zone information.
                    "m" 	The minute, from 0 to 59.
                    "mm" 	The minute, from 00 to 59.
                    "M" 	The month, from 1 to 12.
                    "MM" 	The month, from 01 to 12.
                    "MMM" 	The abbreviated name of the month.
                    "MMMM" 	The full name of the month.
                    "s" 	The second, from 0 to 59.
                    "ss" 	The second, from 00 to 59.
                    "t" 	The first character of the AM/PM designator.
                    "tt" 	The AM/PM designator.
                    "y" 	The year, from 0 to 99.
                    "yy" 	The year, from 00 to 99.
                    "yyy" 	The year, with a minimum of three digits.
                    "yyyy" 	The year as a four-digit number.
                    "yyyyy" 	The year as a five-digit number.
                    "z" 	Hours offset from UTC, with no leading zeros.
                    "zz" 	Hours offset from UTC, with a leading zero for a single-digit value.
                    "zzz" 	Hours and minutes offset from UTC.
                    ":" 	The time separator.
                    "/" 	The date separator.
                    "string"
                    'string' 	Literal string delimiter.
                    % 	Defines the following character as a custom format specifier.
                    \ 	The escape character.
                    Any other character 	The character is copied to the result string unchanged.
                */
                std::string to_string(const std::string& format) const;
                std::wstring to_wstring(const std::wstring& format) const;
                omni::chrono::date_time to_universal_time() const;
                inline omni::chrono::date_time to_utc() const { return this->to_universal_time(); }
                inline std::string to_sortable_string() const { return this->to_string("yyyyMMdd HH:mm:ss"); }
                inline std::wstring to_sortable_wstring() const { return this->to_wstring(L"yyyyMMdd HH:mm:ss"); }
                std::string to_military_dtg_string() const;
                std::wstring to_military_dtg_wstring() const;
                void swap(omni::chrono::date_time& other);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                omni::chrono::date_time& operator=(const omni::chrono::date_time& other);
                omni::chrono::date_time operator+(const omni::chrono::time_span& span);
                omni::chrono::date_time operator-(const omni::chrono::time_span& span);
                omni::chrono::date_time& operator+=(const omni::chrono::time_span& span);
                omni::chrono::date_time& operator-=(const omni::chrono::time_span& span);
                omni::chrono::time_span operator+(const omni::chrono::date_time& other);
                omni::chrono::time_span operator-(const omni::chrono::date_time& other);
                bool operator==(const omni::chrono::date_time& other) const;
                bool operator!=(const omni::chrono::date_time& other) const;
                bool operator<(const omni::chrono::date_time& other) const;
                bool operator<=(const omni::chrono::date_time& other) const;
                bool operator>(const omni::chrono::date_time& other) const;
                bool operator>=(const omni::chrono::date_time& other) const;
                
                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::chrono::date_time) // disposing,name,type(),hash()
                OMNI_OSTREAM_FW(omni::chrono::date_time)

                static inline omni::chrono::date_time min_value()
                {
                    return omni::chrono::date_time();
                }

                static inline omni::chrono::date_time max_value()
                {
                    return omni::chrono::date_time(OMNI_TICKS_TO_10000AD, omni::chrono::date_time_kind::UNSPECIFIED);
                }

                static inline uint64_t min_ticks()
                {
                    return 0;
                }

                static inline uint64_t max_ticks()
                {
                    return OMNI_TICKS_TO_10000AD;
                }

                static omni::chrono::date_time parse(const std::string& date_string);
                static omni::chrono::date_time parse_exact(const std::string& date_string, const std::string& format);
                static omni::chrono::date_time parse_exact(const std::string& date_string, const std::string& format, const omni::chrono::date_time_styles& style);
                static bool try_parse(const std::string& date_string, omni::chrono::date_time& result);
                static bool try_parse_exact(const std::string& date_string, const std::string& format, omni::chrono::date_time& result);
                static bool try_parse_exact(const std::string& date_string, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result);
                static bool try_parse(const std::string& date_string, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason);
                static bool try_parse_exact(const std::string& date_string, const std::string& format, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason);
                static bool try_parse_exact(const std::string& date_string, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result, omni::chrono::date_time_parse_failure& fail_reason);
                static uint16_t days_in_month(uint16_t year, uint16_t month_val);
                static omni::chrono::date_time from_binary(int64_t date_data);
                static omni::chrono::date_time from_file_time(int64_t file_time);
                static omni::chrono::date_time from_file_time_utc(int64_t file_time);
                static omni::chrono::date_time from_oa_date(double oa_val);
                static omni::chrono::date_time from_offset(const omni::chrono::date_time& other, const omni::chrono::span_t& offset);
                static omni::chrono::date_time from_offset(const omni::chrono::date_time& other, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind);
                static omni::chrono::date_time from_offset(uint64_t ticks, const omni::chrono::span_t& offset);
                static omni::chrono::date_time from_offset(uint64_t ticks, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind);
                static omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::span_t& offset);
                static omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind);
                static omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::span_t& offset);
                static omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind);
                static omni::sequence::string_t get_date_time_formats();
                static omni::sequence::string_t get_date_time_formats(char format);
                static double offset_from_utc();
                static omni::chrono::date_time specify_kind(const omni::chrono::date_time& value, const omni::chrono::date_time_kind& kind);
                static omni::chrono::date_time now();
                static omni::chrono::date_time utc_now();
                static omni::chrono::date_time today();
                static bool is_leap_year(uint16_t year);
                static bool is_leap_year(const omni::chrono::date_time& date);
                static bool is_leap_day(uint16_t year, uint16_t month_val, uint16_t day_val);
                static bool is_leap_day(const omni::chrono::date_time& date);
                static bool is_valid_day(uint16_t year, uint16_t month_val, uint16_t day_val);
                static uint16_t to_four_digit_year(uint16_t year, uint16_t two_digit_year_max);
                static uint16_t to_four_digit_year(uint16_t year);
                static bool try_create(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, omni::chrono::date_time& result);
                
            private:
                /**
                 * @brief The underlying date data stored as uin64_t
                 * 
                 * @details The data is stored as an unsigned 64-bit integer
                 * Bits 01-62: The value of 100-nanosecond ticks where 0 represents 1/1/0001 12:00am, up until the value
                 *             12/31/9999 23:59:59.9999999
                 * Bits 63-64: A four-state value that describes the omni::chrono::date_time_kind value of the date time, with a 2nd
                 *             value for the rare case where the date time is local, but is in an overlapped daylight
                 *             savings time hour and it is in daylight savings time. This allows distinction of these
                 *             otherwise ambiguous local times and prevents data loss when round tripping from Local to
                 *             UTC time.
                 */
                uint64_t m_date;
                #if defined(OMNI_SAFE_DATETIME)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                date_time(); // not 'user' accessible as it's used to construct empty (min) DT objects
                date_time(uint64_t ticks, const char* non_op);
                date_time(bool is_ambiguous_dst, const omni::chrono::date_time_kind& kind, uint64_t ticks, const char* non_op);
                omni::chrono::date_time _add(double value, int64_t scale) const;
                omni::chrono::date_time_kind _kind() const;
                int64_t _to_binary_raw() const;
                int64_t _get_date_part(uint16_t part) const;
                omni::chrono::date_time _to_local_time(bool throw_on_overflow) const;

                inline uint64_t _date_value() const
                {
                    #if defined(OMNI_SAFE_DATETIME)
                        omni::sync::scoped_lock<omni::sync::basic_lock> uuid12345(&this->m_mtx);
                    #endif
                    return this->m_date;
                }

                inline int64_t _ticks() const
                {
                    return static_cast<int64_t>(this->m_date & OMNI_TICKS_MASK_FW);
                }

                inline uint64_t _internal_kind() const
                {
                    return (this->m_date & OMNI_DATE_FLAGS_MASK_FW);
                }

                static int64_t _date_to_ticks(uint16_t year, uint16_t month_val, uint16_t day_val);
                static int64_t _time_to_ticks(uint16_t hour, uint16_t minute, uint16_t second);
                static int64_t _double_date_to_ticks(double value);
                static omni::chrono::date_time _from_binary_raw(int64_t date_data);
                static double _ticks_to_oa_date(int64_t value);
                static bool _try_create(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, omni::chrono::date_time& result);
        };

        inline uint16_t days_in_month(uint16_t year, uint16_t month_val)
        {
            return omni::chrono::date_time::days_in_month(year, month_val);
        }
        
        inline omni::chrono::date_time from_binary(int64_t date_data)
        {
            return omni::chrono::date_time::from_binary(date_data);
        }
        
        inline omni::chrono::date_time from_file_time(int64_t file_time)
        {
            return omni::chrono::date_time::from_file_time(file_time);
        }
        
        inline omni::chrono::date_time from_file_time_utc(int64_t file_time)
        {
            return omni::chrono::date_time::from_file_time_utc(file_time);
        }
        
        inline omni::chrono::date_time from_oa_date(double d)
        {
            return omni::chrono::date_time::from_oa_date(d);
        }

        inline omni::chrono::date_time from_offset(const omni::chrono::date_time& other, const omni::chrono::span_t& offset)
        {
            return omni::chrono::date_time::from_offset(other, offset);
        }

        inline omni::chrono::date_time from_offset(const omni::chrono::date_time& other, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
        {
            return omni::chrono::date_time::from_offset(other, offset, kind);
        }

        inline omni::chrono::date_time from_offset(uint64_t ticks, const omni::chrono::span_t& offset)
        {
            return omni::chrono::date_time::from_offset(ticks, offset);
        }

        inline omni::chrono::date_time from_offset(uint64_t ticks, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
        {
            return omni::chrono::date_time::from_offset(ticks, offset, kind);
        }

        inline omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::span_t& offset)
        {
            return omni::chrono::date_time::from_offset(year, month_val, day_val, hour, minute, second, offset);
        }

        inline omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
        {
            return omni::chrono::date_time::from_offset(year, month_val, day_val, hour, minute, second, offset, kind);
        }

        inline omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::span_t& offset)
        {
            return omni::chrono::date_time::from_offset(year, month_val, day_val, hour, minute, second, millisecond, offset);
        }
        
        inline omni::chrono::date_time from_offset(uint16_t year, uint16_t month_val, uint16_t day_val, uint16_t hour, uint16_t minute, uint16_t second, uint16_t millisecond, const omni::chrono::span_t& offset, const omni::chrono::date_time_kind& kind)
        {
            return omni::chrono::date_time::from_offset(year, month_val, day_val, hour, minute, second, millisecond, offset, kind);
        }
        
        inline omni::chrono::date_time specify_kind(const omni::chrono::date_time& value, const omni::chrono::date_time_kind& kind)
        {
            return omni::chrono::date_time::specify_kind(value, kind);
        }
        
        inline omni::chrono::date_time now()
        {
            return omni::chrono::date_time::now();
        }

        inline omni::chrono::date_time utc_now()
        {
            return omni::chrono::date_time::utc_now();
        }
        
        inline omni::chrono::date_time today()
        {
            return omni::chrono::date_time::today();
        }
        
        inline bool is_leap_year(uint16_t year)
        {
            return omni::chrono::date_time::is_leap_year(year);
        }

        inline bool is_leap_year(const omni::chrono::date_time& date)
        {
            return omni::chrono::date_time::is_leap_year(date);
        }
    } // namespace chrono
} // namespace omni

namespace std {
    inline void swap(omni::chrono::date_time& o1, omni::chrono::date_time& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_TIME_HPP
