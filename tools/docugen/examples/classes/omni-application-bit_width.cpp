#include <omni/application>

int main(int argc, char** argv)
{
    std::cout << "Application bit-size: " << omni::application::bit_width() << std::endl;
    return 0;
}