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
#if !defined(OMNI_NET_DEF_HPP)
#define OMNI_NET_DEF_HPP 1

#include <omni/defs/global.hpp>
#include <omni/strings.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <csignal>
// DEV_NOTE: used for buffers in the socket classes regardless of what the default omni_seq_t is
#include <vector>
#if defined(OMNI_OS_WIN)
    #include <io.h>
    #include <ws2tcpip.h>
    #if !defined(OMNI_WIN_NO_PRAGMA_WS2_32_LIB)
        #pragma comment(lib, "ws2_32.lib")
    #endif
#else
    #if !defined(_XOPEN_SOURCE_EXTENDED)
        #define _XOPEN_SOURCE_EXTENDED 1
    #endif
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <sys/un.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <netinet/tcp.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <ctype.h>
    #include <signal.h>
    #include <fcntl.h>
#endif

#define OMNI_SOCKADDR_IN_T_FW struct sockaddr_in
#define OMNI_SOCKADDR_IN6_T_FW struct sockaddr_in6
#define OMNI_SOCKADDR_UN_T_FW struct sockaddr_un
#define OMNI_SOCKADDR_T_FW struct sockaddr

#if defined(OMNI_OS_WIN)
    // #define OMNI_ALLOW_UNIX_SOCKET 1
    /*
        DEV_NOTE: the user must explicitly enable this flag, Windows doesn't have the sockaddr_un struct
        except for certain WSL subsystems. So this flag must be explicitly enabled through the build system
        to enable the Unix socket.
    */
#else
    #define OMNI_ALLOW_UNIX_SOCKET 1
#endif

#if !defined(OMNI_UNIX_SOCKET_MAX_PATH)
    // the sockaddr_un.sun_path var is typically defined as char sun_path[104],
    // but on some systems can be 108 (potentially more), so 128 seems safe.
    #define OMNI_UNIX_SOCKET_MAX_PATH 128
#endif

#if !defined(OMNI_SOMAXCONN)
    #if defined(SOMAXCONN)
        #define OMNI_SOMAXCONN SOMAXCONN
    #else
        #define OMNI_SOMAXCONN 128
    #endif
#endif

#if !defined(OMNI_SOCKET_DEFAULT_GET_HOST_PORT)
    #define OMNI_SOCKET_DEFAULT_GET_HOST_PORT 80 
#endif
#if !defined(OMNI_SOCKET_DEFAULT_BACKLOG)
    #define OMNI_SOCKET_DEFAULT_BACKLOG OMNI_SOMAXCONN
#endif

#if defined(OMNI_WIN_API)
    #define OMNI_SOCKET_OPEN_FW(af, t, p) ::WSASocket(af, static_cast<int>(t), static_cast<int>(p), NULL, 0, WSA_FLAG_OVERLAPPED)
    #define OMNI_SOCKET_ACCEPT_FW(s, a, l) ::WSAAccept(s, a, l, NULL, NULL)
    #define OMNI_SOCKET_CONNECT_FW(s, sa, l) ::WSAConnect(s, sa, l, NULL, NULL, NULL, NULL)
    #define OMNI_SOCKET_CLOSE_FW(s) ::closesocket(s)
#else
    #define OMNI_SOCKET_OPEN_FW(af, t, p) ::socket(af, static_cast<int>(t), static_cast<int>(p))
    #define OMNI_SOCKET_ACCEPT_FW(s, a, l) ::accept(s, a, l)
    #define OMNI_SOCKET_CONNECT_FW(s, sa, l) ::connect(s, sa, l)
    #define OMNI_SOCKET_CLOSE_FW(s) ::close(s)
#endif

#if defined(OMNI_OS_WIN)
    #define OMNI_SOCKET_T_FW SOCKET
    #define OMNI_SOCKLEN_FW int
    #define OMNI_SOCKET_XFR_T_FW char
    #define OMNI_INVALID_SOCKET INVALID_SOCKET
    #define OMNI_SOCK_SYSERR_FW SOCKET_ERROR
    #define OMNI_SOCKET_ERR_FW ::WSAGetLastError()
    #if !defined(OMNI_WINSOCK_HIGH_FW)
        #define OMNI_WINSOCK_HIGH_FW 2
    #endif
    #if !defined(OMNI_WINSOCK_LOW_FW)
        #define OMNI_WINSOCK_LOW_FW 2
    #endif
    #define OMNI_SOCK_RECEIVE_FW SD_RECEIVE
    #define OMNI_SOCK_SEND_FW SD_SEND
    #define OMNI_SOCK_BOTH_FW SD_BOTH
    #define OMNI_MSG_EOR_FW 0
    #define OMNI_SOCK_FLAGS_NONE -1
    #define OMNI_SIN_FAMILY_FW ADDRESS_FAMILY
