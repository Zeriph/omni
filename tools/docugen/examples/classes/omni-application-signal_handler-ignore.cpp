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
        if (atch) {
            if (++count == 300) {
                omni::application::signal_handler::ignore(false);
                std::cout << "Will listen for the signal on app_signal" << std::endl;
                atch = false;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    omni::application::signal_handler::attach(&app_signal);
    omni::application::signal_handler::ignore(true);
    std::cout << "Signal handler attached, but will ignore signals for ~3s" << std::endl;
    return omni::application::run(&app_run);
}