# Omni - A Cross Platform C++ Framework

Omni is an object oriented, cross-platform C++ framework, with recognizable paradigms like [thread objects](https://zeriph.com/omni/docs/examples/threading.html), [delegates and events](https://zeriph.com/omni/docs/examples/delegates_and_events.html), and easy to understand [interfaces](https://zeriph.com/omni/docs/classes/index.html), Omni enables you to get clean and stable C++ code to a wider market more efficiently while lowering code maintenance costs.

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

An example using [timers](https://zeriph.com/omni/docs/examples/timers.html):

```
#include <omni/framework>

static omni::sync::basic_lock mtx;
static std::map<int, std::string> vals;
static std::map<int, int> tcount;

void print_status(int val, const std::string& el)
{
    mtx.lock();
    std::cout << "Thread #" << omni::sync::thread_id() << " (" << vals[val] << ") " << el << std::endl;
    mtx.unlock();
}

void timer_tick(omni::chrono::tick_t tick_time, const omni::generic_ptr& sobj)
{
    int idx = (*static_cast<int*>(sobj));
    tcount[idx] = tcount[idx] + 1;
    print_status(idx, "enter");
    omni::sync::sleep(1500); // sleep 1.5s
    print_status(idx, "leaving");
}

int main(int argc, char* argv[])
{
    int idx[] = { 1, 2, 3, 4 };
    vals[1] = "async_timer";
    vals[2] = "sync_timer";
    vals[3] = "queue_timer";
    vals[4] = "drop_timer";
    
    omni::chrono::async_timer atimer(1000, &timer_tick);
    atimer.state_object = &idx[0];
    
    omni::chrono::sync_timer  stimer(1000);
    omni::chrono::queue_timer qtimer(1000);
    omni::chrono::drop_timer  dtimer(1000);

    stimer.tick += &timer_tick;
    stimer.state_object = &idx[1];
    
    qtimer.tick += &timer_tick;
    qtimer.state_object = &idx[2];
    
    dtimer.tick += &timer_tick;
    dtimer.state_object = &idx[3];
    
    std::cout << "starting timers" << std::endl;
    atimer.start(); // 6 ticks
    stimer.start(); // approximately 3 ticks (delay)
    qtimer.start(); // 6 ticks (deferred)
    dtimer.start(); // approximately 5 ticks
    
    std::cout << "sleeping 6 seconds" << std::endl;
    omni::sync::sleep(6000); // sleep 6s
    
    std::cout << "stopping timers" << std::endl;
    atimer.stop();
    stimer.stop();
    qtimer.stop();
    dtimer.stop();
    
    std::cout << "sleeping 3 seconds to wait the other ticks" << std::endl;
    omni::sync::sleep(3000); // sleep 6s
    
    for (int i = 1; i <= 4; ++i) {
        std::cout << vals[i] << " tick count: " << tcount[i] << std::endl;
    }
    
    return 0;
}
```

## Deployment

Omni is designed with both static and dynamic linking in mind and can be deployed however you might need.

## Authors

* **Zechariah Perez** - *Architect/Developer* - [Zeriph](https://zeriph.com)

## License

Omni has a permissive free license that allows you to make derivative works or use Omni how you see fit without worry of license issues - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments
 
* All those who have laid the ground work for what we have today.

