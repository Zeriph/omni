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
            printv("deg_to_red(2.4) = ", omni::math::deg_to_red(2.4));
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
        }
        
    //private:
        
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMESPAN
