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
#if !defined(OMNI_CRYPTO_MD5_HPP)
#define OMNI_CRYPTO_MD5_HPP 1
#include <omni/types/crypto_t.hpp>

#if defined(OMNI_SAFE_MD5)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_MD5DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_MD5LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_MD5UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_MD5ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_MD5OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_MD5DMTX_FW
    #define OMNI_SAFE_MD5LOCK_FW
    #define OMNI_SAFE_MD5UNLOCK_FW
    #define OMNI_SAFE_MD5ALOCK_FW
    #define OMNI_SAFE_MD5OALOCK_FW(o) 
#endif

namespace omni {
    namespace crypto {
        class md5
        {
            public:
                md5();
                md5(const omni::crypto::md5& cp);
                OMNI_EXPLICIT md5(const std::string& hash);
                md5(const std::string& text, const omni::crypto::hash_type& type);
                ~md5();
                std::string hash_code() const;
                void swap(omni::crypto::md5& o);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                operator std::string() const { return this->to_string(); }
                operator std::wstring() const { return this->to_wstring(); }
                omni::crypto::md5& operator=(const omni::crypto::md5& other);
                bool operator==(const omni::crypto::md5& o) const;
                bool operator!=(const omni::crypto::md5& o) const;
                
                OMNI_MEMBERS_FW(omni::crypto::md5) // disposing,name,type(),hash()
                OMNI_OSTREAM_FW(omni::crypto::md5)

                static std::string compute_hash(const std::string& text);
                static std::string compute_file_hash(const std::string& file);
                static std::string compute_binary_file_hash(const std::string& file);

            private:
                std::string m_hash;
                #if defined(OMNI_SAFE_MD5)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
                
                void _compute(const std::string& text);
                void _compute(const unsigned char* data, uint32_t data_len);
                static void _update(const unsigned char* input, uint32_t length, uint32_t* count, uint8_t* buffer, uint32_t* state);
                static void _transform(const uint8_t* block, uint32_t* state);
                static uint32_t _rotate(uint32_t x, int n);
                static void _r1(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
                static void _r2(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
                static void _r3(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
                static void _r4(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
        };
    }
}

namespace std {
    inline void swap(omni::crypto::md5& o1, omni::crypto::md5& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_CRYPTO_MD5_HPP
