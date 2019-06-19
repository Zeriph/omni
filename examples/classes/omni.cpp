/* main.cpp */
#include <omni/framework>

class MyClass {
    public:
        MyClass() : m_lock(), m_i(42) { }
        MyClass(int i) : m_lock(), m_i(i) { }
        
        void increment_loop()
        {
            std::cout << "entering thread " << omni::sync::thread_id() << std::endl;
            while (!omni::sync::thread::abort_requested()) {
                omni::sync::sleep(100);
                this->m_lock.lock();
                ++this->m_i;
                this->m_lock.unlock();
            }
            std::cout << "leaving thread " << omni::sync::thread_id() << std::endl;
        }
        
        void increment_loop2(omni::sync::thread_arg_t args)
        {
            int* pval = static_cast<int*>(args);
            std::cout << "entering thread " << omni::sync::thread_id() << std::endl;
            while (!omni::sync::thread::abort_requested()) {
                omni::sync::sleep(100);
                ++(*pval);
                this->m_lock.lock();
                ++this->m_i;
                this->m_lock.unlock();
            }
            std::cout << "leaving thread " << omni::sync::thread_id() << std::endl;
        }
        
        int get_val() const
        {
            omni::sync::auto_lock<omni::sync::basic_lock> alock(&this->m_lock);
            return this->m_i;
        }

        operator std::wstring() const
        {
            return omni::string::util::to_wstring(this->get_val());
        }
        
        OMNI_STREAM_OPERATORS(MyClass, get_val())

    private:
        mutable omni::sync::basic_lock m_lock;
        int m_i;
};

static omni::sync::thread* thread2;

// timer_delegate is typedef'd as omni::delegate2<void, omni::chrono::tick_t, const omni::generic_ptr&>
void timer_tick(omni::chrono::tick_t tick, const omni::generic_ptr& sobj)
{
    static int tval;
    std::cout << "tick# " << tval << ": val = " << (*static_cast<MyClass*>(sobj)) << std::endl;
    if (++tval == 5) {
        std::cout << "requesting abort for thread " << thread2->id() << std::endl;
        omni::sync::thread::request_abort(thread2->id());
    }
}

void user_thread_exception(const omni::exception& ex)
{
    std::cout << "An exception occurred: " << ex << std::endl;
}

void thread_exception()
{
    std::cout << "An unknown error occurred." << std::endl;
}

int main(int argc, char* argv[])
{
    // Hook up to any unhandled thread exception
    omni::sync::unhandled_thread_exception += &thread_exception;
    omni::sync::user_thread_exception += &user_thread_exception;
    
    // Our objects
    MyClass val(20);
    int ival = 50;
    
    // Create a managed thread on the stack using the thread_start::bind to attach to val
    omni::sync::thread thread1(omni::sync::bind_param<MyClass, &MyClass::increment_loop2>(val));
    
    // Create a managed thread on the heap using allocate_thread template function
    thread2 = omni::sync::allocate_thread<MyClass, &MyClass::increment_loop>(val, omni::sync::thread_option::AUTO_JOIN, true);
    
    // Async timer, tick every second (1000ms == 1s)
    omni::chrono::async_timer timer(1000);
    
    // hook up the tick event and state object to use
    timer.tick += &timer_tick;
    timer.state_object = &val;
    
    // stream operator
    std::cout << "starting: val = " << val << ", ival = " << ival << std::endl; // output: 20
    std::stringstream ss;
    ss << val; // stream operator
    std::cout << "string stream val = " << ss.str() << std::endl;
    std::string str = omni::string::util::to_string(val); // stream operator
    std::cout << "string val = " << str << std::endl;
    std::wstring wstr = static_cast<std::wstring>(val); // operator std::wstring
    std::wcout << "wstring val = " << wstr << std::endl;
    std::wcout << "wcout val = " << val << std::endl; // stream operator
    
    // start the threads
    timer.start();
    thread1.start(&ival);
    thread2->start();
    
    // print ID's
    std::cout << "thread1: " << thread1.id() << std::endl;
    std::cout << "thread2: " << thread2->id() << std::endl;
    std::cout << "after start: val = " << val << ", ival = " << ival << std::endl;
    
    // auto_join = true, so thread2 will join on destruction
    delete thread2;
    
    // we won't get here until the timer has finished
    std::cout << "after thread destroy: val = " << val << ", ival = " << ival << std::endl;
    // abort the thread and wait for it to finish
    thread1.abort_join();
    std::cout << "ending val = " << val << std::endl;
    return 0;
}