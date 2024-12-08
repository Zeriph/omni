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
#if !defined(OMNI_STRING_UTIL_HPP)
#define OMNI_STRING_UTIL_HPP 1
#include <omni/defs/class_macros.hpp>
#include <omni/types/string_t.hpp>
#include <omni/sequence.hpp>
#include <omni/type.hpp>
#include <omni/defs/consts.hpp>
#include <omni/bits.hpp>
#include <bitset>

namespace omni {
    namespace string {
        class compare_options
        {
            public:
                typedef enum enum_t {
                    NONE = 0,
                    IGNORE_CASE = 1,
                    IGNORE_SYMBOLS = 4
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 3;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return NONE;
                }
                
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::string& val, compare_options& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, compare_options& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                compare_options() :
                    OMNI_CTOR_FW(omni::string::compare_options)
                    m_val(DEFAULT_VALUE())
                { }

                compare_options(const compare_options& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                compare_options(enum_t val) : 
                    OMNI_CTOR_FW(omni::string::compare_options)
                    m_val(val)
                { }

                ~compare_options()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                unsigned short count() const
                {
                    return COUNT();
                }

                bool has_flag(enum_t flag) const
                {
                    return (this->m_val & flag) == flag;
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const compare_options& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                compare_options& operator=(const compare_options& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                compare_options& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                compare_options& operator=(int32_t val)
                {
                    if (!compare_options::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const compare_options& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int32_t val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const compare_options& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int32_t val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const compare_options& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int32_t val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::string::compare_options) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::string::compare_options)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    OMNI_ERR_FW("invalid enum parse", omni::exceptions::invalid_enum())
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string_util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, compare_options& out)
                {
                    enum_t tmp;
                    if (_try_parse(val, tmp)) {
                        out.m_val = tmp;
                        return true;
                    }
                    return false;
                }

                static bool _try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(omni::string_util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(NONE)
                        OMNI_S2E_FW(IGNORE_CASE)
                        OMNI_S2E_FW(IGNORE_SYMBOLS)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(IGNORE_CASE);
                        OMNI_E2SS_FW(IGNORE_SYMBOLS);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(NONE) ||
                        OMNI_I2EV_FW(IGNORE_CASE) ||
                        OMNI_I2EV_FW(IGNORE_SYMBOLS)
                    );
                }
        };

        namespace util {
            template < typename std_string_t >
            bool is_numeric(const std_string_t& str, bool ignore_period)
            {
                if (str.empty()) { return false; }
                typename std_string_t::const_iterator itr = str.begin();
                // could be negative/decimal/euro ("-100"/".42"/",42")
                if (omni::char_util::helpers::is_nde(*itr)) {
                    if (++itr == str.end()) { return false; }
                }
                std::size_t pcnt = 0;
                while (itr != str.end()) {
                    if (!omni::char_util::is_digit(*itr)) {
                        if (omni::char_util::helpers::is_de(*itr)) {
                            /* if it is a period or comma and the flag is set then ignore it.
                            The logic here is that we do not want this function to guess
                            how a specific number might be formatted, but that we can assume
                            that if it is indeed a number, chances are good that it might
                            contain a period or comma, so ignore those. */
                            if (ignore_period) { ++itr; continue; }
                            // more than 1 period means non numeric (i.e. not decimal/whole)
                            if (++pcnt > 1) { return false; }
                        }
                        return false;
                    }
                    ++itr;
                }
                return true;
            }
            
            template < typename std_string_t >
            bool is_numeric(const std_string_t& str, typename std_string_t::value_type period_type, bool ignore_period)
            {
                if (str.empty()) { return false; }
                typename std_string_t::const_iterator itr = str.begin();
                // could be negative/decimal/euro ("-100"/".42"/",42")
                if (omni::char_util::helpers::is_neg(*itr)) {
                    if (++itr == str.end()) { return false; }
                }
                std::size_t pcnt = 0;
                while (itr != str.end()) {
                    if (!omni::char_util::is_digit(*itr)) {
                        if (*itr == period_type) {
                            /* if it is a period or comma and the flag is set then ignore it.
                            The logic here is that we do not want this function to guess
                            how a specific number might be formatted, but that we can assume
                            that if it is indeed a number, chances are good that it might
                            contain a period or comma, so ignore those. */
                            if (ignore_period) { ++itr; continue; }
                            // more than 1 period means non numeric (i.e. not decimal/whole)
                            if (++pcnt > 1) { return false; }
                        }
                        return false;
                    }
                    ++itr;
                }
                return true;
            }
            
            inline bool is_numeric(const std::wstring& str)
            {
                return omni::string::util::is_numeric(str, false);
            }
            
            inline bool is_numeric(const std::wstring& str, wchar_t period_type)
            {
                return omni::string::util::is_numeric(str, period_type, false);
            }
            
