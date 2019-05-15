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
#include <omni/net/socket.hpp>
#include <omni/net/util.hpp>
#include <omni/defs/debug.hpp>

#if defined(OMNI_SAFE_SOCKET)
    #include <omni/sync/basic_lock.hpp>
    #define OMNI_SAFE_SOCKMTX_FW  ,m_mtx()
    #define OMNI_SAFE_SOCKLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_SOCKUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_SOCKALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_SOCKOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_SOCKMTX_FW
    #define OMNI_SAFE_SOCKLOCK_FW
    #define OMNI_SAFE_SOCKUNLOCK_FW
    #define OMNI_SAFE_SOCKALOCK_FW
    #define OMNI_SAFE_SOCKOALOCK_FW(o) 
#endif

// TODO: AF_UNIX address family is for IPC .. so NOT for omni::net::socket .. it would be for omni::ipc::socket
// TODO: make note for omni docs of system call made (like ::connect/::WSAConnect, etc.)

omni::net::socket_error omni::net::socket::_close(uint16_t timeout, bool shutdown)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    if (this->m_connected || this->m_bound) {
        if (timeout > 0) {
            struct linger lop;
            lop.l_onoff = 1;
            lop.l_linger = timeout;
            if (::setsockopt(this->m_socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<char*>(&lop), sizeof(struct linger)) != 0) {
                return this->_parse_error(OMNI_SOCKET_ERR_FW);
            }
        }
        if (shutdown && (this->shutdown(omni::net::socket_shutdown::BOTH) != omni::net::socket_error::SUCCESS)) {
            OMNI_DBGE("could not shutdown the socket")
            return this->m_last_err;
        }
        if (OMNI_SOCKET_CLOSE_FW(this->m_socket) != 0) {
            return this->_parse_error(OMNI_SOCKET_ERR_FW);
        }
        #if defined(OMNI_OS_WIN)
            ::WSACleanup();
        #endif
        if (shutdown) {
            this->m_socket = OMNI_INVALID_SOCKET;
            std::memset(&this->m_addr, 0, sizeof(this->m_addr));
        }
        this->m_open = false;
        this->m_connected = false;
        this->m_bound = false;
        this->m_listen = false;
        this->m_last_err = omni::net::socket_error::SUCCESS;
    } else {
        this->m_last_err = omni::net::socket_error::NOT_CONNECTED;
    }
    return this->m_last_err;
}

