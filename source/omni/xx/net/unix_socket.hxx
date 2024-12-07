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

/* DEV_NOTE: this file is not intended to be used directly by any user code!

 i.e. do not #include <omni/xxx_impl.hxx> and do not compile this source directly.
 this file is included directly in other source. 
*/

// so as not to accidentally build this file with the source
// these macros are defined in chrono
#if !defined(OMNI_NET_UNIX_SOCKET_HXX_FW)
    #error "invalid preprocessor directive detected"
#endif

#if defined(OMNI_SAFE_UNIX_SOCKET)
    #define OMNI_SAFE_UXSOCKMTX_FW  ,m_mtx()
    #define OMNI_SAFE_UXSOCKLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_UXSOCKUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_UXSOCKALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_UXSOCKOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_UXSOCKMTX_FW
    #define OMNI_SAFE_UXSOCKLOCK_FW
    #define OMNI_SAFE_UXSOCKUNLOCK_FW
    #define OMNI_SAFE_UXSOCKALOCK_FW
    #define OMNI_SAFE_UXSOCKOALOCK_FW(o) 
#endif

inline bool omni_ipc_unix_socket_link_exists(const char* file_path)
{
    std::string file(file_path);
    if (file.empty()) { return false; }
    #if defined(OMNI_OS_WIN)
        #if defined(OMNI_WIN_API)
            OMNI_FILE_CHECKA_FW(file, false)
            DWORD res = ::GetFileAttributesA(file.c_str());
            return (res != INVALID_FILE_ATTRIBUTES && !(res & FILE_ATTRIBUTE_DIRECTORY));
        #else
            struct stat fi;
            if (::_stat(file.c_str(), &fi) == 0) {
                return !(S_ISDIR(fi.st_mode));
            }
            return false;
        #endif
    #else
        struct stat fi;
        if (::stat(file.c_str(), &fi) == 0) {
            return !(S_ISDIR(fi.st_mode));
        }
        return false;
    #endif
}

static omni::net::socket_error omni_ipc_unix_socket_remove_link(const char* file_path)
{
    if (omni_ipc_unix_socket_link_exists(file_path)) {
        #if defined(OMNI_OS_WIN)
            #if defined(OMNI_WIN_API)
                OMNI_FILE_CHECKA_FW(file, false)
                if (::DeleteFileA(file_path) == 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::string::to_string_t(omni::system::last_error_str()));
                    return omni::net::socket_error::IO_ERROR;
                }
            #else
                if (::_remove(file_path) != 0) {
                    OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                    return omni::net::socket_error::IO_ERROR;
                }
            #endif
        #else
            if (::remove(file_path) != 0) {
                OMNI_DV1_FW("error deleting file: ", omni::system::last_error());
                return omni::net::socket_error::IO_ERROR;
            }
        #endif
    }
    return omni::net::socket_error::SUCCESS;
}

omni::net::socket_error omni::ipc::unix_socket::_close(uint16_t timeout, bool shutdown)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    // regardless if it's connected/bound, if we request a close and it's open, actually close
    omni::bits::unsafe_unset(this->m_conops, omni::net::connection_option::OPEN);
    if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::CONNECTED) ||
        omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::BOUND))
    {
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
        /* DEV_NOTE: if the socket was not elected to be shutdown, then we could just set
        conops to 0, but since a shutdown could have happened, we can just logically AND
        (1 << omni::net::connection_option::SHUT) and if `shut` is set, it will stay set,
        if it is not, then it 0s out the rest. */
        this->m_conops &= (1 << omni::net::connection_option::SHUT);
        this->m_last_err = omni_ipc_unix_socket_remove_link(this->m_ep);
    } else {
        this->m_last_err = omni::net::socket_error::NOT_CONNECTED;
    }
    return this->m_last_err;
}

