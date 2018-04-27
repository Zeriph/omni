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

/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. don't #include <omni/xxx_impl.hxx> and don't compile this source directly.
 this file is #include'd directly in other source.

 This file is included in framework.cpp and contains the compile_flags.hpp 
 extern values
*/

#include <omni/defs/compile_flags.hpp>
#include <omni/defs/helper.hpp>
    
#define OMNI_CFT_FW(NAME) const bool omni::compile_flags::NAME = true;
#define OMNI_CFF_FW(NAME) const bool omni::compile_flags::NAME = false;
#define OMNI_CST_FW(NAME, VAL) const char omni::compile_flags::NAME[] = VAL;

// OMNI_APLNL
#if defined(OMNI_APLNL)
    OMNI_CST_FW(OMNI_APLNL_VALUE, OMNI_DEF2STR(OMNI_APLNL))
#else
    OMNI_CST_FW(OMNI_APLNL_VALUE, "")
#endif
// OMNI_CHAR_T
#if defined(OMNI_CHAR_T)
    OMNI_CST_FW(OMNI_CHAR_T_VALUE, OMNI_DEF2STR(OMNI_CHAR_T))
#else
    OMNI_CST_FW(OMNI_CHAR_T_VALUE, "")
#endif
// OMNI_CLOCK_FREQ_T
#if defined(OMNI_CLOCK_FREQ_T)
    OMNI_CST_FW(OMNI_CLOCK_FREQ_T_VALUE, OMNI_DEF2STR(OMNI_CLOCK_FREQ_T))
#else
    OMNI_CST_FW(OMNI_CLOCK_FREQ_T_VALUE, "")
#endif
// OMNI_CLOCK_TICK_T
#if defined(OMNI_CLOCK_TICK_T)
    OMNI_CST_FW(OMNI_CLOCK_TICK_T_VALUE, OMNI_DEF2STR(OMNI_CLOCK_TICK_T))
#else
    OMNI_CST_FW(OMNI_CLOCK_TICK_T_VALUE, "")
#endif
// OMNI_COND_T
#if defined(OMNI_COND_T)
    OMNI_CST_FW(OMNI_COND_T_VALUE, OMNI_DEF2STR(OMNI_COND_T))
#else
    OMNI_CST_FW(OMNI_COND_T_VALUE, "")
#endif
// OMNI_DATE
#if defined(OMNI_DATE)
    OMNI_CST_FW(OMNI_DATE_VALUE, OMNI_DATE)
#else
    OMNI_CST_FW(OMNI_DATE_VALUE, "")
#endif
// OMNI_FW_VER_MAJ
#if defined(OMNI_FW_VER_MAJ)
    OMNI_CST_FW(OMNI_FW_VER_MAJ_VALUE, OMNI_DEF2STR(OMNI_FW_VER_MAJ))
#else
    OMNI_CST_FW(OMNI_FW_VER_MAJ_VALUE, "")
#endif
// OMNI_FW_VER_MIN
#if defined(OMNI_FW_VER_MIN)
    OMNI_CST_FW(OMNI_FW_VER_MIN_VALUE, OMNI_DEF2STR(OMNI_FW_VER_MIN))
#else
    OMNI_CST_FW(OMNI_FW_VER_MIN_VALUE, "")
#endif
// OMNI_FW_VER_STR
#if defined(OMNI_FW_VER_STR)
    OMNI_CST_FW(OMNI_FW_VER_STR_VALUE, OMNI_DEF2STR(OMNI_FW_VER_STR))
#else
    OMNI_CST_FW(OMNI_FW_VER_STR_VALUE, "")
#endif
// OMNI_FW_VER_SUB
#if defined(OMNI_FW_VER_SUB)
    OMNI_CST_FW(OMNI_FW_VER_SUB_VALUE, OMNI_DEF2STR(OMNI_FW_VER_SUB))
#else
    OMNI_CST_FW(OMNI_FW_VER_SUB_VALUE, "")
#endif
// OMNI_ISTREAM_T
#if defined(OMNI_ISTREAM_T)
    OMNI_CST_FW(OMNI_ISTREAM_T_VALUE, OMNI_DEF2STR(OMNI_ISTREAM_T))
#else
    OMNI_CST_FW(OMNI_ISTREAM_T_VALUE, "")
#endif
// OMNI_MUTEX_T
#if defined(OMNI_MUTEX_T)
    OMNI_CST_FW(OMNI_MUTEX_T_VALUE, OMNI_DEF2STR(OMNI_MUTEX_T))
#else
    OMNI_CST_FW(OMNI_MUTEX_T_VALUE, "")
#endif
// OMNI_NEW_LINE
#if defined(OMNI_NEW_LINE)
    OMNI_CST_FW(OMNI_NEW_LINE_VALUE, OMNI_DEF2STR(OMNI_NEW_LINE))
#else
    OMNI_CST_FW(OMNI_NEW_LINE_VALUE, "")
#endif
// OMNI_NULL
#if defined(OMNI_NULL)
    OMNI_CST_FW(OMNI_NULL_VALUE, OMNI_DEF2STR(OMNI_NULL))
#else
    OMNI_CST_FW(OMNI_NULL_VALUE, "")
#endif
// OMNI_SEM_T
#if defined(OMNI_SEM_T)
    OMNI_CST_FW(OMNI_SEM_T_VALUE, OMNI_DEF2STR(OMNI_SEM_T))
#else
    OMNI_CST_FW(OMNI_SEM_T_VALUE, "")
#endif
// OMNI_SEQ_T
#if defined(OMNI_SEQ_T_FW)
    OMNI_CST_FW(OMNI_SEQ_T_VALUE, OMNI_DEF2STR(OMNI_SEQ_T_FW))
