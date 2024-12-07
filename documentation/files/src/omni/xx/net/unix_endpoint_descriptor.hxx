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
#if !defined(OMNI_NET_UNIX_SOCKET_EP_HXX_FW)
    #error "invalid preprocessor directive detected"
#endif

#if defined(OMNI_SAFE_UNIX_SOCKET_EP)
    #define OMNI_SAFE_UXSOCKEPMTX_FW  ,m_mtx()
    #define OMNI_SAFE_UXSOCKEPLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_UXSOCKEPUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_UXSOCKEPALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_UXSOCKEPOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_UXSOCKEPMTX_FW
    #define OMNI_SAFE_UXSOCKEPLOCK_FW
    #define OMNI_SAFE_UXSOCKEPUNLOCK_FW
    #define OMNI_SAFE_UXSOCKEPALOCK_FW
    #define OMNI_SAFE_UXSOCKEPOALOCK_FW(o) 
#endif

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::_close(uint16_t timeout, bool shutdown)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::_receive(void* buffer, std::size_t buffer_size, omni::net::socket_flags flags, uint32_t& received)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::_send(const void* buffer, std::size_t buffer_size, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
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

omni::ipc::unix_endpoint_descriptor::unix_endpoint_descriptor() :
    OMNI_CTOR_FW(omni::ipc::unix_endpoint_descriptor)
    m_socket(OMNI_INVALID_SOCKET), m_addr(),  m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_status()
    OMNI_SAFE_UXSOCKEPMTX_FW
{
}

omni::ipc::unix_endpoint_descriptor::unix_endpoint_descriptor(const omni::ipc::unix_endpoint_descriptor& cp) :
    OMNI_CTOR_FW(omni::ipc::unix_endpoint_descriptor)
    m_socket(OMNI_INVALID_SOCKET), m_addr(), m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_status()
    OMNI_SAFE_UXSOCKEPMTX_FW
{
    this->swap(*const_cast<omni::ipc::unix_endpoint_descriptor*>(&cp));
}

omni::ipc::unix_endpoint_descriptor::~unix_endpoint_descriptor()
{
    OMNI_TRY_FW
    if (this->close() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error closing socket");
    }
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

std::string omni::ipc::unix_endpoint_descriptor::endpoint() const
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    return std::string(this->m_addr.sun_path);
}

omni::net::socket_t omni::ipc::unix_endpoint_descriptor::native_handle() const
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    return this->m_socket;
}

bool omni::ipc::unix_endpoint_descriptor::is_connected() const
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW);
}

bool omni::ipc::unix_endpoint_descriptor::is_shutdown() const
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_SHUT_FLAG_FW);
}

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::last_error() const
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    return this->m_last_err;
}

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::connect(const omni::net::socket_t& serv_sock)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::close()
{
    return this->close(0);
}

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::close(uint16_t timeout)
{
    return this->_close(timeout, false);
}

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::ioc(uint32_t op_code, omni::net::xfr_t* val)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::shutdown(omni::net::socket_shutdown how)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
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

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::ipc::unix_endpoint_descriptor::set_blocking_mode(omni::net::blocking_mode mode)
{
    uint32_t val = mode;
    return this->ioc(FIONBIO, reinterpret_cast<omni::net::xfr_t*>(&val));
}

void omni::ipc::unix_endpoint_descriptor::swap(omni::ipc::unix_endpoint_descriptor& other)
{
    if (this != &other) {
        OMNI_SAFE_UXSOCKEPALOCK_FW
        OMNI_SAFE_UXSOCKEPOALOCK_FW(other)
        std::swap(this->m_socket, other.m_socket);
        std::swap(this->m_addr, other.m_addr);
        std::swap(this->m_last_err, other.m_last_err);
        std::swap(this->m_status, other.m_status);
    }
}

omni::string_t omni::ipc::unix_endpoint_descriptor::to_string_t() const
{
    omni::sstream_t s;
    OMNI_SAFE_UXSOCKEPLOCK_FW
    s << this->m_addr.sun_path;
    OMNI_SAFE_UXSOCKEPUNLOCK_FW
    return s.str();
}

std::string omni::ipc::unix_endpoint_descriptor::to_string() const
{
    std::stringstream s;
    OMNI_SAFE_UXSOCKEPLOCK_FW
    s << this->m_addr.sun_path;
    OMNI_SAFE_UXSOCKEPUNLOCK_FW
    return s.str();
}

std::wstring omni::ipc::unix_endpoint_descriptor::to_wstring() const
{
    std::wstringstream s;
    OMNI_SAFE_UXSOCKEPLOCK_FW
    s << this->m_addr.sun_path;
    OMNI_SAFE_UXSOCKEPUNLOCK_FW
    return s.str();
}

omni::ipc::unix_endpoint_descriptor& omni::ipc::unix_endpoint_descriptor::operator=(omni::ipc::unix_endpoint_descriptor& other)
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    OMNI_SAFE_UXSOCKEPOALOCK_FW(other)
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

bool omni::ipc::unix_endpoint_descriptor::operator==(const omni::ipc::unix_endpoint_descriptor& other) const
{
    OMNI_UNUSED(other);
    return false;
}

bool omni::ipc::unix_endpoint_descriptor::operator==(const omni::net::socket_t& sock) const
{
    OMNI_SAFE_UXSOCKEPALOCK_FW
    return this->m_socket == sock;
}

bool omni::ipc::unix_endpoint_descriptor::operator==(const std::string& ep) const
{
    return this->endpoint() == ep;
}
