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
    try {
        if (ac != 3)
            return (84);
        std::srand(std::time(nullptr));
        BabelNetwork::NetworkInfos nwi(av[1], av[2]);
        NetworkClientSocket network(nwi.getIp(), nwi.getPort());
        BabelClient::ClientCore client(ac, av, network);
        return (client.run());
    } catch (BabelErrors::BabelError &err) {
        std::cout << err.what() << std::endl;
        return (84);
    }
}