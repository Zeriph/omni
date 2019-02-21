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
#include <ctime>
#include <omni/defs/class_macros.hpp>
#include <omni/ostream.hpp>

#if defined(OMNI_SAFE_SPAN)
    #include <omni/sync/scoped_lock.hpp>
    #define OMNI_SAFE_SPANMTX_FW m_mtx(),
    #define OMNI_SPAN_ALOCK_FW    omni::sync::scoped_lock<omni::sync::basic_lock> mlock(&this->m_mtx);
    #define OMNI_SPAN_MLOCK_FW    this->m_mtx.lock();
    #define OMNI_SPAN_ULOCK_FW    this->m_mtx.unlock();
#else
    #define OMNI_SAFE_SPANMTX_FW
    #define OMNI_SPAN_ALOCK_FW
    #define OMNI_SPAN_MLOCK_FW
    #define OMNI_SPAN_ULOCK_FW
#endif

namespace omni {
    namespace chrono {        
        /** Undocumented: not finished */
        template < typename TickType >
        class span
        {
            public:
                typedef TickType span_t;

                span() :
                    OMNI_CTOR_FW(omni::chrono::span)
                    OMNI_SAFE_SPANMTX_FW
                    m_ticks(0)
                {
                    OMNI_D5_FW("created");
                }

                span(const span< TickType >& cp) :
                    OMNI_CPCTOR_FW(cp)
                    OMNI_SAFE_SPANMTX_FW
                    m_ticks(cp.m_ticks)
                {
                    OMNI_D5_FW("copied");
                }

                //implicit
                span(span_t ticks) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    OMNI_SAFE_SPANMTX_FW
                    m_ticks(ticks)
                {
                    OMNI_D5_FW("created");
                }

                span(span_t hours, span_t minutes, span_t seconds) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    OMNI_SAFE_SPANMTX_FW
                    m_ticks(0)
                {
                    this->m_ticks = _time_to_ticks(hours, minutes, seconds);
                    OMNI_D5_FW("created");
                }

                span(span_t days, span_t hours, span_t minutes, span_t seconds) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    OMNI_SAFE_SPANMTX_FW
                    m_ticks(0)
                {
                    this->m_ticks = _time_to_ticks(days, hours, minutes, seconds, 0);
                    OMNI_D5_FW("created");
                }

                span(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds) :
                    OMNI_CTOR_FW(omni::chrono::span)
                    OMNI_SAFE_SPANMTX_FW
                    m_ticks(0)
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

                // total ticks
                span_t ticks() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks;
                }

                // days portion
                span_t days() const
                {
                    return static_cast<span_t>(static_cast<double>(this->ticks()) / omni::chrono::TICKS_PER_DAY);
                }

                // hours component
                span_t hours() const
                {
                    return static_cast<span_t>(static_cast<double>(this->ticks()) / omni::chrono::TICKS_PER_DAY) % 24;
                }

                // milliseconds component
                span_t milliseconds() const
                {
                    return static_cast<span_t>(static_cast<double>(this->ticks()) / omni::chrono::TICKS_PER_MILLISECOND) % 1000;
                }

                // minutes component
                span_t minutes() const
                {
                    return static_cast<span_t>(static_cast<double>(this->ticks()) / omni::chrono::TICKS_PER_MINUTE) % 60;
                }

                // seconds component
                span_t seconds() const
                {
                    return static_cast<span_t>(static_cast<double>(this->ticks()) / omni::chrono::TICKS_PER_SECOND) % 60;
                }

                // days as whole and fractional
                double total_days() const
                {
                    return static_cast<double>(this->ticks()) * omni::chrono::DAYS_PER_TICK;
                }

                // hours as whole and fractional
                double total_hours() const
                {
                    return static_cast<double>(this->ticks()) * omni::chrono::HOURS_PER_TICK;
                }

                double total_milliseconds() const
                {
                    double temp = static_cast<double>(this->ticks()) * omni::chrono::MILLISECONDS_PER_TICK;
                    if (temp > max_milliseconds()) {
                        return static_cast<double>(max_milliseconds());
                    }
                    if (temp < min_milliseconds()) {
                        return static_cast<double>(min_milliseconds());
                    }
                    return temp;
                }

                double total_minutes() const
                {
                    return static_cast<double>(this->ticks()) * omni::chrono::MINUTES_PER_TICK;
                }

                double total_seconds() const
                {
                    return static_cast<double>(this->ticks()) * omni::chrono::SECONDS_PER_TICK;
                }

                span< TickType >& add(const span< TickType >& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks += this->m_ticks;
                    } else {
                        this->m_ticks += other.ticks();
                    }
                    return *this;
                }

