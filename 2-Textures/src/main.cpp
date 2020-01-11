#include "engine.h"

int main()
{
    Engine engine(640, 480, "2. Texture Test - Escape to exit");

    if(!engine.Initialize())
    {
        std::cout << std::endl << "Press any key to close program..." << std::endl;
        std::cin.get();
    }
}

