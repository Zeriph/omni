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
#include <omni/crypto/sha256.hpp>
#include <omni/defs/file_def.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#define OMNI_IO_FILE_EX_FW 1
#include <omni/xx/io/file_ex.hxx>

#if defined(OMNI_SAFE_SHA256)
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

#define OMNI_SHA2_SHFR_FW(x, n) (x >> n)
#define OMNI_SHA2_ROTR_FW(x, n) ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define OMNI_SHA2_ROTL_FW(x, n) ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define OMNI_SHA2_CH_FW(x, y, z) ((x & y) ^ (~x & z))
#define OMNI_SHA2_MAJ_FW(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define OMNI_SHA256_F1_FW(x) (OMNI_SHA2_ROTR_FW(x, 2) ^ OMNI_SHA2_ROTR_FW(x, 13) ^ OMNI_SHA2_ROTR_FW(x, 22))
#define OMNI_SHA256_F2_FW(x) (OMNI_SHA2_ROTR_FW(x, 6) ^ OMNI_SHA2_ROTR_FW(x, 11) ^ OMNI_SHA2_ROTR_FW(x, 25))
#define OMNI_SHA256_F3_FW(x) (OMNI_SHA2_ROTR_FW(x, 7) ^ OMNI_SHA2_ROTR_FW(x, 18) ^ OMNI_SHA2_SHFR_FW(x, 3))
#define OMNI_SHA256_F4_FW(x) (OMNI_SHA2_ROTR_FW(x, 17) ^ OMNI_SHA2_ROTR_FW(x, 19) ^ OMNI_SHA2_SHFR_FW(x, 10))
#define OMNI_SHA2_UNPACK32_FW(x, str) { *((str) + 3) = static_cast<uint8_t>((x)); *((str) + 2) = static_cast<uint8_t>((x) >> 8); *((str) + 1) = static_cast<uint8_t>((x) >> 16); *((str) + 0) = static_cast<uint8_t>((x) >> 24); }
#define OMNI_SHA2_PACK32_FW(str, x) { *(x) = (static_cast<uint32_t>(*((str) + 3))) | (static_cast<uint32_t>(*((str) + 2)) <<  8) | (static_cast<uint32_t>(*((str) + 1)) << 16) | (static_cast<uint32_t>(*((str) + 0)) << 24); }
#define OMNI_SHA2_DIGEST_SIZE_FW 32 // (256 / 8)
#define OMNI_SHA2_BLOCK_SIZE_FW 64 // (512 / 8)

namespace omni { namespace crypto { namespace sha256_internal {
    void transform(const unsigned char* message, uint32_t block_nb, uint32_t* hex_vals)
    {
        const uint32_t sha256_k[64] = {
            0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
            0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
            0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
            0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
            0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
            0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
            0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
            0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
            0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
            0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
            0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
            0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
            0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
            0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
            0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
            0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
        };
        uint32_t blkx[64];
        uint32_t blky[8];
        uint32_t t1, t2, i, j;
        const unsigned char* sub_block;
        for (i = 0; i < block_nb; ++i) {
            sub_block = message + (i << 6);
            for (j = 0; j < 16; ++j) {
                OMNI_SHA2_PACK32_FW(&sub_block[j << 2], &blkx[j]);
            }
            for (j = 16; j < 64; ++j) {
                blkx[j] = OMNI_SHA256_F4_FW(blkx[j -  2]) + blkx[j -  7] + OMNI_SHA256_F3_FW(blkx[j - 15]) + blkx[j - 16];
            }
            for (j = 0; j < 8; ++j) {
                blky[j] = hex_vals[j];
            }
            for (j = 0; j < 64; ++j) {
                t1 = blky[7] + OMNI_SHA256_F2_FW(blky[4]) + OMNI_SHA2_CH_FW(blky[4], blky[5], blky[6]) + sha256_k[j] + blkx[j];
                t2 = OMNI_SHA256_F1_FW(blky[0]) + OMNI_SHA2_MAJ_FW(blky[0], blky[1], blky[2]);
                blky[7] = blky[6]; blky[6] = blky[5]; blky[5] = blky[4];
                blky[4] = blky[3] + t1; blky[3] = blky[2]; blky[2] = blky[1];
                blky[1] = blky[0]; blky[0] = t1 + t2;
            }
            for (j = 0; j < 8; ++j) { hex_vals[j] += blky[j]; }
        }
    }
} } }

omni::crypto::sha256::sha256() :
    OMNI_CTOR_FW(omni::crypto::sha256)
    m_hash()
    OMNI_SAFE_SHA256DMTX_FW
{}

omni::crypto::sha256::sha256(const omni::crypto::sha256& cp) :
    OMNI_CPCTOR_FW(cp)
    m_hash(cp.m_hash)
    OMNI_SAFE_SHA256DMTX_FW
{}

OMNI_EXPLICIT omni::crypto::sha256::sha256(const std::string& hash) :
    OMNI_CTOR_FW(omni::crypto::sha256)
    m_hash(hash)
    OMNI_SAFE_SHA256DMTX_FW
{
}

