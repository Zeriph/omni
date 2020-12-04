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
#if !defined(OMNI_TRIANGLE_HPP)
#define OMNI_TRIANGLE_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/point2d.hpp>
#include <omni/geometry/circle.hpp>

#if defined(OMNI_SAFE_TRIANGLE)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_TRIMTX_FW  ,m_mtx()
    #define OMNI_SAFE_TRILOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_TRIUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_TRIALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_TRIOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_TRIMTX_FW
    #define OMNI_SAFE_TRILOCK_FW
    #define OMNI_SAFE_TRIUNLOCK_FW
    #define OMNI_SAFE_TRIALOCK_FW
    #define OMNI_SAFE_TRIOALOCK_FW(o) 
#endif

#if defined(OMNI_TRIANGLE_USE_SA)
    #define OMNI_TRI_SA_FW ,m_sides(), m_angle()
    #define OMNI_TRI_SACP_FW(cp) ,m_sides(cp.m_sides), m_angle(cp.m_angle)
    #define OMNI_TRI_SA_CALC_FW this->_recalc_sas()
#else
    #define OMNI_TRI_SA_FW
    #define OMNI_TRI_SACP_FW(cp)
    #define OMNI_TRI_SA_CALC_FW
#endif

namespace omni {
    namespace geometry {
        class triangle_side
        {
            public:
                typedef enum enum_t {
                    // Side A
                    A = 0,
                    // Side B
                    B = 1,
                    // Side C
                    C = 2
                } enum_t;
                
                static inline unsigned short COUNT()
                {
                    return 3;
                }
                
                static inline enum_t DEFAULT_VALUE()
                {
                    return A;
                }

                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::string& val, triangle_side& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, triangle_side& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                triangle_side() :
                    OMNI_CTOR_FW(omni::geometry::triangle_side)
                    m_val(DEFAULT_VALUE())
                { }

                triangle_side(const triangle_side& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                triangle_side(enum_t val) : 
                    OMNI_CTOR_FW(omni::geometry::triangle_side)
                    m_val(val)
                { }

                ~triangle_side()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const triangle_side& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                triangle_side& operator=(const triangle_side& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                triangle_side& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                triangle_side& operator=(int32_t val)
                {
                    if (!triangle_side::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const triangle_side& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const triangle_side& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const triangle_side& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::geometry::triangle_side) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::geometry::triangle_side)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    OMNI_ERR_FW("invalid enum parse", omni::exceptions::invalid_enum())
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, triangle_side& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(A)
                        OMNI_S2E_FW(B)
                        OMNI_S2E_FW(C)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(A);
                        OMNI_E2SS_FW(B);
                        OMNI_E2SS_FW(C);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        A ||
                        B ||
                        C
                    );
                }
        };

        template < typename T >
        class triangle
        {
            public:
                typedef T coordinate_t;

                triangle() : 
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(), m_b(), m_c(), m_base()
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                { }