#else
    OMNI_CST_FW(OMNI_SEQ_T_VALUE, "")
#endif
// OMNI_SEQCONT_TYPE
#if defined(OMNI_SEQCONT_TYPE)
    OMNI_CST_FW(OMNI_SEQCONT_TYPE_VALUE, OMNI_DEF2STR(OMNI_SEQCONT_TYPE))
#else
    OMNI_CST_FW(OMNI_SEQCONT_TYPE_VALUE, "")
#endif
// OMNI_SIGCALL
#if defined(OMNI_SIGCALL)
    OMNI_CST_FW(OMNI_SIGCALL_VALUE, OMNI_DEF2STR(OMNI_SIGCALL))
#else
    OMNI_CST_FW(OMNI_SIGCALL_VALUE, "")
#endif
// OMNI_SPIN_LOCK_T
#if defined(OMNI_SPIN_LOCK_T)
    OMNI_CST_FW(OMNI_SPIN_LOCK_T_VALUE, OMNI_DEF2STR(OMNI_SPIN_LOCK_T))
#else
    OMNI_CST_FW(OMNI_SPIN_LOCK_T_VALUE, "")
#endif
// OMNI_SSTREAM_T
#if defined(OMNI_SSTREAM_T)
    OMNI_CST_FW(OMNI_SSTREAM_T_VALUE, OMNI_DEF2STR(OMNI_SSTREAM_T))
#else
    OMNI_CST_FW(OMNI_SSTREAM_T_VALUE, "")
#endif
// OMNI_STRING_T
#if defined(OMNI_STRING_T)
    OMNI_CST_FW(OMNI_STRING_T_VALUE, OMNI_DEF2STR(OMNI_STRING_T))
#else
    OMNI_CST_FW(OMNI_STRING_T_VALUE, "")
#endif
// OMNI_THREAD_CALL_T
#if defined(OMNI_THREAD_CALL_T)
    OMNI_CST_FW(OMNI_THREAD_CALL_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_CALL_T))
#else
    OMNI_CST_FW(OMNI_THREAD_CALL_T_VALUE, "")
#endif
// OMNI_THREAD_FNPTR_T
#if defined(OMNI_THREAD_FNPTR_T)
    OMNI_CST_FW(OMNI_THREAD_FNPTR_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_FNPTR_T))
#else
    OMNI_CST_FW(OMNI_THREAD_FNPTR_T_VALUE, "")
#endif
// OMNI_THREAD_HANDLE_T
#if defined(OMNI_THREAD_HANDLE_T)
    OMNI_CST_FW(OMNI_THREAD_HANDLE_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_HANDLE_T))
#else
    OMNI_CST_FW(OMNI_THREAD_HANDLE_T_VALUE, "")
#endif
// OMNI_THREAD_RET_T
#if defined(OMNI_THREAD_RET_T)
    OMNI_CST_FW(OMNI_THREAD_RET_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_RET_T))
#else
    OMNI_CST_FW(OMNI_THREAD_RET_T_VALUE, "")
#endif
// OMNI_THREAD_T
#if defined(OMNI_THREAD_T)
    OMNI_CST_FW(OMNI_THREAD_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_T))
#else
    OMNI_CST_FW(OMNI_THREAD_T_VALUE, "")
#endif
// OMNI_THREAD_ARG_NULL_T
#if defined(OMNI_THREAD_ARG_NULL_T)
    OMNI_CST_FW(OMNI_THREAD_ARG_NULL_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_ARG_NULL_T))
#else
    OMNI_CST_FW(OMNI_THREAD_ARG_NULL_T_VALUE, "")
#endif
// OMNI_THREAD_ARGS_T
#if defined(OMNI_THREAD_ARGS_T)
    OMNI_CST_FW(OMNI_THREAD_ARGS_T_VALUE, OMNI_DEF2STR(OMNI_THREAD_ARGS_T))
#else
    OMNI_CST_FW(OMNI_THREAD_ARGS_T_VALUE, "")
#endif
// OMNI_TIME
#if defined(OMNI_TIME)
    OMNI_CST_FW(OMNI_TIME_VALUE, OMNI_TIME)
#else
    OMNI_CST_FW(OMNI_TIME_VALUE, "")
#endif

// OMNI_CLOCK_GETRES_REALTIME
#if defined(OMNI_CLOCK_GETRES_REALTIME)
    OMNI_CFT_FW(OMNI_CLOCK_GETRES_REALTIME_VALUE)
#else
    OMNI_CFF_FW(OMNI_CLOCK_GETRES_REALTIME_VALUE)
#endif
// OMNI_DBG_L1
#if defined(OMNI_DBG_L1)
    OMNI_CFT_FW(OMNI_DBG_L1_VALUE)
#else
    OMNI_CFF_FW(OMNI_DBG_L1_VALUE)
#endif
// OMNI_DBG_L2
#if defined(OMNI_DBG_L2)
    OMNI_CFT_FW(OMNI_DBG_L2_VALUE)
#else
    OMNI_CFF_FW(OMNI_DBG_L2_VALUE)
#endif
// OMNI_DBG_L3
#if defined(OMNI_DBG_L3)
    OMNI_CFT_FW(OMNI_DBG_L3_VALUE)
#else
    OMNI_CFF_FW(OMNI_DBG_L3_VALUE)
#endif
// OMNI_DBG_L4
#if defined(OMNI_DBG_L4)
    OMNI_CFT_FW(OMNI_DBG_L4_VALUE)
#else
    OMNI_CFF_FW(OMNI_DBG_L4_VALUE)
