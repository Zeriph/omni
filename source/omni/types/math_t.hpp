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
#include <omni/defs/math_def.hpp>
#include <omni/defs/math_radmap_def.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/string/util.hpp>
#include <functional>
#include <cstdarg>

namespace omni {
    namespace math {
        #if !defined(OMNI_NO_CONSTS)
            namespace compat {
                OMNI_CONSTEXT_FW const double PI OMNI_EXT_ASSN_FW(OMNI_MATH_COMPAT_PI);
                OMNI_CONSTEXT_FW const double E OMNI_EXT_ASSN_FW(OMNI_MATH_COMPAT_E);
                OMNI_CONSTEXT_FW const double TAU OMNI_EXT_ASSN_FW(OMNI_MATH_COMPAT_TAU);
            }

            OMNI_CONSTEXT_FW const double E OMNI_EXT_ASSN_FW(OMNI_E);
            OMNI_CONSTEXT_FW const double PI OMNI_EXT_ASSN_FW(OMNI_PI);
            OMNI_CONSTEXT_FW const double PI_180 OMNI_EXT_ASSN_FW(OMNI_PI_180);
            OMNI_CONSTEXT_FW const double TAU OMNI_EXT_ASSN_FW(OMNI_TAU);
            
            OMNI_CONSTEXT_FW const long double E_L OMNI_EXT_ASSN_FW(OMNI_E_L);
            OMNI_CONSTEXT_FW const long double PI_L OMNI_EXT_ASSN_FW(OMNI_PI_L);
            OMNI_CONSTEXT_FW const long double PI_L_180 OMNI_EXT_ASSN_FW(OMNI_PI_L_180);
            OMNI_CONSTEXT_FW const long double TAU_L OMNI_EXT_ASSN_FW(OMNI_TAU_L);
            
            OMNI_CONSTEXT_FW const float E_F OMNI_EXT_ASSN_FW(OMNI_E_F);
            OMNI_CONSTEXT_FW const float PI_F OMNI_EXT_ASSN_FW(OMNI_PI_F);
            OMNI_CONSTEXT_FW const float PI_F_180 OMNI_EXT_ASSN_FW(OMNI_PI_F_180);
            OMNI_CONSTEXT_FW const float TAU_F OMNI_EXT_ASSN_FW(OMNI_TAU_F);

            #if !defined(OMNI_NO_EXTERN_CONSTS)
                extern const double RADS[361];
                extern const double RADS_SIN[361];
                extern const double RADS_COS[361];
            #else
                const double RADS[] = OMNI_MATH_RADS;
                const double RADS_SIN[] = OMNI_MATH_RADS_SIN;
                const double RADS_COS[] = OMNI_MATH_RADS_COS;
            #endif
        #endif

        template < typename T >
        inline bool are_equal(T x, T y, T epsilon)
        {
            return std::fabs(x - y) <= epsilon;
        }

        template < typename T >
        inline bool are_equal(T x, T y)
        {
            return omni::math::are_equal(x, y, std::numeric_limits<T>::epsilon());
        }

