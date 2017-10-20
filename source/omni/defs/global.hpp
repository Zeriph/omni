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
#if !defined(OMNI_GLOBALDEFS_HPP)
#define OMNI_GLOBALDEFS_HPP 1
#include <omni/defs/os.hpp>
#include <omni/defs/helper.hpp>
#include <omni/defs/omni_ver.hpp>
#include <cstddef>

#if defined(OMNI_LITE)
    // TODO: update with any other 'lite' flags
    #define OMNI_NO_OBJECT_NAME
    #define OMNI_NO_DISPOSE_EVENT
    #define OMNI_NO_MUTEX_OWNER
    #define OMNI_NO_TYPE_INFO
    #define OMNI_NO_SAFE_APPLICATION
    #define OMNI_NO_SAFE_DELEGATES
    #define OMNI_NO_SAFE_EVENTS
    #define OMNI_NO_SAFE_PROP
    #define OMNI_NO_SAFE_SEMAPHORE
    #define OMNI_NO_SAFE_CONDITIONAL
    #define OMNI_NO_SAFE_TIMERS
    #define OMNI_NO_SAFE_THREAD
    #define OMNI_NO_SAFE_RUNNABLE_THREAD
    #define OMNI_NO_SAFE_FRAMEWORK
    #define OMNI_NO_FW_VER
    #define OMNI_NO_SAFE_BASIC_THREAD
    #define OMNI_NO_SAFE_MUTEX
    #define OMNI_NO_THROW
    #define OMNI_THREAD_ARGS_RAW_PTR    
#endif

#if defined(OMNI_SAFE_FRAMEWORK) && defined(OMNI_NO_SAFE_FRAMEWORK)
    #undef OMNI_SAFE_FRAMEWORK
#endif

#if defined(OMNI_SAFE_FRAMEWORK)
    #define OMNI_SAFE_APPLICATION
    #define OMNI_SAFE_DELEGATES
    #define OMNI_SAFE_EVENTS
    #define OMNI_SAFE_PROP
    #define OMNI_SAFE_LOCKS
    #define OMNI_SAFE_TIMERS
    #define OMNI_SAFE_THREADS    
    // TODO: add any other "safe" framework entities here
#endif

#if defined(OMNI_SAFE_LOCKS)
    #define OMNI_SAFE_MUTEX
    #define OMNI_SAFE_SEMAPHORE
#endif

#if defined(OMNI_SAFE_MUTEX)
    #define OMNI_MUTEX_OWNER
#endif

#if defined(OMNI_SAFE_TIMERS)
    #define OMNI_SAFE_ASYNC_TIMER
    #define OMNI_SAFE_SYNC_TIMER
    #define OMNI_SAFE_DROP_TIMER
    #define OMNI_SAFE_QUEUE_TIMER
#endif

#if defined(OMNI_SAFE_THREADS)
    #define OMNI_SAFE_THREAD
    #define OMNI_SAFE_BASIC_THREAD
    #define OMNI_SAFE_RUNNABLE_THREAD
#endif

#if defined(OMNI_OBJECT_NAME) && defined(OMNI_NO_OBJECT_NAME)
    #undef OMNI_OBJECT_NAME
#endif
#if defined(OMNI_DISPOSE_EVENT) && defined(OMNI_NO_DISPOSE_EVENT)
    #undef OMNI_DISPOSE_EVENT
#endif    
#if defined(OMNI_TYPE_INFO) && defined(OMNI_NO_TYPE_INFO)
    #undef OMNI_TYPE_INFO
#endif
#if defined(OMNI_SAFE_APPLICATION) && defined(OMNI_NO_SAFE_APPLICATION)
    #undef OMNI_SAFE_APPLICATION
#endif
#if defined(OMNI_SAFE_DELEGATES) && defined(OMNI_NO_SAFE_DELEGATES)
    #undef OMNI_SAFE_DELEGATES
#endif
#if defined(OMNI_SAFE_EVENTS) && defined(OMNI_NO_SAFE_EVENTS)
    #undef OMNI_SAFE_EVENTS
#endif
#if defined(OMNI_SAFE_PROP) && defined(OMNI_NO_SAFE_PROP)
    #undef OMNI_SAFE_PROP
#endif
#if defined(OMNI_SAFE_MUTEX) && defined(OMNI_NO_SAFE_MUTEX)
    #undef OMNI_SAFE_MUTEX
#endif
#if defined(OMNI_SAFE_SEMAPHORE) && defined(OMNI_NO_SAFE_SEMAPHORE)
    #undef OMNI_SAFE_SEMAPHORE
#endif
#if defined(OMNI_SAFE_THREAD) && defined(OMNI_NO_SAFE_THREAD)
    #undef OMNI_SAFE_THREAD
#endif
#if defined(OMNI_SAFE_BASIC_THREAD) && defined(OMNI_NO_SAFE_BASIC_THREAD)
    #under OMNI_SAFE_BASIC_THREAD
#endif
#if defined(OMNI_SAFE_RUNNABLE_THREAD) && defined(OMNI_NO_SAFE_RUNNABLE_THREAD)
    #undef OMNI_SAFE_RUNNABLE_THREAD
#endif
#if defined(OMNI_SAFE_TIMERS) && defined(OMNI_NO_SAFE_TIMERS)
    #undef OMNI_SAFE_ASYNC_TIMER
    #undef OMNI_SAFE_SYNC_TIMER
    #undef OMNI_SAFE_DROP_TIMER
    #undef OMNI_SAFE_QUEUE_TIMER