#endif
// OMNI_DBG_L5
#if defined(OMNI_DBG_L5)
    OMNI_CFT_FW(OMNI_DBG_L5_VALUE)
#else
    OMNI_CFF_FW(OMNI_DBG_L5_VALUE)
#endif
// OMNI_DISPOSE_EVENT
#if defined(OMNI_DISPOSE_EVENT)
    OMNI_CFT_FW(OMNI_DISPOSE_EVENT_VALUE)
#else
    OMNI_CFF_FW(OMNI_DISPOSE_EVENT_VALUE)
#endif
// OMNI_ENABLE_CXX11
#if defined(OMNI_ENABLE_CXX11)
    OMNI_CFT_FW(OMNI_ENABLE_CXX11_VALUE)
#else
    OMNI_CFF_FW(OMNI_ENABLE_CXX11_VALUE)
#endif
// OMNI_ENV_WORDEXP
#if defined(OMNI_ENV_WORDEXP)
    OMNI_CFT_FW(OMNI_ENV_WORDEXP_VALUE)
#else
    OMNI_CFF_FW(OMNI_ENV_WORDEXP_VALUE)
#endif
// OMNI_EXCEPTION_TERMINATE
#if defined(OMNI_EXCEPTION_TERMINATE)
    OMNI_CFT_FW(OMNI_EXCEPTION_TERMINATE_VALUE)
#else
    OMNI_CFF_FW(OMNI_EXCEPTION_TERMINATE_VALUE)
#endif
// OMNI_FW_VER_USE_TIME
#if defined(OMNI_FW_VER_USE_TIME)
    OMNI_CFT_FW(OMNI_FW_VER_USE_TIME_VALUE)
#else
    OMNI_CFF_FW(OMNI_FW_VER_USE_TIME_VALUE)
#endif
// OMNI_LITE
#if defined(OMNI_LITE)
    OMNI_CFT_FW(OMNI_LITE_VALUE)
#else
    OMNI_CFF_FW(OMNI_LITE_VALUE)
#endif
// OMNI_MUTEX_OWNER
#if defined(OMNI_MUTEX_OWNER)
    OMNI_CFT_FW(OMNI_MUTEX_OWNER_VALUE)
#else
    OMNI_CFF_FW(OMNI_MUTEX_OWNER_VALUE)
#endif
// OMNI_NO_BASE_SETLOCALE
#if defined(OMNI_NO_BASE_SETLOCALE)
    OMNI_CFT_FW(OMNI_NO_BASE_SETLOCALE_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_BASE_SETLOCALE_VALUE)
#endif
// OMNI_NO_CLINK
#if defined(OMNI_NO_CLINK)
    OMNI_CFT_FW(OMNI_NO_CLINK_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_CLINK_VALUE)
#endif
// OMNI_NO_DISPOSE_EVENT
#if defined(OMNI_NO_DISPOSE_EVENT)
    OMNI_CFT_FW(OMNI_NO_DISPOSE_EVENT_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_DISPOSE_EVENT_VALUE)
#endif
// OMNI_NO_EXCEPT
#if defined(OMNI_NO_EXCEPT)
    OMNI_CFT_FW(OMNI_NO_EXCEPT_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_EXCEPT_VALUE)
#endif
// OMNI_NO_EXTERN_CONSTS
#if defined(OMNI_NO_EXTERN_CONSTS)
    OMNI_CFT_FW(OMNI_NO_EXTERN_CONSTS_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_EXTERN_CONSTS_VALUE)
#endif
// OMNI_NO_FW_VER
#if defined(OMNI_NO_FW_VER)
    OMNI_CFT_FW(OMNI_NO_FW_VER_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_FW_VER_VALUE)
#endif
// OMNI_NO_MUTEX_OWNER
#if defined(OMNI_NO_MUTEX_OWNER)
    OMNI_CFT_FW(OMNI_NO_MUTEX_OWNER_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_MUTEX_OWNER_VALUE)
#endif
// OMNI_NO_NON_PORTABLE
#if defined(OMNI_NO_NON_PORTABLE)
    OMNI_CFT_FW(OMNI_NO_NON_PORTABLE_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_NON_PORTABLE_VALUE)
#endif
// OMNI_NO_OBJECT_NAME
#if defined(OMNI_NO_OBJECT_NAME)
    OMNI_CFT_FW(OMNI_NO_OBJECT_NAME_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_OBJECT_NAME_VALUE)
#endif
// OMNI_NO_PRINTL
#if defined(OMNI_NO_PRINTL)
    OMNI_CFT_FW(OMNI_NO_PRINTL_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_PRINTL_VALUE)
#endif
// OMNI_NO_PROC_SYS
#if defined(OMNI_NO_PROC_SYS)
    OMNI_CFT_FW(OMNI_NO_PROC_SYS_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_PROC_SYS_VALUE)
#endif
// OMNI_NO_SAFE_APPLICATION
#if defined(OMNI_NO_SAFE_APPLICATION)
    OMNI_CFT_FW(OMNI_NO_SAFE_APPLICATION_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_APPLICATION_VALUE)
#endif
// OMNI_NO_SAFE_BASIC_THREAD
#if defined(OMNI_NO_SAFE_BASIC_THREAD)
    OMNI_CFT_FW(OMNI_NO_SAFE_BASIC_THREAD_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_BASIC_THREAD_VALUE)
#endif
// OMNI_NO_SAFE_CONDITIONAL
#if defined(OMNI_NO_SAFE_CONDITIONAL)
    OMNI_CFT_FW(OMNI_NO_SAFE_CONDITIONAL_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_CONDITIONAL_VALUE)