        template <> inline bool are_equal<uint8_t>(uint8_t x, uint8_t y, uint8_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<int8_t>(int8_t x, int8_t y, int8_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<uint16_t>(uint16_t x, uint16_t y, uint16_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<int16_t>(int16_t x, int16_t y, int16_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<uint32_t>(uint32_t x, uint32_t y, uint32_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<int32_t>(int32_t x, int32_t y, int32_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<uint64_t>(uint64_t x, uint64_t y, uint64_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }
        template <> inline bool are_equal<int64_t>(int64_t x, int64_t y, int64_t epsilon) { OMNI_UNUSED(epsilon); return x == y; }

        template <> inline bool are_equal<bool>(bool x, bool y) { return x == y; }
        template <> inline bool are_equal<uint8_t>(uint8_t x, uint8_t y) { return x == y; }
        template <> inline bool are_equal<int8_t>(int8_t x, int8_t y) { return x == y; }
        template <> inline bool are_equal<uint16_t>(uint16_t x, uint16_t y) { return x == y; }
        template <> inline bool are_equal<int16_t>(int16_t x, int16_t y) { return x == y; }
        template <> inline bool are_equal<uint32_t>(uint32_t x, uint32_t y) { return x == y; }
        template <> inline bool are_equal<int32_t>(int32_t x, int32_t y) { return x == y; }
        template <> inline bool are_equal<uint64_t>(uint64_t x, uint64_t y) { return x == y; }
        template <> inline bool are_equal<int64_t>(int64_t x, int64_t y) { return x == y; }

        class angle_measure
        {
            public:
                typedef enum enum_t {
                    // Angle is less than 90 degrees
                    ACUTE = 0,
                    // Angle is more than 90 degrees
                    OBTUSE = 1,
                    // Angle is 90 degrees
                    RIGHT = 2
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return ACUTE;
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
                static bool try_parse(const std::string& val, angle_measure& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, angle_measure& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                angle_measure() :
                    OMNI_CTOR_FW(omni::math::angle_measure)
                    m_val(DEFAULT_VALUE())
                { }

                angle_measure(const angle_measure& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                angle_measure(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::angle_measure)
                    m_val(val)
                { }

                ~angle_measure()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const angle_measure& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                angle_measure& operator=(const angle_measure& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                angle_measure& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                angle_measure& operator=(int32_t val)
                {
                    if (!angle_measure::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const angle_measure& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const angle_measure& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const angle_measure& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::angle_measure) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::angle_measure)
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
                static bool _try_parse(const S& val, angle_measure& out)
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
                        OMNI_S2E_FW(ACUTE)
                        OMNI_S2E_FW(OBTUSE)
                        OMNI_S2E_FW(RIGHT)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(ACUTE);
                        OMNI_E2SS_FW(OBTUSE);
                        OMNI_E2SS_FW(RIGHT);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        ACUTE ||
                        OBTUSE ||
                        RIGHT
                    );
                }
        };

        class circle_area
        {
            public:
                typedef enum enum_t {
                    // Use the radius of the circle for area
                    RADIUS = 0,
                    // Use the diameter of the circle for area
                    DIAMETER = 1,
                    // Use the circumference of the circle for area
                    CIRCUMFERENCE = 2
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return RADIUS;
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
                static bool try_parse(const std::string& val, circle_area& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, circle_area& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                circle_area() :
                    OMNI_CTOR_FW(omni::math::circle_area)
                    m_val(DEFAULT_VALUE())
                { }

                circle_area(const circle_area& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                circle_area(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::circle_area)
                    m_val(val)
                { }

                ~circle_area()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const circle_area& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                circle_area& operator=(const circle_area& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                circle_area& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                circle_area& operator=(int32_t val)
                {
                    if (!circle_area::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const circle_area& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const circle_area& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const circle_area& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::circle_area) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::circle_area)
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
                static bool _try_parse(const S& val, circle_area& out)
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
                        OMNI_S2E_FW(RADIUS)
                        OMNI_S2E_FW(DIAMETER)
                        OMNI_S2E_FW(CIRCUMFERENCE)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(RADIUS);
                        OMNI_E2SS_FW(DIAMETER);
                        OMNI_E2SS_FW(CIRCUMFERENCE);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        RADIUS ||
                        DIAMETER ||
                        CIRCUMFERENCE
                    );
                }
        };

        class midpoint_rounding
        {
            public:
                typedef enum enum_t {
                    // When a number is halfway between two others, it is rounded toward the nearest even number.
                    TO_EVEN = 0,
                    // When a number is halfway between two others, it is rounded toward the nearest number that is away from zero.
                    AWAY_FROM_ZERO = 1,
                    // When a number is halfway between two others, it is rounded toward the result closest to and
                    // no greater in magnitude than the infinitely precise result.
                    TO_ZERO = 2,
                    // When a number is halfway between two others, it is rounded toward the result closest to and
                    // no greater than the infinitely precise result.
                    TO_NEGATIVE_INFINITY = 3,
                    // When a number is halfway between two others, it is rounded toward the result closest to and
                    // no less than the infinitely precise result.
                    TO_POSITIVE_INFINITY = 4
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 5;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return TO_EVEN;
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
                static bool try_parse(const std::string& val, midpoint_rounding& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, midpoint_rounding& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                midpoint_rounding() :
                    OMNI_CTOR_FW(omni::math::midpoint_rounding)
                    m_val(DEFAULT_VALUE())
                { }

                midpoint_rounding(const midpoint_rounding& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                midpoint_rounding(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::midpoint_rounding)
                    m_val(val)
                { }

                ~midpoint_rounding()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const midpoint_rounding& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                midpoint_rounding& operator=(const midpoint_rounding& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                midpoint_rounding& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                midpoint_rounding& operator=(int32_t val)
                {
                    if (!midpoint_rounding::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const midpoint_rounding& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const midpoint_rounding& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const midpoint_rounding& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::midpoint_rounding) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::midpoint_rounding)
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
                static bool _try_parse(const S& val, midpoint_rounding& out)
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
                        OMNI_S2E_FW(TO_EVEN)
                        OMNI_S2E_FW(AWAY_FROM_ZERO)
                        OMNI_S2E_FW(TO_ZERO)
                        OMNI_S2E_FW(TO_NEGATIVE_INFINITY)
                        OMNI_S2E_FW(TO_POSITIVE_INFINITY)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(TO_EVEN);
                        OMNI_E2SS_FW(AWAY_FROM_ZERO);
                        OMNI_E2SS_FW(TO_ZERO);
                        OMNI_E2SS_FW(TO_NEGATIVE_INFINITY);
                        OMNI_E2SS_FW(TO_POSITIVE_INFINITY);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        TO_EVEN || 
                        AWAY_FROM_ZERO || 
                        TO_ZERO || 
                        TO_NEGATIVE_INFINITY || 
                        TO_POSITIVE_INFINITY
                    );
                }
        };

        class ordinal_name
        {
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
                static bool is_valid(int32_t val)
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

                unsigned short count() const
                {
                    return COUNT();
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

                ordinal_name& operator=(int32_t val)
                {
                    if (!ordinal_name::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                ordinal_name operator|(const ordinal_name& val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val | val.m_val));
                }

                ordinal_name operator|(enum_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val | val));
                }

                ordinal_name operator|(int32_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val | val));
                }

                ordinal_name& operator|=(const ordinal_name& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                ordinal_name& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                ordinal_name& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                ordinal_name operator&(const ordinal_name& val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val & val.m_val));
                }

                ordinal_name operator&(enum_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val & val));
                }

                ordinal_name operator&(int32_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val & val));
                }

                ordinal_name& operator&=(const ordinal_name& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                ordinal_name& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                ordinal_name& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                ordinal_name& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                ordinal_name operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    ordinal_name ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                ordinal_name& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                ordinal_name operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    ordinal_name ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                ordinal_name operator~()
                {
                    return ordinal_name(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                ordinal_name operator^(const ordinal_name& val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                ordinal_name operator^(enum_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val ^ val));
                }

                ordinal_name operator^(int32_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val ^ val));
                }

                ordinal_name& operator^=(const ordinal_name& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                ordinal_name& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                ordinal_name& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                ordinal_name operator<<(const ordinal_name& val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val << val.m_val));
                }

                ordinal_name operator<<(enum_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val << val));
                }

                ordinal_name operator<<(int32_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val << val));
                }

