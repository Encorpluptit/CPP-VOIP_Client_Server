/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [RequestManager.cpp]: Source file for RequestManager feature.
*/

#include "RequestManager.hpp"
#include "UserResponse.hpp"

using namespace BabelServer;
using namespace BabelNetwork;

bool RequestManager::manage(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<AResponse> &response,
    const ClientList &clientList,
    Database &database
)
{
    switch (response->getResponseType()) {
        case AResponse::User:
            manageUser(clientSocket, std::dynamic_pointer_cast<UserResponse>(response), clientList,
                database);
            return true;
        case AResponse::Call:
            manageCall(clientSocket, std::dynamic_pointer_cast<CallResponse>(response), clientList,
                database);
            return true;
        case AResponse::Friend:
            manageFriend(clientSocket, std::dynamic_pointer_cast<FriendResponse>(response), clientList,
                database);
            return true;
        case AResponse::Message:
            manageMessage(clientSocket, std::dynamic_pointer_cast<MessageResponse>(response), clientList,
                database);
            return true;
        case AResponse::UnknownType:
            break;
    }
    return false;
}

void RequestManager::manageUser(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    const ClientList &clientList,
    Database &database
)
{
    auto code = response->getCode();
    auto userTabPtr = _userManager.getUserResponsePtrTab();

    for (const auto &ptr : userTabPtr) {
        if (std::get<0>(ptr) == code)
            return std::get<1>(ptr)(&_userManager, clientSocket, response, clientList, database);
    }
}

void RequestManager::manageCall(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<CallResponse> &response,
    const ClientList &clientList,
    #ifndef _WIN32
    __attribute__((unused))
    #endif
    Database &database
)
{
    if (!clientSocket->getUser()) {
        clientSocket->sendResponse(UserResponse::ClientNotLogged());
        return;
    }
    auto code = response->getCode();
    auto callTabPtr = _callManager.getCallResponsePtrTab();

    for (const auto &ptr : callTabPtr) {
        if (std::get<0>(ptr) == code)
            return std::get<1>(ptr)(&_callManager, clientSocket, response, clientList);
    }
}

void RequestManager::manageFriend(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<FriendResponse> &response,
    const ClientList &clientList,
    Database &database
)
{
    if (!clientSocket->getUser()) {
        clientSocket->sendResponse(UserResponse::ClientNotLogged());
        return;
    }
    auto code = response->getCode();
    auto friendTabPtr = _friendManager.getFriendResponsePtrTab();

    for (const auto &ptr : friendTabPtr) {
        if (std::get<0>(ptr) == code)
            return std::get<1>(ptr)(&_friendManager, clientSocket, response, clientList, database);
    }
    std::cerr << "WRONG FRIEND CODE" << std::endl;
}

void RequestManager::manageMessage(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<MessageResponse> &response,
    const ClientList &clientList,
    Database &database
)
{
    if (!clientSocket->getUser()) {
        clientSocket->sendResponse(UserResponse::ClientNotLogged());
        return;
    }
    auto code = response->getCode();
    auto messageTabPtr = _messageManager.getMessageResponsePtrTab();

    for (const auto &ptr : messageTabPtr) {
        if (std::get<0>(ptr) == code)
            return std::get<1>(ptr)(&_messageManager, clientSocket, response, clientList, database);
    }
}
