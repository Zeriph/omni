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
#if !defined(OMNI_IO_PATH_FW) || !defined(OMNI_PATH_FW) || !defined(OMNI_CHAR_T_FW) || !defined(OMNI_L_FW) || !defined(OMNI_STRING_T_FW)
    #error invalid preprocessor directive detected
#endif

#if defined(OMNI_IO_PATH_INTERNAL_FW)
    namespace omni { namespace io { /** @internal library helper */ namespace path_internal {
        /** @internal library helper */
        template < typename std_string_t >
        std_string_t generate(const std_string_t& path, const std_string_t& file, const std_string_t& ext)
        {
            std_string_t ret = omni::io::path::combine(path, file + ext);
            bool fex = omni::io::file::exists(ret);
            bool dex = omni::io::directory::exists(ret);
            bool is_file = fex && !dex;
            bool is_dir = dex && !fex;
            if (is_file || is_dir) {
                uint64_t max_val = std::numeric_limits<uint64_t>::max();
                std_string_t fpath = (file.empty() ?
                    (path + omni::string::util::lexical_cast<std_string_t>(" - ")) :
                    omni::io::path::combine(path, (file + omni::string::util::lexical_cast<std_string_t>(" - "))));
                for (uint64_t i = 1; i < max_val; ++i) {
                    ret = fpath + omni::string::util::lexical_cast<std_string_t, uint64_t>(i) + ext;
                    if (
                        (is_file && !omni::io::file::exists(ret)) ||
                        (is_dir && !omni::io::directory::exists(ret))
                    ) { break; }
                }
            }
            return ret;
        }
        
        /** @internal library helper */
        template < typename T >
        T get_invalid_file_chars()
        { return T(); }
    } } }
#endif

