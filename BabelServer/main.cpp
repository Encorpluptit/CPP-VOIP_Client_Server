/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "NetworkInfos.hpp"
#include <functional>
#include "AsioListener.hpp"

void launch(char **av);

static void tests(char **av)
{
    std::cout << "TEST LAUNCHED" << std::endl;
    BabelNetwork::NetworkInfos nwi;
    try {
        auto ip = boost::asio::ip::address::from_string(av[1]);
        nwi.setIp(ip.to_string());
    } catch (const std::exception &e) {
        nwi.setIp(boost::asio::ip::address_v4().to_string());
    }
    std::cout << nwi << std::endl;

    boost::asio::io_context context;
    BabelServer::AsioListener listener(nwi, context);

    char data[10] = {0};
    while (std::cin.getline(data, 10 + 1)) {
        std::cout << "loop" << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    try {
        tests(av);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}