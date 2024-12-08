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
#include <omni/crypto/md5.hpp>
#include <omni/crypto/util.hpp>
#include <omni/defs/file_def.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#define OMNI_IO_FILE_EX_FW 1
#include <omni/xx/io/file_ex.hxx>

#if defined(OMNI_SAFE_MD5)
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

// standard MD5 bit-twiddling functions
#define OMNI_MD5_F_FW(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define OMNI_MD5_G_FW(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define OMNI_MD5_H_FW(x, y, z) ((x) ^ (y) ^ (z))
#define OMNI_MD5_I_FW(x, y, z) ((y) ^ ((x) | (~z)))

namespace omni { namespace crypto { namespace md5_internal {
    void transform (const unsigned char* block, uint32_t* state)
    {
        const uint32_t transform_magic[64] = {
            0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE,
            0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
            0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE,
            0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,
            0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA,
            0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
            0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED,
            0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,
            0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C,
            0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
            0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05,
            0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
            0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039,
            0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
            0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1,
            0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391
        };
        const int8_t s1[4] = {  7, 12, 17, 22 };
        const int8_t s2[4] = {  5,  9, 14, 20 };
        const int8_t s3[4] = {  4, 11, 16, 23 };
        const int8_t s4[4] = {  6, 10, 15, 21 };
        const uint32_t* x = reinterpret_cast<const uint32_t*>(block);
        std::size_t i, j;
        uint32_t a, b, c, d, tmp;
        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        // Round 1
        for (i = 0; i < 16; ++i) {
            tmp = a + OMNI_MD5_F_FW(b, c, d) + (x[i]) + transform_magic[i];
            tmp = omni::crypto::util::rotate_left(tmp, static_cast<uint8_t>(s1[i & 3]));
            tmp += b;
            a = d; d = c; c = b; b = tmp;
        }
        // Round 2
        for (i = 0, j = 1; i < 16; ++i, j += 5) {
            tmp = a + OMNI_MD5_G_FW(b, c, d) + (x[j & 15]) + transform_magic[i+16];
            tmp = omni::crypto::util::rotate_left(tmp, static_cast<uint8_t>(s2[i & 3]));
            tmp += b;
            a = d; d = c; c = b; b = tmp;
        }
        // Round 3
        for (i = 0, j = 5; i < 16; ++i, j += 3) {
            tmp = a + OMNI_MD5_H_FW(b, c, d) + (x[j & 15]) + transform_magic[i+32];
            tmp = omni::crypto::util::rotate_left(tmp, static_cast<uint8_t>(s3[i & 3]));
            tmp += b;
            a = d; d = c; c = b; b = tmp;
        }
        // Round 4
        for (i = 0, j = 0; i < 16; ++i, j += 7) {
            tmp = a + OMNI_MD5_I_FW(b, c, d) + (x[j & 15]) + transform_magic[i+48];
            tmp = omni::crypto::util::rotate_left(tmp, static_cast<uint8_t>(s4[i & 3]));
            tmp += b;
            a = d; d = c; c = b; b = tmp;
        }
        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
    }
    std::string compute(const unsigned char* data, uint32_t data_len)
    {
        uint32_t state[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
        unsigned char buffer[64] =  {0};
        uint32_t length = 0;
        uint32_t buflen = length & 63;
        length += data_len;
        if (buflen + data_len < 64)  {
            std::memcpy(buffer + buflen, data, data_len);
            buflen += data_len;
        } else {
            std::memcpy(buffer + buflen, data, 64 - buflen);
            omni::crypto::md5_internal::transform(buffer, state);
            data += 64 - buflen;
            data_len -= 64 - buflen;
            while (data_len >= 64) {
                omni::crypto::md5_internal::transform(data, state);
                data += 64;
                data_len -= 64;
            }
            std::memcpy(buffer, data, data_len);
            buflen = data_len;
        }
        buflen = length & 63;
        buffer[buflen++] = 0x80;
        std::memset(buffer+buflen, 0, 64 - buflen);
        if (buflen > 56) {
            omni::crypto::md5_internal::transform(buffer, state);
            std::memset(buffer, 0, 64);
            buflen = 0;
        }
        *(reinterpret_cast<uint32_t *>(buffer + 56)) = (8 * length);
        *(reinterpret_cast<uint32_t *>(buffer + 60)) = 0;
        omni::crypto::md5_internal::transform(buffer, state);

        unsigned char* digest = reinterpret_cast<unsigned char *>(state);
        return omni::crypto::util::buffer_to_hex_string(digest, 16);
    }
    inline std::string compute(const std::string& text)
    {
        return omni::crypto::md5_internal::compute(reinterpret_cast<const unsigned char*>(text.c_str()), static_cast<uint32_t>(text.length()));
    }
} } }

omni::crypto::md5::md5() :
    OMNI_CTOR_FW(omni::crypto::md5)
    m_hash()
    OMNI_SAFE_MD5DMTX_FW
{}

omni::crypto::md5::md5(const omni::crypto::md5& cp) :
    OMNI_CPCTOR_FW(cp)
    m_hash(cp.m_hash)
    OMNI_SAFE_MD5DMTX_FW
{}

OMNI_EXPLICIT omni::crypto::md5::md5(const std::string& hash) :
    OMNI_CTOR_FW(omni::crypto::md5)
    m_hash(hash)
    OMNI_SAFE_MD5DMTX_FW
{
}

omni::crypto::md5::md5(const std::string& text, const omni::crypto::hash_type& type) :
    OMNI_CTOR_FW(omni::crypto::md5)
    m_hash()
    OMNI_SAFE_MD5DMTX_FW
{
    if (type == omni::crypto::hash_type::STRING) {
        this->m_hash = omni::crypto::md5_internal::compute(text);
    } else {
        if (!omni::io::file_internal::exists(text)) {
            OMNI_ERRV_FW("File not found: ", text, omni::exceptions::file_not_found(text))
        }
        std::ifstream ifile;
        if (type == omni::crypto::hash_type::BINARY_FILE) {
            ifile.open(text.c_str(), std::ios::binary);
        } else {
            ifile.open(text.c_str());
        }
        ifile.seekg(0, ifile.end);
        uint32_t length = static_cast<uint32_t>(ifile.tellg());
        ifile.seekg(0, ifile.beg);
        if (length > 0) {
            char* data = new char[length];
            ifile.read(data, length);
            ifile.close();
            this->m_hash = omni::crypto::md5_internal::compute(reinterpret_cast<const unsigned char*>(data), length);
            delete[] data;
        }
    }
}

omni::crypto::md5::~md5()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
}

