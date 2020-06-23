#include <iostream>

int main()
{
    std::cout << "Babel server!" << std::endl;
    #ifdef _DEBUG_
    std::cerr << "Debug Mode" << std::endl;
    #endif
    return 0;
}
