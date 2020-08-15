#include <omnilib>

static omni::sync::threadpool tpool;
static volatile bool is_run;

class Obj2 : public omni::sync::runnable
{
    public:
        Obj2() : m_val(42), m_mtx() {}
        Obj2(int val) : m_val(val), m_mtx() {}
        
        void increment(omni::generic_ptr pval)
        {
            
            for (int i = 0; i < 10; ++i) {
                this->m_mtx.lock();
                ++this->m_val;
                this->m_mtx.unlock();
                omni::sync::sleep(100);
            }
        }
        
        void print_val()
        {
            omni::sync::scoped_lock<omni::sync::basic_lock> alock(&this->m_mtx);
            std::cout << this->m_val << std::endl;
        }
        
        virtual void run(omni::sync::thread_arg_t args)
        {
            while (is_run) {
                tpool.queue(omni::sync::bind_param<Obj2, &Obj2::increment>(*this));
                omni::sync::sleep(50);
                this->print_val();
            }
        }
        
        int set_val(int val)
        {
            this->m_val = val;
            return this->m_val;
        }
        
    private:
        int m_val;
        omni::sync::basic_lock m_mtx;
};

static Obj2 obj2;

class Obj1 {
    public:
        Obj1() : m_val(42) {}
        Obj1(int val) : m_val(val) {}
        
        int get_val()
        {
            return this->m_val;
        }
        
        void print_val() const
        {
            std::cout << this->m_val << std::endl;
        }
        
        int set_val(int val)
        {
            this->m_val = val;
            return this->m_val;
        }
        
        void runit()
        {
            while (is_run) {
                this->set_val(this->get_val() + 1);
                tpool.queue(omni::sync::bind_param<Obj2, &Obj2::increment>(obj2));
                omni::sync::sleep(50);
                this->print_val();
            }
        }
        
    private:
        int m_val;
};

void run_threads(const Obj1& obj1)
{
    is_run = true;
    omni::sync::thread t1(omni::sync::bind<Obj1, &Obj1::runit>(obj1));
    omni::sync::basic_thread t2(omni::sync::bind<Obj1, &Obj1::runit>(obj1)); // auto-start
    t1.start(); // start thread
    
    omni::sync::runnable_thread rt(obj2);
    omni::sync::create_basic_thread_parameterized<Obj2, &Obj2::run>(obj2); // auto-start/detached
    rt.start(); // start the runnable thread
    
    std::cout << "Obj1 = ";
    obj1.print_val();
    
    std::cout << "Obj2 = ";
    obj2.print_val();
    
    std::cout << "waiting 5 seconds" << std::endl;
    omni::sync::sleep(5000); // sleep 5 seconds
    std::cout << "stopping" << std::endl;
    is_run = false;
    
    std::cout << "waiting on threads to finish" << std::endl;
    // t1.join(); omni::sync::thread types are auto-join by default
    t2.join();
    rt.join();
}

int main(int argc, char* argv[])
{
    Obj1 obj1(128);
    obj2.set_val(255);
    tpool.set_max_threads(10); // max of 10 threads to spawn
    run_threads(obj1);
    std::cout << "clearing any queued threadpool tasks" << std::endl;
    tpool.clear_queue();
    tpool.wait_active_queue();
    std::cout << "leaving" << std::endl;
    return 0;
}
