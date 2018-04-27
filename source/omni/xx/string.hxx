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

// so as not to accidentally build this file with the source
// these macros are defined in string/util.hpp string/cstring.hpp and string/wstring.hpp
#if !defined(OMNI_CHAR_T_FW) || !defined(OMNI_STRING_T_FW)
    #error invalid preprocessor directive detected
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

inline bool contains(const OMNI_STRING_T_FW& chk, const OMNI_STRING_T_FW& fnd, bool ignoreCase)
{
    return omni::string::util::contains(chk, fnd, ignoreCase);
}

inline bool contains(const OMNI_STRING_T_FW& chk, const OMNI_STRING_T_FW& fnd)
{
    return omni::string::util::contains(chk, fnd, false);
}

inline bool is_numeric(const OMNI_STRING_T_FW& str, bool ignorePeriod)
{
    return omni::string::util::is_numeric(str, ignorePeriod);
}

inline bool is_numeric(const OMNI_CHAR_T_FW* str, bool ignorePeriod)
{
    return omni::string::util::is_numeric(str, ignorePeriod);
}

template < std::size_t X >
inline bool is_numeric(const OMNI_CHAR_T_FW (&str)[X], bool ignorePeriod)
{
    return omni::string::util::is_numeric(OMNI_STRING_T_FW(str), ignorePeriod);
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

inline OMNI_STRING_T_FW pad_left(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& pad, std::size_t count)
{
    return omni::string::util::pad_left(str, pad, count);
}

template < std::size_t X >
inline OMNI_STRING_T_FW pad_left(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&pad)[X], std::size_t count)
{
    return omni::string::util::pad_left(str, pad);
}

inline OMNI_STRING_T_FW pad_right(OMNI_STRING_T_FW str, OMNI_CHAR_T_FW pad, std::size_t count)
{
    return omni::string::util::pad_right(str, pad, count);
}

inline OMNI_STRING_T_FW pad_right(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& pad, std::size_t count)
{
    return omni::string::util::pad_right(str, pad, count);
}

template < std::size_t X >
inline OMNI_STRING_T_FW pad_right(OMNI_STRING_T_FW str, const OMNI_CHAR_T_FW (&pad)[X], std::size_t count)
{
    return omni::string::util::pad_right(str, pad);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, std::size_t pos, bool ignoreCase)
{
    return omni::string::util::replace(str, fnd, newstr, pos, ignoreCase);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr)
{
    return omni::string::util::replace(str, fnd, newstr, 0, false);
}

inline OMNI_STRING_T_FW replace(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, bool ignoreCase)
{
    return omni::string::util::replace(str, fnd, newstr, 0, ignoreCase);
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

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, std::size_t pos, bool ignoreCase)
{
    return omni::string::util::replace_all(str, fnd, newstr, pos, ignoreCase);
}

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr)
{
    return omni::string::util::replace_all(str, fnd, newstr, 0, false);
}

inline OMNI_STRING_T_FW replace_all(OMNI_STRING_T_FW str, const OMNI_STRING_T_FW& fnd, const OMNI_STRING_T_FW& newstr, bool ignoreCase)
{
    return omni::string::util::replace_all(str, fnd, newstr, 0, ignoreCase);
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

inline OMNI_STRING_T_FW to_lower(OMNI_STRING_T_FW str)
{
    return omni::string::util::to_lower(str);
}

inline OMNI_STRING_T_FW to_upper(OMNI_STRING_T_FW str)
{
    return omni::string::util::to_upper(str);
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
