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
#if !defined(OMNI_OSTREAM_HPP)
#define OMNI_OSTREAM_HPP 1
#include <omni/types/ostream_t.hpp>

#if defined(OMNI_UNICODE)
    #define OMNI_CERR_FW std::wcerr    
    #define OMNI_CIN_FW std::wcin
    #define OMNI_CLOG_FW std::wclog
    #define OMNI_COUT_FW std::wcout
#else
    #define OMNI_CERR_FW std::cerr
    #define OMNI_CIN_FW std::cin
    #define OMNI_CLOG_FW std::clog
    #define OMNI_COUT_FW std::cout
#endif

namespace omni {
    static OMNI_OSTREAM_T& err = OMNI_CERR_FW;
    static OMNI_ISTREAM_T& in = OMNI_CIN_FW;
    static OMNI_OSTREAM_T& log = OMNI_CLOG_FW;
    static OMNI_OSTREAM_T& out = OMNI_COUT_FW;
} // namespace omni

#undef OMNI_CERR_FW
#undef OMNI_CIN_FW
#undef OMNI_CLOG_FW
#undef OMNI_COUT_FW

#endif // OMNI_OSTREAM_HPP
