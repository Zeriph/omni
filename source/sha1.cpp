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
#include <omni/crypto/sha1.hpp>
#include <omni/defs/file_def.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#define OMNI_IO_FILE_EX_FW 1
#include <omni/xx/io/file_ex.hxx>

#if defined(OMNI_SAFE_SHA1)
    #define OMNI_SAFE_SHA1DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_SHA1LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_SHA1UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_SHA1ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_SHA1OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_SHA1DMTX_FW
    #define OMNI_SAFE_SHA1LOCK_FW
    #define OMNI_SAFE_SHA1UNLOCK_FW
    #define OMNI_SAFE_SHA1ALOCK_FW
    #define OMNI_SAFE_SHA1OALOCK_FW(o) 
#endif

#define OMNI_SHA1_R_FW(value, bits) (((value) << (bits)) | (((value) & 0xFFFFFFFF) >> (32 - (bits))))
#define OMNI_SHA1_B_FW(i) (block[i & 15] = OMNI_SHA1_R_FW(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i & 15], 1))
#define OMNI_SHA1_R0_FW(v, w, x, y, z, i) z += ((w & (x ^ y)) ^ y) + block[i] + 0x5A827999 + OMNI_SHA1_R_FW(v, 5); w = OMNI_SHA1_R_FW(w, 30);
#define OMNI_SHA1_R1_FW(v, w, x, y, z, i) z += ((w & (x ^ y)) ^ y) + OMNI_SHA1_B_FW(i) + 0x5A827999 + OMNI_SHA1_R_FW(v, 5); w = OMNI_SHA1_R_FW(w, 30);
#define OMNI_SHA1_R2_FW(v, w, x, y, z, i) z += (w ^ x ^ y) + OMNI_SHA1_B_FW(i) + 0x6ED9EBA1 + OMNI_SHA1_R_FW(v,5); w = OMNI_SHA1_R_FW(w, 30);
#define OMNI_SHA1_R3_FW(v, w, x, y, z, i) z += (((w | x) & y) | (w & x)) + OMNI_SHA1_B_FW(i) + 0x8F1BBCDC + OMNI_SHA1_R_FW(v, 5); w = OMNI_SHA1_R_FW(w, 30);
#define OMNI_SHA1_R4_FW(v, w, x, y, z, i) z += (w ^ x ^ y) + OMNI_SHA1_B_FW(i) + 0xCA62C1D6 + OMNI_SHA1_R_FW(v, 5); w = OMNI_SHA1_R_FW(w, 30);
#define OMNI_SHA1_DIGEST_SZ_FW 5
#define OMNI_SHA1_BLOCK_SZ_FW 16
#define OMNI_SHA1_BLOCK_BYTE_SZ_FW 64 // OMNI_SHA1_BLOCK_SZ_FW * 4

namespace omni { namespace crypto { /** @internal library helper */ namespace sha1_internal {
        /** @internal library helper */
        void buffer_to_block(const std::string& buffer, uint32_t* block)
        {
            for (uint64_t i = 0; i < OMNI_SHA1_BLOCK_SZ_FW; ++i) {
                block[i] = (buffer[4 * i + 3] & 0xFF) |
                           (static_cast<uint32_t>(buffer[4 * i + 2] & 0xFF) << 8) |
                           (static_cast<uint32_t>(buffer[4 * i + 1] & 0xFF) << 16) |
                           (static_cast<uint32_t>(buffer[4 * i] & 0xFF) << 24);
            }
        }

        /** @internal library helper */
        void read(std::istream& stream, std::string& str, std::size_t size)
        {
            char* buf = new char[size];
            stream.read(buf, static_cast<std::streamsize>(size));
            str.assign(buf, static_cast<std::size_t>(stream.gcount()));
            OMNI_FREE_ARR(buf);
        }

