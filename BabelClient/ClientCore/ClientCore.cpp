/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 8/22/20).
** File description:
** [ClientCore.cpp]: Source file for ClientCore feature.
*/

#include <iostream>
#include "NetworkError.hpp"
#include "ClientCore.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"

BabelClient::ClientCore::ClientCore(int ac, char **av)
    : _logger(BabelUtils::Logger::ClientLog)
{
    initSocket(ac, av);
}

BabelClient::ClientCore::~ClientCore()
{
    stop();
}

void BabelClient::ClientCore::start()
{
    while (!_socket->isReady())
        std::cout << "Waiting Socket to be ready" << std::endl;
}

void BabelClient::ClientCore::run()
{
    std::string data;
    while (std::getline(std::cin, data)) {
        if (data == "exit" || !_socket->isReady()) {
            std::cout << "exit loop" << std::endl;
            break;
        }
        auto Calltest = BabelNetwork::CallResponse::NewCallStarted("damien", "ugo", 156);
        if (!Calltest)
            std::cerr << "Call test Null" << std::endl;
        else
            _socket->sendResponse(Calltest);
    }
}

void BabelClient::ClientCore::stop()
{
    _socket->stop();
}

void BabelClient::ClientCore::init()
{

}

void BabelClient::ClientCore::initSocket(int ac, char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    _socket = boost::make_shared<BabelNetwork::AsioClientSocket>(
        av[1], av[2],
        _logger,
        BabelNetwork::AsioClientSocket::SocketHandler::Client);
    _socket->connect();
}
