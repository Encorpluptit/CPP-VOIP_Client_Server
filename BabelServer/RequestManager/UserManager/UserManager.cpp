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
    switch (database.createUser(login, response->getPassword())) {
        case BabelNetwork::UserResponse::LoginAlreadyTaken:
            clientSocket->sendResponse(BabelNetwork::UserResponse::LoginAlreadyUsed(login));
            return;
        case BabelNetwork::UserResponse::AccountCreated:
            clientSocket->sendResponse(BabelNetwork::UserResponse::AccountCreatedOk(login));
            return;
        default:
            clientSocket->sendResponse(BabelNetwork::UserResponse::UnknowError(login));
            return;
    }
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
    if (response->getPassword() != user->password) {
        clientSocket->sendResponse(BabelNetwork::UserResponse::BadPassword(response->getLogin()));
        return;
    }
    clientSocket->sendResponse(BabelNetwork::UserResponse::BadPassword(response->getLogin()));
    //TODO: Send "Friend connected" to friend list.
}

void UserManager::DeleteAccount(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::UserResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    std::string login(response->getLogin());
    std::string log(BabelUtils::format(
        "Request for Delete Account with login {%s} and password {%s}",
        response->getLogin(), response->getPassword())
    );
    //TODO: Check if user requesting account deletion is logged and the owner
    dbg("%s\n", log.c_str());
    _logger.logThis(log);
    switch (database.deleteUser(response->getLogin())) {
        case BabelNetwork::UserResponse::RequestedAccountDeleted:
            clientSocket->sendResponse(BabelNetwork::UserResponse::RequestedDeletedAccount(login));
            return;
        case BabelNetwork::UserResponse::AccountDeleted:
            clientSocket->sendResponse(BabelNetwork::UserResponse::AccountDeletedOk(login));
            return;
        default:
            clientSocket->sendResponse(BabelNetwork::UserResponse::UnknowError(login));
            return;
    }
    //TODO: Send "Delete Friend" to friend list.
}
