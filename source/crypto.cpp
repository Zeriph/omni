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
#include <omni/crypto_types.hpp>
#include <omni/defs/file_def.hpp>
#include <fstream>
#include <sstream>
#include <cstring>
#define OMNI_IO_FILE_EX_FW 1
#include <omni/xx/io_file_ex.hxx>

// MD5

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

void omni::crypto::md5::_compute(const std::string& text)
{
    this->_compute(reinterpret_cast<const unsigned char*>(text.c_str()), text.length());
}

void omni::crypto::md5::_compute(const unsigned char* data, uint32_t data_len)
{
    uint8_t digest[16] = {0};
    uint8_t buffer[OMNI_MD5_BLOCKSZ_FW] = {0};
    uint32_t count[2] = {0};
    uint32_t state[4] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
    uint32_t i, j, index;
    unsigned char padding[OMNI_MD5_BLOCKSZ_FW] = {0};
    unsigned char bits[8] = {0};
    char obuf[33] = {0};
    padding[0] = 0x80;
    md5::_update(data, data_len, count, buffer, state);
    for (i = 0, j = 0; j < 8; ++i, j += 4) {
        bits[j] = count[i] & 0xFF;
        bits[j+1] = (count[i] >> 8) & 0xFF;
        bits[j+2] = (count[i] >> 16) & 0xFF;
        bits[j+3] = (count[i] >> 24) & 0xFF;
    }
    index = count[0] / 8 % OMNI_MD5_BLOCKSZ_FW;
    md5::_update(padding, ((index < 56) ? (56 - index) : (120 - index)), count, buffer, state);
    md5::_update(bits, 8, count, buffer, state);
    for (i = 0, j = 0; j < 16; ++i, j += 4) {
        digest[j] = state[i] & 0xFF;
        digest[j+1] = (state[i] >> 8) & 0xFF;
        digest[j+2] = (state[i] >> 16) & 0xFF;
        digest[j+3] = (state[i] >> 24) & 0xFF;
    }
    for (i = 0; i < 16; ++i) {
        ::sprintf(obuf+i*2, "%02x", digest[i]);
    }
    obuf[32] = 0;
    this->m_hash = std::string(obuf);
}

void omni::crypto::md5::_update(const unsigned char* input, uint32_t length, uint32_t* count, uint8_t* buffer, uint32_t* state)
{
    uint32_t i;
    uint32_t idx = count[0] / 8 % OMNI_MD5_BLOCKSZ_FW;
    uint32_t hi = 64 - idx;
    if ((count[0] += (length << 3)) < (length << 3)) {
        ++count[1];
    }
    count[1] += (length >> 29);
    if (length >= hi) {
        std::memcpy(&buffer[idx], input, hi);
        md5::_transform(buffer, state);
        for (i = hi; i + OMNI_MD5_BLOCKSZ_FW <= length; i += OMNI_MD5_BLOCKSZ_FW) {
            md5::_transform(&input[i], state);
        }
        idx = 0;
    } else {
        i = 0;
    }
    std::memcpy(&buffer[idx], &input[i], length-i);
}

