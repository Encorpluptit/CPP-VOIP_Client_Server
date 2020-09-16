/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [RequestManager.cpp]: Source file for RequestManager feature.
*/

#include "RequestManager.hpp"

using namespace BabelServer;

bool RequestManager::manage(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    switch (response->getResponseType()) {
        case BabelNetwork::AResponse::User:
            return manageUser(reinterpret_cast<const std::shared_ptr<BabelNetwork::UserResponse>&>(response));
        case BabelNetwork::AResponse::Call:
            return manageCall(reinterpret_cast<const std::shared_ptr<BabelNetwork::CallResponse>&>(response));
        case BabelNetwork::AResponse::Friend:
            return manageFriend(reinterpret_cast<const std::shared_ptr<BabelNetwork::FriendResponse>&>(response));
        case BabelNetwork::AResponse::Message:
            return manageMessage(reinterpret_cast<const std::shared_ptr<BabelNetwork::MessageResponse>&>(response));
        case BabelNetwork::AResponse::UnknownType:
            break;
    }
    return false;
}

bool RequestManager::manageUser(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    return false;
}

bool RequestManager::manageCall(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    return false;
}

bool RequestManager::manageFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    return false;
}

bool RequestManager::manageMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    return false;
}
