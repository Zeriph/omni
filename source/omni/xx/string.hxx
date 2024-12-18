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
 to the omni::string_t and omn::string::X functions (which are aliases for the other namespaces).
 
 Since omni::wstring and omni::cstring are merely wrappers for the omni::string::util functions
 (which are templated) that then pass in the appropriate types (std::string/wstring char/wchar_t)
 putting the relevant code in a header with a few #defs for types makes keeping the files
 in sync (for functions) less messy. It does introduce slight confusion to anyone who might
 want to read this specific code or documentation though, hence this note.
*/

// so as not to accidentally build this file with the source
// these macros are defined in string/util.hpp string/cstring.hpp and string/wstring.hpp
#if !defined(OMNI_CHAR_T_FW) || !defined(OMNI_STRING_T_FW)
    #error "invalid preprocessor directive detected"
#endif

// namespace omni::string/cstring/wstring {

namespace binary {
    inline bool is_valid(const OMNI_STRING_T_FW& str)
    {
        return omni::string::util::binary::is_valid<OMNI_STRING_T_FW>(str);
    }
    
    inline OMNI_STRING_T_FW from_uint(unsigned int val, bool trim)
    {
        return omni::string::util::binary::from_uint<OMNI_STRING_T_FW>(val, trim);
    }
    
    inline OMNI_STRING_T_FW from_uint(unsigned int val)
    {
        return omni::string::util::binary::from_uint<OMNI_STRING_T_FW>(val, true);
    }
    
    inline OMNI_STRING_T_FW from_ulong(unsigned long val, bool trim)
    {
        return omni::string::util::binary::from_ulong<OMNI_STRING_T_FW>(val, trim);
    }
    
    inline OMNI_STRING_T_FW from_ulong(unsigned long val)
    {
        return omni::string::util::binary::from_ulong<OMNI_STRING_T_FW>(val, true);
    }
    
    inline unsigned int to_uint(const OMNI_STRING_T_FW& str)
    {
        return omni::string::util::binary::to_uint(str);
    }
    
    inline unsigned long to_ulong(const OMNI_STRING_T_FW& str)
    {
        return omni::string::util::binary::to_ulong(str);
    }
    
    inline std::size_t to_size_t(const OMNI_STRING_T_FW& str)
    {
        return omni::string::util::binary::to_size_t(str);
    }
}

inline bool contains(const OMNI_STRING_T_FW& haystack, const OMNI_STRING_T_FW& needle, bool ignore_case)
{
    return omni::string::util::contains(haystack, needle, ignore_case);
}

inline bool contains(const OMNI_STRING_T_FW& haystack, const OMNI_STRING_T_FW& needle)
{
    return omni::string::util::contains(haystack, needle, false);
}

inline int32_t compare(const OMNI_STRING_T_FW& str1, size_t idx1, const OMNI_STRING_T_FW& str2, size_t idx2, size_t len, const omni::string::compare_options& options)
{
    return omni::string::util::compare(str1, idx1, str2, idx2, len, options);
}

inline int32_t compare(const OMNI_STRING_T_FW& str1, size_t idx1, size_t len1, const OMNI_STRING_T_FW& str2, size_t idx2, size_t len2, const omni::string::compare_options& options)
{
    return omni::string::util::compare(str1, idx1, len1, str2, idx2, len2, options);
}

inline bool ends_with(const OMNI_STRING_T_FW& haystack, const OMNI_STRING_T_FW& needle)
{
    return omni::string::util::ends_with(haystack, needle);
}

inline bool ends_with(const OMNI_STRING_T_FW& haystack, const OMNI_STRING_T_FW& needle, bool ignore_case)
{
    return omni::string::util::ends_with(haystack, needle, ignore_case);
}

inline bool is_numeric(const OMNI_STRING_T_FW& str, bool ignore_period)
{
    return omni::string::util::is_numeric(str, ignore_period);
}

inline bool is_numeric(const OMNI_CHAR_T_FW* str, bool ignore_period)
{
    return omni::string::util::is_numeric(str, ignore_period);
}

template < std::size_t X >
inline bool is_numeric(const OMNI_CHAR_T_FW (&str)[X], bool ignore_period)
{
    return omni::string::util::is_numeric(OMNI_STRING_T_FW(str), ignore_period);
}

