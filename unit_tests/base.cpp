#include <omnilib>
#include <vector>

int main(int argc, char* argv[])
{
    /*omni::net::network_interface nic = omni::net::network_interface::ETHERNET;
    std::cout << "NIC (cstr): " << nic.to_string() << std::endl;
    std::wcout << "NIC (wstr): " << nic.to_wstring() << std::endl;*/


    omni::net::address_family a = omni::net::address_family::UNIX;
    omni::net::network_interface b = omni::net::network_interface::ETHERNET;
    omni::net::ping_reply c = omni::net::ping_reply::DESTINATION_NETWORK_UNREACHABLE;
    omni::net::protocol_type d = omni::net::protocol_type::ICMP;
    omni::net::socket_error e = omni::net::socket_error::OPERATION_ABORTED;
    omni::net::socket_flags f = omni::net::socket_flags::OUT_OF_BAND;
    omni::net::select_mode g = omni::net::select_mode::SELECT_READ;
    omni::net::socket_option_level h = omni::net::socket_option_level::TCP;
    omni::net::socket_option_name i = omni::net::socket_option_name::NO_DELAY;
    omni::net::socket_shutdown j = omni::net::socket_shutdown::BOTH;
    omni::net::socket_type k = omni::net::socket_type::DGRAM;
    omni::chrono::timer_sync_type l = omni::chrono::timer_sync_type::DROP;
    omni::sync::thread_priority m = omni::sync::thread_priority::ABOVE_NORMAL;
    omni::sync::thread_start_type n = omni::sync::thread_start_type::USER;
    omni::sync::thread_state o = omni::sync::thread_state::STOP_REQUESTED;
    omni::sync::thread_option p = omni::sync::thread_option::ABORT_ON_DESTROY;

    std::cout << a << std::endl
              << b << std::endl
              << c << std::endl
              << d << std::endl
              << e << std::endl
              << f << std::endl
              << g << std::endl
              << h << std::endl
              << i << std::endl
              << j << std::endl
              << k << std::endl
              << l << std::endl
              << m << std::endl
              << n << std::endl
              << o << std::endl
              << p << std::endl;
/*
template < typename Rect >
static void print_r(const Rect& r1, int i)
{
    std::cout << "r" << i << ":{" <<
        r1.left() << ", " <<
        r1.top() << ", " <<
        r1.width() << ", " <<
        r1.height() << ", " <<
        r1.right() << ", " <<
        r1.bottom() << 
    "}" << std::endl;
}

static std::vector<omni::geometry::rectangle_t> enemies;

class MyClass
{
    public:
        MyClass() : m_val(42) {}
        MyClass(int v) : m_val(v) {}

        int get()
        {
            return this->m_val;
        }

        void set(int x, int y)
        {
            this->m_val = x + y;
        }

        void print()
        {
            std::cout << this->m_val << std::endl;
        }

    private:
        int m_val;
};

typedef omni_delegate(void, int, int) d2;

int main(int argc, char* argv[])
{
    MyClass obj(42);

    // omni::delegate<int> pv = omni::delegate<void>::bind<MyClass, &MyClass::print>(obj);
    omni_delegate(void) pv = omni_bind(void, MyClass, print, obj);

    // omni::delegate2<void, int, int> sv = omni::delegate2<void, int, int>::bind<MyClass, &MyClass::set>(obj);
    omni_delegate(void, int, int) sv = omni_bind(void, int, int, MyClass, set, obj);
    
    // NOTE: you can use the OMNI_DELEGATE macro to bind as well
    // omni::delegate2<void, int, int> sv = omni::delegate2<void, int, int>::bind<MyClass, &MyClass::set>(obj);
    d2 sv2 = d2::bind<MyClass, &MyClass::set>(obj);
    
    // omni::delegate<int> gv = omni::delegate<int>::bind<MyClass, &MyClass::get>(obj);
    omni_delegate(int) gv = omni_bind(int, MyClass, get, obj);

    obj.print();
    pv();
    sv(10, 20);
    
    obj.print();
    pv();
    sv2(30, 10);

    obj.print();
    std::cout << gv() << std::endl;




    for (int i = 0; i < 40; ++i) {
        enemies.push_back(omni::geometry::rectangle_t(0,0,150,150));
        print_r(enemies.back(), (i+1));
    }

    omni::geometry::rectangle_t r1( 40, 50, 50, 50);
    omni::geometry::rectangle_t r2( 70, 70, 70, 50);
    omni::geometry::rectangle_t r3 = omni::geometry::rectangle_t::intersect(r1, r2);
    omni::geometry::rectangle_t r4 = omni::geometry::rectangle_t::merge(r1, r2);

    std::cout << "does" << (r1.intersects_with(r2) ? " " : " NOT ") << "intersect" << std::endl;
    
    std::cout << "xywh_p1 " <<
        (omni::geometry::rectangle_xywh_contains_point(r1.x(), r1.y(), r1.width(), r1.height(), r2.x(), r2.y()) ?
            "contains" : "doesn't contain") << std::endl;
    std::cout << "xywh_p2 " <<
        (omni::geometry::rectangle_xywh_contains_point(r1.x(), r1.y(), r1.width(), r1.height(), r2.location()) ?
            "contains" : "doesn't contain") << std::endl;

    std::cout << "ltrb_p1 " <<
        (omni::geometry::rectangle_ltrb_contains_point(r1.left(), r1.top(), r1.right(), r1.bottom(), r2.x(), r2.y()) ?
            "contains" : "doesn't contain") << std::endl;
    std::cout << "ltrb_p2 " <<
        (omni::geometry::rectangle_ltrb_contains_point(r1.left(), r1.top(), r1.right(), r1.bottom(), r2.location()) ?
            "contains" : "doesn't contain") << std::endl;

    print_r(r1, 1);
    print_r(r2, 2);
    print_r(r3, 3);
    print_r(r4, 4);
    */

    return 0;
}