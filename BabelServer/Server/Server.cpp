/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Server.cpp]: Source file for Server feature.
*/

#include <iostream>
#include "Server.hpp"
#include "AsioListener.hpp"

using namespace BabelServer;

Server::Server(int ac, char **av)
    : _logger(BabelUtils::Logger::LogType::ServerLog)
{
    _ready = false;
    initServers(ac, av);
}

Server::~Server()
{
    stop();
    if (_thread)
        _thread->stop();
}

void Server::start()
{
    for (const auto &server : _servers)
        server->start();
    setReady();
//    setThread(boost::make_shared<BabelUtils::BoostThread>(
//        [this] {
//            try {
//                std::cout << "HANDLE CLIENTS REQUESTS" << std::endl;
//                this->runListener();
//                std::cout << "HANDLE CLIENTS REQUESTS FINISHED" << std::endl;
//            } catch (const std::exception &e) {
//                std::cerr << e.what() << std::endl;
//            }
//        })
//    );
    std::string data;
    while (std::getline(std::cin, data)) {
        for (const auto & server : _servers) {
            auto clients = server->getClientList();
            for (const auto & client : clients) {
                auto resp = client->popResponse();
                if (!resp)
                    continue;
                std::cout << resp << std::endl;
            }
        }
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

void Server::runListener()
{
    auto sz = _servers.size();
    unsigned long szStopped = 0;

//    while (isReady() && sz != szStopped) {
    while (isReady() && sz != szStopped) {
        sz = _servers.size();
        szStopped = 0;
        for (const auto &server : _servers) {
            if (!server->isReady()) {
                szStopped += 1;
                continue;
            }
            auto clients = server->getClientList();
            if (clients.empty())
                continue;
            for (const auto &client : clients) {
                auto resp = client->popResponse();
                if (!resp)
                    continue;
                std::cout << "HERE " << resp << std::endl;
            }
        }
//        if (sz == szStopped)
//            break;
    }
}

void Server::initServers(int ac, char **av)
{
    using namespace BabelNetwork;

    for (int i = 1; i < ac; i++)
        _servers.emplace_back(new AsioListener(av[0], av[i], _logger));
}

[[nodiscard]] const BabelUtils::SharedPtr<BabelUtils::AThread> &Server::getThread() const
{
    return _thread;
}

void Server::setThread(const BabelUtils::SharedPtr<BabelUtils::AThread> &thread)
{
    _thread = thread;
}
