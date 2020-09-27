/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 8/22/20).
** File description:
** [ClientCore.cpp]: Source file for ClientCore feature.
*/

#include <iostream>
#include "ClientCore.hpp"
#include "mainwindow.hpp"
#include "NetworkInfos.hpp"

using namespace BabelClient;

ClientCore::ClientCore(int ac, char **av)
    : _logger(BabelUtils::Logger::ClientLog)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);

    initSocket(nwi.getIp(), nwi.getPort());
    appli = new Application(ac, av);
    gui = new MainWindow(nullptr, socket);
    gui->showApp();
    appli->init();
}

ClientCore::~ClientCore()
{

}

void ClientCore::initSocket(const std::string &ip, int port)
{
    socket = new MyTcpSocket();
    socket->doConnect(ip, port);
}

/*void ClientCore::loop()
{
    std::shared_ptr<BabelNetwork::AResponse> response;

    while (1) {
        if ((response = socket->readResponse()) != nullptr)
            checkTypeResponse(response);
    }
}*/

void ClientCore::LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void ClientCore::LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void ClientCore::AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void ClientCore::AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void ClientCore::UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void ClientCore::WrongLogin(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::WrongPassword(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::LoginAlreadyTaken(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::AlreadyLoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallStarted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallLeft(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::IncomingCall(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallAccepted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::CallRefused(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::UserDisconnected(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::AddFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::FriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::UnknowUser(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::SendMessageOk(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::ReceiveMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::UnknowUserMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void ClientCore::doUserResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::UserResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::UserResponse>(response);
    int code = response->getCode();

    for (size_t i = 0; i < userCodeIdx.size(); i++)
        if (userCodeIdx[i] == code)
            user_ptr[i](this, ptr);
}

void ClientCore::doCallResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::CallResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::CallResponse>(response);
    int code = response->getCode();

    for (size_t i = 0; i < callCodeIdx.size(); i++)
        if (callCodeIdx[i] == code)
            call_ptr[i](this, ptr);
}

void ClientCore::doFriendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::FriendResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::FriendResponse>(
        response);
    int code = response->getCode();

    for (size_t i = 0; i < friendCodeIdx.size(); i++)
        if (friendCodeIdx[i] == code)
            friend_ptr[i](this, ptr);
}

void ClientCore::doMessageResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::MessageResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(
        response);
    int code = response->getCode();

    for (size_t i = 0; i < messageCodeIdx.size(); i++)
        if (messageCodeIdx[i] == code)
            message_ptr[i](this, ptr);
}

void ClientCore::doUnknowTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    printf("code : %d\n", response->getCode());
    throw (BabelErrors::BabelError("Unknow Response Type"));
}

void ClientCore::checkTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    dispatch_ptr[response->getResponseType()](this, response);
}