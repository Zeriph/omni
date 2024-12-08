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
    #error "invalid preprocessor directive detected"
#endif

#if defined(OMNI_IO_DIR_INTERNAL_FW)
    namespace omni { namespace io { namespace dir_internal {
        bool create(const std::string& folder, const omni::io::options& io_ops)
        {
            if (omni::io::dir_internal::exists(folder)) { return true; }
            bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
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
                        OMNI_ERRV_RETV_FW("could not create parent directory: ", omni::string::to_string_t(top), omni::exceptions::path_exception("Could not create parent directory", omni::string::to_string(top)), false)
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
        bool create(const std::wstring& folder, const omni::io::options& io_ops)
        {
            if (omni::io::dir_internal::exists(folder)) { return true; }
            bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
            if (folder == L"\\" || folder == L"/") { return true; }
            #if defined(OMNI_OS_WIN)
                if (folder.length() == 2 && folder.at(1) == L':') { return true; }
            #endif
            if (create_path) {
                std::wstring top = omni::io::wpath::get_parent_name(folder);
                if (!omni::io::dir_internal::exists(top)) {
                    if (!omni::io::dir_internal::create(top, true)) {
                        OMNI_ERRV_RETV_FW("could not create parent directory: ", omni::string::to_string_t(top), omni::exceptions::path_exception("Could not create parent directory", omni::string::to_string(top)), false)
                    }
                }
            }
            #if defined(OMNI_OS_WIN) && defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, folder, false)
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

        bool mv(const std::string& folder, const std::string& new_name, const omni::io::options& io_ops)
        {
            bool overwrite = ((io_ops & omni::io::options::OVERWRITE) == omni::io::options::OVERWRITE);
            bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
            std::string root = omni::io::cpath::get_parent_name(new_name);
            if (!omni::io::dir_internal::exists(root)) {
                if (create_path) {
                    if (!omni::io::dir_internal::create(root, io_ops)) {
                        OMNI_D1_FW("could not create parent directory");
                        return false;
                    }
                } else {
                    OMNI_D1_FW("error moving file: new path does not exist");
                    return false;
                }
            }
            if (omni::io::dir_internal::exists(new_name) && !overwrite) {
                return false;
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
        bool mv(const std::wstring& folder, const std::wstring& new_name, const omni::io::options& io_ops)
        {
            bool overwrite = ((io_ops & omni::io::options::OVERWRITE) == omni::io::options::OVERWRITE);
            bool create_path = ((io_ops & omni::io::options::CREATE_PATH) == omni::io::options::CREATE_PATH);
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
            if (omni::io::dir_internal::exists(new_name) && !overwrite) {
                return true;
            }
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    std::wstring tf = OMNI_FILE_CHECKW_FW(tf, folder, false)
                    std::wstring nf = OMNI_FILE_CHECKW_FW(nf, new_name, false)
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

        template < typename STR >
        void recursive_rem(const STR& name) 
        {
            omni_sequence_t<STR> files;
            omni_sequence_t<STR> dirs;
            omni::io::directory::get_files(name, files);
            omni::io::directory::get_directories(name, dirs);
            for (typename omni_sequence_t<STR>::iterator file = files.begin(); file != files.end(); ++file) {
                omni::io::file::remove(*file);
            }
            for (typename omni_sequence_t<STR>::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
                omni::io::directory::remove(*dir, true);
            }
        }
        bool rem(const std::string& folder, bool recursive)
        {
            if (!omni::io::dir_internal::exists(folder)) { return true; }
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
        bool rem(const std::wstring& folder, bool recursive)
        {
            if (!omni::io::dir_internal::exists(folder)) { return true; }
            std::wstring name = omni::io::path::trim_trailing_slash(folder);
            if (name == L"/" || name == L"\\" || (name.size() == 2 && name.at(1) == L':')) { return false; } // its a root drive
            if (recursive) {
                OMNI_DV1_FW("recursively deleting: ", omni::string::to_string_t(name));
                recursive_rem(name);
            }
            #if defined(OMNI_OS_WIN)
                #if defined(OMNI_WIN_API)
                    std::wstring tf = OMNI_FILE_CHECKW_FW(tf, name, false)
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

bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, bool recursive, const omni::io::options& io_ops)
{
    if (!omni::io::OMNI_PATH_FW::create(new_name)) { return false; }
    omni::seq::OMNI_CHAR_T_FW files;
    omni::io::OMNI_PATH_FW::get_files(folder, files);
    bool ret = true;
    if (files.size() > 0) {
        for (omni::seq::OMNI_CHAR_T_FW::iterator file = files.begin(); file != files.end(); ++file) {
            OMNI_DV1_FW("copying file to: ", omni::string::to_string_t(omni::io::path::combine(new_name, omni::io::path::get_name(*file))));
            if (!omni::io::file::copy(*file, omni::io::path::combine(new_name, omni::io::path::get_name(*file)), io_ops)) {
                OMNI_DV1_FW("could not copy file: ", omni::string::to_string_t(*file));
                ret = false;
            }
        }
    }
    if (recursive) {
        omni::seq::OMNI_CHAR_T_FW dirs;
        omni::io::OMNI_PATH_FW::get_directories(folder, dirs);
        if (dirs.size() > 0) {
            for (omni::seq::OMNI_CHAR_T_FW::iterator dir = dirs.begin(); dir != dirs.end(); ++dir) {
                OMNI_DV1_FW("copying directory to: ", omni::string::to_string_t(omni::io::path::combine(new_name, omni::io::path::get_name(*dir))));
                if (!omni::io::OMNI_PATH_FW::copy(*dir, omni::io::path::combine(new_name, omni::io::path::get_name(*dir)), recursive, io_ops)) {
                    OMNI_DV1_FW("could not copy dir: ", omni::string::to_string_t(*dir));
                    ret = false;
                }
            }
        }
    }
    return ret;
}

bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& folder, const omni::io::options& io_ops)
{
    if (omni::io::dir_internal::exists(folder)) { return true; }
    return omni::io::dir_internal::create(folder, io_ops);
}

bool omni::io::OMNI_PATH_FW::exists(const OMNI_STRING_T_FW& folder)
{
    return omni::io::dir_internal::exists(folder);
}

bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, const omni::io::options& io_ops)
{
    // TODO: add a 'copy_first'
    /*
        TODO: exceptions for the following -> 

        Exceptions
        IOException

        An attempt was made to move a directory to a different volume.

        -or-

        destDirName already exists. See the Note in the Remarks section.

        -or-

        The sourceDirName and destDirName parameters refer to the same file or directory.

        -or-

        The directory or a file within it is being used by another process.
        UnauthorizedAccessException

        The caller does not have the required permission.
        ArgumentException

        sourceDirName or destDirName is a zero-length string, contains only white space, or contains one or more invalid characters. You can query for invalid characters with the GetInvalidPathChars() method.
        ArgumentNullException

        sourceDirName or destDirName is null.
        PathTooLongException

        The specified path, file name, or both exceed the system-defined maximum length.
        DirectoryNotFoundException

        The path specified by sourceDirName is invalid (for example, it is on an unmapped drive).
    */
    // TODO: change this to 'omni::io::dir_internal::mv(folder, new_name, io_ops)
    if (!omni::io::OMNI_PATH_FW::copy(folder, new_name, true, io_ops)) {
        return false;
    }
    return omni::io::OMNI_PATH_FW::remove(folder, true);
}

bool omni::io::OMNI_PATH_FW::remove(const OMNI_STRING_T_FW& folder, bool recursive)
{
    if (!omni::io::dir_internal::exists(folder)) { return true; } // folder does not exist
    return omni::io::dir_internal::rem(folder, recursive);
}

bool omni::io::OMNI_PATH_FW::can_access(const OMNI_STRING_T_FW& folder) { return omni::io::dir_internal::can_access(folder); }
bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, bool recursive) { return omni::io::OMNI_PATH_FW::copy(folder, new_name, recursive, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::copy(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::copy(folder, new_name, false, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::create(const OMNI_STRING_T_FW& folder) { return omni::io::OMNI_PATH_FW::create(folder, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::exist(const OMNI_STRING_T_FW& file) { return omni::io::OMNI_PATH_FW::exists(file); }
bool omni::io::OMNI_PATH_FW::move(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::move(folder, new_name, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name, const omni::io::options& io_ops) { return omni::io::OMNI_PATH_FW::move(folder, new_name, io_ops); }
bool omni::io::OMNI_PATH_FW::rename(const OMNI_STRING_T_FW& folder, const OMNI_STRING_T_FW& new_name) { return omni::io::OMNI_PATH_FW::rename(folder, new_name, omni::io::options::NONE); }
bool omni::io::OMNI_PATH_FW::remove(const OMNI_STRING_T_FW& folder) { return omni::io::OMNI_PATH_FW::remove(folder, false); }
