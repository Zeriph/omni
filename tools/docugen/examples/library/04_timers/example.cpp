#include <omnilib>

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
