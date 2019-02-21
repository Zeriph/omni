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
#if !defined(OMNI_KNOWN_COLORS_HPP)
#define OMNI_KNOWN_COLORS_HPP 1
#include <omni/drawing/color.hpp>

namespace omni {
    namespace drawing {
        class known_colors
        {
            public:
                /** The underlying enum type expected */
                typedef enum enum_t {
                    ALICEBLUE = 0xF0F8FF,
                    ANTIQUEWHITE = 0xFAEBD7,
                    AQUA = 0x00FFFF,
                    AQUAMARINE = 0x7FFFD4,
                    AZURE = 0xF0FFFF,
                    BEIGE = 0xF5F5DC,
                    BISQUE = 0xFFE4C4,
                    BLACK = 0x000000,
                    BLANCHEDALMOND = 0xFFEBCD,
                    BLUE = 0x0000FF,
                    BLUEVIOLET = 0x8A2BE2,
                    BROWN = 0xA52A2A,
                    BURLYWOOD = 0xDEB887,
                    CADETBLUE = 0x5F9EA0,
                    CHARTREUSE = 0x7FFF00,
                    CHOCOLATE = 0xD2691E,
                    CORAL = 0xFF7F50,
                    CORNFLOWERBLUE = 0x6495ED,
                    CORNSILK = 0xFFF8DC,
                    CRIMSON = 0xDC143C,
                    CYAN = 0x00FFFF,
                    DARKBLUE = 0x00008B,
                    DARKCYAN = 0x008B8B,
                    DARKGOLDENROD = 0xB8860B,
                    DARKGRAY = 0xA9A9A9,
                    DARKGREEN = 0x006400,
                    DARKKHAKI = 0xBDB76B,
                    DARKMAGENTA = 0x8B008B,
                    DARKOLIVEGREEN = 0x556B2F,
                    DARKORANGE = 0xFF8C00,
                    DARKORCHID = 0x9932CC,
                    DARKRED = 0x8B0000,
                    DARKSALMON = 0xE9967A,
                    DARKSEAGREEN = 0x8FBC8F,
                    DARKSLATEBLUE = 0x483D8B,
                    DARKSLATEGRAY = 0x2F4F4F,
                    DARKTURQUOISE = 0x00CED1,
                    DARKVIOLET = 0x9400D3,
                    DEEPPINK = 0xFF1493,
                    DEEPSKYBLUE = 0x00BFFF,
                    DIMGRAY = 0x696969,
                    DODGERBLUE = 0x1E90FF,
                    FIREBRICK = 0xB22222,
                    FLORALWHITE = 0xFFFAF0,
                    FORESTGREEN = 0x228B22,
                    FUCHSIA = 0xFF00FF,
                    GAINSBORO = 0xDCDCDC,
                    GHOSTWHITE = 0xF8F8FF,
                    GOLD = 0xFFD700,
                    GOLDENROD = 0xDAA520,
                    GRAY = 0x808080,
                    GREEN = 0x008000,
                    GREENYELLOW = 0xADFF2F,
                    HONEYDEW = 0xF0FFF0,
                    HOTPINK = 0xFF69B4,
                    INDIANRED = 0xCD5C5C,
                    INDIGO = 0x4B0082,
                    IVORY = 0xFFFFF0,
                    KHAKI = 0xF0E68C,
                    LAVENDER = 0xE6E6FA,
                    LAVENDERBLUSH = 0xFFF0F5,
                    LAWNGREEN = 0x7CFC00,
                    LEMONCHIFFON = 0xFFFACD,
                    LIGHTBLUE = 0xADD8E6,
                    LIGHTCORAL = 0xF08080,
                    LIGHTCYAN = 0xE0FFFF,
                    LIGHTGOLDENRODYELLOW = 0xFAFAD2,
                    LIGHTGRAY = 0xD3D3D3,
                    LIGHTGREEN = 0x90EE90,
                    LIGHTPINK = 0xFFB6C1,
                    LIGHTSALMON = 0xFFA07A,
                    LIGHTSEAGREEN = 0x20B2AA,
                    LIGHTSKYBLUE = 0x87CEFA,
                    LIGHTSLATEGRAY = 0x778899,
                    LIGHTSTEELBLUE = 0xB0C4DE,
                    LIGHTYELLOW = 0xFFFFE0,
                    LIME = 0x00FF00,
                    LIMEGREEN = 0x32CD32,
                    LINEN = 0xFAF0E6,
                    MAGENTA = 0xFF00FF,
                    MAROON = 0x800000,
                    MEDIUMAQUAMARINE = 0x66CDAA,
                    MEDIUMBLUE = 0x0000CD,
                    MEDIUMORCHID = 0xBA55D3,
                    MEDIUMPURPLE = 0x9370DB,
                    MEDIUMSEAGREEN = 0x3CB371,
                    MEDIUMSLATEBLUE = 0x7B68EE,
                    MEDIUMSPRINGGREEN = 0x00FA9A,
                    MEDIUMTURQUOISE = 0x48D1CC,
                    MEDIUMVIOLETRED = 0xC71585,
                    MIDNIGHTBLUE = 0x191970,
                    MINTCREAM = 0xF5FFFA,
                    MISTYROSE = 0xFFE4E1,
                    MOCCASIN = 0xFFE4B5,
                    NAVAJOWHITE = 0xFFDEAD,
                    NAVY = 0x000080,
                    OLDLACE = 0xFDF5E6,
                    OLIVE = 0x808000,
                    OLIVEDRAB = 0x6B8E23,
                    ORANGE = 0xFFA500,
                    ORANGERED = 0xFF4500,
                    ORCHID = 0xDA70D6,
                    PALEGOLDENROD = 0xEEE8AA,
                    PALEGREEN = 0x98FB98,
                    PALETURQUOISE = 0xAFEEEE,
                    PALEVIOLETRED = 0xDB7093,
                    PAPAYAWHIP = 0xFFEFD5,
                    PEACHPUFF = 0xFFDAB9,
                    PERU = 0xCD853F,
                    PINK = 0xFFC0CB,
                    PLUM = 0xDDA0DD,
                    POWDERBLUE = 0xB0E0E6,
                    PURPLE = 0x800080,
                    REBECCAPURPLE = 0x663399,
                    RED = 0xFF0000,
                    ROSYBROWN = 0xBC8F8F,
                    ROYALBLUE = 0x4169E1,
                    SADDLEBROWN = 0x8B4513,
                    SALMON = 0xFA8072,
                    SANDYBROWN = 0xF4A460,
                    SEAGREEN = 0x2E8B57,
                    SEASHELL = 0xFFF5EE,
                    SIENNA = 0xA0522D,
                    SILVER = 0xC0C0C0,
                    SKYBLUE = 0x87CEEB,
                    SLATEBLUE = 0x6A5ACD,
                    SLATEGRAY = 0x708090,
                    SNOW = 0xFFFAFA,
                    SPRINGGREEN = 0x00FF7F,
                    STEELBLUE = 0x4682B4,
                    TAN = 0xD2B48C,
                    TEAL = 0x008080,
                    THISTLE = 0xD8BFD8,
                    TOMATO = 0xFF6347,
                    TURQUOISE = 0x40E0D0,
                    VIOLET = 0xEE82EE,
                    WHEAT = 0xF5DEB3,
                    WHITE = 0xFFFFFF,
                    WHITESMOKE = 0xF5F5F5,
                    YELLOW = 0xFFFF00,
                    YELLOWGREEN = 0x9ACD32
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 140;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return BLACK;
                }

