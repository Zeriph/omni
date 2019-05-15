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
#include <sys/types.h>
#include <sys/stat.h>
#include <csignal>
#if defined(OMNI_OS_WIN)
    #include <io.h>
	#include <winsock2.h>
	#include <winsock.h>
    #if !defined(OMNI_WIN_NO_PRAGMA_WS2_32_LIB)
        #pragma comment(lib, "ws2_32.lib")
    #endif
#else
    #include <sys/socket.h>
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

#define OMNI_SOCKADDR_IN_T struct sockaddr_in
#define OMNI_SOCKADDR_IN6_T struct sockaddr_in6
#define OMNI_SOCKADDR_UN_T struct sockaddr_un
#define OMNI_SOCKADDR_T struct sockaddr

#if defined(OMNI_OS_WIN)
    #define OMNI_MSG_EOR 0
#else
    #define OMNI_MSG_EOR MSG_EOR
#endif

#if defined(OMNI_WIN_API)
    #define OMNI_SOCKET_OPEN_FW(af, t, p) ::WSASocket(af, static_cast<int>(t), static_cast<int>(p), NULL, 0, WSA_FLAG_OVERLAPPED)
    #define OMNI_SOCKET_ACCEPT_FW(s, a, l) ::WSAAccept(s, a, l, NULL, NULL)
    #define OMNI_SOCKET_CONNECT_FW(s, sa, l) ::WSAConnect(s, sa, l, NULL, NULL, NULL, NULL)
    #define OMNI_SOCKET_CLOSE_FW(s) ::closesocket(s)
    // recv
    // win
    // int WSAAPI WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
    // *nix
#else
    #define OMNI_SOCKET_OPEN_FW(af, t, p) ::socket(af, static_cast<int>(t), static_cast<int>(p))
    #define OMNI_SOCKET_ACCEPT_FW(s, a, l) ::accept(s, a, l)
    #define OMNI_SOCKET_CONNECT_FW(s, sa, l) ::connect(s, sa, l)
    #define OMNI_SOCKET_CLOSE_FW(s) ::close(s)
    //     int recv(SOCKET   s, char *buf,    int len, int flags);
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    
#endif
    // send/recv type
    // win
    // char*
    // typedef char xfr_t;
    // *nix
    // void*
    // typedef void xfr_t;
    // omni::unsafe_t == void*

    



    // recvfrom
    // win
    // int recvfrom(SOCKET s, char *buf, int len, int flags, sockaddr *from, int *fromlen);
    // int WSAAPI WSARecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, sockaddr *lpFrom, LPINT lpFromlen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
    // *nix
    // ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

    // send
    // win
    // int WSAAPI send(SOCKET s, const char *buf, int len, int flags);
    // int WSAAPI WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
    // *nix
    // ssize_t send(int socket, const void *buffer, size_t length, int flags);

    // sendto
    // win
    // int sendto(SOCKET s, const char *buf, int len, int flags, const sockaddr *to, int tolen);
    // int WSAAPI WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const sockaddr *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
    // *nix
    // ssize_t sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);

#if defined(OMNI_OS_WIN)
    #define OMNI_SOCKET_T SOCKET
    #define OMNI_SOCKLEN_FW int
    #define OMNI_SOCKET_XFR_T char
    #define OMNI_INVALID_SOCKET INVALID_SOCKET
    #define OMNI_SOCK_SYSERR_FW 0
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
#else
    #define OMNI_SOCKET_T int
    #define OMNI_SOCKLEN_FW socklen_t
    #define OMNI_SOCKET_XFR_T void
    #define OMNI_INVALID_SOCKET -1
    #define OMNI_SOCK_SYSERR_FW -1
    #define OMNI_SOCKET_ERR_FW errno
    #define OMNI_SOCK_RECEIVE_FW SHUT_RD
    #define OMNI_SOCK_SEND_FW SHUT_WR
    #define OMNI_SOCK_BOTH_FW SHUT_RDWR
#endif

#endif // OMNI_NET_DEF_HPP
