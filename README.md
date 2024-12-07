# Omni - A Cross Platform C++ Framework

Omni is an object oriented, cross-platform C++ framework, with recognizable paradigms like [thread objects](https://zeriph.com/omni/docs/examples/threading.html), [delegates and events](https://zeriph.com/omni/docs/examples/delegates_and_events.html), and easy to understand [interfaces](https://zeriph.com/omni/docs/classes/index.html), Omni enables you to get clean and stable C++ code to a wider market more efficiently while lowering code maintenance costs.

For more information regarding Omni and more in-depth documentation, you can view the HTML documentation included with the source files, or you can go to the [Omni main site](https://zeriph.com/omni/).

## Getting Started

Simply grab the latest [source](https://zeriph.com/omni/files/src.zip) and extract it to where you wish, then either `#include <omni/framework>` **or** `#include <omnilib>`, and make sure you include the directory where you extracted the Omni source via your compiler options.

### Prerequisites

Omni is designed to be usable in many simple ways across many [different platforms](https://zeriph.com/omni/xplat.html) with compilers "out of the box". In other words, as long as you have the correct system headers for the platform you're targeting, you can [build](https://zeriph.com/omni/docs/build/index.html) the framework in many different ways with whatever compiler your system might come with (even older compilers for those more esoteric systems).

A simple example building the framework as a whole, from the command line with the single `library.cpp` source file, and a source file called `main.cpp`. This example assumes the source was extracted to `C:\source\omni` on a Windows platform and uses the Microsoft Visual Studio `cl.exe` C++ compiler, where as for the other platforms (Apple/*nix), the source is assumed extracted to `/source/omni` and the `g++` compiler is used, though `clang` or any other C++ compliant compiler will suffice:
```
Windows:
cl main.cpp C:\source\omni\library.cpp /IC:\source\omni\ /EHa /Feprogram.exe

Apple/Unix/Linux/POSIX:
g++ main.cpp /source/omni/library.cpp -I/source/omni -pthread -o program.bin
```

### Using Omni

A simplistic example using [timers](https://zeriph.com/omni/docs/examples/timers.html) and [sockets](https://zeriph.com/omni/docs/examples/sockets.html):

```
#include <omnilib>
#include <vector>
#include <map>

static std::vector<omni::net::endpoint_descriptor> clients;
static std::map<omni::net::endpoint_descriptor*, omni::chrono::async_timer> timers;
static volatile bool running;

static void timer_tick(omni::chrono::tick_t tick_time, const omni::generic_ptr& sobj)
{
    if (!running) { return; }
    omni::net::endpoint_descriptor* ep = static_cast<omni::net::endpoint_descriptor*>(sobj);
    if (ep != OMNI_NULL) {
        if (!ep->is_connected()) {
            timers[ep].stop();
        } else {
            uint32_t xfr = 0;
            char buf[4] = { 'L', 'U', 'B', 0 };
            if (ep->send(buf, sizeof(buf), xfr) != omni::net::socket_error::SUCCESS) {
                std::cerr << "Error sending to client '" << *ep << "': " << ep->last_error() << std::endl;
            } else {
                if (ep->receive(buf, sizeof(buf), xfr) != omni::net::socket_error::SUCCESS) {
                    std::cerr << "Error receiving from client '" << *ep << "': " << ep->last_error() << std::endl;
                } else {
                    if (std::strncmp(buf, "DUB", 4) != 0) {
                        std::cerr << "Heartbeat error, LUB sent but DUB not received; data = '" << buf << "' .. stopping timer." << std::endl;
                        timers[ep].stop();
                    } else {
                        std::cout << "Client '" << *ep << "' still alive!" << std::endl;
                    }
                }
            }
        }
    }
}

static void server_thread()
{
    omni::net::socket server_sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
    if (server_sock.bind(12345) != omni::net::socket_error::SUCCESS) {
        std::cerr << "Error binding on socket: " << server_sock.last_error() << std::endl;
    } else {
        std::cout << "Bound to port " << server_sock.bound_port() << std::endl;
        if (server_sock.listen() != omni::net::socket_error::SUCCESS) {
            std::cerr << "Error listening on socket: " << server_sock.last_error() << std::endl;
        } else {
            std::cout << "Ready to accept connections" << std::endl;
            while (running) {
                omni::net::endpoint_descriptor remote_ep;
                if (server_sock.accept(remote_ep) != omni::net::socket_error::SUCCESS) {
                    std::cerr << "Error accepting on socket: " << server_sock.last_error() << std::endl;
                } else {
                    std::cout << "Client connected: " << remote_ep << std::endl;
                    clients.push_back(remote_ep);
                    timers[&clients.back()] = omni::chrono::async_timer(1000, &timer_tick);
                    timers[&clients.back()].state_object = &clients.back();
                    std::cout << "Starting heartbeat timer for client " << clients.back() << std::endl;
                    timers[&clients.back()].start();
                }
            }
            for (std::vector<omni::net::endpoint_descriptor>::iterator it = clients.begin(); it != clients.end(); ++it) {
                timers[&(*it)].stop();
                it->close();
            }
        }
    }
}

static void client_thread()
{
    omni::net::socket sock(omni::net::address_family::INET, omni::net::socket_type::STREAM, omni::net::protocol_type::TCP);
    if (sock.connect("127.0.0.1", 12345) != omni::net::socket_error::SUCCESS) {
        std::cerr << "Error connecting: " << sock.last_error() << std::endl;
    } else {
        uint32_t xfr = 0;
        char buff[4] = { 'D', 'U', 'B', 0 };
        while (running) {
            if (sock.receive(buff, sizeof(buff), xfr) != omni::net::socket_error::SUCCESS) {
                std::cerr << "Error receiving: " << sock.last_error() << std::endl;
                running = false;
            } else {
                std::cout << "Data received: " << buff << std::endl;
                if (sock.send("DUB", 4, xfr) != omni::net::socket_error::SUCCESS) {
                    std::cerr << "Error sending: " << sock.last_error() << std::endl;
                }
            }
        }
    }
}

static void signal_handler(int sig)
{
    running = false;
}

int main(int argc, char* argv[])
{
    omni::application::signal_handler::attach(&signal_handler);
    running = true;
    if (argc > 1) {
        std::string arg = omni::string::to_lower(argv[1]);
        if (arg == "-c") {
            return omni::application::run(&client_thread);
        }
    }
    return omni::application::run(&server_thread);
}
```

## Deployment

Omni is designed with both static and dynamic linking in mind and can be deployed however you might need; for more information on building you can view the [build help](https://zeriph.com/omni/docs/build/index.html).

## Authors

* **Zechariah Perez** - *Architect/Developer* - [Zeriph](https://zeriph.com)

## License

Omni has a permissive free license that allows you to make derivative works or use Omni how you see fit without worry of license issues - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
 
* All those who have laid the ground work for what we have today.

