#if !defined(OMNI_UNIT_TEST_HPP)
#define OMNI_UNIT_TEST_HPP

#include <map>

#define OMNI_UTDBGOUT omni::out

#define b2s(b) ((b) ? "true" : "false")
#define B2S(b) (b ? "true" : "false")

#define print(...) OMNI_UTDBGOUT << __VA_ARGS__
#define printl(...) OMNI_UTDBGOUT << __VA_ARGS__ << std::endl
#define printv(m, v) OMNI_UTDBGOUT << m << v << std::endl
#define printsw(v) case v: printl(#v); break
#define printswe(v, e) case v: OMNI_UTDBGOUT << e << #v << std::endl; break
//#define printve(m, v, e) OMNI_UTDBGOUT << m << " = " << v << " -- expected: " << e << std::endl

#define cprint(...) std::cout << __VA_ARGS__
#define cprintl(...) std::cout << __VA_ARGS__ << std::endl
#define cprintv(m, v) std::cout << m << v << std::endl
#define cprintsw(v) case v: cprintl(#v); break
#define cprintswe(v, e) case v: std::cout << e << #v << std::endl; break
//#define cprintve(m, v, e) std::cout << m << " = " << v << " -- expected: " << e << std::endl

#define wprint(...) std::wcout << __VA_ARGS__
#define wprintl(...) std::wcout << __VA_ARGS__ << std::endl
#define wprintv(m, v) std::wcout << m << v << std::endl
#define wprintsw(v) case v: wprintl(#v); break
#define wprintswe(v, e) case v: std::wcout << e << #v << std::endl; break
//#define wprintve(m, v, e) std::wcout << m << " = " << v << " -- expected: " << e << std::endl

#if defined(OMNI_TYPE_INFO)
    #define print_info(...) printl("sizeof(" OMNI_DEF2STR( __VA_ARGS__ ) ") = " << sizeof( __VA_ARGS__ ) << ", hash: " << omni::type_id< __VA_ARGS__ >())
#else
    #define print_info(...) printl("sizeof(" OMNI_DEF2STR( __VA_ARGS__ ) ") = " << sizeof( __VA_ARGS__ ))
#endif
#define print_sizeof(...) printl("sizeof(" OMNI_DEF2STR( __VA_ARGS__ ) ") = " << sizeof( __VA_ARGS__ ))

static inline void pause_test(uint32_t ms)
{
    if (ms == 0) {
        std::string ip;
        std::cout << "Continue (y/n): ";
        std::cin >> ip;
        std::cin.clear();
        if (ip == "n") {
            omni::application::exit();
        }
        std::cout << std::endl;
    } else {
        omni::sync::sleep(ms);
    }
}
static inline void pause_test()
{
    pause_test(0);
}

// TODO: figure this out ??? 

template < typename T >
static inline void test(const std::string& msg, T val, const std::string& exp)
{
    std::string res = omni::string_util::to_string(val);
    std::cout << msg << " = " << val << " -- expected: " << exp << " | " << ((res == exp) ? "PASS" : "FAIL") << std::endl;
}
static inline void test(const std::string& msg, const std::wstring& val, const std::string& exp)
{
    std::string res = omni::string_util::to_string(val);
    std::wcout << msg.c_str() << " = " << val << " -- expected: " << exp.c_str() << " | " << ((res == exp) ? "PASS" : "FAIL") << std::endl;
}
static inline void test(const std::string& msg, const std::wstring& val, const std::wstring& exp)
{
    std::wcout << msg.c_str() << " = " << val << " -- expected: " << exp << " | " << ((val == exp) ? "PASS" : "FAIL") << std::endl;
}

template < typename T >
static inline void test(const char* msg, T val, const std::string& exp)
{
    return test<T>(std::string(msg), val, exp);
}
template < typename T >
static inline void test(const char* msg, T val, const char* exp)
{
    return test<T>(std::string(msg), val, std::string(exp));
}
static inline void test(const char* msg, const std::wstring& val, const char* exp)
{
    return test(std::string(msg), val, std::string(exp));
}
static inline void test(const char* msg, const std::wstring& val, const std::wstring& exp)
{
    return test(std::string(msg), val, exp);
}

namespace omni { class ut; class ut_base; }
typedef std::map<std::size_t, omni::ut> test_map;
typedef std::map<omni::string_t, omni::ut_base*> unit_map;

unit_map units; // the unit test map

namespace omni {
    // the unit test itself
    class ut {
        public:
            ut() : index(), funcptr(), name(), desc(), no_exit() {}
            ut(std::size_t idx, omni::callback func, const char* n, const char* d) :
                index(idx), funcptr(func), name(omni::string::util::to_string_t(n)), desc(omni::string::util::to_string_t(d)), no_exit(false) { }
            ut(std::size_t idx, omni::callback func, omni::string_t n, omni::string_t d) : 
                index(idx), funcptr(func), name(n), desc(d), no_exit(false) { }

            std::size_t index;
            omni::callback funcptr;
            omni::string_t name;
            omni::string_t desc;
            volatile bool no_exit;
            
            static omni::ut current_test;
            
            template < typename Itr >
            static void print_list(Itr s, Itr e)
            {
                while (s != e) {
                    std::cout << *s << std::endl;
                    ++s;
                }
            }
    };

    class ut_base {
        public:
            ut_base(const omni::char_t* nm, const omni::char_t* desc) : 
                m_name(nm),
                m_desc(desc),
                m_list()
            {
                units[this->m_name] = this;
                this->m_list[this->m_list.size()] = omni::ut(this->m_list.size(), omni::callback::bind<ut_base, &ut_base::base_test>(this), "base_test", "tests the basic functionality of the class");
                this->m_list[this->m_list.size()] = omni::ut(this->m_list.size(), omni::callback::bind<ut_base, &ut_base::info_test>(this), "info_test", "displays info about the class/namespace");
            }
            
            virtual ~ut_base() { units.erase(this->m_name); }

            virtual void base_test() = 0; // { omni::XXXXXXX* obj = new omni::XXXXXXX }
            virtual void info_test() = 0; // { print_info(omni::XXXXXXX); }

            const omni::string_t& name() { return this->m_name; }
            const omni::string_t& description() { return this->m_desc; }
            const std::map<std::size_t, omni::ut>& tests() { return this->m_list; }
            
        protected:
            omni::string_t m_name;
            omni::string_t m_desc;
            test_map m_list;
            
            std::size_t _find(std::string test_name)
            {
                test_map::const_iterator tfind = this->m_list.begin();
                omni::string_t nm = omni::string::util::to_string_t(test_name);
                while (tfind != this->m_list.end()) {
                    if (nm == tfind->second.name) {
                        return tfind->second.index;
                    }
                    ++tfind;
                }
                return 0;
            }
            
            std::size_t _find(omni::callback fn)
            {
                test_map::const_iterator tfind = this->m_list.begin();
                while (tfind != this->m_list.end()) {
                    if (fn == tfind->second.funcptr) {
                        return tfind->second.index;
                    }
                    ++tfind;
                }
                return 0;
            }
    };
}

#endif // OMNI_UNIT_TEST_HPP

// This file (unit_test.hpp) is included in every test header; we don't want to double include the actual 'unit_test'
// definition (i.e. 'class ut' and 'class ut_base', etc.), but we do want to include the 'ut_cdefs' header as it
// has the needed helper macros for the unit test classes. Thus the include is outside of the 'double include protection'
// on purpose; the unit test header should include "ut_udefs.hpp" at the end of the unit test header file to undef these
// includes for the separate unit tests otherwise erroneous errors will be generated when you build any unit test.
#include <utdefs/cdefs.hpp>