omni::net::socket_error omni::ipc::unix_socket::_receive(void* buffer, std::size_t buffer_size, omni::net::socket_flags flags, uint32_t& received)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(received);
        WSABUF buf;
        buf.len = buffer_size;
        buf.buf = reinterpret_cast<omni::net::xfr_t*>(buffer);
        if (::WSARecv(this->m_socket, &buf, 1, &recd, &flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        received = static_cast<uint32_t>(recd);
    #else
        long r = ::recv(this->m_socket, (reinterpret_cast<omni::net::xfr_t*>(buffer)), buffer_size, ((flags == omni::net::socket_flags::NONE) ? 0 : static_cast<int>(flags)));
        switch (r) {
            // connection closed
            case 0: return (this->m_last_err = omni::net::socket_error::CONNECTION_RESET);
            // error
            case OMNI_SOCK_SYSERR_FW: return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
            // success
            default: received = static_cast<uint32_t>(r); break;
        }
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::_send(const void* buffer, std::size_t buffer_size, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_WIN_API)
        DWORD flag = static_cast<int>(flags);
        DWORD recd = static_cast<DWORD>(sent);
        WSABUF buf;
        buf.len = buffer_size;
        buf.buf = const_cast<omni::net::xfr_t*>(reinterpret_cast<const omni::net::xfr_t*>(buffer));
        if (::WSASend(this->m_socket, &buf, 1, &recd, flag, NULL, NULL) == SOCKET_ERROR) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        sent = static_cast<uint32_t>(recd);
    #else
        long r = ::send(this->m_socket, (reinterpret_cast<const omni::net::xfr_t*>(buffer)), buffer_size, ((flags == omni::net::socket_flags::NONE) ? 0 : static_cast<int>(flags)));
        if (r == OMNI_SOCK_SYSERR_FW) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        // success
        sent = static_cast<uint32_t>(r);
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::ipc::unix_socket::unix_socket(omni::net::socket_type type) :
    OMNI_CTOR_FW(omni::ipc::unix_socket)
    m_socket(OMNI_INVALID_SOCKET),
    m_addr(),
    // DEV_NOTE: we want 0 default for proto on AF_UNIX, since omni::net::protocol_type::IP could be something other than 0, we are explicit
    m_proto(static_cast<omni::net::protocol_type::enum_t>(0)),
    m_type(type),
    m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_ep(),
    m_conops(0)
    OMNI_SOCK_WSA_FW
    OMNI_SAFE_UXSOCKMTX_FW
{
    std::memset(m_ep, 0, OMNI_UNIX_SOCKET_MAX_PATH);
    if (this->open() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error opening the socket");
    }
}

omni::ipc::unix_socket::unix_socket(omni::net::socket_type type, omni::net::protocol_type protocol) :
    OMNI_CTOR_FW(omni::ipc::unix_socket)
    m_socket(OMNI_INVALID_SOCKET),
    m_addr(),
    m_proto(protocol),
    m_type(type),
    m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_ep(),
    m_conops(0)
    OMNI_SOCK_WSA_FW
    OMNI_SAFE_UXSOCKMTX_FW
{
    std::memset(m_ep, 0, OMNI_UNIX_SOCKET_MAX_PATH);
    if (this->open() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error opening the socket");
    }
}

omni::ipc::unix_socket::unix_socket(omni::net::socket_type type, omni::net::protocol_type protocol, omni::net::socket_create_options create_ops) :
    OMNI_CTOR_FW(omni::ipc::unix_socket)
    m_socket(OMNI_INVALID_SOCKET),
    m_addr(),
    m_proto(protocol),
    m_type(type),
    m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_ep(),
    m_conops(0)
    OMNI_SOCK_WSA_FW
    OMNI_SAFE_UXSOCKMTX_FW
{
    std::memset(m_ep, 0, OMNI_UNIX_SOCKET_MAX_PATH);
    if (create_ops == omni::net::socket_create_options::OPEN_ON_CREATE) {
        if (this->open() != omni::net::socket_error::SUCCESS) {
            OMNI_D1_FW("error opening the socket");
        }
    }
}

omni::ipc::unix_socket::~unix_socket()
{
    OMNI_TRY_FW
    if (this->close() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error closing socket");
    }
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

omni::net::socket_error omni::ipc::unix_socket::accept(omni::ipc::unix_endpoint_descriptor& remote_ep)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::LISTEN)) { // includes bound (cannot listen if not bound)
        return (this->m_last_err = omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED);
    } else if (remote_ep.is_connected()) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    }
    return (this->m_last_err = remote_ep.connect(this->m_socket));
}

