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
#if !defined(OMNI_BITS_HPP)
#define OMNI_BITS_HPP 1
#include <omni/defs/global.hpp>
#include <climits>

#if defined(OMNI_CHECK_ARITHMETIC_OVERFLOW)
    #define OMNI_BITS_WILL_ADD_OVER_FW(a,b) if (omni::bits::will_addition_overflow(a,b)) { OMNI_ERR_FW("An addition overflow exception occurred.", omni::exceptions::overflow_error()) }
    #define OMNI_BITS_WILL_SUB_OVER_FW(a,b) if (omni::bits::will_subtraction_overflow(a,b)) { OMNI_ERR_FW("An subtraction overflow exception occurred.", omni::exceptions::overflow_error()) }
    #define OMNI_BITS_WILL_MUL_OVER_FW(a,b) if (omni::bits::will_multiplication_overflow(a,b)) { OMNI_ERR_FW("An multiplication overflow exception occurred.", omni::exceptions::overflow_error()) }
    #define OMNI_BITS_WILL_ADD_UNDER_FW(a,b) if (omni::bits::will_addition_underflow(a,b)) { OMNI_ERR_FW("An addition underflow exception occurred.", omni::exceptions::underflow_error()) }
    #define OMNI_BITS_WILL_SUB_UNDER_FW(a,b) if (omni::bits::will_subtraction_underflow(a,b)) { OMNI_ERR_FW("An subtraction underflow exception occurred.", omni::exceptions::underflow_error()) }
    #define OMNI_BITS_WILL_MUL_UNDER_FW(a,b) if (omni::bits::will_multiplication_underflow(a,b)) { OMNI_ERR_FW("An multiplication underflow exception occurred.", omni::exceptions::underflow_error()) }
#else
    #define OMNI_BITS_WILL_ADD_OVER_FW(a,b)
    #define OMNI_BITS_WILL_SUB_OVER_FW(a,b)
    #define OMNI_BITS_WILL_MUL_OVER_FW(a,b)
    #define OMNI_BITS_WILL_ADD_UNDER_FW(a,b)
    #define OMNI_BITS_WILL_SUB_UNDER_FW(a,b)
    #define OMNI_BITS_WILL_MUL_UNDER_FW(a,b)
#endif

#define OMNI_XOR_SWAP(a, b) a ^= b; b ^= a; a ^= b
#define OMNI_VAL_HAS_FLAG_BIT(val, flag) ((val & flag) == flag)
#define OMNI_VAL_SET_FLAG_BOOL(val, flag, onoff) val = (onoff ? (val | flag) : ((val | flag) ^ flag))
#define OMNI_VAL_SET_FLAG_BOOL_T(T, val, flag, onoff) val = static_cast<T>(onoff ? (val | flag) : ((val | flag) ^ flag))
#define OMNI_VAL_SET_FLAG_BIT(val, flag) val = (val | flag)
#define OMNI_VAL_UNSET_FLAG_BIT(val, flag) val = ((val | flag) ^ flag)
#define OMNI_IS_N_BIT_SET(val, n) ((val & (1 << n)) == (1 << n))
#define OMNI_SET_N_BIT(val, n) val = (val | (1 << n))
#define OMNI_UNSET_N_BIT(val, n) val = ((val | (1 << n)) ^ (1 << n))
#define OMNI_SIZEOF_BITS(T) (sizeof(T) * CHAR_BIT)

namespace omni {
    namespace bits {
        template < typename T, typename F >
        inline bool has_flag(const T& t, F flag)
        {
            return OMNI_VAL_HAS_FLAG_BIT(t, flag);
        }
        
        template < typename T, typename F >
        inline T& set_flag(T& t, F flag, bool set)
        {
            if (set) { return (OMNI_VAL_SET_FLAG_BIT(t, flag)); }
            return (OMNI_VAL_UNSET_FLAG_BIT(t, flag));
        }
        
        template < typename T, typename F >
        inline T& set_flag(T& t, F flag)
        {
            return (OMNI_VAL_SET_FLAG_BIT(t, flag));
        }
        
        template < typename T, typename F >
        inline T& unset_flag(T& t, F flag)
        {
            return (OMNI_VAL_UNSET_FLAG_BIT(t, flag));
        }
        
        template < typename T >
        inline bool unsafe_is_set(const T& t, uint8_t n)
        {
            return omni::bits::has_flag(t, static_cast<T>(1 << n));
        }
        
        template < typename T >
        inline T& unsafe_set(T& t, uint8_t n, bool s)
        {
            if (s) { return omni::bits::set_flag(t, (1 << n)); } // set
            return omni::bits::unset_flag(t, static_cast<T>(1 << n));
        }
        
