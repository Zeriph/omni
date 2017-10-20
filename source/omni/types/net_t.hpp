/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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

namespace omni {
    /** The net namespace is used to facilitate certain networking operations and handling */
    namespace net {
        /** address_family defines enum values for the addressing scheme that an instance of the omni::net::socket class can use. */
        typedef struct address_family {
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
                NETWORK_DESIGNERS = 28,
                MAX = 29
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 31;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(UNKNOWN);
                    OMNI_E2S_FW(UNSPECIFIED);
                    OMNI_E2S_FW(UNIX);
                    OMNI_E2S_FW(INTERNETWORK);
                    OMNI_E2S_FW(IMPLINK);
                    OMNI_E2S_FW(PUP);
                    OMNI_E2S_FW(CHAOS);
                    OMNI_E2S_FW(IPX);
                    OMNI_E2S_FW(NS);
                    OMNI_E2S_FW(OSI);
                    OMNI_E2S_FW(ISO);
                    OMNI_E2S_FW(ECMA);
                    OMNI_E2S_FW(DATAKIT);
                    OMNI_E2S_FW(CCITT);
                    OMNI_E2S_FW(SNA);
                    OMNI_E2S_FW(DECNET);
                    OMNI_E2S_FW(DATALINK);
                    OMNI_E2S_FW(LAT);
                    OMNI_E2S_FW(HYPERCHANNEL);
                    OMNI_E2S_FW(APPLETALK);
                    OMNI_E2S_FW(NETBIOS);
                    OMNI_E2S_FW(VOICEVIEW);
                    OMNI_E2S_FW(FIREFOX);
                    OMNI_E2S_FW(BANYAN);
                    OMNI_E2S_FW(ATM);
                    OMNI_E2S_FW(INTERNETWORK_V6);
                    OMNI_E2S_FW(CLUSTER);
                    OMNI_E2S_FW(IEEE12844);
                    OMNI_E2S_FW(IRDA);
                    OMNI_E2S_FW(NETWORK_DESIGNERS);
                    OMNI_E2S_FW(MAX);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(UNKNOWN);
                    OMNI_E2WS_FW(UNSPECIFIED);
                    OMNI_E2WS_FW(UNIX);
                    OMNI_E2WS_FW(INTERNETWORK);
                    OMNI_E2WS_FW(IMPLINK);
                    OMNI_E2WS_FW(PUP);
                    OMNI_E2WS_FW(CHAOS);
                    OMNI_E2WS_FW(IPX);
                    OMNI_E2WS_FW(NS);
                    OMNI_E2WS_FW(OSI);
                    OMNI_E2WS_FW(ISO);
                    OMNI_E2WS_FW(ECMA);
                    OMNI_E2WS_FW(DATAKIT);
                    OMNI_E2WS_FW(CCITT);
                    OMNI_E2WS_FW(SNA);
                    OMNI_E2WS_FW(DECNET);
                    OMNI_E2WS_FW(DATALINK);
                    OMNI_E2WS_FW(LAT);
                    OMNI_E2WS_FW(HYPERCHANNEL);
                    OMNI_E2WS_FW(APPLETALK);
                    OMNI_E2WS_FW(NETBIOS);
                    OMNI_E2WS_FW(VOICEVIEW);
                    OMNI_E2WS_FW(FIREFOX);
                    OMNI_E2WS_FW(BANYAN);
                    OMNI_E2WS_FW(ATM);
                    OMNI_E2WS_FW(INTERNETWORK_V6);
                    OMNI_E2WS_FW(CLUSTER);
                    OMNI_E2WS_FW(IEEE12844);
                    OMNI_E2WS_FW(IRDA);
                    OMNI_E2WS_FW(NETWORK_DESIGNERS);
                    OMNI_E2WS_FW(MAX);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } address_family;
        
