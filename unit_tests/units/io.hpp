#if defined(OMNI_UTUA) || defined(OMNI_UT_IO)

#define UT_NAME io
#define UT_ISNS true
#define UT_DESC "Tests the various functionality of the omni::io namespace"
#include <utdefs/unit_test.hpp>
#include <omni/strings.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(file, "tests the file namespace");
            M_LIST_ADD(directory, "tests the directory namespace");
            M_LIST_ADD(path, "tests the path namespace");
        }
        
        UT_CLASS_DTOR() {}

        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            this->file();
            this->directory();
            this->path();
        }

        void file()
        {
            #if defined(OMNI_OS_WIN)
                this->test_cfile("C:\\Code\\test");
                std::cout << std::endl;
                this->test_wfile(L"C:\\Code\\test");
            #else
                this->test_cfile("/Code/test");
                std::cout << std::endl;
                this->test_wfile(L"/Code/test");
            #endif
        }

        void directory()
        {
            #if defined(OMNI_OS_WIN)
                this->test_cdir("C:\\Code\\omni\\source", "C:\\Code\\test\\omni_source", "C:\\Code\\test");
                std::cout << std::endl;
                this->test_wdir(L"C:\\Code\\omni\\source", L"C:\\Code\\test\\omni_source", L"C:\\Code\\test");
            #else
                this->test_cdir("/Code/omni/source", "/Code/test/omni_source", "/Code/test");
                std::cout << std::endl;
                this->test_wdir(L"/Code/omni/source", L"/Code/test/omni_source", L"/Code/test");
            #endif
        }

        void path()
        {
            this->test_cpath("/Code/test", "file", ".txt", "/Code/test/../test/file.txt", "/Code/test/file.txt", "/");
            this->test_wpath(L"/Code/test", L"file", L".txt", L"/Code/test/../test/file.txt", L"/Code/test/file.txt", L"/");

            this->test_cpath("C:\\Code\\test", "file", ".txt", "C:\\Code\\test\\..\\test\\file.txt", "C:\\Code\\test\\file.txt", "\\");
            this->test_wpath(L"C:\\Code\\test", L"file", L".txt", L"C:\\Code\\test\\..\\test\\file.txt", L"C:\\Code\\test\\file.txt", L"\\");

            try {
                this->test_fuzzy();
            } catch (std::exception& ex) {
                std::cout << "EXCEPTION: " << ex.what() << std::endl;
            }
        }

    private:
        template < typename CHAR, typename STREAM >
        void print_list(const CHAR& vals, STREAM& ostr)
        {
            typename CHAR::const_iterator itr = vals.begin();
            while (itr != vals.end()) {
                ostr << '\'' << ((static_cast<int>(*itr) < 32) ? static_cast<int>(*itr) : *itr) << '\'';
                ++itr;
                if (itr != vals.end()) { ostr << ", "; }
            }
            ostr << std::endl;
        }

        void test_cfile(const std::string& path)
        {
            std::cout << "cfile:" << std::endl;
            this->test_file(path, std::cout);
            std::cout << std::endl;
        }
        void test_wfile(const std::wstring& path)
        {
            std::cout << "wfile:" << std::endl;
            this->test_file(path, std::wcout);
            std::cout << std::endl;
        }
        template < typename STR, typename OS >
        void test_file(const STR& path, OS& os)
        {
            try {
                STR file1 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file.txt"));
                STR file2 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file (copy).txt"));
                STR file3 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("other.txt"));
                STR file4 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("moved.txt"));
                STR file5 = omni::io::path::combine(omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("folder")), omni::string::util::lexical_cast<STR>("new_file.txt"));

                os << "copy " << (omni::io::file::copy(file1, file2) ? "success" : "fail") << ": '" << file1 << "' to '" << file2 << "'" << std::endl;
                os << "copy overwrite " << (omni::io::file::copy(file1, file2, true) ? "success" : "fail") << ": '" << file1 << "' to '" << file2 << "'" << std::endl;

                os << "create " << (omni::io::file::create(file3) ? "success" : "fail") << ": '" << file3 << "'" << std::endl;
                os << "create do path " << (omni::io::file::create(file3, true) ? "success" : "fail") << ": '" << file3 << "'" << std::endl;

                os << file1 << (omni::io::file::exists(file1) ? " " : " does not ") << "exists" << std::endl;
                os << file1 << (omni::io::file::exist(file1) ? " " : " does not ") << "exist" << std::endl;

                os << "moving '" << file3 << "' to '" << file4 << "': " << (omni::io::file::move(file3, file4) ? "success" : "fail") << std::endl;
                os << "moving create path '" << file4 << "' to '" << file5 << "': " << (omni::io::file::move(file4, file5, true) ? "success" : "fail") << std::endl;

                os << "removing '" << file5 << "': " << (omni::io::file::remove(file5) ? "success" : "fail") << std::endl;

                os << "renaming '" << file2 << "' to '" << file3 << "': " << (omni::io::file::move(file2, file3) ? "success" : "fail") << std::endl;
                os << "renaming create path '" << file3 << "' to '" << file5 << "': " << (omni::io::file::move(file3, file5, true) ? "success" : "fail") << std::endl;
                
                os << "writing to file '" << file1 << "', data '0123456789ABCDEF': " << omni::io::file::write(file1, omni::string::util::lexical_cast<STR>("0123456789ABCDEF"), false) << " bytes" << std::endl;
                os << "size of '" << file1 << "': " << omni::io::file::get_size(file1) << std::endl;
                os << "contents of '" << file1 << "': '" << omni::io::file::get_contents(file1) << "'" << std::endl;

                #if defined(OMNI_NON_PORTABLE)
                    os << "setting size of '" << file1 << "' to 256: " << omni::io::file::set_size(file1, 256) << std::endl;
                    os << "size of '" << file1 << "': " << omni::io::file::get_size(file1) << std::endl;
                #endif

                unsigned char ubuf[256] = {0};
                char buf[256] = {0};
                omni::seq::uchar_t ubuffer;
                omni::seq::char_t buffer;
                STR strbuf;

                os << "reading ubuf '" << file1 << "', read: " << omni::io::file::read(file1, ubuffer);
                os << " .. data size: '" << ubuffer.size() << "'" << std::endl;
                os << "reading buf '" << file1 << "', read: " << omni::io::file::read(file1, buffer);
                os << " .. data size: '" << buffer.size() << "'" << std::endl;
                os << "reading buf '" << file1 << "', read: " << omni::io::file::read(file1, strbuf);
                os << " .. data size: '" << strbuf.length() << "', data: '" << strbuf << "'" << std::endl;
                
                os << "reading raw ubuf '" << file1 << "', read: " << omni::io::file::read_raw(file1, ubuf, sizeof(ubuf)) << std::endl;;
                os << "reading raw buf '" << file1 << "', read: " << omni::io::file::read_raw(file1, buf, sizeof(buf)) << std::endl;

                os << "writing '" << file2 << "': " << omni::io::file::write(file2, ubuffer) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write(file2, buffer) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write(file2, strbuf) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write(file2, ubuffer, false) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write(file2, buffer, true) << " bytes" << std::endl;

                os << "writing '" << file2 << "': " << omni::io::file::write_raw(file2, ubuf, sizeof(ubuf)) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write_raw(file2, buf, sizeof(buf)) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write_raw(file2, ubuf, sizeof(ubuf), true) << " bytes" << std::endl;
                os << "writing '" << file2 << "': " << omni::io::file::write_raw(file2, buf, sizeof(buf), true) << " bytes" << std::endl;
                
                os << "writing line '" << file2 << "': " << omni::io::file::write_line(file2, ubuffer) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line(file2, buffer) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line(file2, strbuf) << " bytes" << std::endl;

                os << "writing line '" << file2 << "': " << omni::io::file::write_line(file2, ubuffer, true) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line(file2, buffer, true) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line(file2, strbuf, true) << " bytes" << std::endl;

                os << "writing line '" << file2 << "': " << omni::io::file::write_line_raw(file2, ubuf, sizeof(ubuf)) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line_raw(file2, buf, sizeof(buf)) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line_raw(file2, ubuf, sizeof(ubuf), true) << " bytes" << std::endl;
                os << "writing line '" << file2 << "': " << omni::io::file::write_line_raw(file2, buf, sizeof(buf), true) << " bytes" << std::endl;

                os << "removing '" << file2 << "': " << (omni::io::file::remove(file2) ? "success" : "fail") << std::endl;
                os << "removing '" << file3 << "': " << (omni::io::file::remove(file3) ? "success" : "fail") << std::endl;
                os << "removing '" << file4 << "': " << (omni::io::file::remove(file4) ? "success" : "fail") << std::endl;
                os << "removing '" << file5 << "': " << (omni::io::file::remove(file5) ? "success" : "fail") << std::endl;
            } catch (std::exception& ex) {
                std::cout << "EXCEPTION: " << ex.what() << std::endl;
            }
        }
        

        void test_cdir(const std::string& p1, const std::string& p2, const std::string& p3)
        {
            std::cout << "cdirectory:" << std::endl;
            this->test_dir(p1, p2, p3, std::cout);
            std::cout << std::endl;
        }
        void test_wdir(const std::wstring& p1, const std::wstring& p2, const std::wstring& p3)
        {
            std::wcout << "wdirectory:" << std::endl;
            this->test_dir(p1, p2, p3, std::wcout);
            std::wcout << std::endl;
        }
        template< typename STR, typename OS >
        void test_dir(const STR& p1, const STR& p2, const STR& p3, OS& os)
        {
            try {
                omni_sequence_t<STR> dirs = omni::io::directory::get_directories(p1);
                omni_sequence_t<STR> all_dirs = omni::io::directory::get_all_directories(p1);
                omni_sequence_t<STR> files = omni::io::directory::get_files(p1);
                omni_sequence_t<STR> all_files = omni::io::directory::get_all_files(p1);

                STR fldr = omni::string::util::lexical_cast<STR>("folder");
                STR two = omni::string::util::lexical_cast<STR>("2");
                STR tdir = omni::io::path::combine(p3, fldr);
                STR dir2 = omni::io::path::combine(p3, two);

                os << (omni::io::directory::copy(p1, p2, true) ? "successful" : "did not") << " copy: '" << p1 << "' to '" << p2 << "'" << std::endl;
                os << (omni::io::directory::copy(p1, (p2 + omni::string::util::lexical_cast<STR>(" (copy)"))) ? "successful" : "did not") << " copy: '" << p1 << "' to '" << p2 << " (copy)'" << std::endl;
                os << (omni::io::directory::create(tdir, true) ? "successful" : "did not") << " create: '" << tdir << "'" << std::endl;
                os << (omni::io::directory::create(dir2) ? "successful" : "did not") << " create: '" << dir2 << "'" << std::endl;
                os << p1 << " " << (omni::io::directory::exists(p1) ? "exists" : "does not exists") << std::endl;
                os << p1 << " " << (omni::io::directory::exist(p1) ? "exist" : "does not exists") << std::endl;

                os << (omni::io::directory::move(p2, tdir, true) ? "successful" : "did not") << " move: '" << p2 << "' to '" << tdir << "'" << std::endl;
                os << (omni::io::directory::move(tdir, dir2) ? "successful" : "did not") << " move: '" << tdir << "' to '" << dir2 << "'" << std::endl;

                os << (omni::io::directory::remove(dir2, true) ? "removed" : "did not remove") << " " << dir2 << std::endl;
                
                os << (omni::io::directory::copy(p1, p2, true) ? "successful" : "did not") << " copy: '" << p1 << "' to '" << p2 << "'" << std::endl;
                
                os << (omni::io::directory::rename(p2, dir2) ? "successful" : "did not") << " rename: '" << tdir << "' to '" << dir2 << "'" << std::endl;

                os << (omni::io::directory::remove(p3, true) ? "removed" : "did not remove") << " " << dir2 << std::endl;
            } catch (std::exception& ex) {
                std::cout << "EXCEPTION: " << ex.what() << std::endl;
            }
        }

        void test_cpath(const std::string& fpath, const std::string& cfile, const std::string& ext, const std::string& apath1, const std::string& apath2, const std::string& slash)
        {
            std::string file = cfile + ext;
            std::string cfull = omni::io::cpath::combine(fpath, file);
            std::cout << "--omni::io::cpath--" << std::endl;
            cpfunc2(omni::io::cpath::change_extension, file, "mp4");
            cpfunc2(omni::io::cpath::combine, fpath, file);
            cpfunc1(omni::io::cpath::get_extension, file);
            cpfunc1(omni::io::cpath::get_name, cfull);
            cpfunc1(omni::io::cpath::get_name_without_extension, cfull);
            cpfunc1(omni::io::cpath::get_parent_name, cfull);
            cpfunc1(omni::io::cpath::generate, fpath);
            cpfunc2(omni::io::cpath::generate, fpath, cfile);
            cpfunc3(omni::io::cpath::generate, fpath, cfile, ext);
            std::cout << "invalid file chars" << std::endl;
            print_list(omni::io::cpath::get_invalid_file_chars(), std::cout);
            print_list(omni::io::cpath::get_invalid_path_chars(), std::cout);
            cpfunc1(omni::io::cpath::has_extension, file);
            cpfunc1(omni::io::cpath::has_extension, cfile);
            cpfunc1(omni::io::cpath::is_path_absolute, apath1);
            cpfunc1(omni::io::cpath::is_path_absolute, apath2);
            cpfunc1(omni::io::cpath::trim_trailing_slash, fpath + slash);
            cpfunc1(omni::io::cpath::trim_trailing_slash, fpath);
        }
        void test_wpath(const std::wstring& fpath, const std::wstring& cfile, const std::wstring& ext, const std::wstring& apath1, const std::wstring& apath2, const std::wstring& slash)
        {
            // DEV_NOTE: the code just needs to have a BM, and all will be okie doke!! --Jennifer
            std::wstring file = cfile + ext;
            std::wstring cfull = omni::io::wpath::combine(fpath, file);
            std::wcout << "--omni::io::wpath--" << std::endl;
            wpfunc2(omni::io::wpath::change_extension, file, L"mp4");
            wpfunc2(omni::io::wpath::combine, fpath, file);
            wpfunc1(omni::io::wpath::get_extension, file);
            wpfunc1(omni::io::wpath::get_name, cfull);
            wpfunc1(omni::io::wpath::get_name_without_extension, cfull);
            wpfunc1(omni::io::wpath::get_parent_name, cfull);
            wpfunc1(omni::io::wpath::generate, fpath);
            wpfunc2(omni::io::wpath::generate, fpath, cfile);
            wpfunc3(omni::io::wpath::generate, fpath, cfile, ext);
            std::wcout << "invalid file wchars" << std::endl;
            print_list(omni::io::wpath::get_invalid_file_chars(), std::cout);
            print_list(omni::io::wpath::get_invalid_path_chars(), std::cout);
            wpfunc1(omni::io::wpath::has_extension, file);
            wpfunc1(omni::io::wpath::has_extension, cfile);
            wpfunc1(omni::io::wpath::is_path_absolute, apath1);
            wpfunc1(omni::io::wpath::is_path_absolute, apath2);
            wpfunc1(omni::io::wpath::trim_trailing_slash, fpath + slash);
            wpfunc1(omni::io::wpath::trim_trailing_slash, fpath);
        }
        void test_fuzzy()
        {
            std::cout << "--fuzz test--" << std::endl;
            cpfunc2(omni::io::cpath::change_extension, "test", "mp4");
            cpfunc2(omni::io::cpath::combine, "", "");
            cpfunc1(omni::io::cpath::get_extension, "test...booo");
            cpfunc1(omni::io::cpath::get_name, "test\\test/test");
            cpfunc1(omni::io::cpath::get_name_without_extension, "test");
            cpfunc1(omni::io::cpath::get_parent_name, "test//test\\test");
            cpfunc1(omni::io::cpath::generate, "test");
            cpfunc2(omni::io::cpath::generate, "test", "test");
            cpfunc3(omni::io::cpath::generate, "test", "", "test");
            cpfunc1(omni::io::cpath::is_path_absolute, "test\\test");
            cpfunc1(omni::io::cpath::is_path_absolute, "/test\\test");
            cpfunc1(omni::io::cpath::is_path_absolute, "/test\\../test");
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
