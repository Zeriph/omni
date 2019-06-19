#include <omni/framework>

static omni::sync::semaphore sem; // default 5 owners max
static omni::sync::spin_wait spin;
static omni::sync::basic_lock block;
static std::size_t count;

static void increment()
{
    omni::sync::scoped_lock<omni::sync::basic_lock> alock(&block);
    ++count;
}

static void decrement()
{
    omni::sync::scoped_lock<omni::sync::basic_lock> alock(&block);
    --count;
    if (count == 0) {
        spin.signal();
    }
}

class Obj1 {
    public:
        Obj1() : m_val(42), m_mtx(), m_cond() {}
        Obj1(int val) : m_val(val), m_mtx(), m_cond() {}
        
        int get_val()
        {
            omni::sync::scoped_lock<omni::sync::mutex> alock(&this->m_mtx);
            return this->m_val;
        }
        
        void print_val()
        {
            this->m_mtx.lock();
            std::cout << this->m_val << std::endl;
            this->m_mtx.unlock();
        }
        
        int set_val(int val)
        {
            omni::sync::scoped_lock<omni::sync::mutex> alock(&this->m_mtx);
            this->m_val = val;
            return this->m_val;
        }
        
        void thread_func()
        {
            increment();
            sem.wait();
            this->m_cond.wait();
            this->print_val();
            sem.release();
            decrement();
        }
        
        void thread_func2()
        {
            increment();
            sem.wait();
            this->m_cond.wait();
            this->set_val(10);
            this->print_val();
            sem.release();
            decrement();
        }
        
        void signal_all()
        {
            this->m_cond.broadcast();
        }
        
    private:
        int m_val;
        omni::sync::mutex m_mtx;
        omni::sync::conditional m_cond;
};


int main(int argc, char* argv[])
{
    Obj1 obj1(100);
    omni::sync::thread t1(omni::sync::bind<Obj1, &Obj1::thread_func2>(obj1));
    omni::sync::thread t2(omni::sync::bind<Obj1, &Obj1::thread_func2>(obj1));
    for (int i = 0; i < 10; ++i) {
        omni::sync::create_basic_thread<Obj1, &Obj1::thread_func>(obj1);
    }
    t1.start();
    t2.start();
    
    obj1.set_val(obj1.get_val() + 10);
    omni::sync::sleep(1000);
    obj1.signal_all();

    spin.sleep_wait();
    
    t1.join();
    t2.join();
    std::cout << "leaving" << std::endl;
    return 0;
}
