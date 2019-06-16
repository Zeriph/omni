#if defined(OMNI_UTUA) || defined(OMNI_UT_GENERIC_PTR)

#define UT_NAME generic_ptr
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
            print_info(omni::generic_ptr);
            print_info(omni::generic_ptr_safe);
        }
        
        void base_test()
        {
            int x = 42;
            int y = 42;
            omni::generic_ptr gp = &x;
            omni::ptr_t gp2 = &x;
            omni::ptr_t gp3 = &y;
            if (gp == gp2) { printl("gp == gp2!!"); }
            if (gp == gp3) { printl("gp == gp3!!"); }
            
            printv("&gp = ", &gp);
            
            int *iv = gp;
            printv("iv == ", *iv);
            
            int rv = *static_cast<int*>(gp);
            printv("rv == ", rv);
            
            void *vp1 = gp;
            printv("vp1 == ", *static_cast<int*>(vp1));
            
            try {
                float *fv = gp;
                printl("bad cast exception thrown before this line");
            } catch (std::exception& ex) {
                printv("exception happened: ", ex.what());
            }
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_GENERIC_PTR

