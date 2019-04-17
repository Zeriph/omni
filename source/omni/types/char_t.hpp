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
        inline bool is_digit(char c)
        { return (std::isdigit(c) != 0); }
        
        inline bool is_digit(wchar_t c)
        { return (std::iswdigit(c) != 0); }
        
        inline bool is_alpha(char c)
        { return (std::isalpha(c) != 0); }
        
        inline bool is_alpha(wchar_t c)
        { return (std::iswalpha(c) != 0); }
        
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

        inline char to_char(wchar_t wc)
        {
            #if defined(OMNI_WIN_API)
                char cret;
                std::size_t w = ::WideCharToMultiByte(OMNI_CODE_PAGE, 0, &wc, 1, &cret, 1, NULL, NULL);
                if (w != 1) {
                    OMNI_ERRV_FW("expected size of 1 got ", w, omni::exceptions::invalid_size())
                }
                return cret;
            #else
                int rc = std::wctob(wc);
                if (rc == EOF) {
                    OMNI_ERR_FW("invalid wchar to char ", omni::exceptions::invalid_type_cast())
                }
                return static_cast<char>(rc);
            #endif
        }

        inline char to_char(char c)
        {
            return c;
        }

        inline wchar_t to_wchar(char c)
        {
            #if defined(OMNI_WIN_API)
                wchar_t wret;
                std::size_t w = ::MultiByteToWideChar(OMNI_CODE_PAGE, 0, &c, 1, &wret, 1);
                if (w != 1) {
                    OMNI_ERRV_FW("expected size of 1 got ", w, omni::exceptions::invalid_size())
                }
                return wret;
            #else
                wint_t rc = std::btowc(c);
                if (rc == WEOF) {
                    OMNI_ERR_FW("invalid char to wchar ", omni::exceptions::invalid_type_cast())
                }
                return static_cast<wchar_t>(rc);
            #endif
        }

        inline wchar_t to_wchar(wchar_t wc)
        {
            return wc;
        }

        template < typename Cx, typename Cy >
        inline Cx to_char_t(Cy c)
        {
            return static_cast<Cx>(c);
        }

        template<>
        inline char to_char_t<char, wchar_t>(wchar_t c)
        {
            return omni::char_util::to_char(c);
        }

        template<>
        inline char to_char_t<char, char>(char c)
        {
            return c;
        }

        template<>
        inline wchar_t to_char_t<wchar_t, char>(char c)
        {
            return omni::char_util::to_wchar(c);
        }

        template<>
        inline wchar_t to_char_t<wchar_t, wchar_t>(wchar_t c)
        {
            return c;
        }
        
        /** @internal framework helper */
        namespace helpers {
            /** @internal framework helper */
            inline bool is_1or0(char v)
            { return v == '0' || v == '1'; }
            
            /** @internal framework helper */
            inline bool is_1or0(wchar_t v)
            { return v == L'0' || v == L'1'; }
            
            /** @internal framework helper */
            inline bool is_nde(char v)
            { return (v == '-' || v == '.' || v == ','); }
            
            /** @internal framework helper */
            inline bool is_nde(wchar_t v)
            { return (v == L'-' || v == L'.' || v == L','); }
            
            /** @internal framework helper */
            inline bool is_de(char v)
            { return (v == '.' || v == ','); }
            
            /** @internal framework helper */
            inline bool is_de(wchar_t v)
            { return (v == L'.' || v == L','); }
            
            /** @internal framework helper */
            inline bool is_neg(char v)
            { return (v == '-'); }
            
            /** @internal framework helper */
            inline bool is_neg(wchar_t v)
            { return (v == L'-'); }
        }
    }
}

#endif // OMNI_CHAR_T_HPP
