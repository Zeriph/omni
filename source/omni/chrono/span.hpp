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
#if !defined(OMNI_SPAN_HPP)
#define OMNI_SPAN_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/tick_t.hpp>
#include <omni/strings.hpp>
#include <omni/ostream.hpp>
#include <omni/math.hpp>

#if defined(OMNI_SAFE_SPAN)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_SPANMTX_FW  ,m_mtx()
    #define OMNI_SPAN_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> uuid12345(&this->m_mtx);
    #define OMNI_SPAN_OLOCK_FW(o) omni::sync::scoped_lock<omni::sync::basic_lock> uuid54321(&o.m_mtx);
    #define OMNI_SPAN_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_SPAN_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_SPANMTX_FW
    #define OMNI_SPAN_ALOCK_FW
    #define OMNI_SPAN_OLOCK_FW(o) 
    #define OMNI_SPAN_MLOCK_FW
    #define OMNI_SPAN_ULOCK_FW
#endif

/*
    TODO: make note in the docs that a span does not account for 'years' because
    of the variations in calendaring and what a 'year' actually is (see the link
    for DAYS_PER_TROPICAL_YEAR. A 'day' for a span is considered a 24 hour period
    which consists of 60 minute hours and 60 second minutes, so total days can be
    calculated on a constant basis where as years are too variable, which is why
    there is a date_time class.
*/

namespace omni {
    namespace chrono {
        template < typename TickType >
        class span
        {
            public:
                typedef TickType span_t;

                span() :
                    OMNI_CTOR_FW(omni::chrono::span)
                    m_ticks(0)
                    OMNI_SAFE_SPANMTX_FW
                {
                    OMNI_D5_FW("created");
                }

                span(const omni::chrono::span<TickType>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_ticks(cp.m_ticks)
                    OMNI_SAFE_SPANMTX_FW
                {
                    OMNI_D5_FW("copied");
                }

                //implicit
                span(span_t ticks) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    m_ticks(ticks)
                    OMNI_SAFE_SPANMTX_FW
                {
                    OMNI_D5_FW("created");
                }

                span(span_t hours, span_t minutes, span_t seconds) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    m_ticks(0)
                    OMNI_SAFE_SPANMTX_FW
                {
                    this->m_ticks = _time_to_ticks(hours, minutes, seconds);
                    OMNI_D5_FW("created");
                }

                span(span_t days, span_t hours, span_t minutes, span_t seconds) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    m_ticks(0)
                    OMNI_SAFE_SPANMTX_FW
                {
                    this->m_ticks = _time_to_ticks(days, hours, minutes, seconds, 0);
                    OMNI_D5_FW("created");
                }

                span(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    m_ticks(0)
                    OMNI_SAFE_SPANMTX_FW
                {
                    this->m_ticks = _time_to_ticks(days, hours, minutes, seconds, milliseconds);
                    OMNI_D5_FW("created");
                }

                ~span()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                omni::chrono::span<TickType>& add(const omni::chrono::span<TickType>& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks += this->m_ticks;
                    } else {
                        this->m_ticks += other.ticks();
                    }
                    return *this;
                }

                omni::chrono::span<TickType>& add(TickType ticks)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks += ticks;
                    return *this;
                }

                bool can_negate() const
                {
                    return std::numeric_limits<span_t>::min() < 0;
                }

                // days portion
                span_t days() const
                {
                    return static_cast<span_t>(std::abs(static_cast<double>(this->ticks())) / OMNI_TICKS_PER_DAY);
                }

                omni::chrono::span<TickType> duration() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return span<TickType>(this->m_ticks >= 0 ? this->m_ticks : -this->m_ticks);
                }

                // hours component
                span_t hours() const
                {
                    return static_cast<span_t>(std::abs(static_cast<double>(this->ticks())) / OMNI_TICKS_PER_HOUR) % 24;
                }
                
                uint64_t hash_code() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks ^ (this->m_ticks >> 32);
                }

                // milliseconds component
                span_t milliseconds() const
                {
                    return static_cast<span_t>(std::abs(static_cast<double>(this->ticks())) / OMNI_TICKS_PER_MILLISECOND) % 1000;
                }

