/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include <functional>
#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac < 3)
        return 84;
    try {
        BabelServer::Server server(ac - 1, av + 1);
        try {
            server.start();
        } catch (std::exception &e) {
            std::cerr << "Server Runtime: " << e.what() << std::endl;
            server.stop();
        }
    } catch (std::exception &e) {
        std::cerr << "Server Initialisation: " << e.what() << std::endl;
    }
    std::cout << "End main" << std::endl;
    return 0;
}