#include <omni/application>

void app_exit()
{
    std::wcout << "Application exiting: arg count = " << omni::application::args().argc() << ", to string = " << omni::application::args() << std::endl;
}

int main(int argc, const char* argv[])
{
    omni::application::exit_handler::attach(&app_exit);
    std::wcout << "Waiting for CTRL+C" << std::endl;
    return omni::application::run(argc, argv);
}