                ordinal_name& operator<<=(const ordinal_name& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                ordinal_name& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                ordinal_name& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                ordinal_name operator>>(const ordinal_name& val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                ordinal_name operator>>(enum_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val >> val));
                }

                ordinal_name operator>>(int32_t val)
                {
                    return ordinal_name(static_cast<enum_t>(this->m_val >> val));
                }

                ordinal_name& operator>>=(const ordinal_name& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                ordinal_name& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                ordinal_name& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
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

                bool operator<(int32_t val) const
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

                bool operator>(int32_t val) const
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

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
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

                static bool _valid(int32_t val)
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

        class rotation
        {
            public:
                typedef enum enum_t {
                    // Rotate the shape about the origin (0,0)
                    ROTATE_ORIGIN = 0,
                    // Rotate the shape about the center point of the shape itself
                    ROTATE_AXIS = 1
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 2;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return ROTATE_ORIGIN;
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
                static bool try_parse(const std::string& val, rotation& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, rotation& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                rotation() :
                    OMNI_CTOR_FW(omni::math::rotation)
                    m_val(DEFAULT_VALUE())
                { }

                rotation(const rotation& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                rotation(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::rotation)
                    m_val(val)
                { }

                ~rotation()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const rotation& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                rotation& operator=(const rotation& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                rotation& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                rotation& operator=(int32_t val)
                {
                    if (!rotation::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const rotation& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const rotation& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const rotation& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::rotation) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::rotation)
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
                static bool _try_parse(const S& val, rotation& out)
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
                        OMNI_S2E_FW(ROTATE_ORIGIN)
                        OMNI_S2E_FW(ROTATE_AXIS)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(ROTATE_ORIGIN);
                        OMNI_E2SS_FW(ROTATE_AXIS);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        ROTATE_ORIGIN ||
                        ROTATE_AXIS
                    );
                }
        };

        class rotation_angle
        {
            public:
                typedef enum enum_t {
                    // Rotate 0 degrees
                    ZERO = 0,
                    // Rotate 90 degrees
                    NINETY = 90,
                    // Rotate 180 degrees
                    ONE_EIGHTY = 180,
                    // Rotate 270 degrees
                    TWO_SEVENTY = 270
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 4;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return ZERO;
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
                static bool try_parse(const std::string& val, rotation_angle& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, rotation_angle& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                rotation_angle() :
                    OMNI_CTOR_FW(omni::math::rotation_angle)
                    m_val(DEFAULT_VALUE())
                { }

                rotation_angle(const rotation_angle& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                rotation_angle(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::rotation_angle)
                    m_val(val)
                { }

                ~rotation_angle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const rotation_angle& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                rotation_angle& operator=(const rotation_angle& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                rotation_angle& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                rotation_angle& operator=(int32_t val)
                {
                    if (!rotation_angle::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const rotation_angle& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const rotation_angle& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const rotation_angle& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::rotation_angle) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::rotation_angle)
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
                static bool _try_parse(const S& val, rotation_angle& out)
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
                        OMNI_S2E_FW(ZERO)
                        OMNI_S2E_FW(NINETY)
                        OMNI_S2E_FW(ONE_EIGHTY)
                        OMNI_S2E_FW(TWO_SEVENTY)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(ZERO);
                        OMNI_E2SS_FW(NINETY);
                        OMNI_E2SS_FW(ONE_EIGHTY);
                        OMNI_E2SS_FW(TWO_SEVENTY);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        ZERO ||
                        NINETY ||
                        ONE_EIGHTY ||
                        TWO_SEVENTY
                    );
                }
        };

        class rotation_direction
        {
            public:
                typedef enum enum_t {
                    // Rotate the shape about the origin (0,0)
                    COUNTER_CLOCKWISE = 0,
                    // Rotate the shape about the center point of the shape itself
                    CLOCKWISE = 1
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 2;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return COUNTER_CLOCKWISE;
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
                static bool try_parse(const std::string& val, rotation_direction& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, rotation_direction& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                rotation_direction() :
                    OMNI_CTOR_FW(omni::math::rotation_direction)
                    m_val(DEFAULT_VALUE())
                { }

                rotation_direction(const rotation_direction& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                rotation_direction(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::rotation_direction)
                    m_val(val)
                { }

                ~rotation_direction()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const rotation_direction& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                rotation_direction& operator=(const rotation_direction& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                rotation_direction& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                rotation_direction& operator=(int32_t val)
                {
                    if (!rotation_direction::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const rotation_direction& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const rotation_direction& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const rotation_direction& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::rotation_direction) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::rotation_direction)
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
                static bool _try_parse(const S& val, rotation_direction& out)
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
                        OMNI_S2E_FW(COUNTER_CLOCKWISE)
                        OMNI_S2E_FW(CLOCKWISE)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(COUNTER_CLOCKWISE);
                        OMNI_E2SS_FW(CLOCKWISE);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        COUNTER_CLOCKWISE ||
                        CLOCKWISE
                    );
                }
        };

        class shape_comparator
        {
            public:
                typedef enum enum_t {
                    // The shapes are not similar or congruent
                    NOT_EQUAL = 0,
                    // The shapes are similar
                    SIMILAR = 1,
                    // The shapes are congruent
                    CONGRUENT = 2,
                    // The shapes are both congruent and similar
                    SIMILAR_CONGRUENT = 3 // bit mask of 1 & 2
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 4;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return NOT_EQUAL;
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
                static bool try_parse(const std::string& val, shape_comparator& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, shape_comparator& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                shape_comparator() :
                    OMNI_CTOR_FW(omni::math::shape_comparator)
                    m_val(DEFAULT_VALUE())
                { }

                shape_comparator(const shape_comparator& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                shape_comparator(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::shape_comparator)
                    m_val(val)
                { }

                ~shape_comparator()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const shape_comparator& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                shape_comparator& operator=(const shape_comparator& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                shape_comparator& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                shape_comparator& operator=(int32_t val)
                {
                    if (!shape_comparator::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                shape_comparator operator|(const shape_comparator& val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val | val.m_val));
                }

                shape_comparator operator|(enum_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val | val));
                }

                shape_comparator operator|(int32_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val | val));
                }

                shape_comparator& operator|=(const shape_comparator& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                shape_comparator& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                shape_comparator& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                shape_comparator operator&(const shape_comparator& val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val & val.m_val));
                }

                shape_comparator operator&(enum_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val & val));
                }

                shape_comparator operator&(int32_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val & val));
                }

                shape_comparator& operator&=(const shape_comparator& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                shape_comparator& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                shape_comparator& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                shape_comparator& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                shape_comparator operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    shape_comparator ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                shape_comparator& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                shape_comparator operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    shape_comparator ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                shape_comparator operator~()
                {
                    return shape_comparator(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                shape_comparator operator^(const shape_comparator& val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                shape_comparator operator^(enum_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val ^ val));
                }

                shape_comparator operator^(int32_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val ^ val));
                }

                shape_comparator& operator^=(const shape_comparator& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                shape_comparator& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                shape_comparator& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                shape_comparator operator<<(const shape_comparator& val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val << val.m_val));
                }

                shape_comparator operator<<(enum_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val << val));
                }

