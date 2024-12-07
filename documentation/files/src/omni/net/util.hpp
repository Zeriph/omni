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
#if !defined(OMNI_NET_UTIL_HPP)
#define OMNI_NET_UTIL_HPP 1
#include <omni/types/net_t.hpp>
#include <omni/exception.hpp>

namespace omni {
    namespace net {
        inline omni::net::socket_error parse_error(int serr)
        {
            switch (serr) {
                case 0:
                    return omni::net::socket_error::SUCCESS;
                case OMNI_SOCK_ERR_OPERATION_ABORTED_FW:
                    return omni::net::socket_error::OPERATION_ABORTED;
                case OMNI_SOCK_ERR_IO_ERROR_FW:
                    return omni::net::socket_error::IO_ERROR;
                case OMNI_SOCK_ERR_IO_PENDING_FW:
                    return omni::net::socket_error::IO_PENDING;
                case OMNI_SOCK_ERR_INTERRUPTED_FW:
                    return omni::net::socket_error::INTERRUPTED;
                case OMNI_SOCK_ERR_PERMISSION_FW:
                    return omni::net::socket_error::PERMISSION;
                case OMNI_SOCK_ERR_ACCESS_DENIED_FW:
                    return omni::net::socket_error::ACCESS_DENIED;
                case OMNI_SOCK_ERR_FAULT_FW:
                    return omni::net::socket_error::FAULT;
                case OMNI_SOCK_ERR_INSUFFICIENT_MEMORY_FW:
                    return omni::net::socket_error::INSUFFICIENT_MEMORY;
                case OMNI_SOCK_ERR_INVALID_ARGUMENT_FW:
                    return omni::net::socket_error::INVALID_ARGUMENT;
                case OMNI_SOCK_ERR_INVALID_DESCRIPTOR_FW:
                    return omni::net::socket_error::INVALID_DESCRIPTOR;
                case OMNI_SOCK_ERR_TOO_MANY_OPEN_SOCKETS_FW:
                    return omni::net::socket_error::TOO_MANY_OPEN_SOCKETS;
                case OMNI_SOCK_ERR_WOULD_BLOCK_FW:
                    return omni::net::socket_error::WOULD_BLOCK;
                case OMNI_SOCK_ERR_IN_PROGRESS_FW:
                    return omni::net::socket_error::IN_PROGRESS;
                case OMNI_SOCK_ERR_ALREADY_IN_PROGRESS_FW:
                    return omni::net::socket_error::ALREADY_IN_PROGRESS;
                case OMNI_SOCK_ERR_NOT_SOCKET_FW:
                    return omni::net::socket_error::NOT_SOCKET;
                case OMNI_SOCK_ERR_DESTINATION_ADDRESS_REQUIRED_FW:
                    return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED;
                case OMNI_SOCK_ERR_MESSAGE_SIZE_FW:
                    return omni::net::socket_error::MESSAGE_SIZE;
                case OMNI_SOCK_ERR_PROTOCOL_TYPE_FW:
                    return omni::net::socket_error::PROTOCOL_TYPE;
                case OMNI_SOCK_ERR_PROTOCOL_OPTION_FW:
                    return omni::net::socket_error::PROTOCOL_OPTION;
                case OMNI_SOCK_ERR_PROTOCOL_NOT_SUPPORTED_FW:
                    return omni::net::socket_error::PROTOCOL_NOT_SUPPORTED;
                case OMNI_SOCK_ERR_SOCKET_NOT_SUPPORTED_FW:
                    return omni::net::socket_error::SOCKET_NOT_SUPPORTED;
                case OMNI_SOCK_ERR_OPERATION_NOT_SUPPORTED_FW:
                    return omni::net::socket_error::OPERATION_NOT_SUPPORTED;
                case OMNI_SOCK_ERR_PROTOCOL_FAMILY_NOT_SUPPORTED_FW:
                    return omni::net::socket_error::PROTOCOL_FAMILY_NOT_SUPPORTED;
                case OMNI_SOCK_ERR_ADDRESS_FAMILY_NOT_SUPPORTED_FW:
                    return omni::net::socket_error::ADDRESS_FAMILY_NOT_SUPPORTED;
                case OMNI_SOCK_ERR_ADDRESS_ALREADY_IN_USE_FW:
                    return omni::net::socket_error::ADDRESS_ALREADY_IN_USE;
                case OMNI_SOCK_ERR_ADDRESS_NOT_AVAILABLE_FW:
                    return omni::net::socket_error::ADDRESS_NOT_AVAILABLE;
                case OMNI_SOCK_ERR_NETWORK_DOWN_FW:
                    return omni::net::socket_error::NETWORK_DOWN;
                case OMNI_SOCK_ERR_NETWORK_UNREACHABLE_FW:
                    return omni::net::socket_error::NETWORK_UNREACHABLE;
                case OMNI_SOCK_ERR_NETWORK_RESET_FW:
                    return omni::net::socket_error::NETWORK_RESET;
                case OMNI_SOCK_ERR_CONNECTION_ABORTED_FW:
                    return omni::net::socket_error::CONNECTION_ABORTED;
                case OMNI_SOCK_ERR_CONNECTION_RESET_FW:
                    return omni::net::socket_error::CONNECTION_RESET;
                case OMNI_SOCK_ERR_NO_BUFFER_SPACE_AVAILABLE_FW:
                    return omni::net::socket_error::NO_BUFFER_SPACE_AVAILABLE;
                case OMNI_SOCK_ERR_IS_CONNECTED_FW:
                    return omni::net::socket_error::IS_CONNECTED;
                case OMNI_SOCK_ERR_NOT_CONNECTED_FW:
                    return omni::net::socket_error::NOT_CONNECTED;
                case OMNI_SOCK_ERR_SHUTDOWN_FW:
                    return omni::net::socket_error::SHUTDOWN;
                case OMNI_SOCK_ERR_TIMED_OUT_FW:
                    return omni::net::socket_error::TIMED_OUT;
                case OMNI_SOCK_ERR_CONNECTION_REFUSED_FW:
                    return omni::net::socket_error::CONNECTION_REFUSED;
                case OMNI_SOCK_ERR_LOOP_FW:
                    return omni::net::socket_error::LOOP;
                case OMNI_SOCK_ERR_NAME_TOO_LONG_FW:
                    return omni::net::socket_error::NAME_TOO_LONG;
                case OMNI_SOCK_ERR_HOST_DOWN_FW:
                    return omni::net::socket_error::HOST_DOWN;
                case OMNI_SOCK_ERR_HOST_UNREACHABLE_FW:
                    return omni::net::socket_error::HOST_UNREACHABLE;
                case OMNI_SOCK_ERR_PROCESS_LIMIT_FW:
                    return omni::net::socket_error::PROCESS_LIMIT;
                case OMNI_SOCK_ERR_SYSTEM_NOT_READY_FW:
                    return omni::net::socket_error::SYSTEM_NOT_READY;
                case OMNI_SOCK_ERR_VERSION_NOT_SUPPORTED_FW:
                    return omni::net::socket_error::VERSION_NOT_SUPPORTED;
                case OMNI_SOCK_ERR_NOT_INITIALIZED_FW:
                    return omni::net::socket_error::NOT_INITIALIZED;
                case OMNI_SOCK_ERR_DISCONNECTING_FW:
                    return omni::net::socket_error::DISCONNECTING;
                case OMNI_SOCK_ERR_TYPE_NOT_FOUND_FW:
                    return omni::net::socket_error::TYPE_NOT_FOUND;
                default: break;
            }
            return omni::net::socket_error::UNSPECIFIED;
        }

