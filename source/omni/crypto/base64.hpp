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
#if !defined(OMNI_CRYPTO_BASE64_HPP)
#define OMNI_CRYPTO_BASE64_HPP 1

#include <omni/types/char_t.hpp>

namespace omni {
    namespace crypto {
        namespace base64 {
            #if !defined(OMNI_NO_EXTERN_CONSTS)
                extern const char *const CHARS[2];
            #else
                const char *const CHARS[] = OMNI_CRYPTO_BASE64_CHARS;
            #endif
            
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            inline void decode(const std::string& data, std_seq_t<T, std_allocator_t >& out_buff)
            {
                if (!data.empty()) {
                    size_t pos1, pos1a, pos2, pos2a;
                    for (size_t pos = 0; pos < data.size(); pos += 4) {
                        OMNI_CYRPTO_BASE64_CHAR_POS((data[pos+1]), pos1)
                        OMNI_CYRPTO_BASE64_CHAR_POS((data[pos+0]), pos1a)
                        out_buff.push_back(static_cast<T>((pos1a << 2) + ((pos1 & 0x30) >> 4)));
                        if (((pos + 2) < data.size()) && (data[pos+2] != '=') && (data[pos+2] != '.')) {
                            OMNI_CYRPTO_BASE64_CHAR_POS((data[pos+2]), pos2)
                            out_buff.push_back(static_cast<T>(((pos1 & 0x0F) << 4) + ((pos2 & 0x3C) >> 2)));
                            if (((pos + 3) < data.size()) && (data[pos+3] != '=') && (data[pos+3] != '.')) {
                                OMNI_CYRPTO_BASE64_CHAR_POS((data[pos+3]), pos2a)
                                out_buff.push_back(static_cast<T>(((pos2 & 0x03) << 6) + pos2a));
                            }
                        }
                    }
                }
            }

            inline omni_seq_t<uint8_t> decode(const std::string& data)
            {
                omni_seq_t<uint8_t> buff;
                omni::crypto::base64::decode(data, buff);
                return buff;
            }

            inline std::string encode(unsigned char const* data, size_t size, bool url)
            {
                if ((data == OMNI_NULL) || (size == 0)) {
                    return std::string();
                }
                unsigned char end = url ? '.' : '=';
                std::string ret;
                ret.reserve((((size +2) / 3) * 4));
                for (size_t pos = 0; pos < size; pos += 3) {
                    ret.push_back(omni::crypto::base64::CHARS[url][(data[pos] & 0xFC) >> 2]);
                    if ((pos + 1) < size) {
                        ret.push_back(omni::crypto::base64::CHARS[url][(((data[pos] & 0x03) << 4) + ((data[(pos + 1)] & 0xF0) >> 4))]);
                        if ((pos + 2) < size) {
                            ret.push_back(omni::crypto::base64::CHARS[url][(((data[(pos + 1)] & 0x0F) << 2) + ((data[(pos + 2)] & 0xC0) >> 6))]);
                            ret.push_back(omni::crypto::base64::CHARS[url][(data[(pos + 2)] & 0x3F)]);
                        } else {
                            ret.push_back(omni::crypto::base64::CHARS[url][((data[pos + 1] & 0x0F) << 2)]);
                            ret.push_back(end);
                        }
                    } else {
                        ret.push_back(omni::crypto::base64::CHARS[url][((data[(pos + 0)] & 0x03) << 4)]);
                        ret.push_back(end);
                        ret.push_back(end);
                    }
                }
                return ret;
            }

            inline std::string encode(unsigned char const* data, size_t size)
            {
                return omni::crypto::base64::encode(data, size, false);
            }

            inline std::string encode(const std::string& data, bool url)
            {
                return omni::crypto::base64::encode(reinterpret_cast<const unsigned char*>(data.data()), data.size(), url);
            }

            inline std::string encode(const std::string& data)
            {
                return omni::crypto::base64::encode(reinterpret_cast<const unsigned char*>(data.data()), data.size(), false);
            }
        }
    }
}

#endif // OMNI_CRYPTO_BASE64_HPP
