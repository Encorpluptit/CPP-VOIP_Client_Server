#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"

void launch();

int main()
{
    BabelNetwork::ConnectionResponse resp;
    std::cout << resp.serialize() << std::endl;
    std::cout << resp << std::endl;
//    try {
//        launch();
//    }
//    catch (std::exception &e) {
//        std::cerr << e.what() << std::endl;
//    }
//    return 0;
}