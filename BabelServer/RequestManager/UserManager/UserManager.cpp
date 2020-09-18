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
    const BabelNetwork::UserResponse &response,
    __attribute__((unused))const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    std::cout << "Create Account" << std::endl;
    database.createUser(response.getLogin(), response.getPassword());
}

//void BabelServer::UserManager::createAccount(int lol)
//{
//    (void)lol;
//}
