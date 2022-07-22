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
#if !defined(OMNI_NET_T_HPP)
#define OMNI_NET_T_HPP
#include <omni/defs/global.hpp>
#include <omni/defs/class_macros.hpp>
#include <omni/defs/net_def.hpp>
#include <omni/bits.hpp>
#include <omni/stack_buffer.hpp>

/*
    DEV_NOTE: There are numerous socket functions that are standard, while there are also numerous socket functions
    that are OS/implementation specific. Since there are _too_ many variations on what a socket can do, as well as
    what a socket _might_ be able to do, there are various enum types for the `net` namespace that do not have what
    could potentially be all types. Instead, the user can simply utilize the values they need for the platform they
    are targetting.
*/

namespace omni {
    /** The net namespace is used to facilitate certain networking operations and handling */
    namespace net {
        /** address_family defines enum values for the addressing scheme that an instance of the omni::net::socket class can use. */
        class address_family
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = AF_UNSPEC,
                    UNIX = AF_UNIX,
                    INET = AF_INET,
                    INET6 = AF_INET6,
                    SNA = AF_SNA,
                    DECNET = AF_DECnet,
                    APPLETALK = AF_APPLETALK
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 7;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, address_family& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, address_family& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                address_family() :
                    OMNI_CTOR_FW(omni::net::address_family)
                    m_val(DEFAULT_VALUE())
                { }

                address_family(const address_family& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                address_family(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::address_family)
                    m_val(val)
                { }

                ~address_family()
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

                bool operator!=(const address_family& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                address_family& operator=(const address_family& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                address_family& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                address_family& operator=(int32_t val)
                {
                    if (!address_family::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                address_family operator|(const address_family& val)
                {
                    return address_family(static_cast<enum_t>(this->m_val | val.m_val));
                }

                address_family operator|(enum_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val | val));
                }

                address_family operator|(int32_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val | val));
                }

                address_family& operator|=(const address_family& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                address_family& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                address_family& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                address_family operator&(const address_family& val)
                {
                    return address_family(static_cast<enum_t>(this->m_val & val.m_val));
                }

                address_family operator&(enum_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val & val));
                }

