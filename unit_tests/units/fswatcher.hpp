#if defined(OMNI_UTUA) || defined(OMNI_UT_FSWATCHER)

#define UT_NAME fswatcher
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            //omni::fswatcher* obj = new omni::fswatcher();
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_FSWATCHER
