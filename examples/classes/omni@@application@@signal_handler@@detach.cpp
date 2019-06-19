#include <omni/application>

static volatile bool dorun = true;

void app_signal(int sig)
{
    std::cout << "Signal received: " << sig << std::endl;
    dorun = false;
}

void app_run()
{
    int count = 0;
    bool atch = true;
    while (dorun) {
        omni::sync::sleep(10); // small sleep
        if (atch && ++count > 10) {
            atch = false;
            omni::application::signal_handler::detach(&app_signal);
            std::cout << "Will not receive the signal on app_signal" << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    omni::application::signal_handler::attach(&app_signal);
    return omni::application::run(&app_run);
}