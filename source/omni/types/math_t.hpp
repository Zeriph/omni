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
#if !defined(OMNI_MATH_T_HPP)
#define OMNI_MATH_T_HPP 1
#include <omni/defs/global.hpp>

#if defined(OMNI_OS_WIN)
    /* DEV_NOTE: MSVC emits warning 4351 about the dimensional class having it's array value
    initialied in the member init list, e.g. `dimensional() : m_vals() {}`. This is considered
    "new" behavior by MSVC but is perfectly fine behavior per the C++ standard, this 0-init's
    the values in the array (as if memset were called). This is the behavior we want and since
    we are targetting C++03 and above, this is a non-issue. Additionally, testing this behavior
    against MSVC 2008 and above (and inspecting the asm) shows we get the results we want. */
    #if !defined(OMNI_WIN_NO_PRAGMA_DISABLE_4351)
        #pragma warning (disable:4351)
    #endif
#endif

#if !defined(OMNI_PI_F) // float
    #if defined (OMNI_USE_M_PI) && defined(M_PI)
        #define OMNI_PI_F static_cast<float>(M_PI)
    #else
        #define OMNI_PI_F 3.1415926F
    #endif
    #define OMNI_PI_F_180 0.0174533F
    #define OMNI_180_PI_F 57.2957805F
#endif

#if !defined(OMNI_PI) // double
    #if defined (OMNI_USE_M_PI) && defined(M_PI)
        #define OMNI_PI M_PI
    #else
        #define OMNI_PI 3.14159265358979323846
    #endif
    #define OMNI_PI_180 0.01745329251994329577
    #define OMNI_180_PI 57.29577951308232087684
#endif

#if !defined(OMNI_PI_L) // long double
    #if defined (OMNI_USE_M_PI_L) && defined(M_PIl)
        #define OMNI_PI_L M_PIl
    #else
        #define OMNI_PI_L 3.141592653589793238462643383279502884L
    #endif
    #define OMNI_PI_L_180 0.017453292519943295769236907684886127L
    #define OMNI_180_PI_L 57.295779513082320876798154814105170336L
#endif

namespace omni {
    namespace math {
        #if !defined(OMNI_NO_EXTERN_CONSTS)
            extern const double      PI;
            extern const long double PI_L;
            extern const float       PI_F;
            extern const double      PI_180;
            extern const long double PI_L_180;
            extern const float       PI_F_180;
            extern const double      RADS[361];
            extern const double      RADS_SIN[361];
            extern const double      RADS_COS[361];
        #else
            const double      PI = OMNI_PI;
            const long double PI_L = OMNI_PI_L;
            const float       PI_F = OMNI_PI_F;
            const double      PI_180 = OMNI_PI_180;
            const long double PI_L_180 = OMNI_PI_L_180;
            const float       PI_F_180 = OMNI_PI_F_180;
            #define OMNI_MATH_RAD_MAP_FW
            #include <omni/xx/math_radmap.hxx>
            #undef OMNI_MATH_RAD_MAP_FW
        #endif

        class ordinal_name {
            public:
                typedef enum enum_t {
                    Z_AXIS = -3,
                    Y_AXIS = -2,
                    X_AXIS = -1,
                    ORIGIN = 0,
                    I = 1,
                    II = 2,
                    III = 4,
                    IV = 8,
                    V = 16,
                    VI = 32,
                    VII = 64,
                    VIII = 128,
                    I_IV = (I | IV),
                    V_VIII = (V | VIII),
                    II_III = (II | III),
                    VI_VII = (VI | VII),
                    I_II = (I | II),
                    V_VI = (V | VI),
                    III_IV = (III | IV),
                    VII_VIII = (VII | VIII)
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 20;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return ORIGIN;
                }

                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, ordinal_name& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, ordinal_name& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int val)
                {
                    return _valid(val);
                }
                
                ordinal_name() :
                    OMNI_CTOR_FW(omni::math::ordinal_name)
                    m_val(DEFAULT_VALUE())
                { }

