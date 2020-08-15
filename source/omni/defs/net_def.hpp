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
    #if !defined(OMNI_WINSOCK_HIGH)
        #define OMNI_WINSOCK_HIGH 2
    #endif
    #if !defined(OMNI_WINSOCK_LOW)
        #define OMNI_WINSOCK_LOW 2
    #endif
    #define OMNI_SOCK_RECEIVE_FW SD_RECEIVE
    #define OMNI_SOCK_SEND_FW SD_SEND
    #define OMNI_SOCK_BOTH_FW SD_BOTH
    #define OMNI_MSG_EOR 0
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
    #define OMNI_MSG_EOR MSG_EOR
#endif

#if defined(OMNI_OS_WIN)

namespace omni {
    namespace net {
        /** @internal library helper */
        inline int wsa_init()
        {
            WSADATA sdata;
            int err = ::WSAStartup(MAKEWORD(OMNI_WINSOCK_HIGH, OMNI_WINSOCK_LOW), &sdata);
            if (err != 0) {
                // Could not get the winsock dll, fail since cannot create socket
                OMNI_DBGEV("a system error occurred in WSAStartUp: ", err)
            }
            return err;
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
