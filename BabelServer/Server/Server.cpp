/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Server.cpp]: Source file for Server feature.
*/

#include <iostream>
#include "Server.hpp"
#include "AsioListener.hpp"
#include "Debug.hpp"

using namespace BabelServer;

Server::Server(int ac, char **av)
    : _logger(BabelUtils::Logger::LogType::ServerLog),
      _database(_logger),
      _manager(_logger)
{
    _ready = false;
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
    setReady();

    runListener();
}

void Server::stop()
{
    if (listenerRunning()) {
        for (const auto &server : _servers)
            server->stop();
    }
    if (_thread)
        _thread->stop();
}

bool Server::listenerRunning()
{
    return std::all_of(
        _servers.cbegin(), _servers.cend(),
        [](const BabelUtils::SharedPtr<BabelServer::Listener> &server) { return server->isReady(); }
    );
}

void Server::runListener()
{
    while (listenerRunning()) {
        std::cout << "ICI LOL CA LOOP" << std::endl;
        std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> clients;
        for (const auto &server : _servers) {
            auto list = server->getClientList();
            if (list.empty())
                continue;
            clients.insert(clients.end(), list.begin(), list.end());
        }
        if (clients.empty())
            continue;
        for (const auto &client : clients) {
            if (!client->isReady())
                continue;
            auto resp = client->popResponse();
            if (!resp)
                continue;
            if (!_manager.manage(client, resp, clients, _database)) {
                std::string log("Unknown Response Type");
                _logger.logThis(resp, log);
                dbg("%s", log.c_str());
            }
        }
    }
}

void Server::initServers(int ac, char **av)
{
    using namespace BabelNetwork;

    for (int i = 1; i < ac; i++)
        _servers.emplace_back(new AsioListener(av[0], av[i], _logger));
}

const BabelUtils::SharedPtr<BabelUtils::AThread> &Server::getThread() const
{
    return _thread;
}

void Server::setThread(const BabelUtils::SharedPtr<BabelUtils::AThread> &thread)
{
    _thread = thread;
}
