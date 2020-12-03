#include <omnilib>

#define BUFFSZ 65535

int main(int argc, char* argv[])
{
    omni::net::socket sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
    if (sock.connect_host("zeriph.com", 80) != omni::net::socket_error::SUCCESS) {
        std::cout << "Could not connect to host: " << sock.last_error() << std::endl;
        return -1;
    }

    uint32_t xfr = 0;
    const std::string req = "GET / HTTP/1.0\r\nHost: zeriph.com\r\n\r\n";
    std::cout << "Connected to " << sock << std::endl;
    if (sock.send(req.c_str(), req.size(), xfr) != omni::net::socket_error::SUCCESS) {
        std::cout << "Could not send data: " << sock.last_error() << std::endl;
        return -1;
    }

    std::cout << "Sent " << xfr << " bytes" << std::endl;
    char* data = new char[BUFFSZ];
    while (sock.receive(data, BUFFSZ, xfr) == omni::net::socket_error::SUCCESS) {
        if (xfr > 0) { std::cout << data; }
        std::memset(data, 0, BUFFSZ);
    }
    delete[] data;
    
    if (sock.last_error() != omni::net::socket_error::SUCCESS) {
        std::cout << std::endl << "Last socket error: " << sock.last_error() << std::endl;
    }

    // Strictly speaking this is not necessary here since `sock` is a local
    // object, so when it goes out of scope it will call close on destruction.
    sock.close();

    return 0;
}
