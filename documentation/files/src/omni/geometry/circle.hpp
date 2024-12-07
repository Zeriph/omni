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
#if !defined(OMNI_CIRCLE_HPP)
#define OMNI_CIRCLE_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/point2d.hpp>
#include <omni/geometry/path.hpp>

#if defined(OMNI_SAFE_CIRCLE)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_CIRCMTX_FW  ,m_mtx()
    #define OMNI_SAFE_CIRCLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_CIRCUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_CIRCALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_CIRCOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_CIRCMTX_FW
    #define OMNI_SAFE_CIRCLOCK_FW
    #define OMNI_SAFE_CIRCUNLOCK_FW
    #define OMNI_SAFE_CIRCALOCK_FW
    #define OMNI_SAFE_CIRCOALOCK_FW(o) 
#endif

#if defined(OMNI_CIRCLE_IS_CHAINABLE)
#else
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class circle
        {
            public:
                typedef T coordinate_t;
                typedef omni_sequence_t< omni::geometry::point2d< T > > path_t;

                circle() : 
                    OMNI_CTOR_FW(omni::geometry::circle<T>)
                    m_loc(), m_rad()
                    OMNI_SAFE_CIRCMTX_FW
                { }

                circle(const omni::geometry::circle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_loc(cp.location()), m_rad(cp.radius())
                    OMNI_SAFE_CIRCMTX_FW
                { }

                OMNI_EXPLICIT circle(double r) : 
                    OMNI_CTOR_FW(omni::geometry::circle<T>)
                    m_loc(), m_rad(r)
                    OMNI_SAFE_CIRCMTX_FW
                { }

                circle(T x, T y) : 
                    OMNI_CTOR_FW(omni::geometry::circle<T>)
                    m_loc(x, y), m_rad(1.0)
                    OMNI_SAFE_CIRCMTX_FW
                { }

                circle(T x, T y, double r) : 
                    OMNI_CTOR_FW(omni::geometry::circle<T>)
                    m_loc(x, y), m_rad(r)
                    OMNI_SAFE_CIRCMTX_FW
                { }

                ~circle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                double area() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return OMNI_PI * (this->m_rad * this->m_rad);
                }

                double bottom() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return static_cast<double>(this->m_loc.y) - this->m_rad;
                }

                double circumference() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return OMNI_PI_X2 * this->m_rad;
                }

                bool contains(T x, T y, bool include_edge) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return OMNI_CIRCLE_CONTAINS_POINT_FW(this->m_loc.x, this->m_loc.y, this->m_rad, x, y, include_edge);
                }

                bool contains(T x, T y) const
                {
                    return this->contains(x, y, true);
                }

                bool contains(const omni::math::dimensional<T, 2>& point, bool include_edge) const
                {
                    return this->contains(point[0], point[1], include_edge);
                }

                bool contains(const omni::math::dimensional<T, 2>& point) const
                {
                    return this->contains(point[0], point[1]);
                }

                bool contains(const omni::geometry::point2d<T>& point, bool include_edge) const
                {
                    return this->contains(point.x(), point.y(), include_edge);
                }

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::raw_point2d<T>& point, bool include_edge) const
                {
                    return this->contains(point.x, point.y, include_edge);
                }

                bool contains(const omni::geometry::raw_point2d<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }

                bool contains(const omni::geometry::circle<T>& circ, bool include_edge) const
                {
                    if (this == &circ) { return true; }
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_SAFE_CIRCOALOCK_FW(circ)
                    if (OMNI_CIRCLE_CONTAINS_POINT_FW(this->m_loc.x, this->m_loc.y, this->m_rad, circ.m_loc.x, circ.m_loc.y, include_edge)) {
                        return (include_edge ?
                            (circ.m_rad <= this->m_rad) :
                            (circ.m_rad < this->m_rad)
                        );
                    }
                    return false;
                }

                bool contains(const omni::geometry::circle<T>& circ) const
                {
                    return this->contains(circ, true);
                }

                omni::geometry::circle<T>& deflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_RETV_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"), *this)
                    }
                    OMNI_SAFE_CIRCALOCK_FW
                    this->m_rad *= (1.0 - (percent / 100.0));
                    return *this;
                }

                omni::geometry::circle<T>& decrement(T x, T y)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, x)
                    this->m_loc.x -= x;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, y)
                    this->m_loc.y -= y;
                    return *this;
                }

                omni::geometry::circle<T>& decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                omni::geometry::circle<T>& decrement(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                omni::geometry::circle<T>& decrement(const omni::math::dimensional<T, 2>& point)
                {
                    return this->decrement(point[0], point[1]);
                }

                T decrement_x()
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, static_cast<T>(1))
                    return --this->m_loc.x;
                }

                T decrement_y()
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, static_cast<T>(1))
                    return --this->m_loc.y;
                }

                T decrement_x(T val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, val)
                    return (this->m_loc.x -= val);
                }

                T decrement_y(T val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, val)
                    return (this->m_loc.y -= val);
                }

                double diameter() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_rad * 2.0;
                }

                bool empty() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.empty() && omni::math::are_equal<T>(this->m_rad, 0);
                }

                bool empty_size() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return omni::math::are_equal<T>(this->m_rad, 0);
                }

                bool equals(T x, T y, double radius) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return
                        omni::math::are_equal<T>(this->m_loc.x, x) &&
                        omni::math::are_equal<T>(this->m_loc.y, y) &&
                        omni::math::are_equal<T>(this->m_rad, radius);
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_loc.x) ^
                        ((static_cast<int32_t>(this->m_loc.y) << 13) | (static_cast<int32_t>(this->m_loc.y) >> 19)) ^
                        ((static_cast<int32_t>(this->m_rad) << 26) | (static_cast<int32_t>(this->m_rad) >>  6))
                    );
                }

                omni::geometry::circle<T>& inflate(double percent)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    this->m_rad *= ((percent + 100.0) / 100.0);
                    return *this;
                }

                omni::geometry::circle<T>& intersect(const omni::geometry::circle<T>& r2)
                {
                    if (this == &r2) { return *this; }
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_SAFE_CIRCOALOCK_FW(r2)
                    if (this->_intersects_with(r2.m_loc.x, r2.m_loc.y, r2.m_rad, true)) {
                        this->m_loc.x = std::max(this->m_loc.x, r2.m_loc.x);
                        this->m_loc.y = std::max(this->m_loc.y, r2.m_loc.y);
                        this->m_rad = std::max((std::min(this->m_rad, r2.m_rad) - static_cast<double>(this->m_loc.x)), 0.0);
                    } else {
                        this->m_loc.x = 0;
                        this->m_loc.y = 0;
                        this->m_rad = 0;
                    }
                    return *this;
                }

                bool intersects_with(T center_x, T center_y, double radius, bool include_edge) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->_intersects_with(center_x, center_y, radius, include_edge);
                }

                bool intersects_with(T center_x, T center_y, double radius) const
                {
                    return this->intersects_with(center_x, center_y, radius, true);
                }

                bool intersects_with(const omni::geometry::point2d<T>& point, double radius, bool include_edge) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, radius, include_edge);
                }

                bool intersects_with(const omni::geometry::point2d<T>& point, double radius) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, radius);
                }

                bool intersects_with(const omni::geometry::circle<T>& circ, bool include_edge) const
                {
                    if (this == &circ) { return true; }
                    return this->intersects_with(circ.x(), circ.y(), circ.radius(), include_edge);
                }

                bool intersects_with(const omni::geometry::circle<T>& circ) const
                {
                    if (this == &circ) { return true; }
                    return this->intersects_with(circ.x(), circ.y(), circ.radius());
                }
                
                T increment_x()
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, static_cast<T>(1))
                    return ++this->m_loc.x;
                }

                T increment_y()
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, static_cast<T>(1))
                    return ++this->m_loc.y;
                }

                T increment_x(T val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, val)
                    return (this->m_loc.x += val);
                }

                T increment_y(T val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, val)
                    return (this->m_loc.y += val);
                }

                omni::geometry::raw_point2d<T> location() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc;
                }

                double left() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return static_cast<double>(this->m_loc.x) - this->m_rad;
                }

                omni::geometry::circle<T>& offset(T x, T y)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, x)
                    this->m_loc.x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, y)
                    this->m_loc.y += y;
                    return *this;
                }

                omni::geometry::circle<T>& offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                omni::geometry::circle<T>& offset(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                omni::geometry::circle<T>& offset(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->offset(coord[0], coord[1]);
                }

                path_t path() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return omni::geometry::path::circle<T>(this->m_loc.x, this->m_loc.y, this->m_rad);
                }

                double radius() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_rad;
                }

                double right() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return static_cast<double>(this->m_loc.x) + this->m_rad;
                }

                omni::geometry::circle<T>& set_location(T x, T y)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    this->m_loc.x = x;
                    this->m_loc.y = y;
                    return *this;
                }

                omni::geometry::circle<T>& set_location(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->set_location(coord[0], coord[1]);
                }

                omni::geometry::circle<T>& set_location(const omni::geometry::point2d<T>& point)
                {
                    return this->set_location(point.x(), point.y());
                }

                omni::geometry::circle<T>& set_location(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->set_location(point.x, point.y);
                }

                omni::geometry::circle<T>& set_circumference(double circumference)
                {
                    // Circumference = 2 × π × Radius
                    // Radius = Circumference / π / 2
                    this->set_radius((circumference / OMNI_PI) / 2.0);
                    return *this;
                }

                omni::geometry::circle<T>& set_diameter(double diameter)
                {
                    // Diameter = 2 × Radius
                    // Radius = Diameter / 2
                    return this->set_radius(diameter / 2.0);
                }

                omni::geometry::circle<T>& set_radius(double radius)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    this->m_rad = radius;
                    return *this;
                }

                void swap(circle<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_CIRCALOCK_FW
                        OMNI_SAFE_CIRCOALOCK_FW(o)
                        std::swap(this->m_loc, o.m_loc);
                        std::swap(this->m_rad, o.m_rad);
                    }
                }

                double top() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return static_cast<double>(this->m_loc.y) + this->m_rad;
                }

                void translate_xy(T x, T y)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, x)
                    this->m_loc.x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, y)
                    this->m_loc.y += y;
                }

                T x() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x;
                }

                T y() const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.y;
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_CIRCALOCK_FW
                    s << "{" << this->m_loc << " R:" << this->m_rad << "}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_CIRCALOCK_FW
                    s << "{" << this->m_loc << " R:" << this->m_rad << "}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_CIRCALOCK_FW
                    s << "{" << this->m_loc << " R:" << this->m_rad << "}";
                    return s.str();
                }

                operator std::string() const
                { 
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }
                
                bool operator!=(const omni::geometry::circle<T>& val) const
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

                bool operator!=(double val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::circle<T>& operator=(const omni::geometry::circle<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_CIRCALOCK_FW
                        OMNI_SAFE_CIRCOALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_loc.x = val.m_loc.x;
                        this->m_loc.y = val.m_loc.y;
                        this->m_rad = val.m_rad;
                    }
                    return *this;
                }

                bool operator==(const omni::geometry::circle<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_CIRCALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.m_loc.x) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.m_loc.y) &&
                        omni::math::are_equal<T>(this->m_rad, val.m_rad))
                    OMNI_EQUAL_FW(val);
                }

                bool operator==(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.x()) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.y()));
                }

                bool operator==(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return (
                        omni::math::are_equal<T>(this->m_loc.x, val.x) &&
                        omni::math::are_equal<T>(this->m_loc.y, val.y));
                }

                bool operator==(double val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return omni::math::are_equal<T>(this->m_rad, val);
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x < val.x() && this->m_loc.y < val.y();
                }

                bool operator<(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x < val.x && this->m_loc.y < val.y;
                }

                bool operator<(double val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_rad < val;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x > val.x() && this->m_loc.y > val.y();
                }

                bool operator>(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x > val.x && this->m_loc.y > val.y;
                }

                bool operator>(double val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_rad > val;
                }

                bool operator<=(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x <= val.x() && this->m_loc.y <= val.y();
                }

                bool operator<=(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x <= val.x && this->m_loc.y <= val.y;
                }

                bool operator<=(double val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_rad <= val;
                }

                bool operator>=(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x >= val.x() && this->m_loc.y >= val.y();
                }

                bool operator>=(const omni::geometry::raw_point2d<T>& val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_loc.x >= val.x && this->m_loc.y >= val.y;
                }

                bool operator>=(double val) const
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return this->m_rad >= val;
                }

                omni::geometry::circle<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, val.x())
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, val.y())
                    return omni::geometry::circle<T>((this->m_loc.x + val.x()),
                                     (this->m_loc.y + val.y()),
                                     this->m_rad);
                }

                omni::geometry::circle<T> operator+(const omni::geometry::raw_point2d<T>& val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.x, val.x)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_loc.y, val.y)
                    return omni::geometry::circle<T>((this->m_loc.x + val.x),
                                      (this->m_loc.y + val.y),
                                      this->m_rad);
                }

                omni::geometry::circle<T> operator+(double val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return omni::geometry::circle<T>(this->m_loc.x,
                                     this->m_loc.y,
                                     (this->m_rad + val));
                }

                omni::geometry::circle<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, val.x())
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, val.y())
                    return omni::geometry::circle<T>((this->m_loc.x - val.x()),
                                     (this->m_loc.y - val.y()),
                                     this->m_rad);
                }

                omni::geometry::circle<T> operator-(const omni::geometry::raw_point2d<T>& val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.x, val.x)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_loc.y, val.y)
                    return omni::geometry::circle<T>((this->m_loc.x - val.x),
                                     (this->m_loc.y - val.y),
                                     this->m_rad);
                }

                omni::geometry::circle<T> operator-(double val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    return omni::geometry::circle<T>(this->m_loc.x,
                                     this->m_loc.y,
                                     (this->m_rad - val));
                }

                omni::geometry::circle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val);
                    return *this;
                }

                omni::geometry::circle<T>& operator+=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->offset(val);
                    return *this;
                }

                omni::geometry::circle<T>& operator+=(double rad)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    this->m_rad += rad;
                    return *this;
                }

                omni::geometry::circle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val);
                    return *this;
                }

                omni::geometry::circle<T>& operator-=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->decrement(val);
                    return *this;
                }

                omni::geometry::circle<T>& operator-=(double val)
                {
                    OMNI_SAFE_CIRCALOCK_FW
                    this->m_rad -= val;
                    return *this;
                }

                static omni::geometry::circle<T> deflate(const omni::geometry::circle<T>& circ, double percent)
                {
                    return omni::geometry::circle<T>(circ, percent, true);
                }

                static omni::geometry::circle<T> inflate(const omni::geometry::circle<T>& circ, double percent)
                {
                    return omni::geometry::circle<T>(circ, percent, false);
                }

                static omni::geometry::circle<T> intersect(const omni::geometry::circle<T>& a, const omni::geometry::circle<T>& b)
                {
                    return omni::geometry::circle<T>(a, b);
                }

                OMNI_MEMBERS_FW(omni::geometry::circle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::circle<T>)

            private:
                omni::geometry::raw_point2d<T> m_loc;
                double m_rad;
                #if defined(OMNI_SAFE_CIRCLE)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                circle(const omni::geometry::circle<T>& a, const omni::geometry::circle<T>& b) :
                    OMNI_CTOR_FW(omni::geometry::circle<T>)
                    m_loc(a.location()), m_rad(a.radius())
                    OMNI_SAFE_CIRCMTX_FW
                {
                    this->intersect(b);
                }

                circle(const omni::geometry::circle<T>& a, double percent, bool deflate) :
                    OMNI_CTOR_FW(omni::geometry::circle<T>)
                    m_loc(a.location()), m_rad(a.radius())
                    OMNI_SAFE_CIRCMTX_FW
                {
                    if (deflate) {
                        this->deflate(percent);
                    } else {
                        this->inflate(percent);
                    }
                }

                bool _intersects_with(T center_x, T center_y, double radius, bool include_edge) const
                {
                    return omni::math::circles_intersect(
                        this->m_loc.x, this->m_loc.y, this->m_rad,
                        center_x, center_y, radius,
                        include_edge
                    );
                }
        };

        typedef omni::geometry::circle<double> circle_t;
        typedef omni::geometry::circle<float> circleF_t;
        typedef omni::geometry::circle<int32_t> circle32_t;
        typedef omni::geometry::circle<int64_t> circle64_t;


        // DEV_NOTE: "raw" classes do not have checks, like arithmetic over/under flow, locks, etc.

        template < typename T >
        class raw_circle
        {
            public:
                typedef T coordinate_t;
                typedef omni_sequence_t< omni::geometry::point2d< T > > path_t;

                raw_circle() : 
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(), radius()
                { }

                raw_circle(const omni::geometry::raw_circle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    location(cp.location), radius(cp.radius)
                { }

                raw_circle(const omni::geometry::circle<T>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(cp.location()), radius(cp.radius())
                { }

                OMNI_EXPLICIT raw_circle(double r) : 
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(), radius(r)
                { }

                raw_circle(T x, T y) : 
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(x, y), radius(1.0)
                { }

                raw_circle(T x, T y, double r) : 
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(x, y), radius(r)
                { }

                ~raw_circle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                double area() const
                {
                    return OMNI_PI * (this->radius * this->radius);
                }

                double bottom() const
                {
                    return static_cast<double>(this->location.y) - this->radius;
                }

                double circumference() const
                {
                    return OMNI_PI_X2 * this->radius;
                }

                bool contains(T x, T y, bool include_edge) const
                {
                    return OMNI_CIRCLE_CONTAINS_POINT_FW(this->location.x, this->location.y, this->radius, x, y, include_edge);
                }

                bool contains(T x, T y) const
                {
                    return this->contains(x, y, true);
                }

                bool contains(const omni::math::dimensional<T, 2>& point, bool include_edge) const
                {
                    return this->contains(point[0], point[1], include_edge);
                }

                bool contains(const omni::math::dimensional<T, 2>& point) const
                {
                    return this->contains(point[0], point[1]);
                }

                bool contains(const omni::geometry::point2d<T>& point, bool include_edge) const
                {
                    return this->contains(point.x(), point.y(), include_edge);
                }

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::raw_point2d<T>& point, bool include_edge) const
                {
                    return this->contains(point.x, point.y, include_edge);
                }

                bool contains(const omni::geometry::raw_point2d<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }

                bool contains(const omni::geometry::raw_circle<T>& circ, bool include_edge) const
                {
                    if (this == &circ) { return true; }
                    if (OMNI_CIRCLE_CONTAINS_POINT_FW(this->location.x, this->location.y, this->radius, circ.location.x, circ.location.y, include_edge)) {
                        return (include_edge ?
                            (circ.radius <= this->radius) :
                            (circ.radius < this->radius)
                        );
                    }
                    return false;
                }

                bool contains(const omni::geometry::raw_circle<T>& circ) const
                {
                    return this->contains(circ, true);
                }

                omni::geometry::raw_circle<T>& deflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_RETV_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"), *this)
                    }
                    this->radius *= (1.0 - (percent / 100.0));
                    return *this;
                }

                omni::geometry::raw_circle<T>& decrement(T x, T y)
                {
                    this->location.x -= x;
                    this->location.y -= y;
                    return *this;
                }

                omni::geometry::raw_circle<T>& decrement(const omni::geometry::point2d<T>& point)
                {
                    return this->decrement(point.x(), point.y());
                }

                omni::geometry::raw_circle<T>& decrement(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->decrement(point.x, point.y);
                }

                omni::geometry::raw_circle<T>& decrement(const omni::math::dimensional<T, 2>& point)
                {
                    return this->decrement(point[0], point[1]);
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

                double diameter() const
                {
                    return this->radius * 2.0;
                }

                bool empty() const
                {
                    return this->location.empty() && omni::math::are_equal<T>(this->radius, 0);
                }

                bool empty_size() const
                {
                    return omni::math::are_equal<T>(this->radius, 0);
                }

                bool equals(T x, T y, double rad) const
                {
                    return
                        omni::math::are_equal<T>(this->location.x, x) &&
                        omni::math::are_equal<T>(this->location.y, y) &&
                        omni::math::are_equal<T>(this->radius, rad);
                }

                int32_t hash_code() const
                {
                    return (
                        static_cast<int32_t>(this->location.x) ^
                        ((static_cast<int32_t>(this->location.y) << 13) | (static_cast<int32_t>(this->location.y) >> 19)) ^
                        ((static_cast<int32_t>(this->radius) << 26) | (static_cast<int32_t>(this->radius) >>  6))
                    );
                }

                omni::geometry::raw_circle<T>& inflate(double percent)
                {
                    this->radius *= (percent / 100.0);
                    return *this;
                }

                omni::geometry::raw_circle<T>& intersect(const omni::geometry::raw_circle<T>& r2)
                {
                    if (this == &r2) { return *this; }
                    omni::geometry::raw_point2d<T> loc2 = r2.location;
                    double rad = r2.radius;
                    if (this->intersects_with(loc2.x, loc2.y, rad, true)) {
                        this->location.x = std::max(this->location.x, loc2.x);
                        this->location.y = std::max(this->location.y, loc2.y);
                        this->radius = std::max(std::min(this->radius, rad) - static_cast<double>(this->location.x), 0.0);
                    } else {
                        this->location.x = 0;
                        this->location.y = 0;
                        this->radius = 0;
                    }
                    return *this;
                }

                bool intersects_with(T center_x, T center_y, double rad, bool include_edge) const
                {
                    return omni::math::circles_intersect(
                        this->location.x, this->location.y, this->radius,
                        center_x, center_y, rad,
                        include_edge
                    );
                }

                bool intersects_with(T center_x, T center_y, double rad) const
                {
                    return this->intersects_with(center_x, center_y, rad, true);
                }

                bool intersects_with(const omni::geometry::point2d<T>& point, double rad, bool include_edge) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, rad, include_edge);
                }

                bool intersects_with(const omni::geometry::point2d<T>& point, double rad) const
                {
                    T x = point.x();
                    T y = point.y();
                    return this->intersects_with(x, y, rad);
                }

                bool intersects_with(const omni::geometry::raw_circle<T>& circ, bool include_edge) const
                {
                    if (this == &circ) { return true; }
                    return this->intersects_with(circ.x(), circ.y(), circ.radius, include_edge);
                }

                bool intersects_with(const omni::geometry::raw_circle<T>& circ) const
                {
                    if (this == &circ) { return true; }
                    return this->intersects_with(circ.x(), circ.y(), circ.radius);
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

                double left() const
                {
                    return static_cast<double>(this->location.x) - this->radius;
                }

                omni::geometry::raw_circle<T>& offset(T x, T y)
                {
                    this->location.x += x;
                    this->location.y += y;
                    return *this;
                }

                omni::geometry::raw_circle<T>& offset(const omni::geometry::point2d<T>& point)
                {
                    return this->offset(point.x(), point.y());
                }

                omni::geometry::raw_circle<T>& offset(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->offset(point.x, point.y);
                }

                omni::geometry::raw_circle<T>& offset(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->offset(coord[0], coord[1]);
                }

                path_t path() const
                {
                    return omni::geometry::path::circle(this->location.x, this->location.y, this->radius);
                }

                double right() const
                {
                    return static_cast<double>(this->location.x) + this->radius;
                }

                omni::geometry::raw_circle<T>& set_location(T x, T y)
                {
                    this->location.x = x;
                    this->location.y = y;
                    return *this;
                }

                omni::geometry::raw_circle<T>& set_location(const omni::math::dimensional<T, 2>& coord)
                {
                    return this->set_location(coord[0], coord[1]);
                }

                omni::geometry::raw_circle<T>& set_location(const omni::geometry::point2d<T>& point)
                {
                    return this->set_location(point.x(), point.y());
                }

                omni::geometry::raw_circle<T>& set_location(const omni::geometry::raw_point2d<T>& point)
                {
                    return this->set_location(point.x, point.y);
                }

                omni::geometry::raw_circle<T>& set_circumference(double circumference)
                {
                    // Circumference = 2 × π × Radius
                    // Radius = Circumference / π / 2
                    return this->set_radius((circumference / OMNI_PI) / 2.0);
                }

                omni::geometry::raw_circle<T>& set_diameter(double diameter)
                {
                    // Diameter = 2 × Radius
                    // Radius = Diameter / 2
                    return this->set_radius(diameter / 2.0);
                }

                omni::geometry::raw_circle<T>& set_radius(double rad)
                {
                    this->radius = rad;
                    return *this;
                }

                void swap(raw_circle<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->location, o.location);
                        std::swap(this->radius, o.radius);
                    }
                }

                double top() const
                {
                    return static_cast<double>(this->location.y) + this->radius;
                }

                omni::geometry::raw_circle<T>& translate_xy(T x, T y)
                {
                    this->location.x += x;
                    this->location.y += y;
                    return *this;
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
                    s << "{" << this->location << " R:" << this->radius << "}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    s << "{" << this->location << " R:" << this->radius << "}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    s << "{" << this->location << " R:" << this->radius << "}";
                    return s.str();
                }

                operator std::string() const
                { 
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }
                
                bool operator!=(const omni::geometry::raw_circle<T>& val) const
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

                bool operator!=(double val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::raw_circle<T>& operator=(const omni::geometry::raw_circle<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->location.x = val.location.x;
                        this->location.y = val.location.y;
                        this->radius = val.radius;
                    }
                    return *this;
                }

                bool operator==(const omni::geometry::raw_circle<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->location.x, val.location.x) &&
                        omni::math::are_equal<T>(this->location.y, val.location.y) &&
                        omni::math::are_equal<T>(this->radius, val.radius))
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

                bool operator==(double val) const
                {
                    return omni::math::are_equal<T>(this->radius, val);
                }

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x < val.x() && this->location.y < val.y();
                }

                bool operator<(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x < val.x && this->location.y < val.y;
                }

                bool operator<(double val) const
                {
                    return this->radius < val;
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x > val.x() && this->location.y > val.y();
                }

                bool operator>(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x > val.x && this->location.y > val.y;
                }

                bool operator>(double val) const
                {
                    return this->radius > val;
                }

                bool operator<=(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x <= val.x() && this->location.y <= val.y();
                }

                bool operator<=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x <= val.x && this->location.y <= val.y;
                }

                bool operator<=(double val) const
                {
                    return this->radius <= val;
                }

                bool operator>=(const omni::geometry::point2d<T>& val) const
                {
                    return this->location.x >= val.x() && this->location.y >= val.y();
                }

                bool operator>=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->location.x >= val.x && this->location.y >= val.y;
                }

                bool operator>=(double val) const
                {
                    return this->radius >= val;
                }

                omni::geometry::raw_circle<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    return omni::geometry::raw_circle<T>((this->location.x + val.x()),
                                     (this->location.y + val.y()),
                                     this->radius);
                }

                omni::geometry::raw_circle<T> operator+(const omni::geometry::raw_point2d<T>& val)
                {
                    return omni::geometry::raw_circle<T>((this->location.x + val.x),
                                      (this->location.y + val.y),
                                      this->radius);
                }

                omni::geometry::raw_circle<T> operator+(double val)
                {
                    return omni::geometry::raw_circle<T>(this->location.x,
                                     this->location.y,
                                     (this->radius + val));
                }

                omni::geometry::raw_circle<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    return omni::geometry::raw_circle<T>((this->location.x - val.x()),
                                     (this->location.y - val.y()),
                                     this->radius);
                }

                omni::geometry::raw_circle<T> operator-(const omni::geometry::raw_point2d<T>& val)
                {
                    return omni::geometry::raw_circle<T>((this->location.x - val.x),
                                     (this->location.y - val.y),
                                     this->radius);
                }

                omni::geometry::raw_circle<T> operator-(double val)
                {
                    return omni::geometry::raw_circle<T>(this->location.x,
                                     this->location.y,
                                     (this->radius - val));
                }

                omni::geometry::raw_circle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val);
                    return *this;
                }

                omni::geometry::raw_circle<T>& operator+=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->offset(val);
                    return *this;
                }

                omni::geometry::raw_circle<T>& operator+=(double rad)
                {
                    this->radius += rad;
                    return *this;
                }

                omni::geometry::raw_circle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val);
                    return *this;
                }

                omni::geometry::raw_circle<T>& operator-=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->decrement(val);
                    return *this;
                }

                omni::geometry::raw_circle<T>& operator-=(double val)
                {
                    this->radius -= val;
                    return *this;
                }

                static omni::geometry::raw_circle<T> deflate(const omni::geometry::raw_circle<T>& circ, double percent)
                {
                    return omni::geometry::raw_circle<T>(circ, percent, true);
                }

                static omni::geometry::raw_circle<T> inflate(const omni::geometry::raw_circle<T>& circ, double percent)
                {
                    return omni::geometry::raw_circle<T>(circ, percent, false);
                }

                static omni::geometry::raw_circle<T> intersect(const omni::geometry::raw_circle<T>& a, const omni::geometry::raw_circle<T>& b)
                {
                    return omni::geometry::raw_circle<T>(a, b);
                }

                OMNI_MEMBERS_FW(omni::geometry::raw_circle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::raw_circle<T>)

                omni::geometry::raw_point2d<T> location;
                
                double radius;

            private:
                raw_circle(const omni::geometry::raw_circle<T>& a, const omni::geometry::raw_circle<T>& b) :
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(a.location), radius(a.radius)
                    OMNI_SAFE_CIRCMTX_FW
                {
                    this->intersect(b);
                }

                raw_circle(const omni::geometry::raw_circle<T>& a, double percent, bool deflate) :
                    OMNI_CTOR_FW(omni::geometry::raw_circle<T>)
                    location(a.location), radius(a.radius)
                    OMNI_SAFE_CIRCMTX_FW
                {
                    if (deflate) {
                        this->deflate(percent);
                    } else {
                        this->inflate(percent);
                    }
                }
        };

        typedef omni::geometry::raw_circle<double> raw_circle_t;
        typedef omni::geometry::raw_circle<float> raw_circleF_t;
        typedef omni::geometry::raw_circle<int32_t> raw_circle32_t;
        typedef omni::geometry::raw_circle<int64_t> raw_circle64_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::circle<T>& o1, omni::geometry::circle<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::raw_circle<T>& o1, omni::geometry::raw_circle<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_CIRCLE_HPP
