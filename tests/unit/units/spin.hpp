#if defined(OMNI_UTUA) || defined(OMNI_UT_SPIN)

#define UT_ROOT_NS sync
#define UT_NAME spin
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() {
            print_info(omni::sync::spin_lock_t);
            print_info(omni::sync::spin_lock);
            print_info(omni::sync::spin_wait);
            print_info(omni::sync::safe_spin_wait);
        }
        
        void base_test()
        {
            omni::sync::thread t(&UT_CNAME::thread_fn);
            omni::sync::thread t2(&UT_CNAME::wait_fn);
            printl("starting threads");
            t.start();
            t2.start();
            printl("main thread waiting");
            m_wait.busy_wait();
            printl("main thread continuing");
            t.join();
            t2.join();
        }
        
    private:
        static omni::sync::spin_lock m_lock;
        static omni::sync::spin_wait m_wait;

        static void thread_fn(omni::sync::thread_arg_t p)
        {
            printl("in thread function, sleeping 2 seconds");
            omni::sync::sleep(2000);
            printl("signaling");
            m_wait.signal();
            printl("thread_fn return");
        }

        static void wait_fn(omni::sync::thread_arg_t p)
        {
            printl("wait function waiting");
            m_wait.busy_wait();
            printl("wait function continuing");
        }
};

omni::sync::spin_lock UT_CNAME::m_lock;
omni::sync::spin_wait UT_CNAME::m_wait;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SPIN
