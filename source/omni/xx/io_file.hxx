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

 i.e. don't #include <omni/xxx_impl.hxx> and don't compile this source directly.
 this file is #include'd directly in other source. 
 
 The logic is that omni::cstring and omni::wstring namespaces segregate the types
 for explicit calling; i.e. you can call omni::cstring::X to check on a std:string
 and similarly can call omni::wstring::X to check a std::wstring, while still having access
 to the omni::string_t and omn::string::X functions (which are aliases for the other namespaces).
 
 Since omni::wstring and omni::cstring are merely wrappers for the omni::string::util functions
 (which are templated) that then pass in the appropriate types (std::string/wstring char/wchar_t)
 putting the relevant code in a header with a few #defs for types makes keeping the files
 in sync (for functions) less messy. It does introduce slight confusion to anyone who might
 want to read this specific code or documentation though, hence this note.
*/

// so as not to accidentally build this file with the source this macro is defined in io.cpp
#if !defined(OMNI_IO_FILE_FW) || !defined(OMNI_PATH_FW) || !defined(OMNI_L_FW) || !defined(OMNI_STRING_T_FW)
    #error invalid preprocessor directive detected
#endif

#if defined(OMNI_IO_FILE_INTERNAL_FW)
    namespace omni { namespace io { /** @internal framework helper */ namespace file_internal {

    #if defined(OMNI_OS_WIN)
        /** @internal framework helper */
        std::string get_path_name(const std::string& file)
        {
            std::string name = "\\\\?\\";
            long length = ::GetShortPathNameA(file.c_str(), NULL, 0);
            if (length > 0) {
                char *buffer = new char[length];
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
        /** @internal framework helper */
        std::wstring get_path_name(const std::wstring& file)
        {
            std::wstring name = L"\\\\?\\";
            long length = ::GetShortPathNameW(file.c_str(), NULL, 0);
            if (length > 0) {
                wchar_t *buffer = new wchar_t[length];
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
    #endif

    /** @internal framework helper */
    bool exists(const std::string& file)
    {
        if (file.empty()) { return false; }
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, false)
                DWORD res = ::GetFileAttributesA(file.c_str());
                return (res != INVALID_FILE_ATTRIBUTES && !(res & FILE_ATTRIBUTE_DIRECTORY));
            #else
                struct stat fi;
                if (::_stat(file.c_str(), &fi) == 0) {
                    #if defined(S_ISSOCK)
                        return !(S_ISDIR(fi.st_mode)) && !(S_ISSOCK(fi.st_mode));
                    #else
                        return !(S_ISDIR(fi.st_mode));
                    #endif
                }
                return false;
            #endif
        #else
            struct stat fi;
            if (::stat(file.c_str(), &fi) == 0) {
                #if defined(S_ISSOCK)
                    return !(S_ISDIR(fi.st_mode)) && !(S_ISSOCK(fi.st_mode));
                #else
                    return !(S_ISDIR(fi.st_mode));
                #endif
            }
            return false;
        #endif
    }
    /** @internal framework helper */
    bool exists(const std::wstring& file)
    {
        if (file.empty()) { return false; }
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(file, false)
                DWORD res = ::GetFileAttributesW(tf.c_str());
                return (res != INVALID_FILE_ATTRIBUTES && !(res & FILE_ATTRIBUTE_DIRECTORY));
            #else
                struct stat fi;
                if (::_wstat(file.c_str(), &fi) == 0) {
                    #if defined(S_ISSOCK)
                        return !(S_ISDIR(fi.st_mode)) && !(S_ISSOCK(fi.st_mode));
                    #else
                        return !(S_ISDIR(fi.st_mode));
                    #endif
                }
                return false;
            #endif
        #else
            struct stat fi;
            if (::stat(omni::string::util::to_string(file).c_str(), &fi) == 0) {
                #if defined(S_ISSOCK)
                    return !(S_ISDIR(fi.st_mode)) && !(S_ISSOCK(fi.st_mode));
                #else
                    return !(S_ISDIR(fi.st_mode));
                #endif
            }
            return false;
        #endif
    }
    
    /** @internal framework helper */
    template < typename STR, typename ISTREAM, typename OSTREAM >
    bool copy(const STR& file, const STR& new_name)
    {
        ISTREAM src(omni::string::util::to_string(file).c_str(), std::ios::binary);
        if (!src.is_open()) {
            OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::util::to_string_t(file), omni::exceptions::path_exception(omni::string::util::to_string(file)), false)
        }
        OSTREAM dst(omni::string::util::to_string(new_name).c_str(), std::ios::binary);
        if (!dst.is_open()) {
            src.close();
            OMNI_ERRV_RETV_FW(OMNI_PATH_NOT_ACCESSIBLE_STR, omni::string::util::to_string_t(new_name), omni::exceptions::path_exception(omni::string::util::to_string(new_name)), false)
        }
        dst << src.rdbuf();
        src.close();
        dst.close();
        return true;
    }
    /** @internal framework helper */
    bool copy(const std::string& file, const std::string& new_name)
    {
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            OMNI_FILE_CHECKA_FW(file, false)
            if (::CopyFileA(file.c_str(), new_name.c_str(), FALSE) == 0) {
                OMNI_DBGEV("error copying file: ", omni::string::util::to_string_t(omni::system::last_error_str()));
                return false;
            }
            return omni::io::file_internal::exists(new_name);
        #else
            return omni::io::file_internal::copy<std::string, std::ifstream, std::ofstream>(file, new_name);
        #endif
    }
    /** @internal framework helper */
    bool copy(const std::wstring& file, const std::wstring& new_name)
    {
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            std::wstring tf = OMNI_FILE_CHECKW_FW(file, false)
            std::wstring nf = OMNI_FILE_CHECKW_FW(new_name, false)
            if (::CopyFileW(tf.c_str(), nf.c_str(), FALSE) == 0) {
                OMNI_DBGEV("error copying file: ", omni::string::util::to_string_t(omni::system::last_error_str()));
                return false;
            }
            return omni::io::file_internal::exists(new_name);
        #else
            return omni::io::file_internal::copy<std::wstring, std::wifstream, std::wofstream>(file, new_name);
        #endif
    }

    /** @internal framework helper */
    template < typename STR, typename OSTREAM >
    bool create(const STR& file, bool create_path)
    {
        STR parent = omni::io::path::get_parent_name(file);
        if (create_path && !omni::io::directory::exists(parent)) {
            if (!omni::io::directory::create(parent)) {
                return false;
            }
        }
        OSTREAM out(omni::string::util::to_string(file).c_str(), std::ios::binary|std::ios::out);
        out.close(); // close/flush
        return omni::io::file_internal::exists(file);
    }
    /** @internal framework helper */
    bool create(const std::string& file, bool create_path)
    {
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
            int err = omni::system::last_error();
            if (hfile == INVALID_HANDLE_VALUE || err > 0) {
                OMNI_DBGEV("error setting file length: ", err)
                return false;
            }
            ::CloseHandle(hfile);
            return omni::io::file_internal::exists(file);
        #else
            return omni::io::file_internal::create<std::string, std::ofstream>(file, create_path);
        #endif
    }
    /** @internal framework helper */
    bool create(const std::wstring& file, bool create_path)
    {
        #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
            if (create_path) {
                std::wstring parent = omni::io::path::get_parent_name(file);
                if (create_path && !omni::io::directory::exists(parent)) {
                    if (!omni::io::directory::create(parent)) {
                        return false;
                    }
                }
            }
            std::wstring tf = OMNI_FILE_CHECKW_FW(file, false)
            HANDLE hfile = ::CreateFileW(tf.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                   CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
            int err = omni::system::last_error();
            if (hfile == INVALID_HANDLE_VALUE || err > 0) {
                OMNI_DBGEV("error setting file length: ", err)
                return false;
            }
            ::CloseHandle(hfile);
            return omni::io::file_internal::exists(file);
        #else
            return omni::io::file_internal::create<std::wstring, std::wofstream>(file, create_path);
        #endif
    }

    /** @internal framework helper */
    template < typename STR, typename ISTRM, typename SSTRM >
    STR get_contents(const STR& file)
    {
        ISTRM ifile(omni::string::util::to_string(file).c_str());
        SSTRM buf;
        buf << ifile.rdbuf();
        return buf.str();
    }
    /** @internal framework helper */
    std::string get_contents(const std::string& file)
    {
        return get_contents<std::string, std::ifstream, std::stringstream>(file);
    }
    /** @internal framework helper */
    std::wstring get_contents(const std::wstring& file)
    {
        return get_contents<std::wstring, std::wifstream, std::wstringstream>(file);
    }

    /** @internal framework helper */
    uint64_t get_size(const std::string& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, 0)
                WIN32_FILE_ATTRIBUTE_DATA finfo;
                if (::GetFileAttributesExA(file.c_str(), GetFileExInfoStandard, &finfo) == 0) { return 0; }
                LARGE_INTEGER sz;
                sz.HighPart = finfo.nFileSizeHigh;
                sz.LowPart = finfo.nFileSizeLow;
                return static_cast<uint64_t>(sz.QuadPart);
            #else
                struct stat fi;
                if (::_stat(file.c_str(), &fi) == 0) { return fi.st_size; }
                return 0;
            #endif
        #else
            struct stat fi;
            if (::stat(file.c_str(), &fi) == 0) { return fi.st_size; }
            return 0;
        #endif
    }
    /** @internal framework helper */
    uint64_t get_size(const std::wstring& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(file, 0)
                WIN32_FILE_ATTRIBUTE_DATA finfo;
                if (::GetFileAttributesExW(tf.c_str(), GetFileExInfoStandard, &finfo) == 0) { return 0; }
                LARGE_INTEGER sz;
                sz.HighPart = finfo.nFileSizeHigh;
                sz.LowPart = finfo.nFileSizeLow;
                return static_cast<uint64_t>(sz.QuadPart);
            #else
                struct stat fi;
                if (::_wstat(file.c_str(), &fi) == 0) { return fi.st_size;; }
                return 0;
            #endif
        #else
            struct stat fi;
            if (::stat(omni::string::util::to_string(file).c_str(), &fi) == 0) { return fi.st_size;; }
            return 0;
        #endif
    }

    /** @internal framework helper */
    bool mv(const std::string& file, const std::string& new_name, bool create_path)
    {
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
                    OMNI_DV1_FW("error moving file: ", omni::string::util::to_string_t(omni::system::last_error_str()));
                    return false;
                }
            #else
                int ret = ::_rename(file.c_str(), new_name.c_str());
                if (ret != 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::util::to_string_t(omni::system::error_str(ret)));
                    return false;
                }
            #endif
        #else
            int ret = ::rename(file.c_str(), new_name.c_str());
            if (ret != 0) {
                OMNI_DV1_FW("error moving file: ", omni::string::util::to_string_t(omni::system::error_str(ret)));
                return false;
            }
        #endif
        return omni::io::file_internal::exists(new_name);
    }
    /** @internal framework helper */
    bool mv(const std::wstring& file, const std::wstring& new_name, bool create_path)
    {
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
                std::wstring tf = OMNI_FILE_CHECKW_FW(file, false)
                std::wstring nf = OMNI_FILE_CHECKW_FW(new_name, false)
                BOOL ret = ::MoveFileW(tf.c_str(), nf.c_str());
                if (ret == 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::util::to_string_t(omni::system::last_error_str()));
                    return false;
                }
            #else
                int ret = ::_wrename(file.c_str(), new_name.c_str());
                if (ret != 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::util::to_string_t(omni::system::error_str(ret)));
                    return false;
                }
            #endif
        #else
            int ret = ::rename(omni::string::util::to_string(file).c_str(), omni::string::util::to_string(new_name).c_str());
            if (ret != 0) {
                OMNI_DV1_FW("error moving file: ", omni::string::util::to_string_t(omni::system::error_str(ret)));
                return false;
            }
        #endif
        return omni::io::file_internal::exists(new_name);
    }

    /** @internal framework helper */
    template < typename STR, typename IFSTREAM, typename SEQ >
    uint64_t rd(const STR& file, SEQ& buffer)
    {
        IFSTREAM ifile(omni::string::util::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        ifile.seekg(0, ifile.end);
        size_t length = ifile.tellg();
        ifile.seekg(0, ifile.beg);
        // TODO: no like
        ifile.read(reinterpret_cast<typename STR::value_type*>(&buffer[0]), length);
        length = ifile.gcount();
        ifile.close();
        return length;
    }
    /** @internal framework helper */
    uint64_t read(const std::string& file, omni::seq::uchar_t& buffer)
    {
        return omni::io::file_internal::rd<std::string, std::ifstream, omni::seq::uchar_t>(file, buffer);
    }
    /** @internal framework helper */
    uint64_t read(const std::wstring& file, omni::seq::uchar_t& buffer)
    {
        return omni::io::file_internal::rd<std::wstring, std::wifstream, omni::seq::uchar_t>(file, buffer);
    }
    /** @internal framework helper */
    uint64_t read(const std::string& file, omni::seq::char_t& buffer)
    {
        return omni::io::file_internal::rd<std::string, std::ifstream, omni::seq::char_t>(file, buffer);
    }
    /** @internal framework helper */
    uint64_t read(const std::wstring& file, omni::seq::char_t& buffer)
    {
        return omni::io::file_internal::rd<std::wstring, std::wifstream, omni::seq::char_t>(file, buffer);
    }

    /** @internal framework helper */
    template < typename STR, typename IFSTREAM >
    uint64_t rd_f(const STR& file, STR& buffer)
    {
        IFSTREAM ifile(omni::string::util::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        uint64_t length = ifile.tellg();
        ifile >> buffer;
        length = static_cast<uint64_t>(ifile.tellg()) - length;
        ifile.close();
        return length;
    }
    /** @internal framework helper */
    uint64_t read(const std::string& file, std::string& buffer)
    {
        return omni::io::file_internal::rd_f<std::string, std::ifstream>(file, buffer);
    }
    /** @internal framework helper */
    uint64_t read(const std::wstring& file, std::wstring& buffer)
    {
        return omni::io::file_internal::rd_f<std::wstring, std::wifstream>(file, buffer);
    }

    /** @internal framework helper */
    template < typename STR, typename IFSTREAM, typename SEQ >
    uint64_t rd_raw(const STR& file, SEQ* buffer, uint64_t blen)
    {
        IFSTREAM ifile(omni::string::util::to_string(file).c_str(), std::ios::binary);
        if (!ifile.is_open()) { return 0; }
        ifile.seekg (0, ifile.end);
        uint64_t length = ifile.tellg();
        ifile.seekg(0, ifile.beg);
        if (length > blen) { length = blen; }
        // TODO: no like
        ifile.read(reinterpret_cast<typename STR::value_type*>(buffer), length);
        length = ifile.gcount();
        ifile.close();
        return length;
    }
    /** @internal framework helper */
    uint64_t read_raw(const std::string& file, unsigned char* buffer, uint64_t length)
    {
        return omni::io::file_internal::rd_raw<std::string, std::ifstream, unsigned char>(file, buffer, length);
    }
    /** @internal framework helper */
    uint64_t read_raw(const std::wstring& file, unsigned char* buffer, uint64_t length)
    {
        return omni::io::file_internal::rd_raw<std::wstring, std::wifstream, unsigned char>(file, buffer, length);
    }
    /** @internal framework helper */
    uint64_t read_raw(const std::string& file, char* buffer, uint64_t length)
    {
        return omni::io::file_internal::rd_raw<std::string, std::ifstream, char>(file, buffer, length);
    }
    /** @internal framework helper */
    uint64_t read_raw(const std::wstring& file, char* buffer, uint64_t length)
    {
        return omni::io::file_internal::rd_raw<std::wstring, std::wifstream, char>(file, buffer, length);
    }

    /** @internal framework helper */
    bool rem(const std::string& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, false)
                if (::DeleteFileA(file.c_str()) == 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::string::util::to_string_t(omni::system::last_error_str()));
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
    /** @internal framework helper */
    bool rem(const std::wstring& file)
    {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(file, false)
                if (::DeleteFileW(tf.c_str()) == 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::string::util::to_string_t(omni::system::last_error_str()));
                    return false;
                }
            #else
                if (::_wremove(file.c_str()) != 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                    return false;
                }
            #endif
        #else
            if (::remove(omni::string::util::to_string(file).c_str()) != 0) {
                OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                return false;
            }
        #endif
        return !omni::io::file::exists(file);
    }

    #if defined(OMNI_NON_PORTABLE)
        /** @internal framework helper */
        bool set_size(const std::string& file, uint64_t size)
        {
            #if defined(OMNI_OS_WIN)
                OMNI_FILE_CHECKA_FW(file, false)
                HANDLE hfile = ::CreateFileA(file.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                         CREATE_NEW|OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                int err = omni::system::last_error();
                if (hfile == INVALID_HANDLE_VALUE || err > 0) {
                    OMNI_DBGEV("error setting file length: ", err)
                    return false;
                }
                ::SetFilePointer(hfile, size, 0, FILE_BEGIN);
                ::SetEndOfFile(hfile);
                ::CloseHandle(hfile);
            #else
                int fd = ::open(file.c_str(), O_RDWR);
                if (::ftruncate(fd, size) != 0) {
                    OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                    //close(fd);
                    //return false;
                }
                ::close(fd);
                // NOTE: If the above gives issues, try the following
                //if (::truncate(file.c_str(), size) != 0) {
                //    OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                //}
            #endif
            return true;
        }
        /** @internal framework helper */
        bool set_size(const std::wstring& file, uint64_t size)
        {
            #if defined(OMNI_OS_WIN)
                std::wstring tf = OMNI_FILE_CHECKW_FW(file, false)
                HANDLE hfile = ::CreateFileW(tf.c_str(), GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                                                       CREATE_NEW|OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                int err = omni::system::last_error();
                if (hfile == INVALID_HANDLE_VALUE || err > 0) {
                    OMNI_DBGEV("error setting file length: ", err)
                    return false;
                }
                ::SetFilePointer(hfile, size, 0, FILE_BEGIN);
                ::SetEndOfFile(hfile);
                ::CloseHandle(hfile);
            #else
                int fd = ::open(omni::string::util::to_string(file).c_str(), O_RDWR);
                if (::ftruncate(fd, size) != 0) {
                    OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                    //close(fd);
                    //return false;
                }
                ::close(fd);
                // NOTE: If the above gives issues, try the following
                //if (::truncate(file.c_str(), size) != 0) {
                //    OMNI_DBGEV("error setting file length: ", omni::system::last_error())
                //}
            #endif
            return true;
        }
    #endif

    /** @internal framework helper */
    template < typename T, typename O >
    uint64_t write_fw(const std::string& file, const T& buffer, bool append)
    {
        O ofile(file.c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        std::size_t start = ofile.tellp();
        std::size_t end = start;
        ofile << buffer.c_str();
        ofile.flush();
        end = ofile.tellp();
        ofile.close();
        return end - start;   
    }
    /** @internal framework helper */
    uint64_t write(const std::string& file, const std::string& buffer, bool append)
    {
        return write_fw<std::string, std::ofstream>(file, buffer, append);
    }
    /** @internal framework helper */
    uint64_t write(const std::wstring& file, const std::wstring& buffer, bool append)
    {
        return write_fw<std::wstring, std::wofstream>(omni::string::util::to_string(file), buffer, append);
    }

    /** @internal framework helper */
    template < typename T, typename O, typename S, typename ITR >
    uint64_t write_buf_fw(const std::string& file, const S& buffer, bool append)
    {
        O ofile(file.c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        std::size_t start = ofile.tellp();
        std::size_t end = start;
        for (ITR b = buffer.begin(); b != buffer.end(); ++b) {
            ofile << *b;
        }
        ofile.flush();
        end = ofile.tellp();
        ofile.close();
        return end - start;   
    }
    /** @internal framework helper */
    uint64_t write(const std::string& file, const omni::seq::uchar_t& buffer, bool append)
    {
        return write_buf_fw<std::string, std::ofstream, omni::seq::uchar_t, omni::seq::uchar_t::const_iterator>(file, buffer, append);
    }
    /** @internal framework helper */
    uint64_t write(const std::wstring& file, const omni::seq::uchar_t& buffer, bool append)
    {
        return write_buf_fw<std::wstring, std::wofstream, omni::seq::uchar_t, omni::seq::uchar_t::const_iterator>(omni::string::util::to_string(file), buffer, append);
    }
    /** @internal framework helper */
    uint64_t write(const std::string& file, const omni::seq::char_t& buffer, bool append)
    {
        return write_buf_fw<std::string, std::ofstream, omni::seq::char_t, omni::seq::char_t::const_iterator>(file, buffer, append);
    }
    /** @internal framework helper */
    uint64_t write(const std::wstring& file, const omni::seq::char_t& buffer, bool append)
    {
        return write_buf_fw<std::wstring, std::wofstream, omni::seq::char_t, omni::seq::char_t::const_iterator>(omni::string::util::to_string(file), buffer, append);
    }

    /** @internal framework helper */
    template < typename T >
    uint64_t write_raw_fw(const std::string& file, T buffer, size_t sz, bool append)
    {
        std::ofstream ofile(file.c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        std::size_t start = ofile.tellp();
        std::size_t end = start;
        ofile.write(reinterpret_cast<const char*>(buffer), sz);
        ofile.flush();
        end = ofile.tellp();
        ofile.close();
        return end - start;
    }
    /** @internal framework helper */
    uint64_t write_raw(const std::string& file, const unsigned char* buffer, size_t sz, bool append)
    {
        return write_raw_fw<const unsigned char*>(file, buffer, sz, append);
    }
    /** @internal framework helper */
    uint64_t write_raw(const std::wstring& file, const unsigned char* buffer, size_t sz, bool append)
    {
        return write_raw_fw<const unsigned char*>(omni::string::util::to_string(file), buffer, sz, append);
    }
    /** @internal framework helper */
    uint64_t write_raw(const std::string& file, const char* buffer, size_t sz, bool append)
    {
        return write_raw_fw<const char*>(file, buffer, sz, append);
    }
    /** @internal framework helper */
    uint64_t write_raw(const std::wstring& file, const char* buffer, size_t sz, bool append)
    {
        return write_raw_fw<const char*>(omni::string::util::to_string(file), buffer, sz, append);
    }

    /** @internal framework helper */
    template < typename T, typename O, typename S >
    uint64_t write_line_buf_fw(const std::string& file, const S& buffer, bool append)
    {
        O ofile(file.c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        std::size_t start = ofile.tellp();
        std::size_t end = start;
        for (typename S::const_iterator b = buffer.begin(); b != buffer.end(); ++b) {
            ofile << *b;
        }
        ofile << std::endl;
        ofile.flush();
        end = ofile.tellp();
        ofile.close();
        return end - start;   
    }
    /** @internal framework helper */
    uint64_t write_line(const std::string& file, const omni::seq::uchar_t& buffer, bool append)
    {
        return write_line_buf_fw<std::string, std::ofstream, omni::seq::uchar_t>(file, buffer, append);
    }
    /** @internal framework helper */
    uint64_t write_line(const std::wstring& file, const omni::seq::uchar_t& buffer, bool append)
    {
        return write_line_buf_fw<std::wstring, std::wofstream, omni::seq::uchar_t>(omni::string::util::to_string(file), buffer, append);
    }
    /** @internal framework helper */
    uint64_t write_line(const std::string& file, const omni::seq::char_t& buffer, bool append)
    {
        return write_line_buf_fw<std::string, std::ofstream, omni::seq::char_t>(file, buffer, append);
    }
    /** @internal framework helper */
    uint64_t write_line(const std::wstring& file, const omni::seq::char_t& buffer, bool append)
    {
        return write_line_buf_fw<std::wstring, std::wofstream, omni::seq::char_t>(omni::string::util::to_string(file), buffer, append);
    }

    /** @internal framework helper */
    template < typename T, typename O >
    uint64_t write_line_fw(const std::string& file, const T& buffer, bool append)
    {
        O ofile(file.c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        std::size_t start = ofile.tellp();
        std::size_t end = start;
        ofile << buffer.c_str() << std::endl;
        ofile.flush();
        end = ofile.tellp();
        ofile.close();
        return end - start;   
    }
    /** @internal framework helper */
    uint64_t write_line(const std::string& file, const std::string& buffer, bool append)
    {
        return write_line_fw<std::string, std::ofstream>(file, buffer, append);
    }
    /** @internal framework helper */
    uint64_t write_line(const std::wstring& file, const std::wstring& buffer, bool append)
    {
        return write_line_fw<std::wstring, std::wofstream>(omni::string::util::to_string(file), buffer, append);
    }

    /** @internal framework helper */
    template < typename T >
    uint64_t write_line_raw_fw(const std::string& file, T buffer, size_t sz, bool append)
    {
        std::ofstream ofile(file.c_str(), (append ? (std::ios::binary | std::ios::app) : std::ios::binary));
        std::size_t start = ofile.tellp();
        std::size_t end = start;
        ofile.write(reinterpret_cast<const char*>(buffer), sz);
        ofile << std::endl;
        ofile.flush();
        end = ofile.tellp();
        ofile.close();
        return end - start;
    }
    /** @internal framework helper */
    uint64_t write_line_raw(const std::string& file, const unsigned char* buffer, size_t sz, bool append)
    {
        return write_line_raw_fw<const unsigned char*>(file, buffer, sz, append);
    }
    /** @internal framework helper */
    uint64_t write_line_raw(const std::wstring& file, const unsigned char* buffer, size_t sz, bool append)
    {
        return write_line_raw_fw<const unsigned char*>(omni::string::util::to_string(file), buffer, sz, append);
    }
    /** @internal framework helper */
    uint64_t write_line_raw(const std::string& file, const char* buffer, size_t sz, bool append)
    {
        return write_line_raw_fw<const char*>(file, buffer, sz, append);
    }
    /** @internal framework helper */
    uint64_t write_line_raw(const std::wstring& file, const char* buffer, size_t sz, bool append)
    {
        return write_line_raw_fw<const char*>(omni::string::util::to_string(file), buffer, sz, append);
    }

    } } }
#endif // OMNI_IO_FILE_INTERNAL_FW

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::copy(file, new_name, false); }
bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& file) { return omni::io::OMNI_PATH_FW::create(file, true); }
bool omni::io::OMNI_PATH_FW::exist(const OMNI_STRING_T_FW& file) { return omni::io::OMNI_PATH_FW::exists(file); }
bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::move(file, new_name, false); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name, bool create_path) { return omni::io::OMNI_PATH_FW::move(file, new_name, create_path); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::rename(file, new_name, false); }
uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const omni::seq::uchar_t& buffer) { return omni::io::OMNI_PATH_FW::write(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const omni::seq::char_t& buffer) { return omni::io::OMNI_PATH_FW::write(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer) { return omni::io::OMNI_PATH_FW::write(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::write_raw(const OMNI_STRING_T_FW& file, const unsigned char* buffer, uint64_t length) { return omni::io::OMNI_PATH_FW::write_raw(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::write_raw(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length) { return omni::io::OMNI_PATH_FW::write_raw(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const omni::seq::uchar_t& buffer) { return omni::io::OMNI_PATH_FW::write_line(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const omni::seq::char_t& buffer) { return omni::io::OMNI_PATH_FW::write_line(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer) { return omni::io::OMNI_PATH_FW::write_line(file, buffer, false); }
uint64_t omni::io::OMNI_PATH_FW::write_line_raw(const OMNI_STRING_T_FW& file, const unsigned char* buffer, uint64_t length) { return omni::io::OMNI_PATH_FW::write_line_raw(file, buffer, length, false); }
uint64_t omni::io::OMNI_PATH_FW::write_line_raw(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length) { return omni::io::OMNI_PATH_FW::write_line_raw(file, buffer, length, false); }

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name, bool overwrite)
{
    if (file.empty() || new_name.empty()) {
        OMNI_ERR_RETV_FW(OMNI_PATH_EMPTY, omni::exceptions::path_exception(), false);
    }
    if (file == new_name) {
        OMNI_DBGEV("Old and new path are the same: ", omni::string::util::to_string_t(file));
        return true;
    }
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW(OMNI_FILE_NOT_FOUND_STR, omni::string::util::to_string_t(file), omni::exceptions::file_not_found(omni::string::util::to_string(file)), false);
    }
    if (!overwrite && omni::io::file_internal::exists(new_name)) {
        OMNI_DBGEV("New path already exists: ", omni::string::util::to_string_t(new_name));
        return false;
    }
    if (omni::io::file_internal::copy(file, new_name)) {
        return omni::io::file_internal::exists(new_name);
    }
    return false;
}

bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& file, bool create_path)
{
    return omni::io::file_internal::create(file, create_path);
}

bool omni::io::OMNI_PATH_FW::exists(const OMNI_STRING_T_FW& file)
{
    return omni::io::file_internal::exists(file);
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::get_contents(const OMNI_STRING_T_FW& file)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW("file does not exist: ", omni::string::util::to_string_t(file), omni::exceptions::path_exception(omni::string::util::to_string(file)), OMNI_STRING_T_FW())
    }
    return omni::io::file_internal::get_contents(file);
}

uint64_t omni::io::OMNI_PATH_FW::get_size(const OMNI_STRING_T_FW& file)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW("file does not exist: ", omni::string::util::to_string_t(file), omni::exceptions::path_exception(omni::string::util::to_string(file)), 0)
    }
    return omni::io::file_internal::get_size(file);
}

bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& new_name, bool create_path)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_ERRV_RETV_FW("file does not exist: ", omni::string::util::to_string_t(file), omni::exceptions::path_exception(omni::string::util::to_string(file)), false)
    }
    if (omni::io::file_internal::exists(new_name)) {
        OMNI_ERRV_RETV_FW("file already exists: ", omni::string::util::to_string_t(new_name), omni::exceptions::path_exception(omni::string::util::to_string(new_name)), false)
    }
    return omni::io::file_internal::mv(file, new_name, create_path);
}

uint64_t omni::io::OMNI_PATH_FW::read(const OMNI_STRING_T_FW& file, omni::seq::uchar_t& buffer)
{
    return omni::io::file_internal::read(file, buffer);
}

uint64_t omni::io::OMNI_PATH_FW::read(const OMNI_STRING_T_FW& file, omni::seq::char_t& buffer)
{
    return omni::io::file_internal::read(file, buffer);
}

uint64_t omni::io::OMNI_PATH_FW::read(const OMNI_STRING_T_FW& file, OMNI_STRING_T_FW& buffer)
{
    return omni::io::file_internal::read(file, buffer);
}

uint64_t omni::io::OMNI_PATH_FW::read_raw(const OMNI_STRING_T_FW& file, unsigned char* buffer, uint64_t length)
{
    return omni::io::file_internal::read_raw(file, buffer, length);
}

uint64_t omni::io::OMNI_PATH_FW::read_raw(const OMNI_STRING_T_FW& file, char* buffer, uint64_t length)
{
    return omni::io::file_internal::read_raw(file, buffer, length);
}

bool omni::io::OMNI_PATH_FW::remove(const OMNI_STRING_T_FW& file)
{
    if (!omni::io::file_internal::exists(file)) {
        OMNI_DV1_FW("file does not exists: ", omni::string::util::to_string_t(file));
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
    // the data at the end of the file will be freed (in other words, it won't be deleted
    // simply not associated with a file).

    // DEV_NOTE: It is possible, though uncommon, for an extended file to contain random
    // data where the file has been extended. This is typical of a sparse file. It is common
    // in Unix/Linux but no so much in Windows. Note that the reason we don't just write out
    // 'length' worth of null is because depending on 'length' this could take a long time.
    // No pun intended. Using the API to create a 'sparse' file, it simply tells the FAT
    // (file allocation table) that file 'X' is 'length' in size
    #if defined(OMNI_OS_WIN)
        // Because we are using Windows we need to convert the name to 8.3 format otherwise, it's possible to get
        // an INVALID_HANDLE_VALUE returned from a valid file. 
        // Example: 'C:\Develop\C++\file.txt' could exist and there is nothing in the name more than 8 characters
        // long, but because the folder 'C++' has invalid 8.3 characters in it, it will fail. 'C++' in 8.3 format is 'C__~1'
        // CreateFile also needs a '\\?\' in front of the file to open an actual file handle ('\\.\' for a device)    
        
        // First obtain the size needed by passing NULL and 0
        OMNI_STRING_T_FW name = OMNI_STRW("\\\\?\\"); // + file;
        long length = GetShortPathName(file.c_str(), NULL, 0);
        if (length > 0) {
            omni::char_t *buffer = new omni::char_t[length];
            // Now simply call again using same long path.
            length = GetShortPathName(file.c_str(), buffer, length);
            if (length > 0) { // Could not get the short path name, so return the original
                OMNI_STRING_T_FW npath(buffer);
                delete[] buffer;
                name += npath;
            } else {
                delete[] buffer;
            }
        } else {
            name += file;
        }
        
        HANDLE hfile = CreateFile(name.c_str(), // File name
                                 GENERIC_WRITE,  // Open mode (GENERIC_READ/WRITE/EXECUTE/ALL)
                                 FILE_SHARE_READ|FILE_SHARE_WRITE, // Shared mode (FILE_SHARE_WRITE/READ/DELETE)
                                 NULL, // Pointer to the security descriptor
                                 CREATE_NEW|OPEN_EXISTING, // How to create/open (go to definition to see all)
                                 FILE_ATTRIBUTE_NORMAL, // File attributes (go to definition to see all)
                                 NULL); // Handle to file with attributes to copy
        int err = omni::system::last_error();
        if (hfile == INVALID_HANDLE_VALUE || err > 0) {
            OMNI_DBGEV("error setting file length: ", err)
            return false;
        }
        SetFilePointer(hfile, size, 0, FILE_BEGIN);
        SetEndOfFile(hfile);
        CloseHandle(hfile);
    #else
        // DEV_NOTE: The following functions are POSIX functions and MIGHT NOT
        // work on your OS/Filesystem. As there is no standard way of setting the length
        // of a file, you may have to 'hack in' your own way if your needs differ from this
        //int ftruncate(int fd, off_t length);
        //int truncate(const char *path, off_t length);

        // DEV_NOTE: Even though the function call is 'truncate' which would imply only
        // file truncation, if the length passed to the function is longer than the
        // actual file length, the file is indeed expanded.

        int fd = open(omni::string::util::to_string(file).c_str(), O_RDWR);
        if (ftruncate(fd, size) != 0) {
            OMNI_DBGEV("error setting file length: ", omni::system::last_error())
            //close(fd);
            //return false;
        }
        close(fd);
        // NOTE: If the above gives issues, try the following
        //if (truncate(file.c_str(), size) != 0) {
        //    OMNI_DBGEV("error setting file length: ", omni::system::last_error())
        //}
    #endif
    */
    return omni::io::OMNI_PATH_FW::get_size(file) == size;
}
#endif

uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const omni::seq::uchar_t& buffer, bool append)
{
    return omni::io::file_internal::write(file, buffer, append);
}

uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const omni::seq::char_t& buffer, bool append)
{
    return omni::io::file_internal::write(file, buffer, append);
}

uint64_t omni::io::OMNI_PATH_FW::write(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer, bool append)
{
    return omni::io::file_internal::write(file, buffer, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_raw(const OMNI_STRING_T_FW& file, const unsigned char* buffer, uint64_t length, bool append)
{
    return omni::io::file_internal::write_raw(file, buffer, length, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_raw(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length, bool append)
{
    return omni::io::file_internal::write_raw(file, buffer, length, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const omni::seq::uchar_t& buffer, bool append)
{
    return omni::io::file_internal::write_line(file, buffer, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const omni::seq::char_t& buffer, bool append)
{
    return omni::io::file_internal::write_line(file, buffer, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_line(const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& buffer, bool append)
{
    return omni::io::file_internal::write_line(file, buffer, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_line_raw(const OMNI_STRING_T_FW& file, const unsigned char* buffer, uint64_t length, bool append)
{
    return omni::io::file_internal::write_line_raw(file, buffer, length, append);
}

uint64_t omni::io::OMNI_PATH_FW::write_line_raw(const OMNI_STRING_T_FW& file, const char* buffer, uint64_t length, bool append)
{
    return omni::io::file_internal::write_line_raw(file, buffer, length, append);
}
