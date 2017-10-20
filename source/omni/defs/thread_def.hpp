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
#if !defined(OMNI_THREAD_DEF_HPP)
#define OMNI_THREAD_DEF_HPP 1

#if defined(OMNI_OS_WIN)
    #include <process.h>
    #define OMNI_INFINITE_TIMEOUT INFINITE
#else
    #include <pthread.h>
    #define OMNI_INFINITE_TIMEOUT 0xFFFFFFFF
#endif

// define how the thread calls will be setup
#if defined(OMNI_OS_WIN)
    /*
        DEV_NOTE: CreateThread returns a HANDLE, _beginthreadex returns
        a uintptr_t (both defined as unsigned types). Most WinAPI calls
        that need to be made (like WaitForSingleObject for a thread join)
        when working with either thread create function take a 'HANDLE'
        type as their parameter. If _beginthreadex is used we need to convert
        the uintptr_t handle to a HANDLE in every call. Hence why if OMNI_WIN_API
        is not defined, we do not define the OMNI_THREAD_HANDLE_T as a
        uintptr_t, instead we cast _beginthreadex to a HANDLE.
    */
    #if defined(OMNI_WIN_API)
        #define OMNI_THREAD_HANDLE_T HANDLE
        #define OMNI_THREAD_T DWORD
        #define OMNI_THREAD_FNPTR_T DWORD
        #define OMNI_THREAD_RET_T DWORD
        #define OMNI_TMPIDT_FW DWORD
        #define OMNI_CREATE_THREAD_FW(SA, SS, FNP, ARGS, SN, TID) ::CreateThread(SA, SS, FNP, ARGS, SN, TID)
        #define OMNI_WIN_TOHNDL_FW(h) h
    #else
        #define OMNI_THREAD_HANDLE_T uintptr_t
        #define OMNI_THREAD_T unsigned int
        #define OMNI_THREAD_FNPTR_T unsigned int
        #define OMNI_THREAD_RET_T unsigned int
        #define OMNI_TMPIDT_FW unsigned int
        #define OMNI_CREATE_THREAD_FW(SA, SS, FNP, ARGS, SN, TID) ::_beginthreadex(SA, SS, FNP, ARGS, SN, TID)
        #define OMNI_WIN_TOHNDL_FW(h) reinterpret_cast<HANDLE>(h)
    #endif
    #if !defined(OMNI_THREAD_CALL_T)
        #if defined(OMNI_THREAD_STDCALL)
            #define OMNI_THREAD_CALL_T __stdcall
        #elif defined(OMNI_THREAD_FASTCALL)
            #define OMNI_THREAD_CALL_T __fastcall
        #elif defined(OMNI_THREAD_CDECL)
            #define OMNI_THREAD_CALL_T __cdecl
        #else
            /*If WINAPI is defined and the user did not specify manually
            what kind of thread call to use, then use the default WINAPI
            otherwise an empty OMNI_THREAD_CALL_T will default to void (*)()*/
            #if defined(WINAPI)
                #define OMNI_THREAD_CALL_T WINAPI
            #else
                #define OMNI_THREAD_CALL_T
            #endif
            /* DEV_NOTE: we do not define __clrcall since we are not utilizing the CLR
            but you can define OMNI_THREAD_CALL_T to be such if you desire */
        #endif
    #endif
    
    // millisecond sleep functions
    #define OMNI_SLEEP_INIT() 
    #define OMNI_SLEEP1()  ::Sleep(1)
    #define OMNI_SLEEP(ms) ::Sleep(ms)
    #define OMNI_THREAD_YIELD() ::SwitchToThread()
