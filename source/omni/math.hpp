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

// TODO: make notes in the docs here that using a non floating point type could result in truncation of values

namespace omni {
    namespace math {
        template < typename T >
        inline double calculate_angle_radians(T x, T y, T bx, T by, T cx, T cy)
        {
            double c = OMNI_DISTANCE_2POINTS_2D_FW(x, y, bx, by);
            double b = OMNI_DISTANCE_2POINTS_2D_FW(x, y, cx, cy);
            if (omni::math::are_equal(b, 0.0) || omni::math::are_equal(c, 0.0)) {
                return 0.0;
            }
            double cb = OMNI_DISTANCE_2POINTS_2D_FW(bx, by, cx, cy);
            return std::acos(((b * b) + (c * c) - (cb * cb)) / (2.0 * b * c));
        }

        template < typename T >
        inline double calculate_angle_radians(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
        {
            return omni::math::calculate_angle_radians(a[0], a[1], b[0], b[1], c[0], c[1]);
        }

        template < typename T >
        inline double calculate_angle(T x, T y, T bx, T by, T cx, T cy)
        {
            return OMNI_RAD_TO_DEG(omni::math::calculate_angle_radians(x, y, bx, by, cx, cy));
        }

        template < typename T >
        inline double calculate_angle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
        {
            return omni::math::calculate_angle(a[0], a[1], b[0], b[1], c[0], c[1]);
        }

        template < typename T >
        inline void point_on_circle_unsafe(double degrees, double radius, T center_x, T center_y, T& out_x, T& out_y)
        {
            out_x = static_cast<T>(OMNI_MATH_GET_POINT_X_FW(T, center_x, radius, degrees));
            out_y = static_cast<T>(OMNI_MATH_GET_POINT_Y_FW(T, center_y, radius, degrees));
        }

        template < typename T >
        inline void rotate_point(double degrees, const omni::math::rotation_direction& dir, T center_x, T center_y, T& rotate_x, T& rotate_y)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            if (omni::math::are_equal(degrees, 0.0) || omni::math::are_equal(degrees, 360.0)) {
                return; // no rotation
            }
            // build the triangle to get the angle based on relative location to the center
            // point. The center point is treated like the origin so we need the angle of
            // inflection first, then we can calculate the new value
            if (center_x < rotate_x) {
                if (center_y < rotate_y) {
                    // quad 1
                    /*

                        {cx,ry}|  / rx,ry
                               |a/
                               |/
                               ----------------
                            cx,cy 

                    */
                    degrees = (omni::math::calculate_angle(center_x, center_y, rotate_x, rotate_y, center_x, rotate_y)) +
                              ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                } else if (center_y > rotate_y) {
                    // quad 2
                    /*

                        cx,cy  {rx,cy}
                            ----------------
                            |\a
                            | \
                            |  \ rx,ry
                        
                    */
                    degrees = (omni::math::calculate_angle(center_x, center_y, rotate_x, rotate_y, rotate_x, center_y) + 90.0) + 
                              ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                } else { // center_y == rotate_y
                    // quad 1
                    /*
                             |
                        ---cx,cy----------rx,ry---
                             |
                    */
                    degrees = 90.0 + ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                }
            } else if (center_x > rotate_x) {
                if (center_y > rotate_y) {
                    // quad 3
                    /*

                                    cx,cy
                        -----------------
                                     /a|
                                    /  |
                            rx,ry  /   |{cx,ry}
                        
                    */
                    degrees = (omni::math::calculate_angle(center_x, center_y, rotate_x, rotate_y, center_x, rotate_y) + 180.0) +
                              ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                } else if (center_y < rotate_y) {
                    // quad 4
                    /*

                            rx,ry  \  |
                                    \ |
                                    a\|
                        ----------------
                            {rx,cy}   cx,cy
                        
                    */
                    degrees = (omni::math::calculate_angle(center_x, center_y, rotate_x, rotate_y, rotate_x, center_y) + 270.0) +
                              ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                } else { // center_y == rotate_y
                    // quad 3
                    /*
                                            |
                        ---rx,ry----------cx,cy---
                                            |
                    */
                    degrees = 270.0 + ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                }
            } else { // center_x == rotate_x
                if (center_y < rotate_y) {
                    // quad 1
                    /*
                             |
                           rx,ry
                             |
                             |
                             |
                        ---cx,cy--
                             |
                    */
                    degrees = ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                } else if (center_y > rotate_y) {
                    // quad 3
                    /*
                             |
                        ---cx,cy--
                             |
                             |
                             |
                           rx,ry
                             |
                    */
                    degrees = 180.0 + ((dir == omni::math::rotation_direction::CLOCKWISE) ? degrees : (-degrees));
                } else { // center_y == rotate_y
                    // cx == rx && cy == ry .. same points, no rotation
                    return;
                }
            }

            // rotate the point now based on the new angle of inflection
            
            if (degrees > 360.0) { degrees = degrees - 360; }
            else if (degrees < 0.0) { degrees = degrees + 360; }
            omni::math::point_on_circle_unsafe(
                degrees,
                static_cast<double>(OMNI_DISTANCE_2POINTS_2D_FW(center_x, center_y, rotate_x, rotate_y)),
                center_x, center_y,
                rotate_x, rotate_y);
        }

        template < typename T >
        inline void rotate_point(double degrees, const omni::math::rotation_direction& dir, T center_x, T center_y, omni::math::dimensional<T, 2>& rotate)
        {
            omni::math::rotate_point(degrees, dir, center_x, center_y, rotate[0], rotate[1]);
        }

        template < typename T >
        inline void rotate_point(double degrees, const omni::math::rotation_direction& dir, const omni::math::dimensional<T, 2>& center, omni::math::dimensional<T, 2>& rotate)
        {
            omni::math::rotate_point(degrees, dir, center[0], center[1], rotate[0], rotate[1]);
        }

        template < typename T >
        inline double area_of_circle(T radius)
        {
            return OMNI_PI * static_cast<double>(radius * radius);
        }

        template < typename T >
        inline double area_of_circle(T value, const omni::math::circle_area& type)
        {
            switch (type) {
                case omni::math::circle_area::RADIUS:
                    return OMNI_PI * static_cast<double>(value * value);
                case omni::math::circle_area::DIAMETER:
                    return (OMNI_PI / 4) * (value * value);
                case omni::math::circle_area::CIRCUMFERENCE:
                    return static_cast<double>(value * value) / (4 * OMNI_PI);
                default:
                    OMNI_ERR_FW("invalid area type specified", omni::exceptions::index_out_of_range("invalid area type specified"))
                    break;
            }
            return 0.0;
        }

        template < typename T >
        inline double area_of_circle_sector(T radius, double degrees)
        {
            return ((degrees * OMNI_PI) / 360.0) * (radius * radius);
        }

