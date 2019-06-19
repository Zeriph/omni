#include <omni/application>

void app_start()
{
    std::cout << "Application starting up" << std::endl;
}

void app_exit()
{
    std::cout << "Application exiting" << std::endl;
}

void app_shutdown()
{
    std::cout << "Application shutting down" << std::endl;
}

void app_run()
{
    std::cout << "Leaving, waiting for CTRL+C" << std::endl;
}

int main(int argc, const char* argv[])
{
    omni::application::startup_handler::attach(&app_start);
    omni::application::exit_handler::attach(&app_exit);
    omni::application::shutdown_handler::attach(&app_shutdown);
    return omni::application::run(&app_run);
}