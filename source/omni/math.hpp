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
#if !defined(OMNI_MATH_HPP)
#define OMNI_MATH_HPP 1

#include <omni/types/math_t.hpp>

namespace omni {
    namespace math {
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
        
        inline double rad_to_deg(double rad)
        {
            return rad * OMNI_180_PI; // degrees = radians * π / 180
        }

        inline double deg_to_rad(double deg)
        {
            return deg * OMNI_PI_180; // radians =  degrees * 180 / π
        }

        template < typename T >
        inline T delta(const T& a, const T& b)
        {
            return a - b;
        }

        template < typename T >
        inline T delta_squared(const T& a, const T& b)
        {
            return (a - b) * (a - b);
        }

        template < typename T >
        inline double area_of_circle(T radius)
        {
            return OMNI_PI * static_cast<double>(radius) * static_cast<double>(radius);
        }

        template < typename T >
        inline double area_circle_sector(T radius, T degrees)
        {
            return (static_cast<double>(degrees) / 360.0) * omni::math::area_of_circle(radius);
        }

        template < typename T >
        inline double radius_from_area(T area)
        {
            return std::sqrt(static_cast<long double>(area) / OMNI_PI);
        }

        template < typename T >
        inline double distance_between_2_points(T start_x, T start_y, T end_x, T end_y)
        {
            return std::sqrt(
                static_cast<long double>(omni::math::delta_squared(start_x, end_x)) +
                static_cast<long double>(omni::math::delta_squared(start_y, end_y)));
        }

