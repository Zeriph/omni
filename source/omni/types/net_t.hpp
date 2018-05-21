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

// TODO: a lot of same enum types causing 'duplicate' types

namespace omni {
    /** The net namespace is used to facilitate certain networking operations and handling */
    namespace net {
        /** address_family defines enum values for the addressing scheme that an instance of the omni::net::socket class can use. */
        class address_family {
            public:
                typedef enum enum_t {
                    UNKNOWN = -1,
                    UNSPECIFIED = 0,
                    UNIX = 1,
                    INTERNETWORK = 2,
                    IMPLINK = 3,
                    PUP = 4,
                    CHAOS = 5,
                    IPX = 6,
                    NS = 6,
                    OSI = 7,
                    ISO = 7,
                    ECMA = 8,
                    DATAKIT = 9,
                    CCITT = 10,
                    SNA = 11,
                    DECNET = 12,
                    DATALINK = 13,
                    LAT = 14,
                    HYPERCHANNEL = 15,
                    APPLETALK = 16,
                    NETBIOS = 17,
                    VOICEVIEW = 18,
                    FIREFOX = 19,
                    BANYAN = 21,
                    ATM = 22,
                    INTERNETWORK_V6 = 23,
                    CLUSTER = 24,
                    IEEE12844 = 25,
                    IRDA = 26,
                    NETWORK_DESIGNERS = 28
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 30;
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
                static bool is_valid(int val)
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

                address_family& operator=(int val)
                {
                    if (!address_family::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                        OMNI_S2E_FW(UNKNOWN)
                        OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(UNIX)
                        OMNI_S2E_FW(INTERNETWORK)
                        OMNI_S2E_FW(IMPLINK)
                        OMNI_S2E_FW(PUP)
                        OMNI_S2E_FW(CHAOS)
                        OMNI_S2E_FW(IPX)
                        //OMNI_S2E_FW(NS)
                        OMNI_S2E_FW(OSI)
                        //OMNI_S2E_FW(ISO)
                        OMNI_S2E_FW(ECMA)
                        OMNI_S2E_FW(DATAKIT)
                        OMNI_S2E_FW(CCITT)
                        OMNI_S2E_FW(SNA)
                        OMNI_S2E_FW(DECNET)
                        OMNI_S2E_FW(DATALINK)
                        OMNI_S2E_FW(LAT)
                        OMNI_S2E_FW(HYPERCHANNEL)
                        OMNI_S2E_FW(APPLETALK)
                        OMNI_S2E_FW(NETBIOS)
                        OMNI_S2E_FW(VOICEVIEW)
                        OMNI_S2E_FW(FIREFOX)
                        OMNI_S2E_FW(BANYAN)
                        OMNI_S2E_FW(ATM)
                        OMNI_S2E_FW(INTERNETWORK_V6)
                        OMNI_S2E_FW(CLUSTER)
                        OMNI_S2E_FW(IEEE12844)
                        OMNI_S2E_FW(IRDA)
                        OMNI_S2E_FW(NETWORK_DESIGNERS)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(UNIX);
                        OMNI_E2SS_FW(INTERNETWORK);
                        OMNI_E2SS_FW(IMPLINK);
                        OMNI_E2SS_FW(PUP);
                        OMNI_E2SS_FW(CHAOS);
                        OMNI_E2SS_FW(IPX);
                        //OMNI_E2SS_FW(NS);
                        OMNI_E2SS_FW(OSI);
                        //OMNI_E2SS_FW(ISO);
                        OMNI_E2SS_FW(ECMA);
                        OMNI_E2SS_FW(DATAKIT);
                        OMNI_E2SS_FW(CCITT);
                        OMNI_E2SS_FW(SNA);
                        OMNI_E2SS_FW(DECNET);
                        OMNI_E2SS_FW(DATALINK);
                        OMNI_E2SS_FW(LAT);
                        OMNI_E2SS_FW(HYPERCHANNEL);
                        OMNI_E2SS_FW(APPLETALK);
                        OMNI_E2SS_FW(NETBIOS);
                        OMNI_E2SS_FW(VOICEVIEW);
                        OMNI_E2SS_FW(FIREFOX);
                        OMNI_E2SS_FW(BANYAN);
                        OMNI_E2SS_FW(ATM);
                        OMNI_E2SS_FW(INTERNETWORK_V6);
                        OMNI_E2SS_FW(CLUSTER);
                        OMNI_E2SS_FW(IEEE12844);
                        OMNI_E2SS_FW(IRDA);
                        OMNI_E2SS_FW(NETWORK_DESIGNERS);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        UNKNOWN ||
                        UNSPECIFIED ||
                        UNIX ||
                        INTERNETWORK ||
                        IMPLINK ||
                        PUP ||
                        CHAOS ||
                        IPX ||
                        //NS ||
                        OSI ||
                        //ISO ||
                        ECMA ||
                        DATAKIT ||
                        CCITT ||
                        SNA ||
                        DECNET ||
                        DATALINK ||
                        LAT ||
                        HYPERCHANNEL ||
                        APPLETALK ||
                        NETBIOS ||
                        VOICEVIEW ||
                        FIREFOX ||
                        BANYAN ||
                        ATM ||
                        INTERNETWORK_V6 ||
                        CLUSTER ||
                        IEEE12844 ||
                        IRDA ||
                        NETWORK_DESIGNERS
                    );
                }
        };
        