omni::crypto::sha256::sha256(const std::string& text, const omni::crypto::hash_type& type) :
    OMNI_CTOR_FW(omni::crypto::sha256)
    m_hash()
    OMNI_SAFE_SHA256DMTX_FW
{
    if (type == omni::crypto::hash_type::STRING) {
        this->_compute(text);
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
            this->_compute(reinterpret_cast<const unsigned char*>(data), length);
            delete[] data;
        }
    }
}

omni::crypto::sha256::~sha256()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
}

std::string omni::crypto::sha256::hash_code() const
{
    return this->to_string();
}

void omni::crypto::sha256::swap(omni::crypto::sha256& o)
{
    if (this != &o) {
        OMNI_SAFE_SHA256ALOCK_FW
        OMNI_SAFE_SHA256OALOCK_FW(o)
        std::swap(this->m_hash, o.m_hash);
    }
}

omni::string_t omni::crypto::sha256::to_string_t() const
{
    OMNI_SAFE_SHA256ALOCK_FW
    return omni::string::util::to_string_t(this->m_hash);
}

std::string omni::crypto::sha256::to_string() const
{
    OMNI_SAFE_SHA256ALOCK_FW
    return this->m_hash;
}

std::wstring omni::crypto::sha256::to_wstring() const
{
    OMNI_SAFE_SHA256ALOCK_FW
    return omni::string::util::to_wstring(this->m_hash);
}

omni::crypto::sha256& omni::crypto::sha256::operator=(const omni::crypto::sha256& other)
{
    if (this != &other) {
        OMNI_SAFE_SHA256ALOCK_FW
        OMNI_SAFE_SHA256OALOCK_FW(other)
        this->m_hash = other.m_hash;
    }
    return *this;
}

bool omni::crypto::sha256::operator==(const omni::crypto::sha256& o) const
{
    if (this != &o) {
        OMNI_SAFE_SHA256ALOCK_FW
        OMNI_SAFE_SHA256OALOCK_FW(o)
        return this->m_hash == o.m_hash;
    }
    return true;
}

bool omni::crypto::sha256::operator!=(const omni::crypto::sha256& o) const
{
    return !(*this == o);
}

std::string omni::crypto::sha256::compute_hash(const std::string& text)
{
    omni::crypto::sha256 sha(text, omni::crypto::hash_type::STRING);
    return sha.m_hash;
}

std::string omni::crypto::sha256::compute_file_hash(const std::string& file)
{
    omni::crypto::sha256 sha(file, omni::crypto::hash_type::TEXT_FILE);
    return sha.m_hash;
}

std::string omni::crypto::sha256::compute_binary_file_hash(const std::string& file)
{
    omni::crypto::sha256 sha(file, omni::crypto::hash_type::BINARY_FILE);
    return sha.m_hash;
}

void omni::crypto::sha256::_compute(const std::string& text)
{
    this->_compute(reinterpret_cast<const unsigned char*>(text.c_str()), static_cast<uint32_t>(text.size()));
}

void omni::crypto::sha256::_compute(const unsigned char* message, uint32_t len)
{
    uint32_t block_nb, pm_len, len_b, i;
    uint32_t cur_len = 0;
    uint32_t tot_len = 0;
    uint32_t rem_len = 0;
    uint32_t tmp_len = 0;
    uint32_t hex_vals[8] = {
        0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
        0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
    };
    unsigned char data_block[2 * OMNI_SHA2_BLOCK_SIZE_FW];
    unsigned char digest[OMNI_SHA2_DIGEST_SIZE_FW];
    std::memset(digest, 0, sizeof(digest));

    tmp_len = OMNI_SHA2_BLOCK_SIZE_FW - cur_len;
    rem_len = len < tmp_len ? len : tmp_len;
    std::memcpy(&data_block[cur_len], message, rem_len);
    if (cur_len + len < OMNI_SHA2_BLOCK_SIZE_FW) {
        cur_len += len;
    } else {
        uint32_t new_len;
        const unsigned char* shifted_message;
        new_len = len - rem_len;
        block_nb = new_len / OMNI_SHA2_BLOCK_SIZE_FW;
        shifted_message = message + rem_len;
        omni::crypto::sha256_internal::transform(data_block, 1, hex_vals);
        omni::crypto::sha256_internal::transform(shifted_message, block_nb, hex_vals);
        rem_len = new_len % OMNI_SHA2_BLOCK_SIZE_FW;
        std::memcpy(data_block, &shifted_message[block_nb << 6], rem_len);
        cur_len = rem_len;
        tot_len += (block_nb + 1) << 6;
    }

    block_nb = (1 + ((OMNI_SHA2_BLOCK_SIZE_FW - 9) < (cur_len % OMNI_SHA2_BLOCK_SIZE_FW)));
    len_b = (tot_len + cur_len) << 3;
    pm_len = block_nb << 6;
    std::memset(data_block + cur_len, 0, pm_len - cur_len);
    data_block[cur_len] = 0x80;
    OMNI_SHA2_UNPACK32_FW(len_b, data_block + pm_len - 4);
    omni::crypto::sha256_internal::transform(data_block, block_nb, hex_vals);
    for (i = 0 ; i < 8; ++i) {
        OMNI_SHA2_UNPACK32_FW(hex_vals[i], &digest[i << 2]);
    }

    this->m_hash = omni::crypto::util::buffer_to_hex_string(digest);
}
