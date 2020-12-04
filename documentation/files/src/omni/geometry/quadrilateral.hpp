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
#if !defined(OMNI_QUADRILATERAL_HPP)
#define OMNI_QUADRILATERAL_HPP 1
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/geometry/point2d.hpp>
#include <omni/geometry/circle.hpp>

#if defined(OMNI_SAFE_QUADRANGLE)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_QUADRMTX_FW  ,m_mtx()
    #define OMNI_SAFE_QUADRLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_QUADRUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_QUADRALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_QUADROALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_QUADRMTX_FW
    #define OMNI_SAFE_QUADRLOCK_FW
    #define OMNI_SAFE_QUADRUNLOCK_FW
    #define OMNI_SAFE_QUADRALOCK_FW
    #define OMNI_SAFE_QUADROALOCK_FW(o) 
#endif

#if defined(OMNI_QUADRILATERAL_USE_SA)
    #define OMNI_QUADR_SA_FW ,m_sides(), m_angle()
    #define OMNI_QUADR_SACP_FW(cp) ,m_sides(cp.m_sides), m_angle(cp.m_angle)
    #define OMNI_QUADR_SA_CALC_FW this->_recalc_sas()
#else
    #define OMNI_QUADR_SA_FW
    #define OMNI_QUADR_SACP_FW(cp)
    #define OMNI_QUADR_SA_CALC_FW
#endif

namespace omni {
    namespace geometry {
        template < typename T >
        class quadrilateral
        {
            public:
                typedef T coordinate_t;

                quadrilateral() : 
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(), m_b(), m_c(), m_d()
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                { }

                quadrilateral(const omni::geometry::quadrilateral<T>& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_a(cp.a()), m_b(cp.b()), m_c(cp.c()), m_d(cp.d())
                    OMNI_QUADR_SACP_FW(cp)
                    OMNI_SAFE_QUADRMTX_FW
                { }

                OMNI_EXPLICIT quadrilateral(const omni::math::dimensional<T, 8>& cp) :
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(cp[0], cp[1]), m_b(cp[2], cp[3]), m_c(cp[4], cp[5]), m_d(cp[6], cp[7])
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    OMNI_QUADR_SA_CALC_FW
                }

                quadrilateral(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c, const omni::math::dimensional<T, 2>& d) :
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(a[0], a[1]), m_b(b[0], b[1]), m_c(c[0], c[1]), m_d(d[0], d[1])
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    OMNI_QUADR_SA_CALC_FW
                }

                quadrilateral(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::point2d<T>& d) :
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(a.x(), a.y()), m_b(b.x(), b.y()), m_c(c.x(), c.y()), m_d(d.x(), d.y())
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    OMNI_QUADR_SA_CALC_FW
                }