        inline omni::net::server_error parse_server_error(int serr)
        {
            switch (serr) {
                #if defined(OMNI_OS_WIN)
                    case WSAHOST_NOT_FOUND: // The node or service is not known; or both node and service are NULL; or AI_NUMERICSERV was specified in hints.ai_flags and service was not a numeric port-number string.
                        return omni::net::server_error::NODE_OR_SERVICE_NOT_KNOWN;
                    case WSA_NOT_ENOUGH_MEMORY: // A memory allocation failure occurred.
                        return omni::net::server_error::OUT_OF_MEMORY;
                    case WSAEAFNOSUPPORT: // The sa_family member of socket address structure pointed to by the pSockaddr parameter is not supported. 
                        return omni::net::server_error::ADDRESS_FAMILY_NOT_SUPPORTED;
                    case WSANO_RECOVERY: // A nonrecoverable failure in name resolution occurred.
                        return omni::net::server_error::NAME_SERVER_PERMANENT_FAILURE;
                    case WSAEFAULT: // The lpWSAData parameter is not a valid pointer.
                    case WSAEINVAL: // One or more invalid parameters was passed to the GetNameInfoW function. This error is returned if a host name was requested but the NodeBufferSize parameter was zero or if a service name was requested but the ServiceBufferSize parameter was zero. 
                        return omni::net::server_error::INVALID_FLAGS;
                    case WSATRY_AGAIN: // A temporary failure in name resolution occurred.
                        return omni::net::server_error::NAME_SERVER_TEMPORARY_FAILURE;
                    case WSATYPE_NOT_FOUND: // The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter.
                        return omni::net::server_error::SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE;
                    case WSAESOCKTNOSUPPORT: // The ai_socktype member of the pHints parameter is not supported.
                        return omni::net::server_error::SOCKET_TYPE_NOT_SUPPORTED;
                    case WSANO_DATA: // The requested name is valid, but no data of the requested type was found. 
                        return omni::net::server_error::HOST_EXISTS_NO_ADDRESSES_DEFINED;
                    case WSAEINPROGRESS: //A blocking Windows Sockets 1.1 operation is in progress.
                        return omni::net::server_error::IN_PROGRESS;
                    case WSAEPROCLIM: // A limit on the number of tasks supported by the Windows Sockets implementation has been reached. 
                        return omni::net::server_error::PROCESS_LIMIT;
                    case WSAVERNOTSUPPORTED: // The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation. 
                        return omni::net::server_error::VERSION_NOT_SUPPORTED;
                    case WSASYSNOTREADY: // The underlying network subsystem is not ready for network communication. 
                        return omni::net::server_error::SYSTEM_NOT_READY;
                #else
                    case EAI_ADDRFAMILY: // The specified network host does not have any network addresses in the requested address family.
                        return omni::net::server_error::NO_ADDRESSES_IN_FAMILY;
                    case EAI_AGAIN: // The name server returned a temporary failure indication. Try again later.
                        return omni::net::server_error::NAME_SERVER_TEMPORARY_FAILURE;
                    case EAI_BADFLAGS: // hints.ai_flags contains invalid flags; or, hints.ai_flags included AI_CANONNAME and name was NULL.
                        return omni::net::server_error::INVALID_FLAGS;
                    case EAI_FAIL: // The name server returned a permanent failure indication.
                        return omni::net::server_error::NAME_SERVER_PERMANENT_FAILURE;
                    case EAI_FAMILY: // The requested address family is not supported.
                        return omni::net::server_error::ADDRESS_FAMILY_NOT_SUPPORTED;
                    case EAI_MEMORY: // Out of memory.
                        return omni::net::server_error::OUT_OF_MEMORY;
                    case EAI_NODATA: // The specified network host exists, but does not have any network addresses defined.
                        return omni::net::server_error::HOST_EXISTS_NO_ADDRESSES_DEFINED;
                    case EAI_NONAME: // The node or service is not known; or both node and service are NULL; or AI_NUMERICSERV was specified in hints.ai_flags and service was not a numeric port-number string.
                        return omni::net::server_error::NODE_OR_SERVICE_NOT_KNOWN;
                    case EAI_SERVICE: // The requested service is not available for the requested socket type.  It may be available through another socket type.  For example, this error could occur if service was "shell" (a service available only on stream sockets), and either hints.ai_protocol was IPPROTO_UDP, or hints.ai_socktype was SOCK_DGRAM; or the error could occur if service was not NULL, and hints.ai_socktype was SOCK_RAW (a socket type that does not support the concept of services).
                        return omni::net::server_error::SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE;
                    case EAI_SOCKTYPE: // The requested socket type is not supported.  This could occur, for example, if hints.ai_socktype and hints.ai_protocol are inconsistent (e.g., SOCK_DGRAM and IPPROTO_TCP, respectively).
                        return omni::net::server_error::SOCKET_TYPE_NOT_SUPPORTED;
                    case EAI_SYSTEM: // Other system error; errno is set to indicate the error.
                        return omni::net::server_error::SYSTEM_ERROR;
                #endif
                default: break;
            }
            return static_cast<omni::net::server_error::enum_t>(serr);
        }

        inline omni::net::socket_error server_error_to_socket_error(const omni::net::server_error& error)
        {
            switch (error.value()) {
                case omni::net::server_error::SUCCESS:
                    return omni::net::socket_error::SUCCESS;
                case omni::net::server_error::HOST_ADDRESS_REQUIRED:
                    return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED;
                case omni::net::server_error::NO_ADDRESSES_IN_FAMILY:
                    return omni::net::socket_error::ADDRESS_NOT_AVAILABLE;
                case omni::net::server_error::NAME_SERVER_TEMPORARY_FAILURE:
                    return omni::net::socket_error::AGAIN;
                case omni::net::server_error::INVALID_FLAGS:
                    return omni::net::socket_error::INVALID_ARGUMENT;
                case omni::net::server_error::NAME_SERVER_PERMANENT_FAILURE:
                    return omni::net::socket_error::NO_RECOVER;
                case omni::net::server_error::ADDRESS_FAMILY_NOT_SUPPORTED:
                    return omni::net::socket_error::ADDRESS_FAMILY_NOT_SUPPORTED;
                case omni::net::server_error::OUT_OF_MEMORY:
                    return omni::net::socket_error::INSUFFICIENT_MEMORY;
                case omni::net::server_error::HOST_EXISTS_NO_ADDRESSES_DEFINED:
                    return omni::net::socket_error::NO_DAT;
                case omni::net::server_error::NODE_OR_SERVICE_NOT_KNOWN:
                    return omni::net::socket_error::NO_HOST;
                case omni::net::server_error::SERVICE_NOT_AVAILABLE_FOR_SOCKET_TYPE:
                    return omni::net::socket_error::OPERATION_NOT_SUPPORTED;
                case omni::net::server_error::SOCKET_TYPE_NOT_SUPPORTED:
                    return omni::net::socket_error::SOCKET_NOT_SUPPORTED;
                case omni::net::server_error::SYSTEM_ERROR:
                    return omni::net::socket_error::FAULT;
                case omni::net::server_error::IN_PROGRESS:
                    return omni::net::socket_error::IN_PROGRESS;
                case omni::net::server_error::PROCESS_LIMIT:
                    return omni::net::socket_error::PROCESS_LIMIT;
                case omni::net::server_error::SYSTEM_NOT_READY:
                    return omni::net::socket_error::SYSTEM_NOT_READY;
                case omni::net::server_error::VERSION_NOT_SUPPORTED:
                    return omni::net::socket_error::VERSION_NOT_SUPPORTED;
                case omni::net::server_error::NOT_INITIALIZED:
                    return omni::net::socket_error::NOT_INITIALIZED;
                
                case omni::net::server_error::UNSPECIFIED:
                default: break;
            }
            return omni::net::socket_error::UNSPECIFIED;
        }

