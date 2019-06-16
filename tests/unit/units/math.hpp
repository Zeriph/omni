#if defined(OMNI_UTUA) || defined(OMNI_UT_TIMESPAN)

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
            printv("rad_to_deg(2.4) = ", omni::math::rad_to_deg(2.4));
            //double deg_to_red(double deg)
            printv("deg_to_red(2.4) = ", omni::math::deg_to_rad(2.4));
            //template < typename T > T delta(const T& a, const T& b)
            printv("delta(2.2,1.2) = ", omni::math::delta(2.2, 1.2));
            printv("delta(2,1) = ", omni::math::delta(2, 1));
            //template < typename T > T delta_squared(const T& a, const T& b)
            printv("delta_squared(2.2,1.2) = ", omni::math::delta_squared(2.2, 1.2));
            printv("delta_squared(2,1) = ", omni::math::delta_squared(2, 1));
            //template < typename T > double area_of_circle(T radius)
            printv("area_of_circle(4.56) = ", omni::math::area_of_circle(4.56));
            //template < typename T > double area_circle_sector(T radius, T degrees)
            printv("area_circle_sector(4.56, 192) = ", omni::math::area_circle_sector(4.56, 192.0));
            //template < typename T > double radius_from_area(T area)
            printv("radius_from_area(374.52) = ", omni::math::radius_from_area(374.52));
            //template < typename T > double distance_between_2_points(T start_x, T start_y, T end_x, T end_y)
            printv("distance_between_2_points(2,2,9,6) = ", omni::math::distance_between_2_points(2,2,9,6));
            //template < typename T > double lerp_y(T x1, T y1, T x2, T y2, T x)
            printv("lerp_y(2,2,9,6,4) = ", omni::math::lerp_y(2,2,9,6,4));
            //template < typename T > double lerp_x(T x1, T y1, T x2, T y2, T y)
            printv("lerp_x(2,2,9,6,3) = ", omni::math::lerp_x(2,2,9,6,3));

            //template <> inline bool are_equal<int64_t>(int64_t x, int64_t y) { return x == y; }
            printv("are_equal(4.0, 2.4) = ", b2s(omni::math::are_equal(4.0, 2.4)));
            printv("are_equal(4, 2) = ", b2s(omni::math::are_equal(4, 2)));
            printv("are_equal(4, 4) = ", b2s(omni::math::are_equal(4, 4)));
            printv("are_equal(4.001, 4.001) = ", b2s(omni::math::are_equal(4.001, 4.001)));
            printv("are_equal(-2, -2) = ", b2s(omni::math::are_equal(-2, -2)));
            //template < typename T > inline double distance_between_2_points(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            printv("distance_between_2_points(2,2,2,9,6,9) = ", omni::math::distance_between_2_points(2,2,2,9,6,9));
            //template < typename T > inline double distance_between_2_points(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            omni::math::dimensional<int, 2> x1;
            omni::math::dimensional<int, 2> x2;
            x1[0] = 2; x1[1] = 2;
            x2[0] = 9; x2[1] = 6;
            printv("distance_between_2_points(2,2,9,6) = ", omni::math::distance_between_2_points(x1, x2));
            //template < typename T > inline double distance_between_2_points(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            omni::math::dimensional<int, 3> xx1;
            omni::math::dimensional<int, 3> xx2;
            xx1[0] = 2; xx1[1] = 2; xx1[2] = 2;
            xx2[0] = 9; xx2[1] = 6; xx2[2] = 9;
            printv("distance_between_2_points(2,2,2,9,6,9) = ", omni::math::distance_between_2_points(xx1, xx2));
            //template < typename T > inline double liner_interpolation_y(T x1, T y1, T x2, T y2, T x)
            printv("liner_interpolation_y(2,2,9,6,4) = ", omni::math::liner_interpolation_y(2,2,9,6,4));
            //template < typename T > inline double lerp_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
            printv("lerp_y(2,2,9,6,4) = ", omni::math::lerp_y(x1, x2, 4));
            //template < typename T > inline double liner_interpolation_y(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T x)
            printv("liner_interpolation_y(2,2,9,6,4) = ", omni::math::liner_interpolation_y(x1, x2, 4));
            //template < typename T > inline double liner_interpolation_x(T x1, T y1, T x2, T y2, T y)
            printv("liner_interpolation_x(2,2,9,6,3) = ", omni::math::liner_interpolation_x(2,2,9,6,3));
            //template < typename T > inline double lerp_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
            printv("lerp_x(2,2,9,6,3) = ", omni::math::lerp_x(x1, x2, 3));
            //template < typename T > inline double liner_interpolation_x(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end, T y)
            printv("lerp_x(2,2,9,6,3) = ", omni::math::liner_interpolation_x(x1, x2, 3));
            //template < typename T > inline void midpoint(T start_x, T start_y, T end_x, T end_y, T& mid_x, T& mid_y)
            double mid_x = 0.0;
            double mid_y = 0.0;
            omni::math::midpoint(2.0, 2.0, 9.0, 6.0, mid_x, mid_y);
            printv("midpoint(2,2,9,6) = {", mid_x << "," << mid_y << "}");
            //template < typename T > inline void midpoint(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z, T& mid_x, T& mid_y, T& mid_z)
            double mid_z = 0.0;
            omni::math::midpoint3d(2.0, 2.0, 2.0, 9.0, 6.0, 9.0, mid_x, mid_y, mid_z);
            printv("midpoint(2,2,2,9,6,9) = {", mid_x << "," << mid_y << "," << mid_z << "}");
            //template < typename T > inline omni::math::dimensional<T, 2> midpoint(T start_x, T start_y, T end_x, T end_y)
            omni::math::dimensional<int, 2> m1 = omni::math::midpoint(2, 2, 9, 6);
            printv("midpoint(2,2,9,6) = ", m1);
            //template < typename T > inline omni::math::dimensional<T, 2> midpoint(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            omni::math::dimensional<int, 2> m2 = omni::math::midpoint(x1, x2);
            printv("midpoint(2,2,9,6) = ", m2);
            //template < typename T > inline omni::math::dimensional<T, 3> midpoint(T start_x, T start_y, T start_z, T end_x, T end_y, T end_z)
            omni::math::dimensional<int, 3> mm1 = omni::math::midpoint3d(2, 2, 2, 9, 6, 9);
            printv("midpoint(2,2,2,9,6,9) = ", mm1);
            //template < typename T > inline omni::math::dimensional<T, 3> midpoint(const omni::math::dimensional<T, 3>& start, const omni::math::dimensional<T, 3>& end)
            omni::math::dimensional<int, 3> mm2 = omni::math::midpoint3d(xx1, xx2);
            printv("midpoint(2,2,2,9,6,9) = ", mm2);
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
            printv("quad(5,6,1) [-0.2|-1] = {", xp << "," << xm << "}");
            //template < typename T > inline omni::math::dimensional<T, 2> quadratic(T a, T b, T c)
            omni::math::dimensional<double, 2> q = omni::math::quadratic(5.0, 6.0, 1.0);
            printv("quad(5,6,1) [-0.2|-1] = {", q[0] << "," << q[1] << "}");
            //template < typename T > inline double slope(T start_x, T start_y, T end_x, T end_y)
            printv("slope(2,2,9,6) = ", omni::math::slope(2,2,9,6));
            //template < typename T > inline double slope(const omni::math::dimensional<T, 2>& start, const omni::math::dimensional<T, 2>& end)
            printv("slope(2,2,9,6) = ", omni::math::slope(x1, x2));
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