            inline bool is_numeric(const wchar_t* str)
            {
                if (str) { return omni::string::util::is_numeric(std::wstring(str)); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }

            template < std::size_t X >
            inline bool is_numeric(const wchar_t (&str)[X])
            {
                return omni::string::util::is_numeric(std::wstring(str));
            }
            
            inline bool is_numeric(const wchar_t* str, bool ignore_period)
            {
                if (str) { return omni::string::util::is_numeric(std::wstring(str), ignore_period); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const wchar_t (&str)[X], bool ignore_period)
            {
                return omni::string::util::is_numeric(std::wstring(str), ignore_period);
            }
            
            inline bool is_numeric(const wchar_t* str, wchar_t period_type)
            {
                if (str) { return omni::string::util::is_numeric(std::wstring(str), period_type, false); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const wchar_t (&str)[X], wchar_t period_type)
            {
                return omni::string::util::is_numeric(std::wstring(str), period_type, false);
            }
            
            inline bool is_numeric(const wchar_t* str, wchar_t period_type, bool ignore_period)
            {
                if (str) { return omni::string::util::is_numeric(std::wstring(str), period_type, ignore_period); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const wchar_t (&str)[X], wchar_t period_type, bool ignore_period)
            {
                return omni::string::util::is_numeric(std::wstring(str), period_type, ignore_period);
            }
            
            inline bool is_numeric(const std::string& str)
            {
                return omni::string::util::is_numeric(str, false);
            }
            
            inline bool is_numeric(const std::string& str, char period_type)
            {
                return omni::string::util::is_numeric(str, period_type, false);
            }
            
            inline bool is_numeric(const char* str)
            {
                if (str) { return omni::string::util::is_numeric(std::string(str)); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const char (&str)[X])
            {
                return omni::string::util::is_numeric(std::string(str));
            }
            
            inline bool is_numeric(const char* str, bool ignore_period)
            {
                if (str) { return omni::string::util::is_numeric(std::string(str), ignore_period); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const char (&str)[X], bool ignore_period)
            {
                return omni::string::util::is_numeric(std::string(str), ignore_period);
            }
            
            inline bool is_numeric(const char* str, char period_type)
            {
                if (str) { return omni::string::util::is_numeric(std::string(str), period_type, false); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const char (&str)[X], char period_type)
            {
                return omni::string::util::is_numeric(std::string(str), period_type, false);
            }
            
            inline bool is_numeric(const char* str, char period_type, bool ignore_period)
            {
                if (str) { return omni::string::util::is_numeric(std::string(str), period_type, ignore_period); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), false)
            }
            
            template < std::size_t X >
            inline bool is_numeric(const char (&str)[X], char period_type, bool ignore_period)
            {
                return omni::string::util::is_numeric(std::string(str), period_type, ignore_period);
            }
            
            template < typename std_string_t >
            std_string_t to_lower(std_string_t str)
            {
                typename std_string_t::iterator it = str.begin();
                while (it != str.end()) {
                    *it = omni::char_util::to_lower(*it);
                    ++it;
                }
                return str;
            }
            
            template < std::size_t X >
            std::string to_lower(const char (&str)[X])
            {
                return omni::string::util::to_lower(std::string(str));
            }
            
            template < std::size_t X >
            std::wstring to_lower(const wchar_t (&str)[X])
            {
                return omni::string::util::to_lower(std::wstring(str));
            }

            template < typename std_string_t >
            std_string_t lcfirst(std_string_t str)
            {
                if (str.size() > 0) {
                    str[0] = omni::char_util::to_lower(str[0]);
                }
                return str;
            }
            
            template < std::size_t X >
            std::string lcfirst(const char (&str)[X])
            {
                return omni::string::util::lcfirst(std::string(str));
            }
            
            template < std::size_t X >
            std::wstring lcfirst(const wchar_t (&str)[X])
            {
                return omni::string::util::lcfirst(std::wstring(str));
            }
            
            template < typename std_string_t >
            std_string_t to_upper(std_string_t str)
            {
                typename std_string_t::iterator it = str.begin();
                while (it != str.end()) {
                    *it = omni::char_util::to_upper(*it);
                    ++it;
                }
                return str;
            }
            
            template < std::size_t X >
            std::string to_upper(const char (&str)[X])
            {
                return omni::string::util::to_upper(std::string(str));
            }
            
            template < std::size_t X >
            std::wstring to_upper(const wchar_t (&str)[X])
            {
                return omni::string::util::to_upper(std::wstring(str));
            }

            template < typename std_string_t >
            std_string_t ucfirst(std_string_t str)
            {
                if (str.size() > 0) {
                    str[0] = omni::char_util::to_upper(str[0]);
                }
                return str;
            }
            
            template < std::size_t X >
            std::string ucfirst(const char (&str)[X])
            {
                return omni::string::util::ucfirst(std::string(str));
            }
            
            template < std::size_t X >
            std::wstring ucfirst(const wchar_t (&str)[X])
            {
                return omni::string::util::ucfirst(std::wstring(str));
            }

            template < typename std_string_t >
            std_string_t ucwords(std_string_t str, const std::string& separators)
            {
                if (str.size() > 0) {
                    typename std_string_t::size_type pos = 0;
                    str[0] = omni::char_util::to_upper(str[0]);

                    std::string::const_iterator s_it = separators.begin();
                    while (s_it != separators.end()) {
                        while ((pos = str.find(*s_it, pos)) != std_string_t::npos) {
                            if ((++pos) < str.size()) {
                                str[pos] = omni::char_util::to_upper(str[pos]);
                            }
                        }
                        pos = 0;
                        ++s_it;
                    }
                }
                return str;
            }

            template < typename std_string_t >
            std_string_t ucwords(const std_string_t& str)
            {
                return omni::string::util::ucwords(str, std::string(OMNI_STRING_UCWORD_SEPARATORS));
            }
            
            template < std::size_t X >
            std::string ucwords(const char (&str)[X], const std::string& separators)
            {
                return omni::string::util::ucwords(std::string(str), separators);
            }
            
            template < std::size_t X >
            std::wstring ucwords(const wchar_t (&str)[X], const std::string& separators)
            {
                return omni::string::util::ucwords(std::wstring(str), separators);
            }

            template < std::size_t X >
            std::string ucwords(const char (&str)[X])
            {
                return omni::string::util::ucwords(std::string(str), std::string(OMNI_STRING_UCWORD_SEPARATORS));
            }
            
            template < std::size_t X >
            std::wstring ucwords(const wchar_t (&str)[X])
            {
                return omni::string::util::ucwords(std::wstring(str), std::string(OMNI_STRING_UCWORD_SEPARATORS));
            }

            template < typename std_string_t >
            std_string_t to_title_case(const std_string_t& str, const std::string& separators)
            {
                return omni::string::util::ucwords(omni::string::util::to_lower(str), separators);
            }

            template < typename std_string_t >
            std_string_t to_title_case(const std_string_t& str)
            {
                return omni::string::util::to_title_case(str, std::string(OMNI_STRING_UCWORD_SEPARATORS));
            }
            
            template < std::size_t X >
            std::string to_title_case(const char (&str)[X], const std::string& separators)
            {
                return omni::string::util::to_title_case(std::string(str), separators);
            }
            
            template < std::size_t X >
            std::wstring to_title_case(const wchar_t (&str)[X], const std::string& separators)
            {
                return omni::string::util::to_title_case(std::wstring(str), separators);
            }

            template < std::size_t X >
            std::string to_title_case(const char (&str)[X])
            {
                return omni::string::util::to_title_case(std::string(str), std::string(OMNI_STRING_UCWORD_SEPARATORS));
            }
            
            template < std::size_t X >
            std::wstring to_title_case(const wchar_t (&str)[X])
            {
                return omni::string::util::to_title_case(std::wstring(str), std::string(OMNI_STRING_UCWORD_SEPARATORS));
            }

            template < typename std_string_t >
            bool contains(const std_string_t& haystack, const std_string_t& needle, bool ignore_case)
            {
                if (haystack.length() >= needle.length()) {
                    if (ignore_case) {
                        std_string_t tmp = omni::string::util::to_lower(haystack);
                        std_string_t tf = omni::string::util::to_lower(needle);
                        return (tmp.find(tf) != std_string_t::npos);
                    }
                    return (haystack.find(needle) != std_string_t::npos);
                }
                return false;
            }
            
            template < typename std_string_t, std::size_t X >
            bool contains(const std_string_t& haystack, const typename std_string_t::value_type (&needle)[X], bool ignore_case)
            {
                return omni::string::util::contains(haystack, std_string_t(needle), ignore_case);
            }
            
            template < typename std_string_t >
            inline bool contains(const std_string_t& haystack, const std_string_t& needle)
            {
                if (haystack.length() >= needle.length()) {
                    return (haystack.find(needle) != std_string_t::npos);
                }
                return false;
            }
            
            template < typename std_string_t, std::size_t X >
            inline bool contains(const std_string_t& haystack, const typename std_string_t::value_type (&needle)[X])
            {
                return omni::string::util::contains(haystack, std_string_t(needle));
            }

            template < typename std_string_t >
            inline int32_t compare(const std_string_t& str1, std::size_t idx1, const std_string_t& str2, std::size_t idx2, std::size_t len, const omni::string::compare_options& options)
            {
                /*
                    Remarks
                    The substrings to compare start in strA at position indexA and in strB at position indexB. The length of the first substring is the
                    length of strA minus indexA. The length of the second substring is the length of strB minus indexB.

                    The number of characters to compare is the lesser of the lengths of the two substrings, and length. The indexA, indexB, and length
                    parameters must be nonnegative.

                    The comparison uses the culture parameter to obtain culture-specific information, such as casing rules and the alphabetical order of
                    individual characters. For example, a particular culture could specify that certain combinations of characters be treated as a single
                    character, that uppercase and lowercase characters be compared in a particular way, or that the sort order of a character depends on
                    the characters that precede or follow it.

                    Caution

                    The Compare(String, Int32, String, Int32, Int32, CultureInfo, CompareOptions) method is designed primarily for use in sorting or
                    alphabetizing operations. It should not be used when the primary purpose of the method call is to determine whether two substrings
                    are equivalent (that is, when the purpose of the method call is to test for a return value of zero). To determine whether two strings
                    are equivalent, call the Equals method.

                */
                if (idx1 > str1.size()) {
                    OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), 0)
                }
                if (idx2 > str2.size()) {
                    OMNI_ERR_RETV_FW("Index out of range", omni::exceptions::index_out_of_range(), 0)
                }
                if (str1.empty()) {
                    return str2.empty() ? 0 : -1;
                } else if (str2.empty()) {
                    return 1;
                }

                bool ignore_case = options.has_flag(omni::string::compare_options::IGNORE_CASE);
                bool ignore_symbols = options.has_flag(omni::string::compare_options::IGNORE_SYMBOLS);

                std_string_t a = (ignore_case ? omni::string::util::to_lower(str1) : str1).substr(idx1);
                std_string_t b = (ignore_case ? omni::string::util::to_lower(str2) : str2).substr(idx2);
                
                // The number of characters to compare is the lesser of the lengths of the two substrings, and length.
                std::size_t comp_size = std::min(std::min(a.size(), b.size()), len);
                for (std::size_t i = 0; i < comp_size; ++i) {
                    if (ignore_symbols && (!omni::char_util::is_alpha_digit(a[i]) || !omni::char_util::is_alpha_digit(b[i]))) {
                        continue;
                    }
                    if (a[i] < b[i]) {
                        return -1;
                    } else if (a[i] > b[i]) {
                        return 1;
                    }
                }

                return 0;
                /*
                    Value 	Condition
                    Less than zero 	The substring in strA precedes the substring in strB in the sort order.
                    Zero 	The substrings occur in the same position in the sort order, or length is zero.
                    Greater than zero 	The substring in strA follows the substring in strB in the sort order. 
                */
            }
            
            template < typename std_string_t >
            inline int32_t compare(const std_string_t& str1, std::size_t idx1, std::size_t len1, const std_string_t& str2, std::size_t idx2, std::size_t len2, const omni::string::compare_options& options)
            {
                // Verify inputs
                if (idx1 > (str1.size() - len1)) {
                    OMNI_ERR_RETV_FW("offset1 greater than length", omni::exceptions::index_out_of_range("offset1 greater than length"), 0)
                }
                if (idx2 > (str2.size()- len2)) {
                    OMNI_ERR_RETV_FW("offset2 greater than length", omni::exceptions::index_out_of_range("offset2 greater than length"), 0)
                }

                // Check for the null case.
                if (str1.empty()) {
                    return str2.empty() ? 0 : -1;
                } else if (str2.empty()) {
                    return 1;
                }

                bool ignore_case = options.has_flag(omni::string::compare_options::IGNORE_CASE);
                bool ignore_symbols = options.has_flag(omni::string::compare_options::IGNORE_SYMBOLS);

                std_string_t a = (ignore_case ? omni::string::util::to_lower(str1) : str1).substr(idx1, len1);
                std_string_t b = (ignore_case ? omni::string::util::to_lower(str2) : str2).substr(idx2, len2);
                
                // The number of characters to compare is the lesser of the lengths of the two substrings, and length.
                std::size_t comp_size = std::min(a.size(), b.size());
                for (std::size_t i = 0; i < comp_size; ++i) {
                    if (ignore_symbols && (!omni::char_util::is_alpha_digit(a[i]) || !omni::char_util::is_alpha_digit(b[i]))) {
                        continue;
                    }
                    if (a[i] < b[i]) {
                        return -1;
                    } else if (a[i] > b[i]) {
                        return 1;
                    }
                }

                return 0;
                /*
                    Value 	Condition
                    Less than zero 	The substring in strA precedes the substring in strB in the sort order.
                    Zero 	The substrings occur in the same position in the sort order, or length is zero.
                    Greater than zero 	The substring in strA follows the substring in strB in the sort order. 
                */
            }

            template < typename std_string_t >
            bool ends_with(const std_string_t& haystack, const std_string_t& needle, bool ignore_case)
            {
                if (haystack.length() >= needle.length()) {
                    if (ignore_case) {
                        std_string_t tmp = omni::string::util::to_lower(haystack);
                        std_string_t tf = omni::string::util::to_lower(needle);
                        return (tmp.compare(tmp.length() - tf.length(), tf.length(), tf) == 0);
                    }
                    return (haystack.compare(haystack.length() - needle.length(), needle.length(), needle) == 0);
                }
                return false;
            }
            
            template < typename std_string_t, std::size_t X >
            bool ends_with(const std_string_t& haystack, const typename std_string_t::value_type (&needle)[X], bool ignore_case)
            {
                return omni::string::util::ends_with(haystack, std_string_t(needle), ignore_case);
            }
            
            template < typename std_string_t >
            inline bool ends_with(const std_string_t& haystack, const std_string_t& needle)
            {
                if (haystack.length() >= needle.length()) {
                    return (haystack.compare(haystack.length() - needle.length(), needle.length(), needle) == 0);
                }
                return false;
            }
            
            template < typename std_string_t, std::size_t X >
            inline bool ends_with(const std_string_t& haystack, const typename std_string_t::value_type (&needle)[X])
            {
                return omni::string::util::ends_with(haystack, std_string_t(needle));
            }
            
            template < typename std_string_t, typename T >
            std_string_t lexical_cast(const T& val)
            {
                return omni::string_util::omni_internal<std_string_t>::lexical_cast(val);
            }
            
            template < typename std_string_t >
            std_string_t pad_left(std_string_t str, typename std_string_t::value_type pad, std::size_t count)
            {
                if ((count == 0) || (static_cast<int64_t>(count - str.size()) <= 0)) { return str; }
                return str.insert(0, count - str.size(), pad);
            }

            template < typename std_string_t >
            std_string_t pad_left_full(const std_string_t& str, const std_string_t& pad, std::size_t count)
            {
                if (count == 0) { return str; }
                std_string_t ret(pad);
                while (count > 1) {
                    ret.append(pad);
                    --count;
                }
                return ret + str;
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t pad_left_full(std_string_t str, const typename std_string_t::value_type (&pad)[X], std::size_t count)
            {
                return omni::string::util::pad_left_full(str, std_string_t(pad), count);
            }

            template < typename std_string_t >
            std_string_t pad_right(std_string_t str, typename std_string_t::value_type pad, std::size_t count)
            {
                if ((count == 0) || (static_cast<int64_t>(count - str.size()) <= 0)) { return str; }
                return str.append(count - str.size(), pad);
            }

            template < typename std_string_t >
            std_string_t pad_right_full(std_string_t str, const std_string_t& pad, std::size_t count)
            {
                while (count > 0) {
                    str.append(pad);
                    --count;
                }
                return str;
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t pad_right_full(std_string_t str, const typename std_string_t::value_type (&pad)[X], std::size_t count)
            {
                return omni::string::util::pad_right_full(str, std_string_t(pad), count);
            }

            template < typename std_string_t >
            std_string_t replace(std_string_t str, const std_string_t& fnd, const std_string_t& newstr, std::size_t pos, bool ignore_case)
            {
                if (str.empty()) { return str; }
                if (fnd.empty()) { return str; }
                if (pos > str.size()) {
                    OMNI_ERR_RETV_FW("Position cannot be greater than string length", omni::exceptions::invalid_size(), str)
                }
                std::size_t spos = std_string_t::npos;
                if (ignore_case) {
                    spos = (omni::string::util::to_lower(str)).find(omni::string::util::to_lower(fnd), pos);
                } else {
                    spos = str.find(fnd, pos);
                }
                if (spos != std_string_t::npos) {
                    str.replace(spos, fnd.length(), newstr);
                }
                return str;
            }
            
            template < typename std_string_t, std::size_t X, std::size_t Y >
            std_string_t replace(std_string_t str, const typename std_string_t::value_type (&fnd)[X], const typename std_string_t::value_type (&newstr)[Y], std::size_t pos, bool ignore_case)
            {
                return omni::string::util::replace(str, std_string_t(fnd), std_string_t(newstr), pos, ignore_case);
            }

            template < typename std_string_t >
            std_string_t replace_all(std_string_t str, const std_string_t& fnd, const std_string_t& newstr, std::size_t pos, bool ignore_case)
            {
                if (str.empty()) { return str; }
                if (fnd.empty()) { return str; }
                if (pos > str.size()) {
                    OMNI_ERR_RETV_FW("Position cannot be greater than string length", omni::exceptions::invalid_size(), str)
                }
                std::size_t nsz = newstr.size();
                std::size_t fsz = fnd.size();
                std::size_t spos = std_string_t::npos;
                if (ignore_case) {
                    std_string_t lstr = omni::string::util::to_lower(str);
                    std_string_t lfnd = omni::string::util::to_lower(fnd);
                    spos = lstr.find(lfnd, pos);
                    while (spos != std_string_t::npos) {
                        str.replace(spos, fsz, newstr);
                        lstr.replace(spos, fsz, newstr);
                        spos = lstr.find(lfnd, spos + nsz);
                    }
                } else {
                    spos = str.find(fnd, pos);
                    while (spos != std_string_t::npos) {
                        str.replace(spos, fsz, newstr);
                        spos = str.find(fnd, spos + nsz);
                    }
                }
                return str;
            }
            
            template < typename std_string_t, std::size_t X, std::size_t Y >
            std_string_t replace_all(const std_string_t& str, const typename std_string_t::value_type (&fnd)[X], const typename std_string_t::value_type (&newstr)[Y], std::size_t pos, bool ignore_case)
            {
                return omni::string::util::replace_all(str, std_string_t(fnd), std_string_t(newstr), pos, ignore_case);
            }

            template < typename std_string_t >
            std_string_t reverse(std_string_t str)
            {
                std::reverse(str.begin(), str.end());
                return str;
            }
            
            template < std::size_t X >
            inline std::wstring reverse(const wchar_t (&str)[X])
            {
                return omni::string::util::reverse(std::wstring(str));
            }
            
            template < std::size_t X >
            inline std::string reverse(const char (&str)[X])
            {
                return omni::string::util::reverse(std::string(str));
            }
            
            template < template < class, class > class std_seq_t, class std_string_t, class std_allocator_t >
            std_seq_t<std_string_t, std_allocator_t> split(std_string_t str, const std_string_t& delimeter, std::size_t max_val)
            {
                std_seq_t<std_string_t, std_allocator_t> ret;
                if (str.empty()) { return ret; }
                if (max_val == 1) { // If max is 1, then they only want 1 substring, which means the string they sent in
                    ret.push_back(str);
                    return ret;
                }
                if (delimeter.empty()) {
                    typename std_string_t::const_iterator citr = str.begin();
                    while (citr != str.end()) {
                        ret.push_back(std_string_t(citr, ++citr));
                        if ((max_val > 0) && (--max_val)) {
                            ret.push_back(std_string_t(citr, ++citr));
                            break;
                        }
                    }
                    if (citr != str.end()) {
                        typename std_string_t::const_iterator eitr = str.end();
                        ret.push_back(std_string_t(citr, eitr));
                    }
                } else {
                    std::size_t f = str.find(delimeter);
                    while (f != std::string::npos) {
                        ret.push_back(str.substr(0, f));
                        str.erase(0, f+delimeter.size());
                        f = str.find(delimeter);
                        if ((max_val > 0) && (--max_val)) {
                            break;
                        }
                    }
                    ret.push_back(str);
                }
                return ret;
            }
            
            template < template < class, class > class std_seq_t, class std_string_t >
            inline std_seq_t<std_string_t, std::allocator<std_string_t> > split(const std_string_t& str, const std_string_t& delimeter, std::size_t max_val)
            {
                return omni::string::util::split< std_seq_t, std_string_t, std::allocator<std_string_t> >(str, delimeter, max_val);
            }
            
            template < typename std_string_t >
            inline omni_sequence_t<std_string_t> split(const std_string_t& str, const std_string_t& delimeter, std::size_t max_val)
            {
                return omni::string::util::split< omni_sequence_t, std_string_t >(str, delimeter, max_val);
            }
            
            template < typename std_string_t >
            inline omni_sequence_t<std_string_t> split(const std_string_t& str, const std_string_t& delimeter)
            {
                return omni::string::util::split(str, delimeter, 0); 
            }

            template < typename std_string_t, std::size_t X >
            inline omni_sequence_t<std::string> split(const std_string_t& str, const typename std_string_t::value_type (&delimeter)[X])
            {
                return omni::string::util::split(str, std_string_t(delimeter), 0); 
            }
            
            template < std::size_t X, std::size_t Y >
            inline omni_sequence_t<std::string> split(const char (&str)[X], const char (&delimeter)[Y], std::size_t max_val)
            {
                return omni::string::util::split(std::string(str), std::string(delimeter), max_val); 
            }
            
            template < std::size_t X, std::size_t Y >
            inline omni_sequence_t<std::string> split(const char (&str)[X], const char (&delimeter)[Y])
            {
                return omni::string::util::split(std::string(str), std::string(delimeter), 0); 
            }
            
            template < std::size_t X, std::size_t Y >
            inline omni_sequence_t<std::wstring> split(const wchar_t (&str)[X], const wchar_t (&delimeter)[Y], std::size_t max_val)
            {
                return omni::string::util::split(std::wstring(str), std::wstring(delimeter), max_val);
            }
            
            template < std::size_t X, std::size_t Y >
            inline omni_sequence_t<std::wstring> split(const wchar_t (&str)[X], const wchar_t (&delimeter)[Y])
            {
                return omni::string::util::split(std::wstring(str), std::wstring(delimeter), 0); 
            }
            
            inline omni_sequence_t<std::string> split(const char* str, const char* delimeter, std::size_t max_val)
            {
                return omni::string::util::split< omni_sequence_t >(std::string(str), std::string(delimeter), max_val); 
            }
            
            inline omni_sequence_t<std::string> split(const char* str, const char* delimeter)
            {
                return omni::string::util::split< omni_sequence_t >(std::string(str), std::string(delimeter), 0); 
            }
            
            inline omni_sequence_t<std::wstring> split(const wchar_t* str, const wchar_t* delimeter, std::size_t max_val)
            {
                return omni::string::util::split< omni_sequence_t >(std::wstring(str), std::wstring(delimeter), max_val);
            }
            
            inline omni_sequence_t<std::wstring> split(const wchar_t* str, const wchar_t* delimeter)
            {
                return omni::string::util::split< omni_sequence_t >(std::wstring(str), std::wstring(delimeter), 0); 
            }

            template < typename std_string_t >
            bool starts_with(const std_string_t& haystack, const std_string_t& needle, bool ignore_case)
            {
                if (haystack.length() >= needle.length()) {
                    if (ignore_case) {
                        std_string_t tmp = omni::string::util::to_lower(haystack);
                        std_string_t tf = omni::string::util::to_lower(needle);
                        return (tmp.find(tf) == 0);
                    }
                    return (haystack.find(needle) == 0);
                }
                return false;
            }
            
            template < typename std_string_t, std::size_t X >
            bool starts_with(const std_string_t& haystack, const typename std_string_t::value_type (&needle)[X], bool ignore_case)
            {
                return omni::string::util::starts_with(haystack, std_string_t(needle), ignore_case);
            }
            
            template < typename std_string_t >
            inline bool starts_with(const std_string_t& haystack, const std_string_t& needle)
            {
                if (haystack.length() >= needle.length()) {
                    return (haystack.find(needle) == 0);
                }
                return false;
            }
            
            template < typename std_string_t, std::size_t X >
            inline bool starts_with(const std_string_t& haystack, const typename std_string_t::value_type (&needle)[X])
            {
                return omni::string::util::starts_with(haystack, std_string_t(needle));
            }
            
            template < typename T >
            inline std::string to_string(const T& val)
            {
                return omni::string_util::to_string(val);
            }
            
            template < std::size_t X >
            inline std::string to_string(const wchar_t (&str)[X])
            {
                return omni::string_util::to_string(std::wstring(str));
            }
            
            template < std::size_t X >
            inline std::string to_string(const char (&str)[X])
            {
                return std::string(str);
            }
            
            template < typename T >
            inline std::wstring to_wstring(const T& val)
            {
                return omni::string_util::to_wstring(val);
            }
            
            template < std::size_t X >
            inline std::wstring to_wstring(const wchar_t (&str)[X])
            {
                return std::wstring(str);
            }
            
            template < std::size_t X >
            inline std::wstring to_wstring(const char (&str)[X])
            {
                return omni::string_util::to_wstring(std::string(str));
            }
            
            template < typename T >
            inline omni::string_t to_string_t(const T& val)
            {
                return omni::string_util::to_string_t(val);
            }
            
            template < std::size_t X >
            inline omni::string_t to_string_t(const wchar_t (&str)[X])
            {
                return omni::string_util::to_string_t(std::wstring(str));
            }
            
            template < std::size_t X >
            inline omni::string_t to_string_t(const char (&str)[X])
            {
                return omni::string_util::to_string_t(std::string(str));
            }
            
            template < typename T >
            inline T to_type(const std::string& str)
            {
                if (str.empty()) { return T(); }
                T ret;                
                std::stringstream in(str);
                in >> ret;
                return ret;
            }
            
            template <>
            inline bool to_type<bool>(const std::string& str)
            {
                if (!str.empty()) {
                    std::string tmp(str);
                    std::size_t pos = tmp.find_first_not_of("\t \n\r\0");
                    if ((pos != std::string::npos) && (pos > 0)) {
                        tmp = tmp.substr(pos);
                    }
                    pos = tmp.find_last_not_of("\t \n\r\0");
                    if (pos != std::string::npos) {
                        tmp.erase(pos + 1);
                    } else {
                        tmp.clear();
                    }
                    std::size_t sz = tmp.size();
                    if (sz > 0) {
                        if (tmp.find_first_of("tTfF") == 0) {
                            // T/F or true/false??
                            switch (sz) {
                                case 1: {
                                    switch (tmp[0]) {
                                        case 't': case 'T': return true;
                                        case 'f': case 'F': return false;
                                    }
                                } break;
                                case 4: {
                                    if ((tmp[0] == 't' || tmp[0] == 'T') &&
                                        (tmp[1] == 'r' || tmp[1] == 'R') &&
                                        (tmp[2] == 'u' || tmp[2] == 'U') &&
                                        (tmp[3] == 'e' || tmp[3] == 'E'))
                                    {
                                        return true;
                                    }
                                } break;
                                case 5: {
                                    if ((tmp[0] == 'f' || tmp[0] == 'F') &&
                                        (tmp[1] == 'a' || tmp[1] == 'A') &&
                                        (tmp[2] == 'l' || tmp[2] == 'L') &&
                                        (tmp[3] == 's' || tmp[3] == 'S') &&
                                        (tmp[4] == 'e' || tmp[4] == 'E'))
                                    {
                                        return false;
                                    }
                                } break;
                            }
                            // it's not a true/false string, so fall through
                        }
                    }
                }
                OMNI_ERR_RETV_FW("Invalid boolean string specified", omni::exceptions::invalid_parse("Invalid boolean string specified"), false)
            }
            
            template < typename T >
            inline T to_type(const char* str)
            {
                if (str) { return omni::string::util::to_type<T>(std::string(str)); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), T())
            }
            
            template < typename T >
            inline T to_type(const std::wstring& str)
            {
                if (str.empty()) { return T(); }
                T ret;
                std::wstringstream in(str);
                in >> ret;
                return ret;
            }
            
            template <>
            inline bool to_type<bool>(const std::wstring& str)
            {
                if (!str.empty()) {
                    std::wstring tmp(str);
                    std::size_t pos = tmp.find_first_not_of(L"\t \n\r\0");
                    if ((pos != std::wstring::npos) && (pos > 0)) {
                        tmp = tmp.substr(pos);
                    }
                    pos = tmp.find_last_not_of(L"\t \n\r\0");
                    if (pos != std::wstring::npos) {
                        tmp.erase(pos + 1);
                    } else {
                        tmp.clear();
                    }
                    std::size_t sz = tmp.size();
                    if (sz > 0) {
                        if (tmp.find_first_of(L"tTfF") == 0) {
                            // T/F or true/false??
                            switch (sz) {
                                case 1: {
                                    switch (tmp[0]) {
                                        case L't': case L'T': return true;
                                        case L'f': case L'F': return false;
                                    }
                                } break;
                                case 4: {
                                    if ((tmp[0] == L't' || tmp[0] == L'T') &&
                                        (tmp[1] == L'r' || tmp[1] == L'R') &&
                                        (tmp[2] == L'u' || tmp[2] == L'U') &&
                                        (tmp[3] == L'e' || tmp[3] == L'E'))
                                    {
                                        return true;
                                    }
                                } break;
                                case 5: {
                                    if ((tmp[0] == L'f' || tmp[0] == L'F') &&
                                        (tmp[1] == L'a' || tmp[1] == L'A') &&
                                        (tmp[2] == L'l' || tmp[2] == L'L') &&
                                        (tmp[3] == L's' || tmp[3] == L'S') &&
                                        (tmp[4] == L'e' || tmp[4] == L'E'))
                                    {
                                        return false;
                                    }
                                } break;
                            }
                            // it's not a true/false string, so fall through
                        }
                    }
                }
                OMNI_ERR_RETV_FW("Invalid boolean string specified", omni::exceptions::invalid_parse("Invalid boolean string specified"), false)
            }
            
            template < typename T >
            inline T to_type(const wchar_t* str)
            {
                if (str) { return omni::string::util::to_type<T>(std::wstring(str)); }
                OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), T())
            }

            template < typename T >
            inline T to_type(const std::string& str, uint8_t base)
            {
                if (base == 10) {
                    return omni::string::util::to_type<T>(str);
                }
                return static_cast<T>(std::strtoul(str.c_str(), 0, base));
            }

            template <>
            inline bool to_type<bool>(const std::string& str, uint8_t base)
            {
                OMNI_UNUSED(base);
                return omni::string::util::to_type<bool>(str);
            }

            template < typename T >
            inline T to_type(const char* str, uint8_t base)
            {
                if (!str) { OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), T()) }
                return omni::string::util::to_type<T>(std::string(str), base);
            }

            template < typename T >
            inline T to_type(const std::wstring& str, uint8_t base)
            {
                if (base == 10) {
                    return omni::string::util::to_type<T>(str);
                }
                return static_cast<T>(std::strtoul(omni::string::util::to_string(str).c_str(), 0, base));
            }

            template <>
            inline bool to_type<bool>(const std::wstring& str, uint8_t base)
            {
                OMNI_UNUSED(base);
                return omni::string::util::to_type<bool>(str);
            }

            template < typename T >
            inline T to_type(const wchar_t* str, uint8_t base)
            {
                if (!str) { OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), T()) }
                if (base == 10) {
                    return omni::string::util::to_type<T>(std::wstring(str));
                }
                return static_cast<T>(std::strtoul(omni::string::util::to_string(str).c_str(), 0, base));
            }
                        
