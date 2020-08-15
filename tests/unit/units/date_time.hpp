#if defined(OMNI_UTUA) || defined(OMNI_UT_TIMESPAN)

#define UT_ROOT_NS chrono
#define UT_NAME date_time
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
            print_info(omni::chrono::date_time);
        }
        
        void base_test()
        {
            std::cout << omni::chrono::date_time::now() << std::endl;
        }
        
    //private:
        
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMESPAN
