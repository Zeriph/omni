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
#if !defined(OMNI_COLOR_HPP)
#define OMNI_COLOR_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/string/util.hpp>

#if defined(OMNI_SAFE_COLOR)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_CLRDMTX_FW  ,m_mtx()
    #define OMNI_SAFE_CLRLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_CLRUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_CLRALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_CLROALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_CLRDMTX_FW
    #define OMNI_SAFE_CLRLOCK_FW
    #define OMNI_SAFE_CLRUNLOCK_FW
    #define OMNI_SAFE_CLRALOCK_FW
    #define OMNI_SAFE_CLROALOCK_FW(o) 
#endif

#if defined(OMNI_32BIT_COLOR)
    #define OMNI_CLR_INT_FW uint32_t
#else
    #define OMNI_CLR_INT_FW uint64_t
#endif

namespace omni {
    namespace drawing {
        template < typename BitDepth, typename RgbType, uint8_t BitSize = sizeof(BitDepth) * CHAR_BIT >
        class color
        {
            public:
                typedef BitDepth int_t;
                typedef RgbType rgb_t;

                color() : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(0), m_g(0), m_b(0), m_a(0), m_calc_alpha(0)
                    OMNI_SAFE_CLRDMTX_FW
                { }

                color(const omni::drawing::color<BitDepth, RgbType, BitSize>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_r(cp.m_r), m_g(cp.m_g), m_b(cp.m_b), m_a(cp.m_a), m_calc_alpha(cp.m_calc_alpha)
                    OMNI_SAFE_CLRDMTX_FW
                { }

                color(RgbType rgb) : 
                    OMNI_CTOR_FW(omni::drawing::color<T>)
                    m_r(0), m_g(0), m_b(0), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(0)
                    OMNI_SAFE_CLRDMTX_FW
                {
                    this->set_rgb(rgb);
                }

                color(RgbType rgb, bool calculate_alpha) : 
                    OMNI_CTOR_FW(omni::drawing::color<T>)
                    m_r(0), m_g(0), m_b(0), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(calculate_alpha ? 1 : 0)
                    OMNI_SAFE_CLRDMTX_FW
                {
                    this->set_rgb(rgb);
                }

                color(BitDepth r, BitDepth g, BitDepth b) : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(r), m_g(g), m_b(b), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(0)
                    OMNI_SAFE_CLRDMTX_FW
                { }

                color(BitDepth r, BitDepth g, BitDepth b, bool calculate_alpha) : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(r), m_g(g), m_b(b), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(calculate_alpha ? 1 : 0)
                    OMNI_SAFE_CLRDMTX_FW
                { }

                color(BitDepth r, BitDepth g, BitDepth b, BitDepth a) : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(r), m_g(g), m_b(b), m_a(a), m_calc_alpha(0)
                    OMNI_SAFE_CLRDMTX_FW
                { }

                color(BitDepth r, BitDepth g, BitDepth b, BitDepth a, bool calculate_alpha) : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(r), m_g(g), m_b(b), m_a(a), m_calc_alpha(calculate_alpha ? 1 : 0)
                    OMNI_SAFE_CLRDMTX_FW
                { }

                color(float hue, float saturation, float lightness) : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(0), m_g(0), m_b(0), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(0)
                    OMNI_SAFE_CLRDMTX_FW
                {
                    this->set_rgb(omni::drawing::color<BitDepth, RgbType, BitSize>::hsl_to_rgb(hue, saturation, lightness));
                }

                color(float hue, uint32_t saturation, uint32_t lightness) : 
                    OMNI_CTOR_FW(omni::drawing::color)
                    m_r(0), m_g(0), m_b(0), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(0)
                    OMNI_SAFE_CLRDMTX_FW
                {
                    this->set_rgb(omni::drawing::color<BitDepth, RgbType, BitSize>::hsl_to_rgb(hue, saturation, lightness));
                }

                ~color()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                BitDepth r() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_r;
                }

                BitDepth g() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_g;
                }

                BitDepth b() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_b;
                }

