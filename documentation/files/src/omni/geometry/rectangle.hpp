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

#define OMNI_RECT_XYWH_CONTAINS_FW(rx,ry,rw,rh,ox,oy) ((ox >= rx) && (ox <= (rx + rw)) && (oy >= ry) && (oy <= (ry + rh)))
#define OMNI_RECT_LTRB_CONTAINS_FW(left,top,right,bottom,ox,oy) ((ox >= left) && (ox <= right) && (oy >= top) && (oy <= bottom))

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
        inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, const omni::geometry::point2d<T>& point)
        {
            return OMNI_RECT_XYWH_CONTAINS_FW(x, y, w, h, point.x(), point.y());
        }
        template < typename T >
        inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, const omni::geometry::unsafe_point2d<T>& point)
        {
            return OMNI_RECT_XYWH_CONTAINS_FW(x, y, w, h, point.x, point.y);
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
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, const omni::geometry::point2d<T>& point)
        {
            return OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, point.x(), point.y());
        }
        template < typename T >
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, const omni::geometry::unsafe_point2d<T>& point)
        {
            return OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, point.x, point.y);
        }

        template < typename T >
        class rectangle
        {
            public:
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

                rectangle(const omni::math::dimensional<T, 4>& cp) :
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(cp[0], cp[1]), m_edge((cp[0] + cp[2]), (cp[1] + cp[3])), m_size(cp[2], cp[3])
                    OMNI_SAFE_RECTMTX_FW
                { }

                rectangle(T x, T y, T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(x, y), m_edge((x + w), (y + h)), m_size(w, h)
                    OMNI_SAFE_RECTMTX_FW
                { }

                ~rectangle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
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

                bool contains(const omni::geometry::unsafe_point2d<T>& point) const
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

                bool contains(const omni::geometry::unsafe_point2d<T>& point, const omni::geometry::unsafe_size<T> sz) const
                {
                    T left = point.x;
                    T top = point.y;
                    return this->contains(left, top, (left + sz.width), (top + sz.height));
                }

                bool contains(const rectangle<T>& rect) const
                {
                    return this->contains(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void deflate(T w, T h)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_size.width -= w;
                    this->m_size.height -= h;
                    this->m_edge.x -= w;
                    this->m_edge.y -= h;
                }

                void deflate(const omni::geometry::size<T>& sz)
                {
                    this->deflate(sz.width(), sz.height());
                }

                void deflate(const omni::geometry::unsafe_size<T>& sz)
                {
                    this->deflate(sz.width, sz.height);
                }

                void deflate(const omni::math::dimensional<T, 2>& sz) const
                {
                    this->deflate(sz[0], sz[1]);
                }

                void inflate(T w, T h)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_size.width += w;
                    this->m_size.height += h;
                    this->m_edge.x += w;
                    this->m_edge.y += h;
                }

                void inflate(const omni::geometry::size<T>& sz)
                {
                    this->inflate(sz.width(), sz.height());
                }

                void inflate(const omni::geometry::unsafe_size<T>& sz)
                {
                    this->inflate(sz.width, sz.height);
                }

                void inflate(const omni::math::dimensional<T, 2>& sz) const
                {
                    this->inflate(sz[0], sz[1]);
                }

                void intersect(const rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::unsafe_point2d<T> loc2 = r2.location();
                    omni::geometry::unsafe_point2d<T> edge2 = r2.edge();
                    if (this->intersects_with(r2)) {
                        OMNI_SAFE_RECTALOCK_FW
                        if (this->m_loc.x < loc2.x) { this->m_loc.x = loc2.x; }
                        if (this->m_loc.y < loc2.y) { this->m_loc.y = loc2.y; }
                        if (this->m_edge.x > edge2.x) { this->m_edge.x = edge2.x; }
                        if (this->m_edge.y > edge2.y) { this->m_edge.y = edge2.y; }
                        this->m_size.width = this->m_edge.x - this->m_loc.x;
                        this->m_size.height = this->m_edge.y - this->m_loc.y;
                    } else {
                        OMNI_SAFE_RECTALOCK_FW
                        this->m_loc.x = 0;
                        this->m_loc.y = 0;
                        this->m_size.width = 0;
                        this->m_size.height = 0;
                        this->m_edge.x = 0;
                        this->m_edge.y = 0;
                    }
                }

                bool intersects_with(T left, T top, T right, T bottom) const
                {
                    OMNI_SAFE_RECTALOCK_FW
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

                bool intersects_with(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, (x + sz.width()), (y + sz.height()));
                }

                bool intersects_with(const omni::geometry::unsafe_point2d<T>& point, const omni::geometry::unsafe_size<T> sz) const
                {
                    return this->intersects_with(point.x, point.y, (point.x + sz.width), (point.y + sz.height));
                }

                bool intersects_with(const omni::math::dimensional<T, 4>& rect) const
                {
                    return this->intersects_with(rect[0], rect[1], rect[2], rect[3]);
                }

                bool intersects_with(const rectangle<T>& rect) const
                {
                    return this->intersects_with(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void merge(const rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::unsafe_point2d<T> loc2 = r2.location();
                    omni::geometry::unsafe_point2d<T> edge2 = r2.edge();
                    OMNI_SAFE_RECTALOCK_FW
                    if (loc2.x < this->m_loc.x) { this->m_loc.x = loc2.x; }
                    if (loc2.y < this->m_loc.y) { this->m_loc.y = loc2.y; }
                    if (this->m_edge.x < edge2.x) { this->m_edge.x = edge2.x; }
                    if (this->m_edge.y < edge2.y) { this->m_edge.y = edge2.y; }
                    this->m_size.width = this->m_edge.x - this->m_loc.x;
                    this->m_size.height = this->m_edge.y - this->m_loc.y;
                }

                void decrement(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_loc.x -= x;
                    this->m_loc.y -= y;
                    this->m_edge.x -= x;
                    this->m_edge.y -= y;
                }

                void decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                void decrement(const omni::geometry::unsafe_point2d<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                void decrement(const omni::math::dimensional<T, 2>& point)
                {
                    return this->decrement(point[0], point[1]);
                }

                void offset(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_loc.x += x;
                    this->m_loc.y += y;
                    this->m_edge.x += x;
                    this->m_edge.y += y;
                }

                void offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                void offset(const omni::geometry::unsafe_point2d<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                void offset(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->offset(coord[0], coord[1]);
                }

                T bottom() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge.y;
                }

                omni::geometry::unsafe_point2d<T> edge() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge;
                }

                T height() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.height;
                }

                omni::geometry::unsafe_point2d<T> location() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc;
                }

                T left() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x;
                }

                T right() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge.x;
                }

                omni::geometry::unsafe_size<T> size() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size;
                }

                T top() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.y;
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

                void set_location(T x, T y)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_loc.x = x;
                    this->m_loc.y = y;
                    this->_recalc_edge();
                }

                void set_location(const omni::math::dimensional<T, 2>& coord)
                {
                    this->set_location(coord[0], coord[1]);
                }

                void set_location(const omni::geometry::point2d<T>& point)
                {
                    this->set_location(point.x(), point.y());
                }

                void set_location(const omni::geometry::unsafe_point2d<T>& point)
                {
                    this->set_location(point.x, point.y);
                }

                void set_size(T w, T h)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_size.width = w;
                    this->m_size.height = h;
                    this->_recalc_edge();
                }

                void set_size(const omni::math::dimensional<T, 2>& coord)
                {
                    this->set_size(coord[0], coord[1]);
                }

                void set_size(const omni::geometry::size<T>& sz)
                {
                    this->set_size(sz.width(), sz.height());
                }

                void set_size(const omni::geometry::unsafe_size<T>& sz)
                {
                    this->set_size(sz.width, sz.height);
                }

                void swap(rectangle<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_RECTALOCK_FW
                        OMNI_SAFE_RECTOALOCK_FW(o)
                        std::swap(this->m_loc, o.m_loc);
                        std::swap(this->m_size, o.m_size);
                    }
                }
                
                T decrement_x()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    --this->m_edge.x;
                    return --this->m_loc.x;
                }

                T decrement_y()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    --this->m_edge.y;
                    return --this->m_loc.y;
                }

                T decrement_x(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_edge.x -= val;
                    return (this->m_loc.x -= val);
                }

                T decrement_y(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_edge.y -= val;
                    return (this->m_loc.y -= val);
                }
                
                T increment_x()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    ++this->m_edge.x;
                    return ++this->m_loc.x;
                }

                T increment_y()
                {
                    OMNI_SAFE_RECTALOCK_FW
                    ++this->m_edge.y;
                    return ++this->m_loc.y;
                }

                T increment_x(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_edge.x += val;
                    return (this->m_loc.x += val);
                }

                T increment_y(T val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    this->m_edge.y += val;
                    return (this->m_loc.y += val);
                }

                bool empty() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.empty() && this->m_size.empty();
                }

                bool equals(T x, T y, T w, T h)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return
                        omni::math::are_equal<T>(this->m_loc.x, x) &&
                        omni::math::are_equal<T>(this->m_loc.y, y) &&
                        omni::math::are_equal<T>(this->m_size.width, w) &&
                        omni::math::are_equal<T>(this->m_size.height, h);
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
                
                bool operator!=(const rectangle<T>& val) const
                {
                    // TODO: make sure for every operator== there is an operator!=
                    return !(*this == val);
                }
                
                rectangle<T>& operator=(const rectangle<T>& val)
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

                bool operator==(const rectangle<T>& val) const
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

                bool operator==(const omni::geometry::unsafe_point2d<T>& val) const
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

                bool operator==(const omni::geometry::unsafe_size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_size.width, val.width) &&
                        omni::math::are_equal<T>(this->m_size.height, val.height));
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x < val.x() && this->m_loc.y < val.y();
                }

                bool operator<(const omni::geometry::unsafe_point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x < val.x && this->m_loc.y < val.y;
                }

                bool operator<(const omni::geometry::size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width < val.width() && this->m_size.height < val.height();
                }

                bool operator<(const omni::geometry::unsafe_size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width < val.width && this->m_size.height < val.height;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x > val.x() && this->m_loc.y > val.y();
                }

                bool operator>(const omni::geometry::unsafe_point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x > val.x && this->m_loc.y > val.y;
                }

                bool operator>(const omni::geometry::size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width > val.width() && this->m_size.height > val.height();
                }

                bool operator>(const omni::geometry::unsafe_size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.width > val.width && this->m_size.height > val.height;
                }

                rectangle<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>((this->m_loc.x + val.x()),
                                        (this->m_loc.y + val.y()),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                rectangle<T> operator+(const omni::geometry::unsafe_point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>((this->m_loc.x + val.x),
                                        (this->m_loc.y + val.y),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                rectangle<T> operator+(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width + val.width()),
                                        (this->m_size.height + val.height()));
                }

                rectangle<T> operator+(const omni::geometry::unsafe_size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width + val.width),
                                        (this->m_size.height + val.height));
                }

                rectangle<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>((this->m_loc.x - val.x()),
                                        (this->m_loc.y - val.y()),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                rectangle<T> operator-(const omni::geometry::unsafe_point2d<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>((this->m_loc.x - val.x),
                                        (this->m_loc.y - val.y),
                                        this->m_size.width,
                                        this->m_size.height);
                }

                rectangle<T> operator-(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width - val.width()),
                                        (this->m_size.height - val.height()));
                }

                rectangle<T> operator-(const omni::geometry::unsafe_size<T>& val)
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return rectangle<T>(this->m_loc.x,
                                        this->m_loc.y,
                                        (this->m_size.width - val.width),
                                        (this->m_size.height - val.height));
                }

                rectangle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                rectangle<T>& operator+=(const omni::geometry::unsafe_point2d<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                rectangle<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->inflate(val.width(), val.height());
                    return *this;
                }

                rectangle<T>& operator+=(const omni::geometry::unsafe_size<T>& val)
                {
                    this->inflate(val.width, val.height);
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::unsafe_point2d<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->deflate(val.width(), val.height());
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::unsafe_size<T>& val)
                {
                    this->deflate(val.width, val.height);
                    return *this;
                }

                static rectangle<T> fromLTRB(T left, T top, T right, T bottom)
                {
                    return rectangle<T>(left,
                                        top,
                                        (right - left), // width
                                        (bottom - top)); // height
                }

                static rectangle<T> deflate(const rectangle<T>& rect, T w, T h)
                {
                    return rectangle<T>(rect.x(),
                                        rect.y(),
                                        (rect.width() - w),
                                        (rect.height() - h));
                }

                static rectangle<T> inflate(const rectangle<T>& rect, T w, T h)
                {
                    return rectangle<T>(rect.x(),
                                        rect.y(),
                                        (rect.width() + w),
                                        (rect.height() + h));
                }

                static rectangle<T> intersect(const rectangle<T>& a, const rectangle<T>& b)
                {
                    return rectangle<T>(a, b, true);
                }

                static rectangle<T> merge(const rectangle<T>& a, const rectangle<T>& b)
                {
                    return rectangle<T>(a, b, false);
                }

                OMNI_MEMBERS_FW(omni::geometry::rectangle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::rectangle<T>)

            private:
                omni::geometry::unsafe_point2d<T> m_loc;
                omni::geometry::unsafe_point2d<T> m_edge;
                omni::geometry::unsafe_size<T> m_size;
                #if defined(OMNI_SAFE_RECTANGLE)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                rectangle(const rectangle<T>& a, const rectangle<T>& b, bool isect) :
                    OMNI_CTOR_FW(omni::geometry::rectangle<T>)
                    m_loc(a.location()), m_edge(), m_size(a.size())
                    OMNI_SAFE_RECTMTX_FW
                {
                    this->_recalc_edge();
                    if (isect) {
                        this->intersect(b);
                    } else {
                        this->merge(b);
                    }
                }

                void _recalc_edge()
                {
                    this->m_edge.x = this->m_loc.x + this->m_size.width; // right
                    this->m_edge.y = this->m_loc.y + this->m_size.height; // bottom
                }
        };

        typedef omni::geometry::rectangle<int32_t> rectangle_t;
        typedef omni::geometry::rectangle<int64_t> rectangle64_t;
        typedef omni::geometry::rectangle<float> rectangleF_t;

        template < typename T >
        class unsafe_rectangle
        {
            public:
                unsafe_rectangle() : 
                    OMNI_CTOR_FW(omni::geometry::unsafe_rectangle<T>)
                    location(), size()
                { }

                unsafe_rectangle(const omni::geometry::unsafe_rectangle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    location(cp.location), size(cp.size)
                { }

                unsafe_rectangle(const omni::math::dimensional<T, 4>& cp) :
                    OMNI_CTOR_FW(omni::geometry::unsafe_rectangle<T>)
                    location(cp[0], cp[1]), size(cp[2], cp[3])
                { }

                unsafe_rectangle(T x, T y, T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::unsafe_rectangle<T>)
                    location(x, y), size(w, h)
                { }

                ~unsafe_rectangle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
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

                bool contains(const omni::geometry::unsafe_point2d<T>& point) const
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

                bool contains(const omni::geometry::unsafe_point2d<T>& point, const omni::geometry::unsafe_size<T> sz) const
                {
                    T left = point.x;
                    T top = point.y;
                    return this->contains(left, top, (left + sz.width), (top + sz.height));
                }

                bool contains(const unsafe_rectangle<T>& rect) const
                {
                    return this->contains(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void deflate(T w, T h)
                {
                    this->size.width -= w;
                    this->size.height -= h;
                }

                void deflate(const omni::math::dimensional<T, 2>& sz)
                {
                    this->deflate(sz[0], sz[1]);
                }

                void deflate(const omni::geometry::size<T>& sz)
                {
                    this->deflate(sz.width(), sz.height());
                }

                void deflate(const omni::geometry::unsafe_size<T>& sz)
                {
                    this->deflate(sz.width, sz.height);
                }

                void inflate(T w, T h)
                {
                    this->size.width += w;
                    this->size.height += h;
                }

                void inflate(const omni::math::dimensional<T, 2>& sz)
                {
                    this->inflate(sz[0], sz[1]);
                }

                void inflate(const omni::geometry::size<T>& sz)
                {
                    this->inflate(sz.width(), sz.height());
                }

                void inflate(const omni::geometry::unsafe_size<T>& sz)
                {
                    this->inflate(sz.width, sz.height);
                }

                void intersect(const unsafe_rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::unsafe_point2d<T> edge = this->edge();
                    omni::geometry::unsafe_point2d<T> loc2 = r2.location;
                    omni::geometry::unsafe_point2d<T> edge2 = r2.edge();
                    if (this->intersects_with(r2)) {
                        if (this->location.x < loc2.x) { this->location.x = loc2.x; }
                        if (this->location.y < loc2.y) { this->location.y = loc2.y; }
                        if (edge.x > edge2.x) { edge.x = edge2.x; }
                        if (edge.y > edge2.y) { edge.y = edge2.y; }
                        this->size.width = edge.x - this->location.x;
                        this->size.height = edge.y - this->location.y;
                    } else {
                        this->location.x = 0;
                        this->location.y = 0;
                        this->size.width = 0;
                        this->size.height = 0;
                    }
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

                bool intersects_with(const omni::geometry::unsafe_point2d<T>& point, const omni::geometry::unsafe_size<T> sz) const
                {
                    return this->intersects_with(point.x, point.y, (point.x + sz.width), (point.y + sz.height));
                }

                bool intersects_with(const omni::math::dimensional<T, 4>& rect) const
                {
                    return this->intersects_with(rect[0], rect[1], rect[2], rect[3]);
                }

                bool intersects_with(const unsafe_rectangle<T>& rect) const
                {
                    return this->intersects_with(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void merge(const unsafe_rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::unsafe_point2d<T> edge = this->edge();
                    omni::geometry::unsafe_point2d<T> loc2 = r2.location;
                    omni::geometry::unsafe_point2d<T> edge2 = r2.edge();
                    if (loc2.x < this->location.x) { this->location.x = loc2.x; }
                    if (loc2.y < this->location.y) { this->location.y = loc2.y; }
                    if (edge.x < edge2.x) { edge.x = edge2.x; }
                    if (edge.y < edge2.y) { edge.y = edge2.y; }
                    this->size.width = edge.x - this->location.x;
                    this->size.height = edge.y - this->location.y;
                }

                void decrement(T x, T y)
                {
                    this->location.x -= x;
                    this->location.y -= y;
                }

                void decrement(const omni::math::dimensional<T, 2>& point)
                {
                    this->decrement(point[0], point[1]);
                }

                void decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                void decrement(const omni::geometry::unsafe_point2d<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                void offset(T x, T y)
                {
                    this->location.x += x;
                    this->location.y += y;
                }

                void offset(const omni::math::dimensional<T, 2>& point)
                {
                    this->offset(point[0], point[2]);
                }

                void offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                void offset(const omni::geometry::unsafe_point2d<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                T bottom() const
                {
                    return this->location.y + this->size.height;
                }

                omni::geometry::unsafe_point2d<T> edge() const
                {
                    return omni::geometry::unsafe_point2d<T>((this->location.x + this->size.width), (this->location.y + this->size.height));
                }

                T height() const
                {
                    return this->size.height;
                }

                T left() const
                {
                    return this->location.x;
                }

                T right() const
                {
                    return this->location.x + this->size.width;
                }

                T top() const
                {
                    return this->location.y;
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

                void set_location(T x, T y)
                {
                    this->location.x = x;
                    this->location.y = y;
                }

                void set_location(const omni::math::dimensional<T, 2>& point)
                {
                    this->set_location(point[0], point[1]);
                }

                void set_location(const omni::geometry::point2d<T>& point)
                {
                    this->set_location(point.x(), point.y());
                }

                void set_location(const omni::geometry::unsafe_point2d<T>& point)
                {
                    this->set_location(point.x, point.y);
                }

                void set_size(T w, T h)
                {
                    this->size.width = w;
                    this->size.height = h;
                }

                void set_size(const omni::math::dimensional<T, 2>& sz)
                {
                    this->set_size(sz[0], sz[1]);
                }

                void set_size(const omni::geometry::size<T>& sz)
                {
                    this->set_size(sz.width(), sz.height());
                }

                void set_size(const omni::geometry::unsafe_size<T>& sz)
                {
                    this->set_size(sz.width, sz.height);
                }

                void swap(unsafe_rectangle<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->location, o.location);
                        std::swap(this->size, o.size);
                    }
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

                bool empty() const
                {
                    return this->location.empty() && this->size.empty();
                }

                bool equals(T _x, T _y, T _w, T _h)
                {
                    return
                        omni::math::are_equal<T>(this->location.x, _x) &&
                        omni::math::are_equal<T>(this->location.y, _y) &&
                        omni::math::are_equal<T>(this->size.width, _w) &&
                        omni::math::are_equal<T>(this->size.height, _h);
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
                { return this->to_string(); }

                operator std::wstring() const
                { return this->to_wstring(); }
                
                bool operator!=(const unsafe_rectangle<T>& val) const
                {
                    return !(*this == val);
                }
                
                unsafe_rectangle<T>& operator=(const unsafe_rectangle<T>& val)
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

                bool operator==(const unsafe_rectangle<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.m_loc.x) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.m_loc.y) &&
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

                bool operator==(const omni::geometry::unsafe_point2d<T>& val) const
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

                bool operator==(const omni::geometry::unsafe_size<T>& val) const
                {
                    return (
                        omni::math::are_equal<T>(this->size.width, val.width) &&
                        omni::math::are_equal<T>(this->size.height, val.height));
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x < val.x() && this->location.y < val.y();
                }

                bool operator<(const omni::geometry::unsafe_point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x < val.x && this->location.y < val.y;
                }

                bool operator<(const omni::geometry::size<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width < val.width() && this->size.height < val.height();
                }

                bool operator<(const omni::geometry::unsafe_size<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width < val.width && this->size.height < val.height;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x > val.x() && this->location.y > val.y();
                }

                bool operator>(const omni::geometry::unsafe_point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x > val.x && this->location.y > val.y;
                }

                bool operator>(const omni::geometry::size<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width > val.width() && this->size.height > val.height();
                }

                bool operator>(const omni::geometry::unsafe_size<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width > val.width && this->size.height > val.height;
                }

                unsafe_rectangle<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    return unsafe_rectangle<T>((this->location.x + val.x()),
                                        (this->location.y + val.y()),
                                        this->size.width,
                                        this->size.height);
                }

                unsafe_rectangle<T> operator+(const omni::geometry::unsafe_point2d<T>& val)
                {
                    return unsafe_rectangle<T>((this->location.x + val.x),
                                        (this->location.y + val.y),
                                        this->size.width,
                                        this->size.height);
                }

                unsafe_rectangle<T> operator+(const omni::geometry::size<T>& val)
                {
                    return unsafe_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width + val.width()),
                                        (this->size.height + val.height()));
                }

                unsafe_rectangle<T> operator+(const omni::geometry::unsafe_size<T>& val)
                {
                    return unsafe_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width + val.width),
                                        (this->size.height + val.height));
                }

                unsafe_rectangle<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    return unsafe_rectangle<T>((this->location.x - val.x()),
                                        (this->location.y - val.y()),
                                        this->size.width,
                                        this->size.height);
                }

                unsafe_rectangle<T> operator-(const omni::geometry::unsafe_point2d<T>& val)
                {
                    return unsafe_rectangle<T>((this->location.x - val.x),
                                        (this->location.y - val.y),
                                        this->size.width,
                                        this->size.height);
                }

                unsafe_rectangle<T> operator-(const omni::geometry::size<T>& val)
                {
                    return unsafe_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width - val.width()),
                                        (this->size.height - val.height()));
                }

                unsafe_rectangle<T> operator-(const omni::geometry::unsafe_size<T>& val)
                {
                    return unsafe_rectangle<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width - val.width),
                                        (this->size.height - val.height));
                }

                unsafe_rectangle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                unsafe_rectangle<T>& operator+=(const omni::geometry::unsafe_point2d<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                unsafe_rectangle<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->inflate(val.width(), val.height());
                    return *this;
                }

                unsafe_rectangle<T>& operator+=(const omni::geometry::unsafe_size<T>& val)
                {
                    this->inflate(val.width, val.height);
                    return *this;
                }

                unsafe_rectangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                unsafe_rectangle<T>& operator-=(const omni::geometry::unsafe_point2d<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                unsafe_rectangle<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->deflate(val.width(), val.height());
                    return *this;
                }

                unsafe_rectangle<T>& operator-=(const omni::geometry::unsafe_size<T>& val)
                {
                    this->deflate(val.width, val.height);
                    return *this;
                }

                static unsafe_rectangle<T> fromLTRB(T left, T top, T right, T bottom)
                {
                    return unsafe_rectangle<T>(left,
                                            top,
                                            (right - left), // width
                                            (bottom - top)); // height
                }

                static unsafe_rectangle<T> deflate(const unsafe_rectangle<T>& rect, T w, T h)
                {
                    return unsafe_rectangle<T>(rect.x(),
                                            rect.y(),
                                            (rect.width() - w),
                                            (rect.height() - h));
                }

                static unsafe_rectangle<T> inflate(const unsafe_rectangle<T>& rect, T w, T h)
                {
                    return unsafe_rectangle<T>(rect.x(),
                                            rect.y(),
                                            (rect.width() + w),
                                            (rect.height() + h));
                }

                static unsafe_rectangle<T> intersect(const unsafe_rectangle<T>& a, const unsafe_rectangle<T>& b)
                {
                    return unsafe_rectangle<T>(a, b, true);
                }

                static unsafe_rectangle<T> merge(const unsafe_rectangle<T>& a, const unsafe_rectangle<T>& b)
                {
                    return unsafe_rectangle<T>(a, b, false);
                }

                OMNI_MEMBERS_FW(omni::geometry::unsafe_rectangle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::unsafe_rectangle<T>)

                omni::geometry::unsafe_point2d<T> location;
                
                omni::geometry::unsafe_size<T> size;

            private:
                omni::geometry::unsafe_point2d<T> m_loc;
                omni::geometry::unsafe_size<T> m_size;

                unsafe_rectangle(const unsafe_rectangle<T>& a, const unsafe_rectangle<T>& b, bool isect) :
                    OMNI_CTOR_FW(omni::geometry::unsafe_rectangle<T>)
                    location(a.location), size(a.size)
                {
                    if (isect) {
                        this->intersect(b);
                    } else {
                        this->merge(b);
                    }
                }
        };

        typedef omni::geometry::unsafe_rectangle<int32_t> unsafe_rectangle_t;
        typedef omni::geometry::unsafe_rectangle<int64_t> unsafe_rectangle64_t;
        typedef omni::geometry::unsafe_rectangle<float> unsafe_rectangleF_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::rectangle<T>& o1, omni::geometry::rectangle<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::unsafe_rectangle<T>& o1, omni::geometry::unsafe_rectangle<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_RECTANGLE_HPP
