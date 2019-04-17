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
        inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, const omni::geometry::point2d<T>& point)
        {
            return OMNI_RECT_XYWH_CONTAINS_FW(x, y, w, h, point.x(), point.y());
        }
        template < typename T >
        inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, const omni::geometry::point2d_raw<T>& point)
        {
            return OMNI_RECT_XYWH_CONTAINS_FW(x, y, w, h, point.x, point.y);
        }

        template < typename T >
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, T x, T y)
        {
            return OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, x, y);
        }
        template < typename T >
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, const omni::geometry::point2d<T>& point)
        {
            return OMNI_RECT_LTRB_CONTAINS_FW(left, top, right, bottom, point.x(), point.y());
        }
        template < typename T >
        inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, const omni::geometry::point2d_raw<T>& point)
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

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::point2d_raw<T>& point) const
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
                
                bool contains(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T left = point.x();
                    T top = point.y();
                    return this->contains(left, top, (left + sz.width()), (top + sz.height()));
                }

                bool contains(const omni::geometry::point2d_raw<T>& point, const omni::geometry::size_raw<T> sz) const
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

                void deflate(const omni::geometry::size_raw<T>& sz)
                {
                    this->deflate(sz.width, sz.height);
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

                void inflate(const omni::geometry::size_raw<T>& sz)
                {
                    this->inflate(sz.width, sz.height);
                }

                void intersect(const rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::point2d_raw<T> loc2 = r2.location();
                    omni::geometry::point2d_raw<T> edge2 = r2.edge();
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

                bool intersects_with(const omni::geometry::point2d_raw<T>& point, const omni::geometry::size_raw<T> sz) const
                {
                    return this->intersects_with(point.x, point.y, (point.x + sz.width), (point.y + sz.height));
                }

                bool intersects_with(const rectangle<T>& rect) const
                {
                    return this->intersects_with(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void merge(const rectangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::point2d_raw<T> loc2 = r2.location();
                    omni::geometry::point2d_raw<T> edge2 = r2.edge();
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

                void decrement(const omni::geometry::point2d_raw<T>& point)
                {
                    return this->decrement(point.x, point.y);
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

                void offset(const omni::geometry::point2d_raw<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                T bottom() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge.y;
                }

                omni::geometry::point2d_raw<T> edge() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_edge;
                }

                T height() const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_size.height;
                }

                omni::geometry::point2d_raw<T> location() const
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

                omni::geometry::size_raw<T> size() const
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

                void set_location(const omni::geometry::point2d<T>& point)
                {
                    this->set_location(point.x(), point.y());
                }

                void set_location(const omni::geometry::point2d_raw<T>& point)
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

                void set_size(const omni::geometry::size<T>& sz)
                {
                    this->set_size(sz.width(), sz.height());
                }

                void set_size(const omni::geometry::size_raw<T>& sz)
                {
                    this->set_size(sz.width, sz.height);
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
                    return this->m_loc.x == x &&
                           this->m_loc.y == y &&
                           this->m_size.width == w &&
                           this->m_size.height == h;
                }

                const omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_RECTLOCK_FW
                    s << "{" << this->m_loc.to_string_t() << "," << this->m_size.to_string_t() << "}";
                    OMNI_SAFE_RECTUNLOCK_FW
                    return s.str();
                }

                const std::string to_string() const
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

                const std::wstring to_wstring() const
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
                    return !(*this == val);
                }
                
                rectangle<T>& operator=(const rectangle<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_RECTALOCK_FW
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
                    return (this->m_loc.x == val.m_loc.x &&
                            this->m_loc.y == val.m_loc.y &&
                            this->m_size.width == val.m_size.width &&
                            this->m_size.height == val.m_size.height)
                    OMNI_EQUAL_FW(val);
                }

                bool operator==(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (this->m_loc.x == val.x() &&
                            this->m_loc.y == val.y());
                }

                bool operator==(const omni::geometry::point2d_raw<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (this->m_loc.x == val.x &&
                            this->m_loc.y == val.y);
                }

                bool operator==(const omni::geometry::size<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (this->m_size.width == val.width() &&
                            this->m_size.height == val.height());
                }

                bool operator==(const omni::geometry::size_raw<T>& val) const
                {
                    OMNI_SAFE_RECTALOCK_FW
                    return (this->m_size.width == val.width &&
                            this->m_size.height == val.height);
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_RECTALOCK_FW
                    return this->m_loc.x < val.x() && this->m_loc.y < val.y();
                }

                bool operator<(const omni::geometry::point2d_raw<T>& val) const
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

                bool operator<(const omni::geometry::size_raw<T>& val) const
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

                bool operator>(const omni::geometry::point2d_raw<T>& val) const
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

                bool operator>(const omni::geometry::size_raw<T>& val) const
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

                rectangle<T> operator+(const omni::geometry::point2d_raw<T>& val)
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

                rectangle<T> operator+(const omni::geometry::size_raw<T>& val)
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

                rectangle<T> operator-(const omni::geometry::point2d_raw<T>& val)
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

                rectangle<T> operator-(const omni::geometry::size_raw<T>& val)
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

                rectangle<T>& operator+=(const omni::geometry::point2d_raw<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                rectangle<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->inflate(val.width(), val.height());
                    return *this;
                }

                rectangle<T>& operator+=(const omni::geometry::size_raw<T>& val)
                {
                    this->inflate(val.width, val.height);
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::point2d_raw<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->deflate(val.width(), val.height());
                    return *this;
                }

                rectangle<T>& operator-=(const omni::geometry::size_raw<T>& val)
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
                omni::geometry::point2d_raw<T> m_loc;
                omni::geometry::point2d_raw<T> m_edge;
                omni::geometry::size_raw<T> m_size;
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
        class rectangle_raw
        {
            public:
                rectangle_raw() : 
                    OMNI_CTOR_FW(omni::geometry::rectangle_raw<T>)
                    location(), size()
                { }

                rectangle_raw(const omni::geometry::rectangle_raw<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    location(cp.location), size(cp.size)
                {
                }

                rectangle_raw(T x, T y, T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::rectangle_raw<T>)
                    location(x, y), size(w, h)
                { }

                ~rectangle_raw()
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

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::point2d_raw<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }
                
                bool contains(T left, T top, T right, T bottom) const
                {
                    return
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, left, top) &&
                        OMNI_RECT_XYWH_CONTAINS_FW(this->location.x, this->location.y, this->size.width, this->size.height, right, bottom);
                }
                
                bool contains(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz) const
                {
                    T left = point.x();
                    T top = point.y();
                    return this->contains(left, top, (left + sz.width()), (top + sz.height()));
                }

                bool contains(const omni::geometry::point2d_raw<T>& point, const omni::geometry::size_raw<T> sz) const
                {
                    T left = point.x;
                    T top = point.y;
                    return this->contains(left, top, (left + sz.width), (top + sz.height));
                }

                bool contains(const rectangle_raw<T>& rect) const
                {
                    return this->contains(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void deflate(T w, T h)
                {
                    this->size.width -= w;
                    this->size.height -= h;
                }

                void deflate(const omni::geometry::size<T>& sz)
                {
                    this->deflate(sz.width(), sz.height());
                }

                void deflate(const omni::geometry::size_raw<T>& sz)
                {
                    this->deflate(sz.width, sz.height);
                }

                void inflate(T w, T h)
                {
                    this->size.width += w;
                    this->size.height += h;
                }

                void inflate(const omni::geometry::size<T>& sz)
                {
                    this->inflate(sz.width(), sz.height());
                }

                void inflate(const omni::geometry::size_raw<T>& sz)
                {
                    this->inflate(sz.width, sz.height);
                }

                void intersect(const rectangle_raw<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::point2d_raw<T> edge = this->edge();
                    omni::geometry::point2d_raw<T> loc2 = r2.location;
                    omni::geometry::point2d_raw<T> edge2 = r2.edge();
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

                bool intersects_with(const omni::geometry::point2d_raw<T>& point, const omni::geometry::size_raw<T> sz) const
                {
                    return this->intersects_with(point.x, point.y, (point.x + sz.width), (point.y + sz.height));
                }

                bool intersects_with(const rectangle_raw<T>& rect) const
                {
                    return this->intersects_with(rect.left(), rect.top(), rect.right(), rect.bottom());
                }

                void merge(const rectangle_raw<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::point2d_raw<T> edge = this->edge();
                    omni::geometry::point2d_raw<T> loc2 = r2.location;
                    omni::geometry::point2d_raw<T> edge2 = r2.edge();
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

                void decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                void decrement(const omni::geometry::point2d_raw<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                void offset(T x, T y)
                {
                    this->location.x += x;
                    this->location.y += y;
                }

                void offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                void offset(const omni::geometry::point2d_raw<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                T bottom() const
                {
                    return this->location.y + this->size.height;
                }

                omni::geometry::point2d_raw<T> edge() const
                {
                    return omni::geometry::point2d_raw<T>((this->location.x + this->size.width), (this->location.y + this->size.height));
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

                void set_location(const omni::geometry::point2d<T>& point)
                {
                    this->set_location(point.x(), point.y());
                }

                void set_location(const omni::geometry::point2d_raw<T>& point)
                {
                    this->set_location(point.x, point.y);
                }

                void set_size(T w, T h)
                {
                    this->size.width = w;
                    this->size.height = h;
                }

                void set_size(const omni::geometry::size<T>& sz)
                {
                    this->set_size(sz.width(), sz.height());
                }

                void set_size(const omni::geometry::size_raw<T>& sz)
                {
                    this->set_size(sz.width, sz.height);
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
                    return this->location.x == _x &&
                           this->location.y == _y &&
                           this->size.width == _w &&
                           this->size.height == _h;
                }

                const omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->location.to_string_t() << "," << this->size.to_string_t() << "}";
                    return s.str();
                }

                const std::string to_string() const
                {
                    std::string ret = "{";
                    ret.append(this->location.to_string());
                    ret.append(",");
                    ret.append(this->size.to_string());
                    ret.append("}");
                    return ret;
                }

                const std::wstring to_wstring() const
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
                
                bool operator!=(const rectangle_raw<T>& val) const
                {
                    return !(*this == val);
                }
                
                rectangle_raw<T>& operator=(const rectangle_raw<T>& val)
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

                bool operator==(const rectangle_raw<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (this->m_loc.x == val.m_loc.x &&
                            this->m_loc.y == val.m_loc.y &&
                            this->size.width == val.size.width &&
                            this->size.height == val.size.height)
                    OMNI_EQUAL_FW(val);
                }

                bool operator==(const omni::geometry::point2d<T>& val) const
                {
                    return (this->location.x == val.x() &&
                            this->location.y == val.y());
                }

                bool operator==(const omni::geometry::point2d_raw<T>& val) const
                {
                    return (this->location.x == val.x &&
                            this->location.y == val.y);
                }

                bool operator==(const omni::geometry::size<T>& val) const
                {
                    return (this->size.width == val.width() &&
                            this->size.height == val.height());
                }

                bool operator==(const omni::geometry::size_raw<T>& val) const
                {
                    return (this->size.width == val.width &&
                            this->size.height == val.height);
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x < val.x() && this->location.y < val.y();
                }

                bool operator<(const omni::geometry::point2d_raw<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x < val.x && this->location.y < val.y;
                }

                bool operator<(const omni::geometry::size<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width < val.width() && this->size.height < val.height();
                }

                bool operator<(const omni::geometry::size_raw<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width < val.width && this->size.height < val.height;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x > val.x() && this->location.y > val.y();
                }

                bool operator>(const omni::geometry::point2d_raw<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->location.x > val.x && this->location.y > val.y;
                }

                bool operator>(const omni::geometry::size<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width > val.width() && this->size.height > val.height();
                }

                bool operator>(const omni::geometry::size_raw<T>& val) const
                {
                    if (this == &val) { return false; }
                    return this->size.width > val.width && this->size.height > val.height;
                }

                rectangle_raw<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    return rectangle_raw<T>((this->location.x + val.x()),
                                        (this->location.y + val.y()),
                                        this->size.width,
                                        this->size.height);
                }

                rectangle_raw<T> operator+(const omni::geometry::point2d_raw<T>& val)
                {
                    return rectangle_raw<T>((this->location.x + val.x),
                                        (this->location.y + val.y),
                                        this->size.width,
                                        this->size.height);
                }

                rectangle_raw<T> operator+(const omni::geometry::size<T>& val)
                {
                    return rectangle_raw<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width + val.width()),
                                        (this->size.height + val.height()));
                }

                rectangle_raw<T> operator+(const omni::geometry::size_raw<T>& val)
                {
                    return rectangle_raw<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width + val.width),
                                        (this->size.height + val.height));
                }

                rectangle_raw<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    return rectangle_raw<T>((this->location.x - val.x()),
                                        (this->location.y - val.y()),
                                        this->size.width,
                                        this->size.height);
                }

                rectangle_raw<T> operator-(const omni::geometry::point2d_raw<T>& val)
                {
                    return rectangle_raw<T>((this->location.x - val.x),
                                        (this->location.y - val.y),
                                        this->size.width,
                                        this->size.height);
                }

                rectangle_raw<T> operator-(const omni::geometry::size<T>& val)
                {
                    return rectangle_raw<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width - val.width()),
                                        (this->size.height - val.height()));
                }

                rectangle_raw<T> operator-(const omni::geometry::size_raw<T>& val)
                {
                    return rectangle_raw<T>(this->location.x,
                                        this->location.y,
                                        (this->size.width - val.width),
                                        (this->size.height - val.height));
                }

                rectangle_raw<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                rectangle_raw<T>& operator+=(const omni::geometry::point2d_raw<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                rectangle_raw<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->inflate(val.width(), val.height());
                    return *this;
                }

                rectangle_raw<T>& operator+=(const omni::geometry::size_raw<T>& val)
                {
                    this->inflate(val.width, val.height);
                    return *this;
                }

                rectangle_raw<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                rectangle_raw<T>& operator-=(const omni::geometry::point2d_raw<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                rectangle_raw<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->deflate(val.width(), val.height());
                    return *this;
                }

                rectangle_raw<T>& operator-=(const omni::geometry::size_raw<T>& val)
                {
                    this->deflate(val.width, val.height);
                    return *this;
                }

                static rectangle_raw<T> fromLTRB(T left, T top, T right, T bottom)
                {
                    return rectangle_raw<T>(left,
                                            top,
                                            (right - left), // width
                                            (bottom - top)); // height
                }

                static rectangle_raw<T> deflate(const rectangle_raw<T>& rect, T w, T h)
                {
                    return rectangle_raw<T>(rect.x(),
                                            rect.y(),
                                            (rect.width() - w),
                                            (rect.height() - h));
                }

                static rectangle_raw<T> inflate(const rectangle_raw<T>& rect, T w, T h)
                {
                    return rectangle_raw<T>(rect.x(),
                                            rect.y(),
                                            (rect.width() + w),
                                            (rect.height() + h));
                }

                static rectangle_raw<T> intersect(const rectangle_raw<T>& a, const rectangle_raw<T>& b)
                {
                    return rectangle_raw<T>(a, b, true);
                }

                static rectangle_raw<T> merge(const rectangle_raw<T>& a, const rectangle_raw<T>& b)
                {
                    return rectangle_raw<T>(a, b, false);
                }

                OMNI_MEMBERS_FW(omni::geometry::rectangle_raw<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::rectangle_raw<T>)

                omni::geometry::point2d_raw<T> location;
                
                omni::geometry::size_raw<T> size;

            private:
                omni::geometry::point2d_raw<T> m_loc;
                omni::geometry::size_raw<T> m_size;

                rectangle_raw(const rectangle_raw<T>& a, const rectangle_raw<T>& b, bool isect) :
                    OMNI_CTOR_FW(omni::geometry::rectangle_raw<T>)
                    location(a.location), size(a.size)
                {
                    if (isect) {
                        this->intersect(b);
                    } else {
                        this->merge(b);
                    }
                }
        };

        typedef omni::geometry::rectangle_raw<int32_t> raw_rectangle_t;
        typedef omni::geometry::rectangle_raw<int64_t> raw_rectangle64_t;
        typedef omni::geometry::rectangle_raw<float> raw_rectangleF_t;
    }
}

#endif // OMNI_RECTANGLE_HPP
