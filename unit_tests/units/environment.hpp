#if defined(OMNI_UTUA) || defined(OMNI_UT_ENVIRONMENT)

#define UT_NAME environment
#define UT_ISNS true
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            // PATH env_var might not carry over for this test
            omni::out << "Checking PATH" << std::endl;
            if (omni::environment::var_exists("PATH")) {
                omni::out << "omni::environment::get_var(\"PATH\") = ";
                std::cout << omni::environment::get_var("PATH") << std::endl;
                std::wcout << omni::environment::get_var(L"PATH") << std::endl;
            } else {
                omni::out << "PATH environment variable not found" << std::endl;
            }
            #if defined(OMNI_OS_WIN)
                try {
                    omni::out << "omni::environment::get_var(\"%SYSTEMROOT%\") = ";
                    std::cout << omni::environment::get_var("%SYSTEMROOT%") << std::endl;
                    std::wcout << omni::environment::get_var(L"%SYSTEMROOT%") << std::endl;
                } catch (omni::exception e) {
                    omni::out << "framework exception caught: " << e.what() << std::endl;
                }
                try {
                    omni::out << "omni::environment::expand_vars(\"Progfiles is '%ProgramFiles%' and sysroot is '%systemroot%'\") = ";
                    std::cout << omni::environment::expand_vars("Progfiles is '%ProgramFiles%' and sysroot is '%systemroot%'") << std::endl;
                    std::wcout << omni::environment::expand_vars(L"Progfiles is '%ProgramFiles%' and sysroot is '%systemroot%'") << std::endl;
                } catch (omni::exception e) {
                    omni::out << "framework exception caught: " << e.what() << std::endl;
                }
            #else
                try {
                    omni::out << "omni::environment::expand_vars(\"We are currently at `pwd` and path = ${PATH}\") = ";
                    std::cout << omni::environment::expand_vars("We are currently at '`pwd`' and path = '${PATH}'") << std::endl;
                    std::wcout << omni::environment::expand_vars(L"We are currently at '`pwd`' and path = '${PATH}'") << std::endl;
                } catch (omni::exception e) {
                    omni::out << "framework exception caught: " << e.what() << std::endl;
                }
            #endif
            if (omni::environment::var_exists("OMNI_UNAME")) {
                omni::out << "OMNI_UNAME exists" << std::endl;
            } else {
                omni::out << "OMNI_UNAME does NOT exists" << std::endl;
            }
            if (omni::environment::set_var("OMNI_UNAME", "zeriph")) {
                omni::out << "set OMNI_UNAME to 'zeriph'" << std::endl;
            } else {
                omni::out << "did NOT set OMNI_UNAME to 'zeriph'" << std::endl;
            }
            if (omni::environment::var_exists("OMNI_UNAME")) {
                omni::out << "OMNI_UNAME exists" << std::endl;
            } else {
                omni::out << "OMNI_UNAME does NOT exists" << std::endl;
            }
            try {
                omni::out << "calling get_var(\"OMNI_UNAME\")" << std::endl;
                std::cout << "OMNI_UNAME = " << omni::environment::get_var("OMNI_UNAME") << std::endl;
                std::wcout << "OMNI_UNAME = " << omni::environment::get_var(L"OMNI_UNAME") << std::endl;
            } catch (omni::exception e) {
                omni::out << "framework exception caught: " << e.what() << std::endl;
            }
            omni::out << "deleting OMNI_UNAME" << std::endl;
            if (!omni::environment::delete_var("OMNI_UNAME")) {
                omni::out << "could not delete" << std::endl;
            } else {
                omni::out << "deleted" << std::endl;
            }
            if (omni::environment::var_exists("OMNI_UNAME")) {
                omni::out << "OMNI_UNAME exists" << std::endl;
            } else {
                omni::out << "OMNI_UNAME does NOT exists" << std::endl;
            }
            try {
                omni::out << "calling get_var(\"OMNI_UNAME\")" << std::endl;
                std::cout << "OMNI_UNAME = " << omni::environment::get_var("OMNI_UNAME") << std::endl;
                std::wcout << "OMNI_UNAME = " << omni::environment::get_var(L"OMNI_UNAME") << std::endl;
            } catch (omni::exception e) {
                omni::out << "framework exception caught: " << e.what() << std::endl;
            }
            omni::out << "new line";
            omni::out << omni::environment::NEW_LINE;
            omni::out << "new line" << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_ENVIRONMENT
