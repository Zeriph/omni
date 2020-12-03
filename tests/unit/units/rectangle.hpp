#if defined(OMNI_UTUA) || defined(OMNI_UT_RECTANGLE)

#define UT_NAME rectangle
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(rectangle, "test the functionality in omni::geometry::rectangle");
            M_LIST_ADD(raw_rectangle, "test the functionality in omni::geometry::raw_rectangle");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::rectangle<int32_t>);
            print_info(omni::geometry::raw_rectangle<int32_t>);
        }
        
        void base_test()
        {
            rectangle(); printl("");
            raw_rectangle(); printl("");
        }

        void rectangle()
        {
            // rectangle ~~  omni::geometry::rectangle::rectangle()
            omni::geometry::rectangle<int32_t> temp_val(5,10, 15,20);
            omni::geometry::rectangle<int32_t> sq(5,10, 15,15);
            omni::geometry::point2d<int32_t> val(5,10);
            omni::geometry::rectangle<int32_t> _rect(5,15, 20,10);
            omni::geometry::rectangle<int32_t> _r2(8,15, 17,19);
            omni::math::rotation_direction _dir = omni::math::rotation_direction::CLOCKWISE;
            omni::math::rotation_angle _degrees = omni::math::rotation_angle::NINETY;
            float _angle = 45.0; int32_t _distance = 10;
            int32_t _x, _y, _w, _h, _left, _top, _right, _bottom;
            _x = 10; _y = 12;
            _w = 6; _h = 12;
            _left = 10; _top = 10; _right = 20; _bottom = 15;

            printl("Testing constructors");
            try {
                omni::geometry::rectangle<int32_t> fail(10,15,  -10,-15);
                printv("Shouldn't see this: ", fail.area());
            } catch (const std::exception& ex) {
                printv("Exception: ", ex.what());
            }

            try {
                omni::geometry::point2d<int32_t> tpt1(10, 10);
                omni::geometry::point2d<int32_t> tpt2(20, 20);
                omni::geometry::rectangle<int32_t> notfail(tpt1, tpt2);
                printv("Should see this: ", notfail.area());
            } catch (const std::exception& ex) {
                printv("Exception: ", ex.what());
            }

            printv("temp_val.hash_code() = ", temp_val.hash_code());
            
            // area ~~ T omni::geometry::rectangle::area()
            test("temp_val.area()", temp_val.area(), "300");
            
            // bottom ~~ T omni::geometry::rectangle::bottom()
            test("temp_val.bottom()", temp_val.bottom(), "30");

            // bottom_left ~~ omni::geometry::point2d<T> omni::geometry::rectangle::bottom_left()
            test("temp_val.bottom_left()", temp_val.bottom_left(), "{?}");

            // bottom_right ~~ omni::geometry::point2d<T> omni::geometry::rectangle::bottom_right()
            test("temp_val.bottom_right()", temp_val.bottom_right(), "{?}");
            
            // centroid ~~ omni::geometry::point2d<T> omni::geometry::rectangle::centroid()
            test("temp_val.centroid()", temp_val.centroid(), "{12,20}");
            
            // circle_from_circumcenter ~~ omni::geometry::circle<T> omni::geometry::rectangle::circle_from_circumcenter()
            test("temp_val.circle_from_circumcenter()", temp_val.circle_from_circumcenter(), "{{12,20} R:12.5}");
            
            // circle_from_incenter ~~ omni::geometry::circle<T> omni::geometry::rectangle::circle_from_incenter()
            test("temp_val.circle_from_incenter()", temp_val.circle_from_incenter(), "{{12,20} R:7.5}");
            
            // circumcenter ~~ omni::geometry::point2d<T> omni::geometry::rectangle::circumcenter()
            test("temp_val.circumcenter()", temp_val.circumcenter(), "{12,20}");
            
            // compare ~~ omni::math::shape_comparator omni::geometry::rectangle::compare(const rectangle<T>& rect)
            test("temp_val.compare(_rect)", temp_val.compare(_rect), "NOT_EQUAL");
            
            // contains ~~ bool omni::geometry::rectangle::contains(T x, T y)
            test("temp_val.contains(_x, _y)", (temp_val.contains(_x, _y) ? "true" : "false"), "true");
            
            // decrement ~~ void omni::geometry::rectangle::decrement(T x, T y)
            temp_val.decrement(_x, _y);
            test("temp_val.decrement(_x, _y)", temp_val, "{{-5,-2},{15,20}}");
            
            // decrement_x ~~ T omni::geometry::rectangle::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "-6");
            
            // decrement_y ~~ T omni::geometry::rectangle::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "-3");

            // deflate ~~ void omni::geometry::rectangle::deflate(percent)
            temp_val.deflate(15.0);
            test("temp_val.deflate(percent)", temp_val, "{?}");
            temp_val.set_location(-6,-3);
            temp_val.set_size(15,20);
            
            // deflate ~~ void omni::geometry::rectangle::deflate(T w, T h)
            temp_val.deflate(_w, _h);
            test("temp_val.deflate(_w, _h)", temp_val, "{?}");
            temp_val.set_location(-6,-3);
            temp_val.set_size(15,20);
            
            // diagonal ~~ double omni::geometry::rectangle::diagonal()
            test("temp_val.diagonal()", temp_val.diagonal(), "?");
            
            // edge ~~ omni::geometry::raw_point2d<T> omni::geometry::rectangle::edge()
            test("temp_val.edge()", temp_val.edge(), "{?}");
            
            // empty ~~ bool omni::geometry::rectangle::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // equals ~~ bool omni::geometry::rectangle::equals(T x, T y, T w, T h)
            test("temp_val.equals(_x, _y, _w, _h)", (temp_val.equals(_x, _y, _w, _h) ? "true" : "false"), "false");
            
            // height ~~ T omni::geometry::rectangle::height()
            test("temp_val.height()", temp_val.height(), "?");
            
            // incenter ~~ omni::geometry::point2d<T> omni::geometry::rectangle::incenter()
            test("temp_val.incenter()", temp_val.incenter(), "{?}");
            
            // increment ~~ void omni::geometry::rectangle::increment(T x, T y)
            temp_val.increment(_x, _y);
            test("temp_val.increment(_x, _y)", temp_val, "{?}");
            
            // increment_x ~~ T omni::geometry::rectangle::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "?");
            
            // increment_y ~~ T omni::geometry::rectangle::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "?");

            // inflate ~~ void omni::geometry::rectangle::inflate(percent)
            temp_val.inflate(15.0);
            test("temp_val.inflate(percent)", temp_val, "{?}");
            temp_val.set_location(-6,-3);
            temp_val.set_size(15,20);
            
            // inflate ~~ void omni::geometry::rectangle::inflate(T w, T h)
            temp_val.inflate(_w, _h);
            test("temp_val.inflate(_w, _h)", temp_val, "{?}");
            
            // intersect ~~ void omni::geometry::rectangle::intersect(const rectangle<T>& r2)
            temp_val.intersect(_r2);
            test("temp_val.intersect(_r2)", temp_val, "{?}");
            
            // temp_val = {5,10},{w:15,h:20}
            // { 5,10} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {20,10} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} { 8,15} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {25,15} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            // { 5,30} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {20,30} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} { 8,34} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {25,34} {..,..}
            // 
            // _r2      = {8,15},{w:17,h:19}
            // {8,15}  {25,15}
            // {8,34}  {25,34}
            /*
                
            */
            //         { 8,15} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..}
            //         {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {..,..} {20,30}
            // new intersection:
            // { 8,15},{w:15,h:12}

            // intersects_with ~~ bool omni::geometry::rectangle::intersects_with(T left, T top, T right, T bottom)
            test("temp_val.intersects_with(_left, _top, _right, _bottom)", (temp_val.intersects_with(_left, _top, _right, _bottom) ? "true" : "false"), "true");
            
            // is_square ~~ bool omni::geometry::rectangle::is_square()
            test("temp_val.is_square()", (temp_val.is_square() ? "true" : "false"), "false");
            test("sq.is_square()", (sq.is_square() ? "true" : "false"), "true");

            // left ~~ T omni::geometry::rectangle::left()
            test("temp_val.left()", temp_val.left(), "?");
            
            // location ~~ omni::geometry::raw_point2d<T> omni::geometry::rectangle::location()
            test("temp_val.location()", temp_val.location(), "{?}");
            
            // offset ~~ void omni::geometry::rectangle::offset(T x, T y)
            temp_val.offset(_x, _y);
            test("temp_val.offset(_x, _y)", temp_val, "?");
            
            // perimeter ~~ T omni::geometry::rectangle::perimeter()
            test("temp_val.perimeter()", temp_val.perimeter(), "?");
            
            // reflect ~~ void omni::geometry::rectangle::reflect()
            temp_val.reflect();
            test("temp_val.reflect()", temp_val, "?");
            
            // right ~~ T omni::geometry::rectangle::right()
            test("temp_val.right()", temp_val.right(), "?");
            
            // rotate_centroid ~~ void omni::geometry::rectangle::rotate_centroid(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_centroid(_degrees, _dir);
            test("temp_val.rotate_centroid(_degrees, _dir)", temp_val, "?");
            
            // rotate_circumcenter ~~ void omni::geometry::rectangle::rotate_circumcenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_circumcenter(_degrees, _dir);
            test("temp_val.rotate_circumcenter(_degrees, _dir)", temp_val, "?");
            
            // rotate_incenter ~~ void omni::geometry::rectangle::rotate_incenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_incenter(_degrees, _dir);
            test("temp_val.rotate_incenter(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_lb ~~ void omni::geometry::rectangle::rotate_on_lb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_lb(_degrees, _dir);
            test("temp_val.rotate_on_lb(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_lt ~~ void omni::geometry::rectangle::rotate_on_lt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_lt(_degrees, _dir);
            test("temp_val.rotate_on_lt(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_rb ~~ void omni::geometry::rectangle::rotate_on_rb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_rb(_degrees, _dir);
            test("temp_val.rotate_on_rb(_degrees, _dir)", temp_val, "?");
            
            // rotate_on_rt ~~ void omni::geometry::rectangle::rotate_on_rt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_rt(_degrees, _dir);
            test("temp_val.rotate_on_rt(_degrees, _dir)", temp_val, "?");
            
            // rotate_origin ~~ void omni::geometry::rectangle::rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_origin(_degrees, _dir);
            test("temp_val.rotate_origin(_degrees, _dir)", temp_val, "?");
            
            // rotate_point ~~ void omni::geometry::rectangle::rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir)
            temp_val.rotate_point(_degrees, _x, _y, _dir);
            test("temp_val.rotate_point(_degrees, _x, _y, _dir)", temp_val, "?");
            
            // scale ~~ void omni::geometry::rectangle::scale(T x_scale, T y_scale)
            temp_val.scale(_w, _h);
            test("temp_val.scale(_w, _h)", temp_val, "?");

            // set_location ~~ void omni::geometry::rectangle::set_location(T x, T y)
            temp_val.set_location(_x, _y);
            test("temp_val.set_location(_x, _y)", temp_val, "?");
            
            // set_size ~~ void omni::geometry::rectangle::set_size(T w, T h)
            temp_val.set_size(_w, _h);
            test("temp_val.set_size(_w, _h)", temp_val, "?");
            
            // size ~~ omni::geometry::raw_size<T> omni::geometry::rectangle::size()
            test("temp_val.size()", temp_val.size(), "?");
            
            // swap ~~ void omni::geometry::rectangle::swap(rectangle<T>& o)
            temp_val.swap(_rect);
            test("temp_val.swap(_rect)", temp_val, "?");
            
            // to_string ~~ std::string omni::geometry::rectangle::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::geometry::rectangle::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_wstring ~~ std::wstring omni::geometry::rectangle::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // top ~~ T omni::geometry::rectangle::top()
            test("temp_val.top()", temp_val.top(), "?");

            // top_left ~~ T omni::geometry::rectangle::top_left()
            test("temp_val.top_left()", temp_val.top_left(), "?");

            // top_right ~~ T omni::geometry::rectangle::top_right()
            test("temp_val.top_right()", temp_val.top_right(), "?");
            
            // translate_angle ~~ void omni::geometry::rectangle::translate_angle(float angle, T distance)
            temp_val.translate_angle(_angle, _distance);
            test("temp_val.translate_angle(_angle, _distance)", temp_val, "?");
            
            // translate_xy ~~ void omni::geometry::rectangle::translate_xy(T x, T y)
            temp_val.translate_xy(_x, _y);
            test("temp_val.translate_xy(_x, _y)", temp_val, "?");

            // union_merge ~~ void omni::geometry::rectangle::union_merge(const rectangle<T>& r2)
            temp_val.union_merge(sq);
            test("temp_val.union_merge(sq)", temp_val, "?");
            
            // width ~~ T omni::geometry::rectangle::width()
            test("temp_val.width()", temp_val.width(), "?");
            
            // x ~~ T omni::geometry::rectangle::x()
            test("temp_val.x()", temp_val.x(), "?");
            
            // y ~~ T omni::geometry::rectangle::y()
            test("temp_val.y()", temp_val.y(), "?");
            
            // operator std::string ~~  omni::geometry::rectangle::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::geometry::rectangle::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::geometry::rectangle::operator!=(const rectangle<T>& val)
            test("(temp_val != _r2)", ((temp_val != _r2) ? "true" : "false"), "?");
            
            // operator+ ~~ rectangle<T> omni::geometry::rectangle::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + val)", (temp_val + val), "?");
            
            // operator+= ~~ rectangle<T>& omni::geometry::rectangle::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += val)", (temp_val += val), "?");
            
            // operator- ~~ rectangle<T> omni::geometry::rectangle::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - val)", (temp_val - val), "?");
            
            // operator-= ~~ rectangle<T>& omni::geometry::rectangle::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "?");
            
            // operator< ~~ bool omni::geometry::rectangle::operator<(const omni::geometry::point2d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::rectangle::operator<=(const omni::geometry::point2d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");
            
            // operator= ~~ rectangle<T>& omni::geometry::rectangle::operator=(const rectangle<T>& val)
            test("(temp_val = _r2)", (temp_val = _r2), "?");
            
            // operator== ~~ bool omni::geometry::rectangle::operator==(const rectangle<T>& val)
            test("(temp_val == _r2)", ((temp_val == _r2) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::rectangle::operator>(const omni::geometry::point2d<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::rectangle::operator>=(const omni::geometry::point2d<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");

            // from_ltrb ~~ static rectangle<T> omni::geometry::rectangle::from_ltrb(T left, T top, T right, T bottom)
            test("omni::geometry::rectangle::from_ltrb(T left, T top, T right, T bottom)(_left, _top, _right, _bottom)",
                omni::geometry::rectangle<int32_t>::from_ltrb(_left, _top, _right, _bottom),
                "?");
        }

        void raw_rectangle()
        {
            omni::geometry::raw_rectangle<int32_t> temp_val(5,10, 15,20);
            omni::geometry::raw_rectangle<int32_t> sq(5,10, 15,15);
            omni::geometry::point2d<int32_t> val(5,10);
            omni::math::dimensional<int32_t, 2> _point(6, 9);
            omni::math::dimensional<int32_t, 2> _loc(2, 3);
            omni::math::dimensional<int32_t, 2> _sz(6, 9);
            omni::geometry::raw_rectangle<int32_t> _rect(5,15, 20,10);
            omni::geometry::raw_rectangle<int32_t> _r2(8,15, 17,19);
            omni::math::rotation_direction _dir = omni::math::rotation_direction::CLOCKWISE;
            omni::math::rotation_angle _degrees = omni::math::rotation_angle::NINETY;
            float _angle = 45.0; int32_t _distance = 10; double _percent = 15.0;
            int32_t _x_scale = 15; int32_t _y_scale = 2;
            int32_t _x, _y, _w, _h, _left, _top, _right, _bottom, _val;
            _x = 10; _y = 12;
            _w = 6; _h = 12;
            _left = 10; _top = 10; _right = 20; _bottom = 15;
            _val = 10;

            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle()
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::geometry::raw_rectangle<T>& cp)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::geometry::rectangle<T>& cp)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::math::dimensional<T 4>& cp)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(T x, T y, T w, T h)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(T w, T h)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::geometry::raw_size<T>& sz)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::geometry::size<T>& sz)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::geometry::point2d<T>& p1, const omni::geometry::point2d<T>& p2)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const omni::geometry::raw_point2d<T>& p1, const omni::geometry::raw_point2d<T>& p2)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const raw_rectangle<T>& a, const raw_rectangle<T>& b, bool isect)
            // raw_rectangle ~~  omni::geometry::raw_rectangle::raw_rectangle(const raw_rectangle<T>& a, T w, T h, char type)

            // area ~~ T omni::geometry::raw_rectangle::area()
            test("temp_val.area()", temp_val.area(), "?");

            // bottom ~~ T omni::geometry::raw_rectangle::bottom()
            test("temp_val.bottom()", temp_val.bottom(), "?");

            // bottom_left ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::bottom_left()
            test("temp_val.bottom_left()", temp_val.bottom_left(), "?");

            // bottom_right ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::bottom_right()
            test("temp_val.bottom_right()", temp_val.bottom_right(), "?");

            // centroid ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::centroid()
            test("temp_val.centroid()", temp_val.centroid(), "?");

            // circle_from_circumcenter ~~ omni::geometry::circle<T> omni::geometry::raw_rectangle::circle_from_circumcenter()
            test("temp_val.circle_from_circumcenter()", temp_val.circle_from_circumcenter(), "?");

            // circle_from_incenter ~~ omni::geometry::circle<T> omni::geometry::raw_rectangle::circle_from_incenter()
            test("temp_val.circle_from_incenter()", temp_val.circle_from_incenter(), "?");

            // circumcenter ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::circumcenter()
            test("temp_val.circumcenter()", temp_val.circumcenter(), "?");

            // compare ~~ omni::math::shape_comparator omni::geometry::raw_rectangle::compare(const raw_rectangle<T>& rect)
            test("temp_val.compare(_rect)", temp_val.compare(_rect), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(T x, T y)
            test("temp_val.contains(_x, _y)", (temp_val.contains(_x, _y) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const omni::math::dimensional<T 2>& point)
            test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const omni::geometry::point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const omni::geometry::raw_point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(T left, T top, T right, T bottom)
            // test("temp_val.contains(_left, _top, _right, _bottom)", (temp_val.contains(_left, _top, _right, _bottom) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const omni::math::dimensional<T 4>& rect)
            // test("temp_val.contains(_rect)", (temp_val.contains(_rect) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz)
            // test("temp_val.contains(_point, _sz)", (temp_val.contains(_point, _sz) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz)
            // test("temp_val.contains(_point, _sz)", (temp_val.contains(_point, _sz) ? "true" : "false"), "?");

            // contains ~~ bool omni::geometry::raw_rectangle::contains(const raw_rectangle<T>& rect)
            // test("temp_val.contains(_rect)", (temp_val.contains(_rect) ? "true" : "false"), "?");

            // decrement ~~ void omni::geometry::raw_rectangle::decrement(T x, T y)
            temp_val.decrement(_x, _y);
            test("temp_val.decrement(_x, _y)", temp_val, "?");

            // decrement ~~ void omni::geometry::raw_rectangle::decrement(const omni::math::dimensional<T 2>& point)
            temp_val.decrement(_point);
            test("temp_val.decrement(_point)", temp_val, "?");

            // decrement ~~ void omni::geometry::raw_rectangle::decrement(const omni::geometry::point2d<T>& point)
            // temp_val.decrement(_point);
            // test("temp_val.decrement(_point)", temp_val, "?");

            // decrement ~~ void omni::geometry::raw_rectangle::decrement(const omni::geometry::raw_point2d<T>& point)
            // temp_val.decrement(_point);
            // test("temp_val.decrement(_point)", temp_val, "?");

            // decrement_x ~~ T omni::geometry::raw_rectangle::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "?");

            // decrement_x ~~ T omni::geometry::raw_rectangle::decrement_x(T val)
            test("temp_val.decrement_x(_val)", temp_val.decrement_x(_val), "?");

            // decrement_y ~~ T omni::geometry::raw_rectangle::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "?");

            // decrement_y ~~ T omni::geometry::raw_rectangle::decrement_y(T val)
            test("temp_val.decrement_y(_val)", temp_val.decrement_y(_val), "?");

            // deflate ~~ void omni::geometry::raw_rectangle::deflate(double percent)
            temp_val.deflate(_percent);
            test("temp_val.deflate(_percent)", temp_val, "?");

            // deflate ~~ void omni::geometry::raw_rectangle::deflate(T w, T h)
            temp_val.deflate(_w, _h);
            test("temp_val.deflate(_w, _h)", temp_val, "?");

            // deflate ~~ void omni::geometry::raw_rectangle::deflate(const omni::math::dimensional<T 2>& sz)
            // temp_val.deflate(_sz);
            // test("temp_val.deflate(_sz)", temp_val, "?");

            // deflate ~~ void omni::geometry::raw_rectangle::deflate(const omni::geometry::size<T>& sz)
            // temp_val.deflate(_sz);
            // test("temp_val.deflate(_sz)", temp_val, "?");

            // deflate ~~ void omni::geometry::raw_rectangle::deflate(const omni::geometry::raw_size<T>& sz)
            // temp_val.deflate(_sz);
            // test("temp_val.deflate(_sz)", temp_val, "?");

            // deflate ~~ static raw_rectangle<T> omni::geometry::raw_rectangle::deflate(const raw_rectangle<T>& rect, T w, T h)
            // test(" omni::geometry::raw_rectangle::deflate(const raw_rectangle<T>& rect, T w, T h)(_rect, _w, _h)",  omni::geometry::raw_rectangle::deflate(const raw_rectangle<T>& rect, T w, T h)(_rect, _w, _h), "?");

            // diagonal ~~ double omni::geometry::raw_rectangle::diagonal()
            test("temp_val.diagonal()", temp_val.diagonal(), "?");

            // edge ~~ omni::geometry::raw_point2d<T> omni::geometry::raw_rectangle::edge()
            test("temp_val.edge()", temp_val.edge(), "?");

            // empty ~~ bool omni::geometry::raw_rectangle::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "?");

            // equals ~~ bool omni::geometry::raw_rectangle::equals(T _x, T _y, T _w, T _h)
            test("temp_val.equals(_x, _y, _w, _h)", (temp_val.equals(_x, _y, _w, _h) ? "true" : "false"), "?");

            // equals ~~ bool omni::geometry::raw_rectangle::equals(const omni::math::dimensional<T 2>& loc, const omni::math::dimensional<T 2>& sz)
            test("temp_val.equals(_loc, _sz)", (temp_val.equals(_loc, _sz) ? "true" : "false"), "?");

            // equals ~~ bool omni::geometry::raw_rectangle::equals(const omni::geometry::point2d<T>& loc, const omni::geometry::size<T>& sz)
            // test("temp_val.equals(_loc, _sz)", (temp_val.equals(_loc, _sz) ? "true" : "false"), "?");

            // equals ~~ bool omni::geometry::raw_rectangle::equals(const omni::geometry::raw_point2d<T>& loc, const omni::geometry::raw_size<T>& sz)
            // test("temp_val.equals(_loc, _sz)", (temp_val.equals(_loc, _sz) ? "true" : "false"), "?");

            // from_ltrb ~~ static raw_rectangle<T> omni::geometry::raw_rectangle::from_ltrb(T left, T top, T right, T bottom)
            test(" omni::geometry::raw_rectangle::from_ltrb(T left, T top, T right, T bottom)(_left, _top, _right, _bottom)",  omni::geometry::raw_rectangle<int32_t>::from_ltrb(_left, _top, _right, _bottom), "?");

            // hash_code ~~ int32_t omni::geometry::raw_rectangle::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");

            // height ~~ T omni::geometry::raw_rectangle::height()
            test("temp_val.height()", temp_val.height(), "?");

            // incenter ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::incenter()
            test("temp_val.incenter()", temp_val.incenter(), "?");

            // increment ~~ void omni::geometry::raw_rectangle::increment(T x, T y)
            temp_val.increment(_x, _y);
            test("temp_val.increment(_x, _y)", temp_val, "?");

            // increment ~~ void omni::geometry::raw_rectangle::increment(const omni::math::dimensional<T 2>& point)
            temp_val.increment(_point);
            test("temp_val.increment(_point)", temp_val, "?");

            // increment ~~ void omni::geometry::raw_rectangle::increment(const omni::geometry::point2d<T>& point)
            // temp_val.increment(_point);
            // test("temp_val.increment(_point)", temp_val, "?");

            // increment ~~ void omni::geometry::raw_rectangle::increment(const omni::geometry::raw_point2d<T>& point)
            // temp_val.increment(_point);
            // test("temp_val.increment(_point)", temp_val, "?");

            // increment_x ~~ T omni::geometry::raw_rectangle::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "?");

            // increment_x ~~ T omni::geometry::raw_rectangle::increment_x(T val)
            test("temp_val.increment_x(_val)", temp_val.increment_x(_val), "?");

            // increment_y ~~ T omni::geometry::raw_rectangle::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "?");

            // increment_y ~~ T omni::geometry::raw_rectangle::increment_y(T val)
            test("temp_val.increment_y(_val)", temp_val.increment_y(_val), "?");

            // inflate ~~ void omni::geometry::raw_rectangle::inflate(double percent)
            temp_val.inflate(_percent);
            test("temp_val.inflate(_percent)", temp_val, "?");

            // inflate ~~ void omni::geometry::raw_rectangle::inflate(T w, T h)
            temp_val.inflate(_w, _h);
            test("temp_val.inflate(_w, _h)", temp_val, "?");

            // inflate ~~ void omni::geometry::raw_rectangle::inflate(const omni::math::dimensional<T 2>& sz)
            // temp_val.inflate(_sz);
            // test("temp_val.inflate(_sz)", temp_val, "?");

            // inflate ~~ void omni::geometry::raw_rectangle::inflate(const omni::geometry::size<T>& sz)
            // temp_val.inflate(_sz);
            // test("temp_val.inflate(_sz)", temp_val, "?");

            // inflate ~~ void omni::geometry::raw_rectangle::inflate(const omni::geometry::raw_size<T>& sz)
            // temp_val.inflate(_sz);
            // test("temp_val.inflate(_sz)", temp_val, "?");

            // inflate ~~ static raw_rectangle<T> omni::geometry::raw_rectangle::inflate(const raw_rectangle<T>& rect, T w, T h)
            // test(" omni::geometry::raw_rectangle::inflate(const raw_rectangle<T>& rect, T w, T h)(_rect, _w, _h)",  omni::geometry::raw_rectangle::inflate(const raw_rectangle<T>& rect, T w, T h)(_rect, _w, _h), "?");

            // intersect ~~ void omni::geometry::raw_rectangle::intersect(const omni::geometry::rectangle<T>& r2)
            temp_val.intersect(_r2);
            test("temp_val.intersect(_r2)", temp_val, "?");

            // intersect ~~ void omni::geometry::raw_rectangle::intersect(const raw_rectangle<T>& r2)
            temp_val.intersect(_r2);
            test("temp_val.intersect(_r2)", temp_val, "?");

            // intersect ~~ static raw_rectangle<T> omni::geometry::raw_rectangle::intersect(const raw_rectangle<T>& a, const raw_rectangle<T>& b)
            // test(" omni::geometry::raw_rectangle::intersect(const raw_rectangle<T>& a, const raw_rectangle<T>& b)(_a, _b)",  omni::geometry::raw_rectangle::intersect(const raw_rectangle<T>& a, const raw_rectangle<T>& b)(_a, _b), "?");

            // intersects_with ~~ bool omni::geometry::raw_rectangle::intersects_with(T left, T top, T right, T bottom)
            test("temp_val.intersects_with(_left, _top, _right, _bottom)", (temp_val.intersects_with(_left, _top, _right, _bottom) ? "true" : "false"), "?");

            // intersects_with ~~ bool omni::geometry::raw_rectangle::intersects_with(const omni::geometry::point2d<T>& point, const omni::geometry::size<T> sz)
            // test("temp_val.intersects_with(_point, _sz)", (temp_val.intersects_with(_point, _sz) ? "true" : "false"), "?");

            // intersects_with ~~ bool omni::geometry::raw_rectangle::intersects_with(const omni::geometry::raw_point2d<T>& point, const omni::geometry::raw_size<T> sz)
            // test("temp_val.intersects_with(_point, _sz)", (temp_val.intersects_with(_point, _sz) ? "true" : "false"), "?");

            // intersects_with ~~ bool omni::geometry::raw_rectangle::intersects_with(const omni::math::dimensional<T 4>& rect)
            // test("temp_val.intersects_with(_rect)", (temp_val.intersects_with(_rect) ? "true" : "false"), "?");

            // intersects_with ~~ bool omni::geometry::raw_rectangle::intersects_with(const raw_rectangle<T>& rect)
            test("temp_val.intersects_with(_rect)", (temp_val.intersects_with(_rect) ? "true" : "false"), "?");

            // is_square ~~ bool omni::geometry::raw_rectangle::is_square()
            test("temp_val.is_square()", (temp_val.is_square() ? "true" : "false"), "?");

            // left ~~ T omni::geometry::raw_rectangle::left()
            test("temp_val.left()", temp_val.left(), "?");

            // offset ~~ void omni::geometry::raw_rectangle::offset(T x, T y)
            temp_val.offset(_x, _y);
            test("temp_val.offset(_x, _y)", temp_val, "?");

            // offset ~~ void omni::geometry::raw_rectangle::offset(const omni::math::dimensional<T 2>& point)
            temp_val.offset(_point);
            test("temp_val.offset(_point)", temp_val, "?");

            // offset ~~ void omni::geometry::raw_rectangle::offset(const omni::geometry::point2d<T>& point)
            // temp_val.offset(_point);
            // test("temp_val.offset(_point)", temp_val, "?");

            // offset ~~ void omni::geometry::raw_rectangle::offset(const omni::geometry::raw_point2d<T>& point)
            // temp_val.offset(_point);
            // test("temp_val.offset(_point)", temp_val, "?");

            // perimeter ~~ T omni::geometry::raw_rectangle::perimeter()
            test("temp_val.perimeter()", temp_val.perimeter(), "?");

            // reflect ~~ void omni::geometry::raw_rectangle::reflect()
            temp_val.reflect();
            test("temp_val.reflect()", temp_val, "?");

            // right ~~ T omni::geometry::raw_rectangle::right()
            test("temp_val.right()", temp_val.right(), "?");

            // rotate_centroid ~~ void omni::geometry::raw_rectangle::rotate_centroid(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_centroid(_degrees, _dir);
            test("temp_val.rotate_centroid(_degrees, _dir)", temp_val, "?");

            // rotate_circumcenter ~~ void omni::geometry::raw_rectangle::rotate_circumcenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_circumcenter(_degrees, _dir);
            test("temp_val.rotate_circumcenter(_degrees, _dir)", temp_val, "?");

            // rotate_incenter ~~ void omni::geometry::raw_rectangle::rotate_incenter(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_incenter(_degrees, _dir);
            test("temp_val.rotate_incenter(_degrees, _dir)", temp_val, "?");

            // rotate_on_lb ~~ void omni::geometry::raw_rectangle::rotate_on_lb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_lb(_degrees, _dir);
            test("temp_val.rotate_on_lb(_degrees, _dir)", temp_val, "?");

            // rotate_on_lt ~~ void omni::geometry::raw_rectangle::rotate_on_lt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_lt(_degrees, _dir);
            test("temp_val.rotate_on_lt(_degrees, _dir)", temp_val, "?");

            // rotate_on_rb ~~ void omni::geometry::raw_rectangle::rotate_on_rb(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_rb(_degrees, _dir);
            test("temp_val.rotate_on_rb(_degrees, _dir)", temp_val, "?");

            // rotate_on_rt ~~ void omni::geometry::raw_rectangle::rotate_on_rt(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_on_rt(_degrees, _dir);
            test("temp_val.rotate_on_rt(_degrees, _dir)", temp_val, "?");

            // rotate_origin ~~ void omni::geometry::raw_rectangle::rotate_origin(const omni::math::rotation_angle& degrees, const omni::math::rotation_direction& dir)
            temp_val.rotate_origin(_degrees, _dir);
            test("temp_val.rotate_origin(_degrees, _dir)", temp_val, "?");

            // rotate_point ~~ void omni::geometry::raw_rectangle::rotate_point(const omni::math::rotation_angle& degrees, T x, T y, const omni::math::rotation_direction& dir)
            temp_val.rotate_point(_degrees, _x, _y, _dir);
            test("temp_val.rotate_point(_degrees, _x, _y, _dir)", temp_val, "?");

            // scale ~~ void omni::geometry::raw_rectangle::scale(T x_scale, T y_scale)
            temp_val.scale(_x_scale, _y_scale);
            test("temp_val.scale(_x_scale, _y_scale)", temp_val, "?");

            // scale ~~ static raw_rectangle<T> omni::geometry::raw_rectangle::scale(const raw_rectangle<T>& rect, T w, T h)
            test(" omni::geometry::raw_rectangle::scale(const raw_rectangle<T>& rect, T w, T h)(_rect, _w, _h)",  omni::geometry::raw_rectangle<int32_t>::scale(_rect, _w, _h), "?");

            // set_location ~~ void omni::geometry::raw_rectangle::set_location(T x, T y)
            temp_val.set_location(_x, _y);
            test("temp_val.set_location(_x, _y)", temp_val, "?");

            // set_location ~~ void omni::geometry::raw_rectangle::set_location(const omni::math::dimensional<T 2>& point)
            temp_val.set_location(_point);
            test("temp_val.set_location(_point)", temp_val, "?");

            // set_location ~~ void omni::geometry::raw_rectangle::set_location(const omni::geometry::point2d<T>& point)
            // temp_val.set_location(_point);
            // test("temp_val.set_location(_point)", temp_val, "?");

            // set_location ~~ void omni::geometry::raw_rectangle::set_location(const omni::geometry::raw_point2d<T>& point)
            // temp_val.set_location(_point);
            // test("temp_val.set_location(_point)", temp_val, "?");

            // set_size ~~ void omni::geometry::raw_rectangle::set_size(T w, T h)
            temp_val.set_size(_w, _h);
            test("temp_val.set_size(_w, _h)", temp_val, "?");

            // set_size ~~ void omni::geometry::raw_rectangle::set_size(const omni::math::dimensional<T 2>& sz)
            temp_val.set_size(_sz);
            test("temp_val.set_size(_sz)", temp_val, "?");

            // set_size ~~ void omni::geometry::raw_rectangle::set_size(const omni::geometry::size<T>& sz)
            // temp_val.set_size(_sz);
            // test("temp_val.set_size(_sz)", temp_val, "?");

            // set_size ~~ void omni::geometry::raw_rectangle::set_size(const omni::geometry::raw_size<T>& sz)
            // temp_val.set_size(_sz);
            // test("temp_val.set_size(_sz)", temp_val, "?");

            // swap ~~ void omni::geometry::raw_rectangle::swap(raw_rectangle<T>& o)
            temp_val.swap(_rect);
            test("temp_val.swap(_rect)", temp_val, "?");

            // to_string ~~ std::string omni::geometry::raw_rectangle::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");

            // to_string_t ~~ omni::string_t omni::geometry::raw_rectangle::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");

            // to_wstring ~~ std::wstring omni::geometry::raw_rectangle::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");

            // top ~~ T omni::geometry::raw_rectangle::top()
            test("temp_val.top()", temp_val.top(), "?");

            // top_left ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::top_left()
            test("temp_val.top_left()", temp_val.top_left(), "?");

            // top_right ~~ omni::geometry::point2d<T> omni::geometry::raw_rectangle::top_right()
            test("temp_val.top_right()", temp_val.top_right(), "?");

            // translate_angle ~~ void omni::geometry::raw_rectangle::translate_angle(float angle, T distance)
            temp_val.translate_angle(_angle, _distance);
            test("temp_val.translate_angle(_angle, _distance)", temp_val, "?");

            // translate_xy ~~ void omni::geometry::raw_rectangle::translate_xy(T x, T y)
            temp_val.translate_xy(_x, _y);
            test("temp_val.translate_xy(_x, _y)", temp_val, "?");

            // union_merge ~~ void omni::geometry::raw_rectangle::union_merge(const omni::geometry::rectangle<T>& r2)
            temp_val.union_merge(_r2);
            test("temp_val.union_merge(_r2)", temp_val, "?");

            // union_merge ~~ void omni::geometry::raw_rectangle::union_merge(const raw_rectangle<T>& r2)
            temp_val.union_merge(_r2);
            test("temp_val.union_merge(_r2)", temp_val, "?");

            // union_merge ~~ static raw_rectangle<T> omni::geometry::raw_rectangle::union_merge(const raw_rectangle<T>& a, const raw_rectangle<T>& b)
            // test(" omni::geometry::raw_rectangle::union_merge(const raw_rectangle<T>& a, const raw_rectangle<T>& b)(_a, _b)",  omni::geometry::raw_rectangle::union_merge(const raw_rectangle<T>& a, const raw_rectangle<T>& b)(_a, _b), "?");

            // width ~~ T omni::geometry::raw_rectangle::width()
            test("temp_val.width()", temp_val.width(), "?");

            // x ~~ T omni::geometry::raw_rectangle::x()
            test("temp_val.x()", temp_val.x(), "?");

            // y ~~ T omni::geometry::raw_rectangle::y()
            test("temp_val.y()", temp_val.y(), "?");

            // operator std::string ~~  omni::geometry::raw_rectangle::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");

            // operator std::wstring ~~  omni::geometry::raw_rectangle::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");

            // operator!= ~~ bool omni::geometry::raw_rectangle::operator!=(const raw_rectangle<T>& val)
            test("(temp_val != val)", ((temp_val != _r2) ? "true" : "false"), "?");

            // operator+ ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + val)", (temp_val + val), "?");

            // operator+ ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator+(const omni::geometry::raw_point2d<T>& val)
            test("(temp_val + val)", (temp_val + val), "?");

            // operator+ ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator+(const omni::geometry::size<T>& val)
            // test("(temp_val + val)", (temp_val + val), "?");

            // operator+ ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator+(const omni::geometry::raw_size<T>& val)
            // test("(temp_val + val)", (temp_val + val), "?");

            // operator+= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += val)", (temp_val += val), "?");

            // operator+= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator+=(const omni::geometry::raw_point2d<T>& val)
            test("(temp_val += val)", (temp_val += val), "?");

            // operator+= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator+=(const omni::geometry::size<T>& val)
            // test("(temp_val += val)", (temp_val += val), "?");

            // operator+= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator+=(const omni::geometry::raw_size<T>& val)
            // test("(temp_val += val)", (temp_val += val), "?");

            // operator- ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - val)", (temp_val - val), "?");

            // operator- ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator-(const omni::geometry::raw_point2d<T>& val)
            test("(temp_val - val)", (temp_val - val), "?");

            // operator- ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator-(const omni::geometry::size<T>& val)
            // test("(temp_val - val)", (temp_val - val), "?");

            // operator- ~~ raw_rectangle<T> omni::geometry::raw_rectangle::operator-(const omni::geometry::raw_size<T>& val)
            // test("(temp_val - val)", (temp_val - val), "?");

            // operator-= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "?");

            // operator-= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator-=(const omni::geometry::raw_point2d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "?");

            // operator-= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator-=(const omni::geometry::size<T>& val)
            // test("(temp_val -= val)", (temp_val -= val), "?");

            // operator-= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator-=(const omni::geometry::raw_size<T>& val)
            // test("(temp_val -= val)", (temp_val -= val), "?");

            // operator< ~~ bool omni::geometry::raw_rectangle::operator<(const omni::geometry::point2d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");

            // operator< ~~ bool omni::geometry::raw_rectangle::operator<(const omni::geometry::raw_point2d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");

            // operator< ~~ bool omni::geometry::raw_rectangle::operator<(const omni::geometry::size<T>& val)
            // test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");

            // operator< ~~ bool omni::geometry::raw_rectangle::operator<(const omni::geometry::raw_size<T>& val)
            // test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");

            // operator<= ~~ bool omni::geometry::raw_rectangle::operator<=(const omni::geometry::point2d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");

            // operator<= ~~ bool omni::geometry::raw_rectangle::operator<=(const omni::geometry::raw_point2d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");

            // operator<= ~~ bool omni::geometry::raw_rectangle::operator<=(const omni::geometry::size<T>& val)
            // test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");

            // operator<= ~~ bool omni::geometry::raw_rectangle::operator<=(const omni::geometry::raw_size<T>& val)
            // test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");

            // operator= ~~ raw_rectangle<T>& omni::geometry::raw_rectangle::operator=(const raw_rectangle<T>& val)
            test("(temp_val = _r2)", (temp_val = _r2), "?");

            // operator== ~~ bool omni::geometry::raw_rectangle::operator==(const raw_rectangle<T>& val)
            test("(temp_val == _r2)", ((temp_val == _r2) ? "true" : "false"), "?");

            // operator== ~~ bool omni::geometry::raw_rectangle::operator==(const omni::geometry::point2d<T>& val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");

            // operator== ~~ bool omni::geometry::raw_rectangle::operator==(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");

            // operator== ~~ bool omni::geometry::raw_rectangle::operator==(const omni::geometry::size<T>& val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");

            // operator== ~~ bool omni::geometry::raw_rectangle::operator==(const omni::geometry::raw_size<T>& val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");

            // operator> ~~ bool omni::geometry::raw_rectangle::operator>(const omni::geometry::point2d<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");

            // operator> ~~ bool omni::geometry::raw_rectangle::operator>(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");

            // operator> ~~ bool omni::geometry::raw_rectangle::operator>(const omni::geometry::size<T>& val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");

            // operator> ~~ bool omni::geometry::raw_rectangle::operator>(const omni::geometry::raw_size<T>& val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");

            // operator>= ~~ bool omni::geometry::raw_rectangle::operator>=(const omni::geometry::point2d<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");

            // operator>= ~~ bool omni::geometry::raw_rectangle::operator>=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");

            // operator>= ~~ bool omni::geometry::raw_rectangle::operator>=(const omni::geometry::size<T>& val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");

            // operator>= ~~ bool omni::geometry::raw_rectangle::operator>=(const omni::geometry::raw_size<T>& val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");

            // location ~~ omni::geometry::raw_point2d<T> omni::geometry::raw_rectangle::location
            test("temp_val.location", temp_val.location, "?");

            // size ~~ omni::geometry::raw_size<T> omni::geometry::raw_rectangle::size
            test("temp_val.size", temp_val.size, "?");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_RECTANGLE