void omni::crypto::md5::_transform(const uint8_t* block, uint32_t* state)
{
    uint32_t x[16];
    uint32_t a = state[0]; uint32_t b = state[1];
    uint32_t c = state[2]; uint32_t d = state[3];
    for (uint32_t i = 0, j = 0; j < OMNI_MD5_BLOCKSZ_FW; ++i, j += 4) {
        x[i] = (static_cast<uint32_t>(block[j])) |
            ((static_cast<uint32_t>(block[j+1])) << 8) |
            ((static_cast<uint32_t>(block[j+2])) << 16) |
            ((static_cast<uint32_t>(block[j+3])) << 24);
    }
    // Round 1
    md5::_r1(a, b, c, d, x[0], OMNI_MD5_SR1_1_FW, 0xD76AA478);
    md5::_r1(d, a, b, c, x[1], OMNI_MD5_SR1_2_FW, 0xE8C7B756);
    md5::_r1(c, d, a, b, x[2], OMNI_MD5_SR1_3_FW, 0x242070DB);
    md5::_r1(b, c, d, a, x[3], OMNI_MD5_SR1_4_FW, 0xC1BDCEEE);
    md5::_r1(a, b, c, d, x[4], OMNI_MD5_SR1_1_FW, 0xF57C0FAF);
    md5::_r1(d, a, b, c, x[5], OMNI_MD5_SR1_2_FW, 0x4787C62A);
    md5::_r1(c, d, a, b, x[6], OMNI_MD5_SR1_3_FW, 0xA8304613);
    md5::_r1(b, c, d, a, x[7], OMNI_MD5_SR1_4_FW, 0xFD469501);
    md5::_r1(a, b, c, d, x[8], OMNI_MD5_SR1_1_FW, 0x698098D8);
    md5::_r1(d, a, b, c, x[9], OMNI_MD5_SR1_2_FW, 0x8B44F7AF);
    md5::_r1(c, d, a, b, x[10], OMNI_MD5_SR1_3_FW, 0xFFFF5BB1);
    md5::_r1(b, c, d, a, x[11], OMNI_MD5_SR1_4_FW, 0x895CD7BE);
    md5::_r1(a, b, c, d, x[12], OMNI_MD5_SR1_1_FW, 0x6B901122);
    md5::_r1(d, a, b, c, x[13], OMNI_MD5_SR1_2_FW, 0xFD987193);
    md5::_r1(c, d, a, b, x[14], OMNI_MD5_SR1_3_FW, 0xA679438E);
    md5::_r1(b, c, d, a, x[15], OMNI_MD5_SR1_4_FW, 0x49B40821);
    // Round 2 
    md5::_r2(a, b, c, d, x[1], OMNI_MD5_SR2_1_FW, 0xF61E2562);
    md5::_r2(d, a, b, c, x[6], OMNI_MD5_SR2_2_FW, 0xC040B340);
    md5::_r2(c, d, a, b, x[11], OMNI_MD5_SR2_3_FW, 0x265E5A51);
    md5::_r2(b, c, d, a, x[0], OMNI_MD5_SR2_4_FW, 0xE9B6C7AA);
    md5::_r2(a, b, c, d, x[5], OMNI_MD5_SR2_1_FW, 0xD62F105D);
    md5::_r2(d, a, b, c, x[10], OMNI_MD5_SR2_2_FW,  0x2441453);
    md5::_r2(c, d, a, b, x[15], OMNI_MD5_SR2_3_FW, 0xD8A1E681);
    md5::_r2(b, c, d, a, x[4], OMNI_MD5_SR2_4_FW, 0xE7D3FBC8);
    md5::_r2(a, b, c, d, x[9], OMNI_MD5_SR2_1_FW, 0x21E1CDE6);
    md5::_r2(d, a, b, c, x[14], OMNI_MD5_SR2_2_FW, 0xC33707D6);
    md5::_r2(c, d, a, b, x[3], OMNI_MD5_SR2_3_FW, 0xF4D50D87);
    md5::_r2(b, c, d, a, x[8], OMNI_MD5_SR2_4_FW, 0x455A14ED);
    md5::_r2(a, b, c, d, x[13], OMNI_MD5_SR2_1_FW, 0xA9E3E905);
    md5::_r2(d, a, b, c, x[2], OMNI_MD5_SR2_2_FW, 0xFCEFA3F8);
    md5::_r2(c, d, a, b, x[7], OMNI_MD5_SR2_3_FW, 0x676F02D9);
    md5::_r2(b, c, d, a, x[12], OMNI_MD5_SR2_4_FW, 0x8D2A4C8A);
    // Round 3 
    md5::_r3(a, b, c, d, x[5], OMNI_MD5_SR3_1_FW, 0xFFFA3942);
    md5::_r3(d, a, b, c, x[8], OMNI_MD5_SR3_2_FW, 0x8771F681);
    md5::_r3(c, d, a, b, x[11], OMNI_MD5_SR3_3_FW, 0x6D9D6122);
    md5::_r3(b, c, d, a, x[14], OMNI_MD5_SR3_4_FW, 0xFDE5380C);
    md5::_r3(a, b, c, d, x[1], OMNI_MD5_SR3_1_FW, 0xA4BEEA44);
    md5::_r3(d, a, b, c, x[4], OMNI_MD5_SR3_2_FW, 0x4BDECFA9);
    md5::_r3(c, d, a, b, x[7], OMNI_MD5_SR3_3_FW, 0xF6BB4B60);
    md5::_r3(b, c, d, a, x[10], OMNI_MD5_SR3_4_FW, 0xBEBFBC70);
    md5::_r3(a, b, c, d, x[13], OMNI_MD5_SR3_1_FW, 0x289B7EC6);
    md5::_r3(d, a, b, c, x[0], OMNI_MD5_SR3_2_FW, 0xEAA127FA);
    md5::_r3(c, d, a, b, x[3], OMNI_MD5_SR3_3_FW, 0xD4EF3085);
    md5::_r3(b, c, d, a, x[6], OMNI_MD5_SR3_4_FW,  0x4881D05);
    md5::_r3(a, b, c, d, x[9], OMNI_MD5_SR3_1_FW, 0xD9D4D039);
    md5::_r3(d, a, b, c, x[12], OMNI_MD5_SR3_2_FW, 0xE6DB99E5);
    md5::_r3(c, d, a, b, x[15], OMNI_MD5_SR3_3_FW, 0x1FA27CF8);
    md5::_r3(b, c, d, a, x[2], OMNI_MD5_SR3_4_FW, 0xC4AC5665);
    // Round 4 
    md5::_r4(a, b, c, d, x[0], OMNI_MD5_SR4_1_FW, 0xF4292244);
    md5::_r4(d, a, b, c, x[7], OMNI_MD5_SR4_2_FW, 0x432AFF97);
    md5::_r4(c, d, a, b, x[14], OMNI_MD5_SR4_3_FW, 0xAB9423A7);
    md5::_r4(b, c, d, a, x[5], OMNI_MD5_SR4_4_FW, 0xFC93A039);
    md5::_r4(a, b, c, d, x[12], OMNI_MD5_SR4_1_FW, 0x655B59C3);
    md5::_r4(d, a, b, c, x[3], OMNI_MD5_SR4_2_FW, 0x8F0CCC92);
    md5::_r4(c, d, a, b, x[10], OMNI_MD5_SR4_3_FW, 0xFFEFF47D);
    md5::_r4(b, c, d, a, x[1], OMNI_MD5_SR4_4_FW, 0x85845DD1);
    md5::_r4(a, b, c, d, x[8], OMNI_MD5_SR4_1_FW, 0x6FA87E4F);
    md5::_r4(d, a, b, c, x[15], OMNI_MD5_SR4_2_FW, 0xFE2CE6E0);
    md5::_r4(c, d, a, b, x[6], OMNI_MD5_SR4_3_FW, 0xA3014314);
    md5::_r4(b, c, d, a, x[13], OMNI_MD5_SR4_4_FW, 0x4E0811A1);
    md5::_r4(a, b, c, d, x[4], OMNI_MD5_SR4_1_FW, 0xF7537E82);
    md5::_r4(d, a, b, c, x[11], OMNI_MD5_SR4_2_FW, 0xBD3AF235);
    md5::_r4(c, d, a, b, x[2], OMNI_MD5_SR4_3_FW, 0x2AD7D2BB);
    md5::_r4(b, c, d, a, x[9], OMNI_MD5_SR4_4_FW, 0xEB86D391);

    state[0] += a; state[1] += b;
    state[2] += c; state[3] += d;
    std::memset(x, 0, sizeof(x));
}

