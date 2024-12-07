#include <omnilib>

void app_run()
{
    // get a reference
    omni::application::argparser& args = omni::application::args();
    for (int i = 0; i < args.size(); ++i) {
        std::cout << "args[" << i << "]: " << args[i] << std::endl;
    }
    // alternatively
    std::cout << "args = " << args << std::endl;
    std::cout << "Leaving, waiting for CTRL+C" << std::endl;
}

int main(int argc, const char* argv[])
{
    omni::application::set_args(argc, argv);
    return omni::application::run(&app_run);
}