        /** @internal library helper */
        void transform(uint32_t* block, uint32_t* digest, uint64_t& transforms)
        {
            uint32_t a = digest[0]; uint32_t b = digest[1]; uint32_t c = digest[2]; uint32_t d = digest[3]; uint32_t e = digest[4];

            OMNI_SHA1_R0_FW(a,b,c,d,e, 0); OMNI_SHA1_R0_FW(e,a,b,c,d, 1); OMNI_SHA1_R0_FW(d,e,a,b,c, 2); OMNI_SHA1_R0_FW(c,d,e,a,b, 3);
            OMNI_SHA1_R0_FW(b,c,d,e,a, 4); OMNI_SHA1_R0_FW(a,b,c,d,e, 5); OMNI_SHA1_R0_FW(e,a,b,c,d, 6); OMNI_SHA1_R0_FW(d,e,a,b,c, 7);
            OMNI_SHA1_R0_FW(c,d,e,a,b, 8); OMNI_SHA1_R0_FW(b,c,d,e,a, 9); OMNI_SHA1_R0_FW(a,b,c,d,e,10); OMNI_SHA1_R0_FW(e,a,b,c,d,11);
            OMNI_SHA1_R0_FW(d,e,a,b,c,12); OMNI_SHA1_R0_FW(c,d,e,a,b,13); OMNI_SHA1_R0_FW(b,c,d,e,a,14); OMNI_SHA1_R0_FW(a,b,c,d,e,15);
            OMNI_SHA1_R1_FW(e,a,b,c,d,16); OMNI_SHA1_R1_FW(d,e,a,b,c,17); OMNI_SHA1_R1_FW(c,d,e,a,b,18); OMNI_SHA1_R1_FW(b,c,d,e,a,19);
            OMNI_SHA1_R2_FW(a,b,c,d,e,20); OMNI_SHA1_R2_FW(e,a,b,c,d,21); OMNI_SHA1_R2_FW(d,e,a,b,c,22); OMNI_SHA1_R2_FW(c,d,e,a,b,23);
            OMNI_SHA1_R2_FW(b,c,d,e,a,24); OMNI_SHA1_R2_FW(a,b,c,d,e,25); OMNI_SHA1_R2_FW(e,a,b,c,d,26); OMNI_SHA1_R2_FW(d,e,a,b,c,27);
            OMNI_SHA1_R2_FW(c,d,e,a,b,28); OMNI_SHA1_R2_FW(b,c,d,e,a,29); OMNI_SHA1_R2_FW(a,b,c,d,e,30); OMNI_SHA1_R2_FW(e,a,b,c,d,31);
            OMNI_SHA1_R2_FW(d,e,a,b,c,32); OMNI_SHA1_R2_FW(c,d,e,a,b,33); OMNI_SHA1_R2_FW(b,c,d,e,a,34); OMNI_SHA1_R2_FW(a,b,c,d,e,35);
            OMNI_SHA1_R2_FW(e,a,b,c,d,36); OMNI_SHA1_R2_FW(d,e,a,b,c,37); OMNI_SHA1_R2_FW(c,d,e,a,b,38); OMNI_SHA1_R2_FW(b,c,d,e,a,39);
            OMNI_SHA1_R3_FW(a,b,c,d,e,40); OMNI_SHA1_R3_FW(e,a,b,c,d,41); OMNI_SHA1_R3_FW(d,e,a,b,c,42); OMNI_SHA1_R3_FW(c,d,e,a,b,43);
            OMNI_SHA1_R3_FW(b,c,d,e,a,44); OMNI_SHA1_R3_FW(a,b,c,d,e,45); OMNI_SHA1_R3_FW(e,a,b,c,d,46); OMNI_SHA1_R3_FW(d,e,a,b,c,47);
            OMNI_SHA1_R3_FW(c,d,e,a,b,48); OMNI_SHA1_R3_FW(b,c,d,e,a,49); OMNI_SHA1_R3_FW(a,b,c,d,e,50); OMNI_SHA1_R3_FW(e,a,b,c,d,51);
            OMNI_SHA1_R3_FW(d,e,a,b,c,52); OMNI_SHA1_R3_FW(c,d,e,a,b,53); OMNI_SHA1_R3_FW(b,c,d,e,a,54); OMNI_SHA1_R3_FW(a,b,c,d,e,55);
            OMNI_SHA1_R3_FW(e,a,b,c,d,56); OMNI_SHA1_R3_FW(d,e,a,b,c,57); OMNI_SHA1_R3_FW(c,d,e,a,b,58); OMNI_SHA1_R3_FW(b,c,d,e,a,59);
            OMNI_SHA1_R4_FW(a,b,c,d,e,60); OMNI_SHA1_R4_FW(e,a,b,c,d,61); OMNI_SHA1_R4_FW(d,e,a,b,c,62); OMNI_SHA1_R4_FW(c,d,e,a,b,63);
            OMNI_SHA1_R4_FW(b,c,d,e,a,64); OMNI_SHA1_R4_FW(a,b,c,d,e,65); OMNI_SHA1_R4_FW(e,a,b,c,d,66); OMNI_SHA1_R4_FW(d,e,a,b,c,67);
            OMNI_SHA1_R4_FW(c,d,e,a,b,68); OMNI_SHA1_R4_FW(b,c,d,e,a,69); OMNI_SHA1_R4_FW(a,b,c,d,e,70); OMNI_SHA1_R4_FW(e,a,b,c,d,71);
            OMNI_SHA1_R4_FW(d,e,a,b,c,72); OMNI_SHA1_R4_FW(c,d,e,a,b,73); OMNI_SHA1_R4_FW(b,c,d,e,a,74); OMNI_SHA1_R4_FW(a,b,c,d,e,75);
            OMNI_SHA1_R4_FW(e,a,b,c,d,76); OMNI_SHA1_R4_FW(d,e,a,b,c,77); OMNI_SHA1_R4_FW(c,d,e,a,b,78); OMNI_SHA1_R4_FW(b,c,d,e,a,79);

            digest[0] += a; digest[1] += b; digest[2] += c; digest[3] += d; digest[4] += e;

            ++transforms;
        }
        