        /** network_interface defines enum values for what kind of interface the network card is */
        class network_interface {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    LOOPBACK = 0,
                    ETHERNET,
                    WIRELESS
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
                static bool try_parse(const std::string& val, network_interface& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, network_interface& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int val)
                {
                    return _valid(val);
                }
                
                network_interface() :
                    OMNI_CTOR_FW(omni::net::network_interface)
                    m_val(DEFAULT_VALUE())
                { }

                network_interface(const network_interface& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                network_interface(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::network_interface)
                    m_val(val)
                { }

                ~network_interface()
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

                bool operator!=(const network_interface& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                network_interface& operator=(const network_interface& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                network_interface& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                network_interface& operator=(int val)
                {
                    if (!network_interface::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const network_interface& val) const
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

                bool operator>(const network_interface& val) const
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

                bool operator==(const network_interface& val) const
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

                OMNI_MEMBERS_FW(omni::net::network_interface) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::network_interface)
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
                static bool _try_parse(const S& val, network_interface& out)
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
                        OMNI_S2E_FW(LOOPBACK)
                        OMNI_S2E_FW(ETHERNET)
                        OMNI_S2E_FW(WIRELESS)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(LOOPBACK);
                        OMNI_E2SS_FW(ETHERNET);
                        OMNI_E2SS_FW(WIRELESS);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        LOOPBACK ||
                        ETHERNET ||
                        WIRELESS
                    );
                }
        };
        
