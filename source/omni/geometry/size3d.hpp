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
#if !defined(OMNI_GEOMETRY_SIZE3D_HPP)
#define OMNI_GEOMETRY_SIZE3D_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/types/math_t.hpp>

#if defined(OMNI_SAFE_GEO_SIZE3D)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_GSZ3DMTX_FW  ,m_mtx()
    #define OMNI_SAFE_GSZ3LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_GSZ3UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_GSZ3ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_GSZ3OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_GSZ3DMTX_FW
    #define OMNI_SAFE_GSZ3LOCK_FW
    #define OMNI_SAFE_GSZ3UNLOCK_FW
    #define OMNI_SAFE_GSZ3ALOCK_FW 
    #define OMNI_SAFE_GSZ3OALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class size3d
        {
            public:
                typedef T value_t;

                size3d() : 
                    OMNI_CTOR_FW(omni::geometry::size3d<T>)
                    m_w(0), m_h(0), m_d(0)
                    OMNI_SAFE_GSZ3DMTX_FW
                { }

                size3d(const omni::geometry::size3d<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_w(cp.width()), m_h(cp.height()), m_d(cp.depth())
                    OMNI_SAFE_GSZ3DMTX_FW
                { }

                size3d(const omni::math::dimensional<T, 3>& cp) :
                    OMNI_CTOR_FW(omni::geometry::size3d<T>)
                    m_w(cp[0]), m_h(cp[1]), m_d(cp[2])
                    OMNI_SAFE_GSZ3DMTX_FW
                { }

                size3d(T w, T h, T d) : 
                    OMNI_CTOR_FW(omni::geometry::size3d<T>)
                    m_w(w), m_h(h), m_d(d)
                    OMNI_SAFE_GSZ3DMTX_FW
                { }

                ~size3d()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T area() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_w, this->m_h)
                    OMNI_BITS_WILL_MUL_OVER_FW(this->m_h, this->m_d)
                    return (this->m_w * this->m_h * this->m_d);
                }

                T width() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    return this->m_w;
                }

                T height() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    return this->m_h;
                }

                T depth() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    return this->m_d;
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_w) ^
                        ((static_cast<int32_t>(this->m_h) << 13) | (static_cast<int32_t>(this->m_h) >> 19)) ^
                        ((static_cast<int32_t>(this->m_d) << 26) | (static_cast<int32_t>(this->m_d) >>  6))
                    );
                }

                bool empty() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    return
                        omni::math::are_equal<T>(this->m_w, 0) &&
                        omni::math::are_equal<T>(this->m_h, 0) &&
                        omni::math::are_equal<T>(this->m_d, 0);
                }

                void set_dimensions(T w, T h, T d)
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    this->m_w = w;
                    this->m_h = h;
                    this->m_d = d;
                }

                void set_depth(T d)
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    this->m_d = d;
                }

                void set_height(T h)
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    this->m_h = h;
                }

                void set_width(T w)
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    this->m_w = w;
                }

                void swap(size3d<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_GSZ3ALOCK_FW
                        OMNI_SAFE_GSZ3OALOCK_FW(o)
                        std::swap(this->m_w, o.m_w);
                        std::swap(this->m_h, o.m_h);
                        std::swap(this->m_d, o.m_d);
                    }
                }

                omni::math::dimensional<T, 3> to_dimensional() const
                {
                    OMNI_SAFE_GSZ3ALOCK_FW
                    T vals[3] = { this->m_w, this->m_h, this->m_d };
                    return omni::math::dimensional<T, 3>(vals);
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_GSZ3LOCK_FW
                    s << "{" << this->m_w << "," << this->m_h << "," << this->m_d << "}";
                    OMNI_SAFE_GSZ3UNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_GSZ3LOCK_FW
                    s << "{" << this->m_w << "," << this->m_h << "," << this->m_d << "}";
                    OMNI_SAFE_GSZ3UNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_GSZ3LOCK_FW
                    s << "{" << this->m_w << "," << this->m_h << "," << this->m_d << "}";
                    OMNI_SAFE_GSZ3UNLOCK_FW
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

                operator omni::math::dimensional<T, 3>() const
                {
                    return this->to_dimensional();
                }

                bool operator!=(const omni::geometry::size3d<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::size3d<T>& operator=(const omni::geometry::size3d<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_GSZ3ALOCK_FW
                        OMNI_SAFE_GSZ3OALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_w = val.m_w;
                        this->m_h = val.m_h;
                        this->m_d = val.m_d;
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::size3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZ3ALOCK_FW
                    OMNI_SAFE_GSZ3OALOCK_FW(val)
                    return (this->m_w * this->m_h * this->m_d) < (val.m_w * val.m_h * val.m_d);
                }

                bool operator<=(const omni::geometry::size3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZ3ALOCK_FW
                    OMNI_SAFE_GSZ3OALOCK_FW(val)
                    return (this->m_w * this->m_h * this->m_d) <= (val.m_w * val.m_h * val.m_d);
                }

                bool operator>(const omni::geometry::size3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZ3ALOCK_FW
                    OMNI_SAFE_GSZ3OALOCK_FW(val)
                    return (this->m_w * this->m_h * this->m_d) > (val.m_w * val.m_h * val.m_d);
                }

                bool operator>=(const omni::geometry::size3d<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZ3ALOCK_FW
                    OMNI_SAFE_GSZ3OALOCK_FW(val)
                    return (this->m_w * this->m_h * this->m_d) >= (val.m_w * val.m_h * val.m_d);
                }

                bool operator==(const omni::geometry::size3d<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_GSZ3ALOCK_FW
                    OMNI_SAFE_GSZ3OALOCK_FW(val)
                    return (
                        omni::math::are_equal<T>(this->m_w, val.m_w) &&
                        omni::math::are_equal<T>(this->m_h, val.m_h) &&
                        omni::math::are_equal<T>(this->m_d, val.m_d)
                    )
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::size3d<T> operator+(const omni::geometry::size3d<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE3D)
                        OMNI_SAFE_GSZ3ALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZ3OALOCK_FW(val)
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_w, val.m_w)
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_h, val.m_h)
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_d, val.m_d)
                            return omni::geometry::size3d<T> ((this->m_w + val.m_w), (this->m_h + val.m_h), (this->m_d + val.m_d));
                        } else {
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_w, val.m_w)
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_h, val.m_h)
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_d, val.m_d)
                            return omni::geometry::size3d<T> ((this->m_w + val.m_w), (this->m_h + val.m_h), (this->m_d + val.m_d));
                        }
                    #else
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_w, val.m_w)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_h, val.m_h)
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_d, val.m_d)
                        return omni::geometry::size3d<T> ((this->m_w + val.m_w), (this->m_h + val.m_h), (this->m_d + val.m_d));
                    #endif
                }

                omni::geometry::size3d<T> operator-(const omni::geometry::size3d<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE3D)
                        OMNI_SAFE_GSZ3ALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZ3OALOCK_FW(val)
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_w, val.m_w)
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_h, val.m_h)
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_d, val.m_d)
                            return omni::geometry::size3d<T> ((this->m_w - val.m_w), (this->m_h - val.m_h), (this->m_d - val.m_d));
                        } else {
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_w, val.m_w)
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_h, val.m_h)
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_d, val.m_d)
                            return omni::geometry::size3d<T> ((this->m_w - val.m_w), (this->m_h - val.m_h), (this->m_d - val.m_d));
                        }
                    #else
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_w, val.m_w)
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_h, val.m_h)
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_d, val.m_d)
                        return omni::geometry::size3d<T> ((this->m_w - val.m_w), (this->m_h - val.m_h), (this->m_d - val.m_d));
                    #endif
                }

                omni::geometry::size3d<T>& operator+=(const omni::geometry::size3d<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE3D)
                        OMNI_SAFE_GSZ3ALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZ3OALOCK_FW(val)
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_w, val.m_w)
                            this->m_w += val.m_w;
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_h, val.m_h)
                            this->m_h += val.m_h;
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_d, val.m_d)
                            this->m_d += val.m_d;
                        } else {
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_w, val.m_w)
                            this->m_w += val.m_w;
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_h, val.m_h)
                            this->m_h += val.m_h;
                            OMNI_BITS_WILL_ADD_OVER_FW(this->m_d, val.m_d)
                            this->m_d += val.m_d;
                        }
                    #else
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_w, val.m_w)
                        this->m_w += val.m_w;
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_h, val.m_h)
                        this->m_h += val.m_h;
                        OMNI_BITS_WILL_ADD_OVER_FW(this->m_d, val.m_d)
                        this->m_d += val.m_d;
                    #endif
                    return *this;
                }

                omni::geometry::size3d<T>& operator-=(const omni::geometry::size3d<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE3D)
                        OMNI_SAFE_GSZ3ALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZ3OALOCK_FW(val)
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_w, val.m_w)
                            this->m_w -= val.m_w;
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_h, val.m_h)
                            this->m_h -= val.m_h;
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_d, val.m_d)
                            this->m_d -= val.m_d;
                        } else {
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_w, val.m_w)
                            this->m_w -= val.m_w;
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_h, val.m_h)
                            this->m_h -= val.m_h;
                            OMNI_BITS_WILL_SUB_UNDER_FW(this->m_d, val.m_d)
                            this->m_d -= val.m_d;
                        }
                    #else
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_w, val.m_w)
                        this->m_w -= val.m_w;
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_h, val.m_h)
                        this->m_h -= val.m_h;
                        OMNI_BITS_WILL_SUB_UNDER_FW(this->m_d, val.m_d)
                        this->m_d -= val.m_d;
                    #endif
                    return *this;
                }

                OMNI_MEMBERS_FW(omni::geometry::size3d<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::size3d<T>)

            private:
                T m_w;
                T m_h;
                T m_d;
                #if defined(OMNI_SAFE_GEO_SIZE3D)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
        };

        typedef omni::geometry::size3d<int32_t> size3d_t;
        typedef omni::geometry::size3d<int64_t> size3d_64_t;
        typedef omni::geometry::size3d<float> size3d_F_t;

        // DEV_NOTE: "raw" classes do not have checks, like arithmetic over/under flow, locks, etc.

        template < typename T >
        class raw_size3d
        {
            public:
                typedef T value_t;

                raw_size3d() : 
                    OMNI_CTOR_FW(omni::geometry::raw_size3d<T>)
                    width(0), height(0), depth(0)
                { }

                raw_size3d(const omni::geometry::raw_size3d<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    width(cp.width), height(cp.height), depth(cp.depth)
                { }

                raw_size3d(const omni::geometry::size3d<T>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_size3d<T>)
                    width(cp.width()), height(cp.height()), depth(cp.depth())
                { }

                raw_size3d(const omni::math::dimensional<T, 3>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_size3d<T>)
                    width(cp[0]), height(cp[1]), depth(cp[2])
                { }

                raw_size3d(T w, T h, T d) : 
                    OMNI_CTOR_FW(omni::geometry::raw_size3d<T>)
                    width(w), height(h), depth(d)
                { }

                ~raw_size3d()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T area() const
                {
                    return (this->width * this->height * this->depth);
                }

                bool empty() const
                {
                    return
                        omni::math::are_equal<T>(this->width, 0) &&
                        omni::math::are_equal<T>(this->height, 0) &&
                        omni::math::are_equal<T>(this->depth, 0);
                }

                int32_t hash_code() const
                {
                    return (
                        static_cast<int32_t>(this->width) ^
                        ((static_cast<int32_t>(this->height) << 13) | (static_cast<int32_t>(this->height) >> 19)) ^
                        ((static_cast<int32_t>(this->depth) << 26) | (static_cast<int32_t>(this->depth) >>  6))
                    );
                }

                void set_dimensions(T w, T h, T d)
                {
                    this->width = w;
                    this->height = h;
                    this->depth = d;
                }

                void set_depth(T d)
                {
                    this->depth = d;
                }

                void set_height(T h)
                {
                    this->height = h;
                }

                void set_width(T w)
                {
                    this->width = w;
                }

                void swap(raw_size3d<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->width, o.width);
                        std::swap(this->height, o.height);
                        std::swap(this->depth, o.depth);
                    }
                }

                omni::math::dimensional<T, 3> to_dimensional() const
                {
                    T vals[3] = { this->width, this->height, this->depth };
                    return omni::math::dimensional<T, 3>(vals);
                }

                omni::geometry::size3d<T> to_size3d() const
                {
                    return omni::geometry::size3d<T>(this->width, this->height, this->depth);
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->width << "," << this->height << "," << this->depth << "}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    s << "{" << this->width << "," << this->height << "," << this->depth << "}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    s << "{" << this->width << "," << this->height << "," << this->depth << "}";
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

                operator omni::math::dimensional<T, 3>() const
                {
                    return this->to_dimensional();
                }

                bool operator!=(const omni::geometry::raw_size3d<T>& val) const
                {
                    return !(*this == val);
                }
                
                omni::geometry::raw_size3d<T>& operator=(const omni::geometry::raw_size3d<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->width = val.width;
                        this->height = val.height;
                        this->depth = val.depth;
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::raw_size3d<T>& val) const
                {
                    return this->area() < val.area();
                }

                bool operator<=(const omni::geometry::raw_size3d<T>& val) const
                {
                    return this->area() <= val.area();
                }

                bool operator>(const omni::geometry::raw_size3d<T>& val) const
                {
                    return this->area() > val.area();
                }

                bool operator>=(const omni::geometry::raw_size3d<T>& val) const
                {
                    return this->area() >= val.area();
                }

                bool operator==(const omni::geometry::raw_size3d< T >& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        omni::math::are_equal<T>(this->width, val.width) &&
                        omni::math::are_equal<T>(this->height, val.height) &&
                        omni::math::are_equal<T>(this->depth, val.depth)
                    )
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::raw_size3d<T> operator+(const omni::geometry::raw_size3d<T>& val)
                {
                    return omni::geometry::raw_size3d<T>((this->width + val.width), (this->height + val.height), (this->depth + val.depth));
                }

                omni::geometry::raw_size3d<T> operator-(const omni::geometry::raw_size3d<T>& val)
                {
                    return omni::geometry::raw_size3d<T>((this->width - val.width), (this->height - val.height), (this->depth - val.depth));
                }

                omni::geometry::raw_size3d<T>& operator+=(const omni::geometry::raw_size3d<T>& val)
                {
                    this->width += val.width;
                    this->height += val.height;
                    this->depth += val.depth;
                    return *this;
                }

                omni::geometry::raw_size3d<T>& operator-=(const omni::geometry::raw_size3d<T>& val)
                {
                    this->width -= val.width;
                    this->height -= val.height;
                    this->depth -= val.depth;
                    return *this;
                }

                OMNI_MEMBERS_FW(omni::geometry::raw_size3d<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::raw_size3d<T>)

                T width;

                T height;

                T depth;
        };

        typedef omni::geometry::raw_size3d<int32_t> raw_size3d_t;
        typedef omni::geometry::raw_size3d<int64_t> raw_size3d_64_t;
        typedef omni::geometry::raw_size3d<float> raw_size3d_F_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::size3d<T>& o1, omni::geometry::size3d<T>& o2)
    {
        o1.swap(o2);
    }

    template < typename T >
    inline void swap(omni::geometry::raw_size3d<T>& o1, omni::geometry::raw_size3d<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_GEOMETRY_SIZE3D_HPP
