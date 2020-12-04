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
#if !defined(OMNI_ENUM_T_HPP)
#define OMNI_ENUM_T_HPP 1
#include <omni/defs/enum_def.hpp>

#if defined(OMNI_ENUM_INCLUDE_TYPE)
    #define OMNI_ENUM_TYPE_FW(class_name) uint64_t type() const { return omni::type_id<class_name>(); }
#else
    #define OMNI_ENUM_TYPE_FW(class_name) 
#endif

#if defined(OMNI_ENUM_INCLUDE_BITWISE_OPS)
    #define OMNI_ENUM_BITWISE_OPS_FW(class_name) class_name operator|(const class_name& val) { return class_name(static_cast<enum_t>(this->m_val | val.m_val)); } \
        class_name operator|(enum_t val) { return class_name(static_cast<enum_t>(this->m_val | val)); } \
        class_name operator|(int32_t val) { return class_name(static_cast<enum_t>(this->m_val | val)); } \
        class_name& operator|=(const class_name& val) { this->m_val = static_cast<enum_t>(this->m_val | val.m_val); return *this; } \
        class_name& operator|=(enum_t val) { this->m_val = static_cast<enum_t>(this->m_val | val); return *this; } \
        class_name& operator|=(int32_t val) { this->m_val = static_cast<enum_t>(this->m_val | val); return *this; } \
        class_name operator&(const class_name& val) { return class_name(static_cast<enum_t>(this->m_val & val.m_val)); } \
        class_name operator&(enum_t val) { return class_name(static_cast<enum_t>(this->m_val & val)); } \
        class_name operator&(int32_t val) { return class_name(static_cast<enum_t>(this->m_val & val)); } \
        class_name& operator&=(const class_name& val) { this->m_val = static_cast<enum_t>(this->m_val & val.m_val); return *this; } \
        class_name& operator&=(enum_t val) { this->m_val = static_cast<enum_t>(this->m_val & val); return *this; } \
        class_name& operator&=(int32_t val) { this->m_val = static_cast<enum_t>(this->m_val & val); return *this; } \
        class_name& operator++() { this->m_val = static_cast<enum_t>(this->m_val + 1); return *this; } \
        class_name operator++(int dummy) { OMNI_UNUSED(dummy); class_name ret(this->m_val); this->m_val = static_cast<enum_t>(this->m_val + 1); return ret; } \
        class_name& operator--() { this->m_val = static_cast<enum_t>(this->m_val - 1); return *this; } \
        class_name operator--(int dummy) { OMNI_UNUSED(dummy); class_name ret(this->m_val); this->m_val = static_cast<enum_t>(this->m_val - 1); return ret; } \
        class_name operator~() { return class_name(static_cast<enum_t>(~static_cast<int32_t>(this->m_val))); } \
        class_name operator^(const class_name& val) { return class_name(static_cast<enum_t>(this->m_val ^ val.m_val)); } \
        class_name operator^(enum_t val) { return class_name(static_cast<enum_t>(this->m_val ^ val)); } \
        class_name operator^(int32_t val) { return class_name(static_cast<enum_t>(this->m_val ^ val)); } \
        class_name& operator^=(const class_name& val) { this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val); return *this; } \
        class_name& operator^=(enum_t val) { this->m_val = static_cast<enum_t>(this->m_val ^ val); return *this; } \
        class_name& operator^=(int32_t val) { this->m_val = static_cast<enum_t>(this->m_val ^ val); return *this; } \
        class_name operator<<(const class_name& val) { return class_name(static_cast<enum_t>(this->m_val << val.m_val)); } \
        class_name operator<<(enum_t val) { return class_name(static_cast<enum_t>(this->m_val << val)); } \
        class_name operator<<(int32_t val) { return class_name(static_cast<enum_t>(this->m_val << val)); } \
        class_name& operator<<=(const class_name& val) { this->m_val = static_cast<enum_t>(this->m_val << val.m_val); return *this; } \
        class_name& operator<<=(enum_t val) { this->m_val = static_cast<enum_t>(this->m_val << val); return *this; } \
        class_name& operator<<=(int32_t val) { this->m_val = static_cast<enum_t>(this->m_val << val); return *this; } \
        class_name operator>>(const class_name& val) { return class_name(static_cast<enum_t>(this->m_val >> val.m_val)); } \
        class_name operator>>(enum_t val) { return class_name(static_cast<enum_t>(this->m_val >> val)); } \
        class_name operator>>(int32_t val) { return class_name(static_cast<enum_t>(this->m_val >> val)); } \
        class_name& operator>>=(const class_name& val) { this->m_val = static_cast<enum_t>(this->m_val >> val.m_val); return *this; } \
        class_name& operator>>=(enum_t val) { this->m_val = static_cast<enum_t>(this->m_val >> val); return *this; } \
        class_name& operator>>=(int32_t val) { this->m_val = static_cast<enum_t>(this->m_val >> val); return *this; }
#else
    #define OMNI_ENUM_BITWISE_OPS_FW(class_name)
#endif

