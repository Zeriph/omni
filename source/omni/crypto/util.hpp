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
            template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            inline bool string_to_hex(const std::string& hash, std_seq_t<T, std_allocator_t>& out)
            {
                if (hash.size() % 2 == 0) {
                    std::string sub;
                    for (size_t i = 0; i < hash.size(); i += 2) {
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