                quadrilateral(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::raw_point2d<T>& d) :
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(a.x, a.y), m_b(b.x, b.y), m_c(c.x, c.y), m_d(d.x, d.y)
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    OMNI_QUADR_SA_CALC_FW
                }

                quadrilateral(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) : 
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(x1, y1), m_b(x2, y2), m_c(x3, y3), m_d(x4, y4)
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    OMNI_QUADR_SA_CALC_FW
                }

                ~quadrilateral()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                omni::geometry::raw_point2d<T> a() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->m_a;
                }

                double angle_a() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_angle_a();
                }

                double angle_b() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_angle_b();
                }

                double angle_c() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_angle_c();
                }

                double angle_d() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_angle_d();
                }

                double area() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_area();
                }

                omni::geometry::raw_point2d<T> b() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->m_b;
                }

                double base() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_base();
                }

                omni::geometry::raw_point2d<T> c() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->m_c;
                }

                omni::geometry::point2d<double> centroid() const
                {
                    double x, y;
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_get_centroid<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }
                
                omni::geometry::point2d<double> circumcenter() const
                {
                    double x, y;
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_get_circumcenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }

                omni::geometry::circle<double> circle_from_circumcenter() const
                {
                    double x, y;
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_get_circumcenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y
                    );
                    double a = this->_side_a();
                    double b = this->_side_b();
                    double c = this->_side_c();
                    double d = this->_side_d();
                    return omni::geometry::circle<double>(x, y,
                        ((a * b * c * d) / std::sqrt(
                            (a + b + c + d) *
                            (b + c + d - a) *
                            (c + d + a - b) *
                            (d + a + b - c) *
                            (a + b + c - d)
                        ))
                    );
                }

                omni::geometry::circle<double> circle_from_incenter() const
                {
                    double x, y;
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y
                    );
                    return omni::geometry::circle<double>(x, y,
                        (
                            (this->_area() * 2.0) /
                            (this->_side_a() + this->_side_b() + this->_side_c() + this->_side_d())
                        )
                    );
                }

                omni::math::shape_comparator compare(const omni::geometry::quadrilateral<T>& quad) const
                {
                    if (this == &quad) { return omni::math::shape_comparator::SIMILAR_CONGRUENT; }
                    omni::math::shape_comparator ret = omni::math::shape_comparator::NOT_EQUAL;
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(quad)
                    double ta = this->_angle_a(); double oa = quad._angle_a();
                    double tb = this->_angle_b(); double ob = quad._angle_b();
                    double tc = this->_angle_c(); double oc = quad._angle_c();
                    double td = this->_angle_d(); double od = quad._angle_d();

                    if (
                        // a
                        (omni::math::are_equal(ta, oa) || omni::math::are_equal(ta, ob) || omni::math::are_equal(ta, oc) || omni::math::are_equal(ta, od)) &&
                        // b
                        (omni::math::are_equal(tb, oa) || omni::math::are_equal(tb, ob) || omni::math::are_equal(tb, oc) || omni::math::are_equal(tb, od)) &&
                        // c
                        (omni::math::are_equal(tc, oa) || omni::math::are_equal(tc, ob) || omni::math::are_equal(tc, oc) || omni::math::are_equal(tc, od)) &&
                        // d
                        (omni::math::are_equal(td, oa) || omni::math::are_equal(td, ob) || omni::math::are_equal(td, oc) || omni::math::are_equal(td, od))
                    )
                    {
                        ret = omni::math::shape_comparator::SIMILAR;
                    }
                    
                    ta = this->_side_a(); oa = quad._side_a();
                    tb = this->_side_b(); ob = quad._side_b();
                    tc = this->_side_c(); oc = quad._side_c();
                    td = this->_side_d(); od = quad._side_d();

                    if (
                        // a
                        (omni::math::are_equal(ta, oa) || omni::math::are_equal(ta, ob) || omni::math::are_equal(ta, oc) || omni::math::are_equal(ta, od)) &&
                        // b
                        (omni::math::are_equal(tb, oa) || omni::math::are_equal(tb, ob) || omni::math::are_equal(tb, oc) || omni::math::are_equal(tb, od)) &&
                        // c
                        (omni::math::are_equal(tc, oa) || omni::math::are_equal(tc, ob) || omni::math::are_equal(tc, oc) || omni::math::are_equal(tc, od)) &&
                        // d
                        (omni::math::are_equal(td, oa) || omni::math::are_equal(td, ob) || omni::math::are_equal(td, oc) || omni::math::are_equal(td, od))
                    )
                    {
                        ret |= omni::math::shape_comparator::CONGRUENT;
                    }

                    return ret;
                }

                bool contains(T x, T y) const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return omni::math::quadrilateral_contains_point(
                        x, y,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
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

                bool contains(const omni::geometry::quadrilateral<T>& quad) const
                {
                    if (&quad == this) { return true; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(quad)
                    return
                        omni::math::quadrilateral_contains_point(
                            quad.m_a.x, quad.m_a.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y,
                            this->m_d.x, this->m_d.y
                        ) &&
                        omni::math::quadrilateral_contains_point(
                            quad.m_b.x, quad.m_b.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y,
                            this->m_d.x, this->m_d.y
                        ) &&
                        omni::math::quadrilateral_contains_point(
                            quad.m_c.x, quad.m_c.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y,
                            this->m_d.x, this->m_d.y
                        ) &&
                        omni::math::quadrilateral_contains_point(
                            quad.m_d.x, quad.m_d.y,
                            this->m_a.x, this->m_a.y,
                            this->m_b.x, this->m_b.y,
                            this->m_c.x, this->m_c.y,
                            this->m_d.x, this->m_d.y
                        );
                }

                omni::geometry::raw_point2d<T> d() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->m_d;
                }

                void deflate(double percent)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    double factor = percent / 100.0;
                    double x, y;
                    omni::math::quadrilateral_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y);
                    omni::math::extend_line<double>(x, y, this->m_a.x, this->m_a.y, (omni::math::distance_between_2_points(x, y, this->m_a.x, this->m_a.y) * factor), this->m_a.x, this->m_a.y);
                    omni::math::extend_line<double>(x, y, this->m_b.x, this->m_b.y, (omni::math::distance_between_2_points(x, y, this->m_b.x, this->m_b.y) * factor), this->m_b.x, this->m_b.y);
                    omni::math::extend_line<double>(x, y, this->m_c.x, this->m_c.y, (omni::math::distance_between_2_points(x, y, this->m_c.x, this->m_c.y) * factor), this->m_c.x, this->m_c.y);
                    omni::math::extend_line<double>(x, y, this->m_d.x, this->m_d.y, (omni::math::distance_between_2_points(x, y, this->m_d.x, this->m_d.y) * factor), this->m_d.x, this->m_d.y);
                    OMNI_QUADR_SA_CALC_FW
                }

                bool empty() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->m_a.empty() &&
                           this->m_b.empty() &&
                           this->m_c.empty() &&
                           this->m_d.empty()
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        &&
                        omni::math::are_equal(m_sides[0], 0) &&
                        omni::math::are_equal(m_sides[1], 0) &&
                        omni::math::are_equal(m_sides[2], 0) &&
                        omni::math::are_equal(m_sides[3], 0) &&

                        omni::math::are_equal(m_angle[0], 0) &&
                        omni::math::are_equal(m_angle[1], 0) &&
                        omni::math::are_equal(m_angle[2], 0) &&
                        omni::math::are_equal(m_angle[3], 0)
                    #endif
                    ;
                }

                bool equals(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy) const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return
                        omni::math::are_equal(this->m_a.x, ax) &&
                        omni::math::are_equal(this->m_a.y, ay) &&
                        omni::math::are_equal(this->m_b.x, bx) &&
                        omni::math::are_equal(this->m_b.y, by) &&
                        omni::math::are_equal(this->m_c.x, cx) &&
                        omni::math::are_equal(this->m_c.y, cy) &&
                        omni::math::are_equal(this->m_d.x, dx) &&
                        omni::math::are_equal(this->m_d.y, dy);
                }

                bool equals(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c, const omni::math::dimensional<T, 2>& d) const
                {
                    return this->equals(a[0], a[1], b[0], b[1], c[0], c[1], d[0], d[1]);
                }

                bool equals(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::point2d<T>& d) const
                {
                    return this->equals(a.x(), a.y(), b.x(), b.y(), c.x(), c.y(), d.x(), d.y());
                }

                bool equals(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::raw_point2d<T>& d) const
                {
                    return this->equals(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
                }

                int32_t hash_code() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        m_a.hash_code() ^ m_b.hash_code() ^ m_c.hash_code() ^ m_d.hash_code()
                    );
                }

                double height() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (this->_area() * 2.0) / this->_base();
                }

                omni::geometry::point2d<double> incenter() const
                {
                    double x, y;
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y);
                    return omni::geometry::point2d<double>(x, y);
                }

                void inflate(double percent)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    double factor = percent / 100.0;
                    double x, y;
                    omni::math::quadrilateral_get_incenter<double>(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        x, y);
                    omni::math::extend_line<double>(x, y, this->m_a.x, this->m_a.y, (omni::math::distance_between_2_points(x, y, this->m_a.x, this->m_a.y) * factor), this->m_a.x, this->m_a.y);
                    omni::math::extend_line<double>(x, y, this->m_b.x, this->m_b.y, (omni::math::distance_between_2_points(x, y, this->m_b.x, this->m_b.y) * factor), this->m_b.x, this->m_b.y);
                    omni::math::extend_line<double>(x, y, this->m_c.x, this->m_c.y, (omni::math::distance_between_2_points(x, y, this->m_c.x, this->m_c.y) * factor), this->m_c.x, this->m_c.y);
                    omni::math::extend_line<double>(x, y, this->m_d.x, this->m_d.y, (omni::math::distance_between_2_points(x, y, this->m_d.x, this->m_d.y) * factor), this->m_d.x, this->m_d.y);
                    OMNI_QUADR_SA_CALC_FW
                }

                void intersect(const omni::geometry::quadrilateral<T>& quad)
                {
                    if (this == &quad) { return; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(quad)
                    if (this->_intersects_with(quad.m_a.x, quad.m_a.y, quad.m_b.x, quad.m_b.y,
                                               quad.m_c.x, quad.m_c.y, quad.m_d.x, quad.m_d.y))
                    {
                        if (this->m_a.x < quad.m_a.x) { this->m_a.x = quad.m_a.x; }
                        if (this->m_a.y < quad.m_a.y) { this->m_a.y = quad.m_a.y; }
                        if (this->m_b.x < quad.m_b.x) { this->m_b.x = quad.m_b.x; }
                        if (this->m_b.y < quad.m_b.y) { this->m_b.y = quad.m_b.y; }
                        if (this->m_c.x < quad.m_c.x) { this->m_c.x = quad.m_c.x; }
                        if (this->m_c.y < quad.m_c.y) { this->m_c.y = quad.m_c.y; }
                        if (this->m_d.x < quad.m_d.x) { this->m_d.x = quad.m_d.x; }
                        if (this->m_d.y < quad.m_d.y) { this->m_d.y = quad.m_d.y; }
                        OMNI_QUADR_SA_CALC_FW
                    } else {
                        this->m_a.x = 0; this->m_a.y = 0;
                        this->m_b.x = 0; this->m_b.y = 0;
                        this->m_c.x = 0; this->m_c.y = 0;
                        this->m_d.x = 0; this->m_d.y = 0;
                        #if defined(OMNI_QUADRILATERAL_USE_SA)
                            std::memset(this->m_sides, 0, sizeof(this->m_sides));
                            std::memset(this->m_angle, 0, sizeof(this->m_angle));
                        #endif
                    }
                }

                bool intersects_with(const omni::geometry::quadrilateral<T>& quad) const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(quad)
                    return this->_intersects_with(
                        quad.m_a.x, quad.m_a.y,
                        quad.m_b.x, quad.m_b.y,
                        quad.m_c.x, quad.m_c.y,
                        quad.m_d.x, quad.m_d.y
                    );
                }

                bool is_kite() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        (
                            omni::math::are_equal(this->_angle_a(), this->_angle_c()) &&
                            omni::math::are_equal(this->_angle_b(), this->_angle_d())
                        ) && (
                            omni::math::are_equal(this->_side_a(), this->_side_d()) &&
                            omni::math::are_equal(this->_angle_b(), this->_side_c())
                        )
                    );
                }

                bool is_parallelogram() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        (
                            omni::math::are_equal(this->_angle_a(), this->_angle_c()) &&
                            omni::math::are_equal(this->_angle_b(), this->_angle_d())
                        ) && (
                            omni::math::are_equal(this->_side_a(), this->_side_c()) &&
                            omni::math::are_equal(this->_angle_b(), this->_side_d())
                        )
                    );
                }

                bool is_rectangle() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        (
                            omni::math::are_equal(this->_angle_a(), 90.0) &&
                            omni::math::are_equal(this->_angle_b(), 90.0) &&
                            omni::math::are_equal(this->_angle_c(), 90.0) &&
                            omni::math::are_equal(this->_angle_d(), 90.0)
                        ) &&
                        (
                            (omni::math::are_equal(this->_side_a(), this->_side_b()) ||
                            omni::math::are_equal(this->_angle_a(), this->_side_c()) ||
                            omni::math::are_equal(this->_angle_a(), this->_side_d()))
                            &&
                            (omni::math::are_equal(this->_side_b(), this->_side_a()) ||
                            omni::math::are_equal(this->_angle_b(), this->_side_c()) ||
                            omni::math::are_equal(this->_angle_b(), this->_side_d()))
                            &&
                            (omni::math::are_equal(this->_side_c(), this->_side_a()) ||
                            omni::math::are_equal(this->_angle_c(), this->_side_b()) ||
                            omni::math::are_equal(this->_angle_c(), this->_side_d()))
                            &&
                            (omni::math::are_equal(this->_side_d(), this->_side_a()) ||
                            omni::math::are_equal(this->_angle_d(), this->_side_b()) ||
                            omni::math::are_equal(this->_angle_d(), this->_side_c()))
                        )
                    );
                }

                bool is_rhombus() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        (
                            omni::math::are_equal(this->_angle_a(), this->_angle_c()) &&
                            omni::math::are_equal(this->_angle_b(), this->_angle_d())
                        ) &&
                        (
                            omni::math::are_equal(this->_side_a(), this->_side_b()) &&
                            omni::math::are_equal(this->_angle_a(), this->_side_c()) &&
                            omni::math::are_equal(this->_angle_a(), this->_side_d())
                        )
                    );
                }

                bool is_square() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        (
                            omni::math::are_equal(this->_angle_a(), 90.0) &&
                            omni::math::are_equal(this->_angle_b(), 90.0) &&
                            omni::math::are_equal(this->_angle_c(), 90.0) &&
                            omni::math::are_equal(this->_angle_d(), 90.0)
                        ) &&
                        (
                            omni::math::are_equal(this->_side_a(), this->_side_b()) &&
                            omni::math::are_equal(this->_angle_a(), this->_side_c()) &&
                            omni::math::are_equal(this->_angle_a(), this->_side_d())
                        )
                    );
                }

                bool is_trapezoid() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return (
                        omni::math::are_equal(
                            omni::math::slope(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y),
                            omni::math::slope(this->m_c.x, this->m_c.y, this->m_d.x, this->m_d.y)
                        ) ||
                        omni::math::are_equal(
                            omni::math::slope(this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y),
                            omni::math::slope(this->m_d.x, this->m_d.y, this->m_a.x, this->m_a.y)
                        )
                    );
                }

                double perimeter() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_side_a() + this->_side_b() + this->_side_c() + this->_side_d();
                }

                void rotate_on_a(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_abcd(
                        degrees, this->m_a.x, this->m_a.y, dir,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_on_b(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_abcd(
                        degrees, this->m_b.x, this->m_b.y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_on_c(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_abcd(
                        degrees, this->m_c.x, this->m_c.y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_on_d(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_abcd(
                        degrees, this->m_d.x, this->m_d.y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y
                    );
                }

                void rotate_centroid(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_centroid(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_circumcenter(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_incenter(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_incenter(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_origin(double degrees, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_origin(
                        degrees, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_rotate_point(
                        degrees, x, y, dir,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void reflect()
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_reflect(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                double side_a() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_side_a();
                }

                double side_b() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_side_b();
                }

                double side_c() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_side_c();
                }

                double side_d() const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    return this->_side_d();
                }

                void swap(quadrilateral<T>& o)
                {
                    if (this != &o) {
                        OMNI_SAFE_QUADRALOCK_FW
                        OMNI_SAFE_QUADROALOCK_FW(o)
                        std::swap(this->m_a, o.m_a);
                        std::swap(this->m_b, o.m_b);
                        std::swap(this->m_c, o.m_c);
                        std::swap(this->m_d, o.m_d);
                        #if defined(OMNI_QUADRILATERAL_USE_SA)
                            std::swap(this->m_sides, o.m_sides);
                            std::swap(this->m_angle, o.m_angle);
                        #endif
                    }
                }

                void translate_xy(T x, T y)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_translate_xy(
                        x, y,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                void translate_angle(float angle, T distance)
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::math::quadrilateral_translate_angle(
                        angle, distance,
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y
                    );
                }

                omni::string_t to_string_t() const
                {
                    omni::sstream_t s;
                    OMNI_SAFE_QUADRALOCK_FW
                    s << "{[A:" << this->m_a << "],[B:" << this->m_b << "],[C:" << this->m_c << "],[D:" << this->m_d << "]}";
                    return s.str();
                }

                std::string to_string() const
                {
                    std::stringstream s;
                    OMNI_SAFE_QUADRALOCK_FW
                    s << "{[A:" << this->m_a << "],[B:" << this->m_b << "],[C:" << this->m_c << "],[D:" << this->m_d << "]}";
                    return s.str();
                }

                std::wstring to_wstring() const
                {
                    std::wstringstream s;
                    OMNI_SAFE_QUADRALOCK_FW
                    s << "{[A:" << this->m_a << "],[B:" << this->m_b << "],[C:" << this->m_c << "],[D:" << this->m_d << "]}";
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
                
                bool operator!=(const omni::geometry::quadrilateral<T>& val) const
                {
                    return !(*this == val);
                }

                bool operator==(const omni::geometry::quadrilateral<T>& val) const
                {
                    if (this == &val) { return true; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(val)
                    return (
                        (this->m_a == val.m_a) &&
                        (this->m_b == val.m_b) &&
                        (this->m_c == val.m_c) &&
                        (this->m_d == val.m_d))
                    OMNI_EQUAL_FW(val);
                }

                omni::geometry::quadrilateral<T>& operator=(const omni::geometry::quadrilateral<T>& val)
                {
                    if (this != &val) {
                        OMNI_SAFE_QUADRALOCK_FW
                        OMNI_SAFE_QUADROALOCK_FW(val)
                        OMNI_ASSIGN_FW(val)
                        this->m_a = val.m_a;
                        this->m_b = val.m_b;
                        this->m_c = val.m_c;
                        this->m_d = val.m_d;
                        OMNI_QUADR_SA_CALC_FW
                    }
                    return *this;
                }

                bool operator<(const omni::geometry::quadrilateral<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(val)
                    return (this->m_a < val.m_a) &&
                           (this->m_b < val.m_b) &&
                           (this->m_c < val.m_c) &&
                           (this->m_d < val.m_d);
                }

                bool operator<=(const omni::geometry::quadrilateral<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(val)
                    return (this->m_a <= val.m_a) &&
                           (this->m_b <= val.m_b) &&
                           (this->m_c <= val.m_c) &&
                           (this->m_d <= val.m_d);
                }

                bool operator>(const omni::geometry::quadrilateral<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(val)
                    return (this->m_a > val.m_a) &&
                           (this->m_b > val.m_b) &&
                           (this->m_c > val.m_c) &&
                           (this->m_d > val.m_d);
                }

                bool operator>=(const omni::geometry::quadrilateral<T>& val) const
                {
                    if (this == &val) { return false; }
                    OMNI_SAFE_QUADRALOCK_FW
                    OMNI_SAFE_QUADROALOCK_FW(val)
                    return (this->m_a >= val.m_a) &&
                           (this->m_b >= val.m_b) &&
                           (this->m_c >= val.m_c) &&
                           (this->m_d >= val.m_d);
                }

                omni::geometry::quadrilateral<T> operator+(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::geometry::quadrilateral<T> ret(*this);
                    ret.translate_xy(val.x(), val.y());
                    return ret;
                }

                omni::geometry::quadrilateral<T> operator-(const omni::geometry::point2d<T>& val) const
                {
                    OMNI_SAFE_QUADRALOCK_FW
                    omni::geometry::quadrilateral<T> ret(*this);
                    ret.translate_xy(-val.x(), -val.y());
                    return ret;
                }

                omni::geometry::quadrilateral<T>& operator+=(const omni::geometry::point2d<T>& val)
                {
                    this->translate_xy(val.x(), val.y());
                    return *this;
                }

                omni::geometry::quadrilateral<T>& operator-=(const omni::geometry::point2d<T>& val)
                {
                    this->translate_xy(val.x(), val.y());
                    return *this;
                }

                static omni::geometry::quadrilateral<T> deflate(const omni::geometry::quadrilateral<T>& quad, double percent)
                {
                    return omni::geometry::quadrilateral<T>(quad, percent, true);
                }

                static omni::geometry::quadrilateral<T> inflate(const omni::geometry::quadrilateral<T>& quad, double percent)
                {
                    return omni::geometry::quadrilateral<T>(quad, percent, false);
                }

                static omni::geometry::quadrilateral<T> intersect(const omni::geometry::quadrilateral<T>& a, const omni::geometry::quadrilateral<T>& b)
                {
                    return omni::geometry::quadrilateral<T>(a, b);
                }

                OMNI_MEMBERS_FW(omni::geometry::quadrilateral<T>) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::geometry::quadrilateral<T>)

            private:
                omni::geometry::raw_point2d<T> m_a;
                omni::geometry::raw_point2d<T> m_b;
                omni::geometry::raw_point2d<T> m_c;
                omni::geometry::raw_point2d<T> m_d;
                #if defined(OMNI_QUADRILATERAL_USE_SA)
                    double m_sides[4];
                    double m_angle[4];
                #endif
                #if defined(OMNI_SAFE_QUADRANGLE)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                quadrilateral(const omni::geometry::quadrilateral<T>& a, const omni::geometry::quadrilateral<T>& b) :
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(a.a()), m_b(a.b()), m_c(a.c()), m_d(a.d())
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    this->intersect(b);
                }

                quadrilateral(const omni::geometry::quadrilateral<T>& a, double percent, bool deflate) :
                    OMNI_CTOR_FW(omni::geometry::quadrilateral<T>)
                    m_a(a.a()), m_b(a.b()), m_c(a.c()), m_d(a.d())
                    OMNI_QUADR_SA_FW
                    OMNI_SAFE_QUADRMTX_FW
                {
                    if (deflate) {
                        this->deflate(percent);
                    } else {
                        this->inflate(percent);
                    }
                }

                #if defined(OMNI_QUADRILATERAL_USE_SA)
                    void _recalc_sas()
                    {
                        this->m_sides[0] = this->_calc_side_a();
                        this->m_sides[1] = this->_calc_side_b();
                        this->m_sides[2] = this->_calc_side_c();
                        this->m_sides[3] = this->_calc_side_d();

                        this->m_angle[0] = omni::math::calculate_angle(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                        this->m_angle[1] = omni::math::calculate_angle(this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y, this->m_d.x, this->m_d.y);
                        this->m_angle[2] = omni::math::calculate_angle(this->m_c.x, this->m_c.y, this->m_d.x, this->m_d.y, this->m_a.x, this->m_a.y);
                        this->m_angle[3] = omni::math::calculate_angle(this->m_d.x, this->m_d.y, this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y);
                    }
                #endif

                double _area() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return omni::math::area_of_quadrilateral(this->m_sides[0], this->m_sides[1], this->m_sides[2], this->m_sides[3], this->m_angle[0], this->m_angle[2]);
                    #else
                        return omni::math::area_of_quadrilateral(this->_side_a(), this->_side_b(), this->_side_c(), this->_side_d(), this->_angle_a(), this->_angle_c());
                    #endif
                }

                double _angle_a() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_angle[0];
                    #else
                        return omni::math::calculate_angle(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                    #endif
                }

                double _angle_b() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_angle[1];
                    #else
                        return omni::math::calculate_angle(this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y, this->m_d.x, this->m_d.y);
                    #endif
                }

                double _angle_c() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_angle[2];
                    #else
                        return omni::math::calculate_angle(this->m_c.x, this->m_c.y, this->m_d.x, this->m_d.y, this->m_a.x, this->m_a.y);
                    #endif
                }

                double _angle_d() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_angle[3];
                    #else
                        return omni::math::calculate_angle(this->m_d.x, this->m_d.y, this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y);
                    #endif
                }

                double _base() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return std::max(this->m_sides[0], std::max(this->m_sides[1], std::max(this->m_sides[2], this->m_sides[3])));
                    #else
                        return std::max(this->_side_a(), std::max(this->_side_b(), std::max(this->_side_c(), this->_side_d())));
                    #endif
                }

                double _calc_side_a() const
                {
                    if (this->m_a >= this->m_b) {
                        return omni::math::distance_between_2_points(this->m_a.x, this->m_a.y, this->m_b.x, this->m_b.y);
                    }
                    return omni::math::distance_between_2_points(this->m_b.x, this->m_b.y, this->m_a.x, this->m_a.y);
                }

                double _calc_side_b() const
                {
                    if (this->m_b >= this->m_c) {
                        return omni::math::distance_between_2_points(this->m_b.x, this->m_b.y, this->m_c.x, this->m_c.y);
                    }
                    return omni::math::distance_between_2_points(this->m_c.x, this->m_c.y, this->m_b.x, this->m_b.y);
                }

                double _calc_side_c() const
                {
                    if (this->m_c >= this->m_d) {
                        return omni::math::distance_between_2_points(this->m_c.x, this->m_c.y, this->m_d.x, this->m_d.y);
                    }
                    return omni::math::distance_between_2_points(this->m_d.x, this->m_d.y, this->m_c.x, this->m_c.y);
                }

                double _calc_side_d() const
                {
                    if (this->m_d >= this->m_a) {
                        return omni::math::distance_between_2_points(this->m_d.x, this->m_d.y, this->m_a.x, this->m_a.y);
                    }
                    return omni::math::distance_between_2_points(this->m_a.x, this->m_a.y, this->m_d.x, this->m_d.y);
                }

                bool _intersects_with(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy) const
                {
                    return omni::math::quadrilateral_intersects(
                        this->m_a.x, this->m_a.y,
                        this->m_b.x, this->m_b.y,
                        this->m_c.x, this->m_c.y,
                        this->m_d.x, this->m_d.y,
                        ax, ay,
                        bx, by,
                        cx, cy,
                        dx, dy
                    );
                }

                inline double _side_a() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_sides[0];
                    #else    
                        return this->_calc_side_a();
                    #endif
                }

                inline double _side_b() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_sides[1];
                    #else    
                        return this->_calc_side_b();
                    #endif
                }

                inline double _side_c() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_sides[2];
                    #else    
                        return this->_calc_side_c();
                    #endif
                }

                inline double _side_d() const
                {
                    #if defined(OMNI_QUADRILATERAL_USE_SA)
                        return this->m_sides[3];
                    #else    
                        return this->_calc_side_d();
                    #endif
                }
        };

        typedef omni::geometry::quadrilateral<int32_t> quadrilateral_t;
        typedef omni::geometry::quadrilateral<int64_t> quadrilateral64_t;
        typedef omni::geometry::quadrilateral<float> quadrilateralF_t;
        typedef omni::geometry::quadrilateral<double> quadrilateralD_t;
    }
}

namespace std {
    template < typename T >
    inline void swap(omni::geometry::quadrilateral<T>& o1, omni::geometry::quadrilateral<T>& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_QUADRILATERAL_HPP
