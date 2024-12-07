#if defined(OMNI_UTUA) || defined(OMNI_UT_SIZE)

#define UT_NAME size3d
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(size3d, "test the functionality in omni::geometry::size3d");
            M_LIST_ADD(raw_size3d, "test the functionality in omni::geometry::raw_size3d");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::size3d<uint32_t>);
            print_info(omni::geometry::raw_size3d<uint32_t>);
        }
        
        void base_test()
        {
            size3d(); printl("");
            raw_size3d(); printl("");
        }

        void size3d()
        {
            // size3d ~~  omni::geometry::size3d::size3d()
            omni::geometry::size3d<int32_t> temp_val(5, 10, 15);
            omni::geometry::size3d<int32_t> _val(10, 5, 5);
            omni::geometry::size3d<int32_t> val(3, 6, 9);
            int32_t _w, _h, _d;
            _w = _h = _d = 10;
            
            // area ~~ T omni::geometry::size3d::area()
            test("temp_val.area()", temp_val.area(), "750");
            
            // empty ~~ bool omni::geometry::size3d::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");

            // depth ~~ T omni::geometry::size3d::depth()
            test("temp_val.depth()", temp_val.depth(), "15");
            
            // height ~~ T omni::geometry::size3d::height()
            test("temp_val.height()", temp_val.height(), "10");
            
            // set_dimensions ~~ void omni::geometry::size3d::set_dimensions(T w, T h)
            temp_val.set_dimensions(_w, _h, _d);
            test("temp_val.set_dimensions(_w, _h, _d)", temp_val, "{10,10,10}");
            
            // swap ~~ void omni::geometry::size3d::swap(size3d<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{10,5,5}");
            test("_val", _val, "{10, 10, 10}");
            
            // to_dimensional ~~ omni::math::dimensional<T, 3> omni::geometry::size3d::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{10,5,5}");
            
            // to_string ~~ std::string omni::geometry::size3d::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{10,5,5}");
            
            // to_string_t ~~ omni::string_t omni::geometry::size3d::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{10,5,5}");
            
            // to_wstring ~~ std::wstring omni::geometry::size3d::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{10,5,5}");
            
            // width ~~ T omni::geometry::size3d::width()
            test("temp_val.width()", temp_val.width(), "10");
            
            // operator omni::math::dimensional<T, 3> ~~  omni::geometry::size3d::operator omni::math::dimensional<T, 3>()
            omni::math::dimensional<int32_t, 3> ds = temp_val;
            test("(static_cast< omni::math::dimensional<T, 3> >(temp_val))", ds, "{10,5,5}");
            
            // operator std::string ~~  omni::geometry::size3d::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{10,5,5}");
            
            // operator std::wstring ~~  omni::geometry::size3d::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{10,5,5}");
            
            // operator!= ~~ bool omni::geometry::size3d::operator!=(const size3d<T>& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "true");
            
            // operator+ ~~ size3d<T> omni::geometry::size3d::operator+(const size3d<T>& val)
            test("(temp_val + val)", (temp_val + val), "{13,11,14}");
            
            // operator+= ~~ size3d<T>& omni::geometry::size3d::operator+=(const size3d<T>& val)
            test("(temp_val += val)", (temp_val += val), "{13,11,14}");
            
            // operator- ~~ size3d<T> omni::geometry::size3d::operator-(const size3d<T>& val)
            test("(temp_val - val)", (temp_val - val), "{10,5,5}");
            
            // operator-= ~~ size3d<T>& omni::geometry::size3d::operator-=(const size3d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "{10,5,5}");
            
            // operator< ~~ bool omni::geometry::size3d::operator<(const size3d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::geometry::size3d::operator<=(const size3d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "false");
            
            // operator= ~~ size3d<T>& omni::geometry::size3d::operator=(const size3d<T>& val)
            test("(temp_val = val)", (temp_val = val), "{3,6,9}");
            
            // operator== ~~ bool omni::geometry::size3d::operator==(const size3d<T>& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::size3d::operator>(const size3d<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::size3d::operator>=(const size3d<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "true");
        }

        void raw_size3d()
        {
            // raw_size3d ~~  omni::geometry::raw_size3d::raw_size3d()
            omni::geometry::raw_size3d<int32_t> temp_val(5, 10, 15);
            omni::geometry::raw_size3d<int32_t> _val(10, 5, 5);
            omni::geometry::raw_size3d<int32_t> val(3, 6, 9);
            int32_t _w, _h, _d;
            _w = _h = _d = 10;
            
            // area ~~ T omni::geometry::raw_size3d::area()
            test("temp_val.area()", temp_val.area(), "750");
            
            // empty ~~ bool omni::geometry::raw_size3d::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // set_dimensions ~~ void omni::geometry::raw_size3d::set_dimensions(T w, T h)
            temp_val.set_dimensions(_w, _h, _d);
            test("temp_val.set_dimensions(_w, _h, _d)", temp_val, "{10,10,10}");
            
            // swap ~~ void omni::geometry::raw_size3d::swap(raw_size3d<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{10,5,5}");
            test("_val", _val, "{10, 10, 10}");
            
            // to_dimensional ~~ omni::math::dimensional<T, 3> omni::geometry::raw_size3d::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{10,5,5}");
            
            // to_size ~~ omni::geometry::size3d<T> omni::geometry::raw_size3d::to_size3d()
            test("temp_val.to_size3d()", temp_val.to_size3d(), "{10,5,5}");
            
            // to_string ~~ std::string omni::geometry::raw_size3d::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{10,5,5}");
            
            // to_string_t ~~ omni::string_t omni::geometry::raw_size3d::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{10,5,5}");
            
            // to_wstring ~~ std::wstring omni::geometry::raw_size3d::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{10,5,5}");
            
            // operator omni::math::dimensional<T, 3> ~~  omni::geometry::raw_size3d::operator omni::math::dimensional<T, 3>()
            test("(static_cast< omni::math::dimensional<T, 3> >(temp_val))", (static_cast< omni::math::dimensional<int32_t, 3> >(temp_val)), "{10,5,5}");
            
            // operator std::string ~~  omni::geometry::raw_size3d::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{10,5,5}");
            
            // operator std::wstring ~~  omni::geometry::raw_size3d::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{10,5,5}");
            
            // operator!= ~~ bool omni::geometry::raw_size3d::operator!=(const raw_size3d< T >& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "true");
            
            // operator+ ~~ raw_size3d<T> omni::geometry::raw_size3d::operator+(const raw_size3d<T>& val)
            test("(temp_val + val)", (temp_val + val), "{13,11,14}");
            
            // operator+= ~~ raw_size3d<T>& omni::geometry::raw_size3d::operator+=(const raw_size3d<T>& val)
            test("(temp_val += val)", (temp_val += val), "{13,11,14}");
            
            // operator- ~~ raw_size3d<T> omni::geometry::raw_size3d::operator-(const raw_size3d<T>& val)
            test("(temp_val - val)", (temp_val - val), "{10,5,5}");
            
            // operator-= ~~ raw_size3d<T>& omni::geometry::raw_size3d::operator-=(const raw_size3d<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "{10,5,5}");
            
            // operator< ~~ bool omni::geometry::raw_size3d::operator<(const raw_size3d<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::geometry::raw_size3d::operator<=(const raw_size3d<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "false");
            
            // operator= ~~ raw_size3d<T>& omni::geometry::raw_size3d::operator=(const raw_size3d<T>& val)
            test("(temp_val = val)", (temp_val = val), "{3,6,9}");
            
            // operator== ~~ bool omni::geometry::raw_size3d::operator==(const raw_size3d< T >& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::raw_size3d::operator>(const raw_size3d<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::raw_size3d::operator>=(const raw_size3d<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "true");

            // depth ~~ T omni::geometry::raw_size3d::depth
            test("temp_val.depth()", temp_val.depth, "9");
            
            // height ~~ T omni::geometry::raw_size3d::height
            test("temp_val.height", temp_val.height, "6");
            
            // width ~~ T omni::geometry::raw_size3d::width
            test("temp_val.width", temp_val.width, "3");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SIZE
