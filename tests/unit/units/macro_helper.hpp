#if defined(OMNI_UTUA) || defined(OMNI_UT_MACRO_HELPER)

#define UT_NAME macro_helper
#define UT_DESC "Tests the various helper macro's defined in the library"
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() {}
        
        void base_test()
        {
            uint32_t count = OMNI_MACRO_ARG_COUNT(1, 2, 3, 4, 5);
            test("count", count, "5");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_GENERIC_PTR