#define OMNI_ENUM_ASSIGNED(class_name, ...) class class_name { \
    private: \
        template < typename S > static bool _try_parse(const S& val, class_name& out) { enum_t tmp; if (_try_parse(val, tmp)) { out.m_val = tmp; return true; } return false; } \
    public: \
        typedef enum enum_t { __VA_ARGS__ } enum_t; \
        static inline unsigned short COUNT() { return OMNI_EXPAND_FW( OMNI_MACRO_ARG_COUNT( __VA_ARGS__ ) ) ; } \
        class_name() : m_val(DEFAULT_VALUE()) { } \
        class_name(const class_name& cp) : m_val(cp.m_val) { } \
        class_name(enum_t val) : m_val(val) { } \
        ~class_name() { } \
        static bool try_parse(const std::string& val, class_name& out) { return _try_parse(val, out); } \
        static bool try_parse(const std::wstring& val, class_name& out) { return _try_parse(val, out); } \
        bool operator!=(const class_name& val) const { return !(*this == val); } \
        class_name& operator=(const class_name& val) { if (this != &val) { this->m_val = val.m_val; } return *this; } \
        class_name& operator=(enum_t val) { this->m_val = val; return *this; } \
        class_name& operator=(int32_t val) { if (!class_name::is_valid(val)) { OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val)); } else { this->m_val = static_cast<enum_t>(val); } return *this; } \
        OMNI_ENUM_BITWISE_OPS_FW(class_name) \
        bool operator<(const class_name& val) const { return this->m_val < val.m_val; } \
        bool operator>(const class_name& val) const { return this->m_val > val.m_val; } \
        bool operator==(const class_name& val) const { if (this == &val) { return true; } return this->m_val == val.m_val; } \
        static std::string to_string(enum_t v) { return _to_val<std::stringstream>(v); } \
        static std::wstring to_wstring(enum_t v) { return _to_val<std::wstringstream>(v); } \
        static enum_t parse(const std::string& val) { return _parse(val); } \
        static enum_t parse(const std::wstring& val) { return _parse(val); } \
        static bool try_parse(const std::string& val, enum_t& out) { return _try_parse(val, out); } \
        static bool try_parse(const std::wstring& val, enum_t& out) { return _try_parse(val, out); } \
        static bool is_valid(int32_t val) { return _valid(val); } \
        unsigned short count() const { return COUNT(); } \
        enum_t value() const { return this->m_val; } \
        std::string to_string() const { return to_string(this->m_val); } \
        std::wstring to_wstring() const { return to_wstring(this->m_val); } \
        bool operator!=(enum_t val) const { return (this->m_val != val); } \
        bool operator<(enum_t val) const { return this->m_val < val; } \
        bool operator<(int32_t val) const { return this->m_val < static_cast<enum_t>(val); } \
        bool operator>(enum_t val) const { return this->m_val > val; } \
        bool operator>(int32_t val) const { return this->m_val > val; } \
        bool operator==(enum_t val) const { return this->m_val == val; } \
        bool operator==(int32_t val) const { return this->m_val == val; } \
        operator enum_t() const { return this->m_val; } \
        operator std::string() const { return this->to_string(); } \
        operator std::wstring() const { return this->to_wstring(); } \
        uint64_t hash() const { return reinterpret_cast<uint64_t>(this); } \
        friend std::ostream& operator<<(std::ostream& s, const enum_t& c) { s << to_string(c); return s; } \
        friend std::wostream& operator<<(std::wostream& s, const enum_t& c) { s << to_wstring(c); return s; } \
        OMNI_OSTREAM_FW(class_name) \
        OMNI_ENUM_TYPE_FW(class_name)

#define OMNI_ENUM_ASSIGNED_PARSERS(...) private: \
    enum_t m_val; \
    template < typename S > static enum_t _parse(const S& val) { enum_t ret; if (_try_parse(val, ret)) { return ret; } OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum()) return DEFAULT_VALUE(); } \
    template < typename S > static bool _try_parse(const S& str, enum_t& out) { return _try_parse(omni::string::util::to_upper(str), out); } \
    static bool _try_parse(const std::wstring& val, enum_t& out) { return _try_parse(omni::string::util::to_string(val), out); } \
    static bool _try_parse(const std::string& val, enum_t& out) { if (!val.empty()) { \
        OMNI_EXPAND_FW( OMNI_EN_S2E_FW(__VA_ARGS__) ) \
    } return false; } \
    template < typename S > static std::basic_string< typename S::char_type > _to_val(enum_t v) { S ss; switch (v) { \
        OMNI_EXPAND_FW( OMNI_EN_E2SS_FW(__VA_ARGS__) ) \
    default: ss << "UNKNOWN (" << static_cast<int>(v) << ")"; break; } return ss.str(); } \
    static bool _valid(int32_t val) { return (val ==  \
        OMNI_EXPAND_FW( OMNI_EN_OR_FW(__VA_ARGS__) ) \
    ); }

#define OMNI_ENUM_END };

#define OMNI_ENUM_DEFAULT(default_val) public: static inline enum_t DEFAULT_VALUE() { return default_val; }

#define OMNI_ENUM_DEFINE(class_name, ...) \
    OMNI_EXPAND_FW( OMNI_ENUM_ASSIGNED(class_name, __VA_ARGS__ ) ) \
    OMNI_EXPAND_FW( OMNI_ENUM_ASSIGNED_PARSERS( __VA_ARGS__ ) )

#define OMNI_ENUM(class_name, default_val, ...) \
    OMNI_EXPAND_FW( OMNI_ENUM_ASSIGNED(class_name, __VA_ARGS__ ) ) \
    OMNI_EXPAND_FW( OMNI_ENUM_DEFAULT(default_val) ) \
    OMNI_EXPAND_FW( OMNI_ENUM_ASSIGNED_PARSERS( __VA_ARGS__ ) ) \
    OMNI_ENUM_END

#endif // OMNI_ENUM_T_HPP
