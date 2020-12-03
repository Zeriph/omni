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
#if !defined(OMNI_FSTREAM_T_HPP)
#define OMNI_FSTREAM_T_HPP 1
#include <omni/defs/global.hpp>
#include <fstream>

#if defined(OMNI_UNICODE)
    #define OMNI_OFSTREAM_T std::wofstream
    #define OMNI_IFSTREAM_T std::wifstream
    #define OMNI_FSTREAM_T std::wfstream
#else
    #define OMNI_OFSTREAM_T std::ofstream
    #define OMNI_IFSTREAM_T std::ifstream
    #define OMNI_FSTREAM_T std::fstream
#endif

namespace omni {
    namespace io {
        /**
         * Defines the underlying std::ofstream type;
         * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
         */
        typedef OMNI_OFSTREAM_T ofstream_t;
        /**
         * Defines the underlying std::ifstream type;
         * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
         */
        typedef OMNI_IFSTREAM_T ifstream_t;
        /**
         * Defines the underlying std::fstream type;
         * if OMNI_UNICODE is defined the underlying stream will be a wide stream type
         */
        typedef OMNI_FSTREAM_T fstream_t;

        class options
        {
            public:
                typedef enum enum_t {
                    // No I/O options
                    NONE = 0,
                    // Overwrite the existing path
                    OVERWRITE = 1,
                    // Create the new path
                    CREATE_PATH = 2
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return NONE;
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
                static bool try_parse(const std::string& val, options& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, options& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                options() :
                    OMNI_CTOR_FW(omni::io::options)
                    m_val(DEFAULT_VALUE())
                { }

                options(const options& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                options(enum_t val) : 
                    OMNI_CTOR_FW(omni::io::options)
                    m_val(val)
                { }

                options(int32_t val) : 
                    OMNI_CTOR_FW(omni::io::options)
                    m_val(static_cast<enum_t>(val))
                { }

                ~options()
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

                bool operator!=(const options& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                options& operator=(const options& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                options& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                options& operator=(int32_t val)
                {
                    if (!options::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                options operator|(const options& val)
                {
                    return options(static_cast<enum_t>(this->m_val | val.m_val));
                }

                options operator|(enum_t val)
                {
                    return options(static_cast<enum_t>(this->m_val | val));
                }

                options operator|(int32_t val)
                {
                    return options(static_cast<enum_t>(this->m_val | val));
                }

                options& operator|=(const options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                options& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                options& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                options operator&(const options& val)
                {
                    return options(static_cast<enum_t>(this->m_val & val.m_val));
                }

                options operator&(enum_t val)
                {
                    return options(static_cast<enum_t>(this->m_val & val));
                }

                options operator&(int32_t val)
                {
                    return options(static_cast<enum_t>(this->m_val & val));
                }

                options& operator&=(const options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                options& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                options& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                options& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                options operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    options ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                options& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                options operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    options ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                options operator~()
                {
                    return options(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                options operator^(const options& val)
                {
                    return options(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                options operator^(enum_t val)
                {
                    return options(static_cast<enum_t>(this->m_val ^ val));
                }

                options operator^(int32_t val)
                {
                    return options(static_cast<enum_t>(this->m_val ^ val));
                }

                options& operator^=(const options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                options& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                options& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                options operator<<(const options& val)
                {
                    return options(static_cast<enum_t>(this->m_val << val.m_val));
                }

                options operator<<(enum_t val)
                {
                    return options(static_cast<enum_t>(this->m_val << val));
                }

                options operator<<(int32_t val)
                {
                    return options(static_cast<enum_t>(this->m_val << val));
                }

                options& operator<<=(const options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                options& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                options& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                options operator>>(const options& val)
                {
                    return options(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                options operator>>(enum_t val)
                {
                    return options(static_cast<enum_t>(this->m_val >> val));
                }

                options operator>>(int32_t val)
                {
                    return options(static_cast<enum_t>(this->m_val >> val));
                }

                options& operator>>=(const options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                options& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                options& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const options& val) const
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

                bool operator>(const options& val) const
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

                bool operator==(const options& val) const
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

                OMNI_MEMBERS_FW(omni::io::options) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::io::options)
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
                static bool _try_parse(const S& val, options& out)
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
                        OMNI_S2E_FW(NONE)
                        OMNI_S2E_FW(OVERWRITE)
                        OMNI_S2E_FW(CREATE_PATH)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(OVERWRITE);
                        OMNI_E2SS_FW(CREATE_PATH);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        NONE ||
                        OVERWRITE ||
                        CREATE_PATH
                    );
                }
        };
    }
}

#endif // OMNI_FSTREAM_T_HPP
