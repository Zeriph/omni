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
#if !defined(OMNI_TICK_T_HPP)
#define OMNI_TICK_T_HPP 1
#include <omni/defs/global.hpp>

#if !defined(OMNI_OS_WIN)
    #include <cstring> // memset
#endif

#if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
    #if !defined(OMNI_WIN_MONO_TICK_QPC) && !defined(OMNI_WIN_MONO_TICK_COUNT) && !defined(OMNI_WIN_MONO_TICK_COUNT64)
        #define OMNI_WIN_MONO_TICK_QPC
    #endif
    #if defined(OMNI_WIN_MONO_TICK_QPC)
        #define OMNI_CLOCK_TICK_T LARGE_INTEGER
    #elif defined(OMNI_WIN_MONO_TICK_COUNT)
        #define OMNI_CLOCK_TICK_T DWORD
    #elif defined(OMNI_WIN_MONO_TICK_COUNT64)
        #define OMNI_CLOCK_TICK_T ULONGLONG
    #endif
#elif defined(OMNI_OS_APPLE)
    #include <unistd.h>
    #include <sys/time.h>
    #include <mach/mach_time.h> // mach_time func's
    #define OMNI_CLOCK_TICK_T uint64_t
    #define OMNI_CLOCK_FREQ_T mach_timebase_info_data_t
#else
    // DEV_NOTE: some systems might need -lrt
    #include <ctime>
    // DEV_NOTE: csignal contains a reference to CLOCK_MONOTONIC
    #include <csignal>
    #if defined(OMNI_OS_WIN)
        #define OMNI_CLOCK_TICK_T clock_t
    #else
        // non Win/OSX use clock_gettime for tick call
        #define OMNI_CLOCK_TICK_T struct timespec
        #if !defined(CLOCK_MONOTONIC)
            #error CLOCK_MONOTONIC is not defined
        #endif
    #endif
    /* DEV_NOTE: some systems (like QNX) only take CLOCK_REALTIME for clock_getres, but will return correct
    values for clock_gettime with CLOCK_MONOTONIC, use OMNI_CLOCK_GETRES_REALTIME to change this behaviour */
    #if defined(OMNI_CLOCK_GETRES_REALTIME)
        #define OMNI_CLOCK_GETRES_CID_FW CLOCK_REALTIME
    #else
        #define OMNI_CLOCK_GETRES_CID_FW CLOCK_MONOTONIC
    #endif
#endif
#if !defined(OMNI_CLOCK_FREQ_T)
    #define OMNI_CLOCK_FREQ_T OMNI_CLOCK_TICK_T
#endif

// TODO: https://stackoverflow.com/questions/50245373/how-to-check-if-the-system-supports-monotonic-clock

namespace omni {
    namespace chrono {    
        typedef OMNI_CLOCK_TICK_T tick_t;
        typedef OMNI_CLOCK_FREQ_T freq_t;

        const double  TICKS_PER_NANOSECOND = 0.01;
        const int64_t TICKS_PER_MICROSECOND = 10;
        const int64_t TICKS_PER_MILLISECOND = 10000;
        const int64_t TICKS_PER_TENTH_SECOND = 1000000; // TICKS_PER_MILLISECOND * 100;
        const int64_t TICKS_PER_SECOND = 10000000;
        const int64_t TICKS_PER_MINUTE = 600000000;
        const int64_t TICKS_PER_HOUR = 36000000000;
        const int64_t TICKS_PER_DAY = 864000000000;

        const int64_t NANOSECONDS_PER_MICROSECOND = 1000;
        const int64_t NANOSECONDS_PER_MILLISECOND = 1000000;
        const int64_t NANOSECONDS_PER_SECOND = 1000000000;
        const int64_t NANOSECONDS_PER_MINUTE = 60000000000;
        const int64_t NANOSECONDS_PER_HOUR = 3600000000000;
        const int64_t NANOSECONDS_PER_DAY = 86400000000000;
        
        const double  MICROSECONDS_PER_NANOSECOND = 0.001;
        const int64_t MICROSECONDS_PER_MILLISECOND = 1000;
        const int64_t MICROSECONDS_PER_SECOND = 1000000;
        const int64_t MICROSECONDS_PER_MINUTE = 60000000;
        const int64_t MICROSECONDS_PER_HOUR = 3600000000;
        const int64_t MICROSECONDS_PER_DAY = 86400000000;

        const double  MILLISECONDS_PER_NANOSECOND = 0.0001;
        const double  MILLISECONDS_PER_MICROSECOND = 0.001;
        const int64_t MILLISECONDS_PER_SECOND = 1000;
        const int64_t MILLISECONDS_PER_MINUTE = 60000;
        const int64_t MILLISECONDS_PER_HOUR = 3600000;
        const int64_t MILLISECONDS_PER_DAY = 86400000;

        const double  SECONDS_PER_NANOSECOND = 0.000000001;
        const double  SECONDS_PER_MICROSECOND = 0.000001;
        const double  SECONDS_PER_MILLISECOND = 0.001;
        const int64_t SECONDS_PER_MINUTE = 60;
        const int64_t SECONDS_PER_HOUR = 3600;
        const int64_t SECONDS_PER_DAY = 86400;

        const double  MINUTES_PER_NANOSECOND = 0.000000000016667;
        const double  MINUTES_PER_MICROSECOND = 0.000000016667;
        const double  MINUTES_PER_MILLISECOND = 0.000016667;
        const double  MINUTES_PER_SECOND = 0.016667;
        const int64_t MINUTES_PER_HOUR = 60;
        const int64_t MINUTES_PER_DAY = 1440;

        const int64_t NANOSECONDS_PER_TICK = 100;
        const double  MICROSECONDS_PER_TICK = 0.1;
        const double  MILLISECONDS_PER_TICK = 0.0001;
        const double  SECONDS_PER_TICK = 0.0000001;
        const double  MINUTES_PER_TICK = 0.000000001666666666667;
        const double  HOURS_PER_TICK = 0.000000000027777777778;
        const double  DAYS_PER_TICK = 0.000000000001157407407;
    }
}

#endif // OMNI_TICK_T_HPP
