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
#if !defined(OMNI_NET_SOCKET6_EP_HXX_FW)
    #error "invalid preprocessor directive detected"
#endif

#if defined(OMNI_SAFE_SOCKET_EP6)
    #define OMNI_SAFE_SOCKEP6MTX_FW  ,m_mtx()
    #define OMNI_SAFE_SOCKEP6LOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_SOCKEP6UNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_SOCKEP6ALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_SOCKEP6OALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_SOCKEP6MTX_FW
    #define OMNI_SAFE_SOCKEP6LOCK_FW
    #define OMNI_SAFE_SOCKEP6UNLOCK_FW
    #define OMNI_SAFE_SOCKEP6ALOCK_FW
    #define OMNI_SAFE_SOCKEP6OALOCK_FW(o) 
#endif

omni::net::socket_error omni::net::endpoint_descriptor6::_close(uint16_t timeout, bool shutdown)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
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
        if (shutdown) {
            this->m_socket = OMNI_INVALID_SOCKET;
            std::memset(&this->m_addr, 0, sizeof(this->m_addr));
        }
        OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW);
        this->m_last_err = omni::net::socket_error::SUCCESS;
    } else {
        this->m_last_err = omni::net::socket_error::NOT_CONNECTED;
    }
    return this->m_last_err;
}

omni::net::socket_error omni::net::endpoint_descriptor6::_receive(void* buffer, std::size_t buffer_size, omni::net::socket_flags flags, uint32_t& received)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
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
        long r = ::recv(this->m_socket, (reinterpret_cast<omni::net::xfr_t*>(buffer)), buffer_size, static_cast<int>(flags));
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

omni::net::socket_error omni::net::endpoint_descriptor6::_send(const void* buffer, std::size_t buffer_size, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
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
        long r = ::send(this->m_socket, (reinterpret_cast<const omni::net::xfr_t*>(buffer)), buffer_size, static_cast<int>(flags));
        if (r == OMNI_SOCK_SYSERR_FW) {
            return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
        }
        // success
        sent = static_cast<uint32_t>(r);
    #endif
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::endpoint_descriptor6::endpoint_descriptor6() :
    OMNI_CTOR_FW(omni::net::endpoint_descriptor6)
    m_socket(OMNI_INVALID_SOCKET),
    m_addr(),
    m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_status()
    OMNI_SAFE_SOCKEP6MTX_FW
{
}

omni::net::endpoint_descriptor6::endpoint_descriptor6(const omni::net::endpoint_descriptor6& cp) :
    OMNI_CTOR_FW(omni::net::endpoint_descriptor6)
    m_socket(OMNI_INVALID_SOCKET),
    m_addr(),
    m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_status()
    OMNI_SAFE_SOCKEP6MTX_FW
{
    this->swap(*const_cast<omni::net::endpoint_descriptor6*>(&cp));
}

omni::net::endpoint_descriptor6::~endpoint_descriptor6()
{
    OMNI_TRY_FW
    if (this->close() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error closing socket");
    }
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

std::string omni::net::endpoint_descriptor6::endpoint() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (this->m_addr.sin6_family == AF_INET6) {
        return omni::net::util::ip6_binary_to_string(this->m_addr.sin6_addr.s6_addr);
    }
    return omni::net::util::ip4_binary_to_string(this->m_addr.sin6_addr.s6_addr);
}

uint16_t omni::net::endpoint_descriptor6::port() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return static_cast<uint16_t>(this->m_addr.sin6_port);
}

omni::net::socket_t omni::net::endpoint_descriptor6::native_handle() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return this->m_socket;
}

bool omni::net::endpoint_descriptor6::is_ip4() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return (this->m_addr.sin6_family == AF_INET);
}

bool omni::net::endpoint_descriptor6::is_ip6() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return (this->m_addr.sin6_family == AF_INET6);
}

bool omni::net::endpoint_descriptor6::is_connected() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW);
}

bool omni::net::endpoint_descriptor6::is_shutdown() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_SHUT_FLAG_FW);
}

omni::net::socket_error omni::net::endpoint_descriptor6::last_error() const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return this->m_last_err;
}

omni::net::socket_error omni::net::endpoint_descriptor6::connect(const omni::net::socket_t& serv_sock)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::IS_CONNECTED);
    }
    OMNI_SOCKLEN_FW out_len = sizeof(this->m_addr);
    this->m_socket = OMNI_SOCKET_ACCEPT_FW(serv_sock, reinterpret_cast<omni::net::sockaddr_t*>(&(this->m_addr)), &out_len);
    if (this->m_socket == OMNI_INVALID_SOCKET) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW);
    OMNI_VAL_UNSET_FLAG_BIT(this->m_status, OMNI_EPDESC_SHUT_FLAG_FW);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::endpoint_descriptor6::close()
{
    return this->close(0);
}

omni::net::socket_error omni::net::endpoint_descriptor6::close(uint16_t timeout)
{
    return this->_close(timeout, false);
}

omni::net::socket_error omni::net::endpoint_descriptor6::ioc(uint32_t op_code, omni::net::xfr_t* val)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
    }
    int32_t
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

