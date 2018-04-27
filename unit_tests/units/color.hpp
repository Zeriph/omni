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

        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::drawing::color c;
        }

        void colors_test()
        {
            
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
