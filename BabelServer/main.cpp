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
#include "Debug/Debug.hpp"
#include "ConnectionResponse.hpp"

void launch();

int main()
{
    BabelNetwork::ConnectionResponse lol;

    std::cout << std::boolalpha << lol.isOk() << std::endl;
    std::cout << lol.getCode() << std::endl;
    std::cout << lol << std::endl;
    lol.setData("MDR DATA");
    std::cout << lol << std::endl;
    std::cout << std::format("Hello %s!\n", "world");
    dbg("%s", "lol");

    try {
        launch();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}