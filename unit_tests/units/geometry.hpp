#if defined(OMNI_UTUA) || defined(OMNI_UT_GEOMETRY)

#define UT_NAME geometry
#define UT_ISNS true
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(move_test, "tests movement functionality");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::geometry::point_t);
            print_info(omni::geometry::raw_point_t);
            print_info(omni::geometry::point_3d_t);
            print_info(omni::geometry::raw_point_3d_t);
            print_info(omni::geometry::rectangle_t);
            print_info(omni::geometry::raw_rectangle_t);
            print_info(omni::geometry::size_t);
            print_info(omni::geometry::raw_size_t);
        }
        
        void base_test()
        {
            omni::geometry::rectangle_t r1(40, 50, 50, 50);
            omni::geometry::rectangle_t r2(70, 70, 70, 50);
            omni::geometry::rectangle_t r3 = omni::geometry::rectangle_t::intersect(r1, r2);
            omni::geometry::rectangle_t r4 = omni::geometry::rectangle_t::merge(r1, r2);

            std::cout << "r1:" << r1 << std::endl;
            omni::out << "r2:" << r2 << std::endl;
            omni::out << "r3:" << r3 << std::endl;
            omni::out << "r4:" << r4 << std::endl;

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
        }

        void move_test()
        {
            typedef omni_seq_t<omni::geometry::rectangle_t> list_t;
            list_t enemies;
            for (int i = 0; i < 40; ++i) {
                enemies.push_back(omni::geometry::rectangle_t(0,0,150,150));
                omni::out << enemies.back() << std::endl;
            }
            for (list_t::iterator itr = enemies.begin(); itr != enemies.end(); ++itr) {
                *itr += omni::geometry::point_t(10, 10);
                omni::out << *itr << std::endl;
            }
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