        template < typename T >
        inline double area_of_circle_segment(T radius, double degrees)
        {
            return ((((degrees * OMNI_PI) / 360.0) - (std::sin(OMNI_DEG_TO_RAD(degrees)) / 2.0)) * (static_cast<double>(radius) * radius));
        }

        template < typename T >
        inline T area_of_rectangle(T width, T height)
        {
            return width * height;
        }

        template < typename T >
        inline double area_of_triangle(T base, T height)
        {
            return 0.5 * (base * height);
        }

        template < typename T >
        inline double area_of_triangle_sss(T a, T b, T c)
        {
            // Heron's formula
            double s = static_cast<double>(a + b + c) * 0.5; // (s = (a+b+c+) / 2.0;
            return std::sqrt( (s*(s - a)) * (s*(s - b)) * (s*(s - c)) );
        }

        template < typename T >
        inline double area_of_triangle_sas(double degrees, T side1, T side2)
        {
            return (0.5 * side1 * side2) * std::sin(OMNI_DEG_TO_RAD(degrees));
        }

        template < typename T >
        inline double area_of_triangle(double degrees, T side1, T side2)
        {
            return omni::math::area_of_triangle_sas(degrees, side1, side2);
        }

        template < typename T >
        inline double area_of_triangle(T ax, T ay, T bx, T by, T cx, T cy)
        {
            return omni::math::area_of_triangle(
                omni::math::calculate_angle(ax, ay, bx, by, cx, cy),
                OMNI_DISTANCE_2POINTS_2D_FW(ax, ay, bx, by),
                OMNI_DISTANCE_2POINTS_2D_FW(ax, ay, cx, cy)
            );
        }

        template < typename T >
        inline double area_of_quadrilateral(T a, T b, T c, T d, double angle_a_degrees, double angle_c_degrees)
        {
            // Bretschneider's formula
            double s = static_cast<double>(a + b + c + d) / 2.0;
            return std::sqrt(
                ((s - a) * (s - b) * (s - c) * (s - d)) -
                (
                    0.5 * (a * b * c * d) *
                    (
                        1 + std::cos(OMNI_DEG_TO_RAD((angle_a_degrees + angle_c_degrees)))
                    )
                )
            );
        }

        inline double arc_length(double radius, double degrees)
        {
            return radius * OMNI_PI_180 * degrees;
        }

        template < typename T >
        inline T delta(T a, T b)
        {
            return a - b;
        }

        template < typename T >
        inline T delta_squared(T a, T b)
        {
            return (a - b) * (a - b);
        }

        template < typename T >
        inline void calculate_point(T start_x, T start_y, T end_x, T end_y, T len, T& out_x, T& out_y)
        {
            double dist = OMNI_DISTANCE_2POINTS_2D_FW(start_x, start_y, end_x, end_y);
            double seg_rat = (omni::math::are_equal(dist, 0.0) ? static_cast<double>(len) : (static_cast<double>(len) / dist));
            out_x = static_cast<T>((seg_rat * static_cast<double>(end_x)) + ((1.0 - seg_rat) * static_cast<double>(start_x)));
            out_y = static_cast<T>((seg_rat * static_cast<double>(end_y)) + ((1.0 - seg_rat) * static_cast<double>(start_y)));
        }

        template < typename T >
        inline void calculate_point(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, omni::math::dimensional<T, 2>& out)
        {
            omni::math::calculate_point(start[0], start[1], end[0], end[1], out[0], out[1]);
        }

        template < typename T >
        inline omni::math::dimensional<T, 2> calculate_point(T start_x, T start_y, T end_x, T end_y, T len)
        {
            omni::math::dimensional<T, 2> ret;
            omni::math::calculate_point<T>(start_x, start_y, end_x, end_y, len, ret[0], ret[1]);
            return ret;
        }

        template < typename T >
        inline omni::math::dimensional<T, 2> calculate_point(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T len)
        {
            return omni::math::calculate_point(start[0], start[1], end[0], end[1], len);
        }

        template < typename T >
        inline double circle_circumference(T radius)
        {
            return OMNI_PI * static_cast<double>(radius) * 2.0;
        }

        template < typename T >
        inline bool circle_contains_point(T center_x, T center_y, double radius, T x, T y, bool include_edge)
        {
            return OMNI_CIRCLE_CONTAINS_POINT_FW(center_x, center_y, radius, x, y, include_edge);
        }

        template < typename T >
        inline bool circle_contains_point(T center_x, T center_y, double radius, T x, T y)
        {
            return OMNI_CIRCLE_CONTAINS_POINT_FW(center_x, center_y, radius, x, y, true);
        }

        template < typename T >
        inline bool circle_contains_point(T center_x, T center_y, double radius, const omni::math::dimensional<T, 2>& point, bool include_edge)
        {
            return OMNI_CIRCLE_CONTAINS_POINT_FW(center_x, center_y, radius,  point[0], point[1], include_edge);
        }

        template < typename T >
        inline bool circle_contains_point(T center_x, T center_y, double radius, const omni::math::dimensional<T, 2>& point)
        {
            return OMNI_CIRCLE_CONTAINS_POINT_FW(center_x, center_y, radius,  point[0], point[1], true);
        }

        template < typename T >
        inline bool circles_intersect(T x1, T y1, double r1, T x2, T y2, double r2, bool include_edge)
        {
            return (include_edge ?
                (OMNI_DISTANCE_2POINTS_2D_FW(x1, y1, x2, y2) <= (r1 + r2)) :
                (OMNI_DISTANCE_2POINTS_2D_FW(x1, y1, x2, y2) < (r1 + r2))
            );
        }

        template < typename T >
        inline bool circles_intersect(T x1, T y1, double r1, T x2, T y2, double r2)
        {
            return omni::math::circles_intersect<T>(x1, y1, r1, x2, y2, r2, true);
        }

        inline double deg_to_rad(double deg)
        {
            return OMNI_DEG_TO_RAD(deg); // radians =  degrees * 180 / π
        }

        inline double degrees_to_radians(double deg)
        {
            return OMNI_DEG_TO_RAD(deg); // radians =  degrees * 180 / π
        }

        template < typename T >
        inline double distance_between_2_points(T start_x, T start_y, T end_x, T end_y)
        {
            return OMNI_DISTANCE_2POINTS_2D_FW(start_x, start_y, end_x, end_y);
        }