                shape_comparator operator<<(int32_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val << val));
                }

                shape_comparator& operator<<=(const shape_comparator& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                shape_comparator& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                shape_comparator& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                shape_comparator operator>>(const shape_comparator& val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                shape_comparator operator>>(enum_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val >> val));
                }

                shape_comparator operator>>(int32_t val)
                {
                    return shape_comparator(static_cast<enum_t>(this->m_val >> val));
                }

                shape_comparator& operator>>=(const shape_comparator& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                shape_comparator& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                shape_comparator& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const shape_comparator& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const shape_comparator& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const shape_comparator& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::shape_comparator) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::shape_comparator)
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
                static bool _try_parse(const S& val, shape_comparator& out)
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
                        OMNI_S2E_FW(NOT_EQUAL)
                        OMNI_S2E_FW(SIMILAR)
                        OMNI_S2E_FW(CONGRUENT)
                        OMNI_S2E_FW(SIMILAR_CONGRUENT)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NOT_EQUAL);
                        OMNI_E2SS_FW(SIMILAR);
                        OMNI_E2SS_FW(CONGRUENT);
                        OMNI_E2SS_FW(SIMILAR_CONGRUENT);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        NOT_EQUAL ||
                        SIMILAR ||
                        CONGRUENT ||
                        SIMILAR_CONGRUENT
                    );
                }
        };

        class transformation
        {
            public:
                typedef enum enum_t {
                    // Reflect the shape without changes the shape/size
                    REFLECTION = 0,
                    // "Slide" the shape without changing shape/size
                    TRANSLATE = 1
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 2;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return REFLECTION;
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
                static bool try_parse(const std::string& val, transformation& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, transformation& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                transformation() :
                    OMNI_CTOR_FW(omni::math::transformation)
                    m_val(DEFAULT_VALUE())
                { }

                transformation(const transformation& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                transformation(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::transformation)
                    m_val(val)
                { }

                ~transformation()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const transformation& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                transformation& operator=(const transformation& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                transformation& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                transformation& operator=(int32_t val)
                {
                    if (!transformation::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const transformation& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const transformation& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const transformation& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::transformation) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::transformation)
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
                static bool _try_parse(const S& val, transformation& out)
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
                        OMNI_S2E_FW(REFLECTION)
                        OMNI_S2E_FW(TRANSLATE)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(REFLECTION);
                        OMNI_E2SS_FW(TRANSLATE);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        REFLECTION ||
                        TRANSLATE
                    );
                }
        };

        class triangle_measure
        {
            public:
                typedef enum enum_t {
                    // The triangle is a 60/60/60
                    EQUILATERAL = 0,
                    // The triangle has 2 equal sides/angles
                    ISOSCELES = 1,
                    // The triangle has no equal sides/angles
                    SCALENE = 2
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return EQUILATERAL;
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
                static bool try_parse(const std::string& val, triangle_measure& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, triangle_measure& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                triangle_measure() :
                    OMNI_CTOR_FW(omni::math::triangle_measure)
                    m_val(DEFAULT_VALUE())
                { }

                triangle_measure(const triangle_measure& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                triangle_measure(enum_t val) : 
                    OMNI_CTOR_FW(omni::math::triangle_measure)
                    m_val(val)
                { }

                ~triangle_measure()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
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

                bool operator!=(const triangle_measure& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                triangle_measure& operator=(const triangle_measure& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                triangle_measure& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                triangle_measure& operator=(int32_t val)
                {
                    if (!triangle_measure::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const triangle_measure& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const triangle_measure& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const triangle_measure& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::math::triangle_measure) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::math::triangle_measure)
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
                static bool _try_parse(const S& val, triangle_measure& out)
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
                        OMNI_S2E_FW(EQUILATERAL)
                        OMNI_S2E_FW(ISOSCELES)
                        OMNI_S2E_FW(SCALENE)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(EQUILATERAL);
                        OMNI_E2SS_FW(ISOSCELES);
                        OMNI_E2SS_FW(SCALENE);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        EQUILATERAL ||
                        ISOSCELES ||
                        SCALENE
                    );
                }
        };

        template < typename T, std::size_t SZ >
        class dimensional
        {
            public:
                typedef T dimension_t;
                typedef T* iterator;
                typedef const T* const_iterator;

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

                dimensional(T val1, ...) : m_vals()
                {
                    va_list args;
                    va_start(args, val1);
                    this->m_vals[0] = val1;
                    for (size_t i = 1; i < SZ; ++i) {
                        this->m_vals[i] = va_arg(args, T);
                    }
                    va_end(args);
                }

                ~dimensional() {}

                T* begin() const
                {
                    return &(this->m_vals[0]);
                }

                T* end() const
                {
                    return &(this->m_vals[SZ]);
                }

                T at(std::size_t index) const
                {
                    if (index > SZ) {
                        OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), T());
                    }
                    return this->m_vals[index];
                }

                template < typename O_T, std::size_t O_SZ >
                void copy(const omni::math::dimensional<O_T, O_SZ>& o)
                {
                    std::size_t sz = (SZ < O_SZ) ? SZ : O_SZ;
                    for (std::size_t i = 0; i < sz; ++i) {
                        this->m_vals[i] = static_cast<T>(o[i]);
                    }
                }

                void copy(const dimensional& o)
                {
                    for (std::size_t i = 0; i < SZ; ++i) {
                        this->m_vals[i] = o.m_vals[i];
                    }
                }

                std::size_t size() const
                {
                    return SZ;
                }

                template < typename O_T, std::size_t O_SZ >
                void swap(omni::math::dimensional<O_T, O_SZ>& o)
                {
                    std::size_t sz = (SZ < O_SZ) ? SZ : O_SZ;
                    O_T otmp; T tmp;
                    for (std::size_t i = 0; i < sz; ++i) {
                        otmp = o[i];
                        tmp = this->m_vals[i];

                        o[i] = static_cast<O_T>(tmp);
                        this->m_vals[i] = static_cast<T>(otmp);
                    }
                }

                void swap(const dimensional& o)
                {
                    for (std::size_t i = 0; i < SZ; ++i) {
                        OMNI_XOR_SWAP(this->m_vals[i], o.m_vals[i]);
                    }
                }

                template < typename O_T, std::size_t O_SZ >
                dimensional& operator=(const omni::math::dimensional<O_T, O_SZ>& o) 
                {
                    std::size_t sz = (SZ < O_SZ) ? SZ : O_SZ;
                    for (std::size_t i = 0; i < sz; ++i) {
                        this->m_vals[i] = static_cast<T>(o[i]);
                    }
                    return *this;
                }

                dimensional& operator=(const dimensional& o) 
                {
                    this->copy(o);
                    return *this;
                }

                template < typename O_T, std::size_t O_SZ >
                bool operator==(const omni::math::dimensional<O_T, O_SZ>& o) const
                {
                    std::size_t sz = (SZ < O_SZ) ? SZ : O_SZ;
                    for (std::size_t i = 0; i < sz; ++i) {
                        if (!omni::math::are_equal(this->m_vals[i], static_cast<T>(o[i]))) {
                            return false;
                        }
                    }
                    return true;
                }

                bool operator==(const dimensional& o) const
                {
                    for (std::size_t i = 0; i < SZ; ++i) {
                        if (!omni::math::are_equal(this->m_vals[i], o.m_vals[i])) {
                            return false;
                        }
                    }
                    return true;
                }

                template < typename O_T, std::size_t O_SZ >
                bool operator!=(const omni::math::dimensional<O_T, O_SZ>& o) const
                {
                    std::size_t sz = (SZ < O_SZ) ? SZ : O_SZ;
                    for (std::size_t i = 0; i < sz; ++i) {
                        if (omni::math::are_equal(this->m_vals[i], static_cast<T>(o[i]))) {
                            return false;
                        }
                    }
                    return true;
                }

                bool operator!=(const dimensional& o) const
                {
                    for (std::size_t i = 0; i < SZ; ++i) {
                        if (omni::math::are_equal(this->m_vals[i], o.m_vals[i])) {
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

                OMNI_MEMBERS_FW(omni::math::dimensional<T, SZ>) // disposing,name,type(),hash()

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
    template < typename T, std::size_t SZ >
    inline void swap(omni::math::dimensional<T, SZ>& ot1, omni::math::dimensional<T, SZ>& ot2)
    {
        ot1.swap(ot2);
    }
}

#endif // OMNI_MATH_T_HPP
