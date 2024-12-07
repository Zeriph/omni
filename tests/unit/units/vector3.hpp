#if defined(OMNI_UTUA) || defined(OMNI_UT_VECTOR3)

#define UT_NAME vector3
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(vector3, "test the functionality in omni::geometry::vector3");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::vector3<double>);
        }
        
        void base_test()
        {
            vector3(); printl("");
        }

        void vector3()
        {
            // vector3 ~~  omni::geometry::vector3::vector3()
            omni::geometry::vector3<double> _b(5, 5, 5, 15, 15, 15);
            omni::geometry::vector3<double> _o(32,11,12, -3,-5,-6);
            omni::geometry::vector3<double> temp_val(24,50,32, 10,10,10);
            omni::geometry::vector3<double> b(24,50,32, 10,10,10);
            double _x, _y, _z, _start_x, _start_y, _start_z, scalar;
            _x = 5; _y = 6; _z = 7; _start_x = 9; _start_y = 10; _start_z = 8;
            scalar = 2.5;
            printv("temp_val.hash_code() = ", temp_val.hash_code());
            
            // angle_between ~~ float omni::geometry::vector3::angle_between(const vector3& b)
            test("temp_val.angle_between(_b)", temp_val.angle_between(_b), "???");
            
            // assign ~~ void omni::geometry::vector3::assign(V start_x, V start_y, V start_z, V x, V y, V z)
            temp_val.assign(_start_x, _start_y, _start_z, _x, _y, _z);
            test("temp_val.assign(_start_x, _start_y, _start_z, _x, _y, _z)", temp_val, "???");
            
            // assign_head ~~ void omni::geometry::vector3::assign_head(V x, V y, V z)
            temp_val.assign_head(_x, _y, _z);
            test("temp_val.assign_head(_x, _y, _z)", temp_val, "???");
            
            // assign_tail ~~ void omni::geometry::vector3::assign_tail(V start_x, V start_y, V start_z)
            temp_val.assign_tail(_start_x, _start_y, _start_z);
            test("temp_val.assign_tail(_start_x, _start_y, _start_z)", temp_val, "???");
            
            // cross_product ~~ vector3 omni::geometry::vector3::cross_product(const vector3& b)
            test("temp_val.cross_product(_b)", temp_val.cross_product(_b), "???");
            
            // direction_cosines ~~ omni::geometry::point3d<double> omni::geometry::vector3::direction_cosines()
            test("temp_val.direction_cosines()", temp_val.direction_cosines(), "???");
            
            // direction_x ~~ float omni::geometry::vector3::direction_x()
            test("temp_val.direction_x()", temp_val.direction_x(), "???");
            
            // direction_y ~~ float omni::geometry::vector3::direction_y()
            test("temp_val.direction_y()", temp_val.direction_y(), "???");
            
            // direction_z ~~ float omni::geometry::vector3::direction_z()
            test("temp_val.direction_z()", temp_val.direction_z(), "???");
            
            // distance_from ~~ long double omni::geometry::vector3::distance_from(const vector3& b)
            test("temp_val.distance_from(_b)", temp_val.distance_from(_b), "???");
            
            // dot_product ~~ V omni::geometry::vector3::dot_product(const vector3& b)
            test("temp_val.dot_product(_b)", temp_val.dot_product(_b), "???");
            
            // head ~~ point3d_t omni::geometry::vector3::head()
            test("temp_val.head()", temp_val.head(), "???");
            
            // is_standard_form ~~ bool omni::geometry::vector3::is_standard_form()
            test("temp_val.is_standard_form()", (temp_val.is_standard_form() ? "true" : "false"), "???");
            
            // length ~~ V omni::geometry::vector3::length()
            test("temp_val.length()", temp_val.length(), "???");
            
            // magnitude ~~ V omni::geometry::vector3::magnitude()
            test("temp_val.magnitude()", temp_val.magnitude(), "???");
            
            // set_start_x ~~ void omni::geometry::vector3::set_start_x(V start_x)
            temp_val.set_start_x(_start_x);
            test("temp_val.set_start_x(_start_x)", temp_val, "???");
            
            // set_start_y ~~ void omni::geometry::vector3::set_start_y(V start_y)
            temp_val.set_start_y(_start_y);
            test("temp_val.set_start_y(_start_y)", temp_val, "???");
            
            // set_start_z ~~ void omni::geometry::vector3::set_start_z(V start_z)
            temp_val.set_start_z(_start_z);
            test("temp_val.set_start_z(_start_z)", temp_val, "???");
            
            // set_x ~~ void omni::geometry::vector3::set_x(V x)
            temp_val.set_x(_x);
            test("temp_val.set_x(_x)", temp_val, "???");
            
            // set_y ~~ void omni::geometry::vector3::set_y(V y)
            temp_val.set_y(_y);
            test("temp_val.set_y(_y)", temp_val, "???");
            
            // set_z ~~ void omni::geometry::vector3::set_z(V z)
            temp_val.set_z(_z);
            test("temp_val.set_z(_z)", temp_val, "???");
            
            // start_x ~~ V omni::geometry::vector3::start_x()
            test("temp_val.start_x()", temp_val.start_x(), "???");
            
            // start_y ~~ V omni::geometry::vector3::start_y()
            test("temp_val.start_y()", temp_val.start_y(), "???");
            
            // start_z ~~ V omni::geometry::vector3::start_z()
            test("temp_val.start_z()", temp_val.start_z(), "???");
            
            // swap ~~ void omni::geometry::vector3::swap(vector3& o)
            temp_val.swap(_o);
            test("temp_val.swap(_o)", temp_val, "???");
            
            // tail ~~ point3d_t omni::geometry::vector3::tail()
            test("temp_val.tail()", temp_val.tail(), "???");
            
            // to_standard_form ~~ vector3 omni::geometry::vector3::to_standard_form()
            test("temp_val.to_standard_form()", temp_val.to_standard_form(), "???");
            
            // to_string ~~ std::string omni::geometry::vector3::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "???");
            
            // to_string_t ~~ omni::string_t omni::geometry::vector3::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "???");
            
            // to_wstring ~~ std::wstring omni::geometry::vector3::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "???");
            
            // unit_vector ~~ vector3 omni::geometry::vector3::unit_vector()
            test("temp_val.unit_vector()", temp_val.unit_vector(), "???");
            
            // x ~~ V omni::geometry::vector3::x()
            test("temp_val.x()", temp_val.x(), "???");
            
            // x_component ~~ V omni::geometry::vector3::x_component()
            test("temp_val.x_component()", temp_val.x_component(), "???");
            
            // y ~~ V omni::geometry::vector3::y()
            test("temp_val.y()", temp_val.y(), "???");
            
            // y_component ~~ V omni::geometry::vector3::y_component()
            test("temp_val.y_component()", temp_val.y_component(), "???");
            
            // z ~~ V omni::geometry::vector3::z()
            test("temp_val.z()", temp_val.z(), "???");
            
            // z_component ~~ V omni::geometry::vector3::z_component()
            test("temp_val.z_component()", temp_val.z_component(), "???");
            
            // operator omni::geometry::point3d<T> ~~ template < typename T >  omni::geometry::vector3::operator omni::geometry::point3d<T>()
            test("(static_cast< omni::geometry::point3d<T> >(temp_val))", (static_cast< omni::geometry::point3d<double> >(temp_val)), "???");
            
            // operator std::string ~~  omni::geometry::vector3::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "???");
            
            // operator std::wstring ~~  omni::geometry::vector3::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "???");
            
            // operator* ~~ vector3 omni::geometry::vector3::operator*(V scalar)
            test("(temp_val * scalar)", (temp_val * scalar), "???");
            
            // operator+ ~~ vector3 omni::geometry::vector3::operator+(const vector3& b)
            test("(temp_val + b)", (temp_val + b), "???");
            
            // operator- ~~ vector3 omni::geometry::vector3::operator-(const vector3& b)
            test("(temp_val - b)", (temp_val - b), "???");
            
            // operator/ ~~ vector3 omni::geometry::vector3::operator/(V scalar)
            test("(temp_val / scalar)", (temp_val / scalar), "???");
            
            // operator= ~~ vector3& omni::geometry::vector3::operator=(const vector3& b)
            test("(temp_val = b)", (temp_val = b), "???");
            
            // operator== ~~ bool omni::geometry::vector3::operator==(const vector3& b)
            test("(temp_val == b)", ((temp_val == b) ? "true" : "false"), "???");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_VECTOR3
