#include <iostream>
#include "Debug/Debug.hpp"
#include "ConnectionResponse.hpp"

void launch();

int main()
{
    try {
        launch();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}