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
#if !defined(OMNI_WIN_DEF_HPP)
#define OMNI_WIN_DEF_HPP 1

#if defined(OMNI_OS_WIN)
    #if !defined(_WIN32_WINNT)
        #if !defined(OMNI_OS_CYGWIN) && !defined(OMNI_OS_MINGW)
            #include <SDKDDKVer.h>
        #endif
        #if !defined(_WIN32_WINNT)
            // _WIN32_WINNT_NT4 = 0x400
            #define _WIN32_WINNT 0x0400 // for minimum WinAPI compilation
        #endif
    #endif
    #if (_WIN32_WINNT >= 0x0602)
        // Windows 8 API check (certain headers have changed)
        #define OMNI_OS_WIN8
    #endif
    #if !defined(OMNI_NO_WIN_LEAN)
        #if !defined(WIN32_LEAN_AND_MEAN)
            #define WIN32_LEAN_AND_MEAN // trim any extra headers not specifically needed
        #endif
        #if !defined(STRICT)
            #define STRICT // do not imply int types for handles
        #endif
        #if !defined(NOMINMAX)
            #define NOMINMAX // do not conflict with std::min/std::max
        #endif
    #endif
    #include <winsock2.h>
    #include <winsock.h>
    #include <windows.h>
    #if defined(OMNI_UNICODE)
        // macro to determine if platform is windows unicode
        #define OMNI_WINCODE
    #endif
    #if !defined(OMNI_SIGCALL)
        #define OMNI_SIGCALL __cdecl // for signal
    #endif
    #if !defined(OMNI_NO_WIN_API)
        /*DEV_NOTE: if on Win32 and you wish to compile against the
        Win CRT (Windows C Run Time libraries), pass the OMNI_NO_WIN_API
        flag to your compiler, and the library will not use any WinAPI
        calls where feasible; threading calls, for instance, need CloseHandle
        but if OMNI_NO_WIN_API is set, _beginthreadex is called instead of
        CreateThread */
        #if !defined(OMNI_WIN_API)
            #define OMNI_WIN_API
        #endif
    #endif
    /* DEV_NOTE: MSVC emits warning 4351 about the dimensional class having it is array value
    initialized in the member init list, e.g. `dimensional() : m_vals() {}`. This is considered
    "new" behaviour by MSVC but is perfectly fine behaviour per the C++ standard, this 0-init is
    the values in the array (as if memset were called). This is the behaviour we want and since
    we are targeting newer C++ and above, this is a non-issue. Additionally, testing this behaviour
    against MSVC 2008 and above (and inspecting the asm) shows we get the results we want. */
    #if !defined(OMNI_WIN_NO_PRAGMA_DISABLE_4351)
        #pragma warning (disable:4351)
    #endif
#endif

// macro error checks
#if defined(OMNI_WIN_API) && defined(OMNI_NO_WIN_API)
    #error "Cannot define OMNI_WIN_API and OMNI_NO_WIN_API"
#endif
#if defined(OMNI_WIN_API) && !defined(OMNI_OS_WIN)
    #error "Cannot define OMNI_WIN_API on non Windows platform, ensure OMNI_OS_WIN has been defined properly"
#endif
#if defined(OMNI_OS_WIN) && defined(OMNI_THREAD_STDCALL) && defined(OMNI_THREAD_FASTCALL)
    #error "Cannot define both OMNI_THREAD_STDCALL and OMNI_THREAD_FASTCALL"
#endif
#if defined(OMNI_WIN_USE_EVENT_CONDITIONAL) && !defined(OMNI_OS_WIN)
    #error "Cannot define OMNI_WIN_USE_EVENT_CONDITIONAL on a non Win OS"
#endif
#if !defined(OMNI_WIN_USE_EVENT_CONDITIONAL) && (defined(OMNI_OS_WIN) && !defined(OMNI_OS_WIN8))
    #error "_WIN32_WINNT < 0x0602, Omni cannot utilize CONDITION_VARIABLE, must specify OMNI_WIN_USE_EVENT_CONDITIONAL"
#endif

#endif // OMNI_WIN_DEF_HPP