#endif
// OMNI_NO_SAFE_DELEGATES
#if defined(OMNI_NO_SAFE_DELEGATES)
    OMNI_CFT_FW(OMNI_NO_SAFE_DELEGATES_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_DELEGATES_VALUE)
#endif
// OMNI_NO_SAFE_EVENTS
#if defined(OMNI_NO_SAFE_EVENTS)
    OMNI_CFT_FW(OMNI_NO_SAFE_EVENTS_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_EVENTS_VALUE)
#endif
// OMNI_NO_SAFE_FRAMEWORK
#if defined(OMNI_NO_SAFE_FRAMEWORK)
    OMNI_CFT_FW(OMNI_NO_SAFE_FRAMEWORK_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_FRAMEWORK_VALUE)
#endif
// OMNI_NO_SAFE_MUTEX
#if defined(OMNI_NO_SAFE_MUTEX)
    OMNI_CFT_FW(OMNI_NO_SAFE_MUTEX_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_MUTEX_VALUE)
#endif
// OMNI_NO_SAFE_PROP
#if defined(OMNI_NO_SAFE_PROP)
    OMNI_CFT_FW(OMNI_NO_SAFE_PROP_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_PROP_VALUE)
#endif
// OMNI_NO_SAFE_RUNNABLE_THREAD
#if defined(OMNI_NO_SAFE_RUNNABLE_THREAD)
    OMNI_CFT_FW(OMNI_NO_SAFE_RUNNABLE_THREAD_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_RUNNABLE_THREAD_VALUE)
#endif
// OMNI_NO_SAFE_SEMAPHORE
#if defined(OMNI_NO_SAFE_SEMAPHORE)
    OMNI_CFT_FW(OMNI_NO_SAFE_SEMAPHORE_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_SEMAPHORE_VALUE)
#endif
// OMNI_NO_SAFE_THREAD
#if defined(OMNI_NO_SAFE_THREAD)
    OMNI_CFT_FW(OMNI_NO_SAFE_THREAD_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_THREAD_VALUE)
#endif
// OMNI_NO_SAFE_TIMERS
#if defined(OMNI_NO_SAFE_TIMERS)
    OMNI_CFT_FW(OMNI_NO_SAFE_TIMERS_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SAFE_TIMERS_VALUE)
#endif
// OMNI_NO_SINGLE_FILE
#if defined(OMNI_NO_SINGLE_FILE)
    OMNI_CFT_FW(OMNI_NO_SINGLE_FILE_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_SINGLE_FILE_VALUE)
#endif
// OMNI_NO_TERMINATE
#if defined(OMNI_NO_TERMINATE)
    OMNI_CFT_FW(OMNI_NO_TERMINATE_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_TERMINATE_VALUE)
#endif
// OMNI_NO_THROW
#if defined(OMNI_NO_THROW)
    OMNI_CFT_FW(OMNI_NO_THROW_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_THROW_VALUE)
#endif
// OMNI_NO_TYPE_INFO
#if defined(OMNI_NO_TYPE_INFO)
    OMNI_CFT_FW(OMNI_NO_TYPE_INFO_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_TYPE_INFO_VALUE)
#endif
// OMNI_NO_WIN_API
#if defined(OMNI_NO_WIN_API)
    OMNI_CFT_FW(OMNI_NO_WIN_API_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_WIN_API_VALUE)
#endif
// OMNI_NO_WIN_LEAN
#if defined(OMNI_NO_WIN_LEAN)
    OMNI_CFT_FW(OMNI_NO_WIN_LEAN_VALUE)
#else
    OMNI_CFF_FW(OMNI_NO_WIN_LEAN_VALUE)
#endif
// OMNI_NON_PORTABLE
#if defined(OMNI_NON_PORTABLE)
    OMNI_CFT_FW(OMNI_NON_PORTABLE_VALUE)
#else
    OMNI_CFF_FW(OMNI_NON_PORTABLE_VALUE)
#endif
// OMNI_NULL_MACRO
#if defined(OMNI_NULL_MACRO)
    OMNI_CFT_FW(OMNI_NULL_MACRO_VALUE)
#else
    OMNI_CFF_FW(OMNI_NULL_MACRO_VALUE)
#endif
// OMNI_NULL_PTR
#if defined(OMNI_NULL_PTR)
    OMNI_CFT_FW(OMNI_NULL_PTR_VALUE)
#else
    OMNI_CFF_FW(OMNI_NULL_PTR_VALUE)
#endif
// OMNI_OBJECT_NAME
#if defined(OMNI_OBJECT_NAME)
    OMNI_CFT_FW(OMNI_OBJECT_NAME_VALUE)
#else
    OMNI_CFF_FW(OMNI_OBJECT_NAME_VALUE)
#endif
// OMNI_OS_AEGIS
#if defined(OMNI_OS_AEGIS)
    OMNI_CFT_FW(OMNI_OS_AEGIS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_AEGIS_VALUE)
#endif
// OMNI_OS_AIX
#if defined(OMNI_OS_AIX)
    OMNI_CFT_FW(OMNI_OS_AIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_AIX_VALUE)
#endif
// OMNI_OS_AMIGA
#if defined(OMNI_OS_AMIGA)
    OMNI_CFT_FW(OMNI_OS_AMIGA_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_AMIGA_VALUE)
#endif
// OMNI_OS_ANDROID
#if defined(OMNI_OS_ANDROID)
    OMNI_CFT_FW(OMNI_OS_ANDROID_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_ANDROID_VALUE)
#endif
// OMNI_OS_APPLE
#if defined(OMNI_OS_APPLE)
    OMNI_CFT_FW(OMNI_OS_APPLE_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_APPLE_VALUE)
