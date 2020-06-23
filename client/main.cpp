#include <iostream>

int main()
{
    std::cout << "Babel client!" << std::endl;
    #ifdef _DEBUG_
    std::cerr << "Debug Mode" << std::endl;
    #endif
    return 0;
}