inline bool is_numeric(const OMNI_STRING_T_FW& str)
{
    return omni::string::util::is_numeric(str, false);
}

inline bool is_numeric(const OMNI_CHAR_T_FW* str)
{
    return omni::string::util::is_numeric(str, false);
}

template < std::size_t X >
inline bool is_numeric(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::is_numeric(OMNI_STRING_T_FW(str), false);
}

inline OMNI_STRING_T_FW pad_left(OMNI_STRING_T_FW str, OMNI_CHAR_T_FW pad, std::size_t count)
{
    return omni::string::util::pad_left(str, pad, count);
}

inline OMNI_STRING_T_FW pad_left_full(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& pad, std::size_t count)
{
    return omni::string::util::pad_left_full(str, pad, count);
}

template < std::size_t X >
inline OMNI_STRING_T_FW pad_left_full(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&pad)[X], std::size_t count)
{
    return omni::string::util::pad_left_full<OMNI_STRING_T_FW, X>(str, pad, count);
}

inline OMNI_STRING_T_FW pad_right(OMNI_STRING_T_FW str, OMNI_CHAR_T_FW pad, std::size_t count)
{
    return omni::string::util::pad_right(str, pad, count);
}

inline OMNI_STRING_T_FW pad_right_full(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& pad, std::size_t count)
{
    return omni::string::util::pad_right_full(str, pad, count);
}

template < std::size_t X >
inline OMNI_STRING_T_FW pad_right_full(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&pad)[X], std::size_t count)
{
    return omni::string::util::pad_right_full<OMNI_STRING_T_FW, X>(str, pad, count);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, std::size_t pos, bool ignore_case)
{
    return omni::string::util::replace(str, fnd, newstr, pos, ignore_case);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr)
{
    return omni::string::util::replace(str, fnd, newstr, 0, false);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, bool ignore_case)
{
    return omni::string::util::replace(str, fnd, newstr, 0, ignore_case);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, std::size_t pos)
{
    return omni::string::util::replace(str, fnd, newstr, pos, false);
}

template < std::size_t X, std::size_t Y >
inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&fnd)[X], const OMNI_CHAR_T_FW (&newstr)[Y], std::size_t pos)
{
    return omni::string::util::replace(str, fnd, newstr, pos);
}

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, std::size_t pos, bool ignore_case)
{
    return omni::string::util::replace_all(str, fnd, newstr, pos, ignore_case);
}

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr)
{
    return omni::string::util::replace_all(str, fnd, newstr, 0, false);
}

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, bool ignore_case)
{
    return omni::string::util::replace_all(str, fnd, newstr, 0, ignore_case);
}

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, std::size_t pos)
{
    return omni::string::util::replace_all(str, fnd, newstr, pos, false);
}

template < std::size_t X, std::size_t Y >
inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&fnd)[X], const OMNI_CHAR_T_FW (&newstr)[Y], std::size_t pos)
{
    return omni::string::util::replace_all(str, fnd, newstr, pos);
}

inline OMNI_STRING_T_FW reverse(const OMNI_STRING_T_FW& str)
{
    return omni::string::util::reverse(str);
}

template < std::size_t X >
inline OMNI_STRING_T_FW reverse(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::reverse(OMNI_STRING_T_FW(str));
}

template < template < class, class > class std_seq_t, class std_allocator_t >
std_seq_t<OMNI_STRING_T_FW, std_allocator_t> split(const OMNI_STRING_T_FW& str, const OMNI_STRING_T_FW& delimeter, std::size_t max_val)
{
    return omni::string::util::split< std_seq_t, OMNI_STRING_T_FW, std_allocator_t >(str, delimeter, max_val);
}

template < template < class, class > class std_seq_t >
inline std_seq_t<OMNI_STRING_T_FW, std::allocator<OMNI_STRING_T_FW> > split(const OMNI_STRING_T_FW& str, const OMNI_STRING_T_FW& delimeter, std::size_t max_val)
{
    return omni::string::util::split< std_seq_t, OMNI_STRING_T_FW, std::allocator<OMNI_STRING_T_FW> >(str, delimeter, max_val);
}

