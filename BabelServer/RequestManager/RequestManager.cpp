/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [RequestManager.cpp]: Source file for RequestManager feature.
*/

//TODO: REMOVE
#include <iostream>

#include "RequestManager.hpp"

using namespace BabelServer;

bool RequestManager::manage(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::AResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
)
{
    // TODO: Remove
    std::cout << "MANAGE response with code" << response->getCode() << std::endl;
    switch (response->getResponseType()) {
        case BabelNetwork::AResponse::User:
            manageUser(clientSocket, std::dynamic_pointer_cast<BabelNetwork::UserResponse> (response), clientList, database);
            return true;
        case BabelNetwork::AResponse::Call:
            manageCall(clientSocket, std::dynamic_pointer_cast<BabelNetwork::CallResponse> (response), clientList, database);
            return true;
        case BabelNetwork::AResponse::Friend:
            manageFriend(clientSocket, std::dynamic_pointer_cast<BabelNetwork::FriendResponse> (response), clientList, database);
            return true;
        case BabelNetwork::AResponse::Message:
            manageMessage(dynamic_cast<BabelNetwork::MessageResponse &>(*response));
            return true;
        case BabelNetwork::AResponse::UnknownType:
            break;
    }
    return false;
}

void RequestManager::manageUser(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::UserResponse> &response,
    const BabelNetwork::ClientList &clientList,
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
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::CallResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
    )
{
    auto code = response->getCode();
    auto callTabPtr = _callManager.getCallResponsePtrTab();

    for (const auto &ptr : callTabPtr) {
        if (std::get<0>(ptr) == code)
            return std::get<1>(ptr)(&_callManager, clientSocket, response, clientList, database);
    }
}

void RequestManager::manageFriend(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::FriendResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
)
{
    auto code = response->getCode();
    auto friendTabPtr = _friendManager.getFriendResponsePtrTab();

    for (const auto &ptr : friendTabPtr) {
        if (std::get<0>(ptr) == code)
            return std::get<1>(ptr)(&_friendManager, clientSocket, response, clientList, database);
    }
}

void RequestManager::manageMessage(const BabelNetwork::MessageResponse &response)
{
    (void)response;
}