                triangle(const omni::geometry::triangle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_a(cp.a()), m_b(cp.b()), m_c(cp.c()), m_base(cp.base_side())
                    OMNI_TRI_SACP_FW(cp)
                    OMNI_SAFE_TRIMTX_FW
                { }

                OMNI_EXPLICIT triangle(const omni::math::dimensional<T, 6>& cp) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(cp[0], cp[1]), m_b(cp[2], cp[3]), m_c(cp[4], cp[5]), m_base()
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::math::dimensional<T, 6>& cp, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(cp[0], cp[1]), m_b(cp[2], cp[3]), m_c(cp[4], cp[5]), m_base(base)
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a[0], a[1]), m_b(b[0], b[1]), m_c(c[0], c[1]), m_base()
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a[0], a[1]), m_b(b[0], b[1]), m_c(c[0], c[1]), m_base(base)
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a.x(), a.y()), m_b(b.x(), b.y()), m_c(c.x(), c.y()), m_base()
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a.x(), a.y()), m_b(b.x(), b.y()), m_c(c.x(), c.y()), m_base(base)
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a.x, a.y), m_b(b.x, b.y), m_c(c.x, c.y), m_base()
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a.x, a.y), m_b(b.x, b.y), m_c(c.x, c.y), m_base(base)
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(T x1, T y1, T x2, T y2, T x3, T y3) : 
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(x1, y1), m_b(x2, y2), m_c(x3, y3), m_base()
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                triangle(T x1, T y1, T x2, T y2, T x3, T y3, const omni::geometry::triangle_side& base) : 
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(x1, y1), m_b(x2, y2), m_c(x3, y3), m_base(base)
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    OMNI_TRI_SA_CALC_FW
                }

                ~triangle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                omni::geometry::raw_point2d<T> a() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->m_a;
                }

                double angle_a() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_angle_a();
                }

                double angle_b() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_angle_b();
                }

                double angle_c() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_angle_c();
                }

                double area() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_area();
                }

                omni::geometry::raw_point2d<T> b() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->m_b;
                }

                double base() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_base();
                }

                omni::geometry::triangle_side base_side() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->m_base;
                }

                omni::geometry::raw_point2d<T> c() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->m_c;
                }

                omni::geometry::point2d<double> centroid() const
                {
                    double x, y;
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_get_centroid<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }
                
                omni::geometry::point2d<double> circumcenter() const
                {
                    double x, y;
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_get_circumcenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }

                omni::geometry::circle<double> circle_from_circumcenter() const
                {
                    double x, y;
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_get_circumcenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    double a = this->_side_a();
                    double b = this->_side_b();
                    double c = this->_side_c();
                    return omni::geometry::circle<double>(x, y,
                        ((a * b * c) / std::sqrt((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c)))
                    );
                }

                omni::geometry::circle<double> circle_from_incenter() const
                {
                    double x, y;
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    return omni::geometry::circle<double>(x, y,
                        ((this->_area() * 2.0) / (this->_side_a() + this->_side_b() + this->_side_c()))
                    );
                }

                omni::math::shape_comparator compare(const omni::geometry::triangle<T>& tri) const
                {
                    if (this == &tri) { return omni::math::shape_comparator::SIMILAR_CONGRUENT; }
                    omni::math::shape_comparator ret = omni::math::shape_comparator::NOT_EQUAL;
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(tri)
                    double ta = this->_angle_a(); double oa = tri._angle_a();
                    double tb = this->_angle_b(); double ob = tri._angle_b();
                    double tc = this->_angle_c(); double oc = tri._angle_c();

                    if (
                        // a
                        (omni::math::are_equal(ta, oa) || omni::math::are_equal(ta, ob) || omni::math::are_equal(ta, oc)) &&
                        // b
                        (omni::math::are_equal(tb, oa) || omni::math::are_equal(tb, ob) || omni::math::are_equal(tb, oc)) &&
                        // c
                        (omni::math::are_equal(tc, oa) || omni::math::are_equal(tc, ob) || omni::math::are_equal(tc, oc))
                    )
                    {
                        ret = omni::math::shape_comparator::SIMILAR;
                    }
                    
                    ta = this->_side_a(); oa = tri._side_a();
                    tb = this->_side_b(); ob = tri._side_b();
                    tc = this->_side_c(); oc = tri._side_c();

                    if (
                        // a
                        (omni::math::are_equal(ta, oa) || omni::math::are_equal(ta, ob) || omni::math::are_equal(ta, oc)) &&
                        // b
                        (omni::math::are_equal(tb, oa) || omni::math::are_equal(tb, ob) || omni::math::are_equal(tb, oc)) &&
                        // c
                        (omni::math::are_equal(tc, oa) || omni::math::are_equal(tc, ob) || omni::math::are_equal(tc, oc))
                    )
                    {
                        ret |= omni::math::shape_comparator::CONGRUENT;
                    }

                    return ret;
                }

                bool contains(T x, T y) const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return omni::math::triangle_contains_point(
                        x, y,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                bool contains(const omni::math::dimensional<T, 2>& point) const
                {
                    return this->contains(point[0], point[1]);
                }

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::raw_point2d<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }

                bool contains(const omni::geometry::triangle<T>& tri) const
                {
                    if (&tri == this) { return true; }
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(tri)
                    return
                        omni::math::triangle_contains_point(
                            tri.m_a.x, tri.m_a.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y
                        ) &&
                        omni::math::triangle_contains_point(
                            tri.m_b.x, tri.m_b.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y
                        ) &&
                        omni::math::triangle_contains_point(
                            tri.m_c.x, tri.m_c.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y
                        );
                }

                void deflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"))
                    }
                    OMNI_SAFE_TRIALOCK_FW
                    double factor = percent / 100.0;
                    double x, y;
                    omni::math::triangle_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    omni::math::extend_line<double>(x, y, this->m_a.x, this->m_a.y, (omni::math::distance_between_2_points(x, y, this->m_a.x, this->m_a.y) * factor), this->m_a.x, this->m_a.y);
                    omni::math::extend_line<double>(x, y, this->m_b.x, this->m_b.y, (omni::math::distance_between_2_points(x, y, this->m_b.x, this->m_b.y) * factor), this->m_b.x, this->m_b.y);
                    omni::math::extend_line<double>(x, y, this->m_c.x, this->m_c.y, (omni::math::distance_between_2_points(x, y, this->m_c.x, this->m_c.y) * factor), this->m_c.x, this->m_c.y);
                    OMNI_TRI_SA_CALC_FW
                }

                bool empty() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->m_a.empty() &&
                           this->m_b.empty() &&
                           this->m_c.empty()
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        &&
                        omni::math::are_equal(m_sides[0], 0) &&
                        omni::math::are_equal(m_sides[1], 0) &&
                        omni::math::are_equal(m_sides[2], 0) &&

                        omni::math::are_equal(m_angle[0], 0) &&
                        omni::math::are_equal(m_angle[1], 0) &&
                        omni::math::are_equal(m_angle[2], 0)
                    #endif
                    ;
                }

                bool empty_size() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return (
                        (this->m_a == this->m_b) ||
                        (this->m_a == this->m_c) ||
                        (this->m_b == this->m_c)
                    );
                }

                bool equals(T ax, T ay, T bx, T by, T cx, T cy) const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return
                        omni::math::are_equal(this->m_a.x, ax) &&
                        omni::math::are_equal(this->m_a.y, ay) &&
                        omni::math::are_equal(this->m_b.x, bx) &&
                        omni::math::are_equal(this->m_b.y, by) &&
                        omni::math::are_equal(this->m_c.x, cx) &&
                        omni::math::are_equal(this->m_c.y, cy);
                }

                bool equals(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c) const
                {
                    return this->equals(a[0], a[1], b[0], b[1], c[0], c[1]);
                }

                bool equals(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c) const
                {
                    return this->equals(a.x(), a.y(), b.x(), b.y(), c.x(), c.y());
                }

                bool equals(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c) const
                {
                    return this->equals(a.x, a.y, b.x, b.y, c.x, c.y);
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return (
                        static_cast<int32_t>(this->m_base.value()) ^ 
                        m_a.hash_code() ^ m_b.hash_code() ^ m_c.hash_code()
                    );
                }

                double height() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return (this->_area() * 2.0) / this->_base();
                }

                omni::geometry::point2d<double> incenter() const
                {
                    double x, y;
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }

                void inflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"))
                    }
                    OMNI_SAFE_TRIALOCK_FW
                    double factor = percent / 100.0;
                    double x, y;
                    omni::math::triangle_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        x, y);
                    omni::math::extend_line<double>(x, y, this->m_a.x, this->m_a.y, (omni::math::distance_between_2_points(x, y, this->m_a.x, this->m_a.y) * factor), this->m_a.x, this->m_a.y);
                    omni::math::extend_line<double>(x, y, this->m_b.x, this->m_b.y, (omni::math::distance_between_2_points(x, y, this->m_b.x, this->m_b.y) * factor), this->m_b.x, this->m_b.y);
                    omni::math::extend_line<double>(x, y, this->m_c.x, this->m_c.y, (omni::math::distance_between_2_points(x, y, this->m_c.x, this->m_c.y) * factor), this->m_c.x, this->m_c.y);
                    OMNI_TRI_SA_CALC_FW
                }

                void intersect(const omni::geometry::triangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::raw_point2d<T> a = r2.a();
                    omni::geometry::raw_point2d<T> b = r2.b();
                    omni::geometry::raw_point2d<T> c = r2.c();
                    if (this->intersects_with(r2)) {
                        OMNI_SAFE_TRIALOCK_FW
                        if (this->m_a.x < a.x) { this->m_a.x = a.x; }
                        if (this->m_a.y < a.y) { this->m_a.y = a.y; }
                        if (this->m_b.x < b.x) { this->m_b.x = b.x; }
                        if (this->m_b.y < b.y) { this->m_b.y = b.y; }
                        if (this->m_c.x < c.x) { this->m_c.x = c.x; }
                        if (this->m_c.y < c.y) { this->m_c.y = c.y; }
                        OMNI_TRI_SA_CALC_FW
                    } else {
                        OMNI_SAFE_TRIALOCK_FW
                        this->m_a.x = 0; this->m_a.y = 0;
                        this->m_b.x = 0; this->m_b.y = 0;
                        this->m_c.x = 0; this->m_c.y = 0;
                        #if defined(OMNI_TRIANGLE_USE_SA)
                            std::memset(this->m_sides, 0, sizeof(this->m_sides));
                            std::memset(this->m_angle, 0, sizeof(this->m_angle));
                        #endif
                    }
                }

                bool intersects_with(const omni::geometry::triangle<T>& tri) const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(tri)
                    return omni::math::triangle_intersects(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        tri.m_a.x, tri.m_a.y,
                        tri.m_b.x, tri.m_b.y,
                        tri.m_c.x, tri.m_c.y
                    );
                }

                omni::math::triangle_measure measure() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    bool ab = omni::math::are_equal(this->_side_a(), this->_side_b());
                    bool bc = omni::math::are_equal(this->_side_b(), this->_side_c());
                    bool ac = omni::math::are_equal(this->_side_a(), this->_side_c());
                    if (ab && bc) {
                        return omni::math::triangle_measure::EQUILATERAL;
                    }
                    if (ab || bc || ac) {
                        return omni::math::triangle_measure::ISOSCELES;
                    }
                    return omni::math::triangle_measure::SCALENE;
                }

                double perimeter() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_side_a() + this->_side_b() + this->_side_c();
                }

                void rotate_on_a(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_abc(
                        degrees, this->m_a.x, this->m_a.y, dir,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_on_b(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_abc(
                        degrees, this->m_b.x, this->m_b.y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_on_c(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_abc(
                        degrees, this->m_c.x, this->m_c.y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y
                    );
                }

                void rotate_centroid(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_centroid(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_circumcenter(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_incenter(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_incenter(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_origin(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_origin(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_rotate_point(
                        degrees, x, y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void reflect()
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_reflect(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                double semiperimeter() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return (this->_side_a() + this->_side_b() + this->_side_c()) / 2.0;
                }

                void set_base(const omni::geometry::triangle_side& base)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    this->m_base = base;
                }

                double side_a() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_side_a();
                }

                double side_b() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_side_b();
                }

                double side_c() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return this->_side_c();
                }

                void swap(omni::geometry::triangle<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_TRIALOCK_FW
                        OMNI_SAFE_TRIOALOCK_FW(o)
                        std::swap(this->m_a, o.m_a);
                        std::swap(this->m_b, o.m_b);
                        std::swap(this->m_c, o.m_c);
                        #if defined(OMNI_TRIANGLE_USE_SA)
                            std::swap(this->m_sides, o.m_sides);
                            std::swap(this->m_angle, o.m_angle);
                        #endif
                    }
                }

                void translate_xy(T x, T y)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_translate_xy(
                        x, y,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void translate_angle(double degrees, T distance)
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::math::triangle_translate_angle(
                        degrees, distance,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_TRIALOCK_FW
                    s << "{[A:" << this->m_a << "],[B:" << this->m_b << "],[C:" << this->m_c << "]}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_TRIALOCK_FW
                    s << "{[A:" << this->m_a << "],[B:" << this->m_b << "],[C:" << this->m_c << "]}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_TRIALOCK_FW
                    s << "{[A:" << this->m_a << "],[B:" << this->m_b << "],[C:" << this->m_c << "]}";
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
                
                bool operator!=(const omni::geometry::triangle<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator==(const omni::geometry::triangle<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(val)
                    return (
                        (this->m_a == val.m_a) &&
                        (this->m_b == val.m_b) &&
                        (this->m_c == val.m_c))
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::triangle<T>& operator=(const omni::geometry::triangle<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_TRIALOCK_FW
                        OMNI_SAFE_TRIOALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_a = val.m_a;
                        this->m_b = val.m_b;
                        this->m_c = val.m_c;
                        this->m_base = val.m_base;
                        OMNI_TRI_SA_CALC_FW
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(val)
                    return (this->m_a < val.m_a) &&
                           (this->m_b < val.m_b) &&
                           (this->m_c < val.m_c);
                }

                bool operator<=(const omni::geometry::triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(val)
                    return (this->m_a <= val.m_a) &&
                           (this->m_b <= val.m_b) &&
                           (this->m_c <= val.m_c);
                }

                bool operator>(const omni::geometry::triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(val)
                    return (this->m_a > val.m_a) &&
                           (this->m_b > val.m_b) &&
                           (this->m_c > val.m_c);
                }

                bool operator>=(const omni::geometry::triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_TRIALOCK_FW
                    OMNI_SAFE_TRIOALOCK_FW(val)
                    return (this->m_a >= val.m_a) &&
                           (this->m_b >= val.m_b) &&
                           (this->m_c >= val.m_c);
                }

                omni::geometry::triangle<T> operator+(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::geometry::triangle<T> ret(*this);
                    ret.translate_xy(val.x(), val.y());
                    return ret;
                }

                omni::geometry::triangle<T> operator-(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    omni::geometry::triangle<T> ret(*this);
                    ret.translate_xy(-val.x(), -val.y());
                    return ret;
                }

                omni::geometry::triangle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->translate_xy(val.x(), val.y());
                    return *this;
                }

                omni::geometry::triangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->translate_xy(val.x(), val.y());
                    return *this;
                }

                static omni::geometry::triangle<T> deflate(const omni::geometry::triangle<T>& tri, double percent)
                {
                    return omni::geometry::triangle<T>(tri, percent, true);
                }

                static omni::geometry::triangle<T> inflate(const omni::geometry::triangle<T>& tri, double percent)
                {
                    return omni::geometry::triangle<T>(tri, percent, false);
                }

                static omni::geometry::triangle<T> intersect(const omni::geometry::triangle<T>& a, const omni::geometry::triangle<T>& b)
                {
                    return omni::geometry::triangle<T>(a, b);
                }

                OMNI_MEMBERS_FW(omni::geometry::triangle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::triangle<T>)

            private:
                omni::geometry::raw_point2d<T> m_a;
                omni::geometry::raw_point2d<T> m_b;
                omni::geometry::raw_point2d<T> m_c;
                omni::geometry::triangle_side m_base;
                #if defined(OMNI_TRIANGLE_USE_SA)
                    double m_sides[3];
                    double m_angle[3];
                #endif
                #if defined(OMNI_SAFE_TRIANGLE)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                triangle(const omni::geometry::triangle<T>& a, const omni::geometry::triangle<T>& b) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a.a()), m_b(a.b()), m_c(a.c()), m_base(a.base_side())
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    this->intersect(b);
                }

                triangle(const omni::geometry::triangle<T>& a, double percent, bool deflate) :
                    OMNI_CTOR_FW(omni::geometry::triangle<T>)
                    m_a(a.a()), m_b(a.b()), m_c(a.c()), m_base(a.base_side())
                    OMNI_TRI_SA_FW
                    OMNI_SAFE_TRIMTX_FW
                {
                    if (deflate) {
                        this->deflate(percent);
                    } else {
                        this->inflate(percent);
                    }
                }

                #if defined(OMNI_TRIANGLE_USE_SA)
                    void _recalc_sas()
                    {
                        this->m_sides[0] = this->_calc_side_a();
                        this->m_sides[1] = this->_calc_side_b();
                        this->m_sides[2] = this->_calc_side_c();

                        this->m_angle[0] = omni::math::calculate_angle(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                        this->m_angle[1] = omni::math::calculate_angle(this->m_b.x, this->m_b.y, this->m_a.x, this->m_a.y, this->m_c.x, this->m_c.y);
                        this->m_angle[2] = omni::math::calculate_angle(this->m_c.x, this->m_c.y, this->m_b.x, this->m_b.y, this->m_a.x, this->m_a.y);
                    }
                #endif

                double _area() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return omni::math::area_of_triangle(this->m_angle[0], this->m_sides[1], this->m_sides[2]);
                    #else
                        return omni::math::area_of_triangle(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                    #endif
                }

                double _angle_a() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return this->m_angle[0];
                    #else
                        return omni::math::calculate_angle(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                    #endif
                }

                double _angle_b() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return this->m_angle[1];
                    #else
                        return omni::math::calculate_angle(this->m_b.x, this->m_b.y, this->m_a.x, this->m_a.y, this->m_c.x, this->m_c.y);
                    #endif
                }

                double _angle_c() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return this->m_angle[2];
                    #else
                        return omni::math::calculate_angle(this->m_c.x, this->m_c.y, this->m_b.x, this->m_b.y, this->m_a.x, this->m_a.y);
                    #endif
                }

                double _base() const
                {
                    switch (this->m_base) {
                        case omni::geometry::triangle_side::A:
                            #if defined(OMNI_TRIANGLE_USE_SA)
                                return this->m_sides[0];
                            #else
                                return this->_side_a();
                            #endif
                        case omni::geometry::triangle_side::B:
                            #if defined(OMNI_TRIANGLE_USE_SA)
                                return this->m_sides[1];
                            #else
                                return this->_side_b();
                            #endif
                        case omni::geometry::triangle_side::C:
                            #if defined(OMNI_TRIANGLE_USE_SA)
                                return this->m_sides[2];
                            #else
                                return this->_side_c();
                            #endif
                        default: break;
                    }
                    return -1.0; // invalid base
                }

                double _calc_side_a() const
                {
                    if (this->m_b >= this->m_c) {
                        return omni::math::distance_between_2_points(this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                    }
                    return omni::math::distance_between_2_points(this->m_c.x, this->m_c.y, this->m_b.x, this->m_b.y);
                }

                double _calc_side_b() const
                {
                    if (this->m_a >= this->m_c) {
                        return omni::math::distance_between_2_points(this->m_a.x, this->m_a.y, this->m_c.x, this->m_c.y);
                    }
                    return omni::math::distance_between_2_points(this->m_c.x, this->m_c.y, this->m_a.x, this->m_a.y);
                }

                double _calc_side_c() const
                {
                    if (this->m_a >= this->m_b) {
                        return omni::math::distance_between_2_points(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y);
                    }
                    return omni::math::distance_between_2_points(this->m_b.x, this->m_b.y, this->m_a.x, this->m_a.y);
                }

                inline double _side_a() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return this->m_sides[0];
                    #else    
                        return this->_calc_side_a();
                    #endif
                }

                inline double _side_b() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return this->m_sides[1];
                    #else    
                        return this->_calc_side_b();
                    #endif
                }

                inline double _side_c() const
                {
                    #if defined(OMNI_TRIANGLE_USE_SA)
                        return this->m_sides[2];
                    #else    
                        return this->_calc_side_c();
                    #endif
                }
        };

        typedef omni::geometry::triangle<int32_t> triangle_t;
        typedef omni::geometry::triangle<int64_t> triangle64_t;
        typedef omni::geometry::triangle<float> triangleF_t;
        typedef omni::geometry::triangle<double> triangleD_t;

        template < typename T >
        class raw_triangle
        {
            public:
                typedef T coordinate_t;

                raw_triangle() : 
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(), b(), c(), base_side()
                { }

                raw_triangle(const omni::geometry::raw_triangle<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    a(cp.a), b(cp.b), c(cp.c), base_side(cp.base_side)
                { }

                raw_triangle(const omni::geometry::triangle<T>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(cp.a()), b(cp.b()), c(cp.c()), base_side(cp.base_side())
                { }

                raw_triangle(const omni::math::dimensional<T, 6>& cp) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(cp[0], cp[1]), b(cp[2], cp[3]), c(cp[4], cp[5]), base_side()
                { }

                raw_triangle(const omni::geometry::triangle_side& base) : 
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(), b(), c(), base_side(base)
                { }

                raw_triangle(const omni::math::dimensional<T, 6>& cp, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(cp[0], cp[1]), b(cp[2], cp[3]), c(cp[4], cp[5]), base_side(base)
                { }

                raw_triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a[0], a[1]), b(b[0], b[1]), c(c[0], c[1]), base_side()
                { }

                raw_triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a[0], a[1]), b(b[0], b[1]), c(c[0], c[1]), base_side(base)
                { }

                raw_triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a.x(), a.y()), b(b.x(), b.y()), c(c.x(), c.y()), base_side()
                { }

                raw_triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a.x(), a.y()), b(b.x(), b.y()), c(c.x(), c.y()), base_side(base)
                { }

                raw_triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a.x, a.y), b(b.x, b.y), c(c.x, c.y), base_side()
                { }

                raw_triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::triangle_side& base) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a.x, a.y), b(b.x, b.y), c(c.x, c.y), base_side(base)
                { }

                raw_triangle(T x1, T y1, T x2, T y2, T x3, T y3) : 
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(x1, y1), b(x2, y2), c(x3, y3), base_side()
                { }

                raw_triangle(T x1, T y1, T x2, T y2, T x3, T y3, const omni::geometry::triangle_side& base) : 
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(x1, y1), b(x2, y2), c(x3, y3), base_side(base)
                { }

                ~raw_triangle()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                double angle_a() const
                {
                    return this->_angle_a();
                }

                double angle_b() const
                {
                    return this->_angle_b();
                }

                double angle_c() const
                {
                    return this->_angle_c();
                }

                double area() const
                {
                    return this->_area();
                }
                
                double base() const
                {
                    return this->_base();
                }

                omni::geometry::point2d<double> centroid() const
                {
                    double x, y;
                    omni::math::triangle_get_centroid<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }
                
                omni::geometry::point2d<double> circumcenter() const
                {
                    double x, y;
                    omni::math::triangle_get_circumcenter<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }

                omni::geometry::circle<double> circle_frocircumcenter() const
                {
                    double x, y;
                    omni::math::triangle_get_circumcenter<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    double _a = this->_side_a();
                    double _b = this->_side_b();
                    double _c = this->_side_c();
                    return omni::geometry::circle<double>(x, y,
                        ((_a * _b * _c) / std::sqrt((_a + _b + _c) * (_b + _c - _a) * (_c + _a - _b) * (_a + _b - _c)))
                    );
                }

                omni::geometry::circle<double> circle_from_incenter() const
                {
                    double x, y;
                    omni::math::triangle_get_incenter<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    return omni::geometry::circle<double>(x, y,
                        ((this->_area() * 2.0) / (this->_side_a() + this->_side_b() + this->_side_c()))
                    );
                }

                omni::math::shape_comparator compare(const omni::geometry::raw_triangle<T>& tri) const
                {
                    if (this == &tri) { return omni::math::shape_comparator::SIMILAR_CONGRUENT; }
                    omni::math::shape_comparator ret = omni::math::shape_comparator::NOT_EQUAL;
                    double ta = this->_angle_a(); double oa = tri._angle_a();
                    double tb = this->_angle_b(); double ob = tri._angle_b();
                    double tc = this->_angle_c(); double oc = tri._angle_c();

                    if (
                        // a
                        (omni::math::are_equal(ta, oa) || omni::math::are_equal(ta, ob) || omni::math::are_equal(ta, oc)) &&
                        // b
                        (omni::math::are_equal(tb, oa) || omni::math::are_equal(tb, ob) || omni::math::are_equal(tb, oc)) &&
                        // c
                        (omni::math::are_equal(tc, oa) || omni::math::are_equal(tc, ob) || omni::math::are_equal(tc, oc))
                    )
                    {
                        ret = omni::math::shape_comparator::SIMILAR;
                    }
                    
                    ta = this->_side_a(); oa = tri._side_a();
                    tb = this->_side_b(); ob = tri._side_b();
                    tc = this->_side_c(); oc = tri._side_c();

                    if (
                        // a
                        (omni::math::are_equal(ta, oa) || omni::math::are_equal(ta, ob) || omni::math::are_equal(ta, oc)) &&
                        // b
                        (omni::math::are_equal(tb, oa) || omni::math::are_equal(tb, ob) || omni::math::are_equal(tb, oc)) &&
                        // c
                        (omni::math::are_equal(tc, oa) || omni::math::are_equal(tc, ob) || omni::math::are_equal(tc, oc))
                    )
                    {
                        ret |= omni::math::shape_comparator::CONGRUENT;
                    }

                    return ret;
                }

                bool contains(T x, T y) const
                {
                    return omni::math::triangle_contains_point(
                        x, y,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                bool contains(const omni::math::dimensional<T, 2>& point) const
                {
                    return this->contains(point[0], point[1]);
                }

                bool contains(const omni::geometry::point2d<T>& point) const
                {
                    return this->contains(point.x(), point.y());
                }

                bool contains(const omni::geometry::raw_point2d<T>& point) const
                {
                    return this->contains(point.x, point.y);
                }

                bool contains(const omni::geometry::raw_triangle<T>& tri) const
                {
                    if (&tri == this) { return true; }
                    return
                        omni::math::triangle_contains_point(
                            tri.a.x, tri.a.y,
                            this->a.x, this->a.y,
                            this->b.x, this->b.y,
                            this->c.x, this->c.y
                        ) &&
                        omni::math::triangle_contains_point(
                            tri.b.x, tri.b.y,
                            this->a.x, this->a.y,
                            this->b.x, this->b.y,
                            this->c.x, this->c.y
                        ) &&
                        omni::math::triangle_contains_point(
                            tri.c.x, tri.c.y,
                            this->a.x, this->a.y,
                            this->b.x, this->b.y,
                            this->c.x, this->c.y
                        );
                }

                void deflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"))
                    }
                    double factor = percent / 100.0;
                    double x, y;
                    omni::math::triangle_get_incenter<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    omni::math::extend_line<double>(x, y, this->a.x, this->a.y, (omni::math::distance_between_2_points(x, y, this->a.x, this->a.y) * factor), this->a.x, this->a.y);
                    omni::math::extend_line<double>(x, y, this->b.x, this->b.y, (omni::math::distance_between_2_points(x, y, this->b.x, this->b.y) * factor), this->b.x, this->b.y);
                    omni::math::extend_line<double>(x, y, this->c.x, this->c.y, (omni::math::distance_between_2_points(x, y, this->c.x, this->c.y) * factor), this->c.x, this->c.y);
                }

                bool empty() const
                {
                    return this->a.empty() &&
                           this->b.empty() &&
                           this->c.empty();
                }

                bool empty_size() const
                {
                    OMNI_SAFE_TRIALOCK_FW
                    return (
                        (this->a == this->b) ||
                        (this->a == this->c) ||
                        (this->b == this->c)
                    );
                }

                bool equals(T ax, T ay, T bx, T by, T cx, T cy) const
                {
                    return
                        omni::math::are_equal(this->a.x, ax) &&
                        omni::math::are_equal(this->a.y, ay) &&
                        omni::math::are_equal(this->b.x, bx) &&
                        omni::math::are_equal(this->b.y, by) &&
                        omni::math::are_equal(this->c.x, cx) &&
                        omni::math::are_equal(this->c.y, cy);
                }

                bool equals(const omni::math::dimensional<T, 2>& _a, const omni::math::dimensional<T, 2>& _b, const omni::math::dimensional<T, 2>& _c) const
                {
                    return this->equals(_a[0], _a[1], _b[0], _b[1], _c[0], _c[1]);
                }

                bool equals(const omni::geometry::point2d<T>& _a, const omni::geometry::point2d<T>& _b, const omni::geometry::point2d<T>& _c) const
                {
                    return this->equals(_a.x(), _a.y(), _b.x(), _b.y(), _c.x(), _c.y());
                }

                bool equals(const omni::geometry::raw_point2d<T>& _a, const omni::geometry::raw_point2d<T>& _b, const omni::geometry::raw_point2d<T>& _c) const
                {
                    return this->equals(_a.x, _a.y, _b.x, _b.y, _c.x, _c.y);
                }

                int32_t hash_code() const
                {
                    return (
                        static_cast<int32_t>(this->base_side.value()) ^ 
                        a.hash_code() ^ b.hash_code() ^ c.hash_code()
                    );
                }

                double height() const
                {
                    return (this->_area() * 2.0) / this->_base();
                }

                omni::geometry::point2d<double> incenter() const
                {
                    double x, y;
                    omni::math::triangle_get_incenter<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }

                void inflate(double percent)
                {
                    if (percent < 0) {
                        OMNI_ERR_FW("value must be greater than 0", omni::exceptions::overflow_error("value must be greater than 0"))
                    }
                    double factor = percent / 100.0;
                    double x, y;
                    omni::math::triangle_get_incenter<double>(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        x, y);
                    omni::math::extend_line<double>(x, y, this->a.x, this->a.y, (omni::math::distance_between_2_points(x, y, this->a.x, this->a.y) * factor), this->a.x, this->a.y);
                    omni::math::extend_line<double>(x, y, this->b.x, this->b.y, (omni::math::distance_between_2_points(x, y, this->b.x, this->b.y) * factor), this->b.x, this->b.y);
                    omni::math::extend_line<double>(x, y, this->c.x, this->c.y, (omni::math::distance_between_2_points(x, y, this->c.x, this->c.y) * factor), this->c.x, this->c.y);
                }

                void intersect(const omni::geometry::raw_triangle<T>& r2)
                {
                    if (this == &r2) { return; }
                    omni::geometry::raw_point2d<T> _a = r2.a;
                    omni::geometry::raw_point2d<T> _b = r2.b;
                    omni::geometry::raw_point2d<T> _c = r2.c;
                    if (this->intersects_with(r2)) {
                        if (this->a.x < _a.x) { this->a.x = _a.x; }
                        if (this->a.y < _a.y) { this->a.y = _a.y; }
                        if (this->b.x < _b.x) { this->b.x = _b.x; }
                        if (this->b.y < _b.y) { this->b.y = _b.y; }
                        if (this->c.x < _c.x) { this->c.x = _c.x; }
                        if (this->c.y < _c.y) { this->c.y = _c.y; }
                    } else {
                        this->a.x = 0; this->a.y = 0;
                        this->b.x = 0; this->b.y = 0;
                        this->c.x = 0; this->c.y = 0;
                    }
                }

                bool intersects_with(const omni::geometry::raw_triangle<T>& tri) const
                {
                    return omni::math::triangle_intersects(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y,
                        tri.a.x, tri.a.y,
                        tri.b.x, tri.b.y,
                        tri.c.x, tri.c.y
                    );
                }

                omni::math::triangle_measure measure() const
                {
                    bool ab = omni::math::are_equal(this->_side_a(), this->_side_b());
                    bool bc = omni::math::are_equal(this->_side_b(), this->_side_c());
                    bool ac = omni::math::are_equal(this->_side_a(), this->_side_c());
                    if (ab && bc) {
                        return omni::math::triangle_measure::EQUILATERAL;
                    }
                    if ((ab && ac) || (bc && ac)) {
                        return omni::math::triangle_measure::ISOSCELES;
                    }
                    return omni::math::triangle_measure::SCALENE;
                }

                double perimeter() const
                {
                    return this->_side_a() + this->_side_b() + this->_side_c();
                }

                void rotate_on_a(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_abc(
                        degrees, this->a.x, this->a.y, dir,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void rotate_on_b(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_abc(
                        degrees, this->b.x, this->b.y, dir,
                        this->a.x, this->a.y,
                        this->c.x, this->c.y
                    );
                }

                void rotate_on_c(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_abc(
                        degrees, this->c.x, this->c.y, dir,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y
                    );
                }

                void rotate_centroid(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_centroid(
                        degrees, dir,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_circumcenter(
                        degrees, dir,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void rotate_incenter(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_incenter(
                        degrees, dir,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void rotate_origin(double degrees, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_origin(
                        degrees, dir,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir)
                {
                    omni::math::triangle_rotate_point(
                        degrees, x, y, dir,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void reflect()
                {
                    omni::math::triangle_reflect(
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                double semiperimeter() const
                {
                    return (this->_side_a() + this->_side_b() + this->_side_c()) / 2.0;
                }

                double side_a() const
                {
                    return this->_side_a();
                }

                double side_b() const
                {
                    return this->_side_b();
                }

                double side_c() const
                {
                    return this->_side_c();
                }

                void swap(omni::geometry::raw_triangle<T>& o)
                {
                    if (this != &o) {
                        std::swap(this->a, o.a);
                        std::swap(this->b, o.b);
                        std::swap(this->c, o.c);
                    }
                }

                void translate_xy(T x, T y)
                {
                    omni::math::triangle_translate_xy(
                        x, y,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                void translate_angle(double degrees, T distance)
                {
                    omni::math::triangle_translate_angle(
                        degrees, distance,
                        this->a.x, this->a.y,
                        this->b.x, this->b.y,
                        this->c.x, this->c.y
                    );
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    s << "{[A:" << this->a << "],[B:" << this->b << "],[C:" << this->c << "]}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    s << "{[A:" << this->a << "],[B:" << this->b << "],[C:" << this->c << "]}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    s << "{[A:" << this->a << "],[B:" << this->b << "],[C:" << this->c << "]}";
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
                
                bool operator!=(const omni::geometry::raw_triangle<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator==(const omni::geometry::raw_triangle<T>& val) const
                {
                    if (this == &val) { return true; }
                    return (
                        (this->a == val.a) &&
                        (this->b == val.b) &&
                        (this->c == val.c))
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::raw_triangle<T>& operator=(const omni::geometry::raw_triangle<T>& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->a = val.a;
                        this->b = val.b;
                        this->c = val.c;
                        this->base_side = val.base_side;
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::raw_triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    return (this->a < val.a) &&
                           (this->b < val.b) &&
                           (this->c < val.c);
                }

                bool operator<=(const omni::geometry::raw_triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    return (this->a <= val.a) &&
                           (this->b <= val.b) &&
                           (this->c <= val.c);
                }

                bool operator>(const omni::geometry::raw_triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    return (this->a > val.a) &&
                           (this->b > val.b) &&
                           (this->c > val.c);
                }

                bool operator>=(const omni::geometry::raw_triangle<T>& val) const
                {
                    if (this == &val) { return false; }
                    return (this->a >= val.a) &&
                           (this->b >= val.b) &&
                           (this->c >= val.c);
                }

                omni::geometry::raw_triangle<T> operator+(const omni::geometry::point2d<T>& val) const
                {
                    omni::geometry::raw_triangle<T> ret(*this);
                    ret.translate_xy(val.x(), val.y());
                    return ret;
                }

                omni::geometry::raw_triangle<T> operator-(const omni::geometry::point2d<T>& val) const
                {
                    omni::geometry::raw_triangle<T> ret(*this);
                    ret.translate_xy(-val.x(), -val.y());
                    return ret;
                }

                omni::geometry::raw_triangle<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->translate_xy(val.x(), val.y());
                    return *this;
                }

                omni::geometry::raw_triangle<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->translate_xy(val.x(), val.y());
                    return *this;
                }

                static omni::geometry::raw_triangle<T> deflate(const omni::geometry::raw_triangle<T>& tri, double percent)
                {
                    return omni::geometry::raw_triangle<T>(tri, percent, true);
                }

                static omni::geometry::raw_triangle<T> inflate(const omni::geometry::raw_triangle<T>& tri, double percent)
                {
                    return omni::geometry::raw_triangle<T>(tri, percent, false);
                }

                static omni::geometry::raw_triangle<T> intersect(const omni::geometry::raw_triangle<T>& a, const omni::geometry::raw_triangle<T>& b)
                {
                    return omni::geometry::raw_triangle<T>(a, b);
                }

                OMNI_MEMBERS_FW(omni::geometry::raw_triangle<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::raw_triangle<T>)

                omni::geometry::raw_point2d<T> a;

                omni::geometry::raw_point2d<T> b;

                omni::geometry::raw_point2d<T> c;

                omni::geometry::triangle_side base_side;

            private:
                raw_triangle(const omni::geometry::raw_triangle<T>& a, const omni::geometry::raw_triangle<T>& b) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a.a), b(a.b), c(a.c), base_side(a.base_side)
                {
                    this->intersect(b);
                }

                raw_triangle(const omni::geometry::raw_triangle<T>& a, double percent, bool deflate) :
                    OMNI_CTOR_FW(omni::geometry::raw_triangle<T>)
                    a(a.a), b(a.b), c(a.c), base_side(a.base_side)
                {
                    if (deflate) {
                        this->deflate(percent);
                    } else {
                        this->inflate(percent);
                    }
                }

                double _area() const
                {
                    return omni::math::area_of_triangle(this->a.x, this->a.y, this->b.x, this->b.y, this->c.x, this->c.y);
                }

                double _angle_a() const
                {
                    return omni::math::calculate_angle(this->a.x, this->a.y, this->b.x, this->b.y, this->c.x, this->c.y);
                }

                double _angle_b() const
                {
                    return omni::math::calculate_angle(this->b.x, this->b.y, this->a.x, this->a.y, this->c.x, this->c.y);
                }

                double _angle_c() const
                {
                    return omni::math::calculate_angle(this->c.x, this->c.y, this->b.x, this->b.y, this->a.x, this->a.y);
                }

                double _base() const
                {
                    switch (this->base_side) {
                        case omni::geometry::triangle_side::A:
                            return this->_side_a();
                        case omni::geometry::triangle_side::B:
                            return this->_side_b();
                        case omni::geometry::triangle_side::C:
                            return this->_side_c();
                        default: break;
                    }
                    return -1.0; // invalid base
                }

                double _side_a() const
                {
                    if (this->b >= this->c) {
                        return omni::math::distance_between_2_points(this->b.x, this->b.y, this->c.x, this->c.y);
                    }
                    return omni::math::distance_between_2_points(this->c.x, this->c.y, this->b.x, this->b.y);
                }

                double _side_b() const
                {
                    if (this->a >= this->c) {
                        return omni::math::distance_between_2_points(this->a.x, this->a.y, this->c.x, this->c.y);
                    }
                    return omni::math::distance_between_2_points(this->c.x, this->c.y, this->a.x, this->a.y);
                }

                double _side_c() const
                {
                    if (this->a >= this->b) {
                        return omni::math::distance_between_2_points(this->a.x, this->a.y, this->b.x, this->b.y);
                    }
                    return omni::math::distance_between_2_points(this->b.x, this->b.y, this->a.x, this->a.y);
                }
        };

        typedef omni::geometry::raw_triangle<int32_t> raw_triangle_t;
        typedef omni::geometry::raw_triangle<int64_t> raw_triangle64_t;
        typedef omni::geometry::raw_triangle<float> raw_triangleF_t;
        typedef omni::geometry::raw_triangle<double> raw_triangleD_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::triangle<T>& o1, omni::geometry::triangle<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_TRIANGLE_HPP
