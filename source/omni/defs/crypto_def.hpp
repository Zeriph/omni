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
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES
 * LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(OMNI_CRYPTO_DEF_HPP)
#define OMNI_CRYPTO_DEF_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/string/util.hpp>
#include <omni/types/string_t.hpp>
#include <fstream>
#include <sstream>

// md5
#define OMNI_MD5_SR1_1_FW 0x07
#define OMNI_MD5_SR1_2_FW 0x0C
#define OMNI_MD5_SR1_3_FW 0x11
#define OMNI_MD5_SR1_4_FW 0x16
#define OMNI_MD5_SR2_1_FW 0x05
#define OMNI_MD5_SR2_2_FW 0x09
#define OMNI_MD5_SR2_3_FW 0x0E
#define OMNI_MD5_SR2_4_FW 0x14
#define OMNI_MD5_SR3_1_FW 0x04
#define OMNI_MD5_SR3_2_FW 0x11
#define OMNI_MD5_SR3_3_FW 0x10
#define OMNI_MD5_SR3_4_FW 0x17
#define OMNI_MD5_SR4_1_FW 0x06
#define OMNI_MD5_SR4_2_FW 0x0A
#define OMNI_MD5_SR4_3_FW 0x0F
#define OMNI_MD5_SR4_4_FW 0x15

#define OMNI_MD5_BLOCKSZ_FW 64

// sha1
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

// sha256
#define OMNI_SHA2_SHFR_FW(x, n) (x >> n)
#define OMNI_SHA2_ROTR_FW(x, n) ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define OMNI_SHA2_ROTL_FW(x, n) ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define OMNI_SHA2_CH_FW(x, y, z) ((x & y) ^ (~x & z))
#define OMNI_SHA2_MAJ_FW(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define OMNI_SHA256_F1_FW(x) (OMNI_SHA2_ROTR_FW(x, 2) ^ OMNI_SHA2_ROTR_FW(x, 13) ^ OMNI_SHA2_ROTR_FW(x, 22))
#define OMNI_SHA256_F2_FW(x) (OMNI_SHA2_ROTR_FW(x, 6) ^ OMNI_SHA2_ROTR_FW(x, 11) ^ OMNI_SHA2_ROTR_FW(x, 25))
#define OMNI_SHA256_F3_FW(x) (OMNI_SHA2_ROTR_FW(x, 7) ^ OMNI_SHA2_ROTR_FW(x, 18) ^ OMNI_SHA2_SHFR_FW(x, 3))
#define OMNI_SHA256_F4_FW(x) (OMNI_SHA2_ROTR_FW(x, 17) ^ OMNI_SHA2_ROTR_FW(x, 19) ^ OMNI_SHA2_SHFR_FW(x, 10))
#define OMNI_SHA2_UNPACK32_FW(x, str) { *((str) + 3) = (uint8_t) ((x)); *((str) + 2) = (uint8_t) ((x) >> 8); *((str) + 1) = (uint8_t) ((x) >> 16); *((str) + 0) = (uint8_t) ((x) >> 24); }
#define OMNI_SHA2_PACK32_FW(str, x) { *(x) = ((uint32_t) *((str) + 3)) | ((uint32_t) *((str) + 2) <<  8) | ((uint32_t) *((str) + 1) << 16) | ((uint32_t) *((str) + 0) << 24); }
#define OMNI_SHA2_DIGEST_SIZE_FW 32 // (256 / 8)
#define OMNI_SHA2_BLOCK_SIZE_FW 64 // (512 / 8)

// base64
#define OMNI_CRYPTO_BASE64_CHARS { \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_" \
}
#define OMNI_CYRPTO_BASE64_CHAR_POS(c, p) \
switch (c) { \
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': \
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': \
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': \
    case 'V': case 'W': case 'X': case 'Y': case 'Z': \
        p = (c - 'A'); break; \
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': \
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': \
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': \
    case 'v': case 'w': case 'x': case 'y': case 'z': \
        p = (c - 'a' + ('Z' - 'A') + 1); break; \
    case '0': case '1': case '2': case '3': case '4': \
    case '5': case '6': case '7': case '8': case '9': \
        p = (c - '0' + ('Z' - 'A') + ('z' - 'a') + 2); break; \
    case '+': case '-': p = 62; break; \
    case '/': case '_': p = 63; break; \
    default: p = 255; OMNI_ERR_FW("An invalid character was detected in the base64 encoded data", omni::exceptions::invalid_parse("Invalid base64 encoded data")) break; \
}

#endif // OMNI_CRYPTO_DEF_HPP
