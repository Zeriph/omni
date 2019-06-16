#if defined(OMNI_UTUA) || defined(OMNI_UT_TIMER)

#define UT_ROOT_NS chrono
#define UT_NAME timer
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(async_test, "tests the async timer");
            M_LIST_ADD(sync_block_test, "tests the blocking timer");
            M_LIST_ADD(sync_queue_test, "tests queued timer");
            M_LIST_ADD(sync_skip_test, "tests skip timer");
            
            M_LIST_ADD(functionality_test, "tests extended timer functionality");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            //UT_INFO_TEST();
            print_info(omni::chrono::async_timer);
            print_info(omni::chrono::sync_timer);
            print_info(omni::chrono::queue_timer);
            print_info(omni::chrono::drop_timer);
        }
        
        void base_test()
        {
            //SYNC_NOBLOCK = 0,
            tval = 0;
            printl("creating auto with 2s interval");
            omni::chrono::timer_delegate te = &UT_CNAME::inttest1;
            omni::chrono::async_timer t1(2000, te);
            printl("start, sleep 6s, stop");
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(6500);
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            t1.stop();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printv("approx. iterations# ", (6500 / t1.interval()));
            t1.set_interval(1000);
            printv("set interval to ", t1.interval());
            printl("start, sleep 6s, stop");
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(6500);
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            t1.stop();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printv("approx. iterations# ", (6500 / t1.interval()));
            t1.set_interval(2000);
            printv("set interval to ", t1.interval());
            printl("start, sleep 1s, reset");
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(1500);
            t1.reset();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(2500);
            t1.stop();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printl("should only see 1 iteration");
            t1.set_interval(3000);
            printv("set interval to ", t1.interval());
            t1.start();
            omni::sync::sleep(4000);
            printl("should only see 1 iteration");
            printl("setting interval to 1000 ms while running, should see more ticks now");
            t1.set_interval(1000);
            omni::sync::sleep(4000);
            printl("attaching tick handler, should see x2 ticks");
            t1.tick += &UT_CNAME::inttest2;
            omni::sync::sleep(4000);
            printl("stopping");
            t1.stop();
        }

        void async_test()
        {
            /**
             * When the timer interval passes, the interval counter is reset and a separate thread is
             * spawned and detached in which the tick event will be fired.
             */
            tval = 0;
            printl("creating auto with 1s interval");
            omni::chrono::async_timer t1(1000, &UT_CNAME::inttest2);
            m_sw.start();
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(5000);
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printl("should see ~4-5 ticks");
            printl("stopping");
            t1.stop();
            printv("sw time: ", m_sw.stop());
            printl("done");
        }
        
        void sync_block_test()
        {
            /**
             * The tick event will not return (i.e. block the _run thread) until the delegate returns;
             * the next event won't be fired until 'interval' has passed.
             */
            tval = 0;
            printl("creating auto with 1s interval");
            omni::chrono::sync_timer t1(1000, &UT_CNAME::inttest2);
            m_sw.start();
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(5000);
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printl("should see 2 ticks");
            printl("stopping");
            t1.stop();
            printv("sw time: ", m_sw.stop());
            printl("done");
        }
        
        void sync_queue_test()
        {
            /**
             * The tick event will fire, but all subsequent 'ticks' will be queued if delegate blocks;
             * each queued call will be called in succession without regards to the tick event.
             */
            tval = 0;
            printl("creating auto with 1s interval");
            omni::chrono::queue_timer t1(1000, &UT_CNAME::inttest2);
            m_sw.start();
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(5000);
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printl("should see ~2 ticks");
            printl("stopping, waiting on queue");
            t1.stop(); // anything left in queue will be called
            printv("sw time: ", m_sw.stop());
            printl("should see ~5 ticks total, done");
        }
        
        void sync_skip_test()
        {
            /**
             * The tick event will file, but all subsequent 'ticks' will be ignored until the delegate
             * has finished. It is possible to have an events fire immediately after each other if the
             * timing works out such that the delegate call finishes as the tick event is about to occur.
             */
            tval = 0;
            printl("creating auto with 1s interval");
            omni::chrono::drop_timer t1(1000, &UT_CNAME::inttest2);
            m_sw.start();
            t1.start();
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            omni::sync::sleep(5000);
            printv("is_running() = ", OMNI_B2S(t1.is_running()));
            printl("should see ~2 ticks");
            printl("stopping");
            t1.stop();
            printv("sw time: ", m_sw.stop());
            printl("should see ~2 ticks total, done");
        }

        void functionality_test()
        {
            printl("creating auto");
            omni::chrono::async_timer t1;
            printv("interval = ", t1.interval());
            printl("creating auto 2 with interval of 2 seconds (2000 ms)");
            omni::chrono::async_timer t2(2000);
            printv("interval = ", t2.interval());
            printl("copying t2");
            omni::chrono::async_timer t3(t2);
            printv("interval = ", t3.interval());
            printl("assigning t2");
            omni::chrono::async_timer t4 = t2;
            printv("interval = ", t4.interval());
            printl("creating ptr of t2");
            omni::chrono::async_timer *t5 = new omni::chrono::async_timer();
            printv("interval = ", t5->interval());
            printl("deleting");
            delete t5;
            printl("leaving...should see 4 dtors");
        }
    
    private:
        static int tval;
        static omni::stopwatch m_sw;
        
        static void inttest1(omni::chrono::tick_t tick, const omni::generic_ptr& so)
        {
            printv("inttest1 ticked #", tval++ << " @ " << m_sw);
        }
        
        static void inttest2(omni::chrono::tick_t tick, const omni::generic_ptr& so)
        {
            int tv = tval++;
            printv("inttest2 ticked #", tv << " @ " << m_sw);
            omni::sync::sleep(2000);
            printv("inttest2 leaving#", tv);
        }
};

int UT_CNAME::tval;
omni::stopwatch UT_CNAME::m_sw;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMER
