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
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

BabelClient::ClientCore::ClientCore(char **av)
    : _logger(BabelUtils::Logger::ClientLog)
{
    initSocket(av);
}

BabelClient::ClientCore::~ClientCore()
{
    stop();
}

void BabelClient::ClientCore::start()
{
    while (!_socket->isReady());
    std::cout << _socket->describe() << std::endl;
}

void BabelClient::ClientCore::doUserResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    printf("code : %d\n", response->getCode());
}

void BabelClient::ClientCore::doCallResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    printf("code : %d\n", response->getCode());
}

void BabelClient::ClientCore::doFriendResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    printf("code : %d\n", response->getCode());
}

void BabelClient::ClientCore::doMessageResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    printf("code : %d\n", response->getCode());
}

void BabelClient::ClientCore::doUnknowTypeResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    printf("code : %d\n", response->getCode());
    throw(BabelErrors::BabelError("Unknow Response Type"));
}   

void BabelClient::ClientCore::checkTypeResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    dispatch_ptr[response->getResponseType()](this, response);
}

void BabelClient::ClientCore::run()
{
    std::string data;
    std::shared_ptr<BabelNetwork::AResponse> response;

    while (1) {
        std::getline(std::cin, data);
        response = _socket->popResponse();
        if (data == "1")
            response = BabelNetwork::UserResponse::NewLoginRequest("ugo", "lolol");
        if (data == "2")
            response = BabelNetwork::CallResponse::CallRequest("ugo", "damien");
        if (data == "3")
            response = BabelNetwork::FriendResponse::FriendRequestAccepted("ugo", "damien");
        if (data == "4")
            response = BabelNetwork::MessageResponse::MessageReceive("ugo", "damien", "t'es mauvais");
        if (data == "exit" || !_socket->isReady()) {
            std::cout << "exit loop" << std::endl;
            break;
        }
        if (response != nullptr) {
            checkTypeResponse(response);
            response = nullptr;
        }
    }
}

void BabelClient::ClientCore::stop()
{
    _socket->stop();
}

void BabelClient::ClientCore::init()
{

}

void BabelClient::ClientCore::initSocket(char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    _socket = boost::make_shared<BabelNetwork::AsioClientSocket>(
        av[1], av[2],
        _logger,
        BabelNetwork::AsioClientSocket::SocketHandler::Client);
    _socket->connect();
}
