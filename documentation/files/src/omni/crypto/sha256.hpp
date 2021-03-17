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
#if !defined(OMNI_CRYPTO_SHA256_HPP)
#define OMNI_CRYPTO_SHA256_HPP 1
#include <omni/types/crypto_t.hpp>

#if defined(OMNI_SAFE_SHA256)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_SHA256DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_SHA256LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_SHA256UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_SHA256ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_SHA256OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_SHA256DMTX_FW
    #define OMNI_SAFE_SHA256LOCK_FW
    #define OMNI_SAFE_SHA256UNLOCK_FW
    #define OMNI_SAFE_SHA256ALOCK_FW
    #define OMNI_SAFE_SHA256OALOCK_FW(o) 
#endif

namespace omni {
    namespace crypto {
        class sha256
        {
            public:
                sha256();
                sha256(const omni::crypto::sha256& cp);
                OMNI_EXPLICIT sha256(const std::string& hash);
                sha256(const std::string& text, const omni::crypto::hash_type& type);
                ~sha256();
                std::string hash_code() const;
                void swap(omni::crypto::sha256& o);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;
                operator std::string() const { return this->to_string(); }
                operator std::wstring() const { return this->to_wstring(); }
                omni::crypto::sha256& operator=(const omni::crypto::sha256& other);
                bool operator==(const omni::crypto::sha256& o) const;
                bool operator!=(const omni::crypto::sha256& o) const;
                
                OMNI_MEMBERS_FW(omni::crypto::sha256) // disposing,name,type(),hash()
                OMNI_OSTREAM_FW(omni::crypto::sha256)

                static std::string compute_hash(const std::string& text);
                static std::string compute_file_hash(const std::string& file);
                static std::string compute_binary_file_hash(const std::string& file);
                
            private:
                std::string m_hash;
                #if defined(OMNI_SAFE_MD5)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                void _compute(const std::string& text);
                void _compute(const unsigned char* message, uint32_t len);
                static void _transform(const unsigned char* message, uint32_t block_nb, uint32_t* hex_vals);
        };
    }
}

namespace std {
    inline void swap(omni::crypto::sha256& o1, omni::crypto::sha256& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_CRYPTO_SHA256_HPP
