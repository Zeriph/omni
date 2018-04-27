#if defined(OMNI_UTUA) || defined(OMNI_UT_OBJECT)

#define UT_NAME object
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            #if defined(OMNI_TYPE_INFO)
                M_LIST_ADD(type_info_test, "tests the type info of the object");
            #endif
            M_LIST_ADD(tag_test, "tests the tag of the object");
            M_LIST_ADD(assign_test, "tests the copy/swap idiom assign");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            // OMNI_INHERIT_OBJECT does not need to be defined to use a basic omni::object
            omni::object* o = new omni::object("base_test");
            o->disposing += &obj_disposing;
            printv("object 'o': ", o->to_string_t());
            omni::object* o2 = new omni::object("base_test_2");
            printv("object 'o2': ", *o2);
            // false, becuase name != and delegate !=
            printv("o == o2? ", OMNI_BOOL2STR((*o == *o2)));
            o2->name = OMNI_STRW("base_test");
            // false, becuase delegate !=
            printv("o == o2? ", OMNI_BOOL2STR((*o == *o2)));
            o2->disposing += &obj_disposing;
            // true becuase all ==
            printv("o == o2? ", OMNI_BOOL2STR((*o == *o2)));
            o2->tag = o;
            // false becuase tag !=
            printv("o == o2? ", OMNI_BOOL2STR((*o == *o2)));
            delete o;
            delete o2;
            
            // should fail compile since the 'id' ctor is meant for derived classes
            //o = new omni::object("base_test", 1000);
        }

        #if defined(OMNI_TYPE_INFO)
        void type_info_test()
        {
            // OMNI_INHERIT_OBJECT must be defined to derive from it
            omni::object* o = new omni::object("type_info_test");
            o->disposing += &obj_disposing;
            printv("object 'o': ", o->hash());
            delete o;
            //o = new omni::util::version();
            // must re-add delegate since 'delete o;' invalidated the object
            //o->disposing += &obj_disposing;
            /*printv("object 'o': ", o->hash());
            omni::stopwatch s;
            s.disposing += &obj_disposing;
            printv("object 's': ", s.hash());
            printv("o == s? ", OMNI_BOOL2STR((*o == s)));
            delete o;
            o = &s;
            printv("object 'o': ", o->hash());
            printv("o == s? ", OMNI_BOOL2STR((*o == s)));*/
        }
        #endif

        void tag_test()
        {
            omni::string_t s(OMNI_STRW("this is a test"));
            omni::object *o = new omni::object("tag_test");
            o->disposing += &obj_disposing;
            o->tag = &s;
            delete o;
        }
        
        void assign_test()
        {
            omni::object o1("object 1", &obj_disposing);
            omni::object o2("object 2", &obj_disposing);
            
            printv("o1 = ", o1);
            printv("o2 = ", o2);
            
            o1 = o2;
            
            printv("o1 = ", o1);
            printv("o2 = ", o2);
        }
        
        static void obj_disposing()
        {
            printl("an object is being destroyed");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_OBJECT
