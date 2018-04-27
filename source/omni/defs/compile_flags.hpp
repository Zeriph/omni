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
#if !defined(OMNI_COMPILE_FLAGS_HPP)
#define OMNI_COMPILE_FLAGS_HPP 1

#if defined(OMNI_COMPILE_FLAGS)

#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/types/lock_t.hpp>
#include <omni/types/thread_t.hpp>
#include <omni/types/char_t.hpp>
#include <omni/types/tick_t.hpp>

namespace omni {
    /** Defines run time constant values of compile time flags */
    namespace compile_flags {
        // OMNI_APLNL
        extern const char OMNI_APLNL_VALUE[];
        // OMNI_CHAR_T
        extern const char OMNI_CHAR_T_VALUE[];
        // OMNI_CLOCK_FREQ_T
        extern const char OMNI_CLOCK_FREQ_T_VALUE[];
        // OMNI_CLOCK_TICK_T
        extern const char OMNI_CLOCK_TICK_T_VALUE[];
        // OMNI_COND_T
        extern const char OMNI_COND_T_VALUE[];
        // OMNI_DATE
        extern const char OMNI_DATE_VALUE[];
        // OMNI_FW_VER_MAJ
        extern const char OMNI_FW_VER_MAJ_VALUE[];
        // OMNI_FW_VER_MIN
        extern const char OMNI_FW_VER_MIN_VALUE[];
        // OMNI_FW_VER_STR
        extern const char OMNI_FW_VER_STR_VALUE[];
        // OMNI_FW_VER_SUB
        extern const char OMNI_FW_VER_SUB_VALUE[];
        // OMNI_ISTREAM_T
        extern const char OMNI_ISTREAM_T_VALUE[];
        // OMNI_MUTEX_T
        extern const char OMNI_MUTEX_T_VALUE[];
        // OMNI_NEW_LINE
        extern const char OMNI_NEW_LINE_VALUE[];
        // OMNI_NULL
        extern const char OMNI_NULL_VALUE[];
        // OMNI_SEM_T
        extern const char OMNI_SEM_T_VALUE[];
        // OMNI_SEQ_T
        extern const char OMNI_SEQ_T_VALUE[];
        // OMNI_SEQCONT_TYPE
        extern const char OMNI_SEQCONT_TYPE_VALUE[];
        // OMNI_SIGCALL
        extern const char OMNI_SIGCALL_VALUE[];
        // OMNI_SPIN_LOCK_T
        extern const char OMNI_SPIN_LOCK_T_VALUE[];
        // OMNI_SSTREAM_T
        extern const char OMNI_SSTREAM_T_VALUE[];
        // OMNI_STRING_T
        extern const char OMNI_STRING_T_VALUE[];
        // OMNI_THREAD_CALL_T
        extern const char OMNI_THREAD_CALL_T_VALUE[];
        // OMNI_THREAD_FNPTR_T
        extern const char OMNI_THREAD_FNPTR_T_VALUE[];
        // OMNI_THREAD_HANDLE_T
        extern const char OMNI_THREAD_HANDLE_T_VALUE[];
        // OMNI_THREAD_RET_T
        extern const char OMNI_THREAD_RET_T_VALUE[];
        // OMNI_THREAD_T
        extern const char OMNI_THREAD_T_VALUE[];
        // OMNI_THREAD_ARG_NULL_T
        extern const char OMNI_THREAD_ARG_NULL_T_VALUE[];
        // OMNI_THREAD_ARGS_T
        extern const char OMNI_THREAD_ARGS_T_VALUE[];
        // OMNI_TIME
        extern const char OMNI_TIME_VALUE[];
        
