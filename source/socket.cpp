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
#include "omni/defs.hpp"
#include <sstream>
#if defined(OMNI_OS_WIN)
    #include <io.h>
    #include <winsock2.h>
    #include <malloc.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <signal.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "omni/omni.hpp"
#include "omni/socket.hpp"
#include "omni/net.hpp"
#include "omni/system.hpp"
#include "omni/exceptions.hpp"
#include "omni/debug.hpp"

omni::net::socket::socket() :
    OMNI_INHERIT_OBJECT_DEF_MACRO
    blocking(0),
    dontFragment(0),
    enableBroadcast(0),
    exclusiveAddressUse(0),
    lingerstate(),
    multicastLoopback(0),
    nodelay(0),
    receiveBufferSize(0),
    receiveTimeout(0),
    sendBufferSize(0),
    sendTimeout(0),
    ttl(0),
    useOnlyOverlappedIO(0),
    datareceived(),
    m_AddressFamily(omni::net::address_family::UNKNOWN),
    m_Available(0),
    m_IsConnected(0),
    m_IsBound(0),
    m_IsShutdown(0),
    m_Handle(0),
    m_LocalEndPoint(""),
    m_ProtocolType(omni::net::protocol_type::UNKNOWN),
    m_RemoteEndPoint(""),
    m_SocketType(omni::net::socket_type::UNKNOWN)
{
    this->p_Initialize(
        omni::net::address_family::UNKNOWN,
        omni::net::socket_type::UNKNOWN,
        omni::net::protocol_type::UNKNOWN
    );
}

omni::net::socket::socket(const omni::net::socket &cp) :
    OMNI_INHERIT_OBJECT_CPY_MACRO
    blocking(cp.blocking),
    dontFragment(cp.dontFragment),
    enableBroadcast(cp.enableBroadcast),
    exclusiveAddressUse(cp.exclusiveAddressUse),
    lingerstate(cp.lingerstate),
    multicastLoopback(cp.multicastLoopback),
    nodelay(cp.nodelay),
    receiveBufferSize(cp.receiveBufferSize),
    receiveTimeout(cp.receiveTimeout),
    sendBufferSize(cp.sendBufferSize),
    sendTimeout(cp.sendTimeout),
    ttl(cp.ttl),
    useOnlyOverlappedIO(cp.useOnlyOverlappedIO),
    datareceived(cp.datareceived),
    m_AddressFamily(omni::net::address_family::UNKNOWN),
    m_Available(0),
    m_IsConnected(0),
    m_IsBound(0),
    m_IsShutdown(0),
    m_Handle(0),
    m_LocalEndPoint(""),
    m_ProtocolType(omni::net::protocol_type::UNKNOWN),
    m_RemoteEndPoint(""),
    m_SocketType(omni::net::socket_type::UNKNOWN)
{
    this->p_Initialize(
        omni::net::address_family::UNKNOWN,
        omni::net::socket_type::UNKNOWN,
        omni::net::protocol_type::UNKNOWN
    );
    this->m_AddressFamily = cp.addressFamily();
    this->m_Available = cp.available();
    this->m_IsConnected = cp.connected();
    this->m_IsBound = cp.is_bound();
    this->m_IsShutdown = cp.is_shut();
    this->m_Handle = cp.handle();
    this->m_LocalEndPoint = cp.localEndPoint();
    this->m_ProtocolType = cp.protocolType();
    this->m_RemoteEndPoint = cp.remoteEndPoint();
    this->m_SocketType = cp.socketType();
}

omni::net::socket::socket(
    omni::net::address_family::enum_t addressFamily, 
    omni::net::socket_type::enum_t socketType, 
    omni::net::protocol_type::enum_t protocolType) :
    OMNI_INHERIT_OBJECT_DEF_MACRO
    blocking(0),
    dontFragment(0),
    enableBroadcast(0),
    exclusiveAddressUse(0),
    lingerstate(),
    multicastLoopback(0),
    nodelay(0),
    receiveBufferSize(0),
    receiveTimeout(0),
    sendBufferSize(0),
    sendTimeout(0),
    ttl(0),
    useOnlyOverlappedIO(0),
    datareceived(),
    m_AddressFamily(addressFamily),
    m_Available(0),
    m_IsConnected(0),
    m_IsBound(0),
    m_IsShutdown(0),
    m_Handle(0),
    m_LocalEndPoint(""),
    m_ProtocolType(protocolType),
    m_RemoteEndPoint(""),
    m_SocketType(socketType)
{
    this->p_Initialize(addressFamily, socketType, protocolType);
}