        inline omni::net::sockaddr_t* to_sockaddr(omni::net::sockaddr_in_t& addr)
        {
            return reinterpret_cast<omni::net::sockaddr_t*>(&addr);
        }

        inline omni::net::sockaddr_t* to_sockaddr(omni::net::sockaddr_in6_t& addr)
        {
            return reinterpret_cast<omni::net::sockaddr_t*>(&addr);
        }

        inline omni::net::sockaddr_t* to_sockaddr(omni::net::sockaddr_un_t& addr)
        {
            return reinterpret_cast<omni::net::sockaddr_t*>(&addr);
        }

        namespace util {
            inline bool try_parse_ip4(const std::string& ip, uint32_t& result)
            {
                if (ip.empty()) { return false; }
                if (ip.size() > 19) { return false; }
                int64_t ipval = -1;
                if (ip.find(".") != std::string::npos) { // parse octets
                    omni::seq::std_string_t octs = omni::cstring::split(ip, ".");
                    if (octs.size() > 4 || octs.size() < 2) { return false; }
                    // 0377.0377.0377.0377
                    // 0xFF.0xFF.0xFF.0xFF
                    // 255.255.255.255
                    // A.B.C.D | A.B.D | A.D
                    int64_t oct = -1;
                    ipval = 0;
                    for (std::size_t i = 0; i < octs.size(); ++i, oct = -1) {
                        if (octs[i].empty() || octs[i].size() > 4) { return false; }
                        if ((octs[i].size() > 1) && (octs[i].at(0) == '0')) { // hex/octal?
                            if ((octs[i].size() > 2) && ((octs[i].at(1) == 'x') || (octs[i].at(1) == 'X'))) { // hex
                                // it is valid hex if the string is 0x0 to 0xFF
                                if (!omni::char_util::is_hex(octs[i].at(2))) { return false; }
                                if ((octs[i].size() > 3) && !omni::char_util::is_hex(octs[i].at(3))) { return false; }
                                std::stringstream ss;
                                ss << std::hex << octs[i].substr(2);
                                ss >> oct;
                            } else { // octal
                                oct = 0;
                                for (std::size_t c = 1; c < octs[i].size(); ++c) {
                                    if (!omni::char_util::is_octal(octs[i].at(c))) { return false; }
                                    switch (octs[i].size() - c) {
                                        case 1: oct += (omni::char_util::to_int(octs[i].at(c))); break;
                                        case 2: oct += (omni::char_util::to_int(octs[i].at(c)) * 8); break;
                                        case 3: oct += (omni::char_util::to_int(octs[i].at(c)) * 64); break;
                                        default: break;
                                    }
                                }
                            }
                        } else { // regular number
                            if (!omni::string::util::is_numeric(octs[i])) { return false; }
                            oct = omni::string::util::to_type<int>(octs[i]);
                        }
                        if (oct > 255 || oct < 0) { return false; }
                        switch (octs.size()) {
                            case 2: ipval += ((i == 0) ? (static_cast<uint32_t>(oct) << 24) : oct); break;
                            case 3:
                                switch (i) {
                                    case 0: ipval += (static_cast<uint32_t>(oct) << 24); break;
                                    case 1: ipval += (static_cast<uint32_t>(oct) << 16); break;
                                    case 2: ipval += oct; break;
                                    default: break;
                                }
                                break;
                            case 4: ipval += (static_cast<uint32_t>(oct) << ((3 - i) * 8)); break;
                            default: break;
                        }
                    }
                } else { // parse hex/octal/numeric
                    // 0xFFFFFFFF <- max hex
                    // 037777777777 <- max octal
                    // 4,294,967,295 <- max int
                    if ((ip.size() > 1) && (ip.at(0) == '0')) { // hex/octal
                        ipval = 0;
                        if ((ip.at(1) == 'x') || (ip.at(1) == 'X')) {
                            // hex
                            std::string tmp_ip = omni::cstring::reverse(ip.substr(2));
                            int64_t p = 1;
                            for (std::size_t cnt = 0; cnt < tmp_ip.size(); ++cnt, p *= 16) {
                                if (!omni::char_util::is_hex(tmp_ip.at(cnt))) { return false; }
                                ipval += (static_cast<int64_t>(omni::char_util::to_int(tmp_ip.at(cnt), true)) * p);
                            }
                        } else {
                            // octal
                            std::string tmp_ip = omni::cstring::reverse(ip.substr(1));
                            int64_t p = 1;
                            for (std::size_t cnt = 0; cnt < tmp_ip.size(); ++cnt, p *= 8) {
                                if (!omni::char_util::is_octal(tmp_ip.at(cnt))) { return false; }
                                ipval += (static_cast<int64_t>(omni::char_util::to_int(tmp_ip.at(cnt), true)) * p);
                            }
                        }
                    } else if (omni::cstring::is_numeric(ip)) { // numeric val
                        ipval = omni::string::util::to_type<int64_t>(ip);
                    }
                }
                if ((ipval >= 0) && (ipval <= 0xFFFFFFFF)) {
                    result = static_cast<uint32_t>(ipval);
                    return true;
                }
                return false;
            }