                address_family operator&(int32_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val & val));
                }

                address_family& operator&=(const address_family& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                address_family& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                address_family& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                address_family& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                address_family operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    address_family ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                address_family& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                address_family operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    address_family ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                address_family operator~()
                {
                    return address_family(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                address_family operator^(const address_family& val)
                {
                    return address_family(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                address_family operator^(enum_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val ^ val));
                }

                address_family operator^(int32_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val ^ val));
                }

                address_family& operator^=(const address_family& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                address_family& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                address_family& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                address_family operator<<(const address_family& val)
                {
                    return address_family(static_cast<enum_t>(this->m_val << val.m_val));
                }

                address_family operator<<(enum_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val << val));
                }

                address_family operator<<(int32_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val << val));
                }

                address_family& operator<<=(const address_family& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                address_family& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                address_family& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                address_family operator>>(const address_family& val)
                {
                    return address_family(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                address_family operator>>(enum_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val >> val));
                }

                address_family operator>>(int32_t val)
                {
                    return address_family(static_cast<enum_t>(this->m_val >> val));
                }

                address_family& operator>>=(const address_family& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                address_family& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                address_family& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const address_family& val) const
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

                bool operator>(const address_family& val) const
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

                bool operator==(const address_family& val) const
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

                OMNI_MEMBERS_FW(omni::net::address_family) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::net::address_family)
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
                static bool _try_parse(const S& val, address_family& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(UNIX)
                        OMNI_S2E_FW(INET)
                        OMNI_S2E_FW(INET6)
                        OMNI_S2E_FW(SNA)
                        OMNI_S2E_FW(DECNET)
                        OMNI_S2E_FW(APPLETALK)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(UNIX);
                        OMNI_E2SS_FW(INET);
                        OMNI_E2SS_FW(INET6);
                        OMNI_E2SS_FW(SNA);
                        OMNI_E2SS_FW(DECNET);
                        OMNI_E2SS_FW(APPLETALK);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        UNIX ||
                        INET ||
                        INET6 ||
                        SNA ||
                        DECNET ||
                        APPLETALK
                    );
                }
        };

        /** connection_option defines enum values for the type of socket that an instance of the omni::net::socket::socket class represents. */
        class connection_option
        {
            public:
                typedef enum enum_t {
                    CONNECTED,
                    BOUND,
                    OPEN,
                    SHUT,
                    LISTEN
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 5;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return CONNECTED;
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
                static bool try_parse(const std::string& val, connection_option& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, connection_option& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                connection_option() :
                    OMNI_CTOR_FW(omni::net::connection_option)
                    m_val(DEFAULT_VALUE())
                { }

                connection_option(const connection_option& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                connection_option(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::connection_option)
                    m_val(val)
                { }

                ~connection_option()
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

                bool operator!=(const connection_option& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                connection_option& operator=(const connection_option& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                connection_option& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                connection_option& operator=(int32_t val)
                {
                    if (!connection_option::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const connection_option& val) const
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

                bool operator>(const connection_option& val) const
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

                bool operator==(const connection_option& val) const
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

                OMNI_MEMBERS_FW(omni::net::connection_option) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::connection_option)
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
                static bool _try_parse(const S& val, connection_option& out)
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
                        OMNI_S2E_FW(CONNECTED)
                        OMNI_S2E_FW(BOUND)
                        OMNI_S2E_FW(OPEN)
                        OMNI_S2E_FW(SHUT)
                        OMNI_S2E_FW(LISTEN)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(CONNECTED);
                        OMNI_E2SS_FW(BOUND);
                        OMNI_E2SS_FW(OPEN);
                        OMNI_E2SS_FW(SHUT);
                        OMNI_E2SS_FW(LISTEN);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        CONNECTED ||
                        BOUND ||
                        OPEN ||
                        SHUT ||
                        LISTEN
                    );
                }
        };
        
        /** protocol_type defines enum values for the protocols that the omni::net::socket class supports. */
        class protocol_type
        {
            public:
                typedef enum enum_t {
                    UNKNOWN = -1,
                    IP = IPPROTO_IP,
                    ICMP = IPPROTO_ICMP,
                    IGMP = IPPROTO_IGMP,
                    EGP = IPPROTO_EGP,
                    TCP = IPPROTO_TCP,
                    PUP = IPPROTO_PUP,
                    UDP = IPPROTO_UDP,
                    IDP = IPPROTO_IDP,
                    IPV6 = IPPROTO_IPV6,
                    ICMPV6 = IPPROTO_ICMPV6,
                    RAW = IPPROTO_RAW
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 13;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return IP;
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
                static bool try_parse(const std::string& val, protocol_type& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, protocol_type& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                protocol_type() :
                    OMNI_CTOR_FW(omni::net::protocol_type)
                    m_val(DEFAULT_VALUE())
                { }

                protocol_type(const protocol_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                protocol_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::protocol_type)
                    m_val(val)
                { }

                ~protocol_type()
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

                bool operator!=(const protocol_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                protocol_type& operator=(const protocol_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                protocol_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                protocol_type& operator=(int32_t val)
                {
                    if (!protocol_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                protocol_type operator|(const protocol_type& val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val | val.m_val));
                }

                protocol_type operator|(enum_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val | val));
                }

                protocol_type operator|(int32_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val | val));
                }

                protocol_type& operator|=(const protocol_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                protocol_type& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                protocol_type& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                protocol_type operator&(const protocol_type& val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val & val.m_val));
                }

                protocol_type operator&(enum_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val & val));
                }

                protocol_type operator&(int32_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val & val));
                }

                protocol_type& operator&=(const protocol_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                protocol_type& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                protocol_type& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                protocol_type& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                protocol_type operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    protocol_type ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                protocol_type& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                protocol_type operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    protocol_type ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                protocol_type operator~()
                {
                    return protocol_type(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                protocol_type operator^(const protocol_type& val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                protocol_type operator^(enum_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val ^ val));
                }

                protocol_type operator^(int32_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val ^ val));
                }

                protocol_type& operator^=(const protocol_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                protocol_type& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                protocol_type& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                protocol_type operator<<(const protocol_type& val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val << val.m_val));
                }

                protocol_type operator<<(enum_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val << val));
                }

                protocol_type operator<<(int32_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val << val));
                }

                protocol_type& operator<<=(const protocol_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                protocol_type& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                protocol_type& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                protocol_type operator>>(const protocol_type& val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                protocol_type operator>>(enum_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val >> val));
                }

                protocol_type operator>>(int32_t val)
                {
                    return protocol_type(static_cast<enum_t>(this->m_val >> val));
                }

                protocol_type& operator>>=(const protocol_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                protocol_type& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                protocol_type& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const protocol_type& val) const
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

                bool operator>(const protocol_type& val) const
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

                bool operator==(const protocol_type& val) const
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

                OMNI_MEMBERS_FW(omni::net::protocol_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::protocol_type)
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
                static bool _try_parse(const S& val, protocol_type& out)
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
                        OMNI_S2E_FW(IP)
                        OMNI_S2E_FW(ICMP)
                        OMNI_S2E_FW(IGMP)
                        OMNI_S2E_FW(EGP)
                        OMNI_S2E_FW(TCP)
                        OMNI_S2E_FW(PUP)
                        OMNI_S2E_FW(UDP)
                        OMNI_S2E_FW(IDP)
                        OMNI_S2E_FW(IPV6)
                        OMNI_S2E_FW(ICMPV6)
                        OMNI_S2E_FW(RAW)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(IP);
                        OMNI_E2SS_FW(ICMP);
                        OMNI_E2SS_FW(IGMP);
                        OMNI_E2SS_FW(EGP);
                        OMNI_E2SS_FW(TCP);
                        OMNI_E2SS_FW(PUP);
                        OMNI_E2SS_FW(UDP);
                        OMNI_E2SS_FW(IDP);
                        OMNI_E2SS_FW(IPV6);
                        OMNI_E2SS_FW(ICMPV6);
                        OMNI_E2SS_FW(RAW);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNKNOWN ||
                        IP ||
                        ICMP ||
                        IGMP ||
                        EGP ||
                        TCP ||
                        PUP ||
                        UDP ||
                        IDP ||
                        IPV6 ||
                        ICMPV6 ||
                        RAW
                    );
                }
        };

        /** server_error defines enum values for socket errors codes */
        class server_error
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    SUCCESS = 0,
                    HOST_ADDRESS_REQUIRED,
                    NO_ADDRESSES_IN_FAMILY,
                    NAME_SERVER_TEMPORARY_FAILURE,
                    INVALID_FLAGS,
                    NAME_SERVER_PERMANENT_FAILURE,
                    ADDRESS_FAMILY_NOT_SUPPORTED,
                    OUT_OF_MEMORY,
                    HOST_EXISTS_NO_ADDRESSES_DEFINED,
                    NODE_OR_SERVICE_NOT_KNOWN,
                    SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE,
                    SOCKET_TYPE_NOT_SUPPORTED,
                    SYSTEM_ERROR
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 13;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, server_error& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, server_error& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                server_error() :
                    OMNI_CTOR_FW(omni::net::server_error)
                    m_val(DEFAULT_VALUE())
                { }

                server_error(const server_error& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                server_error(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::server_error)
                    m_val(val)
                { }

                ~server_error()
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

                bool operator!=(const server_error& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                server_error& operator=(const server_error& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                server_error& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                server_error& operator=(int32_t val)
                {
                    if (!server_error::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                server_error operator|(const server_error& val)
                {
                    return server_error(static_cast<enum_t>(this->m_val | val.m_val));
                }

                server_error operator|(enum_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val | val));
                }

                server_error operator|(int32_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val | val));
                }

                server_error& operator|=(const server_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                server_error& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                server_error& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                server_error operator&(const server_error& val)
                {
                    return server_error(static_cast<enum_t>(this->m_val & val.m_val));
                }

                server_error operator&(enum_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val & val));
                }

                server_error operator&(int32_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val & val));
                }

                server_error& operator&=(const server_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                server_error& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                server_error& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                server_error& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                server_error operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    server_error ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                server_error& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                server_error operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    server_error ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                server_error operator~()
                {
                    return server_error(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                server_error operator^(const server_error& val)
                {
                    return server_error(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                server_error operator^(enum_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val ^ val));
                }

                server_error operator^(int32_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val ^ val));
                }

                server_error& operator^=(const server_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                server_error& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                server_error& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                server_error operator<<(const server_error& val)
                {
                    return server_error(static_cast<enum_t>(this->m_val << val.m_val));
                }

                server_error operator<<(enum_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val << val));
                }

                server_error operator<<(int32_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val << val));
                }

                server_error& operator<<=(const server_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                server_error& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                server_error& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                server_error operator>>(const server_error& val)
                {
                    return server_error(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                server_error operator>>(enum_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val >> val));
                }

                server_error operator>>(int32_t val)
                {
                    return server_error(static_cast<enum_t>(this->m_val >> val));
                }

                server_error& operator>>=(const server_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                server_error& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                server_error& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const server_error& val) const
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

                bool operator>(const server_error& val) const
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

                bool operator==(const server_error& val) const
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

                OMNI_MEMBERS_FW(omni::net::server_error) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::server_error)
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
                static bool _try_parse(const S& val, server_error& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(SUCCESS)
                        OMNI_S2E_FW(HOST_ADDRESS_REQUIRED)
                        OMNI_S2E_FW(NO_ADDRESSES_IN_FAMILY)
                        OMNI_S2E_FW(NAME_SERVER_TEMPORARY_FAILURE)
                        OMNI_S2E_FW(INVALID_FLAGS)
                        OMNI_S2E_FW(NAME_SERVER_PERMANENT_FAILURE)
                        OMNI_S2E_FW(ADDRESS_FAMILY_NOT_SUPPORTED)
                        OMNI_S2E_FW(OUT_OF_MEMORY)
                        OMNI_S2E_FW(HOST_EXISTS_NO_ADDRESSES_DEFINED)
                        OMNI_S2E_FW(NODE_OR_SERVICE_NOT_KNOWN)
                        OMNI_S2E_FW(SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE)
                        OMNI_S2E_FW(SOCKET_TYPE_NOT_SUPPORTED)
                        OMNI_S2E_FW(SYSTEM_ERROR)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(SUCCESS);
                        OMNI_E2SS_FW(HOST_ADDRESS_REQUIRED);
                        OMNI_E2SS_FW(NO_ADDRESSES_IN_FAMILY);
                        OMNI_E2SS_FW(NAME_SERVER_TEMPORARY_FAILURE);
                        OMNI_E2SS_FW(INVALID_FLAGS);
                        OMNI_E2SS_FW(NAME_SERVER_PERMANENT_FAILURE);
                        OMNI_E2SS_FW(ADDRESS_FAMILY_NOT_SUPPORTED);
                        OMNI_E2SS_FW(OUT_OF_MEMORY);
                        OMNI_E2SS_FW(HOST_EXISTS_NO_ADDRESSES_DEFINED);
                        OMNI_E2SS_FW(NODE_OR_SERVICE_NOT_KNOWN);
                        OMNI_E2SS_FW(SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE);
                        OMNI_E2SS_FW(SOCKET_TYPE_NOT_SUPPORTED);
                        OMNI_E2SS_FW(SYSTEM_ERROR);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        SUCCESS ||
                        HOST_ADDRESS_REQUIRED ||
                        NO_ADDRESSES_IN_FAMILY ||
                        NAME_SERVER_TEMPORARY_FAILURE ||
                        INVALID_FLAGS ||
                        NAME_SERVER_PERMANENT_FAILURE ||
                        ADDRESS_FAMILY_NOT_SUPPORTED ||
                        OUT_OF_MEMORY ||
                        HOST_EXISTS_NO_ADDRESSES_DEFINED ||
                        NODE_OR_SERVICE_NOT_KNOWN ||
                        SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE ||
                        SOCKET_TYPE_NOT_SUPPORTED ||
                        SYSTEM_ERROR
                    );
                }
        };

        /** socket_error defines enum values for socket errors codes */
        class socket_error
        {
            public:
                // TODO: need to have these tied to the actual system codes (e.g. EAGAIN, etc.)
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    SUCCESS = 0,
                    OPERATION_ABORTED = 995,
                    IO_PENDING = 997,
                    INTERRUPTED = 10004,
                    ACCESS_DENIED = 10013,
                    FAULT = 10014,
                    INVALID_ARGUMENT = 10022,
                    TOO_MANY_OPEN_SOCKETS = 10024,
                    WOULD_BLOCK = 10035,
                    IN_PROGRESS = 10036,
                    ALREADY_IN_PROGRESS = 10037,
                    NOT_SOCKET = 10038,
                    DESTINATION_ADDRESS_REQUIRED = 10039,
                    MESSAGE_SIZE = 10040,
                    PROTOCOL_TYPE = 10041,
                    PROTOCOL_OPTION = 10042,
                    PROTOCOL_NOT_SUPPORTED = 10043,
                    SOCKET_NOT_SUPPORTED = 10044,
                    OPERATION_NOT_SUPPORTED = 10045,
                    PROTOCOL_FAMILY_NOT_SUPPORTED = 10046,
                    ADDRESS_FAMILY_NOT_SUPPORTED = 10047,
                    ADDRESS_ALREADY_IN_USE = 10048,
                    ADDRESS_NOT_AVAILABLE = 10049,
                    NETWORK_DOWN = 10050,
                    NETWORK_UNREACHABLE = 10051,
                    NETWORK_RESET = 10052,
                    CONNECTION_ABORTED = 10053,
                    CONNECTION_RESET = 10054,
                    NO_BUFFER_SPACE_AVAILABLE = 10055,
                    IS_CONNECTED = 10056,
                    NOT_CONNECTED = 10057,
                    SHUTDOWN = 10058,
                    TIMED_OUT = 10060,
                    CONNECTION_REFUSED = 10061,
                    HOST_DOWN = 10064,
                    HOST_UNREACHABLE = 10065,
                    PROCESS_LIMIT = 10067,
                    SYSTEM_NOT_READY = 10091,
                    VERSION_NOT_SUPPORTED = 10092,
                    NOT_INITIALIZED = 10093,
                    DISCONNECTING = 10101,
                    TYPE_NOT_FOUND = 10109,
                    NO_HOST = 11001,    // DEV_NOTE: HOST_NOT_FOUND is a #define in netdb.h
                    AGAIN = 11002,      // DEV_NOTE: TRY_AGAIN is a #define in netdb.h
                    NO_RECOVER = 11003, // DEV_NOTE: NO_RECOVERY is a #define in netdb.h
                    NO_DAT = 11004      // DEV_NOTE: NO_DATA is a #define in netdb.h
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 48;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, socket_error& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_error& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                socket_error() :
                    OMNI_CTOR_FW(omni::net::socket_error)
                    m_val(DEFAULT_VALUE())
                { }

                socket_error(const socket_error& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_error(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_error)
                    m_val(val)
                { }

                ~socket_error()
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

                bool operator!=(const socket_error& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_error& operator=(const socket_error& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_error& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_error& operator=(int32_t val)
                {
                    if (!socket_error::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_error operator|(const socket_error& val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_error operator|(enum_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val | val));
                }

                socket_error operator|(int32_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val | val));
                }

                socket_error& operator|=(const socket_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_error& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_error& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_error operator&(const socket_error& val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_error operator&(enum_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val & val));
                }

                socket_error operator&(int32_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val & val));
                }

                socket_error& operator&=(const socket_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_error& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_error& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_error& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_error operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_error ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_error& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_error operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_error ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_error operator~()
                {
                    return socket_error(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_error operator^(const socket_error& val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_error operator^(enum_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_error operator^(int32_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_error& operator^=(const socket_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_error& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_error& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_error operator<<(const socket_error& val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_error operator<<(enum_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val << val));
                }

                socket_error operator<<(int32_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val << val));
                }

                socket_error& operator<<=(const socket_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_error& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_error& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_error operator>>(const socket_error& val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_error operator>>(enum_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val >> val));
                }

                socket_error operator>>(int32_t val)
                {
                    return socket_error(static_cast<enum_t>(this->m_val >> val));
                }

                socket_error& operator>>=(const socket_error& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_error& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_error& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_error& val) const
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

                bool operator>(const socket_error& val) const
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

                bool operator==(const socket_error& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_error) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_error)
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
                static bool _try_parse(const S& val, socket_error& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(SUCCESS)
                        OMNI_S2E_FW(OPERATION_ABORTED)
                        OMNI_S2E_FW(IO_PENDING)
                        OMNI_S2E_FW(INTERRUPTED)
                        OMNI_S2E_FW(ACCESS_DENIED)
                        OMNI_S2E_FW(FAULT)
                        OMNI_S2E_FW(INVALID_ARGUMENT)
                        OMNI_S2E_FW(TOO_MANY_OPEN_SOCKETS)
                        OMNI_S2E_FW(WOULD_BLOCK)
                        OMNI_S2E_FW(IN_PROGRESS)
                        OMNI_S2E_FW(ALREADY_IN_PROGRESS)
                        OMNI_S2E_FW(NOT_SOCKET)
                        OMNI_S2E_FW(DESTINATION_ADDRESS_REQUIRED)
                        OMNI_S2E_FW(MESSAGE_SIZE)
                        OMNI_S2E_FW(PROTOCOL_TYPE)
                        OMNI_S2E_FW(PROTOCOL_OPTION)
                        OMNI_S2E_FW(PROTOCOL_NOT_SUPPORTED)
                        OMNI_S2E_FW(SOCKET_NOT_SUPPORTED)
                        OMNI_S2E_FW(OPERATION_NOT_SUPPORTED)
                        OMNI_S2E_FW(PROTOCOL_FAMILY_NOT_SUPPORTED)
                        OMNI_S2E_FW(ADDRESS_FAMILY_NOT_SUPPORTED)
                        OMNI_S2E_FW(ADDRESS_ALREADY_IN_USE)
                        OMNI_S2E_FW(ADDRESS_NOT_AVAILABLE)
                        OMNI_S2E_FW(NETWORK_DOWN)
                        OMNI_S2E_FW(NETWORK_UNREACHABLE)
                        OMNI_S2E_FW(NETWORK_RESET)
                        OMNI_S2E_FW(CONNECTION_ABORTED)
                        OMNI_S2E_FW(CONNECTION_RESET)
                        OMNI_S2E_FW(NO_BUFFER_SPACE_AVAILABLE)
                        OMNI_S2E_FW(IS_CONNECTED)
                        OMNI_S2E_FW(NOT_CONNECTED)
                        OMNI_S2E_FW(SHUTDOWN)
                        OMNI_S2E_FW(TIMED_OUT)
                        OMNI_S2E_FW(CONNECTION_REFUSED)
                        OMNI_S2E_FW(HOST_DOWN)
                        OMNI_S2E_FW(HOST_UNREACHABLE)
                        OMNI_S2E_FW(PROCESS_LIMIT)
                        OMNI_S2E_FW(SYSTEM_NOT_READY)
                        OMNI_S2E_FW(VERSION_NOT_SUPPORTED)
                        OMNI_S2E_FW(NOT_INITIALIZED)
                        OMNI_S2E_FW(DISCONNECTING)
                        OMNI_S2E_FW(TYPE_NOT_FOUND)
                        OMNI_S2E_FW(NO_HOST)
                        OMNI_S2E_FW(AGAIN)
                        OMNI_S2E_FW(NO_RECOVER)
                        OMNI_S2E_FW(NO_DAT)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(SUCCESS);
                        OMNI_E2SS_FW(OPERATION_ABORTED);
                        OMNI_E2SS_FW(IO_PENDING);
                        OMNI_E2SS_FW(INTERRUPTED);
                        OMNI_E2SS_FW(ACCESS_DENIED);
                        OMNI_E2SS_FW(FAULT);
                        OMNI_E2SS_FW(INVALID_ARGUMENT);
                        OMNI_E2SS_FW(TOO_MANY_OPEN_SOCKETS);
                        OMNI_E2SS_FW(WOULD_BLOCK);
                        OMNI_E2SS_FW(IN_PROGRESS);
                        OMNI_E2SS_FW(ALREADY_IN_PROGRESS);
                        OMNI_E2SS_FW(NOT_SOCKET);
                        OMNI_E2SS_FW(DESTINATION_ADDRESS_REQUIRED);
                        OMNI_E2SS_FW(MESSAGE_SIZE);
                        OMNI_E2SS_FW(PROTOCOL_TYPE);
                        OMNI_E2SS_FW(PROTOCOL_OPTION);
                        OMNI_E2SS_FW(PROTOCOL_NOT_SUPPORTED);
                        OMNI_E2SS_FW(SOCKET_NOT_SUPPORTED);
                        OMNI_E2SS_FW(OPERATION_NOT_SUPPORTED);
                        OMNI_E2SS_FW(PROTOCOL_FAMILY_NOT_SUPPORTED);
                        OMNI_E2SS_FW(ADDRESS_FAMILY_NOT_SUPPORTED);
                        OMNI_E2SS_FW(ADDRESS_ALREADY_IN_USE);
                        OMNI_E2SS_FW(ADDRESS_NOT_AVAILABLE);
                        OMNI_E2SS_FW(NETWORK_DOWN);
                        OMNI_E2SS_FW(NETWORK_UNREACHABLE);
                        OMNI_E2SS_FW(NETWORK_RESET);
                        OMNI_E2SS_FW(CONNECTION_ABORTED);
                        OMNI_E2SS_FW(CONNECTION_RESET);
                        OMNI_E2SS_FW(NO_BUFFER_SPACE_AVAILABLE);
                        OMNI_E2SS_FW(IS_CONNECTED);
                        OMNI_E2SS_FW(NOT_CONNECTED);
                        OMNI_E2SS_FW(SHUTDOWN);
                        OMNI_E2SS_FW(TIMED_OUT);
                        OMNI_E2SS_FW(CONNECTION_REFUSED);
                        OMNI_E2SS_FW(HOST_DOWN);
                        OMNI_E2SS_FW(HOST_UNREACHABLE);
                        OMNI_E2SS_FW(PROCESS_LIMIT);
                        OMNI_E2SS_FW(SYSTEM_NOT_READY);
                        OMNI_E2SS_FW(VERSION_NOT_SUPPORTED);
                        OMNI_E2SS_FW(NOT_INITIALIZED);
                        OMNI_E2SS_FW(DISCONNECTING);
                        OMNI_E2SS_FW(TYPE_NOT_FOUND);
                        OMNI_E2SS_FW(NO_HOST);
                        OMNI_E2SS_FW(AGAIN);
                        OMNI_E2SS_FW(NO_RECOVER);
                        OMNI_E2SS_FW(NO_DAT);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        SUCCESS ||
                        OPERATION_ABORTED ||
                        IO_PENDING ||
                        INTERRUPTED ||
                        ACCESS_DENIED ||
                        FAULT ||
                        INVALID_ARGUMENT ||
                        TOO_MANY_OPEN_SOCKETS ||
                        WOULD_BLOCK ||
                        IN_PROGRESS ||
                        ALREADY_IN_PROGRESS ||
                        NOT_SOCKET ||
                        DESTINATION_ADDRESS_REQUIRED ||
                        MESSAGE_SIZE ||
                        PROTOCOL_TYPE ||
                        PROTOCOL_OPTION ||
                        PROTOCOL_NOT_SUPPORTED ||
                        SOCKET_NOT_SUPPORTED ||
                        OPERATION_NOT_SUPPORTED ||
                        PROTOCOL_FAMILY_NOT_SUPPORTED ||
                        ADDRESS_FAMILY_NOT_SUPPORTED ||
                        ADDRESS_ALREADY_IN_USE ||
                        ADDRESS_NOT_AVAILABLE ||
                        NETWORK_DOWN ||
                        NETWORK_UNREACHABLE ||
                        NETWORK_RESET ||
                        CONNECTION_ABORTED ||
                        CONNECTION_RESET ||
                        NO_BUFFER_SPACE_AVAILABLE ||
                        IS_CONNECTED ||
                        NOT_CONNECTED ||
                        SHUTDOWN ||
                        TIMED_OUT ||
                        CONNECTION_REFUSED ||
                        HOST_DOWN ||
                        HOST_UNREACHABLE ||
                        PROCESS_LIMIT ||
                        SYSTEM_NOT_READY ||
                        VERSION_NOT_SUPPORTED ||
                        NOT_INITIALIZED ||
                        DISCONNECTING ||
                        TYPE_NOT_FOUND ||
                        NO_HOST ||
                        AGAIN ||
                        NO_RECOVER ||
                        NO_DAT
                    );
                }
        };
        
        /** socket_flags defines enum values for socket send and receive behaviors. */
        class socket_flags
        {
            public:
                typedef enum enum_t {
                    NONE = OMNI_SOCK_FLAGS_NONE,
                    OUT_OF_BAND = MSG_OOB,          // 1
                    PEEK = MSG_PEEK,                // 2
                    DONT_ROUTE = MSG_DONTROUTE,     // 4
                    END_OF_RECORD = OMNI_MSG_EOR_FW,   // 8 (0 for Windows)
                } enum_t;

                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 5;
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
                static bool try_parse(const std::string& val, socket_flags& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_flags& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                socket_flags() :
                    OMNI_CTOR_FW(omni::net::socket_flags)
                    m_val(DEFAULT_VALUE())
                { }

                socket_flags(const socket_flags& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_flags(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_flags)
                    m_val(val)
                { }

                ~socket_flags()
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

                bool operator!=(const socket_flags& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_flags& operator=(const socket_flags& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_flags& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_flags& operator=(int32_t val)
                {
                    if (!socket_flags::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_flags operator|(const socket_flags& val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_flags operator|(enum_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val | val));
                }

                socket_flags operator|(int32_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val | val));
                }

                socket_flags& operator|=(const socket_flags& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_flags& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_flags& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_flags operator&(const socket_flags& val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_flags operator&(enum_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val & val));
                }

                socket_flags operator&(int32_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val & val));
                }

                socket_flags& operator&=(const socket_flags& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_flags& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_flags& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_flags& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_flags operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_flags ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_flags& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_flags operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_flags ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_flags operator~()
                {
                    return socket_flags(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_flags operator^(const socket_flags& val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_flags operator^(enum_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_flags operator^(int32_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_flags& operator^=(const socket_flags& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_flags& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_flags& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_flags operator<<(const socket_flags& val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_flags operator<<(enum_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val << val));
                }

                socket_flags operator<<(int32_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val << val));
                }

                socket_flags& operator<<=(const socket_flags& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_flags& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_flags& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_flags operator>>(const socket_flags& val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_flags operator>>(enum_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val >> val));
                }

                socket_flags operator>>(int32_t val)
                {
                    return socket_flags(static_cast<enum_t>(this->m_val >> val));
                }

                socket_flags& operator>>=(const socket_flags& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_flags& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_flags& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_flags& val) const
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

                bool operator>(const socket_flags& val) const
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

                bool operator==(const socket_flags& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_flags) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_flags)
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
                static bool _try_parse(const S& val, socket_flags& out)
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
                        OMNI_S2E_FW(OUT_OF_BAND)
                        OMNI_S2E_FW(PEEK)
                        OMNI_S2E_FW(DONT_ROUTE)
                        OMNI_S2E_FW(END_OF_RECORD)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(OUT_OF_BAND);
                        OMNI_E2SS_FW(PEEK);
                        OMNI_E2SS_FW(DONT_ROUTE);
                        OMNI_E2SS_FW(END_OF_RECORD);
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
                        OUT_OF_BAND ||
                        PEEK ||
                        DONT_ROUTE ||
                        END_OF_RECORD
                    );
                }
        };

        /** select_mode defines enum values for the polling modes for the omni::net::socket::poll method. */
        class select_mode
        {
            public:
                typedef enum enum_t {
                    NONE = -1,
                    SELECT_READ = 0,
                    SELECT_WRITE = 1,
                    SELECT_ERROR = 2
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 4;
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
                static bool try_parse(const std::string& val, select_mode& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, select_mode& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                select_mode() :
                    OMNI_CTOR_FW(omni::net::select_mode)
                    m_val(DEFAULT_VALUE())
                { }

                select_mode(const select_mode& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                select_mode(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::select_mode)
                    m_val(val)
                { }

                ~select_mode()
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

                bool operator!=(const select_mode& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                select_mode& operator=(const select_mode& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                select_mode& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                select_mode& operator=(int32_t val)
                {
                    if (!select_mode::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const select_mode& val) const
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

                bool operator>(const select_mode& val) const
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

                bool operator==(const select_mode& val) const
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

                OMNI_MEMBERS_FW(omni::net::select_mode) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::net::select_mode)
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
                static bool _try_parse(const S& val, select_mode& out)
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
                        OMNI_S2E_FW(SELECT_READ)
                        OMNI_S2E_FW(SELECT_WRITE)
                        OMNI_S2E_FW(SELECT_ERROR)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(SELECT_READ);
                        OMNI_E2SS_FW(SELECT_WRITE);
                        OMNI_E2SS_FW(SELECT_ERROR);
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
                        SELECT_READ || 
                        SELECT_WRITE || 
                        SELECT_ERROR
                    );
                }
        };

        /** blocking_mode defines enum values for the polling modes for the omni::net::socket::poll method. */
        class blocking_mode
        {
            public:
                typedef enum enum_t {
                    BLOCK = 0,
                    DONT_BLOCK = 1
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 2;
                }
                
                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return BLOCK;
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
                static bool try_parse(const std::string& val, blocking_mode& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, blocking_mode& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                blocking_mode() :
                    OMNI_CTOR_FW(omni::net::blocking_mode)
                    m_val(DEFAULT_VALUE())
                { }

                blocking_mode(const blocking_mode& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                blocking_mode(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::blocking_mode)
                    m_val(val)
                { }

                ~blocking_mode()
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

                bool operator!=(const blocking_mode& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                blocking_mode& operator=(const blocking_mode& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                blocking_mode& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                blocking_mode& operator=(int32_t val)
                {
                    if (!blocking_mode::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const blocking_mode& val) const
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

                bool operator>(const blocking_mode& val) const
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

                bool operator==(const blocking_mode& val) const
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

                OMNI_MEMBERS_FW(omni::net::blocking_mode) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::net::blocking_mode)
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
                static bool _try_parse(const S& val, blocking_mode& out)
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
                        OMNI_S2E_FW(BLOCK)
                        OMNI_S2E_FW(DONT_BLOCK)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(BLOCK);
                        OMNI_E2SS_FW(DONT_BLOCK);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        BLOCK ||
                        DONT_BLOCK
                    );
                }
        };

        /** socket_option_level defines enum values for socket option levels for the setsocketoption and getsocketoption methods. */
        class socket_option_level
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    IP = IPPROTO_IP, // 0
                    IP6 = IPPROTO_IPV6, // 41
                    TCP = IPPROTO_TCP, // 6
                    UDP = IPPROTO_UDP, //17
                    SOCKET = SOL_SOCKET // 65535
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 6;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, socket_option_level& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_option_level& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                socket_option_level() :
                    OMNI_CTOR_FW(omni::net::socket_option_level)
                    m_val(DEFAULT_VALUE())
                { }

                socket_option_level(const socket_option_level& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_option_level(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_option_level)
                    m_val(val)
                { }

                ~socket_option_level()
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

                bool operator!=(const socket_option_level& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_option_level& operator=(const socket_option_level& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_option_level& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_option_level& operator=(int32_t val)
                {
                    if (!socket_option_level::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_option_level operator|(const socket_option_level& val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_option_level operator|(enum_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val | val));
                }

                socket_option_level operator|(int32_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val | val));
                }

                socket_option_level& operator|=(const socket_option_level& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_option_level& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_option_level& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_option_level operator&(const socket_option_level& val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_option_level operator&(enum_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val & val));
                }

                socket_option_level operator&(int32_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val & val));
                }

                socket_option_level& operator&=(const socket_option_level& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_option_level& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_option_level& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_option_level& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_option_level operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_option_level ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_option_level& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_option_level operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_option_level ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_option_level operator~()
                {
                    return socket_option_level(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_option_level operator^(const socket_option_level& val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_option_level operator^(enum_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_option_level operator^(int32_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_option_level& operator^=(const socket_option_level& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_option_level& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_option_level& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_option_level operator<<(const socket_option_level& val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_option_level operator<<(enum_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val << val));
                }

                socket_option_level operator<<(int32_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val << val));
                }

                socket_option_level& operator<<=(const socket_option_level& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_option_level& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_option_level& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_option_level operator>>(const socket_option_level& val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_option_level operator>>(enum_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val >> val));
                }

                socket_option_level operator>>(int32_t val)
                {
                    return socket_option_level(static_cast<enum_t>(this->m_val >> val));
                }

                socket_option_level& operator>>=(const socket_option_level& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_option_level& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_option_level& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_option_level& val) const
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

                bool operator>(const socket_option_level& val) const
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

                bool operator==(const socket_option_level& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_option_level) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_option_level)
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
                static bool _try_parse(const S& val, socket_option_level& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(IP)
                        OMNI_S2E_FW(IP6)
                        OMNI_S2E_FW(TCP)
                        OMNI_S2E_FW(UDP)
                        OMNI_S2E_FW(SOCKET)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(IP);
                        OMNI_E2SS_FW(IP6);
                        OMNI_E2SS_FW(TCP);
                        OMNI_E2SS_FW(UDP);
                        OMNI_E2SS_FW(SOCKET);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        IP ||
                        IP6 ||
                        TCP ||
                        UDP ||
                        SOCKET
                    );
                }
        };
        
        /** socket_option defines enum values for configuration option names. */
        class socket_option
        {
            public:
                typedef enum enum_t {
                    DONT_LINGER = -129,
                    UNSPECIFIED = -1,
                    DBG = SO_DEBUG, // 1, -- DEV_NOTE: DBG instead of DEBUG to avoid macro confusion when -DDEBUG defined
                    ACCEPT_CONNECTION = SO_ACCEPTCONN, // 2,
                    REUSE_ADDRESS = SO_REUSEADDR, // 4,
                    KEEP_ALIVE = SO_KEEPALIVE, // 8,
                    DONT_ROUTE = SO_DONTROUTE, // 16,
                    BROADCAST = SO_BROADCAST, // 32,
                    LINGER = SO_LINGER, // 128,
                    OUT_OF_BAND_INLINE = SO_OOBINLINE, // 256,
                    SEND_BUFFER = SO_SNDBUF, // 4097,
                    RECEIVE_BUFFER = SO_RCVBUF, // 4098,
                    SEND_LOW_WATER = SO_SNDLOWAT, // 4099,
                    RECEIVE_LOW_WATER = SO_RCVLOWAT, // 4100,
                    SEND_TIMEOUT = SO_SNDTIMEO, // 4101,
                    RECEIVE_TIMEOUT = SO_RCVTIMEO, // 4102,
                    ERR = SO_ERROR, // 4103,
                    SOCKET_TYPE = SO_TYPE, // 4104,
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 19;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, socket_option& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_option& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                socket_option() :
                    OMNI_CTOR_FW(omni::net::socket_option)
                    m_val(DEFAULT_VALUE())
                { }

                socket_option(const socket_option& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_option(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_option)
                    m_val(val)
                { }

                ~socket_option()
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

                bool operator!=(const socket_option& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_option& operator=(const socket_option& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_option& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_option& operator=(int32_t val)
                {
                    if (!socket_option::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_option operator|(const socket_option& val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_option operator|(enum_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val | val));
                }

                socket_option operator|(int32_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val | val));
                }

                socket_option& operator|=(const socket_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_option& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_option& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_option operator&(const socket_option& val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_option operator&(enum_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val & val));
                }

                socket_option operator&(int32_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val & val));
                }

                socket_option& operator&=(const socket_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_option& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_option& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_option& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_option operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_option ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_option& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_option operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_option ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_option operator~()
                {
                    return socket_option(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_option operator^(const socket_option& val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_option operator^(enum_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_option operator^(int32_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_option& operator^=(const socket_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_option& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_option& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_option operator<<(const socket_option& val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_option operator<<(enum_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val << val));
                }

                socket_option operator<<(int32_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val << val));
                }

                socket_option& operator<<=(const socket_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_option& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_option& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_option operator>>(const socket_option& val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_option operator>>(enum_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val >> val));
                }

                socket_option operator>>(int32_t val)
                {
                    return socket_option(static_cast<enum_t>(this->m_val >> val));
                }

                socket_option& operator>>=(const socket_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_option& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_option& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_option& val) const
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

                bool operator>(const socket_option& val) const
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

                bool operator==(const socket_option& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_option) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_option)
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
                static bool _try_parse(const S& val, socket_option& out)
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
                        OMNI_S2E_FW(DONT_LINGER)
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(DBG)
                        OMNI_S2E_FW(ACCEPT_CONNECTION)
                        OMNI_S2E_FW(REUSE_ADDRESS)
                        OMNI_S2E_FW(KEEP_ALIVE)
                        OMNI_S2E_FW(DONT_ROUTE)
                        OMNI_S2E_FW(BROADCAST)
                        OMNI_S2E_FW(LINGER)
                        OMNI_S2E_FW(OUT_OF_BAND_INLINE)
                        OMNI_S2E_FW(SEND_BUFFER)
                        OMNI_S2E_FW(RECEIVE_BUFFER)
                        OMNI_S2E_FW(SEND_LOW_WATER)
                        OMNI_S2E_FW(RECEIVE_LOW_WATER)
                        OMNI_S2E_FW(SEND_TIMEOUT)
                        OMNI_S2E_FW(RECEIVE_TIMEOUT)
                        OMNI_S2E_FW(ERR)
                        OMNI_S2E_FW(SOCKET_TYPE)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(DONT_LINGER);
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(DBG);
                        OMNI_E2SS_FW(ACCEPT_CONNECTION);
                        OMNI_E2SS_FW(REUSE_ADDRESS);
                        OMNI_E2SS_FW(KEEP_ALIVE);
                        OMNI_E2SS_FW(DONT_ROUTE);
                        OMNI_E2SS_FW(BROADCAST);
                        OMNI_E2SS_FW(LINGER);
                        OMNI_E2SS_FW(OUT_OF_BAND_INLINE);
                        OMNI_E2SS_FW(SEND_BUFFER);
                        OMNI_E2SS_FW(RECEIVE_BUFFER);
                        OMNI_E2SS_FW(SEND_LOW_WATER);
                        OMNI_E2SS_FW(RECEIVE_LOW_WATER);
                        OMNI_E2SS_FW(SEND_TIMEOUT);
                        OMNI_E2SS_FW(RECEIVE_TIMEOUT);
                        OMNI_E2SS_FW(ERR);
                        OMNI_E2SS_FW(SOCKET_TYPE);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val ==
                        DONT_LINGER ||
                        UNSPECIFIED ||
                        DBG ||
                        ACCEPT_CONNECTION ||
                        REUSE_ADDRESS ||
                        KEEP_ALIVE ||
                        DONT_ROUTE ||
                        BROADCAST ||
                        LINGER ||
                        OUT_OF_BAND_INLINE ||
                        SEND_BUFFER ||
                        RECEIVE_BUFFER ||
                        SEND_LOW_WATER ||
                        RECEIVE_LOW_WATER ||
                        SEND_TIMEOUT ||
                        RECEIVE_TIMEOUT ||
                        ERR ||
                        SOCKET_TYPE
                    );
                }
        };

        /** tcp_option defines enum values for configuration option names. */
        class tcp_option
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    NO_DELAY = TCP_NODELAY, // 1,
                    #if defined(TCP_KEEPALIVE)
                        KEEP_ALIVE = TCP_KEEPALIVE
                    #else
                        KEEP_ALIVE = SO_KEEPALIVE
                    #endif
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 3;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, tcp_option& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, tcp_option& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                tcp_option() :
                    OMNI_CTOR_FW(omni::net::tcp_option)
                    m_val(DEFAULT_VALUE())
                { }

                tcp_option(const tcp_option& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                tcp_option(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::tcp_option)
                    m_val(val)
                { }

                ~tcp_option()
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

                bool operator!=(const tcp_option& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                tcp_option& operator=(const tcp_option& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                tcp_option& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                tcp_option& operator=(int32_t val)
                {
                    if (!tcp_option::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                tcp_option operator|(const tcp_option& val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val | val.m_val));
                }

                tcp_option operator|(enum_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val | val));
                }

                tcp_option operator|(int32_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val | val));
                }

                tcp_option& operator|=(const tcp_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                tcp_option& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                tcp_option& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                tcp_option operator&(const tcp_option& val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val & val.m_val));
                }

                tcp_option operator&(enum_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val & val));
                }

                tcp_option operator&(int32_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val & val));
                }

                tcp_option& operator&=(const tcp_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                tcp_option& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                tcp_option& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                tcp_option& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                tcp_option operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    tcp_option ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                tcp_option& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                tcp_option operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    tcp_option ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                tcp_option operator~()
                {
                    return tcp_option(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                tcp_option operator^(const tcp_option& val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                tcp_option operator^(enum_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val ^ val));
                }

                tcp_option operator^(int32_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val ^ val));
                }

                tcp_option& operator^=(const tcp_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                tcp_option& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                tcp_option& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                tcp_option operator<<(const tcp_option& val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val << val.m_val));
                }

                tcp_option operator<<(enum_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val << val));
                }

                tcp_option operator<<(int32_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val << val));
                }

                tcp_option& operator<<=(const tcp_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                tcp_option& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                tcp_option& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                tcp_option operator>>(const tcp_option& val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                tcp_option operator>>(enum_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val >> val));
                }

                tcp_option operator>>(int32_t val)
                {
                    return tcp_option(static_cast<enum_t>(this->m_val >> val));
                }

                tcp_option& operator>>=(const tcp_option& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                tcp_option& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                tcp_option& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const tcp_option& val) const
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

                bool operator>(const tcp_option& val) const
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

                bool operator==(const tcp_option& val) const
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

                OMNI_MEMBERS_FW(omni::net::tcp_option) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::tcp_option)
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
                static bool _try_parse(const S& val, tcp_option& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(NO_DELAY)
                        OMNI_S2E_FW(KEEP_ALIVE)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(NO_DELAY);
                        OMNI_E2SS_FW(KEEP_ALIVE);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        NO_DELAY ||
                        KEEP_ALIVE
                    );
                }
        };

        /** socket_shutdown defines enum values for constants that are used by the omni::net::socket::shutdown method. */
        class socket_shutdown
        {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    RECEIVE = OMNI_SOCK_RECEIVE_FW,
                    SEND = OMNI_SOCK_SEND_FW,
                    BOTH = OMNI_SOCK_BOTH_FW
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 4;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNSPECIFIED;
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
                static bool try_parse(const std::string& val, socket_shutdown& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_shutdown& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }
                
                socket_shutdown() :
                    OMNI_CTOR_FW(omni::net::socket_shutdown)
                    m_val(DEFAULT_VALUE())
                { }

                socket_shutdown(const socket_shutdown& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_shutdown(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_shutdown)
                    m_val(val)
                { }

                ~socket_shutdown()
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

                bool operator!=(const socket_shutdown& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_shutdown& operator=(const socket_shutdown& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_shutdown& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_shutdown& operator=(int32_t val)
                {
                    if (!socket_shutdown::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_shutdown operator|(const socket_shutdown& val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_shutdown operator|(enum_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val | val));
                }

                socket_shutdown operator|(int32_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val | val));
                }

                socket_shutdown& operator|=(const socket_shutdown& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_shutdown& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_shutdown& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_shutdown operator&(const socket_shutdown& val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_shutdown operator&(enum_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val & val));
                }

                socket_shutdown operator&(int32_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val & val));
                }

                socket_shutdown& operator&=(const socket_shutdown& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_shutdown& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_shutdown& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_shutdown& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_shutdown operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_shutdown ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_shutdown& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_shutdown operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_shutdown ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_shutdown operator~()
                {
                    return socket_shutdown(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_shutdown operator^(const socket_shutdown& val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_shutdown operator^(enum_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_shutdown operator^(int32_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_shutdown& operator^=(const socket_shutdown& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_shutdown& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_shutdown& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_shutdown operator<<(const socket_shutdown& val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_shutdown operator<<(enum_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val << val));
                }

                socket_shutdown operator<<(int32_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val << val));
                }

                socket_shutdown& operator<<=(const socket_shutdown& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_shutdown& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_shutdown& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_shutdown operator>>(const socket_shutdown& val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_shutdown operator>>(enum_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val >> val));
                }

                socket_shutdown operator>>(int32_t val)
                {
                    return socket_shutdown(static_cast<enum_t>(this->m_val >> val));
                }

                socket_shutdown& operator>>=(const socket_shutdown& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_shutdown& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_shutdown& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_shutdown& val) const
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

                bool operator>(const socket_shutdown& val) const
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

                bool operator==(const socket_shutdown& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_shutdown) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_shutdown)
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
                static bool _try_parse(const S& val, socket_shutdown& out)
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
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(RECEIVE)
                        OMNI_S2E_FW(SEND)
                        OMNI_S2E_FW(BOTH)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(RECEIVE);
                        OMNI_E2SS_FW(SEND);
                        OMNI_E2SS_FW(BOTH);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        RECEIVE || 
                        SEND || 
                        BOTH
                    );
                }
        };
        
        /** socket_type defines enum values for the type of socket that an instance of the omni::net::socket class represents. */
        class socket_type
        {
            public:
                typedef enum enum_t {
                    UNKNOWN = -1,
                    STREAM = SOCK_STREAM,
                    DGRAM = SOCK_DGRAM,
                    RAW = SOCK_RAW,
                    RDM = SOCK_RDM,
                    SEQPACKET = SOCK_SEQPACKET
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 6;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return UNKNOWN;
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
                static bool try_parse(const std::string& val, socket_type& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_type& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                socket_type() :
                    OMNI_CTOR_FW(omni::net::socket_type)
                    m_val(DEFAULT_VALUE())
                { }

                socket_type(const socket_type& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_type(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_type)
                    m_val(val)
                { }

                ~socket_type()
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

                bool operator!=(const socket_type& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_type& operator=(const socket_type& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_type& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_type& operator=(int32_t val)
                {
                    if (!socket_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_type operator|(const socket_type& val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_type operator|(enum_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val | val));
                }

                socket_type operator|(int32_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val | val));
                }

                socket_type& operator|=(const socket_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_type& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_type& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_type operator&(const socket_type& val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_type operator&(enum_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val & val));
                }

                socket_type operator&(int32_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val & val));
                }

                socket_type& operator&=(const socket_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_type& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_type& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_type& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_type operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_type ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_type& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_type operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_type ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_type operator~()
                {
                    return socket_type(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_type operator^(const socket_type& val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_type operator^(enum_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_type operator^(int32_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_type& operator^=(const socket_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_type& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_type& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_type operator<<(const socket_type& val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_type operator<<(enum_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val << val));
                }

                socket_type operator<<(int32_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val << val));
                }

                socket_type& operator<<=(const socket_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_type& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_type& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_type operator>>(const socket_type& val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_type operator>>(enum_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val >> val));
                }

                socket_type operator>>(int32_t val)
                {
                    return socket_type(static_cast<enum_t>(this->m_val >> val));
                }

                socket_type& operator>>=(const socket_type& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_type& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_type& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_type& val) const
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

                bool operator>(const socket_type& val) const
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

                bool operator==(const socket_type& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_type) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_type)
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
                static bool _try_parse(const S& val, socket_type& out)
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
                        OMNI_S2E_FW(STREAM)
                        OMNI_S2E_FW(DGRAM)
                        OMNI_S2E_FW(RAW)
                        OMNI_S2E_FW(RDM)
                        OMNI_S2E_FW(SEQPACKET)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(STREAM);
                        OMNI_E2SS_FW(DGRAM);
                        OMNI_E2SS_FW(RAW);
                        OMNI_E2SS_FW(RDM);
                        OMNI_E2SS_FW(SEQPACKET);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        UNKNOWN ||
                        STREAM ||
                        DGRAM ||
                        RAW ||
                        RDM ||
                        SEQPACKET
                    );
                }
        };

        /** socket_create_options defines enum values for how an omni::net::socket class should be created when instantiated. */
        class socket_create_options
        {
            public:
                typedef enum enum_t {
                    OPEN_ON_CREATE,
                    USER_OPEN
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 2;
                }

                /** The default value for this enum instance */
                static inline enum_t DEFAULT_VALUE()
                {
                    return OPEN_ON_CREATE;
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
                static bool try_parse(const std::string& val, socket_create_options& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_create_options& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int32_t val)
                {
                    return _valid(val);
                }

                socket_create_options() :
                    OMNI_CTOR_FW(omni::net::socket_create_options)
                    m_val(DEFAULT_VALUE())
                { }

                socket_create_options(const socket_create_options& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_create_options(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_create_options)
                    m_val(val)
                { }

                ~socket_create_options()
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

                bool operator!=(const socket_create_options& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_create_options& operator=(const socket_create_options& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_create_options& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_create_options& operator=(int32_t val)
                {
                    if (!socket_create_options::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                socket_create_options operator|(const socket_create_options& val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val | val.m_val));
                }

                socket_create_options operator|(enum_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val | val));
                }

                socket_create_options operator|(int32_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val | val));
                }

                socket_create_options& operator|=(const socket_create_options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val.m_val);
                    return *this;
                }

                socket_create_options& operator|=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_create_options& operator|=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val | val);
                    return *this;
                }

                socket_create_options operator&(const socket_create_options& val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val & val.m_val));
                }

                socket_create_options operator&(enum_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val & val));
                }

                socket_create_options operator&(int32_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val & val));
                }

                socket_create_options& operator&=(const socket_create_options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val.m_val);
                    return *this;
                }

                socket_create_options& operator&=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }

                socket_create_options& operator&=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val & val);
                    return *this;
                }
                
                socket_create_options& operator++()
                {
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return *this;
                }

                socket_create_options operator++(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_create_options ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val + 1);
                    return ret;
                }

                socket_create_options& operator--()
                {
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return *this;
                }

                socket_create_options operator--(int dummy)
                {
                    OMNI_UNUSED(dummy);
                    socket_create_options ret(this->m_val);
                    this->m_val = static_cast<enum_t>(this->m_val - 1);
                    return ret;
                }

                socket_create_options operator~()
                {
                    return socket_create_options(static_cast<enum_t>(~static_cast<int32_t>(this->m_val)));
                }

                socket_create_options operator^(const socket_create_options& val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val ^ val.m_val));
                }

                socket_create_options operator^(enum_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_create_options operator^(int32_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val ^ val));
                }

                socket_create_options& operator^=(const socket_create_options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val.m_val);
                    return *this;
                }

                socket_create_options& operator^=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_create_options& operator^=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val ^ val);
                    return *this;
                }

                socket_create_options operator<<(const socket_create_options& val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val << val.m_val));
                }

                socket_create_options operator<<(enum_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val << val));
                }

                socket_create_options operator<<(int32_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val << val));
                }

                socket_create_options& operator<<=(const socket_create_options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val.m_val);
                    return *this;
                }

                socket_create_options& operator<<=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_create_options& operator<<=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val << val);
                    return *this;
                }

                socket_create_options operator>>(const socket_create_options& val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val >> val.m_val));
                }

                socket_create_options operator>>(enum_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val >> val));
                }

                socket_create_options operator>>(int32_t val)
                {
                    return socket_create_options(static_cast<enum_t>(this->m_val >> val));
                }

                socket_create_options& operator>>=(const socket_create_options& val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val.m_val);
                    return *this;
                }

                socket_create_options& operator>>=(enum_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                socket_create_options& operator>>=(int32_t val)
                {
                    this->m_val = static_cast<enum_t>(this->m_val >> val);
                    return *this;
                }

                bool operator<(const socket_create_options& val) const
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

                bool operator>(const socket_create_options& val) const
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

                bool operator==(const socket_create_options& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_create_options) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_create_options)
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
                static bool _try_parse(const S& val, socket_create_options& out)
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
                        OMNI_S2E_FW(OPEN_ON_CREATE)
                        OMNI_S2E_FW(USER_OPEN)
                    }
                    return false;
                }

                template < typename S >
                static std::basic_string< typename S::char_type > _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(OPEN_ON_CREATE);
                        OMNI_E2SS_FW(USER_OPEN);
                        default:
                            ss << "UNKNOWN (" << static_cast<int>(v) << ")";
                            break;
                    }
                    return ss.str();
                }

                static bool _valid(int32_t val)
                {
                    return (val == 
                        OPEN_ON_CREATE ||
                        USER_OPEN
                    );
                }
        };

        typedef OMNI_SOCKET_T_FW socket_t;
        typedef OMNI_SOCKADDR_IN_T_FW sockaddr_in_t;
        typedef OMNI_SOCKADDR_IN6_T_FW sockaddr_in6_t;
        typedef OMNI_SOCKADDR_UN_T_FW sockaddr_un_t;
        typedef OMNI_SOCKADDR_T_FW sockaddr_t;
        typedef OMNI_SOCKET_XFR_T_FW xfr_t;
    }
}

#endif // OMNI_NET_T_HPP