omni::net::socket::~socket()
{
    this->dispose();
}

omni::net::address_family::enum_t omni::net::socket::addressFamily() const
{
    return this->m_AddressFamily;
}

int omni::net::socket::available() const
{
    return this->m_Available;
}

bool omni::net::socket::connected() const
{
    return this->m_IsConnected;
}

unsigned int omni::net::socket::handle() const
{
    return this->m_Handle;
}

void omni::net::socket::p_Initialize(
    omni::net::address_family::enum_t addressFamily, 
    omni::net::socket_type::enum_t socketType, 
    omni::net::protocol_type::enum_t protocolType
                                    )
{
    #if defined(OMNI_SHOW_DEBUG_ERR)
        dbga << "initializing" << std::endl;
    #endif
    // DEV_NOTE: Normally we would use the initialization list, but since we have actual functions and API calls to make
    // it's best to do the initialization in an initialize function
    this->m_Handle = -1;
    #if defined(OMNI_OS_WIN) // Microsoft set needed for sockets
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbga << "Calling WSAStartup" << std::endl;
        #endif
        WSADATA WSStartData;
        if ((WSAStartup(MAKEWORD(1,1), &WSStartData)) != 0) {
            #if defined(OMNI_SHOW_DEBUG_ERR)
                dbgerra << "Could not create omni::net::socket object (WSAStartup failed)" << std::endl;
            #endif
            #if !defined(OMNI_NO_THROW)
                throw omni::exceptions::net::wsa_failed();
            #endif
        }
    #endif
    int af = static_cast<int>(addressFamily);
    int st = static_cast<int>(socketType);
    int pt = static_cast<int>(protocolType);
    if ((this->m_Handle = ::socket(af, st, pt)) == -1) {
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbgerra << "Could not create socket object (socket() failed)" << std::endl;
        #endif
        #if !defined(OMNI_NO_THROW)
            throw omni::exceptions::net::socket_create_failed();
        #endif
    }
    this->m_AddressFamily = addressFamily;
    this->m_ProtocolType = protocolType;
    this->m_SocketType = socketType;
    this->m_Available = -1;
    this->m_IsConnected = false;
    this->m_IsBound = false;
    this->m_IsShutdown = false;
    this->m_LocalEndPoint = "";
    this->m_RemoteEndPoint = "";
    this->sendBufferSize = 0;
    this->sendTimeout = 0;
    this->ttl = 255;
    this->useOnlyOverlappedIO = false;
    this->receiveBufferSize = 65536;
    this->receiveTimeout = 1000;
    this->multicastLoopback = false;
    this->nodelay = true;
    this->dontFragment = false;
    this->enableBroadcast = false;
    this->exclusiveAddressUse = false;
}

bool omni::net::socket::is_bound() const
{
    return this->m_IsBound;
}

bool omni::net::socket::is_shut() const
{
    return this->m_IsShutdown;
}

const char *omni::net::socket::localEndPoint() const
{
    // TODO: Finish
    return this->m_LocalEndPoint;
}

omni::net::protocol_type::enum_t omni::net::socket::protocolType() const
{
    return this->m_ProtocolType;
}

const char *omni::net::socket::remoteEndPoint() const
{
    // TODO: Finish
    return this->m_RemoteEndPoint;
}

omni::net::socket_type::enum_t omni::net::socket::socketType() const
{
    return this->m_SocketType;
}

omni::net::socket &omni::net::socket::accept()
{
    // TODO: Finish
    return *this;
}

omni::net::socket &omni::net::socket::bind(std::string localIP)
{
    // TODO: Finish
    OMNI_UNUSED(localIP);
    return *this;
}

