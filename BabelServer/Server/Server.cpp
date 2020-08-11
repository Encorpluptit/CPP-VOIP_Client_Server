/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Server.cpp]: Source file for Server feature.
*/

#include <iostream>
#include "Server.hpp"

using namespace BabelServer;

Server::Server(int ac, char **av)
    : _logger(BabelUtils::Logger::LogType::ServerLog)
{
    initServers(ac, av);
}

Server::~Server()
{
    stop();
}

void Server::start()
{
    for (const auto &server : _servers)
        server->start();

    std::string data;
    while (std::getline(std::cin, data)) {
        std::cout << data << std::endl;
        if (data == "exit") {
            std::cout << "exit loop" << std::endl;
            break;
        }
    }
}

void Server::stop()
{
    for (const auto& server : _servers)
        server->stop();
    if (_thread)
        _thread->stop();
}

void Server::initServers(int ac, char **av)
{
    using namespace BabelNetwork;

    for (int i = 1; i < ac; i++)
        _servers.emplace_back(new AsioListener(av[0], av[i], _logger));
}

[[nodiscard]] const boost::shared_ptr<BabelUtils::BoostThread> &Server::getThread() const
{
    return _thread;
}

void Server::setThread(const boost::shared_ptr<BabelUtils::BoostThread> &thread)
{
    _thread = thread;
}
