#if defined(OMNI_UTUA) || defined(OMNI_UT_CONDITIONAL)

#define UT_ROOT_NS sync
#define UT_NAME conditional
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(broadcast_test, "tests the broadcast functionality of a conditional");
            M_LIST_ADD(timeout_test, "tests the timeout functionality of a conditional");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            int i;
            omni_seq_t<omni::sync::thread*> threads;
            printl("starting threads");
            for (i = 0; i < 5; ++i) {
                threads.push_back(new omni::sync::thread(&UT_CNAME::wait_fn));
                threads.back()->start();
            }
            for (i = 0; i < 5; ++i) {
                threads.push_back(new omni::sync::thread(&UT_CNAME::sleep_fn));
                threads.back()->start();
            }
            printl("main thread sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl("main thread signalling once");
            m_wt.signal();
            for (i = 0; i < 10; ++i) {
                printv("main thread waiting on tid ", threads.back()->id());
                threads.back()->join();
                delete threads.back();
                threads.pop_back();
            }
            printl("main thread continuing");
        }
        
        void broadcast_test()
        {
            int i;
            omni_seq_t<omni::sync::thread*> threads;
            printl("starting threads");
            for (i = 0; i < 5; ++i) {
                threads.push_back(new omni::sync::thread(&UT_CNAME::wait_fn));
                threads.back()->start();
            }
            for (i = 0; i < 5; ++i) {
                threads.push_back(new omni::sync::thread(&UT_CNAME::sleep_fn));
                threads.back()->start();
            }
            printl("main thread sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl("main thread broadcast");
            m_wt.broadcast();
            for (i = 0; i < 10; ++i) {
                printv("main thread waiting on tid ", threads.back()->id());
                threads.back()->join();
                delete threads.back();
                threads.pop_back();
            }
            printl("main thread continuing");
        }

        void timeout_test()
        {
            int i;
            omni_seq_t<omni::sync::thread*> threads;
            printl("starting threads");
            for (i = 0; i < 5; ++i) {
                threads.push_back(new omni::sync::thread(&UT_CNAME::wait_to_fn));
                threads.back()->start();
            }
            for (i = 0; i < 5; ++i) {
                threads.push_back(new omni::sync::thread(&UT_CNAME::sleep_fn));
                threads.back()->start();
            }
            printl("main thread sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl("main thread signalling once");
            m_wt.signal();
            for (i = 0; i < 10; ++i) {
                printv("main thread waiting on tid ", threads.back()->id());
                threads.back()->join();
                delete threads.back();
                threads.pop_back();
            }
            printl("main thread continuing");
        }
        
    private:
        static omni::sync::conditional m_wt;

        static void wait_fn(omni::sync::thread_arg_t p)
        {
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("wait function waiting: ", tid);
            m_wt.wait();
            printv("wait function continuing: ", tid);
        }

        static void wait_to_fn(omni::sync::thread_arg_t p)
        {
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("wait function waiting for 3 seconds: ", tid);
            m_wt.wait(3000);
            printv("wait function continuing: ", tid);
        }
        
        static void sleep_fn(omni::sync::thread_arg_t p)
        {
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("wait function sleeping 6 seconds: ", tid);
            omni::sync::sleep(6000);
            printv("wait function 6s waiting: ", tid);
            m_wt.wait();
            printv("wait function 6s continuing: ", tid);
        }
};

omni::sync::conditional UT_CNAME::m_wt;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_CONDITIONAL
