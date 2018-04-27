#if defined(OMNI_UTUA) || defined(OMNI_UT_BITS)

#define UT_NAME bits
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
            printv("omni::bits::size<int>() = ", omni::bits::size<int>());
            printv("omni::bits::size<long>() = ", omni::bits::size<long>());
            printv("omni::bits::size<float>() = ", omni::bits::size<float>());
        }
        
        void base_test()
        {
            int flag = 4;
            int a = 10;
            int x = 0;
            float b = 1.5;
            std::size_t c = 100;
            
            printv("omni::bits::size<int>() = ", omni::bits::size<int>());
            if (omni::bits::has_flag(x, flag)) { printl("x has flag"); } else { printl("x NOT has flag"); }
            if (!omni::bits::has_flag(a, flag)) { x = omni::bits::set_flag(a, flag); }
            if (omni::bits::has_flag(x, flag)) { printl("x has flag"); } else { printl("x NOT has flag"); }
            if (omni::bits::has_flag(a, flag)) { printl("a has flag"); } else { printl("a NOT has flag"); }
            omni::bits::unset_flag(a, flag);
            if (omni::bits::has_flag(a, flag)) { printl("a has flag"); } else { printl("a NOT has flag"); }
            omni::bits::set_flag(a, flag, true);
            if (omni::bits::has_flag(a, flag)) { printl("a has flag"); } else { printl("a NOT has flag"); }
            
            
            /*
            template < typename T >
            inline bool is_set_nc(const T& t, unsigned short n)
            
            template < typename T >
            inline T& set_nc(T& t, unsigned short n, bool s)
            
            template < typename T >
            inline T& set_nc(T& t, unsigned short n)
            
            template < typename T >
            inline T& unset_nc(T& t, unsigned short n)
            
            template < typename T >
            inline bool is_set(const T& t, unsigned short n)
            
            template < typename T >
            inline T& set(T& t, unsigned short n, bool s)
            
            template < typename T >
            inline T& set(T& t, unsigned short n)
            
            template < typename T >
            inline T& unset(T& t, unsigned short n)
            
            template < typename T >
            inline void xor_swap(T& a, T& b)
            
            template < typename T >
            inline std::size_t size()
            
            template < typename T >
            inline std::size_t size(const T& obj)*/
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_BITS
