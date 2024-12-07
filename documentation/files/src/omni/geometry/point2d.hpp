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
#include <omni/math.hpp>
#include <omni/geometry/size.hpp>
#if defined(OMNI_ENABLE_CXX)
    #include <atomic>
#endif

#if defined(OMNI_SAFE_POINT2D)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_P2DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_P2LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_P2UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_P2ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_P2OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_P2DMTX_FW
    #define OMNI_SAFE_P2LOCK_FW
    #define OMNI_SAFE_P2UNLOCK_FW
    #define OMNI_SAFE_P2ALOCK_FW
    #define OMNI_SAFE_P2OALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class point2d
        {
            public:
                typedef T coordinate_t;

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

                OMNI_EXPLICIT point2d(const omni::math::dimensional<T, 2>& cp) :
                    OMNI_CTOR_FW(omni::geometry::point2d<T>)
                    m_x(cp[0]), m_y(cp[1])
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

                T decrement_x()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, 1)
                    return --this->m_x;
                }

                T decrement_y()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, 1)
                    return --this->m_y;
                }

                T decrement_x(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val)
                    return (this->m_x -= val);
                }

                T decrement_y(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val)
                    return (this->m_y -= val);
                }

                void decrement(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                }

                void decrement(const omni::math::dimensional<T, 2>& val)
                {
                    this->decrement(val[0], val[1]);
                }

                void decrement(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                }

                void decrement(const omni::geometry::raw_size<T>& val)
                {
                    this->decrement(val.width, val.height);
                }

                void decrement(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, x)
                    this->m_x -= x;
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, y)
                    this->m_y -= y;
                }

                double distance_from(const omni::geometry::point2d<T>& val) const
                {
                    return this->distance_from(val.x(), val.y());
                }

                double distance_from(const omni::math::dimensional<T, 2>& val) const
                {
                    return this->distance_from(val[0], val[1]);
                }

                double distance_from(const omni::geometry::size<T>& val) const
                {
                    return this->distance_from(val.width(), val.height());
                }

                double distance_from(const omni::geometry::raw_size<T>& val) const
                {
                    return this->distance_from(val.width, val.height);
                }

                double distance_from(T x, T y) const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return omni::math::distance_between_2_points(this->m_x, this->m_y, x, y);
                }

                bool empty() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return omni::math::are_equal(this->m_x, static_cast<T>(0)) &&
                           omni::math::are_equal(this->m_y, static_cast<T>(0));
                }

                bool equals(T x, T y) const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return this->m_x == x && this->m_y == y;
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_x) ^
                        ((static_cast<int32_t>(this->m_y) << 13) | (static_cast<int32_t>(this->m_y) >> 19))
                    );
                }
                
                T increment_x()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, 1)
                    return ++this->m_x;
                }

                T increment_y()
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, 1)
                    return ++this->m_y;
                }

                T increment_x(T val) 
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val)
                    return (this->m_x += val);
                }

                T increment_y(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val)
                    return (this->m_y += val);
                }

                void increment(const omni::geometry::point2d<T>& val)
                {
                    this->increment(val.x(), val.y());
                }

                void increment(const omni::math::dimensional<T, 2>& val)
                {
                    this->increment(val[0], val[1]);
                }

                void increment(const omni::geometry::size<T>& val)
                {
                    this->increment(val.width(), val.height());
                }

                void increment(const omni::geometry::raw_size<T>& val)
                {
                    this->increment(val.width, val.height);
                }

                void increment(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, x)
                    this->m_x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, y)
                    this->m_y += y;
                }

                void offset(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                }

                void offset(const omni::math::dimensional<T, 2>& val)
                {
                    this->offset(val[0], val[1]);
                }

                void offset(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                }

                void offset(const omni::geometry::raw_size<T>& val)
                {
                    this->offset(val.width, val.height);
                }

                void offset(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, x)
                    this->m_x += x;
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, y)
                    this->m_y += y;
                }

                void set(T x, T y)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x = x;
                    this->m_y = y;
                }

                void set(const omni::math::dimensional<T, 2>& point)
                {
                    this->set(point[0], point[1]);
                }

                void swap(point2d<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_P2ALOCK_FW
                        OMNI_SAFE_P2OALOCK_FW(o)
                        std::swap(this->m_x, o.m_x);
                        std::swap(this->m_y, o.m_y);
                    }
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_P2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_P2UNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_P2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_P2UNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
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

                omni::math::dimensional<T, 2> to_dimensional() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    T vals[2] = { this->m_x, this->m_y };
                    return omni::math::dimensional<T, 2>(vals);
                }
                
                omni::geometry::size<T> to_size() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return omni::geometry::size<T>(this->m_x, this->m_y);
                }

                omni::geometry::raw_size<T> to_raw_size() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    return omni::geometry::raw_size<T>(this->m_x, this->m_y);
                }

                bool operator!=(const omni::geometry::point2d<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::point2d<T>& operator=(const omni::geometry::point2d<T>& val)
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

                bool operator<(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x + this->m_y) < (val.m_x + val.m_y);
                }

                bool operator<=(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x + this->m_y) <= (val.m_x + val.m_y);
                }

                bool operator>(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x + this->m_y) > (val.m_x + val.m_y);
                }

                bool operator>=(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (this->m_x + this->m_y) >= (val.m_x + val.m_y);
                }

                bool operator==(const omni::geometry::point2d<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    return (
                        omni::math::are_equal<T>(this->m_x, val.m_x) &&
                        omni::math::are_equal<T>(this->m_y, val.m_y)
                    )
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::point2d<T> operator+(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val.m_x)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val.m_y)
                    return omni::geometry::point2d<T>((this->m_x + val.m_x), (this->m_y + val.m_y));
                }

                omni::geometry::point2d<T> operator+(const omni::math::dimensional<T, 2>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val[0])
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val[1])
                    return omni::geometry::point2d<T>((this->m_x + val[0]), (this->m_y + val[1]));
                }

                omni::geometry::point2d<T> operator+(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val.width())
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val.height())
                    return omni::geometry::point2d<T>((this->m_x + val.width()), (this->m_y + val.height()));
                }

                omni::geometry::point2d<T> operator+(const omni::geometry::raw_size<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val.width)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val.height)
                    return omni::geometry::point2d<T>((this->m_x + val.width), (this->m_y + val.height));
                }

                omni::geometry::point2d<T> operator+(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val)
                    return omni::geometry::point2d<T>((this->m_x + val), (this->m_y + val));
                }

                omni::geometry::point2d<T> operator-(const omni::geometry::point2d<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_SAFE_P2OALOCK_FW(val)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val.m_x)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val.m_y)
                    return omni::geometry::point2d<T>((this->m_x - val.m_x), (this->m_y - val.m_y));
                }

                omni::geometry::point2d<T> operator-(const omni::math::dimensional<T, 2>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val[0])
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val[1])
                    return omni::geometry::point2d<T>((this->m_x - val[0]), (this->m_y - val[1]));
                }

                omni::geometry::point2d<T> operator-(const omni::geometry::size<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val.width())
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val.height())
                    return omni::geometry::point2d<T>((this->m_x - val.width()), (this->m_y - val.height()));
                }

                omni::geometry::point2d<T> operator-(const omni::geometry::raw_size<T>& val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val.width)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val.height)
                    return omni::geometry::point2d<T>((this->m_x - val.width), (this->m_y - val.height));
                }

                omni::geometry::point2d<T> operator-(T val)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val)
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val)
                    return omni::geometry::point2d<T>((this->m_x - val), (this->m_y - val));
                }

                omni::geometry::point2d<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                    return *this;
                }

                omni::geometry::point2d<T> operator+=(const omni::math::dimensional<T, 2>& val)
                {
                    this->offset(val[0], val[1]);
                    return *this;
                }

                omni::geometry::point2d<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                    return *this;
                }

                omni::geometry::point2d<T>& operator+=(const omni::geometry::raw_size<T>& val)
                {
                    this->offset(val.width, val.height);
                    return *this;
                }

                omni::geometry::point2d<T> operator+=(T val)
                {
                    this->offset(val, val);
                    return *this;
                }

                omni::geometry::point2d<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                    return *this;
                }

                omni::geometry::point2d<T> operator-=(const omni::math::dimensional<T, 2>& val)
                {
                    this->decrement(val[0], val[1]);
                    return *this;
                }

                omni::geometry::point2d<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                    return *this;
                }

                omni::geometry::point2d<T>& operator-=(const omni::geometry::raw_size<T>& val)
                {
                    this->decrement(val.width, val.height);
                    return *this;
                }

                omni::geometry::point2d<T> operator-=(T val)
                {
                    this->decrement(val, val);
                    return *this;
                }

                operator omni::math::dimensional<T, 2>() const
                {
                    return this->to_dimensional();
                }

                operator omni::geometry::size<T>() const
                {
                    return this->to_size();
                }

                operator omni::geometry::raw_size<T>() const
                {
                    return this->to_raw_size();
                }

                static omni::geometry::point2d<T> add(const omni::geometry::point2d<T>& point, const omni::math::dimensional<T, 2> coord)
                {
                    OMNI_BITS_WILL_ADD_OVER_FW(point.x(), coord[0])
                    OMNI_BITS_WILL_ADD_OVER_FW(point.y(), coord[1])
                    return omni::geometry::point2d<T>(point.x() + coord[0], point.y() + coord[1]);
                }

                static omni::geometry::point2d<T> add(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz)
                {
                    OMNI_BITS_WILL_ADD_OVER_FW(point.x(), sz.width())
                    OMNI_BITS_WILL_ADD_OVER_FW(point.y(), sz.height())
                    return omni::geometry::point2d<T>(point.x() + sz.width(), point.y() + sz.height());
                }
                
                static omni::geometry::point2d<T> add(const omni::geometry::point2d<T>& point, const omni::geometry::raw_size<T> sz)
                {
                    OMNI_BITS_WILL_ADD_OVER_FW(point.x(), sz.width)
                    OMNI_BITS_WILL_ADD_OVER_FW(point.y(), sz.height)
                    return omni::geometry::point2d<T>(point.x() + sz.width, point.y() + sz.height);
                }

                static omni::geometry::point2d<T> subtract(const omni::geometry::point2d<T>& point, const omni::math::dimensional<T, 2> coord)
                {
                    OMNI_BITS_WILL_SUB_UNDER_FW(point.x(), coord[0])
                    OMNI_BITS_WILL_SUB_UNDER_FW(point.y(), coord[1])
                    return omni::geometry::point2d<T>(point.x() - coord[0], point.y() - coord[1]);
                }

                static omni::geometry::point2d<T> subtract(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz)
                {
                    OMNI_BITS_WILL_SUB_UNDER_FW(point.x(), sz.width())
                    OMNI_BITS_WILL_SUB_UNDER_FW(point.y(), sz.height())
                    return omni::geometry::point2d<T>(point.x() - sz.width(), point.y() - sz.height());
                }

                static omni::geometry::point2d<T> subtract(const omni::geometry::point2d<T>& point, const omni::geometry::raw_size<T> sz)
                {
                    OMNI_BITS_WILL_SUB_UNDER_FW(point.x(), sz.width)
                    OMNI_BITS_WILL_SUB_UNDER_FW(point.y(), sz.height)
                    return omni::geometry::point2d<T>(point.x() - sz.width, point.y() - sz.height);
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
        typedef omni::geometry::point2d<double> pointD_t;

        typedef omni_sequence_t<omni::geometry::point_t> point_seq_t;
        typedef omni_sequence_t<omni::geometry::point64_t> point64_seq_t;
        typedef omni_sequence_t<omni::geometry::pointF_t> pointF_seq_t;
        typedef omni_sequence_t<omni::geometry::pointD_t> pointD_seq_t;

        // DEV_NOTE: "raw" classes do not have checks, like arithmetic over/under flow, locks, etc.

        template < typename T >
        class raw_point2d
        {
            public:
                typedef T coordinate_t;

                raw_point2d() : 
                    OMNI_CTOR_FW(omni::geometry::raw_point2d<T>)
                    x(0), y(0)
                { }

                raw_point2d(const omni::geometry::raw_point2d<T>& cp) : 
                    OMNI_CPCTOR_FW(cp)
                    x(cp.x), y(cp.y)
                { }

                raw_point2d(const omni::geometry::point2d<T>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_point2d<T>)
                    x(cp.x()), y(cp.y())
                { }

                raw_point2d(const omni::math::dimensional<T, 2>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_point2d<T>)
                    x(cp[0]), y(cp[1])
                { }

                raw_point2d(T _x, T _y) : 
                    OMNI_CTOR_FW(omni::geometry::raw_point2d<T>)
                    x(_x), y(_y)
                { }

                ~raw_point2d()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T decrement_x()
                {
                    return --this->x;
                }

                T decrement_y()
                {
                    return --this->y;
                }

                T decrement_x(T val)
                {
                    return (this->x -= val);
                }

                T decrement_y(T val)
                {
                    return (this->y -= val);
                }

                int32_t hash_code() const
                {
                    return (
                        static_cast<int32_t>(this->x) ^
                        ((static_cast<int32_t>(this->y) << 13) | (static_cast<int32_t>(this->y) >> 19))
                    );
                }
                
                T increment_x()
                {
                    return ++this->x;
                }

                T increment_y()
                {
                    return ++this->y;
                }

                T increment_x(T val) 
                {
                    return (this->x += val);
                }

                T increment_y(T val)
                {
                    return (this->y += val);
                }

                void decrement(const omni::geometry::raw_point2d<T>& val)
                {
                    this->decrement(val.x, val.y);
                }

                void decrement(const omni::geometry::point2d<T>& val)
                {
                    this->decrement(val.x(), val.y());
                }

                void decrement(const omni::math::dimensional<T, 2>& val)
                {
                    this->decrement(val[0], val[1]);
                }

                void decrement(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                }

                void decrement(const omni::geometry::raw_size<T>& val)
                {
                    this->decrement(val.width, val.height);
                }

                void decrement(T _x, T _y)
                {
                    this->x -= _x;
                    this->y -= _y;
                }

                double distance_from(const omni::geometry::raw_point2d<T>& val) const
                {
                    return this->distance_from(val.x, val.y);
                }

                double distance_from(const omni::geometry::point2d<T>& val) const
                {
                    return this->distance_from(val.x(), val.y());
                }

                double distance_from(const omni::math::dimensional<T, 2>& val) const
                {
                    return this->distance_from(val[0], val[1]);
                }

                double distance_from(const omni::geometry::size<T>& val) const
                {
                    return this->distance_from(val.width(), val.height());
                }

                double distance_from(const omni::geometry::raw_size<T>& val) const
                {
                    return this->distance_from(val.width, val.height);
                }

                double distance_from(T _x, T _y) const
                {
                    return omni::math::distance_between_2_points(this->x, this->y, _x, _y);
                }

                bool empty() const
                {
                    return omni::math::are_equal(this->x, static_cast<T>(0)) &&
                           omni::math::are_equal(this->y, static_cast<T>(0));
                }

                bool equals(T _x, T _y) const
                {
                    return this->x == _x && this->y == _y;
                }

                void offset(const omni::geometry::raw_point2d<T>& val)
                {
                    this->offset(val.x, val.y);
                }

                void offset(const omni::geometry::point2d<T>& val)
                {
                    this->offset(val.x(), val.y());
                }

                void offset(const omni::math::dimensional<T, 2>& val)
                {
                    this->offset(val[0], val[1]);
                }

                void offset(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                }

                void offset(const omni::geometry::raw_size<T>& val)
                {
                    this->offset(val.width, val.height);
                }

                void offset(T _x, T _y)
                {
                    this->x += _x;
                    this->y += _y;
                }

                void set(T _x, T _y)
                {
                    this->x = _x;
                    this->y = _y;
                }

                void swap(raw_point2d<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->x, o.x);
                        std::swap(this->y, o.y);
                    }
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->x << "," << this->y << "}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    s << "{" << this->x << "," << this->y << "}";
                    return s.str();
                }

                std::wstring to_wstring() const
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

                omni::geometry::point2d<T> to_point2d() const
                {
                    return omni::geometry::point2d<T>(this->x, this->y);
                }

                omni::math::dimensional<T, 2> to_dimensional() const
                {
                    T vals[2] = { this->x, this->y };
                    return omni::math::dimensional<T, 2>(vals);
                }
                
                omni::geometry::size<T> to_size() const
                {
                    return omni::geometry::size<T>(this->x, this->y);
                }

                omni::geometry::raw_size<T> to_raw_size() const
                {
                    return omni::geometry::raw_size<T>(this->x, this->y);
                }

                bool operator!=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::raw_point2d<T>& operator=(const omni::geometry::raw_point2d<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->x = val.x;
                        this->y = val.y;
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::raw_point2d<T>& val) const
                {
                    return (this->x + this->y) < (val.x + val.y);
                }

                bool operator<=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return (this->x + this->y) <= (val.x + val.y);
                }

                bool operator>(const omni::geometry::raw_point2d<T>& val) const
                {
                    return (this->x + this->y) > (val.x + val.y);
                }

                bool operator>=(const omni::geometry::raw_point2d<T>& val) const
                {
                    return (this->x + this->y) >= (val.x + val.y);
                }

                bool operator==(const omni::geometry::raw_point2d<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->x, val.x) &&
                        omni::math::are_equal<T>(this->y, val.y)
                    )
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::raw_point2d<T> operator+(const omni::geometry::raw_point2d<T>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x + val.x), (this->y + val.y));
                }

                omni::geometry::raw_point2d<T> operator+(const omni::math::dimensional<T, 2>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x + val[0]), (this->y + val[1]));
                }

                omni::geometry::raw_point2d<T> operator+(const omni::geometry::size<T>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x + val.width()), (this->y + val.height()));
                }

                omni::geometry::raw_point2d<T> operator+(const omni::geometry::raw_size<T>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x + val.width), (this->y + val.height));
                }

                omni::geometry::raw_point2d<T> operator+(T val)
                {
                    return omni::geometry::raw_point2d<T>((this->x + val), (this->y + val));
                }

                omni::geometry::raw_point2d<T> operator-(const omni::geometry::raw_point2d<T>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x - val.x), (this->y - val.y));
                }

                omni::geometry::raw_point2d<T> operator-(const omni::math::dimensional<T, 2>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x - val[0]), (this->y - val[1]));
                }

                omni::geometry::raw_point2d<T> operator-(const omni::geometry::size<T>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x - val.width()), (this->y - val.height()));
                }

                omni::geometry::raw_point2d<T> operator-(const omni::geometry::raw_size<T>& val)
                {
                    return omni::geometry::raw_point2d<T>((this->x - val.width), (this->y - val.height));
                }

                omni::geometry::raw_point2d<T> operator-(T val)
                {
                    return omni::geometry::raw_point2d<T>((this->x - val), (this->y - val));
                }

                omni::geometry::raw_point2d<T>& operator+=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->offset(val.x, val.y);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator+=(const omni::math::dimensional<T, 2>& val)
                {
                    this->offset(val);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator+=(const omni::geometry::size<T>& val)
                {
                    this->offset(val.width(), val.height());
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator+=(const omni::geometry::raw_size<T>& val)
                {
                    this->offset(val.width, val.height);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator+=(T val)
                {
                    this->offset(val, val);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator-=(const omni::geometry::raw_point2d<T>& val)
                {
                    this->decrement(val.x, val.y);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator-=(const omni::math::dimensional<T, 2>& val)
                {
                    this->decrement(val);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator-=(const omni::geometry::size<T>& val)
                {
                    this->decrement(val.width(), val.height());
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator-=(const omni::geometry::raw_size<T>& val)
                {
                    this->decrement(val.width, val.height);
                    return *this;
                }

                omni::geometry::raw_point2d<T>& operator-=(T val)
                {
                    this->decrement(val, val);
                    return *this;
                }

                operator omni::geometry::point2d<T>() const
                {
                    return this->to_point2d();
                }

                operator omni::math::dimensional<T, 2>() const
                {
                    return this->to_dimensional();
                }

                operator omni::geometry::size<T>() const
                {
                    return this->to_size();
                }

                operator omni::geometry::raw_size<T>() const
                {
                    return this->to_raw_size();
                }

                static omni::geometry::raw_point2d<T> add(const omni::geometry::raw_point2d<T>& point, const omni::math::dimensional<T, 2> sz)
                {
                    return omni::geometry::raw_point2d<T>(point.x + sz[0], point.y + sz[1]);
                }

                static omni::geometry::raw_point2d<T> add(const omni::geometry::raw_point2d<T>& point, const omni::geometry::size<T> sz)
                {
                    return omni::geometry::raw_point2d<T>(point.x + sz.width(), point.y + sz.height());
                }

                static omni::geometry::raw_point2d<T> add(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz)
                {
                    return omni::geometry::raw_point2d<T>(point.x + sz.width, point.y + sz.height);
                }

                static omni::geometry::raw_point2d<T> subtract(const omni::geometry::raw_point2d<T>& point, const omni::math::dimensional<T, 2> sz)
                {
                    return omni::geometry::raw_point2d<T>(point.x - sz[0], point.y - sz[1]);
                }

                static omni::geometry::raw_point2d<T> subtract(const omni::geometry::raw_point2d<T>& point, const omni::geometry::size<T> sz)
                {
                    return omni::geometry::raw_point2d<T>(point.x - sz.width(), point.y - sz.height());
                }

                static omni::geometry::raw_point2d<T> subtract(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz)
                {
                    return omni::geometry::raw_point2d<T>(point.x - sz.width, point.y - sz.height);
                }

                OMNI_MEMBERS_FW(omni::geometry::raw_point2d<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::raw_point2d<T>)

                T x;

                T y;
        };

        typedef omni::geometry::raw_point2d<int32_t> raw_point_t;
        typedef omni::geometry::raw_point2d<int64_t> raw_point64_t;
        typedef omni::geometry::raw_point2d<float> raw_pointF_t;
        typedef omni::geometry::raw_point2d<double> raw_pointD_t;

        typedef omni_sequence_t<omni::geometry::raw_point_t> raw_point_seq_t;
        typedef omni_sequence_t<omni::geometry::raw_point64_t> raw_point64_seq_t;
        typedef omni_sequence_t<omni::geometry::raw_pointF_t> raw_pointF_seq_t;
        typedef omni_sequence_t<omni::geometry::raw_pointD_t> raw_pointD_seq_t;

        #if defined(OMNI_ENABLE_CXX)
            template < typename T >
            class atomic_point2d
            {
                public:
                    typedef T coordinate_t;

                    atomic_point2d() : 
                        OMNI_CTOR_FW(omni::geometry::atomic_point2d<T>)
                        m_x(0), m_y(0)
                    { }

                    atomic_point2d(const omni::geometry::atomic_point2d<T>& cp) :
                        OMNI_CPCTOR_FW(cp)
                        m_x(cp.x()), m_y(cp.y())
                    { }

                    OMNI_EXPLICIT atomic_point2d(const omni::math::dimensional<T, 2>& cp) :
                        OMNI_CTOR_FW(omni::geometry::atomic_point2d<T>)
                        m_x(cp[0]), m_y(cp[1])
                    { }

                    atomic_point2d(T x, T y) : 
                        OMNI_CTOR_FW(omni::geometry::atomic_point2d<T>)
                        m_x(x), m_y(y)
                    { }

                    ~atomic_point2d()
                    {
                        OMNI_TRY_FW
                        OMNI_DTOR_FW
                        OMNI_CATCH_FW
                        OMNI_D5_FW("destroyed");
                    }

                    T x() const
                    {
                        return this->m_x;
                    }

                    T y() const
                    {
                        return this->m_y;
                    }

                    T decrement_x()
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, 1)
                        return --this->m_x;
                    }

                    T decrement_y()
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, 1)
                        return --this->m_y;
                    }

                    T decrement_x(T val)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val)
                        return (this->m_x -= val);
                    }

                    T decrement_y(T val)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val)
                        return (this->m_y -= val);
                    }

                    void decrement(const omni::geometry::atomic_point2d<T>& val)
                    {
                        this->decrement(val.x(), val.y());
                    }

                    void decrement(const omni::math::dimensional<T, 2>& val)
                    {
                        this->decrement(val[0], val[1]);
                    }

                    void decrement(const omni::geometry::size<T>& val)
                    {
                        this->decrement(val.width(), val.height());
                    }

                    void decrement(const omni::geometry::raw_size<T>& val)
                    {
                        this->decrement(val.width, val.height);
                    }

                    void decrement(T x, T y)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, x)
                        this->m_x -= x;
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, y)
                        this->m_y -= y;
                    }

                    double distance_from(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        return this->distance_from(val.x(), val.y());
                    }

                    double distance_from(const omni::math::dimensional<T, 2>& val) const
                    {
                        return this->distance_from(val[0], val[1]);
                    }

                    double distance_from(const omni::geometry::size<T>& val) const
                    {
                        return this->distance_from(val.width(), val.height());
                    }

                    double distance_from(const omni::geometry::raw_size<T>& val) const
                    {
                        return this->distance_from(val.width, val.height);
                    }

                    double distance_from(T x, T y) const
                    {
                        return omni::math::distance_between_2_points(this->m_x, this->m_y, x, y);
                    }

                    bool empty() const
                    {
                        return omni::math::are_equal(this->m_x, static_cast<T>(0)) &&
                            omni::math::are_equal(this->m_y, static_cast<T>(0));
                    }

                    bool equals(T x, T y) const
                    {
                        return this->m_x == x && this->m_y == y;
                    }

                    int32_t hash_code() const
                    {
                        return (
                            static_cast<int32_t>(this->m_x) ^
                            ((static_cast<int32_t>(this->m_y) << 13) | (static_cast<int32_t>(this->m_y) >> 19))
                        );
                    }
                    
                    T increment_x()
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, 1)
                        return ++this->m_x;
                    }

                    T increment_y()
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, 1)
                        return ++this->m_y;
                    }

                    T increment_x(T val) 
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val)
                        return (this->m_x += val);
                    }

                    T increment_y(T val)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val)
                        return (this->m_y += val);
                    }

                    void increment(const omni::geometry::atomic_point2d<T>& val)
                    {
                        this->increment(val.x(), val.y());
                    }

                    void increment(const omni::math::dimensional<T, 2>& val)
                    {
                        this->increment(val[0], val[1]);
                    }

                    void increment(const omni::geometry::size<T>& val)
                    {
                        this->increment(val.width(), val.height());
                    }

                    void increment(const omni::geometry::raw_size<T>& val)
                    {
                        this->increment(val.width, val.height);
                    }

                    void increment(T x, T y)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, x)
                        this->m_x += x;
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, y)
                        this->m_y += y;
                    }

                    void offset(const omni::geometry::atomic_point2d<T>& val)
                    {
                        this->offset(val.x(), val.y());
                    }

                    void offset(const omni::math::dimensional<T, 2>& val)
                    {
                        this->offset(val[0], val[1]);
                    }

                    void offset(const omni::geometry::size<T>& val)
                    {
                        this->offset(val.width(), val.height());
                    }

                    void offset(const omni::geometry::raw_size<T>& val)
                    {
                        this->offset(val.width, val.height);
                    }

                    void offset(T x, T y)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, x)
                        this->m_x += x;
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, y)
                        this->m_y += y;
                    }

                    void set(T x, T y)
                    {
                        this->m_x = x;
                        this->m_y = y;
                    }

                    void set(const omni::math::dimensional<T, 2>& point)
                    {
                        this->set(point[0], point[1]);
                    }

                    void swap(atomic_point2d<T>& o)
                    {
                        if (this != &o) {
                            std::swap(this->m_x, o.m_x);
                            std::swap(this->m_y, o.m_y);
                        }
                    }

                    omni::string_t to_string_t() const
                    {
                        omni::sstream_t s;
                        s << "{" << this->m_x << "," << this->m_y << "}";
                        return s.str();
                    }

                    std::string to_string() const
                    {
                        std::stringstream s;
                        s << "{" << this->m_x << "," << this->m_y << "}";
                        return s.str();
                    }

                    std::wstring to_wstring() const
                    {
                        std::wstringstream s;
                        s << "{" << this->m_x << "," << this->m_y << "}";
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

                    omni::math::dimensional<T, 2> to_dimensional() const
                    {
                        T vals[2] = { this->m_x, this->m_y };
                        return omni::math::dimensional<T, 2>(vals);
                    }
                    
                    omni::geometry::size<T> to_size() const
                    {
                        return omni::geometry::size<T>(this->m_x, this->m_y);
                    }

                    omni::geometry::raw_size<T> to_raw_size() const
                    {
                        return omni::geometry::raw_size<T>(this->m_x, this->m_y);
                    }

                    bool operator!=(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        return !(*this == val);
                    }
                    
                    omni::geometry::atomic_point2d<T>& operator=(const omni::geometry::atomic_point2d<T>& val)
                    {
                        if (this != &val) {
                            OMNI_ASSIGN_FW(val)
                            this->m_x = val.m_x;
                            this->m_y = val.m_y;
                        }
                        return *this;
                    }

                    bool operator<(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        if (this == &val) { return false; }
                        return (this->m_x + this->m_y) < (val.m_x + val.m_y);
                    }

                    bool operator<=(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        if (this == &val) { return false; }
                        return (this->m_x + this->m_y) <= (val.m_x + val.m_y);
                    }

                    bool operator>(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        if (this == &val) { return false; }
                        return (this->m_x + this->m_y) > (val.m_x + val.m_y);
                    }

                    bool operator>=(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        if (this == &val) { return false; }
                        return (this->m_x + this->m_y) >= (val.m_x + val.m_y);
                    }

                    bool operator==(const omni::geometry::atomic_point2d<T>& val) const
                    {
                        if (this == &val) { return true; }
                        return (
                            omni::math::are_equal<T>(this->m_x, val.m_x) &&
                            omni::math::are_equal<T>(this->m_y, val.m_y)
                        )
                        OMNI_EQUAL_FW(val);
                    }

                    omni::geometry::atomic_point2d<T> operator+(const omni::geometry::atomic_point2d<T>& val)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val.m_x)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val.m_y)
                        return omni::geometry::atomic_point2d<T>((this->m_x + val.m_x), (this->m_y + val.m_y));
                    }

                    omni::geometry::atomic_point2d<T> operator+(const omni::math::dimensional<T, 2>& val)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val[0])
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val[1])
                        return omni::geometry::atomic_point2d<T>((this->m_x + val[0]), (this->m_y + val[1]));
                    }

                    omni::geometry::atomic_point2d<T> operator+(const omni::geometry::size<T>& val)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val.width())
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val.height())
                        return omni::geometry::atomic_point2d<T>((this->m_x + val.width()), (this->m_y + val.height()));
                    }

                    omni::geometry::atomic_point2d<T> operator+(const omni::geometry::raw_size<T>& val)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val.width)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val.height)
                        return omni::geometry::atomic_point2d<T>((this->m_x + val.width), (this->m_y + val.height));
                    }

                    omni::geometry::atomic_point2d<T> operator+(T val)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, val)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, val)
                        return omni::geometry::atomic_point2d<T>((this->m_x + val), (this->m_y + val));
                    }

                    omni::geometry::atomic_point2d<T> operator-(const omni::geometry::atomic_point2d<T>& val)
                    {
                        
                        
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val.m_x)
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val.m_y)
                        return omni::geometry::atomic_point2d<T>((this->m_x - val.m_x), (this->m_y - val.m_y));
                    }

                    omni::geometry::atomic_point2d<T> operator-(const omni::math::dimensional<T, 2>& val)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val[0])
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val[1])
                        return omni::geometry::atomic_point2d<T>((this->m_x - val[0]), (this->m_y - val[1]));
                    }

                    omni::geometry::atomic_point2d<T> operator-(const omni::geometry::size<T>& val)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val.width())
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val.height())
                        return omni::geometry::atomic_point2d<T>((this->m_x - val.width()), (this->m_y - val.height()));
                    }

                    omni::geometry::atomic_point2d<T> operator-(const omni::geometry::raw_size<T>& val)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val.width)
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val.height)
                        return omni::geometry::atomic_point2d<T>((this->m_x - val.width), (this->m_y - val.height));
                    }

                    omni::geometry::atomic_point2d<T> operator-(T val)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, val)
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, val)
                        return omni::geometry::atomic_point2d<T>((this->m_x - val), (this->m_y - val));
                    }

                    omni::geometry::atomic_point2d<T>& operator+=(const omni::geometry::atomic_point2d<T>& val)
                    {
                        this->offset(val.x(), val.y());
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T> operator+=(const omni::math::dimensional<T, 2>& val)
                    {
                        this->offset(val[0], val[1]);
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T>& operator+=(const omni::geometry::size<T>& val)
                    {
                        this->offset(val.width(), val.height());
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T>& operator+=(const omni::geometry::raw_size<T>& val)
                    {
                        this->offset(val.width, val.height);
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T> operator+=(T val)
                    {
                        this->offset(val, val);
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T>& operator-=(const omni::geometry::atomic_point2d<T>& val)
                    {
                        this->decrement(val.x(), val.y());
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T> operator-=(const omni::math::dimensional<T, 2>& val)
                    {
                        this->decrement(val[0], val[1]);
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T>& operator-=(const omni::geometry::size<T>& val)
                    {
                        this->decrement(val.width(), val.height());
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T>& operator-=(const omni::geometry::raw_size<T>& val)
                    {
                        this->decrement(val.width, val.height);
                        return *this;
                    }

                    omni::geometry::atomic_point2d<T> operator-=(T val)
                    {
                        this->decrement(val, val);
                        return *this;
                    }

                    operator omni::math::dimensional<T, 2>() const
                    {
                        return this->to_dimensional();
                    }

                    operator omni::geometry::size<T>() const
                    {
                        return this->to_size();
                    }

                    operator omni::geometry::raw_size<T>() const
                    {
                        return this->to_raw_size();
                    }

                    static omni::geometry::atomic_point2d<T> add(const omni::geometry::atomic_point2d<T>& point, const omni::math::dimensional<T, 2> coord)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(point.x(), coord[0])
                        OMNI_BITS_WILL_ADD_OVER_FW(point.y(), coord[1])
                        return omni::geometry::atomic_point2d<T>(point.x() + coord[0], point.y() + coord[1]);
                    }

                    static omni::geometry::atomic_point2d<T> add(const omni::geometry::atomic_point2d<T>& point, const omni::geometry::size<T> sz)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(point.x(), sz.width())
                        OMNI_BITS_WILL_ADD_OVER_FW(point.y(), sz.height())
                        return omni::geometry::atomic_point2d<T>(point.x() + sz.width(), point.y() + sz.height());
                    }
                    
                    static omni::geometry::atomic_point2d<T> add(const omni::geometry::atomic_point2d<T>& point, const omni::geometry::raw_size<T> sz)
                    {
                        OMNI_BITS_WILL_ADD_OVER_FW(point.x(), sz.width)
                        OMNI_BITS_WILL_ADD_OVER_FW(point.y(), sz.height)
                        return omni::geometry::atomic_point2d<T>(point.x() + sz.width, point.y() + sz.height);
                    }

                    static omni::geometry::atomic_point2d<T> subtract(const omni::geometry::atomic_point2d<T>& point, const omni::math::dimensional<T, 2> coord)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(point.x(), coord[0])
                        OMNI_BITS_WILL_SUB_UNDER_FW(point.y(), coord[1])
                        return omni::geometry::atomic_point2d<T>(point.x() - coord[0], point.y() - coord[1]);
                    }

                    static omni::geometry::atomic_point2d<T> subtract(const omni::geometry::atomic_point2d<T>& point, const omni::geometry::size<T> sz)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(point.x(), sz.width())
                        OMNI_BITS_WILL_SUB_UNDER_FW(point.y(), sz.height())
                        return omni::geometry::atomic_point2d<T>(point.x() - sz.width(), point.y() - sz.height());
                    }

                    static omni::geometry::atomic_point2d<T> subtract(const omni::geometry::atomic_point2d<T>& point, const omni::geometry::raw_size<T> sz)
                    {
                        OMNI_BITS_WILL_SUB_UNDER_FW(point.x(), sz.width)
                        OMNI_BITS_WILL_SUB_UNDER_FW(point.y(), sz.height)
                        return omni::geometry::atomic_point2d<T>(point.x() - sz.width, point.y() - sz.height);
                    }

                    OMNI_MEMBERS_FW(omni::geometry::atomic_point2d<T>) // disposing,name,type(),hash()

                    OMNI_OSTREAM_FW(omni::geometry::atomic_point2d<T>)

                private:
                    std::atomic<T> m_x;
                    std::atomic<T> m_y;
            };

            typedef omni::geometry::atomic_point2d<int32_t> atomic_point_t;
            typedef omni::geometry::atomic_point2d<int64_t> atomic_point64_t;
            typedef omni::geometry::atomic_point2d<float> atomic_pointF_t;
            typedef omni::geometry::atomic_point2d<double> atomic_pointD_t;

            typedef omni_sequence_t<omni::geometry::atomic_point_t> atomic_point_seq_t;
            typedef omni_sequence_t<omni::geometry::atomic_point64_t> atomic_point64_seq_t;
            typedef omni_sequence_t<omni::geometry::atomic_pointF_t> atomic_pointF_seq_t;
            typedef omni_sequence_t<omni::geometry::atomic_pointD_t> atomic_pointD_seq_t;
        #endif
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::point2d<T>& o1, omni::geometry::point2d<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::raw_point2d<T>& o1, omni::geometry::raw_point2d<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_2D_POINT_HPP
