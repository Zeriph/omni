#include <omnilib>

static volatile bool dorun = true;

void app_signal(int sig)
{
    std::cout << "Signal received: " << sig << std::endl;
    dorun = false;
}

void app_run()
{
    int count = 0;
    std::cout << "Running" << std::endl;
    while (dorun) {
        omni::sync::sleep(10); // small sleep
        if (++count > 100) {
            std::cout << "Calling stop" << std::endl;
            omni::application::stop();
        }
    }
}

int main(int argc, const char* argv[])
{
    omni::application::signal_handler::attach(&app_signal);
    int ret = omni::application::run(&app_run);
    std::cout << "Return code: " << ret << std::endl;
    return ret;
}