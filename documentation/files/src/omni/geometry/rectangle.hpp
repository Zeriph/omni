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
#if !defined(OMNI_RECTANGLE_HPP)
#define OMNI_RECTANGLE_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/size.hpp>
#include <omni/geometry/point2d.hpp>
#include <omni/geometry/circle.hpp>
#include <omni/geometry/path.hpp>

#if defined(OMNI_SAFE_RECTANGLE)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_RECTMTX_FW  ,m_mtx()
    #define OMNI_SAFE_RECTLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_RECTUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_RECTALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_RECTOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_RECTMTX_FW
    #define OMNI_SAFE_RECTLOCK_FW
    #define OMNI_SAFE_RECTUNLOCK_FW
    #define OMNI_SAFE_RECTALOCK_FW
    #define OMNI_SAFE_RECTOALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class rectangle
        {
            public:
                typedef T coordinate_t;
                typedef omni_sequence_t< omni::geometry::point2d< T > > path_t;

                rectangle() : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                { }

                rectangle(const omni::geometry::rectangle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_loc(cp.location()), m_edge(), m_size(cp.size())
                    OMNI_SAFE_RECTMTX_FW
                {
                    this->_recalc_edge();
                }

                OMNI_EXPLICIT rectangle(const omni::math::dimensional<T, 4>& cp) :
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(cp[0], cp[1]), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    if ((cp[2] < 0) || (cp[3] < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->m_size.width = cp[2];
                    this->m_size.height = cp[3];
                    this->_recalc_edge();
                }

                rectangle(T x, T y, T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(x, y), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->m_size.width = w;
                    this->m_size.height = h;
                    this->_recalc_edge();
                }

                rectangle(T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(0, 0), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->m_size.width = w;
                    this->m_size.height = h;
                    this->_recalc_edge();
                }

                rectangle(const omni::geometry::raw_size<T>& sz) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(0, 0), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    if ((sz.width < 0) || (sz.height < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->m_size.width = sz.width;
                    this->m_size.height = sz.height;
                    this->_recalc_edge();
                }

                rectangle(const omni::geometry::size<T>& sz) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(0, 0), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    T w = sz.width();
                    T h = sz.height();
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->m_size.width = w;
                    this->m_size.height = h;
                    this->_recalc_edge();
                }

                rectangle(const omni::geometry::point2d<T>& p1, const omni::geometry::point2d<T>& p2) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y())), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    this->m_size.width = std::max(std::max(p1.x(), p2.x()) - this->m_loc.x, 0);
                    this->m_size.height = std::max(std::max(p1.y(), p2.y()) - this->m_loc.y, 0);
                    this->_recalc_edge();
                }

                rectangle(const omni::geometry::raw_point2d<T>& p1, const omni::geometry::raw_point2d<T>& p2) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(std::min(p1.x, p2.x), std::min(p1.y, p2.y)), m_edge(), m_size()
                    OMNI_SAFE_RECTMTX_FW
                {
                    this->m_size.width = std::max(std::max(p1.x, p2.x) - this->m_loc.x, 0);
                    this->m_size.height = std::max(std::max(p1.y, p2.y) - this->m_loc.y, 0);
                    this->_recalc_edge();
                }

                ~rectangle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T area() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.area();
                }

                T bottom() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge.y;
                }

                omni::geometry::point2d<T> bottom_left() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return omni::geometry::point2d<T>(this->m_loc.x, this->m_edge.y);
                }

                omni::geometry::point2d<T> bottom_right() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return omni::geometry::point2d<T>(this->m_edge.x, this->m_edge.y);
                }

                omni::geometry::point2d<T> centroid() const
                {
                    T x, y;
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::midpoint(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                    return omni::geometry::point2d<T>(x, y);
                }
                
                omni::geometry::point2d<T> circumcenter() const
                {
                    return this->centroid();
                }

                omni::geometry::circle<T> circle_from_circumcenter() const
                {
                    T x, y;
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::midpoint(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                    return omni::geometry::circle<T>(x, y,
                        (std::sqrt(
                            static_cast<double>((this->m_size.width * this->m_size.width) + (this->m_size.height * this->m_size.height))
                        ) / 2.0)
                    );
                }

                omni::geometry::circle<T> circle_from_incenter() const
                {
                    T x, y;
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::midpoint(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                    return omni::geometry::circle<T>(x, y,
                        static_cast<double>(std::min(this->m_size.width, this->m_size.height)) / 2.0
                    );
                }

                omni::math::shape_comparator compare(const omni::geometry::rectangle<T>& rect) const
                {
                    if (this == &rect) { return omni::math::shape_comparator::SIMILAR_CONGRUENT; }
                    omni::math::shape_comparator ret = omni::math::shape_comparator::NOT_EQUAL;
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_SAFE_RECTOALOCK_FW(rect)
                    bool w = (this->m_size.width == rect.m_size.width);
                    bool h = (this->m_size.height == rect.m_size.height);
                    if (w || h) {
                        ret = omni::math::shape_comparator::SIMILAR;
                    }
                    if (w && h) {
                        ret |= omni::math::shape_comparator::CONGRUENT;
                    }
                    return ret;
                }

                bool contains(T x, T y) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                }

                bool contains(const omni::math::dimensional<T, 2>& point) const
                {
                    return this->contains(point[0], point[1]);
                }

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::raw_point2d<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }
                
                bool contains(T left, T top, T right, T bottom) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return
                        OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, left, top) &&
                        OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, right, bottom);
                }

                bool contains(const omni::math::dimensional<T, 4>& point) const
                {
                    return this->contains(point[0], point[1], point[2], point[3]);
                }
                
                bool contains(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T left = point.x();
                    T top = point.y();
                    return this->contains(left, top, (left + sz.width()), (top + sz.height()));
                }

                bool contains(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz) const
                {
                    T left = point.x;
                    T top = point.y;
                    return this->contains(left, top, (left + sz.width), (top + sz.height));
                }

                bool contains(const omni::geometry::rectangle<T>& rect) const
                {
                    if (this == &rect) { return true; }
                    return this->contains(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                omni::geometry::rectangle<T>& decrement(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, x)
                    this->m_loc.x -= x;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, y)
                    this->m_loc.y -= y;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_edge.x, x)
                    this->m_edge.x -= x;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_edge.y, y)
                    this->m_edge.y -= y;
                    return *this;
                }

                omni::geometry::rectangle<T>& decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                omni::geometry::rectangle<T>& decrement(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                omni::geometry::rectangle<T>& decrement(const omni::math::dimensional<T, 2>& point)
                {
                    return this->decrement(point[0], point[1]);
                }

                T decrement_x()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_edge.x, 1)
                    --this->m_edge.x;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, 1)
                    return --this->m_loc.x;
                }

                T decrement_y()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_edge.y, 1)
                    --this->m_edge.y;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, 1)
                    return --this->m_loc.y;
                }

                T decrement_x(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_edge.x, val)
                    this->m_edge.x -= val;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, val)
                    return (this->m_loc.x -= val);
                }

                T decrement_y(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_edge.y, val)
                    this->m_edge.y -= val;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, val)
                    return (this->m_loc.y -= val);
                }

                omni::geometry::rectangle<T>& deflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_RETV_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"), *this)
                    }
                    OMNI_SAFE_RECTALOCK_FW

                    T x, y;
                    double out_x, out_y;
                    double factor = (1.0 - (percent / 100.0));
                    omni::math::midpoint(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                    omni::math::extend_line<double>(x, y, this->m_loc.x, this->m_loc.y, (omni::math::distance_between_2_points<double>(x, y, this->m_loc.x, this->m_loc.y) * factor), out_x, out_y);
                    this->m_loc.x = static_cast<T>(out_x);
                    this->m_loc.y = static_cast<T>(out_y);
                    omni::math::extend_line<double>(x, y, this->m_edge.x, this->m_edge.y, (omni::math::distance_between_2_points<double>(x, y, this->m_edge.x, this->m_edge.y) * factor), out_x, out_y);
                    this->m_edge.x = static_cast<T>(out_x);
                    this->m_edge.y = static_cast<T>(out_y);
                    this->m_size.width = std::max((this->m_edge.x - this->m_loc.x), 0);
                    this->m_size.height = std::max((this->m_edge.y - this->m_loc.y), 0);
                    return *this;
                }

                omni::geometry::rectangle<T>& deflate(T w, T h)
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_RETV_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"), *this)
                    }
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, w)
                    this->m_loc.x += w;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, h)
                    this->m_loc.y += h;
                    // do a double add instead of 2*w in case 2*w overflows
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.width, w)
                    this->m_size.width -= w;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.width, w)
                    this->m_size.width -= w;
                    if (this->m_size.width < 0) { this->m_size.width = 0; }
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.height, h)
                    this->m_size.height -= h;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.height, h)
                    this->m_size.height -= h;
                    if (this->m_size.height < 0) { this->m_size.height = 0; }
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& deflate(const omni::geometry::size<T>& sz)
                {
                    return this->deflate(sz.width(), sz.height());
                }

                omni::geometry::rectangle<T>& deflate(const omni::geometry::raw_size<T>& sz)
                {
                    return this->deflate(sz.width, sz.height);
                }

                omni::geometry::rectangle<T>& deflate(const omni::math::dimensional<T, 2>& sz) const
                {
                    return this->deflate(sz[0], sz[1]);
                }

                double diagonal() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return std::sqrt(
                        static_cast<double>((this->m_size.height * this->m_size.height) + (this->m_size.width * this->m_size.width))
                    );
                }

                omni::geometry::raw_point2d<T> edge() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge;
                }

                bool empty() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.empty() && this->m_size.empty();
                }

                bool empty_size() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.empty();
                }

                bool equals(T x, T y, T w, T h) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return
                        omni::math::are_equal<T>(this->m_loc.x, x) &&
                        omni::math::are_equal<T>(this->m_loc.y, y) &&
                        omni::math::are_equal<T>(this->m_size.width, w) &&
                        omni::math::are_equal<T>(this->m_size.height, h);
                }

                bool equals(const omni::math::dimensional<T, 2>& loc, const omni::math::dimensional<T, 2>& sz) const
                {
                    return this->equals(loc[0], loc[1], sz[0], sz[1]);
                }

                bool equals(const omni::geometry::point2d<T>& loc, const omni::geometry::size<T>& sz) const
                {
                    return this->equals(loc.x(), loc.y(), sz.width(), sz.height());
                }

                bool equals(const omni::geometry::raw_point2d<T>& loc, const omni::geometry::raw_size<T>& sz) const
                {
                    return this->equals(loc.x, loc.y, sz.width, sz.height);
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_loc.x) ^
                        ((static_cast<int32_t>(this->m_loc.y) << 13) | (static_cast<int32_t>(this->m_loc.y) >> 19)) ^
                        ((static_cast<int32_t>(this->m_size.width) << 26) | (static_cast<int32_t>(this->m_size.width) >>  6)) ^
                        ((static_cast<int32_t>(this->m_size.height) <<  7) | (static_cast<int32_t>(this->m_size.height) >> 25))
                    );
                }

                T height() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.height;
                }

                omni::geometry::rectangle<T>& increment(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, x)
                    this->m_loc.x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, y)
                    this->m_loc.y += y;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.x, x)
                    this->m_edge.x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.y, y)
                    this->m_edge.y += y;
                    return *this;
                }

                omni::geometry::rectangle<T>& increment(const omni::geometry::point2d<T>& point)
                {
                    return this->increment(point.x(), point.y());
                }

                omni::geometry::rectangle<T>& increment(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->increment(point.x, point.y);
                }

                omni::geometry::rectangle<T>& increment(const omni::math::dimensional<T, 2>& point)
                {
                    return this->increment(point[0], point[1]);
                }

                T increment_x()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.x, 1)
                    ++this->m_edge.x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, 1)
                    return ++this->m_loc.x;
                }

                T increment_y()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.y, 1)
                    ++this->m_edge.y;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, 1)
                    return ++this->m_loc.y;
                }

                T increment_x(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.x, val)
                    this->m_edge.x += val;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, val)
                    return (this->m_loc.x += val);
                }

                T increment_y(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.y, val)
                    this->m_edge.y += val;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, val)
                    return (this->m_loc.y += val);
                }

                omni::geometry::rectangle<T>& inflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_RETV_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"), *this)
                    }
                    OMNI_SAFE_RECTALOCK_FW

                    T x, y;
                    double out_x, out_y;
                    double factor = percent / 100.0;
                    omni::math::midpoint(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                    omni::math::extend_line<double>(x, y, this->m_loc.x, this->m_loc.y, (omni::math::distance_between_2_points<double>(x, y, this->m_loc.x, this->m_loc.y) * factor), out_x, out_y);
                    this->m_loc.x = static_cast<T>(out_x);
                    this->m_loc.y = static_cast<T>(out_y);
                    omni::math::extend_line<double>(x, y, this->m_edge.x, this->m_edge.y, (omni::math::distance_between_2_points<double>(x, y, this->m_edge.x, this->m_edge.y) * factor), out_x, out_y);
                    this->m_edge.x = static_cast<T>(out_x);
                    this->m_edge.y = static_cast<T>(out_y);
                    
                    this->m_size.width = std::max((this->m_edge.x - this->m_loc.x), 0);
                    this->m_size.height = std::max((this->m_edge.y - this->m_loc.y), 0);
                    return *this;
                }

                omni::geometry::rectangle<T>& inflate(T w, T h)
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_RETV_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"), *this)
                    }
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, w)
                    this->m_loc.x -= w;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, h)
                    this->m_loc.y -= h;
                    // do a double add instead of 2*w in case 2*w overflows
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.width, w)
                    this->m_size.width += w;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.width, w)
                    this->m_size.width += w;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.height, h)
                    this->m_size.height += h;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.height, h)
                    this->m_size.height += h;
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& inflate(const omni::geometry::size<T>& sz)
                {
                    return this->inflate(sz.width(), sz.height());
                }

                omni::geometry::rectangle<T>& inflate(const omni::geometry::raw_size<T>& sz)
                {
                    return this->inflate(sz.width, sz.height);
                }

                omni::geometry::rectangle<T>& inflate(const omni::math::dimensional<T, 2>& sz) const
                {
                    return this->inflate(sz[0], sz[1]);
                }

                omni::geometry::rectangle<T>& intersect(const omni::geometry::rectangle<T>& r2)
                {
                    if (this == &r2) { return *this; }
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_SAFE_RECTOALOCK_FW(r2)
                    if (this->_intersects_with(r2.m_loc.x, r2.m_loc.y, r2.m_edge.x, r2.m_edge.y)) {
                        this->m_loc.x = std::max(this->m_loc.x, r2.m_loc.x);
                        this->m_loc.y = std::max(this->m_loc.y, r2.m_loc.y);
                        this->m_size.width = std::max(std::min(this->m_edge.x, r2.m_edge.x) - this->m_loc.x, 0);
                        this->m_size.height = std::max(std::min(this->m_edge.y, r2.m_edge.y) - this->m_loc.y, 0);
                        this->_recalc_edge();
                    } else {
                        this->m_loc.x = 0;
                        this->m_loc.y = 0;
                        this->m_size.width = 0;
                        this->m_size.height = 0;
                        this->m_edge.x = 0;
                        this->m_edge.y = 0;
                    }
                    return *this;
                }

                bool intersects_with(T left, T top, T right, T bottom) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->_intersects_with(left, top, right, bottom);
                }

                bool intersects_with(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, (x + sz.width()), (y + sz.height()));
                }

                bool intersects_with(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz) const
                {
                    return this->intersects_with(point.x, point.y, (point.x + sz.width), (point.y + sz.height));
                }

                bool intersects_with(const omni::math::dimensional<T, 4>& rect) const
                {
                    return this->intersects_with(rect[0], rect[1], rect[2], rect[3]);
                }

                bool intersects_with(const omni::geometry::rectangle<T>& rect) const
                {
                    return this->intersects_with(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                omni::geometry::point2d<T> incenter() const
                {
                    return this->centroid();
                }

                bool is_square() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.height == this->m_size.width;
                }

                omni::geometry::raw_point2d<T> location() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc;
                }

                T left() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x;
                }

                omni::geometry::rectangle<T>& offset(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, x)
                    this->m_loc.x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, y)
                    this->m_loc.y += y;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.x, x)
                    this->m_edge.x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_edge.y, y)
                    this->m_edge.y += y;
                    return *this;
                }

                omni::geometry::rectangle<T>& offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                omni::geometry::rectangle<T>& offset(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                omni::geometry::rectangle<T>& offset(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->offset(coord[0], coord[1]);
                }

                path_t path() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return omni::geometry::path::rectangle(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y);
                }

                T perimeter() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return 2 * (this->m_size.height + this->m_size.width);
                }

                T right() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge.x;
                }

                omni::geometry::rectangle<T>& reflect()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_reflect(this->m_loc.x, this->m_loc.y, this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_on_lt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_rotate_point(
                        degrees, this->m_loc.x, this->m_loc.y, dir,
                        this->m_loc.x, this->m_loc.y,
                        this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_on_rt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_rotate_point(
                        degrees, this->m_loc.x + this->m_size.width, this->m_loc.y, dir,
                        this->m_loc.x, this->m_loc.y,
                        this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_on_lb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_rotate_point(
                        degrees, this->m_loc.x, this->m_loc.y + this->m_size.height, dir,
                        this->m_loc.x, this->m_loc.y,
                        this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_on_rb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_rotate_point(
                        degrees, this->m_loc.x + this->m_size.width, this->m_loc.y + this->m_size.height, dir,
                        this->m_loc.x, this->m_loc.y,
                        this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_centroid(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    T x, y;
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::midpoint(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, x, y);
                    omni::math::rectangle_rotate_point(degrees, x, y, dir, this->m_loc.x, this->m_loc.y, this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_circumcenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    return this->rotate_centroid(degrees, dir);
                }

                omni::geometry::rectangle<T>& rotate_incenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    return this->rotate_centroid(degrees, dir);
                }

                omni::geometry::rectangle<T>& rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_rotate_origin(degrees, dir, this->m_loc.x, this->m_loc.y, this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_rotate_point(degrees, x, y, dir, this->m_loc.x, this->m_loc.y, this->m_size.width, this->m_size.height);
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& scale(T x_scale, T y_scale)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    if (this->m_size.empty()) { // empty??
                        return *this;
                    }

                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_loc.x, x_scale)
                    this->m_loc.x *= x_scale;
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_loc.y, y_scale)
                    this->m_loc.y *= y_scale;
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_size.width, x_scale)
                    this->m_size.width *= x_scale;
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_size.height, y_scale)
                    this->m_size.height *= y_scale; 
        
                    // If the scale in the X dimension is negative, we need to normalize X and Width
                    if (x_scale < 0)  {
                        // Make X the left-most edge again
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, this->m_size.width)
                        this->m_loc.x += this->m_size.width;
                        // and make Width positive
                        OMNI_BITS_WILL_MUL_OVER_FW(this->m_size.width, -1)
                        this->m_size.width *= -1;
                    } 
                    // Do the same for the Y dimension 
                    if (y_scale < 0) {
                        // Make Y the top-most edge again
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, this->m_size.height)
                        this->m_loc.y += this->m_size.height;
                        // and make Height positive
                        OMNI_BITS_WILL_MUL_OVER_FW(this->m_size.height, -1)
                        this->m_size.height *= -1;
                    }
                    return *this;
                }

                omni::geometry::rectangle<T>& set_location(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_loc.x = x;
                    this->m_loc.y = y;
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& set_location(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->set_location(coord[0], coord[1]);
                }

                omni::geometry::rectangle<T>& set_location(const omni::geometry::point2d<T>& point)
                {
                    return this->set_location(point.x(), point.y());
                }

                omni::geometry::rectangle<T>& set_location(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->set_location(point.x, point.y);
                }

                omni::geometry::rectangle<T>& set_size(T w, T h)
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_RETV_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"), *this)
                    }
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_size.width = w;
                    this->m_size.height = h;
                    this->_recalc_edge();
                    return *this;
                }

                omni::geometry::rectangle<T>& set_size(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->set_size(coord[0], coord[1]);
                }

                omni::geometry::rectangle<T>& set_size(const omni::geometry::size<T>& sz)
                {
                    return this->set_size(sz.width(), sz.height());
                }

                omni::geometry::rectangle<T>& set_size(const omni::geometry::raw_size<T>& sz)
                {
                    return this->set_size(sz.width, sz.height);
                }

                omni::geometry::raw_size<T> size() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size;
                }

                void swap(rectangle<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_RECTALOCK_FW
                        OMNI_SAFE_RECTOALOCK_FW(o)
                        std::swap(this->m_loc, o.m_loc);
                        std::swap(this->m_size, o.m_size);
                        std::swap(this->m_edge, o.m_edge);
                    }
                }

                T top() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.y;
                }

                omni::geometry::point2d<T> top_left() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return omni::geometry::point2d<T>(this->m_loc.x, this->m_loc.y);
                }

                omni::geometry::point2d<T> top_right() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return omni::geometry::point2d<T>(this->m_edge.x, this->m_loc.y);
                }

                void translate_xy(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_translate_xy(x, y, this->m_loc.x, this->m_loc.y);
                    this->_recalc_edge();
                }

                void translate_angle(float angle, T distance)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    omni::math::rectangle_translate_angle(angle, distance, this->m_loc.x, this->m_loc.y);
                    this->_recalc_edge();
                }

                void union_merge(const omni::geometry::rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_SAFE_RECTOALOCK_FW(r2)
                    if (this->m_size.empty()) {
                        this->m_loc.x = r2.m_loc.x;
                        this->m_loc.y = r2.m_loc.y;
                        this->m_size.width = r2.m_size.width;
                        this->m_size.height = r2.m_size.height;
                        this->_recalc_edge();
                    } else if (!r2.m_size.empty()) {
                        this->m_loc.x = std::min(this->m_loc.x, r2.m_loc.x);
                        this->m_loc.y = std::min(this->m_loc.y, r2.m_loc.y);
                        this->m_size.width = std::max(std::max(this->m_edge.x, r2.m_edge.x) - this->m_loc.x, 0);
                        this->m_size.height = std::max(std::max(this->m_edge.y, r2.m_edge.y) - this->m_loc.y, 0);
                        this->_recalc_edge();
                    }
                    // else there's no union 
                }

                T width() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width;
                }

                T x() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x;
                }

                T y() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.y;
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_RECTLOCK_FW
                    s << "{" << this->m_loc.to_string_t() << "," << this->m_size.to_string_t() << "}";
                    OMNI_SAFE_RECTUNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::string ret = "{";
                    OMNI_SAFE_RECTLOCK_FW
                    ret.append(this->m_loc.to_string());
                    ret.append(",");
                    ret.append(this->m_size.to_string());
                    OMNI_SAFE_RECTUNLOCK_FW
                    ret.append("}");
                    return ret;
                }

                std::wstring to_wstring() const
                {
                    std::wstring ret = L"{";
                    OMNI_SAFE_RECTLOCK_FW
                    ret.append(this->m_loc.to_wstring());
                    ret.append(L",");
                    ret.append(this->m_size.to_wstring());
                    OMNI_SAFE_RECTUNLOCK_FW
                    ret.append(L"}");
                    return ret;
                }

                operator std::string() const
                { 
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }
                
                bool operator!=(const omni::geometry::rectangle<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator!=(const omni::geometry::point2d<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator!=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator!=(const omni::geometry::size<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator!=(const omni::geometry::raw_size<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::rectangle<T>& operator=(const omni::geometry::rectangle<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_RECTALOCK_FW
                        OMNI_SAFE_RECTOALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_loc.x = val.m_loc.x;
                        this->m_loc.y = val.m_loc.y;
                        this->m_size.width = val.m_size.width;
                        this->m_size.height = val.m_size.height;
                        this->_recalc_edge();
                    }
                    return *this;
                }

                bool operator==(const omni::geometry::rectangle<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.m_loc.x) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.m_loc.y) &&
                        omni::math::are_equal<T>(this->m_size.width, val.m_size.width) &&
                        omni::math::are_equal<T>(this->m_size.height, val.m_size.height))
                    OMNI_EQUAL_FW(val);
                }

                bool operator==(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.x()) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.y()));
                }

                bool operator==(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.x) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.y));
                }

                bool operator==(const omni::geometry::size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_size.width, val.width()) &&
                        omni::math::are_equal<T>(this->m_size.height, val.height()));
                }

                bool operator==(const omni::geometry::raw_size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_size.width, val.width) &&
                        omni::math::are_equal<T>(this->m_size.height, val.height));
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x < val.x() && this->m_loc.y < val.y();
                }

                bool operator<(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x < val.x && this->m_loc.y < val.y;
                }

                bool operator<(const omni::geometry::size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width < val.width() && this->m_size.height < val.height();
                }

                bool operator<(const omni::geometry::raw_size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width < val.width && this->m_size.height < val.height;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x > val.x() && this->m_loc.y > val.y();
                }

                bool operator>(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x > val.x && this->m_loc.y > val.y;
                }

                bool operator>(const omni::geometry::size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width > val.width() && this->m_size.height > val.height();
                }

                bool operator>(const omni::geometry::raw_size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width > val.width && this->m_size.height > val.height;
                }
                
                bool operator<=(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x <= val.x() && this->m_loc.y <= val.y();
                }

                bool operator<=(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x <= val.x && this->m_loc.y <= val.y;
                }

                bool operator<=(const omni::geometry::size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width <= val.width() && this->m_size.height <= val.height();
                }

                bool operator<=(const omni::geometry::raw_size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width <= val.width && this->m_size.height <= val.height;
                }

                bool operator>=(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x >= val.x() && this->m_loc.y >= val.y();
                }

                bool operator>=(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x >= val.x && this->m_loc.y >= val.y;
                }

                bool operator>=(const omni::geometry::size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width >= val.width() && this->m_size.height >= val.height();
                }

                bool operator>=(const omni::geometry::raw_size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width >= val.width && this->m_size.height >= val.height;
                }

                omni::geometry::rectangle<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, val.x())
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, val.y())
                    return omni::geometry::rectangle<T>((this->m_loc.x + val.x()),
                                        (this->m_loc.y + val.y()),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                omni::geometry::rectangle<T> operator+(const omni::geometry::raw_point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, val.x)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, val.y)
                    return omni::geometry::rectangle<T>((this->m_loc.x + val.x),
                                        (this->m_loc.y + val.y),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                omni::geometry::rectangle<T> operator+(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.width, val.width())
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.height, val.height())
                    return omni::geometry::rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width + val.width()),
                                        (this->m_size.height + val.height()));
                }

                omni::geometry::rectangle<T> operator+(const omni::geometry::raw_size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.width, val.width)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_size.height, val.height)
                    return omni::geometry::rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width + val.width),
                                        (this->m_size.height + val.height));
                }

                omni::geometry::rectangle<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, val.x())
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, val.y())
                    return omni::geometry::rectangle<T>((this->m_loc.x - val.x()),
                                        (this->m_loc.y - val.y()),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                omni::geometry::rectangle<T> operator-(const omni::geometry::raw_point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, val.x)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, val.y)
                    return omni::geometry::rectangle<T>((this->m_loc.x - val.x),
                                        (this->m_loc.y - val.y),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                omni::geometry::rectangle<T> operator-(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.width, val.width())
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.height, val.height())
                    return omni::geometry::rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width - val.width()),
                                        (this->m_size.height - val.height()));
                }

                omni::geometry::rectangle<T> operator-(const omni::geometry::raw_size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.width, val.width)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_size.height, val.height)
                    return omni::geometry::rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width - val.width),
                                        (this->m_size.height - val.height));
                }

                omni::geometry::rectangle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                omni::geometry::rectangle<T>& operator+=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                omni::geometry::rectangle<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->inflate(val.width(), val.height());
                    return *this;
                }

                omni::geometry::rectangle<T>& operator+=(const omni::geometry::raw_size<T>& val)
                {
                    this->inflate(val.width, val.height);
                    return *this;
                }

                omni::geometry::rectangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                omni::geometry::rectangle<T>& operator-=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                omni::geometry::rectangle<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->deflate(val.width(), val.height());
                    return *this;
                }

                omni::geometry::rectangle<T>& operator-=(const omni::geometry::raw_size<T>& val)
                {
                    this->deflate(val.width, val.height);
                    return *this;
                }

                static omni::geometry::rectangle<T> from_ltrb(T left, T top, T right, T bottom)
                {
                    OMNI_BITS_WILL_SUB_UNDER_FW(right, left)
                    OMNI_BITS_WILL_SUB_UNDER_FW(bottom, top)
                    return omni::geometry::rectangle<T>(left,
                                        top,
                                        (right - left), // width
                                        (bottom - top)); // height
                }

                static omni::geometry::rectangle<T> deflate(const omni::geometry::rectangle<T>& rect, T w, T h)
                {
                    return omni::geometry::rectangle<T>(rect, w, h, 'd');
                }

                static omni::geometry::rectangle<T> inflate(const omni::geometry::rectangle<T>& rect, T w, T h)
                {
                    return omni::geometry::rectangle<T>(rect, w, h, 'i');
                }

                static omni::geometry::rectangle<T> intersect(const omni::geometry::rectangle<T>& a, const omni::geometry::rectangle<T>& b)
                {
                    return omni::geometry::rectangle<T>(a, b, true);
                }

                static omni::geometry::rectangle<T> scale(const omni::geometry::rectangle<T>& rect, T w, T h)
                {
                    return omni::geometry::rectangle<T>(rect, w, h, 's');
                }

                static omni::geometry::rectangle<T> union_merge(const omni::geometry::rectangle<T>& a, const omni::geometry::rectangle<T>& b)
                {
                    return omni::geometry::rectangle<T>(a, b, false);
                }

                OMNI_MEMBERS_FW(omni::geometry::rectangle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::rectangle<T>)

            private:
                omni::geometry::raw_point2d<T> m_loc;
                omni::geometry::raw_point2d<T> m_edge;
                omni::geometry::raw_size<T> m_size;
                #if defined(OMNI_SAFE_RECTANGLE)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                rectangle(const omni::geometry::rectangle<T>& a, const omni::geometry::rectangle<T>& b, bool isect) :
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(a.location()), m_edge(), m_size(a.size())
                    OMNI_SAFE_RECTMTX_FW
                {
                    this->_recalc_edge();
                    if (isect) {
                        this->intersect(b);
                    } else {
                        this->union_merge(b);
                    }
                }

                rectangle(const omni::geometry::rectangle<T>& a, T w, T h, char type) :
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(a.location()), m_edge(), m_size(a.size())
                    OMNI_SAFE_RECTMTX_FW
                {
                    this->_recalc_edge();
                    switch (type) {
                        case 'd': this->deflate(w, h); break;
                        case 'i': this->inflate(w, h); break;
                        case 's': this->scale(w, h); break;
                    }
                }

                bool _intersects_with(T left, T top, T right, T bottom) const
                {
                    return (
                        OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, left, top) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, right, top) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, left, bottom) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(this->m_loc.x, this->m_loc.y, this->m_edge.x, this->m_edge.y, right, bottom)
                        ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, this->m_loc.x, this->m_loc.y) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, this->m_edge.x, this->m_loc.y) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, this->m_loc.x, this->m_edge.y) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, this->m_edge.x, this->m_edge.y)
                    );
                }

                void _recalc_edge()
                {
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, this->m_size.width)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, this->m_size.height)
                    this->m_edge.x = this->m_loc.x + this->m_size.width; // right
                    this->m_edge.y = this->m_loc.y + this->m_size.height; // bottom
                }
        };

        typedef omni::geometry::rectangle<int32_t> rectangle_t;
        typedef omni::geometry::rectangle<int64_t> rectangle64_t;
        typedef omni::geometry::rectangle<float> rectangleF_t;

        // DEV_NOTE: "raw" classes do not have checks, like arithmetic over/under flow, locks, etc.

        template < typename T >
        class raw_rectangle
        {
            public:
                typedef T coordinate_t;
                typedef omni_sequence_t< omni::geometry::point2d< T > > path_t;

                raw_rectangle() : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(), size()
                { }

                raw_rectangle(const omni::geometry::raw_rectangle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    location(cp.location), size(cp.size)
                {
                    if ((cp.size.width < 0) || (cp.size.height < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->size = cp.size;
                }

                raw_rectangle(const omni::geometry::rectangle<T>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(cp.location()), size(cp.size())
                { }

                raw_rectangle(const omni::math::dimensional<T, 4>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(cp[0], cp[1]), size()
                {
                    if ((cp[2] < 0) || (cp[3] < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->size.width = cp[2];
                    this->size.height = cp[3];
                }

                raw_rectangle(T x, T y, T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(x, y), size(w, h)
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->size.width = w;
                    this->size.height = h;
                }

                raw_rectangle(T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(0, 0), size()
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->size.width = w;
                    this->size.height = h;
                }

                raw_rectangle(const omni::geometry::raw_size<T>& sz) : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(0, 0), size()
                {
                    if ((sz.width < 0) || (sz.height < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->size.width = sz.width;
                    this->size.height = sz.height;
                }

                raw_rectangle(const omni::geometry::size<T>& sz) : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(0, 0), size()
                {
                    T w = sz.width();
                    T h = sz.height();
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"))
                    }
                    this->size.width = w;
                    this->size.height = h;
                }

                raw_rectangle(const omni::geometry::point2d<T>& p1, const omni::geometry::point2d<T>& p2) : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y())), size()
                {
                    this->size.width = std::max(std::max(p1.x(), p2.x()) - this->location.x, 0);
                    this->size.height = std::max(std::max(p1.y(), p2.y()) - this->location.y, 0);
                }

                raw_rectangle(const omni::geometry::raw_point2d<T>& p1, const omni::geometry::raw_point2d<T>& p2) : 
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(std::min(p1.x, p2.x), std::min(p1.y, p2.y)), size()
                {
                    this->size.width = std::max(std::max(p1.x, p2.x) - this->location.x, 0);
                    this->size.height = std::max(std::max(p1.y, p2.y) - this->location.y, 0);
                }

                ~raw_rectangle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T area() const
                {
                    return this->size.width * this->size.height;
                }

                T bottom() const
                {
                    return this->location.y + this->size.height;
                }

                omni::geometry::point2d<T> bottom_left() const
                {
                    return omni::geometry::point2d<T>(this->location.x, (this->location.y + this->size.height));
                }

                omni::geometry::point2d<T> bottom_right() const
                {
                    return this->edge();
                }

                omni::geometry::point2d<T> centroid() const
                {
                    T x, y;
                    omni::math::midpoint(this->location.x, this->location.y, (this->location.x + this->size.width), (this->location.y + this->size.height), x, y);
                    return omni::geometry::point2d<T>(x, y);
                }
                
                omni::geometry::point2d<T> circumcenter() const
                {
                    return this->centroid();
                }

                omni::geometry::circle<T> circle_from_circumcenter() const
                {
                    T x, y;
                    omni::math::midpoint(this->location.x, this->location.y, (this->location.x + this->size.width), (this->location.y + this->size.height), x, y);
                    return omni::geometry::circle<T>(x, y,
                        (std::sqrt(
                            static_cast<double>((this->size.width * this->size.width) + (this->size.height * this->size.height))
                        ) / 2.0)
                    );
                }

                omni::geometry::circle<T> circle_from_incenter() const
                {
                    T x, y;
                    omni::math::midpoint(this->location.x, this->location.y, (this->location.x + this->size.width), (this->location.y + this->size.height), x, y);
                    return omni::geometry::circle<T>(x, y,
                        static_cast<double>(std::min(this->size.width, this->size.height)) / 2.0
                    );
                }

                omni::math::shape_comparator compare(const omni::geometry::raw_rectangle<T>& rect) const
                {
                    if (this == &rect) { return omni::math::shape_comparator::SIMILAR_CONGRUENT; }
                    omni::math::shape_comparator ret = omni::math::shape_comparator::NOT_EQUAL;
                    bool w = (this->size.width == rect.size.width);
                    bool h = (this->size.height == rect.size.height);
                    if (w || h) {
                        ret = omni::math::shape_comparator::SIMILAR;
                    }
                    if (w && h) {
                        ret |= omni::math::shape_comparator::CONGRUENT;
                    }
                    return ret;
                }

                bool contains(T x, T y) const
                {
                    return OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, x, y);
                }

                bool contains(const omni::math::dimensional<T, 2>& point) const
                {
                    return this->contains(point[0], point[1]);
                }

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::raw_point2d<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }
                
                bool contains(T left, T top, T right, T bottom) const
                {
                    return
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, left, top) &&
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, right, bottom);
                }

                bool contains(const omni::math::dimensional<T, 4>& rect) const
                {
                    return this->contains(rect[0], rect[1], rect[2], rect[3]);
                }
                
                bool contains(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T left = point.x();
                    T top = point.y();
                    return this->contains(left, top, (left + sz.width()), (top + sz.height()));
                }

                bool contains(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz) const
                {
                    T left = point.x;
                    T top = point.y;
                    return this->contains(left, top, (left + sz.width), (top + sz.height));
                }

                bool contains(const omni::geometry::raw_rectangle<T>& rect) const
                {
                    if (this == &rect) { return true; }
                    return this->contains(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                omni::geometry::raw_rectangle<T>& decrement(T x, T y)
                {
                    this->location.x -= x;
                    this->location.y -= y;
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& decrement(const omni::math::dimensional<T, 2>& point)
                {
                    return this->decrement(point[0], point[1]);
                }

                void decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                void decrement(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                T decrement_x()
                {
                    return --this->location.x;
                }

                T decrement_y()
                {
                    return --this->location.y;
                }

                T decrement_x(T val)
                {
                    return (this->location.x -= val);
                }

                T decrement_y(T val)
                {
                    return (this->location.y -= val);
                }

                omni::geometry::raw_rectangle<T>& deflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_RETV_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"), *this)
                    }
                    
                    T x, y;
                    double out_x, out_y;
                    double factor = (1.0 - (percent / 100.0));
                    omni::geometry::raw_point2d<T> edg = this->edge();
                    omni::math::midpoint(this->location.x, this->location.y, edg.x, edg.y, x, y);
                    omni::math::extend_line<double>(x, y, this->location.x, this->location.y, (omni::math::distance_between_2_points<double>(x, y, this->location.x, this->location.y) * factor), out_x, out_y);
                    this->location.x = static_cast<T>(out_x);
                    this->location.y = static_cast<T>(out_y);
                    omni::math::extend_line<double>(x, y, edg.x, edg.y, (omni::math::distance_between_2_points<double>(x, y, edg.x, edg.y) * factor), out_x, out_y);
                    edg.x = static_cast<T>(out_x);
                    edg.y = static_cast<T>(out_y);
                    this->size.width = std::max((edg.x - this->location.x), 0);
                    this->size.height = std::max((edg.y - this->location.y), 0);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& deflate(T w, T h)
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_RETV_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"), *this)
                    }
                    this->location.x += w;
                    this->location.y += h;
                    // do a double add instead of 2*w in case 2*w overflows
                    this->size.width -= w;
                    this->size.width -= w;
                    if (this->size.width < 0) { this->size.width = 0; }
                    this->size.height -= h;
                    this->size.height -= h;
                    if (this->size.height < 0) { this->size.height = 0; }
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& deflate(const omni::math::dimensional<T, 2>& sz)
                {
                    return this->deflate(sz[0], sz[1]);
                }

                omni::geometry::raw_rectangle<T>& deflate(const omni::geometry::size<T>& sz)
                {
                    return this->deflate(sz.width(), sz.height());
                }

                omni::geometry::raw_rectangle<T>& deflate(const omni::geometry::raw_size<T>& sz)
                {
                    return this->deflate(sz.width, sz.height);
                }

                double diagonal() const
                {
                    return std::sqrt(
                        static_cast<double>((this->size.height * this->size.height) + (this->size.width * this->size.width))
                    );
                }
                
                omni::geometry::raw_point2d<T> edge() const
                {
                    return omni::geometry::raw_point2d<T>(
                        (this->location.x + this->size.width),
                        (this->location.y + this->size.height)
                    );
                }

                bool empty() const
                {
                    return this->location.empty() && this->size.empty();
                }

                bool empty_size() const
                {
                    return this->size.empty();
                }

                bool equals(T _x, T _y, T _w, T _h) const
                {
                    return
                        omni::math::are_equal<T>(this->location.x, _x) &&
                        omni::math::are_equal<T>(this->location.y, _y) &&
                        omni::math::are_equal<T>(this->size.width, _w) &&
                        omni::math::are_equal<T>(this->size.height, _h);
                }

                bool equals(const omni::math::dimensional<T, 2>& loc, const omni::math::dimensional<T, 2>& sz) const
                {
                    return this->equals(loc[0], loc[1], sz[0], sz[1]);
                }

                bool equals(const omni::geometry::point2d<T>& loc, const omni::geometry::size<T>& sz) const
                {
                    return this->equals(loc.x(), loc.y(), sz.width(), sz.height());
                }

                bool equals(const omni::geometry::raw_point2d<T>& loc, const omni::geometry::raw_size<T>& sz) const
                {
                    return this->equals(loc.x, loc.y, sz.width, sz.height);
                }

                int32_t hash_code() const
                {
                    return (
                        static_cast<int32_t>(this->location.x) ^
                        ((static_cast<int32_t>(this->location.y) << 13) | (static_cast<int32_t>(this->location.y) >> 19)) ^
                        ((static_cast<int32_t>(this->size.width) << 26) | (static_cast<int32_t>(this->size.width) >>  6)) ^
                        ((static_cast<int32_t>(this->size.height) <<  7) | (static_cast<int32_t>(this->size.height) >> 25))
                    );
                }

                T height() const
                {
                    return this->size.height;
                }

                omni::geometry::raw_rectangle<T>& increment(T x, T y)
                {
                    this->location.x -= x;
                    this->location.y -= y;
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& increment(const omni::math::dimensional<T, 2>& point)
                {
                    return this->increment(point[0], point[1]);
                }

                omni::geometry::raw_rectangle<T>& increment(const omni::geometry::point2d<T>& point)
                {
                    return this->increment(point.x(), point.y());
                }

                omni::geometry::raw_rectangle<T>& increment(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->increment(point.x, point.y);
                }

                T increment_x()
                {
                    return ++this->location.x;
                }

                T increment_y()
                {
                    return ++this->location.y;
                }

                T increment_x(T val)
                {
                    return (this->location.x += val);
                }

                T increment_y(T val)
                {
                    return (this->location.y += val);
                }

                omni::geometry::raw_rectangle<T>& inflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_RETV_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"), *this)
                    }
                    T x, y;
                    double out_x, out_y;
                    double factor = percent / 100.0;
                    omni::geometry::raw_point2d<T> edg = this->edge();
                    omni::math::midpoint(this->location.x, this->location.y, edg.x, edg.y, x, y);
                    omni::math::extend_line<double>(x, y, this->location.x, this->location.y, (omni::math::distance_between_2_points<double>(x, y, this->location.x, this->location.y) * factor), out_x, out_y);
                    this->location.x = static_cast<T>(out_x);
                    this->location.y = static_cast<T>(out_y);
                    omni::math::extend_line<double>(x, y, edg.x, edg.y, (omni::math::distance_between_2_points<double>(x, y, edg.x, edg.y) * factor), out_x, out_y);
                    edg.x = static_cast<T>(out_x);
                    edg.y = static_cast<T>(out_y);
                    this->size.width = std::max((edg.x - this->location.x), 0);
                    this->size.height = std::max((edg.y - this->location.y), 0);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& inflate(T w, T h)
                {
                    if ((w < 0) || (h < 0)) {
                        OMNI_ERR_RETV_FW("width and height must be greater than 0", omni::exceptions::overflow_error("width and height must be greater than 0"), *this)
                    }
                    this->location.x -= w;
                    this->location.y -= h;
                    // do a double add instead of 2*w in case 2*w overflows
                    this->size.width += w;
                    this->size.width += w;
                    this->size.height += h;
                    this->size.height += h;
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& inflate(const omni::math::dimensional<T, 2>& sz)
                {
                    return this->inflate(sz[0], sz[1]);
                }

                omni::geometry::raw_rectangle<T>& inflate(const omni::geometry::size<T>& sz)
                {
                    return this->inflate(sz.width(), sz.height());
                }

                omni::geometry::raw_rectangle<T>& inflate(const omni::geometry::raw_size<T>& sz)
                {
                    return this->inflate(sz.width, sz.height);
                }

                omni::geometry::raw_rectangle<T>& intersect(const omni::geometry::rectangle<T>& r2)
                {
                    this->_intersect(r2.x(), r2.y(), r2.edge());
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& intersect(const omni::geometry::raw_rectangle<T>& r2)
                {
                    if (this == &r2) { return *this; }
                    this->_intersect(r2.x(), r2.y(), r2.edge());
                    return *this;
                }

                bool intersects_with(T left, T top, T right, T bottom) const
                {
                    return (
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, left, top) ||
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, right, top) ||
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, left, bottom) ||
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, right, bottom)
                        ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, this->location.x, this->location.y) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, (this->location.x + this->size.width), this->location.y) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, this->location.x, (this->location.y + this->size.height)) ||
                        OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, (this->location.x + this->size.width), (this->location.y + this->size.height))
                    );
                }

                bool intersects_with(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, (x + sz.width()), (y + sz.height()));
                }

                bool intersects_with(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz) const
                {
                    return this->intersects_with(point.x, point.y, (point.x + sz.width), (point.y + sz.height));
                }

                bool intersects_with(const omni::math::dimensional<T, 4>& rect) const
                {
                    return this->intersects_with(rect[0], rect[1], rect[2], rect[3]);
                }

                bool intersects_with(const omni::geometry::raw_rectangle<T>& rect) const
                {
                    return this->intersects_with(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                omni::geometry::point2d<T> incenter() const
                {
                    return this->centroid();
                }

                bool is_square() const
                {
                    return this->size.height == this->size.width;
                }

                T left() const
                {
                    return this->location.x;
                }

                omni::geometry::raw_rectangle<T>& offset(T x, T y)
                {
                    this->location.x += x;
                    this->location.y += y;
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& offset(const omni::math::dimensional<T, 2>& point)
                {
                    return this->offset(point[0], point[2]);
                }

                omni::geometry::raw_rectangle<T>& offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                omni::geometry::raw_rectangle<T>& offset(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                path_t path() const
                {
                    return omni::geometry::path::rectangle(this->location.x, this->location.y, this->size.width, this->size.height);
                }

                T perimeter() const
                {
                    return 2 * (this->size.height + this->size.width);
                }

                T right() const
                {
                    return this->location.x + this->size.width;
                }

                omni::geometry::raw_rectangle<T>& reflect()
                {
                    omni::math::rectangle_reflect(this->location.x, this->location.y, this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_on_lt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::rectangle_rotate_point(
                        degrees, this->location.x, this->location.y, dir,
                        this->location.x, this->location.y,
                        this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_on_rt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::rectangle_rotate_point(
                        degrees, this->location.x + this->size.width, this->location.y, dir,
                        this->location.x, this->location.y,
                        this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_on_lb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::rectangle_rotate_point(
                        degrees, this->location.x, this->location.y + this->size.height, dir,
                        this->location.x, this->location.y,
                        this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_on_rb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::rectangle_rotate_point(
                        degrees, this->location.x + this->size.width, this->location.y + this->size.height, dir,
                        this->location.x, this->location.y,
                        this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_centroid(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    T x, y;
                    omni::math::midpoint(this->location.x, this->location.y, (this->location.x + this->size.width), (this->location.y + this->size.height), x, y);
                    omni::math::rectangle_rotate_point(degrees, x, y, dir, this->location.x, this->location.y, this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_circumcenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    return this->rotate_centroid(degrees, dir);
                }

                omni::geometry::raw_rectangle<T>& rotate_incenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    return this->rotate_centroid(degrees, dir);
                }

                omni::geometry::raw_rectangle<T>& rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::rectangle_rotate_origin(degrees, dir, this->location.x, this->location.y, this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir)
                {
                    omni::math::rectangle_rotate_point(degrees, x, y, dir, this->location.x, this->location.y, this->size.width, this->size.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& scale(T x_scale, T y_scale)
                {
                    if (this->size.empty()) { // empty??
                        return *this;
                    }

                    this->location.x *= x_scale;
                    this->location.y *= y_scale; 
                    this->size.width *= x_scale;
                    this->size.height *= y_scale; 
        
                    // If the scale in the X dimension is negative, we need to normalize X and Width
                    if (x_scale < 0)  {
                        // Make X the left-most edge again
                        this->location.x += this->size.width;
                        // and make Width positive
                        this->size.width *= -1;
                    } 
                    // Do the same for the Y dimension 
                    if (y_scale < 0) {
                        // Make Y the top-most edge again
                        this->location.y += this->size.height;
                        // and make Height positive 
                        this->size.height *= -1;
                    }
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& set_location(T x, T y)
                {
                    this->location.x = x;
                    this->location.y = y;
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& set_location(const omni::math::dimensional<T, 2>& point)
                {
                    return this->set_location(point[0], point[1]);
                }

                omni::geometry::raw_rectangle<T>& set_location(const omni::geometry::point2d<T>& point)
                {
                    return this->set_location(point.x(), point.y());
                }

                omni::geometry::raw_rectangle<T>& set_location(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->set_location(point.x, point.y);
                }

                omni::geometry::raw_rectangle<T>& set_size(T w, T h)
                {
                    this->size.width = w;
                    this->size.height = h;
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& set_size(const omni::math::dimensional<T, 2>& sz)
                {
                    return this->set_size(sz[0], sz[1]);
                }

                omni::geometry::raw_rectangle<T>& set_size(const omni::geometry::size<T>& sz)
                {
                    return this->set_size(sz.width(), sz.height());
                }

                omni::geometry::raw_rectangle<T>& set_size(const omni::geometry::raw_size<T>& sz)
                {
                    return this->set_size(sz.width, sz.height);
                }

                void swap(raw_rectangle<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->location, o.location);
                        std::swap(this->size, o.size);
                    }
                }

                T top() const
                {
                    return this->location.y;
                }

                omni::geometry::point2d<T> top_left() const
                {
                    return omni::geometry::point2d<T>(this->location.x, this->location.y);
                }

                omni::geometry::point2d<T> top_right() const
                {
                    return omni::geometry::point2d<T>(this->edge().x, this->location.y);
                }

                omni::geometry::raw_rectangle<T>& translate_xy(T x, T y)
                {
                    omni::math::rectangle_translate_xy(x, y, this->location.x, this->location.y);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& translate_angle(float angle, T distance)
                {
                    omni::math::rectangle_translate_angle(angle, distance, this->location.x, this->location.y);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& union_merge(const omni::geometry::rectangle<T>& r2)
                {
                    omni::geometry::raw_point2d<T> loc(r2.location());
                    omni::geometry::raw_size<T> sz(r2.size());
                    this->_union_merge(loc.x, loc.y, sz.width, sz.height, r2.edge());
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& union_merge(const omni::geometry::raw_rectangle<T>& r2)
                {
                    if (this == &r2) { return *this; }
                    this->_union_merge(r2.location.x, r2.location.y, r2.size.width, r2.size.height, r2.edge());
                    return *this;
                }

                T width() const
                {
                    return this->size.width;
                }

                T x() const
                {
                    return this->location.x;
                }

                T y() const
                {
                    return this->location.y;
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->location.to_string_t() << "," << this->size.to_string_t() << "}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::string ret = "{";
                    ret.append(this->location.to_string());
                    ret.append(",");
                    ret.append(this->size.to_string());
                    ret.append("}");
                    return ret;
                }

                std::wstring to_wstring() const
                {
                    std::wstring ret = L"{";
                    ret.append(this->location.to_wstring());
                    ret.append(L",");
                    ret.append(this->size.to_wstring());
                    ret.append(L"}");
                    return ret;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                bool operator!=(const omni::geometry::raw_rectangle<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::raw_rectangle<T>& operator=(const omni::geometry::raw_rectangle<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->location.x = val.location.x;
                        this->location.y = val.location.y;
                        this->size.width = val.size.width;
                        this->size.height = val.size.height;
                    }
                    return *this;
                }

                bool operator==(const omni::geometry::raw_rectangle<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->location.x, val.location.x) &&
                        omni::math::are_equal<T>(this->location.y, val.location.y) &&
                        omni::math::are_equal<T>(this->size.width, val.size.width) &&
                        omni::math::are_equal<T>(this->size.height, val.size.height))
                    OMNI_EQUAL_FW(val);
                }

                bool operator==(const omni::geometry::point2d<T>& val) const
                {
                    return (
                        omni::math::are_equal<T>(this->location.x, val.x()) &&
                        omni::math::are_equal<T>(this->location.y, val.y()));
                }

                bool operator==(const omni::geometry::raw_point2d<T>& val) const
                {
                    return (
                        omni::math::are_equal<T>(this->location.x, val.x) &&
                        omni::math::are_equal<T>(this->location.y, val.y));
                }

                bool operator==(const omni::geometry::size<T>& val) const
                {
                    return (
                        omni::math::are_equal<T>(this->size.width, val.width()) &&
                        omni::math::are_equal<T>(this->size.height, val.height()));
                }

                bool operator==(const omni::geometry::raw_size<T>& val) const
                {
                    return (
                        omni::math::are_equal<T>(this->size.width, val.width) &&
                        omni::math::are_equal<T>(this->size.height, val.height));
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x < val.x() && this->location.y < val.y();
                }

                bool operator<(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x < val.x && this->location.y < val.y;
                }

                bool operator<(const omni::geometry::size<T>& val) const
                {
                    return this->size.width < val.width() && this->size.height < val.height();
                }

                bool operator<(const omni::geometry::raw_size<T>& val) const
                {
                    return this->size.width < val.width && this->size.height < val.height;
                }

                bool operator<=(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x <= val.x() && this->location.y <= val.y();
                }

                bool operator<=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x <= val.x && this->location.y <= val.y;
                }

                bool operator<=(const omni::geometry::size<T>& val) const
                {
                    return this->size.width <= val.width() && this->size.height <= val.height();
                }

                bool operator<=(const omni::geometry::raw_size<T>& val) const
                {
                    return this->size.width <= val.width && this->size.height <= val.height;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x > val.x() && this->location.y > val.y();
                }

                bool operator>(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x > val.x && this->location.y > val.y;
                }

                bool operator>(const omni::geometry::size<T>& val) const
                {
                    return this->size.width > val.width() && this->size.height > val.height();
                }

                bool operator>(const omni::geometry::raw_size<T>& val) const
                {
                    return this->size.width > val.width && this->size.height > val.height;
                }

                bool operator>=(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x >= val.x() && this->location.y >= val.y();
                }

                bool operator>=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x >= val.x && this->location.y >= val.y;
                }

                bool operator>=(const omni::geometry::size<T>& val) const
                {
                    return this->size.width >= val.width() && this->size.height >= val.height();
                }

                bool operator>=(const omni::geometry::raw_size<T>& val) const
                {
                    return this->size.width >= val.width && this->size.height >= val.height;
                }

                omni::geometry::raw_rectangle<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>((this->location.x + val.x()),
                                        (this->location.y + val.y()),
                                        this->size.width,
                                        this->size.height);
                }

                omni::geometry::raw_rectangle<T> operator+(const omni::geometry::raw_point2d<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>((this->location.x + val.x),
                                        (this->location.y + val.y),
                                        this->size.width,
                                        this->size.height);
                }

                omni::geometry::raw_rectangle<T> operator+(const omni::geometry::size<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width + val.width()),
                                        (this->size.height + val.height()));
                }

                omni::geometry::raw_rectangle<T> operator+(const omni::geometry::raw_size<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width + val.width),
                                        (this->size.height + val.height));
                }

                omni::geometry::raw_rectangle<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>((this->location.x - val.x()),
                                        (this->location.y - val.y()),
                                        this->size.width,
                                        this->size.height);
                }

                omni::geometry::raw_rectangle<T> operator-(const omni::geometry::raw_point2d<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>((this->location.x - val.x),
                                        (this->location.y - val.y),
                                        this->size.width,
                                        this->size.height);
                }

                omni::geometry::raw_rectangle<T> operator-(const omni::geometry::size<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width - val.width()),
                                        (this->size.height - val.height()));
                }

                omni::geometry::raw_rectangle<T> operator-(const omni::geometry::raw_size<T>& val)
                {
                    return omni::geometry::raw_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width - val.width),
                                        (this->size.height - val.height));
                }

                omni::geometry::raw_rectangle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator+=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->inflate(val.width(), val.height());
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator+=(const omni::geometry::raw_size<T>& val)
                {
                    this->inflate(val.width, val.height);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator-=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->deflate(val.width(), val.height());
                    return *this;
                }

                omni::geometry::raw_rectangle<T>& operator-=(const omni::geometry::raw_size<T>& val)
                {
                    this->deflate(val.width, val.height);
                    return *this;
                }

                static omni::geometry::raw_rectangle<T> from_ltrb(T left, T top, T right, T bottom)
                {
                    return omni::geometry::raw_rectangle<T>(left,
                                            top,
                                            (right - left), // width
                                            (bottom - top)); // height
                }

                static omni::geometry::raw_rectangle<T> deflate(const omni::geometry::raw_rectangle<T>& rect, T w, T h)
                {
                    return omni::geometry::raw_rectangle<T>(rect, w, h, 'd');
                }

                static omni::geometry::raw_rectangle<T> inflate(const omni::geometry::raw_rectangle<T>& rect, T w, T h)
                {
                    return omni::geometry::raw_rectangle<T>(rect, w, h, 'i');
                }

                static omni::geometry::raw_rectangle<T> intersect(const omni::geometry::raw_rectangle<T>& a, const omni::geometry::raw_rectangle<T>& b)
                {
                    return omni::geometry::raw_rectangle<T>(a, b, true);
                }

                static omni::geometry::raw_rectangle<T> scale(const omni::geometry::raw_rectangle<T>& rect, T w, T h)
                {
                    return omni::geometry::raw_rectangle<T>(rect, w, h, 's');
                }

                static omni::geometry::raw_rectangle<T> union_merge(const omni::geometry::raw_rectangle<T>& a, const omni::geometry::raw_rectangle<T>& b)
                {
                    return omni::geometry::raw_rectangle<T>(a, b, false);
                }

                OMNI_MEMBERS_FW(omni::geometry::raw_rectangle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::raw_rectangle<T>)

                omni::geometry::raw_point2d<T> location;
                
                omni::geometry::raw_size<T> size;

            private:
                raw_rectangle(const omni::geometry::raw_rectangle<T>& a, const omni::geometry::raw_rectangle<T>& b, bool isect) :
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(a.location), size(a.size)
                {
                    if (isect) {
                        this->intersect(b);
                    } else {
                        this->union_merge(b);
                    }
                }

                raw_rectangle(const omni::geometry::raw_rectangle<T>& a, T w, T h, char type) :
                    OMNI_CTOR_FW(omni::geometry::raw_rectangle<T>)
                    location(a.location), size(a.size)
                {
                    switch (type) {
                        case 'd': this->deflate(w, h); break;
                        case 'i': this->inflate(w, h); break;
                        case 's': this->scale(w, h); break;
                    }
                }

                void _intersect(T x, T y, const omni::geometry::raw_point2d<T>& r2edge)
                {
                    if (this->intersects_with(x, y, r2edge.x, r2edge.y)) {
                        omni::geometry::raw_point2d<T> edg = this->edge();
                        this->location.x = std::max(this->location.x, x);
                        this->location.y = std::max(this->location.y, y);
                        this->size.width = std::max(std::min(edg.x, r2edge.x) - this->location.x, 0);
                        this->size.height = std::max(std::min(edg.y, r2edge.y) - this->location.y, 0);
                    } else {
                        this->location.x = 0;
                        this->location.y = 0;
                        this->size.width = 0;
                        this->size.height = 0;
                    }
                }

                void _union_merge(T r2x, T r2y, T r2w, T r2h, const omni::geometry::raw_point2d<T>& r2edge)
                {
                    if (this->size.empty()) {
                        this->location.x = r2x;
                        this->location.y = r2y;
                        this->size.width = r2w;
                        this->size.height = r2h;
                    } else if ((r2w > 0) && (r2h > 0)) {
                        omni::geometry::raw_point2d<T> edg = this->edge();
                        this->location.x = std::min(this->location.x, r2x);
                        this->location.y = std::min(this->location.y, r2y);
                        this->size.width = std::max(std::max(edg.x, r2edge.x) - this->location.x, 0);
                        this->size.height = std::max(std::max(edg.y, r2edge.y) - this->location.y, 0);
                    }
                    // else there's no union 
                }
        };

        typedef omni::geometry::raw_rectangle<int32_t> raw_rectangle_t;
        typedef omni::geometry::raw_rectangle<int64_t> raw_rectangle64_t;
        typedef omni::geometry::raw_rectangle<float> raw_rectangleF_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::rectangle<T>& o1, omni::geometry::rectangle<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::raw_rectangle<T>& o1, omni::geometry::raw_rectangle<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_RECTANGLE_HPP
