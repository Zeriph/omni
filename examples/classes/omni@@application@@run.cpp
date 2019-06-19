#include <omni/application>

void app_exit()
{
    std::cout << "Application exiting" << std::endl;
}

void app_run()
{
    std::cout << "Leaving, waiting for CTRL+C" << std::endl;
}

int main(int argc, const char* argv[])
{
    omni::application::exit_handler::attach(&app_exit);
    return omni::application::run(&app_run);
}