bool omni::net::socket::p_CloseSocket(int timeout, bool shutdown) 
{
    if (this->m_Handle == -1) { 
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbga << "The handle is invalid" << std::endl;
        #endif
        return false; 
    }
    if (timeout > 0) {
        // TODO: setsockopt needs to set a LINGER struct so that it's timeout val = timeout
        //setsockopt(m_Handle, 
        /*int setsockopt(
            SOCKET s,
            int level,
            int optname,
            const char *optval,
            int optlen
        );*/
    }
    if (shutdown && !this->shutdown(omni::net::socket_shutdown::BOTH)) {
        #if defined(OMNI_SHOW_DEBUG_ERR)
            int ec = omni::system::getLastError();
            dbga << "Could not shutdown the socket: " << ec << " - " << omni::system::getErrorString(ec) << std::endl;
        #endif
    }
    if (!this->m_IsConnected) {
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbga << "The socket has already been disconnected, no need to close" << std::endl;
        #endif
        return true;
    }
    #if defined(OMNI_SHOW_DEBUG_ERR)
        dbga << "Closing the socket" << std::endl;
    #endif
    int ret = -1;
    #if defined(OMNI_OS_WIN)
        ret = closesocket(this->m_Handle);
        if (ret == 0) { WSACleanup(); }
    #else
        ret = close(this->m_Handle);
    #endif
    #if defined(OMNI_SHOW_DEBUG_ERR)
        if (ret != 0) { 
            int ec = omni::system::getLastError();
            dbga << "There was an error closing the socket: return value = " << ret << ", error = " << ec << " - " << omni::system::getErrorString(ec) << std::endl;
        }
    #endif
    this->m_IsConnected = !(ret == 0);
    return this->m_IsConnected;
}

bool omni::net::socket::close()
{
    return this->close(1000);
}

bool omni::net::socket::close(int timeout)
{
    return this->p_CloseSocket(timeout, true);
}

bool omni::net::socket::connect(std::string host, int port)
{
    if (this->m_Handle == -1) { 
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbga << "The handle is invalid" << std::endl;
        #endif
        return false; 
    }
    struct sockaddr_in Client;
    memset(&Client, 0, (sizeof(Client))); // recv
    Client.sin_family = static_cast<int>(this->m_AddressFamily);
    Client.sin_port = htons(port);
    Client.sin_addr.s_addr = inet_addr(host.c_str());
    #if defined(OMNI_SHOW_DEBUG_ERR)
        dbga << "Attempting to connect the socket to " << host << ":" << port << std::endl;
    #endif
    this->m_IsConnected = ((::connect(this->m_Handle, (reinterpret_cast<struct sockaddr*>(&Client)), sizeof(Client))) == 0);
    this->m_IsShutdown = !this->m_IsConnected;
    return this->m_IsConnected;
}

bool omni::net::socket::disconnect(bool reuseSocket)
{
    return this->p_CloseSocket(0, reuseSocket);
}

void omni::net::socket::dispose()
{
    if (this->m_IsConnected) { this->close(0); }
}

omni::net::socket *omni::net::socket::duplicateAndClose()
{
    omni::net::socket *Copy = new socket(*this);
    this->close();
    return Copy;
    // TODO: Finish .. Socket *Copy = new socket(*this);
    //                 this->Close();
    //                 return Copy;
    return (new omni::net::socket());
}

char *omni::net::socket::getSocketOption(
    omni::net::socket_option_level::enum_t optionLevel, 
    omni::net::socket_option_name::enum_t optionName, 
    int optionLength) const
{
    // TODO: Finish
    OMNI_UNUSED(optionLevel);
    OMNI_UNUSED(optionName);
    OMNI_UNUSED(optionLength);
    return 0;
}

int omni::net::socket::iocontrol(int ioControlCode, char *optionInValue, char *optionOutValue)
{
    // TODO: Finish
    OMNI_UNUSED(ioControlCode);
    OMNI_UNUSED(optionInValue);
    OMNI_UNUSED(optionOutValue);
    return 0;
}

omni::net::socket &omni::net::socket::listen(int backlog)
{
    // TODO: Finish
    OMNI_UNUSED(backlog);
    return *this;
}

bool omni::net::socket::poll(int microSeconds, omni::net::select_mode::enum_t mode)
{
    // TODO: Finish
    OMNI_UNUSED(microSeconds);
    OMNI_UNUSED(mode);
    return 0;
}

int omni::net::socket::receive(char *buffer, int size)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(size);
    return 0;
}

int omni::net::socket::receive(char *buffer, int size, omni::net::socket_flags::enum_t socketFlags)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    return 0;
}

int omni::net::socket::receive(char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(offset);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    return 0;
}

int omni::net::socket::receive(
    char *buffer, 
    int offset, 
    int size, 
    omni::net::socket_flags::enum_t socketFlags, 
    omni::net::socket_error::enum_t &errorCode
                            )
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(offset);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    OMNI_UNUSED(errorCode);
    return 0;
}

