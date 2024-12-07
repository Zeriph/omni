#include <omnilib>

void app_exit()
{
    std::cout << "app_exit!" << std::endl;
}

void app_run()
{
    std::cout << "In non-member function app_run" << std::endl;
    std::cout << "Leaving app_run and waiting for CTRL+C" << std::endl;
}

class app {
    public:
        app() : m_val(42) { std::cout << "app constructing value = " << this->m_val << std::endl; }
        ~app() { std::cout << "app deconstructing value = " << this->m_val << std::endl; }

        void run()
        {
            std::cout << "In member function app::run value = " << this->m_val << std::endl;
            ++this->m_val;
            std::cout << "Increased value by 1, leaving app::run and waiting for CTRL+C" << std::endl;
        }

        static void exit()
        {
            std::cout << "app::exit!" << std::endl;
        }

    private:
        int32_t m_val;
};

int main(int argc, const char* argv[])
{
    omni::application::exit_handler::attach(&app_exit);
    omni::application::exit_handler::attach(&app::exit);
    if (argc > 1) {
        app mainapp;
        // DEV_NOTE: you cant bind member functions to the exit handler in this way
        // you have to create a reference type that will be deconstructed in a static
        // handler, otherwise, the object can be deconstructed before the exit handler
        // is called, causing undefined behavior because of the reference after free.
        return omni::application::run(omni::sync::thread_start::bind<app, &app::run>(mainapp));
    }
    return omni::application::run(&app_run);
}