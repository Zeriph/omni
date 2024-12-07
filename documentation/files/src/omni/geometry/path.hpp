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
#include <omni/geometry/point2d.hpp>

namespace omni {
    namespace geometry {
        namespace path {
            namespace conditional {
                typedef omni::delegate3<bool, double, double, double> circle_break_condition;
                /*
                    DEV_NOTE: we don't have a omni::delegate2<bool, double, double> X_break_condition, because the
                    circle always has 3 doubles for the points/angles of the circle, while the others can be arbitrary
                    precision (i.e. float or int). So the delegate type passed in will be omni::delegate2<bool, T, T>
                */

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                circle(T x, T y, T radius, T step, bool invert_x, bool invert_y, const circle_break_condition& condition)
                {
                    typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                    gp_seq_t points;
                    double x1, y1, angle;
                    if (invert_x && invert_y) { // Flip Horiz/Vert
                        for (angle = 0; angle < 360; angle += step) {
                            x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                            y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                            if (condition && !condition(x1, y1, angle)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                        }
                    } else if (invert_x) { // Flip Horiz
                        for (angle = 360; angle > 0; angle -= step) {
                            x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                            y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                            if (condition && !condition(x1, y1, angle)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                        }
                    } else if (invert_y) { // Flip Vert
                        for (angle = 180; angle > 0; angle -= step) {
                            x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                            y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                            if (condition && !condition(x1, y1, angle)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                        }
                        for (angle = 360; angle > 180; angle -= step) {
                            x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                            y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                            if (condition && !condition(x1, y1, angle)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                        }
                    } else { // Normal
                        for (angle = 180; angle < 360; angle += step) {
                            x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                            y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                            if (condition && !condition(x1, y1, angle)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                        }
                        for (angle = 0; angle < 180; angle += step) {
                            x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                            y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                            if (condition && !condition(x1, y1, angle)) {
                                break;
                            }
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
                circle(T x, T y, T radius, T step, bool invert_x, bool invert_y, const circle_break_condition& condition)
                {
                    return omni::geometry::path::conditional::circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, step, invert_x, invert_y, condition);
                }

                template < template < class, class > class std_seq_t, typename T  >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                circle(T x, T y, T radius, T step, const circle_break_condition& condition)
                {
                    return omni::geometry::path::conditional::circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, step, false, false, condition);
                }

                template < template < class, class > class std_seq_t, typename T  >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                circle(T x, T y, T radius, const circle_break_condition& condition)
                {
                    return omni::geometry::path::conditional::circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, static_cast<T>(1), false, false, condition);
                }

                template < typename T >
                inline typename omni_sequence_t< omni::geometry::point2d<T> >
                circle(T x, T y, T radius, T step, bool invert_x, bool invert_y, const circle_break_condition& condition)
                {
                    return omni::geometry::path::conditional::circle<omni_sequence_t, T>(x, y, radius, step, invert_x, invert_y, condition);
                }

                template < typename T >
                inline typename omni_sequence_t< omni::geometry::point2d<T> >
                circle(T x, T y, T radius, T step, const circle_break_condition& condition)
                {
                    return omni::geometry::path::conditional::circle<omni_sequence_t, T>(x, y, radius, step, condition);
                }

                template < typename T >
                inline typename omni_sequence_t< omni::geometry::point2d<T> >
                circle(T x, T y, T radius, const circle_break_condition& condition)
                {
                    return omni::geometry::path::conditional::circle<omni_sequence_t, T>(x, y, radius, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                void basic_line(T x1, T y1, T x2, T y2, T step, std_seq_t< omni::geometry::point2d<T>, std_allocator_t >& points, const omni::delegate2<bool, T, T>& condition)
                {
                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                    if (omni::math::are_equal<T>(x1, x2)) { // vertical line (y change, x does not)
                        if ((y1 > y2)) {
                            if (step == 1) {
                                for (; y1 > y2; --y1) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            } else {
                                for (; y1 > y2; y1 -= step) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            }
                        } else {
                            if (step == 1) {
                                for (; y1 < y2; ++y1) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            } else {
                                for (; y1 < y2; y1 += step) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            }
                        }
                    } else if (omni::math::are_equal<T>(y1, y2)) { // horiz. line (x change, y does not)
                        if ((x1 > x2)) {
                            if (step == 1) {
                                for (; x1 > x2; --x1) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            } else {
                                for (; x1 > x2; x1 -= step) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            }
                        } else {
                            if (step == 1) {
                                for (; x1 < x2; ++x1) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            } else {
                                for (; x1 < x2; x1 += step) {
                                    if (condition && !condition(x1, y1)) {
                                        break;
                                    }
                                    points.push_back(omni::geometry::point2d<T>(x1, y1));
                                }
                            }
                        }
                    } else { // slant line (x && y change)
                        double len = OMNI_DISTANCE_2POINTS_2D_FW(x1, y1, x2, y2);
                        for (double L = 1.0; L < len; L += static_cast<double>(step)) {
                            omni::geometry::point2d<T> pt(omni::math::calculate_point<T>(x1, y1, x2, y2, static_cast<T>(L), len));
                            if (condition && !condition(pt.x(), pt.y())) {
                                break;
                            }
                            points.push_back(pt);
                        }
                    }
                    points.push_back(omni::geometry::point2d<T>(x2, y2));
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                    gp_seq_t points;
                    omni::geometry::path::conditional::basic_line(x1, y1, x2, y2, step, points, condition);
                    if (remove_duplicates) {
                        typename gp_seq_t::iterator it = points.begin();
                        typename gp_seq_t::iterator next = (it + 1);
                        while (next != points.end()) {
                            if (*it == *next) {
                                points.erase(next);
                                next = it;
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
                line(T x1, T y1, T x2, T y2, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, step, skip, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                line(T x1, T y1, T x2, T y2, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, step, 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                line(T x1, T y1, T x2, T y2, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, static_cast<T>(1), 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(x1, y1, x2, y2, step, skip, remove_duplicates, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                line(T x1, T y1, T x2, T y2, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T>(x1, y1, x2, y2, step, skip, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                line(T x1, T y1, T x2, T y2, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T>(x1, y1, x2, y2, step, 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                line(T x1, T y1, T x2, T y2, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<std_seq_t, T>(x1, y1, x2, y2, static_cast<T>(1), 0, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<omni_sequence_t, T>(x1, y1, x2, y2, step, skip, remove_duplicates, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                line(T x1, T y1, T x2, T y2, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<omni_sequence_t, T>(x1, y1, x2, y2, step, skip, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                line(T x1, T y1, T x2, T y2, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<omni_sequence_t, T>(x1, y1, x2, y2, step, 0, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                line(T x1, T y1, T x2, T y2, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::line<omni_sequence_t, T>(x1, y1, x2, y2, static_cast<T>(1), 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                rectangle(T x, T y, T x_len, T y_len, T step, bool invert_x, bool invert_y, const omni::delegate2<bool, T, T>& condition)
                {
                    typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                    gp_seq_t points;
                    T x1, y1, xm, ym;
                    if (invert_x && invert_y) {
                        xm = (x - x_len);
                        ym = (y - y_len);
                        for (x1 = x; x1 > xm; x1 -= step) {
                            if (condition && !condition(x1, y)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, y));
                        }
                        for (y1 = y; y1 > ym; y1 -= step) {
                            if (condition && !condition(xm, y)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(xm, y1));
                        }
                        points.push_back(omni::geometry::point2d<T>(xm, ym));
                        for (x1 = xm + step; x1 < x; x1 += step) {
                            if (condition && !condition(x1, ym)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, ym));
                        }
                        points.push_back(omni::geometry::point2d<T>(x, ym));
                        for (y1 = ym - step; y1 < y; y1 += step) {
                            if (condition && !condition(x, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x, y1));
                        }
                    } else if (invert_x) {
                        xm = (x - x_len);
                        ym = (y + y_len);
                        for (x1 = x; x1 > xm; x1 -= step) {
                            if (condition && !condition(x1, y)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, y));
                        }
                        for (y1 = y; y1 < ym; y1 += step) {
                            if (condition && !condition(xm, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(xm, y1));
                        }
                        points.push_back(omni::geometry::point2d<T>(xm, ym));
                        for (x1 = xm + step; x1 < x; x1 += step) {
                            if (condition && !condition(x1, ym)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, ym));
                        }
                        points.push_back(omni::geometry::point2d<T>(x, ym));
                        for (y1 = ym - step; y1 > y; y1 -= step) {
                            if (condition && !condition(x, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x, y1));
                        }
                    } else if (invert_y) {
                        xm = (x + x_len);
                        ym = (y - y_len);
                        for (x1 = x; x1 < xm; x1 += step) {
                            if (condition && !condition(x1, y)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, y));
                        }
                        for (y1 = y; y1 > ym; y1 -= step) {
                            if (condition && !condition(xm, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(xm, y1));
                        }
                        points.push_back(omni::geometry::point2d<T>(xm, ym));
                        for (x1 = xm - step; x1 > x; x1 -= step) {
                            if (condition && !condition(x1, ym)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, ym));
                        }
                        points.push_back(omni::geometry::point2d<T>(x, ym));
                        for (y1 = ym - step; y1 < y; y1 += step) {
                            if (condition && !condition(x, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x, y1));
                        }
                    } else {
                        xm = (x + x_len);
                        ym = (y + y_len);
                        for (x1 = x; x1 < xm; x1 += step) {
                            if (condition && !condition(x1, y)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, y));
                        }
                        for (y1 = y; y1 < ym; y1 += step) {
                            if (condition && !condition(xm, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(xm, y1));
                        }
                        points.push_back(omni::geometry::point2d<T>(xm, ym));
                        for (x1 = xm - step; x1 > x; x1 -= step) {
                            if (condition && !condition(x1, ym)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x1, ym));
                        }
                        points.push_back(omni::geometry::point2d<T>(x, ym));
                        for (y1 = ym - step; y1 > y; y1 -= step) {
                            if (condition && !condition(x, y1)) {
                                break;
                            }
                            points.push_back(omni::geometry::point2d<T>(x, y1));
                        }
                    }
                    return points;
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                rectangle(T x, T y, T x_len, T y_len, T step, bool invert_x, bool invert_y, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, step, invert_x, invert_y, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                rectangle(T x, T y, T x_len, T y_len, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, step, false, false, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                rectangle(T x, T y, T x_len, T y_len, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, static_cast<T>(1), false, false, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                rectangle(T x, T y, T x_len, T y_len, T step, bool invert_x, bool invert_y, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<omni_sequence_t, T>(x, y, x_len, y_len, step, invert_x, invert_y, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                rectangle(T x, T y, T x_len, T y_len, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<omni_sequence_t, T>(x, y, x_len, y_len, step, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                rectangle(T x, T y, T x_len, T y_len, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<omni_sequence_t, T>(x, y, x_len, y_len, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                square(T x, T y, T len, T step, bool invert_x, bool invert_y, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::rectangle<std_seq_t, T, std_allocator_t>(x, y, len, len, step, invert_x, invert_y, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                square(T x, T y, T len, T step, bool invert_x, bool invert_y, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, step, invert_x, invert_y, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                square(T x, T y, T len, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, step, false, false, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                square(T x, T y, T len, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, static_cast<T>(1), false, false, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                square(T x, T y, T len, T step, bool invert_x, bool invert_y, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::square<omni_sequence_t, T>(x, y, len, step, invert_x, invert_y, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                square(T x, T y, T len, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::square<omni_sequence_t, T>(x, y, len, step, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                square(T x, T y, T len, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::square<omni_sequence_t, T>(x, y, len, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                    gp_seq_t points;
                    // a -> b
                    omni::geometry::path::conditional::basic_line(ax, ay, bx, by, step, points, condition);
                    // b -> c
                    omni::geometry::path::conditional::basic_line(bx, by, cx, cy, step, points, condition);
                    // c -> a
                    omni::geometry::path::conditional::basic_line(cx, cy, ax, ay, step, points, condition);
                    if (remove_duplicates) {
                        typename gp_seq_t::iterator it = points.begin();
                        typename gp_seq_t::iterator next = (it + 1);
                        while (next != points.end()) {
                            if (*it == *next) {
                                points.erase(next);
                                next = it;
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
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, step, skip, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, step, 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, static_cast<T>(1), 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(ax, ay, bx, by, cx, cy, step, skip, remove_duplicates, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T>(ax, ay, bx, by, cx, cy, step, skip, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T>(ax, ay, bx, by, cx, cy, step, 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<std_seq_t, T>(ax, ay, bx, by, cx, cy, static_cast<T>(1), 0, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, step, skip, remove_duplicates, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, step, skip, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, step, 0, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                triangle(T ax, T ay, T bx, T by, T cx, T cy, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, static_cast<T>(1), 0, true, condition);
                }
                
                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                    gp_seq_t points;
                    // a -> b
                    omni::geometry::path::conditional::basic_line(ax, ay, bx, by, step, points, condition);
                    // b -> c
                    omni::geometry::path::conditional::basic_line(bx, by, cx, cy, step, points, condition);
                    // c -> d
                    omni::geometry::path::conditional::basic_line(cx, cy, dx, dy, step, points, condition);
                    // d -> a
                    omni::geometry::path::conditional::basic_line(dx, dy, ax, ay, step, points, condition);
                    if (remove_duplicates) {
                        typename gp_seq_t::iterator it = points.begin();
                        typename gp_seq_t::iterator next = (it + 1);
                        while (next != points.end()) {
                            if (*it == *next) {
                                points.erase(next);
                                next = it;
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
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, dx, dy, step, 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
                inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, dx, dy, static_cast<T>(1), 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(ax, ay, bx, by, cx, cy, dx, dy, step, skip, remove_duplicates, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, 0, true, condition);
                }

                template < template < class, class > class std_seq_t, typename T >
                inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<std_seq_t, T>(ax, ay, bx, by, cx, cy, dx, dy, static_cast<T>(1), 0, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, bool remove_duplicates, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, remove_duplicates, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, 0, true, condition);
                }

                template < typename T >
                inline omni_sequence_t< omni::geometry::point2d< T > >
                quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, const omni::delegate2<bool, T, T>& condition)
                {
                    return omni::geometry::path::conditional::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, static_cast<T>(1), 0, true, condition);
                }
            }

            /**
             * @brief           Create a path on a circle.
             *
             * @details         Creates a path of 2d points along a circle given an {X, Y} center point
             *                  and a radius size. This will create a point every 1 degree along the circle,
             *                  alternatively you may pass along a stepping value to change the interval each
             *                  node along the path is created.
             *
             * @return          A list of omni::geometry::point2d types containing each point along the path.
             *
             * @param x         The X value of the center of the circle.
             * @param y         The Y value of the center of the circle.
             * @param radius    The radius of the circle.
             * @param step      The stepping value to create each point at (default is 1 degree).
             * @param invert_x  True to invert the X direction the points are added to the list.
             * @param invert_y  True to invert the Y direction the points are added to the list.
             *
             * @tparam std_seq_t        The templated sequence type (e.g. vector/deque/etc.).
             * @tparam T                The underlying type the points will be (e.g. double/int32_t/etc.).
             * @tparam std_allocator_t  The templated sequence type allocator.
             *
             * @warning        Be aware that if you use non floating point types (e.g. int32_t, etc.), that
             *                 the values of the points will be clamped to that type, thus making it possible
             *                 the circle's path will be more jagged than those with a double or float as
             *                 the backing type.
             */
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
                        y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                } else if (invert_x) { // Flip Horiz
                    for (angle = 360; angle > 0; angle -= step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                } else if (invert_y) { // Flip Vert
                    for (angle = 180; angle > 0; angle -= step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                    for (angle = 360; angle > 180; angle -= step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                } else { // Normal
                    for (angle = 180; angle < 360; angle += step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
                        points.push_back(omni::geometry::point2d<T>(static_cast<T>(x1), static_cast<T>(y1)));
                    }
                    for (angle = 0; angle < 180; angle += step) {
                        x1 = (static_cast<double>(x) + (static_cast<double>(radius) * std::cos(angle * OMNI_PI_180)));
                        y1 = (static_cast<double>(y) + (static_cast<double>(radius) * std::sin(angle * OMNI_PI_180)));
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
                return omni::geometry::path::circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T  >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            circle(T x, T y, T radius, T step)
            {
                return omni::geometry::path::circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, step, false, false);
            }

            template < template < class, class > class std_seq_t, typename T  >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            circle(T x, T y, T radius)
            {
                return omni::geometry::path::circle< std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, radius, static_cast<T>(1), false, false);
            }

            template < typename T >
            inline typename omni_sequence_t< omni::geometry::point2d<T> >
            circle(T x, T y, T radius, T step, bool invert_x, bool invert_y)
            {
                return omni::geometry::path::circle<omni_sequence_t, T>(x, y, radius, step, invert_x, invert_y);
            }

            template < typename T >
            inline typename omni_sequence_t< omni::geometry::point2d<T> >
            circle(T x, T y, T radius, T step)
            {
                return omni::geometry::path::circle<omni_sequence_t, T>(x, y, radius, step);
            }

            template < typename T >
            inline typename omni_sequence_t< omni::geometry::point2d<T> >
            circle(T x, T y, T radius)
            {
                return omni::geometry::path::circle<omni_sequence_t, T>(x, y, radius);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            void basic_line(T x1, T y1, T x2, T y2, T step, std_seq_t< omni::geometry::point2d<T>, std_allocator_t >& points)
            {
                points.push_back(omni::geometry::point2d<T>(x1, y1));
                if (omni::math::are_equal<T>(x1, x2)) { // vertical line (y change, x does not)
                    if ((y1 > y2)) {
                        if (omni::math::are_equal(step, T(1))) {
                            for (; y1 > y2; --y1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        } else {
                            for (; y1 > y2; y1 -= step) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        }
                    } else {
                        if (omni::math::are_equal(step, T(1))) {
                            for (; y1 < y2; ++y1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        } else {
                            for (; y1 < y2; y1 += step) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        }
                    }
                } else if (omni::math::are_equal<T>(y1, y2)) { // horiz. line (x change, y does not)
                    if ((x1 > x2)) {
                        if (omni::math::are_equal(step, T(1))) {
                            for (; x1 > x2; --x1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        } else {
                            for (; x1 > x2; x1 -= step) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        }
                    } else {
                        if (omni::math::are_equal(step, T(1))) {
                            for (; x1 < x2; ++x1) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        } else {
                            for (; x1 < x2; x1 += step) { points.push_back(omni::geometry::point2d<T>(x1, y1)); }
                        }
                    }
                } else { // slant line (x && y change)
                    double len = OMNI_DISTANCE_2POINTS_2D_FW(x1, y1, x2, y2);
                    for (double L = 1.0; L < len; L += static_cast<double>(step)) {
                        points.push_back(omni::math::calculate_point<T>(x1, y1, x2, y2, static_cast<T>(L), len));
                    }
                }
                points.push_back(omni::geometry::point2d<T>(x2, y2));
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            {
                typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                gp_seq_t points;
                omni::geometry::path::basic_line(x1, y1, x2, y2, step, points);
                if (remove_duplicates) {
                    typename gp_seq_t::iterator it = points.begin();
                    typename gp_seq_t::iterator next = (it + 1);
                    while (next != points.end()) {
                        if (*it == *next) {
                            points.erase(next);
                            next = it;
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
                return omni::geometry::path::line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2, T step)
            {
                return omni::geometry::path::line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            line(T x1, T y1, T x2, T y2)
            {
                return omni::geometry::path::line<std_seq_t, T, std_allocator_t>(x1, y1, x2, y2, static_cast<T>(1), 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            {
                return omni::geometry::path::line<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(x1, y1, x2, y2, step, skip, remove_duplicates);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            line(T x1, T y1, T x2, T y2, T step, uint32_t skip)
            {
                return omni::geometry::path::line<std_seq_t, T>(x1, y1, x2, y2, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            line(T x1, T y1, T x2, T y2, T step)
            {
                return omni::geometry::path::line<std_seq_t, T>(x1, y1, x2, y2, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            line(T x1, T y1, T x2, T y2)
            {
                return omni::geometry::path::line<std_seq_t, T>(x1, y1, x2, y2, static_cast<T>(1), 0, true);
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
                return omni::geometry::path::line<omni_sequence_t, T>(x1, y1, x2, y2, static_cast<T>(1), 0, true);
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
                return omni::geometry::path::rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            rectangle(T x, T y, T x_len, T y_len, T step)
            {
                return omni::geometry::path::rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, step, false, false);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            rectangle(T x, T y, T x_len, T y_len)
            {
                return omni::geometry::path::rectangle<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, x_len, y_len, static_cast<T>(1), false, false);
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
                return omni::geometry::path::rectangle<std_seq_t, T, std_allocator_t>(x, y, len, len, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            square(T x, T y, T len, T step, bool invert_x, bool invert_y)
            {
                return omni::geometry::path::square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, step, invert_x, invert_y);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            square(T x, T y, T len, T step)
            {
                return omni::geometry::path::square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, step, false, false);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            square(T x, T y, T len)
            {
                return omni::geometry::path::square<std_seq_t, T, std::allocator< omni::geometry::point2d< T > > >(x, y, len, static_cast<T>(1), false, false);
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

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, bool remove_duplicates)
            {
                typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                gp_seq_t points;
                // a -> b
                omni::geometry::path::basic_line(ax, ay, bx, by, step, points);
                // b -> c
                omni::geometry::path::basic_line(bx, by, cx, cy, step, points);
                // c -> a
                omni::geometry::path::basic_line(cx, cy, ax, ay, step, points);
                if (remove_duplicates) {
                    typename gp_seq_t::iterator it = points.begin();
                    typename gp_seq_t::iterator next = (it + 1);
                    while (next != points.end()) {
                        if (*it == *next) {
                            points.erase(next);
                            next = it;
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
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip)
            {
                return omni::geometry::path::triangle<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step)
            {
                return omni::geometry::path::triangle<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            triangle(T ax, T ay, T bx, T by, T cx, T cy)
            {
                return omni::geometry::path::triangle<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, static_cast<T>(1), 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, bool remove_duplicates)
            {
                return omni::geometry::path::triangle<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(ax, ay, bx, by, cx, cy, step, skip, remove_duplicates);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip)
            {
                return omni::geometry::path::triangle<std_seq_t, T>(ax, ay, bx, by, cx, cy, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step)
            {
                return omni::geometry::path::triangle<std_seq_t, T>(ax, ay, bx, by, cx, cy, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy)
            {
                return omni::geometry::path::triangle<std_seq_t, T>(ax, ay, bx, by, cx, cy, static_cast<T>(1), 0, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip, bool remove_duplicates)
            {
                return omni::geometry::path::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, step, skip, remove_duplicates);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step, uint32_t skip)
            {
                return omni::geometry::path::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, step, skip, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy, T step)
            {
                return omni::geometry::path::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, step, 0, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            triangle(T ax, T ay, T bx, T by, T cx, T cy)
            {
                return omni::geometry::path::triangle<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, static_cast<T>(1), 0, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, bool remove_duplicates)
            {
                typedef std_seq_t< omni::geometry::point2d<T>, std_allocator_t > gp_seq_t;
                gp_seq_t points;
                // a -> b
                omni::geometry::path::basic_line(ax, ay, bx, by, step, points);
                // b -> c
                omni::geometry::path::basic_line(bx, by, cx, cy, step, points);
                // c -> d
                omni::geometry::path::basic_line(cx, cy, dx, dy, step, points);
                // d -> a
                omni::geometry::path::basic_line(dx, dy, ax, ay, step, points);
                if (remove_duplicates) {
                    typename gp_seq_t::iterator it = points.begin();
                    typename gp_seq_t::iterator next = (it + 1);
                    while (next != points.end()) {
                        if (*it == *next) {
                            points.erase(next);
                            next = it;
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
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, dx, dy, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T, typename std_allocator_t >
            inline std_seq_t< typename omni::geometry::point2d< T >, std_allocator_t >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T, std_allocator_t>(ax, ay, bx, by, cx, cy, dx, dy, static_cast<T>(1), 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d< T >, typename std::allocator< omni::geometry::point2d< T > > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, bool remove_duplicates)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T, std::allocator< omni::geometry::point2d<T> > >(ax, ay, bx, by, cx, cy, dx, dy, step, skip, remove_duplicates);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, 0, true);
            }

            template < template < class, class > class std_seq_t, typename T >
            inline std_seq_t< typename omni::geometry::point2d<T>, typename std::allocator< omni::geometry::point2d<T> > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
            {
                return omni::geometry::path::quadrilateral<std_seq_t, T>(ax, ay, bx, by, cx, cy, dx, dy, static_cast<T>(1), 0, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip, bool remove_duplicates)
            {
                return omni::geometry::path::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, remove_duplicates);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step, uint32_t skip)
            {
                return omni::geometry::path::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, skip, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T step)
            {
                return omni::geometry::path::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, step, 0, true);
            }

            template < typename T >
            inline omni_sequence_t< omni::geometry::point2d< T > >
            quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
            {
                return omni::geometry::path::quadrilateral<omni_sequence_t, T>(ax, ay, bx, by, cx, cy, dx, dy, static_cast<T>(1), 0, true);
            }
        }
    }
}

#endif // OMNI_GEOMETRY_PATH_HPP