std::string omni::crypto::md5::hash_code() const
{
    return this->to_string();
}

void omni::crypto::md5::swap(omni::crypto::md5& o)
{
    if (this != &o) {
        OMNI_SAFE_MD5ALOCK_FW
        OMNI_SAFE_MD5OALOCK_FW(o)
        std::swap(this->m_hash, o.m_hash);
    }
}

omni::string_t omni::crypto::md5::to_string_t() const
{
    OMNI_SAFE_MD5ALOCK_FW
    return omni::string::util::to_string_t(this->m_hash);
}

std::string omni::crypto::md5::to_string() const
{
    OMNI_SAFE_MD5ALOCK_FW
    return this->m_hash;
}

std::wstring omni::crypto::md5::to_wstring() const
{
    OMNI_SAFE_MD5ALOCK_FW
    return omni::string::util::to_wstring(this->m_hash);
}

omni::crypto::md5& omni::crypto::md5::operator=(const omni::crypto::md5& other)
{
    if (this != &other) {
        OMNI_SAFE_MD5ALOCK_FW
        OMNI_SAFE_MD5OALOCK_FW(other)
        this->m_hash = other.m_hash;
    }
    return *this;
}

bool omni::crypto::md5::operator==(const omni::crypto::md5& o) const
{
    if (this != &o) {
        OMNI_SAFE_MD5ALOCK_FW
        OMNI_SAFE_MD5OALOCK_FW(o)
        return this->m_hash == o.m_hash;
    }
    return true;
}

bool omni::crypto::md5::operator!=(const omni::crypto::md5& o) const
{
    return !(*this == o);
}

std::string omni::crypto::md5::compute_hash(const std::string& text)
{
    omni::crypto::md5 md5(text, omni::crypto::hash_type::STRING);
    return md5.m_hash;
}

std::string omni::crypto::md5::compute_file_hash(const std::string& file)
{
    omni::crypto::md5 md5(file, omni::crypto::hash_type::TEXT_FILE);
    return md5.m_hash;
}

std::string omni::crypto::md5::compute_binary_file_hash(const std::string& file)
{
    omni::crypto::md5 md5(file, omni::crypto::hash_type::BINARY_FILE);
    return md5.m_hash;
}
