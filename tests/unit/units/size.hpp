#if defined(OMNI_UTUA) || defined(OMNI_UT_SIZE)

#define UT_NAME size
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(size, "test the functionality in omni::geometry::size");
            M_LIST_ADD(raw_size, "test the functionality in omni::geometry::raw_size");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::size<uint32_t>);
            print_info(omni::geometry::raw_size<uint32_t>);
        }
        
        void base_test()
        {
            size(); printl("");
            raw_size(); printl("");
        }

        void size()
        {
            // size ~~  omni::geometry::size::size()
            omni::geometry::size<int32_t> temp_val(5, 10);
            omni::geometry::size<int32_t> _val(10, 5);
            omni::geometry::size<int32_t> val(3, 6);
            int32_t _w, _h;
            _w = _h = 10;
            
            // area ~~ T omni::geometry::size::area()
            test("temp_val.area()", temp_val.area(), "50");
            
            // empty ~~ bool omni::geometry::size::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // height ~~ T omni::geometry::size::height()
            test("temp_val.height()", temp_val.height(), "10");
            
            // set_dimensions ~~ void omni::geometry::size::set_dimensions(T w, T h)
            temp_val.set_dimensions(_w, _h);
            test("temp_val.set_dimensions(_w, _h)", temp_val, "{10,10}");
            
            // swap ~~ void omni::geometry::size::swap(size<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{10,5}");
            test("_val", _val, "{10, 10}");
            
            // to_dimensional ~~ omni::math::dimensional<T, 2> omni::geometry::size::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{10,5}");
            
            // to_string ~~ std::string omni::geometry::size::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{10,5}");
            
            // to_string_t ~~ omni::string_t omni::geometry::size::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{10,5}");
            
            // to_wstring ~~ std::wstring omni::geometry::size::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{10,5}");
            
            // width ~~ T omni::geometry::size::width()
            test("temp_val.width()", temp_val.width(), "10");
            
            // operator omni::math::dimensional<T, 2> ~~  omni::geometry::size::operator omni::math::dimensional<T, 2>()
            omni::math::dimensional<int32_t, 2> ds = temp_val;
            test("(static_cast< omni::math::dimensional<T, 2> >(temp_val))", ds, "{10,5}");
            
            // operator std::string ~~  omni::geometry::size::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{10,5}");
            
            // operator std::wstring ~~  omni::geometry::size::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{10,5}");
            
            // operator!= ~~ bool omni::geometry::size::operator!=(const size<T>& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "true");
            
            // operator+ ~~ size<T> omni::geometry::size::operator+(const size<T>& val)
            test("(temp_val + val)", (temp_val + val), "{13,11}");
            
            // operator+= ~~ size<T>& omni::geometry::size::operator+=(const size<T>& val)
            test("(temp_val += val)", (temp_val += val), "{13,11}");
            
            // operator- ~~ size<T> omni::geometry::size::operator-(const size<T>& val)
            test("(temp_val - val)", (temp_val - val), "{10,5}");
            
            // operator-= ~~ size<T>& omni::geometry::size::operator-=(const size<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "{10,5}");
            
            // operator< ~~ bool omni::geometry::size::operator<(const size<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::geometry::size::operator<=(const size<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "false");
            
            // operator= ~~ size<T>& omni::geometry::size::operator=(const size<T>& val)
            test("(temp_val = val)", (temp_val = val), "{3,6}");
            
            // operator== ~~ bool omni::geometry::size::operator==(const size<T>& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::size::operator>(const size<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::size::operator>=(const size<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "true");
        }

        void raw_size()
        {
            // raw_size ~~  omni::geometry::raw_size::raw_size()
            omni::geometry::raw_size<int32_t> temp_val(5, 10);
            omni::geometry::raw_size<int32_t> _val(10, 5);
            omni::geometry::raw_size<int32_t> val(3, 6);
            int32_t _w, _h;
            _w = _h = 10;
            
            // area ~~ T omni::geometry::raw_size::area()
            test("temp_val.area()", temp_val.area(), "50");
            
            // empty ~~ bool omni::geometry::raw_size::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // set_dimensions ~~ void omni::geometry::raw_size::set_dimensions(T w, T h)
            temp_val.set_dimensions(_w, _h);
            test("temp_val.set_dimensions(_w, _h)", temp_val, "{10,10}");
            
            // swap ~~ void omni::geometry::raw_size::swap(raw_size<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{10,5}");
            test("_val", _val, "{10, 10}");
            
            // to_dimensional ~~ omni::math::dimensional<T, 2> omni::geometry::raw_size::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{10,5}");
            
            // to_size ~~ omni::geometry::size<T> omni::geometry::raw_size::to_size()
            test("temp_val.to_size()", temp_val.to_size(), "{10,5}");
            
            // to_string ~~ std::string omni::geometry::raw_size::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{10,5}");
            
            // to_string_t ~~ omni::string_t omni::geometry::raw_size::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{10,5}");
            
            // to_wstring ~~ std::wstring omni::geometry::raw_size::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{10,5}");
            
            // operator omni::math::dimensional<T, 2> ~~  omni::geometry::raw_size::operator omni::math::dimensional<T, 2>()
            test("(static_cast< omni::math::dimensional<T, 2> >(temp_val))", (static_cast< omni::math::dimensional<int32_t, 2> >(temp_val)), "{10,5}");
            
            // operator std::string ~~  omni::geometry::raw_size::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{10,5}");
            
            // operator std::wstring ~~  omni::geometry::raw_size::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{10,5}");
            
            // operator!= ~~ bool omni::geometry::raw_size::operator!=(const raw_size< T >& val)
            test("(temp_val != val)", ((temp_val != val) ? "true" : "false"), "true");
            
            // operator+ ~~ raw_size<T> omni::geometry::raw_size::operator+(const raw_size<T>& val)
            test("(temp_val + val)", (temp_val + val), "{13,11}");
            
            // operator+= ~~ raw_size<T>& omni::geometry::raw_size::operator+=(const raw_size<T>& val)
            test("(temp_val += val)", (temp_val += val), "{13,11}");
            
            // operator- ~~ raw_size<T> omni::geometry::raw_size::operator-(const raw_size<T>& val)
            test("(temp_val - val)", (temp_val - val), "{10,5}");
            
            // operator-= ~~ raw_size<T>& omni::geometry::raw_size::operator-=(const raw_size<T>& val)
            test("(temp_val -= val)", (temp_val -= val), "{10,5}");
            
            // operator< ~~ bool omni::geometry::raw_size::operator<(const raw_size<T>& val)
            test("(temp_val < val)", ((temp_val < val) ? "true" : "false"), "false");
            
            // operator<= ~~ bool omni::geometry::raw_size::operator<=(const raw_size<T>& val)
            test("(temp_val <= val)", ((temp_val <= val) ? "true" : "false"), "false");
            
            // operator= ~~ raw_size<T>& omni::geometry::raw_size::operator=(const raw_size<T>& val)
            test("(temp_val = val)", (temp_val = val), "{3,6}");
            
            // operator== ~~ bool omni::geometry::raw_size::operator==(const raw_size< T >& val)
            test("(temp_val == val)", ((temp_val == val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::raw_size::operator>(const raw_size<T>& val)
            test("(temp_val > val)", ((temp_val > val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::raw_size::operator>=(const raw_size<T>& val)
            test("(temp_val >= val)", ((temp_val >= val) ? "true" : "false"), "true");
            
            // height ~~ T omni::geometry::raw_size::height
            test("temp_val.height", temp_val.height, "3");
            
            // width ~~ T omni::geometry::raw_size::width
            test("temp_val.width", temp_val.width, "6");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SIZE
