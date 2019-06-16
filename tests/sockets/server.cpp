#include <omnilib>

#define LISTEN_PORT 12345

int main(int argc, char* argv[])
{
    omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
    if (s.bind(LISTEN_PORT) != omni::net::socket_error::SUCCESS) {
        std::cout << "Error binding on socket: " << s.last_error() << std::endl;
    } else {
        std::cout << "Bound to port " << s.bound_port() << std::endl;
        if (s.listen() != omni::net::socket_error::SUCCESS) {
            std::cout << "Error listening on socket: " << s.last_error() << std::endl;
        } else {
            std::cout << "Ready to accept connections" << std::endl;
            omni::net::endpoint_descriptor remote_ep;
            if (s.accept(remote_ep) != omni::net::socket_error::SUCCESS) {
                std::cout << "Error accepting on socket: " << s.last_error() << std::endl;
            } else {
                uint32_t xfr = 0;
                char buff[1024] = {0};
                std::cout << "Client connected: " << remote_ep << std::endl;
                if (remote_ep.receive(buff, 1024, xfr) != omni::net::socket_error::SUCCESS) {
                    std::cout << "Error receiving on socket: " << s.last_error() << std::endl;
                } else {
                    std::cout << "Received " << xfr << " bytes: [" << buff << "]" << std::endl;
                    std::cout << "Sending: WELCOME!\\r\\n" << std::endl;
                    if (remote_ep.send("WELCOME!\r\n", 11, xfr) != omni::net::socket_error::SUCCESS) {
                        std::cout << "Error sending on socket: " << s.last_error() << std::endl;    
                    } else {
                        std::cout << "Sent " << xfr << " bytes to client" << std::endl;
                    }
                }
            }
        }
    }
    s.close();
    return 0;
}