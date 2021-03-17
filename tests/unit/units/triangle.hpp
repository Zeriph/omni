#if defined(OMNI_UTUA) || defined(OMNI_UT_TRIANGLE)

#define UT_NAME triangle
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(raw_triangle, "test the functionality in omni::geometry::raw_triangle");
            M_LIST_ADD(triangle, "test the functionality in omni::geometry::triangle");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::triangle<double>);
            print_info(omni::geometry::raw_triangle<double>);
        }
        
        void base_test()
        {
            triangle(); printl("");
            raw_triangle(); printl("");
        }

        void triangle()
        {
            typedef double T;
            omni::geometry::triangle<T> temp_val;
            omni::geometry::triangle<T> triangleT_tri;
            T T_x = 0.0;
            T T_y = 0.0;
            omni::math::dimensional<T, 2> math_dimensionalT2_point;
            omni::geometry::point2d<T> geometry_point2dT_point;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_point;
            double double_percent = 0.0;
            T T_ax = 0.0;
            T T_ay = 0.0;
            T T_bx = 0.0;
            T T_by = 0.0;
            T T_cx = 0.0;
            T T_cy = 0.0;
            omni::math::dimensional<T, 2> math_dimensionalT2_a;
            omni::math::dimensional<T, 2> math_dimensionalT2_b;
            omni::math::dimensional<T, 2> math_dimensionalT2_c;
            omni::geometry::point2d<T> geometry_point2dT_a;
            omni::geometry::point2d<T> geometry_point2dT_b;
            omni::geometry::point2d<T> geometry_point2dT_c;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_a;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_b;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_c;
            omni::geometry::triangle<T> triangleT_r2;
            double double_degrees = 0.0;
            omni::math::rotation_direction math_rotation_direction_dir;
            omni::geometry::triangle_side geometry_triangle_side_base;
            omni::geometry::triangle<T> triangleT_o;
            T T_distance = 0.0;
            omni::geometry::triangle<T> triangleT_val;
            omni::geometry::point2d<T> geometry_point2dT_val;
            omni::geometry::triangle<T> triangleT_a;
            omni::geometry::triangle<T> triangleT_b;
            
            // triangle ~~  omni::geometry::triangle::triangle()
            // triangle ~~  omni::geometry::triangle::triangle(const omni::geometry::triangle<T>& cp)
            // triangle ~~ OMNI_EXPLICIT omni::geometry::triangle::triangle(const omni::math::dimensional<T, 6>& cp)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::math::dimensional<T, 6>& cp, const omni::geometry::triangle_side& base)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c, const omni::geometry::triangle_side& base)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::triangle_side& base)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c)
            // triangle ~~  omni::geometry::triangle::triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::triangle_side& base)
            // triangle ~~  omni::geometry::triangle::triangle(T x1, T y1, T x2, T y2, T x3, T y3)
            // triangle ~~  omni::geometry::triangle::triangle(T x1, T y1, T x2, T y2, T x3, T y3, const omni::geometry::triangle_side& base)
            
            // a ~~ omni::geometry::raw_point2d<T> omni::geometry::triangle::a()
            test("temp_val.a()", temp_val.a(), "{0,0}");
            
            // angle_a ~~ double omni::geometry::triangle::angle_a()
            test("temp_val.angle_a()", temp_val.angle_a(), "0");
            
            // angle_b ~~ double omni::geometry::triangle::angle_b()
            test("temp_val.angle_b()", temp_val.angle_b(), "0");
            
            // angle_c ~~ double omni::geometry::triangle::angle_c()
            test("temp_val.angle_c()", temp_val.angle_c(), "0");
            
            // area ~~ double omni::geometry::triangle::area()
            test("temp_val.area()", temp_val.area(), "0");
            
            // b ~~ omni::geometry::raw_point2d<T> omni::geometry::triangle::b()
            test("temp_val.b()", temp_val.b(), "?");
            
            // base ~~ double omni::geometry::triangle::base()
            test("temp_val.base()", temp_val.base(), "?");
            
            // base_side ~~ omni::geometry::triangle_side omni::geometry::triangle::base_side()
            test("temp_val.base_side()", temp_val.base_side(), "?");
            
            // c ~~ omni::geometry::raw_point2d<T> omni::geometry::triangle::c()
            test("temp_val.c()", temp_val.c(), "?");
            
            // centroid ~~ omni::geometry::point2d<double> omni::geometry::triangle::centroid()
            test("temp_val.centroid()", temp_val.centroid(), "?");
            
            // circle_from_circumcenter ~~ omni::geometry::circle<double> omni::geometry::triangle::circle_from_circumcenter()
            test("temp_val.circle_from_circumcenter()", temp_val.circle_from_circumcenter(), "?");
            
            // circle_from_incenter ~~ omni::geometry::circle<double> omni::geometry::triangle::circle_from_incenter()
            test("temp_val.circle_from_incenter()", temp_val.circle_from_incenter(), "?");
            
            // circumcenter ~~ omni::geometry::point2d<double> omni::geometry::triangle::circumcenter()
            test("temp_val.circumcenter()", temp_val.circumcenter(), "?");
            
            // compare ~~ omni::math::shape_comparator omni::geometry::triangle::compare(const triangle<T>& tri)
            test("temp_val.compare(triangleT_tri)", temp_val.compare(triangleT_tri), "?");
            
            // contains ~~ bool omni::geometry::triangle::contains(T x, T y)
            test("temp_val.contains(T_x, T_y)", (temp_val.contains(T_x, T_y) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::triangle::contains(const omni::math::dimensional<T, 2>& point)
            test("temp_val.contains(math_dimensionalT2_point)", (temp_val.contains(math_dimensionalT2_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::triangle::contains(const omni::geometry::point2d<T>& point)
            test("temp_val.contains(geometry_point2dT_point)", (temp_val.contains(geometry_point2dT_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::triangle::contains(const omni::geometry::raw_point2d<T>& point)
            test("temp_val.contains(geometry_raw_point2dT_point)", (temp_val.contains(geometry_raw_point2dT_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::triangle::contains(const triangle<T>& tri)
            test("temp_val.contains(triangleT_tri)", (temp_val.contains(triangleT_tri) ? "true" : "false"), "?");
            
            // deflate ~~ void omni::geometry::triangle::deflate(double percent)
            temp_val.deflate(double_percent);
            test("temp_val.deflate(double_percent)", temp_val, "?");
            
            // empty ~~ bool omni::geometry::triangle::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "?");
            
            // empty_size ~~ bool omni::geometry::triangle::empty_size()
            test("temp_val.empty_size()", (temp_val.empty_size() ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::triangle::equals(T ax, T ay, T bx, T by, T cx, T cy)
            test("temp_val.equals(T_ax, T_ay, T_bx, T_by, T_cx, T_cy)", (temp_val.equals(T_ax, T_ay, T_bx, T_by, T_cx, T_cy) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::triangle::equals(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
            test("temp_val.equals(math_dimensionalT2_a, math_dimensionalT2_b, math_dimensionalT2_c)", (temp_val.equals(math_dimensionalT2_a, math_dimensionalT2_b, math_dimensionalT2_c) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::triangle::equals(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c)
            test("temp_val.equals(geometry_point2dT_a, geometry_point2dT_b, geometry_point2dT_c)", (temp_val.equals(geometry_point2dT_a, geometry_point2dT_b, geometry_point2dT_c) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::triangle::equals(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c)
            test("temp_val.equals(geometry_raw_point2dT_a, geometry_raw_point2dT_b, geometry_raw_point2dT_c)", (temp_val.equals(geometry_raw_point2dT_a, geometry_raw_point2dT_b, geometry_raw_point2dT_c) ? "true" : "false"), "?");
            
            // hash_code ~~ int32_t omni::geometry::triangle::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");
            
            // height ~~ double omni::geometry::triangle::height()
            test("temp_val.height()", temp_val.height(), "?");
            
            // incenter ~~ omni::geometry::point2d<double> omni::geometry::triangle::incenter()
            test("temp_val.incenter()", temp_val.incenter(), "?");
            
            // inflate ~~ void omni::geometry::triangle::inflate(double percent)
            temp_val.inflate(double_percent);
            test("temp_val.inflate(double_percent)", temp_val, "?");
            
            // intersect ~~ void omni::geometry::triangle::intersect(const triangle<T>& r2)
            temp_val.intersect(triangleT_r2);
            test("temp_val.intersect(triangleT_r2)", temp_val, "?");
            
            // intersects_with ~~ bool omni::geometry::triangle::intersects_with(const triangle<T>& tri)
            test("temp_val.intersects_with(triangleT_tri)", (temp_val.intersects_with(triangleT_tri) ? "true" : "false"), "?");
            
            // measure ~~ omni::math::triangle_measure omni::geometry::triangle::measure()
            test("temp_val.measure()", temp_val.measure(), "?");
            
            // perimeter ~~ double omni::geometry::triangle::perimeter()
            test("temp_val.perimeter()", temp_val.perimeter(), "?");
            
            // reflect ~~ void omni::geometry::triangle::reflect()
            temp_val.reflect();
            test("temp_val.reflect()", temp_val, "?");
            
            // rotate_centroid ~~ void omni::geometry::triangle::rotate_centroid(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_centroid(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_centroid(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_circumcenter ~~ void omni::geometry::triangle::rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_circumcenter(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_circumcenter(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_incenter ~~ void omni::geometry::triangle::rotate_incenter(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_incenter(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_incenter(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_on_a ~~ void omni::geometry::triangle::rotate_on_a(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_a(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_on_a(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_on_b ~~ void omni::geometry::triangle::rotate_on_b(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_b(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_on_b(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_on_c ~~ void omni::geometry::triangle::rotate_on_c(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_c(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_on_c(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_origin ~~ void omni::geometry::triangle::rotate_origin(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_origin(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_origin(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_point ~~ void omni::geometry::triangle::rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir)
            temp_val.rotate_point(double_degrees, T_x, T_y, math_rotation_direction_dir);
            test("temp_val.rotate_point(double_degrees, T_x, T_y, math_rotation_direction_dir)", temp_val, "?");
            
            // semiperimeter ~~ double omni::geometry::triangle::semiperimeter()
            test("temp_val.semiperimeter()", temp_val.semiperimeter(), "?");
            
            // set_base ~~ void omni::geometry::triangle::set_base(const omni::geometry::triangle_side& base)
            temp_val.set_base(geometry_triangle_side_base);
            test("temp_val.set_base(geometry_triangle_side_base)", temp_val, "?");
            
            // side_a ~~ double omni::geometry::triangle::side_a()
            test("temp_val.side_a()", temp_val.side_a(), "?");
            
            // side_b ~~ double omni::geometry::triangle::side_b()
            test("temp_val.side_b()", temp_val.side_b(), "?");
            
            // side_c ~~ double omni::geometry::triangle::side_c()
            test("temp_val.side_c()", temp_val.side_c(), "?");
            
            // swap ~~ void omni::geometry::triangle::swap(triangle<T>& o)
            temp_val.swap(triangleT_o);
            test("temp_val.swap(triangleT_o)", temp_val, "?");
            
            // to_string ~~ std::string omni::geometry::triangle::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::geometry::triangle::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_wstring ~~ std::wstring omni::geometry::triangle::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // translate_angle ~~ void omni::geometry::triangle::translate_angle(double degrees, T distance)
            temp_val.translate_angle(double_degrees, T_distance);
            test("temp_val.translate_angle(double_degrees, T_distance)", temp_val, "?");
            
            // translate_xy ~~ void omni::geometry::triangle::translate_xy(T x, T y)
            temp_val.translate_xy(T_x, T_y);
            test("temp_val.translate_xy(T_x, T_y)", temp_val, "?");
            
            // operator std::string ~~  omni::geometry::triangle::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::geometry::triangle::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::geometry::triangle::operator!=(const triangle<T>& val)
            test("(temp_val != triangleT_val)", ((temp_val != triangleT_val) ? "true" : "false"), "?");
            
            // operator+ ~~ triangle<T> omni::geometry::triangle::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + geometry_point2dT_val)", (temp_val + geometry_point2dT_val), "?");
            
            // operator+= ~~ triangle<T>& omni::geometry::triangle::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += geometry_point2dT_val)", (temp_val += geometry_point2dT_val), "?");
            
            // operator- ~~ triangle<T> omni::geometry::triangle::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - geometry_point2dT_val)", (temp_val - geometry_point2dT_val), "?");
            
            // operator-= ~~ triangle<T>& omni::geometry::triangle::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= geometry_point2dT_val)", (temp_val -= geometry_point2dT_val), "?");
            
            // operator< ~~ bool omni::geometry::triangle::operator<(const triangle<T>& val)
            test("(temp_val < triangleT_val)", ((temp_val < triangleT_val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::triangle::operator<=(const triangle<T>& val)
            test("(temp_val <= triangleT_val)", ((temp_val <= triangleT_val) ? "true" : "false"), "?");
            
            // operator= ~~ triangle<T>& omni::geometry::triangle::operator=(const triangle<T>& val)
            test("(temp_val = triangleT_val)", (temp_val = triangleT_val), "?");
            
            // operator== ~~ bool omni::geometry::triangle::operator==(const triangle<T>& val)
            test("(temp_val == triangleT_val)", ((temp_val == triangleT_val) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::triangle::operator>(const triangle<T>& val)
            test("(temp_val > triangleT_val)", ((temp_val > triangleT_val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::triangle::operator>=(const triangle<T>& val)
            test("(temp_val >= triangleT_val)", ((temp_val >= triangleT_val) ? "true" : "false"), "?");
            
            // deflate ~~ static triangle<T> omni::geometry::triangle::deflate(const triangle<T>& tri, double percent)
            test("omni::geometry::triangle::deflate(triangleT_tri, double_percent)", omni::geometry::triangle<T>::deflate(triangleT_tri, double_percent), "?");
            
            // inflate ~~ static triangle<T> omni::geometry::triangle::inflate(const triangle<T>& tri, double percent)
            test("omni::geometry::triangle::inflate(triangleT_tri, double_percent)", omni::geometry::triangle<T>::inflate(triangleT_tri, double_percent), "?");
            
            // intersect ~~ static triangle<T> omni::geometry::triangle::intersect(const triangle<T>& a, const triangle<T>& b)
            test("omni::geometry::triangle::intersect(triangleT_a, triangleT_b)", omni::geometry::triangle<T>::intersect(triangleT_a, triangleT_b), "?");
        }

        void raw_triangle()
        {
            typedef double T;
            omni::geometry::raw_triangle<T> temp_val;
            omni::geometry::raw_triangle<T> raw_triangleT_tri;
            T T_x = 0.0;
            T T_y = 0.0;
            omni::math::dimensional<T, 2> math_dimensionalT2_point;
            omni::geometry::point2d<T> geometry_point2dT_point;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_point;
            double double_percent = 0.0;
            T T_ax = 0.0;
            T T_ay = 0.0;
            T T_bx = 0.0;
            T T_by = 0.0;
            T T_cx = 0.0;
            T T_cy = 0.0;
            omni::math::dimensional<T, 2> math_dimensionalT2_a;
            omni::math::dimensional<T, 2> math_dimensionalT2_b;
            omni::math::dimensional<T, 2> math_dimensionalT2_c;
            omni::geometry::point2d<T> geometry_point2dT_a;
            omni::geometry::point2d<T> geometry_point2dT_b;
            omni::geometry::point2d<T> geometry_point2dT_c;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_a;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_b;
            omni::geometry::raw_point2d<T> geometry_raw_point2dT_c;
            omni::geometry::raw_triangle<T> raw_triangleT_r2;
            double double_degrees = 0.0;
            omni::math::rotation_direction math_rotation_direction_dir;
            omni::geometry::raw_triangle<T> raw_triangleT_o;
            T T_distance = 0.0;
            omni::geometry::raw_triangle<T> raw_triangleT_val;
            omni::geometry::point2d<T> geometry_point2dT_val;
            omni::geometry::raw_triangle<T> raw_triangleT_a;
            omni::geometry::raw_triangle<T> raw_triangleT_b;
            
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle()
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::raw_triangle<T>& cp)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::triangle<T>& cp)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::math::dimensional<T, 6>& cp)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::triangle_side& base)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::math::dimensional<T, 6>& cp, const omni::geometry::triangle_side& base)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c, const omni::geometry::triangle_side& base)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c, const omni::geometry::triangle_side& base)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c, const omni::geometry::triangle_side& base)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(T x1, T y1, T x2, T y2, T x3, T y3)
            // raw_triangle ~~  omni::geometry::raw_triangle::raw_triangle(T x1, T y1, T x2, T y2, T x3, T y3, const omni::geometry::triangle_side& base)
            
            // angle_a ~~ double omni::geometry::raw_triangle::angle_a()
            test("temp_val.angle_a()", temp_val.angle_a(), "?");
            
            // angle_b ~~ double omni::geometry::raw_triangle::angle_b()
            test("temp_val.angle_b()", temp_val.angle_b(), "?");
            
            // angle_c ~~ double omni::geometry::raw_triangle::angle_c()
            test("temp_val.angle_c()", temp_val.angle_c(), "?");
            
            // area ~~ double omni::geometry::raw_triangle::area()
            test("temp_val.area()", temp_val.area(), "?");
            
            // base ~~ double omni::geometry::raw_triangle::base()
            test("temp_val.base()", temp_val.base(), "?");
            
            // centroid ~~ omni::geometry::point2d<double> omni::geometry::raw_triangle::centroid()
            test("temp_val.centroid()", temp_val.centroid(), "?");
            
            // circle_frocircumcenter ~~ omni::geometry::circle<double> omni::geometry::raw_triangle::circle_frocircumcenter()
            test("temp_val.circle_frocircumcenter()", temp_val.circle_frocircumcenter(), "?");
            
            // circle_from_incenter ~~ omni::geometry::circle<double> omni::geometry::raw_triangle::circle_from_incenter()
            test("temp_val.circle_from_incenter()", temp_val.circle_from_incenter(), "?");
            
            // circumcenter ~~ omni::geometry::point2d<double> omni::geometry::raw_triangle::circumcenter()
            test("temp_val.circumcenter()", temp_val.circumcenter(), "?");
            
            // compare ~~ omni::math::shape_comparator omni::geometry::raw_triangle::compare(const raw_triangle<T>& tri)
            test("temp_val.compare(raw_triangleT_tri)", temp_val.compare(raw_triangleT_tri), "?");
            
            // contains ~~ bool omni::geometry::raw_triangle::contains(T x, T y)
            test("temp_val.contains(T_x, T_y)", (temp_val.contains(T_x, T_y) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_triangle::contains(const omni::math::dimensional<T, 2>& point)
            test("temp_val.contains(math_dimensionalT2_point)", (temp_val.contains(math_dimensionalT2_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_triangle::contains(const omni::geometry::point2d<T>& point)
            test("temp_val.contains(geometry_point2dT_point)", (temp_val.contains(geometry_point2dT_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_triangle::contains(const omni::geometry::raw_point2d<T>& point)
            test("temp_val.contains(geometry_raw_point2dT_point)", (temp_val.contains(geometry_raw_point2dT_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_triangle::contains(const raw_triangle<T>& tri)
            test("temp_val.contains(raw_triangleT_tri)", (temp_val.contains(raw_triangleT_tri) ? "true" : "false"), "?");
            
            // deflate ~~ void omni::geometry::raw_triangle::deflate(double percent)
            temp_val.deflate(double_percent);
            test("temp_val.deflate(double_percent)", temp_val, "?");
            
            // empty ~~ bool omni::geometry::raw_triangle::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "?");
            
            // empty_size ~~ bool omni::geometry::raw_triangle::empty_size()
            test("temp_val.empty_size()", (temp_val.empty_size() ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::raw_triangle::equals(T ax, T ay, T bx, T by, T cx, T cy)
            test("temp_val.equals(T_ax, T_ay, T_bx, T_by, T_cx, T_cy)", (temp_val.equals(T_ax, T_ay, T_bx, T_by, T_cx, T_cy) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::raw_triangle::equals(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
            test("temp_val.equals(math_dimensionalT2_a, math_dimensionalT2_b, math_dimensionalT2_c)", (temp_val.equals(math_dimensionalT2_a, math_dimensionalT2_b, math_dimensionalT2_c) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::raw_triangle::equals(const omni::geometry::point2d<T>& a, const omni::geometry::point2d<T>& b, const omni::geometry::point2d<T>& c)
            test("temp_val.equals(geometry_point2dT_a, geometry_point2dT_b, geometry_point2dT_c)", (temp_val.equals(geometry_point2dT_a, geometry_point2dT_b, geometry_point2dT_c) ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::raw_triangle::equals(const omni::geometry::raw_point2d<T>& a, const omni::geometry::raw_point2d<T>& b, const omni::geometry::raw_point2d<T>& c)
            test("temp_val.equals(geometry_raw_point2dT_a, geometry_raw_point2dT_b, geometry_raw_point2dT_c)", (temp_val.equals(geometry_raw_point2dT_a, geometry_raw_point2dT_b, geometry_raw_point2dT_c) ? "true" : "false"), "?");
            
            // hash_code ~~ int32_t omni::geometry::raw_triangle::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");
            
            // height ~~ double omni::geometry::raw_triangle::height()
            test("temp_val.height()", temp_val.height(), "?");
            
            // incenter ~~ omni::geometry::point2d<double> omni::geometry::raw_triangle::incenter()
            test("temp_val.incenter()", temp_val.incenter(), "?");
            
            // inflate ~~ void omni::geometry::raw_triangle::inflate(double percent)
            temp_val.inflate(double_percent);
            test("temp_val.inflate(double_percent)", temp_val, "?");
            
            // intersect ~~ void omni::geometry::raw_triangle::intersect(const raw_triangle<T>& r2)
            temp_val.intersect(raw_triangleT_r2);
            test("temp_val.intersect(raw_triangleT_r2)", temp_val, "?");
            
            // intersects_with ~~ bool omni::geometry::raw_triangle::intersects_with(const raw_triangle<T>& tri)
            test("temp_val.intersects_with(raw_triangleT_tri)", (temp_val.intersects_with(raw_triangleT_tri) ? "true" : "false"), "?");
            
            // measure ~~ omni::math::triangle_measure omni::geometry::raw_triangle::measure()
            test("temp_val.measure()", temp_val.measure(), "?");
            
            // perimeter ~~ double omni::geometry::raw_triangle::perimeter()
            test("temp_val.perimeter()", temp_val.perimeter(), "?");
            
            // reflect ~~ void omni::geometry::raw_triangle::reflect()
            temp_val.reflect();
            test("temp_val.reflect()", temp_val, "?");
            
            // rotate_centroid ~~ void omni::geometry::raw_triangle::rotate_centroid(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_centroid(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_centroid(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_circumcenter ~~ void omni::geometry::raw_triangle::rotate_circumcenter(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_circumcenter(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_circumcenter(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_incenter ~~ void omni::geometry::raw_triangle::rotate_incenter(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_incenter(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_incenter(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_on_a ~~ void omni::geometry::raw_triangle::rotate_on_a(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_a(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_on_a(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_on_b ~~ void omni::geometry::raw_triangle::rotate_on_b(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_b(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_on_b(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_on_c ~~ void omni::geometry::raw_triangle::rotate_on_c(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_c(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_on_c(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_origin ~~ void omni::geometry::raw_triangle::rotate_origin(double degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_origin(double_degrees, math_rotation_direction_dir);
            test("temp_val.rotate_origin(double_degrees, math_rotation_direction_dir)", temp_val, "?");
            
            // rotate_point ~~ void omni::geometry::raw_triangle::rotate_point(double degrees, T x, T y, const omni::math::rotation_direction& dir)
            temp_val.rotate_point(double_degrees, T_x, T_y, math_rotation_direction_dir);
            test("temp_val.rotate_point(double_degrees, T_x, T_y, math_rotation_direction_dir)", temp_val, "?");
            
            // semiperimeter ~~ double omni::geometry::raw_triangle::semiperimeter()
            test("temp_val.semiperimeter()", temp_val.semiperimeter(), "?");
            
            // side_a ~~ double omni::geometry::raw_triangle::side_a()
            test("temp_val.side_a()", temp_val.side_a(), "?");
            
            // side_b ~~ double omni::geometry::raw_triangle::side_b()
            test("temp_val.side_b()", temp_val.side_b(), "?");
            
            // side_c ~~ double omni::geometry::raw_triangle::side_c()
            test("temp_val.side_c()", temp_val.side_c(), "?");
            
            // swap ~~ void omni::geometry::raw_triangle::swap(raw_triangle<T>& o)
            temp_val.swap(raw_triangleT_o);
            test("temp_val.swap(raw_triangleT_o)", temp_val, "?");
            
            // to_string ~~ std::string omni::geometry::raw_triangle::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::geometry::raw_triangle::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_wstring ~~ std::wstring omni::geometry::raw_triangle::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // translate_angle ~~ void omni::geometry::raw_triangle::translate_angle(double degrees, T distance)
            temp_val.translate_angle(double_degrees, T_distance);
            test("temp_val.translate_angle(double_degrees, T_distance)", temp_val, "?");
            
            // translate_xy ~~ void omni::geometry::raw_triangle::translate_xy(T x, T y)
            temp_val.translate_xy(T_x, T_y);
            test("temp_val.translate_xy(T_x, T_y)", temp_val, "?");
            
            // operator std::string ~~  omni::geometry::raw_triangle::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::geometry::raw_triangle::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::geometry::raw_triangle::operator!=(const raw_triangle<T>& val)
            test("(temp_val != raw_triangleT_val)", ((temp_val != raw_triangleT_val) ? "true" : "false"), "?");
            
            // operator+ ~~ raw_triangle<T> omni::geometry::raw_triangle::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + geometry_point2dT_val)", (temp_val + geometry_point2dT_val), "?");
            
            // operator+= ~~ raw_triangle<T>& omni::geometry::raw_triangle::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += geometry_point2dT_val)", (temp_val += geometry_point2dT_val), "?");
            
            // operator- ~~ raw_triangle<T> omni::geometry::raw_triangle::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - geometry_point2dT_val)", (temp_val - geometry_point2dT_val), "?");
            
            // operator-= ~~ raw_triangle<T>& omni::geometry::raw_triangle::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= geometry_point2dT_val)", (temp_val -= geometry_point2dT_val), "?");
            
            // operator< ~~ bool omni::geometry::raw_triangle::operator<(const raw_triangle<T>& val)
            test("(temp_val < raw_triangleT_val)", ((temp_val < raw_triangleT_val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::raw_triangle::operator<=(const raw_triangle<T>& val)
            test("(temp_val <= raw_triangleT_val)", ((temp_val <= raw_triangleT_val) ? "true" : "false"), "?");
            
            // operator= ~~ raw_triangle<T>& omni::geometry::raw_triangle::operator=(const raw_triangle<T>& val)
            test("(temp_val = raw_triangleT_val)", (temp_val = raw_triangleT_val), "?");
            
            // operator== ~~ bool omni::geometry::raw_triangle::operator==(const raw_triangle<T>& val)
            test("(temp_val == raw_triangleT_val)", ((temp_val == raw_triangleT_val) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::raw_triangle::operator>(const raw_triangle<T>& val)
            test("(temp_val > raw_triangleT_val)", ((temp_val > raw_triangleT_val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::raw_triangle::operator>=(const raw_triangle<T>& val)
            test("(temp_val >= raw_triangleT_val)", ((temp_val >= raw_triangleT_val) ? "true" : "false"), "?");
            
            // a ~~ omni::geometry::raw_point2d<T> omni::geometry::raw_triangle::a
            test("temp_val.a", temp_val.a, "?");
            
            // b ~~ omni::geometry::raw_point2d<T> omni::geometry::raw_triangle::b
            test("temp_val.b", temp_val.b, "?");
            
            // base_side ~~ omni::geometry::triangle_side omni::geometry::raw_triangle::base_side
            test("temp_val.base_side", temp_val.base_side, "?");
            
            // c ~~ omni::geometry::raw_point2d<T> omni::geometry::raw_triangle::c
            test("temp_val.c", temp_val.c, "?");
            
            // deflate ~~ static raw_triangle<T> omni::geometry::raw_triangle::deflate(const raw_triangle<T>& tri, double percent)
            test("omni::geometry::raw_triangle::deflate(raw_triangleT_tri, double_percent)", omni::geometry::raw_triangle<T>::deflate(raw_triangleT_tri, double_percent), "?");
            
            // inflate ~~ static raw_triangle<T> omni::geometry::raw_triangle::inflate(const raw_triangle<T>& tri, double percent)
            test("omni::geometry::raw_triangle::inflate(raw_triangleT_tri, double_percent)", omni::geometry::raw_triangle<T>::inflate(raw_triangleT_tri, double_percent), "?");
            
            // intersect ~~ static raw_triangle<T> omni::geometry::raw_triangle::intersect(const raw_triangle<T>& a, const raw_triangle<T>& b)
            test("omni::geometry::raw_triangle::intersect(raw_triangleT_a, raw_triangleT_b)", omni::geometry::raw_triangle<T>::intersect(raw_triangleT_a, raw_triangleT_b), "?");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TRIANGLE
