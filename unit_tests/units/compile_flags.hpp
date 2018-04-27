#if defined(OMNI_UTUA) || defined(OMNI_UT_COMPILE_FLAGS)

#define UT_NAME compile_flags
#define UT_DESC "Displays the compile_flags info"
#define UT_ISNS
#include <utdefs/unit_test.hpp>

#define printmb(m) printv(OMNI_DEF2STR(m)" = ", OMNI_BOOL2STR(omni::compile_flags::m))
#define printms(m) printv(OMNI_DEF2STR(m)" = ", omni::compile_flags::m)

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            // OMNI_APLNL
            printms(OMNI_APLNL_VALUE);
            // OMNI_CHAR_T
            printms(OMNI_CHAR_T_VALUE);
            // OMNI_CLOCK_FREQ_T
            printms(OMNI_CLOCK_FREQ_T_VALUE);
            // OMNI_CLOCK_TICK_T
            printms(OMNI_CLOCK_TICK_T_VALUE);
            // OMNI_COND_T
            printms(OMNI_COND_T_VALUE);
            // OMNI_DATE
            printms(OMNI_DATE_VALUE);
            // OMNI_FW_VER_MAJ
            printms(OMNI_FW_VER_MAJ_VALUE);
            // OMNI_FW_VER_MIN
            printms(OMNI_FW_VER_MIN_VALUE);
            // OMNI_FW_VER_STR
            printms(OMNI_FW_VER_STR_VALUE);
            // OMNI_FW_VER_SUB
            printms(OMNI_FW_VER_SUB_VALUE);
            // OMNI_ISTREAM_T
            printms(OMNI_ISTREAM_T_VALUE);
            // OMNI_MUTEX_T
            printms(OMNI_MUTEX_T_VALUE);
            // OMNI_NEW_LINE
            printms(OMNI_NEW_LINE_VALUE);
            // OMNI_NULL
            printms(OMNI_NULL_VALUE);
            // OMNI_SEM_T
            printms(OMNI_SEM_T_VALUE);
            // OMNI_SEQ_T
            printms(OMNI_SEQ_T_VALUE);
            // OMNI_SEQCONT_TYPE
            printms(OMNI_SEQCONT_TYPE_VALUE);
            // OMNI_SIGCALL
            printms(OMNI_SIGCALL_VALUE);
            // OMNI_SPIN_LOCK_T
            printms(OMNI_SPIN_LOCK_T_VALUE);
            // OMNI_SSTREAM_T
            printms(OMNI_SSTREAM_T_VALUE);
            // OMNI_STRING_T
            printms(OMNI_STRING_T_VALUE);
            // OMNI_THREAD_CALL_T
            printms(OMNI_THREAD_CALL_T_VALUE);
            // OMNI_THREAD_FNPTR_T
            printms(OMNI_THREAD_FNPTR_T_VALUE);
            // OMNI_THREAD_HANDLE_T
            printms(OMNI_THREAD_HANDLE_T_VALUE);
            // OMNI_THREAD_RET_T
            printms(OMNI_THREAD_RET_T_VALUE);
            // OMNI_THREAD_T
            printms(OMNI_THREAD_T_VALUE);
            // OMNI_THREAD_ARG_NULL_T
            printms(OMNI_THREAD_ARG_NULL_T_VALUE);
            // OMNI_THREAD_ARGS_T
            printms(OMNI_THREAD_ARGS_T_VALUE);
            // OMNI_TIME
            printms(OMNI_TIME_VALUE);
            
            // OMNI_CLOCK_GETRES_REALTIME
            printmb(OMNI_CLOCK_GETRES_REALTIME_VALUE);
            // OMNI_DBG_L1
            printmb(OMNI_DBG_L1_VALUE);
            // OMNI_DBG_L2
            printmb(OMNI_DBG_L2_VALUE);
            // OMNI_DBG_L3
            printmb(OMNI_DBG_L3_VALUE);
            // OMNI_DBG_L4
            printmb(OMNI_DBG_L4_VALUE);
            // OMNI_DBG_L5
            printmb(OMNI_DBG_L5_VALUE);
            // OMNI_DISPOSE_EVENT
            printmb(OMNI_DISPOSE_EVENT_VALUE);
            // OMNI_ENABLE_CXX11
            printmb(OMNI_ENABLE_CXX11_VALUE);
            // OMNI_ENV_WORDEXP
            printmb(OMNI_ENV_WORDEXP_VALUE);
            // OMNI_EXCEPTION_TERMINATE
            printmb(OMNI_EXCEPTION_TERMINATE_VALUE);
            // OMNI_FW_VER_USE_TIME
            printmb(OMNI_FW_VER_USE_TIME_VALUE);
            // OMNI_LITE
            printmb(OMNI_LITE_VALUE);
            // OMNI_MUTEX_OWNER
            printmb(OMNI_MUTEX_OWNER_VALUE);
            // OMNI_NO_BASE_SETLOCALE
            printmb(OMNI_NO_BASE_SETLOCALE_VALUE);
            // OMNI_NO_CLINK
            printmb(OMNI_NO_CLINK_VALUE);
            // OMNI_NO_DISPOSE_EVENT
            printmb(OMNI_NO_DISPOSE_EVENT_VALUE);
            // OMNI_NO_EXCEPT
            printmb(OMNI_NO_EXCEPT_VALUE);
            // OMNI_NO_EXTERN_CONSTS
            printmb(OMNI_NO_EXTERN_CONSTS_VALUE);
            // OMNI_NO_FW_VER
            printmb(OMNI_NO_FW_VER_VALUE);
            // OMNI_NO_MUTEX_OWNER
            printmb(OMNI_NO_MUTEX_OWNER_VALUE);
            // OMNI_NO_NON_PORTABLE
            printmb(OMNI_NO_NON_PORTABLE_VALUE);
            // OMNI_NO_OBJECT_NAME
            printmb(OMNI_NO_OBJECT_NAME_VALUE);
            // OMNI_NO_PRINTL
            printmb(OMNI_NO_PRINTL_VALUE);
            // OMNI_NO_PROC_SYS
            printmb(OMNI_NO_PROC_SYS_VALUE);
            // OMNI_NO_SAFE_APPLICATION
            printmb(OMNI_NO_SAFE_APPLICATION_VALUE);
            // OMNI_NO_SAFE_BASIC_THREAD
            printmb(OMNI_NO_SAFE_BASIC_THREAD_VALUE);
            // OMNI_NO_SAFE_CONDITIONAL
            printmb(OMNI_NO_SAFE_CONDITIONAL_VALUE);
            // OMNI_NO_SAFE_DELEGATES
            printmb(OMNI_NO_SAFE_DELEGATES_VALUE);
            // OMNI_NO_SAFE_EVENTS
            printmb(OMNI_NO_SAFE_EVENTS_VALUE);
            // OMNI_NO_SAFE_FRAMEWORK
            printmb(OMNI_NO_SAFE_FRAMEWORK_VALUE);
            // OMNI_NO_SAFE_MUTEX
            printmb(OMNI_NO_SAFE_MUTEX_VALUE);
            // OMNI_NO_SAFE_PROP
            printmb(OMNI_NO_SAFE_PROP_VALUE);
            // OMNI_NO_SAFE_RUNNABLE_THREAD
            printmb(OMNI_NO_SAFE_RUNNABLE_THREAD_VALUE);
            // OMNI_NO_SAFE_SEMAPHORE
            printmb(OMNI_NO_SAFE_SEMAPHORE_VALUE);
            // OMNI_NO_SAFE_THREAD
            printmb(OMNI_NO_SAFE_THREAD_VALUE);
            // OMNI_NO_SINGLE_FILE
            printmb(OMNI_NO_SINGLE_FILE_VALUE);
            // OMNI_NO_TERMINATE
            printmb(OMNI_NO_TERMINATE_VALUE);
            // OMNI_NO_THROW
            printmb(OMNI_NO_THROW_VALUE);
            // OMNI_NO_TYPE_INFO
            printmb(OMNI_NO_TYPE_INFO_VALUE);
            // OMNI_NO_WIN_API
            printmb(OMNI_NO_WIN_API_VALUE);
            // OMNI_NO_WIN_LEAN
            printmb(OMNI_NO_WIN_LEAN_VALUE);
            // OMNI_NON_PORTABLE
            printmb(OMNI_NON_PORTABLE_VALUE);
            // OMNI_NULL_MACRO
            printmb(OMNI_NULL_MACRO_VALUE);
            // OMNI_NULL_PTR
            printmb(OMNI_NULL_PTR_VALUE);
            // OMNI_OBJECT_NAME
            printmb(OMNI_OBJECT_NAME_VALUE);
            // OMNI_OS_AEGIS
            printmb(OMNI_OS_AEGIS_VALUE);
            // OMNI_OS_AIX
            printmb(OMNI_OS_AIX_VALUE);
            // OMNI_OS_AMIGA
            printmb(OMNI_OS_AMIGA_VALUE);
            // OMNI_OS_ANDROID
            printmb(OMNI_OS_ANDROID_VALUE);
            // OMNI_OS_APPLE
            printmb(OMNI_OS_APPLE_VALUE);
            // OMNI_OS_APPOLO
            printmb(OMNI_OS_APPOLO_VALUE);
            // OMNI_OS_BEOS
            printmb(OMNI_OS_BEOS_VALUE);
            // OMNI_OS_BLUEGENE
            printmb(OMNI_OS_BLUEGENE_VALUE);
            // OMNI_OS_BSD
            printmb(OMNI_OS_BSD_VALUE);
            // OMNI_OS_BSDI
            printmb(OMNI_OS_BSDI_VALUE);
            // OMNI_OS_CONVEX
            printmb(OMNI_OS_CONVEX_VALUE);
            // OMNI_OS_CRAY
            printmb(OMNI_OS_CRAY_VALUE);
            // OMNI_OS_CYGWIN
            printmb(OMNI_OS_CYGWIN_VALUE);
            // OMNI_OS_DGUX
            printmb(OMNI_OS_DGUX_VALUE);
            // OMNI_OS_DRAGONFLYBSD
            printmb(OMNI_OS_DRAGONFLYBSD_VALUE);
            // OMNI_OS_DYNIX
            printmb(OMNI_OS_DYNIX_VALUE);
            // OMNI_OS_ECOS
            printmb(OMNI_OS_ECOS_VALUE);
            // OMNI_OS_EMX
            printmb(OMNI_OS_EMX_VALUE);
            // OMNI_OS_FREEBSD
            printmb(OMNI_OS_FREEBSD_VALUE);
            // OMNI_OS_GNU_FREEBSD
            printmb(OMNI_OS_GNU_FREEBSD_VALUE);
            // OMNI_OS_GNU_HURD
            printmb(OMNI_OS_GNU_HURD_VALUE);
            // OMNI_OS_GNU_LINUX
            printmb(OMNI_OS_GNU_LINUX_VALUE);
            // OMNI_OS_HIUXMPP
            printmb(OMNI_OS_HIUXMPP_VALUE);
            // OMNI_OS_HPUX
            printmb(OMNI_OS_HPUX_VALUE);
            // OMNI_OS_IGNORE
            printmb(OMNI_OS_IGNORE_VALUE);
            // OMNI_OS_INTEGRITY
            printmb(OMNI_OS_INTEGRITY_VALUE);
            // OMNI_OS_INTERIX
            printmb(OMNI_OS_INTERIX_VALUE);
            // OMNI_OS_IRIX
            printmb(OMNI_OS_IRIX_VALUE);
            // OMNI_OS_LINUX
            printmb(OMNI_OS_LINUX_VALUE);
            // OMNI_OS_LYNXOS
            printmb(OMNI_OS_LYNXOS_VALUE);
            // OMNI_OS_MICROWARE_OS9
            printmb(OMNI_OS_MICROWARE_OS9_VALUE);
            // OMNI_OS_MINGW
            printmb(OMNI_OS_MINGW_VALUE);
            // OMNI_OS_MINIX
            printmb(OMNI_OS_MINIX_VALUE);
            // OMNI_OS_MORPHOS
            printmb(OMNI_OS_MORPHOS_VALUE);
            // OMNI_OS_MPEIX
            printmb(OMNI_OS_MPEIX_VALUE);
            // OMNI_OS_MSDOS
            printmb(OMNI_OS_MSDOS_VALUE);
            // OMNI_OS_NETBSD
            printmb(OMNI_OS_NETBSD_VALUE);
            // OMNI_OS_NONSTOP
            printmb(OMNI_OS_NONSTOP_VALUE);
            // OMNI_OS_NUCLEUS
            printmb(OMNI_OS_NUCLEUS_VALUE);
            // OMNI_OS_OPENBSD
            printmb(OMNI_OS_OPENBSD_VALUE);
            // OMNI_OS_OS2
            printmb(OMNI_OS_OS2_VALUE);
            // OMNI_OS_OS400
            printmb(OMNI_OS_OS400_VALUE);
            // OMNI_OS_OSF1
            printmb(OMNI_OS_OSF1_VALUE);
            // OMNI_OS_PALMOS
            printmb(OMNI_OS_PALMOS_VALUE);
            // OMNI_OS_PYRAMID
            printmb(OMNI_OS_PYRAMID_VALUE);
            // OMNI_OS_QNX
            printmb(OMNI_OS_QNX_VALUE);
            // OMNI_OS_RELIANT_UNIX
            printmb(OMNI_OS_RELIANT_UNIX_VALUE);
            // OMNI_OS_SCO_OPENSERVER
            printmb(OMNI_OS_SCO_OPENSERVER_VALUE);
            // OMNI_OS_SOLARIS
            printmb(OMNI_OS_SOLARIS_VALUE);
            // OMNI_OS_SUNOS
            printmb(OMNI_OS_SUNOS_VALUE);
            // OMNI_OS_SVR
            printmb(OMNI_OS_SVR_VALUE);
            // OMNI_OS_SYLLABLE
            printmb(OMNI_OS_SYLLABLE_VALUE);
            // OMNI_OS_SYMBIAN
            printmb(OMNI_OS_SYMBIAN_VALUE);
            // OMNI_OS_ULTRIX
            printmb(OMNI_OS_ULTRIX_VALUE);
            // OMNI_OS_UNICOS
            printmb(OMNI_OS_UNICOS_VALUE);
            // OMNI_OS_UNIX
            printmb(OMNI_OS_UNIX_VALUE);
            // OMNI_OS_UNIXWARE
            printmb(OMNI_OS_UNIXWARE_VALUE);
            // OMNI_OS_UTS
            printmb(OMNI_OS_UTS_VALUE);
            // OMNI_OS_UWIN
            printmb(OMNI_OS_UWIN_VALUE);
            // OMNI_OS_VMS
            printmb(OMNI_OS_VMS_VALUE);
            // OMNI_OS_VOS
            printmb(OMNI_OS_VOS_VALUE);
            // OMNI_OS_WIN
            printmb(OMNI_OS_WIN_VALUE);
            // OMNI_OS_WIN8
            printmb(OMNI_OS_WIN8_VALUE);
            // OMNI_OS_WINCE
            printmb(OMNI_OS_WINCE_VALUE);
            // OMNI_OS_WINDU
            printmb(OMNI_OS_WINDU_VALUE);
            // OMNI_OS_ZOS
            printmb(OMNI_OS_ZOS_VALUE);
            // OMNI_OSTREAM_T
            printmb(OMNI_OSTREAM_T_VALUE);
            // OMNI_SAFE_APPLICATION
            printmb(OMNI_SAFE_APPLICATION_VALUE);
            // OMNI_SAFE_ASYNC_TIMER
            printmb(OMNI_SAFE_ASYNC_TIMER_VALUE);
            // OMNI_SAFE_BASIC_THREAD
            printmb(OMNI_SAFE_BASIC_THREAD_VALUE);
            // OMNI_SAFE_DELEGATES
            printmb(OMNI_SAFE_DELEGATES_VALUE);
            // OMNI_SAFE_DROP_TIMER
            printmb(OMNI_SAFE_DROP_TIMER_VALUE);
            // OMNI_SAFE_EVENTS
            printmb(OMNI_SAFE_EVENTS_VALUE);
            // OMNI_SAFE_FRAMEWORK
            printmb(OMNI_SAFE_FRAMEWORK_VALUE);
            // OMNI_SAFE_LOCKS
            printmb(OMNI_SAFE_LOCKS_VALUE);
            // OMNI_SAFE_MUTEX
            printmb(OMNI_SAFE_MUTEX_VALUE);
            // OMNI_SAFE_PROP
            printmb(OMNI_SAFE_PROP_VALUE);
            // OMNI_SAFE_QUEUE_TIMER
            printmb(OMNI_SAFE_QUEUE_TIMER_VALUE);
            // OMNI_SAFE_RUNNABLE_THREAD
            printmb(OMNI_SAFE_RUNNABLE_THREAD_VALUE);
            // OMNI_SAFE_SEMAPHORE
            printmb(OMNI_SAFE_SEMAPHORE_VALUE);
            // OMNI_SAFE_SYNC_TIMER
            printmb(OMNI_SAFE_SYNC_TIMER_VALUE);
            // OMNI_SAFE_THREAD
            printmb(OMNI_SAFE_THREAD_VALUE);
            // OMNI_SAFE_THREADS
            printmb(OMNI_SAFE_THREADS_VALUE);
            // OMNI_SAFE_TIMERS
            printmb(OMNI_SAFE_TIMERS_VALUE);
            // OMNI_SHOW_DEBUG
            printmb(OMNI_SHOW_DEBUG_VALUE);
            // OMNI_SHOW_DEBUG_ERR
            printmb(OMNI_SHOW_DEBUG_ERR_VALUE);
            // OMNI_SHOW_DEBUG_FILE
            printmb(OMNI_SHOW_DEBUG_FILE_VALUE);
            // OMNI_SHOW_DEBUG_FUNC
            printmb(OMNI_SHOW_DEBUG_FUNC_VALUE);
            // OMNI_SHOW_DEBUG_LINE
            printmb(OMNI_SHOW_DEBUG_LINE_VALUE);
            // OMNI_TERMINATE
            printmb(OMNI_TERMINATE_VALUE);
            // OMNI_THREAD_ARGS_RAW_PTR
            printmb(OMNI_THREAD_ARGS_RAW_PTR_VALUE);
            // OMNI_THREAD_CDECL
            printmb(OMNI_THREAD_CDECL_VALUE);
            // OMNI_THREAD_FASTCALL
            printmb(OMNI_THREAD_FASTCALL_VALUE);
            // OMNI_THREAD_LIB
            printmb(OMNI_THREAD_LIB_VALUE);
            // OMNI_THREAD_STDCALL
            printmb(OMNI_THREAD_STDCALL_VALUE);
            // OMNI_THROW
            printmb(OMNI_THROW_VALUE);
            // OMNI_TIMER_LIB
            printmb(OMNI_TIMER_LIB_VALUE);
            // OMNI_TYPE_INFO
            printmb(OMNI_TYPE_INFO_VALUE);
            // OMNI_UNICODE
            printmb(OMNI_UNICODE_VALUE);
            // OMNI_WIN_API
            printmb(OMNI_WIN_API_VALUE);
            // OMNI_WIN_MONO_TICK_COUNT
            printmb(OMNI_WIN_MONO_TICK_COUNT_VALUE);
            // OMNI_WIN_MONO_TICK_COUNT64
            printmb(OMNI_WIN_MONO_TICK_COUNT64_VALUE);
            // OMNI_WIN_MONO_TICK_QPC
            printmb(OMNI_WIN_MONO_TICK_QPC_VALUE);
            // OMNI_WIN_USE_EVENT_CONDITIONAL
            printmb(OMNI_WIN_USE_EVENT_CONDITIONAL_VALUE);
            
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_COMPILE_FLAGS