namespace omni { namespace io { /** @internal library helper */ namespace path_internal {
    /** @internal library helper */
    template <>
    omni::seq::OMNI_CHAR_T_FW get_invalid_file_chars<omni::seq::OMNI_CHAR_T_FW>()
    {
        static omni::seq::OMNI_CHAR_T_FW::value_type ret[] = {OMNI_L_FW('<'),OMNI_L_FW('>'),OMNI_L_FW(':'),OMNI_L_FW('"'),
                                OMNI_L_FW('/'),OMNI_L_FW('\\'),OMNI_L_FW('|'),OMNI_L_FW('?'),OMNI_L_FW('*'),
                                0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
        return omni::seq::OMNI_CHAR_T_FW(ret, ret + sizeof(ret)/sizeof(omni::seq::OMNI_CHAR_T_FW::value_type));
    }
} } }

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::change_extension(const OMNI_STRING_T_FW& path, const OMNI_STRING_T_FW& extension)
{
    std::size_t psep = path.find_last_of(OMNI_L_FW("."));
    if (psep == OMNI_STRING_T_FW::npos) {
        return path + OMNI_L_FW(".") + extension;
    }
    return path.substr(0, psep) + OMNI_L_FW(".") + extension;
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::combine(const omni_sequence_t<OMNI_STRING_T_FW>& paths, const OMNI_STRING_T_FW& seperator)
{
    std::size_t psep;
    OMNI_STRING_T_FW ret, sep;
    omni_sequence_t<OMNI_STRING_T_FW>::const_iterator itr = paths.begin();
    for (; itr != paths.end(); ++itr) {
        psep = itr->find_last_of(seperator);
        if ((itr == paths.begin()) || (psep == itr->length()-1)) {
            ret += *itr;
        } else {
            ret += seperator + *itr;
        }
    }
    return ret;
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::combine(const OMNI_STRING_T_FW& path1, const OMNI_STRING_T_FW& path2)
{ 
    if (path1.empty()) { return path2; }
    std::size_t psep = path1.find_last_of(OMNI_L_FW("/\\"));
    if (psep == path1.length()-1) { return path1 + path2; }
    if (path1.find_first_of(OMNI_L_FW("\\")) != OMNI_STRING_T_FW::npos) {
        return path1 + OMNI_L_FW("\\") + path2;
    }
    return path1 + OMNI_L_FW("/") + path2;
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::get_extension(const OMNI_STRING_T_FW& path)
{
    std::size_t psep = path.find_last_of(OMNI_L_FW("."));
    if (psep == OMNI_STRING_T_FW::npos) { return OMNI_STRING_T_FW(); }
    return path.substr(psep);
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::get_name(const OMNI_STRING_T_FW& path)
{
    std::size_t psep = path.find_last_of(OMNI_L_FW("/\\"));
    if (psep == OMNI_STRING_T_FW::npos) { return path; }
    return path.substr(psep+1);
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::get_name_without_extension(const OMNI_STRING_T_FW& path)
{
    std::size_t psep = path.find_last_of(OMNI_L_FW("/\\"));
    std::size_t rng = path.find_last_of(OMNI_L_FW("."));
    if (psep == OMNI_STRING_T_FW::npos) { return ((rng == OMNI_STRING_T_FW::npos) ? path : path.substr(rng)); }
    if (rng == OMNI_STRING_T_FW::npos) { return path.substr(psep+1); }
    return path.substr(psep+1, (rng - psep - 1));
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::get_parent_name(const OMNI_STRING_T_FW& path)
{
    std::size_t psep = path.find_last_of(OMNI_L_FW("/\\"));
    if (psep == OMNI_STRING_T_FW::npos) { return OMNI_STRING_T_FW(); }
    return path.substr(0, psep);
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::generate(const OMNI_STRING_T_FW& path)
{
    return omni::io::path_internal::generate<OMNI_STRING_T_FW>(path, OMNI_STRING_T_FW(), OMNI_STRING_T_FW());
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::generate(const OMNI_STRING_T_FW& path, const OMNI_STRING_T_FW& file)
{
    return omni::io::path_internal::generate<OMNI_STRING_T_FW>(path, file, OMNI_STRING_T_FW());
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::generate(const OMNI_STRING_T_FW& path, const OMNI_STRING_T_FW& file, const OMNI_STRING_T_FW& ext)
{
    return omni::io::path_internal::generate<OMNI_STRING_T_FW>(path, file, ext);
}

omni::seq::OMNI_CHAR_T_FW omni::io::OMNI_PATH_FW::get_invalid_file_chars()
{
    return omni::io::path_internal::get_invalid_file_chars<omni::seq::OMNI_CHAR_T_FW>();
}

omni::seq::OMNI_CHAR_T_FW omni::io::OMNI_PATH_FW::get_invalid_path_chars()
{
    return omni::io::path_internal::get_invalid_file_chars<omni::seq::OMNI_CHAR_T_FW>();
}

bool omni::io::OMNI_PATH_FW::has_extension(const OMNI_STRING_T_FW& path)
{
    return path.find_last_of(OMNI_L_FW(".")) != OMNI_STRING_T_FW::npos;
}

bool omni::io::OMNI_PATH_FW::is_path_absolute(const OMNI_STRING_T_FW& path)
{
    return
    (
        (path.find(OMNI_L_FW("..")) == OMNI_STRING_T_FW::npos) &&
            (
                ((path.size() > 0) && ((path.at(0) == OMNI_L_FW('/')) || (path.at(0) == OMNI_L_FW('\\')))) ||
                ((path.size() > 1) && (path.at(1) == OMNI_L_FW(':')))
            )
    );
}

OMNI_STRING_T_FW omni::io::OMNI_PATH_FW::trim_trailing_slash(const OMNI_STRING_T_FW& path)
{
    std::size_t found = path.find_last_not_of(OMNI_L_FW("\\/"));
    if (found != OMNI_STRING_T_FW::npos) {
        return path.substr(0, found+1);
    }
    return path;
}
