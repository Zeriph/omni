#if defined(OMNI_UTUA) || defined(OMNI_UT_IO)

#define UT_NAME io
#define UT_ISNS true
#define UT_DESC "Tests the various functionality of the omni::io namespace"
#include <utdefs/unit_test.hpp>
#include <omni/strings.hpp>

#define TC(code, exception_message) try { code; } catch (std::exception& ex) { std::cout << "EXCEPTION:" << std::endl << exception_message << std::endl << "inner exception: " << ex.what() << std::endl; }

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(file_test, "tests the file namespace");
            M_LIST_ADD(file_read, "tests the file read functionality");
            M_LIST_ADD(file_write, "tests the file write functionality");
            M_LIST_ADD(directory_read, "tests the directory namespace");
            M_LIST_ADD(directory_destruct, "tests the destructive directory functionality");
            M_LIST_ADD(path_test, "tests the path namespace");
        }
        
        UT_CLASS_DTOR() {}

        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            file_test();
            directory_read();
            path_test();
        }

        void file_test()
        {
            omni::application::signal_handler::attach(&app_signal);

            std::string cpath = OMNI_PATH_ROOT + omni::io::path::combine("Code", "test"); 
            test_cfile(cpath);
        }

        void file_read()
        {
            omni::application::signal_handler::attach(&app_signal);

            std::string cpath = OMNI_PATH_ROOT + omni::io::path::combine("Code", "test"); 
            test_cfile_read(cpath);
        }

        void file_write()
        {
            omni::application::signal_handler::attach(&app_signal);

            std::string cpath = OMNI_PATH_ROOT + omni::io::path::combine("Code", "test"); 
            test_cfile_write(cpath);
        }

        void directory_read()
        {
            omni::application::signal_handler::attach(&app_signal);
            
            std::string cfpath = OMNI_PATH_ROOT; cfpath += omni::io::path::combine("Code", "test", "tmp");
            std::string ctpath = OMNI_PATH_ROOT; ctpath += omni::io::path::combine("Code", "test", "tmp", "no");
            std::string cpath = OMNI_PATH_ROOT; cpath += omni::io::path::combine("Code", "test");

            test_cdir(cfpath, ctpath, cpath);
        }

        void directory_destruct()
        {
            omni::application::signal_handler::attach(&app_signal);
            
            std::string cfpath = OMNI_PATH_ROOT + omni::io::path::combine("Code", "test", "tmp");
            std::string ctpath = OMNI_PATH_ROOT + omni::io::path::combine("Code", "test", "tmp", "no");
            std::string cpath = OMNI_PATH_ROOT + omni::io::path::combine("Code", "test");
            
            test_cdir_w(cfpath, ctpath, cpath);
        }

        void path_test()
        {
            omni::application::signal_handler::attach(&app_signal);
            
            std::string cpath = omni::io::path::combine("code", "test", "value", "x", "y", "z.cpp");
            std::wstring wpath = omni::io::path::combine(L"code", L"test", L"value", L"x", L"y", L"z.cpp");

            std::cout << "cpath = " << cpath << std::endl;
            std::wcout << "wpath = " << wpath << std::endl;

            std::cout << "Testing *nix file paths" << std::endl;

            test_cpath("/Code/test", "file", ".txt", "/Code/test/../test/file.txt", "/Code/test/file.txt", "/");
            test_wpath(L"/Code/test", L"file", L".txt", L"/Code/test/../test/file.txt", L"/Code/test/file.txt", L"/");

            std::cout << std::endl << "Testing Windows file paths" << std::endl;

            test_cpath("C:\\Code\\test", "file", ".txt", "C:\\Code\\test\\..\\test\\file.txt", "C:\\Code\\test\\file.txt", "\\");
            test_wpath(L"C:\\Code\\test", L"file", L".txt", L"C:\\Code\\test\\..\\test\\file.txt", L"C:\\Code\\test\\file.txt", L"\\");

            try {
                test_fuzzy();
            } catch (std::exception& ex) {
                std::cout << "FUZZY EXCEPTION: " << ex.what() << std::endl;
            }
        }

    private:
        static void app_signal(int sig)
        {
            std::cout << "Signal received: " << sig << std::endl;
            if (sig == 11) { exit(0); }
        }

        template < typename OS, template < class, class > class std_seq_t, class T, class std_allocator_t >
        void print_all(OS& os, const std_seq_t< T, std_allocator_t >& vals)
        {
            typename std_seq_t< T, std_allocator_t >::const_iterator itr = vals.begin();
            for (; itr != vals.end(); ++itr) {
                os << *itr << std::endl;
            }
            os << std::endl;
        }

        template < typename CHAR, typename STREAM >
        void print_list(const CHAR& vals, STREAM& ostr)
        {
            typename CHAR::const_iterator itr = vals.begin();
            for (; itr != vals.end(); ++itr) {
                ostr << static_cast<uint32_t>(*itr);
                if ((itr+1) != vals.end()) { ostr << ","; }
            }
        }
        template < typename T, std::size_t SZ >
        void print_chars(const T (&data)[SZ])
        {
            for (std::size_t i = 0; i < SZ; ++i) {
                std::cout << static_cast<uint32_t>(data[i]);
                if ((i+1) < SZ) { std::cout << ","; }
            }
        }
        template < typename T, std::size_t SZ >
        void print_chars(const omni::stack_buffer<T, SZ>& data)
        {
            for (std::size_t i = 0; i < SZ; ++i) {
                std::cout << static_cast<uint32_t>(data[i]);
                if ((i+1) < SZ) { std::cout << ","; }
            }
        }
        template < typename T >
        void print_chars(const T* data, std::size_t SZ)
        {
            for (std::size_t i = 0; i < SZ; ++i) {
                std::cout << static_cast<uint32_t>(data[i]);
                if ((i+1) < SZ) { std::cout << ","; }
            }
        }

        void test_cfile(const std::string& path)
        {
            std::cout << "cfile:" << std::endl;
            test_file<std::string>(path);
            std::cout << std::endl;
        }
        void test_wfile(const std::wstring& path)
        {
            std::cout << "wfile:" << std::endl;
            //test_file(path);
            std::cout << std::endl;
        }
        template < typename STR >
        void test_file(const STR& path)
        {
            STR file1 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file.txt"));
            STR file2 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file (copy).txt"));
            STR file3 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("other.txt"));
            STR file4 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("moved.txt"));
            STR file5 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("folder"), omni::string::util::lexical_cast<STR>("new_file.txt"));
            omni::io::options io_ops = omni::io::options::OVERWRITE | omni::io::options::CREATE_PATH;
            if (omni::io::file::exist(file1)) {
                if (omni::io::file::exist(file2)) {
                    test(std::string("copy ") + file1 + " to " + file2, b2s(omni::io::file::copy(file1, file2)), "false");
                } else {
                    test(std::string("copy ") + file1 + " to " + file2, b2s(omni::io::file::copy(file1, file2)), "true");
                }
                test(std::string("overwrite copy ") + file1 + " to " + file2, b2s(omni::io::file::copy(file1, file2, io_ops)), "true");
            } else {
                test(std::string("copy ") + file1 + " to " + file2, b2s(omni::io::file::copy(file1, file2)), "false");
                test(std::string("overwrite copy ") + file1 + " to " + file2, b2s(omni::io::file::copy(file1, file2, io_ops)), "false");
            }
            
            test(std::string("create ") + file3, b2s(omni::io::file::create(file3)), "true");
            test(std::string("create (with path) ") + file3, b2s(omni::io::file::create(file3, io_ops)), "true");
            test(file1 + " exists", b2s(omni::io::file::exists(file1)), "true");
            test(file1 + " exist", b2s(omni::io::file::exist(file1)), "true");

            try {
                std::cout << "moving " << file3 << " to " << file4 << std::endl;
                test("omni::io::file::move(file3, file4)", b2s(omni::io::file::move(file3, file4)), "true");
            } catch (const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
            try {
                std::cout << "moving (w/create_path)" << file4 << " to " << file5 << std::endl;
                test("omni::io::file::move(file4, file5, true)", b2s(omni::io::file::move(file4, file5, io_ops)), "true");
            } catch (const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
            try {
                std::cout << "renaming " << file2 << " to " << file3 << std::endl;
                test("omni::io::file::rename(file2, file3)", b2s(omni::io::file::rename(file2, file3)), "true");
            } catch (const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
            try {
                std::cout << "renaming (w/create_path) " << file3 << " to " << file5 << std::endl;
                test("omni::io::file::rename(file3, file5, true)", b2s(omni::io::file::rename(file3, file5, io_ops)), "true");
            } catch (const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }

            test(std::string("writing data '0123456789ABCDEF' to ") + file1, omni::io::file::write(file1, omni::string::util::lexical_cast<STR>("0123456789ABCDEF"), false), "16");
            test(std::string("file size of ") + file1, omni::io::file::get_size(file1), "16");
            test(std::string("contents of ") + file1, omni::io::file::get_contents(file1), "0123456789ABCDEF");

            #if defined(OMNI_NON_PORTABLE)
                test(std::string("setting file size of ") + file1, b2s(omni::io::file::set_size(file1, 256)), "true");
                test(std::string("file size of ") + file1, omni::io::file::get_size(file1), "256");
            #endif

            test(std::string("removing ") + file2, b2s(omni::io::file::remove(file2)), "true");
            test(std::string("removing ") + file3, b2s(omni::io::file::remove(file3)), "true");
            test(std::string("removing ") + file4, b2s(omni::io::file::remove(file4)), "true");
            test(std::string("removing ") + file5, b2s(omni::io::file::remove(file5)), "true");
            
        }

        void test_cfile_read(const std::string& path)
        {
            std::cout << "cfile:" << std::endl;
            test_file_read_x(path, std::cout);
            std::cout << std::endl;
        }
        void test_wfile_read(const std::wstring& path)
        {
            std::cout << "wfile:" << std::endl;
            test_file_read_x(path, std::wcout);
            std::cout << std::endl;
        }
        template < typename STR, typename OS >
        void test_file_read_x(const STR& path, OS& os)
        {
            STR file1 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file.txt"));
            TC(test_file_read(path, os, file1), "test_file_read error");
            std::cout << "done.." << std::endl;
        }

        void test_cfile_write(const std::string& path)
        {
            std::cout << "cfile:" << std::endl;
            test_file_write_x(path, std::cout);
            std::cout << std::endl;
        }
        void test_wfile_write(const std::wstring& path)
        {
            std::cout << "wfile:" << std::endl;
            test_file_write_x(path, std::wcout);
            std::cout << std::endl;
        }
        template < typename STR, typename OS >
        void test_file_write_x(const STR& path, OS& os)
        {
            STR file1 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file.txt"));
            STR file2 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file (copy).txt"));
            TC(test_file_write(path, os, file1, file2), "test_file_write error");
            std::cout << "done.." << std::endl;
        }
        
        template < typename STR, typename OS >
        void test_file_read(const STR& path, OS& os, const STR& file1)
        {
            const std::size_t SZ = 4;
            omni::stack_buffer<char, SZ> sbuf;
            uint8_t ubuf[SZ] = {0};
            char buf[SZ] = {0};
            wchar_t wbuf[SZ] = {0};
            uint8_t* ubuf_p = new uint8_t[SZ];
            char* buf_p = new char[SZ];
            wchar_t* wbuf_p = new wchar_t[SZ];
            omni::seq::uint8_t ubuffer;
            omni::seq::char_t buffer;
            omni::seq::wide_char_t wbuffer;
            std::vector<char> cvbuf;
            STR strbuf;
            memset(ubuf_p, 0, SZ);
            memset(buf_p, 0, SZ);
            memset(wbuf_p, 0, SZ*sizeof(wchar_t));

            test("omni::io::file::read(file1, ubuf)", omni::io::file::read(file1, ubuf), "4");
            os << "ubuf data: '"; print_chars(ubuf); os << "'" << std::endl;

            test("omni::io::file::read(file1, buf)", omni::io::file::read(file1, buf), "4");
            os << "buf data: '"; print_chars(buf); os << "'" << std::endl;

            test("omni::io::file::read(file1, wbuf)", omni::io::file::read(file1, wbuf), "4");
            os << "wbuf data: '"; print_chars(wbuf); os << "'" << std::endl;

            test("omni::io::file::read(file1, sbuf)", omni::io::file::read(file1, sbuf), "4");
            os << "sbuf data: '"; print_chars<char, SZ>(sbuf); os << "'" << std::endl;

            test("omni::io::file::read(file1, ubuffer)", omni::io::file::read(file1, ubuffer), "17");
            os << "ubuffer data[" << ubuffer.size() << "]: '"; print_list(ubuffer, os); os << "'" << std::endl;

            test("omni::io::file::read(file1, buffer)", omni::io::file::read(file1, buffer), "17");
            os << "buffer data[" << buffer.size() << "]: '"; print_list(buffer, os); os << "'" << std::endl;

            test("omni::io::file::read(file1, wbuffer)", omni::io::file::read(file1, wbuffer), "17");
            os << "wbuffer data[" << wbuffer.size() << "]: '"; print_list(wbuffer, os); os << "'" << std::endl;

            test("omni::io::file::read(file1, cvbuf)", omni::io::file::read(file1, cvbuf), "17");
            os << "cvbuf data[" << cvbuf.size() << "]: '"; print_list(cvbuf, os); os << "'" << std::endl;

            test("omni::io::file::read(file1, strbuf)", omni::io::file::read(file1, strbuf), "16");
            os << "strbuf data[" << strbuf.size() << "]: '" << strbuf << "'" << std::endl;
            
            test("omni::io::file::unsafe_read(file1, ubuf_p, 4)", omni::io::file::unsafe_read(file1, ubuf_p, SZ), "4");
            os << "ubuf_p data: '"; print_chars(ubuf_p, SZ); os << "'" << std::endl;

            test("omni::io::file::unsafe_read(file1, buf_p, 4)", omni::io::file::unsafe_read(file1, buf_p, SZ), "4");
            os << "buf_p data: '"; print_chars(buf_p, SZ); os << "'" << std::endl;

            test("omni::io::file::unsafe_read(file1, wbuf_p, 4)", omni::io::file::unsafe_read(file1, wbuf_p, SZ), "4");
            os << "wbuf_p data: '"; print_chars(wbuf_p, SZ); os << "'" << std::endl;



            sbuf.zeroize();
            ubuffer.clear();
            buffer.clear();
            wbuffer.clear();
            cvbuf.clear();
            memset(ubuf, 0, SZ);
            memset(buf, 0, SZ);
            memset(wbuf, 0, SZ*sizeof(wchar_t));
            memset(ubuf_p, 0, SZ);
            memset(buf_p, 0, SZ);
            memset(wbuf_p, 0, SZ*sizeof(wchar_t));

            test("omni::io::file::read_element(file1, ubuf)", omni::io::file::read_element(file1, ubuf), "4");
            os << "ubuf data: '"; print_chars(ubuf); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, buf)", omni::io::file::read_element(file1, buf), "4");
            os << "buf data: '"; print_chars(buf); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, wbuf)", omni::io::file::read_element(file1, wbuf), "4");
            os << "wbuf data: '"; print_chars(wbuf); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, sbuf)", omni::io::file::read_element(file1, sbuf), "4");
            os << "sbuf data: '"; print_chars<char, SZ>(sbuf); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, ubuffer)", omni::io::file::read_element(file1, ubuffer), "17");
            os << "ubuffer data[" << ubuffer.size() << "]: '"; print_list(ubuffer, os); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, buffer)", omni::io::file::read_element(file1, buffer), "17");
            os << "buffer data[" << buffer.size() << "]: '"; print_list(buffer, os); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, wbuffer)", omni::io::file::read_element(file1, wbuffer), "5");
            os << "wbuffer data[" << wbuffer.size() << "]: '"; print_list(wbuffer, os); os << "'" << std::endl;

            test("omni::io::file::read_element(file1, cvbuf)", omni::io::file::read_element(file1, cvbuf), "17");
            os << "cvbuf data[" << cvbuf.size() << "]: '"; print_list(cvbuf, os); os << "'" << std::endl;
            
            test("omni::io::file::unsafe_read_element(file1, ubuf_p, 4)", omni::io::file::unsafe_read_element(file1, ubuf_p, SZ), "4");
            os << "ubuf_p data: '"; print_chars(ubuf_p, SZ); os << "'" << std::endl;

            test("omni::io::file::unsafe_read_element(file1, buf_p, 4)", omni::io::file::unsafe_read_element(file1, buf_p, SZ), "4");
            os << "buf_p data: '"; print_chars(buf_p, SZ); os << "'" << std::endl;
            
            test("omni::io::file::unsafe_read_element(file1, wbuf_p, 4)", omni::io::file::unsafe_read_element(file1, wbuf_p, SZ), "4");
            os << "wbuf_p data: '"; print_chars(wbuf_p, SZ); os << "'" << std::endl;

            delete[] ubuf_p;
            delete[] buf_p;
            delete[] wbuf_p;
        }
        template < typename STR, typename OS >
        void test_file_write(const STR& path, OS& os, const STR& file1, const STR& file2)
        {
            const std::size_t SZ = 128;
            omni::stack_buffer<char, SZ> sbuf;
            uint8_t ubuf[SZ] = {0};
            char buf[SZ] = {0};
            wchar_t wbuf[SZ] = {0};
            uint8_t* ubuf_p = new uint8_t[SZ];
            char* buf_p = new char[SZ];
            wchar_t* wbuf_p = new wchar_t[SZ];
            wchar_t wstr[] = { L"🌴" };
            omni::seq::uint8_t ubuffer;
            omni::seq::char_t buffer;
            omni::seq::wide_char_t wbuffer;
            std::vector<char> cvbuf;
            STR strbuf;
            memset(ubuf_p, 65, SZ);
            memset(buf_p, 65, SZ);
            for (size_t i = 0; i < SZ; ++i) {
                wbuf_p[i] = wstr[0];
            }
            omni::io::file::read(file1, ubuffer);
            omni::io::file::read(file1, buffer);
            omni::io::file::read(file1, wbuffer);
            omni::io::file::read(file1, cvbuf);
            omni::io::file::read(file1, strbuf);
            omni::io::file::read(file1, sbuf);
            omni::io::file::read(file1, ubuf);
            omni::io::file::read(file1, buf);
            omni::io::file::read(file1, wbuf);
            os << "writing to '" << file2 << "'" << std::endl;
            std::string bsz = omni::string::util::to_string(buffer.size());
            std::string usz = omni::string::util::to_string(ubuffer.size());
            std::string wsz = omni::string::util::to_string(wbuffer.size() * sizeof(wchar_t) * 2);
            std::string csz = omni::string::util::to_string(cvbuf.size());
            std::string ssz = omni::string::util::to_string(strbuf.size());

            test("writing ubuffer: ", omni::io::file::write(file2, ubuffer), usz);
            test("writing buffer: ", omni::io::file::write(file2, buffer), bsz);
            test("writing wbuffer: ", omni::io::file::write(file2, wbuffer), wsz);
            test("writing cvbuf: ", omni::io::file::write(file2, cvbuf), csz);
            test("writing strbuf: ", omni::io::file::write(file2, strbuf), ssz);

            test("writing ubuffer append: ", omni::io::file::write(file2, ubuffer, true), usz);
            test("writing buffer append: ", omni::io::file::write(file2, buffer, true), bsz);
            test("writing wbuffer append: ", omni::io::file::write(file2, wbuffer, true), wsz);
            test("writing cvbuf append: ", omni::io::file::write(file2, cvbuf, true), csz);
            test("writing strbuf append: ", omni::io::file::write(file2, strbuf, true), ssz);

            test("writing stack sbuf: ", omni::io::file::write(file2, sbuf), "128");
            test("writing stack sbuf append: ", omni::io::file::write(file2, sbuf, true), "128");

            test("writing [] ubuf: ", omni::io::file::write(file2, ubuf), "128");
            test("writing [] buf: ", omni::io::file::write(file2, buf), "128");
            test("writing [] wbuf: ", omni::io::file::write(file2, wbuf), "128");

            test("writing [] ubuf append: ", omni::io::file::write(file2, ubuf, true), "128");
            test("writing [] buf append: ", omni::io::file::write(file2, buf, true), "128");
            test("writing [] wbuf append: ", omni::io::file::write(file2, wbuf, true), "128");

            test("writing raw ubuf_p: ", omni::io::file::unsafe_write(file2, ubuf_p, SZ), "128");
            test("writing raw buf_p: ", omni::io::file::unsafe_write(file2, buf_p, SZ), "128");
            test("writing raw wbuf_p: ", omni::io::file::unsafe_write(file2, wbuf_p, SZ), "128");
            
            test("writing raw ubuf_p append: ", omni::io::file::unsafe_write(file2, ubuf_p, SZ, true), "128");
            test("writing raw buf_p append: ", omni::io::file::unsafe_write(file2, buf_p, SZ, true), "128");
            test("writing raw wbuf_p append: ", omni::io::file::unsafe_write(file2, wbuf_p, SZ, true), "128");


            wsz = omni::string::util::to_string(wbuffer.size()*2);
            test("write_element ubuffer: ", omni::io::file::write_element(file2, ubuffer), usz);
            test("write_element buffer: ", omni::io::file::write_element(file2, buffer), bsz);
            test("write_element wbuffer: ", omni::io::file::write_element(file2, wbuffer), wsz);
            test("write_element [] buf: ", omni::io::file::write_element(file2, buf), "128");
            test("write_element [] wbuf: ", omni::io::file::write_element(file2, wbuf), "128");
            test("write_element raw buf_p: ", omni::io::file::unsafe_write_element(file2, buf_p, SZ), "128");
            test("write_element raw wbuf_p: ", omni::io::file::unsafe_write_element(file2, wbuf_p, SZ), "128");

            bsz = omni::string::util::to_string(buffer.size() + 1);
            usz = omni::string::util::to_string(ubuffer.size() + 1);
            wsz = omni::string::util::to_string((wbuffer.size() * sizeof(wchar_t) * 2) + 1);
            csz = omni::string::util::to_string(cvbuf.size() + 1);
            ssz = omni::string::util::to_string(strbuf.size() + 1);
            
            test("writing line ubuf: ", omni::io::file::write_line(file2, ubuffer), usz);
            test("writing line buf: ", omni::io::file::write_line(file2, buffer), bsz);
            test("writing line wbuf: ", omni::io::file::write_line(file2, wbuffer), wsz);
            test("writing line strbuf: ", omni::io::file::write_line(file2, strbuf), ssz);

            test("writing line ubuf append: ", omni::io::file::write_line(file2, ubuffer, true), usz);
            test("writing line buf append: ", omni::io::file::write_line(file2, buffer, true), bsz);
            test("writing line wbuf append: ", omni::io::file::write_line(file2, wbuffer, true), wsz);
            test("writing line strbuf append: ", omni::io::file::write_line(file2, strbuf, true), ssz);

            test("writing line raw ubuf_p: ", omni::io::file::unsafe_write_line(file2, ubuf_p, SZ), "129");
            test("writing line raw buf_p: ", omni::io::file::unsafe_write_line(file2, buf_p, SZ), "129");
            test("writing line raw wbuf_p: ", omni::io::file::unsafe_write_line(file2, wbuf_p, SZ), "129");
            
            test("writing line raw ubuf_p append: ", omni::io::file::unsafe_write_line(file2, ubuf_p, SZ, true), "129");
            test("writing line raw buf_p append: ", omni::io::file::unsafe_write_line(file2, buf_p, SZ, true), "129");
            test("writing line raw wbuf_p append: ", omni::io::file::unsafe_write_line(file2, wbuf_p, SZ, true), "129");
            

            //os << "writing raw wstr: " << omni::io::file::unsafe_write(file2, wstr, 10) << " bytes" << std::endl;
            //os << "writing [] wstr: " << omni::io::file::write(file2, wstr) << " bytes" << std::endl;

            delete[] ubuf_p;
            delete[] buf_p;
            delete[] wbuf_p;
        }

        void test_cdir(const std::string& p1, const std::string& p2, const std::string& p3)
        {
            std::cout << "cdirectory:" << std::endl;
            test_dir(p1, p2, p3, std::cout);
            std::cout << std::endl;
        }
        void test_wdir(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3)
        {
            std::wcout << "wdirectory:" << std::endl;
            test_dir(p1, p2, p3, std::wcout);
            std::wcout << std::endl;
        }
        template< typename STR, typename OS >
        void test_dir(const STR& p1, const STR& p2, const STR& p3, OS& os)
        {
            try {
                // p1 = "/Code/test/tmp"; p2 = "/Code/test/tmp/no"; p3 = "/Code/test";
                std::vector<STR> dirs;
                std::deque<STR> all_dirs;
                std::vector<STR> files;
                std::deque<STR> all_files;

                test("omni::io::directory::exists(p1)", omni::io::directory::exists(p1), "true");
                test("omni::io::directory::can_access(p1)", omni::io::directory::can_access(p1), "true");
                test("omni::io::directory::can_access(p2)", omni::io::directory::can_access(p2), "false");

                test("omni::io::directory::get_directories(p1, dirs)", omni::io::directory::get_directories(p3, dirs), "");
                print_all(os, dirs);
                test("omni::io::directory::get_all_directories(p1, all_dirs)", omni::io::directory::get_all_directories(p3, all_dirs), "");
                print_all(os, all_dirs);
                test("omni::io::directory::get_files(p1, files)", omni::io::directory::get_files(p3, files), "");
                print_all(os, files);
                test("omni::io::directory::get_all_files(p1, all_files)", omni::io::directory::get_all_files(p3, all_files), "");
                print_all(os, all_files);
            } catch (std::exception& ex) {
                std::cout << "EXCEPTION: " << ex.what() << std::endl;
            }
        }
        void test_cdir_w(const std::string& p1, const std::string& p2, const std::string& p3)
        {
            std::cout << "cdirectory:" << std::endl;
            test_dir_write(p1, p2, p3, std::cout);
            std::cout << std::endl;
        }
        void test_wdir_w(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3)
        {
            std::wcout << "wdirectory:" << std::endl;
            test_dir_write(p1, p2, p3, std::wcout);
            std::wcout << std::endl;
        }
        template < typename STR, typename OS >
        void test_dir_write(const STR& p1, const STR& p2, const STR& p3, OS& os)
        {
            try {
                // p1 = "/Code/test/tmp"; p2 = "/Code/test/tmp/no"; p3 = "/Code/test";
                STR fldr = omni::string::util::lexical_cast<STR>("folder");
                STR two = omni::string::util::lexical_cast<STR>("x2x");
                STR dn = omni::string::util::lexical_cast<STR>("dotnet");
                omni::io::options io_ops = omni::io::options::OVERWRITE | omni::io::options::CREATE_PATH;
                STR cp = omni::io::path::combine(p1, dn);   // -> /Code/test/tmp/dotnet
                STR nf = omni::io::path::combine(p1, two);  // -> /Code/test/tmp/x2x
                STR d2 = omni::io::path::combine(nf, dn);   // -> /Code/test/tmp/x2x/dotnet
                STR n2 = omni::io::path::combine(nf, fldr); // -> /Code/test/tmp/x2x/folder

                printl("cp = " << cp.c_str());
                printl("nf = " << nf.c_str());
                printl("d2 = " << d2.c_str());
                printl("n2 = " << n2.c_str());

                test("omni::io::directory::create(n2, io_ops)", b2s(omni::io::directory::create(n2, io_ops)), "true");
                pause_test();
                test("omni::io::directory::remove(n2)", b2s(omni::io::directory::remove(n2)), "true");
                pause_test();
                test("omni::io::directory::copy(cp, d2)", b2s(omni::io::directory::copy(cp, d2)), "true");
                pause_test();
                test("omni::io::directory::rename(d2, n2)", b2s(omni::io::directory::rename(d2, n2)), "true");
                pause_test();
                test("omni::io::directory::copy(cp, d2)", b2s(omni::io::directory::copy(cp, d2)), "true");
                pause_test();
                test("omni::io::directory::copy(cp, d2, true, io_ops)", b2s(omni::io::directory::copy(cp, d2, true, io_ops)), "true");
                pause_test();
                test("omni::io::directory::rename(d2, n2, io_ops)", b2s(omni::io::directory::rename(d2, n2, io_ops)), "true");
                pause_test();
                test("omni::io::directory::copy(cp, d2, true)", b2s(omni::io::directory::copy(cp, d2, true)), "true");
                pause_test();
                test("omni::io::directory::move(d2, n2, io_ops)", b2s(omni::io::directory::move(d2, n2, io_ops)), "true");
                pause_test();
                test("omni::io::directory::remove(n2, true)", b2s(omni::io::directory::remove(n2, true)), "true");
                
            } catch (const std::exception& ex) {
                std::cout << "EXCEPTION: " << ex.what() << std::endl;
            }
        }

        void test_cpath(const std::string& fpath, const std::string& cfile, const std::string& ext, const std::string& apath1, const std::string& apath2, const std::string& slash)
        {
            std::string file = cfile + ext;
            std::string cfull = omni::io::cpath::combine(fpath, file);
            std::cout << "--omni::io::cpath--" << std::endl;
            test("omni::io::cpath::change_extension(file, \"mp4\")", omni::io::cpath::change_extension(file, "mp4"), (cfile + ".mp4"));
            test("omni::io::cpath::combine(fpath, file)", omni::io::cpath::combine(fpath, file), (fpath + slash + file)); 
            test("omni::io::cpath::get_extension(file)", omni::io::cpath::get_extension(file), ext);
            test("omni::io::cpath::get_name(cfull)", omni::io::cpath::get_name(cfull), file);
            test("omni::io::cpath::get_name_without_extension(cfull)", omni::io::cpath::get_name_without_extension(cfull), cfile);
            test("omni::io::cpath::get_parent_name(cfull)", omni::io::cpath::get_parent_name(cfull), fpath);
            cprintv("omni::io::cpath::generate(fpath)", omni::io::cpath::generate(fpath));
            cprintv("omni::io::cpath::generate(fpath, cfile)", omni::io::cpath::generate(fpath, cfile));
            cprintv("omni::io::cpath::generate(fpath, cfile, ext)", omni::io::cpath::generate(fpath, cfile, ext));
            std::cout << "invalid file chars:" << std::endl;
            print_list(omni::io::cpath::get_invalid_file_chars(), std::cout); std::cout << std::endl;
            std::cout << "invalid path chars:" << std::endl;
            print_list(omni::io::cpath::get_invalid_path_chars(), std::cout); std::cout << std::endl;
            test("omni::io::cpath::has_extension(file)", omni::io::cpath::has_extension(file), "true");
            test("omni::io::cpath::has_extension(cfile)", omni::io::cpath::has_extension(cfile), "false");
            test("omni::io::cpath::is_path_absolute(apath1)", omni::io::cpath::is_path_absolute(apath1), "false");
            test("omni::io::cpath::is_path_absolute(apath2)", omni::io::cpath::is_path_absolute(apath2), "true");
            test("omni::io::cpath::trim_trailing_slash(fpath + slash)", omni::io::cpath::trim_trailing_slash(fpath + slash), fpath);
            test("omni::io::cpath::trim_trailing_slash(fpath)", omni::io::cpath::trim_trailing_slash(fpath), fpath);
        }
        void test_wpath(const std::wstring& fpath, const std::wstring& cfile, const std::wstring& ext, const std::wstring& apath1, const std::wstring& apath2, const std::wstring& slash)
        {
            std::wstring file = cfile + ext;
            std::wstring cfull = omni::io::wpath::combine(fpath, file);
            std::wcout << "--omni::io::wpath--" << std::endl;
            test("omni::io::wpath::change_extension(file, L\"mp4\")", omni::io::wpath::change_extension(file, L"mp4"), (cfile + L".mp4"));
            test("omni::io::wpath::combine(fpath, file)", omni::io::wpath::combine(fpath, file), (fpath + slash + file)); 
            test("omni::io::wpath::get_extension(file)", omni::io::wpath::get_extension(file), ext);
            test("omni::io::wpath::get_name(cfull)", omni::io::wpath::get_name(cfull), file);
            test("omni::io::wpath::get_name_without_extension(cfull)", omni::io::wpath::get_name_without_extension(cfull), cfile);
            test("omni::io::wpath::get_parent_name(cfull)", omni::io::wpath::get_parent_name(cfull), fpath);
            wprintv("omni::io::wpath::generate(fpath) = ", omni::io::wpath::generate(fpath));
            wprintv("omni::io::wpath::generate(fpath, cfile) = ", omni::io::wpath::generate(fpath, cfile));
            wprintv("omni::io::wpath::generate(fpath, cfile, ext) = ", omni::io::wpath::generate(fpath, cfile, ext));
            std::wcout << "invalid file chars:" << std::endl;
            print_list(omni::io::wpath::get_invalid_file_chars(), std::wcout); std::wcout << std::endl;
            std::wcout << "invalid path chars:" << std::endl;
            print_list(omni::io::wpath::get_invalid_path_chars(), std::wcout); std::wcout << std::endl;
            test("omni::io::wpath::has_extension(file)", omni::io::wpath::has_extension(file), "true");
            test("omni::io::wpath::has_extension(cfile)", omni::io::wpath::has_extension(cfile), "false");
            test("omni::io::wpath::is_path_absolute(apath1)", omni::io::wpath::is_path_absolute(apath1), "false");
            test("omni::io::wpath::is_path_absolute(apath2)", omni::io::wpath::is_path_absolute(apath2), "true");
            test("omni::io::wpath::trim_trailing_slash(fpath + slash)", omni::io::wpath::trim_trailing_slash(fpath + slash), fpath);
            test("omni::io::wpath::trim_trailing_slash(fpath)", omni::io::wpath::trim_trailing_slash(fpath), fpath);
        }
        void test_fuzzy()
        {
            std::cout << "--fuzz test--" << std::endl;
            test("omni::io::cpath::change_extension(\"test\", \"mp4\")", omni::io::cpath::change_extension("test", "mp4"), "test.mp4");
            test("omni::io::cpath::combine(\"\", \"\")", omni::io::cpath::combine("", ""), "");
            test("omni::io::cpath::get_extension(\"test...booo\")", omni::io::cpath::get_extension("test...booo"), ".booo");
            test("omni::io::cpath::get_name(\"test1\\test2/test3\")", omni::io::cpath::get_name("test1\\test2/test3"), "test3");
            test("omni::io::cpath::get_name_without_extension(\"test\")", omni::io::cpath::get_name_without_extension("test"), "test");
            test("omni::io::cpath::get_parent_name(\"test//test\\test\")", omni::io::cpath::get_parent_name("test//test\\test"), "test//test");
            cprintv("omni::io::cpath::generate(\"test\") = ", omni::io::cpath::generate("test"));
            cprintv("omni::io::cpath::generate(\"test\", \"test\") = ", omni::io::cpath::generate("test", "test"));
            cprintv("omni::io::cpath::generate(\"test\", \"\", \"test\") = ", omni::io::cpath::generate("test", "", "test"));
            test("omni::io::cpath::is_path_absolute(\"test\\test\")", b2s(omni::io::cpath::is_path_absolute("test\\test")), "false");
            test("omni::io::cpath::is_path_absolute(\"/test\\test\")", b2s(omni::io::cpath::is_path_absolute("/test\\test")), "true");
            test("omni::io::cpath::is_path_absolute(\"/test\\../test\")", b2s(omni::io::cpath::is_path_absolute("/test\\../test")), "false");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
