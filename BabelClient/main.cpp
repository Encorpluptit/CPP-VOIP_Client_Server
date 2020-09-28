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
    if (ac != 3)
        return (84);
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    NetworkClientSocket network(nwi.getIp(), nwi.getPort());
    BabelClient::ClientCore client(ac, av, network);
    return (client.run());
}