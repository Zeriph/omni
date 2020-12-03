#if defined(OMNI_UTUA) || defined(OMNI_UT_VECTOR2)

#define UT_NAME vector2
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(vector2, "test the functionality in omni::geometry::vector2");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::vector2<double>);
        }
        
        void base_test()
        {
            vector2(); printl("");
        }

        void vector2()
        {
            // vector2 ~~  omni::geometry::vector2::vector2()
            omni::geometry::vector2<double> _b(5, 5, 15, 15);
            omni::geometry::vector2<double> _o(32, 11, -3, -5);
            omni::geometry::vector2<double> temp_val(24,50, 10,10);
            omni::geometry::vector2<double> b(24,50, 10,10);
            double _x, _y, _start_x, _start_y, scalar;
            _x = 5; _y = 6; _start_x = 9; _start_y = 10;
            scalar = 2.5;
            printv("temp_val.hash_code() = ", temp_val.hash_code());
            
            // angle_between ~~ float omni::geometry::vector2::angle_between(const vector2& b)
            test("temp_val.angle_between(_b)", temp_val.angle_between(_b), "???");
            
            // assign ~~ void omni::geometry::vector2::assign(V start_x, V start_y, V x, V y)
            temp_val.assign(_start_x, _start_y, _x, _y);
            test("temp_val.assign(_start_x, _start_y, _x, _y)", temp_val, "???");
            
            // assign_head ~~ void omni::geometry::vector2::assign_head(V x, V y)
            temp_val.assign_head(_x, _y);
            test("temp_val.assign_head(_x, _y)", temp_val, "???");
            
            // assign_tail ~~ void omni::geometry::vector2::assign_tail(V start_x, V start_y)
            temp_val.assign_tail(_start_x, _start_y);
            test("temp_val.assign_tail(_start_x, _start_y)", temp_val, "???");
            
            // cross_product ~~ V omni::geometry::vector2::cross_product(const vector2& b)
            test("temp_val.cross_product(_b)", temp_val.cross_product(_b), "???");
            
            // direction ~~ float omni::geometry::vector2::direction()
            test("temp_val.direction()", temp_val.direction(), "???");
            
            // distance_from ~~ long double omni::geometry::vector2::distance_from(const vector2& b)
            test("temp_val.distance_from(_b)", temp_val.distance_from(_b), "???");
            
            // dot_product ~~ V omni::geometry::vector2::dot_product(const vector2& b)
            test("temp_val.dot_product(_b)", temp_val.dot_product(_b), "???");
            
            // head ~~ point2d_t omni::geometry::vector2::head()
            test("temp_val.head()", temp_val.head(), "???");
            
            // is_standard_form ~~ bool omni::geometry::vector2::is_standard_form()
            test("temp_val.is_standard_form()", (temp_val.is_standard_form() ? "true" : "false"), "???");
            
            // length ~~ V omni::geometry::vector2::length()
            test("temp_val.length()", temp_val.length(), "???");
            
            // magnitude ~~ V omni::geometry::vector2::magnitude()
            test("temp_val.magnitude()", temp_val.magnitude(), "???");
            
            // set_start_x ~~ void omni::geometry::vector2::set_start_x(V start_x)
            temp_val.set_start_x(_start_x);
            test("temp_val.set_start_x(_start_x)", temp_val, "???");
            
            // set_start_y ~~ void omni::geometry::vector2::set_start_y(V start_y)
            temp_val.set_start_y(_start_y);
            test("temp_val.set_start_y(_start_y)", temp_val, "???");
            
            // set_x ~~ void omni::geometry::vector2::set_x(V x)
            temp_val.set_x(_x);
            test("temp_val.set_x(_x)", temp_val, "???");
            
            // set_y ~~ void omni::geometry::vector2::set_y(V y)
            temp_val.set_y(_y);
            test("temp_val.set_y(_y)", temp_val, "???");
            
            // start_x ~~ V omni::geometry::vector2::start_x()
            test("temp_val.start_x()", temp_val.start_x(), "???");
            
            // start_y ~~ V omni::geometry::vector2::start_y()
            test("temp_val.start_y()", temp_val.start_y(), "???");
            
            // swap ~~ void omni::geometry::vector2::swap(vector2& o)
            temp_val.swap(_o);
            test("temp_val.swap(_o)", temp_val, "???");
            
            // tail ~~ point2d_t omni::geometry::vector2::tail()
            test("temp_val.tail()", temp_val.tail(), "???");
            
            // to_standard_form ~~ vector2 omni::geometry::vector2::to_standard_form()
            test("temp_val.to_standard_form()", temp_val.to_standard_form(), "???");
            
            // to_string ~~ std::string omni::geometry::vector2::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "???");
            
            // to_string_t ~~ omni::string_t omni::geometry::vector2::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "???");
            
            // to_wstring ~~ std::wstring omni::geometry::vector2::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "???");
            
            // unit_vector ~~ vector2 omni::geometry::vector2::unit_vector()
            test("temp_val.unit_vector()", temp_val.unit_vector(), "???");
            
            // x ~~ V omni::geometry::vector2::x()
            test("temp_val.x()", temp_val.x(), "???");
            
            // x_component ~~ V omni::geometry::vector2::x_component()
            test("temp_val.x_component()", temp_val.x_component(), "???");
            
            // y ~~ V omni::geometry::vector2::y()
            test("temp_val.y()", temp_val.y(), "???");
            
            // y_component ~~ V omni::geometry::vector2::y_component()
            test("temp_val.y_component()", temp_val.y_component(), "???");
            
            // operator omni::geometry::point2d<T> ~~ template < typename T >  omni::geometry::vector2::operator omni::geometry::point2d<T>()
            test("(static_cast< omni::geometry::point2d<T> >(temp_val))", (static_cast< omni::geometry::point2d<double> >(temp_val)), "???");
            
            // operator std::string ~~  omni::geometry::vector2::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "???");
            
            // operator std::wstring ~~  omni::geometry::vector2::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "???");
            
            // operator* ~~ vector2 omni::geometry::vector2::operator*(V scalar)
            test("(temp_val * scalar)", (temp_val * scalar), "???");
            
            // operator+ ~~ vector2 omni::geometry::vector2::operator+(const vector2& b)
            test("(temp_val + b)", (temp_val + b), "???");
            
            // operator- ~~ vector2 omni::geometry::vector2::operator-(const vector2& b)
            test("(temp_val - b)", (temp_val - b), "???");
            
            // operator/ ~~ vector2 omni::geometry::vector2::operator/(V scalar)
            test("(temp_val / scalar)", (temp_val / scalar), "???");
            
            // operator= ~~ vector2& omni::geometry::vector2::operator=(const vector2& b)
            test("(temp_val = b)", (temp_val = b), "???");
            
            // operator== ~~ bool omni::geometry::vector2::operator==(const vector2& b)
            test("(temp_val == b)", ((temp_val == b) ? "true" : "false"), "???");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_VECTOR2