        /** @internal library helper */
        void compute_hash(std::istream& stream, std::string& buffer, uint32_t* digest, uint64_t& transforms, std::string& out_result)
        {
            std::string rbuf;
            omni::crypto::sha1_internal::read(stream, rbuf, OMNI_SHA1_BLOCK_BYTE_SZ_FW - buffer.size());
            buffer += rbuf;
            while (stream) {
                uint32_t block[OMNI_SHA1_BLOCK_SZ_FW];
                omni::crypto::sha1_internal::buffer_to_block(buffer, block);
                omni::crypto::sha1_internal::transform(block, digest, transforms);
                omni::crypto::sha1_internal::read(stream, buffer, OMNI_SHA1_BLOCK_BYTE_SZ_FW);
            }

            uint64_t total_bits = (transforms * OMNI_SHA1_BLOCK_BYTE_SZ_FW + buffer.size()) * 8;
            buffer += static_cast<char>(0x80);
            std::size_t orig_size = buffer.size();
            while (buffer.size() < OMNI_SHA1_BLOCK_BYTE_SZ_FW) {
                buffer += static_cast<char>(0x00);
            }
            std::size_t i;
            uint32_t block[OMNI_SHA1_BLOCK_SZ_FW];
            omni::crypto::sha1_internal::buffer_to_block(buffer, block);
            if (orig_size > OMNI_SHA1_BLOCK_BYTE_SZ_FW - 8) {
                omni::crypto::sha1_internal::transform(block, digest, transforms);
                for (i = 0; i < OMNI_SHA1_BLOCK_SZ_FW - 2; ++i) {
                    block[i] = 0;
                }
            }
            block[OMNI_SHA1_BLOCK_SZ_FW - 1] = static_cast<uint32_t>(total_bits);
            block[OMNI_SHA1_BLOCK_SZ_FW - 2] = static_cast<uint32_t>((total_bits >> 32));
            omni::crypto::sha1_internal::transform(block, digest, transforms);
            
            out_result = omni::crypto::util::buffer_to_hex_string(digest, OMNI_SHA1_DIGEST_SZ_FW, 0xFFFFFFFF);
        }
} } }

omni::crypto::sha1::sha1() :
    OMNI_CTOR_FW(omni::crypto::sha1)
    m_hash()
    OMNI_SAFE_SHA1DMTX_FW
{}

