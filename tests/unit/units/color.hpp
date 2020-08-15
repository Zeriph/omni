#if defined(OMNI_UTUA) || defined(OMNI_UT_COLOR)

#define UT_NAME color
#define UT_ROOT_NS drawing
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(colors_test, "tests the different colors");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            #if defined(OMNI_TYPE_INFO)
                printl("sizeof(omni::drawing::color_t) = " << sizeof(omni::drawing::color_t) << ", hash: " << omni::type_id<omni::drawing::color_t>());
            #else
                printl("sizeof(omni::drawing::color_t) = " << sizeof(omni::drawing::color_t));
            #endif
        }
        
        void base_test()
        {
            omni::drawing::color_t red = omni::drawing::known_colors::red();
            omni::drawing::color_t blue = omni::drawing::known_colors::BLUE;
            printl("RED--");
            implicit(red);
            printl("BLUE--");
            implicit(blue);
            blue = red;
            printl("BLUE = RED--");
            implicit(blue);
            printl("red == blue? " << ((red == blue) ? "true" : "false"));
            blue = omni::drawing::known_colors::blue();
            
            omni::drawing::color_t purple = (red + blue);
            omni::drawing::color_t::rgb_t num = red.to_rgb() + blue.to_rgb();
            printl("red + blue = " << purple);
            printl("ir + ib = " << num);
            printl("PURPLE--");
            implicit(purple);
            printl("NUMPLE--");
            implicit(num); // purple
            num ^= std::numeric_limits<omni::drawing::color_t::rgb_t>::max();
            printl("GREEN (LIME)--");
            implicit(num); // green
            purple += num;
            printl("PURPLE + GREEN--");
            implicit(purple); // white

            printl("PURPLE, SET ALPHA--");
            purple = red + blue;
            purple.set_alpha(0.42f);
            purple.set_calculate_alpha(true);
            implicit(purple);
            purple -= red;
            implicit(purple);
        }

        void colors_test()
        {
            printl("color_t::bits = " << omni::drawing::color_t::bits());
            printl("color64_t::bits = " << omni::drawing::color64_t::bits());
            printl("red = " << omni::drawing::known_colors::red());
            printl("lime = " << omni::drawing::known_colors::lime());
            printl("blue = " << omni::drawing::known_colors::blue());
            printl("color_t::from_rgb(0x04CAFF) = " << omni::drawing::color_t::from_rgb(0x04CAFF));
            implicit(0xFFCA42);
        }
    
    private:
        void implicit(const omni::drawing::color_t& c)
        {
            std::cout <<
            "color   = " << c << std::endl <<
            "known   = " << (omni::drawing::known_colors::is_valid(c.to_rgb()) ? "true" : "false") << std::endl <<
            "to rgb  = " << c.to_rgb() << std::endl <<
            "to rgba = " << c.to_rgba() << std::endl <<
            "to argb = " << c.to_argb() << std::endl <<
            "frm clr = " << omni::drawing::known_colors::to_string(omni::drawing::known_colors::from_color(c)) << std::endl <<
            "H|S|L   = " << c.hue() << "° | " << static_cast<int>(c.saturation() * 100) << "% | " << static_cast<int>(c.brightness() * 100) << "%" << std::endl << 
            "calc_a  = " << (c.calculate_alpha() ? "true" : "false") << std::endl <<
            "bitsize = " << c.bit_size() << std::endl << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
