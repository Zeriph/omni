#if defined(OMNI_UTUA) || defined(OMNI_UT_BASIC_THREAD)

#define UT_ROOT_NS sync
#define UT_NAME basic_thread
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(reuse_test, "tests the allow thread reuse option");
            M_LIST_ADD(abort_test, "test the abort capabilities");
            M_LIST_ADD(class_test, "test the class member threading functionality");
            #if defined(OMNI_NON_PORTABLE)
                M_LIST_ADD(priority_test, "test getting/setting the thread priority");
            #endif
            M_LIST_ADD(join_test, "test the thread join capabilities");
            M_LIST_ADD(auto_join_test, "test the thread auto-join capabilities");
            M_LIST_ADD(kill_test, "tests the forceful termination of a thread");
            M_LIST_ADD(basic_thread_test, "tests the basic_thread capability");
            M_LIST_ADD(current_thread_test, "tests the static method to get the current thread as an object");
            M_LIST_ADD(swap2_test, "test the assignment operator");
            M_LIST_ADD(swap_test, "test swapping two thread objects with each other context");
        }
        
        UT_CLASS_DTOR() {}

        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::sync::basic_thread t;
            omni::sync::thread_start d1, d2;
            printl("creating d1");
            d1 = &UT_CNAME::thread_func;
            printl("creating d2");
            d2 = &UT_CNAME::thread_func2;
            printl("creating thread (with thread reuse)");
            t.bind(d1);
            t.set_option(omni::sync::thread_option::ALLOW_THREAD_REUSE, true);
            printl("starting d1");
            t.start();
            printl("waiting for d1");
            t.join();
            printl("d1 done, unbinding");
            t.unbind();
            printl("attaching d2");
            t.bind(d2);
            printl("starting d2");
            t.start();
            printl("waiting for d2");
            t.join();
            printl("d1 done, unbinding");
            t.unbind();
            printl("attaching &thread_func2");
            t.bind(&UT_CNAME::thread_func2);
            printl("starting &thread_func2");
            t.start();
            printl("waiting for &thread_func2");
            t.join();
            printl("&thread_func2 done, unbinding");
            t.unbind();
            printl("returning");
        }
        
        void abort_test()
        {
            printl("creating thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func);
            printl("starting thread then sleeping for 2 seconds");
            t.detach();
            omni::sync::sleep(2000);
            if (t.status() == omni::sync::thread_state::RUNNING) {
                printl("State is currently running");
            } else {
                printl("State is other");
            }
            printl("waiting for thread (won't work)");
            t.join();
            printl("returning and core dump");
        }

        void ctor_test()
        {
            //omni::sync::thread<UT_CNAME, &UT_CNAME::template_thread_func> t(*this);
            //t.start();
            //t.join();
            //omni::sync::thread<UT_CNAME, &UT_CNAME::template_thread_func> t(*this);
            
            //omni::sync::thread* t = new omni::sync::thread< ut_thread, &ut_thread::template_thread_func >(*this);

            //omni::sync::thread* t1 = new omni::sync::thread<&UT_CNAME::thread_func>();
            //omni::sync::thread<&UT_CNAME::thread_func> t1;

            //omni::sync::thread* t2 = new omni::sync::thread<UT_CNAME, &UT_CNAME::template_thread_func>(*this);
            //omni::sync::thread* t = new omni::sync::thread<ut_thread, &ut_thread::template_thread_func>(*this);

            //omni::delegate<void> d = omni::delegate<void>::bind<ut_thread, &ut_thread::template_thread_func>(*this);
            //omni::delegate<void> <ut_thread, &ut_thread::template_thread_func> d(*this);
            //omni::callback b(
            
            //omni::sync::thread t< ut_thread, &ut_thread::template_thread_func >(*this);
            
            

        }

        void class_test()
        {
            printl("creating class object utthread, init list init");
            utthread *utt = new utthread(false);
            printl("starting utt");
            utt->start();
            printl("sleeping 3 seconds");
            omni::sync::sleep(3000);
            printl("waiting");
            utt->wait();
            printl("starting 25");
            utt->start(25);
            printl("sleeping 2 seconds");
            omni::sync::sleep(2000);
            printl("deleting object, dtor being called, aborting thread");
            delete utt;
            
            printl("creating non-pointer type utthread");
            utthread utt2;
            printl("calling attach");
            utt2.attach(omni::sync::parameterized_thread_start::bind<utthread, &utthread::run>(utt2));
            printl("starting utt");
            utt2.start();
            printl("sleeping 3 seconds");
            omni::sync::sleep(3000);
            printl("waiting");
            utt2.wait();
            printl("starting 25");
            utt2.start(25);
            printl("sleeping 2 seconds");
            omni::sync::sleep(2000);
            printl("waiting");
            utt2.wait();
            printl("returning");
        }

        void detach_test()
        {
            printl("creating thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func); // auto start
            
            t.join();
            printl("leaving");
        }
        
        void join_test()
        {
            printl("creating thread");
            omni::chrono::tick_t start = omni::chrono::monotonic_tick();
            printl("starting thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func);
            //t.start(); basic_thread's are auto-start
            printl("waiting for thread for 2 seconds");
            if (!t.join(2000)) {
                printv("join timed out after ", omni::chrono::elapsed_ms(start));
            }
            printl("waiting for thread for 4 seconds");
            if (!t.join(4000)) {
                printv("join timed out after ", omni::chrono::elapsed_ms(start));
            }
            printv("join after ", omni::chrono::elapsed_ms(start));
            printl("returning");
        }

        void auto_join_test()
        {
            printl("creating thread");
            printl("starting thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func, omni::sync::thread_option::AUTO_JOIN, true);
            //t.start(); basic_thread's are auto-start
            printl("leaving function, should auto-join thread");
        }

        void kill_test()
        {
            printl("creating thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func);
            printl("starting thread then sleeping for 2 seconds");
            //t.start(); basic_thread's are auto-start
            omni::sync::sleep(2000);
            printl("killing thread");
            if (!t.kill()) {
                printl("could not kill thread, waiting");
                t.join();
            } else {
                printl("thread killed");
            }
            printl("returning");
        }

        void current_thread_test()
        {
            omni::sync::basic_thread t;
            printv("Thread TID before = ", t.id());
            printv("Thread stack size before = ", t.options().stack_size());
            t = omni::sync::basic_thread::current();
            printv("Thread TID after = ", t.id());
            printv("Thread stack size after = ", t.options().stack_size());
            printl("returning");
        }

        void swap2_test()
        {
            omni::sync::basic_thread t1(&UT_CNAME::thread_func);
            omni::sync::basic_thread t2(&UT_CNAME::thread_func2);
            printl("starting threads");
            //t1.start(); basic_thread's are auto-start
            //t2.start(); basic_thread's are auto-start
            omni::sync::sleep(100);
            t1 = t2;
            t1.join(); // waiting on t2, t1 detached
            printl("returning");
        }
        
        void swap_test()
        {
            omni::sync::basic_thread t1(&UT_CNAME::thread_func);
            omni::sync::basic_thread t2(&UT_CNAME::thread_func2);
            printl("starting threads");
            //t1.start();
            //t2.start();
            printv("t1.tid == ", t1.id());
            printv("t2.tid == ", t2.id());
            printl("swapping");
            std::swap(t1, t2);
            printv("t1.tid == ", t1.id());
            printv("t2.tid == ", t2.id());
            printl("waiting for 1");
            t1.join();
            printl("waiting for 2");
            t2.join();
            printl("returning");
        }

        void reuse_test()
        {
            printl("creating thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func);
            t.set_option(omni::sync::thread_option::ALLOW_THREAD_REUSE, true);
            printl("starting thread then joining");
            //t.start();
            t.join();
            printl("thread reuse is true, restarting then joining");
            t.start();
            t.join();
        }

        #if defined(OMNI_NON_PORTABLE)
        void priority_test()
        {
            printl("creating thread");
            omni::sync::basic_thread t(&UT_CNAME::thread_func);
            t.set_option(omni::sync::thread_option::ALLOW_THREAD_REUSE, true);
            t.set_priority(omni::sync::thread_priority::LOWEST);
            printl("starting thread with omni::priority::LOWEST and sleeping for 2 seconds");
            //t.start();
            omni::sync::sleep(2000);
            printl("reseting priority to normal");
            t.set_priority(omni::sync::thread_priority::NORMAL);
            printl("waiting for thread");
            t.join();
            printl("returning");
        }
        #endif

        void basic_thread_test()
        {
            // basic_thread differs from thread in that it's auto start if a function is specified (or start type == NOW)
            omni::sync::basic_thread st(&UT_CNAME::thread_func);
            printl("waiting on system thread");
            st.join();
            printl("creating system thread 2");
            omni::sync::basic_thread st2(&UT_CNAME::thread_func);
            printl("detaching");
            omni::sync::thread_handle_t handle = st2.handle();
            st2.detach();
            printl("sleeping 1 then testing join...");
            omni::sync::sleep(1000);
            st2.join();
            printl("after join..doing join(handle)");
            if (!omni::sync::join_thread(handle)) {
                printl("error");
            }
            printl("returning");
        }
    
    private:
        static volatile bool m_AbortReq;
        
        class utthread {
            public:
                utthread() : m_abreq(false), m_x(0), m_t()
                {
                    printl("utthread::ctor() called");
                    //this->m_t.bind(omni::sync::thread_start::bind<utthread, &utthread::run>(*this));
                    this->_init();
                }
                
                // you can attach within member initializiation lists, but it's not advised since a 'this' pointer is used
                explicit utthread(bool uil) : m_abreq(false), m_x(0), m_t()
                {
                    printl("utthread::ctor(bool) called, thread start already attached");
                    if (uil) {
                        this->m_t.bind(omni::sync::parameterized_thread_start::bind<utthread, &utthread::run>(this));
                    } else {
                        this->m_t.bind(omni::sync::parameterized_thread_start::bind<utthread, &utthread::run>(*this));
                    }
                    this->_init();
                }
                
                explicit utthread(omni::sync::parameterized_thread_start ts) : m_abreq(false), m_x(0), m_t(ts)
                {
                    printl("utthread::ctor(ts) called, thread start already attached");
                    this->_init();
                }
                
                ~utthread() { }
                
                void attach(omni::sync::parameterized_thread_start ts)
                {
                    this->m_t.bind(ts);
                }
                
                void start()
                {
                    this->m_abreq = false;
                    this->m_x = 10;
                    this->m_t.start();
                }
                
                void start(int i)
                {
                    this->m_abreq = false;
                    this->m_x = i+10;
                    this->m_t.start(&i);
                }
                
                void wait() { this->m_t.join(); }
                
                void run(omni::sync::thread_arg_t p)
                {
                    if (p) { this->m_x = *(static_cast<int*>(p)); }
                    printv("this->m_x before = ", this->m_x);
                    while (!this->m_abreq) {
                        this->m_x++;
                        omni::sync::sleep(500);
                    }
                    printv("this->m_x after = ", this->m_x);
                }
                
            private:
                volatile bool m_abreq;
                int m_x;
                omni::sync::basic_thread m_t;
                
                void _init()
                {
                    this->m_t.set_option(omni::sync::thread_option::ALLOW_THREAD_REUSE, true);
                    // abort/kill it if we get destroyed
                    this->m_t.set_options(omni::sync::thread_option::KILL_ON_DESTROY | omni::sync::thread_option::AUTO_JOIN, true);
                    // give the thread a little time to complete after abort before checking to kill it
                    this->m_t.set_option(omni::sync::thread_option::AUTO_JOIN_TIMEOUT, 1000);
                }
        };
        
        static void thread_func()
        {
            omni::stopwatch sw;
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("thread_func tid#", tid);
            printv("sleeping for 5 seconds on tid#", tid);
            sw.start();
            while (sw.elapsed_ms() <= 5000) {
                omni::sync::sleep(1);
                if (m_AbortReq) { break; }
            }
            sw.stop();
            printv("leaving thread_func tid#", tid);
        }

        static void thread_func2()
        {
            omni::stopwatch sw;
            omni::sync::thread_t tid = omni::sync::thread_id();
            printv("thread_func2 tid#", tid);
            printv("sleeping for 5 seconds on tid#", tid);
            sw.start();
            while (sw.elapsed_ms() <= 5000) {
                omni::sync::sleep(1);
                if (m_AbortReq) { break; }
            }
            sw.stop();
            printv("leaving thread_func2 tid#", tid);
        }
};

volatile bool UT_CNAME::m_AbortReq;

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_BASIC_THREAD