inline omni_sequence_t<OMNI_STRING_T_FW> split(const OMNI_STRING_T_FW& str, const OMNI_STRING_T_FW& delimeter, std::size_t max)
{
    return omni::string::util::split(str, delimeter, max);
}

inline omni_sequence_t<OMNI_STRING_T_FW> split(const OMNI_STRING_T_FW& str, const OMNI_STRING_T_FW& delimeter)
{
    return omni::string::util::split(str, delimeter, 0);
}

inline bool starts_with(const OMNI_STRING_T_FW& haystack, const OMNI_STRING_T_FW& needle)
{
    return omni::string::util::starts_with(haystack, needle);
}

inline bool starts_with(const OMNI_STRING_T_FW& haystack, const OMNI_STRING_T_FW& needle, bool ignore_case)
{
    return omni::string::util::starts_with(haystack, needle, ignore_case);
}

inline OMNI_STRING_T_FW to_lower(OMNI_STRING_T_FW str)
{
    return omni::string::util::to_lower(str);
}

inline OMNI_STRING_T_FW lcfirst(OMNI_STRING_T_FW str)
{
    return omni::string::util::lcfirst(str);
}

template < std::size_t X >
inline OMNI_STRING_T_FW lcfirst(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::lcfirst(OMNI_STRING_T_FW(str));
}

inline OMNI_STRING_T_FW to_upper(OMNI_STRING_T_FW str)
{
    return omni::string::util::to_upper(str);
}

inline OMNI_STRING_T_FW ucfirst(const OMNI_STRING_T_FW& str)
{
    return omni::string::util::ucfirst(str);
}

template < std::size_t X >
inline OMNI_STRING_T_FW ucfirst(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::ucfirst(OMNI_STRING_T_FW(str));
}

inline OMNI_STRING_T_FW ucwords(const OMNI_STRING_T_FW& str, const std::string& separators)
{
    return omni::string::util::ucwords(str, separators);
}

inline OMNI_STRING_T_FW ucwords(const OMNI_STRING_T_FW& str)
{
    return omni::string::util::ucwords(str);
}

template < std::size_t X >
inline OMNI_STRING_T_FW ucwords(const OMNI_CHAR_T_FW (&str)[X], const std::string& separators)
{
    return omni::string::util::ucwords(OMNI_STRING_T_FW(str), separators);
}

template < std::size_t X >
inline OMNI_STRING_T_FW ucwords(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::ucwords(OMNI_STRING_T_FW(str), std::string(OMNI_STRING_UCWORD_SEPARATORS));
}

inline OMNI_STRING_T_FW to_title_case(const OMNI_STRING_T_FW& str, const std::string& separators)
{
    return omni::string::util::to_title_case(str, separators);
}

inline OMNI_STRING_T_FW to_title_case(const OMNI_STRING_T_FW& str)
{
    return omni::string::util::to_title_case(str);
}

template < std::size_t X >
inline OMNI_STRING_T_FW to_title_case(const OMNI_CHAR_T_FW (&str)[X], const std::string& separators)
{
    return omni::string::util::to_title_case(OMNI_STRING_T_FW(str), separators);
}

template < std::size_t X >
inline OMNI_STRING_T_FW to_title_case(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::to_title_case(OMNI_STRING_T_FW(str));
}

template < typename T >
inline std::string to_string(const T& val)
{
    return omni::string::util::to_string(val);
}

inline std::string to_string(const std::string& str)
{
    return str;
}

inline std::string to_string(const char* str)
{
    return std::string(str);
}

template < std::size_t X >
inline std::string to_string(const char (&str)[X])
{
    return std::string(str);
}

template < typename T >
inline std::wstring to_wstring(const T& val)
{
    return omni::string::util::to_wstring(val);
}

inline std::wstring to_wstring(const std::wstring& str)
{
    return str;
}

inline std::wstring to_wstring(const wchar_t* str)
{
    return std::wstring(str);
}

template < std::size_t X >
inline std::wstring to_wstring(const wchar_t (&str)[X])
{
    return std::wstring(str);
}

template < typename T >
inline omni::string_t to_string_t(const T& val)
{
    return omni::string::util::to_string_t(val);
}

