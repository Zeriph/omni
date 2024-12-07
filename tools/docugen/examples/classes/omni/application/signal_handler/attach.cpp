#include <omnilib>

static volatile bool dorun = true;

void app_signal(int sig)
{
    std::cout << "Signal received: " << sig << std::endl;
    dorun = false;
}

void app_run()
{
    while (dorun) {
        omni::sync::sleep(10); // small sleep
    }
}

int main(int argc, char* argv[])
{
    omni::application::signal_handler::attach(&app_signal);
    return omni::application::run(&app_run);
}