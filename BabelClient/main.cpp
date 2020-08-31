/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "ClientCore.hpp"
#include "NetworkError.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
        return (84);
    std::cout << "Babel client!" << std::endl;
    try {
        BabelClient::ClientCore core(ac, av);
        core.start();
        core.run();
    } catch (const BabelErrors::BabelError &e) {
        std::cerr << "IN CLIENT MAIN" << e.what() << std::endl;
    }
    return 0;
}
