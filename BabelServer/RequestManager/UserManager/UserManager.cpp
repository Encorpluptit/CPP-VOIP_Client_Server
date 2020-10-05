//
// Created by encorpluptit on 9/16/20.
//

#include "Debug.hpp"
#include "Models.hpp"
#include "UserManager.hpp"
#include "FriendResponse.hpp"
#include "DatabaseError.hpp"

using namespace BabelServer;
using namespace BabelNetwork;

const std::vector<UserManager::UserManagerFPtr> &BabelServer::UserManager::getUserResponsePtrTab() const
{
    return UserResponsePtrTab;
}

void UserManager::createAccount(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    #ifndef _WIN32
    __attribute__((unused))
    #endif
    const ClientList &clientList,
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
    for (const auto &client : clientList) {
        if (client->getUser() && client->getUser()->login == response->getLogin()) {
            clientSocket->sendResponse(UserResponse::AlreadyLog(response->getLogin()));
            return;
        }
    }
    auto user = database.getUser(response->getLogin());
    if (!user) {
        clientSocket->sendResponse(UserResponse::BadLogin(response->getLogin()));
        return;
    }
    if (response->getPassword() != user->password) {
        clientSocket->sendResponse(UserResponse::BadPassword(response->getLogin()));
        return;
    }
    clientSocket->setUser(user);
    clientSocket->sendResponse(UserResponse::LoggedInOk(response->getLogin()));

    auto friends = database.getFriendships(response->getLogin());
    for (const auto &client: clientList) {
        auto target = client->getUser();
        if (!target || target == user)
            continue;
        for (const auto &friendship : friends) {
            if (friendship.user1ID == target->id || friendship.user2ID == target->id) {
                clientSocket->sendResponse(FriendResponse::AddFriend(response->getLogin(), target->login));
                client->sendResponse(FriendResponse::AddFriend(target->login, response->getLogin()));
            }
        }
    }
}

void UserManager::Logout(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    #ifndef _WIN32
    __attribute__((unused))
    #endif
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
    clientSocket->sendResponse(UserResponse::LoggedOutOk(user->login));
    auto friendships = database.getFriendships(user->login);
    for (const auto &client: clientList) {
        auto target = client->getUser();
        if (!target || target == user)
            continue;
        for (const auto &friendship : friendships) {
            if (friendship.user1ID == target->id || friendship.user2ID == target->id) {
                client->sendResponse(FriendResponse::DeleteFriendOK(target->login, response->getLogin()));
            }
        }
    }
}

void UserManager::DeleteAccount(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<UserResponse> &response,
    #ifndef _WIN32
    __attribute__((unused))
    #endif
    const ClientList &clientList,
    Database &database
) const
{
    std::string log(BabelUtils::format(
        "Request for Delete Account with login {%s} and password {%s}",
        response->getLogin(), response->getPassword())
    );
    //TODO: Check if user requesting account deletion is logged and the owner
    dbg("%s\n", log.c_str());
    _logger.logThis(log);
    auto friendships = database.getFriendships(clientSocket->getUser()->id);

    switch (database.deleteUser(response->getLogin())) {
        case UserResponse::RequestedAccountDeleted:
            clientSocket->sendResponse(UserResponse::RequestedDeletedAccount(response->getLogin()));
            return;
        case UserResponse::AccountDeleted:
            clientSocket->setUser(nullptr);
            clientSocket->sendResponse(UserResponse::AccountDeletedOk(response->getLogin()));
            for (const auto &client: clientList) {
                auto target = client->getUser();
                if (!target || target->login == response->getLogin())
                    continue;
                for (const auto &friendship : friendships) {
                    if (friendship.user1ID == target->id || friendship.user2ID == target->id) {
                        client->sendResponse(FriendResponse::DeleteFriendOK(target->login, response->getLogin()));
                    }
                }
            }
            return;
        default:
            clientSocket->sendResponse(UserResponse::UnknownError(response->getLogin()));
            return;
    }
}
