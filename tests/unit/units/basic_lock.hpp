#if defined(OMNI_UTUA) || defined(OMNI_UT_LOCK)

#define UT_ROOT_NS sync
#define UT_NAME basic_lock
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(auto_lock_test, "tests the auto_lock capabilities");
            M_LIST_ADD(lock_timeout_test, "tests the timeout lock capabilities");
            M_LIST_ADD(trylock_test, "tests the trylock capabilities");
            M_LIST_ADD(error_test1, "tests the error condition of unlocking a non-locked mutex");
            M_LIST_ADD(error_test2, "tests the error condition of unlocking a mutex from the non-owning thread");
            M_LIST_ADD(error_test3, "tests the error condition of destroying a mutex that is in a locked state");
            M_LIST_ADD(recursive_test, "tests the recursive functionality");
            M_LIST_ADD(system_test, "tests the system mutex functionality");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            UT_INFO_TEST();
            print_sizeof(omni::sync::mutex_t);
            print_sizeof(OMNI_MUTEX_T);
        }
        
        void base_test()
        {
            lock_params lp1, lp2;
            lp1.lt = lp2.lt = lt_lock;
            lp1.idx = 1; lp2.idx = 2;
            omni::sync::thread t1(&UT_CNAME::dmy_thread_fn, omni::sync::thread_option::AUTO_JOIN, true);
            omni::sync::thread t2(&UT_CNAME::dmy_thread_fn, omni::sync::thread_option::AUTO_JOIN, true);
            // omni::sync::basic_lock cmtx = m_mtx; // compile error (operator= private and not defined)
            omni::sync::basic_lock amtx;
            // omni::sync::basic_lock acmtx(amtx); // compile error (copy constructor private and not defined)
            //printv("m_mtx.handle: ", &m_mtx.handle());
            //printv("amtx.handle: ", &amtx.handle());
            if (amtx == m_mtx) { printl("logic error"); }
            else { printl("pass: amtx != m_mtx"); }
            if (amtx != m_mtx) { printl("pass: amtx != m_mtx"); }
            else { printl("logic error"); }
            printl("Starting threads (1 then 2)");
            t1.start(&lp1);
            t2.start(&lp2);
            printl("Main thread trying to get lock...");
            m_mtx.lock();
            printl("Main thread got lock, sleeping for 5 seconds");
            omni::sync::sleep(5000);
            printl("Main thread unlocking");
            m_mtx.unlock();
            printl("Main thread returning");
        }
        
        void auto_lock_test()
        {
            printl("creating and starting 2 threads");
            omni::sync::thread t1(&UT_CNAME::auto_lock_fn, omni::sync::thread_option::AUTO_JOIN, true);
            omni::sync::thread t2(&UT_CNAME::auto_lock_fn, omni::sync::thread_option::AUTO_JOIN, true);
            t1.start();
            t2.start();
            printl("threads started, locking through scoped auto lock");
            { // start scope
                /* Even though we are compiling as C++, the compiler still 'might' put this variable
                at the top of the stack, so we can't guarantee the "auto-scope"'ed-ness of the type
                without the use of "scope" brackets; hence the scope brackets */
                omni::sync::auto_lock<omni::sync::basic_lock> amx(&m_mtx);
            } // end scope
            printl("other side of scoped lock");
        }
        
        void lock_timeout_test()
        {
            bool gotLock = false;
            lock_params lp1, lp2;
            lp1.lt = lp2.lt = lt_lock_timeout;
            lp1.idx = 1;
            lp2.idx = 2;
            omni::sync::thread t1(&UT_CNAME::dmy_thread_fn, omni::sync::thread_option::AUTO_JOIN, true);
            omni::sync::thread t2(&UT_CNAME::dmy_thread_fn, omni::sync::thread_option::AUTO_JOIN, true);
            printl("Starting threads (1 then 2)");
            t1.start(&lp1);
            t2.start(&lp2);
            printl("Main thread trying to get lock...");
            omni::stopwatch sw;
            sw.start();
            if (m_mtx.lock(3000)) {
                gotLock = true;
                printl("Main thread got lock, sleeping for 5 seconds");
                omni::sync::sleep(5000);
            } else {
                printv("Main thread could not get lock after timeout, elapsed ms = ", sw.elapsed_ms());
            }
            sw.stop();
            if (gotLock) {
                printl("Main thread unlocking");
                m_mtx.unlock();
            }
            printl("Main thread returning");
        }
        
        void trylock_test()
        {
            bool gotLock = false;
            lock_params lp1, lp2;
            lp1.lt = lp2.lt = lt_trylock;
            lp1.idx = 1;
            lp2.idx = 2;
            omni::sync::thread t1(&UT_CNAME::dmy_thread_fn, omni::sync::thread_option::AUTO_JOIN, true);
            omni::sync::thread t2(&UT_CNAME::dmy_thread_fn, omni::sync::thread_option::AUTO_JOIN, true);
            printl("Starting threads (1 then 2)");
            t1.start(&lp1);
            t2.start(&lp2);
            printl("Main thread will sleep for 1 second to test full trylock");
            omni::sync::sleep(1000);
            if (m_mtx.trylock()) {
                printl("Main thread got lock, unlocking");
                m_mtx.unlock();
            } else {
                printl("Main thread could not get lock");
            }
            printl("Main thread will sleep for 6 seconds to test full trylock");
            omni::sync::sleep(6000);
            printl("Main thread trying to get lock...");
            if (m_mtx.trylock()) {
                gotLock = true;
                printl("Main thread got lock, sleeping for 5 seconds");
                omni::sync::sleep(5000);
            } else {
                printl("Main thread could not get lock");
            }
            if (gotLock) {
                printl("Main thread unlocking");
                m_mtx.unlock();
            }
            printl("Main thread returning");
        }

        void recursive_test()
        {
            printl("creating and starting 2 threads");
            omni::sync::thread t1(&UT_CNAME::recursive_test_fn, omni::sync::thread_option::AUTO_JOIN, true);
            omni::sync::thread t2(&UT_CNAME::recursive_test_fn, omni::sync::thread_option::AUTO_JOIN, true);
            t1.start();
            t2.start();
            printl("locking once");
            m_mtx.lock();
            printl("locking twice");
            m_mtx.lock();
            printl("should get here, now unlocking (2x since 2 locks)");
            m_mtx.unlock();
            m_mtx.unlock();
            printl("leaving");
        }
        
        void system_test()
        {
            printl("testing the mutex_t typedef");
            omni::sync::mutex_init(m_mtx_t);
            bool gotLock = false;
            lock_params lp1, lp2, lp3;
            lp1.lt = lt_syslock;
            lp2.lt = lt_systrylock;
            lp3.lt = lt_sysautolock;
            lp1.idx = 1;
            lp2.idx = 2;
            lp3.idx = 3;
            omni::sync::thread t1(&UT_CNAME::dmy_thread_fn);
            omni::sync::thread t2(&UT_CNAME::dmy_thread_fn);
            omni::sync::thread t3(&UT_CNAME::dmy_thread_fn);
            // basic test
            printl("starting thread 1");
            t1.start(&lp1);
            omni::sync::mutex_lock(m_mtx_t);
            printl("main thread got lock, unlocking and waiting for thread 1");
            omni::sync::mutex_unlock(m_mtx_t);
            t1.join();
            // other sys_test
            t2.start(&lp2);
            printl("Main thread will sleep for 1 second to test full trylock");
            omni::sync::sleep(1000);
            if (omni::sync::mutex_trylock(m_mtx_t)) {
                printl("main thread got lock from trylock, unlocking"); // pass condition
                omni::sync::mutex_unlock(m_mtx_t);
            } else {
                printl("main thread could not get lock");
            }
            printl("main thread will try lock timeout");
            if (omni::sync::mutex_lock(m_mtx_t, 1000)) {
                printl("main thread got lock from lock timeout, unlocking"); // pass condition
                omni::sync::mutex_unlock(m_mtx_t);
            } else {
                printl("main thread could not get lock after 1s");
            }
            omni::sync::sleep(6000);
            printl("Main thread trying to get lock...");
            omni::sync::mutex_lock(m_mtx_t);
            printl("Main thread got lock, unlocking and waiting on thread 2");
            omni::sync::mutex_unlock(m_mtx_t);
            t2.join();
            
            // auto-lock
            printl("Starting thread 3 and testing the auto_mutex_t");
            t3.start(&lp3);
            { // start scope
                omni::sync::auto_lock<omni::sync::mutex_t> amx(&m_mtx_t);
            } // end scope
            printl("other side of scoped lock");
            
            printl("destroying mutex");
            omni::sync::mutex_destroy(m_mtx_t);
            
            // macro tests
            printl("testing the mutex_t macro");
            OMNI_MUTEX_T mtx_t;
            printl("testing against mutex_init");
            omni::sync::mutex_init(mtx_t);
            printl("testing against mutex_lock");
            omni::sync::mutex_lock(mtx_t);
            printl("testing against mutex_unlock");
            omni::sync::mutex_unlock(mtx_t);
            printl("testing against mutex_lock(timeout)");
            if (omni::sync::mutex_lock(mtx_t, 1000)) {
                printl("testing against mutex_unlock");
                omni::sync::mutex_unlock(mtx_t);
            } else {
                printl("did not get lock");
            }
            printl("testing against mutex_trylock");
            if (omni::sync::mutex_trylock(mtx_t)) {
                printl("testing against mutex_unlock");
                omni::sync::mutex_unlock(mtx_t);
            } else {
                printl("did not get lock");
            }
            printl("testing against mutex_destroy");
            omni::sync::mutex_destroy(mtx_t);
        }
        
        void error_test1()
        {
            omni::sync::thread t1(&UT_CNAME::error_test_fn1);
            omni::sync::thread t2(&UT_CNAME::error_test_fn1);
            printl("calling unlock on non-locked mutex -> system will now be in undefined state");
            m_mtx.unlock();
            printl("starting threads");
            t1.start();
            t2.start();
            t1.join();
            t2.join();
            printl("Main thread returning");
        }
        
        void error_test2()
        {
            omni::sync::thread t1(&UT_CNAME::error_test_fn2);
            omni::sync::thread t2(&UT_CNAME::error_test_fn2);
            printl("starting thread 1, sleeping 100ms");
            t1.start();
            omni::sync::sleep(100);
            printl("calling unlock from non-owning thread -> system will now be in undefined state");
            m_mtx.unlock();
            printl("starting thread 2, sleeping 100ms");
            t2.start();
            omni::sync::sleep(100);
            printl("calling unlock from non-owning thread -> system will now be in undefined state");
            m_mtx.unlock();
            t1.join();
            t2.join();
            printl("Main thread returning");
        }

        void error_test3()
        {
            omni::sync::basic_lock amtx(true);
            printl("leaving function with mutex in locked state -> system will now be in undefined state");
        }
        
    private:
        typedef enum {
            lt_lock = 0,
            lt_lock_timeout,
            lt_trylock,
            lt_syslock,
            lt_systrylock,
            lt_sysautolock
        } lock_type;

        typedef struct {
            lock_type lt;
            unsigned int idx;
        } lock_params;

        static omni::sync::basic_lock m_mtx;
        static omni::sync::mutex_t m_mtx_t;

        static void auto_lock_fn(omni::sync::thread_arg_t param)
        {
            omni::sync::auto_lock<omni::sync::basic_lock> amx(&m_mtx);
            printl(omni::sync::thread_id() << " got lock, sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl(omni::sync::thread_id() << " leaving, should auto-unlock");
        }
        
        static void error_test_fn1(omni::sync::thread_arg_t param)
        {
            printl(omni::sync::thread_id() << " waiting for lock");
            m_mtx.lock();
            printl(omni::sync::thread_id() << " got lock, sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl(omni::sync::thread_id() << " unlocking and leaving");
            m_mtx.unlock();
        }
        
        static void error_test_fn2(omni::sync::thread_arg_t param)
        {
            printl(omni::sync::thread_id() << " waiting for lock");
            m_mtx.lock();
            printl(omni::sync::thread_id() << " got lock, sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl(omni::sync::thread_id() << " leaving (still locked)");
        }
        
        static void recursive_test_fn(omni::sync::thread_arg_t param)
        {
            printl(omni::sync::thread_id() << " waiting for lock");
            m_mtx.lock();
            printl(omni::sync::thread_id() << " locking again");
            m_mtx.lock();
            printl(omni::sync::thread_id() << " got lock, sleeping 5 seconds");
            omni::sync::sleep(5000);
            printl(omni::sync::thread_id() << " unlocking 2x (since 2 locks) and leaving");
            m_mtx.unlock();
            m_mtx.unlock();
        }
        
        static void dmy_thread_fn(omni::sync::thread_arg_t param)
        {
            lock_params prms = *(static_cast<lock_params*>(param));
            unsigned int idx = prms.idx;
            printl("Thread " << idx << " trying to get lock...(type " << (int)prms.lt << ")");
            bool gotLock = false;
            switch (prms.lt) {
                case lt_lock:
                    {
                        m_mtx.lock();
                        gotLock = true;
                        printl("Thread " << idx << " got lock, sleeping for 5 seconds");
                        omni::sync::sleep(5000);
                    }
                    break;
                case lt_trylock:
                    {
                        if (m_mtx.trylock()) {
                            gotLock = true;
                            printl("Thread " << idx << " got lock, sleeping for 5 seconds");
                            omni::sync::sleep(5000);
                        } else {
                            printl("Thread " << idx << " did not get lock");
                        }
                    }
                    break;
                case lt_lock_timeout:
                    {
                        omni::stopwatch sw;
                        sw.start();
                        if (m_mtx.lock(3000)) {
                            gotLock = true;
                            printl("Thread " << idx << " got lock, sleeping for 5 seconds");
                            omni::sync::sleep(5000);
                        } else {
                            printl("Thread " << idx << " could not get lock after timeout, elapsed ms = " << sw.elapsed_ms());
                        }
                        sw.stop();
                    }
                    break;
                case lt_syslock:
                    {
                        omni::sync::mutex_lock(m_mtx_t);
                        printl("Thread " << idx << " got lock, sleeping for 5 seconds");
                        omni::sync::sleep(5000);
                        printl("Thread " << idx << " unlocking and leaving");
                        omni::sync::mutex_unlock(m_mtx_t);
                    }
                    break;
                case lt_systrylock:
                    {
                        if (omni::sync::mutex_trylock(m_mtx_t)) {
                            printl("Thread " << idx << " got lock from trylock, sleeping for 5 seconds");
                            omni::sync::sleep(5000);
                            printl("Thread " << idx << " unlocking and leaving");
                            omni::sync::mutex_unlock(m_mtx_t);
                        } else {
                            printl("Thread " << idx << " did not get lock");
                        }
                    }
                    break;
                case lt_sysautolock:
                    {
                        omni::sync::auto_lock<omni::sync::mutex_t> amx(&m_mtx_t);
                        printl("Thread " << idx << " got lock, sleeping for 5 seconds");
                        omni::sync::sleep(5000);
                        printl("Thread " << idx << " leaving, should auto-unlock");
                    }
                    break;
                default: break;
            }
            if (gotLock) {
                printl("Thread " << idx << " unlocking");
                m_mtx.unlock();
            }
            printl("Thread " << idx << " returning");
        }

};
omni::sync::basic_lock UT_CNAME::m_mtx;
omni::sync::mutex_t UT_CNAME::m_mtx_t;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_LOCK

