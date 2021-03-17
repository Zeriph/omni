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
#include <omni/net/endpoint_descriptor.hpp>
#include <omni/net/util.hpp>
#include <omni/defs/debug.hpp>

#if defined(OMNI_SAFE_SOCKET_EP)
    #define OMNI_SAFE_SOCKEPMTX_FW  ,m_mtx()
    #define OMNI_SAFE_SOCKEPLOCK_FW   this->m_mtx.lock();
    #define OMNI_SAFE_SOCKEPUNLOCK_FW this->m_mtx.unlock();
    #define OMNI_SAFE_SOCKEPALOCK_FW  omni::sync::scoped_basic_lock uuid12345(&this->m_mtx);
    #define OMNI_SAFE_SOCKEPOALOCK_FW(o)  omni::sync::scoped_basic_lock uuid54321(&o.m_mtx);
#else
    #define OMNI_SAFE_SOCKEPMTX_FW
    #define OMNI_SAFE_SOCKEPLOCK_FW
    #define OMNI_SAFE_SOCKEPUNLOCK_FW
    #define OMNI_SAFE_SOCKEPALOCK_FW
    #define OMNI_SAFE_SOCKEPOALOCK_FW(o) 
#endif

#define OMNI_EPDESC_CONN_FLAG_FW 1
#define OMNI_EPDESC_SHUT_FLAG_FW 2

omni::net::socket_error omni::net::endpoint_descriptor::_close(uint16_t timeout, bool shutdown)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::socket_error omni::net::endpoint_descriptor::_receive(void* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& received)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::socket_error omni::net::endpoint_descriptor::_send(const void* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& sent)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::endpoint_descriptor::endpoint_descriptor() :
    OMNI_CTOR_FW(omni::net::endpoint_descriptor)
    m_socket(OMNI_INVALID_SOCKET), m_addr(),  m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_status()
    OMNI_SAFE_SOCKEPMTX_FW
{
}

omni::net::endpoint_descriptor::endpoint_descriptor(const omni::net::endpoint_descriptor& cp) :
    OMNI_CTOR_FW(omni::net::endpoint_descriptor)
    m_socket(OMNI_INVALID_SOCKET), m_addr(), m_last_err(omni::net::socket_error::UNSPECIFIED),
    m_status()
    OMNI_SAFE_SOCKEPMTX_FW
{
    this->swap(*const_cast<omni::net::endpoint_descriptor*>(&cp));
}

omni::net::endpoint_descriptor::~endpoint_descriptor()
{
    OMNI_TRY_FW
    if (this->close() != omni::net::socket_error::SUCCESS) {
        OMNI_D1_FW("error closing socket");
    }
    OMNI_DTOR_FW
    OMNI_CATCH_FW
    OMNI_D5_FW("destroyed");
}

uint32_t omni::net::endpoint_descriptor::endpoint() const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return static_cast<uint32_t>(this->m_addr.sin_addr.s_addr);
}

uint16_t omni::net::endpoint_descriptor::port() const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return static_cast<uint16_t>(this->m_addr.sin_port);
}

omni::net::socket_t omni::net::endpoint_descriptor::native_handle() const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return this->m_socket;
}

bool omni::net::endpoint_descriptor::is_connected() const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW);
}

bool omni::net::endpoint_descriptor::is_shutdown() const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_SHUT_FLAG_FW);
}

omni::net::socket_error omni::net::endpoint_descriptor::last_error() const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return this->m_last_err;
}

omni::net::socket_error omni::net::endpoint_descriptor::connect(const omni::net::socket_t& serv_sock)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::socket_error omni::net::endpoint_descriptor::close()
{
    return this->close(0);
}

omni::net::socket_error omni::net::endpoint_descriptor::close(uint16_t timeout)
{
    return this->_close(timeout, false);
}

omni::net::socket_error omni::net::endpoint_descriptor::ioc(uint32_t op_code, omni::net::xfr_t* val, int32_t& result)
{
    OMNI_SAFE_SOCKEPALOCK_FW
    if (!OMNI_VAL_HAS_FLAG_BIT(this->m_status, OMNI_EPDESC_CONN_FLAG_FW)) {
        return (this->m_last_err = omni::net::socket_error::NOT_CONNECTED);
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

omni::net::socket_error omni::net::endpoint_descriptor::get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::socket_error omni::net::endpoint_descriptor::get_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor::get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val)
{
    return this->get_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor::shutdown(omni::net::socket_shutdown how)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::socket_error omni::net::endpoint_descriptor::set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val)
{
    OMNI_SAFE_SOCKEPALOCK_FW
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

omni::net::socket_error omni::net::endpoint_descriptor::set_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

omni::net::socket_error omni::net::endpoint_descriptor::set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val)
{
    return this->set_socket_option(op_level, static_cast<int32_t>(op_name), op_val);
}

void omni::net::endpoint_descriptor::swap(omni::net::endpoint_descriptor& other)
{
    if (this != &other) {
        OMNI_SAFE_SOCKEPALOCK_FW
        OMNI_SAFE_SOCKEPOALOCK_FW(other)
        std::swap(this->m_socket, other.m_socket);
        std::swap(this->m_addr, other.m_addr);
        std::swap(this->m_last_err, other.m_last_err);
        std::swap(this->m_status, other.m_status);
    }
}

omni::string_t omni::net::endpoint_descriptor::to_string_t() const
{
    omni::sstream_t s;
    OMNI_SAFE_SOCKEPLOCK_FW
    s << inet_ntoa(this->m_addr.sin_addr) << ":" << static_cast<uint16_t>(this->m_addr.sin_port);
    OMNI_SAFE_SOCKEPUNLOCK_FW
    return s.str();
}

std::string omni::net::endpoint_descriptor::to_string() const
{
    std::stringstream s;
    OMNI_SAFE_SOCKEPLOCK_FW
    s << inet_ntoa(this->m_addr.sin_addr) << ":" << static_cast<uint16_t>(this->m_addr.sin_port);
    OMNI_SAFE_SOCKEPUNLOCK_FW
    return s.str();
}

std::wstring omni::net::endpoint_descriptor::to_wstring() const
{
    std::wstringstream s;
    OMNI_SAFE_SOCKEPLOCK_FW
    s << inet_ntoa(this->m_addr.sin_addr) << ":" << static_cast<uint16_t>(this->m_addr.sin_port);
    OMNI_SAFE_SOCKEPUNLOCK_FW
    return s.str();
}

omni::net::endpoint_descriptor& omni::net::endpoint_descriptor::operator=(omni::net::endpoint_descriptor& other)
{
    OMNI_SAFE_SOCKEPALOCK_FW
    OMNI_SAFE_SOCKEPOALOCK_FW(other)
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

bool omni::net::endpoint_descriptor::operator==(const omni::net::endpoint_descriptor& other) const
{
    OMNI_UNUSED(other);
    return false;
}

bool omni::net::endpoint_descriptor::operator==(const omni::net::socket_t& sock) const
{
    OMNI_SAFE_SOCKEPALOCK_FW
    return this->m_socket == sock;
}

bool omni::net::endpoint_descriptor::operator==(uint32_t ep) const
{
    return this->endpoint() == ep;
}