        /** network_interface defines enum values for what kind of interface the network card is */
        typedef struct network_interface {
            typedef enum enum_t {
                LOOPBACK = 0,
                ETHERNET,
                WIRELESS
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 3;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(LOOPBACK);
                    OMNI_E2S_FW(ETHERNET);
                    OMNI_E2S_FW(WIRELESS);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(LOOPBACK);
                    OMNI_E2WS_FW(ETHERNET);
                    OMNI_E2WS_FW(WIRELESS);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        };
        
        /** ping_reply defines enum values for reply information received from a ping request */
        typedef struct ping_reply {
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
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 24;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(UNKNOWN);
                    OMNI_E2S_FW(SUCCESS);
                    OMNI_E2S_FW(DESTINATION_NETWORK_UNREACHABLE);
                    OMNI_E2S_FW(DESTINATION_HOST_UNREACHABLE);
                    OMNI_E2S_FW(DESTINATION_PROHIBITED);
                    OMNI_E2S_FW(DESTINATION_PROTOCOL_UNREACHABLE);
                    OMNI_E2S_FW(DESTINATION_PORT_UNREACHABLE);
                    OMNI_E2S_FW(NO_RESOURCES);
                    OMNI_E2S_FW(BAD_OPTION);
                    OMNI_E2S_FW(HARDWARE_ERROR);
                    OMNI_E2S_FW(PACKET_TOO_BIG);
                    OMNI_E2S_FW(TIMED_OUT);
                    OMNI_E2S_FW(BAD_ROUTE);
                    OMNI_E2S_FW(TTL_EXPIRED);
                    OMNI_E2S_FW(TTL_REASSEMBLY_TIME_EXCEEDED);
                    OMNI_E2S_FW(PARAMETER_PROBLEM);
                    OMNI_E2S_FW(SOURCE_QUENCH);
                    OMNI_E2S_FW(BAD_DESTINATION);
                    OMNI_E2S_FW(DESTINATION_UNREACHABLE);
                    OMNI_E2S_FW(TIME_EXCEEDED);
                    OMNI_E2S_FW(BAD_HEADER);
                    OMNI_E2S_FW(UNRECOGNIZED_NEXT_HEADER);
                    OMNI_E2S_FW(ICMP_ERROR);
                    OMNI_E2S_FW(DESTINATIONS_COPEMISMATCH);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(UNKNOWN);
                    OMNI_E2WS_FW(SUCCESS);
                    OMNI_E2WS_FW(DESTINATION_NETWORK_UNREACHABLE);
                    OMNI_E2WS_FW(DESTINATION_HOST_UNREACHABLE);
                    OMNI_E2WS_FW(DESTINATION_PROHIBITED);
                    OMNI_E2WS_FW(DESTINATION_PROTOCOL_UNREACHABLE);
                    OMNI_E2WS_FW(DESTINATION_PORT_UNREACHABLE);
                    OMNI_E2WS_FW(NO_RESOURCES);
                    OMNI_E2WS_FW(BAD_OPTION);
                    OMNI_E2WS_FW(HARDWARE_ERROR);
                    OMNI_E2WS_FW(PACKET_TOO_BIG);
                    OMNI_E2WS_FW(TIMED_OUT);
                    OMNI_E2WS_FW(BAD_ROUTE);
                    OMNI_E2WS_FW(TTL_EXPIRED);
                    OMNI_E2WS_FW(TTL_REASSEMBLY_TIME_EXCEEDED);
                    OMNI_E2WS_FW(PARAMETER_PROBLEM);
                    OMNI_E2WS_FW(SOURCE_QUENCH);
                    OMNI_E2WS_FW(BAD_DESTINATION);
                    OMNI_E2WS_FW(DESTINATION_UNREACHABLE);
                    OMNI_E2WS_FW(TIME_EXCEEDED);
                    OMNI_E2WS_FW(BAD_HEADER);
                    OMNI_E2WS_FW(UNRECOGNIZED_NEXT_HEADER);
                    OMNI_E2WS_FW(ICMP_ERROR);
                    OMNI_E2WS_FW(DESTINATIONS_COPEMISMATCH);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
            
            
            /** Gets or sets the ping buffer to send */
            char *buffer;
            /** Gets or sets the flag to not fragment the ICMP message */
            bool dont_fragment;
            /** Gets or sets the TTL for the ICMP message */
            int ttl;
            /** Gets the time it took for the ICMB message to go and come back */
            long round_trip_time;
            /** The reply type of this instance */
            omni::net::ping_reply::enum_t status;
            
            ping_reply() :
                buffer(0),
                dont_fragment(false),
                ttl(255),
                round_trim_time(0),
                status(omni::net::ping_reply::UNKNOWN)
            {}
        } ping_reply;
        
        /** protocol_type defines enum values for the protocols that the omni::net::socket class supports. */
        typedef struct protocol_type {
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
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 25;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(UNKNOWN);
                    OMNI_E2S_FW(IPV6_HOP_BY_HOP_OPTIONS);
                    OMNI_E2S_FW(UNSPECIFIED);
                    OMNI_E2S_FW(IP);
                    OMNI_E2S_FW(ICMP);
                    OMNI_E2S_FW(IGMP);
                    OMNI_E2S_FW(GGP);
                    OMNI_E2S_FW(IPV4);
                    OMNI_E2S_FW(TCP);
                    OMNI_E2S_FW(PUP);
                    OMNI_E2S_FW(UDP);
                    OMNI_E2S_FW(IDP);
                    OMNI_E2S_FW(IPV6);
                    OMNI_E2S_FW(IPV6_ROUTING_HEADER);
                    OMNI_E2S_FW(IPV6_FRAGMENT_HEADER);
                    OMNI_E2S_FW(IPSEC_ENCAPSULATING_SECURITY_PAYLOAD);
                    OMNI_E2S_FW(IPSEC_AUTHENTICATION_HEADER);
                    OMNI_E2S_FW(ICMPV6);
                    OMNI_E2S_FW(IPV6_NO_NEXT_HEADER);
                    OMNI_E2S_FW(IPV6_DESTINATION_OPTIONS);
                    OMNI_E2S_FW(ND);
                    OMNI_E2S_FW(RAW);
                    OMNI_E2S_FW(IPX);
                    OMNI_E2S_FW(SPX);
                    OMNI_E2S_FW(SPXII);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(UNKNOWN);
                    OMNI_E2WS_FW(IPV6_HOP_BY_HOP_OPTIONS);
                    OMNI_E2WS_FW(UNSPECIFIED);
                    OMNI_E2WS_FW(IP);
                    OMNI_E2WS_FW(ICMP);
                    OMNI_E2WS_FW(IGMP);
                    OMNI_E2WS_FW(GGP);
                    OMNI_E2WS_FW(IPV4);
                    OMNI_E2WS_FW(TCP);
                    OMNI_E2WS_FW(PUP);
                    OMNI_E2WS_FW(UDP);
                    OMNI_E2WS_FW(IDP);
                    OMNI_E2WS_FW(IPV6);
                    OMNI_E2WS_FW(IPV6_ROUTING_HEADER);
                    OMNI_E2WS_FW(IPV6_FRAGMENT_HEADER);
                    OMNI_E2WS_FW(IPSEC_ENCAPSULATING_SECURITY_PAYLOAD);
                    OMNI_E2WS_FW(IPSEC_AUTHENTICATION_HEADER);
                    OMNI_E2WS_FW(ICMPV6);
                    OMNI_E2WS_FW(IPV6_NO_NEXT_HEADER);
                    OMNI_E2WS_FW(IPV6_DESTINATION_OPTIONS);
                    OMNI_E2WS_FW(ND);
                    OMNI_E2WS_FW(RAW);
                    OMNI_E2WS_FW(IPX);
                    OMNI_E2WS_FW(SPX);
                    OMNI_E2WS_FW(SPXII);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } protocol_type;

        /** socket_error defines enum values for socket errors codes */
        typedef struct socket_error {
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
                HST_NOT_FND = 11001,
                TRYAGAIN = 11002,
                NORECOVERY = 11003,
                NODATA = 11004
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 47;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(UNSPECIFIED);
                    OMNI_E2S_FW(SUCCESS);
                    OMNI_E2S_FW(OPERATION_ABORTED);
                    OMNI_E2S_FW(IO_PENDING);
                    OMNI_E2S_FW(INTERRUPTED);
                    OMNI_E2S_FW(ACCESS_DENIED);
                    OMNI_E2S_FW(FAULT);
                    OMNI_E2S_FW(INVALID_ARGUMENT);
                    OMNI_E2S_FW(TOO_MANY_OPENSOCKETS);
                    OMNI_E2S_FW(WOULD_BLOCK);
                    OMNI_E2S_FW(IN_PROGRESS);
                    OMNI_E2S_FW(ALREADY_IN_PROGRESS);
                    OMNI_E2S_FW(NOT_SOCKET);
                    OMNI_E2S_FW(DESTINATION_ADDRESS_REQUIRED);
                    OMNI_E2S_FW(MESSAGE_SIZE);
                    OMNI_E2S_FW(PROTOCOL_TYPE);
                    OMNI_E2S_FW(PROTOCOL_OPTION);
                    OMNI_E2S_FW(PROTOCOL_NOT_SUPPORTED);
                    OMNI_E2S_FW(SOCKET_NOT_SUPPORTED);
                    OMNI_E2S_FW(OPERATION_NOT_SUPPORTED);
                    OMNI_E2S_FW(PROTOCOL_FAMILY_NOT_SUPPORTED);
                    OMNI_E2S_FW(ADDRESS_FAMILY_NOT_SUPPORTED);
                    OMNI_E2S_FW(ADDRESS_ALREADY_IN_USE);
                    OMNI_E2S_FW(ADDRESS_NOT_AVAILABLE);
                    OMNI_E2S_FW(NETWORK_DOWN);
                    OMNI_E2S_FW(NETWORK_UNREACHABLE);
                    OMNI_E2S_FW(NETWORK_RESET);
                    OMNI_E2S_FW(CONNECTION_ABORTED);
                    OMNI_E2S_FW(CONNECTION_RESET);
                    OMNI_E2S_FW(NO_BUFFER_SPACE_AVAILABLE);
                    OMNI_E2S_FW(IS_CONNECTED);
                    OMNI_E2S_FW(NOT_CONNECTED);
                    OMNI_E2S_FW(SHUTDOWN);
                    OMNI_E2S_FW(TIMED_OUT);
                    OMNI_E2S_FW(CONNECTION_REFUSED);
                    OMNI_E2S_FW(HOST_DOWN);
                    OMNI_E2S_FW(HOST_UNREACHABLE);
                    OMNI_E2S_FW(PROCESS_LIMIT);
                    OMNI_E2S_FW(SYSTEM_NOT_READY);
                    OMNI_E2S_FW(VERSION_NOT_SUPPORTED);
                    OMNI_E2S_FW(NOT_INITIALIZED);
                    OMNI_E2S_FW(DISCONNECTING);
                    OMNI_E2S_FW(TYPE_NOT_FOUND);
                    OMNI_E2S_FW(HST_NOT_FND);
                    OMNI_E2S_FW(TRYAGAIN);
                    OMNI_E2S_FW(NORECOVERY);
                    OMNI_E2S_FW(NODATA);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(UNSPECIFIED);
                    OMNI_E2WS_FW(SUCCESS);
                    OMNI_E2WS_FW(OPERATION_ABORTED);
                    OMNI_E2WS_FW(IO_PENDING);
                    OMNI_E2WS_FW(INTERRUPTED);
                    OMNI_E2WS_FW(ACCESS_DENIED);
                    OMNI_E2WS_FW(FAULT);
                    OMNI_E2WS_FW(INVALID_ARGUMENT);
                    OMNI_E2WS_FW(TOO_MANY_OPENSOCKETS);
                    OMNI_E2WS_FW(WOULD_BLOCK);
                    OMNI_E2WS_FW(IN_PROGRESS);
                    OMNI_E2WS_FW(ALREADY_IN_PROGRESS);
                    OMNI_E2WS_FW(NOT_SOCKET);
                    OMNI_E2WS_FW(DESTINATION_ADDRESS_REQUIRED);
                    OMNI_E2WS_FW(MESSAGE_SIZE);
                    OMNI_E2WS_FW(PROTOCOL_TYPE);
                    OMNI_E2WS_FW(PROTOCOL_OPTION);
                    OMNI_E2WS_FW(PROTOCOL_NOT_SUPPORTED);
                    OMNI_E2WS_FW(SOCKET_NOT_SUPPORTED);
                    OMNI_E2WS_FW(OPERATION_NOT_SUPPORTED);
                    OMNI_E2WS_FW(PROTOCOL_FAMILY_NOT_SUPPORTED);
                    OMNI_E2WS_FW(ADDRESS_FAMILY_NOT_SUPPORTED);
                    OMNI_E2WS_FW(ADDRESS_ALREADY_IN_USE);
                    OMNI_E2WS_FW(ADDRESS_NOT_AVAILABLE);
                    OMNI_E2WS_FW(NETWORK_DOWN);
                    OMNI_E2WS_FW(NETWORK_UNREACHABLE);
                    OMNI_E2WS_FW(NETWORK_RESET);
                    OMNI_E2WS_FW(CONNECTION_ABORTED);
                    OMNI_E2WS_FW(CONNECTION_RESET);
                    OMNI_E2WS_FW(NO_BUFFER_SPACE_AVAILABLE);
                    OMNI_E2WS_FW(IS_CONNECTED);
                    OMNI_E2WS_FW(NOT_CONNECTED);
                    OMNI_E2WS_FW(SHUTDOWN);
                    OMNI_E2WS_FW(TIMED_OUT);
                    OMNI_E2WS_FW(CONNECTION_REFUSED);
                    OMNI_E2WS_FW(HOST_DOWN);
                    OMNI_E2WS_FW(HOST_UNREACHABLE);
                    OMNI_E2WS_FW(PROCESS_LIMIT);
                    OMNI_E2WS_FW(SYSTEM_NOT_READY);
                    OMNI_E2WS_FW(VERSION_NOT_SUPPORTED);
                    OMNI_E2WS_FW(NOT_INITIALIZED);
                    OMNI_E2WS_FW(DISCONNECTING);
                    OMNI_E2WS_FW(TYPE_NOT_FOUND);
                    OMNI_E2WS_FW(HST_NOT_FND);
                    OMNI_E2WS_FW(TRYAGAIN);
                    OMNI_E2WS_FW(NORECOVERY);
                    OMNI_E2WS_FW(NODATA);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } socket_error;
        
        /** socket_flags defines enum values for socket send and receive behaviors. */
        typedef struct socket_flags {
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
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 10;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(NONE);
                    OMNI_E2S_FW(OUT_OF_BAND);
                    OMNI_E2S_FW(PEEK);
                    OMNI_E2S_FW(DONT_ROUTE);
                    OMNI_E2S_FW(MAX_IO_VECTOR_LENGTH);
                    OMNI_E2S_FW(TRUNCATED);
                    OMNI_E2S_FW(CONTROL_DATA_TRUNCATED);
                    OMNI_E2S_FW(BROADCAST);
                    OMNI_E2S_FW(MULTICAST);
                    OMNI_E2S_FW(PARTIAL);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(NONE);
                    OMNI_E2WS_FW(OUT_OF_BAND);
                    OMNI_E2WS_FW(PEEK);
                    OMNI_E2WS_FW(DONT_ROUTE);
                    OMNI_E2WS_FW(MAX_IO_VECTOR_LENGTH);
                    OMNI_E2WS_FW(TRUNCATED);
                    OMNI_E2WS_FW(CONTROL_DATA_TRUNCATED);
                    OMNI_E2WS_FW(BROADCAST);
                    OMNI_E2WS_FW(MULTICAST);
                    OMNI_E2WS_FW(PARTIAL);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } socket_flags;

        /** select_mode defines enum values for the polling modes for the omni::net::socket::poll method. */
        typedef struct select_mode {
            typedef enum enum_t {
                SELECT_READ = 0,
                SELECT_WRITE = 1,
                SELECT_ERROR = 2
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 3;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(SELECT_READ);
                    OMNI_E2S_FW(SELECT_WRITE);
                    OMNI_E2S_FW(SELECT_ERROR);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(SELECT_READ);
                    OMNI_E2WS_FW(SELECT_WRITE);
                    OMNI_E2WS_FW(SELECT_ERROR);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } select_mode;

        /** socket_option_level defines enum values for socket option levels for the setsocketoption and getsocketoption methods. */
        typedef struct socket_option_level {
            typedef enum enum_t {
                IP = 0,
                IP6 = 41,
                TCP = 6,
                UDP = 17,
                SOCKET = 65535
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 5;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(IP);
                    OMNI_E2S_FW(IP6);
                    OMNI_E2S_FW(TCP);
                    OMNI_E2S_FW(UDP);
                    OMNI_E2S_FW(SOCKET);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(IP);
                    OMNI_E2WS_FW(IP6);
                    OMNI_E2WS_FW(TCP);
                    OMNI_E2WS_FW(UDP);
                    OMNI_E2WS_FW(SOCKET);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } socket_option_level;
        
        /** socket_option_name defines enum values for configuration option names. */
        typedef struct socket_option_name {
            typedef enum enum_t {
                DONT_LINGER = -129,
                EXCLUSIVE_ADDRESSUSE = -5,
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
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 45;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(DONT_LINGER);
                    OMNI_E2S_FW(EXCLUSIVE_ADDRESSUSE);
                    OMNI_E2S_FW(IPOPTIONS);
                    OMNI_E2S_FW(NO_DELAY);
                    OMNI_E2S_FW(NO_CHECKSUM);
                    OMNI_E2S_FW(DEBUG);
                    OMNI_E2S_FW(BSD_URGENT);
                    OMNI_E2S_FW(EXPEDITED);
                    OMNI_E2S_FW(HEADER_INCLUDED);
                    OMNI_E2S_FW(ACCEPT_CONNECTION);
                    OMNI_E2S_FW(TYPE_OF_SERVICE);
                    OMNI_E2S_FW(REUSE_ADDRESS);
                    OMNI_E2S_FW(IP_TIME_TO_LIVE);
                    OMNI_E2S_FW(KEEP_ALIVE);
                    OMNI_E2S_FW(MULTICAST_INTERFACE);
                    OMNI_E2S_FW(MULTICAST_TIME_TO_LIVE);
                    OMNI_E2S_FW(MULTICAST_LOOPBACK);
                    OMNI_E2S_FW(ADD_MEMBERSHIP);
                    OMNI_E2S_FW(DROP_MEMBERSHIP);
                    OMNI_E2S_FW(DONT_FRAGMENT);
                    OMNI_E2S_FW(ADDSOURCEMEMBERSHIP);
                    OMNI_E2S_FW(DROP_SOURCE_MEMBERSHIP);
                    OMNI_E2S_FW(DONT_ROUTE);
                    OMNI_E2S_FW(BLOCK_SOURCE);
                    OMNI_E2S_FW(UNBLOCK_SOURCE);
                    OMNI_E2S_FW(PACKET_INFORMATION);
                    OMNI_E2S_FW(CHECKSUM_COVERAGE);
                    OMNI_E2S_FW(HOP_LIMIT);
                    OMNI_E2S_FW(IP_PROTECTION_LEVEL);
                    OMNI_E2S_FW(IPV6ONLY);
                    OMNI_E2S_FW(BROADCAST);
                    OMNI_E2S_FW(USE_LOOPBACK);
                    OMNI_E2S_FW(LINGER);
                    OMNI_E2S_FW(OUT_OF_BAND_INLINE);
                    OMNI_E2S_FW(SEND_BUFFER);
                    OMNI_E2S_FW(RECEIVE_BUFFER);
                    OMNI_E2S_FW(SEND_LOW_WATER);
                    OMNI_E2S_FW(RECEIVE_LOW_WATER);
                    OMNI_E2S_FW(SEND_TIMEOUT);
                    OMNI_E2S_FW(RECEIVE_TIMEOUT);
                    OMNI_E2S_FW(ERR);
                    OMNI_E2S_FW(SOCKET_TYPE);
                    OMNI_E2S_FW(UPDATE_ACCEPT_CONTEXT);
                    OMNI_E2S_FW(UPDATE_CONNECT_CONTEXT);
                    OMNI_E2S_FW(MAX_CONNECTIONS);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(DONT_LINGER);
                    OMNI_E2WS_FW(EXCLUSIVE_ADDRESSUSE);
                    OMNI_E2WS_FW(IPOPTIONS);
                    OMNI_E2WS_FW(NO_DELAY);
                    OMNI_E2WS_FW(NO_CHECKSUM);
                    OMNI_E2WS_FW(DEBUG);
                    OMNI_E2WS_FW(BSD_URGENT);
                    OMNI_E2WS_FW(EXPEDITED);
                    OMNI_E2WS_FW(HEADER_INCLUDED);
                    OMNI_E2WS_FW(ACCEPT_CONNECTION);
                    OMNI_E2WS_FW(TYPE_OF_SERVICE);
                    OMNI_E2WS_FW(REUSE_ADDRESS);
                    OMNI_E2WS_FW(IP_TIME_TO_LIVE);
                    OMNI_E2WS_FW(KEEP_ALIVE);
                    OMNI_E2WS_FW(MULTICAST_INTERFACE);
                    OMNI_E2WS_FW(MULTICAST_TIME_TO_LIVE);
                    OMNI_E2WS_FW(MULTICAST_LOOPBACK);
                    OMNI_E2WS_FW(ADD_MEMBERSHIP);
                    OMNI_E2WS_FW(DROP_MEMBERSHIP);
                    OMNI_E2WS_FW(DONT_FRAGMENT);
                    OMNI_E2WS_FW(ADDSOURCEMEMBERSHIP);
                    OMNI_E2WS_FW(DROP_SOURCE_MEMBERSHIP);
                    OMNI_E2WS_FW(DONT_ROUTE);
                    OMNI_E2WS_FW(BLOCK_SOURCE);
                    OMNI_E2WS_FW(UNBLOCK_SOURCE);
                    OMNI_E2WS_FW(PACKET_INFORMATION);
                    OMNI_E2WS_FW(CHECKSUM_COVERAGE);
                    OMNI_E2WS_FW(HOP_LIMIT);
                    OMNI_E2WS_FW(IP_PROTECTION_LEVEL);
                    OMNI_E2WS_FW(IPV6ONLY);
                    OMNI_E2WS_FW(BROADCAST);
                    OMNI_E2WS_FW(USE_LOOPBACK);
                    OMNI_E2WS_FW(LINGER);
                    OMNI_E2WS_FW(OUT_OF_BAND_INLINE);
                    OMNI_E2WS_FW(SEND_BUFFER);
                    OMNI_E2WS_FW(RECEIVE_BUFFER);
                    OMNI_E2WS_FW(SEND_LOW_WATER);
                    OMNI_E2WS_FW(RECEIVE_LOW_WATER);
                    OMNI_E2WS_FW(SEND_TIMEOUT);
                    OMNI_E2WS_FW(RECEIVE_TIMEOUT);
                    OMNI_E2WS_FW(ERR);
                    OMNI_E2WS_FW(SOCKET_TYPE);
                    OMNI_E2WS_FW(UPDATE_ACCEPT_CONTEXT);
                    OMNI_E2WS_FW(UPDATE_CONNECT_CONTEXT);
                    OMNI_E2WS_FW(MAX_CONNECTIONS);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } socket_option_name;

        /** socket_shutdown defines enum values for constants that are used by the omni::net::socket::shutdown method. */
        typedef struct socket_shutdown {
            typedef enum enum_t {
                RECEIVE = 0,
                SEND = 1,
                BOTH = 2
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 3;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(RECEIVE);
                    OMNI_E2S_FW(SEND);
                    OMNI_E2S_FW(BOTH);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(RECEIVE);
                    OMNI_E2WS_FW(SEND);
                    OMNI_E2WS_FW(BOTH);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } socket_shutdown;
        
        /** socket_type defines enum values for the type of socket that an instance of the omni::net::socket::socket class represents. */
        typedef struct socket_type {
            typedef enum enum_t {
                UNKNOWN = -1,
                STREAM = 1,
                DGRAM = 2,
                RAW = 3,
                RDM = 4,
                SEQPACKET = 5
            } enum_t;
            
            /** Defines the number of elements in the state enum */
            static const unsigned short COUNT = 6;
            
            /** Converts the enum to its string representation */
            static const std::string to_string(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2S_FW(STREAM);
                    OMNI_E2S_FW(DGRAM);
                    OMNI_E2S_FW(RAW);
                    OMNI_E2S_FW(RDM);
                    OMNI_E2S_FW(SEQPACKET);
                    OMNI_E2S_FW(UNKNOWN);
                    default: break;
                }
                return "UNKNOWN";
            }
            
            /** Converts the enum to its wide string representation */
            static const std::wstring to_wstring(const enum_t& v)
            {
                switch (v) {
                    OMNI_E2WS_FW(STREAM);
                    OMNI_E2WS_FW(DGRAM);
                    OMNI_E2WS_FW(RAW);
                    OMNI_E2WS_FW(RDM);
                    OMNI_E2WS_FW(SEQPACKET);
                    OMNI_E2WS_FW(UNKNOWN);
                    default: break;
                }
                return OMNI_WSTR("UNKNOWN");
            }
            
            friend std::ostream& operator<<(std::ostream& s, const enum_t& c)
            { s << to_string(c); return s; }
            friend std::wostream& operator<<(std::wostream& s, const enum_t& c)
            { s << to_wstring(c); return s; }
        } socket_type;
    
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
        #if !defined(OMNI_IS_WIN)
            #if !defined(SOCKET)
                #define SOCKET int
            #endif
        #endif
        */
        
        /**
            Specifies whether a  will remain connected after a call to the Close()
            or TcpClient.Close() methods and the length of time it will remain connected, if data remains to be sent.
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
            //** Gets the IP address associated with this interface (if any) 
            std::string address;
            //** Gets the subnet mask of this interface (if any) 
            std::string subnet;
            //** Gets the broadcast of this interface (if any) 
            std::string broadcast;
            //** Gets the speed of this interface 
            long speed;
            //** Gets the network adapter description 
            std::string description;
            //** Gets if the interface is currently up or down 
            bool is_up;
            //** Gets the interface type of this interface 
            omni::net::network_interface::enum_t type;
        } net_interface;*/
    };
};

#endif // OMNI_NET_T_HPP