        /** ping_reply defines enum values for reply information received from a ping request */
        class ping_reply {
            public:
                typedef enum enum_t {
                    UNKNOWN,
                    SUCCESS,
                    DESTINATION_NETWORK_UNREACHABLE,
                    DESTINATION_HOST_UNREACHABLE,
                    DESTINATION_PROHIBITED,
                    DESTINATION_PROTOCOL_UNREACHABLE,
                    DESTINATION_PORT_UNREACHABLE,
                    NO_RESOURCES,
                    BAD_OPTION,
                    HARDWARE_ERROR,
                    PACKET_TOO_BIG,
                    TIMED_OUT,
                    BAD_ROUTE,
                    TTL_EXPIRED,
                    TTL_REASSEMBLY_TIME_EXCEEDED,
                    PARAMETER_PROBLEM,
                    SOURCE_QUENCH,
                    BAD_DESTINATION,
                    DESTINATION_UNREACHABLE,
                    TIME_EXCEEDED,
                    BAD_HEADER,
                    UNRECOGNIZED_NEXT_HEADER,
                    ICMP_ERROR,
                    DESTINATIONS_COPEMISMATCH
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 24;
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
                static bool try_parse(const std::string& val, ping_reply& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, ping_reply& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int val)
                {
                    return _valid(val);
                }
                
                ping_reply() :
                    OMNI_CTOR_FW(omni::net::ping_reply)
                    m_val(DEFAULT_VALUE())
                { }

                ping_reply(const ping_reply& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                ping_reply(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::ping_reply)
                    m_val(val)
                { }

                ~ping_reply()
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

                bool operator!=(const ping_reply& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                ping_reply& operator=(const ping_reply& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                ping_reply& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                ping_reply& operator=(int val)
                {
                    if (!ping_reply::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const ping_reply& val) const
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

                bool operator>(const ping_reply& val) const
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

                bool operator==(const ping_reply& val) const
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

                OMNI_MEMBERS_FW(omni::net::ping_reply) // disposing,name,type(),hash()
                
                OMNI_OSTREAM_FW(omni::net::ping_reply)
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
                static bool _try_parse(const S& val, ping_reply& out)
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
                        OMNI_S2E_FW(SUCCESS)
                        OMNI_S2E_FW(DESTINATION_NETWORK_UNREACHABLE)
                        OMNI_S2E_FW(DESTINATION_HOST_UNREACHABLE)
                        OMNI_S2E_FW(DESTINATION_PROHIBITED)
                        OMNI_S2E_FW(DESTINATION_PROTOCOL_UNREACHABLE)
                        OMNI_S2E_FW(DESTINATION_PORT_UNREACHABLE)
                        OMNI_S2E_FW(NO_RESOURCES)
                        OMNI_S2E_FW(BAD_OPTION)
                        OMNI_S2E_FW(HARDWARE_ERROR)
                        OMNI_S2E_FW(PACKET_TOO_BIG)
                        OMNI_S2E_FW(TIMED_OUT)
                        OMNI_S2E_FW(BAD_ROUTE)
                        OMNI_S2E_FW(TTL_EXPIRED)
                        OMNI_S2E_FW(TTL_REASSEMBLY_TIME_EXCEEDED)
                        OMNI_S2E_FW(PARAMETER_PROBLEM)
                        OMNI_S2E_FW(SOURCE_QUENCH)
                        OMNI_S2E_FW(BAD_DESTINATION)
                        OMNI_S2E_FW(DESTINATION_UNREACHABLE)
                        OMNI_S2E_FW(TIME_EXCEEDED)
                        OMNI_S2E_FW(BAD_HEADER)
                        OMNI_S2E_FW(UNRECOGNIZED_NEXT_HEADER)
                        OMNI_S2E_FW(ICMP_ERROR)
                        OMNI_S2E_FW(DESTINATIONS_COPEMISMATCH)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(SUCCESS);
                        OMNI_E2SS_FW(DESTINATION_NETWORK_UNREACHABLE);
                        OMNI_E2SS_FW(DESTINATION_HOST_UNREACHABLE);
                        OMNI_E2SS_FW(DESTINATION_PROHIBITED);
                        OMNI_E2SS_FW(DESTINATION_PROTOCOL_UNREACHABLE);
                        OMNI_E2SS_FW(DESTINATION_PORT_UNREACHABLE);
                        OMNI_E2SS_FW(NO_RESOURCES);
                        OMNI_E2SS_FW(BAD_OPTION);
                        OMNI_E2SS_FW(HARDWARE_ERROR);
                        OMNI_E2SS_FW(PACKET_TOO_BIG);
                        OMNI_E2SS_FW(TIMED_OUT);
                        OMNI_E2SS_FW(BAD_ROUTE);
                        OMNI_E2SS_FW(TTL_EXPIRED);
                        OMNI_E2SS_FW(TTL_REASSEMBLY_TIME_EXCEEDED);
                        OMNI_E2SS_FW(PARAMETER_PROBLEM);
                        OMNI_E2SS_FW(SOURCE_QUENCH);
                        OMNI_E2SS_FW(BAD_DESTINATION);
                        OMNI_E2SS_FW(DESTINATION_UNREACHABLE);
                        OMNI_E2SS_FW(TIME_EXCEEDED);
                        OMNI_E2SS_FW(BAD_HEADER);
                        OMNI_E2SS_FW(UNRECOGNIZED_NEXT_HEADER);
                        OMNI_E2SS_FW(ICMP_ERROR);
                        OMNI_E2SS_FW(DESTINATIONS_COPEMISMATCH);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val ==
                        UNKNOWN ||
                        SUCCESS ||
                        DESTINATION_NETWORK_UNREACHABLE ||
                        DESTINATION_HOST_UNREACHABLE ||
                        DESTINATION_PROHIBITED ||
                        DESTINATION_PROTOCOL_UNREACHABLE ||
                        DESTINATION_PORT_UNREACHABLE ||
                        NO_RESOURCES ||
                        BAD_OPTION ||
                        HARDWARE_ERROR ||
                        PACKET_TOO_BIG ||
                        TIMED_OUT ||
                        BAD_ROUTE ||
                        TTL_EXPIRED ||
                        TTL_REASSEMBLY_TIME_EXCEEDED ||
                        PARAMETER_PROBLEM ||
                        SOURCE_QUENCH ||
                        BAD_DESTINATION ||
                        DESTINATION_UNREACHABLE ||
                        TIME_EXCEEDED ||
                        BAD_HEADER ||
                        UNRECOGNIZED_NEXT_HEADER ||
                        ICMP_ERROR ||
                        DESTINATIONS_COPEMISMATCH
                    );
                }

                // Gets or sets the ping buffer to send
                //char *buffer;
                // Gets or sets the flag to not fragment the ICMP message
                //bool dont_fragment;
                // Gets or sets the TTL for the ICMP message
                //int ttl;
                // Gets the time it took for the ICMB message to go and come back
                //long round_trip_time;
                // The reply type of this instance
                //omni::net::ping_reply::enum_t status;
                
                /*ping_reply() :
                    buffer(0),
                    dont_fragment(false),
                    ttl(255),
                    round_trim_time(0),
                    status(omni::net::ping_reply::UNKNOWN)
                {}*/
        };
        
        /** protocol_type defines enum values for the protocols that the omni::net::socket class supports. */
        class protocol_type {
            public:
                typedef enum enum_t {
                    UNKNOWN = -1,
                    IPV6_HOP_BY_HOP_OPTIONS = 0,
                    UNSPECIFIED = 0,
                    IP = 0,
                    ICMP = 1,
                    IGMP = 2,
                    GGP = 3,
                    IPV4 = 4,
                    TCP = 6,
                    PUP = 12,
                    UDP = 17,
                    IDP = 22,
                    IPV6 = 41,
                    IPV6_ROUTING_HEADER = 43,
                    IPV6_FRAGMENT_HEADER = 44,
                    IPSEC_ENCAPSULATING_SECURITY_PAYLOAD = 50,
                    IPSEC_AUTHENTICATION_HEADER = 51,
                    ICMPV6 = 58,
                    IPV6_NO_NEXT_HEADER = 59,
                    IPV6_DESTINATION_OPTIONS = 60,
                    ND = 77,
                    RAW = 255,
                    IPX = 1000,
                    SPX = 1256,
                    SPXII = 1257
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 25;
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
                static bool is_valid(int val)
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

                protocol_type& operator=(int val)
                {
                    if (!protocol_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                        //OMNI_S2E_FW(IPV6_HOP_BY_HOP_OPTIONS)
                        //OMNI_S2E_FW(UNSPECIFIED)
                        OMNI_S2E_FW(IP)
                        OMNI_S2E_FW(ICMP)
                        OMNI_S2E_FW(IGMP)
                        OMNI_S2E_FW(GGP)
                        OMNI_S2E_FW(IPV4)
                        OMNI_S2E_FW(TCP)
                        OMNI_S2E_FW(PUP)
                        OMNI_S2E_FW(UDP)
                        OMNI_S2E_FW(IDP)
                        OMNI_S2E_FW(IPV6)
                        OMNI_S2E_FW(IPV6_ROUTING_HEADER)
                        OMNI_S2E_FW(IPV6_FRAGMENT_HEADER)
                        OMNI_S2E_FW(IPSEC_ENCAPSULATING_SECURITY_PAYLOAD)
                        OMNI_S2E_FW(IPSEC_AUTHENTICATION_HEADER)
                        OMNI_S2E_FW(ICMPV6)
                        OMNI_S2E_FW(IPV6_NO_NEXT_HEADER)
                        OMNI_S2E_FW(IPV6_DESTINATION_OPTIONS)
                        OMNI_S2E_FW(ND)
                        OMNI_S2E_FW(RAW)
                        OMNI_S2E_FW(IPX)
                        OMNI_S2E_FW(SPX)
                        OMNI_S2E_FW(SPXII)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        //OMNI_E2SS_FW(IPV6_HOP_BY_HOP_OPTIONS);
                        //OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(IP);
                        OMNI_E2SS_FW(ICMP);
                        OMNI_E2SS_FW(IGMP);
                        OMNI_E2SS_FW(GGP);
                        OMNI_E2SS_FW(IPV4);
                        OMNI_E2SS_FW(TCP);
                        OMNI_E2SS_FW(PUP);
                        OMNI_E2SS_FW(UDP);
                        OMNI_E2SS_FW(IDP);
                        OMNI_E2SS_FW(IPV6);
                        OMNI_E2SS_FW(IPV6_ROUTING_HEADER);
                        OMNI_E2SS_FW(IPV6_FRAGMENT_HEADER);
                        OMNI_E2SS_FW(IPSEC_ENCAPSULATING_SECURITY_PAYLOAD);
                        OMNI_E2SS_FW(IPSEC_AUTHENTICATION_HEADER);
                        OMNI_E2SS_FW(ICMPV6);
                        OMNI_E2SS_FW(IPV6_NO_NEXT_HEADER);
                        OMNI_E2SS_FW(IPV6_DESTINATION_OPTIONS);
                        OMNI_E2SS_FW(ND);
                        OMNI_E2SS_FW(RAW);
                        OMNI_E2SS_FW(IPX);
                        OMNI_E2SS_FW(SPX);
                        OMNI_E2SS_FW(SPXII);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        UNKNOWN ||
                        //IPV6_HOP_BY_HOP_OPTIONS ||
                        //UNSPECIFIED ||
                        IP ||
                        ICMP ||
                        IGMP ||
                        GGP ||
                        IPV4 ||
                        TCP ||
                        PUP ||
                        UDP ||
                        IDP ||
                        IPV6 ||
                        IPV6_ROUTING_HEADER ||
                        IPV6_FRAGMENT_HEADER ||
                        IPSEC_ENCAPSULATING_SECURITY_PAYLOAD ||
                        IPSEC_AUTHENTICATION_HEADER ||
                        ICMPV6 ||
                        IPV6_NO_NEXT_HEADER ||
                        IPV6_DESTINATION_OPTIONS ||
                        ND ||
                        RAW ||
                        IPX ||
                        SPX ||
                        SPXII
                    );
                }
        };

        /** socket_error defines enum values for socket errors codes */
        class socket_error {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    SUCCESS = 0,
                    OPERATION_ABORTED = 995,
                    IO_PENDING = 997,
                    INTERRUPTED = 10004,
                    ACCESS_DENIED = 10013,
                    FAULT = 10014,
                    INVALID_ARGUMENT = 10022,
                    TOO_MANY_OPENSOCKETS = 10024,
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
                    HOST_NOT_FND = 11001,
                    TRYAGAIN = 11002,
                    NORECOVERY = 11003,
                    NODATA = 11004
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 47;
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
                static bool is_valid(int val)
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

                socket_error& operator=(int val)
                {
                    if (!socket_error::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                        OMNI_S2E_FW(TOO_MANY_OPENSOCKETS)
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
                        OMNI_S2E_FW(HOST_NOT_FND)
                        OMNI_S2E_FW(TRYAGAIN)
                        OMNI_S2E_FW(NORECOVERY)
                        OMNI_S2E_FW(NODATA)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
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
                        OMNI_E2SS_FW(TOO_MANY_OPENSOCKETS);
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
                        OMNI_E2SS_FW(HOST_NOT_FND);
                        OMNI_E2SS_FW(TRYAGAIN);
                        OMNI_E2SS_FW(NORECOVERY);
                        OMNI_E2SS_FW(NODATA);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
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
                        TOO_MANY_OPENSOCKETS ||
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
                        HOST_NOT_FND ||
                        TRYAGAIN ||
                        NORECOVERY ||
                        NODATA
                    );
                }
        };
        
        /** socket_flags defines enum values for socket send and receive behaviors. */
        class socket_flags {
            public:
                typedef enum enum_t {
                    NONE = 0,
                    OUT_OF_BAND = 1,
                    PEEK = 2,
                    DONT_ROUTE = 4,
                    MAX_IO_VECTOR_LENGTH = 16,
                    TRUNCATED = 256,
                    CONTROL_DATA_TRUNCATED = 512,
                    BROADCAST = 1024,
                    MULTICAST = 2048,
                    PARTIAL = 32768
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 10;
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
                static bool is_valid(int val)
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

                socket_flags& operator=(int val)
                {
                    if (!socket_flags::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                        OMNI_S2E_FW(MAX_IO_VECTOR_LENGTH)
                        OMNI_S2E_FW(TRUNCATED)
                        OMNI_S2E_FW(CONTROL_DATA_TRUNCATED)
                        OMNI_S2E_FW(BROADCAST)
                        OMNI_S2E_FW(MULTICAST)
                        OMNI_S2E_FW(PARTIAL)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(OUT_OF_BAND);
                        OMNI_E2SS_FW(PEEK);
                        OMNI_E2SS_FW(DONT_ROUTE);
                        OMNI_E2SS_FW(MAX_IO_VECTOR_LENGTH);
                        OMNI_E2SS_FW(TRUNCATED);
                        OMNI_E2SS_FW(CONTROL_DATA_TRUNCATED);
                        OMNI_E2SS_FW(BROADCAST);
                        OMNI_E2SS_FW(MULTICAST);
                        OMNI_E2SS_FW(PARTIAL);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        NONE ||
                        OUT_OF_BAND ||
                        PEEK ||
                        DONT_ROUTE ||
                        MAX_IO_VECTOR_LENGTH ||
                        TRUNCATED ||
                        CONTROL_DATA_TRUNCATED ||
                        BROADCAST ||
                        MULTICAST ||
                        PARTIAL
                    );
                }
        };

        /** select_mode defines enum values for the polling modes for the omni::net::socket::poll method. */
        class select_mode {
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
                static bool is_valid(int val)
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

                select_mode& operator=(int val)
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(NONE);
                        OMNI_E2SS_FW(SELECT_READ);
                        OMNI_E2SS_FW(SELECT_WRITE);
                        OMNI_E2SS_FW(SELECT_ERROR);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        NONE ||
                        SELECT_READ || 
                        SELECT_WRITE || 
                        SELECT_ERROR
                    );
                }
        };

        /** socket_option_level defines enum values for socket option levels for the setsocketoption and getsocketoption methods. */
        class socket_option_level {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    IP = 0,
                    IP6 = 41,
                    TCP = 6,
                    UDP = 17,
                    SOCKET = 65535
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 5;
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
                static bool is_valid(int val)
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

                socket_option_level& operator=(int val)
                {
                    if (!socket_option_level::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(IP);
                        OMNI_E2SS_FW(IP6);
                        OMNI_E2SS_FW(TCP);
                        OMNI_E2SS_FW(UDP);
                        OMNI_E2SS_FW(SOCKET);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
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
        
        /** socket_option_name defines enum values for configuration option names. */
        class socket_option_name {
            public:
                typedef enum enum_t {
                    DONT_LINGER = -129,
                    EXCLUSIVE_ADDRESSUSE = -5,
                    UNSPECIFIED = -1,
                    IPOPTIONS = 1,
                    NO_DELAY = 1,
                    NO_CHECKSUM = 1,
                    DEBUG = 1,
                    BSD_URGENT = 2,
                    EXPEDITED = 2,
                    HEADER_INCLUDED = 2,
                    ACCEPT_CONNECTION = 2,
                    TYPE_OF_SERVICE = 3,
                    REUSE_ADDRESS = 4,
                    IP_TIME_TO_LIVE = 4,
                    KEEP_ALIVE = 8,
                    MULTICAST_INTERFACE = 9,
                    MULTICAST_TIME_TO_LIVE = 10,
                    MULTICAST_LOOPBACK = 11,
                    ADD_MEMBERSHIP = 12,
                    DROP_MEMBERSHIP = 13,
                    DONT_FRAGMENT = 14,
                    ADDSOURCEMEMBERSHIP = 15,
                    DROP_SOURCE_MEMBERSHIP = 16,
                    DONT_ROUTE = 16,
                    BLOCK_SOURCE = 17,
                    UNBLOCK_SOURCE = 18,
                    PACKET_INFORMATION = 19,
                    CHECKSUM_COVERAGE = 20,
                    HOP_LIMIT = 21,
                    IP_PROTECTION_LEVEL = 23,
                    IPV6ONLY = 27,
                    BROADCAST = 32,
                    USE_LOOPBACK = 64,
                    LINGER = 128,
                    OUT_OF_BAND_INLINE = 256,
                    SEND_BUFFER = 4097,
                    RECEIVE_BUFFER = 4098,
                    SEND_LOW_WATER = 4099,
                    RECEIVE_LOW_WATER = 4100,
                    SEND_TIMEOUT = 4101,
                    RECEIVE_TIMEOUT = 4102,
                    ERR = 4103,
                    SOCKET_TYPE = 4104,
                    UPDATE_ACCEPT_CONTEXT = 28683,
                    UPDATE_CONNECT_CONTEXT = 28688,
                    MAX_CONNECTIONS = 2147483647
                } enum_t;
                
                /** Defines the number of elements in the enum */
                static inline unsigned short COUNT()
                {
                    return 45;
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
                static bool try_parse(const std::string& val, socket_option_name& out)
                {
                    return _try_parse(val, out);
                }

                /** Tries parsing a wide string value into its enum representation */
                static bool try_parse(const std::wstring& val, socket_option_name& out)
                {
                    return _try_parse(val, out);
                }

                /** Returns true if the integer value specified is a valid enum value */
                static bool is_valid(int val)
                {
                    return _valid(val);
                }

                socket_option_name() :
                    OMNI_CTOR_FW(omni::net::socket_option_name)
                    m_val(DEFAULT_VALUE())
                { }

                socket_option_name(const socket_option_name& cp) :
                    OMNI_CPCTOR_FW(cp)
                    m_val(cp.m_val)
                { }

                socket_option_name(enum_t val) : 
                    OMNI_CTOR_FW(omni::net::socket_option_name)
                    m_val(val)
                { }

                ~socket_option_name()
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

                bool operator!=(const socket_option_name& val) const
                {
                    return !(*this == val);
                }
                
                bool operator!=(enum_t val) const
                {
                    return (this->m_val != val);
                }
                
                socket_option_name& operator=(const socket_option_name& val)
                {
                    if (this != &val) {
                        OMNI_ASSIGN_FW(val)
                        this->m_val = val.m_val;
                    }
                    return *this;
                }

                socket_option_name& operator=(enum_t val)
                {
                    this->m_val = val;
                    return *this;
                }

                socket_option_name& operator=(int val)
                {
                    if (!socket_option_name::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
                    return *this;
                }

                bool operator<(const socket_option_name& val) const
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

                bool operator>(const socket_option_name& val) const
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

                bool operator==(const socket_option_name& val) const
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

                OMNI_MEMBERS_FW(omni::net::socket_option_name) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket_option_name)
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
                static bool _try_parse(const S& val, socket_option_name& out)
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
                        OMNI_S2E_FW(EXCLUSIVE_ADDRESSUSE)
                        OMNI_S2E_FW(UNSPECIFIED)
                        //OMNI_S2E_FW(IPOPTIONS)
                        OMNI_S2E_FW(NO_DELAY)
                        //OMNI_S2E_FW(NO_CHECKSUM)
                        //OMNI_S2E_FW(DEBUG)
                        OMNI_S2E_FW(BSD_URGENT)
                        //OMNI_S2E_FW(EXPEDITED)
                        //OMNI_S2E_FW(HEADER_INCLUDED)
                        //OMNI_S2E_FW(ACCEPT_CONNECTION)
                        OMNI_S2E_FW(TYPE_OF_SERVICE)
                        //OMNI_S2E_FW(REUSE_ADDRESS)
                        OMNI_S2E_FW(IP_TIME_TO_LIVE)
                        OMNI_S2E_FW(KEEP_ALIVE)
                        OMNI_S2E_FW(MULTICAST_INTERFACE)
                        OMNI_S2E_FW(MULTICAST_TIME_TO_LIVE)
                        OMNI_S2E_FW(MULTICAST_LOOPBACK)
                        OMNI_S2E_FW(ADD_MEMBERSHIP)
                        OMNI_S2E_FW(DROP_MEMBERSHIP)
                        OMNI_S2E_FW(DONT_FRAGMENT)
                        OMNI_S2E_FW(ADDSOURCEMEMBERSHIP)
                        //OMNI_S2E_FW(DROP_SOURCE_MEMBERSHIP)
                        OMNI_S2E_FW(DONT_ROUTE)
                        OMNI_S2E_FW(BLOCK_SOURCE)
                        OMNI_S2E_FW(UNBLOCK_SOURCE)
                        OMNI_S2E_FW(PACKET_INFORMATION)
                        OMNI_S2E_FW(CHECKSUM_COVERAGE)
                        OMNI_S2E_FW(HOP_LIMIT)
                        OMNI_S2E_FW(IP_PROTECTION_LEVEL)
                        OMNI_S2E_FW(IPV6ONLY)
                        OMNI_S2E_FW(BROADCAST)
                        OMNI_S2E_FW(USE_LOOPBACK)
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
                        OMNI_S2E_FW(UPDATE_ACCEPT_CONTEXT)
                        OMNI_S2E_FW(UPDATE_CONNECT_CONTEXT)
                        OMNI_S2E_FW(MAX_CONNECTIONS)
                    }
                    return false;
                }

                template < typename S >
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(DONT_LINGER);
                        OMNI_E2SS_FW(EXCLUSIVE_ADDRESSUSE);
                        OMNI_E2SS_FW(UNSPECIFIED);
                        //OMNI_E2SS_FW(IPOPTIONS);
                        OMNI_E2SS_FW(NO_DELAY);
                        //OMNI_E2SS_FW(NO_CHECKSUM);
                        //OMNI_E2SS_FW(DEBUG);
                        OMNI_E2SS_FW(BSD_URGENT);
                        //OMNI_E2SS_FW(EXPEDITED);
                        //OMNI_E2SS_FW(HEADER_INCLUDED);
                        //OMNI_E2SS_FW(ACCEPT_CONNECTION);
                        OMNI_E2SS_FW(TYPE_OF_SERVICE);
                        //OMNI_E2SS_FW(REUSE_ADDRESS);
                        OMNI_E2SS_FW(IP_TIME_TO_LIVE);
                        OMNI_E2SS_FW(KEEP_ALIVE);
                        OMNI_E2SS_FW(MULTICAST_INTERFACE);
                        OMNI_E2SS_FW(MULTICAST_TIME_TO_LIVE);
                        OMNI_E2SS_FW(MULTICAST_LOOPBACK);
                        OMNI_E2SS_FW(ADD_MEMBERSHIP);
                        OMNI_E2SS_FW(DROP_MEMBERSHIP);
                        OMNI_E2SS_FW(DONT_FRAGMENT);
                        OMNI_E2SS_FW(ADDSOURCEMEMBERSHIP);
                        //OMNI_E2SS_FW(DROP_SOURCE_MEMBERSHIP);
                        OMNI_E2SS_FW(DONT_ROUTE);
                        OMNI_E2SS_FW(BLOCK_SOURCE);
                        OMNI_E2SS_FW(UNBLOCK_SOURCE);
                        OMNI_E2SS_FW(PACKET_INFORMATION);
                        OMNI_E2SS_FW(CHECKSUM_COVERAGE);
                        OMNI_E2SS_FW(HOP_LIMIT);
                        OMNI_E2SS_FW(IP_PROTECTION_LEVEL);
                        OMNI_E2SS_FW(IPV6ONLY);
                        OMNI_E2SS_FW(BROADCAST);
                        OMNI_E2SS_FW(USE_LOOPBACK);
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
                        OMNI_E2SS_FW(UPDATE_ACCEPT_CONTEXT);
                        OMNI_E2SS_FW(UPDATE_CONNECT_CONTEXT);
                        OMNI_E2SS_FW(MAX_CONNECTIONS);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        DONT_LINGER ||
                        EXCLUSIVE_ADDRESSUSE ||
                        UNSPECIFIED ||
                        //IPOPTIONS ||
                        NO_DELAY ||
                        //NO_CHECKSUM ||
                        //DEBUG ||
                        BSD_URGENT ||
                        //EXPEDITED ||
                        //HEADER_INCLUDED ||
                        //ACCEPT_CONNECTION ||
                        TYPE_OF_SERVICE ||
                        //REUSE_ADDRESS ||
                        IP_TIME_TO_LIVE ||
                        KEEP_ALIVE ||
                        MULTICAST_INTERFACE ||
                        MULTICAST_TIME_TO_LIVE ||
                        MULTICAST_LOOPBACK ||
                        ADD_MEMBERSHIP ||
                        DROP_MEMBERSHIP ||
                        DONT_FRAGMENT ||
                        ADDSOURCEMEMBERSHIP ||
                        //DROP_SOURCE_MEMBERSHIP ||
                        DONT_ROUTE ||
                        BLOCK_SOURCE ||
                        UNBLOCK_SOURCE ||
                        PACKET_INFORMATION ||
                        CHECKSUM_COVERAGE ||
                        HOP_LIMIT ||
                        IP_PROTECTION_LEVEL ||
                        IPV6ONLY ||
                        BROADCAST ||
                        USE_LOOPBACK ||
                        LINGER ||
                        OUT_OF_BAND_INLINE ||
                        SEND_BUFFER ||
                        RECEIVE_BUFFER ||
                        SEND_LOW_WATER ||
                        RECEIVE_LOW_WATER ||
                        SEND_TIMEOUT ||
                        RECEIVE_TIMEOUT ||
                        ERR ||
                        SOCKET_TYPE ||
                        UPDATE_ACCEPT_CONTEXT ||
                        UPDATE_CONNECT_CONTEXT ||
                        MAX_CONNECTIONS
                    );
                }
        };

        /** socket_shutdown defines enum values for constants that are used by the omni::net::socket::shutdown method. */
        class socket_shutdown {
            public:
                typedef enum enum_t {
                    UNSPECIFIED = -1,
                    RECEIVE = 0,
                    SEND = 1,
                    BOTH = 2
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
                static bool is_valid(int val)
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

                socket_shutdown& operator=(int val)
                {
                    if (!socket_shutdown::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNSPECIFIED);
                        OMNI_E2SS_FW(RECEIVE);
                        OMNI_E2SS_FW(SEND);
                        OMNI_E2SS_FW(BOTH);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
                {
                    return (val == 
                        UNSPECIFIED ||
                        RECEIVE || 
                        SEND || 
                        BOTH
                    );
                }
        };
        
        /** socket_type defines enum values for the type of socket that an instance of the omni::net::socket::socket class represents. */
        class socket_type {
            public:
                typedef enum enum_t {
                    UNKNOWN = -1,
                    STREAM = 1,
                    DGRAM = 2,
                    RAW = 3,
                    RDM = 4,
                    SEQPACKET = 5
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
                static bool is_valid(int val)
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

                socket_type& operator=(int val)
                {
                    if (!socket_type::is_valid(val)) {
                        OMNI_ERR_RET_FW("Invalid enumeration value specified.", omni::exceptions::invalid_enum(val));
                    } else {
                        this->m_val = static_cast<enum_t>(val);
                    }
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

                bool operator<(int val) const
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

                bool operator>(int val) const
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
                    OMNI_ERRV_FW("invalid enum parse: ", val, omni::exceptions::invalid_enum())
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
                static typename S::string_type _to_val(enum_t v)
                {
                    S ss;
                    switch (v) {
                        OMNI_E2SS_FW(UNKNOWN);
                        OMNI_E2SS_FW(STREAM);
                        OMNI_E2SS_FW(DGRAM);
                        OMNI_E2SS_FW(RAW);
                        OMNI_E2SS_FW(RDM);
                        OMNI_E2SS_FW(SEQPACKET);
                        default: ss << "UNKNOWN"; break;
                    }
                    return ss.str();
                }

                static bool _valid(int val)
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
    
        /*
        #if !defined(SOCK_RECEIVE)
            #define SOCK_RECEIVE 0
        #endif
        #if !defined(SOCK_SEND)
            #define SOCK_SEND 1
        #endif
        #if !defined(SOCK_BOTH)
            #define SOCK_BOTH 2
        #endif
        #if !defined(OMNI_OS_WIN)
            #if !defined(SOCKET)
                #define SOCKET int
            #endif
        #endif
        */
        
        /**
         * Specifies whether a  will remain connected after a call to the Close()
         * or TcpClient.Close() methods and the length of time it will remain connected, if data remains to be sent.
         */
        typedef struct linger_option {
            /** The default constructor */
            linger_option() : enabled(false), linger_time(0) { }
            /**
             * Initializes a new instance of the linger_option class.
             * @param enable true to remain connected after the Close() method is called; otherwise, false.
             * @param seconds The number of seconds to remain connected after the Close() method is called.
             */
            linger_option(bool enable, int seconds) : enabled(enable), linger_time(seconds) { }
            /**
             * Gets or sets a value that indicates whether to linger after the 
             * is closed.
             * 
             * @return true if the  should linger after Close() is called; otherwise, false.                
             */
            bool enabled;
            /**
             * Gets or sets the amount of time to remain connected after calling the Close()
             * method if data remains to be sent.
             * 
             * @return The amount of time, in seconds, to remain connected after calling Close().
             */
            int linger_time;
        } linger_option;
        
        /* A struct to hold network interface information 
        typedef struct net_interface {
            // Gets the IP address associated with this interface (if any) 
            std::string address;
            // Gets the subnet mask of this interface (if any) 
            std::string subnet;
            // Gets the broadcast of this interface (if any) 
            std::string broadcast;
            // Gets the speed of this interface 
            long speed;
            // Gets the network adapter description 
            std::string description;
            // Gets if the interface is currently up or down 
            bool is_up;
            // Gets the interface type of this interface 
            omni::net::network_interface::enum_t type;
        } net_interface;*/
    }
}

#endif // OMNI_NET_T_HPP