omni::net::socket_error omni::net::socket::_parse_error(int err)
{
    switch (err) {
        #if defined(OMNI_OS_WIN)
            case WSANOTINITIALISED: // A successful WSAStartup call must occur before using this function.
                return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
            case WSAENETDOWN: // The network subsystem has failed.
                return (this->m_last_err = omni::net::socket_error::NETWORK_DOWN);
            case WSAEADDRINUSE: // The local address of the socket is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during the execution of bind, but could be delayed until this function if the bind function operates on a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be "committed" at the time of this function.
                return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
            case WSAEINTR: // The (blocking) Windows Socket 1.1 call was canceled through WSACancelBlockingCall.
                return (this->m_last_err = omni::net::socket_error::INTERRUPTED);
            case WSAEINPROGRESS: // A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.
                return (this->m_last_err = omni::net::socket_error::IN_PROGRESS);
            case WSAEALREADY: // A nonblocking connect or WSAConnect call is in progress on the specified socket.
                return (this->m_last_err = omni::net::socket_error::ALREADY_IN_PROGRESS);
            case WSAEADDRNOTAVAIL: // The remote address is not a valid address (such as ADDR_ANY).
                return (this->m_last_err = omni::net::socket_error::ADDRESS_NOT_AVAILABLE);
            case WSAEAFNOSUPPORT: // Addresses in the specified family cannot be used with this socket.
                return (this->m_last_err = omni::net::socket_error::ADDRESS_FAMILY_NOT_SUPPORTED);
            case WSAECONNREFUSED: // The attempt to connect was rejected.
                return (this->m_last_err = omni::net::socket_error::CONNECTION_REFUSED);
            case WSAEFAULT: // The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the buffer length for lpCalleeData, lpSQOS, and lpGQOS are too small, or the buffer length for lpCallerData is too large.
                return (this->m_last_err = omni::net::socket_error::FAULT);
            case WSAEINVAL: // The parameter s is a listening socket, or the destination address specified is not consistent with that of the constrained group to which the socket belongs, or the lpGQOS parameter is not NULL.
                return (this->m_last_err = omni::net::socket_error::INVALID_ARGUMENT);
            case WSAEISCONN: // The socket is already connected (connection-oriented sockets only).
                return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
            case WSAENETUNREACH: // The network cannot be reached from this host at this time.
                return (this->m_last_err = omni::net::socket_error::NETWORK_UNREACHABLE);
            case WSAEHOSTUNREACH: // A socket operation was attempted to an unreachable host.
                return (this->m_last_err = omni::net::socket_error::HOST_UNREACHABLE);
            case WSAENOBUFS: // No buffer space is available. The socket cannot be connected.
                return (this->m_last_err = omni::net::socket_error::NO_BUFFER_SPACE_AVAILABLE);
            case WSAENOTSOCK: // The descriptor is not a socket.
                return (this->m_last_err = omni::net::socket_error::NOT_SOCKET);
            case WSAEOPNOTSUPP: // The FLOWSPEC structures specified in lpSQOS and lpGQOS cannot be satisfied.
                return (this->m_last_err = omni::net::socket_error::OPERATION_NOT_SUPPORTED);
            case WSAEPROTONOSUPPORT: // The lpCallerData parameter is not supported by the service provider.
                return (this->m_last_err = omni::net::socket_error::PROTOCOL_NOT_SUPPORTED);
            case WSAETIMEDOUT: // Attempt to connect timed out without establishing a connection.
                return (this->m_last_err = omni::net::socket_error::TIMED_OUT);
            case WSAEWOULDBLOCK: // The socket is marked as nonblocking and the connection cannot be completed immediately.
                return (this->m_last_err = omni::net::socket_error::WOULD_BLOCK);
            case WSAEACCES: // Attempt to connect datagram socket to broadcast address failed because setsockopt SO_BROADCAST is not enabled. 
                return (this->m_last_err = omni::net::socket_error::ACCESS_DENIED);
        #else
            case EACCES:        // For UNIX domain sockets, which are identified by pathname: Write permission is denied on the socket file, or search permission is denied for one of the directories in the path prefix.
                return (this->m_last_err = omni::net::socket_error::ACCESS_DENIED);
            case EPERM:         // The user tried to connect to a broadcast address without having the socket broadcast flag enabled or the connection request failed because of a local firewall rule.
                return (this->m_last_err = omni::net::socket_error::OPERATION_NOT_SUPPORTED);
            case EADDRINUSE:    // Local address is already in use.
                return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
            case EADDRNOTAVAIL: // (Internet domain sockets) The socket referred to by sockfd had not previously been bound to an address and, upon attempting to bind it to an ephemeral port, it was determined that all port numbers in the ephemeral port range are currently in use.
                return (this->m_last_err = omni::net::socket_error::ADDRESS_NOT_AVAILABLE);
            case EAFNOSUPPORT:  // The passed address didn't have the correct address family in its sa_family field.
                return (this->m_last_err = omni::net::socket_error::ADDRESS_FAMILY_NOT_SUPPORTED);
            case EAGAIN:        // For nonblocking UNIX domain sockets, the socket is nonblocking, and the connection cannot be completed immediately.  For other socket families, there are insufficient entries in the routing cache.
                return (this->m_last_err = omni::net::socket_error::AGAIN);
            case EALREADY:      // The socket is nonblocking and a previous connection attempt has not yet been completed.
                return (this->m_last_err = omni::net::socket_error::ALREADY_IN_PROGRESS);
            case ECONNREFUSED:  // A connect() on a stream socket found no one listening on the remote address.
                return (this->m_last_err = omni::net::socket_error::CONNECTION_REFUSED);
            case EFAULT:        // The socket structure address is outside the user's address space.
                return (this->m_last_err = omni::net::socket_error::FAULT);
            case EINPROGRESS:   // The socket is nonblocking and the connection cannot be completed immediately.  (UNIX domain sockets failed with EAGAIN instead.)
                return (this->m_last_err = omni::net::socket_error::IN_PROGRESS);
            case EINTR:         // The system call was interrupted by a signal that was caught; see signal(7).
                return (this->m_last_err = omni::net::socket_error::INTERRUPTED);
            case EISCONN:       // The socket is already connected.
                return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
            case ENETUNREACH:   // Network is unreachable.
                return (this->m_last_err = omni::net::socket_error::NETWORK_UNREACHABLE);
            case EBADF:         // sockfd is not a valid open file descriptor.
            case ENOTSOCK:      // The file descriptor sockfd does not refer to a socket.
                return (this->m_last_err = omni::net::socket_error::NOT_SOCKET);
            case EPROTOTYPE:    // The socket type does not support the requested communications protocol.  This error can occur, for example, on an attempt to connect a UNIX domain datagram socket to a stream socket.
                return (this->m_last_err = omni::net::socket_error::PROTOCOL_NOT_SUPPORTED);
            case ETIMEDOUT:     // Timeout while attempting connection.  The server may be too busy to accept new connections.  Note that for IP sockets the timeout may be very long when syncookies are enabled on the server.
                return (this->m_last_err = omni::net::socket_error::TIMED_OUT);
        #endif
        default: break;
    }
    return (this->m_last_err = static_cast<omni::net::socket_error::enum_t>(err));
}

