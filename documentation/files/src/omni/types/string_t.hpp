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
#if !defined(OMNI_STRING_T_HPP)
#define OMNI_STRING_T_HPP 1
#include <omni/defs/global.hpp>
#include <omni/types/char_t.hpp>
#include <string>
#include <sstream>
// defines the string types to use for different string processing
#if defined(OMNI_UNICODE)
    #define OMNI_STRING_T std::wstring // Defines a wide character string type
    #define OMNI_SSTREAM_T std::wstringstream
    #define OMNI_STR_WIDEN(v) L##v
#else
    #define OMNI_STRING_T std::string // Defines an standard character string type
    #define OMNI_SSTREAM_T std::stringstream
    #define OMNI_STR_WIDEN(v) v
#endif
#if !defined(OMNI_STRW)
    // DEV_NOTE: for a macro that always widens, use OMNI_WSTR (from helper.hpp)
    #define OMNI_STRW(v) OMNI_STR_WIDEN(v)
#endif

#define OMNI_STRING_UCWORD_SEPARATORS " \t\r\n\f\v"

namespace omni {
    
    typedef OMNI_STRING_T string_t;
    
    typedef OMNI_SSTREAM_T sstream_t;

    namespace string_util {
        template < typename T >
        inline std::string to_string(const T& val)
        {
            std::stringstream o;
            o << val;
            return o.str();
        }

        inline std::string to_string(bool val)
        {
            return (val ? "true" : "false");
        }

        inline std::string to_string(const std::wstring& str, int code_page)
        {
            if (str.empty()) { return std::string(); }
            std::size_t sz = str.length();
            #if defined(OMNI_WIN_API)
                std::size_t nd = ::WideCharToMultiByte(code_page, 0, str.c_str(), sz, NULL, 0, NULL, NULL);
                if (nd != 0) {
                    std::string cret(nd, '\0');
                    std::size_t w = ::WideCharToMultiByte(code_page, 0, str.c_str(), sz, &cret[0], nd, NULL, NULL);
                    if (w != 0) {
                        if (w != sz) {
                            OMNI_ERR_RETV_FW("wrote " << w << " but expected size of " << sz, omni::exceptions::invalid_size(), std::string())
                        }
                        return cret;
                    }
                }
                OMNI_THROW_FW(omni::exceptions::invalid_size())
                return std::string();
            #else
                OMNI_UNUSED(code_page);
                std::string cret(sz, '\0');
                std::size_t w = std::wcstombs(&cret[0], str.c_str(), sz);
                if (w != 0) {
                    if (w != sz) {
                        OMNI_ERR_RETV_FW("wrote " << w << " but expected size of " << sz, omni::exceptions::invalid_size(), std::string())
                    }
                    return cret;
                }
                OMNI_THROW_FW(omni::exceptions::invalid_size())
                return std::string();
            #endif
        }

        inline std::string to_string(const std::wstring& str)
        {
            return omni::string_util::to_string(str, OMNI_CODE_PAGE);
        }

        inline std::string to_string(const wchar_t* str, int code_page)
        {
            if (str) { return omni::string_util::to_string(std::wstring(str), code_page); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::string())
        }

        template < std::size_t X >
        inline std::string to_string(const wchar_t (&str)[X], int code_page)
        {
            return omni::string_util::to_string(std::wstring(str), code_page);
        }

        inline std::string to_string(const char* str, int code_page)
        {
            OMNI_UNUSED(code_page);
            if (str) { return std::string(str); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::string())
        }

        template < std::size_t X >
        inline std::string to_string(const char (&str)[X], int code_page)
        {
            OMNI_UNUSED(code_page);
            return std::string(str);
        }

        inline std::string to_string(const std::string& str, int code_page)
        {
            OMNI_UNUSED(code_page);
            return str;
        }

        inline std::string to_string(const wchar_t* str)
        {
            if (str) { return omni::string_util::to_string(std::wstring(str)); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::string())
        }

        template < std::size_t X >
        inline std::string to_string(const wchar_t (&str)[X])
        {
            return omni::string_util::to_string(std::wstring(str));
        }

        inline std::string to_string(const char* str)
        {
            if (str) { return std::string(str); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::string())
        }

        template < std::size_t X >
        inline std::string to_string(const char (&str)[X])
        {
            return std::string(str);
        }

        inline std::string to_string(const std::string& str)
        {
            return str;
        }

        template < typename T >
        inline std::wstring to_wstring(const T& val)
        {
            std::wstringstream o;
            o << val;
            return o.str();
        }

        inline std::wstring to_wstring(bool val)
        {
            return (val ? OMNI_WSTR("true") : OMNI_WSTR("false"));
        }

