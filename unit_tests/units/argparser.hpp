#if defined(OMNI_UTUA) || defined(OMNI_UT_ARGPARSER)

#define UT_NAME argparser
#define UT_ROOT_NS application
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(ctor_test, "tests the argparser constructor");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::application::argparser args = omni::application::args();
            UT_CNAME::print_arg_info(args);
            const char* targv[] = { "targv", "1", "2", "another", "final" };
            omni::application::argparser a1(5, targv);
            omni::application::argparser *a2 = new omni::application::argparser(5, targv);
            UT_CNAME::print_arg_info(a1);
            UT_CNAME::print_arg_info(*a2);
            delete a2;
        }
        
        void ctor_test()
        {
            omni::application::argparser a1(omni::application::args().argv());
            omni::application::argparser *a2 = new omni::application::argparser(omni::application::args());
            UT_CNAME::print_arg_info(a1);
            UT_CNAME::print_arg_info(*a2);
            delete a2;
        }
        
        void print_arg_info(const omni::application::argparser& args)
        {
            omni::out << "args.argc: " << args.argc() << std::endl;
            if (args.argc() > 1) {
                omni::out << "args[1] = " << args[1].c_str() << std::endl;
            }
            omni::out << "args.to_string_t(): " << args.to_string_t() << std::endl;
            omni::out << "args.to_string_t(true): " << args.to_string_t(true) << std::endl;
            
            std::cout << "args.to_string(): " << args.to_string() << std::endl;
            std::cout << "args.to_string(true): " << args.to_string(true) << std::endl;
            
            std::wcout << "args.to_wstring(): " << args.to_wstring() << std::endl;
            std::wcout << "args.to_wstring(true): " << args.to_wstring(true) << std::endl;
            
            std::cout << "static_cast<std::string>(args) = " << static_cast<std::string>(args) << std::endl;
            std::wcout << "static_cast<std::wstring>(args) = " << static_cast<std::wstring>(args) << std::endl;
            
            omni::out << "testing implicit casting:" << std::endl;
            std::string s = args; // operator std::string() const
            std::wstring w = args; // operator std::wstring() const
            std::cout << "s = " << s << std::endl;
            std::wcout << "w = " << w << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_ARGPARSER
