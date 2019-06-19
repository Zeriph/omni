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
 to the OMNI_STRING_T_FW and omn::string::X functions (which are aliases for the other namespaces).
 
 Since omni::wstring and omni::cstring are merely wrappers for the omni::string::util functions
 (which are templated) that then pass in the appropriate types (std::string/wstring char/wchar_t)
 putting the relevant code in a header with a few #defs for types makes keeping the files
 in sync (for functions) less messy. It does introduce slight confusion to anyone who might
 want to read this specific code or documentation though, hence this note.
*/

// so as not to accidentally build this file with the source this macro is defined in io.cpp
#if !defined(OMNI_IO_DIR_FW) || !defined(OMNI_PATH_FW) || !defined(OMNI_CHAR_T_FW) || !defined(OMNI_L_FW) || !defined(OMNI_STRING_T_FW)
    #error invalid preprocessor directive detected
#endif

#if defined(OMNI_IO_DIR_INTERNAL_FW)
    namespace omni { namespace io { /** @internal framework helper */ namespace dir_internal {
        /** @internal framework helper */
        bool exists(const std::string& folder)
        {
            if (folder.empty()) { return false; }
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    OMNI_FILE_CHECKA_FW(folder, false)
                    DWORD res = ::GetFileAttributesA(folder.c_str());
                    return (res != INVALID_FILE_ATTRIBUTES && (res & FILE_ATTRIBUTE_DIRECTORY));
                #else
                    struct stat fi;
                    if (::_stat(folder.c_str(), &fi) == 0) { return (S_ISDIR(fi.st_mode)); }
                    return false;    
                #endif
            #else
                struct stat fi;
                if (::stat(folder.c_str(), &fi) == 0) { return (S_ISDIR(fi.st_mode)); }
                return false;
            #endif
        }
        /** @internal framework helper */
        bool exists(const std::wstring& folder)
        {
            if (folder.empty()) { return false; }
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    std::wstring tf = OMNI_FILE_CHECKW_FW(folder, false)
                    DWORD res = ::GetFileAttributesW(tf.c_str());
                    return (res != INVALID_FILE_ATTRIBUTES && (res & FILE_ATTRIBUTE_DIRECTORY));
                #else
                    struct stat fi;
                    if (::_wstat(folder.c_str(), &fi) == 0) { return (S_ISDIR(fi.st_mode)); }
                    return false;
                #endif
            #else
                struct stat fi;
                if (::stat(omni::string::to_string(folder).c_str(), &fi) == 0) { return (S_ISDIR(fi.st_mode)); }
                return false;
            #endif
        }

        /** @internal framework helper */
        bool create(const std::string& folder, bool create_path)
        {
            if (folder == "\\" || folder == "/") { return true; }
            #if defined(OMNI_OS_WIN)
                if (folder.length() == 2 && folder.at(1) == ':') { return true; }
                #if defined(OMNI_WIN_API)
                    OMNI_FILE_CHECKA_FW(folder, false)
                #endif
            #endif
            if (create_path) {
                std::string top = omni::io::cpath::get_parent_name(folder);
                if (!omni::io::dir_internal::exists(top)) {
                    if (!omni::io::dir_internal::create(top, true)) {
                        OMNI_ERRV_RETV_FW("could not create parent directory: ", omni::string::to_string_t(top), omni::exceptions::path_exception(omni::string::to_string(top)), false)
                    }
                }
            }
            return
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    (::CreateDirectoryA(folder.c_str(), NULL) != 0);
                #else
                    (::_mkdir(folder.c_str()) == 0);
                #endif
            #else
                (::mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
            #endif
        }
        /** @internal framework helper */
        bool create(const std::wstring& folder, bool create_path)
        {
            if (folder == L"\\" || folder == L"/") { return true; }
            #if defined(OMNI_OS_WIN)
                if (folder.length() == 2 && folder.at(1) == L':') { return true; }
            #endif
            if (create_path) {
                std::wstring top = omni::io::wpath::get_parent_name(folder);
                if (!omni::io::dir_internal::exists(top)) {
                    if (!omni::io::dir_internal::create(top, true)) {
                        OMNI_ERRV_RETV_FW("could not create parent directory: ", omni::string::to_string_t(top), omni::exceptions::path_exception(omni::string::to_string(top)), false)
                    }
                }
            }
            #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(folder, false)
            #endif
            return
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    (::CreateDirectoryW(tf.c_str(), NULL) != 0);
                #else
                    (::_wmkdir(folder.c_str()) == 0);
                #endif
            #else
                (::mkdir(omni::string::to_string(folder).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
            #endif
        }

        #if defined(OMNI_OS_WIN)
            /** @internal framework helper */
            template < typename SEQ >
            SEQ get_dir_cont_win_fw(const std::string& name, int ftype)
            {
                SEQ dirs;
                std::string full = omni::io::cpath::combine(name, "*");
                #if defined(OMNI_WIN_API)
                    OMNI_FILE_CHECKA_FW(full, dirs)
                    WIN32_FIND_DATAA c_file;
                    HANDLE hFile = ::FindFirstFileA(full.c_str(), &c_file);
                    if (hFile != INVALID_HANDLE_VALUE) {
                        do {
                            std::string fname = std::string(c_file.cFileName);
                            if (fname != "." && fname != ".." ) { // don't add root dir
                                std::string file = omni::io::cpath::combine(name, fname);
                                if (ftype == 0) {
                                    if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                                } else {
                                    if (omni::io::cfile::exists(file)) { dirs.push_back(file); }
                                }
                            }
                        } while (::FindNextFileA(hFile, &c_file));
                    }
                    ::FindClose(hFile);
                #else
                    struct _finddata_t c_file;
                    long hFile;
                    if ((hFile = ::_findfirst(full.c_str(), &c_file)) != -1L) {
                        do {
                            std::string fname = std::string(c_file.name);
                            if (fname != "." && fname != ".." ) { // don't add root dir
                                std::string file = omni::io::cpath::combine(name, fname);
                                if (ftype == 0) {
                                    if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                                } else {
                                    if (omni::io::cfile::exists(file)) { dirs.push_back(file); }
                                }
                            }
                        } while (::_findnext(hFile, &c_file) == 0);
                        ::_findclose(hFile);
                    }
                #endif
                return dirs;
            }
            /** @internal framework helper */
            template < typename SEQ >
            SEQ get_dir_cont_win_fw(const std::wstring& name, int ftype)
            {
                SEQ dirs;
                std::wstring full = omni::io::wpath::combine(name, L"*");
                #if defined(OMNI_WIN_API)
                    std::wstring tf = OMNI_FILE_CHECKW_FW(full, false)
                    WIN32_FIND_DATAW c_file;
                    HANDLE hFile = ::FindFirstFileW(tf.c_str(), &c_file);
                    if (hFile != INVALID_HANDLE_VALUE) {
                        do {
                            std::wstring fname = omni::string::to_wstring(c_file.cFileName);
                            if (fname != L"." && fname != L".." ) { // don't add root dir
                                std::wstring file = omni::io::wpath::combine(name, fname);
                                if (ftype == 0) {
                                    if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                                } else {
                                    if (omni::io::wfile::exists(file)) { dirs.push_back(file); }
                                }
                            }
                        } while (::FindNextFileW(hFile, &c_file));
                    }
                    ::FindClose(hFile);
                #else
                    struct _wfinddata_t c_file;
                    long hFile;
                    if ((hFile = ::_wfindfirst(full.c_str(), &c_file)) != -1L) {
                        do {
                            std::wstring fname = std::wstring(c_file.name);
                            if (fname != L"." && fname != L".." ) { // don't add root dir
                                std::wstring file = omni::io::wpath::combine(name, fname);
                                if (ftype == 0) {
                                    if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                                } else {
                                    if (omni::io::wfile::exists(file)) { dirs.push_back(file); }
                                }
                            }
                        } while (::_wfindnext(hFile, &c_file) == 0);
                        ::_wfindclose(hFile);
                    }
                #endif
                return dirs;
            }
        #else
            /** @internal framework helper */
            template < typename SEQ >
            SEQ get_dir_cont_nix_fw(const std::string& name, int ftype)
            {
                SEQ dirs;
                DIR *dp;
                struct dirent *dirp;
                std::string dir = name;
                if ((dp = ::opendir(dir.c_str())) == NULL) {
                    OMNI_ERRV_RETV_FW("Error opening file: ", errno, omni::exceptions::path_exception(name), dirs)
                }
                while ((dirp = ::readdir(dp)) != NULL) {
                    std::string fname = std::string(dirp->d_name);
                    if (fname == "." || fname == "..") { continue; }
                    std::string file = omni::io::cpath::combine(dir, fname);
                    if (ftype == 0) {
                        if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                    } else {
                        if (omni::io::cfile::exists(file)) { dirs.push_back(file); }
                    }
                }
                ::closedir(dp);
                return dirs;
            }
            /** @internal framework helper */
            template < typename SEQ >
            SEQ get_dir_cont_nix_fw(const std::wstring& name, int ftype)
            {
                SEQ dirs;
                DIR *dp;
                struct dirent *dirp;
                if ((dp = ::opendir(omni::string::to_string(name).c_str())) == NULL) {
                    OMNI_ERRV_RETV_FW("Error opening file: ", errno, omni::exceptions::path_exception(omni::string::to_string(name)), dirs)
                }
                while ((dirp = ::readdir(dp)) != NULL) {
                    std::wstring fname = std::wstring(omni::string::to_wstring(dirp->d_name));
                    if (fname == L"." || fname == L"..") { continue; }
                    std::wstring file = omni::io::wpath::combine(name, fname);
                    if (ftype == 0) {
                        if (omni::io::dir_internal::exists(file)) { dirs.push_back(file); }
                    } else {
                        if (omni::io::wfile::exists(file)) { dirs.push_back(file); }
                    }
                }
                ::closedir(dp);
                return dirs;
            }
        #endif

        /** @internal framework helper */
        template < typename STR, typename SEQ >
        SEQ get_elements(const STR& folder, int ftype)
        {
            STR name = omni::io::path::trim_trailing_slash(folder);
            if (!omni::io::dir_internal::exists(name)) {
                SEQ dirs;
                OMNI_ERRV_RETV_FW("directory does not exist: ", omni::string::to_string_t(name), omni::exceptions::path_exception(omni::string::to_string(name)), dirs)
            }
            #if defined(OMNI_OS_WIN)
                return get_dir_cont_win_fw<SEQ>(name, ftype);
            #else
                return get_dir_cont_nix_fw<SEQ>(name, ftype);
            #endif
        }

        /** @internal framework helper */
        bool mv(const std::string& folder, const std::string& new_name, bool create_path)
        {
            std::string root = omni::io::cpath::get_parent_name(new_name);
            if (!omni::io::dir_internal::exists(root)) {
                if (create_path) {
                    if (!omni::io::dir_internal::create(root, true)) {
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
                    OMNI_FILE_CHECKA_FW(folder, false)
                    OMNI_FILE_CHECKA_FW(new_name, false)
                    BOOL ret = ::MoveFileA(folder.c_str(), new_name.c_str());
                    if (ret == 0) {
                        OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::last_error_str()));
                        return false;
                    }
                #else
                    int ret = ::_rename(folder.c_str(), new_name.c_str());
                    if (ret != 0) {
                        OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                        return false;
                    }
                #endif
            #else
                int ret = ::rename(folder.c_str(), new_name.c_str());
                if (ret != 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                    return false;
                }
            #endif
            return omni::io::dir_internal::exists(new_name);
        }
        /** @internal framework helper */
        bool mv(const std::wstring& folder, const std::wstring& new_name, bool create_path)
        {
            std::wstring root = omni::io::wpath::get_parent_name(new_name);
            if (!omni::io::dir_internal::exists(root)) {
                if (create_path) {
                    if (!omni::io::dir_internal::create(root, true)) {
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
                    std::wstring tf = OMNI_FILE_CHECKW_FW(folder, false)
                    std::wstring nf = OMNI_FILE_CHECKW_FW(new_name, false)
                    BOOL ret = ::MoveFileW(tf.c_str(), nf.c_str());
                    if (ret == 0) {
                        OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::last_error_str()));
                        return false;
                    }
                #else
                    int ret = ::_wrename(folder.c_str(), new_name.c_str());
                    if (ret != 0) {
                        OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                        return false;
                    }
                #endif
            #else
                int ret = ::rename(omni::string::to_string(folder).c_str(), omni::string::to_string(new_name).c_str());
                if (ret != 0) {
                    OMNI_DV1_FW("error moving file: ", omni::string::to_string_t(omni::system::error_str(ret)));
                    return false;
                }
            #endif
            return omni::io::dir_internal::exists(new_name);
        }

        /** @internal framework helper */
        template < typename STR >
        void recursive_rem(const STR& name) 
        {
            omni_sequence_t<STR> files = omni::io::directory::get_files(name);
            omni_sequence_t<STR> dirs = omni::io::directory::get_directories(name);
            for (typename omni_sequence_t<STR>::iterator file = files.begin(); file != files.end(); ++file) {
                omni::io::file::remove(*file);
            }
            for (typename omni_sequence_t<STR>::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
                omni::io::directory::remove(*dir, true);
            }
        }
        /** @internal framework helper */
        bool rem(const std::string& folder, bool recursive)
        {
            std::string name = omni::io::path::trim_trailing_slash(folder);
            if (name == "/" || name == "\\" || (name.size() == 2 && name.at(1) == ':')) { return false; } // its a root drive
            if (recursive) {
                OMNI_DV1_FW("recursively deleting: ", omni::string::to_string_t(name));
                recursive_rem(name);
            }
            OMNI_DV1_FW("deleting: ", omni::string::to_string_t(name));
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    OMNI_FILE_CHECKA_FW(name, false)
                    if (::RemoveDirectoryA(name.c_str()) == 0)
                #else
                    if (::_rmdir(name.c_str()) != 0)
                #endif
            #else
                if (::rmdir(name.c_str()) != 0)
            #endif
            {
                OMNI_DV1_FW("folder could not be deleted: ", omni::string::to_string_t(omni::system::last_error_str()));
                return false;
            }
            return !omni::io::dir_internal::exists(folder);
        }
        /** @internal framework helper */
        bool rem(const std::wstring& folder, bool recursive)
        {
            std::wstring name = omni::io::path::trim_trailing_slash(folder);
            if (name == L"/" || name == L"\\" || (name.size() == 2 && name.at(1) == L':')) { return false; } // its a root drive
            if (recursive) {
                OMNI_DV1_FW("recursively deleting: ", omni::string::to_string_t(name));
                recursive_rem(name);
            }
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    std::wstring tf = OMNI_FILE_CHECKW_FW(name, false)
                    if (::RemoveDirectoryW(tf.c_str()) == 0)
                #else
                    if (::_wrmdir(name.c_str()) != 0)
                #endif
            #else
                if (::rmdir(omni::string::to_string(name).c_str()) != 0)
            #endif
            {
                OMNI_DV1_FW("folder could not be deleted: ", omni::string::to_string_t(omni::system::last_error_str()));
                return false;
            }
            return !omni::io::dir_internal::exists(folder);
        }
    } } }
#endif // OMNI_IO_DIR_INTERNAL_FW

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::copy(folder, new_name, true); }
bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& folder) { return omni::io::OMNI_PATH_FW::create(folder, true); }
bool omni::io::OMNI_PATH_FW::exist(const OMNI_STRING_T_FW& file) { return omni::io::OMNI_PATH_FW::exists(file); }
bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::move(folder, new_name, false); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, bool create_path) { return omni::io::OMNI_PATH_FW::move(folder, new_name, create_path); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::rename(folder, new_name, false); }
bool omni::io::OMNI_PATH_FW::remove(const OMNI_STRING_T_FW& folder) { return omni::io::OMNI_PATH_FW::remove(folder, false); }

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, bool recursive)
{
    if (!omni::io::directory::create(new_name)) { return false; }
    omni::seq::OMNI_CHAR_T_FW files = omni::io::directory::get_files(folder);
    bool ret = true;
    if (files.size() > 0) {
        for (omni::seq::OMNI_CHAR_T_FW::iterator file = files.begin(); file != files.end(); ++file) {
            OMNI_DV1_FW("copying file to: ", omni::string::to_string_t(omni::io::path::combine(new_name, omni::io::path::get_name(*file))));
            if (!omni::io::file::copy(*file, omni::io::path::combine(new_name, omni::io::path::get_name(*file)))) {
                OMNI_DV1_FW("could not copy file: ", omni::string::to_string_t(*file));
                ret = false;
            }
        }
    }
    if (recursive) {
        omni::seq::OMNI_CHAR_T_FW dirs = omni::io::directory::get_directories(folder);
        if (dirs.size() > 0) {
            for (omni::seq::OMNI_CHAR_T_FW::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
                OMNI_DV1_FW("copying directory to: ", omni::string::to_string_t(omni::io::path::combine(new_name, omni::io::path::get_name(*dir))));
                if (!omni::io::directory::copy(*dir, omni::io::path::combine(new_name, omni::io::path::get_name(*dir)))) {
                    OMNI_DV1_FW("could not copy dir: ", omni::string::to_string_t(*dir));
                    ret = false;
                }
            }
        }
    }
    return ret;
}

bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& folder, bool create_path)
{
    if (omni::io::dir_internal::exists(folder)) { return true; }
    return omni::io::dir_internal::create(folder, create_path);
}