            inline bool try_parse_ip4(const std::wstring& ip, uint32_t& result)
            {
                return omni::net::util::try_parse_ip4(omni::string::to_string(ip), result);
            }

            inline bool try_parse_ip6(const std::string& ip, uint8_t* result)
            {
                if (::inet_pton(AF_INET6, ip.c_str(), result) == 1) {
                    return true;
                }
                return false;
            }

            inline bool try_parse_ip6(const std::wstring& ip, uint8_t* result)
            {
                if (::inet_pton(AF_INET6, omni::string::util::to_string(ip).c_str(), result) == 1) {
                    return true;
                }
                return false;
            }

            inline bool is_valid_dotted_ip4(const std::string& ip)
            {
                uint32_t tmp = 0;
                return omni::net::util::try_parse_ip4(ip, tmp);
            }

            inline bool is_valid_dotted_ip4(const std::wstring& ip)
            {
                return omni::net::util::is_valid_dotted_ip4(omni::string::to_string(ip));
            }

            inline bool is_valid_ip4(const std::string& ip)
            {
                uint32_t tmp = 0;
                return omni::net::util::try_parse_ip4(ip, tmp);
            }

            inline bool is_valid_ip4(const std::wstring& ip)
            {
                return omni::net::util::is_valid_ip4(omni::string::to_string(ip));
            }

