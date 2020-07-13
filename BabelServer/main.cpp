#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"
#include "NetworkInfos.hpp"
#include "TcpSocket.hpp"

void launch(char **av);

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    try {
        launch(av);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}