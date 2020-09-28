//
// Created by encorpluptit on 9/16/20.
//

#include "Debug.hpp"
#include "Models.hpp"
#include "UserManager.hpp"

using namespace BabelServer;

const std::vector<UserManager::UserManagerFPtr> &BabelServer::UserManager::getUserResponsePtrTab() const
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
    auto login = response->getLogin();
    auto log = BabelUtils::format(
        "Request for User Creation with login {%s} and password {%s}",
        response->getLogin(), response->getPassword()
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
    if (clientSocket->getUser()) {
        clientSocket->sendResponse(BabelNetwork::UserResponse::AlreadyLog(response->getLogin()));
        return;
    }
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
    clientSocket->setUser(user);
    clientSocket->sendResponse(BabelNetwork::UserResponse::LoggedInOk(response->getLogin()));
    //TODO: Send "Friend connected" to friend list.
}

void UserManager::Logout(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::UserResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    std::string log(BabelUtils::format(
        "Request for Logout User with login {%s} and password {%s}",
        response->getLogin(), response->getPassword())
    );
    dbg("%s\n", log.c_str());
    _logger.logThis(log);
    // TODO: Add Already Logged out Management
    auto user = database.getUser(response->getLogin());
    if (!user) {
        clientSocket->sendResponse(BabelNetwork::UserResponse::RequestedDeletedAccount(response->getLogin()));
        return;
    }
    //TODO: UnHash Password ?
    clientSocket->setUser(nullptr);
    clientSocket->sendResponse(BabelNetwork::UserResponse::LoggedOutOk(response->getLogin()));
    //TODO: Send "Friend disconnected" to friend list.
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