            inline bool is_valid_ip6(const std::string& ip)
            {
                omni::net::ip6_binary_address tmp;
                return omni::net::util::try_parse_ip6(ip, tmp);
            }

            inline bool is_valid_ip6(const std::wstring& ip)
            {
                omni::net::ip6_binary_address tmp;
                return omni::net::util::try_parse_ip6(omni::string::util::to_string(ip), tmp);
            }

            inline bool is_valid_port(uint64_t port)
            {
                return (port <= 65535);
            }
            
            inline bool is_valid_port(int64_t port) 
            {
                return (port >= 0 && port <= 65535);
            }
            
            inline bool is_valid_port(uint32_t port)
            {
                return (port <= 65535);
            }
            
            inline bool is_valid_port(int32_t port)
            {
                return (port >= 0 && port <= 65535);
            }
            
            inline omni::string_t to_dotted_ip4_string_t(uint32_t num)
            {
                omni::sstream_t ss;
                ss << (num >> 24) << "."
                   << ((num & 0x00FF0000) >> 16) << "."
                   << ((num & 0x0000FF00) >> 8) << "."
                   << (num & 0x000000FF);
                return ss.str();
            }

            inline std::string to_dotted_ip4_string(uint32_t num)
            {
                std::stringstream ss;
                ss << (num >> 24) << "."
                   << ((num & 0x00FF0000) >> 16) << "."
                   << ((num & 0x0000FF00) >> 8) << "."
                   << (num & 0x000000FF);
                return ss.str();
            }

            inline std::wstring to_dotted_ip4_wstring(uint32_t num)
            {
                std::wstringstream ss;
                ss << (num >> 24) << "."
                   << ((num & 0x00FF0000) >> 16) << "."
                   << ((num & 0x0000FF00) >> 8) << "."
                   << (num & 0x000000FF);
                return ss.str();
            }

            inline std::string ip6_binary_to_string(const uint8_t (&num)[16])
            {
                char buf[INET6_ADDRSTRLEN];
                #if defined(OMNI_OS_WIN)
                if (::inet_ntop(AF_INET6, reinterpret_cast<PVOID>(const_cast<uint8_t*>(&num[0])), buf, sizeof(buf)) != NULL)
                #else
                if (::inet_ntop(AF_INET6, reinterpret_cast<const void*>(&num), buf, sizeof(buf)) != NULL)
                #endif
                {
                    return std::string(buf);
                }
                return std::string();
            }

            inline std::string ip4_binary_to_string(const uint8_t (&num)[16])
            {
                char buf[INET6_ADDRSTRLEN];
                #if defined(OMNI_OS_WIN)
                if (::inet_ntop(AF_INET, reinterpret_cast<PVOID>(const_cast<uint8_t*>(&num[0])), buf, sizeof(buf)) != NULL)
                #else
                if (::inet_ntop(AF_INET, reinterpret_cast<const void*>(&num), buf, sizeof(buf)) != NULL)
                #endif
                {
                    return std::string(buf);
                }
                return std::string();
            }

            inline omni::net::server_error get_host(const std::string& ip,
                                                    uint16_t port,
                                                    omni::net::address_family family,
                                                    std::string& host)
            {
                if (ip.empty()) { return omni::net::server_error::HOST_ADDRESS_REQUIRED; }
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_server_error(wsa.error()); }
                #endif
                std::string tmp = omni::string::util::trim(ip);
                omni::net::server_error ret = omni::net::server_error::SUCCESS;
                struct sockaddr_in sa;
                char out[NI_MAXHOST];
                char si[NI_MAXSERV];
                sa.sin_family = static_cast<OMNI_SIN_FAMILY_FW>(family);
                sa.sin_addr.s_addr = inet_addr(tmp.c_str());
                sa.sin_port = htons(port);
                