int omni::net::socket::receiveFrom(
    char *buffer, 
    int size, 
    omni::net::socket_flags::enum_t socketFlags, 
    const char *remoteIP
                                )
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    OMNI_UNUSED(remoteIP);
    return 0;
}

int omni::net::socket::receiveFrom(
    char *buffer, 
    int offset, 
    int size, 
    omni::net::socket_flags::enum_t socketFlags, 
    const char *remoteIP
                                )
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(offset);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    OMNI_UNUSED(remoteIP);
    return 0;
}

int omni::net::socket::send(const char *buffer, int size, omni::net::socket_flags::enum_t socketFlags)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    return 0;
}

int omni::net::socket::send(const char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(offset);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    return 0;
}

int omni::net::socket::send(
    const char *buffer, 
    int offset, 
    int size, 
    omni::net::socket_flags::enum_t socketFlags, 
    omni::net::socket_error::enum_t &errorCode
                            )
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(offset);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    OMNI_UNUSED(errorCode);
    return 0;
}

int omni::net::socket::sendto(const char *buffer, int size, omni::net::socket_flags::enum_t socketFlags, const char *remoteIP)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    OMNI_UNUSED(remoteIP);
    return 0;
}

int omni::net::socket::sendto(const char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags, const char *remoteIP)
{
    // TODO: Finish
    OMNI_UNUSED(buffer);
    OMNI_UNUSED(offset);
    OMNI_UNUSED(size);
    OMNI_UNUSED(socketFlags);
    OMNI_UNUSED(remoteIP);
    return 0;
}

omni::net::socket &omni::net::socket::setSocketOption(
    omni::net::socket_option_level::enum_t optionLevel, 
    omni::net::socket_option_name::enum_t optionName, 
    int optionValue
                                    )
{
    // TODO: Finish
    OMNI_UNUSED(optionLevel);
    OMNI_UNUSED(optionName);
    OMNI_UNUSED(optionValue);
    return *this;
}

bool omni::net::socket::shutdown(omni::net::socket_shutdown::enum_t how)
{
    if (this->m_Handle == -1) { 
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbga << "The handle is invalid" << std::endl;
        #endif
        return false; 
    }
    if (this->m_IsShutdown) { 
        #if defined(OMNI_SHOW_DEBUG_ERR)
            dbga << "The socket is shutdown, nothing to do" << std::endl;
        #endif
        return true;
    }
    #if defined(OMNI_SHOW_DEBUG_ERR)
        dbga << "Shutting down the socket" << std::endl;
    #endif
    this->m_IsShutdown = (::shutdown(this->m_Handle, static_cast<int>(how)) == 0);
    if (!this->m_IsShutdown) { // Stop sending/receiving data
        #if defined(OMNI_SHOW_DEBUG_ERR)
            int ErrorCode = omni::system::getLastError();
            dbga << "Socket shutdown failed: " << ErrorCode << " - " << omni::system::getErrorString(ErrorCode) << std::endl;
        #endif
    }
    return this->m_IsShutdown;
}

const std::string omni::net::socket::tostring() const
{
    // TODO: return this->IP
    return "0.0.0.0";
}

omni::net::socket &omni::net::socket::operator= (const omni::net::socket &other)
{
    this->close();
    this->blocking = other.blocking;
    this->dontFragment = other.dontFragment;
    this->enableBroadcast = other.enableBroadcast;
    this->exclusiveAddressUse = other.exclusiveAddressUse;
    this->lingerstate = other.lingerstate,
    this->multicastLoopback = other.multicastLoopback;
    this->nodelay = other.nodelay;
    this->receiveBufferSize = other.receiveBufferSize;
    this->receiveTimeout = other.receiveTimeout;
    this->sendBufferSize = other.sendBufferSize;
    this->sendTimeout = other.sendTimeout;
    this->ttl = other.ttl;
    this->useOnlyOverlappedIO = other.useOnlyOverlappedIO;
    this->datareceived = other.datareceived;    
    this->m_AddressFamily = other.addressFamily();
    this->m_Available = other.available();
    this->m_IsConnected = other.connected();
    this->m_IsBound = other.is_bound();
    this->m_IsShutdown = other.is_shut();
    this->m_Handle = other.handle();
    this->m_LocalEndPoint = other.localEndPoint();
    this->m_ProtocolType = other.protocolType();
    this->m_RemoteEndPoint = other.remoteEndPoint();
    this->m_SocketType = other.socketType();
    return *this;
}
