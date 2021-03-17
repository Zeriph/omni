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
#if !defined(OMNI_VECTOR3_HPP)
#define OMNI_VECTOR3_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/point3d.hpp>

#if defined(OMNI_SAFE_VECTOR3)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_VEC3MTX_FW  ,m_mtx()
    #define OMNI_SAFE_VEC3LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_VEC3UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_VEC3ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_VEC3OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_VEC3MTX_FW
    #define OMNI_SAFE_VEC3LOCK_FW
    #define OMNI_SAFE_VEC3UNLOCK_FW
    #define OMNI_SAFE_VEC3ALOCK_FW
    #define OMNI_SAFE_VEC3OALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename V >
        class vector3
        {
            public:
                typedef V coordinate_t;
                typedef omni::geometry::point3d<V> point3d_t;

                vector3() :
                    OMNI_CTOR_FW(omni::geometry::vector3)
                    m_sx(0.0), m_sy(0.0), m_sz(0.0), m_x(), m_y(), m_z()
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                vector3(const omni::geometry::vector3<V>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_sx(cp.start_x()), m_sy(cp.start_y()), m_sz(cp.start_z()), m_x(cp.x()), m_y(cp.y()), m_z(cp.z())
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                template < typename T >
                vector3(const omni::geometry::point3d<T>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector3)
                    m_sx(0.0), m_sy(0.0), m_sz(0.0), m_x(head.x()), m_y(head.y()), m_z(head.z())
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                template < typename T >
                vector3(const omni::geometry::point3d<T>& tail, const omni::geometry::point3d<T>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector3)
                    m_sx(tail.x()), m_sy(tail.y()), m_sz(tail.z()), m_x(head.x()), m_y(head.y()), m_z(head.z())
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                template < typename T >
                vector3(const omni::math::dimensional<T, 3>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector3)
                    m_sx(0.0), m_sy(0.0), m_sz(0.0), m_x(head[0]), m_y(head[1]), m_z(head[2])
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                template < typename T >
                vector3(const omni::math::dimensional<T, 3>& tail, const omni::math::dimensional<T, 3>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector3)
                    m_sx(tail[0]), m_sy(tail[1]), m_sz(tail[2]), m_x(head[0]), m_y(head[1]), m_z(head[2])
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                vector3(V x, V y, V z) :
                    m_sx(0.0), m_sy(0.0), m_sz(0.0), m_x(x), m_y(y), m_z(z)
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                vector3(V start_x, V start_y, V start_z, V x, V y, V z) :
                    m_sx(start_x), m_sy(start_y), m_sz(start_z), m_x(x), m_y(y), m_z(z)
                    OMNI_SAFE_VEC3MTX_FW
                {
                }

                ~vector3()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                double angle_between(const omni::geometry::vector3<V>& b)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return OMNI_RAD_TO_DEG((this->_dot_product(b) / (this->_magnitude() * b._magnitude())));
                }

                void assign(V start_x, V start_y, V start_z, V x, V y, V z)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_sx = start_x;
                    this->m_sy = start_y;
                    this->m_sz = start_z;
                    this->m_x = x;
                    this->m_y = y;
                    this->m_z = z;
                }

                template < typename T >
                void assign(const omni::geometry::point3d<T>& tail, const omni::geometry::point3d<T>& head)
                {
                    this->assign(
                        static_cast<V>(tail.x()),
                        static_cast<V>(tail.y()),
                        static_cast<V>(tail.z()),
                        static_cast<V>(head.x()),
                        static_cast<V>(head.y()),
                        static_cast<V>(head.z())
                    );
                }

                template < typename T >
                void assign(const omni::math::dimensional<T, 3>& tail, const omni::math::dimensional<T, 3>& head)
                {
                    this->assign(
                        static_cast<V>(tail[0]),
                        static_cast<V>(tail[1]),
                        static_cast<V>(tail[2]),
                        static_cast<V>(head[0]),
                        static_cast<V>(head[1]),
                        static_cast<V>(head[2])
                    );
                }

                void assign_head(V x, V y, V z)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_x = x;
                    this->m_y = y;
                    this->m_z = z;
                }

                template < typename T >
                void assign_head(const omni::geometry::point3d<T>& head)
                {
                    this->assign_head(
                        static_cast<V>(head.x()),
                        static_cast<V>(head.y()),
                        static_cast<V>(head.z())
                    );
                }

                template < typename T >
                void assign_head(const omni::math::dimensional<T, 3>& head)
                {
                    this->assign_head(
                        static_cast<V>(head[0]),
                        static_cast<V>(head[1]),
                        static_cast<V>(head[2])
                    );
                }

                void assign_tail(V start_x, V start_y, V start_z)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_sx = start_x;
                    this->m_sy = start_y;
                    this->m_sz = start_z;
                }

                template < typename T >
                void assign_tail(const omni::geometry::point3d<T>& tail)
                {
                    this->assign_tail(
                        static_cast<V>(tail.x()),
                        static_cast<V>(tail.y()),
                        static_cast<V>(tail.z())
                    );
                }

                template < typename T >
                void assign_tail(const omni::math::dimensional<T, 3>& tail)
                {
                    this->assign_tail(
                        static_cast<V>(tail[0]),
                        static_cast<V>(tail[1]),
                        static_cast<V>(tail[2])
                    );
                }

                omni::geometry::vector3<V> cross_product(const omni::geometry::vector3<V>& b) const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC3OALOCK_FW(b)
                        /*
                            3d
                            c.x = a.y * b.z − a.z * b.y
                            c.y = a.z * b.x − a.x * b.z
                            c.z = a.x * b.y − a.y * b.x
                        */
                        return omni::geometry::vector3<V>(
                            ((this->m_y * b.m_z) - (this->m_z * b.m_y)), // x
                            ((this->m_z * b.m_x) - (this->m_x * b.m_z)), // y
                            ((this->m_x * b.m_y) - (this->m_y * b.m_x))  // z
                        );
                    }
                    return omni::geometry::vector3<V>(
                        ((this->m_y * b.m_z) - (this->m_z * b.m_y)), // x
                        ((this->m_z * b.m_x) - (this->m_x * b.m_z)), // y
                        ((this->m_x * b.m_y) - (this->m_y * b.m_x))  // z
                    );
                }

                V dot_product(const omni::geometry::vector3<V>& b) const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC3OALOCK_FW(b)
                        return this->_dot_product(b);
                    }
                    return this->_dot_product(b);
                }

                /**
                 * Returns the direction as degrees
                 */
                double direction_x() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_direction_x();
                }

                double direction_y() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_direction_y();
                }

                double direction_z() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_direction_z();
                }

                omni::geometry::point3d<double> direction_cosines() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return omni::geometry::point3d<double>(
                        std::cos(this->_x() / this->_magnitude()),
                        std::cos(this->_y() / this->_magnitude()),
                        std::cos(this->_z() / this->_magnitude())
                    );
                }

                long double distance_from(const omni::geometry::vector3<V>& b)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC3OALOCK_FW(b)
                        return std::sqrt(
                            ((b._x() - this->_x()) * (b._x() - this->_x())) + 
                            ((b._y() - this->_y()) * (b._y() - this->_y())) + 
                            ((b._z() - this->_z()) * (b._z() - this->_z()))
                        );
                    }
                    return std::sqrt(
                        ((b._x() - this->_x()) * (b._x() - this->_x())) + 
                        ((b._y() - this->_y()) * (b._y() - this->_y())) + 
                        ((b._z() - this->_z()) * (b._z() - this->_z()))
                    );
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_sx) ^
                        ((static_cast<int32_t>(this->m_sy) << 13) | (static_cast<int32_t>(this->m_sy) >> 19)) ^
                        ((static_cast<int32_t>(this->m_sz) << 20) | (static_cast<int32_t>(this->m_sz) >> 14)) ^
                        ((static_cast<int32_t>(this->m_x) << 26) | (static_cast<int32_t>(this->m_x) >>  6)) ^
                        ((static_cast<int32_t>(this->m_y) <<  7) | (static_cast<int32_t>(this->m_y) >> 25)) ^
                        ((static_cast<int32_t>(this->m_z) <<  24) | (static_cast<int32_t>(this->m_z) >> 8))
                    );
                }

                point3d_t head() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return point3d_t(this->m_x, this->m_y, this->m_z);
                }

                bool is_standard_form() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return (
                        omni::math::are_equal<V>(this->m_sx, 0) &&
                        omni::math::are_equal<V>(this->m_sy, 0) &&
                        omni::math::are_equal<V>(this->m_sz, 0)
                    );
                }

                V length() const
                {
                    return this->magnitude();
                }

                V magnitude() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_magnitude();
                }

                void set_start_x(V start_x)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_sx = start_x;
                }

                void set_start_y(V start_y)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_sy = start_y;
                }

                void set_start_z(V start_z)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_sz = start_z;
                }

                void set_x(V x)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_x = x;
                }

                void set_y(V y)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_y = y;
                }

                void set_z(V z)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_z = z;
                }

                V start_x() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->m_sx;
                }

                V start_y() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->m_sy;
                }

                V start_z() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->m_sz;
                }

                void swap(vector3& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_VEC3ALOCK_FW
                        OMNI_SAFE_VEC3OALOCK_FW(o)
                        std::swap(this->m_sx, o.m_sx);
                        std::swap(this->m_sy, o.m_sy);
                        std::swap(this->m_sz, o.m_sz);
                        std::swap(this->m_x, o.m_x);
                        std::swap(this->m_y, o.m_y);
                        std::swap(this->m_z, o.m_z);
                    }
                }

                point3d_t tail() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return point3d_t(this->m_sx, this->m_sy, this->m_sz);
                }

                omni::geometry::vector3<V> to_standard_form() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return omni::geometry::vector3<V>(this->_x(), this->_y(), this->_z());
                }

                omni::geometry::vector3<V> unit_vector() const
                {
                    return *this / this->magnitude();
                }

                V x() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->m_x;
                }

                V y() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->m_y;
                }

                V z() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->m_z;
                }

                V x_component() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_x();
                }

                V y_component() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_y();
                }

                V z_component() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return this->_z();
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_VEC3LOCK_FW
                    s << "{" << this->m_x << ","
                             << this->m_y << ","
                             << this->m_z << ";"
                             << this->_direction_x() << ","
                             << this->_direction_y() << ","
                             << this->_direction_z() << ","
                             << this->_magnitude() << "}";
                    OMNI_SAFE_VEC3UNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_VEC3LOCK_FW
                    s << "{" << this->m_x << ","
                             << this->m_y << ","
                             << this->m_z << ";"
                             << this->_direction_x() << ","
                             << this->_direction_y() << ","
                             << this->_direction_z() << ","
                             << this->_magnitude() << "}";
                    OMNI_SAFE_VEC3UNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_VEC3LOCK_FW
                    s << "{" << this->m_x << ","
                             << this->m_y << ","
                             << this->m_z << ";"
                             << this->_direction_x() << ","
                             << this->_direction_y() << ","
                             << this->_direction_z() << ","
                             << this->_magnitude() << "}";
                    OMNI_SAFE_VEC3UNLOCK_FW
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

                template < typename T >
                operator omni::geometry::point3d<T>() const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return omni::geometry::point3d<T>(
                        static_cast<T>(this->_x()),
                        static_cast<T>(this->_y()),
                        static_cast<T>(this->_z())
                    );
                }

                bool operator==(const omni::geometry::vector3<V>& b) const
                {
                    if (this == &b) { return true; }
                    OMNI_SAFE_VEC3ALOCK_FW
                    OMNI_SAFE_VEC3OALOCK_FW(b)
                    return (
                        omni::math::are_equal(this->_magnitude(), b._magnitude()) &&
                        omni::math::are_equal(this->_direction_x(), b._direction_x()) &&
                        omni::math::are_equal(this->_direction_y(), b._direction_y()) &&
                        omni::math::are_equal(this->_direction_z(), b._direction_z())
                    )
                    OMNI_EQUAL_FW(b);
                }

                bool operator!=(const omni::geometry::vector3<V>& b) const
                {
                    return !(*this == b);
                }

                omni::geometry::vector3<V>& operator=(const omni::geometry::vector3<V>& b)
                {
                    if (this != &b) {
                        OMNI_SAFE_VEC3ALOCK_FW
                        OMNI_SAFE_VEC3OALOCK_FW(b)
                        OMNI_ASSIGN_FW(b)
                        this->m_sx = b.m_sx;
                        this->m_sy = b.m_sy;
                        this->m_sz = b.m_sz;
                        this->m_x = b.m_x;
                        this->m_y = b.m_y;
                        this->m_z = b.m_z;
                    }
                    return *this;
                }

                template < typename T >
                omni::geometry::vector3<V>& operator=(const omni::geometry::point3d<T>& point)
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    this->m_x = static_cast<V>(point.x());
                    this->m_y = static_cast<V>(point.y());
                    this->m_z = static_cast<V>(point.z());
                    return *this;
                }

                omni::geometry::vector3<V> operator-(const omni::geometry::vector3<V>& b) const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC3OALOCK_FW(b)
                        return omni::geometry::vector3<V>(
                            this->m_sx,
                            this->m_sy,
                            this->m_sz,
                            (this->m_x + (-b.m_x)),
                            (this->m_y + (-b.m_y)),
                            (this->m_z + (-b.m_z))
                        );
                    }
                    return omni::geometry::vector3<V>(
                        this->m_sx,
                        this->m_sy,
                        this->m_sz,
                        (this->m_x + (-b.m_x)),
                        (this->m_y + (-b.m_y)),
                        (this->m_z + (-b.m_z))
                    );
                }

                omni::geometry::vector3<V> operator+(const omni::geometry::vector3<V>& b) const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC3OALOCK_FW(b)
                        return omni::geometry::vector3<V>(
                            this->m_sx,
                            this->m_sy,
                            this->m_sz,
                            (this->m_x + b.m_x),
                            (this->m_y + b.m_y),
                            (this->m_z + b.m_z)
                        );
                    }
                    return omni::geometry::vector3<V>(
                        this->m_sx,
                        this->m_sy,
                        this->m_sz,
                        (this->m_x + b.m_x),
                        (this->m_y + b.m_y),
                        (this->m_z + b.m_z)
                    );
                }

                // scalar multiplication
                omni::geometry::vector3<V> operator*(V scalar) const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return omni::geometry::vector3<V>(
                        this->m_sx,
                        this->m_sy,
                        this->m_sz,
                        (this->m_x * scalar),
                        (this->m_y * scalar),
                        (this->m_z * scalar)
                    );
                }

                // scalar division
                omni::geometry::vector3<V> operator/(V scalar) const
                {
                    OMNI_SAFE_VEC3ALOCK_FW
                    return omni::geometry::vector3<V>(
                        this->m_sx,
                        this->m_sy,
                        this->m_sz,
                        (this->m_x / scalar),
                        (this->m_y / scalar),
                        (this->m_z / scalar)
                    );
                }

                OMNI_MEMBERS_FW(omni::geometry::vector3<V>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::vector3<V>)

            private:
                V m_sx;
                V m_sy;
                V m_sz;
                V m_x;
                V m_y;
                V m_z;

                #if defined(OMNI_SAFE_VECTOR3)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                inline V _dot_product(const omni::geometry::vector3<V>& b) const
                {
                    return (this->_x() * b._x()) + (this->_y() * b._y()) + (this->_z() * b._z());
                }

                inline double _direction_x() const
                {
                    return omni::math::rad_to_deg(std::atan(this->_x() / this->_magnitude()));
                }

                inline double _direction_y() const
                {
                    return omni::math::rad_to_deg(std::atan(this->_y() / this->_magnitude()));
                }

                inline double _direction_z() const
                {
                    return omni::math::rad_to_deg(std::atan(this->_z() / this->_magnitude()));
                }

                inline V _magnitude() const
                {
                    return std::sqrt(
                        (this->_x() * this->_x()) + 
                        (this->_y() * this->_y()) + 
                        (this->_z() * this->_z())
                    );
                }

                inline V _x() const
                {
                    return (this->m_x - this->m_sx);
                }

                inline V _y() const
                {
                    return (this->m_y - this->m_sy);
                }

                inline V _z() const
                {
                    return (this->m_z - this->m_sz);
                }
        };

        typedef omni::geometry::vector3<float> vector3F_t;
        typedef omni::geometry::vector3<double> vector3D_t;
    }
}

namespace std {
    template < typename V >
    inline void swap(omni::geometry::vector3<V>& a, omni::geometry::vector3<V>& b)
    {
        a.swap(b);
    }
}

#endif // OMNI_VECTOR3_HPP
