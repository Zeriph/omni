#if defined(OMNI_UTUA) || defined(OMNI_UT_STACK_BUFFER)

#define UT_NAME stack_buffer
#include <utdefs/unit_test.hpp>
#include <vector>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(iterator_test, "tests the capabilities of the iterator functionality");
            M_LIST_ADD(template_test, "tests the capabilities of the template functionality");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::stack_buffer<char, 10>);
            print_info(omni::stack_buffer<uint8_t, 10>);
            print_info(omni::stack_buffer<uint16_t, 10>);
            print_info(omni::stack_buffer<uint32_t, 10>);
            print_info(omni::stack_buffer<uint64_t, 10>);
        }
        
        void base_test()
        {
            typedef omni::stack_buffer<char, 5> buf5;
            // omni::stack_buffer<char, 5> sbuf("12345"); // compilation error: (char[5] != char[6])
            buf5 sbuf("1234");
            // sbuf = "12345"; // compilation error: (char[5] != char[6])
            printl("sizeof(sbuf) == " << sizeof(sbuf) << ", sizeof(omni::stack_buffer<char, 5>) == " << sizeof(buf5));
            printl("sbuf size == " << sbuf.size() << ", sbuf capacity == " << sbuf.capacity() << ", sbuf data == '" << sbuf.data() << "'");
            
            printl("iterating write");
            iterate_write(sbuf.begin(), sbuf.end());

            printl("iterating read");
            iterate_read(sbuf.begin(), sbuf.end());


            printl("modifying via 'operator char*'");
            modify(sbuf, sbuf.size());
            printl("reading via 'operator const char*'");
            readify(sbuf, sbuf.size());

            printl("std::reverse");
            std::reverse(sbuf.begin(), sbuf.end());

            printl("iterating");
            for (buf5::iterator it = sbuf.begin(); it != sbuf.end(); ++it) {
                std::cout << *it;
            }
            std::cout << std::endl;

            // std::cout << "sbuf size == " << sbuf.size() << ", sbuf data == '" << *sbuf << "'" << std::endl;
            // produces compilation error (no operator*()) .. makes sense, since it should be equivalent to the following:
            // char buf[5] = "1234";
            // std::cout << *buf;

            printl("assing vector<char>");
            std::vector<char> cvec = sbuf;
            iterate_read(cvec.begin(), cvec.end());
            printl("writing to vector, sbuf should be unchanged");
            iterate_write(cvec.begin(), cvec.end());
            iterate_read(cvec.begin(), cvec.end());
            iterate_read(sbuf.begin(), sbuf.end());

            printv("sbuf capacity = ", sbuf.capacity());
            printv("sbuf size = ", sbuf.size());
            printv("cvec capacity = ", cvec.capacity());
            printv("cvec size = ", cvec.size());


            printl("assigning one bigger");
            try {
                // this also throws warnings (as it should) on some compilers
                sbuf = "12345";
            } catch (omni::exception oex) {
                printv("omni exception: ", oex.what());
            } catch (std::exception ex) {
                printv("exception: ", ex.what());
            }
            printl("assigning one smaller");
            sbuf = "ZZ";
            iterate_read(sbuf.begin(), sbuf.end());
        }

        void iterator_test()
        {
            typedef omni::stack_buffer<uint32_t, 4> buf_t;
            buf_t buf(10, 20, 30, 40);

            printl("iterator");
            buf_t::iterator itr = buf.begin();
            while (itr != buf.end()) {
                std::cout << *itr;
                *itr += 10;
                if (++itr != buf.end()) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;

            printl("const_iterator");
            buf_t::const_iterator citr = buf.begin();
            while (citr != buf.end()) {
                std::cout << *citr;
                if (++citr != buf.end()) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }

        void template_test()
        {
            omni::stack_buffer<uint32_t, 10> ubuf;
            for (uint32_t i = 0; i < ubuf.size(); ++i) {
                ubuf[i] = (i + 1) * 10;
            }
            printl("sizeof(ubuf) == " << sizeof(ubuf) << std::endl <<
                   "ubuf size == " << ubuf.size() << std::endl <<
                   "ubuf capacity == " << ubuf.capacity() << std::endl <<
                   "ubuf data == '" << ubuf.data() << "'");
            iterate_read(ubuf.begin(), ubuf.end());
            iterate_write(ubuf.begin(), ubuf.end());
            iterate_read(ubuf.begin(), ubuf.end());


            printl("assing vector<uint32_t>");
            for (uint32_t i = 0; i < ubuf.size(); ++i) {
                ubuf[i] = (i + 1) * 10;
            }
            std::vector<uint32_t> cvec = ubuf;
            iterate_read(cvec.begin(), cvec.end());
            printl("writing to vector, ubuf should be unchanged");
            iterate_write(cvec.begin(), cvec.end());
            iterate_read(cvec.begin(), cvec.end());
            iterate_read(ubuf.begin(), ubuf.end());

            printv("ubuf capacity = ", ubuf.capacity());
            printv("ubuf size = ", ubuf.size());
            printv("cvec capacity = ", cvec.capacity());
            printv("cvec size = ", cvec.size());
            printv("sizeof(cvec) = ", sizeof(cvec));
            printv("vec.size*sizeof(T) = ", (cvec.capacity() * sizeof(uint32_t)));
        }

    private:
        template < typename Itr >
        void iterate_read(Itr start, Itr end)
        {
            while (start != end) {
                std::cout << *start << " ";
                ++start;
            }
            std::cout << std::endl;
        }

        template < typename Itr >
        void iterate_write(Itr start, Itr end)
        {
            while (start != end) {
                *start = '1';
                ++start;
            }
        }

        void readify(const char* val, size_t sz)
        {
            for (size_t i = 0; i < sz; ++i) {
                std::cout << val[i];
            }
            std::cout << std::endl;
        }

        void modify(char* val, size_t sz)
        {
            for (size_t i = 0; i < sz; ++i) {
                val[i] = (char)(i + 65);
            }
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_STACK_BUFFER
