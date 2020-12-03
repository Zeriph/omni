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
#if !defined(OMNI_CHAR_T_HPP)
#define OMNI_CHAR_T_HPP 1
#include <omni/defs/global.hpp>
#include <cctype>
#include <cwctype>
#include <cstdlib>
#include <cwchar>

// defines the string types to use for different string processing
#if defined(OMNI_UNICODE)
    #define OMNI_CHAR_T wchar_t     // Defines a wide character type
#else
    #define OMNI_CHAR_T char       // Defines a standard character type
#endif

namespace omni {
    typedef OMNI_CHAR_T char_t;

    namespace char_util {
        inline bool is_alpha(char c)
        { return (std::isalpha(c) != 0); }
        
        inline bool is_alpha(wchar_t c)
        { return (std::iswalpha(c) != 0); }

        inline bool is_digit(char c)
        { return (std::isdigit(c) != 0); }
        
        inline bool is_digit(wchar_t c)
        { return (std::iswdigit(c) != 0); }

        inline bool is_punct(char c)
        { return (std::ispunct(c) != 0); }

        inline bool is_punct(wchar_t c)
        { return (std::iswpunct(c) != 0); }

        inline bool is_alpha_digit(char c)
        {
            return omni::char_util::is_alpha(c) ||
                   omni::char_util::is_digit(c);
        }

        inline bool is_alpha_digit(wchar_t c)
        {
            return omni::char_util::is_alpha(c) ||
                   omni::char_util::is_digit(c);
        }

        inline bool is_alpha_digit_punct(char c)
        {
            return omni::char_util::is_alpha(c) ||
                   omni::char_util::is_digit(c) ||
                   omni::char_util::is_punct(c);
        }

        inline bool is_alpha_digit_punct(wchar_t c)
        {
            return omni::char_util::is_alpha(c) ||
                   omni::char_util::is_digit(c) ||
                   omni::char_util::is_punct(c); 
        }

        inline bool is_alpha_num(char c)
        {
            return omni::char_util::is_alpha_digit(c);
        }

        inline bool is_alpha_num(wchar_t c)
        {
            return omni::char_util::is_alpha_digit(c);
        }

        inline bool is_alpha_num_punct(char c)
        {
            return omni::char_util::is_alpha_digit_punct(c);
        }

        inline bool is_alpha_num_punct(wchar_t c)
        {
            return omni::char_util::is_alpha_digit_punct(c);
        }
        
        inline bool is_hex(char c)
        {
            switch (c) {
                case 'A': case 'a':
                case 'B': case 'b':
                case 'C': case 'c':
                case 'D': case 'd':
                case 'E': case 'e':
                case 'F': case 'f':
                case '0': case '1': case '2': case '3': case '4': 
                case '5': case '6': case '7': case '8': case '9': 
                    return true;
                default: break;
            }
            return false;
        }

        inline bool is_hex(wchar_t c)
        {
            switch (c) {
                case L'A': case L'a':
                case L'B': case L'b':
                case L'C': case L'c':
                case L'D': case L'd':
                case L'E': case L'e':
                case L'F': case L'f':
                case L'0': case L'1': case L'2': case L'3': case L'4': 
                case L'5': case L'6': case L'7': case L'8': case L'9': 
                    return true;
                default: break;
            }
            return false;
        }

        inline bool is_octal(char c)
        {
            switch (c) {
                case '0': case '1': case '2': case '3':
                case '4':  case '5': case '6': case '7':
                    return true;
                default: break;
            }
            return false;
        }

        inline bool is_octal(wchar_t c)
        {
            switch (c) {
                case L'0': case L'1': case L'2': case L'3':
                case L'4': case L'5': case L'6': case L'7':
                    return true;
                default: break;
            }
            return false;
        }

        inline bool is_white_space(char c)
        { return (std::isspace(c) != 0); }

        inline bool is_white_space(wchar_t c)
        { return (std::iswspace(c) != 0); }

        inline char to_char(wchar_t wc, int code_page)
        {
            #if defined(OMNI_WIN_API)
                char cret;
                std::size_t w = ::WideCharToMultiByte(code_page, 0, &wc, 1, &cret, 1, NULL, NULL);
                if (w != 1) {
                    OMNI_ERRV_FW("expected size of 1 got ", w, omni::exceptions::invalid_size())
                }
                return cret;
            #else
                OMNI_UNUSED(code_page);
                int rc = std::wctob(wc);
                if (rc == EOF) {
                    OMNI_ERR_FW("invalid wchar to char ", omni::exceptions::invalid_type_cast())
                }
                return static_cast<char>(rc);
            #endif
        }

        inline char to_char(wchar_t wc)
        {
            return omni::char_util::to_char(wc, OMNI_CODE_PAGE);
        }

