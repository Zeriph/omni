#if defined(OMNI_UTUA) || defined(OMNI_UT_SEMAPHORE)

#include <list>

#define UT_ROOT_NS sync
#define UT_NAME semaphore
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            this->m_sem = new omni::sync::semaphore(5);
            M_LIST_ADD(releasecnt_test, "tests the release(count) semaphore");
            M_LIST_ADD(wait_to_test, "tests the wait_timeout semaphore");
        }
        
        UT_CLASS_DTOR() { delete this->m_sem; }
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            this->create_threads(10);
            printl("main thread waiting for semaphore");
            this->m_sem->wait();
            printl("main thread enters semaphore");
            printv("m_sem is ", (this->m_sem->locked()>0?"locked":"unlocked"));
            omni::sync::sleep(3000);
            printl("main thread releasing semaphore");
            this->m_sem->release();
            this->destroy_threads();
            printv("m_sem is ", (this->m_sem->locked()>0?"locked":"unlocked"));
            printl("main thread returning");
        }
        
        void thread_func(omni::sync::thread_arg_t p)
        {
            unsigned int tid = *(static_cast<int*>(p));
            omni::stopwatch sw;
            printl("tid# "<<tid<<" waiting...");
            sw.start();
            this->m_sem->wait();
            sw.stop();
            printl("tid# "<<tid<<" locked after "<<sw.elapsed_ms()<<"ms, sleeping 5s");
            omni::sync::sleep(5000);
            printl("tid# "<<tid<<" unlocking and leaving");
            this->m_sem->release();
        }

        void create_threads(unsigned int cnt)
        {
            printl("entering thread creation loop");
            for (unsigned int i = 1; i <= cnt; i++) {
                this->m_t.push_back(new omni::sync::thread(omni::sync::parameterized_thread_start::bind<UT_CNAME, &UT_CNAME::thread_func>(this)));
                this->m_t.back()->start(&i);
            }
        }

        void destroy_threads()
        {
            printl("destroying threads");
            std::list<omni::sync::thread*>::iterator itr = this->m_t.begin();
            for (; itr != this->m_t.end(); itr++) {
                (*itr)->join();
                delete (*itr);
            }
        }
        
        void releasecnt_test()
        {
            this->create_threads(10);
            omni::sync::sleep(2000);
            printl("main thread releasing 5 semaphore locks");
            this->m_sem->release(5);
            this->destroy_threads();
            printl("main thread returning");
            /* should get exception in thread_func on m_sem->release of invalid count since
               we've already decremented the counter by 5 threads 'manually' + each thread that
               had the semaphore before (5), so 5+5=10 (number of threads in list); so when
               we try to call m_sem->release again, it's like saying char x[10]; x[10] .. array
               out of bounds. */
        }

        void wait_to_test()
        {
            this->create_threads(10);
            omni::sync::sleep(1000);
            printl("main thread waiting 1000 ms for semaphore");
            omni::stopwatch sw;
            sw.start();
            bool gotwait = m_sem->wait(1000);
            sw.stop();
            if (gotwait) {
                printl("main thread enters semaphore");
                omni::sync::sleep(3000);
                printl("main thread releasing semaphore");
                this->m_sem->release();
            } else {
                printl("main thread failed wait after " << sw.elapsed_ms() << " ms");
            }
            this->destroy_threads();
            printl("main thread returning");
        }
        
    private:
        omni::sync::semaphore *m_sem;
        std::list<omni::sync::thread*> m_t;
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SEMAPHORE
