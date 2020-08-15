#if defined(OMNI_UTUA) || defined(OMNI_UT_SOCKET)

#define UT_NAME socket
#define UT_ROOT_NS net
#include <utdefs/unit_test.hpp>
#include <vector>

#define BUFFSZ 65535
#define SERVER_PORT 12345

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(host_test, "tests host/ip functionality");
            M_LIST_ADD(client_server_test, "tests the client/server functionality");
            M_LIST_ADD(www_test, "tests getting index.html from zeriph.com with stack_buffer/vector");
            M_LIST_ADD(unsafe_www_test, "tests getting index.html from zeriph.com with unsafe_X funcs");
        }
        
        UT_CLASS_DTOR() {}
        
        void info_test() { UT_INFO_TEST(); }
        
        void base_test()
        {
            omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
            std::cout << "socket is connected: " << OMNI_BOOL2STR(s.is_connected()) << std::endl;
        }

        void host_test()
        {
            omni::seq::std_string_t ips;
            std::string host;
            omni::net::socket_error err = omni::net::util::get_ip("zeriph.com", ips);
            if (err == omni::net::socket_error::SUCCESS) {
                std::cout << "IP's for zeriph.com:" << std::endl;
                for (omni::seq::std_string_t::iterator it = ips.begin(); it != ips.end(); ++it) {
                    std::cout << *it << std::endl;
                }
            } else {
                std::cout << "Error getting IP's: " << err << std::endl;
            }

            err = omni::net::util::get_host("68.66.224.12", 80, host);
            if (err == omni::net::socket_error::SUCCESS) {
                std::cout << "Got host: " << host << std::endl;
            } else {
                std::cout << "Error getting host: " << err << std::endl;
            }
        }

        void unsafe_www_test()
        {
            uint32_t xfr = 0;
            const std::string req = "GET / HTTP/1.0\r\nHost: zeriph.com\r\n\r\n";
            omni::net::socket sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
            if (sock.connect_host("zeriph.com", 80) == omni::net::socket_error::SUCCESS) {
                std::cout << "Connected to " << sock << std::endl;
                if (sock.unsafe_send(req.c_str(), req.size(), xfr) == omni::net::socket_error::SUCCESS) {
                    std::cout << "Sent " << xfr << " bytes" << std::endl;

                    char* data = new char[BUFFSZ];
                    while (sock.unsafe_receive(data, BUFFSZ, xfr) == omni::net::socket_error::SUCCESS) {
                        if (xfr > 0) { std::cout << data; }
                        std::memset(data, 0, BUFFSZ);
                    }
                    delete[] data;
                }
            }
            if (sock.last_error() != omni::net::socket_error::SUCCESS) {
                std::cout << std::endl << "Last socket error: " << sock.last_error() << std::endl;
            }

            // Strictly speaking this is not necessary here since `sock` is a local
            // object, so when it goes out of scope it will call close on destruction.
            sock.close();
        }

        void www_test()
        {
            uint32_t xfr = 0;
            omni::stack_buffer<char, 1024> req = "GET / HTTP/1.0\r\nHost: zeriph.com\r\n\r\n";
            omni::net::socket sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
            if (sock.connect_host("zeriph.com", 80) == omni::net::socket_error::SUCCESS) {
                std::cout << "Connected to " << sock << std::endl;
                if (sock.send(req, xfr) == omni::net::socket_error::SUCCESS) {
                    std::cout << "Sent " << xfr << " bytes" << std::endl;

                    
                    std::vector<char> data(BUFFSZ);
                    while (sock.receive(data, xfr) == omni::net::socket_error::SUCCESS) {
                        if (xfr > 0) { std::cout << &data[0]; }
                        std::memset(&data[0], 0, BUFFSZ);
                    }
                }
            }
            if (sock.last_error() != omni::net::socket_error::SUCCESS) {
                std::cout << std::endl << "Last socket error: " << sock.last_error() << std::endl;
            }

            // Strictly speaking this is not necessary here since `sock` is a local
            // object, so when it goes out of scope it will call close on destruction.
            sock.close();
        }

        void client_server_test()
        {
            omni::sync::basic_thread server(&server_thread);
            omni::sync::basic_thread client(&client_thread, omni::sync::thread_start_type::USER);
            omni::sync::sleep(100); // wait a bit for the server to start listening
            client.start();
            server.join();
            client.join();
        }

    private:
        static void client_thread()
        {
            uint32_t xfr = 0;
            omni::stack_buffer<char, 1024> buff;
            omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
            if (s.connect("127.0.0.1", SERVER_PORT) == omni::net::socket_error::SUCCESS) {
                std::cout << "Connected to " << s << std::endl;
                std::cout << "Sending: HELLO!\\r\\n" << std::endl;
                if (s.unsafe_send("HELLO!\r\n", 9, xfr) == omni::net::socket_error::SUCCESS) {
                    std::cout << "Sent " << xfr << " bytes to server" << std::endl;
                    if (s.receive(buff, xfr) == omni::net::socket_error::SUCCESS) {
                        std::cout << "Received " << xfr << " bytes from server: [" << buff << "]" << std::endl;
                    } else {
                        std::cout << "Could not receive data: " << s.last_error() << std::endl;
                    }
                } else {
                    std::cout << "Could not send data: " << s.last_error() << std::endl;
                }
            } else {
                std::cout << "Could not connect: " << s.last_error() << std::endl;
            }
            s.close();
        }

        static void server_thread()
        {
            uint32_t xfr = 0;
            omni::stack_buffer<char, 1024> buff;
            omni::net::endpoint_descriptor remote_ep;
            omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
            if (s.bind(SERVER_PORT) == omni::net::socket_error::SUCCESS) {
                std::cout << "Bound to port " << SERVER_PORT << std::endl;
                if (s.listen() == omni::net::socket_error::SUCCESS) {
                    std::cout << "Ready to accept connections" << std::endl;
                    if (s.accept(remote_ep) == omni::net::socket_error::SUCCESS) {
                        std::cout << "Client connected: " << remote_ep << std::endl;
                        if (remote_ep.receive(buff, xfr) == omni::net::socket_error::SUCCESS) {
                            std::cout << "Received " << xfr << " bytes: [" << buff << "]" << std::endl;
                            std::cout << "Sending: WELCOME!\\r\\n" << std::endl;
                            if (remote_ep.unsafe_send("WELCOME!\r\n", 11, xfr) == omni::net::socket_error::SUCCESS) {
                                std::cout << "Sent " << xfr << " bytes to client" << std::endl;
                            } else {
                                std::cout << "Error sending on socket: " << s.last_error() << std::endl;    
                            }
                        } else {
                            std::cout << "Error receiving on socket: " << s.last_error() << std::endl;
                        }
                    } else {
                        std::cout << "Error accepting on socket: " << s.last_error() << std::endl;
                    }
                } else {
                    std::cout << "Error listening on socket: " << s.last_error() << std::endl;
                }
            } else {
                std::cout << "Error binding on socket: " << s.last_error() << std::endl;
            }
            s.close();
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_SOCKET
