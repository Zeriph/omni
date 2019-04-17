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
#if !defined(OMNI_GEOMETRY_SIZE_HPP)
#define OMNI_GEOMETRY_SIZE_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>

#if defined(OMNI_SAFE_GEO_SIZE)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_GSZDMTX_FW  ,m_mtx()
    #define OMNI_SAFE_GSZLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_GSZUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_GSZALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_GSZOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_GSZDMTX_FW
    #define OMNI_SAFE_GSZLOCK_FW
    #define OMNI_SAFE_GSZUNLOCK_FW
    #define OMNI_SAFE_GSZALOCK_FW 
    #define OMNI_SAFE_GSZOALOCK_FW(o) 
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class size
        {
            public:
                size() : 
                    OMNI_CTOR_FW(omni::geometry::size<T>)
                    m_w(0), m_h(0)
                    OMNI_SAFE_GSZDMTX_FW
                { }

                size(const omni::geometry::size<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_w(cp.m_w), m_h(cp.m_h)
                    OMNI_SAFE_GSZDMTX_FW
                { }

                size(T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::size<T>)
                    m_w(w), m_h(h)
                    OMNI_SAFE_GSZDMTX_FW
                { }

                ~size()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                T width() const
                {
                    OMNI_SAFE_GSZALOCK_FW
                    return this->m_w;
                }

                T height() const
                {
                    OMNI_SAFE_GSZALOCK_FW
                    return this->m_h;
                }

                bool empty() const
                {
                    OMNI_SAFE_GSZALOCK_FW
                    return this->m_w == 0 && this->m_h == 0;
                }

                void set_dimensions(T w, T h)
                {
                    OMNI_SAFE_GSZALOCK_FW
                    this->m_w = w;
                    this->m_h = h;
                }

                const omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_GSZLOCK_FW
                    s << "{" << this->m_w << "," << this->m_h << "}";
                    OMNI_SAFE_GSZUNLOCK_FW
                    return s.str();
                }

                const std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_GSZLOCK_FW
                    s << "{" << this->m_w << "," << this->m_h << "}";
                    OMNI_SAFE_GSZUNLOCK_FW
                    return s.str();
                }

                const std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_GSZLOCK_FW
                    s << "{" << this->m_w << "," << this->m_h << "}";
                    OMNI_SAFE_GSZUNLOCK_FW
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

                bool operator!=(const size<T>& val) const
                {
                    return !(*this == val);
                }
                
                size<T>& operator=(const size<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_GSZALOCK_FW
                        OMNI_SAFE_GSZOALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_w = val.m_w;
                        this->m_h = val.m_h;
                    }
                    return *this;
                }

                bool operator<(const size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZALOCK_FW
                    OMNI_SAFE_GSZOALOCK_FW(val)
                    return this->m_w < val.m_w && this->m_h < val.m_h;
                }

                bool operator<=(const size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZALOCK_FW
                    OMNI_SAFE_GSZOALOCK_FW(val)
                    return this->m_w <= val.m_w && this->m_h <= val.m_h;
                }

                bool operator>(const size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZALOCK_FW
                    OMNI_SAFE_GSZOALOCK_FW(val)
                    return this->m_w > val.m_w && this->m_h > val.m_h;
                }

                bool operator>=(const size<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_GSZALOCK_FW
                    OMNI_SAFE_GSZOALOCK_FW(val)
                    return this->m_w >= val.m_w && this->m_h >= val.m_h;
                }

                bool operator==(const size<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_GSZALOCK_FW
                    OMNI_SAFE_GSZOALOCK_FW(val)
                    return (this->m_w == val.m_w && this->m_h == val.m_h)
                    OMNI_EQUAL_FW(val);
                }

                size<T> operator+(const size<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE)
                        OMNI_SAFE_GSZALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZOALOCK_FW(val)
                            return size<T> ((this->m_w + val.m_w), (this->m_h + val.m_h));
                        } else {
                            return size<T> ((this->m_w + val.m_w), (this->m_h + val.m_h));
                        }
                    #else
                        return size<T>((this->m_w + val.m_w), (this->m_h + val.m_h));
                    #endif
                }

                size<T> operator-(const size<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE)
                        OMNI_SAFE_GSZALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZOALOCK_FW(val)
                            return size<T> ((this->m_w - val.m_w), (this->m_h - val.m_h));
                        } else {
                            return size<T> ((this->m_w - val.m_w), (this->m_h - val.m_h));
                        }
                    #else
                        return size<T>((this->m_w - val.m_w), (this->m_h - val.m_h));
                    #endif
                }

                size<T>& operator+=(const size<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE)
                        OMNI_SAFE_GSZALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZOALOCK_FW(val)
                            this->m_w += val.m_w;
                            this->m_h += val.m_h;
                        } else {
                            this->m_w += val.m_w;
                            this->m_h += val.m_h;
                        }
                    #else    
                        this->m_w += val.m_w;
                        this->m_h += val.m_h;
                    #endif
                    return *this;
                }

                size<T>& operator-=(const size<T>& val)
                {
                    #if defined(OMNI_SAFE_GEO_SIZE)
                        OMNI_SAFE_GSZALOCK_FW
                        if (this != &val) {
                            OMNI_SAFE_GSZOALOCK_FW(val)
                            this->m_w -= val.m_w;
                            this->m_h -= val.m_h;
                        } else {
                            this->m_w -= val.m_w;
                            this->m_h -= val.m_h;
                        }
                    #else    
                        this->m_w -= val.m_w;
                        this->m_h -= val.m_h;
                    #endif
                    return *this;
                }

                OMNI_MEMBERS_FW(omni::geometry::size<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::size<T>)

            private:
                T m_w;
                T m_h;
                #if defined(OMNI_SAFE_GEO_SIZE)
                    mutable omni::sync::basic_lock m_mtx;
                #endif
        };

        typedef omni::geometry::size<int32_t> size_t;
        typedef omni::geometry::size<int64_t> size64_t;
        typedef omni::geometry::size<float> sizeF_t;

        template < typename T >
        class size_raw
        {
            public:
                size_raw() : 
                    OMNI_CTOR_FW(omni::geometry::size_raw<T>)
                    width(0), height(0)
                { }

                size_raw(const omni::geometry::size_raw<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    width(cp.width), height(cp.height)
                { }

                size_raw(T w, T h) : 
                    OMNI_CTOR_FW(omni::geometry::size_raw<T>)
                    width(w), height(h)
                { }

                ~size_raw()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                bool empty() const { return this->width == 0 && this->height == 0; }

                const omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{" << this->width << "," << this->height << "}";
                    return s.str();
                }

                const std::string to_string() const
                {
                    std::stringstream s;
                    s << "{" << this->width << "," << this->height << "}";
                    return s.str();
                }

                const std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    s << "{" << this->width << "," << this->height << "}";
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

                bool operator!=(const size_raw< T >& val) const
                {
                    return !(*this == val);
                }
                
                size_raw<T>& operator=(const size_raw<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->width = val.width;
                        this->height = val.height;
                    }
                    return *this;
                }

                bool operator<(const size_raw<T>& val) const
                {
                    return this->width < val.width && this->height < val.height;
                }

                bool operator<=(const size_raw<T>& val) const
                {
                    return this->width <= val.width && this->height <= val.height;
                }

                bool operator>(const size_raw<T>& val) const
                {
                    return this->width > val.width && this->height > val.height;
                }

                bool operator>=(const size_raw<T>& val) const
                {
                    return this->width >= val.width && this->height >= val.height;
                }

                bool operator==(const size_raw< T >& val) const
                {
                    if (this == &val) { return true; }
                    return (this->width == val.width && this->height == val.height)
                    OMNI_EQUAL_FW(val);
                }

                size_raw<T> operator+(const size_raw<T>& val)
                {
                    return size<T>((this->width + val.width), (this->height + val.height));
                }

                size_raw<T> operator-(const size_raw<T>& val)
                {
                    return size<T>((this->width - val.width), (this->height - val.height));
                }

                size_raw<T>& operator+=(const size_raw<T>& val)
                {
                    this->width += val.width;
                    this->height += val.height;
                    return *this;
                }

                size_raw<T>& operator-=(const size_raw<T>& val)
                {
                    this->width -= val.width;
                    this->height -= val.height;
                    return *this;
                }

                OMNI_MEMBERS_FW(omni::geometry::size_raw<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::size_raw<T>)

                T width;

                T height;
        };

        typedef omni::geometry::size_raw<int32_t> raw_size_t;
        typedef omni::geometry::size_raw<int64_t> raw_size64_t;
        typedef omni::geometry::size_raw<float> raw_sizeF_t;
    }
}

#endif // OMNI_GEOMETRY_SIZE_HPP
