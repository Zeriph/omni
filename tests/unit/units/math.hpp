#if defined(OMNI_UTUA) || defined(OMNI_UT_MATH)

#define UT_ROOT_NS math
#define UT_NAME math
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            printv("omni::math::PI = ", omni::math::PI);
            printv("omni::math::PI_L = ", omni::math::PI_L);
            printv("omni::math::PI_F = ", omni::math::PI_F);
            printv("omni::math::PI_180 = ", omni::math::PI_180);
            printv("omni::math::PI_L_180 = ", omni::math::PI_L_180);
            printv("omni::math::PI_F_180 = ", omni::math::PI_F_180);
            for (int i = 0; i < 361; ++i) {
                printl("RADS[" << i << "] = " << omni::math::RADS[i]);
                printl("RADS_SIN[" << i << "] = " << omni::math::RADS_SIN[i]);
                printl("RADS_COS[" << i << "] = " << omni::math::RADS_COS[i]);
            }
        }
        
        void base_test()
        {
            //double rad_to_deg(double rad)
            printve("rad_to_deg(1.01) = ", omni::math::rad_to_deg(1.01), (57.868758));
            //double deg_to_rad(double deg)
            printve("deg_to_rad(57.868758) = ", omni::math::deg_to_rad(57.868758), (1.01));
            //template < typename T > T delta(const T& a, const T& b)
            printve("delta(2.2,1.2) = ", omni::math::delta(2.2, 1.2), (1.0));
            printve("delta(2,1) = ", omni::math::delta(2, 1), 1);
            //template < typename T > T delta_squared(const T& a, const T& b)
            printve("delta_squared(4.2,1.2) = ", omni::math::delta_squared(4.2, 1.2), (9.0));
            printve("delta_squared(4,1) = ", omni::math::delta_squared(4, 1), (9));
            //template < typename T > double area_of_circle(T radius)
            printve("area_of_circle(3) = ", omni::math::area_of_circle(3), (28.27));
            //template < typename T > double area_circle_sector(T radius, T degrees)
            printv("area_circle_sector(3, 192) = ", omni::math::area_circle_sector(3, 192));
            //template < typename T > double radius_from_area(T area)
            printve("radius_from_area(28.27) = ", omni::math::radius_from_area(28.27), (3));
            //template < typename T > double distance_between_2_points(T start_x, T start_y, T end_x, T end_y)
            printve("distance_between_2_points(3,2,9,7) = ", omni::math::distance_between_2_points(3,2,9,7), (7.8102));
            //template < typename T > double lerp_y(T x1, T y1, T x2, T y2, T x)
            printv("lerp_y(3,2,9,7,4) = ", omni::math::lerp_y(3,2,9,7,4));
            //template < typename T > double lerp_x(T x1, T y1, T x2, T y2, T y)
            printv("lerp_x(3,2,9,7,2) = ", omni::math::lerp_x(3,2,9,7,2));

            //template <> inline bool are_equal<int64_t>(int64_t x, int64_t y) { return x == y; }
            printve("are_equal(4.0, 2.4) = ", b2s(omni::math::are_equal(4.0, 2.4)), "false");
            printve("are_equal(4, 2) = ", b2s(omni::math::are_equal(4, 2)), "false");
            printve("are_equal(4, 4) = ", b2s(omni::math::are_equal(4, 4)), "true");
            printve("are_equal(4.001, 4.001) = ", b2s(omni::math::are_equal(4.001, 4.001)), "true");
            printve("are_equal(-2, -2) = ", b2s(omni::math::are_equal(-2, -2)), "true");
            //template < typename T > inline double distance_between_2_points(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            printve("distance_between_2_points(8,2,6,3,5,7) = ", omni::math::distance_between_2_points(8,2,6,3,5,7), (5.9));
            //template < typename T > inline double distance_between_2_points(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 3; x1[1] = 2;
            x2[0] = 9; x2[1] = 7;
            printve("distance_between_2_points(x1{3,2},x2{9,7}) = ", omni::math::distance_between_2_points(x1, x2), (7.8102));
            //template < typename T > inline double distance_between_2_points(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            omni::math::dimensional<int, 3> xx1;
            omni::math::dimensional<int, 3> xx2;
            xx1[0] = 3; xx1[1] = 2; xx1[2] = 1;
            xx2[0] = 9; xx2[1] = 7; xx2[2] = 1;
            printve("distance_between_2_points(x1{3,2,1},x2{9,7,1}) = ", omni::math::distance_between_2_points(xx1, xx2), (7.8102));
            //template < typename T > inline double liner_interpolation_y(T x1, T y1, T x2, T y2, T x)
            printv("liner_interpolation_y(3.0,2.0,9.0,7.0,4.0) = ", omni::math::liner_interpolation_y(3.0,2.0,9.0,7.0,4.0));
            //template < typename T > inline double liner_interpolation_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
            printv("liner_interpolation_y(3,2,9,7,4) = ", omni::math::liner_interpolation_y(x1, x2, 4));
            //template < typename T > inline double lerp_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
            printv("lerp_y(3,2,9,7,4) = ", omni::math::lerp_y(x1, x2, 4));
            //template < typename T > inline double liner_interpolation_x(T x1, T y1, T x2, T y2, T y)
            printv("liner_interpolation_x(3.0,2.0,9.0,7.0,2.8333) = ", omni::math::liner_interpolation_x(3.0,2.0,9.0,7.0,2.8333));
            //template < typename T > inline double liner_interpolation_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
            printv("liner_interpolation_x(3,2,9,7,2) = ", omni::math::liner_interpolation_x(x1, x2, 2));
            //template < typename T > inline double lerp_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
            printv("lerp_x(3,2,9,7,2) = ", omni::math::lerp_x(x1, x2, 2));
            //template < typename T > inline void midpoint(T start_x, T start_y, T end_x, T end_y, T& mid_x, T& mid_y)
            double mid_x = 0.0;
            double mid_y = 0.0;
            omni::math::midpoint(6.4, 3.0, -10.7, 4.0, mid_x, mid_y);
            printve("midpoint(6.4,3,-10.7,4) = {", mid_x << "," << mid_y << "}", ("{-2.15, 3.5}"));
            //template < typename T > inline void midpoint(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z, T& mid_x, T& mid_y, T& mid_z)
            double mid_z = 0.0;
            omni::math::midpoint3d(3.0, 2.0, 1.0, 9.0, 7.0, 1.0, mid_x, mid_y, mid_z);
            printv("midpoint(3,2,1,9,7,1) = {", mid_x << "," << mid_y << "," << mid_z << "}");
            //template < typename T > inline omni::math::dimensional<T, 2> midpoint(T start_x, T start_y, T end_x, T end_y)
            omni::math::dimensional<int, 2> m1 = omni::math::midpoint(3, 2, 9, 7);
            printv("midpoint(3,2,9,7) = ", m1);
            //template < typename T > inline omni::math::dimensional<T, 2> midpoint(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            omni::math::dimensional<int, 2> m2 = omni::math::midpoint(x1, x2);
            printv("midpoint(3,2,9,7) = ", m2);
            //template < typename T > inline omni::math::dimensional<T, 3> midpoint(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            omni::math::dimensional<int, 3> mm1 = omni::math::midpoint3d(3, 2, 1, 9, 7, 1);
            printv("midpoint(3,2,1,9,7,1) = ", mm1);
            //template < typename T > inline omni::math::dimensional<T, 3> midpoint(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            omni::math::dimensional<int, 3> mm2 = omni::math::midpoint3d(xx1, xx2);
            printv("midpoint(3,2,1,9,7,1) = ", mm2);
            //template < typename T > inline omni::math::ordinal_name octant(T x, T y, T z)
            printv("octant(1,1,1) = ", omni::math::octant(1,1,1));
            printv("octant(-1,1,1) = ", omni::math::octant(-1,1,1));
            printv("octant(-1,-1,1) = ", omni::math::octant(-1,-1,1));
            printv("octant(1,-1,1) = ", omni::math::octant(1,-1,1));
            printv("octant(1,1,-1) = ", omni::math::octant(1,1,-1));
            printv("octant(-1,1,-1) = ", omni::math::octant(-1,1,-1));
            printv("octant(-1,-1,-1) = ", omni::math::octant(-1,-1,-1));
            printv("octant(1,-1,-1) = ", omni::math::octant(1,-1,-1));
            printv("octant(1,0,0) = ", omni::math::octant(1,0,0));
            printv("octant(0,1,0) = ", omni::math::octant(0,1,0));
            printv("octant(0,0,1) = ", omni::math::octant(0,0,1));
            //template < typename T > inline omni::math::ordinal_name octant(const omni::math::dimensional<T, 3>& point)
            printv("octant(2,2,2) = ", omni::math::octant(xx1));
            //template < typename T > inline omni::math::ordinal_name quadrant(T x, T y)
            printv("quadrant(1,1) = ", omni::math::quadrant(1,1));
            printv("quadrant(-1,1) = ", omni::math::quadrant(-1,1));
            printv("quadrant(-1,-1) = ", omni::math::quadrant(-1,-1));
            printv("quadrant(1,-1) = ", omni::math::quadrant(1,-1));
            printv("quadrant(1,0) = ", omni::math::quadrant(1,0));
            printv("quadrant(0,1) = ", omni::math::quadrant(0,1));
            printv("quadrant(0,0) = ", omni::math::quadrant(0,0));
            //template < typename T > inline omni::math::ordinal_name quadrant(const omni::math::dimensional<T, 2>& point)
            printv("quadrant(2,2) = ", omni::math::quadrant(x1));
            //template < typename T > inline void quadratic(T a, T b, T c, T& x_plus, T& x_minus)
            double xp = 0.0;
            double xm = 0.0;
            omni::math::quadratic(5.0, 6.0, 1.0, xp, xm);
            printve("quad(5,6,1) = {", xp << "," << xm << "}", "[-0.2|-1]");
            //template < typename T > inline omni::math::dimensional<T, 2> quadratic(T a, T b, T c)
            omni::math::dimensional<double, 2> q = omni::math::quadratic(5.0, 6.0, 1.0);
            printve("quad(5,6,1) = {", q[0] << "," << q[1] << "}", "[-0.2|-1]");
            //template < typename T > inline double slope(T start_x, T start_y, T end_x, T end_y)
            printve("slope(1,2,4,3) = ", omni::math::slope(1,2,4,3), "1/3");
            //template < typename T > inline double slope(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            printv("slope(3,2,9,7) = ", omni::math::slope(x1, x2));
            //template < typename T > inline T summation(T index, T end, const omni::delegate1<T, T>& sum)
            omni::delegate1<int, int> d = &summer;
            printv("summation(2,7,(2k+3)) = ", omni::math::summation(2, 7, d));
        }
    private:
        static int summer(int val)
        {
            return (2*val) + 3;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMESPAN
