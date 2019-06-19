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
#if !defined(OMNI_SOCKET_EP_HPP)
#define OMNI_SOCKET_EP_HPP 1
#include <omni/types/net_t.hpp>
#if defined(OMNI_SAFE_SOCKET_EP)
    #include <omni/sync/basic_lock.hpp>
#endif

namespace omni {
    namespace net {
        /** The endpoint_descriptor class is used to facilitate network communications from a remote endpoint accepted by a server */
        class endpoint_descriptor
        {
            public:
                endpoint_descriptor();
                endpoint_descriptor(const endpoint_descriptor& cp);
                ~endpoint_descriptor();
                
                omni::net::socket_error connect(const omni::net::socket_t& serv_sock);
                omni::net::socket_error close();
                omni::net::socket_error close(uint16_t timeout);
                uint32_t endpoint() const;
                omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val);
                omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t& op_val);
                omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val);
                omni::net::socket_t native_handle() const;
                omni::net::socket_error ioc(uint32_t op_code, omni::net::xfr_t* val, int32_t& result);
                bool is_connected() const;
                bool is_shutdown() const;
                omni::net::socket_error last_error() const;
                uint16_t port() const;
                omni::net::socket_error receive(char* buffer, uint32_t len, uint32_t& rcvd);
                omni::net::socket_error receive(int8_t* buffer, uint32_t len, uint32_t& rcvd);
                omni::net::socket_error receive(uint8_t* buffer, uint32_t len, uint32_t& rcvd);
                omni::net::socket_error receive(char* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd);
                omni::net::socket_error receive(int8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd);
                omni::net::socket_error receive(uint8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd);
                omni::net::socket_error send(const char* buffer, uint32_t len, uint32_t& sent);
                omni::net::socket_error send(const int8_t* buffer, uint32_t len, uint32_t& sent);
                omni::net::socket_error send(const uint8_t* buffer, uint32_t len, uint32_t& sent);
                omni::net::socket_error send(const char* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent);
                omni::net::socket_error send(const int8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent);
                omni::net::socket_error send(const uint8_t* buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t op_val);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val);
                omni::net::socket_error shutdown(omni::net::socket_shutdown how);
                void swap(omni::net::endpoint_descriptor& other);
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;

                omni::net::endpoint_descriptor& operator=(omni::net::endpoint_descriptor &other);
                bool operator==(const omni::net::endpoint_descriptor &other) const;
                bool operator==(const omni::net::socket_t &sock) const;
                bool operator==(uint32_t ep) const;

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::net::endpoint_descriptor) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::endpoint_descriptor)

            private:
                omni::net::socket_t m_socket;
                omni::net::sockaddr_in_t m_addr;
                omni::net::socket_error m_last_err;
                bool m_connected;
                bool m_shut;
                #if defined(OMNI_SAFE_SOCKET_EP)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                omni::net::socket_error _close(uint16_t timeout, bool shutdown);
        };
    }
}

namespace std {
    inline void swap(omni::net::endpoint_descriptor& o1, omni::net::endpoint_descriptor& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_SOCKET_EP_HPP
