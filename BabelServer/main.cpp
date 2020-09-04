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

/*static void tests(char **av)
{
    std::cout << "TEST LAUNCHED" << std::endl;
    BabelUtils::Logger logger(BabelUtils::Logger::LogType::ServerLog);
    BabelServer::AsioListener listener(av[1], av[2], logger);
    listener.start();

    std::string data;
    while (std::getline(std::cin, data)) {
        std::cout << data << std::endl;
        if (data == "exit") {
            std::cout << "exit loop" << std::endl;
            break;
        }
    }
}*/

int main(int ac, char **av)
{
    if (ac < 3)
        return 84;
    try {
        BabelServer::Server server(ac - 1, av + 1);
        server.start();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "End main" <<std::endl;
    return 0;
}