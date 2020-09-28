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

using namespace BabelClient;

ClientCore::ClientCore(char **av)
    : _logger(BabelUtils::Logger::ClientLog)
{
    initSocket(av);
    logged = false;
}

ClientCore::~ClientCore()
{
    stop();
}

bool socketRdy(bool set, bool value)
{
    static bool rdy = false;

    if (set) {
        rdy = value;
    }
    return rdy;
}

void ClientCore::setSocketReady() const
{
    socketRdy(true, true);
}

void ClientCore::setSocketNotReady() const
{
    socketRdy(true, false);
}

void ClientCore::getSocketState() const
{
    socketRdy(false, false);
}

void ClientCore::start()
{
    while (!_socket->isReady());
    std::cout << _socket->describe() << std::endl;
    setReady();
}


// TODO: GROSSE MERDE, T'ES MAUVAIS
// PASSE LES SHARED PTR EN CONST REF
void ClientCore::LoggedIn(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    logged = true;
    name = response->getLogin();
}

void ClientCore::LoggedOut(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    logged = false;
}

void ClientCore::AccountCreate(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    logged = true;
    name = response->getLogin();
}

void ClientCore::AccountDelete(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    logged = false;
}

void ClientCore::UnknowUserError(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    //FRONT ARTHUR;
}

void ClientCore::WrongLogin(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::WrongPassword(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::LoginAlreadyTaken(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::AlreadyLoggedIn(std::shared_ptr<BabelNetwork::UserResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallStarted(std::shared_ptr<BabelNetwork::CallResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallLeft(std::shared_ptr<BabelNetwork::CallResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::IncomingCall(std::shared_ptr<BabelNetwork::CallResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallAccepted(std::shared_ptr<BabelNetwork::CallResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallRefused(std::shared_ptr<BabelNetwork::CallResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::UserDisconnected(std::shared_ptr<BabelNetwork::CallResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::AddFriend(std::shared_ptr<BabelNetwork::FriendResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::FriendRequest(std::shared_ptr<BabelNetwork::FriendResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::UnknowUser(std::shared_ptr<BabelNetwork::FriendResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::SendMessageOk(std::shared_ptr<BabelNetwork::MessageResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::ReceiveMessage(std::shared_ptr<BabelNetwork::MessageResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::UnknowUserMessage(std::shared_ptr<BabelNetwork::MessageResponse> response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::doUserResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    std::shared_ptr<BabelNetwork::UserResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::UserResponse>(response);
    int code = response->getCode();

    for (size_t i = 0; i < userCodeIdx.size(); i++)
        if (userCodeIdx[i] == code)
            user_ptr[i](this, ptr);
}

void ClientCore::doCallResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    std::shared_ptr<BabelNetwork::CallResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::CallResponse>(response);
    int code = response->getCode();

    for (size_t i = 0; i < callCodeIdx.size(); i++)
        if (callCodeIdx[i] == code)
            call_ptr[i](this, ptr);
}

void ClientCore::doFriendResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    std::shared_ptr<BabelNetwork::FriendResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::FriendResponse>(
        response);
    int code = response->getCode();

    for (size_t i = 0; i < friendCodeIdx.size(); i++)
        if (friendCodeIdx[i] == code)
            friend_ptr[i](this, ptr);
}

void ClientCore::doMessageResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    std::shared_ptr<BabelNetwork::MessageResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(
        response);
    int code = response->getCode();

    for (size_t i = 0; i < messageCodeIdx.size(); i++)
        if (messageCodeIdx[i] == code)
            message_ptr[i](this, ptr);
}

void ClientCore::doUnknowTypeResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    printf("code : %d\n", response->getCode());
    throw (BabelErrors::BabelError("Unknow Response Type"));
}

void ClientCore::checkTypeResponse(std::shared_ptr<BabelNetwork::AResponse> response)
{
    dispatch_ptr[response->getResponseType()](this, response);
}

void ClientCore::run()
{
    std::string data;
    std::shared_ptr<BabelNetwork::AResponse> response = nullptr;

    while (isReady()) {
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
        if (data == "5")
            response = BabelNetwork::UserResponse::AccountCreationRequest("ugo", "lolol");
        if (data == "6")
            response = BabelNetwork::UserResponse::AccountDeletionRequest("ugo");
        if (data == "7")
            response = BabelNetwork::CallResponse::CallRequest("ugo", "dam", _socket->getIp(), _socket->getPort());
        if (data == "8")
            response = BabelNetwork::CallResponse::RefusedCall("ugo", "dam");
        if (data == "9")
            response = BabelNetwork::CallResponse::AcceptCall("ugo", "dam");
        if (data == "10")
            response = BabelNetwork::MessageResponse::RequestMessageSend("dam", "ugo", "coucou");
        if (data == "exit" || !_socket->isReady()) {
            std::cout << "exit loop" << std::endl;
            break;
        }
        if (response != nullptr) {
            checkTypeResponse(response);
            _socket->sendResponse(response);
        }
    }
}

void ClientCore::stop()
{
    _socket->stop();
}

//void ClientCore::init()
//{
//
//}

void ClientCore::initSocket(char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);

    _socket = boost::make_shared<BabelNetwork::AsioClientSocket>(
        av[1], av[2],
        _logger,
        BabelNetwork::AsioClientSocket::SocketHandler::Client);
    _socket->connect();
}
