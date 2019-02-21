#if defined(OMNI_UTUA) || defined(OMNI_UT_APPLICATION)

#define UT_NAME application
#define UT_ISNS true
#include <utdefs/unit_test.hpp>
#include <omni/sync/basic_thread_allocate>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            // add other tests here
            M_LIST_ADD(app_exit, "Tests the application exit delegate");
            M_LIST_ADD(get_signal_code, "Tests the get signal code");
            M_LIST_ADD(ignore_signal_code, "Tests the ignore signal functionality");
            M_LIST_ADD(set_sig_code_and_stop, "Tests the set signal code and the stop functionality");
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
        }

        void ignore_signal_code()
        {
            omni::application::signal_handler::attach(&UT_CNAME::application_getsigcode);
            omni::application::signal_handler::ignore(true);
            printl("Set signal handler and ignore_signal_request to true");
            back_thread_igsig();
        }

        void set_sig_code_and_stop()
        {
            omni::application::set_return_code(42);
            printl("Program will exit with signal 0, check program return with 'echo $?' (should be 42)");
            omni::application::stop();
        }
    
    private:
        static void application_getsigcode(int sig)
        {
            printv("signal received: ", sig);
        }

        static void back_thread_igsig()
        {
            omni::stopwatch sw;
            printl("Background thread waiting ~2s then resetting");
            sw.start();
            while (sw.elapsed_ms() < 2000) {
                omni::sync::sleep(1);
            }
            omni::application::signal_handler::ignore(false);
            printl("Reset ignore signal handler");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_APPLICATION
