#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"

void launch();

int main()
{
    BabelUtils::Logger log(BabelUtils::Logger::ServerLog);

    int lol = 5;
    log.logThis("%d", lol);
//    try {
//        launch();
//    }
//    catch (std::exception &e) {
//        std::cerr << e.what() << std::endl;
//    }
//    return 0;
}