omni::net::socket::socket(omni::net::address_family family,
                          omni::net::socket_type type, 
                          omni::net::protocol_type protocol) :
    OMNI_CTOR_FW(omni::net::socket)
    m_socket(OMNI_INVALID_SOCKET), m_addr(), m_family(family), m_proto(protocol), m_type(type), 
    m_last_err(omni::net::socket_error::UNSPECIFIED), m_ep4(), m_port(), m_bep4(), m_bport(), 
    m_connected(), m_bound(), m_open(), m_shut(), m_listen()
    OMNI_SAFE_SOCKMTX_FW
{
    if (this->open() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error opening the socket");
    }
}

omni::net::socket::socket(omni::net::socket_type type,
                          omni::net::protocol_type protocol) :
    OMNI_CTOR_FW(omni::net::socket)
    m_socket(OMNI_INVALID_SOCKET), m_addr(), m_family(omni::net::address_family::UNSPECIFIED),
    m_proto(protocol), m_type(type), m_last_err(omni::net::socket_error::UNSPECIFIED), m_ep4(), 
    m_port(), m_bep4(), m_bport(), m_connected(), m_bound(), m_open(), m_shut(), m_listen()
    OMNI_SAFE_SOCKMTX_FW
{
    if (this->open() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error opening the socket");
    }
}

