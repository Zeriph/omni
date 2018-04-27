#if defined(OMNI_UTUA) || defined(OMNI_UT_TESTNAME)

#define UT_NAME testname
// #define UT_DESC "Some description" // define if you want a different description
// #define UT_ISNS true // mark if UT_NAME is a namespace
// #define UT_ROOT_NS xxxx // mark if the root NS is !omni
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            #error MUST DEFINE TESTS
            M_LIST_ADD(a_test, "tests some other functionality");
        }
        
        UT_CLASS_DTOR() {}

        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::x tval;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
