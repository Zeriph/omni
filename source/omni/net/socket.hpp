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
#if !defined(OMNI_SOCKET_HPP)
#define OMNI_SOCKET_HPP 1
#include <omni/types/net_t.hpp>
#include <omni/net/host_helper.hpp>

namespace omni {
    namespace net {
        /** The socket class is used to facilitate network communications */
        class socket
        {
            public:
                socket(omni::net::address_family family,
                       omni::net::socket_type type,
                       omni::net::protocol_type protocol);
                socket(omni::net::socket_type type, omni::net::protocol_type protocol);
                ~socket();
                
                omni::net::address_family address_family() const;
                omni::net::socket_error accept(omni::net::endpoint_descriptor& remote_ep);
                omni::net::socket_error bind();
                omni::net::socket_error bind(uint32_t ip, uint16_t port);
                omni::net::socket_error bind(const std::string& ip, uint16_t port);
                omni::net::socket_error bind(const std::wstring& ip, uint16_t port);
                omni::net::socket_error bind(const std::string& ip);
                omni::net::socket_error bind(const std::wstring& ip);
                uint32_t bound_endpoint() const;
                uint16_t bound_port() const;
                omni::net::socket_error close();
                omni::net::socket_error close(uint16_t timeout);
                omni::net::socket_error connect();
                omni::net::socket_error connect(uint32_t ip, uint16_t port);
                omni::net::socket_error connect(const std::string& ip, uint16_t port);
                omni::net::socket_error connect(const std::wstring& ip, uint16_t port);
                omni::net::socket_error disconnect(bool reuse);
                uint32_t endpoint() const;
                omni::net::socket_t native_handle() const;
                omni::net::socket_error open();
                omni::net::socket_error open(omni::net::socket_type type, omni::net::protocol_type protocol);
                omni::net::socket_error open(omni::net::address_family family, omni::net::socket_type type, omni::net::protocol_type protocol);
                uint16_t port() const;
                bool is_bound() const;
                bool is_connected() const;
                bool is_open() const;
                bool is_shutdown() const;
                bool is_listening() const;
                omni::net::socket_error listen(int32_t backlog);
                omni::net::socket_error last_error() const;
                omni::net::protocol_type protocol() const;
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t op_val);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val);
                omni::net::socket& set_address_family(omni::net::address_family family);
                omni::net::socket& set_protocol_type(omni::net::protocol_type protocol);
                omni::net::socket& set_socket_type(omni::net::socket_type type);
                omni::net::socket_error shutdown(omni::net::socket_shutdown how);
                omni::net::socket_type socket_type() const;
                omni::string_t to_string_t() const;
                std::string to_string() const;
                std::wstring to_wstring() const;

                operator std::string() const
                {
                    return this->to_string();
                }

                operator std::wstring() const
                {
                    return this->to_wstring();
                }

                OMNI_MEMBERS_FW(omni::net::socket) // disposing,name,type(),hash()

                OMNI_OSTREAM_FW(omni::net::socket)

                
                //omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, omni::unsafe_t out_val, size_t out_len) const;
                //omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, omni::unsafe_t out_val, size_t out_len) const;
                //omni::net::socket_error io_control(uint32_t op_code, omni::unsafe_t val, size_t val_len);
                //omni::net::socket_error io_control(uint32_t op_code, omni::unsafe_t val, size_t val_len, omni::unsafe_t out_val, size_t out_len);
                //omni::net::socket_error poll(uint32_t us, omni::net::select_mode mode);
                
                omni::net::socket_error receive(omni::unsafe_t buffer, uint32_t len, uint32_t& rcvd);
                omni::net::socket_error receive(omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd);
                omni::net::socket_error receive(omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, uint32_t& rcvd);

                omni::net::socket_error receive_from(omni::unsafe_t buffer, uint32_t len, const std::string& ip, uint32_t& rcvd);
                omni::net::socket_error receive_from(omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint32_t& rcvd);
                omni::net::socket_error receive_from(omni::unsafe_t buffer, uint32_t offset, uint32_t len, const std::string& ip, uint32_t& rcvd);
                omni::net::socket_error receive_from(omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint32_t& rcvd);
                
                omni::net::socket_error send(const omni::unsafe_t buffer, uint32_t len, uint32_t& sent);
                omni::net::socket_error send(const omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, uint32_t& sent);
                omni::net::socket_error send(const omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, uint32_t& sent);
                
                omni::net::socket_error send_to(const omni::unsafe_t buffer, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent);
                omni::net::socket_error send_to(const omni::unsafe_t buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent);
                omni::net::socket_error send_to(const omni::unsafe_t buffer, uint32_t offset, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent);
                omni::net::socket_error send_to(const omni::unsafe_t buffer, uint32_t offset, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent);
                
                
            private:
                socket(); // = delete
                socket(const omni::net::socket &cp); // = delete
                omni::net::socket& operator= (const omni::net::socket &other); // = delete
                
                omni::net::socket_t m_socket;
                omni::net::sockaddr_t m_addr;
                omni::net::address_family m_family;
                omni::net::protocol_type m_proto;
                omni::net::socket_type m_type;
                omni::net::socket_error m_last_err;
                uint32_t m_ep4;
                uint16_t m_port;
                uint32_t m_bep4;
                uint16_t m_bport;
                bool m_connected;
                bool m_bound;
                bool m_open;
                bool m_shut;
                bool m_listen;
                #if defined(OMNI_SAFE_SOCKET)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                omni::net::socket_error _close(uint16_t timeout, bool shutdown);
                omni::net::socket_error _parse_error(int err);
        };
    }
}

#endif // OMNI_SOCKET_HPP