                BitDepth a() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_a;
                }

                float alpha() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return static_cast<float>(this->m_a) / std::numeric_limits<BitDepth>::max();
                }

                float brightness() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return omni::drawing::color<BitDepth, RgbType, BitSize>::brightness(this->m_r, this->m_g, this->m_b);
                }

                float hue() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return omni::drawing::color<BitDepth, RgbType, BitSize>::hue(this->m_r, this->m_g, this->m_b);
                }

                float saturation() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return omni::drawing::color<BitDepth, RgbType, BitSize>::saturation(this->m_r, this->m_g, this->m_b);
                }

                uint32_t bit_size() const
                {
                    return BitSize;
                }

                bool calculate_alpha() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_calc_alpha == 1);
                }

                BitDepth decrement_r()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return --this->m_r;
                }

                BitDepth decrement_g()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return --this->m_g;
                }

                BitDepth decrement_b()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return --this->m_b;
                }

                BitDepth decrement_a()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return --this->m_a;
                }

                BitDepth decrease_r(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_r -= val);
                }

                BitDepth decrease_g(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_g -= val);
                }

                BitDepth decrease_b(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_b -= val);
                }

                BitDepth decrease_a(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_a -= val);
                }
                
                BitDepth increment_r()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return ++this->m_r;
                }

                BitDepth increment_g()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return ++this->m_g;
                }

                BitDepth increment_b()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return ++this->m_b;
                }

                BitDepth increment_a()
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return ++this->m_a;
                }

                BitDepth increase_r(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_r += val);
                }

                BitDepth increase_g(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_g += val);
                }

                BitDepth increase_b(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_b += val);
                }

                BitDepth increase_a(BitDepth val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (this->m_a += val);
                }

                bool empty() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_r == 0 &&
                           this->m_g == 0 &&
                           this->m_b == 0 &&
                           this->m_a == 0;
                }

                bool equals(BitDepth r, BitDepth g, BitDepth b) const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_r == r &&
                           this->m_g == g &&
                           this->m_b == b;
                }

                bool equals(BitDepth r, BitDepth g, BitDepth b, BitDepth a) const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return this->m_r == r &&
                           this->m_g == g &&
                           this->m_b == b &&
                           this->m_a == a;
                }

                void set_alpha(float alpha)
                {
                    if (alpha <= 1.00 && alpha >= 0.00) {
                        OMNI_SAFE_CLRALOCK_FW
                        this->m_a = static_cast<BitDepth>(std::numeric_limits<BitDepth>::max() * alpha);
                    } else {
                        OMNI_ERR_FW(OMNI_ERR_RANGE_STR, omni::exceptions::invalid_range())
                    }
                }

                void set_calculate_alpha(bool calc)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    this->m_calc_alpha = (calc ? 1 : 0);
                }

                void set_rgb(BitDepth r, BitDepth g, BitDepth b)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    this->m_r = r;
                    this->m_g = g;
                    this->m_b = b;
                }

                void set_rgb(RgbType rgb)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    this->m_r = static_cast<BitDepth>(rgb >> (BitSize * 2));
                    this->m_g = static_cast<BitDepth>((rgb >> BitSize) ^
                                        (static_cast<RgbType>(this->m_r) << BitSize));
                    this->m_b = static_cast<BitDepth>(rgb ^ 
                                        (static_cast<RgbType>(this->m_g) << BitSize) ^ 
                                        (static_cast<RgbType>(this->m_r) << (BitSize * 2)));
                }

                void set_rgba(BitDepth r, BitDepth g, BitDepth b, BitDepth a)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    this->m_r = r;
                    this->m_g = g;
                    this->m_b = b;
                    this->m_a = a;
                }

                void set_rgba(RgbType rgba)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    this->m_r = static_cast<BitDepth>(rgba >> (BitSize * 3));
                    this->m_g = static_cast<BitDepth>((rgba >> (BitSize * 2)) ^
                                        (static_cast<RgbType>(this->m_r) << BitSize));
                    this->m_b = static_cast<BitDepth>((rgba >> BitSize) ^
                                        (static_cast<RgbType>(this->m_g) << BitSize) ^
                                        (static_cast<RgbType>(this->m_r) << (BitSize * 2)));
                    this->m_a = static_cast<BitDepth>(rgba ^ 
                                        (static_cast<RgbType>(this->m_b) << BitSize) ^
                                        (static_cast<RgbType>(this->m_g) << (BitSize * 2)) ^
                                        (static_cast<RgbType>(this->m_r) << (BitSize * 3)));
                }

                void set_argb(RgbType argb)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    this->m_a = static_cast<BitDepth>(argb >> (BitSize * 3));
                    this->m_r = static_cast<BitDepth>((argb >> (BitSize * 2)) ^
                                        (static_cast<RgbType>(this->m_a) << BitSize));
                    this->m_g = static_cast<BitDepth>((argb >> BitSize) ^
                                        (static_cast<RgbType>(this->m_r) << BitSize) ^ 
                                        (static_cast<RgbType>(this->m_a) << (BitSize * 2)));
                    this->m_b = static_cast<BitDepth>(argb ^
                                        (static_cast<RgbType>(this->m_g) << BitSize) ^
                                        (static_cast<RgbType>(this->m_r) << (BitSize * 2)) ^
                                        (static_cast<RgbType>(this->m_a) << (BitSize * 3)));
                }

                void swap(color<BitDepth, RgbType, BitSize>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_CLRALOCK_FW
                        OMNI_SAFE_CLROALOCK_FW(o)
                        std::swap(this->m_r, o.m_r);
                        std::swap(this->m_g, o.m_g);
                        std::swap(this->m_b, o.m_b);
                        std::swap(this->m_a, o.m_a);
                    }
                }

                RgbType to_rgb() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (static_cast<RgbType>(this->m_r) << (BitSize * 2)) ^
                           (static_cast<RgbType>(this->m_g) << BitSize) ^
                           static_cast<RgbType>(this->m_b);
                }

                RgbType to_rgba() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (static_cast<RgbType>(this->m_r) << (BitSize * 3)) ^
                           (static_cast<RgbType>(this->m_g) << (BitSize * 2)) ^
                           (static_cast<RgbType>(this->m_b) << BitSize) ^
                           static_cast<RgbType>(this->m_a);
                }

                RgbType to_argb() const
                {
                    OMNI_SAFE_CLRALOCK_FW
                    return (static_cast<RgbType>(this->m_a) << (BitSize * 3)) ^
                           (static_cast<RgbType>(this->m_r) << (BitSize * 2)) ^
                           (static_cast<RgbType>(this->m_g) << BitSize) ^
                           static_cast<RgbType>(this->m_b);
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_CLRLOCK_FW
                    s << std::hex << "{r:" << static_cast<uint64_t>(this->m_r) <<
                                     ",g:" << static_cast<uint64_t>(this->m_g) <<
                                     ",b:" << static_cast<uint64_t>(this->m_b) <<
                                     ",a:" << this->alpha() << "}";
                    OMNI_SAFE_CLRUNLOCK_FW
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_CLRLOCK_FW
                    s << std::hex << "{r:" << static_cast<uint64_t>(this->m_r) <<
                                     ",g:" << static_cast<uint64_t>(this->m_g) <<
                                     ",b:" << static_cast<uint64_t>(this->m_b) <<
                                     ",a:" << this->alpha() << "}";
                    OMNI_SAFE_CLRUNLOCK_FW
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_CLRLOCK_FW
                    s << std::hex << "{r:" << static_cast<uint64_t>(this->m_r) <<
                                     ",g:" << static_cast<uint64_t>(this->m_g) <<
                                     ",b:" << static_cast<uint64_t>(this->m_b) <<
                                     ",a:" << this->alpha() << "}";
                    OMNI_SAFE_CLRUNLOCK_FW
                    return s.str();
                }

                operator std::string() const { return this->to_string(); }

                operator std::wstring() const { return this->to_wstring(); }

                bool operator!=(const omni::drawing::color<BitDepth, RgbType, BitSize>& val) const
                {
                    return !(*this == val);
                }

                bool operator!=(RgbType val) const
                {
                    return !(*this == val);
                }
                
                omni::drawing::color<BitDepth, RgbType, BitSize>& operator=(const omni::drawing::color<BitDepth, RgbType, BitSize>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_CLRALOCK_FW
                        OMNI_SAFE_CLROALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_r = val.m_r;
                        this->m_g = val.m_g;
                        this->m_b = val.m_b;
                        this->m_a = val.m_a;
                    }
                    return *this;
                }

                omni::drawing::color<BitDepth, RgbType, BitSize>& operator=(RgbType val)
                {
                    this->set_rgb(val);
                    return *this;
                }

                bool operator<(const omni::drawing::color<BitDepth, RgbType, BitSize>& val) const
                {
                    if (this == &val) { return false; }
                    if (this->m_calc_alpha == 1) {
                        return this->to_rgba() < val.to_rgba();
                    }
                    return this->to_rgb() < val.to_rgb();
                }

                bool operator<(RgbType val) const
                {
                    if (this->m_calc_alpha == 1) {
                        return (this->to_rgba() < val);
                    }
                    return (this->to_rgb() < val);
                }

                bool operator>(const omni::drawing::color<BitDepth, RgbType, BitSize>& val) const
                {
                    if (this == &val) { return false; }
                    if (this->m_calc_alpha == 1) {
                        return this->to_rgba() > val.to_rgba();
                    }
                    return this->to_rgb() > val.to_rgb();
                }

                bool operator>(RgbType val) const
                {
                    if (this->m_calc_alpha == 1) {
                        return (this->to_rgba() > val);
                    }
                    return (this->to_rgb() > val);
                }

                bool operator==(const omni::drawing::color<BitDepth, RgbType, BitSize>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_CLRALOCK_FW
                    OMNI_SAFE_CLROALOCK_FW(val)
                    return (this->m_r == val.m_r &&
                            this->m_g == val.m_g &&
                            this->m_b == val.m_b &&
                            ((this->m_calc_alpha == 1) ? (this->m_a > val.m_a) : true))
                    OMNI_EQUAL_FW(val);
                }

                bool operator==(RgbType val) const
                {
                    if (this->m_calc_alpha == 1) {
                        return (this->to_rgba() == val);
                    }
                    return (this->to_rgb() == val);
                }

                omni::drawing::color<BitDepth, RgbType, BitSize> operator+(const omni::drawing::color<BitDepth, RgbType, BitSize>& val)
                {
                    #if defined(OMNI_SAFE_COLOR)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        omni::drawing::color<BitDepth, RgbType, BitSize> ret(
                            (this->m_r + val.m_r),
                            (this->m_g + val.m_g),
                            (this->m_b + val.m_b),
                            ((this->m_calc_alpha == 1) ? (this->m_a + val.m_a) : this->m_a),
                            (this->m_calc_alpha ? true : false)
                        );
                        if (this != &val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                        return ret;
                    #else
                        return omni::drawing::color<BitDepth, RgbType, BitSize>(
                            (this->m_r + val.m_r),
                            (this->m_g + val.m_g),
                            (this->m_b + val.m_b),
                            ((this->m_calc_alpha == 1) ? (this->m_a + val.m_a) : this->m_a),
                            (this->m_calc_alpha ? true : false)
                        );
                    #endif
                }

                omni::drawing::color<BitDepth, RgbType, BitSize> operator+(RgbType val)
                {
                    if (this->m_calc_alpha == 1) {
                        return omni::drawing::color<BitDepth, RgbType, BitSize>((this->to_rgba() + val), true);
                    }
                    return omni::drawing::color<BitDepth, RgbType, BitSize>((this->to_rgb() + val), false);
                }

                omni::drawing::color<BitDepth, RgbType, BitSize> operator-(const omni::drawing::color<BitDepth, RgbType, BitSize>& val)
                {
                    #if defined(OMNI_SAFE_COLOR)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        omni::drawing::color<BitDepth, RgbType, BitSize> ret(
                            (this->m_r - val.m_r),
                            (this->m_g - val.m_g),
                            (this->m_b - val.m_b),
                            ((this->m_calc_alpha == 1) ? (this->m_a - val.m_a) : this->m_a),
                            (this->m_calc_alpha ? true : false)
                        );
                        if (this != &val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                        return ret;
                    #else
                        return omni::drawing::color<BitDepth, RgbType, BitSize>(
                            (this->m_r - val.m_r),
                            (this->m_g - val.m_g),
                            (this->m_b - val.m_b),
                            ((this->m_calc_alpha == 1) ? (this->m_a - val.m_a) : this->m_a),
                            (this->m_calc_alpha ? true : false)
                        );
                    #endif
                }

                omni::drawing::color<BitDepth, RgbType, BitSize> operator-(RgbType val)
                {
                    if (this->m_calc_alpha == 1) {
                        return omni::drawing::color<BitDepth, RgbType, BitSize>((this->to_rgba() - val), true);
                    }
                    return omni::drawing::color<BitDepth, RgbType, BitSize>((this->to_rgb() - val), false);
                }

                omni::drawing::color<BitDepth, RgbType, BitSize>& operator+=(const omni::drawing::color<BitDepth, RgbType, BitSize>& val)
                {
                    #if defined(OMNI_SAFE_COLOR)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        this->m_r += val.m_r;
                        this->m_g += val.m_g;
                        this->m_b += val.m_b;
                        if (this->m_calc_alpha == 1) { this->m_a += val.m_a; }
                        if (this != & val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                    #else    
                        this->m_r += val.m_r;
                        this->m_g += val.m_g;
                        this->m_b += val.m_b;
                        if (this->m_calc_alpha == 1) { this->m_a += val.m_a; }
                    #endif
                    return *this;
                }

                omni::drawing::color<BitDepth, RgbType, BitSize>& operator+=(RgbType val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    if (this->m_calc_alpha == 1) {
                        RgbType rgba = (
                            (static_cast<RgbType>(this->m_r) << (BitSize * 3)) ^
                            (static_cast<RgbType>(this->m_g) << (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_b) << BitSize) ^
                            (this->m_a)
                        ) + val;
                        this->m_r = (rgba >> (BitSize * 3));
                        this->m_g = static_cast<BitDepth>((rgba >> (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_r) << BitSize));
                        this->m_b = static_cast<BitDepth>((rgba >> BitSize) ^
                            (static_cast<RgbType>(this->m_g) << BitSize) ^
                            (static_cast<RgbType>(this->m_r) << (BitSize * 2)));
                        this->m_a = static_cast<BitDepth>(rgba ^
                            (static_cast<RgbType>(this->m_b) << BitSize) ^
                            (static_cast<RgbType>(this->m_g) << (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_r) << (BitSize * 3)));
                    } else {
                        RgbType rgb = (
                            (static_cast<RgbType>(this->m_r) << (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_g) << BitSize) ^
                            static_cast<RgbType>(this->m_b)) + val;
                        this->m_r = static_cast<BitDepth>(rgb >> (BitSize * 2));
                        this->m_g = static_cast<BitDepth>((rgb >> BitSize) ^ (static_cast<RgbType>(this->m_r) << BitSize));
                        this->m_b = static_cast<BitDepth>(rgb ^
                            (static_cast<RgbType>(this->m_g) << BitSize) ^
                            (static_cast<RgbType>(this->m_r) << (BitSize * 2)));
                    }
                    return *this;
                }

                omni::drawing::color<BitDepth, RgbType, BitSize>& operator-=(const omni::drawing::color<BitDepth, RgbType, BitSize>& val)
                {
                    #if defined(OMNI_SAFE_COLOR)
                        this->m_mtx.lock();
                        if (this != &val) { val.m_mtx.lock(); }
                        this->m_r -= val.m_r;
                        this->m_g -= val.m_g;
                        this->m_b -= val.m_b;
                        if (this->m_calc_alpha == 1) { this->m_a -= val.m_a; }
                        if (this != & val) { val.m_mtx.unlock(); }
                        this->m_mtx.unlock();
                    #else    
                        this->m_r -= val.m_r;
                        this->m_g -= val.m_g;
                        this->m_b -= val.m_b;
                        if (this->m_calc_alpha == 1) { this->m_a -= val.m_a; }
                    #endif
                    return *this;
                }

                omni::drawing::color<BitDepth, RgbType, BitSize>& operator-=(RgbType val)
                {
                    OMNI_SAFE_CLRALOCK_FW
                    if (this->m_calc_alpha == 1) {
                        RgbType rgba = ((static_cast<RgbType>(this->m_r) << (BitSize * 3)) ^
                            (static_cast<RgbType>(this->m_g) << (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_b) << BitSize) ^
                            static_cast<RgbType>(this->m_a)) - val;
                        this->m_r = (rgba >> (BitSize * 3));
                        this->m_g = ((rgba >> (BitSize * 2)) ^ (static_cast<RgbType>(this->m_r) << BitSize));
                        this->m_b = ((rgba >> BitSize) ^
                            (static_cast<RgbType>(this->m_g) << BitSize) ^
                            (static_cast<RgbType>(this->m_r) << (BitSize * 2)));
                        this->m_a = (rgba ^
                            (static_cast<RgbType>(this->m_b) << BitSize) ^
                            (static_cast<RgbType>(this->m_g) << (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_r) << (BitSize * 3)));
                    } else {
                        RgbType rgb = ((static_cast<RgbType>(this->m_r) << (BitSize * 2)) ^
                            (static_cast<RgbType>(this->m_g) << BitSize) ^
                            static_cast<RgbType>(this->m_b)) - val;
                        this->m_r = (rgb >> (BitSize * 2));
                        this->m_g = ((rgb >> BitSize) ^ (static_cast<RgbType>(this->m_r) << BitSize));
                        this->m_b = (rgb ^
                            (static_cast<RgbType>(this->m_g) << BitSize) ^
                            (static_cast<RgbType>(this->m_r) << (BitSize * 2)));
                    }
                    return *this;
                }

                OMNI_MEMBERS_FW(omni::drawing::color<BitDepth, RgbType, BitSize>) // disposing,name,type(),hash()
                OMNI_OSTREAM_FW(omni::drawing::color<BitDepth, RgbType, BitSize>)

                // gets the L of the HSL
                static float brightness(BitDepth red, BitDepth green, BitDepth blue)
                {
                    // ((max + min) / 2) / BitDepth::max
                    return
                    (
                        (
                            static_cast<float>(std::max(std::max(red, green), blue) + std::min(std::min(red, green), blue))
                            / 2.0f
                        )
                        / std::numeric_limits<BitDepth>::max()
                    );
                }

                static uint32_t bits()
                {
                    return BitSize;
                }

                static omni::drawing::color<BitDepth, RgbType, BitSize> from_hsl(float hue, float saturation, float lightness)
                {
                    return omni::drawing::color<BitDepth, RgbType, BitSize>(hue, saturation, lightness);
                }

                static omni::drawing::color<BitDepth, RgbType, BitSize> from_hsl(float hue, uint32_t saturation, uint32_t lightness)
                {
                    return omni::drawing::color<BitDepth, RgbType, BitSize>(hue, saturation, lightness);
                }

                static omni::drawing::color<BitDepth, RgbType, BitSize> from_rgb(RgbType rgb)
                {
                    return omni::drawing::color<BitDepth, RgbType, BitSize>(rgb);
                }

                static omni::drawing::color<BitDepth, RgbType, BitSize> from_argb(RgbType argb)
                {
                    return omni::drawing::color<BitDepth, RgbType, BitSize>(argb, false, false);
                }

                static omni::drawing::color<BitDepth, RgbType, BitSize> from_rgba(RgbType rgba)
                {
                    return omni::drawing::color<BitDepth, RgbType, BitSize>(rgba, true, false);
                }

                // gets the H of the HSL (in degrees)
                static float hue(BitDepth red, BitDepth green, BitDepth blue)
                {
                    BitDepth cmax = std::max(std::max(red, green), blue);
                    BitDepth cmin = std::min(std::min(red, green), blue);
                    if (cmax == cmin) { return 0.0f; }
                    float ret = 0.0f;
                    if (cmax == red) {
                        ret = 60.0f * (std::fmod((static_cast<float>(green - blue) / (cmax - cmin)), 6.0f));
                    } else if (cmax == green) {
                        ret = 60.0f * ((static_cast<float>(blue - red) / (cmax - cmin)) + 2.0f);
                    } else if (cmax == blue) {
                        ret = 60.0f * ((static_cast<float>(red - green) / (cmax - cmin)) + 4.0f);
                    }
                    if (ret < 0.0f) { ret += 360.0f; }
                    return ret;
                }

                // gets the S of the HSL
                static float saturation(BitDepth red, BitDepth green, BitDepth blue)
                {
                    BitDepth cmax = std::max(std::max(red, green), blue);
                    BitDepth cmin = std::min(std::min(red, green), blue);
                    if (cmax == cmin) { return 0.0f; }
                    return 
                        (static_cast<float>(cmax - cmin) / std::numeric_limits<BitDepth>::max())
                        /
                        (1.0f - std::fabs((static_cast<float>(cmax + cmin) / std::numeric_limits<BitDepth>::max()) - 1.0f));
                }

                static RgbType hsl_to_rgb(float hue, float saturation, float luminance)
                {
                    if ((hue > 360.0f || hue < 0.0f) ||
                        (saturation > 1.0f || saturation < 0.0f) ||
                        (luminance > 1.0f || luminance < 0.0f))
                    {
                        OMNI_ERR_RETV_FW(OMNI_ERR_RANGE_STR, omni::exceptions::invalid_range(), 0)
                    }
                    if ((hue == 0.00f) && (saturation == 0.00f) && (luminance == 0.0f)) { return 0; }
                    BitDepth nmax = std::numeric_limits<BitDepth>::max();
                    float C = (1.0f - std::fabs((2.0f * luminance) - 1.0f)) * saturation;
                    float X = C * (1.0f - std::fabs(std::fmod((hue / 60.0f), 2.0f) - 1.0f));
                    float m = luminance - C / 2.0f;
                    float tr = 0.0f;
                    float tg = 0.0f;
                    float tb = 0.0f;
                    if (hue < 120.0f) {
                        if (hue < 60.0f) {
                            tr = C;
                            tg = X;
                        } else {
                            tr = X;
                            tg = C;
                        }
                    } else if (hue < 240.0f) {
                        if (hue < 180.0f) {
                            tg = C;
                            tb = X;
                        } else {
                            tg = X;
                            tb = C;
                        }
                    } else if (hue < 360.0f) {
                        if (hue < 300.0f) {
                            tr = X;
                            tb = C;
                        } else {
                            tr = C;
                            tb = X;
                        }
                    }
                    return (
                        (static_cast<BitDepth>(::ceilf((tr + m) * nmax)) << (BitSize * 2)) ^
                        (static_cast<BitDepth>(::ceilf((tg + m) * nmax)) << BitSize) ^
                        (static_cast<BitDepth>(::ceilf((tb + m) * nmax)))
                    );
                }

                static RgbType hsl_to_rgb(float hue, uint32_t saturation, uint32_t lightness)
                {
                    return omni::drawing::color<BitDepth, RgbType, BitSize>::hsl_to_rgb(
                        hue,
                        (static_cast<float>(saturation) / 100.0f),
                        (static_cast<float>(lightness) / 100.0f)
                    );
                }
                
            private:
                BitDepth m_r;
                BitDepth m_g;
                BitDepth m_b;
                BitDepth m_a;
                volatile OMNI_CLR_INT_FW m_calc_alpha;
                #if defined(OMNI_SAFE_COLOR)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                color(RgbType val, bool is_rgba, bool calc) : 
                    OMNI_CTOR_FW(omni::drawing::color<BitDepth>)
                    m_r(0), m_g(0), m_b(0), m_a(std::numeric_limits<BitDepth>::max()), m_calc_alpha(calc ? 1 : 0)
                    OMNI_SAFE_CLRDMTX_FW
                {
                    if (is_rgba) {
                        this->set_rgba(val);
                    } else {
                        this->set_argb(val);
                    }
                }
        };

        typedef omni::drawing::color<uint8_t, uint32_t> color_t;
        typedef omni::drawing::color<uint16_t, uint64_t> color64_t;
    }
}

namespace std {
    template < typename BitDepth, typename RgbType, uint8_t BitSize >
    inline void swap(omni::drawing::color<BitDepth, RgbType, BitSize>& o1, omni::drawing::color<BitDepth, RgbType, BitSize>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_COLOR_HPP