                // minutes component
                span_t minutes() const
                {
                    return static_cast<span_t>(std::abs(static_cast<double>(this->ticks())) / OMNI_TICKS_PER_MINUTE) % 60;
                }

                omni::chrono::span<TickType> negate() const
                {
                    if (this->can_negate()) {
                        // has sign, can negate
                        OMNI_SPAN_ALOCK_FW
                        return span<TickType>(-this->m_ticks);
                    }
                    OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("cannot negate unsigned span"), span<TickType>::zero())
                }

                // seconds component
                span_t seconds() const
                {
                    return static_cast<span_t>(std::abs(static_cast<double>(this->ticks())) / OMNI_TICKS_PER_SECOND) % 60;
                }

                omni::chrono::span<TickType>& subtract(const omni::chrono::span<TickType>& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks = 0; // x-x is always 0
                    } else {
                        this->m_ticks -= other.ticks();
                    }
                    return *this;
                }

                omni::chrono::span<TickType>& subtract(TickType ticks)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks -= ticks;
                    return *this;
                }

                void swap(omni::chrono::span<TickType>& o)
                {
                    if (this != &o) {
                        OMNI_SPAN_ALOCK_FW
                        OMNI_SPAN_OLOCK_FW(o)
                        std::swap(this->m_ticks, o.m_ticks);
                    }
                }

                // total ticks
                span_t ticks() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks;
                }

                // days as whole and fractional
                double total_days() const
                {
                    return static_cast<double>(this->ticks()) * OMNI_DAYS_PER_TICK;
                }

                // hours as whole and fractional
                double total_hours() const
                {
                    return static_cast<double>(this->ticks()) * OMNI_HOURS_PER_TICK;
                }

                double total_milliseconds() const
                {
                    double temp = static_cast<double>(this->ticks()) * OMNI_MILLISECONDS_PER_TICK;
                    if (temp > omni::chrono::span<TickType>::max_milliseconds()) {
                        return static_cast<double>(omni::chrono::span<TickType>::max_milliseconds());
                    }
                    if (temp < omni::chrono::span<TickType>::min_milliseconds()) {
                        return static_cast<double>(omni::chrono::span<TickType>::min_milliseconds());
                    }
                    return temp;
                }

                double total_minutes() const
                {
                    return static_cast<double>(this->ticks()) * OMNI_MINUTES_PER_TICK;
                }

                double total_seconds() const
                {
                    return static_cast<double>(this->ticks()) * OMNI_SECONDS_PER_TICK;
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t ss;
                    this->_to_string_base(ss);
                    return ss.str();
                }

                std::string to_string() const
                {
                    std::stringstream ss;
                    this->_to_string_base(ss);
                    return ss.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream ss;
                    this->_to_string_base(ss);
                    return ss.str();
                }

                omni::chrono::span<TickType>& operator=(const omni::chrono::span<TickType>& other)
                {
                    if (this != &other) {
                        OMNI_SPAN_ALOCK_FW
                        OMNI_ASSIGN_FW(other)
                        this->m_ticks = other.ticks();
                    }
                    return *this;
                }

                omni::chrono::span<TickType>& operator=(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks = val;
                    return *this;
                }

                omni::chrono::span<TickType> operator-(const omni::chrono::span<TickType>& other)
                {
                    if (this == &other) {
                        // no need to lock, since (m_ticks - m_ticks == 0)
                        return span<TickType>(0);
                    }
                    OMNI_SPAN_ALOCK_FW
                    return span<TickType>(this->m_ticks - other.ticks());
                }

                omni::chrono::span<TickType> operator-(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    return span<TickType>(this->m_ticks - val);
                }

                omni::chrono::span<TickType> operator+(const omni::chrono::span<TickType>& other)
                {
                    if (this == &other) {
                        OMNI_SPAN_ALOCK_FW
                        return span<TickType>(this->m_ticks + this->m_ticks);
                    }
                    OMNI_SPAN_ALOCK_FW
                    return span<TickType>(this->m_ticks + other.ticks());
                }

                omni::chrono::span<TickType> operator+(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    return span<TickType>(this->m_ticks + val);
                }

                omni::chrono::span<TickType>& operator-=(const omni::chrono::span<TickType>& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks = 0; // x-x is always 0
                    } else {
                        this->m_ticks -= other.ticks();
                    }
                    return *this;
                }

                omni::chrono::span<TickType>& operator-=(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks -= val;
                    return *this;
                }

                omni::chrono::span<TickType>& operator+=(const omni::chrono::span<TickType>& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        // t+t = 2t = t<<1
                        this->m_ticks <<= 1;
                    } else {
                        this->m_ticks += other.ticks();
                    }
                    return *this;
                }

                omni::chrono::span<TickType>& operator+=(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks += val;
                    return *this;
                }

                omni::chrono::span<TickType> operator-()
                {
                    return this->negate();
                }

                omni::chrono::span<TickType>& operator+()
                {
                    // useful as a no-op (might get optimized out)
                    return *this;
                }

                bool operator==(const omni::chrono::span<TickType>& other) const
                {
                    if (this == &other) { return true; }
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks == other.ticks();
                }

                bool operator==(span_t val) const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks == val;
                }

                bool operator!=(const omni::chrono::span<TickType>& other) const
                {
                    if (this == &other) { return false; }
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks != other.ticks();
                }

                bool operator!=(span_t val) const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks != val;
                }

                bool operator<(const omni::chrono::span<TickType>& other) const
                {
                    if (this == &other) { return false; }
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks < other.ticks();
                }

                bool operator<(span_t val) const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks < val;
                }

                bool operator>(const omni::chrono::span<TickType>& other) const
                {
                    if (this == &other) { return false; }
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks > other.ticks();
                }

                bool operator>(span_t val) const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks > val;
                }

                bool operator<=(const omni::chrono::span<TickType>& other) const
                {
                    if (this == &other) { return true; }
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks <= other.ticks();
                }

                bool operator<=(span_t val) const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks <= val;
                }

                bool operator>=(const omni::chrono::span<TickType>& other) const
                {
                    if (this == &other) { return true; }
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks >= other.ticks();
                }

                bool operator>=(span_t val) const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks >= val;
                }

                operator span_t() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks;
                }

                operator std::string() const { return this->to_string(); }

                operator std::wstring() const { return this->to_wstring(); }

                OMNI_MEMBERS_FW(omni::chrono::span<TickType>) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::chrono::span<TickType>)

                static omni::chrono::span<TickType> parse(const std::string& s)
                {
                    span<TickType> ret;
                    if (!omni::chrono::span<TickType>::try_parse(s, ret)) {
                        OMNI_ERR_RETV_FW("parse error", omni::exceptions::invalid_parse(), ret)
                    }
                    return ret;
                }

                static omni::chrono::span<TickType> parse(const std::wstring& s)
                {
                    span<TickType> ret;
                    if (!omni::chrono::span<TickType>::try_parse(s, ret)) {
                        OMNI_ERR_RETV_FW("parse error", omni::exceptions::invalid_parse(), ret)
                    }
                    return ret;
                }

                static bool try_parse(const std::string& s, omni::chrono::span<TickType>& result)
                {
                    return _try_parse<std::string, char>(s, result);
                }

                static bool try_parse(const std::wstring& s, omni::chrono::span<TickType>& result)
                {
                    return _try_parse<std::wstring, wchar_t>(s, result);
                }

                static inline omni::chrono::span<TickType> from_time(span_t hours, span_t minutes, span_t seconds)
                {
                    return span<TickType>(hours, minutes, seconds);
                }

                static inline omni::chrono::span<TickType> from_time(span_t days, span_t hours, span_t minutes, span_t seconds)
                {
                    return span<TickType>(days, hours, minutes, seconds);
                }

                static inline omni::chrono::span<TickType> from_time(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds)
                {
                    return span<TickType>(days, hours, minutes, seconds, milliseconds);
                }

                static inline omni::chrono::span<TickType> from_days(double value)
                {
                    return _interval(value, OMNI_MILLISECONDS_PER_DAY);
                }

                static inline omni::chrono::span<TickType> from_hours(double value)
                {
                    return _interval(value, OMNI_MILLISECONDS_PER_HOUR);
                }

                static inline omni::chrono::span<TickType> from_milliseconds(double value)
                {
                    return _interval(value, 1);
                }

                static inline omni::chrono::span<TickType> from_minutes(double value)
                {
                    return _interval(value, OMNI_MILLISECONDS_PER_MINUTE);
                }

                static inline omni::chrono::span<TickType> from_microseconds(span_t value)
                {
                    return span<TickType>(value * OMNI_TICKS_PER_MICROSECOND);
                }

                static inline omni::chrono::span<TickType> from_nanoseconds(span_t value)
                {
                    return span<TickType>(value * OMNI_TICKS_PER_NANOSECOND);
                }

                static inline omni::chrono::span<TickType> from_seconds(double value)
                {
                    return _interval(value, OMNI_MILLISECONDS_PER_SECOND);
                }

                static inline omni::chrono::span<TickType> from_ticks(span_t value)
                {
                    return span<TickType>(value);
                }

                static inline span_t max_seconds()
                {
                    return std::numeric_limits<span_t>::max() / OMNI_TICKS_PER_SECOND;
                }
                
                static inline span_t min_seconds()
                {
                    return std::numeric_limits<span_t>::min() / OMNI_TICKS_PER_SECOND;
                }
                
                static inline span_t max_milliseconds()
                {
                    return std::numeric_limits<span_t>::max() / OMNI_TICKS_PER_MILLISECOND;
                }
                
                static inline span_t min_milliseconds()
                {
                    return std::numeric_limits<span_t>::min() / OMNI_TICKS_PER_MILLISECOND;
                }

                static inline omni::chrono::span<TickType> max_value()
                {
                    return span<TickType>(std::numeric_limits<span_t>::max());
                }

                static inline omni::chrono::span<TickType> min_value()
                {
                    return span<TickType>(std::numeric_limits<span_t>::min());
                }

                static inline omni::chrono::span<TickType> zero()
                {
                    return span<TickType>(0);
                }
                
            private:
                span_t m_ticks; // 100-nanosecond units
                #if defined(OMNI_SAFE_SPAN)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                template < typename StrStr >
                void _to_string_base(StrStr& ss) const
                {
                    span_t t = this->ticks();
                    span_t d = static_cast<span_t>(std::abs(static_cast<double>(t)) / OMNI_TICKS_PER_DAY);
                    span_t h = static_cast<span_t>(std::abs(static_cast<double>(t)) / OMNI_TICKS_PER_HOUR) % 24;
                    span_t m = static_cast<span_t>(std::abs(static_cast<double>(t)) / OMNI_TICKS_PER_MINUTE) % 60;
                    span_t s = static_cast<span_t>(std::abs(static_cast<double>(t)) / OMNI_TICKS_PER_SECOND) % 60;
                    // d.hh:mm:ss.ms
                    if (t < 0) { ss << "-"; }
                    ss << d << ".";
                    if (h < 10) { ss << "0"; }
                    ss << h << ":";
                    if (m < 10) { ss << "0"; }
                    ss << m << ":";
                    if (s < 10) { ss << "0"; }
                    ss << s << ".";
                    ss << (static_cast<span_t>(std::abs(static_cast<double>(t)) / OMNI_TICKS_PER_MILLISECOND) % 1000);
                }

                static omni::chrono::span<TickType> _interval(double value, int32_t scale)
                {
                    if (!omni::math::is_nan(value)) { // NaN check
                        double tmp = value * scale;
                        double millis = tmp + ((value >= 0) ? 0.5 : -0.5);
                        if ((millis > omni::chrono::span<TickType>::max_milliseconds()) || (millis < omni::chrono::span<TickType>::min_milliseconds())) {
                            OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid span"), span<TickType>::zero())
                        }
                        return span<TickType>(static_cast<span_t>(millis) * OMNI_TICKS_PER_MILLISECOND);
                    }
                    OMNI_ERR_RETV_FW(OMNI_NAN_ERR_STR, omni::exceptions::nan_error("span cannot be NaN"), span<TickType>::zero())
                }

                static span_t _time_to_ticks(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds)
                {
                    span_t tot = (((days * 86400 /* 3600 * 24*/) + (hours * 3600) + (minutes * 60) + seconds) * 1000) + milliseconds;
                    if (tot > omni::chrono::span<TickType>::max_milliseconds() || tot < omni::chrono::span<TickType>::min_milliseconds())
                        OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid span"), span<TickType>::zero())
                    return tot * OMNI_TICKS_PER_MILLISECOND;
                }

                static span_t _time_to_ticks(span_t hour, span_t minute, span_t second)
                {
                    // totalSeconds is bounded by 2^31 * 2^12 + 2^31 * 2^8 + 2^31,
                    // which is less than 2^44, meaning we will not overflow totalSeconds.
                    span_t tot = (hour * 3600) + (minute * 60) + second;
                    if (tot > omni::chrono::span<TickType>::max_seconds() || tot < omni::chrono::span<TickType>::min_seconds()) {
                        OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid span"), span<TickType>::zero())
                    }
                    return tot * OMNI_TICKS_PER_SECOND;
                }

                template < typename Str, typename Char >
                static bool _try_parse(const Str& s, span<TickType>& result)
                {
                    /*
                        Elements in square brackets ([ and ]) are optional.
                        One selection from the list of alternatives enclosed in braces ({ and }) and separated by vertical bars (|) is required.

                        Element     Description
                        ws     Optional white space.
                        -     An optional minus sign, which indicates a negative TimeSpan.
                        d     Days, ranging from 0 to 10675199.
                        .     A culture-sensitive symbol that separates days from hours. The invariant format uses a period (".") character.
                        hh     Hours, ranging from 0 to 23.
                        :     The culture-sensitive time separator symbol. The invariant format uses a colon (":") character.
                        mm     Minutes, ranging from 0 to 59.
                        ss     Optional seconds, ranging from 0 to 59.
                        .     A culture-sensitive symbol that separates seconds from fractions of a second. The invariant format uses a period (".") character.
                        ff     Optional fractional seconds, consisting of one to seven decimal digits.

                        The components of s must collectively specify a time interval that is greater than or equal to TimeSpan.MinValue and less than or equal to TimeSpan.MaxValue. 


                        FORMAT:
                        [ws][-]{ d | [d.]hh:mm[:ss[.ff]] }[ws]

                        If the s argument is not a day value only, it must include an hours and a minutes component; other components are optional.
                        If they are present, the values of each time component must fall within a specified range.
                        For example, the value of hh, the hours component, must be between 0 and 23.
                        Because of this, passing "23:00:00" to the Parse method returns a time interval of 23 hours.
                        On the other hand, passing "24:00:00" returns a time interval of 24 days.
                        Because "24" is outside the range of the hours component, it is interpreted as the days component.
                        
                        // d.hh:mm:ss.ms
                        //    foreach (+InvariantPattern, -InvariantPattern, +LocalizedPattern, -LocalizedPattern) try
                        //       1 number  => d
                        //       2 numbers => h:m
                        //       3 numbers => h:m:s     | d.h:m   | h:m:.f
                        //       4 numbers => h:m:s.f   | d.h:m:s | d.h:m:.f
                        //       5 numbers => d.h:m:s.f
                    */

                    Str ts = omni::string::util::trim(s);
                    if (ts.size() == 0) { return false; }
                    bool can_negate = (std::numeric_limits<TickType>::min() < 0);
                    bool is_neg = false;
                    if (ts[0] == omni::char_util::to_char_t<Char, char>('-')) {
                        if (can_negate) {
                            is_neg = true;
                            ts = ts.substr(1);
                        } else {
                            return false;
                        }
                    } else if (ts[0] == omni::char_util::to_char_t<Char, char>('+')) {
                        ts = ts.substr(1); // remove the + sign
                    }

                    TickType val;
                    if (omni::string::util::is_numeric(ts)) {
                        // 1 number: days, ranging from 0 to 10675199 (whole numbers only)
                        val = omni::string::util::to_type<TickType>(ts);
                        if (val < 0 || val > 10675199) { return false; }
                        val = _time_to_ticks(val, 0, 0, 0, 0);
                        result.m_ticks = (is_neg ? -val : val);
                        return true;
                    }

                    Char period = omni::char_util::to_char_t<Char, char>('.');
                    Str delim = omni::string::util::to_type<Str>(":");
                    Str pdel = omni::string::util::to_type<Str>(".");

                    if (ts.find(omni::char_util::to_char_t<Char, char>(':')) != Str::npos) {
                        TickType days = 0, hrs = 0, mins = 0, sec = 0, ms = 0;
                        Str msstr;
                        omni_sequence_t<Str> vals = omni::string::util::split(ts, delim);
                        omni_sequence_t<Str> pvals;
                        switch (vals.size()) {
                            case 2: {
                                // d.h:m | h:m
                                if (!omni::string::util::is_numeric(vals[0], true) ||
                                    !omni::string::util::is_numeric(vals[1]))
                                { return false; }
                                mins = omni::string::util::to_type<TickType>(vals[1]);
                                if (vals[0].find(period) != Str::npos) {
                                    pvals = omni::string::util::split(vals[0], pdel);
                                    days = omni::string::util::to_type<TickType>(pvals[0]);
                                    hrs = omni::string::util::to_type<TickType>(pvals[1]);
                                } else {
                                    hrs = omni::string::util::to_type<TickType>(vals[0]);
                                }
                            } break;
                            case 3: {
                                // h:m:s | h:m:.f | h:m:s.f | d.h:m:s | d.h:m:.f | d.h:m:s.f
                                if (!omni::string::util::is_numeric(vals[0], true) ||
                                    !omni::string::util::is_numeric(vals[1]) ||
                                    !omni::string::util::is_numeric(vals[2], true))
                                { return false; }
                                mins = omni::string::util::to_type<TickType>(vals[1]);
                                if (vals[0].find(period) != Str::npos) {
                                    // d.h: m:s | d.h: m:.f | d.h: m:s.f
                                    pvals = omni::string::util::split(vals[0], pdel);
                                    days = omni::string::util::to_type<TickType>(pvals[0]);
                                    hrs = omni::string::util::to_type<TickType>(pvals[1]);
                                } else {
                                    // h: m:s | h: m:.f | h: m:s.f
                                    hrs = omni::string::util::to_type<TickType>(vals[0]);
                                }
                                if (vals[2].find(period) != Str::npos) {
                                    // h:m: .f | d.h:m: .f | h:m: s.f | d.h:m: s.f
                                    pvals = omni::string::util::split(vals[2], pdel);
                                    if (pvals.size() > 1) {
                                        if (!pvals[0].empty()) { sec = omni::string::util::to_type<TickType>(pvals[0]); }
                                        msstr = pvals[1];
                                    } else {
                                        msstr = pvals[0];
                                    }
                                } else {
                                    // h:m: s | d.h:m: s
                                    sec = omni::string::util::to_type<TickType>(vals[2]);
                                }
                            } break;
                        }
                        // hh     Hours, ranging from 0 to 23.
                        // mm     Minutes, ranging from 0 to 59.
                        // ss     Optional seconds, ranging from 0 to 59.
                        // ff     Optional fractional seconds, consisting of one to seven decimal digits.
                        if ((hrs < 0 || hrs > 23) || (mins < 0 || mins > 59) || (sec < 0 || sec > 59))
                        { return false; }

                        if (!msstr.empty()) {
                            ms = omni::string::util::to_type<double>(omni::string::util::to_type<Str>("0.") + msstr) * 1000;
                        }
                        val = _time_to_ticks(days, hrs, mins, sec, ms);
                        result.m_ticks = (is_neg ? -val : val);
                        return true;
                    }
                    return false;
                }
        };
        
        typedef omni::chrono::span<int64_t> span_t;
        typedef omni::chrono::span<uint64_t> unsigned_span_t;
        typedef unsigned_span_t uspan_t;
    } // namespace chrono
} // namespace omni

namespace std {
    template < typename TickType >
    inline void swap(omni::chrono::span<TickType>& o1, omni::chrono::span<TickType>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_SPAN_HPP
