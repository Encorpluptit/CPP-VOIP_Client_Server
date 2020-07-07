//#include <iostream>
//#include "../common/Debug.hpp"
//
//int feature1();
//int feature2();
//
//int main()
//{
//    std::cout << "Babel server!" << std::endl;
//    feature1();
//    feature2();
//    dbg("%s", "DEBUG");
//    #ifdef _DEBUG_
//    std::cerr << "Debug Mode" << std::endl;
//    #endif
//    #ifdef _BABEL_LOG_
//    std::cerr << "Log Mode" << std::endl;
//    #endif
//    return 0;
//}

#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"

void launch();

int main()
{
    dbg("%s", "DEBUG MODE");
    BabelNetwork::ConnectionResponse lol;
    try {
        launch();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}