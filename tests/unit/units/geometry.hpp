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
            M_LIST_ADD(triangle, "test the functionality in omni::geometry::triangle via direct use");
            M_LIST_ADD(util, "tests util class");
            M_LIST_ADD(vector, "tests the vector classes");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            UT_INFO_TEST();
        }
        
        void base_test()
        {
            move_test(); printl("");
            path_test(); printl("");
            util(); printl("");
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

        void triangle()
        {
            omni::geometry::triangle32_t t1(0,0, 0,2, 2,0);
            omni::geometry::triangle_t t2(2.5,2.5, 6.9,8.9, 5,3, omni::geometry::triangle_side::A);
            printl("to_string | side_a | side_b | side_c | angle_a | angle_b | angle_c | base | base_side | height | semiperimeter | perimeter | measure | incenter | circumcenter | centroid");
            ptri(t1, "t1");
            ptri(t2, "t2");
            printl("\n\nDeflating t2 50%");
            t2.deflate(50.0);
            ptri(t2, "t2");
            printl("\nInflating t2 200%");
            t2.inflate(200.0);
            ptri(t2, "t2");
            printl("\n\nRotating t2 90 degrees CW");
            t2.rotate_centroid(90.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t2, "t2");
            printl("\nRotating t2 90 degrees CCW");
            t2.rotate_centroid(90.0, omni::math::rotation_direction::COUNTER_CLOCKWISE);
            ptri(t2, "t2");
            printl("\nRotating t2 47.25 degrees CCW");
            t2.rotate_centroid(47.25, omni::math::rotation_direction::COUNTER_CLOCKWISE);
            ptri(t2, "t2");
            printl("\n\nRotating t1 90 degrees CCW");
            t1.rotate_centroid(90.0, omni::math::rotation_direction::COUNTER_CLOCKWISE);
            ptri(t1, "t1");
            printl("\nRotating t1 90 degrees CW");
            t1.rotate_centroid(90.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t1, "t1");
            printl("\nRotating t1 47.25 degrees CCW");
            t1.rotate_centroid(47.25, omni::math::rotation_direction::COUNTER_CLOCKWISE);
            ptri(t1, "t1");

            
            omni::geometry::triangle_t t3(0,0, 0,2, 2,0);
            omni::geometry::triangle_t t4(2,2, 6,8, 5,3, omni::geometry::triangle_side::A);
            omni::geometry::triangle_t t5(t3);
            omni::geometry::triangle_t t6(t3);
            ptri(t3, "t3");
            ptri(t4, "t4");
            t4.intersect(t3);
            ptri(t4, "t4");

            if (t4 != t3) {
                t4 = t3;
            }
            ptri(t4, "t4");

            ptri(t5, "t5");
            t5.translate_xy(5,5);
            ptri(t5, "t5");

            if (t5 > t6) {
                printl("t5 > t6");
            } else {
                printl("t5 < t6");
            }

            omni::geometry::pointD_t pt(10, 10);
            ptri(t6, "t6");
            t6 += pt;
            ptri(t6, "t6");
            if (t5 < t6) {
                printl("t5 < t6");
            } else {
                printl("t5 > t6");
            }

            t5 -= pt;
            ptri(t5, "t5");

            ptri((t3 + pt), "t3+pt");
            ptri((t6 - pt), "t6-pt");
            
            t5.rotate_on_a(120.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.rotate_on_b(120.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.rotate_on_c(120.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.rotate_circumcenter(90.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.rotate_incenter(90.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.rotate_origin(90.0, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.rotate_point(43, 2, 3, omni::math::rotation_direction::CLOCKWISE);
            ptri(t5, "t5");

            t5.reflect();
            ptri(t5, "t5");

            t5.swap(t6);
            ptri(t5, "t5");

            t5.translate_xy(15, 15);
            ptri(t5, "t5");

            t5.translate_angle(25, 62);
            ptri(t5, "t5");
        }

        void util()
        {
            // template < typename T > inline omni::geometry::point2d<T> point_on_circle(T degrees, T radius, T center_x, T center_y)
            // template <> inline omni::geometry::point2d<uint8_t> point_on_circle<uint8_t>(uint8_t degrees, uint8_t radius, uint8_t center_x, uint8_t center_y)
            printl(omni::geometry::point_on_circle(25.6, 12.2, 12.0, 15.0));
        }

        void vector()
        {
            omni::geometry::vector2F_t a(3,2);
            omni::geometry::vector2F_t b(5,6);

            std::cout << "vector a(" << a << ") - b(" << b << ") = " << (a - b) << std::endl;

        }

    private:

        static void path_test_sig(int sig)
        {
            if (sig == SIGSEGV) { exit(0); }
        }

        template < typename T >
        void ptri(omni::geometry::triangle<T> tri, const char* nm)
        {
            std::cout << nm << ": " << tri << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
