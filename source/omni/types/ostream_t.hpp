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
#if !defined(OMNI_OSTREAM_T_HPP)
#define OMNI_OSTREAM_T_HPP 1
#include <omni/defs/global.hpp>
#include <iostream>

#if defined(OMNI_UNICODE)
    #define OMNI_OSTREAM_T std::wostream
    #define OMNI_ISTREAM_T std::wistream
#else
    #define OMNI_OSTREAM_T std::ostream
    #define OMNI_ISTREAM_T std::istream
#endif

#if !defined(OMNI_NO_PRINTL)
    #define println(v) std::cout << v << std::endl
    #define printwln(v) std::wcout << v << std::endl
#endif

/* helper macros used to define a friend function of a class that can be used to 'output' to a stream
 friend ostream<< to write to std::ostream/std::wostream. Use if you include <omni/ostream.hpp> in the class header
*/
#define OMNI_FOSTREAM_OPC_FW(cls, v) friend std::ostream& operator<<(std::ostream& s, const cls& c) { s << c.v; return s; }
#define OMNI_FOSTREAM_OPW_FW(cls, v) friend std::wostream& operator<<(std::wostream& s, const cls& c) { s << c.v; return s; }

#define OMNI_FOSTREAM_OPC2T_FW(cls, v) friend std::ostream& operator<<(std::ostream& s, const cls& c) { s << omni::string::util::to_string(c.v); return s; }
#define OMNI_FOSTREAM_OPW2T_FW(cls, v) friend std::wostream& operator<<(std::wostream& s, const cls& c) { s << omni::string::util::to_wstring(c.v); return s; }

#define OMNI_FOSTREAM_OPS_FW(cls, v) friend omni::ostream_t& operator<<(omni::ostream_t& s, const cls& c) { s << omni::string::util::to_string_t(c.v); return s; }

#define OMNI_OSTREAM_OPC_FW(cls, v) std::ostream& operator<<(std::ostream& s, const cls& c) { s << c.v; return s; }
#define OMNI_OSTREAM_OPW_FW(cls, v) std::wostream& operator<<(std::wostream& s, const cls& c) { s << c.v; return s; }

#define OMNI_OSTREAM_OPC2T_FW(cls, v) std::ostream& operator<<(std::ostream& s, const cls& c) { s << omni::string::util::to_string(c.v); return s; }
#define OMNI_OSTREAM_OPW2T_FW(cls, v) std::wostream& operator<<(std::wostream& s, const cls& c) { s << omni::string::util::to_wstring(c.v); return s; }

#define OMNI_OSTREAM_OPS_FW(cls, v) omni::ostream_t& operator<<(omni::ostream_t& s, const cls& c) { s << omni::string::util::to_string_t(c.v); return s; }

#define OMNI_OSTREAM_OPERATOR(cls, v) OMNI_FOSTREAM_OPC_FW(cls, v)
#define OMNI_WOSTREAM_OPERATOR(cls, v) OMNI_FOSTREAM_OPW_FW(cls, v)
#define OMNI_STREAM_OPERATORS(cls, v) OMNI_OSTREAM_OPERATOR(cls, v) OMNI_WOSTREAM_OPERATOR(cls, v)

namespace omni {
    /**
     * Defines the underlying std::ostream type;
     * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
     */
    typedef OMNI_OSTREAM_T ostream_t;
    /**
     * Defines the underlying std::istream type;
     * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
     */
    typedef OMNI_ISTREAM_T istream_t;
}

#endif // OMNI_OSTREAM_T_HPP