        template < typename T >
        inline double distance_between_2_points(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
        {
            return std::sqrt(
                static_cast<long double>(omni::math::delta_squared(start_x, end_x)) +
                static_cast<long double>(omni::math::delta_squared(start_y, end_y)) +
                static_cast<long double>(omni::math::delta_squared(start_z, end_z)));
        }

        template < typename T >
        inline double distance_between_2_points(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
        {
            return omni::math::distance_between_2_points(start[0], start[1], end[0], end[1]);
        }

        template < typename T >
        inline double distance_between_2_points(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
        {
            return omni::math::distance_between_2_points(start[0], start[1], start[2], end[0], end[1], end[2]);
        }

        template < typename T >
        inline double lerp_y(T x1, T y1, T x2, T y2, T x)
        {
            return ((omni::math::delta(x, x1) * omni::math::delta(y2, y1) / omni::math::delta(x2, x1)) + y1);
        }

        template < typename T >
        inline double liner_interpolation_y(T x1, T y1, T x2, T y2, T x)
        {
            return omni::math::lerp_y<T>(x1, y1, x2, y2, x);
        }

        template < typename T >
        inline double lerp_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
        {
            return omni::math::lerp_y(start[0], start[1], end[0], end[1], x);
        }
        
        template < typename T >
        inline double liner_interpolation_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
        {
            return omni::math::lerp_y(start[0], start[1], end[0], end[1], x);
        }

        template < typename T >
        inline double lerp_x(T x1, T y1, T x2, T y2, T y)
        {
            return ((omni::math::delta(y, y1) * omni::math::delta(x2, x1) / omni::math::delta(y2, y1)) + x1);
        }

        template < typename T >
        inline double liner_interpolation_x(T x1, T y1, T x2, T y2, T y)
        {
            return omni::math::lerp_x<T>(x1, y1, x2, y2, y);
        }

        template < typename T >
        inline double lerp_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
        {
            return omni::math::lerp_x(start[0], start[1], end[0], end[1], y);
        }

        template < typename T >
        inline double liner_interpolation_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
        {
            return omni::math::lerp_x(start[0], start[1], end[0], end[1], y);
        }

        template < typename T >
        inline void midpoint(T start_x, T start_y, T end_x, T end_y, T& mid_x, T& mid_y)
        {
            mid_x = ((start_x + end_x) / 2);
            mid_y = ((start_y + end_y) / 2);
        }

        template < typename T >
        inline void midpoint3d(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z, T& mid_x, T& mid_y, T& mid_z)
        {
            mid_x = ((start_x + end_x) / 2);
            mid_y = ((start_y + end_y) / 2);
            mid_z = ((start_z + end_z) / 2);
        }

        template < typename T >
        inline omni::math::dimensional<T, 2> midpoint(T start_x, T start_y, T end_x, T end_y)
        {
            omni::math::dimensional<T, 2> ret;
            omni::math::midpoint<T>(start_x, start_y, end_x, end_y, ret[0], ret[1]);
            return ret;
        }

        template < typename T >
        inline omni::math::dimensional<T, 2> midpoint(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
        {
            omni::math::dimensional<T, 2> ret;
            omni::math::midpoint<T>(start[0], start[1], end[0], end[1], ret[0], ret[1]);
            return ret;
        }

        template < typename T >
        inline omni::math::dimensional<T, 3> midpoint3d(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
        {
            omni::math::dimensional<T, 3> ret;
            omni::math::midpoint3d<T>(start_x, start_y, start_z, end_x, end_y, end_z, ret[0], ret[1], ret[2]);
            return ret;
        }

        template < typename T >
        inline omni::math::dimensional<T, 3> midpoint3d(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
        {
            omni::math::dimensional<T, 3> ret;
            omni::math::midpoint3d<T>(start[0], start[1], start[2], end[0], end[1], end[2], ret[0], ret[1], ret[2]);
            return ret;
        }

        template < typename T >
        inline omni::math::ordinal_name octant(T x, T y, T z)
        {
            // x+ = 001000 =  8, x- = 000100 = 4
            // y+ = 000010 =  2, y- = 000001 = 1
            // z+ = 100000 = 32, z- = 010000 = 16
            switch (
                ((z > 0) ? (1<<5) : ((z < 0) ? (1<<4) : 0)) | 
                ((x > 0) ? (1<<3) : ((x < 0) ? (1<<2) : 0)) | 
                ((y > 0) ? (1<<1) : ((y < 0) ? 1 : 0))
            )
            {
                case 42: case 10: return omni::math::ordinal_name::I;     // +++ = 101010 = 42/10 = quad 1
                case 38: case  6: return omni::math::ordinal_name::II;    // -++ = 100110 =  38/6 = quad 2
                case 37: case  5: return omni::math::ordinal_name::III;   // --+ = 100101 =  37/5 = quad 3
                case 41: case  9: return omni::math::ordinal_name::IV;    // +-+ = 101001 =  41/9 = quad 4
                case 26: return omni::math::ordinal_name::V;              // ++- = 011010 = 26 = quad 5
                case 22: return omni::math::ordinal_name::VI;             // -+- = 010110 = 22 = quad 6
                case 21: return omni::math::ordinal_name::VII;            // --- = 010101 = 21 = quad 7
                case 25: return omni::math::ordinal_name::VIII;           // +-- = 011001 = 25 = quad 8
                // x,0,z
                case 40: return omni::math::ordinal_name::I_IV;           // +0+ = 101000 = 40 = quads 1 & 4
                case 24: return omni::math::ordinal_name::V_VIII;         // +0- = 011000 = 24 = quads 5 & 8
                case 36: return omni::math::ordinal_name::II_III;         // -0+ = 100100 = 36 = quads 2 & 3
                case 20: return omni::math::ordinal_name::VI_VII;         // -0- = 010100 = 20 = quads 6 & 7
                // 0,y,z
                case 34: return omni::math::ordinal_name::I_II;           // 0++ = 100010 = 34 = quads 1 & 2
                case 18: return omni::math::ordinal_name::V_VI;           // 0+- = 010010 = 18 = quads 5 & 6
                case 33: return omni::math::ordinal_name::III_IV;         // 0-+ = 100001 = 33 = quads 3 & 4
                case 17: return omni::math::ordinal_name::VII_VIII;       // 0-- = 010001 = 17 = quads 7 & 8
                // 0,0,0
                case 8: case 4: return omni::math::ordinal_name::X_AXIS;  // 001000/000100 =  8/4  = X
                case 2: case 1: return omni::math::ordinal_name::Y_AXIS;  // 000010/000001 =  2/1  = Y
                case 32: case 16: return omni::math::ordinal_name::Z_AXIS;// 100000/010000 = 32/16 = Z
                default: break;
            }
            return omni::math::ordinal_name::ORIGIN;
        }

        template < typename T >
        inline omni::math::ordinal_name octant(const omni::math::dimensional<T, 3>& point)
        {
            return omni::math::octant<T>(point[0], point[1], point[2]);
        }

        template < typename T >
        inline void point_on_circle(T angle, T radius, T center_x, T center_y, T& out_x, T& out_y)
        {
            if (angle > static_cast<T>(360)) {
                OMNI_ERR_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"))
            }
            out_x = OMNI_MATH_GET_POINT_X_FW(T, center_x, radius, angle);
            out_y = OMNI_MATH_GET_POINT_Y_FW(T, center_y, radius, angle);
        }

        template <> inline void point_on_circle<int64_t>(int64_t angle, int64_t radius, int64_t center_x, int64_t center_y, int64_t& out_x, int64_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(int64_t, out_x, out_y, center_x, center_y, radius, angle); }
        template <> inline void point_on_circle<uint64_t>(uint64_t angle, uint64_t radius, uint64_t center_x, uint64_t center_y, uint64_t& out_x, uint64_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(uint64_t, out_x, out_y, center_x, center_y, radius, angle); }
        template <> inline void point_on_circle<int32_t>(int32_t angle, int32_t radius, int32_t center_x, int32_t center_y, int32_t& out_x, int32_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(int32_t, out_x, out_y, center_x, center_y, radius, angle); }
        template <> inline void point_on_circle<uint32_t>(uint32_t angle, uint32_t radius, uint32_t center_x, uint32_t center_y, uint32_t& out_x, uint32_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(uint32_t, out_x, out_y, center_x, center_y, radius, angle); }
        template <> inline void point_on_circle<int16_t>(int16_t angle, int16_t radius, int16_t center_x, int16_t center_y, int16_t& out_x, int16_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(int16_t, out_x, out_y, center_x, center_y, radius, angle); }
        template <> inline void point_on_circle<uint16_t>(uint16_t angle, uint16_t radius, uint16_t center_x, uint16_t center_y, uint16_t& out_x, uint16_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(uint16_t, out_x, out_y, center_x, center_y, radius, angle); }
        template <> inline void point_on_circle<int8_t>(int8_t angle, int8_t radius, int8_t center_x, int8_t center_y, int8_t& out_x, int8_t& out_y) { out_x = OMNI_MATH_GET_POINT_X_INT_FW(int8_t, center_x, radius, angle); out_y = OMNI_MATH_GET_POINT_Y_INT_FW(int8_t, center_y, radius, angle); }
        template <> inline void point_on_circle<uint8_t>(uint8_t angle, uint8_t radius, uint8_t center_x, uint8_t center_y, uint8_t& out_x, uint8_t& out_y) { out_x = OMNI_MATH_GET_POINT_X_INT_FW(uint8_t, center_x, radius, angle); out_y = OMNI_MATH_GET_POINT_Y_INT_FW(uint8_t, center_y, radius, angle); }

        template < typename T >
        inline omni::math::ordinal_name quadrant(T x, T y)
        {
            // x+ = 1000 = 8, x- = 0100 = 4
            // y+ = 0010 = 2, y- = 0001 = 1
            switch (
                ((x > 0) ? (1<<3) : ((x < 0) ? (1<<2) : 0)) |
                ((y > 0) ? (1<<1) : ((y < 0) ? 1 : 0))
            )
            {
                case 10: return omni::math::ordinal_name::I; // ++ = 1010 = 10 = quad 1
                case  6: return omni::math::ordinal_name::II; // -+ = 0110 =  6 = quad 2
                case  5: return omni::math::ordinal_name::III; // -- = 0101 =  5 = quad 3
                case  9: return omni::math::ordinal_name::IV; // +- = 1001 =  9 = quad 4
                case 8: case 4: return omni::math::ordinal_name::X_AXIS; // 1000/0100 = 8/4 = X
                case 2: case 1: return omni::math::ordinal_name::Y_AXIS; // 0010/0001 = 2/1 = Y
                default: break;
            }
            return omni::math::ordinal_name::ORIGIN;
        }

        template < typename T >
        inline omni::math::ordinal_name quadrant(const omni::math::dimensional<T, 2>& point)
        {
            return omni::math::quadrant<T>(point[0], point[1]);
        }

        template < typename T >
        inline void quadratic(T a, T b, T c, T& x_plus, T& x_minus)
        {
            if (omni::math::are_equal(a, T(0))) {
                OMNI_ERR_FW("division by zero, a must not be 0", omni::exceptions::invalid_range("division by zero, a must not be 0"))
            }
            x_plus = ((-b) + std::sqrt(static_cast<long double>((b * b) - (4 * a * c)))) / (2 * a);
            x_minus = ((-b) - std::sqrt(static_cast<long double>((b * b) - (4 * a * c)))) / (2 * a);
        }

        template < typename T >
        inline omni::math::dimensional<T, 2> quadratic(T a, T b, T c)
        {
            omni::math::dimensional<T, 2> ret;
            omni::math::quadratic<T>(a, b, c, ret[0], ret[1]);
            return ret;
        }

        template < typename T >
        inline double slope(T start_x, T start_y, T end_x, T end_y)
        {
            if (omni::math::are_equal(start_x, end_x)) {
                OMNI_ERR_RETV_FW("division by zero, x values equal", omni::exceptions::invalid_range("division by zero, x values equal"), 0.0)
            }
            return static_cast<double>(end_y - start_y) / static_cast<double>(end_x - start_x);
        }

        template < typename T >
        inline double slope(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
        {
            return omni::math::slope(start[0], start[1], end[0], end[1]);
        }

        template < typename T >
        inline T summation(T index, T end, const omni::delegate1<T, T>& sum)
        {
            T val;
            if (sum) {
                val = sum(index);
                for (T i = index+1; i <= end; ++i) {
                    val += sum(i);
                }
            } else {
                val = index;
                for (T i = index+1; i <= end; ++i) {
                    val += i;
                }
            }
            return val;
        }
    }
}

#endif // OMNI_MATH_HPP