                ordinal_name(const ordinal_name& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                ordinal_name(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::ordinal_name)
                    m_val(val)
                { }

                ~ordinal_name()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const ordinal_name& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                ordinal_name& operator=(const ordinal_name& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                ordinal_name& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                ordinal_name& operator=(int val)
                {
                    if (!ordinal_name::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const ordinal_name& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const ordinal_name& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const ordinal_name& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator int32_t() const
                {
                    return static_cast<int32_t>(this->m_val);
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::ordinal_name) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::ordinal_name)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    OMNI_ERR_FW("invalid enum parse", omni::exceptions::invalid_enum())
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, ordinal_name& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(Z_AXIS)
                        OMNI_S2E_FW(Y_AXIS)
                        OMNI_S2E_FW(X_AXIS)
                        OMNI_S2E_FW(ORIGIN)
                        OMNI_S2E_FW(I)
                        OMNI_S2E_FW(II)
                        OMNI_S2E_FW(III)
                        OMNI_S2E_FW(IV)
                        OMNI_S2E_FW(V)
                        OMNI_S2E_FW(VI)
                        OMNI_S2E_FW(VII)
                        OMNI_S2E_FW(VIII)
                        OMNI_S2E_FW(I_IV)
                        OMNI_S2E_FW(V_VIII)
                        OMNI_S2E_FW(II_III)
                        OMNI_S2E_FW(VI_VII)
                        OMNI_S2E_FW(I_II)
                        OMNI_S2E_FW(V_VI)
                        OMNI_S2E_FW(III_IV)
                        OMNI_S2E_FW(VII_VIII)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(Z_AXIS);
                        OMNI_E2SS_FW(Y_AXIS);
                        OMNI_E2SS_FW(X_AXIS);
                        OMNI_E2SS_FW(ORIGIN);
                        OMNI_E2SS_FW(I);
                        OMNI_E2SS_FW(II);
                        OMNI_E2SS_FW(III);
                        OMNI_E2SS_FW(IV);
                        OMNI_E2SS_FW(V);
                        OMNI_E2SS_FW(VI);
                        OMNI_E2SS_FW(VII);
                        OMNI_E2SS_FW(VIII);
                        OMNI_E2SS_FW(I_IV);
                        OMNI_E2SS_FW(V_VIII);
                        OMNI_E2SS_FW(II_III);
                        OMNI_E2SS_FW(VI_VII);
                        OMNI_E2SS_FW(I_II);
                        OMNI_E2SS_FW(V_VI);
                        OMNI_E2SS_FW(III_IV);
                        OMNI_E2SS_FW(VII_VIII);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        Z_AXIS || 
                        Y_AXIS || 
                        X_AXIS || 
                        ORIGIN || 
                        I || 
                        II || 
                        III || 
                        IV || 
                        V || 
                        VI || 
                        VII || 
                        VIII || 
                        I_IV || 
                        V_VIII || 
                        II_III || 
                        VI_VII || 
                        I_II || 
                        V_VI || 
                        III_IV || 
                        VII_VIII
                    );
                }
        };

        template < typename T, size_t SZ >
        class dimensional
        {
            public:
                typedef T dimension_t;

                dimensional() : m_vals() {}

                dimensional(const dimensional& cp) : m_vals()
                {
                    this->copy(cp);
                }

                dimensional(T vals[SZ]) : m_vals()
                {
                    for (std::size_t i = 0; i < SZ; ++i) {
                        this->m_vals[i] = vals[i];
                    }
                }

                ~dimensional() {}

                T at(std::size_t index)
                {
                    if (index > SZ) {
                        OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), T());
                    }
                    return this->m_vals[index];
                }

                void copy(const dimensional& o)
                {
                    for (size_t i = 0; i < SZ; ++i) {
                        this->m_vals[i] = o.m_vals[i];
                    }
                }

                size_t size() const
                {
                    return SZ;
                }

                void swap(const dimensional& o)
                {
                    for (size_t i = 0; i < SZ; ++i) {
                        OMNI_XOR_SWAP(this->m_vals[i], o.m_vals[i]);
                    }
                }

                dimensional& operator=(const dimensional& o) 
                {
                    this->copy(o);
                    return *this;
                }

                bool operator==(const dimensional& o)
                {
                    for (size_t i = 0; i < SZ; ++i) {
                        if (this->m_vals[i] != o.m_vals[i]) {
                            return false;
                        }
                    }
                    return true;
                }

                T& operator[](std::size_t idx)
                {
                    return this->m_vals[idx];
                }

                T operator[](std::size_t idx) const
                {
                    return this->m_vals[idx];
                }

                std::string to_string() const
                {
                    std::stringstream ss;
                    ss << "{";
                    for (std::size_t i = 0; i < SZ; ++i) {
                        ss << this->m_vals[i];
                        if ((i + 1) < SZ) { ss << ","; }
                    }
                    ss << "}";
                    return ss.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream ss;
                    ss << "{";
                    for (std::size_t i = 0; i < SZ; ++i) {
                        ss << this->m_vals[i];
                        if ((i + 1) < SZ) { ss << ","; }
                    }
                    ss << "}";
                    return ss.str();
                }
                
                operator std::string()
                {
                    return this->to_string();
                }

                operator std::wstring()
                {
                    return this->to_wstring();
                }

                friend std::ostream& operator<<(std::ostream& os, const dimensional& v)
                {
                    os << v.to_string();
                    return os;
                }

                friend std::wostream& operator<<(std::wostream& os, const dimensional& v)
                {
                    os << v.to_wstring();
                    return os;
                }

            private:
                mutable T m_vals[SZ];
        };
    }
}

namespace std {
    template < typename T, size_t SZ >
    inline void swap(omni::math::dimensional<T, SZ>& ot1, omni::math::dimensional<T, SZ>& ot2)
    {
        ot1.swap(ot2);
    }
}

#endif // OMNI_MATH_T_HPP