        inline char to_char(char c)
        {
            return c;
        }

        inline char to_char(char c, int code_page)
        {
            OMNI_UNUSED(code_page);
            return c;
        }

        inline int to_int(char c, bool has_hex)
        {
            if (omni::char_util::is_digit(c)) {
                return c - '0';
            } else if (has_hex) {
                switch (c) {
                    case 'A': case 'a': return 10;
                    case 'B': case 'b': return 11;
                    case 'C': case 'c': return 12;
                    case 'D': case 'd': return 13;
                    case 'E': case 'e': return 14;
                    case 'F': case 'f': return 15;
                    default: break;
                }
            }
            return -1;
        }

        inline int to_int(wchar_t c, bool has_hex)
        { return omni::char_util::to_int(omni::char_util::to_char(c), has_hex); }

        inline int to_int(char c)
        { return omni::char_util::to_int(c, false); }

        inline int to_int(wchar_t c)
        { return omni::char_util::to_int(omni::char_util::to_char(c)); }
        
        template < typename std_char_t >
        std_char_t to_lower(std_char_t c)
        { OMNI_UNUSED(c); OMNI_ERR_RETV_FW("Invalid template parameter specified.", omni::exceptions::invalid_template_type(), c) }
        
        template <>
        inline char to_lower<char>(char c)
        { return static_cast<char>(std::tolower(c)); }
        
        template <>
        inline wchar_t to_lower<wchar_t>(wchar_t c)
        { return std::towlower(c); }
        
        template < typename std_char_t >
        std_char_t to_upper(std_char_t c)
        { OMNI_UNUSED(c); OMNI_ERR_RETV_FW("Invalid template parameter specified.", omni::exceptions::invalid_template_type(), c) }
        
        template <>
        inline char to_upper<char>(char c)
        { return static_cast<char>(std::toupper(c)); }
        
        template <>
        inline wchar_t to_upper<wchar_t>(wchar_t c)
        { return std::towupper(c); }

        inline wchar_t to_wchar(char c, int code_page)
        {
            #if defined(OMNI_WIN_API)
                wchar_t wret;
                std::size_t w = ::MultiByteToWideChar(code_page, 0, &c, 1, &wret, 1);
                if (w != 1) {
                    OMNI_ERRV_FW("expected size of 1 got ", w, omni::exceptions::invalid_size())
                }
                return wret;
            #else
                OMNI_UNUSED(code_page);
                wint_t rc = std::btowc(c);
                if (rc == WEOF) {
                    OMNI_ERR_FW("invalid char to wchar ", omni::exceptions::invalid_type_cast())
                }
                return static_cast<wchar_t>(rc);
            #endif
        }

        inline wchar_t to_wchar(char c)
        {
            return omni::char_util::to_wchar(c, OMNI_CODE_PAGE);
        }

        inline wchar_t to_wchar(wchar_t wc)
        {
            return wc;
        }

        inline wchar_t to_wchar(wchar_t wc, int code_page)
        {
            OMNI_UNUSED(code_page);
            return wc;
        }

        template < typename Cx, typename Cy >
        inline Cx to_char_t(Cy c)
        {
            return static_cast<Cx>(c);
        }

        template <>
        inline char to_char_t<char,wchar_t>(wchar_t c)
        {
            return omni::char_util::to_char(c);
        }

        template <>
        inline char to_char_t<char,char>(char c)
        {
            return c;
        }

        template <>
        inline wchar_t to_char_t<wchar_t,char>(char c)
        {
            return omni::char_util::to_wchar(c);
        }

        template <>
        inline wchar_t to_char_t<wchar_t,wchar_t>(wchar_t c)
        {
            return c;
        }
        
        /** @internal library helper */
        namespace helpers {
            /** @internal library helper */
            inline bool is_1or0(char v)
            { return v == '0' || v == '1'; }
            
            /** @internal library helper */
            inline bool is_1or0(wchar_t v)
            { return v == L'0' || v == L'1'; }
            
            /** @internal library helper */
            inline bool is_nde(char v)
            { return (v == '-' || v == '.' || v == ','); }
            
            /** @internal library helper */
            inline bool is_nde(wchar_t v)
            { return (v == L'-' || v == L'.' || v == L','); }
            
            /** @internal library helper */
            inline bool is_de(char v)
            { return (v == '.' || v == ','); }
            
            /** @internal library helper */
            inline bool is_de(wchar_t v)
            { return (v == L'.' || v == L','); }
            
            /** @internal library helper */
            inline bool is_neg(char v)
            { return (v == '-'); }
            
            /** @internal library helper */
            inline bool is_neg(wchar_t v)
            { return (v == L'-'); }
        }
    }
}

#endif // OMNI_CHAR_T_HPP
