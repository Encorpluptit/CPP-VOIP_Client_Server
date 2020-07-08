#include <iostream>
#include "Debug/Debug.hpp"

int feature1();
int feature2();

int main()
{
    std::cout << "Babel client!" << std::endl;
    feature1();
    feature2();
    dbg("%s", "DEBUG");
    #ifdef _DEBUG_
    std::cerr << "Debug Mode" << std::endl;
    #endif
    #ifdef _BABEL_LOG_
    std::cerr << "Log Mode" << std::endl;
    #endif
    return 0;
}
