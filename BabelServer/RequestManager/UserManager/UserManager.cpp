//
// Created by encorpluptit on 9/16/20.
//

//TODO: REMOVE
#include <iostream>

#include "UserManager.hpp"

using namespace BabelServer;

const std::vector<UserManager::UserResponseTuple> &BabelServer::UserManager::getUserResponsePtrTab() const
{
    return UserResponsePtrTab;
}

void UserManager::createAccount(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::UserResponse> &response,
    __attribute__((unused))const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    // TODO: Log Function
    _logger.logThis(BabelUtils::format("Request for User Creation with login {%s} and password {%s}", response->getLogin(), response->getPassword()));
    database.createUser(response->getLogin(), response->getPassword());
}

//void BabelServer::UserManager::createAccount(int lol)
//{
//    (void)lol;
//}
