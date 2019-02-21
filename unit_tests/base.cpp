#include <omnilib>
#include <vector>

#define printl(v) std::cout << v << std::endl

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

    static void geo_test()
    {
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
    }
*/

static omni::sync::thread _thread;
static omni::chrono::unsigned_timespan _span;

static void thread_join_test()
{
    time_t start = omni::chrono::monotonic::tick();
    printl("sleeping for 2 seconds");
    omni::sync::sleep(2000);
    _span = omni::chrono::elapsed_us(start) * omni::chrono::TICKS_PER_MICROSECOND;
    printl("leaving thread");
}

int main(int argc, char* argv[])
{   
    _thread.bind(&thread_join_test);
    printl("bound, starting ...");
    _thread.start();
    printl("joining in main thread");
    _thread.join();
    printl("leaving main thread");
    printl("timespan = " << _span);
    _span += 5 * omni::chrono::TICKS_PER_HOUR;
    _span += 5 * omni::chrono::TICKS_PER_MINUTE;
    _span += 5 * omni::chrono::TICKS_PER_DAY;
    printl("timespan = " << _span);
    printl("total days = " << _span.total_days());
    printl("total hours = " << _span.total_hours());
    printl("total minutes = " << _span.total_minutes());
    printl("total seconds = " << _span.total_seconds());
    printl("total ms = " << _span.total_milliseconds());
    return 0;
}