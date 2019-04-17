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
#include <omni/defs/helper.hpp>
#include <omni/defs/omni_ver.hpp>
#include <cstddef>

#if defined(_USE_MATH_DEFINES)
    #define OMNI_USE_MATH_DEFINES_FW 1
#else
    #define _USE_MATH_DEFINES
    #define OMNI_USE_MATH_DEFINES_FW 2
#endif
#include <cmath>
#if OMNI_USE_MATH_DEFINES_FW == 2
    #undef _USE_MATH_DEFINES
#endif

#if defined(OMNI_NO_CSTDINT)
    #include <stdint.h>
#else
    // DEV_NOTE: this causes compiler errors on some compilers complaining of 
    // C++11 support, so use uint_t types instead of std::uint_t types
    #include <cstdint>
#endif

#if defined(__UNICODE__) || defined(UNICODE) || defined(_UNICODE) || defined(__UNICODE)
    #define OMNI_UNICODE
#endif

#if defined(OMNI_BUILD_UNSAFE)
    #define OMNI_NO_MUTEX_OWNER
    #define OMNI_NO_SAFE_FRAMEWORK
    #define OMNI_NO_THROW
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

#include <omni/defs/lite_def.hpp>
#include <omni/defs/safe_def.hpp>
#include <omni/defs/cancel_check_def.hpp>
#include <omni/defs/win_def.hpp>
#include <omni/defs/null_def.hpp>

#if defined(OMNI_WIN_API)
    // For a list of error codes: http://msdn.microsoft.com/en-us/library/ms681381(VS.85).aspx
    #define OMNI_GLE ::GetLastError()
    #define OMNI_GLE_PRNT static_cast<long>(::GetLastError())
#else
    // For a list of error codes: see errno.h
    #include <cerrno>  // C++ def's, but some impl's don't have errno defined here
    #include <errno.h> // so also include C defs ... (this happens a lot more than we'd like)
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
    #define OMNI_CODE_PAGE CP_UTF8
#endif

#if defined(OMNI_ENABLE_CXX)
    // #define OMNI_CXX_THREAD_FW
    // #define OMNI_CXX_MUTEX_FW
#endif

// if debug isn't defined, this won't get included
#include <omni/defs/debug.hpp>
// if OMNI_NO_THROW is defined (or OMNI_THROW is not defined) this won't get included
#include <omni/exception.hpp>

#if !defined(OMNI_NEW_LINE)
    #if defined(OMNI_OS_WIN)
        #define OMNI_NEW_LINE "\r\n"
        #define OMNI_PATH_SEPARATOR "\\"
    #else
        #if defined(OMNI_APLNL)
            #define OMNI_NEW_LINE "\r"
            #define OMNI_PATH_SEPARATOR "/"
        #else
            #define OMNI_NEW_LINE "\n"
            #define OMNI_PATH_SEPARATOR "/"
        #endif
    #endif
#endif

/* DEV_NOTE: something that came across was a 'virtual thunk' error, this happened when compiling the
framework as a library using certain features (like omni::type_info or omni::object) and then compiling
the source linked against WITHOUT those features (especially on calls to virtually inherited items like
the omni::runnable & omni::runnable_thread). Just something to be aware of! */

#endif // OMNI_GLOBALDEFS_HPP
