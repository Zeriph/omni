#if defined(OMNI_UTUA) || defined(OMNI_UT_CIRCLE)

#define UT_NAME circle
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(circle, "test the functionality in omni::geometry::circle");
            M_LIST_ADD(raw_circle, "test the functionality in omni::geometry::raw_circle");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::circle<double>);
            print_info(omni::geometry::raw_circle<double>);
        }
        
        void base_test()
        {
            circle(); printl("");
            raw_circle(); printl("");
        }

        void circle()
        {
            // circle ~~  omni::geometry::circle::circle()
            typedef double T;
            typedef omni::geometry::circle<T> circ;
            // circle ~~ OMNI_EXPLICIT omni::geometry::circle::circle(double r)
            circ val(10.25);
            // circle ~~  omni::geometry::circle::circle(T x, T y)
            circ _o(10, 20);
            // circle ~~  omni::geometry::circle::circle(T x, T y, double r)
            circ temp_val(10, 20, 5.5);
            // circle ~~  omni::geometry::circle::circle(const omni::geometry::circle<T>& cp)
            circ _circ(_o);
            circ _a(5,5, 5);
            circ _b(7,7, 5);
            circ _r2(10,15, 10.25);

            omni::geometry::point2d<T> _point(1.25, 3.5);
            bool _include_edge = true;
            T _x, _y, _val, _percent, _center_x, _center_y, _radius, _circumference, _diameter;
            _x = 2.5; _y = 5.25; _val = 1.25; _percent = 50.0;
            _center_x = 0.25; _center_y = 1.0; _radius = 10;
            _circumference = 125.2; _diameter = 14.25;

            // area ~~ double omni::geometry::circle::area()
            test("temp_val.area()", temp_val.area(), "?");
            
            // bottom ~~ double omni::geometry::circle::bottom()
            test("temp_val.bottom()", temp_val.bottom(), "?");
            
            // circumference ~~ double omni::geometry::circle::circumference()
            test("temp_val.circumference()", temp_val.circumference(), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(T x, T y, bool include_edge)
            test("temp_val.contains(_x, _y, _include_edge)", (temp_val.contains(_x, _y, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(T x, T y)
            test("temp_val.contains(_x, _y)", (temp_val.contains(_x, _y) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const omni::math::dimensional<T 2>& point, bool include_edge)
            // test("temp_val.contains(_point, _include_edge)", (temp_val.contains(_point, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const omni::math::dimensional<T 2>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const omni::geometry::point2d<T>& point, bool include_edge)
            // test("temp_val.contains(_point, _include_edge)", (temp_val.contains(_point, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const omni::geometry::point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const omni::geometry::raw_point2d<T>& point, bool include_edge)
            // test("temp_val.contains(_point, _include_edge)", (temp_val.contains(_point, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const omni::geometry::raw_point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const circle<T>& circ, bool include_edge)
            // test("temp_val.contains(_circ, _include_edge)", (temp_val.contains(_circ, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::circle::contains(const circle<T>& circ)
            test("temp_val.contains(_circ)", (temp_val.contains(_circ) ? "true" : "false"), "?");
            
            // decrement ~~ void omni::geometry::circle::decrement(T x, T y)
            temp_val.decrement(_x, _y);
            test("temp_val.decrement(_x, _y)", temp_val, "?");
            
            // decrement ~~ void omni::geometry::circle::decrement(const omni::geometry::point2d<T>& point)
            temp_val.decrement(_point);
            test("temp_val.decrement(_point)", temp_val, "?");
            
            // decrement ~~ void omni::geometry::circle::decrement(const omni::geometry::raw_point2d<T>& point)
            // temp_val.decrement(_point);
            // test("temp_val.decrement(_point)", temp_val, "?");
            
            // decrement ~~ void omni::geometry::circle::decrement(const omni::math::dimensional<T 2>& point)
            // temp_val.decrement(_point);
            // test("temp_val.decrement(_point)", temp_val, "?");
            
            // decrement_x ~~ T omni::geometry::circle::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "?");
            
            // decrement_x ~~ T omni::geometry::circle::decrement_x(T val)
            test("temp_val.decrement_x(_val)", temp_val.decrement_x(_val), "?");
            
            // decrement_y ~~ T omni::geometry::circle::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "?");
            
            // decrement_y ~~ T omni::geometry::circle::decrement_y(T val)
            test("temp_val.decrement_y(_val)", temp_val.decrement_y(_val), "?");
            
            // deflate ~~ void omni::geometry::circle::deflate(double percent)
            temp_val.deflate(_percent);
            test("temp_val.deflate(_percent)", temp_val, "?");
            
            // diameter ~~ double omni::geometry::circle::diameter()
            test("temp_val.diameter()", temp_val.diameter(), "?");
            
            // empty ~~ bool omni::geometry::circle::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "?");
            
            // empty_size ~~ bool omni::geometry::circle::empty_size()
            test("temp_val.empty_size()", (temp_val.empty_size() ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::circle::equals(T x, T y, double radius)
            test("temp_val.equals(_x, _y, _radius)", (temp_val.equals(_x, _y, _radius) ? "true" : "false"), "?");
            
            // hash_code ~~ int32_t omni::geometry::circle::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");
            
            // increment_x ~~ T omni::geometry::circle::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "?");
            
            // increment_x ~~ T omni::geometry::circle::increment_x(T val)
            test("temp_val.increment_x(_val)", temp_val.increment_x(_val), "?");
            
            // increment_y ~~ T omni::geometry::circle::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "?");
            
            // increment_y ~~ T omni::geometry::circle::increment_y(T val)
            test("temp_val.increment_y(_val)", temp_val.increment_y(_val), "?");
            
            // inflate ~~ void omni::geometry::circle::inflate(double percent)
            temp_val.inflate(_percent);
            test("temp_val.inflate(_percent)", temp_val, "?");
            
            // intersect ~~ void omni::geometry::circle::intersect(const circle<T>& r2)
            temp_val.intersect(_r2);
            test("temp_val.intersect(_r2)", temp_val, "?");
            
            // intersects_with ~~ bool omni::geometry::circle::intersects_with(T center_x, T center_y, double radius, bool include_edge)
            test("temp_val.intersects_with(_center_x, _center_y, _radius, _include_edge)", (temp_val.intersects_with(_center_x, _center_y, _radius, _include_edge) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::circle::intersects_with(T center_x, T center_y, double radius)
            test("temp_val.intersects_with(_center_x, _center_y, _radius)", (temp_val.intersects_with(_center_x, _center_y, _radius) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::circle::intersects_with(const omni::geometry::point2d<T>& point, double radius, bool include_edge)
            // test("temp_val.intersects_with(_point, _radius, _include_edge)", (temp_val.intersects_with(_point, _radius, _include_edge) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::circle::intersects_with(const omni::geometry::point2d<T>& point, double radius)
            // test("temp_val.intersects_with(_point, _radius)", (temp_val.intersects_with(_point, _radius) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::circle::intersects_with(const circle<T>& circ, bool include_edge)
            // test("temp_val.intersects_with(_circ, _include_edge)", (temp_val.intersects_with(_circ, _include_edge) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::circle::intersects_with(const circle<T>& circ)
            // test("temp_val.intersects_with(_circ)", (temp_val.intersects_with(_circ) ? "true" : "false"), "?");
            
            // left ~~ double omni::geometry::circle::left()
            test("temp_val.left()", temp_val.left(), "?");
            
            // location ~~ omni::geometry::raw_point2d<T> omni::geometry::circle::location()
            test("temp_val.location()", temp_val.location(), "?");
            
            // offset ~~ void omni::geometry::circle::offset(T x, T y)
            temp_val.offset(_x, _y);
            test("temp_val.offset(_x, _y)", temp_val, "?");
            
            // offset ~~ void omni::geometry::circle::offset(const omni::geometry::point2d<T>& point)
            temp_val.offset(_point);
            test("temp_val.offset(_point)", temp_val, "?");
            
            // offset ~~ void omni::geometry::circle::offset(const omni::geometry::raw_point2d<T>& point)
            // temp_val.offset(_point);
            // test("temp_val.offset(_point)", temp_val, "?");
            
            // offset ~~ void omni::geometry::circle::offset(const omni::math::dimensional<T 2>& coord)
            // temp_val.offset(_coord);
            // test("temp_val.offset(_coord)", temp_val, "?");
            
            // radius ~~ double omni::geometry::circle::radius()
            test("temp_val.radius()", temp_val.radius(), "?");
            
            // right ~~ double omni::geometry::circle::right()
            test("temp_val.right()", temp_val.right(), "?");
            
            // set_circumference ~~ void omni::geometry::circle::set_circumference(double circumference)
            temp_val.set_circumference(_circumference);
            test("temp_val.set_circumference(_circumference)", temp_val, "?");
            
            // set_diameter ~~ void omni::geometry::circle::set_diameter(double diameter)
            temp_val.set_diameter(_diameter);
            test("temp_val.set_diameter(_diameter)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::circle::set_location(T x, T y)
            temp_val.set_location(_x, _y);
            test("temp_val.set_location(_x, _y)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::circle::set_location(const omni::math::dimensional<T 2>& coord)
            // temp_val.set_location(_coord);
            // test("temp_val.set_location(_coord)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::circle::set_location(const omni::geometry::point2d<T>& point)
            // temp_val.set_location(_point);
            // test("temp_val.set_location(_point)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::circle::set_location(const omni::geometry::raw_point2d<T>& point)
            // temp_val.set_location(_point);
            // test("temp_val.set_location(_point)", temp_val, "?");
            
            // set_radius ~~ void omni::geometry::circle::set_radius(double radius)
            temp_val.set_radius(_radius);
            test("temp_val.set_radius(_radius)", temp_val, "?");
            
            // swap ~~ void omni::geometry::circle::swap(circle<T>& o)
            temp_val.swap(_o);
            test("temp_val.swap(_o)", temp_val, "?");
            
            // to_string ~~ std::string omni::geometry::circle::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::geometry::circle::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_wstring ~~ std::wstring omni::geometry::circle::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // top ~~ double omni::geometry::circle::top()
            test("temp_val.top()", temp_val.top(), "?");
            
            // translate_xy ~~ void omni::geometry::circle::translate_xy(T x, T y)
            temp_val.translate_xy(_x, _y);
            test("temp_val.translate_xy(_x, _y)", temp_val, "?");
            
            // x ~~ T omni::geometry::circle::x()
            test("temp_val.x()", temp_val.x(), "?");
            
            // y ~~ T omni::geometry::circle::y()
            test("temp_val.y()", temp_val.y(), "?");
            
            // operator std::string ~~  omni::geometry::circle::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::geometry::circle::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::geometry::circle::operator!=(const circle<T>& val)
            test("(temp_val != _val)", ((temp_val != _val) ? "true" : "false"), "?");
            
            // operator+ ~~ circle<T> omni::geometry::circle::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + _point)", (temp_val + _point), "?");
            
            // operator+ ~~ circle<T> omni::geometry::circle::operator+(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val + val)", (temp_val + val), "?");
            
            // operator+ ~~ circle<T> omni::geometry::circle::operator+(double val)
            // test("(temp_val + val)", (temp_val + val), "?");
            
            // operator+= ~~ circle<T>& omni::geometry::circle::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += _point)", (temp_val += _point), "?");
            
            // operator+= ~~ circle<T>& omni::geometry::circle::operator+=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val += val)", (temp_val += val), "?");
            
            // operator+= ~~ circle<T>& omni::geometry::circle::operator+=(double rad)
            // test("(temp_val += rad)", (temp_val += rad), "?");
            
            // operator- ~~ circle<T> omni::geometry::circle::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - _point)", (temp_val - _point), "?");
            
            // operator- ~~ circle<T> omni::geometry::circle::operator-(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val - val)", (temp_val - val), "?");
            
            // operator- ~~ circle<T> omni::geometry::circle::operator-(double val)
            // test("(temp_val - val)", (temp_val - val), "?");
            
            // operator-= ~~ circle<T>& omni::geometry::circle::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= _point)", (temp_val -= _point), "?");
            
            // operator-= ~~ circle<T>& omni::geometry::circle::operator-=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val -= val)", (temp_val -= val), "?");
            
            // operator-= ~~ circle<T>& omni::geometry::circle::operator-=(double val)
            // test("(temp_val -= val)", (temp_val -= val), "?");
            
            // operator< ~~ bool omni::geometry::circle::operator<(const omni::geometry::point2d<T>& val)
            test("(temp_val < _point)", ((temp_val < _point) ? "true" : "false"), "?");
            
            // operator< ~~ bool omni::geometry::circle::operator<(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");
            
            // operator< ~~ bool omni::geometry::circle::operator<(double val)
            // test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::circle::operator<=(const omni::geometry::point2d<T>& val)
            test("(temp_val <= _point)", ((temp_val <= _point) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::circle::operator<=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::circle::operator<=(double val)
            // test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");
            
            // operator= ~~ circle<T>& omni::geometry::circle::operator=(const circle<T>& val)
            test("(temp_val = _val)", (temp_val = _val), "?");
            
            // operator== ~~ bool omni::geometry::circle::operator==(const circle<T>& val)
            test("(temp_val == _val)", ((temp_val == _val) ? "true" : "false"), "?");
            
            // operator== ~~ bool omni::geometry::circle::operator==(const omni::geometry::point2d<T>& val)
            test("(temp_val == _point)", ((temp_val == _point) ? "true" : "false"), "?");
            
            // operator== ~~ bool omni::geometry::circle::operator==(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");
            
            // operator== ~~ bool omni::geometry::circle::operator==(double val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::circle::operator>(const omni::geometry::point2d<T>& val)
            test("(temp_val > _point)", ((temp_val > _point) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::circle::operator>(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::circle::operator>(double val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::circle::operator>=(const omni::geometry::point2d<T>& val)
            test("(temp_val >= _point)", ((temp_val >= _point) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::circle::operator>=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::circle::operator>=(double val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");

            // deflate ~~ static circle<T> omni::geometry::circle::deflate(const circle<T>& circ, double percent)
            test(" omni::geometry::circle::deflate(_circ, _percent)",  omni::geometry::circle<T>::deflate(_circ, _percent), "?");

            // inflate ~~ static circle<T> omni::geometry::circle::inflate(const circle<T>& circ, double percent)
            test(" omni::geometry::circle::inflate(_circ, _percent)",  omni::geometry::circle<T>::inflate(_circ, _percent), "?");
        
            // intersect ~~ static circle<T> omni::geometry::circle::intersect(const circle<T>& a, const circle<T>& b)
            test(" omni::geometry::circle::intersect(_a, _b)",  omni::geometry::circle<T>::intersect(_a, _b), "?");
        }

        void raw_circle()
        {
            // raw_circle ~~  omni::geometry::raw_circle::raw_circle()
            typedef double T;
            typedef omni::geometry::raw_circle<T> circ;
            // raw_circle ~~ OMNI_EXPLICIT omni::geometry::raw_circle::raw_circle(double r)
            circ val(10.25);
            // raw_circle ~~  omni::geometry::raw_circle::raw_circle(T x, T y)
            circ _o(10, 20);
            // raw_circle ~~  omni::geometry::raw_circle::raw_circle(T x, T y, double r)
            circ temp_val(10, 20, 5.5);
            // raw_circle ~~  omni::geometry::raw_circle::raw_circle(const omni::geometry::raw_circle<T>& cp)
            circ _circ(_o);
            circ _a(5,5, 5);
            circ _b(7,7, 5);
            circ _r2(10,15, 10.25);
            // raw_circle ~~  omni::geometry::raw_circle::raw_circle(const omni::geometry::circle<T>& cp)

            omni::geometry::point2d<T> _point(1.25, 3.5);
            bool _include_edge = true;
            T _x, _y, _val, _percent, _center_x, _center_y, _radius, _circumference, _diameter;
            _x = 2.5; _y = 5.25; _val = 1.25; _percent = 50.0;
            _center_x = 0.25; _center_y = 1.0; _radius = 10;
            _circumference = 125.2; _diameter = 14.25;

            // area ~~ double omni::geometry::raw_circle::area()
            test("temp_val.area()", temp_val.area(), "?");
            
            // bottom ~~ double omni::geometry::raw_circle::bottom()
            test("temp_val.bottom()", temp_val.bottom(), "?");
            
            // circumference ~~ double omni::geometry::raw_circle::circumference()
            test("temp_val.circumference()", temp_val.circumference(), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(T x, T y, bool include_edge)
            test("temp_val.contains(_x, _y, _include_edge)", (temp_val.contains(_x, _y, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(T x, T y)
            test("temp_val.contains(_x, _y)", (temp_val.contains(_x, _y) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const omni::math::dimensional<T 2>& point, bool include_edge)
            // test("temp_val.contains(_point, _include_edge)", (temp_val.contains(_point, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const omni::math::dimensional<T 2>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const omni::geometry::point2d<T>& point, bool include_edge)
            // test("temp_val.contains(_point, _include_edge)", (temp_val.contains(_point, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const omni::geometry::point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const omni::geometry::raw_point2d<T>& point, bool include_edge)
            // test("temp_val.contains(_point, _include_edge)", (temp_val.contains(_point, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const omni::geometry::raw_point2d<T>& point)
            // test("temp_val.contains(_point)", (temp_val.contains(_point) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const raw_circle<T>& circ, bool include_edge)
            test("temp_val.contains(_circ, _include_edge)", (temp_val.contains(_circ, _include_edge) ? "true" : "false"), "?");
            
            // contains ~~ bool omni::geometry::raw_circle::contains(const raw_circle<T>& circ)
            // test("temp_val.contains(_circ)", (temp_val.contains(_circ) ? "true" : "false"), "?");
            
            // decrement ~~ void omni::geometry::raw_circle::decrement(T x, T y)
            temp_val.decrement(_x, _y);
            test("temp_val.decrement(_x, _y)", temp_val, "?");
            
            // decrement ~~ void omni::geometry::raw_circle::decrement(const omni::geometry::point2d<T>& point)
            temp_val.decrement(_point);
            test("temp_val.decrement(_point)", temp_val, "?");
            
            // decrement ~~ void omni::geometry::raw_circle::decrement(const omni::geometry::raw_point2d<T>& point)
            // temp_val.decrement(_point);
            // test("temp_val.decrement(_point)", temp_val, "?");
            
            // decrement ~~ void omni::geometry::raw_circle::decrement(const omni::math::dimensional<T 2>& point)
            // temp_val.decrement(_point);
            // test("temp_val.decrement(_point)", temp_val, "?");
            
            // decrement_x ~~ T omni::geometry::raw_circle::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "?");
            
            // decrement_x ~~ T omni::geometry::raw_circle::decrement_x(T val)
            test("temp_val.decrement_x(_val)", temp_val.decrement_x(_val), "?");
            
            // decrement_y ~~ T omni::geometry::raw_circle::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "?");
            
            // decrement_y ~~ T omni::geometry::raw_circle::decrement_y(T val)
            test("temp_val.decrement_y(_val)", temp_val.decrement_y(_val), "?");
            
            // deflate ~~ void omni::geometry::raw_circle::deflate(double percent)
            temp_val.deflate(_percent);
            test("temp_val.deflate(_percent)", temp_val, "?");
            
            // diameter ~~ double omni::geometry::raw_circle::diameter()
            test("temp_val.diameter()", temp_val.diameter(), "?");
            
            // empty ~~ bool omni::geometry::raw_circle::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "?");
            
            // empty_size ~~ bool omni::geometry::raw_circle::empty_size()
            test("temp_val.empty_size()", (temp_val.empty_size() ? "true" : "false"), "?");
            
            // equals ~~ bool omni::geometry::raw_circle::equals(T x, T y, double radius)
            test("temp_val.equals(_x, _y, _radius)", (temp_val.equals(_x, _y, _radius) ? "true" : "false"), "?");
            
            // hash_code ~~ int32_t omni::geometry::raw_circle::hash_code()
            test("temp_val.hash_code()", temp_val.hash_code(), "?");
            
            // increment_x ~~ T omni::geometry::raw_circle::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "?");
            
            // increment_x ~~ T omni::geometry::raw_circle::increment_x(T val)
            test("temp_val.increment_x(_val)", temp_val.increment_x(_val), "?");
            
            // increment_y ~~ T omni::geometry::raw_circle::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "?");
            
            // increment_y ~~ T omni::geometry::raw_circle::increment_y(T val)
            test("temp_val.increment_y(_val)", temp_val.increment_y(_val), "?");
            
            // inflate ~~ void omni::geometry::raw_circle::inflate(double percent)
            temp_val.inflate(_percent);
            test("temp_val.inflate(_percent)", temp_val, "?");
            
            // intersect ~~ void omni::geometry::raw_circle::intersect(const raw_circle<T>& r2)
            temp_val.intersect(_r2);
            test("temp_val.intersect(_r2)", temp_val, "?");
            
            // intersects_with ~~ bool omni::geometry::raw_circle::intersects_with(T center_x, T center_y, double radius, bool include_edge)
            test("temp_val.intersects_with(_center_x, _center_y, _radius, _include_edge)", (temp_val.intersects_with(_center_x, _center_y, _radius, _include_edge) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::raw_circle::intersects_with(T center_x, T center_y, double radius)
            test("temp_val.intersects_with(_center_x, _center_y, _radius)", (temp_val.intersects_with(_center_x, _center_y, _radius) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::raw_circle::intersects_with(const omni::geometry::point2d<T>& point, double radius, bool include_edge)
            // test("temp_val.intersects_with(_point, _radius, _include_edge)", (temp_val.intersects_with(_point, _radius, _include_edge) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::raw_circle::intersects_with(const omni::geometry::point2d<T>& point, double radius)
            // test("temp_val.intersects_with(_point, _radius)", (temp_val.intersects_with(_point, _radius) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::raw_circle::intersects_with(const raw_circle<T>& circ, bool include_edge)
            // test("temp_val.intersects_with(_circ, _include_edge)", (temp_val.intersects_with(_circ, _include_edge) ? "true" : "false"), "?");
            
            // intersects_with ~~ bool omni::geometry::raw_circle::intersects_with(const raw_circle<T>& circ)
            // test("temp_val.intersects_with(_circ)", (temp_val.intersects_with(_circ) ? "true" : "false"), "?");
            
            // left ~~ double omni::geometry::raw_circle::left()
            test("temp_val.left()", temp_val.left(), "?");
            
            // offset ~~ void omni::geometry::raw_circle::offset(T x, T y)
            temp_val.offset(_x, _y);
            test("temp_val.offset(_x, _y)", temp_val, "?");
            
            // offset ~~ void omni::geometry::raw_circle::offset(const omni::geometry::point2d<T>& point)
            temp_val.offset(_point);
            test("temp_val.offset(_point)", temp_val, "?");
            
            // offset ~~ void omni::geometry::raw_circle::offset(const omni::geometry::raw_point2d<T>& point)
            // temp_val.offset(_point);
            // test("temp_val.offset(_point)", temp_val, "?");
            
            // offset ~~ void omni::geometry::raw_circle::offset(const omni::math::dimensional<T 2>& coord)
            // temp_val.offset(_coord);
            // test("temp_val.offset(_coord)", temp_val, "?");
            
            // right ~~ double omni::geometry::raw_circle::right()
            test("temp_val.right()", temp_val.right(), "?");
            
            // set_circumference ~~ void omni::geometry::raw_circle::set_circumference(double circumference)
            temp_val.set_circumference(_circumference);
            test("temp_val.set_circumference(_circumference)", temp_val, "?");
            
            // set_diameter ~~ void omni::geometry::raw_circle::set_diameter(double diameter)
            temp_val.set_diameter(_diameter);
            test("temp_val.set_diameter(_diameter)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::raw_circle::set_location(T x, T y)
            temp_val.set_location(_x, _y);
            test("temp_val.set_location(_x, _y)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::raw_circle::set_location(const omni::math::dimensional<T 2>& coord)
            // temp_val.set_location(_coord);
            // test("temp_val.set_location(_coord)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::raw_circle::set_location(const omni::geometry::point2d<T>& point)
            // temp_val.set_location(_point);
            // test("temp_val.set_location(_point)", temp_val, "?");
            
            // set_location ~~ void omni::geometry::raw_circle::set_location(const omni::geometry::raw_point2d<T>& point)
            // temp_val.set_location(_point);
            // test("temp_val.set_location(_point)", temp_val, "?");
            
            // set_radius ~~ void omni::geometry::raw_circle::set_radius(double radius)
            temp_val.set_radius(_radius);
            test("temp_val.set_radius(_radius)", temp_val, "?");
            
            // swap ~~ void omni::geometry::raw_circle::swap(raw_circle<T>& o)
            temp_val.swap(_o);
            test("temp_val.swap(_o)", temp_val, "?");
            
            // to_string ~~ std::string omni::geometry::raw_circle::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "?");
            
            // to_string_t ~~ omni::string_t omni::geometry::raw_circle::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "?");
            
            // to_wstring ~~ std::wstring omni::geometry::raw_circle::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "?");
            
            // top ~~ double omni::geometry::raw_circle::top()
            test("temp_val.top()", temp_val.top(), "?");
            
            // translate_xy ~~ void omni::geometry::raw_circle::translate_xy(T x, T y)
            temp_val.translate_xy(_x, _y);
            test("temp_val.translate_xy(_x, _y)", temp_val, "?");
            
            // x ~~ T omni::geometry::raw_circle::x()
            test("temp_val.x()", temp_val.x(), "?");
            
            // y ~~ T omni::geometry::raw_circle::y()
            test("temp_val.y()", temp_val.y(), "?");
            
            // operator std::string ~~  omni::geometry::raw_circle::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "?");
            
            // operator std::wstring ~~  omni::geometry::raw_circle::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "?");
            
            // operator!= ~~ bool omni::geometry::raw_circle::operator!=(const raw_circle<T>& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "?");
            
            // operator+ ~~ raw_circle<T> omni::geometry::raw_circle::operator+(const omni::geometry::point2d<T>& val)
            test("(temp_val + _point)", (temp_val + _point), "?");
            
            // operator+ ~~ raw_circle<T> omni::geometry::raw_circle::operator+(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val + val)", (temp_val + val), "?");
            
            // operator+ ~~ raw_circle<T> omni::geometry::raw_circle::operator+(double val)
            // test("(temp_val + val)", (temp_val + val), "?");
            
            // operator+= ~~ raw_circle<T>& omni::geometry::raw_circle::operator+=(const omni::geometry::point2d<T>& val)
            test("(temp_val += _point)", (temp_val += _point), "?");
            
            // operator+= ~~ raw_circle<T>& omni::geometry::raw_circle::operator+=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val += val)", (temp_val += val), "?");
            
            // operator+= ~~ raw_circle<T>& omni::geometry::raw_circle::operator+=(double rad)
            // test("(temp_val += rad)", (temp_val += rad), "?");
            
            // operator- ~~ raw_circle<T> omni::geometry::raw_circle::operator-(const omni::geometry::point2d<T>& val)
            test("(temp_val - _point)", (temp_val - _point), "?");
            
            // operator- ~~ raw_circle<T> omni::geometry::raw_circle::operator-(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val - val)", (temp_val - val), "?");
            
            // operator- ~~ raw_circle<T> omni::geometry::raw_circle::operator-(double val)
            // test("(temp_val - val)", (temp_val - val), "?");
            
            // operator-= ~~ raw_circle<T>& omni::geometry::raw_circle::operator-=(const omni::geometry::point2d<T>& val)
            test("(temp_val -= _point)", (temp_val -= _point), "?");
            
            // operator-= ~~ raw_circle<T>& omni::geometry::raw_circle::operator-=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val -= val)", (temp_val -= val), "?");
            
            // operator-= ~~ raw_circle<T>& omni::geometry::raw_circle::operator-=(double val)
            // test("(temp_val -= val)", (temp_val -= val), "?");
            
            // operator< ~~ bool omni::geometry::raw_circle::operator<(const omni::geometry::point2d<T>& val)
            test("(temp_val < _point)", ((temp_val < _point) ? "true" : "false"), "?");
            
            // operator< ~~ bool omni::geometry::raw_circle::operator<(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");
            
            // operator< ~~ bool omni::geometry::raw_circle::operator<(double val)
            // test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::raw_circle::operator<=(const omni::geometry::point2d<T>& val)
            test("(temp_val <= _point)", ((temp_val <= _point) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::raw_circle::operator<=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");
            
            // operator<= ~~ bool omni::geometry::raw_circle::operator<=(double val)
            // test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "?");
            
            // operator= ~~ raw_circle<T>& omni::geometry::raw_circle::operator=(const raw_circle<T>& val)
            test("(temp_val = val)", (temp_val = val), "?");
            
            // operator== ~~ bool omni::geometry::raw_circle::operator==(const raw_circle<T>& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");
            
            // operator== ~~ bool omni::geometry::raw_circle::operator==(const omni::geometry::point2d<T>& val)
            test("(temp_val == _point)", ((temp_val == _point) ? "true" : "false"), "?");
            
            // operator== ~~ bool omni::geometry::raw_circle::operator==(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");
            
            // operator== ~~ bool omni::geometry::raw_circle::operator==(double val)
            // test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::raw_circle::operator>(const omni::geometry::point2d<T>& val)
            test("(temp_val > _point)", ((temp_val > _point) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::raw_circle::operator>(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");
            
            // operator> ~~ bool omni::geometry::raw_circle::operator>(double val)
            // test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::raw_circle::operator>=(const omni::geometry::point2d<T>& val)
            test("(temp_val >= _point)", ((temp_val >= _point) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::raw_circle::operator>=(const omni::geometry::raw_point2d<T>& val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");
            
            // operator>= ~~ bool omni::geometry::raw_circle::operator>=(double val)
            // test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "?");
            
            // location ~~ omni::geometry::raw_point2d<T> omni::geometry::raw_circle::location
            test("temp_val.location", temp_val.location, "?");
            
            // radius ~~ double omni::geometry::raw_circle::radius
            test("temp_val.radius", temp_val.radius, "?");

            // deflate ~~ static raw_circle<T> omni::geometry::raw_circle::deflate(const raw_circle<T>& circ, double percent)
            test("omni::geometry::raw_circle::deflate(_circ, _percent)",  omni::geometry::raw_circle<T>::deflate(_circ, _percent), "?");
            
            // inflate ~~ static raw_circle<T> omni::geometry::raw_circle::inflate(const raw_circle<T>& circ, double percent)
            test("omni::geometry::raw_circle::inflate(_circ, _percent)",  omni::geometry::raw_circle<T>::inflate(_circ, _percent), "?");
            
            // intersect ~~ static raw_circle<T> omni::geometry::raw_circle::intersect(const raw_circle<T>& a, const raw_circle<T>& b)
            test("omni::geometry::raw_circle::intersect(_a, _b)",  omni::geometry::raw_circle<T>::intersect(_a, _b), "?");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_CIRCLE
