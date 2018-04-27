#if defined(OMNI_UTUA) || defined(OMNI_UT_APPLICATION)

#define UT_NAME application
#define UT_ISNS true
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            // add other tests here
            M_LIST_ADD(app_exit, "Tests the application exit delegate");
            M_LIST_ADD(get_signal_code, "Tests the get signal code");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            this->info_test();
            omni::out << "omni::application::bit_width = " << omni::application::bit_width() << std::endl;
        }
        
        void app_exit()
        {
            printl("If the application ends before you press CTRL+C, this test fails");
        }

        void get_signal_code()
        {
            omni::application::signal_handler::attach(&UT_CNAME::application_getsigcode);
            //omni::application::signal_handler::ignore(true);
            //printl("Set signal handler and omni::application::ignore_signal_request(true);");
        }
    
    private:
        static void application_getsigcode(int sig)
        {
            printv("signal recieved: ", sig);
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_APPLICATION
