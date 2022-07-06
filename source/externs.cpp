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
#include <omni/defs/global.hpp>

#include <omni/chrono/tick.hpp>
OMNI_CLOCK_FREQ_T omni::chrono::monotonic::m_freq;

#if defined(OMNI_THROW)
    #include <omni/types/thread_t.hpp>
    omni::action omni::sync::unhandled_thread_exception;
    omni::event1<void, const omni::exception&> omni::sync::user_thread_exception;
#endif

// default of having the constants be externally linked
#if !defined(OMNI_NO_EXTERN_CONSTS) && !defined(OMNI_NO_CONSTS)
    // DEV_NOTE: These values are to keep in line with the .NET framework
    #include <omni/types/date_t.hpp>
        const int64_t omni::chrono::DAYS_PER_100_YEARS = OMNI_DAYS_PER_100_YEARS; // DAYS_PER_4_YEARS * 25 - 1
        const int64_t omni::chrono::DAYS_PER_400_YEARS = OMNI_DAYS_PER_400_YEARS; // DAYS_PER_100_YEARS * 4 + 1
        const int64_t omni::chrono::DAYS_TO_1601AD = OMNI_DAYS_TO_1601AD; // Number of days from 1/1/0001 to 12/31/1600 -> DAYS_PER_400_YEARS * 4
        const int64_t omni::chrono::DAYS_TO_1899AD = OMNI_DAYS_TO_1899AD; // Number of days from 1/1/0001 to 12/30/1899 -> DAYS_PER_400_YEARS * 4 + DAYS_PER_100_YEARS * 3 - 367;
        const int64_t omni::chrono::DAYS_TO_10000AD = OMNI_DAYS_TO_10000AD; // Number of days from 1/1/0001 to 12/31/9999 -> DAYS_PER_400_YEARS * 25 - 366
        const int64_t omni::chrono::DAYS_TO_EPOCH = OMNI_DAYS_TO_EPOCH; // Number of days from 1/1/0001 to 12/31/1969 -> DAYS_TO_1601AD + (DAYS_PER_100_YEARS * 3) + (DAYS_PER_4_YEARS * 17) + (DAYS_PER_YEAR * 2)
        const int64_t omni::chrono::TICKS_TO_10000AD = OMNI_TICKS_TO_10000AD; // DAYS_TO_10000AD * TICKS_PER_DAY - 1;
        const int64_t omni::chrono::MILLISECONDS_TO_10000AD = OMNI_MILLISECONDS_TO_10000AD; // DAYS_TO_10000AD * MILLISECONDS_PER_DAY;
        const int64_t omni::chrono::FILE_TIME_OFFSET = OMNI_FILE_TIME_OFFSET; // DAYS_TO_1601AD * TICKS_PER_DAY;
        const int64_t omni::chrono::DOUBLE_DATE_OFFSET = OMNI_DOUBLE_DATE_OFFSET; // DAYS_TO_1899AD * TICKS_PER_DAY;
        const int64_t omni::chrono::EPOCH_OFFSET = OMNI_EPOCH_OFFSET; // DAYS_TO_EPOCH * TICKS_PER_DAY;
        // The minimum OA date is 0100/01/01 (Note it is year 100).
        // The maximum OA date is 9999/12/31
        const int64_t omni::chrono::OA_DATE_MIN_AS_TICKS = OMNI_OA_DATE_MIN_AS_TICKS; // (DAYS_PER_100_YEARS - DAYS_PER_YEAR) * TICKS_PER_DAY;
        const double omni::chrono::OA_DATE_MIN_AS_DOUBLE = OMNI_OA_DATE_MIN_AS_DOUBLE; // All OA dates must be greater than (not >=) OA_DATE_MIN_AS_DOUBLE
        const double omni::chrono::OA_DATE_MAX_AS_DOUBLE = OMNI_OA_DATE_MAX_AS_DOUBLE; // All OA dates must be less than (not <=) OA_DATE_MAX_AS_DOUBLE
        const int32_t omni::chrono::DAYS_TO_MONTH_365[] = OMNI_DAYS_TO_MONTH_365;
        const int32_t omni::chrono::DAYS_TO_MONTH_366[] = OMNI_DAYS_TO_MONTH_366;
        const double  omni::chrono::DAYS_PER_TROPICAL_YEAR = OMNI_DAYS_PER_TROPICAL_YEAR;
        const int64_t omni::chrono::DAYS_PER_YEAR = OMNI_DAYS_PER_YEAR; // non-leap
        const int64_t omni::chrono::DAYS_PER_LEAP_YEAR = OMNI_DAYS_PER_LEAP_YEAR;
        const int64_t omni::chrono::DAYS_PER_4_YEARS = OMNI_DAYS_PER_4_YEARS; // 365 * 4 + 1 leap day

    #include <omni/types/tick_t.hpp>
        const double  omni::chrono::TICKS_PER_NANOSECOND = OMNI_TICKS_PER_NANOSECOND;
        const int64_t omni::chrono::TICKS_PER_MICROSECOND = OMNI_TICKS_PER_MICROSECOND;
        const int64_t omni::chrono::TICKS_PER_MILLISECOND = OMNI_TICKS_PER_MILLISECOND;
        const int64_t omni::chrono::TICKS_PER_TENTH_SECOND = OMNI_TICKS_PER_TENTH_SECOND; // TICKS_PER_MILLISECOND * 100;
        const int64_t omni::chrono::TICKS_PER_SECOND = OMNI_TICKS_PER_SECOND;
        const int64_t omni::chrono::TICKS_PER_MINUTE = OMNI_TICKS_PER_MINUTE;
        const int64_t omni::chrono::TICKS_PER_HOUR = OMNI_TICKS_PER_HOUR;
        const int64_t omni::chrono::TICKS_PER_DAY = OMNI_TICKS_PER_DAY;
        const int64_t omni::chrono::NANOSECONDS_PER_MICROSECOND = OMNI_NANOSECONDS_PER_MICROSECOND;
        const int64_t omni::chrono::NANOSECONDS_PER_MILLISECOND = OMNI_NANOSECONDS_PER_MILLISECOND;
        const int64_t omni::chrono::NANOSECONDS_PER_SECOND = OMNI_NANOSECONDS_PER_SECOND;
        const int64_t omni::chrono::NANOSECONDS_PER_MINUTE = OMNI_NANOSECONDS_PER_MINUTE;
        const int64_t omni::chrono::NANOSECONDS_PER_HOUR = OMNI_NANOSECONDS_PER_HOUR;
        const int64_t omni::chrono::NANOSECONDS_PER_DAY = OMNI_NANOSECONDS_PER_DAY;
        const double  omni::chrono::MICROSECONDS_PER_NANOSECOND = OMNI_MICROSECONDS_PER_NANOSECOND;
        const int64_t omni::chrono::MICROSECONDS_PER_MILLISECOND = OMNI_MICROSECONDS_PER_MILLISECOND;
        const int64_t omni::chrono::MICROSECONDS_PER_SECOND = OMNI_MICROSECONDS_PER_SECOND;
        const int64_t omni::chrono::MICROSECONDS_PER_MINUTE = OMNI_MICROSECONDS_PER_MINUTE;
        const int64_t omni::chrono::MICROSECONDS_PER_HOUR = OMNI_MICROSECONDS_PER_HOUR;
        const int64_t omni::chrono::MICROSECONDS_PER_DAY = OMNI_MICROSECONDS_PER_DAY;
        const double  omni::chrono::MILLISECONDS_PER_NANOSECOND = OMNI_MILLISECONDS_PER_NANOSECOND;
        const double  omni::chrono::MILLISECONDS_PER_MICROSECOND = OMNI_MILLISECONDS_PER_MICROSECOND;
        const int64_t omni::chrono::MILLISECONDS_PER_SECOND = OMNI_MILLISECONDS_PER_SECOND;
        const int64_t omni::chrono::MILLISECONDS_PER_MINUTE = OMNI_MILLISECONDS_PER_MINUTE;
        const int64_t omni::chrono::MILLISECONDS_PER_HOUR = OMNI_MILLISECONDS_PER_HOUR;
        const int64_t omni::chrono::MILLISECONDS_PER_DAY = OMNI_MILLISECONDS_PER_DAY;
        const double  omni::chrono::SECONDS_PER_NANOSECOND = OMNI_SECONDS_PER_NANOSECOND;
        const double  omni::chrono::SECONDS_PER_MICROSECOND = OMNI_SECONDS_PER_MICROSECOND;
        const double  omni::chrono::SECONDS_PER_MILLISECOND = OMNI_SECONDS_PER_MILLISECOND;
        const int64_t omni::chrono::SECONDS_PER_MINUTE = OMNI_SECONDS_PER_MINUTE;
        const int64_t omni::chrono::SECONDS_PER_HOUR = OMNI_SECONDS_PER_HOUR;
        const int64_t omni::chrono::SECONDS_PER_DAY = OMNI_SECONDS_PER_DAY;
        const double  omni::chrono::MINUTES_PER_NANOSECOND = OMNI_MINUTES_PER_NANOSECOND;
        const double  omni::chrono::MINUTES_PER_MICROSECOND = OMNI_MINUTES_PER_MICROSECOND;
        const double  omni::chrono::MINUTES_PER_MILLISECOND = OMNI_MINUTES_PER_MILLISECOND;
        const double  omni::chrono::MINUTES_PER_SECOND = OMNI_MINUTES_PER_SECOND;
        const int64_t omni::chrono::MINUTES_PER_HOUR = OMNI_MINUTES_PER_HOUR;
        const int64_t omni::chrono::MINUTES_PER_DAY = OMNI_MINUTES_PER_DAY;
        const int64_t omni::chrono::NANOSECONDS_PER_TICK = OMNI_NANOSECONDS_PER_TICK;
        const double  omni::chrono::MICROSECONDS_PER_TICK = OMNI_MICROSECONDS_PER_TICK;
        const double  omni::chrono::MILLISECONDS_PER_TICK = OMNI_MILLISECONDS_PER_TICK;
        const double  omni::chrono::SECONDS_PER_TICK = OMNI_SECONDS_PER_TICK;
        const double  omni::chrono::MINUTES_PER_TICK = OMNI_MINUTES_PER_TICK;
        const double  omni::chrono::HOURS_PER_TICK = OMNI_HOURS_PER_TICK;
        const double  omni::chrono::DAYS_PER_TICK = OMNI_DAYS_PER_TICK;

    #include <omni/constants.hpp>
        const uint64_t omni::consts::size::binary::KB = OMNI_KIB_IVAL;
        const uint64_t omni::consts::size::binary::MB = OMNI_MIB_IVAL;
        const uint64_t omni::consts::size::binary::GB = OMNI_GIB_IVAL;
        const uint64_t omni::consts::size::binary::TB = OMNI_TIB_IVAL;
        const uint64_t omni::consts::size::binary::PB = OMNI_PIB_IVAL;
        const uint64_t omni::consts::size::binary::EB = OMNI_EIB_IVAL;

        const uint64_t omni::consts::size::decimal::KB = OMNI_KB_IVAL;
        const uint64_t omni::consts::size::decimal::MB = OMNI_MB_IVAL;
        const uint64_t omni::consts::size::decimal::GB = OMNI_GB_IVAL;
        const uint64_t omni::consts::size::decimal::TB = OMNI_TB_IVAL;
        const uint64_t omni::consts::size::decimal::PB = OMNI_PB_IVAL;
        const uint64_t omni::consts::size::decimal::EB = OMNI_EB_IVAL;
    
    // #include <omni/consts/cconsts.hpp>
        #define OMNI_CHAR_T_FW const char
        #define OMNI_STRW_FW(v) v
        #define OMNI_EXT_NS_FW omni::cconsts
        #include <omni/xx/ext_const.hxx>
        #undef OMNI_CHAR_T_FW
        #undef OMNI_STRW_FW
        #undef OMNI_EXT_NS_FW
        
        // #include <omni/consts/wconsts.hpp>
        #define OMNI_CHAR_T_FW const wchar_t
        #define OMNI_STRW_FW(v) OMNI_WSTR(v)
        #define OMNI_EXT_NS_FW omni::wconsts
        #include <omni/xx/ext_const.hxx>
        #undef OMNI_CHAR_T_FW
        #undef OMNI_STRW_FW
        #undef OMNI_EXT_NS_FW

    #include <omni/environment.hpp>
        const omni::char_t omni::environment::NEW_LINE[] = OMNI_STRW(OMNI_NEW_LINE);

    #include <omni/math.hpp>
        const double omni::math::compat::E = OMNI_MATH_COMPAT_E;
        const double omni::math::compat::PI = OMNI_MATH_COMPAT_PI;
        const double omni::math::compat::TAU = OMNI_MATH_COMPAT_TAU;

        const double omni::math::E = OMNI_E;
        const double omni::math::PI = OMNI_PI;
        const double omni::math::PI_180 = OMNI_PI_180;
        const double omni::math::TAU = OMNI_TAU;

        const long double omni::math::E_L = OMNI_E_L;
        const long double omni::math::PI_L = OMNI_PI_L;
        const long double omni::math::PI_L_180 = OMNI_PI_L_180;
        const long double omni::math::TAU_L = OMNI_TAU_L;
        
        const float omni::math::E_F = OMNI_E_F;
        const float omni::math::PI_F = OMNI_PI_F;
        const float omni::math::PI_F_180 = OMNI_PI_F_180;
        const float omni::math::TAU_F = OMNI_TAU_F;

        const double omni::math::RADS[] = OMNI_MATH_RADS;
        const double omni::math::RADS_SIN[] = OMNI_MATH_RADS_SIN;
        const double omni::math::RADS_COS[] = OMNI_MATH_RADS_COS;

    #include <omni/crypto/base64.hpp>
        const char *const omni::crypto::base64::CHARS[] = OMNI_CRYPTO_BASE64_CHARS;
#endif