omni::net::socket_error omni::net::endpoint_descriptor6::get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
    }
    int serr = 0;
    OMNI_SOCKLEN_FW sz;
    if ((op_level == omni::net::socket_option_level::SOCKET) &&
        ((op_name == omni::net::socket_option::LINGER) || (op_name == omni::net::socket_option::DONT_LINGER)))
    {
        struct linger lop;
        std::memset(&lop, 0, sizeof(struct linger));
        sz = static_cast<OMNI_SOCKLEN_FW>(sizeof(struct linger));
        serr = ::getsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(omni::net::socket_option::LINGER),
                           reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&lop),
                           &sz);
        if (serr == 0) { op_val = static_cast<int32_t>(lop.l_linger); }
    } else {
        OMNI_SOCKET_XFR_T_FW* val = reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&op_val);
        sz = static_cast<OMNI_SOCKLEN_FW>(sizeof(val));
        serr = ::getsockopt(this->m_socket, static_cast<int>(op_level), static_cast<int>(op_name), val, &sz);
        if (serr == 0) { op_val = *(reinterpret_cast<int32_t*>(val)); }
    }
    if (serr != 0) { return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW)); }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::endpoint_descriptor6::get_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor6::get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor6::shutdown(omni::net::socket_shutdown how)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
    } else if (OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_SHUT_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::SUCCESS);
    }
    int serr = ::shutdown(this->m_socket, static_cast<int>(how));
    if (serr == OMNI_SOCK_SYSERR_FW) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    OMNI_VAL_SET_FLAG_BIT(this->m_status, OMNI_EPDESC_SHUT_FLAG_FW);
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::endpoint_descriptor6::set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
    }
    int serr = 0;
    if ((op_level == omni::net::socket_option_level::SOCKET) &&
        ((op_name == omni::net::socket_option::LINGER) || (op_name == omni::net::socket_option::DONT_LINGER)))
    {
        struct linger lop;
        std::memset(&lop, 0, sizeof(struct linger));
        if (op_name == omni::net::socket_option::LINGER) {
            lop.l_onoff = 1;
            lop.l_linger = op_val;
        }
        serr = ::setsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(omni::net::socket_option::LINGER),
                           reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&lop),
                           sizeof(struct linger));
    } else {
        serr = ::setsockopt(this->m_socket,
                           static_cast<int>(op_level),
                           static_cast<int>(op_name),
                           reinterpret_cast<OMNI_SOCKET_XFR_T_FW*>(&op_val),
                           sizeof(int32_t));
    }
    if (serr != 0) {
        return (this->m_last_err = omni::net::parse_error(OMNI_SOCKET_ERR_FW));
    }
    return (this->m_last_err = omni::net::socket_error::SUCCESS);
}

omni::net::socket_error omni::net::endpoint_descriptor6::set_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor6::set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor6::set_blocking_mode(omni::net::blocking_mode mode)
{
    uint32_t val = mode;
    return this->ioc(FIONBIO, reinterpret_cast<omni::net::xfr_t*>(&val));
}

void omni::net::endpoint_descriptor6::swap(omni::net::endpoint_descriptor6& other)
{
    if (this != &other) {
        OMNI_SAFE_SOCKEP6ALOCK_FW
        OMNI_SAFE_SOCKEP6OALOCK_FW(other)
        std::swap(this->m_socket, other.m_socket);
        std::swap(this->m_addr, other.m_addr);
        std::swap(this->m_last_err, other.m_last_err);
        std::swap(this->m_status, other.m_status);
    }
}

omni::string_t omni::net::endpoint_descriptor6::to_string_t() const
{
    omni::sstream_t s;
    OMNI_SAFE_SOCKEP6LOCK_FW
    s << omni::net::util::ip6_binary_to_string(this->m_addr.sin6_addr.s6_addr).c_str() << ":" << static_cast<uint16_t>(this->m_addr.sin6_port);
    OMNI_SAFE_SOCKEP6UNLOCK_FW
    return s.str();
}

std::string omni::net::endpoint_descriptor6::to_string() const
{
    std::stringstream s;
    OMNI_SAFE_SOCKEP6LOCK_FW
    s << omni::net::util::ip6_binary_to_string(this->m_addr.sin6_addr.s6_addr) << ":" << static_cast<uint16_t>(this->m_addr.sin6_port);
    OMNI_SAFE_SOCKEP6UNLOCK_FW
    return s.str();
}

std::wstring omni::net::endpoint_descriptor6::to_wstring() const
{
    std::wstringstream s;
    OMNI_SAFE_SOCKEP6LOCK_FW
    s << omni::net::util::ip6_binary_to_string(this->m_addr.sin6_addr.s6_addr).c_str() << ":" << static_cast<uint16_t>(this->m_addr.sin6_port);
    OMNI_SAFE_SOCKEP6UNLOCK_FW
    return s.str();
}

omni::net::endpoint_descriptor6& omni::net::endpoint_descriptor6::operator=(omni::net::endpoint_descriptor6& other)
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    OMNI_SAFE_SOCKEP6OALOCK_FW(other)
    OMNI_ASSIGN_FW(other)
    this->m_socket = other.m_socket;
    //this->m_addr = other.m_addr;
    std::memcpy(&this->m_addr, &other.m_addr, sizeof(this->m_addr));
    this->m_status = other.m_status;
    
    other.m_socket = OMNI_INVALID_SOCKET;
    std::memset(&other.m_addr, 0, sizeof(other.m_addr));
    other.m_status = 0;
    return *this;
}

bool omni::net::endpoint_descriptor6::operator==(const omni::net::endpoint_descriptor6& other) const
{
    OMNI_UNUSED(other);
    return false;
}

bool omni::net::endpoint_descriptor6::operator==(const omni::net::socket_t& sock) const
{
    OMNI_SAFE_SOCKEP6ALOCK_FW
    return this->m_socket == sock;
}

bool omni::net::endpoint_descriptor6::operator==(const std::string& ep) const
{
    return this->endpoint() == ep;
}