#else
    #define OMNI_THREAD_HANDLE_T pthread_t
    #define OMNI_THREAD_T pthread_t
    #define OMNI_THREAD_RET_T void
    #define OMNI_THREAD_FNPTR_T void*
    /*
        These calling conventions are Windows specific and the 
        code where these macros are used will not make use of
        the __attribute__((Xcall)) compiler flag (especially
        since most of the code where this is being used is thread
        code). NOTE however that if you wish to, you can define
        OMNI_THREAD_CALL_T to be what you wish (__attribute__((std/fastcall/cdecl))
    */
    #if !defined(OMNI_THREAD_CALL_T)
        #if defined(OMNI_THREAD_STDCALL)
            #define OMNI_THREAD_CALL_T __attribute__((stdcall))
        #elif defined(OMNI_THREAD_FASTCALL)
            #define OMNI_THREAD_CALL_T __attribute__((fastcall))
        #elif defined(OMNI_THREAD_CDECL)
            #define OMNI_THREAD_CALL_T __attribute__((cdecl))
        #else
            #define OMNI_THREAD_CALL_T
        #endif
    #endif
    
    // millisecond sleep functions
    #define OMNI_SLEEP_INIT() struct timespec omni_stime; struct timespec omni_rtime; struct timespec* omni_ta[3] = { 0, &omni_stime, &omni_rtime }
    #define OMNI_SLEEP_WAIT_FW while ((::nanosleep(omni_ta[1], omni_ta[2]) == -1) && (errno == EINTR)) { omni_ta[0] = omni_ta[1]; omni_ta[1] = omni_ta[2]; omni_ta[2] = omni_ta[0]; }
    #define OMNI_SLEEP1()  omni_ta[1]->tv_sec = 0; omni_ta[1]->tv_nsec = 1000000; OMNI_SLEEP_WAIT_FW
    #define OMNI_SLEEP(ms) omni_ta[1]->tv_sec = ((ms < 1000) ? 0 : (ms/1000)); omni_ta[1]->tv_nsec = ((ms % 1000) * 1000000); OMNI_SLEEP_WAIT_FW
    #define OMNI_THREAD_YIELD() ::sched_yield()
#endif

#if !defined(OMNI_THREAD_ARGS_T)
    #if defined(OMNI_THREAD_ARGS_RAW_PTR)
        #define OMNI_THREAD_ARGS_T void*
        #define OMNI_THREAD_ARG_NULL_T OMNI_NULL
    #else
        #define OMNI_THREAD_ARGS_T omni::generic_ptr
    #define OMNI_THREAD_ARG_NULL_T omni::generic_ptr::null()
    #endif
#endif

#if defined(OMNI_THROW)
    #define OMNI_THREAD_TRY_FW try {
    #define OMNI_CBLOCK_FW \
        OMNI_DBGE("An unhandled exception occurred on the thread function."); \
        if (omni::sync::unhandled_thread_exception) { omni::sync::unhandled_thread_exception(); } \
        else { throw omni::exceptions::thread_exception("An unhandled exception occurred on the thread function."); }
    #define OMNI_CSXBLOCK_FW(ex) \
        OMNI_DBGEV("An exception occurred on the thread function: ", ex.what()); \
        if (omni::sync::unhandled_thread_exception) { omni::sync::unhandled_thread_exception(); } \
        else { throw omni::exceptions::thread_exception(ex.what()); }
    #define OMNI_CEXBLOCK_FW(ex) \
        OMNI_DBGEV("An exception occurred on the thread function: ", ex.what()); \
        if (omni::sync::user_thread_exception) { omni::sync::user_thread_exception(ex); } \
        else { throw ex; }
    #define OMNI_THREAD_CATCHEX_FW(ex) ex } \
        catch (omni::exception tex) { ex OMNI_CEXBLOCK_FW(tex) } \
        catch (std::exception sx) { ex OMNI_CSXBLOCK_FW(sx) } \
        catch (...) { ex OMNI_CBLOCK_FW }
    #define OMNI_THREAD_CATCH_FW } \
        catch (omni::exception ex) { OMNI_CEXBLOCK_FW(ex) } \
        catch (std::exception sx) { OMNI_CSXBLOCK_FW(sx) } \
        catch (...) { OMNI_CBLOCK_FW }    
#else
    #define OMNI_THREAD_TRY_FW 
    #define OMNI_THREAD_CATCHEX_FW(ex) ex
    #define OMNI_THREAD_CATCH_FW
#endif

#endif // OMNI_THREAD_DEF_HPP