        template < typename T >
        inline double distance_between_2_points(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
        {
            return OMNI_DISTANCE_2POINTS_3D_FW(start_x, start_y, start_z, end_x, end_y, end_z);
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
        inline void extend_line(T start_x, T start_y, T end_x, T end_y, T length, T& out_x, T& out_y)
        {
            omni::math::calculate_point(start_x, start_y, end_x, end_y, length, out_x, out_y);
        }

        template < typename T >
        inline void extend_line(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T length, omni::math::dimensional<T, 2>& out)
        {
            return omni::math::extend_line(start[0], start[1], end[0], end[1], length, out[0], out[1]);
        }

        inline bool is_nan(long double val)
        {
            #if defined(OMNI_ENABLE_CXX)
                return std::isnan(val);
            #else
                #if defined(OMNI_OS_WIN)
                    #if defined(isnan)
                        return ::isnan(val) != 0;
                    #else
                        return ::_isnan(val) != 0;
                    #endif
                #else
                    #if defined(isnan)
                        return ::isnan(val) == 1;
                    #else
                        return val != val;
                    #endif
                #endif
            #endif
        }

        inline bool is_nan(double val)
        {
            #if defined(OMNI_ENABLE_CXX)
                return std::isnan(val);
            #else
                #if defined(OMNI_OS_WIN)
                    #if defined(isnan)
                        return isnan(val) != 0;
                    #else
                        return _isnan(val) != 0;
                    #endif
                #else
                    #if defined(isnan)
                        return isnan(val) == 1;
                    #else
                        return val != val;
                    #endif
                #endif
            #endif
        }

        inline bool is_nan(float val)
        {
            #if defined(OMNI_ENABLE_CXX)
                return std::isnan(val);
            #else
                #if defined(OMNI_OS_WIN)
                    #if defined(isnan)
                        return isnan(val) != 0;
                    #else
                        return _isnan(val) != 0;
                    #endif
                #else
                    #if defined(isnan)
                        return isnan(val) == 1;
                    #else
                        return val != val;
                    #endif
                #endif
            #endif
        }

        template < typename T >
        inline double lerp_y(T x1, T y1, T x2, T y2, T x)
        {
            if (omni::math::are_equal(x2, x1)) {
                return static_cast<double>(y1 + y2) / 2;
            }
            return (((x - x1) * (y2 - y1) / (x2 - x1)) + y1);
        }

        template < typename T >
        inline double linear_interpolation_y(T x1, T y1, T x2, T y2, T x)
        {
            return omni::math::lerp_y<T>(x1, y1, x2, y2, x);
        }

        template < typename T >
        inline double lerp_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
        {
            return omni::math::lerp_y(start[0], start[1], end[0], end[1], x);
        }
        
        template < typename T >
        inline double linear_interpolation_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
        {
            return omni::math::lerp_y(start[0], start[1], end[0], end[1], x);
        }

        template < typename T >
        inline double lerp_x(T x1, T y1, T x2, T y2, T y)
        {
            if (omni::math::are_equal(y2, y1)) {
                return static_cast<double>(x1 + x2) / 2;
            }
            return (((y - y1) * (x2 - x1) / (y2 - y1)) + x1);
        }

        template < typename T >
        inline double linear_interpolation_x(T x1, T y1, T x2, T y2, T y)
        {
            return omni::math::lerp_x<T>(x1, y1, x2, y2, y);
        }

        template < typename T >
        inline double lerp_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
        {
            return omni::math::lerp_x(start[0], start[1], end[0], end[1], y);
        }

        template < typename T >
        inline double linear_interpolation_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
        {
            return omni::math::lerp_x(start[0], start[1], end[0], end[1], y);
        }

        template < typename T >
        inline bool lines_intersect(T line1_x1, T line1_y1, T line1_x2, T line1_y2, T line2_x1, T line2_y1, T line2_x2, T line2_y2)
        {
            /*
            det = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4)

            TODO: to find the intersection point:
            {Px, Py} = {
                (x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4) / det
                ,
                (x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4) / det
            }

            */
            T det = ((line1_x1 - line1_x2) * (line2_y1 - line2_y2)) - ((line1_y1 - line1_y2) * (line2_x1 - line2_x2));
            if (omni::math::are_equal(det, static_cast<T>(0))) { return false; }
            double t = ((line1_x1 - line2_x1) * (line2_y1 - line2_y2)) - ((line1_y1 - line2_y1) * (line2_x1 - line2_x2));
            double u = ((line1_x1 - line1_x2) * (line1_y1 - line2_y1)) - ((line1_y1 - line1_y2) * (line1_x1 - line2_x1));
            if (((0.0 <= t) && (t <= 1.0)) || ((0.0 <= u) && (u <= 1.0))) { return true; }
            double px = ((((line1_x1 * line1_y2) - (line1_y1 * line1_x2)) * (line2_x1 - line2_x2)) - ((line1_x1 - line1_x2) * ((line2_x1 * line2_y2) - (line2_y1 * line2_x2)))) / det;
            double py = ((((line1_x1 * line1_y2) - (line1_y1 * line1_x2)) * (line2_y1 - line2_y2)) - ((line1_y1 - line1_y2) * ((line2_x1 * line2_y2) - (line2_y1 * line2_x2)))) / det;
            if (omni::math::are_equal(px, 0.0) || omni::math::are_equal(py, 0.0)) { return false; }
            return true;
        }

        template < typename T >
        inline bool lines_intersect(const omni::math::dimensional<T, 2>& line1_start, const omni::math::dimensional<T, 2>& line1_end, const omni::math::dimensional<T, 2>& line2_start, const omni::math::dimensional<T, 2>& line2_end)
        {
            return omni::math::lines_intersect(
                line1_start[0], line1_start[1],
                line1_end[0], line1_end[1],
                line2_start[0], line2_start[1],
                line2_end[0], line2_end[1]
            );
        }

        template < typename T >
        inline bool lines_intersect(const omni::math::dimensional<T, 4>& line1, const omni::math::dimensional<T, 4>& line2)
        {
            return omni::math::lines_intersect(
                line1[0], line1[1], line1[2], line1[3],
                line2[0], line2[1], line2[2], line2[3]
            );
        }

        template < typename T >
        inline void midpoint(T start_x, T start_y, T end_x, T end_y, T& mid_x, T& mid_y)
        {
            mid_x = ((start_x + end_x) / 2);
            mid_y = ((start_y + end_y) / 2);
        }

        template < typename T >
        inline void midpoint(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, omni::math::dimensional<T, 2>& out)
        {
            omni::math::midpoint(start[0], start[1], end[0], end[1], out[0], out[1]);
        }

        template < typename T >
        inline void midpoint3d(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z, T& mid_x, T& mid_y, T& mid_z)
        {
            mid_x = ((start_x + end_x) / 2);
            mid_y = ((start_y + end_y) / 2);
            mid_z = ((start_z + end_z) / 2);
        }

        template < typename T >
        inline void midpoint3d(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end, omni::math::dimensional<T, 3>& out)
        {
            omni::math::midpoint3d(start[0], start[1], start[2], end[0], end[1], end[2], out[0], out[1], out[2]);
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
        inline void point_on_circle(double degrees, double radius, T center_x, T center_y, T& out_x, T& out_y)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            omni::math::point_on_circle_unsafe(degrees, radius, center_x, center_y, out_x, out_y);
        }

        template <> inline void point_on_circle<int64_t>(double degrees, double radius, int64_t center_x, int64_t center_y, int64_t& out_x, int64_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(int64_t, out_x, out_y, center_x, center_y, radius, degrees); }
        template <> inline void point_on_circle<uint64_t>(double degrees, double radius, uint64_t center_x, uint64_t center_y, uint64_t& out_x, uint64_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(uint64_t, out_x, out_y, center_x, center_y, radius, degrees); }
        template <> inline void point_on_circle<int32_t>(double degrees, double radius, int32_t center_x, int32_t center_y, int32_t& out_x, int32_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(int32_t, out_x, out_y, center_x, center_y, radius, degrees); }
        template <> inline void point_on_circle<uint32_t>(double degrees, double radius, uint32_t center_x, uint32_t center_y, uint32_t& out_x, uint32_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(uint32_t, out_x, out_y, center_x, center_y, radius, degrees); }
        template <> inline void point_on_circle<int16_t>(double degrees, double radius, int16_t center_x, int16_t center_y, int16_t& out_x, int16_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(int16_t, out_x, out_y, center_x, center_y, radius, degrees); }
        template <> inline void point_on_circle<uint16_t>(double degrees, double radius, uint16_t center_x, uint16_t center_y, uint16_t& out_x, uint16_t& out_y) { OMNI_MATH_GET_POINT_INT_FW(uint16_t, out_x, out_y, center_x, center_y, radius, degrees); }
        template <> inline void point_on_circle<int8_t>(double degrees, double radius, int8_t center_x, int8_t center_y, int8_t& out_x, int8_t& out_y) { out_x = OMNI_MATH_GET_POINT_X_INT_FW(int8_t, center_x, radius, degrees); out_y = OMNI_MATH_GET_POINT_Y_INT_FW(int8_t, center_y, radius, degrees); }
        template <> inline void point_on_circle<uint8_t>(double degrees, double radius, uint8_t center_x, uint8_t center_y, uint8_t& out_x, uint8_t& out_y) { out_x = OMNI_MATH_GET_POINT_X_INT_FW(uint8_t, center_x, radius, degrees); out_y = OMNI_MATH_GET_POINT_Y_INT_FW(uint8_t, center_y, radius, degrees); }

        template < typename T >
        inline void point_on_circle(double degrees, T radius, const omni::math::dimensional<T, 2>& center, omni::math::dimensional<T, 2>& out)
        {
            return omni::math::point_on_circle(degrees, radius, center[0], center[1], out[0], out[1]);
        }

        template < typename T >
        inline void quadrant(T x, T y, omni::math::ordinal_name::enum_t& quad)
        {
            // x+ = 1000 = 8, x- = 0100 = 4
            // y+ = 0010 = 2, y- = 0001 = 1
            switch (
                ((x > 0) ? (1<<3) : ((x < 0) ? (1<<2) : 0)) |
                ((y > 0) ? (1<<1) : ((y < 0) ? 1 : 0))
            )
            {
                case 10: quad = omni::math::ordinal_name::I; break; // ++ = 1010 = 10 = quad 1
                case  6: quad = omni::math::ordinal_name::II; break; // -+ = 0110 =  6 = quad 2
                case  5: quad = omni::math::ordinal_name::III; break; // -- = 0101 =  5 = quad 3
                case  9: quad = omni::math::ordinal_name::IV; break; // +- = 1001 =  9 = quad 4
                case 8: case 4: quad = omni::math::ordinal_name::X_AXIS; break; // 1000/0100 = 8/4 = X
                case 2: case 1: quad = omni::math::ordinal_name::Y_AXIS; break; // 0010/0001 = 2/1 = Y
                default: quad = omni::math::ordinal_name::ORIGIN; break;
            }
        }

        template < typename T >
        inline omni::math::ordinal_name quadrant(T x, T y)
        {
            omni::math::ordinal_name::enum_t ret;
            omni::math::quadrant<T>(x, y, ret);
            return ret;
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
            x_plus = ((-b) + std::sqrt(static_cast<double>((b * b) - (4 * a * c)))) / (2 * a);
            x_minus = ((-b) - std::sqrt(static_cast<double>((b * b) - (4 * a * c)))) / (2 * a);
        }

        template < typename T >
        inline omni::math::dimensional<T, 2> quadratic(T a, T b, T c)
        {
            omni::math::dimensional<T, 2> ret;
            omni::math::quadratic<T>(a, b, c, ret[0], ret[1]);
            return ret;
        }

        template < typename T >
        inline bool quadrilateral_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T dx1, T dy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2, T dx2, T dy2)
        {
            return omni::math::lines_intersect(ax1, ay1, bx1, by1, ax2, ay2, bx2, by2) ||
                   omni::math::lines_intersect(ax1, ay1, bx1, by1, bx2, by2, cx2, cy2) ||
                   omni::math::lines_intersect(ax1, ay1, bx1, by1, cx2, cy2, dx2, dy2) ||
                   omni::math::lines_intersect(ax1, ay1, bx1, by1, dx2, dy2, ax2, ay2) ||

                   omni::math::lines_intersect(bx1, by1, cx1, cy1, ax2, ay2, bx2, by2) ||
                   omni::math::lines_intersect(bx1, by1, cx1, cy1, bx2, by2, cx2, cy2) ||
                   omni::math::lines_intersect(bx1, by1, cx1, cy1, cx2, cy2, dx2, dy2) ||
                   omni::math::lines_intersect(bx1, by1, cx1, cy1, dx2, dy2, ax2, ay2) ||

                   omni::math::lines_intersect(cx1, cy1, dx1, dy1, ax2, ay2, bx2, by2) ||
                   omni::math::lines_intersect(cx1, cy1, dx1, dy1, bx2, by2, cx2, cy2) ||
                   omni::math::lines_intersect(cx1, cy1, dx1, dy1, cx2, cy2, dx2, dy2) ||
                   omni::math::lines_intersect(cx1, cy1, dx1, dy1, dx2, dy2, ax2, ay2) ||

                   omni::math::lines_intersect(dx1, dy1, ax1, ay1, ax2, ay2, bx2, by2) ||
                   omni::math::lines_intersect(dx1, dy1, ax1, ay1, bx2, by2, cx2, cy2) ||
                   omni::math::lines_intersect(dx1, dy1, ax1, ay1, cx2, cy2, dx2, dy2) ||
                   omni::math::lines_intersect(dx1, dy1, ax1, ay1, dx2, dy2, ax2, ay2);
        }

        template < typename T >
        inline void quadrilateral_reflect(T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            ax = -ax; bx = -bx; cx = -cx; dx = -dx;
            ay = -ay; by = -by; cy = -cy; dy = -dy;
        }

        template < typename T >
        inline void quadrilateral_rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            omni::math::rotate_point(degrees, dir, x, y, ax, ay);
            omni::math::rotate_point(degrees, dir, x, y, bx, by);
            omni::math::rotate_point(degrees, dir, x, y, cx, cy);
            omni::math::rotate_point(degrees, dir, x, y, dx, dy);
        }