                /** Converts the enum to its string representation */
                static std::string to_string(enum_t v)
                {
                    return _to_val<std::stringstream>(v);
                }
            
                /** Converts the enum to its wide string representation */
                static std::wstring to_wstring(enum_t v)
                {
                    return _to_val<std::wstringstream>(v);
                }

                /** Parsing a string value into its enum representation */
                static enum_t parse(const std::string& val)
                {
                    return _parse(val);
                }

                /** Parsing a wide string value into its enum representation */
                static enum_t parse(const std::wstring& val)
                {
                    return _parse(val);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, enum_t& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a string value into its enum representation */
                static bool try_parse(const std::string& val, known_colors& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, known_colors& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int val)
                {
                    return _valid(val);
                }

                static enum_t from_color(const omni::drawing::color_t& val)
                {
                    omni::drawing::color_t::rgb_t rgb = val.to_rgb();
                    if (_valid(rgb)) {
                        return static_cast<enum_t>(rgb);
                    }
                    // TODO: error
                    return DEFAULT_VALUE();
                }

                static enum_t from_rgb(omni::drawing::color_t::rgb_t rgb)
                {
                    if (_valid(rgb)) {
                        return static_cast<enum_t>(rgb);
                    }
                    // TODO: error
                    return DEFAULT_VALUE();
                }

                static color_t get_color(enum_t val)
                {
                    if (_valid(val)) {
                        return omni::drawing::color_t(static_cast<omni::drawing::color_t::rgb_t>(val));
                    }
                    // TODO: error
                    return omni::drawing::color_t();
                }

                static omni::drawing::color_t aliceblue() { return omni::drawing::color_t(ALICEBLUE); }
                static omni::drawing::color_t antiquewhite() { return omni::drawing::color_t(ANTIQUEWHITE); }
                static omni::drawing::color_t aqua() { return omni::drawing::color_t(AQUA); }
                static omni::drawing::color_t aquamarine() { return omni::drawing::color_t(AQUAMARINE); }
                static omni::drawing::color_t azure() { return omni::drawing::color_t(AZURE); }
                static omni::drawing::color_t beige() { return omni::drawing::color_t(BEIGE); }
                static omni::drawing::color_t bisque() { return omni::drawing::color_t(BISQUE); }
                static omni::drawing::color_t black() { return omni::drawing::color_t(BLACK); }
                static omni::drawing::color_t blanchedalmond() { return omni::drawing::color_t(BLANCHEDALMOND); }
                static omni::drawing::color_t blue() { return omni::drawing::color_t(BLUE); }
                static omni::drawing::color_t blueviolet() { return omni::drawing::color_t(BLUEVIOLET); }
                static omni::drawing::color_t brown() { return omni::drawing::color_t(BROWN); }
                static omni::drawing::color_t burlywood() { return omni::drawing::color_t(BURLYWOOD); }
                static omni::drawing::color_t cadetblue() { return omni::drawing::color_t(CADETBLUE); }
                static omni::drawing::color_t chartreuse() { return omni::drawing::color_t(CHARTREUSE); }
                static omni::drawing::color_t chocolate() { return omni::drawing::color_t(CHOCOLATE); }
                static omni::drawing::color_t coral() { return omni::drawing::color_t(CORAL); }
                static omni::drawing::color_t cornflowerblue() { return omni::drawing::color_t(CORNFLOWERBLUE); }
                static omni::drawing::color_t cornsilk() { return omni::drawing::color_t(CORNSILK); }
                static omni::drawing::color_t crimson() { return omni::drawing::color_t(CRIMSON); }
                static omni::drawing::color_t cyan() { return omni::drawing::color_t(CYAN); }
                static omni::drawing::color_t darkblue() { return omni::drawing::color_t(DARKBLUE); }
                static omni::drawing::color_t darkcyan() { return omni::drawing::color_t(DARKCYAN); }
                static omni::drawing::color_t darkgoldenrod() { return omni::drawing::color_t(DARKGOLDENROD); }
                static omni::drawing::color_t darkgray() { return omni::drawing::color_t(DARKGRAY); }
                static omni::drawing::color_t darkgreen() { return omni::drawing::color_t(DARKGREEN); }
                static omni::drawing::color_t darkkhaki() { return omni::drawing::color_t(DARKKHAKI); }
                static omni::drawing::color_t darkmagenta() { return omni::drawing::color_t(DARKMAGENTA); }
                static omni::drawing::color_t darkolivegreen() { return omni::drawing::color_t(DARKOLIVEGREEN); }
                static omni::drawing::color_t darkorange() { return omni::drawing::color_t(DARKORANGE); }
                static omni::drawing::color_t darkorchid() { return omni::drawing::color_t(DARKORCHID); }
                static omni::drawing::color_t darkred() { return omni::drawing::color_t(DARKRED); }
                static omni::drawing::color_t darksalmon() { return omni::drawing::color_t(DARKSALMON); }
                static omni::drawing::color_t darkseagreen() { return omni::drawing::color_t(DARKSEAGREEN); }
                static omni::drawing::color_t darkslateblue() { return omni::drawing::color_t(DARKSLATEBLUE); }
                static omni::drawing::color_t darkslategray() { return omni::drawing::color_t(DARKSLATEGRAY); }
                static omni::drawing::color_t darkturquoise() { return omni::drawing::color_t(DARKTURQUOISE); }
                static omni::drawing::color_t darkviolet() { return omni::drawing::color_t(DARKVIOLET); }
                static omni::drawing::color_t deeppink() { return omni::drawing::color_t(DEEPPINK); }
                static omni::drawing::color_t deepskyblue() { return omni::drawing::color_t(DEEPSKYBLUE); }
                static omni::drawing::color_t dimgray() { return omni::drawing::color_t(DIMGRAY); }
                static omni::drawing::color_t dodgerblue() { return omni::drawing::color_t(DODGERBLUE); }
                static omni::drawing::color_t firebrick() { return omni::drawing::color_t(FIREBRICK); }
                static omni::drawing::color_t floralwhite() { return omni::drawing::color_t(FLORALWHITE); }
                static omni::drawing::color_t forestgreen() { return omni::drawing::color_t(FORESTGREEN); }
                static omni::drawing::color_t fuchsia() { return omni::drawing::color_t(FUCHSIA); }
                static omni::drawing::color_t gainsboro() { return omni::drawing::color_t(GAINSBORO); }
                static omni::drawing::color_t ghostwhite() { return omni::drawing::color_t(GHOSTWHITE); }
                static omni::drawing::color_t gold() { return omni::drawing::color_t(GOLD); }
                static omni::drawing::color_t goldenrod() { return omni::drawing::color_t(GOLDENROD); }
                static omni::drawing::color_t gray() { return omni::drawing::color_t(GRAY); }
                static omni::drawing::color_t green() { return omni::drawing::color_t(GREEN); }
                static omni::drawing::color_t greenyellow() { return omni::drawing::color_t(GREENYELLOW); }
                static omni::drawing::color_t honeydew() { return omni::drawing::color_t(HONEYDEW); }
                static omni::drawing::color_t hotpink() { return omni::drawing::color_t(HOTPINK); }
                static omni::drawing::color_t indianred() { return omni::drawing::color_t(INDIANRED); }
                static omni::drawing::color_t indigo() { return omni::drawing::color_t(INDIGO); }
                static omni::drawing::color_t ivory() { return omni::drawing::color_t(IVORY); }
                static omni::drawing::color_t khaki() { return omni::drawing::color_t(KHAKI); }
                static omni::drawing::color_t lavender() { return omni::drawing::color_t(LAVENDER); }
                static omni::drawing::color_t lavenderblush() { return omni::drawing::color_t(LAVENDERBLUSH); }
                static omni::drawing::color_t lawngreen() { return omni::drawing::color_t(LAWNGREEN); }
                static omni::drawing::color_t lemonchiffon() { return omni::drawing::color_t(LEMONCHIFFON); }
                static omni::drawing::color_t lightblue() { return omni::drawing::color_t(LIGHTBLUE); }
                static omni::drawing::color_t lightcoral() { return omni::drawing::color_t(LIGHTCORAL); }
                static omni::drawing::color_t lightcyan() { return omni::drawing::color_t(LIGHTCYAN); }
                static omni::drawing::color_t lightgoldenrodyellow() { return omni::drawing::color_t(LIGHTGOLDENRODYELLOW); }
                static omni::drawing::color_t lightgray() { return omni::drawing::color_t(LIGHTGRAY); }
                static omni::drawing::color_t lightgreen() { return omni::drawing::color_t(LIGHTGREEN); }
                static omni::drawing::color_t lightpink() { return omni::drawing::color_t(LIGHTPINK); }
                static omni::drawing::color_t lightsalmon() { return omni::drawing::color_t(LIGHTSALMON); }
                static omni::drawing::color_t lightseagreen() { return omni::drawing::color_t(LIGHTSEAGREEN); }
                static omni::drawing::color_t lightskyblue() { return omni::drawing::color_t(LIGHTSKYBLUE); }
                static omni::drawing::color_t lightslategray() { return omni::drawing::color_t(LIGHTSLATEGRAY); }
                static omni::drawing::color_t lightsteelblue() { return omni::drawing::color_t(LIGHTSTEELBLUE); }
                static omni::drawing::color_t lightyellow() { return omni::drawing::color_t(LIGHTYELLOW); }
                static omni::drawing::color_t lime() { return omni::drawing::color_t(LIME); }
                static omni::drawing::color_t limegreen() { return omni::drawing::color_t(LIMEGREEN); }
                static omni::drawing::color_t linen() { return omni::drawing::color_t(LINEN); }
                static omni::drawing::color_t magenta() { return omni::drawing::color_t(MAGENTA); }
                static omni::drawing::color_t maroon() { return omni::drawing::color_t(MAROON); }
                static omni::drawing::color_t mediumaquamarine() { return omni::drawing::color_t(MEDIUMAQUAMARINE); }
                static omni::drawing::color_t mediumblue() { return omni::drawing::color_t(MEDIUMBLUE); }
                static omni::drawing::color_t mediumorchid() { return omni::drawing::color_t(MEDIUMORCHID); }
                static omni::drawing::color_t mediumpurple() { return omni::drawing::color_t(MEDIUMPURPLE); }
                static omni::drawing::color_t mediumseagreen() { return omni::drawing::color_t(MEDIUMSEAGREEN); }
                static omni::drawing::color_t mediumslateblue() { return omni::drawing::color_t(MEDIUMSLATEBLUE); }
                static omni::drawing::color_t mediumspringgreen() { return omni::drawing::color_t(MEDIUMSPRINGGREEN); }
                static omni::drawing::color_t mediumturquoise() { return omni::drawing::color_t(MEDIUMTURQUOISE); }
                static omni::drawing::color_t mediumvioletred() { return omni::drawing::color_t(MEDIUMVIOLETRED); }
                static omni::drawing::color_t midnightblue() { return omni::drawing::color_t(MIDNIGHTBLUE); }
                static omni::drawing::color_t mintcream() { return omni::drawing::color_t(MINTCREAM); }
                static omni::drawing::color_t mistyrose() { return omni::drawing::color_t(MISTYROSE); }
                static omni::drawing::color_t moccasin() { return omni::drawing::color_t(MOCCASIN); }
                static omni::drawing::color_t navajowhite() { return omni::drawing::color_t(NAVAJOWHITE); }
                static omni::drawing::color_t navy() { return omni::drawing::color_t(NAVY); }
                static omni::drawing::color_t oldlace() { return omni::drawing::color_t(OLDLACE); }
                static omni::drawing::color_t olive() { return omni::drawing::color_t(OLIVE); }
                static omni::drawing::color_t olivedrab() { return omni::drawing::color_t(OLIVEDRAB); }
                static omni::drawing::color_t orange() { return omni::drawing::color_t(ORANGE); }
                static omni::drawing::color_t orangered() { return omni::drawing::color_t(ORANGERED); }
                static omni::drawing::color_t orchid() { return omni::drawing::color_t(ORCHID); }
                static omni::drawing::color_t palegoldenrod() { return omni::drawing::color_t(PALEGOLDENROD); }
                static omni::drawing::color_t palegreen() { return omni::drawing::color_t(PALEGREEN); }
                static omni::drawing::color_t paleturquoise() { return omni::drawing::color_t(PALETURQUOISE); }
                static omni::drawing::color_t palevioletred() { return omni::drawing::color_t(PALEVIOLETRED); }
                static omni::drawing::color_t papayawhip() { return omni::drawing::color_t(PAPAYAWHIP); }
                static omni::drawing::color_t peachpuff() { return omni::drawing::color_t(PEACHPUFF); }
                static omni::drawing::color_t peru() { return omni::drawing::color_t(PERU); }
                static omni::drawing::color_t pink() { return omni::drawing::color_t(PINK); }
                static omni::drawing::color_t plum() { return omni::drawing::color_t(PLUM); }
                static omni::drawing::color_t powderblue() { return omni::drawing::color_t(POWDERBLUE); }
                static omni::drawing::color_t purple() { return omni::drawing::color_t(PURPLE); }
                static omni::drawing::color_t red() { return omni::drawing::color_t(RED); }
                static omni::drawing::color_t rosybrown() { return omni::drawing::color_t(ROSYBROWN); }
                static omni::drawing::color_t royalblue() { return omni::drawing::color_t(ROYALBLUE); }
                static omni::drawing::color_t saddlebrown() { return omni::drawing::color_t(SADDLEBROWN); }
                static omni::drawing::color_t salmon() { return omni::drawing::color_t(SALMON); }
                static omni::drawing::color_t sandybrown() { return omni::drawing::color_t(SANDYBROWN); }
                static omni::drawing::color_t seagreen() { return omni::drawing::color_t(SEAGREEN); }
                static omni::drawing::color_t seashell() { return omni::drawing::color_t(SEASHELL); }
                static omni::drawing::color_t sienna() { return omni::drawing::color_t(SIENNA); }
                static omni::drawing::color_t silver() { return omni::drawing::color_t(SILVER); }
                static omni::drawing::color_t skyblue() { return omni::drawing::color_t(SKYBLUE); }
                static omni::drawing::color_t slateblue() { return omni::drawing::color_t(SLATEBLUE); }
                static omni::drawing::color_t slategray() { return omni::drawing::color_t(SLATEGRAY); }
                static omni::drawing::color_t snow() { return omni::drawing::color_t(SNOW); }
                static omni::drawing::color_t springgreen() { return omni::drawing::color_t(SPRINGGREEN); }
                static omni::drawing::color_t steelblue() { return omni::drawing::color_t(STEELBLUE); }
                static omni::drawing::color_t tan() { return omni::drawing::color_t(TAN); }
                static omni::drawing::color_t teal() { return omni::drawing::color_t(TEAL); }
                static omni::drawing::color_t thistle() { return omni::drawing::color_t(THISTLE); }
                static omni::drawing::color_t tomato() { return omni::drawing::color_t(TOMATO); }
                static omni::drawing::color_t turquoise() { return omni::drawing::color_t(TURQUOISE); }
                static omni::drawing::color_t violet() { return omni::drawing::color_t(VIOLET); }
                static omni::drawing::color_t wheat() { return omni::drawing::color_t(WHEAT); }
                static omni::drawing::color_t white() { return omni::drawing::color_t(WHITE); }
                static omni::drawing::color_t whitesmoke() { return omni::drawing::color_t(WHITESMOKE); }
                static omni::drawing::color_t yellow() { return omni::drawing::color_t(YELLOW); }
                static omni::drawing::color_t yellowgreen() { return omni::drawing::color_t(YELLOWGREEN); }

                known_colors() :
                    OMNI_CTOR_FW(omni::drawing::known_colors)
                    m_val(DEFAULT_VALUE())
                { }

                known_colors(const known_colors& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                known_colors(enum_t val) : 
                    OMNI_CTOR_FW(omni::drawing::known_colors)
                    m_val(val)
                { }

                ~known_colors()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }

                enum_t value() const
                {
                    return this->m_val;
                }

                const std::string to_string() const
                {
                    return to_string(this->m_val);
                }

                const std::wstring to_wstring() const
                {
                    return to_wstring(this->m_val);
                }

                bool operator!=(const known_colors& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                known_colors& operator=(const known_colors& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                known_colors& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                known_colors& operator=(int val)
                {
                    if (!known_colors::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const known_colors& val) const
                {
                    return this->m_val < val.m_val;
                }

                bool operator<(enum_t val) const
                {
                    return this->m_val < val;
                }

                bool operator<(int val) const
                {
                    return this->m_val < static_cast<enum_t>(val);
                }

                bool operator>(const known_colors& val) const
                {
                    return this->m_val > val.m_val;
                }

                bool operator>(enum_t val) const
                {
                    return this->m_val > val;
                }

                bool operator>(int val) const
                {
                    return this->m_val > val;
                }

                bool operator==(const known_colors& val) const
                {
                    if (this == &val) { return true; }
                    return this->m_val == val.m_val
                            OMNI_EQUAL_FW(val);
                }

                bool operator==(enum_t val) const
                {
                    return this->m_val == val;
                }

                bool operator==(int val) const
                {
                    return this->m_val == val;
                }

                operator enum_t() const
                {
                    return this->m_val;
                }

                operator int() const
                {
                    return static_cast<int>(this->m_val);
                }

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                omni::drawing::color_t::rgb_t to_rgb() const
                {
                    return static_cast<omni::drawing::color_t::rgb_t>(this->m_val);
                }

                color_t to_color() const
                {
                    return omni::drawing::known_colors::get_color(this->m_val);
                }

                OMNI_MEMBERS_FW(omni::drawing::known_colors) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::drawing::known_colors)
                OMNI_OSTREAM_FN_FW(enum_t)

            private:
                enum_t m_val;

                template < typename S >
                static enum_t _parse(const S& val)
                {
                    enum_t ret;
                    if (_try_parse(val, ret)) { return ret; }
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
                    return DEFAULT_VALUE();
                }

                template < typename S >
                static bool _try_parse(const S& str, enum_t& out)
                {
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, known_colors& out)
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
                    return _try_parse(omni::string::util::to_string(val), out);
                }

                static bool _try_parse(const std::string& val, enum_t& out)
                {
                    if (!val.empty()) {
                        OMNI_S2E_FW(ALICEBLUE)
                        OMNI_S2E_FW(ANTIQUEWHITE)
                        OMNI_S2E_FW(AQUA)
                        OMNI_S2E_FW(AQUAMARINE)
                        OMNI_S2E_FW(AZURE)
                        OMNI_S2E_FW(BEIGE)
                        OMNI_S2E_FW(BISQUE)
                        OMNI_S2E_FW(BLACK)
                        OMNI_S2E_FW(BLANCHEDALMOND)
                        OMNI_S2E_FW(BLUE)
                        OMNI_S2E_FW(BLUEVIOLET)
                        OMNI_S2E_FW(BROWN)
                        OMNI_S2E_FW(BURLYWOOD)
                        OMNI_S2E_FW(CADETBLUE)
                        OMNI_S2E_FW(CHARTREUSE)
                        OMNI_S2E_FW(CHOCOLATE)
                        OMNI_S2E_FW(CORAL)
                        OMNI_S2E_FW(CORNFLOWERBLUE)
                        OMNI_S2E_FW(CORNSILK)
                        OMNI_S2E_FW(CRIMSON)
                        //OMNI_S2E_FW(CYAN) // same as aqua
                        OMNI_S2E_FW(DARKBLUE)
                        OMNI_S2E_FW(DARKCYAN)
                        OMNI_S2E_FW(DARKGOLDENROD)
                        OMNI_S2E_FW(DARKGRAY)
                        OMNI_S2E_FW(DARKGREEN)
                        OMNI_S2E_FW(DARKKHAKI)
                        OMNI_S2E_FW(DARKMAGENTA)
                        OMNI_S2E_FW(DARKOLIVEGREEN)
                        OMNI_S2E_FW(DARKORANGE)
                        OMNI_S2E_FW(DARKORCHID)
                        OMNI_S2E_FW(DARKRED)
                        OMNI_S2E_FW(DARKSALMON)
                        OMNI_S2E_FW(DARKSEAGREEN)
                        OMNI_S2E_FW(DARKSLATEBLUE)
                        OMNI_S2E_FW(DARKSLATEGRAY)
                        OMNI_S2E_FW(DARKTURQUOISE)
                        OMNI_S2E_FW(DARKVIOLET)
                        OMNI_S2E_FW(DEEPPINK)
                        OMNI_S2E_FW(DEEPSKYBLUE)
                        OMNI_S2E_FW(DIMGRAY)
                        OMNI_S2E_FW(DODGERBLUE)
                        OMNI_S2E_FW(FIREBRICK)
                        OMNI_S2E_FW(FLORALWHITE)
                        OMNI_S2E_FW(FORESTGREEN)
                        OMNI_S2E_FW(FUCHSIA)
                        OMNI_S2E_FW(GAINSBORO)
                        OMNI_S2E_FW(GHOSTWHITE)
                        OMNI_S2E_FW(GOLD)
                        OMNI_S2E_FW(GOLDENROD)
                        OMNI_S2E_FW(GRAY)
                        OMNI_S2E_FW(GREEN)
                        OMNI_S2E_FW(GREENYELLOW)
                        OMNI_S2E_FW(HONEYDEW)
                        OMNI_S2E_FW(HOTPINK)
                        OMNI_S2E_FW(INDIANRED)
                        OMNI_S2E_FW(INDIGO)
                        OMNI_S2E_FW(IVORY)
                        OMNI_S2E_FW(KHAKI)
                        OMNI_S2E_FW(LAVENDER)
                        OMNI_S2E_FW(LAVENDERBLUSH)
                        OMNI_S2E_FW(LAWNGREEN)
                        OMNI_S2E_FW(LEMONCHIFFON)
                        OMNI_S2E_FW(LIGHTBLUE)
                        OMNI_S2E_FW(LIGHTCORAL)
                        OMNI_S2E_FW(LIGHTCYAN)
                        OMNI_S2E_FW(LIGHTGOLDENRODYELLOW)
                        OMNI_S2E_FW(LIGHTGRAY)
                        OMNI_S2E_FW(LIGHTGREEN)
                        OMNI_S2E_FW(LIGHTPINK)
                        OMNI_S2E_FW(LIGHTSALMON)
                        OMNI_S2E_FW(LIGHTSEAGREEN)
                        OMNI_S2E_FW(LIGHTSKYBLUE)
                        OMNI_S2E_FW(LIGHTSLATEGRAY)
                        OMNI_S2E_FW(LIGHTSTEELBLUE)
                        OMNI_S2E_FW(LIGHTYELLOW)
                        OMNI_S2E_FW(LIME)
                        OMNI_S2E_FW(LIMEGREEN)
                        OMNI_S2E_FW(LINEN)
                        //OMNI_S2E_FW(MAGENTA) // same as fuchsia
                        OMNI_S2E_FW(MAROON)
                        OMNI_S2E_FW(MEDIUMAQUAMARINE)
                        OMNI_S2E_FW(MEDIUMBLUE)
                        OMNI_S2E_FW(MEDIUMORCHID)
                        OMNI_S2E_FW(MEDIUMPURPLE)
                        OMNI_S2E_FW(MEDIUMSEAGREEN)
                        OMNI_S2E_FW(MEDIUMSLATEBLUE)
                        OMNI_S2E_FW(MEDIUMSPRINGGREEN)
                        OMNI_S2E_FW(MEDIUMTURQUOISE)
                        OMNI_S2E_FW(MEDIUMVIOLETRED)
                        OMNI_S2E_FW(MIDNIGHTBLUE)
                        OMNI_S2E_FW(MINTCREAM)
                        OMNI_S2E_FW(MISTYROSE)
                        OMNI_S2E_FW(MOCCASIN)
                        OMNI_S2E_FW(NAVAJOWHITE)
                        OMNI_S2E_FW(NAVY)
                        OMNI_S2E_FW(OLDLACE)
                        OMNI_S2E_FW(OLIVE)
                        OMNI_S2E_FW(OLIVEDRAB)
                        OMNI_S2E_FW(ORANGE)
                        OMNI_S2E_FW(ORANGERED)
                        OMNI_S2E_FW(ORCHID)
                        OMNI_S2E_FW(PALEGOLDENROD)
                        OMNI_S2E_FW(PALEGREEN)
                        OMNI_S2E_FW(PALETURQUOISE)
                        OMNI_S2E_FW(PALEVIOLETRED)
                        OMNI_S2E_FW(PAPAYAWHIP)
                        OMNI_S2E_FW(PEACHPUFF)
                        OMNI_S2E_FW(PERU)
                        OMNI_S2E_FW(PINK)
                        OMNI_S2E_FW(PLUM)
                        OMNI_S2E_FW(POWDERBLUE)
                        OMNI_S2E_FW(PURPLE)
                        OMNI_S2E_FW(RED)
                        OMNI_S2E_FW(ROSYBROWN)
                        OMNI_S2E_FW(ROYALBLUE)
                        OMNI_S2E_FW(SADDLEBROWN)
                        OMNI_S2E_FW(SALMON)
                        OMNI_S2E_FW(SANDYBROWN)
                        OMNI_S2E_FW(SEAGREEN)
                        OMNI_S2E_FW(SEASHELL)
                        OMNI_S2E_FW(SIENNA)
                        OMNI_S2E_FW(SILVER)
                        OMNI_S2E_FW(SKYBLUE)
                        OMNI_S2E_FW(SLATEBLUE)
                        OMNI_S2E_FW(SLATEGRAY)
                        OMNI_S2E_FW(SNOW)
                        OMNI_S2E_FW(SPRINGGREEN)
                        OMNI_S2E_FW(STEELBLUE)
                        OMNI_S2E_FW(TAN)
                        OMNI_S2E_FW(TEAL)
                        OMNI_S2E_FW(THISTLE)
                        OMNI_S2E_FW(TOMATO)
                        OMNI_S2E_FW(TURQUOISE)
                        OMNI_S2E_FW(VIOLET)
                        OMNI_S2E_FW(WHEAT)
                        OMNI_S2E_FW(WHITE)
                        OMNI_S2E_FW(WHITESMOKE)
                        OMNI_S2E_FW(YELLOW)
                        OMNI_S2E_FW(YELLOWGREEN)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(ALICEBLUE);
                        OMNI_E2SS_FW(ANTIQUEWHITE);
                        OMNI_E2SS_FW(AQUA);
                        OMNI_E2SS_FW(AQUAMARINE);
                        OMNI_E2SS_FW(AZURE);
                        OMNI_E2SS_FW(BEIGE);
                        OMNI_E2SS_FW(BISQUE);
                        OMNI_E2SS_FW(BLACK);
                        OMNI_E2SS_FW(BLANCHEDALMOND);
                        OMNI_E2SS_FW(BLUE);
                        OMNI_E2SS_FW(BLUEVIOLET);
                        OMNI_E2SS_FW(BROWN);
                        OMNI_E2SS_FW(BURLYWOOD);
                        OMNI_E2SS_FW(CADETBLUE);
                        OMNI_E2SS_FW(CHARTREUSE);
                        OMNI_E2SS_FW(CHOCOLATE);
                        OMNI_E2SS_FW(CORAL);
                        OMNI_E2SS_FW(CORNFLOWERBLUE);
                        OMNI_E2SS_FW(CORNSILK);
                        OMNI_E2SS_FW(CRIMSON);
                        //OMNI_E2SS_FW(CYAN); // same as aqua
                        OMNI_E2SS_FW(DARKBLUE);
                        OMNI_E2SS_FW(DARKCYAN);
                        OMNI_E2SS_FW(DARKGOLDENROD);
                        OMNI_E2SS_FW(DARKGRAY);
                        OMNI_E2SS_FW(DARKGREEN);
                        OMNI_E2SS_FW(DARKKHAKI);
                        OMNI_E2SS_FW(DARKMAGENTA);
                        OMNI_E2SS_FW(DARKOLIVEGREEN);
                        OMNI_E2SS_FW(DARKORANGE);
                        OMNI_E2SS_FW(DARKORCHID);
                        OMNI_E2SS_FW(DARKRED);
                        OMNI_E2SS_FW(DARKSALMON);
                        OMNI_E2SS_FW(DARKSEAGREEN);
                        OMNI_E2SS_FW(DARKSLATEBLUE);
                        OMNI_E2SS_FW(DARKSLATEGRAY);
                        OMNI_E2SS_FW(DARKTURQUOISE);
                        OMNI_E2SS_FW(DARKVIOLET);
                        OMNI_E2SS_FW(DEEPPINK);
                        OMNI_E2SS_FW(DEEPSKYBLUE);
                        OMNI_E2SS_FW(DIMGRAY);
                        OMNI_E2SS_FW(DODGERBLUE);
                        OMNI_E2SS_FW(FIREBRICK);
                        OMNI_E2SS_FW(FLORALWHITE);
                        OMNI_E2SS_FW(FORESTGREEN);
                        OMNI_E2SS_FW(FUCHSIA);
                        OMNI_E2SS_FW(GAINSBORO);
                        OMNI_E2SS_FW(GHOSTWHITE);
                        OMNI_E2SS_FW(GOLD);
                        OMNI_E2SS_FW(GOLDENROD);
                        OMNI_E2SS_FW(GRAY);
                        OMNI_E2SS_FW(GREEN);
                        OMNI_E2SS_FW(GREENYELLOW);
                        OMNI_E2SS_FW(HONEYDEW);
                        OMNI_E2SS_FW(HOTPINK);
                        OMNI_E2SS_FW(INDIANRED);
                        OMNI_E2SS_FW(INDIGO);
                        OMNI_E2SS_FW(IVORY);
                        OMNI_E2SS_FW(KHAKI);
                        OMNI_E2SS_FW(LAVENDER);
                        OMNI_E2SS_FW(LAVENDERBLUSH);
                        OMNI_E2SS_FW(LAWNGREEN);
                        OMNI_E2SS_FW(LEMONCHIFFON);
                        OMNI_E2SS_FW(LIGHTBLUE);
                        OMNI_E2SS_FW(LIGHTCORAL);
                        OMNI_E2SS_FW(LIGHTCYAN);
                        OMNI_E2SS_FW(LIGHTGOLDENRODYELLOW);
                        OMNI_E2SS_FW(LIGHTGRAY);
                        OMNI_E2SS_FW(LIGHTGREEN);
                        OMNI_E2SS_FW(LIGHTPINK);
                        OMNI_E2SS_FW(LIGHTSALMON);
                        OMNI_E2SS_FW(LIGHTSEAGREEN);
                        OMNI_E2SS_FW(LIGHTSKYBLUE);
                        OMNI_E2SS_FW(LIGHTSLATEGRAY);
                        OMNI_E2SS_FW(LIGHTSTEELBLUE);
                        OMNI_E2SS_FW(LIGHTYELLOW);
                        OMNI_E2SS_FW(LIME);
                        OMNI_E2SS_FW(LIMEGREEN);
                        OMNI_E2SS_FW(LINEN);
                        //OMNI_E2SS_FW(MAGENTA); // same as fuchsia
                        OMNI_E2SS_FW(MAROON);
                        OMNI_E2SS_FW(MEDIUMAQUAMARINE);
                        OMNI_E2SS_FW(MEDIUMBLUE);
                        OMNI_E2SS_FW(MEDIUMORCHID);
                        OMNI_E2SS_FW(MEDIUMPURPLE);
                        OMNI_E2SS_FW(MEDIUMSEAGREEN);
                        OMNI_E2SS_FW(MEDIUMSLATEBLUE);
                        OMNI_E2SS_FW(MEDIUMSPRINGGREEN);
                        OMNI_E2SS_FW(MEDIUMTURQUOISE);
                        OMNI_E2SS_FW(MEDIUMVIOLETRED);
                        OMNI_E2SS_FW(MIDNIGHTBLUE);
                        OMNI_E2SS_FW(MINTCREAM);
                        OMNI_E2SS_FW(MISTYROSE);
                        OMNI_E2SS_FW(MOCCASIN);
                        OMNI_E2SS_FW(NAVAJOWHITE);
                        OMNI_E2SS_FW(NAVY);
                        OMNI_E2SS_FW(OLDLACE);
                        OMNI_E2SS_FW(OLIVE);
                        OMNI_E2SS_FW(OLIVEDRAB);
                        OMNI_E2SS_FW(ORANGE);
                        OMNI_E2SS_FW(ORANGERED);
                        OMNI_E2SS_FW(ORCHID);
                        OMNI_E2SS_FW(PALEGOLDENROD);
                        OMNI_E2SS_FW(PALEGREEN);
                        OMNI_E2SS_FW(PALETURQUOISE);
                        OMNI_E2SS_FW(PALEVIOLETRED);
                        OMNI_E2SS_FW(PAPAYAWHIP);
                        OMNI_E2SS_FW(PEACHPUFF);
                        OMNI_E2SS_FW(PERU);
                        OMNI_E2SS_FW(PINK);
                        OMNI_E2SS_FW(PLUM);
                        OMNI_E2SS_FW(POWDERBLUE);
                        OMNI_E2SS_FW(PURPLE);
                        OMNI_E2SS_FW(RED);
                        OMNI_E2SS_FW(ROSYBROWN);
                        OMNI_E2SS_FW(ROYALBLUE);
                        OMNI_E2SS_FW(SADDLEBROWN);
                        OMNI_E2SS_FW(SALMON);
                        OMNI_E2SS_FW(SANDYBROWN);
                        OMNI_E2SS_FW(SEAGREEN);
                        OMNI_E2SS_FW(SEASHELL);
                        OMNI_E2SS_FW(SIENNA);
                        OMNI_E2SS_FW(SILVER);
                        OMNI_E2SS_FW(SKYBLUE);
                        OMNI_E2SS_FW(SLATEBLUE);
                        OMNI_E2SS_FW(SLATEGRAY);
                        OMNI_E2SS_FW(SNOW);
                        OMNI_E2SS_FW(SPRINGGREEN);
                        OMNI_E2SS_FW(STEELBLUE);
                        OMNI_E2SS_FW(TAN);
                        OMNI_E2SS_FW(TEAL);
                        OMNI_E2SS_FW(THISTLE);
                        OMNI_E2SS_FW(TOMATO);
                        OMNI_E2SS_FW(TURQUOISE);
                        OMNI_E2SS_FW(VIOLET);
                        OMNI_E2SS_FW(WHEAT);
                        OMNI_E2SS_FW(WHITE);
                        OMNI_E2SS_FW(WHITESMOKE);
                        OMNI_E2SS_FW(YELLOW);
                        OMNI_E2SS_FW(YELLOWGREEN);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(uint64_t val)
                {
                    return (val == 
                            ALICEBLUE ||
                            ANTIQUEWHITE ||
                            AQUA ||
                            AQUAMARINE ||
                            AZURE ||
                            BEIGE ||
                            BISQUE ||
                            BLACK ||
                            BLANCHEDALMOND ||
                            BLUE ||
                            BLUEVIOLET ||
                            BROWN ||
                            BURLYWOOD ||
                            CADETBLUE ||
                            CHARTREUSE ||
                            CHOCOLATE ||
                            CORAL ||
                            CORNFLOWERBLUE ||
                            CORNSILK ||
                            CRIMSON ||
                            //CYAN || // same as aqua
                            DARKBLUE ||
                            DARKCYAN ||
                            DARKGOLDENROD ||
                            DARKGRAY ||
                            DARKGREEN ||
                            DARKKHAKI ||
                            DARKMAGENTA ||
                            DARKOLIVEGREEN ||
                            DARKORANGE ||
                            DARKORCHID ||
                            DARKRED ||
                            DARKSALMON ||
                            DARKSEAGREEN ||
                            DARKSLATEBLUE ||
                            DARKSLATEGRAY ||
                            DARKTURQUOISE ||
                            DARKVIOLET ||
                            DEEPPINK ||
                            DEEPSKYBLUE ||
                            DIMGRAY ||
                            DODGERBLUE ||
                            FIREBRICK ||
                            FLORALWHITE ||
                            FORESTGREEN ||
                            FUCHSIA ||
                            GAINSBORO ||
                            GHOSTWHITE ||
                            GOLD ||
                            GOLDENROD ||
                            GRAY ||
                            GREEN ||
                            GREENYELLOW ||
                            HONEYDEW ||
                            HOTPINK ||
                            INDIANRED ||
                            INDIGO ||
                            IVORY ||
                            KHAKI ||
                            LAVENDER ||
                            LAVENDERBLUSH ||
                            LAWNGREEN ||
                            LEMONCHIFFON ||
                            LIGHTBLUE ||
                            LIGHTCORAL ||
                            LIGHTCYAN ||
                            LIGHTGOLDENRODYELLOW ||
                            LIGHTGRAY ||
                            LIGHTGREEN ||
                            LIGHTPINK ||
                            LIGHTSALMON ||
                            LIGHTSEAGREEN ||
                            LIGHTSKYBLUE ||
                            LIGHTSLATEGRAY ||
                            LIGHTSTEELBLUE ||
                            LIGHTYELLOW ||
                            LIME ||
                            LIMEGREEN ||
                            LINEN ||
                            //MAGENTA || // same as fuchsia
                            MAROON ||
                            MEDIUMAQUAMARINE ||
                            MEDIUMBLUE ||
                            MEDIUMORCHID ||
                            MEDIUMPURPLE ||
                            MEDIUMSEAGREEN ||
                            MEDIUMSLATEBLUE ||
                            MEDIUMSPRINGGREEN ||
                            MEDIUMTURQUOISE ||
                            MEDIUMVIOLETRED ||
                            MIDNIGHTBLUE ||
                            MINTCREAM ||
                            MISTYROSE ||
                            MOCCASIN ||
                            NAVAJOWHITE ||
                            NAVY ||
                            OLDLACE ||
                            OLIVE ||
                            OLIVEDRAB ||
                            ORANGE ||
                            ORANGERED ||
                            ORCHID ||
                            PALEGOLDENROD ||
                            PALEGREEN ||
                            PALETURQUOISE ||
                            PALEVIOLETRED ||
                            PAPAYAWHIP ||
                            PEACHPUFF ||
                            PERU ||
                            PINK ||
                            PLUM ||
                            POWDERBLUE ||
                            PURPLE ||
                            RED ||
                            ROSYBROWN ||
                            ROYALBLUE ||
                            SADDLEBROWN ||
                            SALMON ||
                            SANDYBROWN ||
                            SEAGREEN ||
                            SEASHELL ||
                            SIENNA ||
                            SILVER ||
                            SKYBLUE ||
                            SLATEBLUE ||
                            SLATEGRAY ||
                            SNOW ||
                            SPRINGGREEN ||
                            STEELBLUE ||
                            TAN ||
                            TEAL ||
                            THISTLE ||
                            TOMATO ||
                            TURQUOISE ||
                            VIOLET ||
                            WHEAT ||
                            WHITE ||
                            WHITESMOKE ||
                            YELLOW ||
                            YELLOWGREEN
                    );
                }
        };
    }
}

#endif // OMNI_KNOWN_COLORS_HPP
