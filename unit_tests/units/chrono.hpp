#if defined(OMNI_UTUA) || defined(OMNI_UT_CHRONO)

#define UT_NAME chrono
#define UT_ISNS true // mark if UT_NAME is a namespace
// #define UT_DESC "Some description" // define if you want a different description
// #define UT_ROOT_NS xxxx // mark if the root NS is !omni
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            //M_LIST_ADD(clock_test, "tests some other functionality");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            print_info(omni::chrono::time);
            print_info(omni::chrono::span);
            print_info(omni::chrono::tick_t);
        }
        
        void base_test()
        {
            omni::chrono::tick_t start = omni::chrono::monotonic_tick();
            printl("got start, sleeping 1s");
            omni::sync::sleep(1000);
            unsigned long ms = omni::chrono::elapsed_ms(start);
            printv("start elapsed ms: ", ms);
            omni::chrono::tick_t current = omni::chrono::monotonic_tick();
            omni::sync::sleep(1000);
            ms = omni::chrono::elapsed_ms(current);
            printv("current elapsed ms: ", ms);
            ms = omni::chrono::elapsed_ms(start);
            printv("start elapsed ms: ", ms);
            ms = omni::chrono::elapsed_ms(start, current);
            printv("start-current elapsed ms: ", ms);
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_CHRONO
