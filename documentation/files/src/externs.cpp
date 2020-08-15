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
#if !defined(OMNI_NO_EXTERN_CONSTS)
    // DEV_NOTE: These values are to keep in line with the .NET framework
    #include <omni/types/date_t.hpp>
    const int64_t omni::chrono::DAYS_PER_YEAR = 365; // non-leap
    const int64_t omni::chrono::DAYS_PER_4_YEARS = 1461; // 365 * 4 + 1 leap day
    const int64_t omni::chrono::DAYS_PER_100_YEARS = 36524; // DAYS_PER_4_YEARS * 25 - 1
    const int64_t omni::chrono::DAYS_PER_400_YEARS = 146097; // DAYS_PER_100_YEARS * 4 + 1
    const int64_t omni::chrono::DAYS_TO_1601AD = 584388; // Number of days from 1/1/0001 to 12/31/1600 -> DAYS_PER_400_YEARS * 4
    const int64_t omni::chrono::DAYS_TO_EPOCH = 719527; // Number of days from 1/1/0001 to 12/31/1969 -> DAYS_TO_1601AD + (DAYS_PER_100_YEARS * 3) + (DAYS_PER_4_YEARS * 17) + (DAYS_PER_YEAR * 2)
    const int64_t omni::chrono::DAYS_TO_1899AD = 693593; // Number of days from 1/1/0001 to 12/30/1899 -> DAYS_PER_400_YEARS * 4 + DAYS_PER_100_YEARS * 3 - 367;
    const int64_t omni::chrono::DAYS_TO_10000AD = 3652059; // Number of days from 1/1/0001 to 12/31/9999 -> DAYS_PER_400_YEARS * 25 - 366
    const int64_t omni::chrono::TICKS_TO_10000AD = 3155378975999999999; // DAYS_TO_10000AD * TICKS_PER_DAY - 1;
    const int64_t omni::chrono::MILLISECONDS_TO_10000AD = 315537897600000; // DAYS_TO_10000AD * MILLISECONDS_PER_DAY;
    const int64_t omni::chrono::FILE_TIME_OFFSET = 504911232000000000; // DAYS_TO_1601AD * TICKS_PER_DAY;
    const int64_t omni::chrono::EPOCH_OFFSET = 621671328000000000; // DAYS_TO_EPOCH * TICKS_PER_DAY;
    const int64_t omni::chrono::DOUBLE_DATE_OFFSET = 599264352000000000; // DAYS_TO_1899AD * TICKS_PER_DAY;
    // The minimum OA date is 0100/01/01 (Note it is year 100).
    // The maximum OA date is 9999/12/31
    const int64_t omni::chrono::OA_DATE_MIN_AS_TICKS = 31241376000000000; // (DAYS_PER_100_YEARS - DAYS_PER_YEAR) * TICKS_PER_DAY;
    const double omni::chrono::OA_DATE_MIN_AS_DOUBLE = -657435.0; // All OA dates must be greater than (not >=) OA_DATE_MIN_AS_DOUBLE
    const double omni::chrono::OA_DATE_MAX_AS_DOUBLE = 2958466.0; // All OA dates must be less than (not <=) OA_DATE_MAX_AS_DOUBLE
    const int32_t omni::chrono::DAYS_TO_MONTH_365[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
    const int32_t omni::chrono::DAYS_TO_MONTH_366[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

    #include <omni/types/tick_t.hpp>
    const double  omni::chrono::TICKS_PER_NANOSECOND = 0.01;
    const int64_t omni::chrono::TICKS_PER_MICROSECOND = 10;
    const int64_t omni::chrono::TICKS_PER_MILLISECOND = 10000;
    const int64_t omni::chrono::TICKS_PER_TENTH_SECOND = 1000000; // TICKS_PER_MILLISECOND * 100;
    const int64_t omni::chrono::TICKS_PER_SECOND = 10000000;
    const int64_t omni::chrono::TICKS_PER_MINUTE = 600000000;
    const int64_t omni::chrono::TICKS_PER_HOUR = 36000000000;
    const int64_t omni::chrono::TICKS_PER_DAY = 864000000000;
    const int64_t omni::chrono::NANOSECONDS_PER_MICROSECOND = 1000;
    const int64_t omni::chrono::NANOSECONDS_PER_MILLISECOND = 1000000;
    const int64_t omni::chrono::NANOSECONDS_PER_SECOND = 1000000000;
    const int64_t omni::chrono::NANOSECONDS_PER_MINUTE = 60000000000;
    const int64_t omni::chrono::NANOSECONDS_PER_HOUR = 3600000000000;
    const int64_t omni::chrono::NANOSECONDS_PER_DAY = 86400000000000;
    const double  omni::chrono::MICROSECONDS_PER_NANOSECOND = 0.001;
    const int64_t omni::chrono::MICROSECONDS_PER_MILLISECOND = 1000;
    const int64_t omni::chrono::MICROSECONDS_PER_SECOND = 1000000;
    const int64_t omni::chrono::MICROSECONDS_PER_MINUTE = 60000000;
    const int64_t omni::chrono::MICROSECONDS_PER_HOUR = 3600000000;
    const int64_t omni::chrono::MICROSECONDS_PER_DAY = 86400000000;
    const double  omni::chrono::MILLISECONDS_PER_NANOSECOND = 0.0001;
    const double  omni::chrono::MILLISECONDS_PER_MICROSECOND = 0.001;
    const int64_t omni::chrono::MILLISECONDS_PER_SECOND = 1000;
    const int64_t omni::chrono::MILLISECONDS_PER_MINUTE = 60000;
    const int64_t omni::chrono::MILLISECONDS_PER_HOUR = 3600000;
    const int64_t omni::chrono::MILLISECONDS_PER_DAY = 86400000;
    const double  omni::chrono::SECONDS_PER_NANOSECOND = 0.000000001;
    const double  omni::chrono::SECONDS_PER_MICROSECOND = 0.000001;
    const double  omni::chrono::SECONDS_PER_MILLISECOND = 0.001;
    const int64_t omni::chrono::SECONDS_PER_MINUTE = 60;
    const int64_t omni::chrono::SECONDS_PER_HOUR = 3600;
    const int64_t omni::chrono::SECONDS_PER_DAY = 86400;
    const double  omni::chrono::MINUTES_PER_NANOSECOND = 0.000000000016667;
    const double  omni::chrono::MINUTES_PER_MICROSECOND = 0.000000016667;
    const double  omni::chrono::MINUTES_PER_MILLISECOND = 0.000016667;
    const double  omni::chrono::MINUTES_PER_SECOND = 0.016667;
    const int64_t omni::chrono::MINUTES_PER_HOUR = 60;
    const int64_t omni::chrono::MINUTES_PER_DAY = 1440;
    const int64_t omni::chrono::NANOSECONDS_PER_TICK = 100;
    const double  omni::chrono::MICROSECONDS_PER_TICK = 0.1;
    const double  omni::chrono::MILLISECONDS_PER_TICK = 0.0001;
    const double  omni::chrono::SECONDS_PER_TICK = 0.0000001;
    const double  omni::chrono::MINUTES_PER_TICK = 0.000000001666666666667;
    const double  omni::chrono::HOURS_PER_TICK = 0.000000000027777777778;
    const double  omni::chrono::DAYS_PER_TICK = 0.000000000001157407407;

    #include <omni/constants.hpp>
    const uint32_t omni::consts::size::binary::KB = OMNI_KIB_IVAL;
    const uint32_t omni::consts::size::binary::MB = OMNI_MIB_IVAL;
    const uint32_t omni::consts::size::binary::GB = OMNI_GIB_IVAL;
    const uint32_t omni::consts::size::decimal::KB = OMNI_KB_IVAL;
    const uint32_t omni::consts::size::decimal::MB = OMNI_MB_IVAL;
    const uint32_t omni::consts::size::decimal::GB = OMNI_GB_IVAL;
    
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
    const double omni::math::E = OMNI_E;
    const long double omni::math::E_L = OMNI_E_L;
    const float omni::math::E_F = OMNI_E_F;
    const double omni::math::PI = OMNI_PI;
    const long double omni::math::PI_L = OMNI_PI_L;
    const float omni::math::PI_F = OMNI_PI_F;
    const double omni::math::PI_180 = OMNI_PI_180;
    const long double omni::math::PI_L_180 = OMNI_PI_L_180;
    const float omni::math::PI_F_180 = OMNI_PI_F_180;

    #define OMNI_MATH_RAD_MAP_FW omni::math::
    //const double omni::math::RADS[] = { /* map of whole degree to rad */ };
    //const double omni::math::RADS_SIN[] = { /* map of sine(whole deg to rad) */ };
    //const double omni::math::RADS_COS[] = { /* map of cosine(whole deg to rad) */ };
    #include <omni/xx/math_radmap.hxx>
    #undef OMNI_MATH_RAD_MAP_FW
#endif
