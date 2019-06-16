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

        inline omni::net::socket_error parse_error(int err)
        {
            switch (err) {
                #if defined(OMNI_OS_WIN)
                    case WSANOTINITIALISED: // A successful WSAStartup call must occur before using this function.
                        return omni::net::socket_error::NOT_INITIALIZED;
                    case WSAENETDOWN: // The network subsystem has failed.
                        return omni::net::socket_error::NETWORK_DOWN;
                    case WSAEADDRINUSE: // The local address of the socket is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during the execution of bind, but could be delayed until this function if the bind function operates on a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be "committed" at the time of this function.
                        return omni::net::socket_error::ADDRESS_ALREADY_IN_USE;
                    case WSAEINTR: // The (blocking) Windows Socket 1.1 call was canceled through WSACancelBlockingCall.
                        return omni::net::socket_error::INTERRUPTED;
                    case WSAEINPROGRESS: // A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
                        return omni::net::socket_error::IN_PROGRESS;
                    case WSAEALREADY: // A nonblocking connect or WSAConnect call is in progress on the specified socket.
                        return omni::net::socket_error::ALREADY_IN_PROGRESS;
                    case WSAEADDRNOTAVAIL: // The remote address is not a valid address (such as ADDR_ANY).
                        return omni::net::socket_error::ADDRESS_NOT_AVAILABLE;
                    case WSAEAFNOSUPPORT: // Addresses in the specified family cannot be used with this socket.
                        return omni::net::socket_error::ADDRESS_FAMILY_NOT_SUPPORTED;
                    case WSAECONNREFUSED: // The attempt to connect was rejected.
                        return omni::net::socket_error::CONNECTION_REFUSED;
                    case WSAEFAULT: // The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the buffer length for lpCalleeData, lpSQOS, and lpGQOS are too small, or the buffer length for lpCallerData is too large.
                        return omni::net::socket_error::FAULT;
                    case WSAEINVAL: // The parameter s is a listening socket, or the destination address specified is not consistent with that of the constrained group to which the socket belongs, or the lpGQOS parameter is not NULL.
                        return omni::net::socket_error::INVALID_ARGUMENT;
                    case WSAEISCONN: // The socket is already connected (connection-oriented sockets only).
                        return omni::net::socket_error::IS_CONNECTED;
                    case WSAENETUNREACH: // The network cannot be reached from this host at this time.
                        return omni::net::socket_error::NETWORK_UNREACHABLE;
                    case WSAEHOSTUNREACH: // A socket operation was attempted to an unreachable host.
                        return omni::net::socket_error::HOST_UNREACHABLE;
                    case WSAENOBUFS: // No buffer space is available. The socket cannot be connected.
                        return omni::net::socket_error::NO_BUFFER_SPACE_AVAILABLE;
                    case WSAENOTSOCK: // The descriptor is not a socket.
                        return omni::net::socket_error::NOT_SOCKET;
                    case WSAENOPROTOOPT:
                        return omni::net::socket_error::PROTOCOL_OPTION;
                    case WSAEOPNOTSUPP:
                        return omni::net::socket_error::OPERATION_NOT_SUPPORTED;
                    case WSAEPROTONOSUPPORT: // The lpCallerData parameter is not supported by the service provider.
                        return omni::net::socket_error::PROTOCOL_NOT_SUPPORTED;
                    case WSAETIMEDOUT: // Attempt to connect timed out without establishing a connection.
                        return omni::net::socket_error::TIMED_OUT;
                    case WSAEWOULDBLOCK: // The socket is marked as nonblocking and the connection cannot be completed immediately.
                        return omni::net::socket_error::WOULD_BLOCK;
                    case WSAEACCES: // Attempt to connect datagram socket to broadcast address failed because setsockopt SO_BROADCAST is not enabled. 
                        return omni::net::socket_error::ACCESS_DENIED;
                    case WSAEDISCON: // Socket s is message oriented and the virtual circuit was gracefully closed by the remote side. 
                        return omni::net::socket_error::DISCONNECTING;
                    case WSA_IO_PENDING: // An overlapped operation was successfully initiated and completion will be indicated at a later time.
                        return omni::net::socket_error::IO_PENDING;
                    case WSA_OPERATION_ABORTED: // The overlapped operation has been canceled due to the closure of the socket. 
                        return omni::net::socket_error::OPERATION_ABORTED;
                #else
                    case EACCES:        // For UNIX domain sockets, which are identified by pathname: Write permission is denied on the socket file, or search permission is denied for one of the directories in the path prefix.
                        return omni::net::socket_error::ACCESS_DENIED;
                    case EOPNOTSUPP:    // The socket argument is associated with a socket that does not support one or more of the values set in flags.
                    case EPERM:         // The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.
                        return omni::net::socket_error::OPERATION_NOT_SUPPORTED;
                    case EADDRINUSE:    // Local address is already in use.
                        return omni::net::socket_error::ADDRESS_ALREADY_IN_USE;
                    case EADDRNOTAVAIL: // (Internet domain sockets) The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.
                        return omni::net::socket_error::ADDRESS_NOT_AVAILABLE;
                    case EAFNOSUPPORT:  // The passed address didn't have the correct address family in its sa_family field.
                        return omni::net::socket_error::ADDRESS_FAMILY_NOT_SUPPORTED;
                    case EAGAIN:        // For nonblocking UNIX domain sockets, the socket is nonblocking, and the connection cannot be completed immediately.  For other socket families, there are insufficient entries in the routing cache.
                        return omni::net::socket_error::AGAIN;
                    case EALREADY:      // The socket is nonblocking and a previous connection attempt has not yet been completed.
                        return omni::net::socket_error::ALREADY_IN_PROGRESS;
                    case ECONNREFUSED:  // A connect() on a stream socket found no one listening on the remote address.
                        return omni::net::socket_error::CONNECTION_REFUSED;
                    case EIO:           // An I/O error occurred while reading from or writing to the file system.
                    case EFAULT:        // The socket structure address is outside the user's address space.
                        return omni::net::socket_error::FAULT;
                    case EINPROGRESS:   // The socket is nonblocking and the connection cannot be completed immediately.  (UNIX domain sockets failed with EAGAIN instead.)
                        return omni::net::socket_error::IN_PROGRESS;
                    case EINTR:         // The system call was interrupted by a signal that was caught; see signal(7).
                        return omni::net::socket_error::INTERRUPTED;
                    case EISCONN:       // The socket is already connected.
                        return omni::net::socket_error::IS_CONNECTED;
                    case ENETUNREACH:   // Network is unreachable.
                        return omni::net::socket_error::NETWORK_UNREACHABLE;
                    case EBADF:         // sockfd is not a valid open file descriptor.
                    case ENOTSOCK:      // The file descriptor sockfd does not refer to a socket.
                        return omni::net::socket_error::NOT_SOCKET;
                    case EPROTOTYPE:    // The socket type does not support the requested communications protocol.  This error can occur, for example, on an attempt to connect a UNIX domain datagram socket to a stream socket.
                        return omni::net::socket_error::PROTOCOL_NOT_SUPPORTED;
                    case ETIMEDOUT:     // Timeout while attempting connection.  The server may be too busy to accept new connections.  Note that for IP sockets the timeout may be very long when syncookies are enabled on the server.
                        return omni::net::socket_error::TIMED_OUT;
                    case ENOBUFS:       // Insufficient resources were available in the system to perform the operation.
                    case ENOMEM:        // Insufficient memory was available to fulfill the request.
                        return omni::net::socket_error::NO_BUFFER_SPACE_AVAILABLE;
                    case EINVAL:        // Invalid argument passed.
                        return omni::net::socket_error::INVALID_ARGUMENT;
                    case EDESTADDRREQ:  // The socket is not connection-mode, and no peer address is set.
                        return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED;
                    case ECONNRESET:    // A connection was forcibly closed by a peer.
                        return omni::net::socket_error::CONNECTION_RESET;
                    case EMSGSIZE:      // The message is too large to be sent all at once, as the socket requires.
                        return omni::net::socket_error::MESSAGE_SIZE;
                    case ENOTCONN:      // The socket is not connected or otherwise has not had the peer pre-specified.
                        return omni::net::socket_error::NOT_CONNECTED;
                    case EPIPE:         // The socket is shut down for writing, or the socket is connection-mode and is no longer connected. In the latter case, and if the socket is of type SOCK_STREAM, the SIGPIPE signal is generated to the calling thread.
                        return omni::net::socket_error::SHUTDOWN;
                    case ENETDOWN:      // The local network interface used to reach the destination is down.
                        return omni::net::socket_error::NETWORK_DOWN;
                #endif
                default: break;
            }
            return static_cast<omni::net::socket_error::enum_t>(err);
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
                    int oct = -1;
                    ipval = 0;
                    for (int i = 0; i < octs.size(); ++i, oct = -1) {
                        if (octs[i].empty() || octs[i].size() > 4) { return false; }
                        if ((octs[i].size() > 1) && (octs[i].at(0) == '0')) { // hex/octal?
                            if ((octs[i].size() > 2) && ((octs[i].at(1) == 'x') || (octs[i].at(1) == 'X'))) { // hex
                                // it's valid hex if the string is 0x0 to 0xFF
                                if (!omni::char_util::is_hex(octs[i].at(2))) { return false; }
                                if ((octs[i].size() > 3) && !omni::char_util::is_hex(octs[i].at(3))) { return false; }
                                std::stringstream ss;
                                ss << std::hex << octs[i].substr(2);
                                ss >> oct;
                            } else { // octal
                                oct = 0;
                                for (size_t c = 1; c < octs[i].size(); ++c) {
                                    if (!omni::char_util::is_octal(octs[i].at(c))) { return false; }
                                    switch (octs[i].size() - c) {
                                        case 1: oct += (omni::char_util::to_int(octs[i].at(c))); break;
                                        case 2: oct += (omni::char_util::to_int(octs[i].at(c)) * 8); break;
                                        case 3: oct += (omni::char_util::to_int(octs[i].at(c)) * 64); break;
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
                            for (int cnt = 0; cnt < tmp_ip.size(); ++cnt, p *= 16) {
                                if (!omni::char_util::is_hex(tmp_ip.at(cnt))) { return false; }
                                ipval += (static_cast<int64_t>(omni::char_util::to_int(tmp_ip.at(cnt), true)) * p);
                            }
                        } else {
                            // octal
                            std::string tmp_ip = omni::cstring::reverse(ip.substr(1));
                            int64_t p = 1;
                            for (int cnt = 0; cnt < tmp_ip.size(); ++cnt, p *= 8) {
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

            inline omni::net::socket_error get_host(const std::string& ip,
                                                    uint16_t port,
                                                    omni::net::address_family family,
                                                    std::string& host)
            {
                if (ip.empty()) { return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED; }
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_error(wsa.error()); }
                #endif
                std::string tmp = omni::string::util::trim(ip);
                omni::net::socket_error ret = omni::net::socket_error::SUCCESS;
                struct sockaddr_in sa;
                char out[NI_MAXHOST];
                char si[NI_MAXSERV];
                sa.sin_family = static_cast<int>(family);
                sa.sin_addr.s_addr = inet_addr(tmp.c_str());
                sa.sin_port = htons(port);
                int err = ::getnameinfo(reinterpret_cast<struct sockaddr *>(&sa), sizeof(struct sockaddr), out, NI_MAXHOST, si, NI_MAXSERV, NI_NUMERICSERV);
                if (err != 0) {
                    ret = omni::net::parse_error(err);
                } else {
                    host.assign(out);
                }
                return ret;
            }

            inline omni::net::socket_error get_host(const std::string& ip, uint16_t port, std::string& host)
            {
                return omni::net::util::get_host(ip, port, omni::net::address_family::UNSPECIFIED, host);
            }
            
            inline omni::net::socket_error get_host(const std::string& ip, std::string& host)
            {
                return omni::net::util::get_host(ip, OMNI_SOCKET_DEFAULT_GET_HOST_PORT, omni::net::address_family::UNSPECIFIED, host);
            }

            inline omni::net::socket_error get_host(const std::wstring& ip,
                                                    uint16_t port,
                                                    omni::net::address_family family,
                                                    std::wstring& host)
            {
                if (host.empty()) { return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED; }
                #if defined(OMNI_WIN_API)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_error(wsa.error()); }
                    std::string tmp = omni::string::to_string(omni::string::util::trim(ip));
                    omni::net::socket_error ret = omni::net::socket_error::SUCCESS;
                    struct sockaddr_in sa;
                    wchar_t out[NI_MAXHOST];
                    wchar_t si[NI_MAXSERV];
                    sa.sin_family = static_cast<int>(family);
                    sa.sin_addr.s_addr = inet_addr(tmp.c_str());
                    sa.sin_port = htons(port);
                    int err = ::GetNameInfoW(reinterpret_cast<struct sockaddr *>(&sa), sizeof(struct sockaddr), out, NI_MAXHOST, si, NI_MAXSERV, NI_NUMERICSERV);
                    if (err != 0) {
                        ret = omni::net::parse_error(err);
                    } else {
                        host = omni::string::to_wstring(out);
                    }
                    return ret;
                #else
                    std::string val;
                    std::string tmp = omni::string::to_string(omni::string::util::trim(ip));
                    omni::net::socket_error err = omni::net::util::get_host(tmp, port, family, val);
                    if (err == omni::net::socket_error::SUCCESS) {
                        host = omni::string::to_wstring(val);
                    }
                    return err;
                #endif
            }

            inline omni::net::socket_error get_host(const std::wstring& ip, uint16_t port, std::wstring& host)
            {
                return omni::net::util::get_host(ip, port, omni::net::address_family::UNSPECIFIED, host);
            }
            
            inline omni::net::socket_error get_host(const std::wstring& ip, std::wstring& host)
            {
                return omni::net::util::get_host(ip, OMNI_SOCKET_DEFAULT_GET_HOST_PORT, omni::net::address_family::UNSPECIFIED, host);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::socket_error get_ip(const std::string& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  omni::net::protocol_type proto,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                if (host.empty()) { return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED; }
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_error(wsa.error()); }
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
                    return omni::net::parse_error(ret);
                }
                for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                    if (ptr->ai_family == omni::net::address_family::INTERNETWORK) {
                        ips.push_back(std::string(inet_ntoa((reinterpret_cast<struct sockaddr_in *>(ptr->ai_addr))->sin_addr)));
                    }
                }
                ::freeaddrinfo(result);
                return omni::net::socket_error::SUCCESS;
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::socket_error get_ip(const std::string& host,
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
            inline omni::net::socket_error get_ip(const std::string& host,
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
            inline omni::net::socket_error get_ip(const std::string& host,
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
            inline omni::net::socket_error get_ip(const std::string& host,
                                                  std_seq_t< std::string, std::allocator<std::string> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               OMNI_SOCKET_DEFAULT_GET_HOST_PORT,
                                               omni::net::address_family::UNSPECIFIED,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::socket_error get_ip(const std::wstring& host,
                                                  uint16_t port,
                                                  omni::net::address_family family,
                                                  omni::net::socket_type type,
                                                  omni::net::protocol_type proto,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                if (host.empty()) { return omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED; }
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info wsa;
                    if (!wsa) { return omni::net::parse_error(wsa.error()); }
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
                        return omni::net::parse_error(ret);
                    }
                    for (ADDRINFOW* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                        if (ptr->ai_family == omni::net::address_family::INTERNETWORK) {
                            std::memset(buf, 0, sizeof(buf));
                            len = 46;
                            ret = ::WSAAddressToString((reinterpret_cast<LPSOCKADDR>(ptr->ai_addr)), static_cast<DWORD>(ptr->ai_addrlen), NULL, buf, &len);
                            if (ret != 0) {
                                ::FreeAddrInfoW(result);
                                return omni::net::parse_error(ret);
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
                        return omni::net::parse_error(ret);
                    }
                    for (struct addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                        if (ptr->ai_family == omni::net::address_family::INTERNETWORK) {
                            ips.push_back(omni::string::to_wstring(inet_ntoa((reinterpret_cast<struct sockaddr_in *>(ptr->ai_addr))->sin_addr)));
                        }
                    }
                    ::freeaddrinfo(result);
                #endif
                return omni::net::socket_error::SUCCESS;
            }

            template < template < class, class > class std_seq_t >
            inline omni::net::socket_error get_ip(const std::wstring& host,
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
            inline omni::net::socket_error get_ip(const std::wstring& host,
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
            inline omni::net::socket_error get_ip(const std::wstring& host,
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
            inline omni::net::socket_error get_ip(const std::wstring& host,
                                                  std_seq_t< std::wstring, std::allocator<std::wstring> >& ips)
            {
                return omni::net::util::get_ip(host,
                                               OMNI_SOCKET_DEFAULT_GET_HOST_PORT,
                                               omni::net::address_family::UNSPECIFIED,
                                               omni::net::socket_type::STREAM,
                                               omni::net::protocol_type::TCP,
                                               ips);
            }

            // TODO: future -> to_ip6/parse_ip6
            // TODO: omni::net::socket_error poll(omni::net::socket_t handle, uint32_t us, omni::net::select_mode mode);
            // TODO: does this make sense -> static omni::net::pingreply ping(const std::string& ip);
        }
    }
}

#endif // OMNI_NET_UTIL_HPP