uint32_t omni::crypto::md5::_rotate(uint32_t x, int n)
{
    return (x << n) | (x >> (32 - n));
}

void omni::crypto::md5::_r1(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = md5::_rotate(a + ((b & c) | (~b & d)) + x + ac, s) + b;
}

void omni::crypto::md5::_r2(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = md5::_rotate(a + ((b & d) | (c & ~d)) + x + ac, s) + b;
}

void omni::crypto::md5::_r3(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = md5::_rotate(a + (b ^ c ^ d) + x + ac, s) + b;
}

void omni::crypto::md5::_r4(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = md5::_rotate(a + (c ^ (b | ~d)) + x + ac, s) + b;
}

// SHA1

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
    omni::crypto::sha1 md5(text, omni::crypto::hash_type::STRING);
    return md5.m_hash;
}

std::string omni::crypto::sha1::compute_file_hash(const std::string& file)
{
    omni::crypto::sha1 md5(file, omni::crypto::hash_type::TEXT_FILE);
    return md5.m_hash;
}

std::string omni::crypto::sha1::compute_binary_file_hash(const std::string& file)
{
    omni::crypto::sha1 md5(file, omni::crypto::hash_type::BINARY_FILE);
    return md5.m_hash;
}

void omni::crypto::sha1::_compute(std::istream& stream)
{
    uint32_t digest[OMNI_SHA1_DIGEST_SZ_FW] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    uint64_t transforms = 0;
    std::string buffer;

    omni::crypto::sha1::_compute_hash(stream, buffer, digest, transforms);
    this->m_hash = omni::crypto::sha1::_final(buffer, digest, transforms);
}

void omni::crypto::sha1::_compute_hash(std::istream& stream, std::string& buffer, uint32_t* digest, uint64_t& transforms)
{
    std::string rbuf;
    omni::crypto::sha1::_read(stream, rbuf, OMNI_SHA1_BLOCK_BYTE_SZ_FW - buffer.size());
    buffer += rbuf;
    while (stream) {
        uint32_t block[OMNI_SHA1_BLOCK_SZ_FW];
        omni::crypto::sha1::_buffer_to_block(buffer, block);
        omni::crypto::sha1::_transform(block, digest, transforms);
        omni::crypto::sha1::_read(stream, buffer, OMNI_SHA1_BLOCK_BYTE_SZ_FW);
    }
}