omni::net::socket::~socket()
{
    OMNI_TRY_FW
    if (this->close() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error closing socket");
    }
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

omni::net::socket_error omni::net::socket::accept(omni::net::endpoint_descriptor& remote_ep)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (!this->m_listen) { // includes this->m_bound (can't listen if not bound)
        return (this->m_last_err = omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED);
    }
    OMNI_SOCKLEN_FW out_len = sizeof(remote_ep.addr);
    remote_ep.sock = OMNI_SOCKET_ACCEPT_FW(this->m_socket, &(remote_ep.addr), &out_len);
    if (remote_ep.sock == OMNI_INVALID_SOCKET) {
        return this->_parse_error(OMNI_SOCKET_ERR_FW);
    }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::bind()
{
    OMNI_SAFE_SOCKLOCK_FW
    uint32_t ip = this->m_ep4;
    uint16_t port = this->m_port;
    OMNI_SAFE_SOCKUNLOCK_FW
    return this->bind(ip, port);
}

omni::net::socket_error omni::net::socket::bind(uint32_t ip, uint16_t port)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (this->m_connected) { // can't bind to a 'connect()'ed socket
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    } else if (this->m_bound) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    this->m_bep4 = ip;
    this->m_bport = port;
    std::memset(&this->m_addr, 0, sizeof(this->m_addr));
    switch (this->m_family.value()) {
        case omni::net::address_family::INTERNETWORK: {
            omni::net::sockaddr_in_t addr;
            std::memset(&addr, 0, sizeof(addr));
            addr.sin_family = static_cast<int>(this->m_family);
            addr.sin_port = htons(this->m_bport);
            addr.sin_addr.s_addr = htonl(this->m_bep4);
            std::memcpy(&(this->m_addr), &addr, sizeof(addr));
        } break;
        // TODO: how do you set this?
        /*case omni::net::address_family::INTERNETWORK_V6: {
            omni::net::sockaddr_in6_t addr6;
            std::memset(&addr6, 0, sizeof(addr6));
            addr6.sin6_family = static_cast<int>(this->m_family);
            addr6.sin6_port = htons(this->m_bport);
            // addr6.sin6_addr = IN6ADDR_ANY_INIT;
            std::memcpy(&(this->m_addr), &addr6, sizeof(addr6));
        } break;*/
        default:
            // omni::net::address_family::UNIX is not support in this socket since that's an IPC protocol
            return (this->m_last_err = omni::net::socket_error::PROTOCOL_FAMILY_NOT_SUPPORTED);
    }
    if (::bind(this->m_socket, &(this->m_addr), sizeof(this->m_addr)) != 0) {
        this->m_bound = false;
        return this->_parse_error(OMNI_SOCKET_ERR_FW);
    }
    this->m_bound = true;
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::bind(const std::string& ip, uint16_t port)
{
    uint32_t ep;
    if (omni::net::util::try_parse_ip4(ip, ep)) {
        return this->bind(ep, port);
    }
    return omni::net::socket_error::INVALID_ARGUMENT;
}

omni::net::socket_error omni::net::socket::bind(const std::wstring& ip, uint16_t port)
{
    uint32_t ep;
    if (omni::net::util::try_parse_ip4(ip, ep)) {
        return this->bind(ep, port);
    }
    return omni::net::socket_error::INVALID_ARGUMENT;
}

omni::net::socket_error omni::net::socket::bind(const std::string& ip)
{
    return this->bind(ip, 0);
}

omni::net::socket_error omni::net::socket::bind(const std::wstring& ip)
{
    return this->bind(ip, 0);
}

omni::net::socket_error omni::net::socket::close()
{
    return this->close(0);
}

omni::net::socket_error omni::net::socket::close(uint16_t timeout)
{
    return this->_close(timeout, false);
}

omni::net::socket_error omni::net::socket::connect()
{
    OMNI_SAFE_SOCKALOCK_FW
    // DEV_NOTE: htons/etc. could be macro's so we don't use global namespace (i.e. ::htons)
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (this->m_connected) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    } else if (this->m_bound) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    std::memset(&this->m_addr, 0, sizeof(this->m_addr));
    // TODO: need to figure out this hacky C based polymorph
    switch (this->m_family.value()) {
        case omni::net::address_family::INTERNETWORK: {
            omni::net::sockaddr_in_t addr;
            std::memset(&addr, 0, sizeof(addr));
            addr.sin_family = static_cast<int>(this->m_family);
            addr.sin_port = htons(this->m_port);
            addr.sin_addr.s_addr = htonl(this->m_ep4);
            std::memcpy(&(this->m_addr), &addr, sizeof(addr));
        } break;
        // TODO: how do you set this?
        /*case omni::net::address_family::INTERNETWORK_V6: {
            omni::net::sockaddr_in6_t addr6;
            std::memset(&addr6, 0, sizeof(addr6));
            addr6.sin6_family = static_cast<int>(this->m_family);
            addr6.sin6_port = htons(this->m_port);
            // addr6.sin6_addr = IN6ADDR_ANY_INIT;
            std::memcpy(&(this->m_addr), &addr6, sizeof(addr6));
        } break;*/
        default:
            // omni::net::address_family::UNIX is not support in this socket since that's an IPC protocol
            return (this->m_last_err = omni::net::socket_error::PROTOCOL_FAMILY_NOT_SUPPORTED);
    }
    if (OMNI_SOCKET_CONNECT_FW(this->m_socket, &(this->m_addr), sizeof(this->m_addr)) != 0) {
        this->m_connected = false;
        return this->_parse_error(OMNI_SOCKET_ERR_FW);
    }
    this->m_connected = true;
    this->m_shut = false;
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
    
}

omni::net::socket_error omni::net::socket::connect(uint32_t ip, uint16_t port)
{
    OMNI_SAFE_SOCKLOCK_FW
    this->m_ep4 = ip;
    this->m_port = port;   
    OMNI_SAFE_SOCKUNLOCK_FW
    return this->connect();
}

omni::net::socket_error omni::net::socket::connect(const std::string& ip, uint16_t port)
{
    uint32_t ep = 0;
    if (!omni::net::util::try_parse_ip4(ip, ep)) {
        return omni::net::socket_error::ADDRESS_NOT_AVAILABLE;
    }
    return this->connect(ep, port);
}

omni::net::socket_error omni::net::socket::connect(const std::wstring& ip, uint16_t port)
{
    return this->connect(omni::string::util::to_string(ip), port);
}

omni::net::socket_error omni::net::socket::disconnect(bool reuse)
{
    return this->_close(0, reuse);
}

