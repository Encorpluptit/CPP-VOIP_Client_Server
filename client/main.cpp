#include <iostream>

int feature1();
int feature2();

int main()
{
    std::cout << "Babel client!" << std::endl;
    feature1();
    feature2();
    #ifdef _DEBUG_
    std::cerr << "Debug Mode" << std::endl;
    #endif
    #ifdef _BABEL_LOG_
    std::cerr << "Log Mode" << std::endl;
    #endif
    return 0;
}
