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
#if !defined(OMNI_GLOBALDEFS_HPP)
#define OMNI_GLOBALDEFS_HPP 1
#include <omni/defs/os.hpp>
#include <omni/defs/arch.hpp>
#include <omni/defs/cancel_check_def.hpp>
#include <omni/defs/helper.hpp>
#include <omni/defs/omni_ver.hpp>
#include <cstddef>
#include <limits>
#include <utility>
#include <iomanip>

#if defined(OMNI_USE_MATH_DEFS) && !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES
#endif
#if defined(_USE_MATH_DEFINES)
    #define OMNI_USE_MATH_DEFINES_FW 1
#else
    #define _USE_MATH_DEFINES
    #define OMNI_USE_MATH_DEFINES_FW 2
#endif
#include <math.h> // for C99 isnan
#include <float.h>
#include <cmath>
#include <cfloat>
#if OMNI_USE_MATH_DEFINES_FW == 2
    #undef _USE_MATH_DEFINES
#endif

#if !defined(OMNI_NAN)
    #if defined(NAN)
        #define OMNI_NAN NAN
    #else
        #define OMNI_NAN std::numeric_limits<double>::quiet_NaN()
    #endif
#endif

#if defined(OMNI_NO_CSTDINT)
    #include <stdint.h>
#else
    // DEV_NOTE: this causes compiler errors on some, and need to use stdint.h instead
    #include <cstdint>
#endif

#if defined(OMNI_NO_CSTDIO)
    #include <stdio.h>
#else
    #include <cstdio>
#endif

#if defined(__UNICODE__) || defined(UNICODE) || defined(_UNICODE) || defined(__UNICODE)
    #define OMNI_UNICODE
#endif

#if defined(OMNI_BUILD_UNSAFE)
    #define OMNI_NO_MUTEX_OWNER
    #define OMNI_NO_SAFE_LIBRARY
    #define OMNI_NO_THROW // DEV_NOTE: this is highly UN-recommended
#endif

// default auto-init chrono::tick
#if !defined(OMNI_CHRONO_AUTO_INIT_TICK)
    #define OMNI_CHRONO_AUTO_INIT_TICK
#endif
// default mutex owner
#if !defined(OMNI_MUTEX_OWNER)
    #define OMNI_MUTEX_OWNER
#endif
// default allow non-portable
#if !defined(OMNI_NON_PORTABLE)
    #define OMNI_NON_PORTABLE
#endif

// default of implicit constructors
#if defined(OMNI_USE_EXPLICIT)
    #define OMNI_EXPLICIT explicit
#endif

#if defined(OMNI_APPLE_OLD_API)
    #define OMNI_NO_OS_MACOS
#endif

#include <omni/defs/lite_def.hpp>
#include <omni/defs/cancel_check_def.hpp>
#include <omni/defs/safe_def.hpp>
#include <omni/defs/win_def.hpp>
#include <omni/defs/null_def.hpp>
#include <omni/defs/32bit_def.hpp>

#if !defined(OMNI_EXPLICIT)
    #define OMNI_EXPLICIT 
#endif

#define OMNI_FREE(v) delete v; v = OMNI_NULL
#define OMNI_FREE_ARR(v) delete[] v; v = OMNI_NULL

#if defined(OMNI_WIN_API)
    // For a list of error codes: http://msdn.microsoft.com/en-us/library/ms681381(VS.85).aspx
    #define OMNI_GLE ::GetLastError()
    #define OMNI_GLE_PRNT static_cast<long>(::GetLastError())
#else
    // For a list of error codes: see errno.h
    #include <cerrno>  // C++ defs, but some impls do not have errno defined here
    #include <errno.h> // so also include C defs ... (this happens a lot more than we would like)
    #define OMNI_GLE errno
    #define OMNI_GLE_PRNT errno
#endif

#if defined(OMNI_NO_EXTERN_CONSTS)
    #define OMNI_CONSTEXT_FW 
    #define OMNI_EXT_ASSN_FW(v) = (v)
#else
    #define OMNI_CONSTEXT_FW extern 
    #define OMNI_EXT_ASSN_FW(v)
#endif

#if defined(OMNI_NO_CLINK)
    #define OMNI_CLINKO_FW 
    #define OMNI_CLINKC_FW 
#else
    #define OMNI_CLINKO_FW extern "C" {
    #define OMNI_CLINKC_FW }
#endif

#if !defined(OMNI_CODE_PAGE)
    #if defined(OMNI_OS_WIN) || defined(CP_UTF8)
        #define OMNI_CODE_PAGE CP_UTF8
    #else
        #define OMNI_CODE_PAGE 0
    #endif
#endif

#if !defined(OMNI_BASE_LOCALE_CATEGORY)
    #define OMNI_BASE_LOCALE_CATEGORY LC_ALL
#endif
#if !defined(OMNI_BASE_LOCALE)
    #define OMNI_BASE_LOCALE ""
#endif

#if defined(OMNI_ENABLE_CXX) || defined(OMNI_ENABLE_NOEXCEPT)
    #define OMNI_DTOR_THROWS noexcept(false)
    #define OMNI_DTOR_NO_THROWS noexcept(true)
#else
    #define OMNI_DTOR_THROWS
    #define OMNI_DTOR_NO_THROWS throw()
#endif

// if debug is not defined, this will not get included
#include <omni/defs/debug.hpp>
// if OMNI_NO_THROW is defined (or OMNI_THROW is not defined) this will not get included
#include <omni/exception.hpp>

#define OMNI_EOL_RN "\r\n"
#define OMNI_EOL_R "\r"
#define OMNI_EOL_N "\n"

#if !defined(OMNI_NEW_LINE)
    #if defined(OMNI_OS_WIN)
        #define OMNI_NEW_LINE "\r\n"
        #define OMNI_WNEW_LINE L"\r\n"
        #define OMNI_PATH_SEPARATOR "\\"
        #define OMNI_WPATH_SEPARATOR L"\\"
        #define OMNI_PATH_ROOT "C:\\"
        #define OMNI_WPATH_ROOT L"C:\\"
    #else
        #if defined(OMNI_APLNL)
            #define OMNI_NEW_LINE "\r"
            #define OMNI_WNEW_LINE L"\r"
        #else
            #define OMNI_NEW_LINE "\n"
            #define OMNI_WNEW_LINE L"\n"
        #endif
        #define OMNI_PATH_SEPARATOR "/"
        #define OMNI_WPATH_SEPARATOR L"/"
        #define OMNI_PATH_ROOT "/"
        #define OMNI_WPATH_ROOT L"/"
    #endif
#endif

// DEV_NOTE: this is triple included to enclose the header and cancel all defines that need be
#include <omni/defs/cancel_check_def.hpp>

namespace omni {
    typedef void* unsafe_t;
}

/* DEV_NOTE: something that came across was a virtual thunk error, this happened when compiling the
library as a library using certain features (like omni::type_info or omni::object) and then compiling
the source linked against WITHOUT those features (especially on calls to virtually inherited items like
the omni::runnable & omni::runnable_thread). Just something to be aware of! */

#endif // OMNI_GLOBALDEFS_HPP