                span< TickType >& add(TickType ticks)
                {
                    OMNI_SPAN_MLOCK_FW
                    this->m_ticks += ticks;
                    OMNI_SPAN_ULOCK_FW
                    return *this;
                }
                
                uint64_t generate_hash() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return this->m_ticks ^ (this->_ticks >> 32);
                }
                
                span< TickType >& subtract(const span< TickType >& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks -= this->m_ticks;
                    } else {
                        this->m_ticks -= other.ticks();
                    }
                    return *this;
                }

                span< TickType >& subtract(TickType ticks)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks -= ticks;
                    return *this;
                }

                span< TickType > duration() const // TODO: make note signedness
                {
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(this->m_ticks >= 0 ? this->m_ticks : -this->m_ticks);
                }

                span< TickType > negate() const
                {
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(-this->m_ticks);
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

                span< TickType >& operator=(const span< TickType >& other)
                {
                    if (this != &other) {
                        OMNI_SPAN_ALOCK_FW
                        this->m_ticks = other.ticks();
                    }
                    return *this;
                }

                span< TickType >& operator=(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks = val;
                    return *this;
                }

                span< TickType > operator-(const span< TickType >& other)
                {
                    if (this == &other) {
                        OMNI_SPAN_ALOCK_FW
                        return span< TickType >(this->m_ticks - this->m_ticks);
                    }
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(this->m_ticks - other.ticks());
                }

                span< TickType > operator-(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(this->m_ticks - val);
                }

                span< TickType > operator+(const span< TickType >& other)
                {
                    if (this == &other) {
                        OMNI_SPAN_ALOCK_FW
                        return span< TickType >(this->m_ticks + this->m_ticks);
                    }
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(this->m_ticks + other.ticks());
                }

                span< TickType > operator+(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(this->m_ticks + val);
                }

                span< TickType >& operator-=(const span< TickType >& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks -= this->m_ticks;
                    } else {
                        this->m_ticks -= other.ticks();
                    }
                    return *this;
                }

                span< TickType >& operator-=(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks -= val;
                    return *this;
                }

                span< TickType >& operator+=(const span< TickType >& other)
                {
                    OMNI_SPAN_ALOCK_FW
                    if (this == &other) {
                        this->m_ticks += this->m_ticks;
                    } else {
                        this->m_ticks += other.ticks();
                    }
                    return *this;
                }

                span< TickType >& operator+=(span_t val)
                {
                    OMNI_SPAN_ALOCK_FW
                    this->m_ticks += val;
                    return *this;
                }

                span< TickType > operator-()
                {
                    OMNI_SPAN_ALOCK_FW
                    return span< TickType >(-this->m_ticks);
                }

                span< TickType >& operator+()
                {
                    return *this;
                }

                bool operator==(const span< TickType >& other) const
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

                bool operator!=(const span< TickType >& other) const
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

                bool operator<(const span< TickType >& other) const
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

                bool operator>(const span< TickType >& other) const
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

                bool operator<=(const span< TickType >& other) const
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

                bool operator>=(const span< TickType >& other) const
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

                OMNI_MEMBERS_FW(omni::chrono::span< TickType >) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::chrono::span< TickType >)

                static span< TickType > parse(const std::string& s)
                {
                    span< TickType > ret;
                    if (!omni::chrono::span<TickType>::try_parse(s, ret)) {
                        OMNI_ERR_RETV_FW("parse error", omni::exceptions::invalid_parse(), ret)
                    }
                    return ret;
                }

                static bool try_parse(const std::string& s, span< TickType >& result)
                {
                    // d.hh:mm:ss.ms
                    //    foreach (+InvariantPattern, -InvariantPattern, +LocalizedPattern, -LocalizedPattern) try
                    //       1 number  => d
                    //       2 numbers => h:m
                    //       3 numbers => h:m:s     | d.h:m   | h:m:.f
                    //       4 numbers => h:m:s.f   | d.h:m:s | d.h:m:.f
                    //       5 numbers => d.h:m:s.f

                    return false;
                }

                static inline span< TickType > from_time(span_t hours, span_t minutes, span_t seconds)
                {
                    return span< TickType >(hours, minutes, seconds);
                }

                static inline span< TickType > from_time(span_t days, span_t hours, span_t minutes, span_t seconds)
                {
                    return span< TickType >(days, hours, minutes, seconds);
                }

                static inline span< TickType > from_time(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds)
                {
                    return span< TickType >(days, hours, minutes, seconds, milliseconds);
                }

                static inline span< TickType > from_days(double value)
                {
                    return _interval(value, omni::chrono::MILLISECONDS_PER_DAY);
                }

                static inline span< TickType > from_hours(double value)
                {
                    return _interval(value, omni::chrono::MILLISECONDS_PER_HOUR);
                }

                static inline span< TickType > from_milliseconds(double value)
                {
                    return _interval(value, 1);
                }

                static inline span< TickType > from_minutes(double value)
                {
                    return _interval(value, omni::chrono::MILLISECONDS_PER_MINUTE);
                }

                static inline span< TickType > from_seconds(double value)
                {
                    return _interval(value, omni::chrono::MILLISECONDS_PER_SECOND);
                }

                static inline span< TickType > from_ticks(span_t value)
                {
                    return span< TickType >(value);
                }

                static inline span_t max_seconds()
                {
                    return std::numeric_limits<span_t>::max() / omni::chrono::TICKS_PER_SECOND;
                }
                
                static inline span_t min_seconds()
                {
                    return std::numeric_limits<span_t>::min() / omni::chrono::TICKS_PER_SECOND;
                }
                
                static inline span_t max_milliseconds()
                {
                    return std::numeric_limits<span_t>::max() / omni::chrono::TICKS_PER_MILLISECOND;
                }
                
                static inline span_t min_milliseconds()
                {
                    return std::numeric_limits<span_t>::min() / omni::chrono::TICKS_PER_MILLISECOND;
                }

                static inline span< TickType > max_value()
                {
                    return span< TickType >(std::numeric_limits<span_t>::max());
                }

                static inline span< TickType > min_value()
                {
                    return span< TickType >(std::numeric_limits<span_t>::min());
                }

                static inline span< TickType > zero()
                {
                    return span< TickType >(0);
                }
                
            private:
                span_t m_ticks; // 100-nanosecond units
                #if defined(OMNI_SAFE_SPAN) // TODO: FINISH THIS
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                template < typename StrStr >
                void _to_string_base(StrStr& ss) const
                {
                    span_t t = this->ticks();
                    span_t d = t / omni::chrono::TICKS_PER_DAY;
                    span_t h = static_cast<span_t>(static_cast<double>(t) / omni::chrono::TICKS_PER_DAY) % 24;
                    span_t m = static_cast<span_t>(static_cast<double>(t) / omni::chrono::TICKS_PER_MINUTE) % 60;
                    span_t s = static_cast<span_t>(static_cast<double>(t) / omni::chrono::TICKS_PER_SECOND) % 60;
                    span_t ms = static_cast<span_t>(static_cast<double>(t) / omni::chrono::TICKS_PER_MILLISECOND) % 1000;
                    // d.hh:mm:ss.ms
                    ss << d << ".";
                    if (h < 10) { ss << "0"; }
                    ss << h << ":";
                    if (m < 10) { ss << "0"; }
                    ss << m << ":";
                    if (s < 10) { ss << "0"; }
                    ss << s << "." << ms;
                }

                static span< TickType > _interval(double value, int32_t scale)
                {
                    if (value == value) { // NaN check
                        double tmp = value * scale;
                        double millis = tmp + ((value >= 0) ? 0.5 : -0.5);
                        if ((millis > max_milliseconds()) || (millis < min_milliseconds())) {
                            OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid span"), span< TickType >::zero())
                        }
                        return span< TickType >(static_cast<span_t>(millis) * omni::chrono::TICKS_PER_MILLISECOND);
                    }
                    OMNI_ERR_RETV_FW(OMNI_NAN_ERR_STR, omni::exceptions::nan_error("span cannot be NaN"), span< TickType >::zero())
                }

                static span_t _time_to_ticks(span_t days, span_t hours, span_t minutes, span_t seconds, span_t milliseconds)
                {
                    span_t tot = (((days * 3600 * 24) + (hours * 3600) + (minutes * 60) + seconds) * 1000) + milliseconds;
                    if (tot > max_milliseconds() || tot < min_milliseconds())
                        OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid span"), span< TickType >::zero())
                    return tot * omni::chrono::TICKS_PER_MILLISECOND;
                }

                static span_t _time_to_ticks(span_t hour, span_t minute, span_t second)
                {
                    // totalSeconds is bounded by 2^31 * 2^12 + 2^31 * 2^8 + 2^31,
                    // which is less than 2^44, meaning we won't overflow totalSeconds.
                    span_t tot = (hour * 3600) + (minute * 60) + second;
                    if (tot > max_seconds() || tot < min_seconds()) {
                        OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid span"), span< TickType >::zero())
                    }
                    return tot * omni::chrono::TICKS_PER_SECOND;
                }
        };

        // signed
        typedef omni::chrono::span<int64_t> timespan;
        // unsigned
        typedef omni::chrono::span<uint64_t> unsigned_timespan;
    } // namespace chrono
} // namespace omni

#endif // OMNI_SPAN_HPP
