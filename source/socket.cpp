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

#if defined(OMNI_OS_WIN)
    #define OMNI_SOCK_WSA_FW , m_wsa(true)
    #define OMNI_SOCK_CLOSE_FW this->m_wsa.close();
    #define OMNI_SOCK_OPEN_FW if (!this->m_wsa.open()) { return (this->m_last_err = omni::net::parse_error(this->m_wsa.error())); }
#else
    #define OMNI_SOCK_WSA_FW 
    #define OMNI_SOCK_CLOSE_FW 
    #define OMNI_SOCK_OPEN_FW 
#endif

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
                return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
            }
        }
        if (shutdown && (this->shutdown(omni::net::socket_shutdown::BOTH) != omni::net::socket_error::SUCCESS)) {
            OMNI_DBGE("could not shutdown the socket")
            return this->m_last_err;
        }
        if (OMNI_SOCKET_CLOSE_FW(this->m_socket) != 0) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        OMNI_SOCK_CLOSE_FW
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

omni::net::socket::socket(omni::net::address_family family,
                          omni::net::socket_type type, 
                          omni::net::protocol_type protocol) :
    OMNI_CTOR_FW(omni::net::socket)
    m_socket(OMNI_INVALID_SOCKET), m_addr(), m_family(family), m_proto(protocol), m_type(type), 
    m_last_err(omni::net::socket_error::UNSPECIFIED), m_ep4(), m_port(), m_bep4(), m_bport(), 
    m_connected(), m_bound(), m_open(), m_shut(), m_listen()
    OMNI_SOCK_WSA_FW
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
    OMNI_SOCK_WSA_FW
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
    } else if (remote_ep.is_connected()) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    }
    return (this->m_last_err = remote_ep.connect(this->m_socket));
}

omni::net::socket_error omni::net::socket::bind()
{
    OMNI_SAFE_SOCKLOCK_FW
    uint32_t ip = this->m_ep4;
    uint16_t port = this->m_port;
    OMNI_SAFE_SOCKUNLOCK_FW
    return this->bind(ip, port);
}

omni::net::socket_error omni::net::socket::bind(uint16_t port)
{
    OMNI_SAFE_SOCKLOCK_FW
    uint32_t ip = this->m_ep4;
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
            this->m_addr.sin_family = static_cast<int>(this->m_family);
            this->m_addr.sin_port = htons(this->m_bport);
            this->m_addr.sin_addr.s_addr = htonl(this->m_bep4);
        } break;
        default:
            // omni::net::address_family::UNIX is not support in this socket since that's an IPC protocol
            // omni::net::address_family::INTERNETWORK_V6 is not supported in this socket, that's socket6
            return (this->m_last_err = omni::net::socket_error::PROTOCOL_FAMILY_NOT_SUPPORTED);
    }
    if (::bind(this->m_socket, omni::net::to_sockaddr(this->m_addr), sizeof(this->m_addr)) != 0) {
        this->m_bound = false;
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
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
    return (this->m_last_err = omni::net::socket_error::INVALID_ARGUMENT);
}

omni::net::socket_error omni::net::socket::bind(const std::wstring& ip, uint16_t port)
{
    uint32_t ep;
    if (omni::net::util::try_parse_ip4(ip, ep)) {
        return this->bind(ep, port);
    }
    return (this->m_last_err = omni::net::socket_error::INVALID_ARGUMENT);
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
    switch (this->m_family.value()) {
        case omni::net::address_family::INTERNETWORK: {
            this->m_addr.sin_family = static_cast<int>(this->m_family);
            this->m_addr.sin_port = htons(this->m_port);
            this->m_addr.sin_addr.s_addr = htonl(this->m_ep4);
        } break;
        default:
            // omni::net::address_family::UNIX is not support in this socket since that's an IPC protocol
            // omni::net::address_family::INTERNETWORK_V6 is not supported in this socket, that's a socket6
            return (this->m_last_err = omni::net::socket_error::PROTOCOL_FAMILY_NOT_SUPPORTED);
    }
    if (OMNI_SOCKET_CONNECT_FW(this->m_socket, omni::net::to_sockaddr(this->m_addr), sizeof(this->m_addr)) != 0) {
        this->m_connected = false;
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
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
        return (this->m_last_err = omni::net::socket_error::ADDRESS_NOT_AVAILABLE);
    }
    return this->connect(ep, port);
}