        template < typename T >
        inline void quadrilateral_rotate_origin(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            if (omni::math::are_equal(degrees, 0.0) || omni::math::are_equal(degrees, 360.0)) {
                return; // no rotation
            } else if (omni::math::are_equal(degrees, 180.0)) {
                // (x, y) -> (-x, -y)
                ax = -ax; bx = -bx; cx = -cx; dx = -dx;
                ay = -ay; by = -by; cy = -cy; dy = -dy;
            } else {
                bool ts = omni::math::are_equal(degrees, 270.0);
                bool nt = (!ts && omni::math::are_equal(degrees, 90.0));
                bool cw = (dir == omni::math::rotation_direction::CLOCKWISE);
                if ((nt && cw) || (ts && !cw)) {
                    // (x, y) -> (y, -x)
                    std::swap(ax, ay); ay = -ay;
                    std::swap(bx, by); by = -by;
                    std::swap(cx, cy); cy = -cy;
                    std::swap(dx, dy); dy = -dy;
                } else if ((ts && cw) || (nt && !cw)) {
                    // (x, y) -> (-y, x)
                    std::swap(ax, ay); ax = -ax;
                    std::swap(bx, by); bx = -bx;
                    std::swap(cx, cy); cx = -cx;
                    std::swap(dx, dy); dx = -dx;
                } else {
                    omni::math::quadrilateral_rotate_point<T>(degrees, 0, 0, dir, ax, ay, bx, by, cx, cy, dx, dy);
                }
            }
        }