#endif
// OMNI_OS_APPOLO
#if defined(OMNI_OS_APPOLO)
    OMNI_CFT_FW(OMNI_OS_APPOLO_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_APPOLO_VALUE)
#endif
// OMNI_OS_BEOS
#if defined(OMNI_OS_BEOS)
    OMNI_CFT_FW(OMNI_OS_BEOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_BEOS_VALUE)
#endif
// OMNI_OS_BLUEGENE
#if defined(OMNI_OS_BLUEGENE)
    OMNI_CFT_FW(OMNI_OS_BLUEGENE_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_BLUEGENE_VALUE)
#endif
// OMNI_OS_BSD
#if defined(OMNI_OS_BSD)
    OMNI_CFT_FW(OMNI_OS_BSD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_BSD_VALUE)
#endif
// OMNI_OS_BSDI
#if defined(OMNI_OS_BSDI)
    OMNI_CFT_FW(OMNI_OS_BSDI_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_BSDI_VALUE)
#endif
// OMNI_OS_CONVEX
#if defined(OMNI_OS_CONVEX)
    OMNI_CFT_FW(OMNI_OS_CONVEX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_CONVEX_VALUE)
#endif
// OMNI_OS_CRAY
#if defined(OMNI_OS_CRAY)
    OMNI_CFT_FW(OMNI_OS_CRAY_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_CRAY_VALUE)
#endif
// OMNI_OS_CYGWIN
#if defined(OMNI_OS_CYGWIN)
    OMNI_CFT_FW(OMNI_OS_CYGWIN_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_CYGWIN_VALUE)
#endif
// OMNI_OS_DGUX
#if defined(OMNI_OS_DGUX)
    OMNI_CFT_FW(OMNI_OS_DGUX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_DGUX_VALUE)
#endif
// OMNI_OS_DRAGONFLYBSD
#if defined(OMNI_OS_DRAGONFLYBSD)
    OMNI_CFT_FW(OMNI_OS_DRAGONFLYBSD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_DRAGONFLYBSD_VALUE)
#endif
// OMNI_OS_DYNIX
#if defined(OMNI_OS_DYNIX)
    OMNI_CFT_FW(OMNI_OS_DYNIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_DYNIX_VALUE)
#endif
// OMNI_OS_ECOS
#if defined(OMNI_OS_ECOS)
    OMNI_CFT_FW(OMNI_OS_ECOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_ECOS_VALUE)
#endif
// OMNI_OS_EMX
#if defined(OMNI_OS_EMX)
    OMNI_CFT_FW(OMNI_OS_EMX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_EMX_VALUE)
#endif
// OMNI_OS_FREEBSD
#if defined(OMNI_OS_FREEBSD)
    OMNI_CFT_FW(OMNI_OS_FREEBSD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_FREEBSD_VALUE)
#endif
// OMNI_OS_GNU_FREEBSD
#if defined(OMNI_OS_GNU_FREEBSD)
    OMNI_CFT_FW(OMNI_OS_GNU_FREEBSD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_GNU_FREEBSD_VALUE)
#endif
// OMNI_OS_GNU_HURD
#if defined(OMNI_OS_GNU_HURD)
    OMNI_CFT_FW(OMNI_OS_GNU_HURD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_GNU_HURD_VALUE)
#endif
// OMNI_OS_GNU_LINUX
#if defined(OMNI_OS_GNU_LINUX)
    OMNI_CFT_FW(OMNI_OS_GNU_LINUX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_GNU_LINUX_VALUE)
#endif
// OMNI_OS_HIUXMPP
#if defined(OMNI_OS_HIUXMPP)
    OMNI_CFT_FW(OMNI_OS_HIUXMPP_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_HIUXMPP_VALUE)
#endif
// OMNI_OS_HPUX
#if defined(OMNI_OS_HPUX)
    OMNI_CFT_FW(OMNI_OS_HPUX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_HPUX_VALUE)
#endif
// OMNI_OS_IGNORE
#if defined(OMNI_OS_IGNORE)
    OMNI_CFT_FW(OMNI_OS_IGNORE_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_IGNORE_VALUE)
#endif
// OMNI_OS_INTEGRITY
#if defined(OMNI_OS_INTEGRITY)
    OMNI_CFT_FW(OMNI_OS_INTEGRITY_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_INTEGRITY_VALUE)
#endif
// OMNI_OS_INTERIX
#if defined(OMNI_OS_INTERIX)
    OMNI_CFT_FW(OMNI_OS_INTERIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_INTERIX_VALUE)
#endif
// OMNI_OS_IRIX
#if defined(OMNI_OS_IRIX)
    OMNI_CFT_FW(OMNI_OS_IRIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_IRIX_VALUE)
#endif
// OMNI_OS_LINUX
#if defined(OMNI_OS_LINUX)
    OMNI_CFT_FW(OMNI_OS_LINUX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_LINUX_VALUE)
#endif
// OMNI_OS_LYNXOS
#if defined(OMNI_OS_LYNXOS)
    OMNI_CFT_FW(OMNI_OS_LYNXOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_LYNXOS_VALUE)
#endif
// OMNI_OS_MICROWARE_OS9
#if defined(OMNI_OS_MICROWARE_OS9)
    OMNI_CFT_FW(OMNI_OS_MICROWARE_OS9_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_MICROWARE_OS9_VALUE)
#endif
// OMNI_OS_MINGW
#if defined(OMNI_OS_MINGW)
    OMNI_CFT_FW(OMNI_OS_MINGW_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_MINGW_VALUE)
#endif
// OMNI_OS_MINIX
#if defined(OMNI_OS_MINIX)
    OMNI_CFT_FW(OMNI_OS_MINIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_MINIX_VALUE)
