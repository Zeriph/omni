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
#if !defined(OMNI_CRYPTO_UTIL_HPP)
#define OMNI_CRYPTO_UTIL_HPP 1
#include <omni/types/crypto_t.hpp>
#include <omni/types/seq_t.hpp>

namespace omni {
    namespace crypto {
        namespace util
        {
            template < typename T, std::size_t SZ >
            inline std::string buffer_to_hex_string(T (&buffer)[SZ])
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < SZ; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << buffer[i];
                }
                return ss.str();
            }

            template < typename T, std::size_t SZ >
            inline std::string buffer_to_hex_string(T (&buffer)[SZ], uint32_t mask)
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < SZ; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << (buffer[i] & mask);
                }
                return ss.str();
            }

            template < typename T >
            inline std::string buffer_to_hex_string(const T *const buffer, std::size_t buffer_sz)
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < buffer_sz; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << buffer[i];
                }
                return ss.str();
            }

            template < typename T >
            inline std::string buffer_to_hex_string(const T *const buffer, std::size_t buffer_sz, uint32_t mask)
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < buffer_sz; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << (buffer[i] & mask);
                }
                return ss.str();
            }

            template < std::size_t SZ >
            inline std::string buffer_to_hex_string(unsigned char (&buffer)[SZ])
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < SZ; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(unsigned char) * 2) << std::hex << static_cast<uint32_t>(buffer[i]);
                }
                return ss.str();
            }

            template <>
            inline std::string buffer_to_hex_string<unsigned char>(const unsigned char *const buffer, std::size_t buffer_sz)
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < buffer_sz; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(unsigned char) * 2) << std::hex << static_cast<uint32_t>(buffer[i]);
                }
                return ss.str();
            }

            template <>
            inline std::string buffer_to_hex_string<unsigned char>(const unsigned char *const buffer, std::size_t buffer_sz, uint32_t mask)
            {
                std::ostringstream ss;
                for (std::size_t i = 0; i < buffer_sz; ++i) {
                    ss << std::setfill('0') << std::setw(sizeof(unsigned char) * 2) << std::hex << (static_cast<uint32_t>(buffer[i]) & mask);
                }
                return ss.str();
            }

            template < typename T >
            inline T rotate_left(T x, uint8_t n)
            {
                if (n > (sizeof(T) * 8)) {
                    OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid rotation"), 0)
                }
                return ((x << n) | (x >> ((sizeof(T) * 8) - n)));
            }

            template < typename T >
            inline T rotate_right(T x, uint8_t n)
            {
                if (n > (sizeof(T) * 8)) {
                    OMNI_ERR_RETV_FW(OMNI_OVERFLOW_STR, omni::exceptions::overflow_error("invalid rotation"), 0)
                }
                return ((x >> n) | (x << ((sizeof(T) * 8) - n)));
            }

            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            inline bool string_to_hex(const std::string& hash, std_seq_t<T, std_allocator_t>& out)
            {
                if (hash.size() % 2 == 0) {
                    std::string sub;
                    for (std::size_t i = 0; i < hash.size(); i += 2) {
                        sub = hash.substr(i, 2);
                        if (!omni::char_util::is_hex(sub[0]) || !omni::char_util::is_hex(sub[1])) {
                            return false;
                        }
                        out.push_back(static_cast<T>(std::strtoul(sub.c_str(), NULL, 16)));
                    }
                    return true;
                }
                return false;
            }

            template < template < class, class > class std_seq_t, class T >
            inline bool string_to_hex(const std::string& hash, std_seq_t<T, std::allocator<T> >& out)
            {
                return omni::crypto::util::string_to_hex< std_seq_t, T, std::allocator<T> >(hash, out);
            }

            template < template < class, class > class std_seq_t >
            inline bool string_to_hex(const std::string& hash, std_seq_t<uint8_t, std::allocator<uint8_t> >& out)
            {
                return omni::crypto::util::string_to_hex< std_seq_t, uint8_t >(hash, out);
            }

            inline bool string_to_hex(const std::string& hash, omni_seq_t<uint8_t>& out)
            {
                return omni::crypto::util::string_to_hex< omni_seq_t, uint8_t >(hash, out);
            }
        }
    }
}

#endif // OMNI_CRYPTO_SHA1_HPP
