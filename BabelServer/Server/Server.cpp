/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Server.cpp]: Source file for Server feature.
*/

#include "Server.hpp"

using namespace BabelServer;

Server::Server(int ac, char **av)
    : _logger(BabelUtils::Logger::LogType::ServerLog)
{
    initServers(ac, av);
}

void Server::run()
{
    while (!_servers.empty());
}

void Server::initServers(int ac, char **av)
{
    using namespace boost::asio::ip;
    using namespace BabelNetwork;
    boost::asio::io_context context;
    BabelNetwork::NetworkInfos nwi;

    if (ac == 1) {
        try {
            nwi = NetworkInfos(address::from_string(av[0]).to_string());
        } catch (const std::exception &e) {
            nwi = NetworkInfos(address::from_string(av[0]).to_string());
        }
        _servers.emplace_back(new AsioListener(nwi, context));
    } else {
        for (int i = 1; i < ac; i++) {
            try {
                nwi = NetworkInfos(address::from_string(av[0]).to_string(), av[i]);
            } catch (const std::exception &e) {
                nwi = NetworkInfos(address::from_string(av[0]).to_string(), av[i]);
            }
            _servers.emplace_back(new AsioListener(nwi, context));
        }
    }
}
