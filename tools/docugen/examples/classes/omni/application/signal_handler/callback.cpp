#include <omnilib>

static volatile bool dorun = true;

void app_signal(int sig)
{
    std::cout << "Signal received: " << sig << std::endl;
    dorun = false;
}

void other_app_sig(int sig)
{
    std::cout << "Other signal: " << sig << std::endl;
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
    omni::application::signal_handler::callback cb = &app_signal;
    if (argc > 3) { cb = &other_app_sig; }
    omni::application::signal_handler::attach(cb);
    return omni::application::run(&app_run);
}