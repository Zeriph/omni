#if defined(OMNI_UTUA) || defined(OMNI_UT_EXCEPTIONS)

#define UT_NAME exception
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(string_test, "tests string casting capabilities of the class");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            #if defined(OMNI_NO_THROW)
                printl("OMNI_NO_THROW is defined, exceptions not enabled");
            #else
                print_info(omni::exception);
                print_info(omni::exceptions::stopwatch_exception);
                print_info(omni::exceptions::string_exception);
                print_info(omni::exceptions::invalid_binary_format);
                print_info(omni::exceptions::invalid_binary_size);
                print_info(omni::exceptions::invalid_size);
                print_info(omni::exceptions::environment_exception);
                print_info(omni::exceptions::invalid_environment_variable);
                print_info(omni::exceptions::pipe_exception);
                print_info(omni::exceptions::clock_exception );
                print_info(omni::exceptions::invalid_delegate);
                print_info(omni::exceptions::invalid_type_cast);
                print_info(omni::exceptions::index_out_of_range);
                print_info(omni::exceptions::null_pointer_exception);
                print_info(omni::exceptions::application_exception);
                print_info(omni::exceptions::invalid_application_state);
                print_info(omni::exceptions::invalid_version);
                print_info(omni::exceptions::mutex_system_exception);
                print_info(omni::exceptions::mutex_unlock_exception);
                print_info(omni::exceptions::invalid_thread_owner);
                print_info(omni::exceptions::semaphore_system_exception);
                print_info(omni::exceptions::semaphore_release_exception);
                print_info(omni::exceptions::active_wait_exception);
                print_info(omni::exceptions::invalid_release_count);
                print_info(omni::exceptions::thread_exception);
                print_info(omni::exceptions::thread_running_exception);
                print_info(omni::exceptions::invalid_thread_state);
                print_info(omni::exceptions::invalid_thread_handle);
                print_info(omni::exceptions::invalid_thread_option);
                print_info(omni::exceptions::invalid_thread_start_type);
                print_info(omni::exceptions::threadpool_exception);
                print_info(omni::exceptions::threadpool_state_exception);
                print_info(omni::exceptions::threadpool_thread_exception);
                print_info(omni::exceptions::invalid_threadpool_size);
            #endif
        }
        
        void base_test()
        {
            #if defined(OMNI_NO_THROW)
                printl("OMNI_NO_THROW is defined, exceptions not enabled");
            #else
                UT_CNAME::ex_t(omni::exception("This is exceptional"));
                UT_CNAME::ex_t(omni::exception(std::string("This is a const char* cast to omni::exception")));
                UT_CNAME::ex_t(omni::exceptions::stopwatch_exception());
                UT_CNAME::ex_t(omni::exceptions::stopwatch_exception(10));
                UT_CNAME::ex_t(omni::exceptions::stopwatch_exception(static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::stopwatch_exception("stopwatch ex"));
                UT_CNAME::ex_t(omni::exceptions::stopwatch_exception("stopwatch ex", 10));
                UT_CNAME::ex_t(omni::exceptions::stopwatch_exception("stopwatch ex", static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::string_exception());
                UT_CNAME::ex_t(omni::exceptions::string_exception("omni::exceptions::string_exception"));
                UT_CNAME::ex_t(omni::exceptions::invalid_binary_format());
                UT_CNAME::ex_t(omni::exceptions::invalid_binary_size());
                UT_CNAME::ex_t(omni::exceptions::invalid_size());
                UT_CNAME::ex_t(omni::exceptions::environment_exception());
                UT_CNAME::ex_t(omni::exceptions::environment_exception(123456789));
                UT_CNAME::ex_t(omni::exceptions::invalid_environment_variable());
                UT_CNAME::ex_t(omni::exceptions::pipe_exception());
                UT_CNAME::ex_t(omni::exceptions::clock_exception());
                UT_CNAME::ex_t(omni::exceptions::invalid_delegate());
                UT_CNAME::ex_t(omni::exceptions::invalid_type_cast());
                UT_CNAME::ex_t(omni::exceptions::index_out_of_range());
                UT_CNAME::ex_t(omni::exceptions::index_out_of_range("omni::exceptions::index_out_of_range"));
                UT_CNAME::ex_t(omni::exceptions::index_out_of_range(std::string("omni::exceptions::index_out_of_range")));
                UT_CNAME::ex_t(omni::exceptions::null_pointer_exception());
                UT_CNAME::ex_t(omni::exceptions::application_exception());
                UT_CNAME::ex_t(omni::exceptions::application_exception(10));
                UT_CNAME::ex_t(omni::exceptions::application_exception(static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::application_exception("application exception"));
                UT_CNAME::ex_t(omni::exceptions::application_exception("app except: ", 10));
                UT_CNAME::ex_t(omni::exceptions::application_exception("app except: ", static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::invalid_application_state());
                UT_CNAME::ex_t(omni::exceptions::invalid_version());
                UT_CNAME::ex_t(omni::exceptions::mutex_system_exception());
                UT_CNAME::ex_t(omni::exceptions::mutex_system_exception(10));
                UT_CNAME::ex_t(omni::exceptions::mutex_system_exception(static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::mutex_system_exception("mutext sys ex"));
                UT_CNAME::ex_t(omni::exceptions::mutex_system_exception("mutext sys ex", 10));
                UT_CNAME::ex_t(omni::exceptions::mutex_system_exception("mutext sys ex", static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::mutex_unlock_exception());
                UT_CNAME::ex_t(omni::exceptions::invalid_thread_owner());
                UT_CNAME::ex_t(omni::exceptions::semaphore_system_exception());
                UT_CNAME::ex_t(omni::exceptions::semaphore_system_exception(10));
                UT_CNAME::ex_t(omni::exceptions::semaphore_system_exception(static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::semaphore_system_exception("sem sys ex"));
                UT_CNAME::ex_t(omni::exceptions::semaphore_system_exception("sem sys ex", 10));
                UT_CNAME::ex_t(omni::exceptions::semaphore_system_exception("sem sys ex", static_cast<long>(1000)));
                UT_CNAME::ex_t(omni::exceptions::semaphore_release_exception());
                UT_CNAME::ex_t(omni::exceptions::active_wait_exception());
                UT_CNAME::ex_t(omni::exceptions::invalid_release_count());
                UT_CNAME::ex_t(omni::exceptions::thread_exception());
                UT_CNAME::ex_t(omni::exceptions::thread_exception(static_cast<int>(10)));
                UT_CNAME::ex_t(omni::exceptions::thread_exception(static_cast<std::size_t>(1000)));
                UT_CNAME::ex_t(omni::exceptions::thread_exception(std::string("thread ex")));
                UT_CNAME::ex_t(omni::exceptions::thread_exception("thread ex"));
                UT_CNAME::ex_t(omni::exceptions::thread_exception(std::string("thread ex"), static_cast<int>(10)));
                UT_CNAME::ex_t(omni::exceptions::thread_exception(std::string("thread ex"), static_cast<std::size_t>(1000)));
                UT_CNAME::ex_t(omni::exceptions::thread_exception("thread ex", static_cast<int>(10)));
                UT_CNAME::ex_t(omni::exceptions::thread_exception("thread ex", static_cast<std::size_t>(1000)));
                UT_CNAME::ex_t(omni::exceptions::thread_running_exception());
                UT_CNAME::ex_t(omni::exceptions::invalid_thread_state());
                UT_CNAME::ex_t(omni::exceptions::invalid_thread_handle());
                UT_CNAME::ex_t(omni::exceptions::invalid_thread_option());
                UT_CNAME::ex_t(omni::exceptions::invalid_thread_option(100));
                UT_CNAME::ex_t(omni::exceptions::invalid_thread_start_type());
                UT_CNAME::ex_t(omni::exceptions::threadpool_exception());
                UT_CNAME::ex_t(omni::exceptions::threadpool_exception(std::string("threadpool ex")));
                UT_CNAME::ex_t(omni::exceptions::threadpool_exception("threadpool ex"));
                UT_CNAME::ex_t(omni::exceptions::threadpool_state_exception());
                UT_CNAME::ex_t(omni::exceptions::threadpool_thread_exception());
                UT_CNAME::ex_t(omni::exceptions::invalid_threadpool_size());
            #endif
        }
        
        void string_test()
        {
            #if defined(OMNI_NO_THROW)
                printl("OMNI_NO_THROW is defined, exceptions not enabled");
            #else
                omni::exception e("this is a test");
                std::string s = e;
                std::wstring w = e;
                std::wcout << w << std::endl;
                std::cout << s << std::endl;
                
                std::cout << static_cast<std::string>(e) << std::endl;
                std::wcout << static_cast<std::wstring>(e) << std::endl;
                
                try {
                    throw omni::exceptions::thread_exception();
                } catch (omni::exceptions::thread_exception e) {
                    std::cout << "e = " << e << std::endl;
                }
            #endif
        }

    private:    
        static void ex_t_std(const omni::exception& ex)
        {
            #if defined(OMNI_NO_THROW)
                printl("OMNI_NO_THROW is defined, exceptions not enabled");
            #else
                try { throw ex; }
                catch (std::exception& e) {
                    omni::out << "caught std::exception: " << e.what() << std::endl;
                }
            #endif
        }

        static void ex_t_omni(const omni::exception& ex)
        {
            #if defined(OMNI_NO_THROW)
                printl("OMNI_NO_THROW is defined, exceptions not enabled");
            #else
                try { throw ex; }
                catch (omni::exception& e) {
                    omni::out << "caught omni::exception: " << e << std::endl;
                }
            #endif
        }

        static void ex_t(const omni::exception& ex)
        {
            #if defined(OMNI_NO_THROW)
                printl("OMNI_NO_THROW is defined, exceptions not enabled");
            #else
                printl("Testing exception (std then omni)");
                ex_t_std(ex);
                ex_t_omni(ex);
            #endif
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_EXCEPTIONS