        // OMNI_CLOCK_GETRES_REALTIME
        extern const bool OMNI_CLOCK_GETRES_REALTIME_VALUE;
        // OMNI_DBG_L1
        extern const bool OMNI_DBG_L1_VALUE;
        // OMNI_DBG_L2
        extern const bool OMNI_DBG_L2_VALUE;
        // OMNI_DBG_L3
        extern const bool OMNI_DBG_L3_VALUE;
        // OMNI_DBG_L4
        extern const bool OMNI_DBG_L4_VALUE;
        // OMNI_DBG_L5
        extern const bool OMNI_DBG_L5_VALUE;
        // OMNI_DISPOSE_EVENT
        extern const bool OMNI_DISPOSE_EVENT_VALUE;
        // OMNI_ENABLE_CXX11
        extern const bool OMNI_ENABLE_CXX11_VALUE;
        // OMNI_ENV_WORDEXP
        extern const bool OMNI_ENV_WORDEXP_VALUE;
        // OMNI_EXCEPTION_TERMINATE
        extern const bool OMNI_EXCEPTION_TERMINATE_VALUE;
        // OMNI_FW_VER_USE_TIME
        extern const bool OMNI_FW_VER_USE_TIME_VALUE;
        // OMNI_LITE
        extern const bool OMNI_LITE_VALUE;
        // OMNI_MUTEX_OWNER
        extern const bool OMNI_MUTEX_OWNER_VALUE;
        // OMNI_NO_BASE_SETLOCALE
        extern const bool OMNI_NO_BASE_SETLOCALE_VALUE;
        // OMNI_NO_CLINK
        extern const bool OMNI_NO_CLINK_VALUE;
        // OMNI_NO_DISPOSE_EVENT
        extern const bool OMNI_NO_DISPOSE_EVENT_VALUE;
        // OMNI_NO_EXCEPT
        extern const bool OMNI_NO_EXCEPT_VALUE;
        // OMNI_NO_EXTERN_CONSTS
        extern const bool OMNI_NO_EXTERN_CONSTS_VALUE;
        // OMNI_NO_FW_VER
        extern const bool OMNI_NO_FW_VER_VALUE;
        // OMNI_NO_MUTEX_OWNER
        extern const bool OMNI_NO_MUTEX_OWNER_VALUE;
        // OMNI_NO_NON_PORTABLE
        extern const bool OMNI_NO_NON_PORTABLE_VALUE;
        // OMNI_NO_OBJECT_NAME
        extern const bool OMNI_NO_OBJECT_NAME_VALUE;
        // OMNI_NO_PRINTL
        extern const bool OMNI_NO_PRINTL_VALUE;
        // OMNI_NO_PROC_SYS
        extern const bool OMNI_NO_PROC_SYS_VALUE;
        // OMNI_NO_SAFE_APPLICATION
        extern const bool OMNI_NO_SAFE_APPLICATION_VALUE;
        // OMNI_NO_SAFE_BASIC_THREAD
        extern const bool OMNI_NO_SAFE_BASIC_THREAD_VALUE;
        // OMNI_NO_SAFE_CONDITIONAL
        extern const bool OMNI_NO_SAFE_CONDITIONAL_VALUE;
        // OMNI_NO_SAFE_DELEGATES
        extern const bool OMNI_NO_SAFE_DELEGATES_VALUE;
        // OMNI_NO_SAFE_EVENTS
        extern const bool OMNI_NO_SAFE_EVENTS_VALUE;
        // OMNI_NO_SAFE_FRAMEWORK
        extern const bool OMNI_NO_SAFE_FRAMEWORK_VALUE;
        // OMNI_NO_SAFE_MUTEX
        extern const bool OMNI_NO_SAFE_MUTEX_VALUE;
        // OMNI_NO_SAFE_PROP
        extern const bool OMNI_NO_SAFE_PROP_VALUE;
        // OMNI_NO_SAFE_RUNNABLE_THREAD
        extern const bool OMNI_NO_SAFE_RUNNABLE_THREAD_VALUE;
        // OMNI_NO_SAFE_SEMAPHORE
        extern const bool OMNI_NO_SAFE_SEMAPHORE_VALUE;
        // OMNI_NO_SAFE_THREAD
        extern const bool OMNI_NO_SAFE_THREAD_VALUE;
        // OMNI_NO_SAFE_TIMERS
        extern const bool OMNI_NO_SAFE_TIMERS_VALUE;
        // OMNI_NO_SINGLE_FILE
        extern const bool OMNI_NO_SINGLE_FILE_VALUE;
        // OMNI_NO_TERMINATE
        extern const bool OMNI_NO_TERMINATE_VALUE;
        // OMNI_NO_THROW
        extern const bool OMNI_NO_THROW_VALUE;
        // OMNI_NO_TYPE_INFO
        extern const bool OMNI_NO_TYPE_INFO_VALUE;
        // OMNI_NO_WIN_API
        extern const bool OMNI_NO_WIN_API_VALUE;
        // OMNI_NO_WIN_LEAN
        extern const bool OMNI_NO_WIN_LEAN_VALUE;
        // OMNI_NON_PORTABLE
        extern const bool OMNI_NON_PORTABLE_VALUE;
        // OMNI_NULL_MACRO
        extern const bool OMNI_NULL_MACRO_VALUE;
        // OMNI_NULL_PTR
        extern const bool OMNI_NULL_PTR_VALUE;
        // OMNI_OBJECT_NAME
        extern const bool OMNI_OBJECT_NAME_VALUE;
        // OMNI_OS_AEGIS
        extern const bool OMNI_OS_AEGIS_VALUE;
        // OMNI_OS_AIX
        extern const bool OMNI_OS_AIX_VALUE;
        // OMNI_OS_AMIGA
        extern const bool OMNI_OS_AMIGA_VALUE;
        // OMNI_OS_ANDROID
        extern const bool OMNI_OS_ANDROID_VALUE;
        // OMNI_OS_APPLE
        extern const bool OMNI_OS_APPLE_VALUE;
        // OMNI_OS_APPOLO
        extern const bool OMNI_OS_APPOLO_VALUE;
        // OMNI_OS_BEOS
        extern const bool OMNI_OS_BEOS_VALUE;
        // OMNI_OS_BLUEGENE
        extern const bool OMNI_OS_BLUEGENE_VALUE;
        // OMNI_OS_BSD
        extern const bool OMNI_OS_BSD_VALUE;
        // OMNI_OS_BSDI
        extern const bool OMNI_OS_BSDI_VALUE;
        // OMNI_OS_CONVEX
        extern const bool OMNI_OS_CONVEX_VALUE;
        // OMNI_OS_CRAY
        extern const bool OMNI_OS_CRAY_VALUE;
        // OMNI_OS_CYGWIN
        extern const bool OMNI_OS_CYGWIN_VALUE;
        // OMNI_OS_DGUX
        extern const bool OMNI_OS_DGUX_VALUE;
        // OMNI_OS_DRAGONFLYBSD
        extern const bool OMNI_OS_DRAGONFLYBSD_VALUE;
        // OMNI_OS_DYNIX
        extern const bool OMNI_OS_DYNIX_VALUE;
        // OMNI_OS_ECOS
        extern const bool OMNI_OS_ECOS_VALUE;
        // OMNI_OS_EMX
        extern const bool OMNI_OS_EMX_VALUE;
        // OMNI_OS_FREEBSD
        extern const bool OMNI_OS_FREEBSD_VALUE;
        // OMNI_OS_GNU_FREEBSD
        extern const bool OMNI_OS_GNU_FREEBSD_VALUE;
        // OMNI_OS_GNU_HURD
        extern const bool OMNI_OS_GNU_HURD_VALUE;
        // OMNI_OS_GNU_LINUX
        extern const bool OMNI_OS_GNU_LINUX_VALUE;
        // OMNI_OS_HIUXMPP
        extern const bool OMNI_OS_HIUXMPP_VALUE;
        // OMNI_OS_HPUX
        extern const bool OMNI_OS_HPUX_VALUE;
        // OMNI_OS_IGNORE
        extern const bool OMNI_OS_IGNORE_VALUE;
        // OMNI_OS_INTEGRITY
        extern const bool OMNI_OS_INTEGRITY_VALUE;
        // OMNI_OS_INTERIX
        extern const bool OMNI_OS_INTERIX_VALUE;
        // OMNI_OS_IRIX
        extern const bool OMNI_OS_IRIX_VALUE;
        // OMNI_OS_LINUX
        extern const bool OMNI_OS_LINUX_VALUE;
        // OMNI_OS_LYNXOS
        extern const bool OMNI_OS_LYNXOS_VALUE;
        // OMNI_OS_MICROWARE_OS9
        extern const bool OMNI_OS_MICROWARE_OS9_VALUE;
        // OMNI_OS_MINGW
        extern const bool OMNI_OS_MINGW_VALUE;
        // OMNI_OS_MINIX
        extern const bool OMNI_OS_MINIX_VALUE;
        // OMNI_OS_MORPHOS
        extern const bool OMNI_OS_MORPHOS_VALUE;
        // OMNI_OS_MPEIX
        extern const bool OMNI_OS_MPEIX_VALUE;
        // OMNI_OS_MSDOS
        extern const bool OMNI_OS_MSDOS_VALUE;
        // OMNI_OS_NETBSD
        extern const bool OMNI_OS_NETBSD_VALUE;
        // OMNI_OS_NONSTOP
        extern const bool OMNI_OS_NONSTOP_VALUE;
        // OMNI_OS_NUCLEUS
        extern const bool OMNI_OS_NUCLEUS_VALUE;
        // OMNI_OS_OPENBSD
        extern const bool OMNI_OS_OPENBSD_VALUE;
        // OMNI_OS_OS2
        extern const bool OMNI_OS_OS2_VALUE;
        // OMNI_OS_OS400
        extern const bool OMNI_OS_OS400_VALUE;
        // OMNI_OS_OSF1
        extern const bool OMNI_OS_OSF1_VALUE;
        // OMNI_OS_PALMOS
        extern const bool OMNI_OS_PALMOS_VALUE;
        // OMNI_OS_PYRAMID
        extern const bool OMNI_OS_PYRAMID_VALUE;
        // OMNI_OS_QNX
        extern const bool OMNI_OS_QNX_VALUE;
        // OMNI_OS_RELIANT_UNIX
        extern const bool OMNI_OS_RELIANT_UNIX_VALUE;
        // OMNI_OS_SCO_OPENSERVER
        extern const bool OMNI_OS_SCO_OPENSERVER_VALUE;
        // OMNI_OS_SOLARIS
        extern const bool OMNI_OS_SOLARIS_VALUE;
        // OMNI_OS_SUNOS
        extern const bool OMNI_OS_SUNOS_VALUE;
        // OMNI_OS_SVR
        extern const bool OMNI_OS_SVR_VALUE;
        // OMNI_OS_SYLLABLE
        extern const bool OMNI_OS_SYLLABLE_VALUE;
        // OMNI_OS_SYMBIAN
        extern const bool OMNI_OS_SYMBIAN_VALUE;
        // OMNI_OS_ULTRIX
        extern const bool OMNI_OS_ULTRIX_VALUE;
        // OMNI_OS_UNICOS
        extern const bool OMNI_OS_UNICOS_VALUE;
        // OMNI_OS_UNIX
        extern const bool OMNI_OS_UNIX_VALUE;
        // OMNI_OS_UNIXWARE
        extern const bool OMNI_OS_UNIXWARE_VALUE;
        // OMNI_OS_UTS
        extern const bool OMNI_OS_UTS_VALUE;
        // OMNI_OS_UWIN
        extern const bool OMNI_OS_UWIN_VALUE;
        // OMNI_OS_VMS
        extern const bool OMNI_OS_VMS_VALUE;
        // OMNI_OS_VOS
        extern const bool OMNI_OS_VOS_VALUE;
        // OMNI_OS_WIN
        extern const bool OMNI_OS_WIN_VALUE;
        // OMNI_OS_WIN8
        extern const bool OMNI_OS_WIN8_VALUE;
        // OMNI_OS_WINCE
        extern const bool OMNI_OS_WINCE_VALUE;
        // OMNI_OS_WINDU
        extern const bool OMNI_OS_WINDU_VALUE;
        // OMNI_OS_ZOS
        extern const bool OMNI_OS_ZOS_VALUE;
        // OMNI_OSTREAM_T
        extern const bool OMNI_OSTREAM_T_VALUE;
        // OMNI_SAFE_APPLICATION
        extern const bool OMNI_SAFE_APPLICATION_VALUE;
        // OMNI_SAFE_ASYNC_TIMER
        extern const bool OMNI_SAFE_ASYNC_TIMER_VALUE;
        // OMNI_SAFE_BASIC_THREAD
        extern const bool OMNI_SAFE_BASIC_THREAD_VALUE;
        // OMNI_SAFE_DELEGATES
        extern const bool OMNI_SAFE_DELEGATES_VALUE;
        // OMNI_SAFE_DROP_TIMER
        extern const bool OMNI_SAFE_DROP_TIMER_VALUE;
        // OMNI_SAFE_EVENTS
        extern const bool OMNI_SAFE_EVENTS_VALUE;
        // OMNI_SAFE_FRAMEWORK
        extern const bool OMNI_SAFE_FRAMEWORK_VALUE;
        // OMNI_SAFE_LOCKS
        extern const bool OMNI_SAFE_LOCKS_VALUE;
        // OMNI_SAFE_MUTEX
        extern const bool OMNI_SAFE_MUTEX_VALUE;
        // OMNI_SAFE_PROP
        extern const bool OMNI_SAFE_PROP_VALUE;
        // OMNI_SAFE_QUEUE_TIMER
        extern const bool OMNI_SAFE_QUEUE_TIMER_VALUE;
        // OMNI_SAFE_RUNNABLE_THREAD
        extern const bool OMNI_SAFE_RUNNABLE_THREAD_VALUE;
        // OMNI_SAFE_SEMAPHORE
        extern const bool OMNI_SAFE_SEMAPHORE_VALUE;
        // OMNI_SAFE_SYNC_TIMER
        extern const bool OMNI_SAFE_SYNC_TIMER_VALUE;
        // OMNI_SAFE_THREAD
        extern const bool OMNI_SAFE_THREAD_VALUE;
        // OMNI_SAFE_THREADS
        extern const bool OMNI_SAFE_THREADS_VALUE;
        // OMNI_SAFE_TIMERS
        extern const bool OMNI_SAFE_TIMERS_VALUE;
        // OMNI_SHOW_DEBUG
        extern const bool OMNI_SHOW_DEBUG_VALUE;
        // OMNI_SHOW_DEBUG_ERR
        extern const bool OMNI_SHOW_DEBUG_ERR_VALUE;
        // OMNI_SHOW_DEBUG_FILE
        extern const bool OMNI_SHOW_DEBUG_FILE_VALUE;
        // OMNI_SHOW_DEBUG_FUNC
        extern const bool OMNI_SHOW_DEBUG_FUNC_VALUE;
        // OMNI_SHOW_DEBUG_LINE
        extern const bool OMNI_SHOW_DEBUG_LINE_VALUE;
        // OMNI_TERMINATE
        extern const bool OMNI_TERMINATE_VALUE;
        // OMNI_THREAD_ARGS_RAW_PTR
        extern const bool OMNI_THREAD_ARGS_RAW_PTR_VALUE;
        // OMNI_THREAD_CDECL
        extern const bool OMNI_THREAD_CDECL_VALUE;
        // OMNI_THREAD_FASTCALL
        extern const bool OMNI_THREAD_FASTCALL_VALUE;
        // OMNI_THREAD_LIB
        extern const bool OMNI_THREAD_LIB_VALUE;
        // OMNI_THREAD_STDCALL
        extern const bool OMNI_THREAD_STDCALL_VALUE;
        // OMNI_THROW
        extern const bool OMNI_THROW_VALUE;
        // OMNI_TIMER_LIB
        extern const bool OMNI_TIMER_LIB_VALUE;
        // OMNI_TYPE_INFO
        extern const bool OMNI_TYPE_INFO_VALUE;
        // OMNI_UNICODE
        extern const bool OMNI_UNICODE_VALUE;
        // OMNI_WIN_API
        extern const bool OMNI_WIN_API_VALUE;
        // OMNI_WIN_MONO_TICK_COUNT
        extern const bool OMNI_WIN_MONO_TICK_COUNT_VALUE;
        // OMNI_WIN_MONO_TICK_COUNT64
        extern const bool OMNI_WIN_MONO_TICK_COUNT64_VALUE;
        // OMNI_WIN_MONO_TICK_QPC
        extern const bool OMNI_WIN_MONO_TICK_QPC_VALUE;
        // OMNI_WIN_USE_EVENT_CONDITIONAL
        extern const bool OMNI_WIN_USE_EVENT_CONDITIONAL_VALUE;
    }
}

#endif // OMNI_COMPILE_FLAGS

#endif // OMNI_COMPILE_FLAGS_HPP
