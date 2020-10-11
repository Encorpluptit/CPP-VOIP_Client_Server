/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "ClientCore.hpp"

int main(int ac, char **av)
{
    std::cout << "ici" << std::endl;
    if (ac != 3)
        return (84);
    std::cout << "ici" << std::endl;
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    std::cout << "ici" << std::endl;
    NetworkClientSocket network(nwi.getIp(), nwi.getPort());
    std::cout << "ici" << std::endl;
    BabelClient::ClientCore client(ac, av, network);
    std::cout << "ici" << std::endl;
    return (client.run());
}