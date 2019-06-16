#include <omnilib>

#define SERVER_PORT 12345

static void client_thread()
{
    omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
    if (s.connect("127.0.0.1", SERVER_PORT) != omni::net::socket_error::SUCCESS) {
        std::cout << "Could not connect: " << s.last_error() << std::endl;
    } else {
        uint32_t xfr = 0;
        std::cout << "Connected to " << s << std::endl;
        std::cout << "Sending: HELLO!\\r\\n" << std::endl;
        if (s.send("HELLO!\r\n", 9, xfr) != omni::net::socket_error::SUCCESS) {
            std::cout << "Could not send data: " << s.last_error() << std::endl;
        } else {
            char buff[1024] = {0};
            std::cout << "Sent " << xfr << " bytes to server" << std::endl;
            if (s.receive(buff, 1024, xfr) != omni::net::socket_error::SUCCESS) {
                std::cout << "Could not receive data: " << s.last_error() << std::endl;
            } else {
                std::cout << "Received " << xfr << " bytes from server: [" << buff << "]" << std::endl;
            }
        }
    }
    s.close();
}

static void server_thread()
{
    omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::IP);
    if (s.bind(SERVER_PORT) != omni::net::socket_error::SUCCESS) {
        std::cout << "Error binding on socket: " << s.last_error() << std::endl;
    } else {
        std::cout << "Bound to port " << SERVER_PORT << std::endl;
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
}

int main(int argc, char* argv[])
{
    omni::sync::basic_thread server(&server_thread);
    omni::sync::basic_thread client(&client_thread, omni::sync::thread_start_type::USER);
    omni::sync::sleep(100); // wait a bit for the server to start listening
    client.start();
    server.join();
    client.join();
    return 0;
}
