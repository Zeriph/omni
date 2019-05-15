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
    if (omni::string::util::is_numeric(val)) {
        std::cout << val << " = yes" << std::endl;
    } else {
        std::cout << val << " = no" << std::endl;
    }
}

void ip_test(const std::string& ip, const std::string& pf)
{
    std::cout << ip << " - should " << pf << " | result: ";
    if (omni::net::util::is_valid_ip4(ip)) {
        printl("PASS");
    } else {
        printl("FAIL");
    }
    std::cout << std::endl;
}

void ip_dot_test(const std::string& ip, const std::string& pf)
{
    std::cout << ip << " - should " << pf << " | result: ";
    if (omni::net::util::is_valid_dotted_ip4(ip)) {
        printl("PASS");
    } else {
        printl("FAIL");
    }
    std::cout << std::endl;
}

void ip_num_test(uint64_t val, const std::string& sip)
{
    uint32_t out = 0;
    std::string ip = omni::net::util::to_dotted_ip4_string(static_cast<uint32_t>(val));
    if (ip == sip) {
        std::cout << val << " = " << ip << "...";
        if (omni::net::util::try_parse_ip4(ip, out)) {
            std::cout << "out = " << out << "...";
            if (val == out) {
                std::cout << "PASS" << std::endl;
            } else {
                std::cout << "FAIL, VAL != OUT" << std::endl;
            }
        }
    } else {
        std::cout << "FAIL, IP != SIP" << std::endl;
    }
    std::cout << std::endl;
}

void do_ip_tests()
{
    ip_test("192.168.1.1", "PASS");
    ip_test("0Xc0a80101", "PASS");
    ip_test("0xC0.0xA8.1.0200", "PASS");
    ip_test("037777777777", "PASS");
    ip_test("0377.0377.0377.0377", "PASS");
    ip_test("0xFF.0xFF.0xFF.0xFF", "PASS");
    ip_test(" 192.168.1.1", "FAIL");
    ip_test("192.168.1.1 ", "FAIL");
    ip_test(" 192.168.1.1 ", "FAIL");
    ip_test(omni::cstring::trim(" 192.168.1.1 "), "PASS");
    ip_test("a", "FAIL");
    ip_test("x", "FAIL");
    ip_test("0x0", "PASS");
    ip_test("0xg", "FAIL");
    ip_test("0g", "FAIL");
    ip_test("19a.g4.hi.00", "FAIL");
    ip_test("3232235777", "PASS");
    std::cout << "ip_dot_test" << std::endl;
    ip_dot_test("255.255.255.255.255", "FAIL");
    ip_dot_test("255...255.255.", "FAIL");
    ip_dot_test("255..255.255", "FAIL");
    ip_dot_test(".255.255.255", "FAIL");
    ip_dot_test(".255.", "FAIL");
    ip_dot_test("255.", "FAIL");
    ip_dot_test(".255", "FAIL");
    ip_dot_test("255255255255255255255", "FAIL");
    ip_dot_test("255.255.255.255", "PASS");
    ip_dot_test("255.255.255", "PASS");
    ip_dot_test("255.255", "PASS");

    ip_dot_test("0xFF.0XFF.0377", "PASS");
    ip_dot_test("0377.255", "PASS");
    
    std::cout << "to_dotted_ipv4_string" << std::endl;
    ip_test(omni::net::util::to_dotted_ip4_string(3232235777), "PASS");
    ip_test(omni::net::util::to_dotted_ip4_string(4294967295), "PASS");
    ip_test(omni::net::util::to_dotted_ip4_string(0xC0A80134), "PASS");

    std::cout << "ip_num_test" << std::endl;
    ip_num_test(3232235777, "192.168.1.1");
    ip_num_test(4294967295, "255.255.255.255");
    ip_num_test(0xC0A80134, "192.168.1.52");

    std::cout << "0xFACE = " << omni::string::util::to_type<uint32_t>("0xFACE", 16) << std::endl;
    std::cout << "0371 = " << omni::string::util::to_type<uint32_t>("0371", 8) << std::endl;
    std::cout << "12345 = " << omni::string::util::to_type<uint32_t>("12345", 10) << std::endl;
}

int main(int argc, char* argv[])
{
    omni::net::socket s(omni::net::address_family::INTERNETWORK, omni::net::socket_type::STREAM, omni::net::protocol_type::IP);
    std::cout << "s is bound? " << (s.is_bound() ? "yes" : "no") << std::endl;
    std::cout << "s is connected? " << (s.is_connected() ? "yes" : "no") << std::endl;
    std::cout << "s is open? " << (s.is_open() ? "yes" : "no") << std::endl;
    std::cout << "s is listening? " << (s.is_listening() ? "yes" : "no") << std::endl;
    std::cout << "s is shutdown? " << (s.is_shutdown() ? "yes" : "no") << std::endl;
    
    
    /*omni::geometry::point_seq_t points = omni::geometry::path::get_circle(10, 10, 30);

    std::cout << "point count " << points.size() << std::endl;
    for (omni::geometry::point_seq_t::iterator itr = points.begin(); itr != points.end(); ++itr) {
        std::cout << "point: " << *itr << std::endl;
    }*/

    // [ws][-]{ d | [d.]hh:mm[:ss[.ff]] }[ws]
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