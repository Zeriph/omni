#if defined(OMNI_UTUA) || defined(OMNI_UT_POINT3D)

#define UT_NAME point3d
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(point3d, "test the functionality in omni::geometry::point3d");
            M_LIST_ADD(raw_point3d, "test the functionality in omni::geometry::raw_point3d");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::point3d<int32_t>);
            print_info(omni::geometry::raw_point3d<int32_t>);
        }
        
        void base_test()
        {
            point3d(); printl("");
            raw_point3d(); printl("");
        }

        void point3d()
        {
            // point3d ~~  omni::geometry::point3d::point3d()
            omni::geometry::point3d<int32_t> val(1,1,1);
            omni::geometry::point3d<int32_t> _val(5,5,5);
            omni::geometry::point3d<int32_t> temp_val(5, 10, 15);
            int32_t _x, _y, _z;
            _x = -1; _y = 4; _z = 9;

            printv("temp_val.hash_code()", temp_val.hash_code());
            
            // decrement ~~ void omni::geometry::point3d::decrement(const point3d<T>& val)
            temp_val.decrement(_val);
            test("temp_val.decrement(_val)", temp_val, "{0,5,10}");
            
            // decrement_x ~~ T omni::geometry::point3d::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "-1");
            
            // decrement_y ~~ T omni::geometry::point3d::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "4");
            
            // decrement_z ~~ T omni::geometry::point3d::decrement_z()
            test("temp_val.decrement_z()", temp_val.decrement_z(), "9");
            
            // empty ~~ bool omni::geometry::point3d::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // equals ~~ bool omni::geometry::point3d::equals(T x, T y, T z)
            test("temp_val.equals(_x, _y, _z)", (temp_val.equals(_x, _y, _z) ? "true" : "false"), "true");
            
            // increment ~~ void omni::geometry::point3d::increment(const point3d<T>& val)
            temp_val.increment(_val);
            test("temp_val.increment(_val)", temp_val, "{4,9,14}");
            
            // increment_x ~~ T omni::geometry::point3d::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "5");
            
            // increment_y ~~ T omni::geometry::point3d::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "10");
            
            // increment_z ~~ T omni::geometry::point3d::increment_z()
            test("temp_val.increment_z()", temp_val.increment_z(), "15");
            
            // offset ~~ void omni::geometry::point3d::offset(const point3d<T>& val)
            temp_val.offset(_val);
            test("temp_val.offset(_val)", temp_val, "{10,15,20}");
            
            // set ~~ void omni::geometry::point3d::set(T x, T y, T z)
            _val.set(_x, _y, _z);
            test("temp_val.set(_x, _y, _z)", _val, "{-1,4,9}");

            // swap ~~ void omni::geometry::point3d::swap(point3d<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{-1,4,9}");
            test("_val", _val, "{10,15,20}");
            
            // to_dimensional ~~ omni::math::dimensional<T, 3> omni::geometry::point3d::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{-1,4,9}");
            
            // to_string ~~ std::string omni::geometry::point3d::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{-1,4,9}");
            
            // to_string_t ~~ omni::string_t omni::geometry::point3d::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{-1,4,9}");
            
            // to_wstring ~~ std::wstring omni::geometry::point3d::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{-1,4,9}");
            
            // x ~~ T omni::geometry::point3d::x()
            test("temp_val.x()", temp_val.x(), "-1");
            
            // y ~~ T omni::geometry::point3d::y()
            test("temp_val.y()", temp_val.y(), "4");
            
            // z ~~ T omni::geometry::point3d::z()
            test("temp_val.z()", temp_val.z(), "9");
            
            // operator omni::math::dimensional<T, 3> ~~  omni::geometry::point3d::operator omni::math::dimensional<T, 3>()
            test("(static_cast< omni::math::dimensional<T, 3> >(temp_val))", (static_cast< omni::math::dimensional<int32_t, 3> >(temp_val)), "{-1,4,9}");
            
            // operator std::string ~~  omni::geometry::point3d::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{-1,4,9}");
            
            // operator std::wstring ~~  omni::geometry::point3d::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{-1,4,9}");
            
            // operator!= ~~ bool omni::geometry::point3d::operator!=(const point3d< T >& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "true");
            
            // operator+ ~~ point3d<T> omni::geometry::point3d::operator+(const point3d<T>& val)
            test("(temp_val + val)", (temp_val + val), "{0,5,10}");
            
            // operator+= ~~ point3d<T>& omni::geometry::point3d::operator+=(const point3d<T>& val)
            test("(temp_val += val)", (temp_val += val), "{0,5,10}");
            
            // operator- ~~ point3d<T> omni::geometry::point3d::operator-(const point3d<T>& val)
            test("(temp_val - val)", (temp_val - val), "{-1,4,9}");
            
            // operator-= ~~ point3d<T>& omni::geometry::point3d::operator-=(const point3d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "{-1,4,9}");
            
            // operator< ~~ bool omni::geometry::point3d::operator<(const point3d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::geometry::point3d::operator<=(const point3d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "false");
            
            // operator= ~~ point3d<T>& omni::geometry::point3d::operator=(const point3d<T>& val)
            test("(temp_val = val)", (temp_val = val), "{1,1,1}");
            
            // operator== ~~ bool omni::geometry::point3d::operator==(const point3d< T >& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::point3d::operator>(const point3d<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::point3d::operator>=(const point3d<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "true");


            omni::geometry::point3d<int32_t> _point(2,4,6);
            omni::math::dimensional<int32_t, 3> _coord(3,4,5);
            // add ~~ static point3d<T> omni::geometry::point3d::add(const point3d<T>& point, const omni::math::dimensional<T 3> coord)
            test("omni::geometry::point3d::add(const point3d<T>& point, const omni::math::dimensional<T 3> coord)",
                omni::geometry::point3d<int32_t>::add(_point, _coord),
                "{5,8,11}");
            
            // subtract ~~ static point3d<T> omni::geometry::point3d::subtract(const point3d<T>& point, const omni::math::dimensional<T 3> coord)
            test("omni::geometry::point3d::subtract(const point3d<T>& point, const omni::math::dimensional<T 3> coord)",
                omni::geometry::point3d<int32_t>::subtract(_point, _coord),
                "{-1,0,1}");
        }

        void raw_point3d()
        {
            
            // raw_point3d ~~  omni::geometry::raw_point3d::raw_point3d()
            omni::geometry::raw_point3d<int32_t> val(1,1,1);
            omni::geometry::raw_point3d<int32_t> _val(5,5,5);
            omni::geometry::raw_point3d<int32_t> temp_val(5, 10, 15);
            int32_t __x, __y, __z;
            __x = -1; __y = 4; __z = 9;

            printv("temp_val.hash_code()", temp_val.hash_code());
            
            // decrement ~~ void omni::geometry::raw_point3d::decrement(const raw_point3d<T>& val)
            temp_val.decrement(_val);
            test("temp_val.decrement(_val)", temp_val, "{0,5,10}");
            
            // decrement_x ~~ T omni::geometry::raw_point3d::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "-1");
            
            // decrement_y ~~ T omni::geometry::raw_point3d::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "4");
            
            // decrement_z ~~ T omni::geometry::raw_point3d::decrement_z()
            test("temp_val.decrement_z()", temp_val.decrement_z(), "9");
            
            // empty ~~ bool omni::geometry::raw_point3d::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // equals ~~ bool omni::geometry::raw_point3d::equals(T _x, T _y, T _z)
            test("temp_val.equals(__x, __y, __z)", (temp_val.equals(__x, __y, __z) ? "true" : "false"), "true");
            
            // increment_x ~~ T omni::geometry::raw_point3d::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "0");
            
            // increment_y ~~ T omni::geometry::raw_point3d::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "5");
            
            // increment_z ~~ T omni::geometry::raw_point3d::increment_z()
            test("temp_val.increment_z()", temp_val.increment_z(), "10");
            
            // offset ~~ void omni::geometry::raw_point3d::offset(const raw_point3d<T>& val)
            temp_val.offset(_val);
            test("temp_val.offset(_val)", temp_val, "{5,10,15}");
            
            // set ~~ void omni::geometry::raw_point3d::set(T _x, T _y, T _z)
            _val.set(__x, __y, __z);
            test("temp_val.set(__x, __y, __z)", _val, "{-1,4,9}");
            
            // swap ~~ void omni::geometry::raw_point3d::swap(raw_point3d<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{-1,4,9}");
            test("_val", _val, "{5,10,15}");
            
            // to_dimensional ~~ omni::math::dimensional<T, 3> omni::geometry::raw_point3d::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{-1,4,9}");
            
            // to_point3d ~~ omni::geometry::point3d<T> omni::geometry::raw_point3d::to_point3d()
            test("temp_val.to_point3d()", temp_val.to_point3d(), "{-1,4,9}");
            
            // to_string ~~ std::string omni::geometry::raw_point3d::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{-1,4,9}");
            
            // to_string_t ~~ omni::string_t omni::geometry::raw_point3d::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{-1,4,9}");
            
            // to_wstring ~~ std::wstring omni::geometry::raw_point3d::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{-1,4,9}");
            
            // operator omni::geometry::point3d<T> ~~  omni::geometry::raw_point3d::operator omni::geometry::point3d<T>()
            omni::geometry::point3d<int32_t> p3 = temp_val;
            test("(static_cast< omni::geometry::point3d<T> >(temp_val))", p3, "{-1,4,9}");
            
            // operator omni::math::dimensional<T, 3> ~~  omni::geometry::raw_point3d::operator omni::math::dimensional<T, 3>()
            omni::math::dimensional<int32_t, 3> d3 = temp_val;
            test("(static_cast< omni::math::dimensional<T, 3> >(temp_val))", d3, "{-1,4,9}");
            
            // operator std::string ~~  omni::geometry::raw_point3d::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{-1,4,9}");
            
            // operator std::wstring ~~  omni::geometry::raw_point3d::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{-1,4,9}");
            
            // operator!= ~~ bool omni::geometry::raw_point3d::operator!=(const raw_point3d<T>& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "true");
            
            // operator+ ~~ raw_point3d<T> omni::geometry::raw_point3d::operator+(const raw_point3d<T>& val)
            test("(temp_val + val)", (temp_val + val), "{0,5,10}");
            
            // operator+= ~~ raw_point3d<T>& omni::geometry::raw_point3d::operator+=(const raw_point3d<T>& val)
            test("(temp_val += val)", (temp_val += val), "{0,5,10}");
            
            // operator- ~~ raw_point3d<T> omni::geometry::raw_point3d::operator-(const raw_point3d<T>& val)
            test("(temp_val - val)", (temp_val - val), "{-1,4,9}");
            
            // operator-= ~~ raw_point3d<T>& omni::geometry::raw_point3d::operator-=(const raw_point3d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "{-1,4,9}");
            
            // operator< ~~ bool omni::geometry::raw_point3d::operator<(const raw_point3d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::geometry::raw_point3d::operator<=(const raw_point3d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "false");
            
            // operator= ~~ raw_point3d<T>& omni::geometry::raw_point3d::operator=(const raw_point3d<T>& val)
            test("(temp_val = val)", (temp_val = val), "{1,1,1}");
            
            // operator== ~~ bool omni::geometry::raw_point3d::operator==(const raw_point3d<T>& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::raw_point3d::operator>(const raw_point3d<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::raw_point3d::operator>=(const raw_point3d<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "true");
            
            // x ~~ T omni::geometry::raw_point3d::x
            test("temp_val.x", temp_val.x, "1");
            
            // y ~~ T omni::geometry::raw_point3d::y
            test("temp_val.y", temp_val.y, "1");
            
            // z ~~ T omni::geometry::raw_point3d::z
            test("temp_val.z", temp_val.z, "1");

            omni::geometry::raw_point3d<int32_t> _point(5,4,6);
            omni::math::dimensional<int32_t, 3> _sz(3,10,1);

            // add ~~ static raw_point3d<T> omni::geometry::raw_point3d::add(const raw_point3d<T>& point, const omni::math::dimensional<T 3> sz)
            test("omni::geometry::raw_point3d::add(const raw_point3d<T>& point, const omni::math::dimensional<T 3> sz)",
                omni::geometry::raw_point3d<int32_t>::add(_point, _sz),
                "{8,14,7}");

            // subtract ~~ static raw_point3d<T> omni::geometry::raw_point3d::subtract(const raw_point3d<T>& point, const omni::math::dimensional<T 3> sz)
            test("omni::geometry::raw_point3d::subtract(const raw_point3d<T>& point, const omni::math::dimensional<T 3> sz)",
                omni::geometry::raw_point3d<int32_t>::subtract(_point, _sz),
                "{2,-6,5}");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_POINT3D
