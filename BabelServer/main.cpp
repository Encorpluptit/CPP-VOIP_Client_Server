/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include <functional>
#include "AsioListener.hpp"
#include "Server.hpp"

void launch(char **av);

static void tests(char **av)
{
    std::cout << "TEST LAUNCHED" << std::endl;
    boost::asio::io_context context;
    BabelServer::AsioListener listener(av[1], av[2], context);
    listener.setThread(boost::make_shared<BabelUtils::BoostThread>(
        [objPtr = &listener] {
            std::cout << "THREAD LAUNCHED on " << objPtr->getNetworkInfos() << std::endl;
            objPtr->getContext().run();
            std::cout << "THREAD FINISHED on " << objPtr->getNetworkInfos() << std::endl;
        }
        )
    );

    char data[10] = {0};
    while (std::cin.getline(data, 10 + 1)) {
        std::cout << "loop" << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac < 3)
        return 84;
    try {
//        BabelServer::Server server(ac - 1, av + 1);
//        server.run();
        tests(av);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}