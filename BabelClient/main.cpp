/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "Debug.hpp"
#include "AsioClientSocket.hpp"

int feature1();

int feature2();

static void socket_testing(char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    boost::asio::io_context context;
    BabelNetwork::AsioClientSocket client(nwi, context);
    client.connect();
//    client.setThread(boost::make_shared<BabelUtils::BoostThread>(
//        [&client] {
//            std::cout << "CLIENT THREAD LAUNCHED" << std::endl;
//            client.getContext().run();
//            std::cout << "CLIENT THREAD FINISHED" << std::endl;
//        }
//        )
//    );
    char data[10] = {0};
    while (std::cin.getline(data, 10 + 1)) {
        std::cout << "loop" << std::endl;
    }
}

int main(int ac, char **av)
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
    socket_testing(av);
    return 0;
}