        template < typename T >
        inline void quadrilateral_translate_xy(T x, T y, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            ax += x; bx += x; cx += x; dx += x;
            ay += y; by += y; cy += y; dy += y;
        }

        template < typename T >
        inline void quadrilateral_translate_angle(double degrees, T distance, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            if (omni::math::are_equal(degrees, 0.0) || omni::math::are_equal(degrees, 360.0)) {
                // no rotational translation, just add distance to all the y pairs
                omni::math::quadrilateral_translate_xy(static_cast<T>(0), distance, ax, ay, bx, by, cx, cy, dx, dy);
            } else {
                omni::math::point_on_circle(degrees, distance, ax, ay, ax, ay);
                omni::math::point_on_circle(degrees, distance, bx, by, bx, by);
                omni::math::point_on_circle(degrees, distance, cx, cy, cx, cy);
                omni::math::point_on_circle(degrees, distance, dx, dy, dx, dy);
            }
        }

        inline double rad_to_deg(double rad)
        {
            return OMNI_RAD_TO_DEG(rad); // degrees = radians * π / 180
        }

        inline double radians_to_degrees(double rad)
        {
            return OMNI_RAD_TO_DEG(rad); // degrees = radians * π / 180
        }

        template < typename T >
        inline double radius_from_area(T area)
        {
            return std::sqrt(static_cast<double>(area) / OMNI_PI);
        }

        template < typename T >
        inline void rectangle_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
        {
            T w, x, y, z;
            omni::math::midpoint(ax, ay, cx, cy, x, y);
            omni::math::midpoint(bx, by, dx, dy, w, z);
            out_x = (omni::math::are_equal(x, w) ? x : w);
            out_y = (omni::math::are_equal(y, z) ? y : z);
        }

        template < typename T >
        inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, T x2, T y2)
        {
            return OMNI_RECT_XYWH_CONTAINS_FW(x, y, w, h, x2, y2);
        }

