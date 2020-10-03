//
// Created by encorpluptit on 9/21/20.
//

#ifndef CPP_BABEL_2020_FRIENDMANAGER_HPP
#define CPP_BABEL_2020_FRIENDMANAGER_HPP

#include "Listener.hpp"
#include "Logger.hpp"
#include "FriendResponse.hpp"
#include "Database.hpp"

namespace BabelServer {

    class FriendManager {
        using FriendManagerMethodProt = void(
            const FriendManager *,
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::FriendResponse> &,
            const BabelNetwork::ClientList &,
            BabelServer::Database &
        );
        using FriendResponseFPtr = std::tuple<BabelNetwork::FriendResponse::ResponseCode, std::function<FriendManagerMethodProt>>;

        /* <- Constructor - Destructor -> */
    public:
        explicit FriendManager(BabelUtils::Logger &logger) : _logger(logger) {};

        ~FriendManager() = default;

        /* <- Public Methods -> */
    private:
        void friendshipRequest(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::FriendResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        void acceptFriendship(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::FriendResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        void declineFriendship(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::FriendResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        void deleteFriend(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::FriendResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const std::vector<FriendResponseFPtr> &getFriendResponsePtrTab() const;


        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        const std::vector<std::tuple<BabelNetwork::FriendResponse::ResponseCode, std::function<FriendManagerMethodProt>>> FriendResponsePtrTab = {
            {BabelNetwork::FriendResponse::ResponseCode::RequestAddFriend,     &FriendManager::friendshipRequest},
            {BabelNetwork::FriendResponse::ResponseCode::AcceptFriendRequest,  &FriendManager::acceptFriendship},
            {BabelNetwork::FriendResponse::ResponseCode::DeclineFriendRequest, &FriendManager::declineFriendship},
            {BabelNetwork::FriendResponse::ResponseCode::RequestDeleteFriend,  &FriendManager::deleteFriend},
        };
    };
}

#endif //CPP_BABEL_2020_FRIENDMANAGER_HPP
