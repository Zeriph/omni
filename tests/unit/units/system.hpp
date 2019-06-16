#if defined(OMNI_UTUA) || defined(OMNI_UT_SYSTEM)

#define UT_NAME system
#define UT_ISNS 
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::out << "omni::system::cwd = " << omni::system::cwd() << std::endl;
            omni::out << "omni::system::is_big_endian() = " << OMNI_BOOL2STR(omni::system::is_big_endian()) << std::endl;
            omni::out << "omni::system::last_error() = " << omni::system::last_error() << std::endl;
            std::cout << "omni::system::last_error_str() = " << omni::system::last_error_str() << std::endl;
            #if defined(OMNI_NON_PORTABLE)
                omni::out << "omni::system::path = " << omni::system::path() << std::endl;
                std::cout << "omni::system::processors() = " << omni::system::processors() << std::endl;
            #endif
            
            std::string err;
            for (int i = 0; i < 65535; i++) {
                err = omni::system::error_str(i);
                if (!omni::cstring::contains(err, "Unknown error")) {
                    std::cout << i << " = " << err << std::endl;
                }
            }
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SYSTEM
