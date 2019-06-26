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
        namespace path {
            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            circle(T x, T y, T radius, T step, bool invert_x, bool invert_y)
            {
                typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                gp_seq_t points;
                double x1, y1, angle;
                if (invert_x && invert_y) { // Flip Horiz/Vert
                    for (angle = 0; angle < 360; angle += step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                } else if (invert_x) { // Flip Horiz
                    for (angle = 360; angle > 0; angle -= step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                } else if (invert_y) { // Flip Vert
                    for (angle = 180; angle > 0; angle -= step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                    for (angle = 360; angle > 180; angle -= step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                } else { // Normal
                    for (angle = 180; angle < 360; angle += step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                    for (angle = 0; angle < 180; angle += step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                }
                for (typename gp_seq_t::iterator a = points.begin(); a != points.end(); ++a) {
                    for (typename gp_seq_t::iterator b = (a + 1); b != points.end(); ++b) {
                        if (*a == *b) {
                            points.erase(b);
                            --b;
                        }
                    }
                }
                return points;
            }

            template < template < class, class > class std_seq_t, typename T  >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            circle(T x, T y, T radius, T step, bool invert_x, bool invert_y)
            {
                return circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T  >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            circle(T x, T y, T radius, T step)
            {
                return circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, step, false, false);
            }

            template < template < class, class > class std_seq_t, typename T  >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            circle(T x, T y, T radius)
            {
                return circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, T(1), false, false);
            }

            template < typename T >
            inline typename omni_sequence_t< omni::geometry::point2d<T> >
            circle(T x, T y, T radius, T step, bool invert_x, bool invert_y)
            {
                return circle<omni_sequence_t, T>(x, y, radius, step, invert_x, invert_y);
            }

            template < typename T >
            inline typename omni_sequence_t< omni::geometry::point2d<T> >
            circle(T x, T y, T radius, T step)
            {
                return circle<omni_sequence_t, T>(x, y, radius, step);
            }

            template < typename T >
            inline typename omni_sequence_t< omni::geometry::point2d<T> >
            circle(T x, T y, T radius)
            {
                return circle<omni_sequence_t, T>(x, y, radius);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            {
                typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                gp_seq_t points;
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
                    double len = std::sqrt(static_cast<double>(run * run) + static_cast<double>(rise * rise));
                    for (double L = 1.0; L < len; L += static_cast<double>(step)) {
                        points.push_back(omni::geometry::vector2::calculate_point<T>(x1, y1, x2, y2, static_cast<T>(L)));
                    }
                }
                points.push_back(omni::geometry::point2d<T>(x2, y2));
                if (remove_duplicates) {
                    typename gp_seq_t::iterator it = points.begin();
                    typename gp_seq_t::iterator next = (it + 1);
                    while (next != points.end()) {
                        if (*it == *next) {
                            points.erase(next);
                            next = (it + 1);
                        }
                        it = next++;
                    }
                }
                if (skip > 0) {
                    uint32_t x = 0;
                    for (typename gp_seq_t::iterator itr = points.begin(); itr != points.end(); ++itr) {
                        if (++x % skip == 0) { continue; }
                        if (x == skip) { x = 0; }
                        points.erase(itr--);
                    }
                }
                return points;
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip)
            {
                return line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2, T step)
            {
                return line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2)
            {
                return line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, T(1), 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            {
                return line<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(x1, y1, x2, y2, step, skip, remove_duplicates);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip)
            {
                return line<std_seq_t, T>(x1, y1, x2, y2, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            line(T x1, T y1, T x2, T y2, T step)
            {
                return line<std_seq_t, T>(x1, y1, x2, y2, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            line(T x1, T y1, T x2, T y2)
            {
                return line<std_seq_t, T>(x1, y1, x2, y2, T(1), 0, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            {
                return omni::geometry::path::line<omni_sequence_t, T>(x1, y1, x2, y2, step, skip, remove_duplicates);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip)
            {
                return omni::geometry::path::line<omni_sequence_t, T>(x1, y1, x2, y2, step, skip, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            line(T x1, T y1, T x2, T y2, T step)
            {
                return omni::geometry::path::line<omni_sequence_t, T>(x1, y1, x2, y2, step, 0, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            line(T x1, T y1, T x2, T y2)
            {
                return omni::geometry::path::line<omni_sequence_t, T>(x1, y1, x2, y2, T(1), 0, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            rectangle(T x, T y, T x_len, T y_len, T step, bool invert_x, bool invert_y)
            {
                typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                gp_seq_t points;
                T x1, y1, xm, ym;
                if (invert_x && invert_y) {
                    xm = (x - x_len);
                    ym = (y - y_len);
                    for (x1 = x; x1 > xm; x1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(x1, y));
                    }
                    for (y1 = y; y1 > ym; y1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(xm, y1));
                    }
                    points.push_back(omni::geometry::point2d<T>(xm, ym));
                    for (x1 = xm + step; x1 < x; x1 += step) {
                        points.push_back(omni::geometry::point2d<T>(x1, ym));
                    }
                    points.push_back(omni::geometry::point2d<T>(x, ym));
                    for (y1 = ym - step; y1 < y; y1 += step) {
                        points.push_back(omni::geometry::point2d<T>(x, y1));
                    }
                } else if (invert_x) {
                    xm = (x - x_len);
                    ym = (y + y_len);
                    for (x1 = x; x1 > xm; x1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(x1, y));
                    }
                    for (y1 = y; y1 < ym; y1 += step) {
                        points.push_back(omni::geometry::point2d<T>(xm, y1));
                    }
                    points.push_back(omni::geometry::point2d<T>(xm, ym));
                    for (x1 = xm + step; x1 < x; x1 += step) {
                        points.push_back(omni::geometry::point2d<T>(x1, ym));
                    }
                    points.push_back(omni::geometry::point2d<T>(x, ym));
                    for (y1 = ym - step; y1 > y; y1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(x, y1));
                    }
                } else if (invert_y) {
                    xm = (x + x_len);
                    ym = (y - y_len);
                    for (x1 = x; x1 < xm; x1 += step) {
                        points.push_back(omni::geometry::point2d<T>(x1, y));
                    }
                    for (y1 = y; y1 > ym; y1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(xm, y1));
                    }
                    points.push_back(omni::geometry::point2d<T>(xm, ym));
                    for (x1 = xm - step; x1 > x; x1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(x1, ym));
                    }
                    points.push_back(omni::geometry::point2d<T>(x, ym));
                    for (y1 = ym - step; y1 < y; y1 += step) {
                        points.push_back(omni::geometry::point2d<T>(x, y1));
                    }
                } else {
                    xm = (x + x_len);
                    ym = (y + y_len);
                    for (x1 = x; x1 < xm; x1 += step) {
                        points.push_back(omni::geometry::point2d<T>(x1, y));
                    }
                    for (y1 = y; y1 < ym; y1 += step) {
                        points.push_back(omni::geometry::point2d<T>(xm, y1));
                    }
                    points.push_back(omni::geometry::point2d<T>(xm, ym));
                    for (x1 = xm - step; x1 > x; x1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(x1, ym));
                    }
                    points.push_back(omni::geometry::point2d<T>(x, ym));
                    for (y1 = ym - step; y1 > y; y1 -= step) {
                        points.push_back(omni::geometry::point2d<T>(x, y1));
                    }
                }
                return points;
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            rectangle(T x, T y, T x_len, T y_len, T step, bool invert_x, bool invert_y)
            {
                return rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, step);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            rectangle(T x, T y, T x_len, T y_len, T step)
            {
                return rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, step, false, false);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            rectangle(T x, T y, T x_len, T y_len)
            {
                return rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, T(1), false, false);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            rectangle(T x, T y, T x_len, T y_len, T step, bool invert_x, bool invert_y)
            {
                return omni::geometry::path::rectangle<omni_sequence_t, T>(x, y, x_len, y_len, step, invert_x, invert_y);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            rectangle(T x, T y, T x_len, T y_len, T step)
            {
                return omni::geometry::path::rectangle<omni_sequence_t, T>(x, y, x_len, y_len, step);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            rectangle(T x, T y, T x_len, T y_len)
            {
                return omni::geometry::path::rectangle<omni_sequence_t, T>(x, y, x_len, y_len);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            square(T x, T y, T len, T step, bool invert_x, bool invert_y)
            {
                return rectangle<std_seq_t, T, std_allocator_t>(x, y, len, len, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            square(T x, T y, T len, T step, bool invert_x, bool invert_y)
            {
                return square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            square(T x, T y, T len, T step)
            {
                return square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, step, false, false);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            square(T x, T y, T len)
            {
                return square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, T(1));
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            square(T x, T y, T len, T step, bool invert_x, bool invert_y)
            {
                return omni::geometry::path::square<omni_sequence_t, T>(x, y, len, step, invert_x, invert_y);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            square(T x, T y, T len, T step)
            {
                return omni::geometry::path::square<omni_sequence_t, T>(x, y, len, step);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            square(T x, T y, T len)
            {
                return omni::geometry::path::square<omni_sequence_t, T>(x, y, len);
            }
        }
    }
}

#endif // OMNI_GEOMETRY_PATH_HPP