std::string omni::crypto::sha1::_final(std::string& buffer, uint32_t* digest, uint64_t& transforms)
{
    uint64_t total_bits = (transforms * OMNI_SHA1_BLOCK_BYTE_SZ_FW + buffer.size()) * 8;
    buffer += 0x80;
    std::size_t orig_size = buffer.size();
    while (buffer.size() < OMNI_SHA1_BLOCK_BYTE_SZ_FW) {
        buffer += static_cast<char>(0x00);
    }
    std::size_t i;
    uint32_t block[OMNI_SHA1_BLOCK_SZ_FW];
    omni::crypto::sha1::_buffer_to_block(buffer, block);
    if (orig_size > OMNI_SHA1_BLOCK_BYTE_SZ_FW - 8) {
        omni::crypto::sha1::_transform(block, digest, transforms);
        for (i = 0; i < OMNI_SHA1_BLOCK_SZ_FW - 2; ++i) {
            block[i] = 0;
        }
    }
    block[OMNI_SHA1_BLOCK_SZ_FW - 1] = total_bits;
    block[OMNI_SHA1_BLOCK_SZ_FW - 2] = (total_bits >> 32);
    omni::crypto::sha1::_transform(block, digest, transforms);
    std::ostringstream result;
    for (i = 0; i < OMNI_SHA1_DIGEST_SZ_FW; i++) {
        result << std::hex << std::setfill('0') << std::setw(8);
        result << (digest[i] & 0xFFFFFFFF);
    }
    return result.str();
}                

void omni::crypto::sha1::_transform(uint32_t* block, uint32_t* digest, uint64_t& transforms)
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

void omni::crypto::sha1::_buffer_to_block(const std::string& buffer, uint32_t* block)
{
    for (uint64_t i = 0; i < OMNI_SHA1_BLOCK_SZ_FW; ++i) {
        block[i] = (buffer[4 * i + 3] & 0xFF) |
                    ((buffer[4 * i + 2] & 0xFF) << 8) |
                    ((buffer[4 * i + 1] & 0xFF) << 16) |
                    ((buffer[4 * i] & 0xFF) << 24);
    }
}

void omni::crypto::sha1::_read(std::istream& stream, std::string& str, std::size_t size)
{
    char* buf = new char[size];
    stream.read(buf, size);
    str.assign(buf, stream.gcount());
    OMNI_FREE_ARR(buf);
}

// SHA256

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
    this->_compute(reinterpret_cast<const unsigned char*>(text.c_str()), text.length());
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
        omni::crypto::sha256::_transform(data_block, 1, hex_vals);
        omni::crypto::sha256::_transform(shifted_message, block_nb, hex_vals);
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
    omni::crypto::sha256::_transform(data_block, block_nb, hex_vals);
    for (i = 0 ; i < 8; ++i) {
        OMNI_SHA2_UNPACK32_FW(hex_vals[i], &digest[i << 2]);
    }

    char buf[2 * OMNI_SHA2_DIGEST_SIZE_FW + 1];
    buf[2 * OMNI_SHA2_DIGEST_SIZE_FW] = 0;
    for (i = 0; i < OMNI_SHA2_DIGEST_SIZE_FW; ++i) {
        sprintf(buf+i*2, "%02x", digest[i]);
    }
    this->m_hash = std::string(buf);
}

void omni::crypto::sha256::_transform(const unsigned char* message, uint32_t block_nb, uint32_t* hex_vals)
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
        for (j = 0; j < 16; ++j) { OMNI_SHA2_PACK32_FW(&sub_block[j << 2], &blkx[j]); }
        for (j = 16; j < 64; j++) { blkx[j] = OMNI_SHA256_F4_FW(blkx[j -  2]) + blkx[j -  7] + OMNI_SHA256_F3_FW(blkx[j - 15]) + blkx[j - 16]; }
        for (j = 0; j < 8; j++) { blky[j] = hex_vals[j]; }
        for (j = 0; j < 64; j++) {
            t1 = blky[7] + OMNI_SHA256_F2_FW(blky[4]) + OMNI_SHA2_CH_FW(blky[4], blky[5], blky[6]) + sha256_k[j] + blkx[j];
            t2 = OMNI_SHA256_F1_FW(blky[0]) + OMNI_SHA2_MAJ_FW(blky[0], blky[1], blky[2]);
            blky[7] = blky[6]; blky[6] = blky[5]; blky[5] = blky[4];
            blky[4] = blky[3] + t1; blky[3] = blky[2]; blky[2] = blky[1];
            blky[1] = blky[0]; blky[0] = t1 + t2;
        }
        for (j = 0; j < 8; j++) { hex_vals[j] += blky[j]; }
    }
}
