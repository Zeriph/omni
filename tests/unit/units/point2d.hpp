#if defined(OMNI_UTUA) || defined(OMNI_UT_POINT2D)

#define UT_NAME point2d
#define UT_ROOT_NS geometry
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(point2d, "test the functionality in omni::geometry::point2d");
            M_LIST_ADD(raw_point2d, "test the functionality in omni::geometry::raw_point2d");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::point_t);
            print_info(omni::geometry::raw_point_t);
        }
        
        void base_test()
        {
            point2d(); printl("");
            raw_point2d(); printl("");
        }

        void point2d()
        {
            omni::geometry::pointD_t pdt(334.299191919817, 445.48481811);
            omni::geometry::pointF_t pft(3.14159, -1.570795);
            omni::geometry::point64_t pst(8589934592, -8589934592);
            omni::geometry::point_t pnt;

            printl(pdt);
            printl(pft);
            printl(pnt);

            printl(pst);
            printv("pst.hash_code()", pst.hash_code());

            //  omni::geometry::point2d::point2d()
            omni::geometry::point_t val(5, 10);
            omni::geometry::point_t temp_val;
            omni::geometry::point_t::coordinate_t T_x = -6;
            omni::geometry::point_t::coordinate_t T_y = -11;


            // void omni::geometry::point2d::decrement(const point2d<T>& val)
            temp_val.decrement(val);
            test("temp_val.decrement(val)", temp_val, "{-5, -10}");

            // T omni::geometry::point2d::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "-6");

            // T omni::geometry::point2d::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "-11");

            // bool omni::geometry::point2d::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");

            // bool omni::geometry::point2d::equals(T x, T y)
            test("temp_val.equals(T_x, T_y)", (temp_val.equals(T_x, T_y) ? "true" : "false"), "true");

            // void omni::geometry::point2d::increment(const point2d<T>& val)
            temp_val.increment(val);
            test("temp_val.increment(val)", temp_val, "{-1, -1}");

            // T omni::geometry::point2d::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "0");

            // T omni::geometry::point2d::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "0");

            // void omni::geometry::point2d::offset(const point2d<T>& val)
            temp_val.offset(val);
            test("temp_val.offset(val)", temp_val, "{5, 10}");

            // void omni::geometry::point2d::set(T x, T y)
            temp_val.set(T_x, T_y);
            test("temp_val.set(T_x, T_y)", temp_val, "{-6, -11}");

            // void omni::geometry::point2d::swap(point2d<T>& o)
            temp_val.swap(val);
            test("temp_val.swap(val)", temp_val, "{5, 10}");
            test("val", val, "{-6,-11}");

            // omni::math::dimensional<T, 2> omni::geometry::point2d::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{5, 10}");

            // omni::geometry::raw_size<T> omni::geometry::point2d::to_raw_size()
            test("temp_val.to_raw_size()", temp_val.to_raw_size(), "{5, 10}");

            // omni::geometry::size<T> omni::geometry::point2d::to_size()
            test("temp_val.to_size()", temp_val.to_size(), "{5, 10}");

            // std::string omni::geometry::point2d::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{5, 10}");

            // omni::string_t omni::geometry::point2d::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{5, 10}");

            // std::wstring omni::geometry::point2d::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{5, 10}");

            // T omni::geometry::point2d::x()
            test("temp_val.x()", temp_val.x(), "5");

            // T omni::geometry::point2d::y()
            test("temp_val.y()", temp_val.y(), "10");

            //  omni::geometry::point2d::operator omni::geometry::raw_size<T>()
            omni::geometry::raw_size<int32_t> srsz = temp_val;
            test("(operator  omni::geometry::raw_size<T>)", srsz, "{5, 10}");

            //  omni::geometry::point2d::operator omni::geometry::size<T>()
            omni::geometry::size<int32_t> ssz = temp_val;
            test("(operator  omni::geometry::size<T>)", ssz, "{5, 10}");

            //  omni::geometry::point2d::operator omni::math::dimensional<T, 2>()
            omni::math::dimensional<int32_t, 2> dim = temp_val;
            test("(operator  omni::math::dimensional<T, 2>)", dim, "{5, 10}");

            //  omni::geometry::point2d::operator std::string()
            test("(operator  std::string)", static_cast<std::string>(temp_val), "{5, 10}");

            //  omni::geometry::point2d::operator std::wstring()
            test("(operator  std::wstring)", static_cast<std::wstring>(temp_val), "{5, 10}");

            // bool omni::geometry::point2d::operator!=(const point2d<T>& val)
            test("(temp_val != omni::geometry::point2d(10, 20))", ((temp_val != omni::geometry::point_t(10, 20)) ? "true" : "false"), "true");

            // point2d<T> omni::geometry::point2d::operator+(const point2d<T>& val)
            test("(temp_val + omni::geometry::point2d(10, 20))", (temp_val + omni::geometry::point_t(10, 20)), "{15, 30}");

            // point2d<T>& omni::geometry::point2d::operator+=(const point2d<T>& val)
            test("(temp_val += omni::geometry::point2d(10, 20))", (temp_val += omni::geometry::point_t(10, 20)), "{15, 30}");

            // point2d<T> omni::geometry::point2d::operator-(const point2d<T>& val)
            test("(temp_val - omni::geometry::point2d(10, 20))", (temp_val - omni::geometry::point_t(10, 20)), "{5, 10}");

            // point2d<T>& omni::geometry::point2d::operator-=(const point2d<T>& val)
            test("(temp_val -= omni::geometry::point2d(10, 20))", (temp_val -= omni::geometry::point_t(10, 20)), "{5, 10}");

            // bool omni::geometry::point2d::operator<(const point2d<T>& val)
            test("(temp_val < omni::geometry::point2d(10, 20))", ((temp_val < omni::geometry::point_t(10, 20)) ? "true" : "false"), "true");

            // bool omni::geometry::point2d::operator<=(const point2d<T>& val)
            test("(temp_val <= omni::geometry::point2d(10, 20))", ((temp_val <= omni::geometry::point_t(10, 20)) ? "true" : "false"), "true");

            // point2d<T>& omni::geometry::point2d::operator=(const point2d<T>& val)
            test("(temp_val = omni::geometry::point2d(10, 20))", (temp_val = omni::geometry::point_t(10, 20)), "{10, 20}");

            // bool omni::geometry::point2d::operator==(const point2d<T>& val)
            test("(temp_val == omni::geometry::point2d(10, 20))", ((temp_val == omni::geometry::point_t(10, 20)) ? "true" : "false"), "true");

            // bool omni::geometry::point2d::operator>(const point2d<T>& val)
            test("(temp_val > omni::geometry::point2d(10, 20))", ((temp_val > omni::geometry::point_t(10, 20)) ? "true" : "false"), "false");

            // bool omni::geometry::point2d::operator>=(const point2d<T>& val)
            test("(temp_val >= omni::geometry::point2d(10, 20))", ((temp_val >= omni::geometry::point_t(10, 20)) ? "true" : "false"), "true");

            // static point2d<T> omni::geometry::point2d::add(const point2d<T>& point, const omni::math::dimensional<T 2> coord)
            test("omni::geometry::point_t::add(const point2d<T>& point, const omni::math::dimensional<T, 2> coord)", omni::geometry::point_t::add(temp_val, omni::math::dimensional<int32_t, 2>(5, 10)), "{15, 30}");

            // static point2d<T> omni::geometry::point2d::subtract(const point2d<T>& point, const omni::math::dimensional<T 2> coord)
            test("omni::geometry::point_t::subtract(const point2d<T>& point, const omni::math::dimensional<T 2> coord)", omni::geometry::point_t::subtract(temp_val, omni::math::dimensional<int32_t, 2>(10, 20)), "{0, 0}");
        }

        void raw_point2d()
        {
            // raw_point2d ~~  omni::geometry::raw_point2d::raw_point2d()
            omni::geometry::pointD_t pdt(334.299191919817, 445.48481811);
            omni::geometry::pointF_t pft(3.14159, -1.570795);
            omni::geometry::point64_t pst(8589934592, -8589934592);
            omni::geometry::point_t pnt;

            printl(pdt);
            printl(pft);
            printl(pnt);
            printl(pst);
            printv("pst.hash_code()", pst.hash_code());

            //  omni::geometry::point2d::point2d()
            omni::geometry::raw_point_t _val(5, 10);
            omni::geometry::raw_point_t temp_val;
            omni::geometry::raw_point_t::coordinate_t __x = -6;
            omni::geometry::raw_point_t::coordinate_t __y = -11;
            
            
            // decrement ~~ void omni::geometry::raw_point2d::decrement(const raw_point2d<T>& val)
            temp_val.decrement(_val);
            test("temp_val.decrement(_val)", temp_val, "{-5,-10}");
            
            // decrement_x ~~ T omni::geometry::raw_point2d::decrement_x()
            test("temp_val.decrement_x()", temp_val.decrement_x(), "-6");
            
            // decrement_y ~~ T omni::geometry::raw_point2d::decrement_y()
            test("temp_val.decrement_y()", temp_val.decrement_y(), "-11");
            
            // empty ~~ bool omni::geometry::raw_point2d::empty()
            test("temp_val.empty()", (temp_val.empty() ? "true" : "false"), "false");
            
            // equals ~~ bool omni::geometry::raw_point2d::equals(T _x, T _y)
            test("temp_val.equals(__x, __y)", (temp_val.equals(__x, __y) ? "true" : "false"), "true");
            
            // increment_x ~~ T omni::geometry::raw_point2d::increment_x()
            test("temp_val.increment_x()", temp_val.increment_x(), "-5");
            
            // increment_y ~~ T omni::geometry::raw_point2d::increment_y()
            test("temp_val.increment_y()", temp_val.increment_y(), "-10");
            
            // offset ~~ void omni::geometry::raw_point2d::offset(const raw_point2d<T>& val)
            temp_val.offset(_val);
            test("temp_val.offset(_val)", temp_val, "{0,0}");
            
            // set ~~ void omni::geometry::raw_point2d::set(T _x, T _y)
            _val.set(__x, __y);
            test("temp_val.set(__x, __y)", _val, "{-6,-11}");
            
            // swap ~~ void omni::geometry::raw_point2d::swap(raw_point2d<T>& o)
            temp_val.swap(_val);
            test("temp_val.swap(_val)", temp_val, "{-6,-11}");
            test("_val", _val, "{0,0}");
            _val.set(1,1);
            
            // to_dimensional ~~ omni::math::dimensional<T, 2> omni::geometry::raw_point2d::to_dimensional()
            test("temp_val.to_dimensional()", temp_val.to_dimensional(), "{-6,-11}");
            
            // to_point2d ~~ omni::geometry::point2d<T> omni::geometry::raw_point2d::to_point2d()
            test("temp_val.to_point2d()", temp_val.to_point2d(), "{-6,-11}");
            
            // to_raw_size ~~ omni::geometry::raw_size<T> omni::geometry::raw_point2d::to_raw_size()
            test("temp_val.to_raw_size()", temp_val.to_raw_size(), "{-6,-11}");
            
            // to_size ~~ omni::geometry::size<T> omni::geometry::raw_point2d::to_size()
            test("temp_val.to_size()", temp_val.to_size(), "{-6,-11}");
            
            // to_string ~~ std::string omni::geometry::raw_point2d::to_string()
            test("temp_val.to_string()", temp_val.to_string(), "{-6,-11}");
            
            // to_string_t ~~ omni::string_t omni::geometry::raw_point2d::to_string_t()
            test("temp_val.to_string_t()", temp_val.to_string_t(), "{-6,-11}");
            
            // to_wstring ~~ std::wstring omni::geometry::raw_point2d::to_wstring()
            test("temp_val.to_wstring()", temp_val.to_wstring(), "{-6,-11}");
            
            // operator omni::geometry::point2d<T> ~~  omni::geometry::raw_point2d::operator omni::geometry::point2d<T>()
            omni::geometry::point2d<int32_t> pt = temp_val;
            test("(static_cast< omni::geometry::point2d<T> >(temp_val))", pt, "{-6,-11}");
            
            // operator omni::geometry::raw_size<T> ~~  omni::geometry::raw_point2d::operator omni::geometry::raw_size<T>()
            omni::geometry::raw_size<int32_t> szx = temp_val;
            test("(static_cast< omni::geometry::raw_size<T> >(temp_val))", szx, "{-6,-11}");
            
            // operator omni::geometry::size<T> ~~  omni::geometry::raw_point2d::operator omni::geometry::size<T>()
            omni::geometry::size<int32_t> szy = temp_val;
            test("(static_cast< omni::geometry::size<T> >(temp_val))", szy, "{-6,-11}");
            
            // operator omni::math::dimensional<T, 2> ~~  omni::geometry::raw_point2d::operator omni::math::dimensional<T, 2>()
            omni::math::dimensional<int32_t, 2> dm = temp_val;
            test("(static_cast< omni::math::dimensional<T, 2> >(temp_val))", dm, "{-6,-11}");
            
            // operator std::string ~~  omni::geometry::raw_point2d::operator std::string()
            test("(static_cast< std::string >(temp_val))", (static_cast< std::string >(temp_val)), "{-6,-11}");
            
            // operator std::wstring ~~  omni::geometry::raw_point2d::operator std::wstring()
            test("(static_cast< std::wstring >(temp_val))", (static_cast< std::wstring >(temp_val)), "{-6,-11}");
            
            // operator!= ~~ bool omni::geometry::raw_point2d::operator!=(const raw_point2d<T>& val)
            test("(temp_val != _val)", ((temp_val != _val) ? "true" : "false"), "true");
            
            // operator+ ~~ raw_point2d<T> omni::geometry::raw_point2d::operator+(const raw_point2d<T>& val)
            test("(temp_val + _val)", (temp_val + _val), "{-5,10}");
            
            // operator+= ~~ raw_point2d<T>& omni::geometry::raw_point2d::operator+=(const raw_point2d<T>& val)
            test("(temp_val += _val)", (temp_val += _val), "{-5,10}");
            
            // operator- ~~ raw_point2d<T> omni::geometry::raw_point2d::operator-(const raw_point2d<T>& val)
            test("(temp_val - _val)", (temp_val - _val), "{-6,-11}");
            
            // operator-= ~~ raw_point2d<T>& omni::geometry::raw_point2d::operator-=(const raw_point2d<T>& val)
            test("(temp_val -= _val)", (temp_val -= _val), "{-6,-11}");
            
            // operator< ~~ bool omni::geometry::raw_point2d::operator<(const raw_point2d<T>& val)
            test("(temp_val < _val)", ((temp_val < _val) ? "true" : "false"), "true");
            
            // operator<= ~~ bool omni::geometry::raw_point2d::operator<=(const raw_point2d<T>& val)
            test("(temp_val <= _val)", ((temp_val <= _val) ? "true" : "false"), "true");
            
            // operator= ~~ raw_point2d<T>& omni::geometry::raw_point2d::operator=(const raw_point2d<T>& val)
            test("(temp_val = _val)", (temp_val = _val), "{1,1}");
            
            // operator== ~~ bool omni::geometry::raw_point2d::operator==(const raw_point2d<T>& val)
            test("(temp_val == _val)", ((temp_val == _val) ? "true" : "false"), "true");
            
            // operator> ~~ bool omni::geometry::raw_point2d::operator>(const raw_point2d<T>& val)
            test("(temp_val > _val)", ((temp_val > _val) ? "true" : "false"), "false");
            
            // operator>= ~~ bool omni::geometry::raw_point2d::operator>=(const raw_point2d<T>& val)
            test("(temp_val >= _val)", ((temp_val >= _val) ? "true" : "false"), "true");
            
            // x ~~ T omni::geometry::raw_point2d::x
            test("temp_val.x", temp_val.x, "1");
            
            // y ~~ T omni::geometry::raw_point2d::y
            test("temp_val.y", temp_val.y, "1");
            
            omni::geometry::raw_point2d<int32_t> _point(1, 2);
            omni::math::dimensional<int32_t, 2> _sz(3, 4);
            // add ~~ static raw_point2d<T> omni::geometry::raw_point2d::add(const raw_point2d<T>& point, const omni::math::dimensional<T 2> sz)
            test(" omni::geometry::raw_point2d::add(const raw_point2d<T>& point, const omni::math::dimensional<T 2> sz)",
                omni::geometry::raw_point2d<int32_t>::add(_point, _sz),
                "{4,6}");
            
            // subtract ~~ static raw_point2d<T> omni::geometry::raw_point2d::subtract(const raw_point2d<T>& point, const omni::math::dimensional<T 2> sz)
            test(" omni::geometry::raw_point2d::subtract(const raw_point2d<T>& point, const omni::math::dimensional<T 2> sz)",
                omni::geometry::raw_point2d<int32_t>::subtract(_point, _sz),
                "{-2,-2}");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_POINT2D