            template < typename std_string_t >
            std_string_t trim_front_syschars(std_string_t str)
            {
                if (str.empty()) { return str; }
                std::size_t end = std_string_t::npos;
                for (std::size_t i = 0; i < str.length(); ++i) {
                    end = i;
                    if (static_cast<std::size_t>(str[i]) > 31) { break; }
                    ++end;
                }
                if (end > 0) { // if end == 0, that is the whole string, so only return if >0
                    if (end == str.length()) { // if end == len, there is nothing left, return empty
                        return std_string_t();
                    }
                    return str.substr(end);
                }
                return str;
            }
            
            template < typename std_string_t >
            std_string_t trim_front(std_string_t str, std_string_t params)
            {
                if (str.empty() || params.empty()) { return str; }
                std::size_t pos = str.find_first_not_of(params);
                if ((pos != std_string_t::npos) && (pos > 0)) {
                    return str.substr(pos);
                }
                return str;
            }
            
            template < typename std_string_t >
            std_string_t trim_front(std_string_t str)
            {
                return omni::string::util::trim_front(
                            omni::string::util::trim_front_syschars(str),
                            omni::string::util::lexical_cast<std_string_t>("\t \n\r\0")
                       );
            }
            
            template < typename std_string_t >
            std_string_t trim_front(std_string_t str, const typename std_string_t::value_type param)
            {
                std_string_t params(1, param);
                return omni::string::util::trim_front(str, params);
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t trim_front(std_string_t str, const typename std_string_t::value_type (&params)[X])
            {
                return omni::string::util::trim_front(str, std_string_t(params));
            }
            
            template < typename std_string_t, typename iterator_t >
            std_string_t trim_front(std_string_t str, iterator_t begin, iterator_t end)
            {
                std_string_t params(begin, end);
                return omni::string::util::trim_front(str, params);
            }
            
            template < typename std_string_t >
            std_string_t trim_end_syschars(std_string_t str)
            {
                if (str.empty()) { return str; }
                std::size_t end = str.length();
                for (std::size_t i = end; i > 0; --i, --end) {
                    if (static_cast<std::size_t>(str[i]) > 31) { break; }
                }
                if (++end < str.length()) { return str.substr(0, end); }
                return str;
            }
            
            template < typename std_string_t >
            std_string_t trim_end(std_string_t str, std_string_t params)
            {
                if (str.empty() || params.empty()) { return str; }
                std::size_t pos = str.find_last_not_of(params);
                if (pos != std_string_t::npos) {
                    str.erase(pos + 1);
                } else {
                    str.clear();
                }
                return str;
            }
            
            template < typename std_string_t >
            std_string_t trim_end(std_string_t str)
            {
                return omni::string::util::trim_end(
                            omni::string::util::trim_end_syschars(str),
                            omni::string::util::lexical_cast<std_string_t>("\t \n\r\0")
                       );
            }
            
            template < typename std_string_t >
            std_string_t trim_end(std_string_t str, const typename std_string_t::value_type param)
            {
                std_string_t params(1, param);
                return omni::string::util::trim_end(str, params);
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t trim_end(std_string_t str, const typename std_string_t::value_type (&params)[X])
            {
                return omni::string::util::trim_end(str, std_string_t(params));
            }
            
            template < typename std_string_t, typename iterator_t >
            std_string_t trim_end(std_string_t str, iterator_t begin, iterator_t end)
            {
                std_string_t params(begin, end);
                return omni::string::util::trim_end(str, params);
            }
            
            template < typename std_string_t >
            std_string_t trim(std_string_t str, std_string_t params)
            {
                if (str.empty()) { return str; }
                str = omni::string::util::trim_front(str, params);
                return omni::string::util::trim_end(str, params);
            }
            
            template < typename std_string_t >
            std_string_t trim_syschars(std_string_t str)
            {
                str = omni::string::util::trim_front_syschars(str);
                return omni::string::util::trim_end_syschars(str);
            }
            
            template < typename std_string_t >
            std_string_t trim(std_string_t str)
            {
                if (str.empty()) { return str; }
                // Trim Both leading and trailing spaces
                str = omni::string::util::trim_front(str);
                return omni::string::util::trim_end(str);
            }
            
            template < typename std_string_t >
            std_string_t trim(std_string_t str, const typename std_string_t::value_type param)
            {
                std_string_t params(1, param);
                return omni::string::util::trim(str, params);
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t trim(std_string_t str, const typename std_string_t::value_type (&params)[X])
            {
                return omni::string::util::trim(str, std_string_t(params));
            }
            
            template < typename std_string_t, typename iterator_t >
            std_string_t trim(std_string_t str, iterator_t begin, iterator_t end)
            {
                std_string_t params(begin, end);
                return omni::string::util::trim(str, params);
            }
            
            namespace binary {
                template < typename std_string_t >
                bool is_valid(const std_string_t& str)
                {
                    if (str.empty()) { return false; }
                    typename std_string_t::const_iterator itr = str.begin();
                    while (itr != str.end()) {
                        if (!omni::char_util::helpers::is_1or0(*itr)) { return false; }
                        ++itr;
                    }
                    return true;
                }
                
                template < typename std_string_t >
                std_string_t from_ulong(unsigned long val, bool trim)
                {
                    /* DEV_NOTE: some older compilers complain about the to_string, the workaround is
                    to give the full to_string template parameters with the char type (for a std::string) */
                    std::string ret = std::bitset<OMNI_SIZEOF_BITS(unsigned long)>
                        (static_cast<uint64_t>(val)).
                        to_string<char, std::char_traits<char>, std::allocator<char> >();
                    if (trim) {
                        std::string::iterator itr = ret.begin();
                        while (itr != ret.end()) {
                            if (*itr == '0') {
                                ret.erase(itr);
                                --itr;
                            }
                            else { break; }
                            ++itr;
                        }
                    }
                    return omni::string::util::lexical_cast<std_string_t>(ret);
                }
                
                template < typename std_string_t >
                std_string_t from_ulong(unsigned long val)
                {
                    return omni::string::util::binary::from_ulong<std_string_t>(val, true);
                }
                
                template < typename std_string_t >
                std_string_t from_uint(unsigned int val, bool trim)
                {
                    return omni::string::util::binary::from_ulong<std_string_t>(static_cast<unsigned long>(val), trim);
                }
                
                template < typename std_string_t >
                std_string_t from_uint(unsigned int val)
                {
                    return omni::string::util::binary::from_ulong<std_string_t>(static_cast<unsigned long>(val), true);
                }
                
                template < typename std_string_t >
                unsigned int to_uint(const std_string_t& str)
                {
                    if (!omni::string::util::binary::is_valid(str)) {
                        OMNI_ERR_RETV_FW(OMNI_STRING_INVALID_SIZE_STR, omni::exceptions::invalid_binary_size(), 0)
                    }
                    const std::size_t msz = OMNI_SIZEOF_BITS(unsigned int);
                    if (str.length() > msz) {
                        OMNI_ERR_RETV_FW(OMNI_STRING_INVALID_SIZE_STR, omni::exceptions::invalid_binary_size(), 0)
                    }
                    return static_cast<unsigned int>(std::bitset<msz>(omni::string::util::to_string(str)).to_ulong());
                }
                
                template < typename std_string_t >
                unsigned long to_ulong(const std_string_t& str)
                {
                    if (!omni::string::util::binary::is_valid(str)) {
                        OMNI_ERR_RETV_FW(OMNI_STRING_INVALID_SIZE_STR, omni::exceptions::invalid_binary_size(), 0)
                    }
                    const std::size_t msz = OMNI_SIZEOF_BITS(unsigned long);
                    if (str.length() > msz) {
                        OMNI_ERR_RETV_FW(OMNI_STRING_INVALID_SIZE_STR, omni::exceptions::invalid_binary_size(), 0)
                    }
                    return (std::bitset<msz>(omni::string::util::to_string(str)).to_ulong());
                }
                
                template < typename std_string_t >
                std::size_t to_size_t(const std_string_t& str)
                {
                    if (!omni::string::util::binary::is_valid(str)) {
                        OMNI_ERR_RETV_FW(OMNI_STRING_INVALID_SIZE_STR, omni::exceptions::invalid_binary_size(), 0)
                    }
                    if (str.length() > OMNI_SIZEOF_BITS(std::size_t)) {
                        OMNI_ERR_RETV_FW(OMNI_STRING_INVALID_SIZE_STR, omni::exceptions::invalid_binary_size(), 0)
                    }
                    const std::size_t msz = OMNI_SIZEOF_BITS(unsigned long);
                    std::string tmp(omni::string::util::to_string(str));
                    std::size_t len = tmp.length();
                    if (len % 2 != 0) {
                        tmp.insert(0, "0");
                        len = tmp.length();
                    }
                    std::size_t l2 = len / 2;
                    std::size_t hi = (std::bitset<msz>(tmp.substr(0, l2)).to_ulong());
                    unsigned long lo = (std::bitset<msz>(tmp.substr(l2)).to_ulong());
                    std::size_t ret = (hi << (sizeof(std::size_t)/2)) ^ lo;
                    return ret;
                }
            } // namespace binary
        } // namespace util

        /* DEV_NOTE: Some thoughts behind the separation of logic in string namespaces.
            
            If OMNI_UNICODE is defined, then
                the omni::string_t type is a std::wstring
            if it is not defined, then
                the omni::string_t type is a std::string
            
            The omni::cstring namespace functions operate on std::string types
            The omni::wstring namespace functions operate on std::wstring types
            The omni::string namespace functions operate on omni::string_t types
            
            So if OMNI_UNICODE is defined, then
                the omni::string_t type is a std::wstring
                so omni::string namespace functions can operate on omni::string_t and std::wstring
                and omni::wstring namespace functions can operate on std::wstring and omni::string_t
            if it is not defined, then
                the omni::string_t type is a std::string
                so omni::string namespace functions can operate on omni::string_t and std::string
                and omni::cstring namespace functions can operate on std::string and omni::string_t
                
            This gives a developer options to develop specific builds while still having access
            to different string utility functions. You might want to make a build with the
            omni::string_t as a std::wstring type, but might want to specifically check against
            a std::string type (i.e. ensure type safety), so you can still use the omni::string
            namespace functions as your default types then use the omni::cstring namespace
            to check on a std::string type.
            
            It should be noted that the omni::string/cstring/wstring namespaces are merely
            type safe convenience wrappers to the omni::string::util namespace, which contains
            the same functions, but templated for ease of reuse (e.g. you could call
            omni::string::util::trim<std::string>(str, "ABC"), or, if a specific 3rd party
            library had another type of base string type, you could potentially call 
            omni::string::util::trim<SomeOtherStringType>(str, "ABC"))
        */
        #if defined(OMNI_UNICODE)
            // UTF-16/wchar_t/std::wstring/omni::wstring
            #define OMNI_CHAR_T_FW wchar_t
            #define OMNI_STRING_T_FW std::wstring
            #include <omni/xx/string.hxx>
            #undef OMNI_CHAR_T_FW
            #undef OMNI_STRING_T_FW
        #else
            // UTF-8/char/std::string/omni::cstring
            #define OMNI_CHAR_T_FW char
            #define OMNI_STRING_T_FW std::string
            #include <omni/xx/string.hxx>
            #undef OMNI_CHAR_T_FW
            #undef OMNI_STRING_T_FW
        #endif
    } // namespace string
}

#endif // OMNI_STRING_UTIL_HPP
