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
#include <omni/net/endpoint_descriptor.hpp>
#if defined(OMNI_SAFE_SOCKET)
    #include <omni/sync/basic_lock.hpp>
#endif

namespace omni {
    namespace net {
        /** The socket class is used to facilitate network communications */
        class socket
        {
            public:
                socket(omni::net::socket_type type, omni::net::protocol_type protocol);
                socket(omni::net::address_family family,
                       omni::net::socket_type type,
                       omni::net::protocol_type protocol);
                socket(omni::net::address_family family,
                       omni::net::socket_type type,
                       omni::net::protocol_type protocol,
                       omni::net::socket_create_options create_ops);
                ~socket();
                
                omni::net::address_family address_family() const;
                omni::net::socket_error accept(omni::net::endpoint_descriptor& remote_ep);
                omni::net::socket_error bind();
                omni::net::socket_error bind(uint16_t port);
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
                omni::net::socket_error connect_host(const std::string& host, uint16_t port);
                omni::net::socket_error connect_host(const std::wstring& host, uint16_t port);
                omni::net::socket_error disconnect(bool reuse);
                uint32_t endpoint() const;
                omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t& op_val);
                omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t& op_val);
                omni::net::socket_error get_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t& op_val);
                omni::net::socket_t native_handle() const;
                omni::net::socket_error open();
                omni::net::socket_error open(omni::net::socket_type type, omni::net::protocol_type protocol);
                omni::net::socket_error open(omni::net::address_family family, omni::net::socket_type type, omni::net::protocol_type protocol);
                omni::net::socket_error ioc(uint32_t op_code, omni::net::xfr_t* val);
                bool is_bound() const;
                bool is_connected() const;
                bool is_open() const;
                bool is_shutdown() const;
                bool is_listening() const;
                omni::net::socket_error listen();
                omni::net::socket_error listen(int32_t backlog);
                omni::net::socket_error last_error() const;
                uint16_t port() const;
                omni::net::protocol_type protocol() const;
                template < typename T >
                omni::net::socket_error receive(std::vector<T>& buffer, uint32_t& received)
                {
                    // if CXX buffer.data
                    return this->_receive(&buffer[0], (buffer.size() * sizeof(T)), omni::net::socket_flags::NONE, received);
                }
                template < typename T >
                omni::net::socket_error receive(std::vector<T>& buffer, omni::net::socket_flags flags, uint32_t& received)
                {
                    // if CXX buffer.data
                    return this->_receive(&buffer[0], (buffer.size() * sizeof(T)), flags, received);
                }
                template < std::size_t SZ >
                omni::net::socket_error receive(char (&buffer)[SZ], uint32_t& received)
                {
                    return this->_receive(buffer, SZ, omni::net::socket_flags::NONE, received);
                }
                template < std::size_t SZ >
                omni::net::socket_error receive(char (&buffer)[SZ], omni::net::socket_flags flags, uint32_t& received)
                {
                    return this->_receive(buffer, SZ, flags, received);
                }
                omni::net::socket_error unsafe_receive(char* buffer, uint32_t buffer_size, uint32_t& received)
                {
                    return this->_receive(buffer, buffer_size, omni::net::socket_flags::NONE, received);
                }
                omni::net::socket_error unsafe_receive(char* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& received)
                {
                    return this->_receive(buffer, buffer_size, flags, received);
                }
                template < typename T >
                omni::net::socket_error receive_from(std::vector<T>& buffer, uint32_t& received)
                {
                    uint16_t fport = 0;
                    std::string fip;
                    return this->_receive_from(&buffer[0], (buffer.size() * sizeof(T)), omni::net::socket_flags::NONE, fip, fport, received); 
                }
                template < typename T >
                omni::net::socket_error receive_from(std::vector<T>& buffer, omni::net::socket_flags flags, uint32_t& received)
                {
                    uint16_t fport = 0;
                    std::string fip;
                    return this->_receive_from(&buffer[0], (buffer.size() * sizeof(T)), flags, fip, fport, received); 
                }
                template < typename T >
                omni::net::socket_error receive_from(std::vector<T>& buffer, std::string& from_ip, uint16_t& from_port, uint32_t& received)
                {
                    return this->_receive_from(&buffer[0], (buffer.size() * sizeof(T)), omni::net::socket_flags::NONE, from_ip, from_port, received);
                }
                template < typename T >
                omni::net::socket_error receive_from(std::vector<T>& buffer, omni::net::socket_flags flags, std::string& from_ip, uint16_t& from_port, uint32_t& received)
                {
                    return this->_receive_from(&buffer[0], (buffer.size() * sizeof(T)), flags, from_ip, from_port, received);
                }
                template < std::size_t SZ >
                omni::net::socket_error receive_from(char (&buffer)[SZ], uint32_t& received)
                {
                    uint16_t fport = 0;
                    std::string fip;
                    return this->_receive_from(buffer, SZ, omni::net::socket_flags::NONE, fip, fport, received); 
                }
                template < std::size_t SZ >
                omni::net::socket_error receive_from(char (&buffer)[SZ], omni::net::socket_flags flags, uint32_t& received)
                {
                    uint16_t fport = 0;
                    std::string fip;
                    return this->_receive_from(buffer, SZ, flags, fip, fport, received); 
                }
                template < std::size_t SZ >
                omni::net::socket_error receive_from(char (&buffer)[SZ], std::string& from_ip, uint16_t& from_port, uint32_t& received)
                {
                    return this->_receive_from(buffer, SZ, omni::net::socket_flags::NONE, from_ip, from_port, received);
                }
                template < std::size_t SZ >
                omni::net::socket_error receive_from(char (&buffer)[SZ], omni::net::socket_flags flags, std::string& from_ip, uint16_t& from_port, uint32_t& received)
                {
                    return this->_receive_from(buffer, SZ, flags, from_ip, from_port, received);
                }
                omni::net::socket_error unsafe_receive_from(char* buffer, uint32_t buffer_size, uint32_t& received)
                {
                    uint16_t fport = 0;
                    std::string fip;
                    return this->_receive_from(buffer, buffer_size, omni::net::socket_flags::NONE, fip, fport, received); 
                }
                omni::net::socket_error unsafe_receive_from(char* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& received)
                {
                    uint16_t fport = 0;
                    std::string fip;
                    return this->_receive_from(buffer, buffer_size, flags, fip, fport, received); 
                }
                omni::net::socket_error unsafe_receive_from(char* buffer, uint32_t buffer_size, std::string& from_ip, uint16_t& from_port, uint32_t& received)
                {
                    return this->_receive_from(buffer, buffer_size, omni::net::socket_flags::NONE, from_ip, from_port, received);
                }
                omni::net::socket_error unsafe_receive_from(char* buffer, uint32_t buffer_size, omni::net::socket_flags flags, std::string& from_ip, uint16_t& from_port, uint32_t& received)
                {
                    return this->_receive_from(buffer, buffer_size, flags, from_ip, from_port, received);
                }
                template < typename T >
                omni::net::socket_error send(const std::vector<T>& buffer, uint32_t& sent)
                {
                    return this->_send(&buffer[0], (buffer.size() * sizeof(T)), omni::net::socket_flags::NONE, sent);
                }
                template < typename T >
                omni::net::socket_error send(const std::vector<T>& buffer, omni::net::socket_flags flags, uint32_t& sent)
                {
                    return this->_send(&buffer[0], (buffer.size() * sizeof(T)), flags, sent);
                }
                template < std::size_t SZ >
                omni::net::socket_error send(const char (&buffer)[SZ], uint32_t& sent)
                {
                    return this->_send(buffer, SZ, omni::net::socket_flags::NONE, sent);
                }
                template < std::size_t SZ >
                omni::net::socket_error send(const char (&buffer)[SZ], omni::net::socket_flags flags, uint32_t& sent)
                {
                    return this->_send(buffer, SZ, flags, sent);
                }
                omni::net::socket_error send(const std::string& buffer, uint32_t& sent)
                {
                    return this->unsafe_send(buffer.data(), buffer.size(), sent);
                }
                omni::net::socket_error unsafe_send(const char* buffer, uint32_t buffer_size, uint32_t& sent)
                {
                    return this->_send(buffer, buffer_size, omni::net::socket_flags::NONE, sent);
                }
                omni::net::socket_error unsafe_send(const char* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& sent)
                {
                    return this->_send(buffer, buffer_size, flags, sent);
                }
                template < typename T >
                omni::net::socket_error send_to(const std::vector<T>& buffer, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent)
                {
                    return this->_send_to(buffer, len, omni::net::socket_flags::NONE, ip, port, sent);
                }
                template < typename T >
                omni::net::socket_error send_to(const std::vector<T>& buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent)
                {
                    return this->_send_to(buffer, len, flags, ip, port, sent);
                }
                template < std::size_t SZ >
                omni::net::socket_error send_to(const char (&buffer)[SZ], const std::string& ip, uint16_t port, uint32_t& sent)
                {
                    return this->_send_to(buffer, SZ, omni::net::socket_flags::NONE, ip, port, sent);
                }
                template < std::size_t SZ >
                omni::net::socket_error send_to(const char (&buffer)[SZ], omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent)
                {
                    return this->_send_to(buffer, SZ, flags, ip, port, sent);
                }
                omni::net::socket_error unsafe_send_to(const char* buffer, uint32_t len, const std::string& ip, uint16_t port, uint32_t& sent)
                {
                    return this->_send_to(buffer, len, omni::net::socket_flags::NONE, ip, port, sent);
                }
                omni::net::socket_error unsafe_send_to(const char* buffer, uint32_t len, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent)
                {
                    return this->_send_to(buffer, len, flags, ip, port, sent);
                }
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, int32_t op_name, int32_t op_val);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, omni::net::socket_option op_name, int32_t op_val);
                omni::net::socket_error set_socket_option(omni::net::socket_option_level op_level, omni::net::tcp_option op_name, int32_t op_val);
                omni::net::socket& set_address_family(omni::net::address_family family);
                omni::net::socket& set_protocol_type(omni::net::protocol_type protocol);
                omni::net::socket& set_socket_type(omni::net::socket_type type);
                omni::net::socket_error set_blocking_mode(omni::net::blocking_mode mode);
                omni::net::socket_error shutdown(omni::net::socket_shutdown how);
                omni::net::socket_type socket_type() const;
                void swap(omni::net::socket& other);
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

            private:
                omni::net::socket_t m_socket;
                omni::net::sockaddr_in_t m_addr;
                omni::net::address_family m_family;
                omni::net::protocol_type m_proto;
                omni::net::socket_type m_type;
                omni::net::socket_error m_last_err;
                uint32_t m_ep4;
                uint16_t m_port;
                uint16_t m_conops;
                
                #if defined(OMNI_OS_WIN)
                    omni::net::wsa_info m_wsa;
                #endif
                #if defined(OMNI_SAFE_SOCKET)
                    mutable omni::sync::basic_lock m_mtx;
                #endif

                socket(); // = delete
                socket(const omni::net::socket& cp); // = delete
                omni::net::socket& operator= (const omni::net::socket& other); // = delete
                
                omni::net::socket_error _close(uint16_t timeout, bool shutdown);
                omni::net::socket_error _receive(void* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& received);
                omni::net::socket_error _receive_from(void* buffer, uint32_t buffer_size, omni::net::socket_flags flags, std::string& from_ip, uint16_t& from_port, uint32_t& received);
                omni::net::socket_error _send(const void* buffer, uint32_t buffer_size, omni::net::socket_flags flags, uint32_t& sent);
                omni::net::socket_error _send_to(const void* buffer, uint32_t buffer_size, omni::net::socket_flags flags, const std::string& ip, uint16_t port, uint32_t& sent);
        };

        // TODO: future -> for systems that support dual-stack sockets via ip6
        //class socket6 {  enum_t mode = DUAL || IP6; };

        // TODO: future -> for systems that do NOT support dual-stack sockets
        //class dual_socket { omni::net::socket ip4; omni::net::socket6 ip6;  }

        // TODO: future -> AF_UNIX address family is for IPC
        // so NOT for omni::net::socket .. it would be for omni::ipc::socket
    }
}

namespace std {
    inline void swap(omni::net::socket& o1, omni::net::socket& o2)
    {
        o1.swap(o2);
    }
}

#endif // OMNI_SOCKET_HPP
