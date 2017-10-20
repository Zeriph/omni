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
#if !defined(OMNI_CONSTANTS_HPP)
#define OMNI_CONSTANTS_HPP
#include <omni/defs/global.hpp>

#if !defined(OMNI_NO_CSTRING_IMPL) // define this if you only want omni::wconsts header
    #include <omni/consts/cconsts.hpp>
#endif
#if !defined(OMNI_NO_WSTRING_IMPL) // define this if you only want omni::cconsts header
    #include <omni/consts/wconsts.hpp>
#endif

#if defined(OMNI_UNICODE) && !defined(OMNI_NO_WSTRING_IMPL)
    #define OMNI_CONSTS_NS_FW omni::wconsts
#else
    #define OMNI_CONSTS_NS_FW omni::cconsts
#endif

namespace omni {
    namespace consts {
        namespace err = OMNI_CONSTS_NS_FW::err;
        namespace misc = OMNI_CONSTS_NS_FW::misc;
        namespace sz {
            namespace bin {
                namespace str = OMNI_CONSTS_NS_FW::sz::bin::str;
                const unsigned int KB = OMNI_KIB_IVAL;
                const unsigned int MB = OMNI_MIB_IVAL;
                const std::size_t GB = OMNI_GIB_IVAL;
            }
            namespace dec {
                namespace str = OMNI_CONSTS_NS_FW::sz::dec::str;
                const unsigned int KB = OMNI_KB_IVAL; 
                const unsigned int MB = OMNI_MB_IVAL;
                const std::size_t GB = OMNI_GB_IVAL;
            }
        }
    }
}

#undef OMNI_CONSTS_NS_FW

#endif // OMNI_CONSTANTS_HPP