        template < typename T >
        inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, const omni::math::dimensional<T, 2>& point)
        {
            return OMNI_RECT_XYWH_CONTAINS_FW(x, y, w, h, point[0], point[1]);
        }

        template < typename T >
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, T x, T y)
        {
            return OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, x, y);
        }

        template < typename T >
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, const omni::math::dimensional<T, 2>& point)
        {
            return OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, point[0], point[1]);
        }

        template < typename T >
        inline void rectangle_reflect(T& x, T& y, T w, T h)
        {
            x = -x; x -= w;
            y = -y; y -= h;
        }

        template < typename T >
        inline void rectangle_translate_xy(T x, T y, T& ax, T& ay)
        {
            ax += x; 
            ay += y;
        }

        template < typename T >
        inline void rectangle_translate_angle(double degrees, T distance, T& ax, T& ay)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            if (omni::math::are_equal(degrees, 0.0) || omni::math::are_equal(degrees, 360.0)) {
                // no rotational translation, just add distance to all the x pairs
                omni::math::rectangle_translate_xy(static_cast<T>(0), distance, ax, ay);
            } else {
                omni::math::point_on_circle(static_cast<T>(degrees), distance, ax, ay, ax, ay);
            }
        }

        template < typename T >
        inline void rectangle_rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& w, T& h)
        {
            if (!omni::math::rotation_angle::is_valid(static_cast<int>(degrees.value()))) {
                OMNI_ERR_FW("angle must be between 0, 90, 180 or 270 degrees", omni::exceptions::overflow_error("angle must be between 0, 90, 180 or 270 degrees"))
            }
            if (degrees == omni::math::rotation_angle::ZERO) { return; }  // no rotation
            double deg = 0; double nx = 0; double ny = 0;
            switch (degrees) {
                case omni::math::rotation_angle::NINETY:
                    deg = ((dir == omni::math::rotation_direction::COUNTER_CLOCKWISE) ? 270.0 : 90.0);
                    std::swap(w, h);
                    break;
                case omni::math::rotation_angle::ONE_EIGHTY: deg = 180.0; break;
                case omni::math::rotation_angle::TWO_SEVENTY:
                    deg = ((dir == omni::math::rotation_direction::COUNTER_CLOCKWISE) ? 90.0 : 270.0);
                    std::swap(w, h);
                    break;
                case omni::math::rotation_angle::ZERO:
                default: break;
            }
            omni::math::point_on_circle<double>(deg, omni::math::distance_between_2_points<double>(x, y, static_cast<double>(ax), static_cast<double>(ay)), x, y, nx, ny);
            ax = static_cast<T>(nx);
            ay = static_cast<T>(ny);
        }

        template < typename T >
        inline void rectangle_rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& w, T& h)
        {
            if (!omni::math::rotation_angle::is_valid(static_cast<int>(degrees.value()))) {
                OMNI_ERR_FW("angle must be between 0, 90, 180 or 270 degrees", omni::exceptions::overflow_error("angle must be between 0, 90, 180 or 270 degrees"))
            }
            if (degrees == omni::math::rotation_angle::ZERO) { return; }  // no rotation
            if (degrees == omni::math::rotation_angle::ONE_EIGHTY) {
                // (x, y) -> (-x, -y) (180 about origin)
                ax = -ax; ay = -ay;
                ax -= w;
            } else {
                std::swap(w, h);
                bool ts = (degrees == omni::math::rotation_angle::TWO_SEVENTY);
                bool nt = (!ts && (degrees == omni::math::rotation_angle::NINETY));
                bool cw = (dir == omni::math::rotation_direction::CLOCKWISE);
                if ((nt && cw) || (ts && !cw)) {
                    // (x, y) -> (y, -x) (270 about origin)
                    std::swap(ax, ay);
                    ay = -ay;
                } else if ((ts && cw) || (nt && !cw)) {
                    // (x, y) -> (-y, x) (90 about origin)
                    std::swap(ax, ay);
                    ax = -ax;
                    ay += h;
                } else {
                    omni::math::rectangle_rotate_point<T>(degrees, 0, 0, dir, ax, ay, w, h);
                }
            }
        }

        inline double round(double val, uint8_t digits, const omni::math::midpoint_rounding& direction)
        {
            if (digits > OMNI_MATH_MAX_ROUND_DIGITS_FW) {
                OMNI_ERR_RETV_FW("Invalid range specified for rounding digit", omni::exceptions::invalid_range(), val);
            }
            if (std::fabs(val) < OMNI_MATH_ROUND_LIMIT_FW) {
                double p = std::pow(10.0, static_cast<double>(digits));
                val *= p;
                double f = std::modf(val , &val);
                if ((std::fabs(f) > 0.5) || omni::math::are_equal(std::fabs(f), 0.5)) {
                    switch (direction) {
                        case omni::math::midpoint_rounding::AWAY_FROM_ZERO:
                            //if (static_cast<int64_t>(val) % 2 != 0) {}
                            val += ((f < 0) ? -1 : 1);
                            break;
                        case omni::math::midpoint_rounding::TO_EVEN:
                            if (static_cast<int64_t>(val) % 2 != 0) {
                                val += ((f < 0) ? -1 : 1);
                            }
                            break;
                        case omni::math::midpoint_rounding::TO_ZERO:
                            val += ((f < 0) ? 1 : -1);
                            break;
                        case omni::math::midpoint_rounding::TO_NEGATIVE_INFINITY:
                            val += -1;
                            break;
                        case omni::math::midpoint_rounding::TO_POSITIVE_INFINITY:
                            val += 1;
                            break;
                        default: break;
                    }
                }
                val /= p;
            }
            return val;
        }

        inline double round(double val, uint8_t digits, std::float_round_style direction)
        {
            switch (direction) {
                case std::round_to_nearest: // Rounding toward nearest representable value
                    return omni::math::round(val, digits, omni::math::midpoint_rounding::TO_EVEN);
                case std::round_toward_zero: // Rounding toward zero
                    return omni::math::round(val, digits, omni::math::midpoint_rounding::TO_ZERO);
                case std::round_toward_neg_infinity: // Rounding toward negative infinity 
                    return omni::math::round(val, digits, omni::math::midpoint_rounding::TO_NEGATIVE_INFINITY);
                case std::round_toward_infinity: // Rounding toward positive infinity
                    return omni::math::round(val, digits, omni::math::midpoint_rounding::TO_POSITIVE_INFINITY);
                case std::round_indeterminate: // Rounding style cannot be determined
                default: break;
            }
            return omni::math::round(val, digits, omni::math::midpoint_rounding::AWAY_FROM_ZERO);
        }

        inline double round(double val, uint8_t digits)
        {
            return omni::math::round(val, digits, omni::math::midpoint_rounding::TO_EVEN);
        }

        inline double round(double val)
        {
            return omni::math::round(val, 0, omni::math::midpoint_rounding::TO_EVEN);
        }

        template < typename T >
        inline void rotate_point(double degrees, T center_x, T center_y, T& rotate_x, T& rotate_y)
        {
            omni::math::rotate_point(degrees, omni::math::rotation_direction::CLOCKWISE, center_x, center_y, rotate_x, rotate_y);
        }

        template < typename T >
        inline void rotate_point(double degrees, T center_x, T center_y, omni::math::dimensional<T, 2>& rotate)
        {
            omni::math::rotate_point(degrees, omni::math::rotation_direction::CLOCKWISE, center_x, center_y, rotate[0], rotate[1]);
        }

        template < typename T >
        inline void rotate_point(double degrees, const omni::math::dimensional<T, 2>& center, omni::math::dimensional<T, 2>& rotate)
        {
            omni::math::rotate_point(degrees, omni::math::rotation_direction::CLOCKWISE, center[0], center[1], rotate[0], rotate[1]);
        }

        template < typename T >
        inline T sign(T val)
        {
            if (omni::math::are_equal(val, T(0))) {
                return 0;
            }
            if (val < 1) {
                return -1;
            }
            return 1;
        }

        template < typename T >
        inline double slope(T start_x, T start_y, T end_x, T end_y)
        {
            if (!omni::math::are_equal(start_x, end_x)) {
                return static_cast<double>(end_y - start_y) / static_cast<double>(end_x - start_x);
            }
            return 0.0;
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

        template < typename T >
        inline T summation(T index, T end, const omni::delegate1<T, T>& sum, const omni::delegate1<bool, T>& break_cond)
        {
            T val;
            if (sum) {
                val = sum(index);
                for (T i = index+1; i <= end; ++i) {
                    val += sum(i);
                    if (break_cond(val)) { break; }
                }
            } else {
                val = index;
                for (T i = index+1; i <= end; ++i) {
                    val += i;
                    if (break_cond(val)) { break; }
                }
            }
            return val;
        }
        
        template < typename T >
        inline bool triangle_contains_point(T x, T y, T ax, T ay, T bx, T by, T cx, T cy)
        {
            T s = (ay * cx) - (ax * cy) + ((cy - ay) * x) + ((ax - cx) * y);
            T t = (ax * by) - (ay * bx) + ((ay - by) * x) + ((bx - ax) * y);
            if ((s < 0) != (t < 0)) {
                return false;
            }
            T A = (-by * cx) + (ay * (cx - bx)) + (ax * (by - cy)) + (bx * cy);

            return (A < 0) ?
                ((s <= 0) && (s + t >= A)) :
                ((s >= 0) && (s + t <= A));
        }

        template < typename T >
        inline bool triangle_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2)
        {
            return omni::math::lines_intersect(ax1, ay1, bx1, by1, ax2, ay2, bx2, by2) || // AB.1 -> AB.2
                   omni::math::lines_intersect(ax1, ay1, bx1, by1, bx2, by2, cx2, cy2) || // AB.1 -> BC.2
                   omni::math::lines_intersect(ax1, ay1, bx1, by1, cx2, cy2, ax2, ay2) || // AB.1 -> CA.2

                   omni::math::lines_intersect(bx1, by1, cx1, cy1, ax2, ay2, bx2, by2) || // BC.1 -> AB.2
                   omni::math::lines_intersect(bx1, by1, cx1, cy1, bx2, by2, cx2, cy2) || // BC.1 -> BC.2
                   omni::math::lines_intersect(bx1, by1, cx1, cy1, cx2, cy2, ax2, ay2) || // BC.1 -> CA.2

                   omni::math::lines_intersect(cx1, cy1, ax1, ay1, ax2, ay2, bx2, by2) || // CA.1 -> AB.2
                   omni::math::lines_intersect(cx1, cy1, ax1, ay1, bx2, by2, cx2, cy2) || // CA.1 -> BC.2
                   omni::math::lines_intersect(cx1, cy1, ax1, ay1, cx2, cy2, ax2, ay2);   // CA.1 -> CA.2
        }

        template < typename T >
        inline void triangle_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
        {
            out_x = static_cast<T>(static_cast<double>(ax + bx + cx) / 3);
            out_y = static_cast<T>(static_cast<double>(ay + by + cy) / 3);
        }

        template < typename T >
        inline void triangle_get_incenter(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
        {
            double sA = ((bx + by) >= (cx + cy) ? omni::math::distance_between_2_points(bx, by, cx, cy) : omni::math::distance_between_2_points(cx, cy, bx, by));
            double sB = ((ax + ay) >= (cx + cy) ? omni::math::distance_between_2_points(ax, ay, cx, cy) : omni::math::distance_between_2_points(cx, cy, ax, ay));
            double sC = ((ax + ay) >= (bx + by) ? omni::math::distance_between_2_points(ax, ay, bx, by) : omni::math::distance_between_2_points(bx, by, ax, ay));
            double per = sA + sB + sC;
            if (omni::math::are_equal(per, 0.0)) { // a 0 perimiter?
                out_x = static_cast<T>(static_cast<double>(ax + bx + cx) / 3);
                out_y = static_cast<T>(static_cast<double>(ay + by + cy) / 3);
            } else {
                out_x = static_cast<T>(((sA * ax) + (sB * bx) + (sC * cx)) / per);
                out_y = static_cast<T>(((sA * ay) + (sB * by) + (sC * cy)) / per);
            }
        }

        template < typename T >
        inline void triangle_get_circumcenter(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
        {
            double sinA = std::sin(OMNI_DEG_TO_RAD((2 * omni::math::calculate_angle(ax, ay, bx, by, cx, cy))));
            double sinB = std::sin(OMNI_DEG_TO_RAD((2 * omni::math::calculate_angle(bx, by, ax, ay, cx, cy))));
            double sinC = std::sin(OMNI_DEG_TO_RAD((2 * omni::math::calculate_angle(cx, cy, bx, by, ax, ay))));
            double per = sinA + sinB + sinC;
            if (omni::math::are_equal(per, 0.0)) { // a 0 perimiter?
                out_x = static_cast<T>(static_cast<double>(ax + bx + cx) / 3);
                out_y = static_cast<T>(static_cast<double>(ay + by + cy) / 3);
            } else {
                out_x = static_cast<T>(((ax * sinA) + (bx * sinB) + (cx * sinC)) / per);
                out_y = static_cast<T>(((ay * sinA) + (by * sinB) + (cy * sinC)) / per);
            }
        }

        template < typename T >
        inline void triangle_reflect(T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            ax = -ax; bx = -bx; cx = -cx;
            ay = -ay; by = -by; cy = -cy;
        }

        template < typename T >
        inline void triangle_rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            omni::math::rotate_point(degrees, dir, x, y, ax, ay);
            omni::math::rotate_point(degrees, dir, x, y, bx, by);
            omni::math::rotate_point(degrees, dir, x, y, cx, cy);
        }

        template < typename T >
        inline void triangle_rotate_origin(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            if (omni::math::are_equal(degrees, 0.0) || omni::math::are_equal(degrees, 360.0)) {
                return; // no rotation
            } else if (omni::math::are_equal(degrees, 180.0)) {
                // (x, y) -> (-x, -y)
                ax = -ax; bx = -bx; cx = -cx;
                ay = -ay; by = -by; cy = -cy;
            } else {
                bool ts = omni::math::are_equal(degrees, 270.0);
                bool nt = (!ts && omni::math::are_equal(degrees, 90.0));
                bool cw = (dir == omni::math::rotation_direction::CLOCKWISE);
                if ((nt && cw) || (ts && !cw)) {
                    // (x, y) -> (y, -x)
                    std::swap(ax, ay); ay = -ay;
                    std::swap(bx, by); by = -by;
                    std::swap(cx, cy); cy = -cy;
                } else if ((ts && cw) || (nt && !cw)) {
                    // (x, y) -> (-y, x)
                    std::swap(ax, ay); ax = -ax;
                    std::swap(bx, by); bx = -bx;
                    std::swap(cx, cy); cx = -cx;
                } else {
                    omni::math::triangle_rotate_point<T>(degrees, 0, 0, dir, ax, ay, bx, by, cx, cy);
                }
            }
        }

        template < typename T >
        inline void triangle_rotate_centroid(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            T ox, oy;
            omni::math::triangle_get_centroid(ax, ay, bx, by, cx, cy, ox, oy);
            omni::math::triangle_rotate_point<T>(degrees, ox, oy, dir, ax, ay, bx, by, cx, cy);
        }
        
        template < typename T >
        inline void triangle_rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            T ox, oy;
            omni::math::triangle_get_circumcenter(ax, ay, bx, by, cx, cy, ox, oy);
            omni::math::triangle_rotate_point<T>(degrees, ox, oy, dir, ax, ay, bx, by, cx, cy);
        }

        template < typename T >
        inline void triangle_rotate_incenter(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            T ox, oy;            
            omni::math::triangle_get_incenter(ax, ay, bx, by, cx, cy, ox, oy);
            omni::math::triangle_rotate_point<T>(degrees, ox, oy, dir, ax, ay, bx, by, cx, cy);
        }

        template < typename T >
        inline void triangle_rotate_abc(double degrees, T x1, T y1, const omni::math::rotation_direction& dir, T& x2, T& y2, T& x3, T& y3)
        {
            omni::math::triangle_rotate_point<T>(degrees, x1, y1, dir, x1, y1, x2, y2, x3, y3);
        }

        template < typename T >
        inline void triangle_translate_xy(T x, T y, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            ax += x; bx += x; cx += x;
            ay += y; by += y; cy += y;
        }

        template < typename T >
        inline void triangle_translate_angle(double degrees, T distance, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
        {
            if ((degrees < 0.0) || (degrees > 360.0)) {
                OMNI_ERR_FW("angle must be between 0-360 degrees", omni::exceptions::overflow_error("angle must be between 0-360 degrees"))
            }
            if (omni::math::are_equal(degrees, 0.0) || omni::math::are_equal(degrees, 360.0)) {
                // no rotational translation, just add distance to all the y pairs
                omni::math::triangle_translate_xy(static_cast<T>(0), distance, ax, ay, bx, by, cx, cy);
            } else {
                omni::math::point_on_circle(degrees, distance, ax, ay, ax, ay);
                omni::math::point_on_circle(degrees, distance, bx, by, bx, by);
                omni::math::point_on_circle(degrees, distance, cx, cy, cx, cy);
            }
        }

        inline double truncate(double val)
        {
            std::modf(val, &val);
            return val;
        }

        inline double trunc(double val)
        {
            return omni::math::truncate(val);
        }

        template < typename T >
        inline double area_of_quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
        {
            return omni::math::area_of_quadrilateral(
                (((ax >= bx) && (ay >= by)) ?
                (OMNI_DISTANCE_2POINTS_2D_FW(ax, ay, bx, by)) :
                (OMNI_DISTANCE_2POINTS_2D_FW(bx, by, ax, ay))),

                (((bx >= cx) && (by >= cy)) ?
                (OMNI_DISTANCE_2POINTS_2D_FW(bx, by, cx, cy)) :
                (OMNI_DISTANCE_2POINTS_2D_FW(cx, cy, bx, by))),

                (((cx >= dx) && (cy >= dy)) ?
                (OMNI_DISTANCE_2POINTS_2D_FW(cx, cy, dx, dy)) :
                (OMNI_DISTANCE_2POINTS_2D_FW(dx, dy, cx, cy))),

                (((dx >= ax) && (dy >= ay)) ?
                (OMNI_DISTANCE_2POINTS_2D_FW(dx, dy, ax, ay)) :
                (OMNI_DISTANCE_2POINTS_2D_FW(ax, ay, dx, dy))),

                omni::math::calculate_angle(ax, ay, bx, by, cx, cy),
                omni::math::calculate_angle(cx, cy, dx, dy, ax, ay)
            );
        }

        static double ieee_remainder(double x, double y)
        {
            if (omni::math::is_nan(x)) {
                return x; // IEEE 754-2008: NaN payload must be preserved
            }
            if (omni::math::is_nan(y)) {
                return y; // IEEE 754-2008: NaN payload must be preserved
            }
            if (omni::math::are_equal(y, 0.0)) {
                if (x < 0.0000000000000000000) {
                    return -0.0;
                }
                return 0.0;
            }
            double divres = x / y;
            double ares = 0;
            double rmod = std::modf(divres, &ares);
            if (omni::math::is_nan(rmod)) {
                return OMNI_NAN;
            }
            if (omni::math::are_equal(rmod, 0.0)) {
                if (x < 0.0000000000000000000) {
                    return -0.0;
                }
            }
            ares = rmod - (std::fabs(y) * omni::math::sign(x));
            if (std::fabs(ares) == std::fabs(rmod)) {
                if (std::fabs(omni::math::round(divres)) > std::fabs(divres)) {
                    return ares;
                } else { 
                    return rmod;
                }
            }
            if (std::fabs(ares) < std::fabs(rmod)) {
                return ares;
            }
            return rmod;
        }

        template < typename T >
        inline bool quadrilateral_contains_point(T x, T y, T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
        {
            return omni::math::triangle_contains_point(x, y, ax, ay, bx, by, cx, cy) ||
                   omni::math::triangle_contains_point(x, y, cx, cy, dx, dy, ax, ay);
        }

        template < typename T >
        inline void quadrilateral_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
        {
            T x1, y1, x2, y2, x3, y3, x4, y4;
            omni::math::triangle_get_centroid(ax, ay, bx, by, cx, cy, x1, y1); // ABC
            omni::math::triangle_get_centroid(bx, by, cx, cy, dx, dy, x2, y2); // BCD
            omni::math::triangle_get_centroid(ax, ay, cx, cy, dx, dy, x3, y3); // ACD
            omni::math::triangle_get_centroid(ax, ay, bx, by, dx, dy, x4, y4); // ABD
            omni::math::rectangle_get_centroid(x1, y1, x2, y2, x3, y3, x4, y4, out_x, out_y);
        }

        template < typename T >
        inline void quadrilateral_get_circumcenter(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
        {
            omni::math::quadrilateral_get_centroid(ax, ay, bx, by, cx, cy, dx, dy, out_x, out_y);
        }

        template < typename T >
        inline void quadrilateral_get_incenter(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
        {
            omni::math::quadrilateral_get_centroid(ax, ay, bx, by, cx, cy, dx, dy, out_x, out_y);
        }

        template < typename T >
        inline void quadrilateral_rotate_centroid(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            T ox, oy;
            omni::math::quadrilateral_get_centroid(ax, ay, bx, by, cx, cy, dx, dy, ox, oy);
            omni::math::quadrilateral_rotate_point<T>(degrees, ox, oy, dir, ax, ay, bx, by, cx, cy, dx, dy);
        }
        
        template < typename T >
        inline void quadrilateral_rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            T ox, oy;
            omni::math::quadrilateral_get_circumcenter(ax, ay, bx, by, cx, cy, dx, dy, ox, oy);
            omni::math::quadrilateral_rotate_point<T>(degrees, ox, oy, dir, ax, ay, bx, by, cx, cy, dx, dy);
        }

        template < typename T >
        inline void quadrilateral_rotate_incenter(double degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
        {
            T ox, oy;
            omni::math::quadrilateral_get_incenter(ax, ay, bx, by, cx, cy, dx, dy, ox, oy);
            omni::math::quadrilateral_rotate_point<T>(degrees, ox, oy, dir, ax, ay, bx, by, cx, cy, dx, dy);
        }

        template < typename T >
        inline void quadrilateral_rotate_abcd(double degrees, T x1, T y1, const omni::math::rotation_direction& dir, T& x2, T& y2, T& x3, T& y3, T& x4, T& y4)
        {
           omni::math::quadrilateral_rotate_point<T>(degrees, x1, y1, dir, x1, y1, x2, y2, x3, y3, x4, y4);
        }
    }
}

#endif // OMNI_MATH_HPP
