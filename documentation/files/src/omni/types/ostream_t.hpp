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

// helper macros used to define a friend function of a class that can be used to output to a stream

// DEV_NOTE: the variadic macro's are to capture all values passed even with comma's, e.g. OMNI_OSTREAM_OPERATOR(some_class<X, Y, Z>)
// will pass the whole X,Y,Z instead of splitting it and passing 'some_class<X' then 'Y' and 'Z'.

#define OMNI_FOSTREAM_OPC_FW(v, ...) friend std::ostream& operator<<(std::ostream& _s, const __VA_ARGS__& _c) { _s << _c.v; return _s; }
#define OMNI_FOSTREAM_OPW_FW(v, ...) friend std::wostream& operator<<(std::wostream& _s, const __VA_ARGS__& _c) { _s << _c.v; return _s; }

#define OMNI_FOSTREAM_OPC_FN_FW(fn, ...) friend std::ostream& operator<<(std::ostream& _s, const __VA_ARGS__& _c) { _s << fn(_c); return _s; }
#define OMNI_FOSTREAM_OPW_FN_FW(fn, ...) friend std::wostream& operator<<(std::wostream& _s, const __VA_ARGS__& _c) { _s << fn(_c); return _s; }

#define OMNI_FOSTREAM_OPC2T_FW(v, ...) friend std::ostream& operator<<(std::ostream& _s, const __VA_ARGS__& _c) { _s << omni::string::util::to_string(_c.v); return _s; }
#define OMNI_FOSTREAM_OPW2T_FW(v, ...) friend std::wostream& operator<<(std::wostream& _s, const __VA_ARGS__& _c) { _s << omni::string::util::to_wstring(_c.v); return _s; }

#define OMNI_FOSTREAM_OPS_FW(v, ...) friend omni::ostream_t& operator<<(omni::ostream_t& _s, const __VA_ARGS__& _c) { _s << omni::string::util::to_string_t(_c.v); return _s; }

#define OMNI_OSTREAM_OPC_FW(v, ...) std::ostream& operator<<(std::ostream& _s, const __VA_ARGS__& _c) { s << c.v; return s; }
#define OMNI_OSTREAM_OPW_FW(v, ...) std::wostream& operator<<(std::wostream& _s, const __VA_ARGS__& _c) { s << c.v; return s; }

#define OMNI_OSTREAM_OPC2T_FW(v, ...) std::ostream& operator<<(std::ostream& _s, const __VA_ARGS__& _c) { s << omni::string::util::to_string(c.v); return s; }
#define OMNI_OSTREAM_OPW2T_FW(v, ...) std::wostream& operator<<(std::wostream& _s, const __VA_ARGS__& _c) { s << omni::string::util::to_wstring(c.v); return s; }

#define OMNI_OSTREAM_OPS_FW(v, ...) omni::ostream_t& operator<<(omni::ostream_t& _s, const __VA_ARGS__& _c) { s << omni::string::util::to_string_t(c.v); return s; }

#define OMNI_OSTREAM_OPERATOR(v, ...) OMNI_FOSTREAM_OPC_FW(v, __VA_ARGS__)
#define OMNI_WOSTREAM_OPERATOR(v, ...) OMNI_FOSTREAM_OPW_FW(v, __VA_ARGS__)

#define OMNI_OSTREAM_FN_OPERATOR(fn, ...) OMNI_FOSTREAM_OPC_FN_FW(fn, __VA_ARGS__)
#define OMNI_WOSTREAM_FN_OPERATOR(fn, ...) OMNI_FOSTREAM_OPW_FN_FW(fn, __VA_ARGS__)

#define OMNI_STREAM_OPERATORS(v, ...) OMNI_OSTREAM_OPERATOR(v, __VA_ARGS__) OMNI_WOSTREAM_OPERATOR(v, __VA_ARGS__)
#define OMNI_STREAM_FN_OPERATORS(v, ...) OMNI_OSTREAM_FN_OPERATOR(v, __VA_ARGS__) OMNI_WOSTREAM_FN_OPERATOR(v, __VA_ARGS__)

namespace omni {
    typedef OMNI_OSTREAM_T ostream_t;
    typedef OMNI_ISTREAM_T istream_t;
}

#endif // OMNI_OSTREAM_T_HPP
