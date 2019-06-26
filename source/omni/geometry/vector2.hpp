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
        class vector2
        {
            public:
                vector2() :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_x(), m_y()
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(const omni::geometry::vector2& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_x(cp.x()), m_y(cp.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }
                
                vector2(omni::geometry::point_t p) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_x(p.x()), m_y(p.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(omni::geometry::point64_t p) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_x(p.x()), m_y(p.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(omni::geometry::pointF_t p) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_x(p.x()), m_y(p.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                template < typename T >
                vector2(const omni::geometry::point2d<T>& p) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_x(p.x()), m_y(p.y())
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                template < typename T >
                vector2(const omni::math::dimensional<T, 2>& p) :
                    OMNI_CTOR_FW(omni::geometry::vector2)
                    m_x(p[0]), m_y(p[1])
                    OMNI_SAFE_VEC2MTX_FW
                {
                }

                vector2(double x, double y) :
                    m_x(x), m_y(y)
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

                double x() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->m_x;
                }

                double y() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return this->m_y;
                }

                void swap(vector2& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_VEC2ALOCK_FW
                        OMNI_SAFE_VEC2OALOCK_FW(o)
                        std::swap(this->m_x, o.m_x);
                        std::swap(this->m_y, o.m_y);
                    }
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_VEC2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_VEC2UNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_VEC2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
                    OMNI_SAFE_VEC2UNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_VEC2LOCK_FW
                    s << "{" << this->m_x << "," << this->m_y << "}";
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

                operator point_t() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return point_t(static_cast<int32_t>(this->m_x), static_cast<int32_t>(this->m_y));
                }

                operator pointF_t() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return pointF_t(static_cast<float>(this->m_x), static_cast<float>(this->m_y));
                }

                operator pointD_t() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return pointD_t(this->m_x, this->m_y);
                }

                bool operator==(const vector2& b) const
                {
                    if (this == &b) { return true; }
                    OMNI_SAFE_VEC2ALOCK_FW
                    OMNI_SAFE_VEC2OALOCK_FW(b)
                    return (
                        omni::math::are_equal<double>(this->m_x, b.m_x) &&
                        omni::math::are_equal<double>(this->m_y, b.m_y)
                    )
                    OMNI_EQUAL_FW(b);
                }

                vector2& operator=(const vector2& b)
                {
                    if (this != &b) {
                        OMNI_SAFE_VEC2ALOCK_FW
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        OMNI_ASSIGN_FW(b)
                        this->m_x = b.m_x;
                        this->m_y = b.m_y;
                    }
                    return *this;
                }

                vector2 operator-(const vector2& b) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        return vector2((b.m_x - this->m_x), (b.m_y - this->m_y));
                    }
                    return vector2((b.m_x - this->m_x), (b.m_y - this->m_y));
                }

                vector2 operator+(const vector2& b) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    if (this != &b) {
                        OMNI_SAFE_VEC2OALOCK_FW(b)
                        return vector2((this->m_x + b.m_x), (this->m_y + b.m_y));
                    }
                    return vector2((this->m_x + b.m_x), (this->m_y + b.m_y));
                }

                vector2 operator*(double d) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return vector2((this->m_x * d), (this->m_y * d));
                }

                vector2 operator/(double d) const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return vector2((this->m_x / d), (this->m_y / d));
                }

                vector2 unit_vector() const
                {
                    return *this / this->length();
                }

                double length() const
                {
                    OMNI_SAFE_VEC2ALOCK_FW
                    return std::sqrt((this->m_x * this->m_x) + (this->m_y * this->m_y));
                }
                
                template < typename T >
                static omni::geometry::point2d<T> calculate_point(const vector2& a, const vector2& b, double distance)
                {
                    vector2 ab = a - b;
                    return a + ab.unit_vector() * distance;
                }

                template < typename T >
                static omni::geometry::point2d<T> calculate_point(T x1, T y1, T x2, T y2, T distance)
                {
                    return omni::geometry::vector2::calculate_point<T>(
                        vector2(omni::geometry::point2d<T>(x1, y1)),
                        vector2(omni::geometry::point2d<T>(x2, y2)),
                        distance
                    );
                }

                OMNI_MEMBERS_FW(omni::geometry::vector2) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::vector2)

            private:
                double m_x;
                double m_y;

                #if defined(OMNI_SAFE_VECTOR2)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
        };
    }
}

namespace std {
    inline void swap(omni::geometry::vector2& o1, omni::geometry::vector2& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_VECTOR2_HPP
