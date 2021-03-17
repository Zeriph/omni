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
#if !defined(OMNI_IO_FILE_EX_HPP)
#define OMNI_IO_FILE_EX_HPP 1

/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. do not #include <omni/xxx_impl.hxx> and do not compile this source directly.
 this file is included directly in other source.
*/

// so as not to accidentally build this file with the source
// these macros are defined in io_file_rw.hxx
#if !defined(OMNI_IO_FILE_EX_FW)
    #error invalid preprocessor directive detected
#endif

namespace omni { namespace io { /** @internal library helper */ namespace file_internal {
    /** @internal library helper */
    inline bool exists(const std::string& file)
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
    /** @internal library helper */
    inline bool exists(const std::wstring& file)
    {
        if (file.empty()) { return false; }
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, file, false)
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
            if (::stat(omni::string::to_string(file).c_str(), &fi) == 0) {
                #if defined(S_ISSOCK)
                    return !(S_ISDIR(fi.st_mode)) && !(S_ISSOCK(fi.st_mode));
                #else
                    return !(S_ISDIR(fi.st_mode));
                #endif
            }
            return false;
        #endif
    }
}}}

namespace omni { namespace io { /** @internal library helper */ namespace dir_internal {
    /** @internal library helper */
    inline bool exists(const std::string& folder)
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
    /** @internal library helper */
    inline bool exists(const std::wstring& folder)
    {
        if (folder.empty()) { return false; }
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                std::wstring tf = OMNI_FILE_CHECKW_FW(tf, folder, false)
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
}}}

#undef OMNI_IO_FILE_EX_FW

#endif // OMNI_IO_FILE_EX_HPP
