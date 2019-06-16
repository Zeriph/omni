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
#if !defined(OMNI_GEOMETRY_PATH_HPP)
#define OMNI_GEOMETRY_PATH_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/size.hpp>
#include <omni/geometry/point2d.hpp>
#include <omni/math.hpp>

namespace omni {
    namespace geometry {
        /** Undocumented: not finished */
        namespace path {
            template < typename T >
            static typename omni_sequence_t< omni::geometry::point2d<T> > get_circle(T x, T y, T radius, T step, bool invert_x, bool invert_y)
            {
                omni_sequence_t< omni::geometry::point2d<T> > points;
                T x1, y1;
                T angle;
                if (invert_x && invert_y) { // Flip Horiz/Vert
                    for (angle = static_cast<T>(0); angle < static_cast<T>(360); angle += step) {
                        x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                        y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                        points.push_back(omni::geometry::point2d<T>(x1, y1));
                        //omni::geometry::point2d<T> p(x1, y1);
                        //if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                    }
                } else if (invert_x) { // Flip Horiz
                    for (angle = static_cast<T>(360); angle > static_cast<T>(0); angle -= step) {
                        x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                        y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                        points.push_back(omni::geometry::point2d<T>(x1, y1));
                        //omni::geometry::point_t p(x1, y1);
                        //if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                    }
                } else if (invert_y) { // Flip Vert
                    for (angle = static_cast<T>(180); angle > static_cast<T>(0); angle -= step) {
                        x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                        y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                        points.push_back(omni::geometry::point2d<T>(x1, y1));
                        //omni::geometry::point_t p(x1, y1);
                        //if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                    }
                    for (angle = static_cast<T>(360); angle > static_cast<T>(180); angle -= step) {
                        x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                        y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                        points.push_back(omni::geometry::point2d<T>(x1, y1));
                        //omni::geometry::point_t p(x1, y1);
                        //if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                    }
                } else { // Normal
                    for (angle = static_cast<T>(180); angle < static_cast<T>(360); angle += step) {
                        x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                        y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                        points.push_back(omni::geometry::point2d<T>(x1, y1));
                        //omni::geometry::point_t p(x1, y1);
                        //if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                    }
                    for (angle = static_cast<T>(0); angle < static_cast<T>(180); angle += step) {
                        x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                        y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                        points.push_back(omni::geometry::point2d<T>(x1, y1));
                        //omni::geometry::point_t p(x1, y1);
                        //if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                    }
                }
                return points;
            }

            template < typename T >
            static typename omni_sequence_t< omni::geometry::point2d<T> > get_circle(T x, T y, T radius, T step)
            {
                return get_circle(x, y, radius, step, false, false);
            }

            template < typename T >
            static typename omni_sequence_t< omni::geometry::point2d<T> > get_circle(T x, T y, T radius)
            {
                return get_circle(x, y, radius, static_cast<T>(1), false, false);
            }

            /*
                TODO: OLD CODE .. remove once tests complete

                static omni::geometry::point_seq_t get_circle(double x, double y, double radius, double step, bool invert_x, bool invert_y)
                {
                    omni::geometry::point_seq_t points;
                    double x1, y1;
                    double angle;
                    if (invert_x && invert_y) { // Flip Horiz/Vert
                        for (angle = 0; angle < 360; angle += step) {
                            x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                            y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    } else if (invert_x) { // Flip Horiz
                        for (angle = 360; angle > 0; angle -= step) {
                            x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                            y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    } else if (invert_y) { // Flip Vert
                        for (angle = 180; angle > 0; angle -= step) {
                            x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                            y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                        for (angle = 360; angle > 180; angle -= step) {
                            x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                            y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    } else { // Normal
                        for (angle = 180; angle < 360; angle += step) {
                            x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                            y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                        for (angle = 0; angle < 180; angle += step) {
                            x1 = std::ceil(x + (radius * std::cos((OMNI_PI_180 * angle) - angle)));
                            y1 = std::ceil(y + (radius * std::sin((OMNI_PI_180 * angle) - angle)));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    }
                    return points;
                }

                static omni::geometry::point_seq_t get_circle(int32_t x, int32_t y, uint32_t radius, bool invert_x, bool invert_y)
                {
                    omni::geometry::point_seq_t points;
                    double x0 = static_cast<double>(x);
                    double y0 = static_cast<double>(y);
                    double r = static_cast<double>(radius);
                    double x1, y1;
                    int angle;
                    if (invert_x && invert_y) { // Flip Horiz/Vert
                        for (angle = 0; angle < 360; ++angle) {
                            x1 = std::ceil(x0 + (r * omni::math::RADS_COS[angle]));
                            y1 = std::ceil(y0 + (r * omni::math::RADS_SIN[angle]));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    } else if (invert_x) { // Flip Horiz
                        for (angle = 360; angle > 0; --angle) {
                            x1 = std::ceil(x0 + (r * omni::math::RADS_COS[angle]));
                            y1 = std::ceil(y0 + (r * omni::math::RADS_SIN[angle]));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    } else if (invert_y) { // Flip Vert
                        for (angle = 180; angle > 0; --angle) {
                            x1 = std::ceil(x0 + (r * omni::math::RADS_COS[angle]));
                            y1 = std::ceil(y0 + (r * omni::math::RADS_SIN[angle]));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                        for (angle = 360; angle > 180; --angle) {
                            x1 = std::ceil(x0 + (r * omni::math::RADS_COS[angle]));
                            y1 = std::ceil(y0 + (r * omni::math::RADS_SIN[angle]));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    } else { // Normal
                        for (angle = 180; angle < 360; ++angle) {
                            x1 = std::ceil(x0 + (r * omni::math::RADS_COS[angle]));
                            y1 = std::ceil(y0 + (r * omni::math::RADS_SIN[angle]));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                        for (angle = 0; angle < 180; ++angle) {
                            x1 = std::ceil(x0 + (r * omni::math::RADS_COS[angle]));
                            y1 = std::ceil(y0 + (r * omni::math::RADS_SIN[angle]));
                            omni::geometry::point_t p(x1, y1);
                            if (std::find(points.begin(), points.end(), p) == points.end()) { points.push_back(p); }
                        }
                    }
                    return points;
                }

                static omni::geometry::point_seq_t get_circle(double x, double y, double radius)
                {
                    return omni::geometry::path::get_circle(x, y, radius, 1.0, false, false);
                }

                static omni::geometry::point_seq_t get_circle(double x, double y, double radius, double step)
                {
                    return omni::geometry::path::get_circle(x, y, radius, step, false, false);
                }

                static omni::geometry::point_seq_t get_circle(int32_t x, int32_t y, uint32_t radius)
                {
                    return omni::geometry::path::get_circle(x, y, radius, false, false);
                }
            */

            template < typename T >
            static omni::geometry::point2d<T> get_point_on_circle(T angle, T radius, T center_x, T center_y)
            {
                if (angle > static_cast<T>(360)) {
                    OMNI_ERR_RETV_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"), omni::geometry::pointF_t())
                }
                return omni::geometry::point2d<T>(
                    (center_x + (radius * std::cos((OMNI_PI_180 * angle) - angle))),
                    (center_y + (radius * std::sin((OMNI_PI_180 * angle) - angle)))
                );
            }

            /*
                TODO: OLD CODE .. remove once tests complete

                static omni::geometry::pointF_t get_pointF_on_circle(double angle, double radius, double center_x, double center_y)
                {
                    if (angle > 360) {
                        OMNI_ERR_RETV_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"), omni::geometry::pointF_t())
                    }
                    return omni::geometry::pointF_t(
                        (center_x + (radius * std::cos((OMNI_PI_180 * angle) - angle))),
                        (center_y + (radius * std::sin((OMNI_PI_180 * angle) - angle)))
                    );
                }

                static omni::geometry::pointF_t get_pointF_on_circle(uint16_t angle, uint32_t radius, int32_t center_x, int32_t center_y)
                {
                    if (angle > 360) {
                        OMNI_ERR_RETV_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"), omni::geometry::pointF_t())
                    }
                    double rad = static_cast<double>(radius);
                    return omni::geometry::pointF_t(
                        (static_cast<double>(center_x) + (rad * omni::math::RADS_COS[angle])),
                        (static_cast<double>(center_y) + (rad * omni::math::RADS_SIN[angle]))
                    );
                }

                static omni::geometry::point_t get_point_on_circle(double angle, double radius, double center_x, double center_y)
                {
                    if (angle > 360) {
                        OMNI_ERR_RETV_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"), omni::geometry::pointF_t())
                    }
                    return omni::geometry::point_t(
                        static_cast<omni::geometry::point_t::coordinate_t>(std::ceil(center_x + (radius * std::cos((OMNI_PI_180 * angle) - angle)))),
                        static_cast<omni::geometry::point_t::coordinate_t>(std::ceil(center_y + (radius * std::sin((OMNI_PI_180 * angle) - angle))))
                    );
                }

                static omni::geometry::point_t get_point_on_circle(uint16_t angle, uint32_t radius, int32_t center_x, int32_t center_y)
                {
                    if (angle > 360) {
                        OMNI_ERR_RETV_FW("angle cannot be greater than 360 degrees", omni::exceptions::overflow_error("angle cannot be greater than 360 degrees"), omni::geometry::pointF_t())
                    }
                    double rad = static_cast<double>(radius);
                    return omni::geometry::point_t(
                        static_cast<omni::geometry::point_t::coordinate_t>(std::ceil(static_cast<double>(center_x) + (rad * omni::math::RADS_COS[angle]))),
                        static_cast<omni::geometry::point_t::coordinate_t>(std::ceil(static_cast<double>(center_y) + (rad * omni::math::RADS_SIN[angle])))
                    );
                }
            */

            template < typename T >
            static typename omni_sequence_t< omni::geometry::point2d<T> > get_path(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            {
                omni_sequence_t< omni::geometry::point2d<T> > points;
                bool negx = (x1 > x2);
                bool negy = (y1 > y2);
                points.push_back(omni::geometry::point2d<T>(x1, y1));
                if (omni::math::are_equal<T>(x1, x2)) { // vertical line (y change, x doesn't)
                    if (negy) {
                        for (; y1 > y2; --y1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                    } else {
                        for (; y1 < y2; ++y1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                    }
                } else if (omni::math::are_equal<T>(y1, y2)) { // horiz. line (x change, y doesn't)
                    if (negx) {
                        for (; x1 > x2; --x1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                    } else {
                        for (; x1 < x2; ++x1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                    }
                } else { // slant line (x && y change)
                    T run = x2 - x1;
                    T rise = y2 - y1;
                    T len = std::sqrt((run * run) + (rise * rise));
                    for (T L = 1.0; L < len; L += step) {
                        points.push_back(omni::geometry::vector2::calculate_point<T>(x1, y1, x2, y2, L));
                    }
                }
                points.push_back(omni::geometry::point2d<T>(x2, y2));
                if (skip > 0 || remove_duplicates) {
                    uint32_t x = 0;
                    typename omni_sequence_t< omni::geometry::point2d<T> >::iterator it = points.begin();
                    typename omni_sequence_t< omni::geometry::point2d<T> >::iterator next = (it + 1);
                    for (; (skip > 0) && (it != points.end()); it = next++) {
                        if (++x % skip == 0) { continue; }
                        if (x == skip) { x = 0; }
                        points.erase(it);
                    }
                    // TODO: finish this .. optimize function
                    if (remove_duplicates) {
                        it = points.begin(); next = (it + 1);
                        while (next != points.end()) {
                            if (omni::math::are_equal<T>(*it, *next)) {
                                points.erase(next);
                                next = (it + 1);
                            } else {
                                it = next++;
                            }
                        }
                    }

                }
                return points;
            }

            template < typename T >
            static typename omni_sequence_t< omni::geometry::point2d<T> > get_path(T x1, T y1, T x2, T y2, T step)
            {
                return omni::geometry::path::get_path<T>(x1, y1, x2, y2, step, true);
            }

            /*
                TODO: OLD CODE .. remove once tests complete

                template < typename T >
                static typename omni_sequence_t< omni::geometry::point2d<T> > get_path(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
                {
                    if (skip > 0) {
                        omni_sequence_t< omni::geometry::point2d<T> > path = omni::geometry::path::get_path<T>(x1, y1, x2, y2, step, remove_duplicates);
                        uint32_t x = 0;
                        for (omni::geometry::point_seq_t::iterator itr = path.begin(); itr != path.end(); ++itr) {
                            if (++x % skip == 0) { continue; }
                            if (x == skip) { x = 0; }
                            path.erase(itr--);
                        }
                        return path;
                    }
                    return omni::geometry::path::get_path<T>(x1, y1, x2, y2, step, remove_duplicates);
                }
            */

            template < typename T >
            static typename omni_sequence_t< omni::geometry::point2d<T> > get_path(T x1, T y1, T x2, T y2, T step, uint32_t skip)
            {
                return omni::geometry::path::get_path<T>(x1, y1, x2, y2, step, skip, true);
            }
        }
    }
}

#endif // OMNI_GEOMETRY_PATH_HPP
