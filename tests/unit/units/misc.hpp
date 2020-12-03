#if defined(OMNI_UT_MISC) || defined(OMNI_UTUA)

#define UT_NAME misc
#define UT_DESC "misc unit test"
#include <utdefs/unit_test.hpp>

#define CONST_OUT(v) omni::out << OMNI_DEF2STR(v) << " = " << v << std::endl

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
            std::cout << "cout" << std::endl;
            std::wcout << "wcout" << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_MISC
