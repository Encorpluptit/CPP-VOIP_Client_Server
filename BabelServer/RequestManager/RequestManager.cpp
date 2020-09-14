/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [RequestManager.cpp]: Source file for RequestManager feature.
*/

#include "RequestManager.hpp"

using namespace BabelServer;

bool RequestManager::manage(std::shared_ptr<BabelNetwork::AResponse>)
{
    return false;
}

bool RequestManager::manageUser(std::shared_ptr<BabelNetwork::UserResponse>)
{
    return false;
}

bool RequestManager::manageCall(std::shared_ptr<BabelNetwork::CallResponse>)
{
    return false;
}

bool RequestManager::manageFriend(std::shared_ptr<BabelNetwork::FriendResponse>)
{
    return false;
}

bool RequestManager::manageMessage(std::shared_ptr<BabelNetwork::MessageResponse>)
{
    return false;
}