#else
    #define OMNI_SOCKET_T_FW int
    #define OMNI_SOCKLEN_FW socklen_t
    #define OMNI_SOCKET_XFR_T_FW void
    #define OMNI_INVALID_SOCKET -1
    #define OMNI_SOCK_SYSERR_FW -1
    #define OMNI_SOCKET_ERR_FW errno
    #define OMNI_SOCK_RECEIVE_FW SHUT_RD
    #define OMNI_SOCK_SEND_FW SHUT_WR
    #define OMNI_SOCK_BOTH_FW SHUT_RDWR
    #define OMNI_MSG_EOR_FW MSG_EOR
    #define OMNI_SOCK_FLAGS_NONE 0
    #if defined(OMNI_OS_APPLE)
        #define OMNI_SIN_FAMILY_FW sa_family_t
    #else
        #define OMNI_SIN_FAMILY_FW short
    #endif
#endif

// start network error codes

#if defined(OMNI_OS_WIN)
    #define OMNI_SOCK_ERR_OPERATION_ABORTED_FW WSA_OPERATION_ABORTED
    // WSA_IO_INCOMPLETE is 996 and there is no real equivelent of general I/O error in WinSock,
    // EIO in most *nix is defined as 5, so just make it the same for Win
    #define OMNI_SOCK_ERR_IO_ERROR_FW 5
    #define OMNI_SOCK_ERR_IO_PENDING_FW WSA_IO_PENDING
    #define OMNI_SOCK_ERR_INTERRUPTED_FW WSAEINTR
    // WSAEACCESS is the only one in WinSock that is about permission, but since EPERM and EACCESS are
    // different on *nix systems we'll make it the same on Win, EPERM on most *nix is defined as 1
    #define OMNI_SOCK_ERR_PERMISSION_FW 1
    #define OMNI_SOCK_ERR_ACCESS_DENIED_FW WSAEACCES
    #define OMNI_SOCK_ERR_FAULT_FW WSAEFAULT
    #define OMNI_SOCK_ERR_INSUFFICIENT_MEMORY_FW WSA_NOT_ENOUGH_MEMORY
    #define OMNI_SOCK_ERR_INVALID_ARGUMENT_FW WSAEINVAL
    #define OMNI_SOCK_ERR_INVALID_DESCRIPTOR_FW WSAEBADF
    #define OMNI_SOCK_ERR_TOO_MANY_OPEN_SOCKETS_FW WSAEMFILE
    #define OMNI_SOCK_ERR_WOULD_BLOCK_FW WSAEWOULDBLOCK
    #define OMNI_SOCK_ERR_IN_PROGRESS_FW WSAEINPROGRESS
    #define OMNI_SOCK_ERR_ALREADY_IN_PROGRESS_FW WSAEALREADY
    #define OMNI_SOCK_ERR_NOT_SOCKET_FW WSAENOTSOCK
    #define OMNI_SOCK_ERR_DESTINATION_ADDRESS_REQUIRED_FW WSAEDESTADDRREQ
    #define OMNI_SOCK_ERR_MESSAGE_SIZE_FW WSAEMSGSIZE
    #define OMNI_SOCK_ERR_PROTOCOL_TYPE_FW WSAEPROTOTYPE
    #define OMNI_SOCK_ERR_PROTOCOL_OPTION_FW WSAENOPROTOOPT
    #define OMNI_SOCK_ERR_PROTOCOL_NOT_SUPPORTED_FW WSAEPROTONOSUPPORT
    #define OMNI_SOCK_ERR_SOCKET_NOT_SUPPORTED_FW WSAESOCKTNOSUPPORT
    #define OMNI_SOCK_ERR_OPERATION_NOT_SUPPORTED_FW WSAEOPNOTSUPP
    #define OMNI_SOCK_ERR_PROTOCOL_FAMILY_NOT_SUPPORTED_FW WSAEPFNOSUPPORT
    #define OMNI_SOCK_ERR_ADDRESS_FAMILY_NOT_SUPPORTED_FW WSAEAFNOSUPPORT
    #define OMNI_SOCK_ERR_ADDRESS_ALREADY_IN_USE_FW WSAEADDRINUSE
    #define OMNI_SOCK_ERR_ADDRESS_NOT_AVAILABLE_FW WSAEADDRNOTAVAIL
    #define OMNI_SOCK_ERR_NETWORK_DOWN_FW WSAENETDOWN
    #define OMNI_SOCK_ERR_NETWORK_UNREACHABLE_FW WSAENETUNREACH
    #define OMNI_SOCK_ERR_NETWORK_RESET_FW WSAENETRESET
    #define OMNI_SOCK_ERR_CONNECTION_ABORTED_FW WSAECONNABORTED
    #define OMNI_SOCK_ERR_CONNECTION_RESET_FW WSAECONNRESET
    #define OMNI_SOCK_ERR_NO_BUFFER_SPACE_AVAILABLE_FW WSAENOBUFS
    #define OMNI_SOCK_ERR_IS_CONNECTED_FW WSAEISCONN
    #define OMNI_SOCK_ERR_NOT_CONNECTED_FW WSAENOTCONN
    #define OMNI_SOCK_ERR_SHUTDOWN_FW WSAESHUTDOWN
    #define OMNI_SOCK_ERR_TIMED_OUT_FW WSAETIMEDOUT
    #define OMNI_SOCK_ERR_CONNECTION_REFUSED_FW WSAECONNREFUSED
    #define OMNI_SOCK_ERR_LOOP_FW WSAELOOP
    #define OMNI_SOCK_ERR_NAME_TOO_LONG_FW WSAENAMETOOLONG
    #define OMNI_SOCK_ERR_HOST_DOWN_FW WSAEHOSTDOWN
    #define OMNI_SOCK_ERR_HOST_UNREACHABLE_FW WSAEHOSTUNREACH
    #define OMNI_SOCK_ERR_PROCESS_LIMIT_FW WSAEPROCLIM
    #define OMNI_SOCK_ERR_SYSTEM_NOT_READY_FW WSASYSNOTREADY
    #define OMNI_SOCK_ERR_VERSION_NOT_SUPPORTED_FW WSAVERNOTSUPPORTED
    #define OMNI_SOCK_ERR_NOT_INITIALIZED_FW WSANOTINITIALISED
    #define OMNI_SOCK_ERR_DISCONNECTING_FW WSAEDISCON
    #define OMNI_SOCK_ERR_TYPE_NOT_FOUND_FW WSATYPE_NOT_FOUND
    #define OMNI_SOCK_ERR_NO_HOST_FW WSAHOST_NOT_FOUND
    #define OMNI_SOCK_ERR_AGAIN_FW WSATRY_AGAIN
    #define OMNI_SOCK_ERR_NO_RECOVER_FW WSANO_RECOVERY
    #define OMNI_SOCK_ERR_NO_DAT_FW WSANO_DATA
