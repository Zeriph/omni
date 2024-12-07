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
#if !defined(OMNI_CRYPTO_SHA1_HPP)
#define OMNI_CRYPTO_SHA1_HPP 1
#include <omni/types/crypto_t.hpp>
#if defined(OMNI_SAFE_SHA1)
    #include <omni/sync/basic_lock.hpp>
#endif

namespace omni {
    namespace crypto {
        class sha1
        {
            public:
                sha1();
                sha1(const omni::crypto::sha1& cp);
                OMNI_EXPLICIT sha1(const std::string& hash);
                sha1(const std::string& text, const omni::crypto::hash_type& type);
                ~sha1();
                std::string hash_code() const;
                void swap(omni::crypto::sha1& o);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                operator std::string() const { return this->to_string(); }
                operator std::wstring() const { return this->to_wstring(); }
                omni::crypto::sha1& operator=(const omni::crypto::sha1& other);
                bool operator==(const omni::crypto::sha1& o) const;
                bool operator!=(const omni::crypto::sha1& o) const;
                
                OMNI_MEMBERS_FW(omni::crypto::sha1) // disposing,name,type(),hash()
                OMNI_OSTREAM_FW(omni::crypto::sha1)

                static std::string compute_hash(const std::string& text);
                static std::string compute_file_hash(const std::string& file);
                static std::string compute_binary_file_hash(const std::string& file);

            private:
                std::string m_hash;
                #if defined(OMNI_SAFE_SHA1)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                void _compute(std::istream& stream);
        };
    }
}

namespace std {
    inline void swap(omni::crypto::sha1& o1, omni::crypto::sha1& o2)
    {
        o1.swap(o2);
    }
}
#endif // OMNI_CRYPTO_SHA1_HPP
