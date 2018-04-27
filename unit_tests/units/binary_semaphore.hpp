#if defined(OMNI_UTUA) || defined(OMNI_UT_BINARY_SEMAPHORE)

#define UT_ROOT_NS sync
#define UT_NAME binary_semaphore
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(trywait_test, "tests the trywait capability of the binary semaphore");
            M_LIST_ADD(recursive_test, "tests the recursive functionality");
            M_LIST_ADD(error_test, "tests explicit error functionality");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::sync::thread t1(&UT_CNAME::thread_func);
            omni::sync::thread t2(&UT_CNAME::thread_func);
            t1.start();
            t2.start();
            m_sem.lock();
            m_sem.unlock();
            t1.join();
            t2.join();
        }
        
        void trywait_test()
        {
            omni::sync::thread t(&UT_CNAME::trywait_thread);
            t.start();
            printl("grabbing bin_sem on main");
            if (m_sem.trylock()) {
                printl("lock acquired on main");
                omni::sync::sleep(1000);
                printl("releasing lock on main");
                m_sem.unlock();
            } else {
                printl("lock not acquired on main");
            }
            t.join();
        }

        void recursive_test()
        {
            printl("locking once");
            m_sem.lock();
            printl("locking twice (will have to CTRL+C)");
            m_sem.lock();
            printl("should not get here; now unlocking (2x since 2 locks)");
            m_sem.unlock();
            m_sem.unlock();
        }

        void error_test()
        {
            omni::sync::thread t1(&UT_CNAME::error_test_fn);
            omni::sync::thread t2(&UT_CNAME::error_test_fn);
            t1.start();
            t2.start();
            omni::sync::sleep(100);
            printl("Calling unlock...should error");
            m_sem.unlock();
            t1.join();
            t2.join();
            m_sem.unlock();
            printl("Main thread returning");
        }
        
    private:
        static omni::sync::binary_semaphore m_sem;
        
        static void thread_func(omni::sync::thread_arg_t p)
        {
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("grabbing bin_sem on tid# ", tid);
            m_sem.lock();
            printv("sleep 5 seconds on tid# ", tid);
            omni::sync::sleep(5000);
            printv("releasing bin_sem on tid#", tid);
            m_sem.unlock();
        }

        static void error_test_fn(omni::sync::thread_arg_t param)
        {
            std::cout << omni::sync::thread_id() << " waiting for lock" << std::endl;
            m_sem.lock();
            std::cout << omni::sync::thread_id() << " got lock, sleeping 5 seconds" << std::endl;
            omni::sync::sleep(5000);
            std::cout << omni::sync::thread_id() << " leaving" << std::endl;
        }

        static void trywait_thread(omni::sync::thread_arg_t p)
        {
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("grabbing bin_sem on tid# ", tid);
            if (m_sem.trylock()) {
                printv("lock acquired on tid# ", tid);
                omni::sync::sleep(1000);
                printv("releasing lock on tid# ", tid);
                m_sem.unlock();
            } else {
                printv("lock not acquired on tid# ", tid);
            }
        }
};

omni::sync::binary_semaphore UT_CNAME::m_sem;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_BINARY_SEMAPHORE
