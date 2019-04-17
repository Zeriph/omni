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

void unsigned_test(const std::string& val, const std::string& should_be)
{
    omni::chrono::unsigned_timespan t;
    std::cout << "Parsing '" << val << "'...";
    if (omni::chrono::unsigned_timespan::try_parse(val, t)) {
        std::cout << "success: '" << t << "' should be '" << should_be << "'" << std::endl;
    } else {
        std::cout << "failed" << std::endl;
    }
}

void signed_test(const std::string& val, const std::string& should_be)
{
    omni::chrono::timespan t;
    std::cout << "Parsing '" << val << "'...";
    if (omni::chrono::timespan::try_parse(val, t)) {
        std::cout << "success: '" << t << "' should be '" << should_be << "'" << std::endl;
    } else {
        std::cout << "failed" << std::endl;
    }
}

void do_parse(const std::string& val, const std::string& should_be)
{
    signed_test(val, should_be);
    unsigned_test(val, should_be);
}

void num_test(const std::string& val)
{
    if (omni::string::util::is_numeric(val), true) {
        std::cout << val << " = yes" << std::endl;
    } else {
        std::cout << val << " = no" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    /*omni::geometry::point_seq_t points = omni::geometry::path::get_circle(10, 10, 30);

    std::cout << "point count " << points.size() << std::endl;
    for (omni::geometry::point_seq_t::iterator itr = points.begin(); itr != points.end(); ++itr) {
        std::cout << "point: " << *itr << std::endl;
    }*/

    // [ws][-]{ d | [d.]hh:mm[:ss[.ff]] }[ws]

    std::string s = "here's a standard string";
    std::wstring w = L"here's a wide string";
    std::string sw = omni::string_util::to_string(w);
    std::wstring ws = omni::string_util::to_wstring(s);
    
    std::cout << "s = " << s << std::endl;
    std::wcout << "w = " << w << std::endl;
    std::cout << "sw = " << sw << std::endl;
    std::wcout << "ws = " << ws << std::endl;

    std::cout << "cstr dnotfnd = " << omni::cconsts::err::DELEGATE_NOT_FOUND << std::endl;
    std::wcout << "wstr dnotfnd = " << omni::wconsts::err::DELEGATE_NOT_FOUND << std::endl;
    

    /*num_test("2");
    num_test("2.4");

    do_parse("10", "10.00:00:00.0");
    do_parse("16:24", "0.16:24:00.0");
    do_parse("25:24", "fail");
    do_parse("23:60", "fail");
    do_parse("23:23:23", "0.23:23:23.0");
    do_parse("2.4:4:2.4", "2.04:04:02.4");
    do_parse(" 12:10 ", "0.12:10:00.0");
    do_parse(" -12:10 ", "-0.12:10:00.0");
    do_parse(" 12:a0 ", "fail");
    do_parse(" b 12:10 ", "fail");*/
    
    return 0;
}