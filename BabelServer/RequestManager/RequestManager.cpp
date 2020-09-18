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
            manageCall(dynamic_cast<BabelNetwork::CallResponse &>(*response));
            return true;
        case BabelNetwork::AResponse::Friend:
            manageFriend(dynamic_cast<BabelNetwork::FriendResponse &>(*response));
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

void RequestManager::manageCall(const BabelNetwork::CallResponse &response)
{
    (void)response;
}

void RequestManager::manageFriend(const BabelNetwork::FriendResponse &response)
{
    (void)response;
}

void RequestManager::manageMessage(const BabelNetwork::MessageResponse &response)
{
    (void)response;
}
