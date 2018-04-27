#if defined(OMNI_UTUA) || defined(OMNI_UT_SMART_PTR)

#define UT_NAME smart_ptr
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR() {}
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            print_info(omni::smart_ptr<int>);
            print_info(omni::smart_ptr_safe<int>);
        }
        
        void base_test()
        {
            omni::smart_ptr<int> t(new int(10));
            omni::smart_ptr<int> t1(new int[10]()); // UNDEFINED
            
            #if defined(OMNI_DISPOSE_EVENT)
                t.disposing += &UT_CNAME::disposing;
                t1.disposing += &UT_CNAME::disposing;
            #endif
            
            omni::out << "t = " << *t << std::endl;
            *t = 20;
            omni::out << "t = " << *t << std::endl;
        }
    
    private:
        static void disposing(const omni::smart_ptr<int>& sender)
        {
            omni::out << "Disposing " << *sender << std::endl;
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SMART_PTR
