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
#if !defined(OMNI_SYSTEM_HPP)
#define OMNI_SYSTEM_HPP
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/strings.hpp>

namespace omni {
    namespace system {
        class architecture_type
        {
            public:
                typedef enum enum_t {
                    // Unknown architecture type
                    UNKNOWN = 0,
                    // AMD64
                    AMD64,
                    // ARM
                    ARM,
                    // ARM64
                    ARM64,
                    // Blackfin
                    BLACKFIN,
                    // Convex
                    CONVEX,
                    // DEC-Alpha
                    DEC_ALPHA,
                    // Elbrus
                    ELBRUS,
                    // Epiphany
                    EPIPHANY,
                    // HP/PA RISC
                    HPPA_RISC,
                    // Intel x80
                    INTEL_X80,
                    // Intel x86
                    INTEL_X86,
                    // Intel Itanium (IA-64)
                    INTEL_IA64,
                    // LoongArch
                    LOONGARCH,
                    // Motorola 68k
                    MOTOROLA_68K,
                    // MIPS
                    MIPS,
                    // NEC
                    NEC,
                    // PNaCl
                    PNACL,
                    // PowerPC
                    POWER_PC,
                    // Pyramid 9810
                    PYRAMID_9810,
                    // RISC-V
                    RISC_V,
                    // RS/6000
                    RS6000,
                    // SPARC
                    SPARC,
                    // SuperH
                    SUPER_H,
                    // SystemZ
                    SYSTEM_Z,
                    // TMS320
                    TMS320,
                    // TMS470
                    TMS470
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 27;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return UNKNOWN;
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

                static bool try_parse(const std::string& val, architecture_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, architecture_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                architecture_type() :
                    OMNI_CTOR_FW(omni::sync::architecture_type)
                    m_val(DEFAULT_VALUE())
                { }

                architecture_type(const architecture_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                architecture_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::architecture_type)
                    m_val(val)
                { }

                ~architecture_type()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }
                
                unsigned short count()
                {
                    return COUNT();
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

                bool operator!=(const architecture_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                architecture_type& operator=(const architecture_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                architecture_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                architecture_type& operator=(int32_t val)
                {
                    if (!architecture_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const architecture_type& val) const
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

                bool operator>(const architecture_type& val) const
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

                bool operator==(const architecture_type& val) const
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

                OMNI_MEMBERS_FW(omni::system::architecture_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::system::architecture_type)
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
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, architecture_type& out)
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
                        OMNI_S2E_FW(UNKNOWN)
                        OMNI_S2E_FW(DEC_ALPHA)
                        OMNI_S2E_FW(AMD64)
                        OMNI_S2E_FW(ARM)
                        OMNI_S2E_FW(ARM64)
                        OMNI_S2E_FW(BLACKFIN)
                        OMNI_S2E_FW(CONVEX)
                        OMNI_S2E_FW(ELBRUS)
                        OMNI_S2E_FW(EPIPHANY)
                        OMNI_S2E_FW(HPPA_RISC)
                        OMNI_S2E_FW(INTEL_X80)
                        OMNI_S2E_FW(INTEL_X86)
                        OMNI_S2E_FW(INTEL_IA64)
                        OMNI_S2E_FW(MOTOROLA_68K)
                        OMNI_S2E_FW(MIPS)
                        OMNI_S2E_FW(NEC)
                        OMNI_S2E_FW(PNACL)
                        OMNI_S2E_FW(POWER_PC)
                        OMNI_S2E_FW(PYRAMID_9810)
                        OMNI_S2E_FW(RISC_V)
                        OMNI_S2E_FW(RS6000)
                        OMNI_S2E_FW(SPARC)
                        OMNI_S2E_FW(SUPER_H)
                        OMNI_S2E_FW(SYSTEM_Z)
                        OMNI_S2E_FW(TMS320)
                        OMNI_S2E_FW(TMS470)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(DEC_ALPHA);
                        OMNI_E2SS_FW(AMD64);
                        OMNI_E2SS_FW(ARM);
                        OMNI_E2SS_FW(ARM64);
                        OMNI_E2SS_FW(BLACKFIN);
                        OMNI_E2SS_FW(CONVEX);
                        OMNI_E2SS_FW(ELBRUS);
                        OMNI_E2SS_FW(EPIPHANY);
                        OMNI_E2SS_FW(HPPA_RISC);
                        OMNI_E2SS_FW(INTEL_X80);
                        OMNI_E2SS_FW(INTEL_X86);
                        OMNI_E2SS_FW(INTEL_IA64);
                        OMNI_E2SS_FW(LOONGARCH);
                        OMNI_E2SS_FW(MOTOROLA_68K);
                        OMNI_E2SS_FW(MIPS);
                        OMNI_E2SS_FW(NEC);
                        OMNI_E2SS_FW(PNACL);
                        OMNI_E2SS_FW(POWER_PC);
                        OMNI_E2SS_FW(PYRAMID_9810);
                        OMNI_E2SS_FW(RISC_V);
                        OMNI_E2SS_FW(RS6000);
                        OMNI_E2SS_FW(SPARC);
                        OMNI_E2SS_FW(SUPER_H);
                        OMNI_E2SS_FW(SYSTEM_Z);
                        OMNI_E2SS_FW(TMS320);
                        OMNI_E2SS_FW(TMS470);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(UNKNOWN) ||
                        OMNI_I2EV_FW(DEC_ALPHA) ||
                        OMNI_I2EV_FW(AMD64) ||
                        OMNI_I2EV_FW(ARM) ||
                        OMNI_I2EV_FW(ARM64) ||
                        OMNI_I2EV_FW(BLACKFIN) ||
                        OMNI_I2EV_FW(CONVEX) ||
                        OMNI_I2EV_FW(ELBRUS) ||
                        OMNI_I2EV_FW(EPIPHANY) ||
                        OMNI_I2EV_FW(HPPA_RISC) ||
                        OMNI_I2EV_FW(INTEL_X80) ||
                        OMNI_I2EV_FW(INTEL_X86 )||
                        OMNI_I2EV_FW(INTEL_IA64) ||
                        OMNI_I2EV_FW(LOONGARCH) ||
                        OMNI_I2EV_FW(MOTOROLA_68K) ||
                        OMNI_I2EV_FW(MIPS) ||
                        OMNI_I2EV_FW(NEC) ||
                        OMNI_I2EV_FW(PNACL) ||
                        OMNI_I2EV_FW(POWER_PC) ||
                        OMNI_I2EV_FW(PYRAMID_9810) ||
                        OMNI_I2EV_FW(RISC_V) ||
                        OMNI_I2EV_FW(RS6000) ||
                        OMNI_I2EV_FW(SPARC) ||
                        OMNI_I2EV_FW(SUPER_H) ||
                        OMNI_I2EV_FW(SYSTEM_Z) ||
                        OMNI_I2EV_FW(TMS320) ||
                        OMNI_I2EV_FW(TMS470)
                    );
                }
        };

        class endian_type
        {
            public:
                typedef enum enum_t {
                    UNKNOWN,
                    BIG,
                    LITTLE,
                    BIG_WORD,
                    LITTLE_WORD
                } enum_t;

                static inline unsigned short COUNT()
                {
                    return 5;
                }

                static inline enum_t DEFAULT_VALUE()
                {
                    return UNKNOWN;
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

                static bool try_parse(const std::string& val, endian_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool try_parse(const std::wstring& val, endian_type& out)
                {
                    return _try_parse(val, out);
                }

                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                endian_type() :
                    OMNI_CTOR_FW(omni::sync::endian_type)
                    m_val(DEFAULT_VALUE())
                { }

                endian_type(const endian_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                endian_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::sync::endian_type)
                    m_val(val)
                { }

                ~endian_type()
                {
                    OMNI_TRY_FW
                    OMNI_DTOR_FW
                    OMNI_CATCH_FW
                    OMNI_D5_FW("destroyed");
                }
                
                unsigned short count()
                {
                    return COUNT();
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

                bool operator!=(const endian_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                endian_type& operator=(const endian_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                endian_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                endian_type& operator=(int32_t val)
                {
                    if (!endian_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const endian_type& val) const
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

                bool operator>(const endian_type& val) const
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

                bool operator==(const endian_type& val) const
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

                OMNI_MEMBERS_FW(omni::system::endian_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::system::endian_type)
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
                    return _try_parse(omni::string::util::to_upper(str), out);
                }

                template < typename S >
                static bool _try_parse(const S& val, endian_type& out)
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
                        OMNI_S2E_FW(UNKNOWN)
                        OMNI_S2E_FW(BIG)
                        OMNI_S2E_FW(LITTLE)
                        OMNI_S2E_FW(BIG_WORD)
                        OMNI_S2E_FW(LITTLE_WORD)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(BIG);
                        OMNI_E2SS_FW(LITTLE);
                        OMNI_E2SS_FW(BIG_WORD);
                        OMNI_E2SS_FW(LITTLE_WORD);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (
                        OMNI_I2EV_FW(UNKNOWN) ||
                        OMNI_I2EV_FW(BIG) ||
                        OMNI_I2EV_FW(LITTLE) ||
                        OMNI_I2EV_FW(BIG_WORD) ||
                        OMNI_I2EV_FW(LITTLE_WORD)
                    );
                }
        };

        omni::system::endian_type endianness();
        omni::system::architecture_type architecture();
        int32_t last_error();
        std::string last_error_str();

        #if defined(OMNI_NON_PORTABLE)
            omni::string_t cwd();
            std::string error_str(int code);
            omni::string_t path();
            uint64_t processors();
            std::string signal_str(int sig);
        #endif
    }
}

#endif // OMNI_SYSTEM_HPP
