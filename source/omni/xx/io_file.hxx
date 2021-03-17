/*
 * Copyright (c), Zeriph Enterprises
 * All rights reserved.
 * 
 * Contributor(s):
 * Zechariah Perez, omni (at) zeriph (dot) com
 * 
 * THIS SOFTWARE IS PROVIDED BY ZERIPH AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ZERIPH AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. do not #include <omni/xxx_impl.hxx> and do not compile this source directly.
 this file is included directly in other source.
*/

// so as not to accidentally build this file with the source this macro is defined in io.cpp
#if !defined(OMNI_IO_FILE_FW) || !defined(OMNI_PATH_FW) || !defined(OMNI_L_FW) || !defined(OMNI_STRING_T_FW)
    #error invalid preprocessor directive detected
#endif

#if defined(OMNI_IO_FILE_INTERNAL_FW)
    namespace omni {
    namespace io {
    /** @internal library helper */
    namespace file_internal {

    #if defined(OMNI_OS_WIN)
        /* DEV_NOTE: this code is Windows only .. it returns the short/long path name for a file
        but that is largely irrelevant as it only returns an 8.3 short path name if it is enabled
        in the registry for above Windows XP. Since this is a one-off type of thing and likely
        not largely used, this will not be exposed or documented beyond this file scope. */

        /** @internal library helper */
        std::string get_path_name(const std::string& file)
        {
            std::string name = "\\\\?\\";
            long length = ::GetShortPathNameA(file.c_str(), NULL, 0);
            if (length > 0) {
                char* buffer = new char[length];
                length = ::GetShortPathNameA(file.c_str(), buffer, length);
                if (length > 0) {
                    std::string npath(buffer);
                    delete[] buffer;
                    name += npath;
                } else {
                    delete[] buffer;
                }
            } else {
                name += file;
            }
            return name;
        }

        /** @internal library helper */
        std::wstring get_path_name(const std::wstring& file)
        {
            std::wstring name = L"\\\\?\\";
            long length = ::GetShortPathNameW(file.c_str(), NULL, 0);
            if (length > 0) {
                wchar_t* buffer = new wchar_t[length];
                length = ::GetShortPathNameW(file.c_str(), buffer, length);
                if (length > 0) {
                    std::wstring npath(buffer);
                    delete[] buffer;
                    name += npath;
                } else {
                    delete[] buffer;
                }
            } else {
                name += file;
            }
            return name;
        }

        /** @internal library helper */
        bool win_copy_file(const std::string& file, const std::string& new_name)
        {
            OMNI_FILE_CHECKA_FW(file, false)
            OMNI_FILE_CHECKA_FW(new_name, false)
            BOOL res = ::CopyFileA(file.c_str(), new_name.c_str(), FALSE); // don't fail if exists (e.g. overwrite)
            if (res == 0) {
                if (OMNI_GLE == ERROR_FILE_NOT_FOUND) {
                    OMNI_ERRV_RETV_FW(OMNI_FILE_NOT_FOUND_STR, omni::string::to_string_t(file), omni::exceptions::file_not_found(omni::string::to_string(file)), false);
                } else {
                    std::string ex = OMNI_PATH_NOT_ACCESSIBLE_STR;
                    ex += omni::string::util::to_string(OMNI_GLE);
                    OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string_t(file), omni::exceptions::path_exception(ex, file), false)
                }
            }
            return true;
        }

        /** @internal library helper */
        bool win_copy_file(const std::wstring& file, const std::wstring& new_name)
        {
            std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
            std::wstring nf = OMNI_FILE_CHECKW_FW(nf, new_name, false)
            BOOL res = ::CopyFileW(tf.c_str(), nf.c_str(), FALSE); // don't fail if exists (e.g. overwrite)
            if (res == 0) {
                if (OMNI_GLE == ERROR_FILE_NOT_FOUND) {
                    OMNI_ERRV_RETV_FW(OMNI_FILE_NOT_FOUND_STR, omni::string::to_string_t(file), omni::exceptions::file_not_found(omni::string::to_string(file)), false);
                } else {
                    std::string ex = OMNI_PATH_NOT_ACCESSIBLE_STR;
                    ex += omni::string::util::to_string(OMNI_GLE);
                    OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string_t(file), omni::exceptions::path_exception(ex, omni::string::to_string(file)), false)
                }
            }
            return true;
        }
    #endif
    
    /** @internal library helper */
    template < typename STR, typename ISTREAM, typename OSTREAM >
    bool copy(const STR& file, const STR& new_name)
    {
        #if defined(OMNI_IO_FILE_COPY_USE_FSTREAM)
            ISTREAM src(omni::string::to_string(file).c_str(), std::ios::binary);
            if (!src.is_open()) {
                src.close();
                OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string_t(file), omni::exceptions::path_exception(OMNI_PATH_NOT_ACCESSIBLE_STR,omni::string::to_string(file)), false)
            }
            OSTREAM dst(omni::string::to_string(new_name).c_str(), std::ios::binary);
            if (!dst.is_open()) {
                src.close();
                dst.close();
                OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string_t(new_name), omni::exceptions::path_exception(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string(new_name)), false)
            }
            dst << src.rdbuf();
            src.close();
            dst.close();
            return true;
        #else
            #if defined(OMNI_OS_WIN)
                return win_copy_file(file, new_name);
            #else
                char buf[OMNI_IO_FILE_COPY_BUFSZ];
                size_t size;
                int src = ::open(omni::string::to_string(file).c_str(), O_RDONLY, 0);
                if (src == -1) {
                    ::close(src);
                    OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string_t(file), omni::exceptions::path_exception(OMNI_PATH_NOT_ACCESSIBLE_STR,omni::string::to_string(file)), false)
                }
                int dst = ::open(omni::string::to_string(new_name).c_str(), O_WRONLY | O_CREAT); // | O_TRUNC);
                if (dst == -1) {
                    ::close(src);
                    ::close(dst);
                    OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string_t(new_name), omni::exceptions::path_exception(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::to_string(new_name)), false)
                }
                while ((size = ::read(src, buf, BUFSIZ)) > 0) {
                    ::write(dst, buf, size);
                }
                ::close(src);
                ::close(dst);
                return true;
            #endif
        #endif
    }
    /** @internal library helper */
    bool copy(const std::string& file, const std::string& new_name)
    {
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            OMNI_FILE_CHECKA_FW(file, false)
            if (::CopyFileA(file.c_str(), new_name.c_str(), FALSE) == 0) {
                OMNI_DBGEV("error copying file: ", omni::string::to_string_t(omni::system::last_error_str()));
                return false;
            }
            return omni::io::file_internal::exists(new_name);
        #else
            return omni::io::file_internal::copy<std::string, std::ifstream, std::ofstream>(file, new_name);
        #endif
    }
    /** @internal library helper */
    bool copy(const std::wstring& file, const std::wstring& new_name)
    {
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
            std::wstring nf = OMNI_FILE_CHECKW_FW(nf, new_name, false)
            if (::CopyFileW(tf.c_str(), nf.c_str(), FALSE) == 0) {
                OMNI_DBGEV("error copying file: ", omni::string::to_string_t(omni::system::last_error_str()));
                return false;
            }
            return omni::io::file_internal::exists(new_name);
        #else
            return omni::io::file_internal::copy<std::wstring, std::wifstream, std::wofstream>(file, new_name);
        #endif
    }

    /** @internal library helper */
    template < typename STR, typename OSTREAM >
    bool create(const STR& file, const omni::io::options& io_ops)
    {
        bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
        STR parent = omni::io::path::get_parent_name(file);
        if (create_path && !omni::io::directory::exists(parent)) {
            if (!omni::io::directory::create(parent)) {
                return false;
            }
        }
        OSTREAM out(omni::string::to_string(file).c_str(), std::ios::binary|std::ios::out);
        out.close(); // close/flush
        return omni::io::file_internal::exists(file);
    }
    /** @internal library helper */
    bool create(const std::string& file, const omni::io::options& io_ops)
    {
        bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            if (create_path) {
                std::string parent = omni::io::path::get_parent_name(file);
                if (create_path && !omni::io::directory::exists(parent)) {
                    if (!omni::io::directory::create(parent)) {
                        return false;
                    }
                }
            }
            OMNI_FILE_CHECKA_FW(file, false)
            HANDLE hfile = ::CreateFileA(file.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                       CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hfile == INVALID_HANDLE_VALUE) {
                OMNI_DBGEV("error creating file: ", omni::system::last_error_str().c_str())
                return false;
            }
            ::CloseHandle(hfile);
            return omni::io::file_internal::exists(file);
        #else
            return omni::io::file_internal::create<std::string, std::ofstream>(file, create_path);
        #endif
    }
    /** @internal library helper */
    bool create(const std::wstring& file, const omni::io::options& io_ops)
    {
        bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            if (create_path) {
                std::wstring parent = omni::io::path::get_parent_name(file);
                if (create_path && !omni::io::directory::exists(parent)) {
                    if (!omni::io::directory::create(parent)) {
                        return false;
                    }
                }
            }
            std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
            HANDLE hfile = ::CreateFileW(tf.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                     CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hfile == INVALID_HANDLE_VALUE) {
                OMNI_DBGEV("error creating file: ", omni::system::last_error_str().c_str())
                return false;
            }
            ::CloseHandle(hfile);
            return omni::io::file_internal::exists(file);
        #else
            return omni::io::file_internal::create<std::wstring, std::wofstream>(file, create_path);
        #endif
    }

    /** @internal library helper */
    template < typename STR, typename ISTRM, typename SSTRM >
    STR get_contents(const STR& file)
    {
        ISTRM ifile(omni::string::to_string(file).c_str());
        SSTRM buf;
        buf << ifile.rdbuf();
        return buf.str();
    }
    /** @internal library helper */
    std::string get_contents(const std::string& file)
    {
        return get_contents<std::string, std::ifstream, std::stringstream>(file);
    }
    /** @internal library helper */
    std::wstring get_contents(const std::wstring& file)
    {
        return get_contents<std::wstring, std::wifstream, std::wstringstream>(file);
    }

    /** @internal library helper */
    uint64_t get_size(const std::string& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, 0)
                WIN32_FILE_ATTRIBUTE_DATA finfo;
                if (::GetFileAttributesExA(file.c_str(), GetFileExInfoStandard, &finfo) == 0) {
                    return 0;
                }
                LARGE_INTEGER sz;
                sz.HighPart = finfo.nFileSizeHigh;
                sz.LowPart = finfo.nFileSizeLow;
                return static_cast<uint64_t>(sz.QuadPart);
            #else
                struct stat fi;
                if (::_stat(file.c_str(), &fi) == 0) {
                    return static_cast<uint64_t>(fi.st_size);
                }
                return 0;
            #endif
        #else
            struct stat fi;
            if (::stat(file.c_str(), &fi) == 0) {
                return static_cast<uint64_t>(fi.st_size);
            }
            return 0;
        #endif
    }
    /** @internal library helper */
    uint64_t get_size(const std::wstring& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, 0)
                WIN32_FILE_ATTRIBUTE_DATA finfo;
                if (::GetFileAttributesExW(tf.c_str(), GetFileExInfoStandard, &finfo) == 0) {
                    return 0;
                }
                LARGE_INTEGER sz;
                sz.HighPart = finfo.nFileSizeHigh;
                sz.LowPart = finfo.nFileSizeLow;
                return static_cast<uint64_t>(sz.QuadPart);
            #else
                struct stat fi;
                if (::_wstat(file.c_str(), &fi) == 0) {
                    return static_cast<uint64_t>(fi.st_size);
                }
                return 0;
            #endif
        #else
            struct stat fi;
            if (::stat(omni::string::to_string(file).c_str(), &fi) == 0) {
                return static_cast<uint64_t>(fi.st_size);
            }
            return 0;
        #endif
    }

    /** @internal library helper */
    bool mv(const std::string& file, const std::string& new_name, const omni::io::options& io_ops)
    {
        bool overwrite = ((io_ops & omni::io::options::OVERWRITE) == omni::io::options::OVERWRITE);
        bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
        if (!omni::io::cfile::exists(file)) {
            OMNI_DV1_FW("file does not exists:", file);
            return false;
        }
        if (!overwrite && omni::io::file_internal::exists(new_name)) {
            OMNI_DBGEV("New path already exists: ", omni::string::to_string_t(new_name));
            return false;
        }
        std::string root = omni::io::cpath::get_parent_name(new_name);
        if (!omni::io::cdirectory::exists(root)) {
            if (create_path) {
                if (!omni::io::cdirectory::create(root, true)) {
                    OMNI_D1_FW("could not create parent directory");
                    return false;
                }
            } else {
                OMNI_D1_FW("error moving file: new path does not exist");
                return false;
            }
        }
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, false)
                OMNI_FILE_CHECKA_FW(new_name, false)
                BOOL ret = ::MoveFileA(file.c_str(), new_name.c_str());
                if (ret == 0) {
                    OMNI_DV1_FW("error moving file: ", omni::system::last_error_str().c_str());
                    return false;
                }
            #else
                int ret = ::_rename(file.c_str(), new_name.c_str());
                if (ret != 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                    return false;
                }
            #endif
        #else
            int ret = ::rename(file.c_str(), new_name.c_str());
            if (ret != 0) {
                OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                return false;
            }
        #endif
        return omni::io::file_internal::exists(new_name);
    }
    /** @internal library helper */
    bool mv(const std::wstring& file, const std::wstring& new_name, const omni::io::options& io_ops)
    {
        bool overwrite = ((io_ops & omni::io::options::OVERWRITE) == omni::io::options::OVERWRITE);
        bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
        if (!omni::io::wfile::exists(file)) {
            OMNI_DV1_FW("file does not exists:", omni::string::to_string_t(file));
            return false;
        }
        if (!overwrite && omni::io::file_internal::exists(new_name)) {
            OMNI_DBGEV("New path already exists: ", omni::string::to_string_t(new_name));
            return false;
        }
        std::wstring root = omni::io::wpath::get_parent_name(new_name);
        if (!omni::io::wdirectory::exists(root)) {
            if (create_path) {
                if (!omni::io::wdirectory::create(root, true)) {
                    OMNI_D1_FW("could not create parent directory");
                    return false;
                }
            } else {
                OMNI_D1_FW("error moving file: new path does not exist");
                return false;
            }
        }
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
                std::wstring nf = OMNI_FILE_CHECKW_FW(nf, new_name, false)
                BOOL ret = ::MoveFileW(tf.c_str(), nf.c_str());
                if (ret == 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::last_error_str()));
                    return false;
                }
            #else
                int ret = ::_wrename(file.c_str(), new_name.c_str());
                if (ret != 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                    return false;
                }
            #endif
        #else
            int ret = ::rename(omni::string::to_string(file).c_str(), omni::string::to_string(new_name).c_str());
            if (ret != 0) {
                OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                return false;
            }
        #endif
        return omni::io::file_internal::exists(new_name);
    }

    /** @internal library helper */
    template < typename STR, typename IFSTREAM >
    uint64_t rd_f(const STR& file, STR& buffer)
    {
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        uint64_t length = static_cast<uint64_t>(ifile.tellg());
        ifile >> buffer;
        length = static_cast<uint64_t>(ifile.tellg()) - length;
        ifile.close();
        return length;
    }
    /** @internal library helper */
    uint64_t read(const std::string& file, std::string& buffer)
    {
        return omni::io::file_internal::rd_f<std::string, std::ifstream>(file, buffer);
    }
    /** @internal library helper */
    uint64_t read(const std::wstring& file, std::wstring& buffer)
    {
        return omni::io::file_internal::rd_f<std::wstring, std::wifstream>(file, buffer);
    }

    /** @internal library helper */
    template < typename STR, typename IFSTREAM, typename SEQ >
    uint64_t unsafe_rd(const STR& file, SEQ* buffer, uint64_t blen)
    {
        if ((blen == 0) || (buffer == OMNI_NULL)) { return 0; }
        IFSTREAM ifile(omni::string::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        ifile.seekg(0, ifile.end);
        uint64_t length = static_cast<uint64_t>(ifile.tellg());
        ifile.seekg(0, ifile.beg);
        if (length > blen) { length = blen; }
        ifile.read(reinterpret_cast<typename IFSTREAM::char_type*>(buffer), static_cast<std::streamsize>(length));
        length = static_cast<uint64_t>(ifile.gcount());
        ifile.close();
        return length;
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::string& file, char* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, char>(file, buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::wstring& file, char* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, char>(omni::string::to_string(file), buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::string& file, wchar_t* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, wchar_t>(file, buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::wstring& file, wchar_t* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, wchar_t>(omni::string::to_string(file), buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::string& file, uint8_t* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, uint8_t>(file, buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::wstring& file, uint8_t* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, uint8_t>(omni::string::to_string(file), buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::string& file, int8_t* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, int8_t>(file, buffer, length);
    }
    /** @internal library helper */
    uint64_t unsafe_read(const std::wstring& file, int8_t* buffer, uint64_t length)
    {
        return omni::io::file_internal::unsafe_rd<std::string, std::ifstream, int8_t>(omni::string::to_string(file), buffer, length);
    }

    /** @internal library helper */
    bool rem(const std::string& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, false)
                if (::DeleteFileA(file.c_str()) == 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::string::to_string_t(omni::system::last_error_str()));
                    return false;
                }
            #else
                if (::_remove(file.c_str()) != 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                    return false;
                }
            #endif
        #else
            if (::remove(file.c_str()) != 0) {
                OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                return false;
            }
        #endif
        return !omni::io::file::exists(file);
    }
    /** @internal library helper */
    bool rem(const std::wstring& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
                if (::DeleteFileW(tf.c_str()) == 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::string::to_string_t(omni::system::last_error_str()));
                    return false;
                }
            #else
                if (::_wremove(file.c_str()) != 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                    return false;
                }
            #endif
        #else
            if (::remove(omni::string::to_string(file).c_str()) != 0) {
                OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                return false;
            }
        #endif
        return !omni::io::file::exists(file);
    }

    #if defined(OMNI_NON_PORTABLE)
        /** @internal library helper */
        bool set_size(const std::string& file, uint64_t size)
        {
            #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, false)
                HANDLE hfile = ::CreateFileA(file.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                           CREATE_NEW|OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hfile == INVALID_HANDLE_VALUE) {
                    OMNI_DBGEV("error setting file length: ", omni::system::last_error_str().c_str())
                    return false;
                }
                ::SetFilePointer(hfile, size, 0, FILE_BEGIN);
                ::SetEndOfFile(hfile);
                ::CloseHandle(hfile);
            #else
                #if defined(OMNI_OS_WIN)
                    int fd = ::_open(file.c_str(), O_RDWR);
                    if (fd == -1) {
                        OMNI_DBGEV("Could not open file: ", omni::system::last_error_str().c_str())
                        return false;
                    }
                    errno_t ret = _chsize_s(fd, static_cast<__int64>(size));
                    if (ret != 0) {
                        OMNI_DBGEV("error setting file length: ", oomni::system::last_error_str().c_str())
                        ::_close(fd);
                        return false;
                    }
                    ::_close(fd);
                #else
                    #if defined(OMNI_IO_USE_TRUNCATE)
                        if (OMNI_IO_FILE_TRUNCATE_FN (file.c_str(), static_cast<off_t>(size)) != 0) {
                            OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                            return false;
                        }
                    #else
                        int fd = ::open(file.c_str(), O_RDWR);
                        if (fd == -1) {
                            OMNI_DBGEV("Could not open file: ", omni::system::last_error())
                            return false;
                        }
                        if (OMNI_IO_FILE_FTRUNCATE_FN (fd, static_cast<off_t>(size)) != 0) {
                            OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                            ::close(fd);
                            return false;
                        }
                        ::close(fd);
                    #endif
                #endif
            #endif
            return true;
        }
        /** @internal library helper */
        bool set_size(const std::wstring& file, uint64_t size)
        {
            #if defined(OMNI_OS_WIN)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
                HANDLE hfile = ::CreateFileW(tf.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                         CREATE_NEW|OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hfile == INVALID_HANDLE_VALUE) {
                    OMNI_DBGEV("error setting file length: ", omni::system::last_error_str().c_str())
                    return false;
                }
                ::SetFilePointer(hfile, size, 0, FILE_BEGIN);
                ::SetEndOfFile(hfile);
                ::CloseHandle(hfile);
            #else
                #if defined(OMNI_OS_WIN)
                    int fd = ::_wopen(file.c_str(), O_RDWR);
                    if (fd == -1) {
                        OMNI_DBGEV("Could not open file: ", omni::system::last_error_str().c_str())
                        return false;
                    }
                    errno_t ret = _chsize_s(fd, static_cast<__int64>(size));
                    if (ret != 0) {
                        OMNI_DBGEV("error setting file length: ", ret)
                        ::_close(fd);
                        return false;
                    }
                    ::_close(fd);
                #else
                    #if defined(OMNI_IO_USE_TRUNCATE)
                        if (OMNI_IO_FILE_TRUNCATE_FN (file.c_str(), static_cast<off_t>(size)) != 0) {
                            OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                            return false;
                        }
                    #else
                        int fd = ::open(omni::string::to_string(file).c_str(), O_RDWR);
                        if (fd == -1) {
                            OMNI_DBGEV("Could not open file: ", omni::system::last_error())
                            return false;
                        }
                        if (OMNI_IO_FILE_FTRUNCATE_FN (fd, static_cast<off_t>(size)) != 0) {
                            OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                            ::close(fd);
                            return false;
                        }
                        ::close(fd);
                    #endif
                #endif
            #endif
            return true;
        }
    #endif

    /** @internal library helper */
    template < typename T, typename O >
    uint64_t write_fw(const std::string& file, const T& buffer, bool append)
    {
        O ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        ofile << buffer.c_str();
        ofile.flush();
        end = static_cast<uint64_t>(ofile.tellp());
        ofile.close();
        return (end - start);
    }
    /** @internal library helper */
    uint64_t write(const std::string& file, const std::string& buffer, bool append)
    {
        return write_fw<std::string, std::ofstream>(file, buffer, append);
    }
    /** @internal library helper */
    uint64_t write(const std::wstring& file, const std::wstring& buffer, bool append)
    {
        return write_fw<std::wstring, std::wofstream>(omni::string::to_string(file), buffer, append);
    }

    /** @internal library helper */
    template < typename STR, typename OFSTREAM, typename SEQ >
    uint64_t unsafe_write_fw(const STR& file, const SEQ* buffer, uint64_t length, bool append)
    {
        if ((length == 0) || (buffer == OMNI_NULL)) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        if (!ofile.is_open()) { return 0; }
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buffer);
        ofile.write(bf, static_cast<std::streamsize>(length));
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        return (end - start);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::string& file, const char* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::string, std::ofstream, char>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::wstring& file, const char* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::wstring, std::wofstream, char>(omni::string::to_wstring(file), buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::string& file, const wchar_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::string, std::ofstream, wchar_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::wstring, std::wofstream, wchar_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::string& file, const uint8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::string, std::ofstream, uint8_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::wstring, std::wofstream, uint8_t>(omni::string::to_wstring(file), buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::string& file, const int8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::string, std::ofstream, int8_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_fw<std::wstring, std::wofstream, int8_t>(file, buffer, length, append);
    }
    
    /** @internal library helper */
    template < typename STR, typename OFSTREAM >
    uint64_t write_line_fw(const std::string& file, const STR& buffer, bool append)
    {
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        ofile << buffer.c_str() << std::endl;
        ofile.flush();
        end = static_cast<uint64_t>(ofile.tellp());
        ofile.close();
        return (end - start);
    }
    /** @internal library helper */
    uint64_t write_line(const std::string& file, const std::string& buffer, bool append)
    {
        return write_line_fw<std::string, std::ofstream>(file, buffer, append);
    }
    /** @internal library helper */
    uint64_t write_line(const std::wstring& file, const std::wstring& buffer, bool append)
    {
        return write_line_fw<std::wstring, std::wofstream>(omni::string::to_string(file), buffer, append);
    }

    /** @internal library helper */
    template < typename STR, typename OFSTREAM, typename SEQ >
    uint64_t unsafe_write_line_fw(const STR& file, const SEQ* buffer, uint64_t length, bool append)
    {
        if ((length == 0) || (buffer == OMNI_NULL)) { return 0; }
        OFSTREAM ofile(omni::string::to_string(file).c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        uint64_t start = static_cast<uint64_t>(ofile.tellp());
        uint64_t end = start;
        const typename OFSTREAM::char_type* bf = reinterpret_cast<const typename OFSTREAM::char_type*>(buffer);
        ofile.write(bf, static_cast<std::streamsize>(length));
        ofile << std::endl;
        ofile.flush();
        if ((ofile.rdstate() & OFSTREAM::failbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: failbit set", omni::exception("Error on write: failbit set"))
        } else if ((ofile.rdstate() & OFSTREAM::badbit) != 0) {
            end = start;
            OMNI_ERR_FW("Error on write: badbit set", omni::exception("Error on write: badbit set"))
        } else {
            end = static_cast<uint64_t>(ofile.tellp());
        }
        ofile.close();
        return (end - start);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::string& file, const char* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::string, std::ofstream, char>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::wstring& file, const char* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::wstring, std::wofstream, char>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::string& file, const wchar_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::string, std::ofstream, wchar_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::wstring& file, const wchar_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::wstring, std::wofstream, wchar_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::string& file, const uint8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::string, std::ofstream, uint8_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::wstring& file, const uint8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::wstring, std::wofstream, uint8_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::string& file, const int8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::string, std::ofstream, int8_t>(file, buffer, length, append);
    }
    /** @internal library helper */
    uint64_t unsafe_write_line(const std::wstring& file, const int8_t* buffer, uint64_t length, bool append)
    {
        return unsafe_write_line_fw<std::wstring, std::wofstream, int8_t>(file, buffer, length, append);
    }

    } } }
#endif // OMNI_IO_FILE_INTERNAL_FW

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name, const omni::io::options& io_ops)
{
    if (file.empty() || new_name.empty()) {
        OMNI_ERR_RETV_FW(OMNI_PATH_EMPTY_STR, omni::exceptions::path_exception(OMNI_PATH_EMPTY_STR), false);
    }
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW(OMNI_FILE_NOT_FOUND_STR, omni::string::to_string_t(file), omni::exceptions::file_not_found(omni::string::to_string(file)), false);
    }
    bool overwrite = ((io_ops & omni::io::options::OVERWRITE) == omni::io::options::OVERWRITE);
    bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
    if (!overwrite && omni::io::file_internal::exists(new_name)) {
        OMNI_DBGEV("New path already exists: ", omni::string::to_string_t(new_name));
        return false;
    }
    OMNI_STRING_T_FW root = omni::io::path::get_parent_name(new_name);
    if (!omni::io::directory::exists(root)) {
        if (create_path) {
            if (!omni::io::directory::create(root, true)) {
                OMNI_D1_FW("could not create parent directory");
                return false;
            }
        } else {
            OMNI_D1_FW("error copying file: new path does not exist");
            return false;
        }
    }
    if (omni::io::file_internal::copy(file, new_name)) {
        return omni::io::file_internal::exists(new_name);
    }
    return false;
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::get_contents(const OMNI_STRING_T_FW& file)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW("file does not exist: ", omni::string::to_string_t(file), omni::exceptions::path_exception("File does not exist", omni::string::to_string(file)), OMNI_STRING_T_FW())
    }
    return omni::io::file_internal::get_contents(file);
}

uint64_t omni::io::OMNI_PATH_FW::get_size(const OMNI_STRING_T_FW& file)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW("file does not exist: ", omni::string::to_string_t(file), omni::exceptions::path_exception("File does not exist", omni::string::to_string(file)), 0)
    }
    return omni::io::file_internal::get_size(file);
}

bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name, const omni::io::options& io_ops)
{
    bool overwrite = ((io_ops & omni::io::options::OVERWRITE) == omni::io::options::OVERWRITE);
    bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW("file does not exist: ", omni::string::to_string_t(file), omni::exceptions::path_exception("File does not exist", omni::string::to_string(file)), false)
    }
    if (!overwrite && omni::io::file_internal::exists(new_name)) {
        OMNI_ERRV_RETV_FW("file already exists: ", omni::string::to_string_t(new_name), omni::exceptions::path_exception("File already exist", omni::string::to_string(new_name)), false)
    }
    OMNI_STRING_T_FW root = omni::io::path::get_parent_name(new_name);
    if (!omni::io::directory::exists(root)) {
        if (create_path) {
            if (!omni::io::directory::create(root, true)) {
                OMNI_D1_FW("could not create parent directory");
                return false;
            }
        } else {
            OMNI_D1_FW("error copying file: new path does not exist");
            return false;
        }
    }
    return omni::io::file_internal::mv(file, new_name, io_ops);
}

bool omni::io::OMNI_PATH_FW::remove(const OMNI_STRING_T_FW& file)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_DV1_FW("file does not exists: ", omni::string::to_string_t(file));
        return true;
    }
    return omni::io::file_internal::rem(file);
}