omni::crypto::sha1::sha1(const omni::crypto::sha1& cp) :
    OMNI_CPCTOR_FW(cp)
    m_hash(cp.m_hash)
    OMNI_SAFE_SHA1DMTX_FW
{}

OMNI_EXPLICIT omni::crypto::sha1::sha1(const std::string& hash) :
    OMNI_CTOR_FW(omni::crypto::sha1)
    m_hash(hash)
    OMNI_SAFE_SHA1DMTX_FW
{
}

omni::crypto::sha1::sha1(const std::string& text, const omni::crypto::hash_type& type) :
    OMNI_CTOR_FW(omni::crypto::sha1)
    m_hash()
    OMNI_SAFE_SHA1DMTX_FW
{
    if (type == omni::crypto::hash_type::STRING) {
        std::istringstream stream(text);
        this->_compute(stream);
    } else {
        if (!omni::io::file_internal::exists(text)) {
            OMNI_ERRV_FW("File not found: ", text, omni::exceptions::file_not_found(text))
        }
        if (type == omni::crypto::hash_type::BINARY_FILE) {
            std::ifstream stream(text.c_str(), std::ios::binary);
            this->_compute(stream);
        } else {
            std::ifstream stream(text.c_str());
            this->_compute(stream);
        }
    }
}

omni::crypto::sha1::~sha1()
{
    OMNI_TRY_FW
    OMNI_DTOR_FW
    OMNI_CATCH_FW
}

std::string omni::crypto::sha1::hash_code() const
{
    return this->to_string();
}

void omni::crypto::sha1::swap(omni::crypto::sha1& o)
{
    if (this != &o) {
        OMNI_SAFE_SHA1ALOCK_FW
        OMNI_SAFE_SHA1OALOCK_FW(o)
        std::swap(this->m_hash, o.m_hash);
    }
}

omni::string_t omni::crypto::sha1::to_string_t() const
{
    OMNI_SAFE_SHA1ALOCK_FW
    return omni::string::util::to_string_t(this->m_hash);
}

std::string omni::crypto::sha1::to_string() const
{
    OMNI_SAFE_SHA1ALOCK_FW
    return this->m_hash;
}

std::wstring omni::crypto::sha1::to_wstring() const
{
    OMNI_SAFE_SHA1ALOCK_FW
    return omni::string::util::to_wstring(this->m_hash);
}

omni::crypto::sha1& omni::crypto::sha1::operator=(const omni::crypto::sha1& other)
{
    if (this != &other) {
        OMNI_SAFE_SHA1ALOCK_FW
        OMNI_SAFE_SHA1OALOCK_FW(other)
        this->m_hash = other.m_hash;
    }
    return *this;
}

bool omni::crypto::sha1::operator==(const omni::crypto::sha1& o) const
{
    if (this != &o) {
        OMNI_SAFE_SHA1ALOCK_FW
        OMNI_SAFE_SHA1OALOCK_FW(o)
        return this->m_hash == o.m_hash;
    }
    return true;
}

bool omni::crypto::sha1::operator!=(const omni::crypto::sha1& o) const
{
    return !(*this == o);
}

std::string omni::crypto::sha1::compute_hash(const std::string& text)
{
    omni::crypto::sha1 var(text, omni::crypto::hash_type::STRING);
    return var.m_hash;
}

std::string omni::crypto::sha1::compute_file_hash(const std::string& file)
{
    omni::crypto::sha1 var(file, omni::crypto::hash_type::TEXT_FILE);
    return var.m_hash;
}

std::string omni::crypto::sha1::compute_binary_file_hash(const std::string& file)
{
    omni::crypto::sha1 var(file, omni::crypto::hash_type::BINARY_FILE);
    return var.m_hash;
}

void omni::crypto::sha1::_compute(std::istream& stream)
{
    uint32_t digest[OMNI_SHA1_DIGEST_SZ_FW] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    uint64_t transforms = 0;
    std::string buffer;
    omni::crypto::sha1_internal::compute_hash(stream, buffer, digest, transforms, this->m_hash);
}

#undef OMNI_IO_FILE_EX_FW
