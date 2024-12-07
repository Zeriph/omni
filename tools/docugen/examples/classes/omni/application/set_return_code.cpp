#include <omnilib>

static volatile bool dorun = true;

void app_signal(int sig)
{
    std::cout << "Signal received: " << sig << std::endl;
    omni::application::set_return_code(1);
    dorun = false;
}

void app_run()
{
    omni::application::set_return_code(-1);
    while (dorun) {
        omni::sync::sleep(10); // small sleep
    }
}

int main(int argc, const char* argv[])
{
    omni::application::signal_handler::attach(&app_signal);
    int ret = omni::application::run(&app_run);
    std::cout << "Return code: " << ret << std::endl;
    return ret;
}