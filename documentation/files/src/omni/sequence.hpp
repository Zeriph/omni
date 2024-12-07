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
#if !defined(OMNI_SEQUENCE_HPP)
#define OMNI_SEQUENCE_HPP 1
#include <omni/defs/global.hpp>
#include <omni/types/seq_t.hpp>
#include <omni/types/string_t.hpp>

namespace omni {
    namespace sequence {
        typedef omni_sequence_t<omni::string_t> string_t;
        typedef omni_sequence_t<std::string> std_string_t;
        typedef omni_sequence_t<std::wstring> std_wstring_t;
        typedef omni_sequence_t<char> char_t;
        typedef omni_sequence_t<wchar_t> wide_char_t;
        typedef omni_sequence_t<short> short_t;
        typedef omni_sequence_t<int> int_t;
        typedef omni_sequence_t<long> long_t;
        typedef omni_sequence_t<double> double_t;
        typedef omni_sequence_t<float> float_t;
        typedef omni_sequence_t<int8_t> int8_t;
        typedef omni_sequence_t<int16_t> int16_t;
        typedef omni_sequence_t<int32_t> int32_t;
        typedef omni_sequence_t<int64_t> int64_t;
        typedef omni_sequence_t<unsigned char> uchar_t;
        typedef omni_sequence_t<unsigned short> ushort_t;
        typedef omni_sequence_t<unsigned int> uint_t;
        typedef omni_sequence_t<unsigned long> ulong_t;
        typedef omni_sequence_t<uint8_t> uint8_t;
        typedef omni_sequence_t<uint16_t> uint16_t;
        typedef omni_sequence_t<uint32_t> uint32_t;
        typedef omni_sequence_t<uint64_t> uint64_t;
    }

    namespace seq = omni::sequence;
}

#endif // OMNI_SEQUENCE_HPP
