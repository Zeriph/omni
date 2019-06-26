#if defined(OMNI_UTUA) || defined(OMNI_UT_GEOMETRY)

#define UT_NAME geometry
#define UT_ISNS true
#include <utdefs/unit_test.hpp>
#include <vector>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(move_test, "tests movement functionality");
            M_LIST_ADD(path_test, "tests the path namespace functionality");
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
            print_info(omni::geometry::vector2);
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

        static void path_test_sig(int sig)
        {
            if (sig == SIGSEGV) { exit(0); }
        }

        void path_test()
        {
            omni::application::signal_handler::attach(&path_test_sig);

            //template < typename T >
            //static typename omni_sequence_t< omni::geometry::point2d<T> > circle(T x, T y, T radius, T step, bool invert_x, bool invert_y)

            omni_sequence_t< omni::geometry::point2d<int> >::iterator it;
            std::vector< omni::geometry::point2d<double> >::iterator it2;
            omni_sequence_t< omni::geometry::point2d<int> > path = omni::geometry::path::circle(1, 1, 10, 1, false, false);
            std::sort(path.begin(), path.end());
            std::cout << "int: circle(1,1,10,1,false,false) = [" << path.size() << "]" << std::endl;
            for (it = path.begin(); it != path.end(); ++it) {
                std::cout << "[" << it->x() << ", " << it->y() << "] ";
            }
            std::cout << std::endl << std::endl;


            omni_sequence_t< omni::geometry::point2d<double> > pathf = omni::geometry::path::circle(1.0, 1.0, 10.0, 1.0, false, false);
            std::sort(pathf.begin(), pathf.end());
            std::cout << "float: circle(1.0,1.0,10.0,1.0,false,false) = [" << pathf.size() << "]" << std::endl;
            for (omni_sequence_t< omni::geometry::point2d<double> >::iterator itf = pathf.begin(); itf != pathf.end(); ++itf) {
                std::cout << "[" << itf->x() << ", " << itf->y() << "] ";
            }
            std::cout << std::endl << std::endl;

            //template < typename T >
            //static omni::geometry::point2d<T> point_on_circle(T angle, T radius, T center_x, T center_y)
            omni::geometry::point2d<int> point = omni::geometry::point_on_circle(30, 10, 1, 1);
            std::cout << "point_on_circle(30,10,1,1) = [" << point.x() << ", " << point.y() << "]" << std::endl << std::endl;

            omni::geometry::point2d<double> pointF = omni::geometry::point_on_circle(30.0, 10.0, 1.0, 1.0);
            std::cout << "point_on_circle(30.0,10.0,1.0,1.0) = [" << pointF.x() << ", " << pointF.y() << "]" << std::endl << std::endl;

            //template < typename T >
            //static typename omni_sequence_t< omni::geometry::point2d<T> >
            //line(T x1, T y1, T x2, T y2, T step, uint32_t skip, bool remove_duplicates)
            omni_sequence_t< omni::geometry::point2d<int> > path2 = omni::geometry::path::line(1, 1, 10, 10);
            std::cout << "line(1,1,10,10) = ";
            for (it = path2.begin(); it != path2.end(); ++it) {
                std::cout << "[" << it->x() << ", " << it->y() << "] ";
            }
            std::cout << std::endl << std::endl;

            std::vector< omni::geometry::point2d< double> > path3 = omni::geometry::path::line<std::vector, double>(1.0, 1.0, 10.0, 10.0);

            std::cout << "line(1.0,1.0,10.0,10.0,1.0,0,true) = ";
            for (it2 = path3.begin(); it2 != path3.end(); ++it2) {
                std::cout << "[" << it2->x() << ", " << it2->y() << "] ";
            }
            std::cout << std::endl << std::endl;


            std::vector< omni::geometry::point2d< int > > rect = omni::geometry::path::square<std::vector, int>(0, 0, 10, 1);
            std::vector< omni::geometry::point2d< int > >::iterator ir;
            std::cout << "get_square(0,0,10,1) = ";
            for (ir = rect.begin(); ir != rect.end(); ++ir) {
                std::cout << "[" << ir->x() << ", " << ir->y() << "] ";
            }
            std::cout << std::endl << std::endl;

            rect = omni::geometry::path::rectangle<std::vector, int>(0, 0, 10, 5, 1);
            std::cout << "get_rect(0,0,10,5,1) = ";
            for (ir = rect.begin(); ir != rect.end(); ++ir) {
                std::cout << "[" << ir->x() << ", " << ir->y() << "] ";
            }
            std::cout << std::endl << std::endl;

            rect = omni::geometry::path::square<std::vector, int>(0, 0, 10, 1, true, false);
            std::cout << "get_square(0,0,10,1,true,false) = ";
            for (ir = rect.begin(); ir != rect.end(); ++ir) {
                std::cout << "[" << ir->x() << ", " << ir->y() << "] ";
            }
            std::cout << std::endl << std::endl;

            rect = omni::geometry::path::square<std::vector, int>(0, 0, 10, 1, false, true);
            std::cout << "get_square(0,0,10,1,false,true) = ";
            for (ir = rect.begin(); ir != rect.end(); ++ir) {
                std::cout << "[" << ir->x() << ", " << ir->y() << "] ";
            }
            std::cout << std::endl << std::endl;

            rect = omni::geometry::path::square<std::vector, int>(0, 0, 10, 1, true, true);
            std::cout << "get_square(0,0,10,1,true,true) = ";
            for (ir = rect.begin(); ir != rect.end(); ++ir) {
                std::cout << "[" << ir->x() << ", " << ir->y() << "] ";
            }
            std::cout << std::endl << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