inline omni::string_t to_string_t(const omni::string_t& val)
{
    return val;
}

inline OMNI_STRING_T_FW trim(OMNI_STRING_T_FW str)
{
    return omni::string::util::trim(str);
}

inline OMNI_STRING_T_FW trim(OMNI_STRING_T_FW str, OMNI_CHAR_T_FW param)
{
    return omni::string::util::trim(str, param);
}

inline OMNI_STRING_T_FW trim(OMNI_STRING_T_FW str, OMNI_STRING_T_FW params)
{
    return omni::string::util::trim(str, params);
}

inline OMNI_STRING_T_FW trim(OMNI_STRING_T_FW str, omni_sequence_t<OMNI_CHAR_T_FW>& params)
{
    return omni::string::util::trim(str, params.begin(), params.end());
}

template < std::size_t X >
inline OMNI_STRING_T_FW trim(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&params)[X])
{
    return omni::string::util::trim(str, OMNI_STRING_T_FW(params));
}

inline OMNI_STRING_T_FW trim_end(OMNI_STRING_T_FW str)
{
    return omni::string::util::trim_end(str);
}

inline OMNI_STRING_T_FW trim_end(OMNI_STRING_T_FW str, OMNI_CHAR_T_FW param)
{
    return omni::string::util::trim_end(str, param);
}

inline OMNI_STRING_T_FW trim_end(OMNI_STRING_T_FW str, OMNI_STRING_T_FW params)
{
    return omni::string::util::trim_end(str, params);
}

inline OMNI_STRING_T_FW trim_end(OMNI_STRING_T_FW str, omni_sequence_t<OMNI_CHAR_T_FW>& params)
{
    return omni::string::util::trim_end(str, params.begin(), params.end());
}

template < std::size_t X >
inline OMNI_STRING_T_FW trim_end(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&params)[X])
{
    return omni::string::util::trim_end(str, OMNI_STRING_T_FW(params));
}

inline OMNI_STRING_T_FW trim_front(OMNI_STRING_T_FW str)
{
    return omni::string::util::trim_front(str);
}

inline OMNI_STRING_T_FW trim_front(OMNI_STRING_T_FW str, OMNI_CHAR_T_FW param)
{
    return omni::string::util::trim_front(str, param);
}

inline OMNI_STRING_T_FW trim_front(OMNI_STRING_T_FW str, OMNI_STRING_T_FW params)
{
    return omni::string::util::trim_front(str, params);
}

inline OMNI_STRING_T_FW trim_front(OMNI_STRING_T_FW str, omni_sequence_t<OMNI_CHAR_T_FW>& params)
{
    return omni::string::util::trim_front(str, params.begin(), params.end());
}

template < std::size_t X >
inline OMNI_STRING_T_FW trim_front(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&params)[X])
{
    return omni::string::util::trim_front(str, OMNI_STRING_T_FW(params));
}

inline OMNI_STRING_T_FW trim_syschars(OMNI_STRING_T_FW str)
{
    return omni::string::util::trim_syschars(str);
}

inline OMNI_STRING_T_FW trim_front_syschars(OMNI_STRING_T_FW str)
{
    return omni::string::util::trim_front_syschars(str);
}

inline OMNI_STRING_T_FW trim_end_syschars(OMNI_STRING_T_FW str)
{
    return omni::string::util::trim_end_syschars(str);
}

template < typename T >
inline OMNI_STRING_T_FW lexical_cast(const T& val)
{
    return omni::string::util::lexical_cast<OMNI_STRING_T_FW>(val);
}

template < typename ret_t >
inline ret_t type_cast(const OMNI_STRING_T_FW& str)
{
    return omni::string::util::to_type<ret_t>(str);
}

template < typename ret_t >
inline ret_t type_cast(const OMNI_CHAR_T_FW* str)
{
    return omni::string::util::to_type<ret_t>(str);
}

template < typename ret_t, std::size_t X >
inline ret_t type_cast(const OMNI_CHAR_T_FW (&str)[X])
{
    return omni::string::util::to_type<ret_t>(OMNI_STRING_T_FW(str));
}

// } namespace omni::string/cstring/wstring