        template < typename T >
        inline T& unsafe_set(T& t, uint8_t n)
        {
            return omni::bits::set_flag(t, static_cast<T>(1 << n));
        }
        
        template < typename T >
        inline T& unsafe_unset(T& t, uint8_t n)
        {
            return omni::bits::unset_flag(t, static_cast<T>(1 << n));
        }
        
        template < typename T >
        inline bool is_set(const T& t, uint8_t n)
        {
            if (n > OMNI_SIZEOF_BITS(T)) {
                OMNI_ERRV_RETV_FW(n, " > sizeof(T)", omni::exceptions::index_out_of_range("Invalid bit", n), false)
            }
            return omni::bits::unsafe_is_set(t, n);
        }
        
        template < typename T >
        inline T& set(T& t, uint8_t n, bool s)
        {
            if (n > OMNI_SIZEOF_BITS(T)) {
                OMNI_ERRV_RETV_FW(n, " > sizeof(T)", omni::exceptions::index_out_of_range("Invalid bit", n), false)
            }
            return omni::bits::unsafe_set(t, n, s);
        }
        
        template < typename T >
        inline T& set(T& t, uint8_t n)
        {
            if (n > OMNI_SIZEOF_BITS(T)) {
                OMNI_ERRV_RETV_FW(n, " > sizeof(T)", omni::exceptions::index_out_of_range("Invalid bit", n), false)
            }
            return omni::bits::unsafe_set(t, n);
        }
        
        template < typename T >
        inline T& unset(T& t, uint8_t n)
        {
            if (n > OMNI_SIZEOF_BITS(T)) {
                OMNI_ERRV_RETV_FW(n, " > sizeof(T)", omni::exceptions::index_out_of_range("Invalid bit", n), false)
            }
            return omni::bits::unsafe_unset(t, n);
        }
        
        template < typename T >
        inline void xor_swap(T& a, T& b)
        {
            if (a != b) {
                OMNI_XOR_SWAP(a, b); // a ^= b; b ^= a; a ^= b
            }
        }
        
        template < typename T1, typename T2 >
        inline void xor_swap(T1& a, T2& b)
        {
            if (a != b) {
                OMNI_XOR_SWAP(a, b); // a ^= b; b ^= a; a ^= b
            }
        }
        
        template < typename T >
        inline std::size_t size()
        {
            return OMNI_SIZEOF_BITS(T); // (sizeof(T) * CHAR_BIT)
        }
        
        template < typename T >
        inline std::size_t size(const T& obj)
        {
            return OMNI_SIZEOF_BITS(obj); // (sizeof(obj) * CHAR_BIT)
        }

        template < typename T >
        inline bool test_overflow(T a, T b, char op)
        {
            switch (op) {
                case '+': return ((b > 0) && (a > std::numeric_limits<T>::max() - b));
                case '-': return ((b < 0) && (a > std::numeric_limits<T>::max() + b));
                case '*':
                    return ((a > std::numeric_limits<T>::max() / b) ||
                           ((a == -1) && (b == std::numeric_limits<T>::min())) ||
                           ((b == -1) && (a == std::numeric_limits<T>::min())));
                default: break;
            }
            return false;
        }

        template < typename T >
        inline bool test_underflow(T a, T b, char op)
        {
            switch (op) {
                case '+': return ((b < 0) && (a < std::numeric_limits<T>::min() - b));
                case '-': return ((b > 0) && (a < std::numeric_limits<T>::min() + b));
                case '*': return ((a < std::numeric_limits<T>::min() / b));
                default: break;
            }
            return false;
        }

        template < typename T >
        inline bool will_addition_overflow(T a, T b)
        {
            return test_overflow<T>(a, b, '+');
        }

        template < typename T >
        inline bool will_subtraction_overflow(T a, T b)
        {
            return test_overflow<T>(a, b, '-');
        }

        template < typename T >
        inline bool will_multiplication_overflow(T a, T b)
        {
            return test_overflow<T>(a, b, '*');
        }

        template < typename T >
        inline bool will_addition_underflow(T a, T b)
        {
            return test_underflow<T>(a, b, '+');
        }

        template < typename T >
        inline bool will_subtraction_underflow(T a, T b)
        {
            return test_underflow<T>(a, b, '-');
        }

        template < typename T >
        inline bool will_multiplication_underflow(T a, T b)
        {
            return test_underflow<T>(a, b, '*');
        }
    } // namespace bits
}

#endif // OMNI_BITS_HPP
