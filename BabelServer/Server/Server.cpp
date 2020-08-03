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
    getThread()->stop();
}


void Server::run()
{
//    while (!_servers.empty());
}

void Server::initServers(int ac, char **av)
{
    using namespace BabelNetwork;
    boost::asio::io_context context;

    for (int i = 1; i < ac; i++)
        _servers.emplace_back(new AsioListener(av[0], av[i], context));
//    setThread(boost::make_shared<BabelUtils::BoostThread>(boost::bind(&BabelNetwork::AsioSocket::startContext, boost::ref(context))));
//    setThread(boost::make_shared<BabelUtils::BoostThread>(
//        [objPtr = &context] {
//            std::cout << "THREAD LAUNCHED" << std::endl;
//            objPtr->run();
//            std::cout << "THREAD FINISHED" << std::endl;
//        }
//        )
//    );
//    char data[10] = {0};
//    while (std::cin.getline(data, 10 + 1)) {
//        std::cout << "loop" << std::endl;
//    }
}

[[nodiscard]] const boost::shared_ptr<BabelUtils::BoostThread> &Server::getThread() const
{
    return _thread;
}

void Server::setThread(const boost::shared_ptr<BabelUtils::BoostThread> &thread)
{
    _thread = thread;
}
