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
#include <omni/geometry/size.hpp>

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
                point3d() : 
                    OMNI_CTOR_FW(omni::geometry::point3d<T>)
                    m_x(0), m_y(0), m_z(0)
                    OMNI_SAFE_P3DMTX_FW
                { }

                point3d(const omni::geometry::point3d<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_x(cp.m_x), m_y(cp.m_y), m_z(cp.m_z)
                    OMNI_SAFE_P3DMTX_FW
                { }

                point3d(const omni::math::dimensional<T, 3>& cp) : 
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

                bool empty() const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return this->m_x == 0 && this->m_y == 0 && this->m_z == 0;
                }

                bool equals(T x, T y, T z) const
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return
                        omni::math::are_equal<T>(this->m_x, x) &&
                        omni::math::are_equal<T>(this->m_y, y) &&
                        omni::math::are_equal<T>(this->m_z, z);
                }

                void set_coordinates(T x, T y, T z)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    this->m_x = x;
                    this->m_y = y;
                    this->m_z = z;
                }

                void set_coordinates(const omni::math::dimensional<T, 3>& point)
                {
                    this->set_coordinates(point[0], point[1], point[2]);
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

                T decrease_x(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_x -= val);
                }

                T decrease_y(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_y -= val);
                }

                T decrease_z(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_z -= val);
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

                T increase_x(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_x += val);
                }

                T increase_y(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_y += val);
                }

                T increase_z(T val)
                {
                    OMNI_SAFE_P3ALOCK_FW
                    return (this->m_z += val);
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

                operator std::string() const { return this->to_string(); }

                operator std::wstring() const { return this->to_wstring(); }

                bool operator!=(const point3d< T >& val) const
                {
                    return !(*this == val);
                }

                point3d<T>& operator=(const point3d<T>& val)
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

                bool operator<(const point3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return this->m_x < val.m_x &&
                           this->m_y < val.m_y &&
                           this->m_z < val.m_z;
                }

                bool operator>(const point3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_P3ALOCK_FW
                    OMNI_SAFE_P3OALOCK_FW(val)
                    return this->m_x > val.m_x && 
                           this->m_y > val.m_y &&
                           this->m_z > val.m_z;
                }

                bool operator==(const point3d< T >& val) const
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

                point3d<T> operator+(const point3d<T>& val)
                {
                    #if defined(OMNI_SAFE_POINT3D)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        point3d<T> ret((this->m_x + val.m_x),
                                       (this->m_y + val.m_y),
                                       (this->m_z + val.m_z));
                        if (this != &val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                        return ret;
                    #else
                        return point3d<T>((this->m_x + val.m_x),
                                          (this->m_y + val.m_y),
                                          (this->m_z + val.m_z));
                    #endif
                }

                point3d<T> operator-(const point3d<T>& val)
                {
                    #if defined(OMNI_SAFE_POINT3D)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        point3d<T> ret((this->m_x - val.m_x),
                                       (this->m_y - val.m_y),
                                       (this->m_z - val.m_z));
                        if (this != &val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                        return ret;
                    #else
                        return point3d<T>((this->m_x - val.m_x),
                                          (this->m_y - val.m_y),
                                          (this->m_z - val.m_z));
                    #endif
                }

                point3d<T>& operator+=(const point3d<T>& val)
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

                point3d<T>& operator-=(const point3d<T>& val)
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

        template < typename T >
        class point3d_raw
        {
            public:
                point3d_raw() : 
                    OMNI_CTOR_FW(omni::geometry::point3d_raw<T>)
                    x(0), y(0), z(0)
                { }

                point3d_raw(const omni::geometry::point3d_raw<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    x(cp.x), y(cp.y), z(cp.z)
                { }

                point3d_raw(const omni::math::dimensional<T, 3>& cp) : 
                    OMNI_CTOR_FW(omni::geometry::point3d_raw<T>)
                    x(cp[0]), y(cp[1]), z(cp[2])
                { }

                point3d_raw(T _x, T _y, T _z) : 
                    OMNI_CTOR_FW(omni::geometry::point3d_raw<T>)
                    x(_x), y(_y), z(_z)
                { }

                ~point3d_raw()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                bool empty() const
                {
                    return this->x == 0 && this->y == 0 && this->z == 0;
                }

                bool equals(T _x, T _y, T _z) const
                {
                    return
                        omni::math::are_equal<T>(this->x, _x) &&
                        omni::math::are_equal<T>(this->y, _y) &&
                        omni::math::are_equal<T>(this->z, _z);
                }

                void set(T _x, T _y, T _z)
                {
                    this->x = _x;
                    this->y = _y;
                    this->z = _z;
                }

                void swap(point3d_raw<T>& o)
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

                operator std::string() const { return this->to_string(); }

                operator std::wstring() const { return this->to_wstring(); }

                bool operator!=(const point3d_raw<T>& val) const
                {
                    return !(*this == val);
                }
                
                point3d_raw<T>& operator=(const point3d_raw<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->x = val.x;
                        this->y = val.y;
                        this->z = val.z;
                    }
                    return *this;
                }

                bool operator<(const point3d_raw<T>& val) const
                {
                    return this->x < val.x &&
                           this->y < val.y &&
                           this->z < val.z;
                }

                bool operator>(const point3d_raw<T>& val) const
                {
                    return this->x > val.x && 
                           this->y > val.y &&
                           this->z > val.z;
                }

                bool operator==(const point3d_raw<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->x, val.x) &&
                        omni::math::are_equal<T>(this->y, val.y) &&
                        omni::math::are_equal<T>(this->z, val.z))
                    OMNI_EQUAL_FW(val);
                }

                point3d_raw<T> operator+(const point3d_raw<T>& val)
                {
                    return point3d_raw<T>((this->x + val.x),
                                          (this->y + val.y),
                                          (this->z + val.z));
                }

                point3d_raw<T> operator-(const point3d_raw<T>& val)
                {
                    return point3d_raw<T>((this->x - val.x),
                                          (this->y - val.y),
                                          (this->z - val.z));
                }

                point3d_raw<T>& operator+=(const point3d_raw<T>& val)
                {
                    this->x += val.x;
                    this->y += val.y;
                    this->z += val.z;
                    return *this;
                }

                point3d_raw<T>& operator-=(const point3d_raw<T>& val)
                {
                    this->x -= val.x;
                    this->y -= val.y;
                    this->z -= val.z;
                    return *this;
                }

                OMNI_MEMBERS_FW(omni::geometry::point3d_raw<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::point3d_raw<T>)

                T x;

                T y;

                T z;
        };

        typedef omni::geometry::point3d_raw<int32_t> raw_point_3d_t;
        typedef omni::geometry::point3d_raw<int64_t> raw_point64_3d_t;
        typedef omni::geometry::point3d_raw<float> raw_pointF_3d_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::point3d<T>& o1, omni::geometry::point3d<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::point3d_raw<T>& o1, omni::geometry::point3d_raw<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_3D_POINT_HPP
