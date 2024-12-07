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
#if defined(OMNI_OS_WIN)
    #include <windows.h>
#else
    #include <dirent.h>
    #include <unistd.h>
    #include <sys/time.h>
    #include <fcntl.h>
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

#define OMNI_NET_SOCKET4_HXX_FW 1
#include "omni/xx/net/socket4.hxx"
#undef OMNI_NET_SOCKET4_HXX_FW

#define OMNI_NET_SOCKET6_HXX_FW 1
#include "omni/xx/net/socket6.hxx"
#undef OMNI_NET_SOCKET6_HXX_FW

#if defined(OMNI_ALLOW_UNIX_SOCKET)
    #define OMNI_NET_UNIX_SOCKET_HXX_FW 1
    #include "omni/xx/net/unix_socket.hxx"
    #undef OMNI_NET_UNIX_SOCKET_HXX_FW
#endif
