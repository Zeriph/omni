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
#if !defined(OMNI_CANCEL_CHECK_DEF_HPP)
#define OMNI_CANCEL_CHECK_DEF_HPP 1

// TODO: (continuous) add any other no-library entities here that do _not_ relate to the safe options

#if defined(OMNI_SAFE_LIBRARY) && defined(OMNI_NO_SAFE_LIBRARY)
    #undef OMNI_SAFE_LIBRARY
#endif
#if defined(OMNI_32BIT) && defined(OMNI_NO_32BIT)
    #undef OMNI_32BIT
#endif
#if defined(OMNI_OS_MACOS) && defined(OMNI_NO_OS_MACOS)
    #undef OMNI_OS_MACOS
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
#if defined(OMNI_HEAVY_OBJECT_COMPARE) && defined(OMNI_NO_HEAVY_OBJECT_COMPARE)
    #undef OMNI_HEAVY_OBJECT_COMPARE
#endif
#if defined(OMNI_CHRONO_AUTO_INIT_TICK) && defined(OMNI_NO_CHRONO_AUTO_INIT_TICK)
    #undef OMNI_CHRONO_AUTO_INIT_TICK
#endif
#if defined(OMNI_MUTEX_OWNER) && defined(OMNI_NO_MUTEX_OWNER)
    #undef OMNI_MUTEX_OWNER
#endif
#if defined(OMNI_NON_PORTABLE) && defined(OMNI_NO_NON_PORTABLE)
    #undef OMNI_NON_PORTABLE
#endif
#if defined(OMNI_ENABLE_NOEXCEPT) && defined(OMNI_NO_NOEXCEPT)
    #undef OMNI_ENABLE_NOEXCEPT
#endif
#if defined(OMNI_EXPLICIT) && defined(OMNI_NO_EXPLICIT)
    #undef OMNI_EXPLICIT
#endif
#if defined(OMNI_ENV_WORDEXP) && defined(OMNI_NO_ENV_WORDEXP)
    #undef OMNI_ENV_WORDEXP
#endif
#if defined(OMNI_IO_FILE_COPY_USE_FSTREAM) && defined(OMNI_NO_IO_FILE_COPY_USE_FSTREAM)
    #undef OMNI_IO_FILE_COPY_USE_FSTREAM
#endif
#if defined(OMNI_CLOCK_GETRES_REALTIME) && defined(OMNI_NO_CLOCK_GETRES_REALTIME)
    #undef OMNI_CLOCK_GETRES_REALTIME
#endif
#if defined(OMNI_FW_VER_USE_TIME) && defined(OMNI_NO_FW_VER_USE_TIME)
    #undef OMNI_FW_VER_USE_TIME
#endif
#if defined(OMNI_SHOW_DEBUG) && defined(OMNI_NO_SHOW_DEBUG)
    #undef OMNI_SHOW_DEBUG
#endif
#if defined(OMNI_THREAD_ARGS_RAW_PTR) && defined(OMNI_NO_THREAD_ARGS_RAW_PTR)
    #undef OMNI_THREAD_ARGS_RAW_PTR
#endif
#if defined(OMNI_THREAD_CDECL) && defined(OMNI_NO_THREAD_CDECL)
    #undef OMNI_THREAD_CDECL
#endif
#if defined(OMNI_THREAD_FASTCALL) && defined(OMNI_NO_THREAD_FASTCALL)
    #undef OMNI_THREAD_FASTCALL
#endif
#if defined(OMNI_THREAD_STDCALL) && defined(OMNI_NO_THREAD_STDCALL)
    #undef OMNI_THREAD_STDCALL
#endif
#if defined(OMNI_THREADPOOL_USE_SEQ_T) && defined(OMNI_NO_THREADPOOL_USE_SEQ_T)
    #undef OMNI_THREADPOOL_USE_SEQ_T
#endif
#if defined(OMNI_WIN_USE_EVENT_CONDITIONAL) && defined(OMNI_NO_WIN_USE_EVENT_CONDITIONAL)
    #undef OMNI_WIN_USE_EVENT_CONDITIONAL
#endif
#if defined(OMNI_USE_CMATH_CONSTS) && defined(OMNI_NO_USE_CMATH_CONSTS)
    #undef OMNI_USE_CMATH_CONSTS
#endif
#if defined(OMNI_USE_MATH_DEFS) && defined(OMNI_NO_USE_MATH_DEFS)
    #undef OMNI_USE_MATH_DEFS
#endif
#if defined(OMNI_USE_M_E) && defined(OMNI_NO_USE_M_E)
    #undef OMNI_USE_M_E
#endif
#if defined(OMNI_USE_M_E_F) && defined(OMNI_NO_USE_M_E_F)
    #undef OMNI_USE_M_E_F
#endif
#if defined(OMNI_USE_M_E_L) && defined(OMNI_NO_USE_M_E_L)
    #undef OMNI_USE_M_E_L
#endif
#if defined(OMNI_USE_M_PI_F) && defined(OMNI_NO_USE_M_PI_F)
    #undef OMNI_USE_MATH_DEFS
#endif
#if defined(OMNI_SAFE_SHA256) && defined(OMNI_NO_SAFE_SHA256)
    #undef OMNI_SAFE_SHA256
#endif
#if defined(OMNI_SAFE_SHA1) && defined(OMNI_NO_SAFE_SHA1)
    #undef OMNI_SAFE_SHA1
#endif
#if defined(OMNI_SAFE_MD5) && defined(OMNI_NO_SAFE_MD5)
    #undef OMNI_SAFE_MD5
#endif
#if defined(OMNI_NO_GUI)
    #if !defined(OMNI_NO_GUI_USE_X11)
        #define OMNI_NO_GUI_USE_X11
    #endif
    #if !defined(OMNI_NO_GUI_LIB)
        #define OMNI_NO_GUI_LIB
    #endif
    #if !defined(OMNI_NO_GUI_APP)
        #define OMNI_NO_GUI_APP
    #endif
#endif
#if defined(OMNI_GUI_USE_X11) && defined(OMNI_NO_GUI_USE_X11)
    #undef OMNI_GUI_USE_X11
#endif
#if defined(OMNI_GUI_LIB) && defined(OMNI_NO_GUI_LIB)
    #undef OMNI_GUI_LIB
#endif
#if defined(OMNI_GUI_APP) && defined(OMNI_NO_GUI_APP)
    #undef OMNI_GUI_APP
#endif
#if defined(OMNI_NO_UNICODE)
    #if defined(OMNI_UNICODE)
        #undef OMNI_UNICODE
    #endif
    #if defined(__UNICODE__)
        #undef __UNICODE__
    #endif
    #if defined(UNICODE)
        #undef UNICODE
    #endif
    #if defined(_UNICODE)
        #undef _UNICODE
    #endif
    #if defined(__UNICODE)
        #undef __UNICODE
    #endif
#endif

#endif // OMNI_CANCEL_CHECK_DEF_HPP