#if defined(OMNI_NON_PORTABLE)
bool omni::io::OMNI_PATH_FW::set_size(const OMNI_STRING_T_FW& file, uint64_t size)
{
    // The file must exist before this function can continue
    if (!omni::io::file_internal::exists(file)) {
        if (!omni::io::file_internal::create(file, true)) {
            OMNI_DBGE("could not create file")
            return false;
        }
    }

    if (!omni::io::file_internal::set_size(file, size)) { return false; }

    // DEV_NOTE: the following comments are here for instructional purpose
    /*
    // This function CAN destroy data. This functions uses API to extend or shorten
    // a file. If data is in the file and you extend the file, the data will stay
    // in place and the file length will simple be extended. If you shorten the file
    // the data at the end of the file will be freed (in other words, it will not be deleted
    // simply not associated with a file).

    // DEV_NOTE: It is possible, though uncommon, for an extended file to contain random
    // data where the file has been extended. This is typical of a sparse file. It is common
    // in Unix/Linux but no so much in Windows. Note that the reason we do not just write out
    // length worth of null is because depending on length this could take a long time.
    // No pun intended. Using the API to create a sparse file, it simply tells the FAT
    // (file allocation table) that file X is length in size
    */
    return omni::io::OMNI_PATH_FW::get_size(file) == size;
}
#endif

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::copy(file, new_name, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& file, const omni::io::options& io_ops) { return omni::io::file_internal::create(file, io_ops); }
bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& file) { return omni::io::OMNI_PATH_FW::create(file, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::exists(const OMNI_STRING_T_FW& file) { return omni::io::file_internal::exists(file); }
bool omni::io::OMNI_PATH_FW::exist(const OMNI_STRING_T_FW& file) { return omni::io::OMNI_PATH_FW::exists(file); }
bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::move(file, new_name, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name, const omni::io::options& io_ops) { return omni::io::OMNI_PATH_FW::move(file, new_name, io_ops); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::rename(file, new_name, omni::io::options::NONE); }
uint64_t omni::io::OMNI_PATH_FW::read(const OMNI_STRING_T_FW& file, OMNI_STRING_T_FW& buffer) { return omni::io::file_internal::read(file, buffer); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_read(const OMNI_STRING_T_FW& file, char* buffer, uint64_t length) { return omni::io::file_internal::unsafe_read(file, buffer, length); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_read(const OMNI_STRING_T_FW& file, wchar_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_read(file, buffer, length); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_read(const OMNI_STRING_T_FW& file, uint8_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_read(file, buffer, length); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_read(const OMNI_STRING_T_FW& file, int8_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_read(file, buffer, length); }
uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer) { return omni::io::file_internal::write(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const wchar_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const uint8_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const int8_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer) { return omni::io::file_internal::write_line(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const wchar_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const uint8_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const int8_t* buffer, uint64_t length) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer, bool append) { return omni::io::file_internal::write(file, buffer, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write(const OMNI_STRING_T_FW& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer, bool append) { return omni::io::file_internal::write_line(file, buffer, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const wchar_t* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const uint8_t* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, append); }
uint64_t omni::io::OMNI_PATH_FW::unsafe_write_line(const OMNI_STRING_T_FW& file, const int8_t* buffer, uint64_t length, bool append) { return omni::io::file_internal::unsafe_write_line(file, buffer, length, append); }
