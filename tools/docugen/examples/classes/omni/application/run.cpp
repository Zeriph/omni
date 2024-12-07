#include <omnilib>

void app_exit()
{
    std::cout << "Application exiting" << std::endl;
}

int main(int argc, const char* argv[])
{
    omni::application::exit_handler::attach(&app_exit);
    std::cout << "Waiting for CTRL+C" << std::endl;
    return omni::application::run();
}