#endif
// OMNI_OS_MORPHOS
#if defined(OMNI_OS_MORPHOS)
    OMNI_CFT_FW(OMNI_OS_MORPHOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_MORPHOS_VALUE)
#endif
// OMNI_OS_MPEIX
#if defined(OMNI_OS_MPEIX)
    OMNI_CFT_FW(OMNI_OS_MPEIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_MPEIX_VALUE)
#endif
// OMNI_OS_MSDOS
#if defined(OMNI_OS_MSDOS)
    OMNI_CFT_FW(OMNI_OS_MSDOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_MSDOS_VALUE)
#endif
// OMNI_OS_NETBSD
#if defined(OMNI_OS_NETBSD)
    OMNI_CFT_FW(OMNI_OS_NETBSD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_NETBSD_VALUE)
#endif
// OMNI_OS_NONSTOP
#if defined(OMNI_OS_NONSTOP)
    OMNI_CFT_FW(OMNI_OS_NONSTOP_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_NONSTOP_VALUE)
#endif
// OMNI_OS_NUCLEUS
#if defined(OMNI_OS_NUCLEUS)
    OMNI_CFT_FW(OMNI_OS_NUCLEUS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_NUCLEUS_VALUE)
#endif
// OMNI_OS_OPENBSD
#if defined(OMNI_OS_OPENBSD)
    OMNI_CFT_FW(OMNI_OS_OPENBSD_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_OPENBSD_VALUE)
#endif
// OMNI_OS_OS2
#if defined(OMNI_OS_OS2)
    OMNI_CFT_FW(OMNI_OS_OS2_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_OS2_VALUE)
#endif
// OMNI_OS_OS400
#if defined(OMNI_OS_OS400)
    OMNI_CFT_FW(OMNI_OS_OS400_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_OS400_VALUE)
#endif
// OMNI_OS_OSF1
#if defined(OMNI_OS_OSF1)
    OMNI_CFT_FW(OMNI_OS_OSF1_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_OSF1_VALUE)
#endif
// OMNI_OS_PALMOS
#if defined(OMNI_OS_PALMOS)
    OMNI_CFT_FW(OMNI_OS_PALMOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_PALMOS_VALUE)
#endif
// OMNI_OS_PYRAMID
#if defined(OMNI_OS_PYRAMID)
    OMNI_CFT_FW(OMNI_OS_PYRAMID_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_PYRAMID_VALUE)
#endif
// OMNI_OS_QNX
#if defined(OMNI_OS_QNX)
    OMNI_CFT_FW(OMNI_OS_QNX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_QNX_VALUE)
#endif
// OMNI_OS_RELIANT_UNIX
#if defined(OMNI_OS_RELIANT_UNIX)
    OMNI_CFT_FW(OMNI_OS_RELIANT_UNIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_RELIANT_UNIX_VALUE)
#endif
// OMNI_OS_SCO_OPENSERVER
#if defined(OMNI_OS_SCO_OPENSERVER)
    OMNI_CFT_FW(OMNI_OS_SCO_OPENSERVER_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_SCO_OPENSERVER_VALUE)
#endif
// OMNI_OS_SOLARIS
#if defined(OMNI_OS_SOLARIS)
    OMNI_CFT_FW(OMNI_OS_SOLARIS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_SOLARIS_VALUE)
#endif
// OMNI_OS_SUNOS
#if defined(OMNI_OS_SUNOS)
    OMNI_CFT_FW(OMNI_OS_SUNOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_SUNOS_VALUE)
#endif
// OMNI_OS_SVR
#if defined(OMNI_OS_SVR)
    OMNI_CFT_FW(OMNI_OS_SVR_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_SVR_VALUE)
#endif
// OMNI_OS_SYLLABLE
#if defined(OMNI_OS_SYLLABLE)
    OMNI_CFT_FW(OMNI_OS_SYLLABLE_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_SYLLABLE_VALUE)
#endif
// OMNI_OS_SYMBIAN
#if defined(OMNI_OS_SYMBIAN)
    OMNI_CFT_FW(OMNI_OS_SYMBIAN_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_SYMBIAN_VALUE)
#endif
// OMNI_OS_ULTRIX
#if defined(OMNI_OS_ULTRIX)
    OMNI_CFT_FW(OMNI_OS_ULTRIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_ULTRIX_VALUE)
#endif
// OMNI_OS_UNICOS
#if defined(OMNI_OS_UNICOS)
    OMNI_CFT_FW(OMNI_OS_UNICOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_UNICOS_VALUE)
#endif
// OMNI_OS_UNIX
#if defined(OMNI_OS_UNIX)
    OMNI_CFT_FW(OMNI_OS_UNIX_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_UNIX_VALUE)
#endif
// OMNI_OS_UNIXWARE
#if defined(OMNI_OS_UNIXWARE)
    OMNI_CFT_FW(OMNI_OS_UNIXWARE_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_UNIXWARE_VALUE)
#endif
// OMNI_OS_UTS
#if defined(OMNI_OS_UTS)
    OMNI_CFT_FW(OMNI_OS_UTS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_UTS_VALUE)
#endif
// OMNI_OS_UWIN
#if defined(OMNI_OS_UWIN)
    OMNI_CFT_FW(OMNI_OS_UWIN_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_UWIN_VALUE)
#endif
// OMNI_OS_VMS
#if defined(OMNI_OS_VMS)
    OMNI_CFT_FW(OMNI_OS_VMS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_VMS_VALUE)
#endif
// OMNI_OS_VOS
#if defined(OMNI_OS_VOS)
    OMNI_CFT_FW(OMNI_OS_VOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_VOS_VALUE)
