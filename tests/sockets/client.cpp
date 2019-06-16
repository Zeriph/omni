#include <omnilib>

#define SERVER_PORT 12345

int main(int argc, char* argv[])
{
    std::string ip = "127.0.0.1";
    if (argc > 1 && omni::net::util::is_valid_ip4(argv[1])) {
        ip = argv[1];
    }
    omni::net::socket s(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
    if (s.connect(ip, SERVER_PORT) != omni::net::socket_error::SUCCESS) {
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
    return 0;
}