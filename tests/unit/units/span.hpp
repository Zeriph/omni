#if defined(OMNI_UTUA) || defined(OMNI_UT_TIMESPAN)

#define UT_ROOT_NS chrono
#define UT_NAME timespan
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() {
            print_info(omni::chrono::span_t);
            print_info(omni::chrono::unsigned_span_t);
        }
        
        void base_test()
        {
            omni::chrono::span_t ts(10000000000);
            std::cout << ts << std::endl;
        }
        
    //private:
        
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TIMESPAN