#endif
// OMNI_OS_WIN
#if defined(OMNI_OS_WIN)
    OMNI_CFT_FW(OMNI_OS_WIN_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_WIN_VALUE)
#endif
// OMNI_OS_WIN8
#if defined(OMNI_OS_WIN8)
    OMNI_CFT_FW(OMNI_OS_WIN8_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_WIN8_VALUE)
#endif
// OMNI_OS_WINCE
#if defined(OMNI_OS_WINCE)
    OMNI_CFT_FW(OMNI_OS_WINCE_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_WINCE_VALUE)
#endif
// OMNI_OS_WINDU
#if defined(OMNI_OS_WINDU)
    OMNI_CFT_FW(OMNI_OS_WINDU_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_WINDU_VALUE)
#endif
// OMNI_OS_ZOS
#if defined(OMNI_OS_ZOS)
    OMNI_CFT_FW(OMNI_OS_ZOS_VALUE)
#else
    OMNI_CFF_FW(OMNI_OS_ZOS_VALUE)
#endif
// OMNI_OSTREAM_T
#if defined(OMNI_OSTREAM_T)
    OMNI_CFT_FW(OMNI_OSTREAM_T_VALUE)
#else
    OMNI_CFF_FW(OMNI_OSTREAM_T_VALUE)
#endif
// OMNI_SAFE_APPLICATION
#if defined(OMNI_SAFE_APPLICATION)
    OMNI_CFT_FW(OMNI_SAFE_APPLICATION_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_APPLICATION_VALUE)
#endif
// OMNI_SAFE_ASYNC_TIMER
#if defined(OMNI_SAFE_ASYNC_TIMER)
    OMNI_CFT_FW(OMNI_SAFE_ASYNC_TIMER_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_ASYNC_TIMER_VALUE)
#endif
// OMNI_SAFE_BASIC_THREAD
#if defined(OMNI_SAFE_BASIC_THREAD)
    OMNI_CFT_FW(OMNI_SAFE_BASIC_THREAD_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_BASIC_THREAD_VALUE)
#endif
// OMNI_SAFE_DELEGATES
#if defined(OMNI_SAFE_DELEGATES)
    OMNI_CFT_FW(OMNI_SAFE_DELEGATES_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_DELEGATES_VALUE)
#endif
// OMNI_SAFE_DROP_TIMER
#if defined(OMNI_SAFE_DROP_TIMER)
    OMNI_CFT_FW(OMNI_SAFE_DROP_TIMER_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_DROP_TIMER_VALUE)
#endif
// OMNI_SAFE_EVENTS
#if defined(OMNI_SAFE_EVENTS)
    OMNI_CFT_FW(OMNI_SAFE_EVENTS_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_EVENTS_VALUE)
#endif
// OMNI_SAFE_FRAMEWORK
#if defined(OMNI_SAFE_FRAMEWORK)
    OMNI_CFT_FW(OMNI_SAFE_FRAMEWORK_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_FRAMEWORK_VALUE)
#endif
// OMNI_SAFE_LOCKS
#if defined(OMNI_SAFE_LOCKS)
    OMNI_CFT_FW(OMNI_SAFE_LOCKS_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_LOCKS_VALUE)
#endif
// OMNI_SAFE_MUTEX
#if defined(OMNI_SAFE_MUTEX)
    OMNI_CFT_FW(OMNI_SAFE_MUTEX_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_MUTEX_VALUE)
#endif
// OMNI_SAFE_PROP
#if defined(OMNI_SAFE_PROP)
    OMNI_CFT_FW(OMNI_SAFE_PROP_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_PROP_VALUE)
#endif
// OMNI_SAFE_QUEUE_TIMER
#if defined(OMNI_SAFE_QUEUE_TIMER)
    OMNI_CFT_FW(OMNI_SAFE_QUEUE_TIMER_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_QUEUE_TIMER_VALUE)
#endif
// OMNI_SAFE_RUNNABLE_THREAD
#if defined(OMNI_SAFE_RUNNABLE_THREAD)
    OMNI_CFT_FW(OMNI_SAFE_RUNNABLE_THREAD_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_RUNNABLE_THREAD_VALUE)
#endif
// OMNI_SAFE_SEMAPHORE
#if defined(OMNI_SAFE_SEMAPHORE)
    OMNI_CFT_FW(OMNI_SAFE_SEMAPHORE_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_SEMAPHORE_VALUE)
#endif
// OMNI_SAFE_SYNC_TIMER
#if defined(OMNI_SAFE_SYNC_TIMER)
    OMNI_CFT_FW(OMNI_SAFE_SYNC_TIMER_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_SYNC_TIMER_VALUE)
#endif
// OMNI_SAFE_THREAD
#if defined(OMNI_SAFE_THREAD)
    OMNI_CFT_FW(OMNI_SAFE_THREAD_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_THREAD_VALUE)
#endif
// OMNI_SAFE_THREADS
#if defined(OMNI_SAFE_THREADS)
    OMNI_CFT_FW(OMNI_SAFE_THREADS_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_THREADS_VALUE)
#endif
// OMNI_SAFE_TIMERS
#if defined(OMNI_SAFE_TIMERS)
    OMNI_CFT_FW(OMNI_SAFE_TIMERS_VALUE)
#else
    OMNI_CFF_FW(OMNI_SAFE_TIMERS_VALUE)
#endif
// OMNI_SHOW_DEBUG
#if defined(OMNI_SHOW_DEBUG)
    OMNI_CFT_FW(OMNI_SHOW_DEBUG_VALUE)
#else
    OMNI_CFF_FW(OMNI_SHOW_DEBUG_VALUE)
#endif
// OMNI_SHOW_DEBUG_ERR
#if defined(OMNI_SHOW_DEBUG_ERR)
    OMNI_CFT_FW(OMNI_SHOW_DEBUG_ERR_VALUE)