omni::net::socket_error omni::net::socket::open()
{
    OMNI_SAFE_SOCKALOCK_FW
    if (this->m_open) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    #if defined(OMNI_OS_WIN)
        WSADATA sdata;
        int err = ::WSAStartup(MAKEWORD(OMNI_WINSOCK_HIGH, OMNI_WINSOCK_LOW), &sdata);
        if (err != 0) {
            // Could not get the winsock dll, fail since can't create socket
            OMNI_DBGEV("a system error occurred in WSAStartUp: ", err)
            return this->_parse_error(err);
        }
    #endif
    this->m_socket = OMNI_SOCKET_OPEN_FW(this->m_family, this->m_type, this->m_proto);
    if (this->m_socket == OMNI_INVALID_SOCKET) {
        int err = OMNI_SOCKET_ERR_FW;
        OMNI_DBGEV("a system error occurred creating the socket: ", err)
        return this->_parse_error(err);
    }
    this->m_open = true;
    this->m_shut = false;
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::open(omni::net::socket_type type, omni::net::protocol_type protocol)
{
    OMNI_SAFE_SOCKLOCK_FW
    this->m_type = type;
    this->m_proto = protocol;
    OMNI_SAFE_SOCKUNLOCK_FW
    return this->open();
}

omni::net::socket_error omni::net::socket::open(omni::net::address_family family, omni::net::socket_type type, omni::net::protocol_type protocol)
{
    OMNI_SAFE_SOCKLOCK_FW
    this->m_family = family;
    this->m_type = type;
    this->m_proto = protocol;
    OMNI_SAFE_SOCKUNLOCK_FW
    return this->open();
}

omni::net::socket_error omni::net::socket::listen(int32_t backlog)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (!this->m_bound) {
        return (this->m_last_err = omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED);
    } else if (this->m_connected) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    }
    if (backlog > SOMAXCONN) {
        return (this->m_last_err = omni::net::socket_error::INVALID_ARGUMENT);
    }
    if (::listen(this->m_socket, static_cast<int>(backlog)) != 0) {
        return this->_parse_error(OMNI_SOCKET_ERR_FW);
    }
    this->m_listen = true;
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::shutdown(omni::net::socket_shutdown how)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (this->m_shut) {
        return (this->m_last_err = omni::net::socket_error::SUCCESS);
    }
    int err = ::shutdown(this->m_socket, static_cast<int>(how));
    if (err == OMNI_SOCK_SYSERR_FW) {
        return this->_parse_error(OMNI_SOCKET_ERR_FW);
    }
    this->m_shut = true;
    this->m_listen = false;
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}


omni::net::socket_error omni::net::socket::set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    int err = 0;
    if ((op_level.value() == omni::net::socket_option_level::SOCKET) &&
        ((op_name == omni::net::socket_option::LINGER) || (op_name == omni::net::socket_option::DONT_LINGER)))
    {
        struct linger lop;
        std::memset(&lop, 0, sizeof(struct linger));
        if (op_name == omni::net::socket_option::LINGER) {
            lop.l_onoff = 1;
            lop.l_linger = op_val;
        }
        err = ::setsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(omni::net::socket_option::LINGER),
                           reinterpret_cast<char*>(&lop),
                           sizeof(struct linger));
    } else {
        err = ::setsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(op_name),
                           reinterpret_cast<char*>(&op_val),
                           sizeof(int32_t));
    }
    if (err != 0) {
        return this->_parse_error(OMNI_SOCKET_ERR_FW);
    }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::set_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name.value()), op_val);
}

omni::net::socket_error omni::net::socket::set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name.value()), op_val);
}

omni::net::socket_error omni::net::socket::receive(omni::unsafe_t buffer, uint32_t len, uint32_t& rcvd)
{
    return this->receive(buffer, len, omni::net::socket_flags::NONE, rcvd);
}

omni::net::socket_error omni::net::socket::receive(omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd)
{
    return this->receive(buffer + offset, len, flags, rcvd);
}

omni::net::socket_error omni::net::socket::receive(omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    //recv(this->m_socket, (reinterpret_cast<void*>(buffer+offset)), len, flags);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}



omni::net::socket_error omni::net::socket::receive_from(omni::unsafe_t buffer, uint32_t offset, uint32_t len, const std::string& ip, uint32_t& rcvd)
{
    return this->receive_from(buffer, offset, len, omni::net::socket_flags::NONE, ip, rcvd);
}

omni::net::socket_error omni::net::socket::receive_from(omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint32_t& rcvd)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }

    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}