#endif


#if defined(__UNICODE__) || defined(UNICODE) || defined(_UNICODE) || defined(__UNICODE)
    #define OMNI_UNICODE
#endif

/* "non-portable" functions are areas of code that do not work across all platforms (for instance,
thread scheduling is OS/architecture dependant thus omni::thread::*priority* functionality is only
compiled in if you specify to allow non-portable code. */
#if defined(OMNI_NON_PORTABLE) && defined(OMNI_NO_NON_PORTABLE)
    #undef OMNI_NON_PORTABLE
#endif

/* As the NULL macro is implementation defined and not all compilers will support
the nullptr keyword, the default for null pointer values is to zeroize them, that is,
the preferred way to initialize pointer types to the null value is to set them to the 0
address over setting to NULL or nullptr. Example:

int* val = 0;       <- preferred way
int* val = NULL;    <- OK, but NULL could be anything, so not really 'safe'
int* val = nullptr; <- OK and expresses intent better, but not all compilers support this

We don't want to overuse macro's through the framework, but in this scenario, it's also
preferable to avoid being able to do something like this:

static const int nullptr = 0;
int* val = &nullptr;

'&nullptr' is not allowed in C++11 and additional checks would need to be in place to avoid this in
C++11 compilers and not in previous editions; as well int* val = nullptr could have an implicit cast
since you are referencing a named variable (nullptr), this isn't the case in C++11 with the nullptr keyword. 

So to avoid all of this, we will give the user the option to choose (or define) their null pointer
value. Defining OMNI_NULL_PTR sets the C++11 nullptr keyword while OMNI_NULL_MACRO will use the
implementation defined NULL macro, and if nothing, the default is to use 0. While the macro name
OMNI_NULL is more verbose than 0/NULL/nullptr, it does express the intent better than just plain 0.
*/
#if defined(OMNI_NULL_PTR) && defined(OMNI_NULL_MACRO)
    #error "Can not define OMNI_NULL_PTR and OMNI_NULL_MACRO together"
#endif
#if (defined(OMNI_NULL_PTR) || defined(OMNI_NULL_MACRO)) && defined(OMNI_NULL)
    #error "Can not define OMNI_NULL as well as OMNI_NULL_PTR or OMNI_NULL_MACRO"
#endif
#if defined(OMNI_NULL_PTR)
    #define OMNI_NULL nullptr
#endif
#if defined(OMNI_NULL_MACRO)
    #define OMNI_NULL NULL
#endif
#if !defined(OMNI_NULL)
    #define OMNI_NULL 0
#endif

#if defined(OMNI_OS_WIN)
    #if !defined(_WIN32_WINNT)
        #include <SDKDDKVer.h>
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
        #define WIN32_LEAN_AND_MEAN // trim any extra headers not specifically needed
        #define STRICT // don't imply int types for handles
        #define NOMINMAX // don't conflict with std::min/std::max
    #endif
    #include <windows.h>
    #if defined(OMNI_UNICODE)
        // macro to determine if platform is windows unicode
        #define OMNI_WINCODE
    #endif
    #if !defined(OMNI_NO_WIN_API)
        /*DEV_NOTE: if on Win32 and you wish to compile against the
        Win CRT (Windows C Run Time libraries), pass the OMNI_NO_WIN_API
        flag to your compiler, and the framework will not use any WinAPI
        calls where feasible; threading calls, for instance, need CloseHandle
        but if OMNI_NO_WIN_API is set, _beginthreadex is called instead of
        CreateThread */
        #if !defined(OMNI_WIN_API)
            #define OMNI_WIN_API
        #endif
    #endif
#endif

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

// default mutex owner
#if !defined(OMNI_MUTEX_OWNER)
    #define OMNI_MUTEX_OWNER
#endif
#if defined(OMNI_MUTEX_OWNER) && defined(OMNI_NO_MUTEX_OWNER)
    #undef OMNI_MUTEX_OWNER
#endif

// macro error checks
#if defined(OMNI_NO_CSTRING_IMPL) && !defined(OMNI_UNICODE)
    #error "OMNI_NO_CSTRING_IMPL defined with non unicode build; omni::cstring namespace used for non unicode builds"
#endif
#if defined(OMNI_NO_WSTRING_IMPL) && defined(OMNI_UNICODE)
    #error "OMNI_NO_WSTRING_IMPL defined with unicode build; omni::wstring namespace used for unicode builds"
#endif
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

#if defined(OMNI_NO_EXTERN_CONSTS)
    #define OMNI_CONSTEXT_FW const
    #define OMNI_EXT_ASSN_FW(v) v
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

#if defined(OMNI_ENABLE_CXX)
    // #define OMNI_CXX_THREAD_FW
    // #define OMNI_CXX_MUTEX_FW
#endif

// if debug isn't define, this won't get included
#include <omni/defs/debug.hpp>
// if OMNI_NO_THROW is defined (or OMNI_THROW is not defined) this won't get included
#include <omni/exception.hpp>

/* DEV_NOTE: something that came across was a 'virtual thunk' error, this happened when compiling the
framework as a library using certain features (like omni::type_info or omni::object) and then compiling
the source linked against WITHOUT those features (especially on calls to virtually inherited items like
the omni::runnable & omni::runnable_thread). Just something to be aware of! */

#endif // OMNI_GLOBALDEFS_HPP
