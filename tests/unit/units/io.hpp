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
            omni::application::signal_handler::attach(&app_signal);

            std::string cpath; 
            std::wstring wpath;
            #if defined(OMNI_OS_WIN)
                cpath = "C:\\Code\\test"; wpath = L"C:\\Code\\test";
            #else
                cpath = "/Code/test"; wpath = L"/Code/test";
            #endif
            this->test_cfile(cpath);
            std::cout << std::endl;
            this->test_wfile(wpath);
        }

        void directory()
        {
            omni::application::signal_handler::attach(&app_signal);

            std::string cpath, cfpath, ctpath;
            std::wstring wpath, wfpath, wtpath;
            #if defined(OMNI_OS_WIN)
                cfpath = "C:\\Code\\omni\\source"; ctpath = "C:\\Code\\test\\omni_source"; cpath = "C:\\Code\\test";
                wfpath = L"C:\\Code\\omni\\source"; wtpath = L"C:\\Code\\test\\omni_source"; wpath = L"C:\\Code\\test";
            #else
                cfpath = "/Code/omni/source"; ctpath = "/Code/test/omni_source"; cpath = "/Code/test";
                wfpath = L"/Code/omni/source"; wtpath = L"/Code/test/omni_source"; wpath = L"/Code/test";
            #endif
            this->test_cdir(cfpath, ctpath, cpath);
            std::cout << std::endl;
            this->test_wdir(wfpath, wtpath, wpath);
        }

        void path()
        {
            omni::application::signal_handler::attach(&app_signal);

            std::cout << "Testing *nix file paths" << std::endl;

            this->test_cpath("/Code/test", "file", ".txt", "/Code/test/../test/file.txt", "/Code/test/file.txt", "/");
            this->test_wpath(L"/Code/test", L"file", L".txt", L"/Code/test/../test/file.txt", L"/Code/test/file.txt", L"/");

            std::cout << std::endl << "Testing Windows file paths" << std::endl;

            this->test_cpath("C:\\Code\\test", "file", ".txt", "C:\\Code\\test\\..\\test\\file.txt", "C:\\Code\\test\\file.txt", "\\");
            this->test_wpath(L"C:\\Code\\test", L"file", L".txt", L"C:\\Code\\test\\..\\test\\file.txt", L"C:\\Code\\test\\file.txt", L"\\");

            try {
                this->test_fuzzy();
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

        template < typename CHAR, typename STREAM >
        void print_list(const CHAR& vals, STREAM& ostr)
        {
            typename CHAR::const_iterator itr = vals.begin();
            while (itr != vals.end()) {
                ostr << '\'' << ((static_cast<int>(*itr) < 32) ? static_cast<int>(*itr) : *itr) << '\'';
                ++itr;
                if (itr != vals.end()) { ostr << ", "; }
            }
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
            STR file1 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file.txt"));
            STR file2 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("file (copy).txt"));
            STR file3 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("other.txt"));
            STR file4 = omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("moved.txt"));
            STR file5 = omni::io::path::combine(omni::io::path::combine(path, omni::string::util::lexical_cast<STR>("folder")), omni::string::util::lexical_cast<STR>("new_file.txt"));
            
            TC(os << "copy " << (omni::io::file::copy(file1, file2) ? "success" : "fail") << ": '" << file1 << "' to '" << file2 << "'" << std::endl, "copy");
            TC(os << "copy overwrite " << (omni::io::file::copy(file1, file2, true) ? "success" : "fail") << ": '" << file1 << "' to '" << file2 << "'" << std::endl, "copy overwrite");
            TC(os << "create " << (omni::io::file::create(file3) ? "success" : "fail") << ": '" << file3 << "'" << std::endl, "create");
            TC(os << "create do create_path=true " << (omni::io::file::create(file3, true) ? "success" : "fail") << ": '" << file3 << "'" << std::endl, "create do create_path=true ");

            os << file1 << (omni::io::file::exists(file1) ? " " : " does not ") << "exists" << std::endl;
            os << file1 << (omni::io::file::exist(file1) ? " " : " does not ") << "exist" << std::endl;

            TC(os << "moving '" << file3 << "' to '" << file4 << "': " << (omni::io::file::move(file3, file4) ? "success" : "fail") << std::endl, "moving");
            TC(os << "moving create_path=true '" << file4 << "' to '" << file5 << "': " << (omni::io::file::move(file4, file5, true) ? "success" : "fail") << std::endl, "moving create_path=true");

            TC(os << "removing '" << file5 << "': " << (omni::io::file::remove(file5) ? "success" : "fail") << std::endl, "removing");

            TC(os << "renaming '" << file2 << "' to '" << file3 << "': " << (omni::io::file::move(file2, file3) ? "success" : "fail") << std::endl, "renaming");
            TC(os << "renaming create_path=true '" << file3 << "' to '" << file5 << "': " << (omni::io::file::move(file3, file5, true) ? "success" : "fail") << std::endl, "renaming create_path=true");
            
            TC(os << "writing to file '" << file1 << "', data '0123456789ABCDEF': " << omni::io::file::write(file1, omni::string::util::lexical_cast<STR>("0123456789ABCDEF"), false) << " bytes" << std::endl, "writing to file1");
            TC(os << "size of '" << file1 << "': " << omni::io::file::get_size(file1) << std::endl, "size of error");
            TC(os << "contents of '" << file1 << "': '" << omni::io::file::get_contents(file1) << "'" << std::endl, "contents of error");

            #if defined(OMNI_NON_PORTABLE)
                os << "setting size of '" << file1 << "' to 256: " << omni::io::file::set_size(file1, 256) << std::endl;
                os << "size of '" << file1 << "': " << omni::io::file::get_size(file1) << std::endl;
            #endif

            TC(this->test_file_read(path, os, file1), "test_file_read error");
            TC(this->test_file_write(path, os, file1, file2), "test_file_write error");

            TC(os << "removing '" << file2 << "': " << (omni::io::file::remove(file2) ? "success" : "fail") << std::endl, "removing file2");
            TC(os << "removing '" << file3 << "': " << (omni::io::file::remove(file3) ? "success" : "fail") << std::endl, "removing file3");
            TC(os << "removing '" << file4 << "': " << (omni::io::file::remove(file4) ? "success" : "fail") << std::endl, "removing file4");
            TC(os << "removing '" << file5 << "': " << (omni::io::file::remove(file5) ? "success" : "fail") << std::endl, "removing file5");
            
            std::cout << "done.." << std::endl;
        }
        template < typename STR, typename OS >
        void test_file_read(const STR& path, OS& os, const STR& file1)
        {
            uint8_t ubuf[256] = {0};
            char buf[256] = {0};
            wchar_t wbuf[256] = {0};
            omni::seq::uint8_t ubuffer;
            omni::seq::char_t buffer;
            omni::seq::wide_char_t wbuffer;
            STR strbuf;

            os << "reading ubuf '" << file1 << "', read: " << omni::io::file::read(file1, ubuffer);
            os << " .. data size: '" << ubuffer.size() << "', data: '";
            print_list(ubuffer, os); os << "'" << std::endl;

            os << "reading buf '" << file1 << "', read: " << omni::io::file::read(file1, buffer);
            os << " .. data size: '" << buffer.size() << "', data: '";
            print_list(buffer, os); os << "'" << std::endl;

            os << "reading wbuf '" << file1 << "', read: " << omni::io::file::read(file1, wbuffer);
            os << " .. data size: '" << wbuffer.size() << "', data: '";
            print_list(wbuffer, os); os << "'" << std::endl;

            os << "reading strbuf '" << file1 << "', read: " << omni::io::file::read(file1, strbuf);
            os << " .. data size: '" << strbuf.length() << "', data: '" << strbuf << "'" << std::endl;
            
            os << "reading raw ubuf '" << file1 << "', read: " << omni::io::file::unsafe_read(file1, ubuf, sizeof(ubuf)) << std::endl;;
            os << "ubuf data: '" << ubuf << "'" << std::endl;

            os << "reading raw buf '" << file1 << "', read: " << omni::io::file::unsafe_read(file1, buf, sizeof(buf)) << std::endl;
            os << "buf data: '" << buf << "'" << std::endl;

            os << "reading raw wbuf '" << file1 << "', read: " << omni::io::file::unsafe_read(file1, wbuf, sizeof(wbuf)) << std::endl;
            os << "wbuf data: '" << wbuf << "'" << std::endl;
        }
        template < typename STR, typename OS >
        void test_file_write(const STR& path, OS& os, const STR& file1, const STR& file2)
        {
            uint8_t ubuf[256] = {0};
            char buf[256] = {0};
            wchar_t wbuf[256] = {0};
            omni::seq::uint8_t ubuffer;
            omni::seq::char_t buffer;
            omni::seq::wide_char_t wbuffer;
            STR strbuf;
            omni::io::file::read(file1, ubuffer);
            omni::io::file::read(file1, buffer);
            omni::io::file::read(file1, wbuffer);
            omni::io::file::read(file1, strbuf);
            omni::io::file::unsafe_read(file1, ubuf, sizeof(ubuf));
            omni::io::file::unsafe_read(file1, buf, sizeof(buf));
            omni::io::file::unsafe_read(file1, wbuf, sizeof(wbuf)/sizeof(wchar_t));
            os << "writing to '" << file2 << "'" << std::endl;

            os << "writing ubuf: " << omni::io::file::write(file2, ubuffer) << " bytes" << std::endl;
            os << "writing buf: " << omni::io::file::write(file2, buffer) << " bytes" << std::endl;
            os << "writing wbuf: " << omni::io::file::write(file2, wbuffer) << " bytes" << std::endl;
            os << "writing strbuf: " << omni::io::file::write(file2, strbuf) << " bytes" << std::endl;
            os << "writing ubuf append: " << omni::io::file::write(file2, ubuffer, true) << " bytes" << std::endl;
            os << "writing buf append: " << omni::io::file::write(file2, buffer, true) << " bytes" << std::endl;
            os << "writing wbuf append: " << omni::io::file::write(file2, wbuffer, true) << " bytes" << std::endl;
            os << "writing strbuf append: " << omni::io::file::write(file2, strbuf, true) << " bytes" << std::endl;

            os << "writing raw ubuf: " << omni::io::file::unsafe_write(file2, ubuf, sizeof(ubuf)) << " bytes" << std::endl;
            os << "writing raw buf: " << omni::io::file::unsafe_write(file2, buf, sizeof(buf)) << " bytes" << std::endl;
            os << "writing raw wbuf: " << omni::io::file::unsafe_write(file2, wbuf, sizeof(wbuf)/sizeof(wchar_t)) << " bytes" << std::endl;
            os << "writing raw ubuf append: " << omni::io::file::unsafe_write(file2, ubuf, sizeof(ubuf), true) << " bytes" << std::endl;
            os << "writing raw buf append: " << omni::io::file::unsafe_write(file2, buf, sizeof(buf), true) << " bytes" << std::endl;
            os << "writing raw wbuf append: " << omni::io::file::unsafe_write(file2, wbuf, sizeof(wbuf)/sizeof(wchar_t), true) << " bytes" << std::endl;
            
            os << "writing line ubuf: " << omni::io::file::write_line(file2, ubuffer) << " bytes" << std::endl;
            os << "writing line buf: " << omni::io::file::write_line(file2, buffer) << " bytes" << std::endl;
            os << "writing line wbuf: " << omni::io::file::write_line(file2, wbuffer) << " bytes" << std::endl;
            os << "writing line strbuf: " << omni::io::file::write_line(file2, strbuf) << " bytes" << std::endl;

            os << "writing line ubuf append: " << omni::io::file::write_line(file2, ubuffer, true) << " bytes" << std::endl;
            os << "writing line buf append: " << omni::io::file::write_line(file2, buffer, true) << " bytes" << std::endl;
            os << "writing line wbuf append: " << omni::io::file::write_line(file2, wbuffer, true) << " bytes" << std::endl;
            os << "writing line strbuf append: " << omni::io::file::write_line(file2, strbuf, true) << " bytes" << std::endl;

            os << "writing line raw ubuf: " << omni::io::file::unsafe_write_line(file2, ubuf, sizeof(ubuf)) << " bytes" << std::endl;
            os << "writing line raw buf: " << omni::io::file::unsafe_write_line(file2, buf, sizeof(buf)) << " bytes" << std::endl;
            os << "writing line raw wbuf: " << omni::io::file::unsafe_write_line(file2, wbuf, sizeof(wbuf)/sizeof(wchar_t)) << " bytes" << std::endl;
            os << "writing line raw ubuf append: " << omni::io::file::unsafe_write_line(file2, ubuf, sizeof(ubuf), true) << " bytes" << std::endl;
            os << "writing line raw buf append: " << omni::io::file::unsafe_write_line(file2, buf, sizeof(buf), true) << " bytes" << std::endl;
            os << "writing line raw wbuf append: " << omni::io::file::unsafe_write_line(file2, wbuf, sizeof(wbuf)/sizeof(wchar_t), true) << " bytes" << std::endl;
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
                // cfpath = "/Code/omni/source"; ctpath = "/Code/test/omni_source"; cpath = "/Code/test";
                omni_sequence_t<STR> dirs = omni::io::directory::get_directories(p1);
                omni_sequence_t<STR> all_dirs = omni::io::directory::get_all_directories(p1);
                omni_sequence_t<STR> files = omni::io::directory::get_files(p1);
                omni_sequence_t<STR> all_files = omni::io::directory::get_all_files(p1);

                os << "directory count for '" << p1 << "' = " << dirs.size() << std::endl;
                os << "all directories count for '" << p1 << "' = " << all_dirs.size() << std::endl;
                os << "file count for '" << p1 << "' = " << files.size() << std::endl;
                os << "all files count for '" << p1 << "' = " << all_files.size() << std::endl;

                STR fldr = omni::string::util::lexical_cast<STR>("folder");
                STR two = omni::string::util::lexical_cast<STR>("x2x");
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
                
                os << (omni::io::directory::rename(p2, dir2) ? "successful" : "did not") << " rename: '" << p2 << "' to '" << dir2 << "'" << std::endl;

                os << (omni::io::directory::remove(dir2, true) ? "removed" : "did not remove") << " " << dir2 << std::endl;

                os << (omni::io::directory::remove((p2 + omni::string::util::lexical_cast<STR>(" (copy)")), true) ? "removed" : "did not remove") << " " << p2 << " (copy)'" << std::endl;
            } catch (std::exception& ex) {
                std::cout << "EXCEPTION: " << ex.what() << std::endl;
            }
        }

        void test_cpath(const std::string& fpath, const std::string& cfile, const std::string& ext, const std::string& apath1, const std::string& apath2, const std::string& slash)
        {
            std::string file = cfile + ext;
            std::string cfull = omni::io::cpath::combine(fpath, file);
            std::cout << "--omni::io::cpath--" << std::endl;
            cpfuncex2(omni::io::cpath::change_extension, file, "mp4", (cfile + ".mp4"));
            cpfuncex2(omni::io::cpath::combine, fpath, file, (fpath + slash + file)); 
            cpfuncex1(omni::io::cpath::get_extension, file, ext.substr(1));
            cpfuncex1(omni::io::cpath::get_name, cfull, file);
            cpfuncex1(omni::io::cpath::get_name_without_extension, cfull, cfile);
            cpfuncex1(omni::io::cpath::get_parent_name, cfull, fpath);
            cpfunc1(omni::io::cpath::generate, fpath);
            cpfunc2(omni::io::cpath::generate, fpath, cfile);
            cpfunc3(omni::io::cpath::generate, fpath, cfile, ext);
            std::cout << "invalid file chars:" << std::endl;
            print_list(omni::io::cpath::get_invalid_file_chars(), std::cout); std::cout << std::endl;
            std::cout << "invalid path chars:" << std::endl;
            print_list(omni::io::cpath::get_invalid_path_chars(), std::cout); std::cout << std::endl;
            cpfuncex1(omni::io::cpath::has_extension, file, true);
            cpfuncex1(omni::io::cpath::has_extension, cfile, false);
            cpfuncex1(omni::io::cpath::is_path_absolute, apath1, false);
            cpfuncex1(omni::io::cpath::is_path_absolute, apath2, true);
            cpfuncex1(omni::io::cpath::trim_trailing_slash, fpath + slash, fpath);
            cpfuncex1(omni::io::cpath::trim_trailing_slash, fpath, fpath);
        }
        void test_wpath(const std::wstring& fpath, const std::wstring& cfile, const std::wstring& ext, const std::wstring& apath1, const std::wstring& apath2, const std::wstring& slash)
        {
            // DEV_NOTE: the code just needs to have a BM, and all will be okie doke!! --Jennifer
            std::wstring file = cfile + ext;
            std::wstring cfull = omni::io::wpath::combine(fpath, file);
            std::wcout << "--omni::io::wpath--" << std::endl;
            wpfuncex2(omni::io::wpath::change_extension, file, L"mp4", (cfile + L".mp4"));
            wpfuncex2(omni::io::wpath::combine, fpath, file, (fpath + slash + file)); 
            wpfuncex1(omni::io::wpath::get_extension, file, ext.substr(1));
            wpfuncex1(omni::io::wpath::get_name, cfull, file);
            wpfuncex1(omni::io::wpath::get_name_without_extension, cfull, cfile);
            wpfuncex1(omni::io::wpath::get_parent_name, cfull, fpath);
            wpfunc1(omni::io::wpath::generate, fpath);
            wpfunc2(omni::io::wpath::generate, fpath, cfile);
            wpfunc3(omni::io::wpath::generate, fpath, cfile, ext);
            std::wcout << "invalid file chars:" << std::endl;
            print_list(omni::io::wpath::get_invalid_file_chars(), std::wcout); std::wcout << std::endl;
            std::wcout << "invalid path chars:" << std::endl;
            print_list(omni::io::wpath::get_invalid_path_chars(), std::wcout); std::wcout << std::endl;
            wpfuncex1(omni::io::wpath::has_extension, file, true);
            wpfuncex1(omni::io::wpath::has_extension, cfile, false);
            wpfuncex1(omni::io::wpath::is_path_absolute, apath1, false);
            wpfuncex1(omni::io::wpath::is_path_absolute, apath2, true);
            wpfuncex1(omni::io::wpath::trim_trailing_slash, fpath + slash, fpath);
            wpfuncex1(omni::io::wpath::trim_trailing_slash, fpath, fpath);
        }
        void test_fuzzy()
        {
            std::cout << "--fuzz test--" << std::endl;
            cpfuncex2(omni::io::cpath::change_extension, "test", "mp4", "test.mp4");
            cpfuncex2(omni::io::cpath::combine, "", "", "");
            cpfuncex1(omni::io::cpath::get_extension, "test...booo", "booo");
            cpfuncex1(omni::io::cpath::get_name, "test1\\test2/test3", "test3");
            cpfuncex1(omni::io::cpath::get_name_without_extension, "test", "test");
            cpfuncex1(omni::io::cpath::get_parent_name, "test//test\\test", "test//test");
            cpfunc1(omni::io::cpath::generate, "test");
            cpfunc2(omni::io::cpath::generate, "test", "test");
            cpfunc3(omni::io::cpath::generate, "test", "", "test");
            cpfuncex1(omni::io::cpath::is_path_absolute, "test\\test", false);
            cpfuncex1(omni::io::cpath::is_path_absolute, "/test\\test", true);
            cpfuncex1(omni::io::cpath::is_path_absolute, "/test\\../test", false);
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_TESTNAME
