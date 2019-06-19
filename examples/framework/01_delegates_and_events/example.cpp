#include <omni/framework>

class Obj1 {
    public:
        Obj1() : m_val(42) {}
        Obj1(int val) : m_val(val) {}
        
        int get_val() { return this->m_val; }
        
        void print_val() { std::cout << "object val: " << this->m_val << std::endl; }
        
        int set_val(int val)
        {
            this->m_val = val;
            return this->m_val;
        }
        
        void timer_ticked(omni::chrono::tick_t time, const omni::generic_ptr& sobj)
        {
            std::cout << "timer ticked, new val: " << ++this->m_val << std::endl;
        }
        
    private:
        int m_val;
};

int main(int argc, char* argv[])
{
    Obj1 obj1(255);
    omni::callback cb = omni::callback::bind<Obj1, &Obj1::print_val>(obj1);
    omni::delegate<int> di = omni::delegate<int>::bind<Obj1, &Obj1::get_val>(obj1);
    omni::delegate1<int, int> ri = omni::delegate1<int, int>::bind<Obj1, &Obj1::set_val>(obj1);
    
    omni::chrono::async_timer timer(1000); // tick every 1 second
    timer.tick += omni::chrono::timer_delegate::bind<Obj1, &Obj1::timer_ticked>(obj1);
    timer.start();
    
    int x = obj1.get_val();
    obj1.print_val();
    std::cout << "x = " << x << std::endl;
    omni::sync::sleep(2000);
    
    cb();     // calls obj1.print_val
    x = di(); // calls obj1.get_val
    std::cout << "x = " << x << ", di = " << di() << std::endl;
    omni::sync::sleep(2000);
    
    int y = ri(x * 2); // calls obj1.set_val
    std::cout << "y = " << y << std::endl;
    obj1.print_val();
    omni::sync::sleep(2000);
    
    timer.stop();
    obj1.print_val();
    return 0;
}