#else
    #define OMNI_SOCK_ERR_OPERATION_ABORTED_FW 995 // "Overlapped operation aborted" .. windows specific ??
    #define OMNI_SOCK_ERR_IO_ERROR_FW EIO
    #define OMNI_SOCK_ERR_IO_PENDING_FW 997 // "Overlapped operations will complete later." .. windows specific ??
    #define OMNI_SOCK_ERR_INTERRUPTED_FW EINTR
    #define OMNI_SOCK_ERR_PERMISSION_FW EPERM
    #define OMNI_SOCK_ERR_ACCESS_DENIED_FW EACCES
    #define OMNI_SOCK_ERR_FAULT_FW EFAULT
    #define OMNI_SOCK_ERR_INSUFFICIENT_MEMORY_FW ENOMEM
    #define OMNI_SOCK_ERR_INVALID_ARGUMENT_FW EINVAL
    #define OMNI_SOCK_ERR_INVALID_DESCRIPTOR_FW EBADF
    #define OMNI_SOCK_ERR_TOO_MANY_OPEN_SOCKETS_FW ENFILE
    #define OMNI_SOCK_ERR_WOULD_BLOCK_FW EWOULDBLOCK
    #define OMNI_SOCK_ERR_IN_PROGRESS_FW EINPROGRESS
    #define OMNI_SOCK_ERR_ALREADY_IN_PROGRESS_FW EALREADY
    #define OMNI_SOCK_ERR_NOT_SOCKET_FW ENOTSOCK
    #define OMNI_SOCK_ERR_DESTINATION_ADDRESS_REQUIRED_FW EDESTADDRREQ
    #define OMNI_SOCK_ERR_MESSAGE_SIZE_FW EMSGSIZE
    #define OMNI_SOCK_ERR_PROTOCOL_TYPE_FW EPROTOTYPE
    #define OMNI_SOCK_ERR_PROTOCOL_OPTION_FW EPROTO
    #define OMNI_SOCK_ERR_PROTOCOL_NOT_SUPPORTED_FW EPROTONOSUPPORT
    #define OMNI_SOCK_ERR_SOCKET_NOT_SUPPORTED_FW ESOCKTNOSUPPORT
    #define OMNI_SOCK_ERR_OPERATION_NOT_SUPPORTED_FW EOPNOTSUPP
    #define OMNI_SOCK_ERR_PROTOCOL_FAMILY_NOT_SUPPORTED_FW EPFNOSUPPORT
    #define OMNI_SOCK_ERR_ADDRESS_FAMILY_NOT_SUPPORTED_FW EAFNOSUPPORT
    #define OMNI_SOCK_ERR_ADDRESS_ALREADY_IN_USE_FW EADDRINUSE
    #define OMNI_SOCK_ERR_ADDRESS_NOT_AVAILABLE_FW EADDRNOTAVAIL
    #define OMNI_SOCK_ERR_NETWORK_DOWN_FW ENETDOWN
    #define OMNI_SOCK_ERR_NETWORK_UNREACHABLE_FW ENETUNREACH
    #define OMNI_SOCK_ERR_NETWORK_RESET_FW ENETRESET
    #define OMNI_SOCK_ERR_CONNECTION_ABORTED_FW ECONNABORTED
    #define OMNI_SOCK_ERR_CONNECTION_RESET_FW ECONNRESET
    #define OMNI_SOCK_ERR_NO_BUFFER_SPACE_AVAILABLE_FW ENOBUFS
    #define OMNI_SOCK_ERR_IS_CONNECTED_FW EISCONN
    #define OMNI_SOCK_ERR_NOT_CONNECTED_FW ENOTCONN
    #define OMNI_SOCK_ERR_SHUTDOWN_FW ESHUTDOWN
    #define OMNI_SOCK_ERR_TIMED_OUT_FW ETIMEDOUT
    #define OMNI_SOCK_ERR_CONNECTION_REFUSED_FW ECONNREFUSED
    #define OMNI_SOCK_ERR_LOOP_FW ELOOP
    #define OMNI_SOCK_ERR_NAME_TOO_LONG_FW ENAMETOOLONG
    #define OMNI_SOCK_ERR_HOST_DOWN_FW EHOSTDOWN
    #define OMNI_SOCK_ERR_HOST_UNREACHABLE_FW EHOSTUNREACH
    #define OMNI_SOCK_ERR_PROCESS_LIMIT_FW EMFILE
    #define OMNI_SOCK_ERR_SYSTEM_NOT_READY_FW 10091 // "WSAStartup not called" .. windows specific
    #define OMNI_SOCK_ERR_VERSION_NOT_SUPPORTED_FW 10092 // "Winsock.dll wrong version" .. windows specific
    #define OMNI_SOCK_ERR_NOT_INITIALIZED_FW 10093 // "Successful WSAStartup not yet performed." .. windows specific
    #define OMNI_SOCK_ERR_DISCONNECTING_FW 10101 // "Graceful shutdown in progress." happens for WSARecv, *nix equiv would be ENOTCONN (already marked), so use windows number
    #define OMNI_SOCK_ERR_TYPE_NOT_FOUND_FW 10109 // "class type not found" .. windows specific ??
    #define OMNI_SOCK_ERR_NO_HOST_FW 11001 // "Host not found." .. this would be one of the other host fail error codes, so use windows number
    #define OMNI_SOCK_ERR_AGAIN_FW 11002 // "Nonauthoritative host not found." .. see above note about host errors, using windows num
    #define OMNI_SOCK_ERR_NO_RECOVER_FW NO_RECOVERY // doesn't make much sense for non-recoverable in *nix, so just use this one from netdb.h
    #define OMNI_SOCK_ERR_NO_DAT_FW ENODATA // there is a "NO_DATA" in netdb.h, but ENODATA would be more appropriate here