omni::net::socket_error omni::ipc::unix_socket::bind()
{
    OMNI_SAFE_UXSOCKLOCK_FW
    std::string ep(this->m_ep);
    OMNI_SAFE_UXSOCKUNLOCK_FW
    return this->bind(ep);
}

omni::net::socket_error omni::ipc::unix_socket::bind(const char* ep)
{
    if (ep == OMNI_NULL_PTR) {
        return omni::net::socket_error::INVALID_ARGUMENT;
    }
    return this->bind(std::string(ep));
}

omni::net::socket_error omni::ipc::unix_socket::bind(const std::string& ep)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::CONNECTED)) { // cannot bind to a connect()-ed socket
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    } else if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::BOUND)) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    std::strncpy(this->m_ep, ep.c_str(), OMNI_UNIX_SOCKET_MAX_PATH);
    std::memset(&this->m_addr, 0, sizeof(this->m_addr));
    this->m_addr.sun_family = static_cast<OMNI_SIN_FAMILY_FW>(omni::net::address_family::UNIX);
    std::strncpy(this->m_addr.sun_path, this->m_ep, (sizeof(this->m_addr.sun_path) - 1));
    if (::bind(this->m_socket, omni::net::to_sockaddr(this->m_addr), sizeof(this->m_addr)) != 0) {
        omni::bits::unsafe_unset(this->m_conops, omni::net::connection_option::BOUND);
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    omni::bits::unsafe_set(this->m_conops, omni::net::connection_option::BOUND);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::bind(const std::wstring& ep)
{
    return this->bind(omni::string::util::to_string(ep));
}

omni::net::socket_error omni::ipc::unix_socket::close()
{
    return this->close(0);
}

omni::net::socket_error omni::ipc::unix_socket::close(uint16_t timeout)
{
    return this->_close(timeout, false);
}

omni::net::socket_error omni::ipc::unix_socket::connect()
{
    OMNI_SAFE_UXSOCKALOCK_FW
    // DEV_NOTE: htons/etc. could be macros so we do not use global namespace (i.e. ::htons)
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::CONNECTED)) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    } else if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::BOUND)) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    std::memset(&this->m_addr, 0, sizeof(this->m_addr));
    this->m_addr.sun_family = static_cast<OMNI_SIN_FAMILY_FW>(omni::net::address_family::UNIX);
    std::strncpy(this->m_addr.sun_path, this->m_ep, (sizeof(this->m_addr.sun_path) - 1));
    if (OMNI_SOCKET_CONNECT_FW(this->m_socket, omni::net::to_sockaddr(this->m_addr), sizeof(this->m_addr)) != 0) {
        omni::bits::unsafe_unset(this->m_conops, omni::net::connection_option::CONNECTED);
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    omni::bits::unsafe_set(this->m_conops, omni::net::connection_option::CONNECTED);
    omni::bits::unsafe_unset(this->m_conops, omni::net::connection_option::SHUT);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
    
}

omni::net::socket_error omni::ipc::unix_socket::connect(const char* ep)
{
    if (ep == OMNI_NULL_PTR) {
        return omni::net::socket_error::INVALID_ARGUMENT;
    }
    return this->connect(std::string(ep));
}

omni::net::socket_error omni::ipc::unix_socket::connect(const std::string& ep)
{
    OMNI_SAFE_UXSOCKLOCK_FW
    std::strncpy(this->m_ep, ep.c_str(), OMNI_UNIX_SOCKET_MAX_PATH);
    OMNI_SAFE_UXSOCKUNLOCK_FW
    return this->connect();
}