                int serr = ::getnameinfo(
                    reinterpret_cast<struct sockaddr *>(&sa), // const struct sockaddr *restrict addr
                    sizeof(struct sockaddr_in),               // socklen_t addrlen
                    out,                                      // char *restrict host
                    NI_MAXHOST,                               // socklen_t hostlen
                    si,                                       // char *restrict serv
                    NI_MAXSERV,                               // socklen_t servlen
                    NI_NUMERICSERV                            // int flags
                );
                if (serr != 0) {
                    ret = omni::net::parse_server_error(serr);
                } else {
                    host.assign(out);
                }
                return ret;
            }

            inline omni::net::server_error get_host(const std::string& ip, uint16_t port, std::string& host)
            {
                return omni::net::util::get_host(ip, port, omni::net::address_family::INET, host);
            }
            
            inline omni::net::server_error get_host(const std::string& ip, std::string& host)
            {
                return omni::net::util::get_host(ip, OMNI_SOCKET_DEFAULT_GET_HOST_PORT, omni::net::address_family::INET, host);
            }

            inline omni::net::server_error get_host(const std::wstring& ip,
                                                    uint16_t port,
                                                    omni::net::address_family family,
                                                    std::wstring& host)
            {
                if (host.empty()) { return omni::net::server_error::HOST_ADDRESS_REQUIRED; }
                #if defined(OMNI_WIN_API)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_server_error(wsa.error()); }
                    std::string tmp = omni::string::to_string(omni::string::util::trim(ip));
                    omni::net::server_error ret = omni::net::server_error::SUCCESS;
                    struct sockaddr_in sa;
                    wchar_t out[NI_MAXHOST];
                    wchar_t si[NI_MAXSERV];
                    sa.sin_family = static_cast<OMNI_SIN_FAMILY_FW>(family);
                    sa.sin_addr.s_addr = ::inet_addr(tmp.c_str());
                    sa.sin_port = ::htons(port);
                    int serr = ::GetNameInfoW(reinterpret_cast<struct sockaddr *>(&sa), sizeof(struct sockaddr), out, NI_MAXHOST, si, NI_MAXSERV, NI_NUMERICSERV);
                    if (serr != 0) {
                        ret = omni::net::parse_server_error(::WSAGetLastError());
                    } else {
                        host = omni::string::to_wstring(out);
                    }
                    return ret;
                #else
                    std::string val;
                    std::string tmp = omni::string::to_string(omni::string::util::trim(ip));
                    omni::net::server_error serr = omni::net::util::get_host(tmp, port, family, val);
                    if (serr == omni::net::server_error::SUCCESS) {
                        host = omni::string::to_wstring(val);
                    }
                    return serr;
                #endif
            }

            inline omni::net::server_error get_host(const std::wstring& ip, uint16_t port, std::wstring& host)
            {
                return omni::net::util::get_host(ip, port, omni::net::address_family::INET, host);
            }
            
            inline omni::net::server_error get_host(const std::wstring& ip, std::wstring& host)
            {
                return omni::net::util::get_host(ip, OMNI_SOCKET_DEFAULT_GET_HOST_PORT, omni::net::address_family::INET, host);
            }

