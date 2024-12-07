#include <omnilib>

static void timer_func(omni::chrono::tick_t tick, const omni::generic_ptr& so)
{
    std::cout << "monotonic tick count = " << tick << std::endl;
}

int main(int argc, char* argv[])
{
    omni::chrono::async_timer timer(2000);
    timer.tick += timer_func;
    std::cout << "Starting the timer with a delay of 1 second" << std::endl;
    timer.start(1000);
    omni::sync::sleep(6000);
    std::cout << "Stopping the timer" << std::endl;
    timer.stop();
    return 0;
}