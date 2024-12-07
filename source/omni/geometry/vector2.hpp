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
#if !defined(OMNI_VECTOR2_HPP)
#define OMNI_VECTOR2_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/point2d.hpp>

#if defined(OMNI_SAFE_VECTOR2)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_VEC2MTX_FW  ,m_mtx()
    #define OMNI_SAFE_VEC2LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_VEC2UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_VEC2ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_VEC2OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_VEC2MTX_FW
    #define OMNI_SAFE_VEC2LOCK_FW
    #define OMNI_SAFE_VEC2UNLOCK_FW
    #define OMNI_SAFE_VEC2ALOCK_FW
    #define OMNI_SAFE_VEC2OALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename V >
        class vector2
        {
            public:
                typedef V coordinate_t;
                typedef omni::geometry::point2d<V> point2d_t;

                vector2() :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_sx(0.0), m_sy(0.0), m_x(), m_y()
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(const omni::geometry::vector2<V>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_sx(cp.start_x()), m_sy(cp.start_y()), m_x(cp.x()), m_y(cp.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                template < typename T >
                vector2(const omni::geometry::point2d<T>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_sx(0.0), m_sy(0.0), m_x(head.x()), m_y(head.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                template < typename T >
                vector2(const omni::geometry::point2d<T>& tail, const omni::geometry::point2d<T>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_sx(tail.x()), m_sy(tail.y()), m_x(head.x()), m_y(head.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                template < typename T >
                vector2(const omni::math::dimensional<T, 2>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_sx(0.0), m_sy(0.0), m_x(head[0]), m_y(head[1])
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                template < typename T >
                vector2(const omni::math::dimensional<T, 2>& tail, const omni::math::dimensional<T, 2>& head) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_sx(tail[0]), m_sy(tail[1]), m_x(head[0]), m_y(head[1])
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(V x, V y) :
                    m_sx(0.0), m_sy(0.0), m_x(x), m_y(y)
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(V start_x, V start_y, V x, V y) :
                    m_sx(start_x), m_sy(start_y), m_x(x), m_y(y)
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                ~vector2()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                double angle_between(const omni::geometry::vector2<V>& b)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return OMNI_RAD_TO_DEG((this->_dot_product(b) / (this->_magnitude() * b._magnitude())));
                }

                omni::geometry::vector2<V>& assign(V start_x, V start_y, V x, V y)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_sx = start_x;
                    this->m_sy = start_y;
                    this->m_x = x;
                    this->m_y = y;
                    return *this;
                }

                template < typename T >
                omni::geometry::vector2<V>& assign(const omni::geometry::point2d<T>& tail, const omni::geometry::point2d<T>& head)
                {
                    return this->assign(
                        static_cast<V>(tail.x()),
                        static_cast<V>(tail.y()),
                        static_cast<V>(head.x()),
                        static_cast<V>(head.y())
                    );
                }

                template < typename T >
                omni::geometry::vector2<V>& assign(const omni::math::dimensional<T, 2>& tail, const omni::math::dimensional<T, 2>& head)
                {
                    return this->assign(
                        static_cast<V>(tail[0]),
                        static_cast<V>(tail[1]),
                        static_cast<V>(head[0]),
                        static_cast<V>(head[1])
                    );
                }

                omni::geometry::vector2<V>& assign_head(V x, V y)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_x = x;
                    this->m_y = y;
                    return *this;
                }

                template < typename T >
                omni::geometry::vector2<V>& assign_head(const omni::geometry::point2d<T>& head)
                {
                    return this->assign_head(
                        static_cast<V>(head.x()),
                        static_cast<V>(head.y())
                    );
                }

                template < typename T >
                omni::geometry::vector2<V>& assign_head(const omni::math::dimensional<T, 2>& head)
                {
                    return this->assign_head(
                        static_cast<V>(head[0]),
                        static_cast<V>(head[1])
                    );
                }

                omni::geometry::vector2<V>& assign_tail(V start_x, V start_y)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_sx = start_x;
                    this->m_sy = start_y;
                    return *this;
                }

                template < typename T >
                omni::geometry::vector2<V>& assign_tail(const omni::geometry::point2d<T>& tail)
                {
                    return this->assign_tail(
                        static_cast<V>(tail.x()),
                        static_cast<V>(tail.y())
                    );
                }

                template < typename T >
                omni::geometry::vector2<V>& assign_tail(const omni::math::dimensional<T, 2>& tail)
                {
                    return this->assign_tail(
                        static_cast<V>(tail[0]),
                        static_cast<V>(tail[1])
                    );
                }

                V cross_product(const omni::geometry::vector2<V>& b) const
                {
                    // returns scalar since 2d
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        /*
                            3d
                            c.x = a.y * b.z − a.z * b.y
                            c.y = a.z * b.x − a.x * b.z
                            c.z = a.x * b.y − a.y * b.x
                            return vector3(((this->_y() * b._z()) - (this->_z() * b._y())),  // x
                                        ((this->_z() * b._x()) - (this->_x() * b._z())),  // y
                                        ((this->_x() * b._y()) - (this->_y() * b._x()))); // z

                            2d
                            cx = ay * 0 − 0 * by = 0
                            cy = 0 * bx − ax * 0 = 0
                            cz = ax * by − ay * bx = (this->m_x * b.m_y) - (this->m_y * b.m_x);
                        */
                        OMNI_BITS_WILL_MUL_OVER_FW(this->_x(), b._y())
                        OMNI_BITS_WILL_MUL_OVER_FW(this->_y(), b._x())
                        return (this->_x() * b._y()) - (this->_y() * b._x());
                    }
                    OMNI_BITS_WILL_MUL_OVER_FW(this->_x(), b._y())
                    OMNI_BITS_WILL_MUL_OVER_FW(this->_y(), b._x())
                    return (this->_x() * b._y()) - (this->_y() * b._x());
                }

                V dot_product(const omni::geometry::vector2<V>& b) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        return this->_dot_product(b);
                    }
                    return this->_dot_product(b);
                }

                /**
                 * Returns the direction as degrees
                 */
                double direction() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->_direction();
                }

                long double distance_from(const omni::geometry::vector2<V>& b)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        return std::sqrt(
                            ((b._x() - this->_x()) * (b._x() - this->_x())) + 
                            ((b._y() - this->_y()) * (b._y() - this->_y()))
                        );
                    }
                    return std::sqrt(
                        ((b._x() - this->_x()) * (b._x() - this->_x())) + 
                        ((b._y() - this->_y()) * (b._y() - this->_y()))
                    );
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_sx) ^
                        ((static_cast<int32_t>(this->m_sy) << 13) | (static_cast<int32_t>(this->m_sy) >> 19)) ^
                        ((static_cast<int32_t>(this->m_x) << 26) | (static_cast<int32_t>(this->m_x) >>  6)) ^
                        ((static_cast<int32_t>(this->m_y) <<  7) | (static_cast<int32_t>(this->m_y) >> 25))
                    );
                }

                point2d_t head() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return point2d_t(this->m_x, this->m_y);
                }

                bool is_standard_form() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return (
                        omni::math::are_equal<V>(this->m_sx, 0) &&
                        omni::math::are_equal<V>(this->m_sy, 0)
                    );
                }

                V length() const
                {
                    return this->magnitude();
                }

                V magnitude() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->_magnitude();
                }

                omni::geometry::vector2<V>& set_start_x(V start_x)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_sx = start_x;
                    return *this;
                }

                omni::geometry::vector2<V>& set_start_y(V start_y)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_sy = start_y;
                    return *this;
                }

                omni::geometry::vector2<V>& set_x(V x)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_x = x;
                    return *this;
                }

                omni::geometry::vector2<V>& set_y(V y)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_y = y;
                    return *this;
                }

                V start_x() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->m_sx;
                }

                V start_y() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->m_sy;
                }

                void swap(vector2& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_VEC2ALOCK_FW
                        OMNI_SAFE_VEC2OALOCK_FW(o)
                        std::swap(this->m_sx, o.m_sx);
                        std::swap(this->m_sy, o.m_sy);
                        std::swap(this->m_x, o.m_x);
                        std::swap(this->m_y, o.m_y);
                    }
                }

                point2d_t tail() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return point2d_t(this->m_sx, this->m_sy);
                }

                omni::geometry::vector2<V> to_standard_form() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return omni::geometry::vector2<V>(this->_x(), this->_y());
                }

                omni::geometry::vector2<V> unit_vector() const
                {
                    return *this / this->magnitude();
                }

                V x() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->m_x;
                }

                V y() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->m_y;
                }

                V x_component() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->_x();
                }

                V y_component() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->_y();
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_VEC2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << ";" << this->_direction() << "," << this->_magnitude() << "}";
                    OMNI_SAFE_VEC2UNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_VEC2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << ";" << this->_direction() << "," << this->_magnitude() << "}";
                    OMNI_SAFE_VEC2UNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_VEC2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << ";" << this->_direction() << "," << this->_magnitude() << "}";
                    OMNI_SAFE_VEC2UNLOCK_FW
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
                operator omni::geometry::point2d<T>() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return omni::geometry::point2d<T>(static_cast<T>(this->_x()), static_cast<T>(this->_y()));
                }

                bool operator==(const omni::geometry::vector2<V>& b) const
                {
                    if (this == &b) { return true; }
                    OMNI_SAFE_VEC2ALOCK_FW
                    OMNI_SAFE_VEC2OALOCK_FW(b)
                    return (
                        omni::math::are_equal(this->_magnitude(), b._magnitude()) &&
                        omni::math::are_equal(this->_direction(), b._direction())
                    )
                    OMNI_EQUAL_FW(b);
                }

                bool operator!=(const omni::geometry::vector2<V>& b) const
                {
                    return !(*this == b);
                }

                omni::geometry::vector2<V>& operator=(const omni::geometry::vector2<V>& b)
                {
                    if (this != &b) {
                        OMNI_SAFE_VEC2ALOCK_FW
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        OMNI_ASSIGN_FW(b)
                        this->m_sx = b.m_sx;
                        this->m_sy = b.m_sy;
                        this->m_x = b.m_x;
                        this->m_y = b.m_y;
                    }
                    return *this;
                }

                template < typename T >
                omni::geometry::vector2<V>& operator=(const omni::geometry::point2d<T>& point)
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    this->m_x = static_cast<V>(point.x());
                    this->m_y = static_cast<V>(point.y());
                    return *this;
                }

                omni::geometry::vector2<V> operator-(const omni::geometry::vector2<V>& b) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, (-b.m_x))
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, (-b.m_y))
                        return omni::geometry::vector2<V>(
                            this->m_sx,
                            this->m_sy,
                            (this->m_x + (-b.m_x)),
                            (this->m_y + (-b.m_y))
                        );
                    }
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, (-b.m_x))
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, (-b.m_y))
                    return omni::geometry::vector2<V>(
                        this->m_sx,
                        this->m_sy,
                        (this->m_x + (-b.m_x)),
                        (this->m_y + (-b.m_y))
                    );
                }

                omni::geometry::vector2<V> operator+(const omni::geometry::vector2<V>& b) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, b.m_x)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, b.m_y)
                        return omni::geometry::vector2<V>(
                            this->m_sx,
                            this->m_sy,
                            (this->m_x + b.m_x),
                            (this->m_y + b.m_y)
                        );
                    }
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_x, b.m_x)
                    OMNI_BITS_WILL_ADD_OVER_FW(this->m_y, b.m_y)
                    return omni::geometry::vector2<V>(
                        this->m_sx,
                        this->m_sy,
                        (this->m_x + b.m_x),
                        (this->m_y + b.m_y)
                    );
                }

                // scalar multiplication
                omni::geometry::vector2<V> operator*(V scalar) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_x, scalar)
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_y, scalar)
                    return omni::geometry::vector2<V>(
                        this->m_sx,
                        this->m_sy,
                        (this->m_x * scalar),
                        (this->m_y * scalar)
                    );
                }

                // scalar division
                omni::geometry::vector2<V> operator/(V scalar) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return omni::geometry::vector2<V>(
                        this->m_sx,
                        this->m_sy,
                        (this->m_x / scalar),
                        (this->m_y / scalar)
                    );
                }

                OMNI_MEMBERS_FW(omni::geometry::vector2<V>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::vector2<V>)

            private:
                V m_sx;
                V m_sy;
                V m_x;
                V m_y;

                #if defined(OMNI_SAFE_VECTOR2)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                inline V _dot_product(const omni::geometry::vector2<V>& b) const
                {
                    OMNI_BITS_WILL_MUL_OVER_FW(this->_x(), b._x())
                    OMNI_BITS_WILL_MUL_OVER_FW(this->_y(), b._y())
                    return (this->_x() * b._x()) + (this->_y() * b._y());
                }

                inline double _direction() const
                {
                    return omni::math::rad_to_deg(
                        std::atan(
                            this->_y() / this->_x()
                        )
                    );
                }

                inline V _magnitude() const
                {
                    OMNI_BITS_WILL_MUL_OVER_FW(this->_x(), this->_x())
                    OMNI_BITS_WILL_MUL_OVER_FW(this->_y(), this->_y())
                    return std::sqrt(
                        (this->_x() * this->_x()) +
                        (this->_y() * this->_y())
                    );
                }

                inline V _x() const
                {
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_x, this->m_sx)
                    return (this->m_x - this->m_sx);
                }

                inline V _y() const
                {
                    OMNI_BITS_WILL_SUB_UNDER_FW(this->m_y, this->m_sy)
                    return (this->m_y - this->m_sy);
                }
        };

        typedef omni::geometry::vector2<float> vector2F_t;
        typedef omni::geometry::vector2<double> vector2D_t;
    }
}

namespace std {
    template < typename V >
    inline void swap(omni::geometry::vector2<V>& a, omni::geometry::vector2<V>& b)
    {
        a.swap(b);
    }

    /*
    template < typename V >
    inline void swap(omni::geometry::immutable::vector2<V>& a, omni::geometry::immutable::vector2<V>& b)
    {
        a.swap(b);
    }
    */
}

#endif // OMNI_VECTOR2_HPP