omni::net::socket_error omni::net::socket::connect(const std::wstring& ip, uint16_t port)
{
    return this->connect(omni::string::util::to_string(ip), port);
}

omni::net::socket_error omni::net::socket::connect_host(const std::string& host, uint16_t port)
{
    omni::seq::std_string_t ip;
    omni::net::socket_error err = omni::net::util::get_ip(host, port, ip);
    if (err == omni::net::socket_error::SUCCESS) {
        if (ip.size() > 0) {
            return this->connect(ip[0], port);
        } else {
            return (this->m_last_err = omni::net::socket_error::ADDRESS_NOT_AVAILABLE);
        }
    }
    return (this->m_last_err = err);
}

omni::net::socket_error omni::net::socket::connect_host(const std::wstring& host, uint16_t port)
{
    return this->connect_host(omni::string::to_string(host), port);
}

omni::net::socket_error omni::net::socket::disconnect(bool reuse)
{
    return this->_close(0, reuse);
}

omni::net::socket_error omni::net::socket::ioc(uint32_t op_code, omni::net::xfr_t* val, int32_t& result)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_OS_WIN)
        result = ::ioctlsocket(this->m_socket, static_cast<long>(op_code), reinterpret_cast<u_long*>(val));
    #else
        result = ::ioctl(this->m_socket, static_cast<unsigned long>(op_code), val);
    #endif
    if (result == OMNI_SOCK_SYSERR_FW) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    int err = 0;
    OMNI_SOCKLEN_FW sz;
    if ((op_level.value() == omni::net::socket_option_level::SOCKET) &&
        ((op_name == omni::net::socket_option::LINGER) || (op_name == omni::net::socket_option::DONT_LINGER)))
    {
        struct linger lop;
        std::memset(&lop, 0, sizeof(struct linger));
        sz = static_cast<OMNI_SOCKLEN_FW>(sizeof(struct linger));
        err = ::getsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(omni::net::socket_option::LINGER),
                           reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&lop),
                           &sz);
        if (err == 0) { op_val = static_cast<int32_t>(lop.l_linger); }
    } else {
        OMNI_SOCKET_XFR_T_FW* val = reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&op_val);
        sz = static_cast<OMNI_SOCKLEN_FW>(sizeof(val));
        err = ::getsockopt(this->m_socket, static_cast<int>(op_level), static_cast<int>(op_name), val, &sz);
        if (err == 0) { op_val = *(reinterpret_cast<int32_t*>(val)); }
    }
    if (err != 0) { return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW)); }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::get_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name.value()), op_val);
}

omni::net::socket_error omni::net::socket::get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name.value()), op_val);
}

omni::net::socket_error omni::net::socket::open()
{
    OMNI_SAFE_SOCKALOCK_FW
    if (this->m_open) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    OMNI_SOCK_OPEN_FW
    this->m_socket = OMNI_SOCKET_OPEN_FW(this->m_family, this->m_type, this->m_proto);
    if (this->m_socket == OMNI_INVALID_SOCKET) {
        int err = OMNI_SOCKET_ERR_FW;
        OMNI_DBGEV("a system error occurred creating the socket: ", err)
        return (this->m_last_err = omni::net::parse_error(err));
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

omni::net::socket_error omni::net::socket::listen()
{
    return this->listen(OMNI_SOCKET_DEFAULT_BACKLOG);
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
    if (backlog > OMNI_SOMAXCONN) {
        return (this->m_last_err = omni::net::socket_error::INVALID_ARGUMENT);
    }
    if (::listen(this->m_socket, static_cast<int>(backlog)) != 0) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
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
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
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
                           reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&lop),
                           sizeof(struct linger));
    } else {
        err = ::setsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(op_name),
                           reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&op_val),
                           sizeof(int32_t));
    }
    if (err != 0) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
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

omni::net::socket_error omni::net::socket::receive(char* buffer, uint32_t len, uint32_t& rcvd)
{
    return this->receive(buffer, len, omni::net::socket_flags::NONE, rcvd);
}

omni::net::socket_error omni::net::socket::receive(int8_t* buffer, uint32_t len, uint32_t& rcvd)
{
    return this->receive(buffer, len, omni::net::socket_flags::NONE, rcvd);
}

omni::net::socket_error omni::net::socket::receive(uint8_t* buffer, uint32_t len, uint32_t& rcvd)
{
    return this->receive(buffer, len, omni::net::socket_flags::NONE, rcvd);
}