omni::net::socket_error omni::ipc::unix_socket::connect(const std::wstring& ep)
{
    return this->connect(omni::string::util::to_string(ep));
}

omni::net::socket_error omni::ipc::unix_socket::disconnect(bool reuse)
{
    return this->_close(0, reuse);
}

omni::net::socket_error omni::ipc::unix_socket::ioc(uint32_t op_code, omni::net::xfr_t* val)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    #if defined(OMNI_OS_WIN)
        int32_t result = ::ioctlsocket(this->m_socket, static_cast<long>(op_code), reinterpret_cast<u_long*>(val));
    #else
        int32_t result = ::ioctl(this->m_socket, static_cast<unsigned long>(op_code), val);
    #endif
    if (result == OMNI_SOCK_SYSERR_FW) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    int serr = 0;
    OMNI_SOCKLEN_FW sz;
    OMNI_SOCKET_XFR_T_FW* val = reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&op_val);
    sz = static_cast<OMNI_SOCKLEN_FW>(sizeof(val));
    serr = ::getsockopt(this->m_socket, static_cast<int>(op_level), static_cast<int>(op_name), val, &sz);
    if (serr == 0) { op_val = *(reinterpret_cast<int32_t*>(val)); }
    if (serr != 0) { return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW)); }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::ipc::unix_socket::open()
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::ADDRESS_ALREADY_IN_USE);
    }
    OMNI_SOCK_OPEN_FW
    this->m_socket = OMNI_SOCKET_OPEN_FW(omni::net::address_family::UNIX, this->m_type, this->m_proto);
    if (this->m_socket == OMNI_INVALID_SOCKET) {
        int serr = OMNI_SOCKET_ERR_FW;
        OMNI_DBGEV("a system error occurred creating the socket: ", serr)
        return (this->m_last_err = omni::net::parse_error(serr));
    }
    omni::bits::unsafe_set(this->m_conops, omni::net::connection_option::OPEN);
    omni::bits::unsafe_unset(this->m_conops, omni::net::connection_option::SHUT);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::open(omni::net::socket_type type, omni::net::protocol_type protocol)
{
    OMNI_SAFE_UXSOCKLOCK_FW
    this->m_type = type;
    this->m_proto = protocol;
    OMNI_SAFE_UXSOCKUNLOCK_FW
    return this->open();
}

omni::net::socket_error omni::ipc::unix_socket::listen()
{
    return this->listen(OMNI_SOCKET_DEFAULT_BACKLOG);
}

omni::net::socket_error omni::ipc::unix_socket::listen(int32_t backlog)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::BOUND)) {
        return (this->m_last_err = omni::net::socket_error::DESTINATION_ADDRESS_REQUIRED);
    } else if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::CONNECTED)) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    }
    if (backlog > OMNI_SOMAXCONN) {
        return (this->m_last_err = omni::net::socket_error::INVALID_ARGUMENT);
    }
    if (::listen(this->m_socket, static_cast<int>(backlog)) != 0) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    omni::bits::unsafe_set(this->m_conops, omni::net::connection_option::LISTEN);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::shutdown(omni::net::socket_shutdown how)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    } else if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::SHUT)) {
        return (this->m_last_err = omni::net::socket_error::SUCCESS);
    }
    int serr = ::shutdown(this->m_socket, static_cast<int>(how));
    if (serr == OMNI_SOCK_SYSERR_FW) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    omni::bits::unsafe_set(this->m_conops, omni::net::connection_option::SHUT);
    omni::bits::unsafe_unset(this->m_conops, omni::net::connection_option::LISTEN);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (!omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        return (this->m_last_err = omni::net::socket_error::NOT_INITIALIZED);
    }
    int serr = ::setsockopt(this->m_socket,
                            static_cast<int>(op_level),
                            static_cast<int>(op_name),
                            reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&op_val),
                            sizeof(int32_t));
    if (serr != 0) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::ipc::unix_socket::set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::ipc::unix_socket::set_blocking_mode(omni::net::blocking_mode mode)
{
    uint32_t val = mode;
    return this->ioc(FIONBIO, reinterpret_cast<omni::net::xfr_t*>(&val));
}