omni::net::socket_error omni::net::socket::receive_from(omni::unsafe_t buffer, uint32_t len, const std::string& ip, uint32_t& rcvd)
{
    return this->receive_from(buffer, 0, len, omni::net::socket_flags::NONE, ip, rcvd);
}

omni::net::socket_error omni::net::socket::receive_from(omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint32_t& rcvd)
{
    return this->receive_from(buffer, 0, len, flags, ip, rcvd);
}

omni::net::socket_error omni::net::socket::send(const omni::unsafe_t buffer, uint32_t len, uint32_t& sent)
{
    return this->send(buffer, 0, len, omni::net::socket_flags::NONE, sent);
}

omni::net::socket_error omni::net::socket::send(const omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent)
{
    return this->send(buffer, 0, len, flags, sent);
}

omni::net::socket_error omni::net::socket::send(const omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }

    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::send_to(const omni::unsafe_t buffer, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent)
{
    return this->send_to(buffer, 0, len, omni::net::socket_flags::NONE, ip, port, sent);
}

omni::net::socket_error omni::net::socket::send_to(const omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent)
{
    return this->send_to(buffer, 0, len, flags, ip, port, sent);
}

omni::net::socket_error omni::net::socket::send_to(const omni::unsafe_t buffer, uint32_t offset, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent)
{
    return this->send_to(buffer, offset, len, omni::net::socket_flags::NONE, ip, port, sent);
}

omni::net::socket_error omni::net::socket::send_to(const omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }

    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::address_family omni::net::socket::address_family() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_family;
}

uint32_t omni::net::socket::endpoint() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_ep4;
}

uint16_t omni::net::socket::port() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_port;
}

uint32_t omni::net::socket::bound_endpoint() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_bep4;
}

uint16_t omni::net::socket::bound_port() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_bport;
}

omni::net::socket_t omni::net::socket::native_handle() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_socket;
}

bool omni::net::socket::is_bound() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_bound;
}

bool omni::net::socket::is_connected() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_connected;
}

bool omni::net::socket::is_open() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_open;
}

bool omni::net::socket::is_shutdown() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_shut;
}

bool omni::net::socket::is_listening() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_listen;
}

omni::net::socket_error omni::net::socket::last_error() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_last_err;
}

omni::net::protocol_type omni::net::socket::protocol() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_proto;
}

omni::net::socket& omni::net::socket::set_address_family(omni::net::address_family family)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (this->m_open) {
        OMNI_ERR_FW("The socket is open", omni::exceptions::socket_exception(static_cast<int>(omni::net::socket_error::IS_CONNECTED)));
    }
    this->m_family = family;
    return *this;
}

omni::net::socket& omni::net::socket::set_protocol_type(omni::net::protocol_type protocol)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (this->m_open) {
        OMNI_ERR_FW("The socket is open", omni::exceptions::socket_exception(static_cast<int>(omni::net::socket_error::IS_CONNECTED)));
    }
    this->m_proto = protocol;
    return *this;
}

omni::net::socket& omni::net::socket::set_socket_type(omni::net::socket_type type)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (this->m_open) {
        OMNI_ERR_FW("The socket is open", omni::exceptions::socket_exception(static_cast<int>(omni::net::socket_error::IS_CONNECTED)));
    }
    this->m_type = type;
    return *this;
}

omni::net::socket_type omni::net::socket::socket_type() const
{
    OMNI_SAFE_SOCKALOCK_FW
    return this->m_type;
}

omni::string_t omni::net::socket::to_string_t() const
{
    omni::sstream_t s;
    OMNI_SAFE_SOCKLOCK_FW
    s << omni::net::util::to_dotted_ip4_string_t(this->m_ep4) << ":" << this->m_port;
    OMNI_SAFE_SOCKUNLOCK_FW
    return s.str();
}

std::string omni::net::socket::to_string() const
{
    std::stringstream s;
    OMNI_SAFE_SOCKLOCK_FW
    s << omni::net::util::to_dotted_ip4_string(this->m_ep4) << ":" << this->m_port;
    OMNI_SAFE_SOCKUNLOCK_FW
    return s.str();
}

std::wstring omni::net::socket::to_wstring() const
{
    std::wstringstream s;
    OMNI_SAFE_SOCKLOCK_FW
    s << omni::net::util::to_dotted_ip4_wstring(this->m_ep4) << ":" << this->m_port;
    OMNI_SAFE_SOCKUNLOCK_FW
    return s.str();
}
