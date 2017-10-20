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
#include <omni/chrono/tick.hpp>
OMNI_CLOCK_FREQ_T omni::chrono::monotonic::m_freq;

#if defined(OMNI_THROW)
    #include <omni/types/thread_t.hpp>
    omni::action omni::sync::unhandled_thread_exception;
    omni::event1<void, const omni::exception&> omni::sync::user_thread_exception;
#endif

// default of having the constants be externally linked
#if !defined(OMNI_NO_EXTERN_CONSTS)
    #if !defined(OMNI_NO_CSTRING_IMPL) // define this if you only want omni::wconsts header
        #include <omni/consts/cconsts.hpp>
        #define OMNI_CHAR_T_FW char
        #define OMNI_STRW_FW(v) v
        #define OMNI_EXT_NS_FW omni::cconsts
        #include <omni/xx/ext_const.hxx>
        #undef OMNI_CHAR_T_FW
        #undef OMNI_STRW_FW
        #undef OMNI_EXT_NS_FW
    #endif
    #if !defined(OMNI_NO_WSTRING_IMPL) // define this if you only want omni::cconsts header
        #include <omni/consts/wconsts.hpp>
        #define OMNI_CHAR_T_FW wchar_t
        //#define OMNI_STRW_FW(v) L##v
        #define OMNI_STRW_FW(v) OMNI_WSTR(v)
        #define OMNI_EXT_NS_FW omni::wconsts
        #include <omni/xx/ext_const.hxx>
        #undef OMNI_CHAR_T_FW
        #undef OMNI_STRW_FW
        #undef OMNI_EXT_NS_FW
    #endif
#endif

// define OMNI_COMPILE_FLAGS if you want the compile time constant values built into the framework 
#if defined(OMNI_COMPILE_FLAGS)
    #include <omni/xx/compile_flags.hxx>
#endif // OMNI_COMPILE_FLAGS
