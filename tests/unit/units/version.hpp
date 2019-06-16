#if defined(OMNI_UTUA) || defined(OMNI_UT_VERSION)

#define UT_NAME version
#define UT_ROOT_NS util
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::util::version v(1,2,3,4);
            omni::out << "version: " << v << std::endl;
            v = "4.3.2.1";
            omni::out << "version: " << v << std::endl;
            v = "9.1";
            omni::out << "version: " << v << std::endl;
            omni::util::version lv("5.2.3.4");
            omni::out << "version: " << lv << std::endl;
            omni::out << "creating invalid version: should fail if !OMNI_NO_THROW" << std::endl;
            try {
                lv = "1.3.g";
            } catch (std::exception& e) {
                omni::out << "error: " << e.what() << std::endl;
            }
            omni::out << "version: " << lv << std::endl;
            
            std::string sv = v;
            std::wstring wsv = v;
            std::cout << "sv = " << sv << std::endl;
            std::wcout << "wsv = " << wsv << std::endl;
            
            
            uint64_t mj = v.major_number();
            uint64_t mi = v.minor_number();
            uint64_t mb = v.build();
            uint64_t mr = v.revision();
            
            std::cout <<mj<<"."<<mi<<"."<<mb<<"."<<mr<<std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_VERSION
