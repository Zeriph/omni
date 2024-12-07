#if defined(OMNI_UTUA) || defined(OMNI_UT_SEQ)

#define UT_ROOT_NS seq
#define UT_NAME seq
#define UT_ISNS true
#define UT_DESC "Tests the various functionality of the omni::seq namespace"
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::seq::string_t ost = _get_list<omni::string_t>(omni::string::to_string_t("abc"),omni::string::to_string_t("abc"),omni::string::to_string_t("abc"),omni::string::to_string_t("abc"),omni::string::to_string_t("abc"));
            print("ost vals ="); omni_foreach(omni::string_t, val, ost) { print(*val << ", "); } print(std::endl);

            omni::seq::std_string_t osst = _get_list<std::string>("abc","def","ghi","jkl","mno");
            print("osst vals ="); omni_foreach(std::string, val, osst) { cprint(*val << ", "); } print(std::endl);
            
            omni::seq::std_wstring_t oswt = _get_list<std::wstring>(L"abc",L"def",L"ghi",L"jkl",L"mno");
            print("oswt vals ="); omni_foreach(std::wstring, val, oswt) { wprint(*val << ", "); } print(std::endl);

            omni::seq::char_t oct = _get_list<char>('a','b','c','d','e');
            print("oct vals ="); omni_foreach(char, val, oct) { print(*val << ", "); } print(std::endl);

            omni::seq::wide_char_t owct = _get_list<wchar_t>(L'a',L'b',L'c',L'd',L'e');
            print("owct vals ="); omni_foreach(wchar_t, val, owct) { wprint(*val << ", "); } print(std::endl);

            omni::seq::short_t os = _get_list<short>(-1000,-2000,-3000,-4000,-5000);
            print("os vals ="); omni_foreach(short, val, os) { print(*val << ", "); } print(std::endl);

            omni::seq::int_t oi = _get_list<int>(-1000,-2000,-3000,-4000,-5000);
            print("oi vals ="); omni_foreach(int, val, oi) { print(*val << ", "); } print(std::endl);

            omni::seq::long_t ol = _get_list<long>(-1000,-2000,-3000,-4000,-5000);
            print("ol vals ="); omni_foreach(long, val, ol) { print(*val << ", "); } print(std::endl);

            omni::seq::double_t od = _get_list<double>(-1.23,1.23,3.11,4000,5000);
            print("od vals ="); omni_foreach(double, val, od) { print(*val << ", "); } print(std::endl);

            omni::seq::float_t of = _get_list<float>(-1.23,1.23,3.11,4000,5000);
            print("of vals ="); omni_foreach(float, val, of) { print(*val << ", "); } print(std::endl);

            omni::seq::int8_t oi8 = _get_list<int8_t>(-10,20,30,127,-128);
            print("oi8 vals ="); omni_foreach(int8_t, val, oi8) { print(*val << ", "); } print(std::endl);

            omni::seq::int16_t oi16 = _get_list<int16_t>((int16_t)-1000,(int16_t)-2000,(int16_t)-3000,(int16_t)-4000,(int16_t)-5000);
            print("oi16 vals ="); omni_foreach(int16_t, val, oi16) { print(*val << ", "); } print(std::endl);

            omni::seq::int32_t oi32 = _get_list<int32_t>(-1000,-2000,-3000,-4000,-5000);
            print("oi32 vals ="); omni_foreach(int32_t, val, oi32) { print(*val << ", "); } print(std::endl);

            omni::seq::int64_t oi64 = _get_list<int64_t>(-1000,-2000,-3000,-4000,-5000);
            print("oi64 vals ="); omni_foreach(int64_t, val, oi64) { print(*val << ", "); } print(std::endl);

            omni::seq::uchar_t ouc = _get_list<unsigned char>(8,16,32,64,255);
            print("ouc vals ="); omni_foreach(unsigned char, val, ouc) { print(*val << ", "); } print(std::endl);

            omni::seq::ushort_t ous = _get_list<unsigned short>(1000,2000,3000,4000,5000);
            print("ous vals ="); omni_foreach(unsigned short, val, ous) { print(*val << ", "); } print(std::endl);

            omni::seq::uint_t oui = _get_list<unsigned int>(1000,2000,3000,4000,5000);
            print("oui vals ="); omni_foreach(unsigned int, val, oui) { print(*val << ", "); } print(std::endl);

            omni::seq::ulong_t oul = _get_list<unsigned long>(1000,2000,3000,4000,5000);
            print("oul vals ="); omni_foreach(unsigned long, val, oul) { print(*val << ", "); } print(std::endl);

            omni::seq::uint8_t oui8 = _get_list<uint8_t>(8,16,32,64,255);
            print("oui8 vals ="); omni_foreach(uint8_t, val, oui8) { print(*val << ", "); } print(std::endl);

            omni::seq::uint16_t oui16 = _get_list<uint16_t>(1000,2000,3000,4000,5000);
            print("oui16 vals ="); omni_foreach(uint16_t, val, oui16) { print(*val << ", "); } print(std::endl);

            omni::seq::uint32_t oui32 = _get_list<uint32_t>(1000,2000,3000,4000,5000);
            print("oui32 vals ="); omni_foreach(uint32_t, val, oui32) { print(*val << ", "); } print(std::endl);

            omni::seq::uint64_t oui64 = _get_list<uint64_t>(1000,2000,3000,4000,5000);
            print("oui64 vals ="); omni_foreach(uint64_t, val, oui64) { print(*val << ", "); } print(std::endl);

            //template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            //inline bool equal(const std_seq_t<T, std_allocator_t >& a, const std_seq_t<T, std_allocator_t >& b)
            omni::seq::uint8_t oui822 = oui8;
            test("oui8 == oui822? ", b2s(omni::sequence::equal(oui8, oui822)), "true");
            //inline bool equals(InputIterator start1, InputIterator end1, InputIterator start2, InputIterator end2)
            test("oui8.begin-end == oui822.begin-end? ", b2s(omni::sequence::equals(oui8.begin(), oui8.end(), oui822.begin(), oui822.end())), "true");
            oui822.pop_back();
            test("oui8.begin-end == oui822.begin-end? ", b2s(omni::sequence::equals(oui8.begin(), oui8.end(), oui822.begin(), oui822.end())), "false");
            //template < template < class, class > class std_seq_t, class T, class std_allocator_t, class InputIterator >
            //void add_range(std_seq_t<T, std_allocator_t>& array, InputIterator start, InputIterator end)
            omni::sequence::add_range(oui822, oui8.begin(), oui8.end());
            print("oui822 vals ="); omni_foreach(uint8_t, val, oui822) { print(*val << ", "); } print(std::endl);
            //template < template < class, class > class std_seq_t, class T, class std_allocator_t >
            //void add_range(std_seq_t<T, std_allocator_t>& array1, const std_seq_t<T, std_allocator_t>& array2)
            omni::sequence::add_range(oui822, oui8);
            print("oui822 vals ="); omni_foreach(uint8_t, val, oui822) { print(*val << ", "); } print(std::endl);

            std::vector<uint8_t> vec;
            for (int i = 10; i < 15; ++i) { vec.push_back(i); }
            print("vector<uint8_t> ="); std_foreach(std::vector<uint8_t>, val, vec) { print(*val << ", "); } print(std::endl);
        }

    private:
        template < typename T >
        omni_seq_t<T> _get_list(T a, T b, T c, T d, T e)
        {
            omni_seq_t<T> vals;
            vals.push_back(a);
            vals.push_back(b);
            vals.push_back(c);
            vals.push_back(d);
            vals.push_back(e);
            return vals;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMESPAN
