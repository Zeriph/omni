#if defined(OMNI_UTUA) || defined(OMNI_UT_STRING)

#define UT_NAME string
#define UT_ISNS 
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(binary_test, "tests the binary string functionality of the omni::string namespace");
            M_LIST_ADD(trim_test, "tests the trim functionality");
            M_LIST_ADD(cast_test, "tests the cast functionality");
            M_LIST_ADD(cstring_test, "tests the basic functionality of the omni::cstring namespace");
            M_LIST_ADD(wstring_test, "tests the basic functionality of the omni::wstring namespace");
            M_LIST_ADD(string_util_test, "tests the string util namespace");
            M_LIST_ADD(split_test, "tests the string split functionality");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::string_t s = OMNI_STRW("omni::string_t test");
            omni::out << s << std::endl;
            omni::char_t c = OMNI_STRW('c');
            omni::out << "char test: " << c << std::endl;
            
            /*
            TODO: add the following
            ->inline bool ends_with(const OMNI_STRING_T_FW& chk, const OMNI_STRING_T_FW& fnd, bool ignore_case)
            ->inline bool starts_with(const OMNI_STRING_T_FW& chk, const OMNI_STRING_T_FW& fnd, bool ignore_case)

            omni::string::contains(const std::string& chk, const std::string& fnd, bool ignoreCase);
            omni::string::is_numeric(const std::string& str, bool ignorePeriod);
            omni::string::pad_left(std::string str, char pad, size_t count);
            omni::string::pad_left(std::string str, const std::string& pad, size_t count);
            omni::string::pad_right(std::string str, char pad, size_t count);
            omni::string::pad_right(std::string str, const std::string& pad, size_t count);
            omni::string::replace(std::string str, const std::string& fnd, const std::string& newstr, size_t pos, bool ignoreCase);
            omni::string::replace_all(std::string str, const std::string& fnd, const std::string& newstr, size_t pos, bool ignoreCase);
            omni::string::reverse(const std::string& str);
            omni::string::split(const std::string& str, const std::string& delimeter, size_t max);
            omni::string::to_lower(std::string str);
            omni::string::to_upper(std::string str);
            omni::string::to_string(const std::wstring& str);
            omni::string::to_wstring(const std::string& str);
            omni::string::trim(std::string str);
            omni::string::trim(std::string str, char param);
            omni::string::trim(std::string str, omni_seq_t<std::string> params);
            omni::string::trim_end(std::string str);
            omni::string::trim_end(std::string str, char param);
            omni::string::trim_end(std::string str, omni_seq_t<std::string> params);
            omni::string::trim_front(std::string str);
            omni::string::trim_front(std::string str, char param);
            omni::string::trim_front(std::string str, omni_seq_t<std::string> params);
            omni::string::trim_syschars(std::string str);
            omni::string::trim_front_syschars(std::string str);
            omni::string::trim_end_syschars(std::string str);
            template <typename type> std::string type_cast(type val);
            template <bool> std::string type_cast(bool val);
            template <typename ret_t> ret_t type_cast(const std::string &str);
            template <bool> bool type_cast(const std::string& str);
            template <typename ret_t> ret_t type_cast(const char *str);*/
        }
        
        void binary_test()
        {
            omni::out << "bin sizeof(uint): " << omni::bits::size<unsigned int>() << std::endl;
            omni::out << "bin sizeof(ulong): " << omni::bits::size<unsigned long>() << std::endl;
            omni::out << "bin sizeof(size_t): " << omni::bits::size<std::size_t>() << std::endl;
            
            // 01010111
            printv("87 in binary: ", omni::string::binary::from_uint(87));
            printv("87 in binary (not trimmed): ", omni::string::binary::from_uint(87, false));
            
            // 00001111000011111111000011111111
            printv("252702975 in binary: ", omni::string::binary::from_ulong(252702975));
            printv("252702975 in binary (not trimmed): ", omni::string::binary::from_ulong(252702975, false));

            unsigned int osbtui = omni::cstring::binary::to_uint("10110101");
            printv("10110101 = ", osbtui); // 181
            unsigned long osbtul = omni::cstring::binary::to_ulong("11111111000011111111000011111111");
            printv("11111111000011111111000011111111 = ", osbtul); // 4,279,234,815
            
            try {
                unsigned int osbtui2 = omni::cstring::binary::to_uint("10110101a");
                printv("osbtui2 = ", osbtui2); // "The specified string does not contain a valid binary number"
            } catch (const std::exception& ex) {
                std::cout << "exception caught: " << ex.what() << std::endl;
            }
            try {
                unsigned long osbtul2 = omni::cstring::binary::to_ulong("1011010100000000000000200000000010110101");
                printv("osbtul2 = ", osbtul2); // "The specified string does not contain a valid binary number"
            } catch (const std::exception& ex) {
                std::cout << "exception caught: " << ex.what() << std::endl;
            }
            try {
                // 33 char's (sizeof(uint) == 32)
                unsigned int osbtui2 = omni::cstring::binary::to_uint("101010101010101000000000010110101");
                printv("osbtui2 = ", osbtui2); // "The binary string length is greater than sizeof conversion unit"
            } catch (const std::exception& ex) {
                std::cout << "exception caught: " << ex.what() << std::endl;
            }
            try {
                // 65 char's (sizeof(ulong) == 64)
                unsigned long osbtul2 = omni::cstring::binary::to_ulong("10101010101010100000000001011010110101010101010100000000001010101");
                printv("osbtul2 = ", osbtul2); // "The binary string length is greater than sizeof conversion unit"
            } catch (const std::exception& ex) {
                std::cout << "exception caught: " << ex.what() << std::endl;
            }
        }

        void trim_test()
        {
            std::string p = " TxZ"; // trim chars
            std::string s = "   TxZxxxTTTzZZthis is a test string   ";
            
            std::cout << "Trim chars: |" << p << "|" << std::endl;
            
            std::cout << "TRIM FRONT" << std::endl;
            std::cout << "s = |" << s << "|" << std::endl;
            std::string c = omni::string::util::trim_front(s, p.begin(), p.end());
            std::cout << "s = |" << s << "|" << std::endl;
            std::cout << "c = |" << c << "|" << std::endl;
            std::cout << "z = |zZZthis is a test string   |" << std::endl;
            
            std::cout << "TRIM END" << std::endl;
            s = "   this is a test string XXzzTxZxxxTTTxZZ   ";
            std::cout << "s = |" << s << "|" << std::endl;
            c = omni::string::util::trim_end(s, p);
            std::cout << "s = |" << s << "|" << std::endl;
            std::cout << "c = |" << c << "|" << std::endl;
            std::cout << "z = |   this is a test string XXzz|" << std::endl;
            
            std::cout << "TRIM" << std::endl;
            s = "   \tTxZxxxTTTzZZthis is a test string XXzzTxZxxxTTTxZZ   \t\r\n   \0   ";
            std::cout << "s = |" << s << "|" << std::endl;
            c = omni::string::util::trim(s);
            std::cout << "s = |" << s << "|" << std::endl;
            std::cout << "c = |" << c << "|" << std::endl;
            std::cout << "z = |TxZxxxTTTzZZthis is a test string XXzzTxZxxxTTTxZZ|" << std::endl;
            
            std::cout << "EX TRIM" << std::endl;
            std::string cs = "   \tTxZxxxTTTzZZthis is a test string XXzzTxZxxxTTTxZZ   \t\r\n   \0   ";
            std::wstring ws = L"   \tTxZxxxTTTzZZthis is a test string XXzzTxZxxxTTTxZZ   \t\r\n   \0   ";
            std::cout << "cs = |" << cs << "|" << std::endl;
            std::wcout << "ws = |" << ws << "|" << std::endl;
            
            std::string cc = omni::cstring::trim(cs);
            std::wstring wc = omni::wstring::trim(ws);
            
            std::string ccu = omni::string::util::trim(cs);
            std::wstring wcu = omni::string::util::trim(ws);
            
            std::cout << "cs = |" << cs << "|" << std::endl;
            std::cout << "cc = |" << cc << "|" << std::endl;
            std::cout << "ccu= |" << ccu<< "|" << std::endl;
            
            std::wcout << "ws = |" << ws << "|" << std::endl;
            std::wcout << "wc = |" << wc << "|" << std::endl;
            std::wcout << "wcu= |" << wcu<< "|" << std::endl;
            std::cout << "zz = |TxZxxxTTTzZZthis is a test string XXzzTxZxxxTTTxZZ|" << std::endl;
        }
        
        void cast_test()
        {
            std::wstring ws2 = omni::wstring::lexical_cast(42);
            std::string cs2 = omni::cstring::lexical_cast(42);
            omni::string_t os2 = omni::string::lexical_cast(42);
            
            wprintv("42 == ws2(s) == ", ws2);
            cprintv("42 == cs2(s) == ", cs2);
            printv("42 == os2(s) == ", os2);
            
            int ws3 = omni::wstring::type_cast<int>(ws2);
            int cs3 = omni::cstring::type_cast<int>(cs2);
            int os3 = omni::string::type_cast<int>(os2);
            
            wprintv("42 == ws3(i) == ", ws3);
            cprintv("42 == cs3(i) == ", cs3);
            printv("42 == os3(i) == ", os3);
            
            int ws4 = omni::string::util::to_type<int>(ws2) + 22;
            int cs4 = omni::string::util::to_type<int>(cs2) + 22;
            int os4 = omni::string::util::to_type<int>(os2) + 22;
            
            wprintv("64 == ws4(i) == ", ws4);
            cprintv("64 == cs4(i) == ", cs4);
            printv("64 == os4(i) == ", os4);
            
            std::wstring ws5 = omni::wstring::lexical_cast(ws4);
            std::string cs5 = omni::cstring::lexical_cast(ws4);
            omni::string_t os5 = omni::string::lexical_cast(ws4);
            
            wprintv("64 == ws5(i) == ", ws5);
            cprintv("64 == cs5(i) == ", cs5);
            printv("64 == os5(i) == ", os5);
            
            std::wstring ws = omni::string::util::to_wstring(true);
            std::string cs = omni::string::util::to_string(true);
            omni::string_t os = omni::string::util::to_string_t(true);
            printv("true = ", true);
            printv("false = ", false);
            wprintv("ws = ", ws);
            cprintv("cs = ", cs);
            printv("os = ", os);
            
            bool tval = true;
            bool fval = false;
            printv("tval = ", omni::string::lexical_cast(tval));
            printv("fval = ", omni::string::lexical_cast(fval));
            
            printv("lexi true = ", omni::string::lexical_cast(true));
            printv("lexi false = ", omni::string::lexical_cast(false));
            
            omni::object o("my name");
            printv("omni::object o = ", o);
            cprintv("omni::object o = ", o);
            std::string sa = omni::string::util::to_string(o);
            std::string sa2 = omni::cstring::lexical_cast(o);
            cprintv("sa = ", sa);
            cprintv("sa2 = ", sa2);
            std::wstring wa = omni::string::util::to_wstring(o);
            std::wstring wa2 = omni::wstring::lexical_cast(o);
            wprintv("wa = ", wa);
            wprintv("wa2 = ", wa2);
            omni::string_t oa = omni::string::util::to_string_t(o);
            omni::string_t oa2 = omni::string::lexical_cast(o);
            printv("oa = ", oa);
            printv("oa2 = ", oa2);
            
            printv("omni::application::args() = ", omni::application::args());
            std::string sargs = omni::cstring::lexical_cast(omni::application::args());
            std::string sargs2 = omni::string::util::to_string(omni::application::args());
            cprintv("sargs = ", sargs);
            cprintv("sargs2 = ", sargs2);
            std::wstring wargs = omni::wstring::lexical_cast(omni::application::args());
            std::wstring wargs2 = omni::string::util::to_wstring(omni::application::args());
            wprintv("wargs = ", wargs);
            wprintv("wargs2 = ", wargs2);
            omni::string_t oargs = omni::string::lexical_cast(omni::application::args());
            omni::string_t oargs2 = omni::string::util::to_string_t(omni::application::args());
            printv("oargs = ", oargs);
            printv("oargs2 = ", oargs2);
        }
        
        void cstring_test()
        {
            std::string s = "   this is a test string   ";
            std::cout << "s = |" << s << "|" << std::endl;
            std::string c = omni::cstring::trim(s);
            std::cout << "c = |" << c << "|" << std::endl;
            std::cout << "s = |" << s << "|" << std::endl;
        }

        void wstring_test()
        {
            std::wstring s = L"   this is a test string   ";
            std::wcout << "s = |" << s << "|" << std::endl;
            std::wstring c = omni::wstring::trim(s);
            std::wcout << "c = |" << c << "|" << std::endl;
            std::wcout << "s = |" << s << "|" << std::endl;
        }

        void split_test()
        {
            omni_seq_t<std::string> seqt = omni::string::util::split("this is a test", " ");
            std::deque<std::string> veqt = omni::string::util::split("this is a test", " ");
            
            
            omni::ut::print_list(seqt.begin(), seqt.end());
            omni::ut::print_list(veqt.begin(), veqt.end());
            
            
        }
        
        void string_util_test()
        {
            std::string s = omni::string::util::to_string(42);
            std::cout << "sval = " << s << std::endl; // output: sval = 42
            
            omni::object o("my name");
            
            std::string sa = omni::string::util::to_string(o);
            std::cout << "sval = " << sa << std::endl; // output: sval = whatever_the_args_would_be
            
            std::string imp = omni::string::util::to_string(42);
            int iimp = omni::string::util::to_type<int>("42");
            std::cout << "imp = " << imp << std::endl;
            std::cout << "iimp = " << iimp << std::endl;
            
            std::string is = omni::string::util::to_string(42); // stringizes 42
            int i = omni::string::util::to_type<int>(is);
            std::cout << "i = " << i << std::endl; // i = 42
            int z = omni::string::util::to_type<int>("42");
            std::cout << "z = " << z << std::endl; // z = 42
            
            
            
            std::wstring ws = omni::string::util::to_wstring(42);
            std::wcout << "sval = " << ws << std::endl; // output: sval = 42
            
            std::wstring wis = omni::string::util::to_wstring(42); // stringizes 42
            int wi = omni::string::util::to_type<int>(wis);
            std::wcout << "i = " << wi << std::endl; // i = 42
            int wz = omni::string::util::to_type<int>(L"42");
            std::wcout << "z = " << wz << std::endl; // z = 42
            
            std::string sstr("string value");
            std::wstring wstr(L"wstring value");
            
            std::cout << "sstr = " << sstr << std::endl;
            std::wcout << "wstr = " << wstr << std::endl;
            
            sstr = omni::string::util::to_upper(sstr);
            wstr = omni::string::util::to_upper(wstr);
            
            std::cout << "sstr = " << sstr << std::endl;
            std::wcout << "wstr = " << wstr << std::endl;
            
            sstr = omni::string::util::to_upper("this IS a test");
            wstr = omni::string::util::to_upper(L"this IS a test");
            
            std::cout << "sstr = " << sstr << std::endl;
            std::wcout << "wstr = " << wstr << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_STRING