#else
    OMNI_CFF_FW(OMNI_SHOW_DEBUG_ERR_VALUE)
#endif
// OMNI_SHOW_DEBUG_FILE
#if defined(OMNI_SHOW_DEBUG_FILE)
    OMNI_CFT_FW(OMNI_SHOW_DEBUG_FILE_VALUE)
#else
    OMNI_CFF_FW(OMNI_SHOW_DEBUG_FILE_VALUE)
#endif
// OMNI_SHOW_DEBUG_FUNC
#if defined(OMNI_SHOW_DEBUG_FUNC)
    OMNI_CFT_FW(OMNI_SHOW_DEBUG_FUNC_VALUE)
#else
    OMNI_CFF_FW(OMNI_SHOW_DEBUG_FUNC_VALUE)
#endif
// OMNI_SHOW_DEBUG_LINE
#if defined(OMNI_SHOW_DEBUG_LINE)
    OMNI_CFT_FW(OMNI_SHOW_DEBUG_LINE_VALUE)
#else
    OMNI_CFF_FW(OMNI_SHOW_DEBUG_LINE_VALUE)
#endif
// OMNI_TERMINATE
#if defined(OMNI_TERMINATE)
    OMNI_CFT_FW(OMNI_TERMINATE_VALUE)
#else
    OMNI_CFF_FW(OMNI_TERMINATE_VALUE)
#endif
// OMNI_THREAD_ARGS_RAW_PTR
#if defined(OMNI_THREAD_ARGS_RAW_PTR)
    OMNI_CFT_FW(OMNI_THREAD_ARGS_RAW_PTR_VALUE)
#else
    OMNI_CFF_FW(OMNI_THREAD_ARGS_RAW_PTR_VALUE)
#endif
// OMNI_THREAD_CDECL
#if defined(OMNI_THREAD_CDECL)
    OMNI_CFT_FW(OMNI_THREAD_CDECL_VALUE)
#else
    OMNI_CFF_FW(OMNI_THREAD_CDECL_VALUE)
#endif
// OMNI_THREAD_FASTCALL
#if defined(OMNI_THREAD_FASTCALL)
    OMNI_CFT_FW(OMNI_THREAD_FASTCALL_VALUE)
#else
    OMNI_CFF_FW(OMNI_THREAD_FASTCALL_VALUE)
#endif
// OMNI_THREAD_LIB
#if defined(OMNI_THREAD_LIB)
    OMNI_CFT_FW(OMNI_THREAD_LIB_VALUE)
#else
    OMNI_CFF_FW(OMNI_THREAD_LIB_VALUE)
#endif
// OMNI_THREAD_STDCALL
#if defined(OMNI_THREAD_STDCALL)
    OMNI_CFT_FW(OMNI_THREAD_STDCALL_VALUE)
#else
    OMNI_CFF_FW(OMNI_THREAD_STDCALL_VALUE)
#endif
// OMNI_THROW
#if defined(OMNI_THROW)
    OMNI_CFT_FW(OMNI_THROW_VALUE)
#else
    OMNI_CFF_FW(OMNI_THROW_VALUE)
#endif
// OMNI_TIMER_LIB
#if defined(OMNI_TIMER_LIB)
    OMNI_CFT_FW(OMNI_TIMER_LIB_VALUE)
#else
    OMNI_CFF_FW(OMNI_TIMER_LIB_VALUE)
#endif
// OMNI_TYPE_INFO
#if defined(OMNI_TYPE_INFO)
    OMNI_CFT_FW(OMNI_TYPE_INFO_VALUE)
#else
    OMNI_CFF_FW(OMNI_TYPE_INFO_VALUE)
#endif
// OMNI_UNICODE
#if defined(OMNI_UNICODE)
    OMNI_CFT_FW(OMNI_UNICODE_VALUE)
#else
    OMNI_CFF_FW(OMNI_UNICODE_VALUE)
#endif
// OMNI_WIN_API
#if defined(OMNI_WIN_API)
    OMNI_CFT_FW(OMNI_WIN_API_VALUE)
#else
    OMNI_CFF_FW(OMNI_WIN_API_VALUE)
#endif
// OMNI_WIN_MONO_TICK_COUNT
#if defined(OMNI_WIN_MONO_TICK_COUNT)
    OMNI_CFT_FW(OMNI_WIN_MONO_TICK_COUNT_VALUE)
#else
    OMNI_CFF_FW(OMNI_WIN_MONO_TICK_COUNT_VALUE)
#endif
// OMNI_WIN_MONO_TICK_COUNT64
#if defined(OMNI_WIN_MONO_TICK_COUNT64)
    OMNI_CFT_FW(OMNI_WIN_MONO_TICK_COUNT64_VALUE)
#else
    OMNI_CFF_FW(OMNI_WIN_MONO_TICK_COUNT64_VALUE)
#endif
// OMNI_WIN_MONO_TICK_QPC
#if defined(OMNI_WIN_MONO_TICK_QPC)
    OMNI_CFT_FW(OMNI_WIN_MONO_TICK_QPC_VALUE)
#else
    OMNI_CFF_FW(OMNI_WIN_MONO_TICK_QPC_VALUE)
#endif
// OMNI_WIN_USE_EVENT_CONDITIONAL
#if defined(OMNI_WIN_USE_EVENT_CONDITIONAL)
    OMNI_CFT_FW(OMNI_WIN_USE_EVENT_CONDITIONAL_VALUE)
#else
    OMNI_CFF_FW(OMNI_WIN_USE_EVENT_CONDITIONAL_VALUE)
#endif
