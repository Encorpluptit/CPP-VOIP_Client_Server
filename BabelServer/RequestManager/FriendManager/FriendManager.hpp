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
//        void createAccount(
//            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
//            const std::shared_ptr<BabelNetwork::UserResponse> &response,
//            const BabelNetwork::ClientList &clientList,
//            Database &database
//        ) const;
//
//        void Login(
//            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
//            const std::shared_ptr<BabelNetwork::UserResponse> &response,
//            const BabelNetwork::ClientList &clientList,
//            Database &database
//        ) const;
//
//        void DeleteAccount(
//            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
//            const std::shared_ptr<BabelNetwork::UserResponse> &response,
//            const BabelNetwork::ClientList &clientList,
//            Database &database
//        ) const;

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const std::vector<FriendResponseFPtr> &getFriendResponsePtrTab() const;


        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        const std::vector<std::tuple<BabelNetwork::FriendResponse::ResponseCode, std::function<FriendManagerMethodProt>>> FriendResponsePtrTab = {
            {BabelNetwork::FriendResponse::ResponseCode::RequestAddFriend, nullptr},
            {BabelNetwork::FriendResponse::ResponseCode::AddFriend,        nullptr},
        };


    };
}

#endif //CPP_BABEL_2020_FRIENDMANAGER_HPP