omni::net::address_family omni::ipc::unix_socket::address_family() const
{
    return omni::net::address_family::UNIX;
}

std::string omni::ipc::unix_socket::endpoint() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return std::string(this->m_ep);
}

std::string omni::ipc::unix_socket::bound_endpoint() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::BOUND)) {
        return std::string(this->m_ep);
    }
    return std::string();
}

omni::net::socket_t omni::ipc::unix_socket::native_handle() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return this->m_socket;
}

bool omni::ipc::unix_socket::is_bound() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::BOUND);
}

bool omni::ipc::unix_socket::is_connected() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::CONNECTED);
}

bool omni::ipc::unix_socket::is_open() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN);
}

bool omni::ipc::unix_socket::is_shutdown() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::SHUT);
}

bool omni::ipc::unix_socket::is_listening() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::LISTEN);
}

omni::net::socket_error omni::ipc::unix_socket::last_error() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return this->m_last_err;
}

omni::net::protocol_type omni::ipc::unix_socket::protocol() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return this->m_proto;
}

omni::ipc::unix_socket& omni::ipc::unix_socket::set_protocol_type(omni::net::protocol_type protocol)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        OMNI_ERR_FW("The socket is open", omni::exceptions::socket_exception(static_cast<int>(omni::net::socket_error::IS_CONNECTED)));
    }
    this->m_proto = protocol;
    return *this;
}

omni::ipc::unix_socket& omni::ipc::unix_socket::set_socket_type(omni::net::socket_type type)
{
    OMNI_SAFE_UXSOCKALOCK_FW
    if (omni::bits::unsafe_is_set(this->m_conops, omni::net::connection_option::OPEN)) {
        OMNI_ERR_FW("The socket is open", omni::exceptions::socket_exception(static_cast<int>(omni::net::socket_error::IS_CONNECTED)));
    }
    this->m_type = type;
    return *this;
}

omni::net::socket_type omni::ipc::unix_socket::socket_type() const
{
    OMNI_SAFE_UXSOCKALOCK_FW
    return this->m_type;
}

void omni::ipc::unix_socket::swap(omni::ipc::unix_socket& other)
{
    if (this != &other) {
        OMNI_SAFE_UXSOCKALOCK_FW
        OMNI_SAFE_UXSOCKOALOCK_FW(other)
        std::swap(this->m_socket, other.m_socket);
        std::swap(this->m_addr, other.m_addr);
        std::swap(this->m_proto, other.m_proto);
        std::swap(this->m_type, other.m_type);
        std::swap(this->m_last_err, other.m_last_err);
        std::swap(this->m_ep, other.m_ep);
        std::swap(this->m_conops, other.m_conops);
        #if defined(OMNI_OS_WIN)
            this->m_wsa.swap(other.m_wsa);
        #endif
    }
}

omni::string_t omni::ipc::unix_socket::to_string_t() const
{
    omni::sstream_t s;
    OMNI_SAFE_UXSOCKLOCK_FW
    s << this->m_ep;
    OMNI_SAFE_UXSOCKUNLOCK_FW
    return s.str();
}

std::string omni::ipc::unix_socket::to_string() const
{
    std::stringstream s;
    OMNI_SAFE_UXSOCKLOCK_FW
    s << this->m_ep;
    OMNI_SAFE_UXSOCKUNLOCK_FW
    return s.str();
}

std::wstring omni::ipc::unix_socket::to_wstring() const
{
    std::wstringstream s;
    OMNI_SAFE_UXSOCKLOCK_FW
    s << this->m_ep;
    OMNI_SAFE_UXSOCKUNLOCK_FW
    return s.str();
}
