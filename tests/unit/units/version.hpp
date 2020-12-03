#if defined(OMNI_UTUA) || defined(OMNI_UT_VERSION)

#define UT_NAME version
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            print_info(omni::version);
            print_info(omni::net::version);
        }
        
        void base_test()
        {
            std_test();
            net_test();
        }

        void net_test()
        {
            omni::out << "Testing omni::net::version" << std::endl;

            omni::net::version v(1,2,3,4);
            omni::out << "version: " << v << " (should be 1.2.3.4)" << std::endl;
            omni::out << "version: " << v.to_string_t(0) << " (should be '')" << std::endl;
            omni::out << "version: " << v.to_string_t(1) << " (should be 1)" << std::endl;
            omni::out << "version: " << v.to_string_t(2) << " (should be 1.2)" << std::endl;
            omni::out << "version: " << v.to_string_t(3) << " (should be 1.2.3)" << std::endl;
            omni::out << "version: " << v.to_string_t(4) << " (should be 1.2.3.4)" << std::endl;
            omni::out << "hash code: " << v.hash_code() << std::endl;
            v = "4.3.2.1";
            omni::out << "version: " << v << " (should be 4.3.2.1)" << std::endl;
            v = "9.1";
            omni::out << "version: " << v << " (should be 9.1)" << std::endl;
            omni::net::version lv("5.2.3.4");
            omni::out << "version: " << lv << " (should be 5.2.3.4)" << std::endl;
            omni::out << "creating invalid version: should fail if !OMNI_NO_THROW" << std::endl;
            try {
                lv = "1.3.g";
            } catch (std::exception& e) {
                omni::out << "error: " << e.what() << std::endl;
            }
            try {
                lv = omni::net::version(-1);
            } catch (std::exception& e) {
                omni::out << "error: " << e.what() << std::endl;
            }
            try {
                lv = omni::net::version(1, -1);
            } catch (std::exception& e) {
                omni::out << "error: " << e.what() << std::endl;
            }
            try {
                lv = omni::net::version(1, 1, -1);
            } catch (std::exception& e) {
                omni::out << "error: " << e.what() << std::endl;
            }
            try {
                lv = omni::net::version(1, 1, 1, -1);
            } catch (std::exception& e) {
                omni::out << "error: " << e.what() << std::endl;
            }
            omni::out << "version: " << lv << std::endl;
            
            std::string sv = v;
            std::wstring wsv = v;
            std::cout << "sv = " << sv << std::endl;
            std::wcout << "wsv = " << wsv << std::endl;
            
            
            int32_t mj = v.major_number();
            int32_t mi = v.minor_number();
            int32_t mb = v.build();
            int32_t mr = v.revision();
            int32_t mmr = v.major_revision();
            int32_t mnr = v.minor_revision();
            
            std::cout << mj << "." << mi << "." << mb << "." << mr << " (" << mmr << "." << mnr << ")" << std::endl;

            omni::out << std::endl;
        }

        void std_test()
        {
            omni::out << "Testing omni::version" << std::endl;
            omni::version v(1,2,3,4);
            omni::out << "version: " << v << " (should be 1.2.3.4)" << std::endl;
            omni::out << "version: " << v.to_string_t(0) << " (should be '')" << std::endl;
            omni::out << "version: " << v.to_string_t(1) << " (should be 1)" << std::endl;
            omni::out << "version: " << v.to_string_t(2) << " (should be 1.2)" << std::endl;
            omni::out << "version: " << v.to_string_t(3) << " (should be 1.2.3)" << std::endl;
            omni::out << "version: " << v.to_string_t(4) << " (should be 1.2.3.4)" << std::endl;
            omni::out << "hash code: " << v.hash_code() << std::endl;
            v = "4.3.2.1";
            omni::out << "version: " << v << " (should be 4.3.2.1)" << std::endl;
            v = "9.1";
            omni::out << "version: " << v << " (should be 9.1.0.0)" << std::endl;
            omni::version lv("5.2.3.4");
            omni::out << "version: " << lv << " (should be 5.2.3.4)" << std::endl;
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
            
            std::cout << mj << "." << mi << "." << mb << "." << mr << std::endl;

            omni::out << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_VERSION
