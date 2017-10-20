/*
 * Copyright (c) 2017, Zeriph Enterprises
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * - Neither the name of Zeriph, Zeriph Enterprises, LLC, nor the names
 *   of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
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
#include <omni/delegate/0.hpp>
#include <omni/delegate/1.hpp>
#include <omni/exception.hpp>
#include <string>
#include <csignal>

namespace omni {
    namespace net {
        // DEV_NOTE: While we could make socket a stream object, we would be overloading just about everything
        // because of how we handle sockets vs. normal streams
        /** The socket class is used to facilitate network communications */
        class socket
        {
            socket(const omni::net::socket &cp);
            
            public:
                socket();
                socket(omni::net::address_family::enum_t family,
                       omni::net::socket_type::enum_t type, 
                       omni::net::protocol_type::enum_t protocol);
                virtual ~socket();
                
                bool blocking;
                bool dontFragment;
                bool enableBroadcast;
                bool exclusiveAddressUse;
                omni::net::linger_option linger_state;
                bool multicastLoopback;
                bool nodelay;
                int receiveBufferSize;
                int receiveTimeout;
                int sendBufferSize;
                int sendTimeout;
                short ttl;
                bool useOnlyOverlappedIO;
                
                omni::net::address_family::enum_t address_family() const;
                int available() const;
                omni::net::socket& accept();
                omni::net::socket& bind(std::string ip);
                bool connected() const;
                bool close();
                bool close(int timeout);
                bool connect(std::string host, int port);
                bool disconnect(bool reuse);
                unsigned int handle() const;
                bool is_bound() const;
                bool is_shut() const;
                omni::net::socket& listen(int backlog);
                bool poll(int microSeconds, omni::net::select_mode::enum_t mode);
                omni::net::protocol_type::enum_t protocol() const;
                omni::net::socket& set_socket_option(omni::net::socket_option_level::enum_t optionLevel, omni::net::socket_option_name::enum_t optionName, int optionValue);
                bool shutdown(omni::net::socket_shutdown::enum_t how);
                omni::net::socket_type::enum_t socket_type() const;;
                const std::string to_string() const;
                
                
                omni::net::socket *duplicateAndClose();
                char *getSocketOption(omni::net::socket_option_level::enum_t optionLevel, omni::net::socket_option_name::enum_t optionName, int optionLength) const;
                int iocontrol(int ioControlCode, char *optionInValue, char *optionOutValue);
                const char *localEndPoint() const;
                const char *remoteEndPoint() const;
                
                int receive(char *buffer, int size);
                int receive(char *buffer, int size, omni::net::socket_flags::enum_t socketFlags);
                int receive(char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags);
                int receive(char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags, omni::net::socket_error::enum_t &errorCode);
                int receiveFrom(char *buffer, int size, omni::net::socket_flags::enum_t socketFlags, const char *remoteIP);
                int receiveFrom(char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags, const char *remoteIP);
                int send(const char *buffer, int size, omni::net::socket_flags::enum_t socketFlags);
                int send(const char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags);
                int send(const char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags, omni::net::socket_error::enum_t &errorCode);
                int sendto(const char *buffer, int size, omni::net::socket_flags::enum_t socketFlags, const char *remoteIP);
                int sendto(const char *buffer, int offset, int size, omni::net::socket_flags::enum_t socketFlags, const char *remoteIP);
                
                
                // Events
                /** Occurs when data is received on the socket */
                omni::action received;
                
                // Operators
                omni::net::socket& operator= (const omni::net::socket &other);
                omni::net::socket& operator<< (const char *data); // writes data to socket
                omni::net::socket& operator>> (const char *read); // reads data from socket
                
                /* examples for operator overload:
                omni::net::socket s("192.168.1.1", 80);
                ...
                s.connect();
                if (s.connected()) {
                    if (isServer) {
                        const char *data;
                        s >> data; // wait until data read from socket, then put to 'data' (don't forget about mem leeks, etc)
                        printf("data rcvd: %s\n", data);
                        s << "hiya! how's it going?"; // showing operator<<(const char*)
                    } else { // client
                        // write to socket
                        std::string data = "hello there";
                        const char *rcvd;
                        s << data; // showing operator<<(std::string)
                        s >> rcvd;
                        printf("data rcvd: %s\n", rcvd);
                    }
                }
                */
                
                /*
                static std::string getBroadcastFromIpAndSubnet(const std::string &ip, const std::string &subnet);
                static OMNI_SEQ_T<networkinterface> getInterfaces();
                static unsigned int ipToNum(const std::string &ip);
                static bool isValidIp(const std::string &ip, bool includeBroadcast = false);
                static bool isValidPort(int port);
                static std::string numToIp(unsigned int num);
                static bool osSupportsIPv4();
                static bool osSupportsIPv6();
                static omni::net::pingreply ping(const std::string &ip);
                */
                
            private:
                // Methods
                void p_Initialize(omni::net::address_family::enum_t addressFamily, omni::net::socket_type::enum_t socketType, omni::net::protocol_type::enum_t protocolType);
                bool p_CloseSocket(int timeout, bool shutdown);
                // Members
                omni::net::address_family::enum_t m_AddressFamily;
                int m_Available;
                bool m_IsConnected;
                bool m_IsBound;
                bool m_IsShutdown;
                int m_Handle;
                const char *m_LocalEndPoint;
                omni::net::protocol_type::enum_t m_ProtocolType;
                const char *m_RemoteEndPoint;
                omni::net::socket_type::enum_t m_SocketType;
        };
    }
}

#endif // OMNI_SOCKET_HPP
