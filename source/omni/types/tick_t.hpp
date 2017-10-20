/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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

namespace omni {
    namespace chrono {    
        typedef OMNI_CLOCK_TICK_T tick_t;
        typedef OMNI_CLOCK_FREQ_T freq_t;
    }
}

#endif // OMNI_TICK_T_HPP