omni::net::socket_error omni::net::socket::receive(char* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(rcvd);
        WSABUF buf;
        buf.len = len;
        buf.buf = buffer;
        if (::WSARecv(this->m_socket, &buf, 1, &recd, &flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        rcvd = static_cast<uint32_t>(recd);
    #else
        long r = ::recv(this->m_socket, (reinterpret_cast<omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags));
        switch (r) {
            // connection closed
            case 0: return (this->m_last_err = omni::net::socket_error::CONNECTION_RESET);
            // error
            case OMNI_SOCK_SYSERR_FW: return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
            // success
            default: rcvd = r; break;
        }
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::receive(int8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(rcvd);
        WSABUF buf;
        buf.len = len;
        buf.buf = reinterpret_cast<omni::net::xfr_t*>(buffer);
        if (::WSARecv(this->m_socket, &buf, 1, &recd, &flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        rcvd = static_cast<uint32_t>(recd);
    #else
        long r = ::recv(this->m_socket, (reinterpret_cast<omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags));
        switch (r) {
            // connection closed
            case 0: return (this->m_last_err = omni::net::socket_error::CONNECTION_RESET);
            // error
            case OMNI_SOCK_SYSERR_FW: return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
            // success
            default: rcvd = r; break;
        }
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::receive(uint8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(rcvd);
        WSABUF buf;
        buf.len = len;
        buf.buf = reinterpret_cast<omni::net::xfr_t*>(buffer);
        if (::WSARecv(this->m_socket, &buf, 1, &recd, &flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        rcvd = static_cast<uint32_t>(recd);
    #else
        long r = ::recv(this->m_socket, (reinterpret_cast<omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags));
        switch (r) {
            // connection closed
            case 0: return (this->m_last_err = omni::net::socket_error::CONNECTION_RESET);
            // error
            case OMNI_SOCK_SYSERR_FW: return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
            // success
            default: rcvd = r; break;
        }
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::receive_from(char* buffer, uint32_t len, uint32_t& rcvd)
{
    std::string fip;
    uint16_t port;
    return this->receive_from(buffer, len, omni::net::socket_flags::NONE, fip, port, rcvd);
}

omni::net::socket_error omni::net::socket::receive_from(char* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd)
{
    std::string fip;
    uint16_t port;
    return this->receive_from(buffer, len, flags, fip, port, rcvd);
}

omni::net::socket_error omni::net::socket::receive_from(char* buffer, uint32_t len, std::string& from_ip, uint16_t& from_port, uint32_t& rcvd)
{
    return this->receive_from(buffer, len, omni::net::socket_flags::NONE, from_ip, from_port, rcvd);
}

omni::net::socket_error omni::net::socket::receive_from(char* buffer, uint32_t len, omni::net::socket_flags flags, std::string& from_ip, uint16_t& from_port, uint32_t& rcvd)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    omni::net::sockaddr_in_t src_addr;
    OMNI_SOCKLEN_FW addrlen = sizeof(omni::net::sockaddr_in_t);
    std::memset(&src_addr, 0, addrlen);
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(rcvd);
        WSABUF buf;
        buf.len = len;
        buf.buf = reinterpret_cast<omni::net::xfr_t*>(buffer);
        if (::WSARecvFrom(this->m_socket, &buf, 1, &recd, &flag, omni::net::to_sockaddr(src_addr), &addrlen, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        rcvd = static_cast<uint32_t>(recd);
    #else
        long r = ::recvfrom(this->m_socket, (reinterpret_cast<omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags), omni::net::to_sockaddr(src_addr), &addrlen);
        switch (r) {
            // connection closed
            case 0: return (this->m_last_err = omni::net::socket_error::CONNECTION_RESET);
            // error
            case OMNI_SOCK_SYSERR_FW: return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
            // success
            default: rcvd = r; break;
        }
    #endif
    from_ip.assign(inet_ntoa(src_addr.sin_addr));
    from_port = ntohs(src_addr.sin_port);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::send(const char* buffer, uint32_t len, uint32_t& sent)
{
    return this->send(buffer, len, omni::net::socket_flags::NONE, sent);
}

omni::net::socket_error omni::net::socket::send(const int8_t* buffer, uint32_t len, uint32_t& sent)
{
    return this->send(buffer, len, omni::net::socket_flags::NONE, sent);
}

omni::net::socket_error omni::net::socket::send(const uint8_t* buffer, uint32_t len, uint32_t& sent)
{
    return this->send(buffer, len, omni::net::socket_flags::NONE, sent);
}

omni::net::socket_error omni::net::socket::send(const char* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(sent);
        WSABUF buf;
        buf.len = len;
        buf.buf = const_cast<omni::net::xfr_t*>(reinterpret_cast<const omni::net::xfr_t*>(buffer));
        if (::WSASend(this->m_socket, &buf, 1, &recd, flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        sent = static_cast<uint32_t>(recd);
    #else
        long r = ::send(this->m_socket, (reinterpret_cast<const omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags));
        if (r == OMNI_SOCK_SYSERR_FW) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        // success
        sent = r;
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::send(const int8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(sent);
        WSABUF buf;
        buf.len = len;
        buf.buf = const_cast<omni::net::xfr_t*>(reinterpret_cast<const omni::net::xfr_t*>(buffer));
        if (::WSASend(this->m_socket, &buf, 1, &recd, flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        sent = static_cast<uint32_t>(recd);
    #else
        long r = ::send(this->m_socket, (reinterpret_cast<const omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags));
        if (r == OMNI_SOCK_SYSERR_FW) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        // success
        sent = r;
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::send(const uint8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(sent);
        WSABUF buf;
        buf.len = len;
        buf.buf = const_cast<omni::net::xfr_t*>(reinterpret_cast<const omni::net::xfr_t*>(buffer));
        if (::WSASend(this->m_socket, &buf, 1, &recd, flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        sent = static_cast<uint32_t>(recd);
    #else
        long r = ::send(this->m_socket, (reinterpret_cast<const omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags));
        if (r == OMNI_SOCK_SYSERR_FW) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        // success
        sent = r;
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::socket::send_to(const char* buffer, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent)
{
    return this->send_to(buffer, len, omni::net::socket_flags::NONE, ip, port, sent);
}

omni::net::socket_error omni::net::socket::send_to(const char* buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent)
{
    OMNI_SAFE_SOCKALOCK_FW
    if (!this->m_open) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    uint32_t ep = 0;
    if (omni::net::util::try_parse_ip4(ip, ep)) {
        return (this->m_last_err = omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED);
    }
    omni::net::sockaddr_in_t to_addr;
    OMNI_SOCKLEN_FW addrlen = sizeof(omni::net::sockaddr_in_t);
    std::memset(&to_addr, 0, addrlen);
    to_addr.sin_family = static_cast<int>(this->m_family);
    to_addr.sin_port = htons(port);
    to_addr.sin_addr.s_addr = htonl(ep);
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(sent);
        WSABUF buf;
        buf.len = len;
        buf.buf = const_cast<omni::net::xfr_t*>(reinterpret_cast<const omni::net::xfr_t*>(buffer));
        if (::WSASendTo(this->m_socket, &buf, 1, &recd, flag, omni::net::to_sockaddr(to_addr), addrlen, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        sent = static_cast<uint32_t>(recd);
    #else
        long r = ::sendto(this->m_socket, (reinterpret_cast<const omni::net::xfr_t*>(buffer)), len, static_cast<int>(flags), omni::net::to_sockaddr(to_addr), addrlen);
        if (r == OMNI_SOCK_SYSERR_FW) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        // success
        sent = r;
    #endif
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

void omni::net::socket::swap(omni::net::socket& other)
{
    if (this != &other) {
        OMNI_SAFE_SOCKALOCK_FW
        OMNI_SAFE_SOCKOALOCK_FW(other)
        std::swap(this->m_socket, other.m_socket);
        std::swap(this->m_addr, other.m_addr);
        std::swap(this->m_family, other.m_family);
        std::swap(this->m_proto, other.m_proto);
        std::swap(this->m_type, other.m_type);
        std::swap(this->m_last_err, other.m_last_err);
        std::swap(this->m_ep4, other.m_ep4);
        std::swap(this->m_port, other.m_port);
        std::swap(this->m_bep4, other.m_bep4);
        std::swap(this->m_bport, other.m_bport);
        std::swap(this->m_connected, other.m_connected);
        std::swap(this->m_bound, other.m_bound);
        std::swap(this->m_open, other.m_open);
        std::swap(this->m_shut, other.m_shut);
        std::swap(this->m_listen, other.m_listen);
        #if defined(OMNI_OS_WIN)
            this->m_wsa.swap(other.m_wsa);
        #endif
    }
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
