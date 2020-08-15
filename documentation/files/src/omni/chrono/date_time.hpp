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

/*
    TODO: need to add these once the Calendar class is built
    date_time(uint16_t year, uint8_t month, uint8_t day, Calendar calendar);
    date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, Calendar calendar);
    date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint32_t millisecond, Calendar calendar);
    date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint32_t millisecond, Calendar calendar, const omni::chrono::date_time_kind& kind);

    TODO: add these when IFormatProvider is ever completed (not important for this release)
    std::string to_string(std::string format, IFormatProvider provider);
    std::string[] GetDateTimeFormats(IFormatProvider provider);
    std::string[] GetDateTimeFormats(char format, IFormatProvider provider);
    static date_time Parse(const std::string& s, IFormatProvider provider);
    static date_time Parse(const std::string& s, IFormatProvider provider, DateTimeStyles styles);
    static date_time ParseExact(const std::string& s, std::string format, IFormatProvider provider);
    static date_time ParseExact(const std::string& s, std::string format, IFormatProvider provider, DateTimeStyles style);
    static date_time ParseExact(const std::string& s, std::string[] formats, IFormatProvider provider, DateTimeStyles style);
    static bool TryParse(const std::string& s, IFormatProvider provider, DateTimeStyles styles, out date_time result);
    static bool TryParseExact(const std::string& s, const std::string& format, IFormatProvider provider, DateTimeStyles style, date_time& result);
    static bool TryParseExact(const std::string& s, const std::string& formats[], IFormatProvider provider, DateTimeStyles style, date_time& result);

    TODO: do these make sense to add??
    static int Compare(date_time t1, date_time t2);
    static bool Equals(date_time t1, date_time t2);
*/

namespace omni {
    namespace chrono {
        class date_time
        {
            public:
                date_time(const omni::chrono::date_time& cp);
                explicit date_time(uint64_t ticks);
                date_time(uint64_t ticks, const omni::chrono::date_time_kind& kind);
                date_time(uint16_t year, uint8_t month, uint8_t day);
                date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
                date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, const omni::chrono::date_time_kind& kind);
                date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond);
                date_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, const omni::chrono::date_time_kind& kind);
                ~date_time();
                
                omni::chrono::date_time add(const omni::chrono::time_span& value);
                omni::chrono::date_time add_days(double value);
                omni::chrono::date_time add_hours(double value);
                omni::chrono::date_time add_milliseconds(double value);
                omni::chrono::date_time add_minutes(double value);
                omni::chrono::date_time add_months(uint32_t months);
                omni::chrono::date_time add_seconds(double value);
                omni::chrono::date_time add_ticks(int64_t value);
                omni::chrono::date_time add_years(int16_t value);
                bool is_dst() const;
                inline bool is_daylight_saving_time() const { return this->is_dst(); }
                int64_t to_binary() const;
                omni::chrono::date_time date() const;
                uint8_t day() const;
                omni::chrono::day_of_week day_of_week() const;
                uint16_t day_of_year() const;
                int32_t hash_code() const;
                uint8_t hour() const;
                omni::chrono::date_time_kind kind() const;
                uint16_t millisecond() const;
                uint8_t minute() const;
                uint8_t month() const;
                uint8_t second() const;
                uint64_t ticks() const;
                omni::chrono::time_span time_of_day() const;
                uint16_t year() const;
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
                std::string to_string(const std::string& format) const;
                std::wstring to_wstring(const std::wstring& format) const;
                omni::chrono::date_time to_universal_time() const;
                omni::sequence::string_t get_date_time_formats() const;
                omni::sequence::string_t get_date_time_formats(char format) const;
                void swap(omni::chrono::date_time& other);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                omni::chrono::date_time& operator=(const omni::chrono::date_time& ap);
                omni::chrono::date_time operator+(const omni::chrono::time_span& t);
                omni::chrono::date_time operator-(const omni::chrono::time_span& t);
                omni::chrono::date_time& operator+=(const omni::chrono::time_span& t);
                omni::chrono::date_time& operator-=(const omni::chrono::time_span& t);
                omni::chrono::time_span operator+(const omni::chrono::date_time& d2);
                omni::chrono::time_span operator-(const omni::chrono::date_time& d2);

                bool operator==(const omni::chrono::date_time& d2) const;
                bool operator!=(const omni::chrono::date_time& d2) const;
                bool operator<(const omni::chrono::date_time& d2) const;
                bool operator<=(const omni::chrono::date_time& d2) const;
                bool operator>(const omni::chrono::date_time& d2) const;
                bool operator>=(const omni::chrono::date_time& d2) const;
                
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

                static inline date_time min_value()
                {
                    return date_time();
                }

                static inline date_time max_value()
                {
                    return date_time(omni::chrono::TICKS_TO_10000AD, omni::chrono::date_time_kind::UNSPECIFIED);
                }

                static uint16_t days_in_month(uint16_t year, uint8_t month);
                static omni::chrono::date_time from_binary(int64_t date_data);
                static omni::chrono::date_time from_file_time(int64_t file_time);
                static omni::chrono::date_time from_file_time_utc(int64_t file_time);
                static omni::chrono::date_time from_oa_date(double d);
                static omni::chrono::date_time specify_kind(const date_time& value, const omni::chrono::date_time_kind& kind);
                static omni::chrono::date_time now();
                static omni::chrono::date_time utc_now();
                static omni::chrono::date_time today();
                static bool is_leap_year(uint16_t year);
                static omni::chrono::date_time parse(const std::string& s);
                static omni::chrono::date_time parse_exact(const std::string& s, const std::string& format);
                static bool try_parse(const std::string& s, omni::chrono::date_time& result);
                static bool try_parse_exact(const std::string& s, const std::string& format, const omni::chrono::date_time_styles& style, omni::chrono::date_time& result);
                
            private:
                uint64_t m_date;
                #if defined(OMNI_SAFE_DATETIME)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                date_time(); // not 'user' accessable as it's used to construct empty (min) DT objects
                date_time(bool is_ambiguous_dst, const omni::chrono::date_time_kind& kind, uint64_t ticks, const std::string& non_op);
                omni::chrono::date_time _add(double value, int64_t scale);
                omni::chrono::date_time_kind _kind() const;
                int64_t _to_binary_raw() const;
                int64_t _get_date_part(uint8_t part) const;
                bool _is_ambiguous_daylight_saving_time() const;
                omni::chrono::date_time _to_local_time(bool throw_on_overflow) const;

                inline int64_t _ticks() const
                {
                    return static_cast<int64_t>(this->m_date & OMNI_TICKS_MASK_FW);
                }

                inline uint64_t _internal_kind() const
                {
                    return (this->m_date & OMNI_FLAGS_MASK_FW);
                }

                static int64_t _date_to_ticks(uint16_t year, uint8_t month, uint8_t day);
                static int64_t _time_to_ticks(uint8_t hour, uint8_t minute, uint8_t second);
                static int64_t _double_date_to_ticks(double value);
                static omni::chrono::date_time _from_binary_raw(int64_t date_data);
                static double _ticks_to_oa_date(int64_t value);
                static bool _try_create(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, omni::chrono::date_time& result);
        };

        inline uint16_t days_in_month(uint16_t year, uint8_t month)
        {
            return omni::chrono::date_time::days_in_month(year, month);
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
    } // namespace chrono
} // namespace omni

namespace std {
    inline void swap(omni::chrono::date_time& o1, omni::chrono::date_time& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_TIME_HPP
