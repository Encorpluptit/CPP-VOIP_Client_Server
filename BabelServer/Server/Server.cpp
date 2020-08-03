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

Server::~Server()
{
    for (const auto& server : _servers)
        server->stop();
//    getThread()->stop();
}

void Server::run()
{
    std::string data;
    while (std::getline(std::cin, data)) {
        std::cout << data << std::endl;
        if (data == "exit") {
            std::cout << "exit loop" << std::endl;
            break;
        }
    }
//    while (!_servers.empty());
}

void Server::initServers(int ac, char **av)
{
    using namespace BabelNetwork;
    boost::asio::io_context context;

//    _servers.emplace_back(new AsioListener(av[0], av[1]));

    for (int i = 1; i < ac; i++)
        _servers.emplace_back(new AsioListener(av[0], av[i]));

//    setThread(boost::make_shared<BabelUtils::BoostThread>(
//        boost::bind(&BabelNetwork::AsioSocket::startContext2, _servers.front())));
//    setThread(boost::make_shared<BabelUtils::BoostThread>(
//        boost::bind(&BabelNetwork::AsioSocket::startContext, boost::ref(context))));
//    setThread(boost::make_shared<BabelUtils::BoostThread>(
//        [objPtr = &context] {
//            std::cout << "THREAD LAUNCHED" << std::endl;
//            objPtr->run();
//            std::cout << "THREAD FINISHED" << std::endl;
//        }
//        )
//    );

//    for (auto &server: _servers)
//        server->start();
//    context.run();
//    std::string data;
//    while (std::getline(std::cin, data)) {
//        std::cout << data << std::endl;
//        if (data == "exit") {
//            std::cout << "exit loop" << std::endl;
//            break;
//        }
//    }
//    context.stop();
//    getThread()->stop();
}

[[nodiscard]] const boost::shared_ptr<BabelUtils::BoostThread> &Server::getThread() const
{
    return _thread;
}

void Server::setThread(const boost::shared_ptr<BabelUtils::BoostThread> &thread)
{
    _thread = thread;
}
