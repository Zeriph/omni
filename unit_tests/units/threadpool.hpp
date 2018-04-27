#if defined(OMNI_UTUA) || defined(OMNI_UT_THREADPOOL)

#define UT_ROOT_NS sync
#define UT_NAME threadpool
#include <utdefs/unit_test.hpp>

#define UT_TPOOL_MAX 80

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(set_max_test, "tests the set_max_threads function of the threadpool");
            M_LIST_ADD(set_min_test, "tests the set_min_threads function of the threadpool");
            UT_CNAME::m_lock.lock();
            UT_CNAME::m_lock.unlock();
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::sync::threadpool tp; // 5, 25
            printl("queuing " << UT_TPOOL_MAX << " threads");
            for (int i = 0; i < UT_TPOOL_MAX; ++i) { tp.queue(&UT_CNAME::thread_test); }
            printl("queue size = " << tp.queue_size() << ", should be " << (UT_TPOOL_MAX - tp.max_threads()));
            printl("active " << tp.active_threads() << " calling wait_active");
            tp.wait_active_queue();
            
            printv("max = ", UT_CNAME::m_max);
            printv("count = ", UT_CNAME::m_val);
            
            printl("leaving base");
        }
        
        void set_max_test()
        {
            omni::sync::threadpool tp; // 5, 25
            printl("queuing " << UT_TPOOL_MAX << " threads");
            for (int i = 0; i < (UT_TPOOL_MAX*2); ++i) { tp.queue(&UT_CNAME::thread_test); }
            printl("queue size = " << tp.queue_size() << ", should be " << (UT_TPOOL_MAX - tp.max_threads()));
            tp.set_max_threads((UT_TPOOL_MAX*2));
            printl("queue size = " << tp.queue_size() << ", should be " << ((UT_TPOOL_MAX*2) - tp.max_threads()));
            tp.wait_active_queue();
            
            printv("max = ", UT_CNAME::m_max);
            printv("count = ", UT_CNAME::m_val);
            
            printl("leaving base");
        }

        void set_min_test()
        {
            omni::sync::threadpool tp; // 5, 25
            printl("queuing " << UT_TPOOL_MAX << " threads");
            for (int i = 0; i < UT_TPOOL_MAX; i++) { tp.queue(&UT_CNAME::thread_test); }
            printl("queue size = " << tp.queue_size() << ", should be " << (UT_TPOOL_MAX - tp.max_threads()));
            tp.set_min_threads(2);
            printl("queue size = " << tp.queue_size() << ", should be " << (UT_TPOOL_MAX - tp.max_threads()));
            tp.wait_active_queue();
            
            printv("max = ", UT_CNAME::m_max);
            printv("count = ", UT_CNAME::m_val);
            
            printl("leaving base");
        }

    private:
        static int m_val;
        static int m_max;
        static omni::sync::basic_lock m_lock;
    
        static void do_inc()
        {
            UT_CNAME::m_lock.lock();
            ++UT_CNAME::m_val;
            ++UT_CNAME::m_max;
            printv("count = ", UT_CNAME::m_val);
            UT_CNAME::m_lock.unlock();
        }
        
        static void do_dec()
        {
            UT_CNAME::m_lock.lock();
            --UT_CNAME::m_val;
            printv("count = ", UT_CNAME::m_val);
            UT_CNAME::m_lock.unlock();
        }
    
        static void thread_test(omni::sync::thread_arg_t p)
        {
            printv("in thread with id of ", omni::sync::thread_id());
            UT_CNAME::do_inc();
            omni::sync::sleep(10000);
            UT_CNAME::do_dec();
            printv("leaving thread id of ", omni::sync::thread_id());
        }
};

omni::sync::basic_lock UT_CNAME::m_lock;
int UT_CNAME::m_val;
int UT_CNAME::m_max;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_THREADPOOL
