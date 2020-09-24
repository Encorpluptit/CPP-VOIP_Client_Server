//
// Created by encorpluptit on 9/16/20.
//

#include "Debug.hpp"
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
    std::string login = response->getLogin();
    std::string log(BabelUtils::format(
        "Request for User Creation with login {%s} and password {%s}",
        response->getLogin(), response->getPassword())
    );
    dbg("%s\n", log.c_str());
    _logger.logThis(log);
    //TODO: Hash Password ?
    if (database.createUser(login, response->getPassword()) < 0) {
        clientSocket->sendResponse(BabelNetwork::UserResponse::LoginUse(login));
        return;
    }
    clientSocket->sendResponse(BabelNetwork::UserResponse::AccountCreatedOk(login));
}

void UserManager::Login(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::UserResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    std::string log(BabelUtils::format(
        "Request for Login User with login {%s} and password {%s}",
        response->getLogin(), response->getPassword())
    );
    dbg("%s\n", log.c_str());
    _logger.logThis(log);
    // TODO: Add Already Logged in Management
    auto user = database.getUser(response->getLogin());
    if (!user) {
        clientSocket->sendResponse(BabelNetwork::UserResponse::BadLogin(response->getLogin()));
        return;
    }
    //TODO: UnHash Password ?
    std::cout << "RESPONSE : " << response->getPassword() << "USER : " << user->password << std::endl;
    if (response->getPassword() != user->password) {
        clientSocket->sendResponse(BabelNetwork::UserResponse::BadPassword(response->getLogin()));
        return;
    }
    clientSocket->sendResponse(BabelNetwork::UserResponse::LoggedInOk(response->getLogin()));
    //TODO: Send "Friend connected" to friend list.
}

//void BabelServer::UserManager::createAccount(int lol)
//{
//    (void)lol;
//}