        inline std::wstring to_wstring(const std::string& str, int code_page)
        {
            if (str.empty()) { return std::wstring(); }
            std::size_t sz = str.length();
            #if defined(OMNI_WIN_API)
                std::size_t nd = ::MultiByteToWideChar(code_page, 0, str.c_str(), sz, NULL, 0);
                if (nd != 0) {
                    std::wstring wret(nd, L'\0');
                    std::size_t w = ::MultiByteToWideChar(code_page, 0, str.c_str(), sz, &wret[0], nd);
                    if (w != 0) {
                        if (w != sz) {
                            OMNI_ERR_RETV_FW("wrote " << w << " but expected size of " << sz, omni::exceptions::invalid_size(), std::wstring())
                        }
                        return wret;
                    }
                }
                OMNI_THROW_FW(omni::exceptions::invalid_size())
                return std::wstring();
            #else
                OMNI_UNUSED(code_page);
                std::wstring wret(sz, L'\0');
                std::size_t w = std::mbstowcs(&wret[0], str.c_str(), sz);
                if (w != 0) {
                    if (w != sz) {
                        OMNI_ERR_RETV_FW("wrote " << w << " but expected size of " << sz, omni::exceptions::invalid_size(), std::wstring())
                    }
                    return wret;
                }
                OMNI_THROW_FW(omni::exceptions::invalid_size())
                return std::wstring();
            #endif
        }

        inline std::wstring to_wstring(const std::string& str)
        {
            return omni::string_util::to_wstring(str, OMNI_CODE_PAGE);
        }

        inline std::wstring to_wstring(const char* str, int code_page)
        {
            if (str) { return omni::string_util::to_wstring(std::string(str), code_page); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::wstring())
        }

        template < std::size_t X >
        inline std::wstring to_wstring(const char (&str)[X], int code_page)
        {
            return omni::string_util::to_wstring(std::string(str), code_page);
        }

        inline std::wstring to_wstring(const wchar_t* str, int code_page)
        {
            OMNI_UNUSED(code_page);
            if (str) { return std::wstring(str); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::wstring())
        }

        template < std::size_t X >
        inline std::wstring to_wstring(const wchar_t (&str)[X], int code_page)
        {
            OMNI_UNUSED(code_page);
            return std::wstring(str);
        }

        inline std::wstring to_wstring(const std::wstring& str, int code_page)
        {
            OMNI_UNUSED(code_page);
            return str;
        }

        inline std::wstring to_wstring(const char* str)
        {
            if (str) { return omni::string_util::to_wstring(std::string(str)); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::wstring())
        }

        template < std::size_t X >
        inline std::wstring to_wstring(const char (&str)[X])
        {
            return omni::string_util::to_wstring(std::string(str));
        }

        inline std::wstring to_wstring(const wchar_t* str)
        {
            if (str) { return std::wstring(str); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), std::wstring())
        }

        template < std::size_t X >
        inline std::wstring to_wstring(const wchar_t (&str)[X])
        {
            return std::wstring(str);
        }

        inline std::wstring to_wstring(const std::wstring& str)
        {
            return str;
        }

        template < typename T >
        inline omni::string_t to_string_t(const T& val)
        {
            omni::sstream_t o;
            o << val;
            return o.str();
        }

        inline omni::string_t to_string_t(bool val)
        {
            #if defined(OMNI_UNICODE)
                return (val ? OMNI_WSTR("true") : OMNI_WSTR("false"));
            #else
                return (val ? "true" : "false");
            #endif
        }

        inline omni::string_t to_string_t(const std::wstring& str)
        {
            #if defined(OMNI_UNICODE)
                return str;
            #else
                return omni::string_util::to_string(str);
            #endif
        }

        inline omni::string_t to_string_t(const wchar_t* str)
        {
            if (str) { return omni::string_util::to_string_t(std::wstring(str)); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
        }

        template < std::size_t X >
        inline omni::string_t to_string_t(const wchar_t (&str)[X])
        {
            #if defined(OMNI_UNICODE)
                return std::wstring(str);
            #else
                return omni::string_util::to_string(str);
            #endif
        }

        inline omni::string_t to_string_t(const std::string& str)
        {
            #if defined(OMNI_UNICODE)
                return omni::string_util::to_wstring(str);
            #else
                return str;
            #endif
        }

        inline omni::string_t to_string_t(const char* str)
        {
            if (str) { return omni::string_util::to_string_t(std::string(str)); }
            OMNI_ERR_RETV_FW("Null pointer specified", omni::exceptions::null_pointer_exception(), omni::string_t())
        }

        template < std::size_t X >
        inline omni::string_t to_string_t(const char (&str)[X])
        {
            #if defined(OMNI_UNICODE)
                return omni::string_util::to_wstring(str);
            #else
                return std::string(str);
            #endif
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
        
        template < typename std_string_t >
        class omni_internal
        {
            public:
                template < typename T >
                inline static std_string_t lexical_cast(const T& val)
                {
                    return val;
                }
        };

        template <>
        class omni_internal<std::wstring>
        {
            public:
                template < typename T >
                inline static std::wstring lexical_cast(const T& val)
                {
                    return omni::string_util::to_wstring(val);
                }
        };

        template <>
        class omni_internal<std::string>
        {
            public:
                template < typename T >
                inline static std::string lexical_cast(const T& val)
                {
                    return omni::string_util::to_string(val);
                }
        };
    }
}

#endif // OMNI_STRING_T_HPP
