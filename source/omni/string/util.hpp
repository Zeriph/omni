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
#include <omni/types/string_t.hpp>
#include <omni/sequence.hpp>
#include <omni/type.hpp>
#include <omni/defs/consts.hpp>
#include <omni/bits.hpp>
#include <bitset>

namespace omni {
    namespace string {
        /**
         * @brief   The util namespace is utilized by omni::cstring and omni::wstring
         *          directly. You can use the omni::string::util namespace directly in
         *          user code, but it is recommended you utilize the omni::(c|w)string
         *          namespace versions instead.
         */
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
                if (count == 0) { return str; }
                return str.insert(0, count, pad);
            }

            template < typename std_string_t >
            std_string_t pad_left(const std_string_t& str, const std_string_t& pad, std::size_t count)
            {
                if (count == 0) { return str; }
                std_string_t ret(pad);
                while (count > 0) {
                    ret.append(pad);
                    --count;
                }
                return ret + str;
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t pad_left(std_string_t str, const typename std_string_t::value_type (&pad)[X], std::size_t count)
            {
                return omni::string::util::pad_left(str, std_string_t(pad), count);
            }

            template < typename std_string_t >
            std_string_t pad_right(std_string_t str, typename std_string_t::value_type pad, std::size_t count)
            {
                if (count == 0) { return str; }
                return str.append(count, pad);
            }

            template < typename std_string_t >
            std_string_t pad_right(std_string_t str, const std_string_t& pad, std::size_t count)
            {
                while (count > 0) {
                    str.append(pad);
                    --count;
                }
                return str;
            }
            
            template < typename std_string_t, std::size_t X >
            std_string_t pad_right(std_string_t str, typename std_string_t::value_type (&pad)[X], std::size_t count)
            {
                return omni::string::util::pad_right(str, std_string_t(pad), count);
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
                    std::size_t t = str.find_first_of("tT");
                    std::size_t f = str.find_first_of("fF");
                    if (t == std::string::npos && f == std::string::npos) {
                        t = str.find_first_of("123456789");
                        if (t == 1) { return true; }
                    } else {
                        if (str == "true") { return true; }
                        if (str == "false") { return false; }
                        if (t == 1) { return true; }
                    }
                }
                return false;
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
                    std::size_t t = str.find_first_of(L"tT");
                    std::size_t f = str.find_first_of(L"fF");
                    if (t == std::wstring::npos && f == std::wstring::npos) {
                        t = str.find_first_of(L"123456789");
                        if (t == 1) { return true; }
                    } else {
                        if (str == L"true") { return true; }
                        if (str == L"false") { return false; }
                        if (t == 1) { return true; }
                    }
                }
                return false;
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
                if (pos != std_string_t::npos) {
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

        /* DEV_NOTE: Some info on the logic idea behind the separation of logic in string namespaces.
        
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
