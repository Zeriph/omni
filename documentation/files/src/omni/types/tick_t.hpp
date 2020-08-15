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
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES);
 * LOSS OF USE, DATA, OR PROFITS); OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(OMNI_TICK_T_HPP)
#define OMNI_TICK_T_HPP 1
#include <omni/defs/tick_def.hpp>

namespace omni {
    namespace chrono {    
        typedef OMNI_CLOCK_TICK_T tick_t;
        typedef OMNI_CLOCK_FREQ_T freq_t;

        inline int64_t MAX_TICKS() { return std::numeric_limits<int64_t>::max(); }
        inline int64_t MIN_TICKS() { return std::numeric_limits<int64_t>::min(); }

        OMNI_CONSTEXT_FW const double  TICKS_PER_NANOSECOND OMNI_EXT_ASSN_FW(0.01);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_MICROSECOND OMNI_EXT_ASSN_FW(10);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_MILLISECOND OMNI_EXT_ASSN_FW(10000);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_TENTH_SECOND OMNI_EXT_ASSN_FW(1000000); // TICKS_PER_MILLISECOND * 100);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_SECOND OMNI_EXT_ASSN_FW(10000000);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_MINUTE OMNI_EXT_ASSN_FW(600000000);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_HOUR OMNI_EXT_ASSN_FW(36000000000);
        OMNI_CONSTEXT_FW const int64_t TICKS_PER_DAY OMNI_EXT_ASSN_FW(864000000000);

        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_MICROSECOND OMNI_EXT_ASSN_FW(1000);
        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_MILLISECOND OMNI_EXT_ASSN_FW(1000000);
        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_SECOND OMNI_EXT_ASSN_FW(1000000000);
        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_MINUTE OMNI_EXT_ASSN_FW(60000000000);
        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_HOUR OMNI_EXT_ASSN_FW(3600000000000);
        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_DAY OMNI_EXT_ASSN_FW(86400000000000);
        
        OMNI_CONSTEXT_FW const double  MICROSECONDS_PER_NANOSECOND OMNI_EXT_ASSN_FW(0.001);
        OMNI_CONSTEXT_FW const int64_t MICROSECONDS_PER_MILLISECOND OMNI_EXT_ASSN_FW(1000);
        OMNI_CONSTEXT_FW const int64_t MICROSECONDS_PER_SECOND OMNI_EXT_ASSN_FW(1000000);
        OMNI_CONSTEXT_FW const int64_t MICROSECONDS_PER_MINUTE OMNI_EXT_ASSN_FW(60000000);
        OMNI_CONSTEXT_FW const int64_t MICROSECONDS_PER_HOUR OMNI_EXT_ASSN_FW(3600000000);
        OMNI_CONSTEXT_FW const int64_t MICROSECONDS_PER_DAY OMNI_EXT_ASSN_FW(86400000000);

        OMNI_CONSTEXT_FW const double  MILLISECONDS_PER_NANOSECOND OMNI_EXT_ASSN_FW(0.0001);
        OMNI_CONSTEXT_FW const double  MILLISECONDS_PER_MICROSECOND OMNI_EXT_ASSN_FW(0.001);
        OMNI_CONSTEXT_FW const int64_t MILLISECONDS_PER_SECOND OMNI_EXT_ASSN_FW(1000);
        OMNI_CONSTEXT_FW const int64_t MILLISECONDS_PER_MINUTE OMNI_EXT_ASSN_FW(60000);
        OMNI_CONSTEXT_FW const int64_t MILLISECONDS_PER_HOUR OMNI_EXT_ASSN_FW(3600000);
        OMNI_CONSTEXT_FW const int64_t MILLISECONDS_PER_DAY OMNI_EXT_ASSN_FW(86400000);

        OMNI_CONSTEXT_FW const double  SECONDS_PER_NANOSECOND OMNI_EXT_ASSN_FW(0.000000001);
        OMNI_CONSTEXT_FW const double  SECONDS_PER_MICROSECOND OMNI_EXT_ASSN_FW(0.000001);
        OMNI_CONSTEXT_FW const double  SECONDS_PER_MILLISECOND OMNI_EXT_ASSN_FW(0.001);
        OMNI_CONSTEXT_FW const int64_t SECONDS_PER_MINUTE OMNI_EXT_ASSN_FW(60);
        OMNI_CONSTEXT_FW const int64_t SECONDS_PER_HOUR OMNI_EXT_ASSN_FW(3600);
        OMNI_CONSTEXT_FW const int64_t SECONDS_PER_DAY OMNI_EXT_ASSN_FW(86400);

        OMNI_CONSTEXT_FW const double  MINUTES_PER_NANOSECOND OMNI_EXT_ASSN_FW(0.000000000016667);
        OMNI_CONSTEXT_FW const double  MINUTES_PER_MICROSECOND OMNI_EXT_ASSN_FW(0.000000016667);
        OMNI_CONSTEXT_FW const double  MINUTES_PER_MILLISECOND OMNI_EXT_ASSN_FW(0.000016667);
        OMNI_CONSTEXT_FW const double  MINUTES_PER_SECOND OMNI_EXT_ASSN_FW(0.016667);
        OMNI_CONSTEXT_FW const int64_t MINUTES_PER_HOUR OMNI_EXT_ASSN_FW(60);
        OMNI_CONSTEXT_FW const int64_t MINUTES_PER_DAY OMNI_EXT_ASSN_FW(1440);

        OMNI_CONSTEXT_FW const int64_t NANOSECONDS_PER_TICK OMNI_EXT_ASSN_FW(100);
        OMNI_CONSTEXT_FW const double  MICROSECONDS_PER_TICK OMNI_EXT_ASSN_FW(0.1);
        OMNI_CONSTEXT_FW const double  MILLISECONDS_PER_TICK OMNI_EXT_ASSN_FW(0.0001);
        OMNI_CONSTEXT_FW const double  SECONDS_PER_TICK OMNI_EXT_ASSN_FW(0.0000001);
        OMNI_CONSTEXT_FW const double  MINUTES_PER_TICK OMNI_EXT_ASSN_FW(0.000000001666666666667);
        OMNI_CONSTEXT_FW const double  HOURS_PER_TICK OMNI_EXT_ASSN_FW(0.000000000027777777778);
        OMNI_CONSTEXT_FW const double  DAYS_PER_TICK OMNI_EXT_ASSN_FW(0.000000000001157407407);
    }
}

#endif // OMNI_TICK_T_HPP