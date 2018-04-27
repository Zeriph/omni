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
#if !defined(OMNI_2D_POINT_HPP)
#define OMNI_2D_POINT_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/size.hpp>
#include <omni/defs/point_def.hpp>

namespace omni {
    namespace geometry {
        template < typename T >
        class point2d
        {
            public:
                point2d() : 
                    OMNI_CTOR_FW(omni::geometry::point2d<T>)
                    m_x(0), m_y(0)
                    OMNI_SAFE_P2DMTX_FW
                { }

                point2d(const omni::geometry::point2d<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_x(cp.x()), m_y(cp.y())
                    OMNI_SAFE_P2DMTX_FW
                { }

                point2d(T x, T y) : 
                    OMNI_CTOR_FW(omni::geometry::point2d<T>)
                    m_x(x), m_y(y)
                    OMNI_SAFE_P2DMTX_FW
                { }

                ~point2d()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T x() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return this->m_x;
                }

                T y() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return this->m_y;
                }

                bool empty() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return this->m_x == 0 && this->m_y == 0;
                }

                bool equals(T x, T y) const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return this->m_x == x && this->m_y == y;
                }

                void set(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x = x;
                    this->m_y = y;
                }

                T decrement_x()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return --this->m_x;
                }

                T decrement_y()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return --this->m_y;
                }

                T decrement_x(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return (this->m_x -= val);
                }

                T decrement_y(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return (this->m_y -= val);
                }
                
                T increment_x()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return ++this->m_x;
                }

                T increment_y()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return ++this->m_y;
                }

                T increment_x(T val) 
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return (this->m_x += val);
                }

                T increment_y(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return (this->m_y += val);
                }

                void decrement(const point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                }

                void decrement(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                }

                void decrement(const omni::geometry::size_raw<T>& val)
                {
                    this->decrement(val.width, val.height);
                }

                void decrement(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x -= x;
                    this->m_y -= y;
                }

                void offset(const point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                }

                void offset(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                }

                void offset(const omni::geometry::size_raw<T>& val)
                {
                    this->offset(val.width, val.height);
                }

                void offset(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x += x;
                    this->m_y += y;
                }

                const omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_P2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_P2UNLOCK_FW
                    return s.str();
                }

                const std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_P2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_P2UNLOCK_FW
                    return s.str();
                }

                const std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_P2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_P2UNLOCK_FW
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
                
                omni::geometry::size<T> to_size() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return omni::geometry::size<T>(this->m_x, this->m_y);
                }

                omni::geometry::size_raw<T> to_size_raw() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return omni::geometry::size_raw<T>(this->m_x, this->m_y);
                }

                bool operator!=(const point2d<T>& val) const
                {
                    return !(*this == val);
                }
                
                point2d<T>& operator=(const point2d<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_P2ALOCK_FW
                        OMNI_SAFE_P2OALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_x = val.m_x;
                        this->m_y = val.m_y;
                    }
                    return *this;
                }

                bool operator<(const point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x < val.m_x) && (this->m_y < val.m_y);
                }

                bool operator<=(const point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x <= val.m_x) && (this->m_y <= val.m_y);
                }

                bool operator>(const point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x > val.m_x) && (this->m_y > val.m_y);
                }

                bool operator>=(const point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x >= val.m_x) && (this->m_y >= val.m_y);
                }

                bool operator==(const point2d<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return ((this->m_x == val.m_x) && (this->m_y == val.m_y))
                    OMNI_EQUAL_FW(val);
                }

                point2d<T> operator+(const point2d<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return point2d<T>((this->m_x + val.m_x), (this->m_y + val.m_y));
                }

                point2d<T> operator+(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return point2d<T>((this->m_x + val.width()), (this->m_y + val.height()));
                }

                point2d<T> operator+(const omni::geometry::size_raw<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return point2d<T>((this->m_x + val.width), (this->m_y + val.height));
                }

                point2d<T> operator-(const point2d<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return point2d<T>((this->m_x - val.m_x), (this->m_y - val.m_y));
                }

                point2d<T> operator-(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return point2d<T>((this->m_x - val.width()), (this->m_y - val.height()));
                }

                point2d<T> operator-(const omni::geometry::size_raw<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return point2d<T>((this->m_x - val.width), (this->m_y - val.height));
                }

                point2d<T>& operator+=(const point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                point2d<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                    return *this;
                }

                point2d<T>& operator+=(const omni::geometry::size_raw<T>& val)
                {
                    this->offset(val.width, val.height);
                    return *this;
                }

                point2d<T>& operator-=(const point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                point2d<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                    return *this;
                }

                point2d<T>& operator-=(const omni::geometry::size_raw<T>& val)
                {
                    this->decrement(val.width, val.height);
                    return *this;
                }

                operator omni::geometry::size<T>() const
                {
                    return this->to_size();
                }

                operator omni::geometry::size_raw<T>() const
                {
                    return this->to_size_raw();
                }

                static point2d<T> add(const point2d<T>& point, const omni::geometry::size<T> sz)
                {
                    return point2d<T>(point.x() + sz.width(), point.y() + sz.height());
                }

                static point2d<T> add(const point2d<T>& point, const omni::geometry::size_raw<T> sz)
                {
                    return point2d<T>(point.x() + sz.width, point.y() + sz.height);
                }

                static point2d<T> subtract(const point2d<T>& point, const omni::geometry::size<T> sz)
                {
                    return point2d<T>(point.x() - sz.width(), point.y() - sz.height());
                }

                static point2d<T> subtract(const point2d<T>& point, const omni::geometry::size_raw<T> sz)
                {
                    return point2d<T>(point.x() - sz.width, point.y() - sz.height);
                }

                OMNI_MEMBERS_FW(omni::geometry::point2d<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::point2d<T>)

            private:
                T m_x;
                T m_y;
                #if defined(OMNI_SAFE_POINT2D)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
        };

        typedef omni::geometry::point2d<int32_t> point_t;
        typedef omni::geometry::point2d<int64_t> point64_t;
        typedef omni::geometry::point2d<float> pointF_t;

        template < typename T >
        class point2d_raw
        {
            public:
                point2d_raw() : 
                    OMNI_CTOR_FW(omni::geometry::point2d<T>)
                    x(0), y(0)
                { }

                point2d_raw(const omni::geometry::point2d<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    x(cp.x), y(cp.y)
                { }

                point2d_raw(T _x, T _y) : 
                    OMNI_CTOR_FW(omni::geometry::point2d<T>)
                    x(_x), y(_y)
                { }

                ~point2d_raw()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T x;

                T y;

                bool empty() const
                {
                    return this->x == 0 && this->y == 0;
                }

                bool equals(T _x, T _y) const
                {
                    return this->x == _x && this->y == _y;
                }

                void set(T x, T y)
                {
                    this->x = x;
                    this->y = y;
                }

                void decrement(const point2d_raw<T>& val)
                {
                    this->decrement(val.x, val.y);
                }

                void decrement(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                }

                void decrement(const omni::geometry::size_raw<T>& val)
                {
                    this->decrement(val.width, val.height);
                }

                void decrement(T x, T y)
                {
                    this->x -= x;
                    this->y -= y;
                }

                void offset(const point2d_raw<T>& val)
                {
                    this->offset(val.x, val.y);
                }

                void offset(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                }

                void offset(const omni::geometry::size_raw<T>& val)
                {
                    this->offset(val.width, val.height);
                }

                void offset(T x, T y)
                {
                    this->x += x;
                    this->y += y;
                }

                const omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->x << "," << this->y << "}";
                    return s.str();
                }

                const std::string to_string() const
                {
                    std::stringstream s;
                    s << "{" << this->x << "," << this->y << "}";
                    return s.str();
                }

                const std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    s << "{" << this->x << "," << this->y << "}";
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
                
                omni::geometry::size<T> to_size() const
                {
                    return omni::geometry::size<T>(this->x, this->y);
                }

                omni::geometry::size_raw<T> to_size_raw() const
                {
                    return omni::geometry::size_raw<T>(this->x, this->y);
                }

                bool operator!=(const point2d_raw<T>& val) const
                {
                    return !(*this == val);
                }
                
                point2d_raw<T>& operator=(const point2d_raw<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->x = val.x;
                        this->y = val.y;
                    }
                    return *this;
                }

                bool operator<(const point2d_raw<T>& val) const
                {
                    return (this->x < val.x) && (this->y < val.y);
                }

                bool operator<=(const point2d_raw<T>& val) const
                {
                    return (this->x <= val.x) && (this->y <= val.y);
                }

                bool operator>(const point2d_raw<T>& val) const
                {
                    return (this->x > val.x) && (this->y > val.y);
                }

                bool operator>=(const point2d_raw<T>& val) const
                {
                    return (this->x >= val.x) && (this->y >= val.y);
                }

                bool operator==(const point2d_raw<T>& val) const
                {
                    if (this == &val) { return true; }
                    return ((this->x == val.x) && (this->y == val.y))
                    OMNI_EQUAL_FW(val);
                }

                point2d_raw<T> operator+(const point2d_raw<T>& val)
                {
                    return point2d_raw<T>((this->x + val.x), (this->y + val.y));
                }

                point2d_raw<T> operator+(const omni::geometry::size<T>& val)
                {
                    return point2d_raw<T>((this->x + val.width()), (this->y + val.height()));
                }

                point2d_raw<T> operator+(const omni::geometry::size_raw<T>& val)
                {
                    return point2d_raw<T>((this->x + val.width), (this->y + val.height));
                }

                point2d_raw<T> operator-(const point2d_raw<T>& val)
                {
                    return point2d_raw<T>((this->x - val.x), (this->y - val.y));
                }

                point2d_raw<T> operator-(const omni::geometry::size<T>& val)
                {
                    return point2d_raw<T>((this->x - val.width()), (this->y - val.height()));
                }

                point2d_raw<T> operator-(const omni::geometry::size_raw<T>& val)
                {
                    return point2d_raw<T>((this->x - val.width), (this->y - val.height));
                }

                point2d_raw<T>& operator+=(const point2d_raw<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                point2d_raw<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                    return *this;
                }

                point2d_raw<T>& operator+=(const omni::geometry::size_raw<T>& val)
                {
                    this->offset(val.width, val.height);
                    return *this;
                }

                point2d_raw<T>& operator-=(const point2d_raw<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                point2d_raw<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                    return *this;
                }

                point2d_raw<T>& operator-=(const omni::geometry::size_raw<T>& val)
                {
                    this->decrement(val.width, val.height);
                    return *this;
                }

                operator omni::geometry::size<T>() const
                {
                    return this->to_size();
                }

                operator omni::geometry::size_raw<T>() const
                {
                    return this->to_size_raw();
                }

                static point2d_raw<T> add(const point2d_raw<T>& point, const omni::geometry::size<T> sz)
                {
                    return point2d_raw<T>(point.x + sz.width(), point.y + sz.height());
                }

                static point2d_raw<T> add(const point2d_raw<T>& point, const omni::geometry::size_raw<T> sz)
                {
                    return point2d_raw<T>(point.x + sz.width, point.y + sz.height);
                }

                static point2d_raw<T> subtract(const point2d_raw<T>& point, const omni::geometry::size<T> sz)
                {
                    return point2d_raw<T>(point.x - sz.width(), point.y - sz.height());
                }

                static point2d_raw<T> subtract(const point2d_raw<T>& point, const omni::geometry::size_raw<T> sz)
                {
                    return point2d_raw<T>(point.x - sz.width, point.y - sz.height);
                }

                OMNI_MEMBERS_FW(omni::geometry::point2d_raw<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::point2d_raw<T>)
        };

        typedef omni::geometry::point2d_raw<int32_t> raw_point_t;
        typedef omni::geometry::point2d_raw<int64_t> raw_point64_t;
        typedef omni::geometry::point2d_raw<float> raw_pointF_t;
    }
}

#endif // OMNI_2D_POINT_HPP
