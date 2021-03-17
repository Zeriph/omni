#if defined(OMNI_UTUA) || defined(OMNI_UT_MATH)

#define UT_ROOT_NS math
#define UT_NAME math
#define UT_ISNS true
#define UT_DESC "Tests the various functionality of the omni::math namespace"
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(dimensional, "tests dimensional class");
            M_LIST_ADD(angles, "tests the angle functionality");
            M_LIST_ADD(circles, "tests the circles functionality");
            M_LIST_ADD(lines, "tests the lines functionality");
            M_LIST_ADD(rectangles, "tests the rectangles functionality");
            M_LIST_ADD(triangles, "tests the triangles functionality");
            M_LIST_ADD(quadrilaterals, "tests the quadrilaterals functionality");
            M_LIST_ADD(are_equal, "tests the omni::math::are_equal");
            M_LIST_ADD(area_of, "tests the omni::math::area_of_circle/rect/triangle");
            M_LIST_ADD(area_of_circle_sector, "tests the omni::math::area_of_circle_sector");
            M_LIST_ADD(arc_length, "tests the omni::math::arc_length");
            M_LIST_ADD(calculate_point, "tests the omni::math::calculate_point");
            M_LIST_ADD(clamp, "tests the omni::math::clamp");
            M_LIST_ADD(deg_to_rad, "tests the omni::math::deg_to_rad");
            M_LIST_ADD(delta, "tests the omni::math::delta");
            M_LIST_ADD(distance_between_2_points, "tests the omni::math::distance_between_2_points");
            M_LIST_ADD(is_nan, "tests the omni::math::is_nan");
            M_LIST_ADD(ieee_remainder, "tests the omni::math::ieee_remainder");
            M_LIST_ADD(lerp_y, "tests the omni::math::lerp_y");
            M_LIST_ADD(lerp_x, "tests the omni::math::lerp_x");
            M_LIST_ADD(midpoint, "tests the omni::math::midpoint");
            M_LIST_ADD(midpoint3d, "tests the omni::math::midpoint3d");
            M_LIST_ADD(octant, "tests the omni::math::octant");
            M_LIST_ADD(point_on_circle, "tests the omni::math::point_on_circle");
            M_LIST_ADD(quadrant, "tests the omni::math::quadrant");
            M_LIST_ADD(quadratic, "tests the omni::math::quadratic");
            M_LIST_ADD(rad_to_deg, "tests the omni::math::rad_to_deg");
            M_LIST_ADD(radius_from_area, "tests the omni::math::radius_from_area");
            M_LIST_ADD(round, "tests the omni::math::round");
            M_LIST_ADD(sign, "tests the omni::math::sign");
            M_LIST_ADD(slope, "tests the omni::math::slope");
            M_LIST_ADD(summation, "tests the omni::math::summation");
            M_LIST_ADD(truncate, "tests the omni::math::truncate");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            printv("omni::math::E = ", OMNI_E);
            printv("omni::math::E_L = ", OMNI_E_L);
            printv("omni::math::E_F = ", OMNI_E_F);
            printv("omni::math::PI = ", OMNI_PI);
            printv("omni::math::PI_L = ", OMNI_PI_L);
            printv("omni::math::PI_F = ", OMNI_PI_F);
            printv("omni::math::PI_180 = ", OMNI_PI_180);
            printv("omni::math::PI_L_180 = ", OMNI_PI_L_180);
            printv("omni::math::PI_F_180 = ", OMNI_PI_F_180);
            printv("omni::math::TAU = ", OMNI_TAU);
            printv("omni::math::TAU_L = ", OMNI_TAU_L);
            printv("omni::math::TAU_F = ", OMNI_TAU_F);
            printv("omni::math::compat::E = ", OMNI_E);
            printv("omni::math::compat::PI = ", OMNI_PI);
            printv("omni::math::compat::TAU = ", OMNI_TAU);

            #if !defined(OMNI_NO_CONSTS)
                for (int i = 0; i < 361; ++i) {
                    printl("RADS[" << i << "] = " << omni::math::RADS[i]);
                    printl("RADS_SIN[" << i << "] = " << omni::math::RADS_SIN[i]);
                    printl("RADS_COS[" << i << "] = " << omni::math::RADS_COS[i]);
                }
            #else
                double r[] = OMNI_MATH_RADS;
                double s[] = OMNI_MATH_RADS_SIN;
                double c[] = OMNI_MATH_RADS_COS;
                for (int i = 0; i < 361; ++i) {
                    printl("RADS[" << i << "] = " << r[i]);
                    printl("RADS_SIN[" << i << "] = " << s[i]);
                    printl("RADS_COS[" << i << "] = " << c[i]);
                }
            #endif

            uint8_t xx[3] = {1,2,3};
            uint8_t yy[4] = {4,3,2,1};
            omni::math::dimensional<uint8_t, 3> xyz(xx);
            omni::math::dimensional<uint8_t, 4> xyzt(yy);

            printv("omni::math::dimensional<uint8_t, 3> = ", xyz);
            printv("omni::math::dimensional<uint8_t, 4> = ", xyzt);

            print_info(omni::math::dimensional<uint8_t, 3>);
            print_info(omni::math::dimensional<uint64_t, 3>);
        }
        
        void base_test()
        {
            dimensional(); printl("");
            angles(); printl("");
            circles(); printl("");
            lines(); printl("");
            rectangles(); printl("");
            triangles(); printl("");
            quadrilaterals(); printl("");
            are_equal(); printl("");
            area_of(); printl("");
            area_of_circle_sector(); printl("");
            arc_length(); printl("");
            calculate_point(); printl("");
            deg_to_rad(); printl("");
            delta(); printl("");
            distance_between_2_points(); printl("");
            is_nan(); printl("");
            ieee_remainder(); printl("");
            lerp_y(); printl("");
            lerp_x(); printl("");
            midpoint(); printl("");
            midpoint3d(); printl("");
            octant(); printl("");
            point_on_circle(); printl("");
            quadrant(); printl("");
            quadratic(); printl("");
            rad_to_deg(); printl("");
            radius_from_area(); printl("");
            round(); printl("");
            sign(); printl("");
            slope(); printl("");
            summation(); printl("");
            truncate(); printl("");
        }

        void dimensional()
        {
            /*
                typedef T dimension_t;
                dimensional()
                dimensional(const dimensional& cp)
                dimensional(T vals[SZ])
                dimensional(T val1, ...)
                ~dimensional() {}
                T at(std::size_t index)
                std::size_t size() const
                T& operator[](std::size_t idx)
                T operator[](std::size_t idx) const
                std::string to_string() const
                std::wstring to_wstring() const
                operator std::string()
                operator std::wstring()
                friend std::ostream& operator<<(std::ostream& os, const dimensional& v)
                friend std::wostream& operator<<(std::wostream& os, const dimensional& v)

                void copy(const dimensional& o)
                void copy(const dimensional<O_T, O_SZ>& o)
                void swap(const dimensional& o)
                void swap(const dimensional<O_T, O_SZ>& o)
                dimensional& operator=(const dimensional& o) 
                dimensional& operator=(const dimensional<O_T, O_SZ>& o) 
                bool operator==(const dimensional& o)
                bool operator==(const dimensional<O_T, O_SZ>& o)
            */
            omni::math::dimensional<double, 2> dd1(4.5, 9.5);
            omni::math::dimensional<double, 2> dd2;
            omni::math::dimensional<uint32_t, 3> di1(25, 50, 100);
            omni::math::dimensional<int32_t, 3> di3(-5, 10, 15);
            dd2[0] = OMNI_PI;

            printl("dd2[" << dd2.size() << "] = " << dd2);
            printl("di3[" << di3.size() << "] = " << di3);

            printl("dd2.at(0) = " << dd2.at(0) << ", dd2.at(1) = " << dd2.at(1));
            printl("di3[0] = " << di3[0] << ", di3[1] = " << di3[1]);

            if (!(dd2 == di3)) {
                printl("dd2 != di3");
            }
            if (dd2 != di3) {
                printl("dd2 != di3");
            }

            dd2.swap(di3);
            printl("dd2[" << dd2.size() << "] = " << dd2);
            printl("di3[" << di3.size() << "] = " << di3);

            printl("di1 = " << di1);
            di3 = di1;
            printl("di3 = " << di3);
            if (di3 == di1) {
                printl("di3 == di1");
            }

            printl("di1 = " << di1);
            printl("dd1 = " << dd1);
            di1.copy(dd1);
            if (di3 == di1) {
                printl("di3 == di1");
            } else {
                printl("di3 != di1");
            }
            printl("di1 = " << di1);
            printl("dd1 = " << dd1);
        }

        void angles()
        {
            // inline double calculate_angle(T x, T y, T bx, T by, T cx, T cy)
            // inline double calculate_angle(const omni::math::dimensional<T, 2>& a, const omni::math::dimensional<T, 2>& b, const omni::math::dimensional<T, 2>& c)
            test("omni::math::calculate_angle(0,0, 0,2, 2,0)", omni::math::calculate_angle(0,0, 0,2, 2,0), "90");

            test("omni::math::calculate_angle(2,2, 4,4, 2,4)", omni::math::calculate_angle(2,2, 4,4, 2,4), "45");

            //inline void rotate_point(double degrees, const omni::math::rotation_direction& dir, T center_x, T center_y, T& rotate_x, T& rotate_y)
            //inline void rotate_point(double degrees, const omni::math::rotation_direction& dir, T center_x, T center_y, omni::math::dimensional<T, 2>& rotate)
            //inline void rotate_point(double degrees, const omni::math::rotation_direction& dir, const omni::math::dimensional<T, 2>& center, omni::math::dimensional<T, 2>& rotate)

            omni::math::dimensional<double, 2> xy(4.0, 4.0);
            omni::math::rotate_point(45.0, omni::math::rotation_direction::CLOCKWISE, 2.0, 2.0, xy);
            test("omni::math::rotate_point(45.0, CLOCKWISE, 2.0, 2.0, {4.0, 4.0})", xy, "{4.82843,2}");
            omni::math::rotate_point(45.0, omni::math::rotation_direction::COUNTER_CLOCKWISE, 2.0, 2.0, xy);
            test("omni::math::rotate_point(45.0, COUNTER_CLOCKWISE, 2.0, 2.0, {4.82843, 2})", xy, "{4,4}");

            double x = 4.0; double y = 4.0;
            omni::math::rotate_point(45.0, omni::math::rotation_direction::CLOCKWISE, 2.0, 2.0, x, y);
            test("omni::math::rotate_point(45.0, CLOCKWISE, 2.0, 2.0, {4.0, 4.0})", (omni::math::dimensional<double, 2>(x,y)), "{4.82843,2}");
            printl("x = " << x << ", y = " << y);
            omni::math::rotate_point(45.0, omni::math::rotation_direction::COUNTER_CLOCKWISE, 2.0, 2.0, x, y);
            test("omni::math::rotate_point(45.0, COUNTER_CLOCKWISE, 2.0, 2.0, {4.82843, 2})", (omni::math::dimensional<double, 2>(x,y)), "{4,4}");
            printl("x = " << x << ", y = " << y);
        }

        void circles()
        {
            /*
                inline double area_of_circle(T radius)
                inline double area_of_circle(T value, const omni::math::circle_area& type)
                inline double area_of_circle_sector(T radius, T degrees)
                inline double area_of_circle_segment(T radius, T degrees)
                inline double circle_circumference(T radius)
                inline bool circle_contains_point(T center_x, T center_y, double radius, T x, T y, bool include_edge)
                inline bool circle_contains_point(T center_x, T center_y, double radius, T x, T y)
                inline bool circle_contains_point(T center_x, T center_y, double radius, const omni::math::dimensional<T, 2>& point, bool include_edge)
                inline bool circle_contains_point(T center_x, T center_y, double radius, const omni::math::dimensional<T, 2>& point)
                inline bool circles_intersect(T x1, T y1, double r1, T x2, T y2, double r2, bool include_edge)
                inline bool circles_intersect(T x1, T y1, double r1, T x2, T y2, double r2)
                inline double radius_from_area(T area)
            */
            test("area_of_circle(3)", omni::math::area_of_circle(3), "28.2743");

            test("area_of_circle(3, RAD)", omni::math::area_of_circle(3, omni::math::circle_area::RADIUS), "28.2743");
            test("area_of_circle(3, DIA)", omni::math::area_of_circle(3, omni::math::circle_area::DIAMETER), "7.06858");
            test("area_of_circle(3, CIR)", omni::math::area_of_circle(3, omni::math::circle_area::CIRCUMFERENCE), "0.716197");

            //template < typename T > double area_of_circle_sector(T radius, T degrees)
            test("area_of_circle_sector(3, 192)", omni::math::area_of_circle_sector(3, 192), "15.0796");
            
            //template < typename T > double area_of_circle_segment(T radius, T degrees)
            test("area_of_circle_segment(3, 192)", omni::math::area_of_circle_segment(3, 192), "16.0152");

            //inline double circle_circumference(T radius)
            test("circle_circumference(3.5)", omni::math::circle_circumference(3.5), "21.9911");
            
            //inline bool circle_contains_point(T center_x, T center_y, double radius, T x, T y, bool include_edge)
            test("circle_contains_point(10, 10, 3.5, 11, 11, true)", (omni::math::circle_contains_point(10, 10, 3.5, 11, 11, true) ? "true" : "false"), "true");
            
            //inline bool circle_contains_point(T center_x, T center_y, double radius, T x, T y)
            test("circle_contains_point(10, 10, 3.5, 11, 15)", (omni::math::circle_contains_point(10, 10, 3.5, 11, 15) ? "true" : "false"), "false");
            
            //inline bool circles_intersect(T x1, T y1, double r1, T x2, T y2, double r2, bool include_edge)
            test("circles_intersect(10, 10, 3.5, 13, 13, 3.5, true)", (omni::math::circles_intersect(10, 10, 3.5, 13, 13, 3.5, true) ? "true" : "false"), "true");
            
            //inline bool circles_intersect(T x1, T y1, double r1, T x2, T y2, double r2)
            test("circles_intersect(10, 10, 1.5, 15, 15, 1.5)", (omni::math::circles_intersect(10, 10, 1.5, 15, 15, 1.5) ? "true" : "false"), "false");
            
            //inline double radius_from_area(T area)
            test("radius_from_area(100)", omni::math::radius_from_area(100), "5.6419");
        }

        void clamp()
        {
            // template < typename T >
            // inline T& clamp(const T& value, const T& min_val, const T& max_val)

            // template < typename T >
            //inline T& clamp(const T& value, const T& min_val, const T& max_val, const omni::delegate<bool, T, T>& comp)
        }

        void lines()
        {
            /*
                inline void extend_line(T start_x, T start_y, T end_x, T end_y, T length, T& out_x, T& out_y)
                inline void extend_line(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T length, omni::math::dimensional<T, 2>& out)
                inline bool lines_intersect(T line1_x1, T line1_y1, T line1_x2, T line1_y2, T line2_x1, T line2_y1, T line2_x2, T line2_y2)
                inline bool lines_intersect(const omni::math::dimensional<T, 2>& line1_start, const omni::math::dimensional<T, 2>& line1_end, const omni::math::dimensional<T, 2>& line2_start, const omni::math::dimensional<T, 2>& line2_end)
                inline bool lines_intersect(const omni::math::dimensional<T, 4>& line1, const omni::math::dimensional<T, 4>& line2)
            */

            //inline void extend_line(T start_x, T start_y, T end_x, T end_y, T length, T& out_x, T& out_y)
            double x, y;
            omni::math::extend_line(3.0,2.0, 9.0,7.0, 0.5, x, y);
            test("omni::math::extend_line(3,2, 9,7, 0.5, x, y)", (omni::geometry::raw_point2d<double>(x,y)), "{3.38411,2.32009}");

            omni::math::extend_line(3.0,2.0, 9.0,7.0, 2.0, x, y);
            test("omni::math::extend_line(3,2, 9,7, 2, x, y)", (omni::geometry::raw_point2d<double>(x,y)), "{4.53644,3.28037}");

            //inline bool lines_intersect(T line1_x1, T line1_y1, T line1_x2, T line1_y2, T line2_x1, T line2_y1, T line2_x2, T line2_y2)
            test("lines_intersect(10,10, 20,20,  15,15, 25,5)", (omni::math::lines_intersect(10,10, 20,20,  15,15, 25,5) ? "true" : "false"), "true");

            test("lines_intersect(10,10, 20,20,  11,10, 21,20)", (omni::math::lines_intersect(10,10, 20,20,  11,10, 21,20) ? "true" : "false"), "false");
        }

        void rectangles()
        {
            /*
                inline T area_of_rectangle(T width, T height)
                inline bool rectangle_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
                inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, T x2, T y2)
                inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, const omni::math::dimensional<T, 2>& point)
                inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, T x, T y)
                inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, const omni::math::dimensional<T, 2>& point)
                inline void rectangle_reflect(T& x, T& y, T w, T h)
                inline void rectangle_translate_xy(T x, T y, T& ax, T& ay)
                inline void rectangle_translate_angle(T degrees, T distance, T& ax, T& ay)
                inline void rectangle_rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& w, T& h)
                inline void rectangle_rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& w, T& h)
            */

            double x,y,w,h;

            //template < typename T > inline T area_of_rectangle(T width, T height)
            test("area_of_rectangle(3.14, 4.2)", omni::math::area_of_rectangle(3.14, 4.2), "13.188");
            
            //inline bool rectangle_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
            omni::math::rectangle_get_centroid<double>(10,10, 20,10, 20,5, 10,5, x, y);
            test("rectangle_get_centroid(10,10, 20,10, 20,5, 10,5)", (omni::geometry::raw_point2d<double>(x,y)), "{15,7.5}");
            
            //inline bool rectangle_xywh_contains_point(T x, T y, T w, T h, T x2, T y2)
            test("rectangle_xywh_contains_point(10, 10, 15, 10, 24, 19)", (omni::math::rectangle_xywh_contains_point(10, 10, 15, 10, 24, 19) ? "true" : "false"), "true");
            test("rectangle_xywh_contains_point(10, 10, 10, 5, 24, 19)", (omni::math::rectangle_xywh_contains_point(10, 10, 10, 5, 24, 19) ? "true" : "false"), "false");
            
            //inline bool rectangle_ltrb_contains_point(T left, T top, T right, T bottom, T x, T y)
            test("rectangle_ltrb_contains_point(10, 10, 25, 20, 24, 19)", (omni::math::rectangle_ltrb_contains_point(10, 10, 25, 20, 24, 19) ? "true" : "false"), "true");
            test("rectangle_ltrb_contains_point(10, 10, 20, 15, 24, 19)", (omni::math::rectangle_ltrb_contains_point(10, 10, 20, 15, 24, 19) ? "true" : "false"), "false");
            
            //inline void rectangle_reflect(T& x, T& y, T w, T h)
            x = 10; y = 10; w = 10; h = 5;
            omni::math::rectangle_reflect(x, y, w, h);
            test("rectangle_reflect(10, 10, 10, 5)", (omni::geometry::raw_point2d<double>(x,y)), "{-20,-15}");
            
            //inline void rectangle_translate_xy(T x, T y, T& ax, T& ay)
            x = 5; y = 5; w = 10; h = 10;
            omni::math::rectangle_translate_xy(w,h,x,y);
            test("rectangle_translate_xy(10, 10, x, y)", (omni::geometry::raw_point2d<double>(x,y)), "{15,15}");
            
            //inline void rectangle_translate_angle(T degrees, T distance, T& ax, T& ay)
            x = 10; y = 10;
            omni::math::rectangle_translate_angle<double>(25.0, 15.0, x, y);
            test("rectangle_translate_angle(25, 15, x,y)", (omni::geometry::raw_point2d<double>(x,y)), "{16.3393,23.5946}");
            
            //inline void rectangle_rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& w, T& h)
            x = 10; y = 10; w = 10; h = 5;
            omni::math::rectangle_rotate_point(omni::math::rotation_angle::NINETY, x, y, omni::math::rotation_direction::COUNTER_CLOCKWISE, x, y, w, h);
            test("rectangle_rotate_point(90, CCW, 10, 10, 10, 10, 10, 5)", (omni::math::dimensional<double, 4>(x,y, w, h)), "{10,10,5,10}");
            
            //inline void rectangle_rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& w, T& h)
            x = 10; y = 10; w = 10; h = 5;
            omni::math::rectangle_rotate_origin(omni::math::rotation_angle::NINETY, omni::math::rotation_direction::CLOCKWISE, x, y, w, h);
            test("rectangle_rotate_origin(90, CW, 10, 10, 10, 5)", (omni::math::dimensional<double, 4>(x,y, w, h)), "{10,-10,5,10}");
        }

        void triangles()
        {
            /*
                inline double area_of_triangle(T base, T height)
                inline double area_of_triangle(T a, T b, T c)
                inline double area_of_triangle(T ax, T ay, T bx, T by, T cx, T cy)
                inline double area_of_triangle_sas(double degrees, T side1, T side2)
                inline double area_of_triangle_sss(T side1, T side2, T side3)
                inline bool triangle_contains_point(T x, T y, T ax, T ay, T bx, T by, T cx, T cy)
                inline bool triangle_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2, float epsilon)
                inline bool triangle_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2)
                inline void triangle_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
                inline void triangle_get_incenter(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
                inline void triangle_get_circumcenter(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
                inline void triangle_reflect(T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_rotate_point(T degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_rotate_origin(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_rotate_centroid(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_rotate_circumcenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_rotate_incenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_rotate_abc(T degrees, T x1, T y1, const omni::math::rotation_direction& dir, T& x2, T& y2, T& x3, T& y3)
                inline void triangle_translate_xy(T x, T y, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
                inline void triangle_translate_angle(T degrees, T distance, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            */

            double x,y;
            double ax,ay,bx,by,cx,cy;

            //template < typename T > inline double area_of_triangle(T base, T height)
            test("area_of_triangle(3.14, 4.2)", omni::math::area_of_triangle(3.14, 4.2), "6.594");

            //template < typename T > inline double area_of_triangle_sss(T a, T b, T c)
            test("area_of_triangle_sss(5.2, 7.1, 9.0)", omni::math::area_of_triangle_sss(5.2, 7.1, 9.0), "196.37166");

            //inline double area_of_triangle_sas(double degrees, T side1, T side2)
            test("area_of_triangle_sas(45, 9, 12)", omni::math::area_of_triangle_sas(45, 9, 12), "??");

            //inline bool triangle_contains_point(T x, T y, T ax, T ay, T bx, T by, T cx, T cy)
            test("triangle_contains_point(12,12, 10,10, 10,20, 15,15)", (omni::math::triangle_contains_point(12,12, 10,10, 10,20, 15,15) ? "true" : "false"), "true");
            test("triangle_contains_point(5,5, 10,10, 10,20, 15,15)", (omni::math::triangle_contains_point(5,5, 10,10, 10,20, 15,15) ? "true" : "false"), "false");

            //inline bool triangle_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2)
            test("triangle_intersects(10,10, 10,20, 15,15,  12,12, 8,8, 10,10)", (omni::math::triangle_intersects(10,10, 10,20, 15,15,  12,12, 8,8, 10,10) ? "true" : "false"), "true");
            test("triangle_intersects(10,10, 10,20, 15,15,  0,2, 2,2, 1,1)", (omni::math::triangle_intersects(10,10, 10,20, 15,15,  0,2, 2,2, 1,1) ? "true" : "false"), "false");
            

            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            //inline void triangle_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
            omni::math::triangle_get_centroid(ax, ay, bx, by, cx, cy, x, y);
            test("triangle_get_centroid(10,10, 10,20, 15,15)", (omni::math::dimensional<double, 2>(x,y)), "{?,?}");
            
            //inline void triangle_get_incenter(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
            omni::math::triangle_get_incenter(ax, ay, bx, by, cx, cy, x, y);
            test("triangle_get_incenter(10,10, 10,20, 15,15)", (omni::math::dimensional<double, 2>(x,y)), "{?,?}");
            
            //inline void triangle_get_circumcenter(T ax, T ay, T bx, T by, T cx, T cy, T& out_x, T& out_y)
            omni::math::triangle_get_circumcenter(ax, ay, bx, by, cx, cy, x, y);
            test("triangle_get_circumcenter(10,10, 10,20, 15,15)", (omni::math::dimensional<double, 2>(x,y)), "{?,?}");
            
            //inline void triangle_reflect(T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_reflect(ax, ay, bx, by, cx, cy);
            test("triangle_reflect(10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_rotate_point(T degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_rotate_point(190.0, 4.0, 4.0, omni::math::rotation_direction::CLOCKWISE, ax, ay, bx, by, cx, cy);
            test("triangle_rotate_point(190, 4,4, CW, 10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_rotate_origin(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_rotate_origin(190.0, omni::math::rotation_direction::CLOCKWISE, ax, ay, bx, by, cx, cy);
            test("triangle_rotate_origin(190, CW, 10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_rotate_centroid(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_rotate_centroid(190.0, omni::math::rotation_direction::CLOCKWISE, ax, ay, bx, by, cx, cy);
            test("triangle_rotate_centroid(90, CW, 10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_rotate_circumcenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_rotate_circumcenter(190.0, omni::math::rotation_direction::CLOCKWISE, ax, ay, bx, by, cx, cy);
            test("triangle_rotate_circumcenter190, CW, (10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_rotate_incenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_rotate_incenter(190.0, omni::math::rotation_direction::CLOCKWISE, ax, ay, bx, by, cx, cy);
            test("triangle_rotate_incenter(190, CW, 10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_rotate_abc(T degrees, T x1, T y1, const omni::math::rotation_direction& dir, T& x2, T& y2, T& x3, T& y3)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_rotate_abc(190.0, ax, ay, omni::math::rotation_direction::CLOCKWISE, bx, by, cx, cy);
            test("triangle_rotate_abc(190, 10,10, CW, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_translate_xy(T x, T y, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_translate_xy(4.0, 4.0, ax, ay, bx, by, cx, cy);
            test("triangle_translate_xy(4,4, 10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");
            
            //inline void triangle_translate_angle(T degrees, T distance, T& ax, T& ay, T& bx, T& by, T& cx, T& cy)
            ax = 10; ay = 10; bx = 10; by = 20; cx = 15; cy = 15;
            omni::math::triangle_translate_angle(190.0, 4.0, ax, ay, bx, by, cx, cy);
            test("triangle_translate_angle(190, 4, 10,10, 10,20, 15,15)", (omni::math::dimensional<double, 6>(ax,ay,bx,by,cx,cy)), "{?,?, ?,?, ?,?}");

        }
        
        void quadrilaterals()
        {
            /*
                inline double area_of_quadrilateral(T a, T b, T c, T d, double angle_a, double angle_c)
                inline double area_of_quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
                inline bool quadrilateral_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T dx1, T dy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2, T dx2, T dy2, float epsilon)
                inline bool quadrilateral_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T dx1, T dy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2, T dx2, T dy2)
                inline void quadrilateral_reflect(T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_rotate_point(T degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_rotate_origin(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_translate_xy(T x, T y, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_translate_angle(T degrees, T distance, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline bool quadrilateral_contains_point(T x, T y, T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
                inline void quadrilateral_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
                inline void quadrilateral_get_circumcenter(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
                inline void quadrilateral_get_incenter(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
                inline void quadrilateral_rotate_centroid(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_rotate_circumcenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_rotate_incenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
                inline void quadrilateral_rotate_abcd(T degrees, T x1, T y1, const omni::math::rotation_direction& dir, T& x2, T& y2, T& x3, T& y3, T& x4, T& y4)
            */

            double x,y, ax,ay,bx,by,cx,cy,dx,dy;
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;

            //inline double area_of_quadrilateral(T a, T b, T c, T d, double angle_a, double angle_c)
            test("area_of_quadrilateral(10, 10, 15, 12, 90, 60)", omni::math::area_of_quadrilateral(10,10,15,12,90,60), "??");

            //inline double area_of_quadrilateral(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
            test("area_of_quadrilateral(10,10, 10,20, 20,20, 25,10)", omni::math::area_of_quadrilateral(ax,ay,bx,by,cx,cy,dx,dy), "??");
            
            //inline bool quadrilateral_intersects(T ax1, T ay1, T bx1, T by1, T cx1, T cy1, T dx1, T dy1, T ax2, T ay2, T bx2, T by2, T cx2, T cy2, T dx2, T dy2)
            test("quadrilateral_intersects(10,10, 10,20, 20,20, 25,10,  15,15, 15,25, 25,25, 30,15)", (omni::math::quadrilateral_intersects(10,10, 10,20, 20,20, 25,10,  15,15, 15,25, 25,25, 30,15) ? "true" : "false"), "true");
            test("quadrilateral_intersects(10,10, 10,20, 20,20, 25,10,  5,5, 5,8, 8,8, 10,3)", (omni::math::quadrilateral_intersects(10,10, 10,20, 20,20, 25,10,  5,5, 5,8, 8,8, 10,3) ? "true" : "false"), "false");
            
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_reflect(T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_reflect(ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_reflect(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");
            
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_rotate_point(T degrees, T x, T y, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_rotate_point(120.0, 4.0,4.0, omni::math::rotation_direction::CLOCKWISE, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_rotate_point(120, 4,4, CW, 10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");
            
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_rotate_origin(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_rotate_origin(235.0, omni::math::rotation_direction::CLOCKWISE, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_rotate_origin(235, CW, 10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");
            
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_translate_xy(T x, T y, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_translate_xy(4.0,4.0, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_translate_xy(4,4, 10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");
            
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_translate_angle(T degrees, T distance, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_translate_angle(240.0, 5.0, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_translate_angle(240, 5, 10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");
            
            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline bool quadrilateral_contains_point(T x, T y, T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy)
            test("quadrilateral_contains_point(14,14, 10,10, 10,20, 20,20, 25,10)", (omni::math::quadrilateral_contains_point(14, 14, 10,10, 10,20, 20,20, 25,10) ? "true" : "false"), "true");
            test("quadrilateral_contains_point(5,5, 10,10, 10,20, 20,20, 25,10)", (omni::math::quadrilateral_contains_point(5, 5, 10,10, 10,20, 20,20, 25,10) ? "true" : "false"), "false");

            //inline void quadrilateral_get_centroid(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
            omni::math::quadrilateral_get_centroid(ax,ay, bx,by, cx,cy, dx,dy, x, y);
            test("quadrilateral_get_centroid(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 2>(x,y)), "{?,?}");

            //inline void quadrilateral_get_circumcenter(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
            omni::math::quadrilateral_get_circumcenter(ax,ay, bx,by, cx,cy, dx,dy, x,y);
            test("quadrilateral_get_circumcenter(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 2>(x,y)), "{?,?}");

            //inline void quadrilateral_get_incenter(T ax, T ay, T bx, T by, T cx, T cy, T dx, T dy, T& out_x, T& out_y)
            omni::math::quadrilateral_get_incenter(ax,ay, bx,by, cx,cy, dx,dy, x, y);
            test("quadrilateral_get_incenter(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 2>(x,y)), "{?,?}");

            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_rotate_centroid(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_rotate_centroid(235.0, omni::math::rotation_direction::CLOCKWISE, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_rotate_centroid(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");

            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_rotate_circumcenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_rotate_circumcenter(235.0, omni::math::rotation_direction::CLOCKWISE, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_rotate_circumcenter(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");

            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_rotate_incenter(T degrees, const omni::math::rotation_direction& dir, T& ax, T& ay, T& bx, T& by, T& cx, T& cy, T& dx, T& dy)
            omni::math::quadrilateral_rotate_incenter(235.0, omni::math::rotation_direction::CLOCKWISE, ax,ay, bx,by, cx,cy, dx,dy);
            test("quadrilateral_rotate_incenter(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");

            ax = 10; ay = 10; bx = 10; by = 20; cx = 20; cy = 20; dx = 25; dy = 10;
            //inline void quadrilateral_rotate_abcd(T degrees, T x1, T y1, const omni::math::rotation_direction& dir, T& x2, T& y2, T& x3, T& y3, T& x4, T& y4)
            omni::math::quadrilateral_rotate_abcd(235.0, ax,ay, omni::math::rotation_direction::CLOCKWISE, bx,by, cx,cy, dx,dy);
            test("quadrilateral_rotate_abcd(10,10, 10,20, 20,20, 25,10)", (omni::math::dimensional<double, 8>(ax,ay,bx,by,cx,cy,dx,dy)), "{?,?, ?,?, ?,?, ?,?}");

        }

        void are_equal()
        {
            //template <> inline bool are_equal<int64_t>(int64_t x, int64_t y) { return x == y; }
            test("are_equal(4.0, 2.4)", b2s(omni::math::are_equal(4.0, 2.4)), "false");
            test("are_equal(4, 2)", b2s(omni::math::are_equal(4, 2)), "false");
            test("are_equal(4, 4)", b2s(omni::math::are_equal(4, 4)), "true");
            test("are_equal(4.001, 4.001)", b2s(omni::math::are_equal(4.001, 4.001)), "true");
            test("are_equal(-2, -2)", b2s(omni::math::are_equal(-2, -2)), "true");
        }

        void area_of()
        {
            //template < typename T > double area_of_circle(T radius)
            test("area_of_circle(3)", omni::math::area_of_circle(3), "28.2743");

            test("area_of_circle(3, RAD)", omni::math::area_of_circle(3, omni::math::circle_area::RADIUS), "28.2743");
            test("area_of_circle(3, DIA)", omni::math::area_of_circle(3, omni::math::circle_area::DIAMETER), "7.06858");
            test("area_of_circle(3, CIR)", omni::math::area_of_circle(3, omni::math::circle_area::CIRCUMFERENCE), "0.716197");

            //template < typename T > inline T area_of_rectangle(T width, T height)
            test("area_of_rectangle(3.14, 4.2)", omni::math::area_of_rectangle(3.14, 4.2), "13.188");

            //template < typename T > inline double area_of_triangle(T base, T height)
            test("area_of_triangle(3.14, 4.2)", omni::math::area_of_triangle(3.14, 4.2), "6.594");

            //template < typename T > inline double area_of_triangle(T a, T b, T c)
            test("area_of_triangle(5.2, 7.1, 9.0)", omni::math::area_of_triangle(5.2, 7.1, 9.0), "2.89571");
        }

        void area_of_circle_sector()
        {
            //template < typename T > double area_of_circle_sector(T radius, T degrees)
            test("area_of_circle_sector(3, 192)", omni::math::area_of_circle_sector(3, 192), "15.0796");
            
            //template < typename T > double area_of_circle_segment(T radius, T degrees)
            test("area_of_circle_segment(3, 192)", omni::math::area_of_circle_segment(3, 192), "16.0152");
        }

        void arc_length()
        {
            // template < typename T > inline double arc_length(T radius, T degrees)
            test("arc_length(3, 192)", omni::math::arc_length(3, 192), "10.0531");
        }

        void calculate_point()
        {
            //inline void calculate_point(T start_x, T start_y, T end_x, T end_y, T len, T& out_x, T& out_y)
            //inline omni::math::dimensional<T, 2> calculate_point(T start_x, T start_y, T end_x, T end_y, T len)
            //template < typename T > inline void calculate_point(T start_x, T start_y, T end_x, T end_y, T len, T& out_x, T& out_y)
            double pt_x = 0.0;
            double pt_y = 0.0;
            double plen = 0.4;
            
            omni::math::calculate_point(6.4, 3.0, -10.7, 4.0, plen, pt_x, pt_y);
            test("calculate_point(6.4,3, -10.7,4, 0.4)", omni::geometry::point2d<double>(pt_x,pt_y), "{6.00068,3.02335}");

            // template < typename T > inline omni::math::dimensional<T, 2> calculate_point(T start_x, T start_y, T end_x, T end_y, T len)
            omni::math::dimensional<double, 2> ptcalc_d = omni::math::calculate_point(3.0, 2.0, 9.0, 7.0, 0.5);
            test("calculate_point(3.0,2.0, 9.0,7.0, 0.5)", ptcalc_d, "{3.38411,2.32009}");
            omni::math::dimensional<int, 2> ptcalc_i = omni::math::calculate_point(3, 2, 9, 7, 2);
            test("calculate_point(3,2, 9,7, 2)", ptcalc_i, "{4,3}");
        }

        void deg_to_rad()
        {
            //inline double deg_to_rad(double deg)
            //inline double degrees_to_radians(double deg)
            test("deg_to_rad(57.868758)", omni::math::deg_to_rad(57.868758), "1.01");
            test("degrees_to_radians(57.868758)", omni::math::degrees_to_radians(57.868758), "1.01");
        }

        void delta()
        {
            //template < typename T > T delta(const T& a, const T& b)
            test("delta(2.2,1.2)", omni::math::delta(2.2, 1.2), "1");
            test("delta(2,1)", omni::math::delta(2, 1), "1");
            
            //template < typename T > T delta_squared(const T& a, const T& b)
            test("delta_squared(4.2,1.2)", omni::math::delta_squared(4.2, 1.2), "9");
            test("delta_squared(4,1)", omni::math::delta_squared(4, 1), "9");
        }

        void distance_between_2_points()
        {
            //template < typename T > double distance_between_2_points(T start_x, T start_y, T end_x, T end_y)
            test("distance_between_2_points(3,2,9,7)", omni::math::distance_between_2_points(3,2,9,7), "7.81025");
            
            //template < typename T > inline double distance_between_2_points(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            test("distance_between_2_points(8,2,6,3,5,7)", omni::math::distance_between_2_points(8,2,6,3,5,7), "5.91608");
            //template < typename T > inline double distance_between_2_points(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 3; x1[1] = 2;
            x2[0] = 9; x2[1] = 7;
            test("distance_between_2_points(x1{3,2},x2{9,7})", omni::math::distance_between_2_points(x1, x2), "7.81025");
            //template < typename T > inline double distance_between_2_points(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            omni::math::dimensional<int, 3> xx1;
            omni::math::dimensional<int, 3> xx2;
            xx1[0] = 3; xx1[1] = 2; xx1[2] = 1;
            xx2[0] = 9; xx2[1] = 7; xx2[2] = 1;
            test("distance_between_2_points(x1{3,2,1},x2{9,7,1})", omni::math::distance_between_2_points(xx1, xx2), "7.81025");
        }

        void is_nan()
        {
            test("is_nan(4.0)", b2s(omni::math::is_nan(4.0)), "false");
            test("is_nan(OMNI_NAN)", b2s(omni::math::is_nan(OMNI_NAN)), "true");
            test("is_nan(std::sqrt(-1))", b2s(omni::math::is_nan(std::sqrt(-1.0))), "true");
        }

        void ieee_remainder()
        {
            //static double ieee_remainder(double x, double y)
            test("ieee_remainder(4.2, 7.5)", omni::math::ieee_remainder(4.2, 7.5), "0.56");
        }

        void lerp_y()
        {
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 3; x1[1] = 2;
            x2[0] = 9; x2[1] = 7;

            //template < typename T > double lerp_y(T x1, T y1, T x2, T y2, T x)
            test("lerp_y<double>(3,2,9,7,4)", omni::math::lerp_y<double>(3.0,2.0,9.0,7.0,4.0), "2.833333");
            //template < typename T > inline double linear_interpolation_y(T x1, T y1, T x2, T y2, T x)
            test("linear_interpolation_y(3.0,2.0,9.0,7.0,4.3333)", omni::math::linear_interpolation_y(3.0,2.0,9.0,7.0,4.3333), "3.11108");
            //template < typename T > inline double linear_interpolation_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
            test("linear_interpolation_y(3,2,9,7,4)", omni::math::linear_interpolation_y(x1, x2, 4), "2");
            //template < typename T > inline double lerp_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
            test("lerp_y(3,2,9,7,4)", omni::math::lerp_y(x1, x2, 4), "2");
        }

        void lerp_x()
        {
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 3; x1[1] = 2;
            x2[0] = 9; x2[1] = 7;
            
            //template < typename T > double lerp_x(T x1, T y1, T x2, T y2, T y)
            test("lerp_x<double>(3,2,9,7,2)", omni::math::lerp_x<double>(3,2,9,7,2), "3");
            //template < typename T > inline double linear_interpolation_x(T x1, T y1, T x2, T y2, T y)
            test("linear_interpolation_x(3.0,2.0,9.0,7.0,2.8333)", omni::math::linear_interpolation_x(3.0,2.0,9.0,7.0,2.8333), "3.99996");
            //template < typename T > inline double linear_interpolation_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
            test("linear_interpolation_x(3,2,9,7,2)", omni::math::linear_interpolation_x(x1, x2, 2), "3");
            //template < typename T > inline double lerp_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
            test("lerp_x(3,2,9,7,2)", omni::math::lerp_x(x1, x2, 2), "3");
        }

        void midpoint()
        {
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 3; x1[1] = 2;
            x2[0] = 9; x2[1] = 7;
            
            double mid_x = 0.0;
            double mid_y = 0.0;
            //template < typename T > inline void midpoint(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z, T& mid_x, T& mid_y, T& mid_z)
            omni::math::midpoint(6.4, 3.0, -10.7, 4.0, mid_x, mid_y);
            test("midpoint(6.4,3, -10.7,4)", omni::geometry::point2d<double>(mid_x, mid_y) , "{-2.15,3.5}");
            //template < typename T > inline omni::math::dimensional<T, 2> midpoint(T start_x, T start_y, T end_x, T end_y)
            omni::math::dimensional<int, 2> m1 = omni::math::midpoint(3, 2, 9, 7);
            test("midpoint(3,2,9,7)", m1, "{6,4}");
            //template < typename T > inline omni::math::dimensional<T, 2> midpoint(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            omni::math::dimensional<int, 2> m2 = omni::math::midpoint(x1, x2);
            test("midpoint(3,2,9,7)", m2, "{6,4}");
        }

        void midpoint3d()
        {
            omni::math::dimensional<int, 3> xx1;
            omni::math::dimensional<int, 3> xx2;
            xx1[0] = 3; xx1[1] = 2; xx1[2] = 1;
            xx2[0] = 9; xx2[1] = 7; xx2[2] = 1;
            //inline void midpoint3d(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z, T& mid_x, T& mid_y, T& mid_z)
            //inline omni::math::dimensional<T, 3> midpoint3d(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            //inline omni::math::dimensional<T, 3> midpoint3d(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            //template < typename T > inline omni::math::dimensional<T, 3> midpoint(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            double mid_x = 0.0;
            double mid_y = 0.0;
            double mid_z = 0.0;
            omni::math::midpoint3d(4.0, 2.0, 1.5, 8.5, 7.2, 2.5, mid_x, mid_y, mid_z);
            printv("midpoint3d(4,2,1.5, 8.5,7.2,2.5) = {", mid_x << "," << mid_y << "," << mid_z << "} -- expected: {6.25, 4.6, 2}" << " | " <<
                ((omni::math::are_equal(mid_x, 6.25) && omni::math::are_equal(mid_y, 4.6) && omni::math::are_equal(mid_z, 2.0)) ? "PASS" : "FAIL")
            );

            omni::math::dimensional<int, 3> mm1 = omni::math::midpoint3d(3, 2, 1, 9, 7, 1);
            test("midpoint3d(3,2,1, 9,7,1)", mm1, "{6,4,1}");
            //template < typename T > inline omni::math::dimensional<T, 3> midpoint(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            omni::math::dimensional<int, 3> mm2 = omni::math::midpoint3d(xx1, xx2);
            test("midpoint3d(3,2,1, 9,7,1)", mm2, "{6,4,1}");
        }

        void octant()
        {
            omni::math::dimensional<int, 3> xx1;
            xx1[0] = 3; xx1[1] = 2; xx1[2] = 1;
            //inline omni::math::ordinal_name octant(T x, T y, T z)
            //inline omni::math::ordinal_name octant(const omni::math::dimensional<T, 3>& point)
            //template < typename T > inline omni::math::ordinal_name octant(T x, T y, T z)
            test("octant(1,1,1)", omni::math::octant(1,1,1), "I");
            test("octant(-1,1,1)", omni::math::octant(-1,1,1), "II");
            test("octant(-1,-1,1)", omni::math::octant(-1,-1,1), "III");
            test("octant(1,-1,1)", omni::math::octant(1,-1,1), "IV");
            test("octant(1,1,-1)", omni::math::octant(1,1,-1), "V");
            test("octant(-1,1,-1)", omni::math::octant(-1,1,-1), "VI");
            test("octant(-1,-1,-1)", omni::math::octant(-1,-1,-1), "VII");
            test("octant(1,-1,-1)", omni::math::octant(1,-1,-1), "VIII");
            test("octant(1,0,0)", omni::math::octant(1,0,0), "X_AXIS");
            test("octant(0,1,0)", omni::math::octant(0,1,0), "Y_AXIS");
            test("octant(0,0,1)", omni::math::octant(0,0,1), "Z_AXIS");
            //template < typename T > inline omni::math::ordinal_name octant(const omni::math::dimensional<T, 3>& point)
            test("octant(2,2,2)", omni::math::octant(xx1), "I");
        }

        void point_on_circle()
        {
            //inline void point_on_circle(T angle, T radius, T center_x, T center_y, T& out_x, T& out_y)
            double deg = 243;
            double r = 20;
            double x = 10;
            double y = 10;
            double ox = 0;
            double oy = 0;
            omni::math::point_on_circle(deg, r, x, y, ox, oy);
            printl("point_on_circle(243, 20, 10, 10,...) = {" << ox << ", " << oy << "} -- expected: {-7.82013, 0.92019} | " <<
                ((omni::math::are_equal(ox, -7.82013) && omni::math::are_equal(oy, 0.92019)) ? "PASS" : "FAIL")
            );

            /*
                                                                                   0d
                                                     |                             |
              270d  |--R--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--C--| 90d
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                             243d                    |                             |
                              X                      |                             |
                    |__|__|__|__|__|__|__|__|__|__|__0__|__|__|__|__|__|__|__|__|__|__|
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             |
                                                     |                             R
                                                     |                             |
                                                                                  180d
            
            */
        }

        void quadrant()
        {
            omni::math::dimensional<int, 2> x1;
            x1[0] = 3; x1[1] = 2;
            
            //inline omni::math::ordinal_name quadrant(T x, T y)
            //inline omni::math::ordinal_name quadrant(const omni::math::dimensional<T, 2>& point)
            //template < typename T > inline omni::math::ordinal_name quadrant(T x, T y)
            test("quadrant(1,1)", omni::math::quadrant(1,1), "I");
            test("quadrant(-1,1)", omni::math::quadrant(-1,1), "II");
            test("quadrant(-1,-1)", omni::math::quadrant(-1,-1), "III");
            test("quadrant(1,-1)", omni::math::quadrant(1,-1), "IV");
            test("quadrant(1,0)", omni::math::quadrant(1,0), "X_AXIS");
            test("quadrant(0,1)", omni::math::quadrant(0,1), "Y_AXIS");
            test("quadrant(0,0)", omni::math::quadrant(0,0), "ORIGIN");
            //template < typename T > inline omni::math::ordinal_name quadrant(const omni::math::dimensional<T, 2>& point)
            test("quadrant(2,2)", omni::math::quadrant(x1), "I");
        }

        void quadratic()
        {
            //inline void quadratic(T a, T b, T c, T& x_plus, T& x_minus)
            //inline omni::math::dimensional<T, 2> quadratic(T a, T b, T c)

            //template < typename T > inline void quadratic(T a, T b, T c, T& x_plus, T& x_minus)
            double xp = 0.0;
            double xm = 0.0;
            omni::math::quadratic(5.0, 6.0, 1.0, xp, xm);
            test("quad(5,6,1)", omni::geometry::point2d<double>(xp, xm), "{-0.2,-1}");
            
            //template < typename T > inline omni::math::dimensional<T, 2> quadratic(T a, T b, T c)
            omni::math::dimensional<double, 2> q = omni::math::quadratic(5.0, 6.0, 1.0);
            test("quad(5,6,1)", q, "{-0.2,-1}");
        }

        void rad_to_deg()
        {
            //inline double rad_to_deg(double rad)
            //inline double radians_to_degrees(double rad)
            test("rad_to_deg(1.01)", omni::math::rad_to_deg(1.01), "57.8687");
            test("radians_to_degrees(1.01)", omni::math::radians_to_degrees(1.01), "57.8687");
        }

        void radius_from_area()
        {
            //inline double radius_from_area(T area)
            //template < typename T > double radius_from_area(T area)
            test("radius_from_area(28.27)", omni::math::radius_from_area(28.27), "2.99977");
        }

        void round()
        {
            //inline double round(double val, uint8_t digits, const omni::math::midpoint_rounding& direction)
            //inline double round(double val, uint8_t digits, std::float_round_style direction)
            //inline double round(double val, uint8_t digits)
            //inline double round(double val)
            //inline double round(double val, uint8_t digits, const omni::math::midpoint_rounding& direction)
            test("round(3.14159, 3, omni::math::midpoint_rounding::TO_EVEN)", omni::math::round(3.14159, 3, omni::math::midpoint_rounding::TO_EVEN), "3.142");
            test("round(3.14159, 3, omni::math::midpoint_rounding::AWAY_FROM_ZERO)", omni::math::round(3.14159, 3, omni::math::midpoint_rounding::AWAY_FROM_ZERO), "3.142");
            test("round(3.14159, 3, omni::math::midpoint_rounding::TO_ZERO)", omni::math::round(3.14159, 3, omni::math::midpoint_rounding::TO_ZERO), "3.14");
            test("round(3.14159, 3, omni::math::midpoint_rounding::TO_NEGATIVE_INFINITY)", omni::math::round(3.14159, 3, omni::math::midpoint_rounding::TO_NEGATIVE_INFINITY), "3.14");
            test("round(3.14159, 3, omni::math::midpoint_rounding::TO_POSITIVE_INFINITY)", omni::math::round(3.14159, 3, omni::math::midpoint_rounding::TO_POSITIVE_INFINITY), "3.142");

            //inline double round(double val, uint8_t digits, std::float_round_style direction)
            test("round(3.14159, 3, std::round_to_nearest)", omni::math::round(3.14159, 3, std::round_to_nearest), "3.142");
            test("round(3.14159, 3, std::round_indeterminate)", omni::math::round(3.14159, 3, std::round_indeterminate), "3.142");
            test("round(3.14159, 3, std::round_toward_zero)", omni::math::round(3.14159, 3, std::round_toward_zero), "3.14");
            test("round(3.14159, 3, std::round_toward_neg_infinity)", omni::math::round(3.14159, 3, std::round_toward_neg_infinity), "3.14");
            test("round(3.14159, 3, std::round_toward_infinity)", omni::math::round(3.14159, 3, std::round_toward_infinity), "3.142");

            //inline double round(double val, uint8_t digits)
            test("round(3.14159, 4)", omni::math::round(3.14159, 4), "3.1416");
            test("round(3.14159, 3)", omni::math::round(3.14159, 3), "3.142");
            test("round(3.14159, 2)", omni::math::round(3.14159, 2), "3.14");
            test("round(3.14159, 1)", omni::math::round(3.14159, 1), "3.1");
            //inline double round(double val)
            test("round(3.14159)", omni::math::round(3.14159), "3");
            test("round(3.90001)", omni::math::round(3.90001), "4");
        }

        void sign()
        {
            //inline T sign(T val)
            test("sign(3.14159)", omni::math::sign(3.14159), "1");
            test("sign(-3.14159)", omni::math::sign(-3.14159), "-1");
            test("sign(0.0)", omni::math::sign(0.0), "0");
        }

        void slope()
        {
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 3; x1[1] = 2;
            x2[0] = 9; x2[1] = 7;
            //inline double slope(T start_x, T start_y, T end_x, T end_y)
            //inline double slope(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            //template < typename T > inline double slope(T start_x, T start_y, T end_x, T end_y)
            test("slope(1,2,4,3) (1/3)", omni::math::slope(1,2,4,3), "0.333333");
            //template < typename T > inline double slope(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            test("slope(3,2,9,7) (5/6)", omni::math::slope(x1, x2), "0.833333");
        }

        void summation()
        {
            //inline T summation(T index, T end, const omni::delegate1<T, T>& sum)
            //inline T summation(T index, T end, const omni::delegate1<T, T>& sum, const omni::delegate1<bool, T>& break_cond)
            //template < typename T > inline T summation(T index, T end, const omni::delegate1<T, T>& sum)
            omni::delegate1<int, int> d = &summer;
            test("summation(2,7,(2k+3))", omni::math::summation(2, 7, d), "72");
            //inline T summation(T index, T end, const omni::delegate1<T, T>& sum, const omni::delegate1<bool, T>& break_cond)
            omni::delegate1<bool, int> b = &break_summer;
            test("summation(2,7,(2k+3))", omni::math::summation(2, 7, d, b), "16");
        }

        void truncate()
        {
            //inline double truncate(double val)
            //inline double trunc(double val)
            test("truncate(3.14159)", omni::math::truncate(3.14159), "3");
            test("trunc(3.14159)", omni::math::trunc(3.14159), "3");
        }

    private:
        static int summer(int val)
        {
            return (2*val) + 3;
        }

        static bool break_summer(int val)
        {
            return val > 10;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMESPAN
