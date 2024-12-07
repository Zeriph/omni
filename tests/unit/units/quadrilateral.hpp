#if defined(OMNI_UTUA) || defined(OMNI_UT_QUADRILATERAL)

#define UT_NAME quadrilateral
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(quadrilateral, "test the functionality in omni::geometry::quadrilateral");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::quadrilateral<double>);
        }
        
        void base_test()
        {
            quadrilateral(); printl("");
        }

        void quadrilateral()
        {
            typedef double T;
            typedef omni::geometry::quadrilateral<T> qd;
            typedef omni::geometry::point2d<T> pt;

            omni::math::rotation_direction _dir = omni::math::rotation_direction::CLOCKWISE;
            T _ax, _ay, _bx, _by, _cx, _cy, _dx, _dy, _x, _y, _percent, _degrees, _angle, _distance;
            _x = 10.25; _y = 9.75; _percent = 50.0; _degrees = 45.0; _angle = 32.0; _distance = 25.25;
            _ax = 9; _ay = 8; _bx = 9; _by = 18; _cx = 20; _cy = 18; _dx = 23; _dy = 25;
            pt _point(_x, _y);
            pt _a(_x, _y);
            pt _b(42, 38);
            pt _c(32, 42);
            pt _d(22, 15);
            pt val(5.5, 5.5);

            // quadrilateral ~~  omni::geometry::quadrilateral::quadrilateral()
            // quadrilateral ~~  omni::geometry::quadrilateral::quadrilateral(const omni::geometry::quadrilateral<T>& cp)
            // quadrilateral ~~ OMNI_EXPLICIT omni::geometry::quadrilateral::quadrilateral(const omni::math::dimensional<T 8>& cp)
            // quadrilateral ~~  omni::geometry::quadrilateral::quadrilateral(const omni::math::dimensional<T 2>& a, const omni::math::dimensional<T 2>& b, const omni::math::dimensional<T 2>& c, const omni::math::dimensional<T 2>& d)
            // quadrilateral ~~  omni::geometry::quadrilateral::quadrilateral(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::point2d<T>& d)
            // quadrilateral ~~  omni::geometry::quadrilateral::quadrilateral(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::raw_point2d<T>& d)
            // quadrilateral ~~  omni::geometry::quadrilateral::quadrilateral(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4)
            qd temp_val(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy);
            qd _quad(_a, _b, _c, _d);
            qd _r2(_quad);
            qd _qa(_quad);
            qd _qb(temp_val);
            
            
            // a ~~ omni::geometry::raw_point2d<T> omni::geometry::quadrilateral::a()
            test("temp_val.a()", temp_val.a(), "?");
            
            // angle_a ~~ double omni::geometry::quadrilateral::angle_a()
            test("temp_val.angle_a()", temp_val.angle_a(), "?");
            
            // angle_b ~~ double omni::geometry::quadrilateral::angle_b()
            test("temp_val.angle_b()", temp_val.angle_b(), "?");
            
            // angle_c ~~ double omni::geometry::quadrilateral::angle_c()
            test("temp_val.angle_c()", temp_val.angle_c(), "?");
            
            // angle_d ~~ double omni::geometry::quadrilateral::angle_d()
            test("temp_val.angle_d()", temp_val.angle_d(), "?");
            
            // area ~~ double omni::geometry::quadrilateral::area()
            test("temp_val.area()", temp_val.area(), "?");
            
            // b ~~ omni::geometry::raw_point2d<T> omni::geometry::quadrilateral::b()
            test("temp_val.b()", temp_val.b(), "?");
            
            // base ~~ double omni::geometry::quadrilateral::base()
            test("temp_val.base()", temp_val.base(), "?");
            
            // c ~~ omni::geometry::raw_point2d<T> omni::geometry::quadrilateral::c()
            test("temp_val.c()", temp_val.c(), "?");
            
            // centroid ~~ omni::geometry::point2d<double> omni::geometry::quadrilateral::centroid()
            test("temp_val.centroid()", temp_val.centroid(), "?");
            
            // circle_from_circumcenter ~~ omni::geometry::circle<double> omni::geometry::quadrilateral::circle_from_circumcenter()
            test("temp_val.circle_from_circumcenter()", temp_val.circle_from_circumcenter(), "?");
            
            // circle_from_incenter ~~ omni::geometry::circle<double> omni::geometry::quadrilateral::circle_from_incenter()
            test("temp_val.circle_from_incenter()", temp_val.circle_from_incenter(), "?");
            
            // circumcenter ~~ omni::geometry::point2d<double> omni::geometry::quadrilateral::circumcenter()
            test("temp_val.circumcenter()", temp_val.circumcenter(), "?");
            
            // compare ~~ omni::math::shape_comparator omni::geometry::quadrilateral::compare(const quadrilateral<T>& quad)
            test("temp_val.compare(_quad)", temp_val.compare(_quad), "?");
            
            // contains ~~ bool omni::geometry::quadrilateral::contains(T x, T y)
            test("temp_val.contains(_x, _y)", (temp_val.contains(_x, _y) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::quadrilateral::contains(const omni::geometry::point2d<T>& point)
            test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::quadrilateral::contains(const omni::math::dimensional<T 2>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::quadrilateral::contains(const omni::geometry::raw_point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::quadrilateral::contains(const quadrilateral<T>& quad)
            // test("temp_val.contains(_quad)", (temp_val.contains(_quad) ? "true" : "false"), "?");
            
            // d ~~ omni::geometry::raw_point2d<T> omni::geometry::quadrilateral::d()
            test("temp_val.d()", temp_val.d(), "?");
            
            // deflate ~~ void omni::geometry::quadrilateral::deflate(double percent)
            temp_val.deflate(_percent);
            test("temp_val.deflate(_percent)", temp_val, "?");
            
            // empty ~~ bool omni::geometry::quadrilateral::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::quadrilateral::equals(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
            test("temp_val.equals(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy)", (temp_val.equals(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::quadrilateral::equals(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::point2d<T>& d)
            test("temp_val.equals(_a, _b, _c, _d)", (temp_val.equals(_a, _b, _c, _d) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::quadrilateral::equals(const omni::math::dimensional<T 2>& a, const omni::math::dimensional<T 2>& b, const omni::math::dimensional<T 2>& c, const omni::math::dimensional<T 2>& d)
            // test("temp_val.equals(_a, _b, _c, _d)", (temp_val.equals(_a, _b, _c, _d) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::quadrilateral::equals(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::raw_point2d<T>& d)
            // test("temp_val.equals(_a, _b, _c, _d)", (temp_val.equals(_a, _b, _c, _d) ? "true" : "false"), "?");
            
            // hash_code ~~ int32_t omni::geometry::quadrilateral::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");
            
            // height ~~ double omni::geometry::quadrilateral::height()
            test("temp_val.height()", temp_val.height(), "?");
            
            // incenter ~~ omni::geometry::point2d<double> omni::geometry::quadrilateral::incenter()
            test("temp_val.incenter()", temp_val.incenter(), "?");
            
            // inflate ~~ void omni::geometry::quadrilateral::inflate(double percent)
            temp_val.inflate(_percent);
            test("temp_val.inflate(_percent)", temp_val, "?");
            
            // intersect ~~ void omni::geometry::quadrilateral::intersect(const quadrilateral<T>& r2)
            temp_val.intersect(_r2);
            test("temp_val.intersect(_r2)", temp_val, "?");
            
            // intersects_with ~~ bool omni::geometry::quadrilateral::intersects_with(const quadrilateral<T>& quad)
            test("temp_val.intersects_with(_quad)", (temp_val.intersects_with(_quad) ? "true" : "false"), "?");
            
            // is_kite ~~ bool omni::geometry::quadrilateral::is_kite()
            test("temp_val.is_kite()", (temp_val.is_kite() ? "true" : "false"), "?");
            
            // is_parallelogram ~~ bool omni::geometry::quadrilateral::is_parallelogram()
            test("temp_val.is_parallelogram()", (temp_val.is_parallelogram() ? "true" : "false"), "?");
            
            // is_rectangle ~~ bool omni::geometry::quadrilateral::is_rectangle()
            test("temp_val.is_rectangle()", (temp_val.is_rectangle() ? "true" : "false"), "?");
            
            // is_rhombus ~~ bool omni::geometry::quadrilateral::is_rhombus()
            test("temp_val.is_rhombus()", (temp_val.is_rhombus() ? "true" : "false"), "?");
            
            // is_square ~~ bool omni::geometry::quadrilateral::is_square()
            test("temp_val.is_square()", (temp_val.is_square() ? "true" : "false"), "?");
            
            // is_trapezoid ~~ bool omni::geometry::quadrilateral::is_trapezoid()
            test("temp_val.is_trapezoid()", (temp_val.is_trapezoid() ? "true" : "false"), "?");
            
            // perimeter ~~ double omni::geometry::quadrilateral::perimeter()
            test("temp_val.perimeter()", temp_val.perimeter(), "?");
            
            // reflect ~~ void omni::geometry::quadrilateral::reflect()
            temp_val.reflect();
            test("temp_val.reflect()", temp_val, "?");
            
            // rotate_centroid ~~ void omni::geometry::quadrilateral::rotate_centroid(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_centroid(_degrees, _dir);
            test("temp_val.rotate_centroid(_degrees, _dir)", temp_val, "?");
            
            // rotate_circumcenter ~~ void omni::geometry::quadrilateral::rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_circumcenter(_degrees, _dir);
            test("temp_val.rotate_circumcenter(_degrees, _dir)", temp_val, "?");
            
            // rotate_incenter ~~ void omni::geometry::quadrilateral::rotate_incenter(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_incenter(_degrees, _dir);
            test("temp_val.rotate_incenter(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_a ~~ void omni::geometry::quadrilateral::rotate_on_a(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_a(_degrees, _dir);
            test("temp_val.rotate_on_a(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_b ~~ void omni::geometry::quadrilateral::rotate_on_b(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_b(_degrees, _dir);
            test("temp_val.rotate_on_b(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_c ~~ void omni::geometry::quadrilateral::rotate_on_c(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_c(_degrees, _dir);
            test("temp_val.rotate_on_c(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_d ~~ void omni::geometry::quadrilateral::rotate_on_d(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_d(_degrees, _dir);
            test("temp_val.rotate_on_d(_degrees, _dir)", temp_val, "?");
            
            // rotate_origin ~~ void omni::geometry::quadrilateral::rotate_origin(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_origin(_degrees, _dir);
            test("temp_val.rotate_origin(_degrees, _dir)", temp_val, "?");
            
            // rotate_point ~~ void omni::geometry::quadrilateral::rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir)
            temp_val.rotate_point(_degrees, _x, _y, _dir);
            test("temp_val.rotate_point(_degrees, _x, _y, _dir)", temp_val, "?");
            
            // side_a ~~ double omni::geometry::quadrilateral::side_a()
            test("temp_val.side_a()", temp_val.side_a(), "?");
            
            // side_b ~~ double omni::geometry::quadrilateral::side_b()
            test("temp_val.side_b()", temp_val.side_b(), "?");
            
            // side_c ~~ double omni::geometry::quadrilateral::side_c()
            test("temp_val.side_c()", temp_val.side_c(), "?");
            
            // side_d ~~ double omni::geometry::quadrilateral::side_d()
            test("temp_val.side_d()", temp_val.side_d(), "?");
            
            // swap ~~ void omni::geometry::quadrilateral::swap(quadrilateral<T>& o)
            temp_val.swap(_quad);
            test("temp_val.swap(_quad)", temp_val, "?");
            
            // to_string ~~ std::string omni::geometry::quadrilateral::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::geometry::quadrilateral::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_wstring ~~ std::wstring omni::geometry::quadrilateral::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // translate_angle ~~ void omni::geometry::quadrilateral::translate_angle(float angle, T distance)
            temp_val.translate_angle(_angle, _distance);
            test("temp_val.translate_angle(_angle, _distance)", temp_val, "?");
            
            // translate_xy ~~ void omni::geometry::quadrilateral::translate_xy(T x, T y)
            temp_val.translate_xy(_x, _y);
            test("temp_val.translate_xy(_x, _y)", temp_val, "?");
            
            // operator std::string ~~  omni::geometry::quadrilateral::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::geometry::quadrilateral::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::geometry::quadrilateral::operator!=(const quadrilateral<T>& val)
            test("(temp_val != _quad)", ((temp_val != _quad) ? "true" : "false"), "?");
            
            // operator+ ~~ quadrilateral<T> omni::geometry::quadrilateral::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + val)", (temp_val + val), "?");
            
            // operator+= ~~ quadrilateral<T>& omni::geometry::quadrilateral::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += val)", (temp_val += val), "?");
            
            // operator- ~~ quadrilateral<T> omni::geometry::quadrilateral::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - val)", (temp_val - val), "?");
            
            // operator-= ~~ quadrilateral<T>& omni::geometry::quadrilateral::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "?");
            
            // operator< ~~ bool omni::geometry::quadrilateral::operator<(const quadrilateral<T>& val)
            test("(temp_val < _quad)", ((temp_val < _quad) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::quadrilateral::operator<=(const quadrilateral<T>& val)
            test("(temp_val <= _quad)", ((temp_val <= _quad) ? "true" : "false"), "?");
            
            // operator= ~~ quadrilateral<T>& omni::geometry::quadrilateral::operator=(const quadrilateral<T>& val)
            test("(temp_val = _quad)", (temp_val = _quad), "?");
            
            // operator== ~~ bool omni::geometry::quadrilateral::operator==(const quadrilateral<T>& val)
            test("(temp_val == _quad)", ((temp_val == _quad) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::quadrilateral::operator>(const quadrilateral<T>& val)
            test("(temp_val > _quad)", ((temp_val > _quad) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::quadrilateral::operator>=(const quadrilateral<T>& val)
            test("(temp_val >= _quad)", ((temp_val >= _quad) ? "true" : "false"), "?");
            
            // deflate ~~ static quadrilateral<T> omni::geometry::quadrilateral::deflate(const quadrilateral<T>& quad, double percent)
            test("omni::geometry::quadrilateral::deflate(_quad, _percent)", omni::geometry::quadrilateral<T>::deflate(_quad, _percent), "?");
            
            // inflate ~~ static quadrilateral<T> omni::geometry::quadrilateral::inflate(const quadrilateral<T>& quad, double percent)
            test("omni::geometry::quadrilateral::inflate(_quad, _percent)", omni::geometry::quadrilateral<T>::inflate(_quad, _percent), "?");
            
            // intersect ~~ static quadrilateral<T> omni::geometry::quadrilateral::intersect(const quadrilateral<T>& a, const quadrilateral<T>& b)
            test("omni::geometry::quadrilateral::intersect(_qa, _qb)", omni::geometry::quadrilateral<T>::intersect(_qa, _qb), "?");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_QUADRILATERAL