            template < template < class, class > class std_seq_t, typename std_allocator_t >
            inline omni::net::server_error get_ip(const std::string& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  omni::net::protocol_type proto,
                                                  std_seq_t< std::string, std_allocator_t >& ips)
            {
                if (host.empty()) { return omni::net::server_error::HOST_ADDRESS_REQUIRED; }
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_server_error(wsa.error()); }
                #endif
                std::string tmp = omni::string::util::trim(host);
                std::string sport = omni::string::to_string(port);
                struct addrinfo* result = NULL;
                struct addrinfo hints;
                std::memset(&hints, 0, sizeof(struct addrinfo));
                hints.ai_family = static_cast<int>(family);
                hints.ai_socktype = static_cast<int>(type);
                hints.ai_protocol = static_cast<int>(proto);
                int ret = ::getaddrinfo(tmp.c_str(), sport.c_str(), &hints, &result);
                if (ret != 0) {
                    return omni::net::parse_server_error(ret);
                }
                for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                    if (ptr->ai_family == omni::net::address_family::INET) {
                        ips.push_back(std::string(inet_ntoa((reinterpret_cast<struct sockaddr_in *>(ptr->ai_addr))->sin_addr)));
                    }
                }
                ::freeaddrinfo(result);
                return omni::net::server_error::SUCCESS;
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::string& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  omni::net::protocol_type proto,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                return get_ip<std_seq_t, std::allocator<std::string> >(host, port, family, type, proto, ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::string& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               port,
                                               family,
                                               type,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::string& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               port,
                                               family,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::string& host,
                                                  uint16_t port,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               port,
                                               omni::net::address_family::UNSPECIFIED,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::string& host,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               OMNI_SOCKET_DEFAULT_GET_HOST_PORT,
                                               omni::net::address_family::UNSPECIFIED,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t, typename std_allocator_t >
            inline omni::net::server_error get_ip(const std::wstring& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  omni::net::protocol_type proto,
                                                  std_seq_t< std::wstring, std_allocator_t >& ips)
            {
                if (host.empty()) { return omni::net::server_error::HOST_ADDRESS_REQUIRED; }
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_server_error(wsa.error()); }
                #endif
                #if defined(OMNI_WIN_API)
                    std::wstring tmp = omni::string::util::trim(host);
                    std::wstring sport = omni::string::to_wstring(port);
                    wchar_t buf[46];
                    DWORD len = 46;
                    ADDRINFOW* result = NULL;
                    ADDRINFOW hints;
                    std::memset(&hints, 0, sizeof(struct addrinfo));
                    hints.ai_family = static_cast<int>(family);
                    hints.ai_socktype = static_cast<int>(type);
                    hints.ai_protocol = static_cast<int>(proto);
                    int ret = ::GetAddrInfoW(tmp.c_str(), sport.c_str(), &hints, &result);
                    if (ret != 0) {
                        return omni::net::parse_server_error(::WSAGetLastError());
                    }
                    for (ADDRINFOW* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                        if (ptr->ai_family == omni::net::address_family::INET) {
                            std::memset(buf, 0, sizeof(buf));
                            len = 46;
                            ret = ::WSAAddressToString((reinterpret_cast<LPSOCKADDR>(ptr->ai_addr)), static_cast<DWORD>(ptr->ai_addrlen), NULL, buf, &len);
                            if (ret != 0) {
                                ::FreeAddrInfoW(result);
                                return omni::net::parse_server_error(::WSAGetLastError());
                            }
                            ips.push_back(std::wstring(buf));
                        }
                    }
                    ::FreeAddrInfoW(result);
                #else
                    std::string tmp = omni::string::util::trim(omni::string::to_string(host));
                    std::string sport = omni::string::to_string(port);
                    struct addrinfo* result = NULL;
                    struct addrinfo hints;
                    std::memset(&hints, 0, sizeof(struct addrinfo));
                    hints.ai_family = static_cast<int>(family);
                    hints.ai_socktype = static_cast<int>(type);
                    hints.ai_protocol = static_cast<int>(proto);
                    int ret = ::getaddrinfo(tmp.c_str(), sport.c_str(), &hints, &result);
                    if (ret != 0) {
                        return omni::net::parse_server_error(ret);
                    }
                    for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                        if (ptr->ai_family == omni::net::address_family::INET) {
                            ips.push_back(omni::string::to_wstring(inet_ntoa((reinterpret_cast<struct sockaddr_in *>(ptr->ai_addr))->sin_addr)));
                        }
                    }
                    ::freeaddrinfo(result);
                #endif
                return omni::net::server_error::SUCCESS;
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::wstring& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  omni::net::protocol_type proto,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                return get_ip<std_seq_t, std::allocator<std::wstring> >(host, port, family, type, proto, ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::wstring& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               port,
                                               family,
                                               type,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::wstring& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               port,
                                               family,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::wstring& host,
                                                  uint16_t port,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               port,
                                               omni::net::address_family::UNSPECIFIED,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::server_error get_ip(const std::wstring& host,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               OMNI_SOCKET_DEFAULT_GET_HOST_PORT,
                                               omni::net::address_family::UNSPECIFIED,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }
        }
    }
}

#endif // OMNI_NET_UTIL_HPP
