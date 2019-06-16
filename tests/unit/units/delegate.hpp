#if defined(OMNI_UTUA) || defined(OMNI_UT_DELEGATE)

#define UT_NAME delegate
#define UT_DESC "Tests the various omni::delegate functionality"
#include <utdefs/unit_test.hpp>

#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
// #include <map>
// #include <priority_queue>
// #include <multiset>
// #include <multimap>
// #include <array>
// #include <forward_list>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(attach_test, "tests the attach/detach functionality for STL containers");
            M_LIST_ADD(copy_test, "tests the timing of the copying stuff");
            M_LIST_ADD(cocon_test, "test co/contra-variance");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            print_info(omni::callback);
            print_info(omni::callback1);
            print_info(omni::callback2);
            print_info(omni::callback3);
            print_info(omni::callback4);
            print_info(omni::callback5);
            print_info(omni::callback6);
            print_info(omni::callback7);
            print_info(omni::callback8);
            print_info(omni::callback9);
            print_info(omni::callback10);
            print_info(omni::callback11);
            print_info(omni::callback12);
            print_info(omni::callback13);
            print_info(omni::callback14);
            print_info(omni::callback15);
            print_info(omni::callback16);
        }
        
        void base_test()
        {
            //omni::smart_ptr<void> test(static_cast<void*>(new child_code(10)));
            //(static_cast<child_code*>(*test))->pval();
            omni::callback dtest = &UT_CNAME::class_base_test;
            dtest();
            
            int v = 42;
            void *p = static_cast<void*>(&v);
            child_code b;
            child_code *pb = &b;
            child_code *const pcb = &b;
            const child_code cb;
            const child_code *cpb = &cb;
            const child_code *const cpcb = &cb;
            
            //omni::callback aaa(&child_code::blah, b);
            //aaa();
            omni::callback dtest2 = omni::callback::bind<child_code, &child_code::blah>(b);
            dtest2();
            
            printl("bind b");
            omni::callback1 a = omni::callback1::bind<child_code, &child_code::doit>(b);
            printl("bind &b");
            omni::callback1 ada = omni::callback1::bind<child_code, &child_code::doit>(&b);
            
            printl("");
            
            printl("bind pb");
            omni::callback1 pa = omni::callback1::bind<child_code, &child_code::doit>(pb);
            printl("bind *pb");
            omni::callback1 apa = omni::callback1::bind<child_code, &child_code::doit>(*pb);
            
            printl("");
            
            printl("bind pcb");
            omni::callback1 pca = omni::callback1::bind<child_code, &child_code::doit>(pcb);
            printl("bind *pcb");
            omni::callback1 apca = omni::callback1::bind<child_code, &child_code::doit>(*pcb);
          
            printl("");
          
            printl("bind cb");
            omni::callback1 ca = omni::callback1::bind<child_code, &child_code::doit>(cb);
            printl("bind &cb");
            omni::callback1 aca = omni::callback1::bind<child_code, &child_code::doit>(&cb);
            
            printl("");
            
            printl("bind cpb");
            omni::callback1 cpa = omni::callback1::bind<child_code, &child_code::doit>(cpb);
            printl("bind *cpb");
            omni::callback1 acpa = omni::callback1::bind<child_code, &child_code::doit>(*cpb);
            
            printl("");
            
            printl("bind cpcb");
            omni::callback1 cpca = omni::callback1::bind<child_code, &child_code::doit>(cpcb);
            printl("bind *cpcb");
            omni::callback1 acpca = omni::callback1::bind<child_code, &child_code::doit>(*cpcb);
            
            //// START INVOKE
            
            printl("invoke b");
            a(p);
            printl("invoke &b");
            ada(p);
            
            printl("");
            
            printl("invoke pb");
            pa(p);
            printl("invoke *pb");
            apa(p);
            
            printl("");
            
            printl("invoke pcb");
            pca(p);
            printl("invoke *pcb");
            apca(p);
          
            printl("");
          
            printl("invoke cb");
            ca(p);
            printl("invoke &cb");
            aca(p);
            
            printl("");
            
            printl("invoke cpb");
            cpa(p);
            printl("invoke *cpb");
            acpa(p);
            
            printl("");
            
            printl("invoke cpcb");
            cpca(p);
            printl("invoke *cpcb");
            acpca(p);
            
            
            ///// start const check
            
            printl("bind b_const");
            omni::callback1 a_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(b);
            printl("bind &b_const");
            omni::callback1 ada_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(&b);
            
            printl("");
            
            printl("bind pb_const");
            omni::callback1 pa_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(pb);
            printl("bind *pb_const");
            omni::callback1 apa_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(*pb);
            
            printl("");
            
            printl("bind pcb_const");
            omni::callback1 pca_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(pcb);
            printl("bind *pcb_const");
            omni::callback1 apca_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(*pcb);
          
            printl("");
          
            printl("bind cb_const");
            omni::callback1 ca_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(cb);
            printl("bind &cb_const");
            omni::callback1 aca_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(&cb);
            
            printl("");
            
            printl("bind cpb_const");
            omni::callback1 cpa_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(cpb);
            printl("bind *cpb_const");
            omni::callback1 acpa_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(*cpb);
            
            printl("");
            
            printl("bind cpcb_const");
            omni::callback1 cpca_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(cpcb);
            printl("bind *cpcb_const");
            omni::callback1 acpca_const = omni::callback1::bind_const<child_code, &child_code::doit_const>(*cpcb);
            
            //// START INVOKE
            
            printl("invoke b_const");
            a_const(p);
            printl("invoke &b_const");
            ada_const(p);
            
            printl("");
            
            printl("invoke pb_const");
            pa_const(p);
            printl("invoke *pb_const");
            apa_const(p);
            
            printl("");
            
            printl("invoke pcb_const");
            pca_const(p);
            printl("invoke *pcb_const");
            apca_const(p);
          
            printl("");
          
            printl("invoke cb_const");
            ca_const(p);
            printl("invoke &cb_const");
            aca_const(p);
            
            printl("");
            
            printl("invoke cpb_const");
            cpa_const(p);
            printl("invoke *cpb_const");
            acpa_const(p);
            
            printl("");
            
            printl("invoke cpcb_const");
            cpca_const(p);
            printl("invoke *cpcb_const");
            acpca_const(p);
        }
        
        void attach_test()
        {
            omni::callback d1 = &UT_CNAME::class_base_test;
            omni::callback d2 = &UT_CNAME::class_base_test;
            
            omni::action e, e2, e3;
            std::list<omni::callback> l;
            std::vector<omni::callback> v;
            std::deque<omni::callback> d;
            std::list<omni::callback>::iterator il;
            std::vector<omni::callback>::iterator iv;
            std::deque<omni::callback>::iterator id;
            
            e += d1; e += d2;
            l.push_back(d1); l.push_back(d2);
            v.push_back(d1); v.push_back(d2);
            d.push_back(d1); d.push_back(d2);
            
            printl("testing lists (should be 6)");
            for (il = l.begin(); il != l.end(); ++il) { (*il)(); }
            for (iv = v.begin(); iv != v.end(); ++iv) { (*iv)(); }
            for (id = d.begin(); id != d.end(); ++id) { (*id)(); }
            printl("testing event (should be 2)");
            if (e) { e(); }
            
            e.attach(l.begin(), l.end());
            e.attach(v.begin(), v.end());
            e.attach(d.begin(), d.end());
            
            for (il = l.begin(); il != l.end(); ++il) { e += *il; }
            for (iv = v.begin(); iv != v.end(); ++iv) { e += *iv; }
            for (id = d.begin(); id != d.end(); ++id) { e += *id; }
            printl("event with attached delegates from lists (14)");
            if (e) { e(); }
            
            e2 = e;
            
            e.detach(l.begin(), l.end());
            e.detach(v.begin(), v.end());
            e.detach(d.begin(), d.end());
            printl("event with detached delegates from lists (8)");
            if (e) { e(); }
            
            e3 = e + e2;
        }
        
        void copy_test()
        {
            omni::callback cb1 = &class_base_test;
            omni::callback cb2 = &class_base_test2;
            
            omni::stopwatch sw;
            std::size_t tot = 0;
            int mval = 1000000;
            for (int x = 0; x < mval; ++x) {
                sw.restart();
                cb1 = cb2;
                cb1 = &class_base_test;
                sw.stop();
                tot += sw.elapsed_us();
            }
            printv("tot: ", tot);
            printv("avg: ", (static_cast<double>(tot) / mval));
        }
        
        void cocon_test()
        {
            // covariance
            omni::delegate<strx> covar = &UT_CNAME::getstrx;
            objx x = covar();
            // contravariance (fails even for regular fn_ptrs)
            //omni::delegate1<void, strx> convar = &setstrx;
            //strxfnptr f = &setstrx;
            
            omni::delegate1<void, objx> convar =  omni::delegate1<void, objx>::bind<UT_CNAME, &UT_CNAME::setstrx>(this);
            //strxfnptr f = &setstrx;
            convar(covar());
        }
        
    private:
        static void class_base_test()
        {
            printl("base test");
        }
        
        static void class_base_test2()
        {
            printl("base test");
        }
    
        class objx {};
        class strx : public objx {};
        
        typedef void (*strxfnptr)(strx);
        typedef void* (*test_fnptr_t)(void*);

        class thread_class
        {
            public:
                thread_class() {/* empty */}
                virtual ~thread_class() {/* empty */}

                /** Returns true if the thread was successfully started, false if there was an error starting the thread */
                bool start(void *p)
                {
                    _args = p;
                    #if defined(_MSC_VER)
                    return false;
                    #else
                    return (pthread_create(&_thread, NULL, _run, this) == 0);
                    #endif
                }

                /** Will not return until the internal thread has exited. */
                void join()
                {
                    #if !defined(_MSC_VER)
                    pthread_join(_thread, NULL);
                    #endif
                }

                protected:
                    /** Implement this method in your subclass with the code you want your thread to run. */
                    virtual void run() = 0;
                    void *_args;
                    
                private:
                    static void *_run(void *t)
                    {
                        ((thread_class*)t)->run();
                        return NULL;
                    }
                    
                    OMNI_THREAD_T _thread;
        };

        class child_code : public thread_class {
            public:
                child_code() : value(0) {}
                child_code(int i) : value(i) {}
                ~child_code() { value = 0; }
                void pval() const { std::cout << this->value << std::endl; }
                int value;
                
                void blah()
                {
                    printl("in blah");
                }
                
                void doit(void *p)
                {
                    int x = *(static_cast<int*>(p));
                    if (this->value == x) { ++this->value; }
                    else { this->value = x; }
                    this->pval();
                }
            
                void doit_const(void *p) const
                {
                    this->pval();
                }
            
                void class_blankness(const omni::sync::thread *const sender,
                            omni::sync::thread_state::enum_t ostate,
                            omni::sync::thread_state::enum_t nstate)
                {
                    printl("blah (class)");
                }
            protected:
                void run()
                {
                    doit(this->_args);
                }
        };
    
        static strx getstrx()
        {
            return strx();
        }

        void setstrx(objx obj)
        {
        }
    
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_DELEGATE