bool omni::io::OMNI_PATH_FW::exists(const OMNI_STRING_T_FW& folder)
{
    return omni::io::dir_internal::exists(folder);
}

omni::seq::OMNI_CHAR_T_FW omni::io::OMNI_PATH_FW::get_directories(const OMNI_STRING_T_FW& folder)
{
    return omni::io::dir_internal::get_elements<OMNI_STRING_T_FW, omni::seq::OMNI_CHAR_T_FW>(folder, 0);
}

omni::seq::OMNI_CHAR_T_FW omni::io::OMNI_PATH_FW::get_files(const OMNI_STRING_T_FW& folder)
{
    return omni::io::dir_internal::get_elements<OMNI_STRING_T_FW, omni::seq::OMNI_CHAR_T_FW>(folder, 1);
}

omni::seq::OMNI_CHAR_T_FW omni::io::OMNI_PATH_FW::get_all_directories(const OMNI_STRING_T_FW& folder)
{
    omni::seq::OMNI_CHAR_T_FW dirs = omni::io::OMNI_PATH_FW::get_directories(folder);
    omni::seq::OMNI_CHAR_T_FW subs;
    for (omni::seq::OMNI_CHAR_T_FW::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
        omni::seq::OMNI_CHAR_T_FW sub = omni::io::OMNI_PATH_FW::get_all_directories(*dir);
        subs.insert(subs.end(), sub.begin(), sub.end());
    }
    dirs.insert(dirs.end(), subs.begin(), subs.end());
    return dirs;   
}

omni::seq::OMNI_CHAR_T_FW omni::io::OMNI_PATH_FW::get_all_files(const OMNI_STRING_T_FW& folder)
{
    omni::seq::OMNI_CHAR_T_FW files = omni::io::OMNI_PATH_FW::get_files(folder);
    omni::seq::OMNI_CHAR_T_FW dirs = omni::io::OMNI_PATH_FW::get_directories(folder);
    for (omni::seq::OMNI_CHAR_T_FW::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
        omni::seq::OMNI_CHAR_T_FW sub = omni::io::OMNI_PATH_FW::get_all_files(*dir);
        files.insert(files.end(), sub.begin(), sub.end());
    }
    return files;
}

bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, bool create_path)
{
    if (!omni::io::OMNI_PATH_FW::copy(folder, new_name, create_path)) {
        return false;
    }
    return omni::io::OMNI_PATH_FW::remove(folder, true);
}

bool omni::io::OMNI_PATH_FW::remove(const OMNI_STRING_T_FW& folder, bool recursive)
{
    if (!omni::io::dir_internal::exists(folder)) { return true; } // folder doesn't exist
    return omni::io::dir_internal::rem(folder, recursive);
}
