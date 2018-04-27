#if defined(OMNI_UTUA) || defined(OMNI_UT_PROPERTY)

#define UT_NAME property
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(class_test, "tests a property with overridden class get/set");
            M_LIST_ADD(static_test, "tests a property with non-member get/set");
            M_LIST_ADD(pointer_type_test, "tests the property with a pointer type");
            M_LIST_ADD(pointer_test, "tests the property with a pointer type as a pointer");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test()
        {
            print_info(omni::property<int>);
            print_info(omni::property<bool>);
            print_info(omni::property<char*>);
            print_info(omni::property<double>);
            print_info(omni::property<int>::get);
            print_info(omni::property<int>::set);
            print_info(omni::property<int>::value_t);
        }
        
        void base_test()
        {
            omni::property<int> it;
            std::cout << "it == 0:" << it << std::endl;
            it = 10;
            std::cout << "it == 10:" << it << std::endl;
            int x = it++; // post
            std::cout << "(post) x == 10:" << x << std::endl;
            std::cout << "(    ) it == 11:" << it << std::endl;
            std::cout << "(pre ) it == 10:" << --it << std::endl; // pre
            std::cout << "(    ) it == 10:" << it << std::endl;
            std::cout << "(pre ) it == 11:" << ++it << std::endl; // pre
            std::cout << "(    ) it == 11:" << it << std::endl;
            std::cout << "(post) it == 11:" << it++ << std::endl; // post
            std::cout << "(    ) it == 12:" << it << std::endl;
            
            int y = 1 + it;
            std::cout << "y = " << y << ", it = " << it << std::endl;
            y = it + 1;
            std::cout << "y = " << y << ", it = " << it << std::endl;
            
            if (20 > it) { std::cout << "20 > it" << std::endl; }
            if (it < 20) { std::cout << "it < 20" << std::endl; }
            if (12 >= it) { std::cout << "12 >= it" << std::endl; }
            if (it <= 12) { std::cout << "it <= 12" << std::endl; }
            
            it += 20;
            std::cout << "it == " << it << std::endl;
            
            y = (it /= 2);
            std::cout << "it == " << it << std::endl;
        }
        
        void class_test()
        {
            prop_class p(30);
            std::cout << "p.x = " << p.x << std::endl;
            p.x = 42;
            std::cout << "p.x = " << p.x << std::endl;
        }

        void static_test()
        {
            omni::property<int> x(&UT_CNAME::prop_get, &UT_CNAME::prop_set, 10);
            x = 10;
            std::cout << "x == " << x << std::endl;
            int y = x;
            std::cout << "y == " << y << std::endl;
        }

        void pointer_type_test()
        {
            omni::property<int*> x;
            std::cout << "x == " << x << std::endl; // pointer address (0)
            //std::cout << "x == " << *x << std::endl; // error: dereference null pointer
            x = new int(10);
            std::cout << "x == " << x << std::endl; // pointer address
            std::cout << "*x == " << *x << std::endl; // 10
            int y = *x;
            std::cout << "y == " << y << std::endl; // y == 10
            *x = 20; // dereferencing the pointer to set its value
            y = *x;
            std::cout << "*x == " << *x << std::endl;
            std::cout << "y == " << y << std::endl; // y == 20
            // delete x; // error: calling delete on type 'omni::property<T>'
            delete x(); // OK: 'T operator()()' returns the underlying pointer to be deleted
            std::cout << "x == " << x << std::endl; // pointer address (dangling pointer since x != 0)
            std::cout << "x == " << *x << std::endl; // same value as before? garbage? crash? depends on OS/compiler/etc.
            // example:
            /*int* t = new int(10);
            std::cout << "t == " << t << std::endl;
            std::cout << "*t == " << *t << std::endl; 
            delete t;
            std::cout << "t == " << t << std::endl;
            std::cout << "*t == " << *t << std::endl;*/
            
        }

        void pointer_test()
        {
            omni::property<int*> *x;
            //x = new int(10); // type mismatch error: 'int*' != 'omni::property<int*>*'
            x = new omni::property<int*>(new int(10)); // OK
            
            std::cout << "x == " << x << std::endl; // pointer address of 'x'
            std::cout << "*x == " << *x << std::endl; // pointer address of underlying type
            int y = **x;
            std::cout << "y == " << y << std::endl; // y == 10
            **x = 20; // dereferencing the pointer to set its value
            y = **x;
            std::cout << "**x == " << **x << std::endl;
            std::cout << "y == " << y << std::endl; // y == 20
            // 
            delete (*x)(); // delete underlying pointer first
            std::cout << "*x == " << *x << std::endl; // pointer address (dangling pointer since x != 0)
            std::cout << "**x == " << **x << std::endl; // same value as before? garbage? crash? depends on OS/compiler/etc.
            delete x;    
        }
        
    private:
        static void prop_set(int val)
        {
            std::cout << "value being set = " << val << std::endl;
        }

        static int prop_get()
        {
            std::cout << "returning prop_get(42)" << std::endl;
            return 42;
        }
        
        // prop_class for class testing
        class prop_class 
        {
            public:
                typedef omni::property<int> prop_int;
                
                prop_class() :
                    _ix(0), x()
                {
                    x.bind_get(prop_int::get::bind<prop_class, &prop_class::_get_x>(*this)); // bind to this::_get_x
                    x.bind_set(prop_int::set::bind<prop_class, &prop_class::_set_x>(*this)); // bind to this::_set_x
                }
            
                prop_class(int val) :
                    _ix(val), x()
                {
                    x.bind_get(prop_int::get::bind<prop_class, &prop_class::_get_x>(*this)); // bind to this::_get_x
                    x.bind_set(prop_int::set::bind<prop_class, &prop_class::_set_x>(*this)); // bind to this::_set_x
                    x = val; // when called with a value in the ctor, property<T>::set is called
                }
                
                prop_int x;
                
            private:
                int _ix;
                
                int _get_x()
                {
                    std::cout << "returning _ix of " << this->_ix << std::endl;
                    return this->_ix;
                }
                
                void _set_x(int x)
                {
                    this->_ix = x;
                    std::cout << "set _ix to " << this->_ix << std::endl;
                }
        };
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_PROPERTY
