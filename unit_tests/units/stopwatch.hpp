#if defined(OMNI_UTUA) || defined(OMNI_UT_STOPWATCH)

#define UT_NAME stopwatch
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(bool_test, "tests the bool assignment ability");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::stopwatch sw;
            printl("start");
            sw.start();
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (~1000): ", sw.elapsed_ms());
            
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printl("stop");
            sw.stop();
            printv("elapsed ms (~2000): ", sw.elapsed_ms());
            
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (no change ~2000): ", sw.elapsed_ms());
            
            printl("restart");
            sw.restart();
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (~1000): ", sw.elapsed_ms());
            
            printl("reset (0's out, no restart)");
            sw.reset();
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (0): ", sw.elapsed_ms());
            
            printl("start with 1s offset");
            sw.start(1000);
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (1s sleep+1s offset ~2000): ", sw.elapsed_ms());
            
            printl("restart");
            sw.restart();
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (~1000): ", sw.elapsed_ms());
            
            printl("reset (0's out, no restart)");
            sw.reset();
            printl("start with 2s offset");
            sw.start(2000);
            printl("sleep 2s");
            omni::sync::sleep(2000);
            printv("elapsed ms (2s sleep+2s offset ~4000): ", sw.elapsed_ms());
            
            
            printl("reset (0's out, no restart)");
            sw.reset();
            printl("start with 3s offset");
            sw.start(3000);
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (1s sleep+3s offset ~4000): ", sw.elapsed_ms());

        }
        
        void bool_test()
        {
            omni::stopwatch sw;
            printl("start");
            sw = true;
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (~1000): ", sw.elapsed_ms());
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printl("stop");
            sw = false;
            printv("elapsed ms (~2000): ", sw.elapsed_ms());
            printl("sleep 1s");
            omni::sync::sleep(1000);
            printv("elapsed ms (~2000): ", sw.elapsed_ms());
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_STOPWATCH
