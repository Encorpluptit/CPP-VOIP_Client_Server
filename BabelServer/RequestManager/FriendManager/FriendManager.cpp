//
// Created by encorpluptit on 9/21/20.
//

#include "FriendManager.hpp"

using namespace BabelServer;
using namespace BabelNetwork;

const std::vector<FriendManager::FriendResponseFPtr> &FriendManager::getFriendResponsePtrTab() const
{
    return FriendResponsePtrTab;
}

void FriendManager::acceptFriendship(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<FriendResponse> &response,
    const ClientList &clientList,
    Database &database
) const
{
    switch (database.createFriendship(response->getLogin(), response->getFriendLogin())) {
        case FriendResponse::UnknownUser:
            clientSocket->sendResponse(FriendResponse::UserNotExist(response));
            return;
        case FriendResponse::FriendAdded:
            for (const auto &client : clientList) {
                auto user = client->getUser();
                if (!user || user->login != response->getFriendLogin())
                    continue;
                client->sendResponse(FriendResponse::AddFriend(user->login, response->getLogin()));
                break;
            }
            clientSocket->sendResponse(FriendResponse::AddFriend(response->getLogin(), response->getFriendLogin()));
            return;
        default:
            clientSocket->sendResponse(FriendResponse::UnknownErrorOccured(response));
            return;
    }
}

void FriendManager::friendshipRequest(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<FriendResponse> &response,
    const ClientList &clientList,
    #ifndef _WIN32
    __attribute__((unused))
    #endif
    Database &database
) const
{
    auto friendships = database.getFriendships(clientSocket->getUser()->login);

    for (const auto &client : clientList) {
        auto user = client->getUser();
        if (!user || user->login != response->getFriendLogin())
            continue;
        for (const auto &friendship : friendships) {
            if (user->id == friendship.id) {
                clientSocket->sendResponse(FriendResponse::FriendshipExist(response));
                return;
            }
        }
        std::cout << response->getLogin() << "|" << response->getFriendLogin() << std::endl;
//        client->sendResponse(FriendResponse::NewFriendRequest(response));
        client->sendResponse(FriendResponse::NewFriendRequest(response->getFriendLogin(), response->getLogin()));
        return;
    }
    clientSocket->sendResponse(FriendResponse::UserNotExist(response));
}

void FriendManager::declineFriendship(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<FriendResponse> &response,
    const ClientList &clientList,
    #ifndef _WIN32
    __attribute__((unused))
    #endif
    Database &database
) const
{
    for (const auto &client : clientList) {
        auto user = client->getUser();
        if (!user || user->login != response->getFriendLogin())
            continue;
        client->sendResponse(FriendResponse::FriendRequestDeclined(response));
        return;
    }
    clientSocket->sendResponse(FriendResponse::UserNotExist(response));
}

void FriendManager::deleteFriend(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<FriendResponse> &response,
    const ClientList &clientList,
    Database &database
) const
{
    switch (database.deleteFriendship(response->getLogin(), response->getFriendLogin())) {
        case FriendResponse::FriendDeleted:
            for (const auto &client : clientList) {
                auto user = client->getUser();
                if (user && response->getFriendLogin() == user->login) {
                    client->sendResponse(
                        FriendResponse::DeleteFriendOK(response->getFriendLogin(), response->getLogin()));
                    break;
                }
            }
            clientSocket->sendResponse(FriendResponse::DeleteFriendOK(response));
            return;
        case FriendResponse::FriendshipUnknown:
            clientSocket->sendResponse(FriendResponse::UnknownFriendship(response));
            return;
        case FriendResponse::UnknownUser:
            clientSocket->sendResponse(FriendResponse::UserNotExist(response));
            return;
        default:
            clientSocket->sendResponse(FriendResponse::UnknownErrorOccured(response));
            return;
    }
}