#endif

#if defined(OMNI_OS_WIN)

namespace omni {
    namespace net {
        /** @internal library helper */
        inline int wsa_init()
        {
            WSADATA sdata;
            int serr = ::WSAStartup(MAKEWORD(OMNI_WINSOCK_HIGH_FW, OMNI_WINSOCK_LOW_FW), &sdata);
            if (serr != 0) {
                // Could not get the winsock dll, fail since cannot create socket
                OMNI_DBGEV("a system error occurred in WSAStartUp: ", serr)
            }
            return serr;
        }

        /** @internal library helper */
        inline void wsa_close()
        {
            ::WSACleanup();
        }

        /** @internal library helper */
        class wsa_info
        {
            public:
                wsa_info() : m_err(-1)
                { this->open(); }
                
                explicit wsa_info(bool val) : m_err(-1)
                { OMNI_UNUSED(val); }

                ~wsa_info()
                { if (this->m_err == 0) { omni::net::wsa_close(); } }

                void close()
                { omni::net::wsa_close(); this->m_err = -1; }

                int error() const
                { return this->m_err; }

                bool open() { if (this->m_err != 0)
                { this->m_err = omni::net::wsa_init(); } return (this->m_err == 0); }

                operator bool() const
                { return this->m_err == 0; }

                void swap(wsa_info& other)
                { if (this != &other) { std::swap(this->m_err, other.m_err); } }
            private:
                int m_err;
        };
    }
}

#endif

#endif // OMNI_NET_DEF_HPP
