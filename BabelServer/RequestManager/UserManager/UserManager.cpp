//
// Created by encorpluptit on 9/16/20.
//

#include "Debug.hpp"
#include "Models.hpp"
#include "UserManager.hpp"
#include "FriendResponse.hpp"

using namespace BabelServer;
using namespace BabelNetwork;

const std::vector<UserManager::UserManagerFPtr> &BabelServer::UserManager::getUserResponsePtrTab() const
{
    return UserResponsePtrTab;
}

void UserManager::createAccount(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    __attribute__((unused))const ClientList &clientList,
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
        case UserResponse::LoginAlreadyTaken:
            clientSocket->sendResponse(UserResponse::LoginAlreadyUsed(login));
            return;
        case UserResponse::AccountCreated:
            clientSocket->sendResponse(UserResponse::AccountCreatedOk(login));
            return;
        default:
            clientSocket->sendResponse(UserResponse::UnknownError(login));
            return;
    }
}

void UserManager::Login(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    const ClientList &clientList,
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
        clientSocket->sendResponse(UserResponse::AlreadyLog(response->getLogin()));
        return;
    }
    auto user = database.getUser(response->getLogin());
    if (!user) {
        clientSocket->sendResponse(UserResponse::BadLogin(response->getLogin()));
        return;
    }
    //TODO: UnHash Password ?
    std::cout << "RESPONSE : " << response->getPassword() << "USER : " << user->password << std::endl;
    if (response->getPassword() != user->password) {
        clientSocket->sendResponse(UserResponse::BadPassword(response->getLogin()));
        return;
    }
    clientSocket->setUser(user);
    clientSocket->sendResponse(UserResponse::LoggedInOk(response->getLogin()));
    for (const auto &client: clientList) {
        if (client->getUser())
            clientSocket->sendResponse(FriendResponse::FriendRequestAccepted(response->getLogin(), user->login));
    }
    //TODO: Send "Friend connected" to friend list.
}

void UserManager::Logout(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    const ClientList &clientList,
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
    if (!clientSocket->getUser()) {
        clientSocket->sendResponse(UserResponse::ClientNotLogged());
        return;
    }
    auto user = database.getUser(response->getLogin());
    if (!user) {
        clientSocket->sendResponse(UserResponse::RequestedDeletedAccount(response->getLogin()));
        return;
    }
    //TODO: UnHash Password ?
    clientSocket->setUser(nullptr);
    clientSocket->sendResponse(UserResponse::LoggedOutOk(response->getLogin()));
    //TODO: Send "Friend disconnected" to friend list.
}

void UserManager::DeleteAccount(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    const ClientList &clientList,
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
        case UserResponse::RequestedAccountDeleted:
            clientSocket->sendResponse(UserResponse::RequestedDeletedAccount(login));
            return;
        case UserResponse::AccountDeleted:
            clientSocket->sendResponse(UserResponse::AccountDeletedOk(login));
            return;
        default:
            clientSocket->sendResponse(UserResponse::UnknownError(login));
            return;
    }
    //TODO: Send "Delete Friend" to friend list.
}
