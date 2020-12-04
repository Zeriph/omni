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
#if !defined(OMNI_3D_POINT_HPP)
#define OMNI_3D_POINT_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>

#if defined(OMNI_SAFE_POINT3D)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_P3DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_P3LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_P3UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_P3ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_P3OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_P3DMTX_FW
    #define OMNI_SAFE_P3LOCK_FW
    #define OMNI_SAFE_P3UNLOCK_FW
    #define OMNI_SAFE_P3ALOCK_FW
    #define OMNI_SAFE_P3OALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class point3d
        {
            public:
                typedef T coordinate_t;

                point3d() : 
                    OMNI_CTOR_FW(omni::geometry::point3d<T>)
                    m_x(0), m_y(0), m_z(0)
                    OMNI_SAFE_P3DMTX_FW
                { }

                point3d(const omni::geometry::point3d<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_x(cp.x()), m_y(cp.y()), m_z(cp.z())
                    OMNI_SAFE_P3DMTX_FW
                { }

                OMNI_EXPLICIT point3d(const omni::math::dimensional<T, 3>& cp) : 
                    OMNI_CTOR_FW(omni::geometry::point3d<T>)
                    m_x(cp[0]), m_y(cp[1]), m_z(cp[2])
                    OMNI_SAFE_P3DMTX_FW
                { }

                point3d(T x, T y, T z) : 
                    OMNI_CTOR_FW(omni::geometry::point3d<T>)
                    m_x(x), m_y(y), m_z(z)
                    OMNI_SAFE_P3DMTX_FW
                { }

                ~point3d()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T x() const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return this->m_x;
                }

                T y() const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return this->m_y;
                }

                T z() const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return this->m_z;
                }

                T decrement_x()
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return --this->m_x;
                }

                T decrement_y()
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return --this->m_y;
                }

                T decrement_z()
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return --this->m_z;
                }

                T decrement_x(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_x -= val);
                }

                T decrement_y(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_y -= val);
                }

                T decrement_z(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_z -= val);
                }

                void decrement(const omni::geometry::point3d<T>& val)
                {
                    this->decrement(val.x(), val.y(), val.z());
                }

                void decrement(const omni::math::dimensional<T, 3>& val)
                {
                    this->decrement(val[0], val[1], val[2]);
                }

                void decrement(T x, T y, T z)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x -= x;
                    this->m_y -= y;
                    this->m_z -= z;
                }

                bool empty() const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return omni::math::are_equal(this->m_x, static_cast<T>(0)) &&
                           omni::math::are_equal(this->m_y, static_cast<T>(0)) &&
                           omni::math::are_equal(this->m_z, static_cast<T>(0));
                }

                bool equals(T x, T y, T z) const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return
                        omni::math::are_equal<T>(this->m_x, x) &&
                        omni::math::are_equal<T>(this->m_y, y) &&
                        omni::math::are_equal<T>(this->m_z, z);
                }
                
                int32_t hash_code() const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_x) ^
                        ((static_cast<int32_t>(this->m_y) << 13) | (static_cast<int32_t>(this->m_y) >> 19)) ^
                        ((static_cast<int32_t>(this->m_z) << 26) | (static_cast<int32_t>(this->m_z) >>  6))
                    );
                }

                T increment_x()
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return ++this->m_x;
                }

                T increment_y()
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return ++this->m_y;
                }

                T increment_z()
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return ++this->m_z;
                }

                T increment_x(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_x += val);
                }

                T increment_y(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_y += val);
                }

                T increment_z(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_z += val);
                }

                void increment(const omni::geometry::point3d<T>& val)
                {
                    this->increment(val.x(), val.y(), val.z());
                }

                void increment(const omni::math::dimensional<T, 3>& val)
                {
                    this->increment(val[0], val[1], val[2]);
                }

                void increment(T x, T y, T z)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x += x;
                    this->m_y += y;
                    this->m_z += z;
                }

                void offset(const omni::geometry::point3d<T>& val)
                {
                    this->offset(val.x(), val.y(), val.z());
                }

                void offset(const omni::math::dimensional<T, 3>& val)
                {
                    this->offset(val[0], val[1], val[2]);
                }

                void offset(T x, T y, T z)
                {
                    OMNI_SAFE_P2ALOCK_FW
                    this->m_x += x;
                    this->m_y += y;
                    this->m_z += z;
                }

                void set(T x, T y, T z)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    this->m_x = x;
                    this->m_y = y;
                    this->m_z = z;
                }

                void set(const omni::math::dimensional<T, 3>& point)
                {
                    this->set(point[0], point[1], point[2]);
                }

                void swap(point3d<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_P3ALOCK_FW
                        OMNI_SAFE_P3OALOCK_FW(o)
                        std::swap(this->m_x, o.m_x);
                        std::swap(this->m_y, o.m_y);
                        std::swap(this->m_z, o.m_z);
                    }
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_P3LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "}";
                    OMNI_SAFE_P3UNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_P3LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "}";
                    OMNI_SAFE_P3UNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_P3LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "}";
                    OMNI_SAFE_P3UNLOCK_FW
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

                omni::math::dimensional<T, 3> to_dimensional() const
                {
                    OMNI_SAFE_P2ALOCK_FW
                    T vals[3] = { this->m_x, this->m_y, this->m_z };
                    return omni::math::dimensional<T, 3>(vals);
                }

                bool operator!=(const omni::geometry::point3d< T >& val) const
                {
                    return !(*this == val);
                }

                omni::geometry::point3d<T>& operator=(const omni::geometry::point3d<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_P3ALOCK_FW
                        OMNI_SAFE_P3OALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_x = val.m_x;
                        this->m_y = val.m_y;
                        this->m_z = val.m_z;
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::point3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return (this->m_x + this->m_y + this->m_z) < (val.m_x + val.m_y + val.m_z);
                }

                bool operator<=(const omni::geometry::point3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return (this->m_x + this->m_y + this->m_z) <= (val.m_x + val.m_y + val.m_z);
                }

                bool operator>(const omni::geometry::point3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return (this->m_x + this->m_y + this->m_z) > (val.m_x + val.m_y + val.m_z);
                }

                bool operator>=(const omni::geometry::point3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return (this->m_x + this->m_y + this->m_z) >= (val.m_x + val.m_y + val.m_z);
                }

                bool operator==(const omni::geometry::point3d< T >& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return (
                        omni::math::are_equal<T>(this->m_x, val.m_x) &&
                        omni::math::are_equal<T>(this->m_y, val.m_y) &&
                        omni::math::are_equal<T>(this->m_z, val.m_z))
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::point3d<T> operator+(const omni::geometry::point3d<T>& val)
                {
                    #if defined(OMNI_SAFE_POINT3D)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        omni::geometry::point3d<T> ret((this->m_x + val.m_x),
                                       (this->m_y + val.m_y),
                                       (this->m_z + val.m_z));
                        if (this != &val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                        return ret;
                    #else
                        return omni::geometry::point3d<T>((this->m_x + val.m_x),
                                          (this->m_y + val.m_y),
                                          (this->m_z + val.m_z));
                    #endif
                }

                omni::geometry::point3d<T> operator+(const omni::math::dimensional<T, 3>& val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return omni::geometry::point3d<T>((this->m_x + val[0]),
                                      (this->m_y + val[1]),
                                      (this->m_z + val[2]));
                }

                omni::geometry::point3d<T> operator+(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return omni::geometry::point3d<T>((this->m_x + val),
                                      (this->m_y + val),
                                      (this->m_z + val));
                }

                omni::geometry::point3d<T> operator-(const omni::geometry::point3d<T>& val)
                {
                    #if defined(OMNI_SAFE_POINT3D)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        omni::geometry::point3d<T> ret((this->m_x - val.m_x),
                                       (this->m_y - val.m_y),
                                       (this->m_z - val.m_z));
                        if (this != &val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                        return ret;
                    #else
                        return omni::geometry::point3d<T>((this->m_x - val.m_x),
                                          (this->m_y - val.m_y),
                                          (this->m_z - val.m_z));
                    #endif
                }

                omni::geometry::point3d<T> operator-(const omni::math::dimensional<T, 3>& val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return omni::geometry::point3d<T>((this->m_x - val[0]),
                                      (this->m_y - val[1]),
                                      (this->m_z - val[2]));
                }

                omni::geometry::point3d<T> operator-(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return omni::geometry::point3d<T>((this->m_x - val),
                                      (this->m_y - val),
                                      (this->m_z - val));
                }

                omni::geometry::point3d<T>& operator+=(const omni::geometry::point3d<T>& val)
                {
                    #if defined(OMNI_SAFE_POINT3D)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        this->m_x += val.m_x;
                        this->m_y += val.m_y;
                        this->m_z += val.m_z;
                        if (this != & val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                    #else    
                        this->m_x += val.m_x;
                        this->m_y += val.m_y;
                        this->m_z += val.m_z;
                    #endif
                    return *this;
                }

                omni::geometry::point3d<T>& operator+=(const omni::math::dimensional<T, 3>& val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    this->m_x += val[0];
                    this->m_y += val[1];
                    this->m_z += val[2];
                    return *this;
                }

                omni::geometry::point3d<T>& operator+=(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    this->m_x += val;
                    this->m_y += val;
                    this->m_z += val;
                    return *this;
                }

                omni::geometry::point3d<T>& operator-=(const omni::geometry::point3d<T>& val)
                {
                    #if defined(OMNI_SAFE_POINT3D)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        this->m_x -= val.m_x;
                        this->m_y -= val.m_y;
                        this->m_z -= val.m_z;
                        if (this != & val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                    #else    
                        this->m_x -= val.m_x;
                        this->m_y -= val.m_y;
                        this->m_z -= val.m_z;
                    #endif
                    return *this;
                }

                omni::geometry::point3d<T>& operator-=(const omni::math::dimensional<T, 3>& val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    this->m_x -= val[0];
                    this->m_y -= val[1];
                    this->m_z -= val[2];
                    return *this;
                }

                omni::geometry::point3d<T>& operator-=(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    this->m_x -= val;
                    this->m_y -= val;
                    this->m_z -= val;
                    return *this;
                }

                operator omni::math::dimensional<T, 3>() const
                {
                    return this->to_dimensional();
                }

                static omni::geometry::point3d<T> add(const omni::geometry::point3d<T>& point, const omni::math::dimensional<T, 3> coord)
                {
                    return omni::geometry::point3d<T>(point.x() + coord[0],
                                      point.y() + coord[1],
                                      point.z() + coord[2]);
                }

                static omni::geometry::point3d<T> subtract(const omni::geometry::point3d<T>& point, const omni::math::dimensional<T, 3> coord)
                {
                    return omni::geometry::point3d<T>(point.x() - coord[0],
                                      point.y() - coord[1],
                                      point.z() - coord[2]);
                }

                OMNI_MEMBERS_FW(omni::geometry::point3d<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::point3d<T>)

            private:
                T m_x;
                T m_y;
                T m_z;
                #if defined(OMNI_SAFE_POINT3D)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
        };

        typedef omni::geometry::point3d<int32_t> point_3d_t;
        typedef omni::geometry::point3d<int64_t> point64_3d_t;
        typedef omni::geometry::point3d<float> pointF_3d_t;
        typedef omni::geometry::point3d<double> pointD_3d_t;

        typedef omni_sequence_t<omni::geometry::point_3d_t> point_3d_seq_t;
        typedef omni_sequence_t<omni::geometry::point64_3d_t> point64_3d_seq_t;
        typedef omni_sequence_t<omni::geometry::pointF_3d_t> pointF_3d_seq_t;
        typedef omni_sequence_t<omni::geometry::pointD_3d_t> pointD_3d_seq_t;

        template < typename T >
        class raw_point3d
        {
            public:
                typedef T coordinate_t;

                raw_point3d() : 
                    OMNI_CTOR_FW(omni::geometry::raw_point3d<T>)
                    x(0), y(0), z(0)
                { }

                raw_point3d(const omni::geometry::raw_point3d<T>& cp) : 
                    OMNI_CPCTOR_FW(cp)
                    x(cp.x), y(cp.y), z(cp.z)
                { }

                raw_point3d(const omni::geometry::point3d<T>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_point3d<T>)
                    x(cp.x()), y(cp.y()), z(cp.z())
                { }

                raw_point3d(const omni::math::dimensional<T, 3>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_point3d<T>)
                    x(cp[0]), y(cp[1]), z(cp[2])
                { }

                raw_point3d(T _x, T _y, T _z) : 
                    OMNI_CTOR_FW(omni::geometry::raw_point3d<T>)
                    x(_x), y(_y), z(_z)
                { }

                ~raw_point3d()
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

                T decrement_z()
                {
                    return --this->z;
                }

                T decrement_x(T val)
                {
                    return (this->x -= val);
                }

                T decrement_y(T val)
                {
                    return (this->y -= val);
                }

                T decrement_z(T val)
                {
                    return (this->z -= val);
                }

                int32_t hash_code() const
                {
                    return (
                        static_cast<int32_t>(this->x) ^
                        ((static_cast<int32_t>(this->y) << 13) | (static_cast<int32_t>(this->y) >> 19)) ^
                        ((static_cast<int32_t>(this->z) << 26) | (static_cast<int32_t>(this->z) >>  6))
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

                T increment_z()
                {
                    return ++this->z;
                }

                T increment_x(T val) 
                {
                    return (this->x += val);
                }

                T increment_y(T val)
                {
                    return (this->y += val);
                }

                T increment_z(T val)
                {
                    return (this->z += val);
                }

                void decrement(const omni::geometry::raw_point3d<T>& val)
                {
                    this->decrement(val.x, val.y, val.z);
                }

                void decrement(const omni::geometry::point3d<T>& val)
                {
                    this->decrement(val.x(), val.y(), val.z());
                }

                void decrement(const omni::math::dimensional<T, 3>& val)
                {
                    this->decrement(val[0], val[1], val[2]);
                }

                void decrement(T _x, T _y, T _z)
                {
                    this->x -= _x;
                    this->y -= _y;
                    this->z -= _z;
                }

                bool empty() const
                {
                    return omni::math::are_equal(this->x, static_cast<T>(0)) &&
                           omni::math::are_equal(this->y, static_cast<T>(0)) &&
                           omni::math::are_equal(this->z, static_cast<T>(0));
                }

                bool equals(T _x, T _y, T _z) const
                {
                    return this->x == _x && 
                           this->y == _y &&
                           this->z == _z;
                }

                void offset(const omni::geometry::raw_point3d<T>& val)
                {
                    this->offset(val.x, val.y, val.z);
                }

                void offset(const omni::geometry::point3d<T>& val)
                {
                    this->offset(val.x(), val.y(), val.z());
                }

                void offset(const omni::math::dimensional<T, 3>& val)
                {
                    this->offset(val[0], val[1], val[2]);
                }

                void offset(T _x, T _y, T _z)
                {
                    this->x += _x;
                    this->y += _y;
                    this->z += _z;
                }

                void set(T _x, T _y, T _z)
                {
                    this->x = _x;
                    this->y = _y;
                    this->z = _z;
                }

                void swap(raw_point3d<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->x, o.x);
                        std::swap(this->y, o.y);
                        std::swap(this->z, o.z);
                    }
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->x << "," << this->y << "," << this->z << "}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    s << "{" << this->x << "," << this->y << "," << this->z << "}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    s << "{" << this->x << "," << this->y << "," << this->z << "}";
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

                omni::geometry::point3d<T> to_point3d() const
                {
                    return omni::geometry::point3d<T>(this->x, this->y, this->z);
                }

                omni::math::dimensional<T, 3> to_dimensional() const
                {
                    T vals[3] = { this->x, this->y, this->z };
                    return omni::math::dimensional<T, 3>(vals);
                }

                bool operator!=(const omni::geometry::raw_point3d<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::raw_point3d<T>& operator=(const omni::geometry::raw_point3d<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->x = val.x;
                        this->y = val.y;
                        this->z = val.z;
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::raw_point3d<T>& val) const
                {
                    return (this->x + this->y + this->z) < (val.x + val.y + val.z);
                }

                bool operator<=(const omni::geometry::raw_point3d<T>& val) const
                {
                    return (this->x + this->y + this->z) <= (val.x + val.y + val.z);
                }

                bool operator>(const omni::geometry::raw_point3d<T>& val) const
                {
                    return (this->x + this->y + this->z) > (val.x + val.y + val.z);
                }

                bool operator>=(const omni::geometry::raw_point3d<T>& val) const
                {
                    return (this->x + this->y + this->z) >= (val.x + val.y + val.z);
                }

                bool operator==(const omni::geometry::raw_point3d<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->x, val.x) &&
                        omni::math::are_equal<T>(this->y, val.y) &&
                        omni::math::are_equal<T>(this->z, val.z)
                    )
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::raw_point3d<T> operator+(const omni::geometry::raw_point3d<T>& val)
                {
                    return omni::geometry::raw_point3d<T>((this->x + val.x),
                                          (this->y + val.y),
                                          (this->z + val.z));
                }

                omni::geometry::raw_point3d<T> operator+(const omni::math::dimensional<T, 3>& val)
                {
                    return omni::geometry::raw_point3d<T>((this->x + val[0]),
                                          (this->y + val[1]),
                                          (this->z + val[2]));
                }

                omni::geometry::raw_point3d<T> operator+(T val)
                {
                    return omni::geometry::raw_point3d<T>((this->x + val),
                                          (this->y + val),
                                          (this->z + val));
                }

                omni::geometry::raw_point3d<T> operator-(const omni::geometry::raw_point3d<T>& val)
                {
                    return omni::geometry::raw_point3d<T>((this->x - val.x),
                                          (this->y - val.y),
                                          (this->z - val.z));
                }

                omni::geometry::raw_point3d<T> operator-(const omni::math::dimensional<T, 3>& val)
                {
                    return omni::geometry::raw_point3d<T>((this->x - val[0]),
                                          (this->y - val[1]),
                                          (this->z - val[2]));
                }

                omni::geometry::raw_point3d<T> operator-(T val)
                {
                    return omni::geometry::raw_point3d<T>((this->x - val),
                                          (this->y - val),
                                          (this->z - val));
                }

                omni::geometry::raw_point3d<T>& operator+=(const omni::geometry::raw_point3d<T>& val)
                {
                    this->offset(val.x, val.y, val.z);
                    return *this;
                }

                omni::geometry::raw_point3d<T>& operator+=(const omni::math::dimensional<T, 3>& val)
                {
                    this->offset(val);
                    return *this;
                }

                omni::geometry::raw_point3d<T>& operator+=(T val)
                {
                    this->offset(val, val, val);
                    return *this;
                }

                omni::geometry::raw_point3d<T>& operator-=(const omni::geometry::raw_point3d<T>& val)
                {
                    this->decrement(val.x, val.y, val.z);
                    return *this;
                }

                omni::geometry::raw_point3d<T>& operator-=(const omni::math::dimensional<T, 3>& val)
                {
                    this->decrement(val);
                    return *this;
                }

                omni::geometry::raw_point3d<T>& operator-=(T val)
                {
                    this->decrement(val, val, val);
                    return *this;
                }

                operator omni::geometry::point3d<T>() const
                {
                    return this->to_point3d();
                }

                operator omni::math::dimensional<T, 3>() const
                {
                    return this->to_dimensional();
                }

                static omni::geometry::raw_point3d<T> add(const omni::geometry::raw_point3d<T>& point, const omni::math::dimensional<T, 3> sz)
                {
                    return omni::geometry::raw_point3d<T>((point.x + sz[0]),
                                          (point.y + sz[1]),
                                          (point.z + sz[2]));
                }

                static omni::geometry::raw_point3d<T> subtract(const omni::geometry::raw_point3d<T>& point, const omni::math::dimensional<T, 3> sz)
                {
                    return omni::geometry::raw_point3d<T>((point.x - sz[0]),
                                          (point.y - sz[1]),
                                          (point.z - sz[2]));
                }

                OMNI_MEMBERS_FW(omni::geometry::raw_point3d<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::raw_point3d<T>)

                T x;

                T y;

                T z;
        };

        typedef omni::geometry::raw_point3d<int32_t> raw_point_3d_t;
        typedef omni::geometry::raw_point3d<int64_t> raw_point64_3d_t;
        typedef omni::geometry::raw_point3d<float> raw_pointF_3d_t;
        typedef omni::geometry::raw_point3d<double> raw_pointD_3d_t;

        typedef omni_sequence_t<omni::geometry::raw_point_3d_t> raw_point_3d_seq_t;
        typedef omni_sequence_t<omni::geometry::raw_point64_3d_t> raw_point64_3d_seq_t;
        typedef omni_sequence_t<omni::geometry::raw_pointF_3d_t> raw_pointF_3d_seq_t;
        typedef omni_sequence_t<omni::geometry::raw_pointD_3d_t> raw_pointD_3d_seq_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::point3d<T>& o1, omni::geometry::point3d<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::raw_point3d<T>& o1, omni::geometry::raw_point3d<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_3D_POINT_HPP
