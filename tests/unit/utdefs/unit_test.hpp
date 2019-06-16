#if !defined(OMNI_UNIT_TEST_HPP)
#define OMNI_UNIT_TEST_HPP

#include <map>

#define OMNI_UTDBGOUT omni::out

#define b2s(b) ((b) ? "true" : "false")
#define print(m) OMNI_UTDBGOUT << m
#define printl(m) OMNI_UTDBGOUT << m << std::endl
#define printv(m, v) OMNI_UTDBGOUT << m << v << std::endl
#define printsw(v) case v: printl(#v); break
#define printswe(v, e) case v: OMNI_UTDBGOUT << e << #v << std::endl; break

#define cprint(m) std::cout << m
#define cprintl(m) std::cout << m << std::endl
#define cprintv(m, v) std::cout << m << v << std::endl

#define wprint(m) std::wcout << m
#define wprintl(m) std::wcout << m << std::endl
#define wprintv(m, v) std::wcout << m << v << std::endl

#if defined(OMNI_TYPE_INFO)
    #define print_info(cls) printl("sizeof("OMNI_DEF2STR(cls)") = " << sizeof(cls) << ", hash: " << omni::type_id<cls>())
#else
    #define print_info(cls) printl("sizeof("OMNI_DEF2STR(cls)") = " << sizeof(cls))
#endif
#define print_sizeof(cls) printl("sizeof("OMNI_DEF2STR(cls)") = " << sizeof(cls))

#define cpfunc1(func, arg1) std::cout << OMNI_DEF2STR(func) << "(\"" << arg1 << "\") = " << func(arg1) << std::endl
#define cpfunc2(func, arg1, arg2) std::cout << OMNI_DEF2STR(func) << "(\"" << arg1 << "\", \"" << arg2 << "\") = " << func(arg1, arg2) << std::endl
#define cpfunc3(func, arg1, arg2, arg3) std::cout << OMNI_DEF2STR(func) << "(\"" << arg1 << "\", \"" << arg2 << "\", \"" << arg3 << "\") = " << func(arg1, arg2, arg3) << std::endl

#define wpfunc1(func, arg1) std::wcout << OMNI_DEF2STR(func) << "(\"" << arg1 << "\") = " << func(arg1) << std::endl
#define wpfunc2(func, arg1, arg2) std::wcout << OMNI_DEF2STR(func) << "(\"" << arg1 << "\", \"" << arg2 << "\") = " << func(arg1, arg2) << std::endl
#define wpfunc3(func, arg1, arg2, arg3) std::wcout << OMNI_DEF2STR(func) << "(\"" << arg1 << "\", \"" << arg2 << "\", \"" << arg3 << "\") = " << func(arg1, arg2, arg3) << std::endl

#define B2S(b) (b ? "true" : "false")

namespace omni { class ut; class ut_base; }
typedef std::map<std::size_t, omni::ut> test_map;
typedef std::map<omni::string_t, omni::ut_base*> unit_map;

unit_map units; // the unit test map

namespace omni {
    class ut {
        public:
            ut() : index(), funcptr(), name(), desc() {}
            ut(std::size_t idx, omni::callback func, const char* n, const char* d) :
                index(idx), funcptr(func), name(omni::string::util::to_string_t(n)), desc(omni::string::util::to_string_t(d)) { }
            ut(std::size_t idx, omni::callback func, omni::string_t n, omni::string_t d) : 
                index(idx), funcptr(func), name(n), desc(d) { }

            std::size_t index;
            omni::callback funcptr;
            omni::string_t name;
            omni::string_t desc;
            
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
