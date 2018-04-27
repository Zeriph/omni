#if defined(OMNI_UTUA) || defined(OMNI_UT_RUNNABLE)

#define UT_ROOT_NS sync
#define UT_NAME runnable
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(state_changed_test, "test the state_changed thread functionality");
            M_LIST_ADD(reuse_test, "tests the allowThreadReuse option");
            M_LIST_ADD(abort_test, "test the abort capabilities");
            M_LIST_ADD(stack_size_test, "test the stack size capabilities");
            M_LIST_ADD(join_test, "test the thread join capabilities");
            M_LIST_ADD(auto_join_test, "test the thread auto-join capabilities");
            M_LIST_ADD(kill_test, "tests the forceful termination of a thread");
            M_LIST_ADD(swap_test, "test swapping two thread objects with each other context");
            #if defined(OMNI_NON_PORTABLE)
                M_LIST_ADD(priority_test, "test getting/setting the thread priority");
            #endif
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); } // TODO: print_info(omni::sync::runnable_thread);
        
        void base_test()
        {
            printl("starting rtt");
            RunnableTest rtt(10);
            omni::sync::runnable_thread t_rtt(rtt);
            t_rtt.start();
            omni::sync::sleep(1000);
            rtt.doStop();
            t_rtt.join();
            printl("ending rtt");
            
            printl("starting tt");
            ThreadTest tt(10);
            tt.start();
            omni::sync::sleep(1000);
            tt.doStop();
            tt.join();
            printl("ending tt");

            printl("starting t");
            omni::sync::runnable_thread* t = new ThreadTest(10);
            t->start();
            omni::sync::sleep(1000);
            //(dynamic_cast<ThreadTest*>(t))->doStop();
            t->join();
            delete t;
            printl("ending t");
        }

        void abort_test()
        {
            printl("creating thread");
            ThreadAbortTest t;
            printl("starting thread then sleeping for 2 seconds");
            t.start();
            omni::sync::sleep(2000);
            if (t.status() == omni::sync::thread_state::RUNNING) {
                printl("State is currently running");
            } else {
                printl("State is other");
            }
            printl("aborting thread");
            t.abort();
            printl("waiting for thread");
            t.join();
            printl("returning");
        }
        
        void stack_size_test()
        {
            printl("creating thread");
            ThreadAbortTest t;
            t.set_option(omni::sync::thread_option::STACK_SIZE, OMNI_MIB_IVAL);
            printl("starting thread then sleeping for 2 seconds");
            t.start();
            omni::sync::sleep(2000);
            if (t.status() == omni::sync::thread_state::RUNNING) {
                printl("State is currently running");
            } else {
                printl("State is other");
            }
            printl("aborting thread");
            t.abort();
            printl("waiting for thread");
            t.join();
            printl("returning");
        }

        void join_test()
        {
            printl("creating thread");
            ThreadTest t;
            printl("starting thread");
            t.start();
            printl("waiting for thread for 2 seconds");
            if (!t.join(2000)) {
                printl("join timed out");
            }
            printl("waiting for thread for 4 seconds");
            if (!t.join(4000)) {
                printl("join timed out");
            }
            t.doStop();
            t.join();
            printl("returning");
        }

        void auto_join_test()
        {
            printl("creating thread");
            AutoJoinTest t;
            t.set_option(omni::sync::thread_option::AUTO_JOIN, true);
            printl("starting thread");
            t.start();
            printl("leaving function, should auto-join thread");
        }

        void kill_test()
        {
            printl("creating thread");
            KillTest t;
            printl("starting thread then sleeping for 2 seconds");
            t.start();
            omni::sync::sleep(2000);
            printl("killing thread");
            if (!t.kill()) {
                printl("could not kill thread, waiting");
                t.doStop();
                t.join();
            } else {
                printl("thread killed");
            }
            printl("returning");
        }

        void state_changed_test()
        {
            printl("starting rtt");
            RunnableTest rtt(10);
            omni::sync::runnable_thread t_rtt(rtt);
            t_rtt.state_changed += &UT_CNAME::thread_state_changed;
            t_rtt.start();
            omni::sync::sleep(1000);
            rtt.doStop();
            t_rtt.join();
            printl("ending rtt");
            
            printl("starting tt");
            ThreadTest tt(10);
            tt.state_changed += &UT_CNAME::thread_state_changed;
            tt.start();
            omni::sync::sleep(1000);
            tt.doStop();
            tt.join();
            printl("ending tt");

            printl("starting t");
            omni::sync::runnable_thread* t = new ThreadTest(10);
            t->state_changed += &UT_CNAME::thread_state_changed;
            t->start();
            omni::sync::sleep(1000);
            //(dynamic_cast<ThreadTest*>(t))->doStop();
            t->join();
            delete t;
            printl("ending t");
        }

        void reuse_test()
        {
            printl("creating thread");
            ThreadTest t;
            t.set_option(omni::sync::thread_option::ALLOW_THREAD_REUSE, true);
            printl("starting thread then joining");
            t.start();
            omni::sync::sleep(1000);
            t.doStop();
            t.join();
            printl("thread reuse is true, restarting then joining");
            t.start();
            omni::sync::sleep(1000);
            t.doStop();
            t.join();
        }

        void swap_test()
        {
            ThreadTest t1;
            ThreadAbortTest t2;
            printl("starting threads");
            t1.start();
            t2.start();
            printv("t1.tid == ", t1.id());
            printv("t2.tid == ", t2.id());
            omni::sync::sleep(200);
            printl("swapping");
            std::swap(t1, t2);
            printv("t1.tid == ", t1.id());
            printv("t2.tid == ", t2.id());
            printl("sleep 200");
            omni::sync::sleep(200);
            printl("t1 stop/join");
            t1.doStop();
            if (!t1.join(100)) {
                printl("t1 join fail, t2 stop/ t1 join");
                t2.doStop();
                t1.join();
            }
            printl("t2 stop/join");
            t2.doStop();
            if (!t2.join(100)) {
                printl("t2 join fail, t1 stop/ t2 join");
                t1.doStop();
                t2.join();
            }
            printl("returning");
        }

        #if defined(OMNI_NON_PORTABLE)
        void priority_test()
        {
            printl("creating thread");
            ThreadTest t;
            t.set_option(omni::sync::thread_option::ALLOW_THREAD_REUSE, true);
            t.set_priority(omni::sync::thread_priority::LOWEST);
            printl("starting thread with omni::priority::LOWEST and sleeping for 2 seconds");
            t.start();
            omni::sync::sleep(2000);
            printl("resetting priority to normal");
            t.set_priority(omni::sync::thread_priority::NORMAL);
            printl("waiting for thread");
            t.doStop();
            t.join();
            printl("returning");
        }
        #endif

    private:
        class RunnableTest : virtual public omni::sync::runnable
        {
            public:
                RunnableTest() : _val(0), _sreq(false) {}
                RunnableTest(int v) : _val(v), _sreq(false) {}
                ~RunnableTest() {}
                void doStop() { this->_sreq = true; }

                virtual void run(omni::sync::thread_arg_t param)
                {
                    printv("before run, _val = ", this->_val);
                    while (!this->_sreq) {
                        this->_val++;
                        printv("while run, _val = ", this->_val);
                        omni::sync::sleep(50);
                    }
                    printv("after run, _val = ", this->_val);
                    this->_sreq = false;
                }
            
            private:
                int _val;
                volatile bool _sreq;
        };

        class ThreadTest : virtual public omni::sync::runnable_thread
        {
            public:
                ThreadTest() : _val(0), _sreq(false) {}
                ThreadTest(int v) : _val(v), _sreq(false) {}
                ~ThreadTest() {}
                void doStop() { this->_sreq = true; }

                virtual void run(omni::sync::thread_arg_t param)
                {
                    printv("before run, _val = ", this->_val);
                    while (!this->_sreq) {
                        this->_val++;
                        printv("while run, _val = ", this->_val);
                        omni::sync::sleep(50);
                    }
                    printv("after run, _val = ", this->_val);
                    this->_sreq = false;
                }
            
            private:
                int _val;
                volatile bool _sreq;
        };

        class ThreadAbortTest : virtual public omni::sync::runnable_thread
        {
            public:
                ThreadAbortTest() : _val(0), _sreq(false) {}
                ThreadAbortTest(int v) : _val(v), _sreq(false) {}
                ~ThreadAbortTest() {}
                void doStop() { this->_sreq = true; }

                virtual void state_update(omni::sync::thread_state::enum_t old_state)
                {
                    if (this->status() == omni::sync::thread_state::ABORT_REQUESTED) {
                        this->doStop();
                    }
                }
                
                virtual void run(omni::sync::thread_arg_t param)
                {
                    printv("before run, _val = ", this->_val);
                    while (!this->_sreq) {
                        this->_val++;
                        printv("while run, _val = ", this->_val);
                        omni::sync::sleep(50);
                    }
                    printv("after run, _val = ", this->_val);
                    this->_sreq = false;
                }
            
            private:
                int _val;
                volatile bool _sreq;
        };

        class AutoJoinTest : virtual public omni::sync::runnable_thread
        {
            public:
                AutoJoinTest() : _val(0), _sreq(false) {}
                AutoJoinTest(int v) : _val(v), _sreq(false) {}
                ~AutoJoinTest() {}
                void doStop() { this->_sreq = true; }

                virtual void run(omni::sync::thread_arg_t param)
                {
                    printv("before run, _val = ", this->_val);
                    while (!this->_sreq && this->_val < 10) {
                        this->_val++;
                        printv("while run, _val = ", this->_val);
                        omni::sync::sleep(50);
                    }
                    printv("after run, _val = ", this->_val);
                    this->_sreq = false;
                }
            
            private:
                int _val;
                volatile bool _sreq;
        };

        class KillTest : virtual public omni::sync::runnable_thread
        {
            public:
                KillTest() : _val(0), _sreq(false) {}
                KillTest(int v) : _val(v), _sreq(false) {}
                ~KillTest() {}
                void doStop() { this->_sreq = true; }

                virtual void run(omni::sync::thread_arg_t param)
                {
                    printv("before run, _val = ", this->_val);
                    while (!this->_sreq) {
                        this->_val++;
                        printv("while run, _val = ", this->_val);
                        omni::sync::sleep(50);
                    }
                    printv("after run, _val = ", this->_val);
                    this->_sreq = false;
                }
            
            private:
                int _val;
                volatile bool _sreq;
        };

        static void thread_state_changed(const omni::sync::runnable_thread& sender, omni::sync::thread_state::enum_t ostate)
        {
            printv("thread_state_changed: tid#", sender.id());
            switch (sender.status().value()) {
                printswe(omni::sync::thread_state::UNSTARTED, "status = ");
                printswe(omni::sync::thread_state::START_REQUESTED, "status = ");
                printswe(omni::sync::thread_state::RUNNING, "status = ");
                printswe(omni::sync::thread_state::COMPLETED, "status = ");
                printswe(omni::sync::thread_state::STOP_REQUESTED, "status = ");
                printswe(omni::sync::thread_state::STOPPED, "status = ");
                printswe(omni::sync::thread_state::ABORT_REQUESTED, "status = ");
                printswe(omni::sync::thread_state::ABORTED, "status = ");
                printswe(omni::sync::thread_state::UNKNOWN, "status = ");
            }
        }

        
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_RUNNABLE
