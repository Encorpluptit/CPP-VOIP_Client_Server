/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [RequestManager.hpp]: Header file for RequestManager feature.
*/

#ifndef CPP_BABEL_2020_REQUESTMANAGER_HPP
#define CPP_BABEL_2020_REQUESTMANAGER_HPP

#include <vector>
#include <functional>

#include "ClientSocket.hpp"

#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

#include "Database.hpp"
#include "UserManager.hpp"
#include "FriendManager.hpp"
#include "CallManager.hpp"
#include "MessageManager.hpp"

namespace BabelServer {
    class RequestManager {

        /* <- Constructor - Destructor -> */
    public:
        explicit RequestManager(BabelUtils::Logger &logger)
            : _logger(logger), _userManager(logger), _callManager(logger),
              _friendManager(logger), _messageManager(logger) {};

        /* <- Public Methods -> */
    public:
        [[nodiscard]] bool manage(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::AResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        );

        /* <- Private Methods -> */
    private:
        void manageUser(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        );

        void manageCall(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        );

        void manageFriend(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::FriendResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        );

        void manageMessage(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::MessageResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        );

        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        const UserManager _userManager;
        CallManager _callManager;
        const FriendManager _friendManager;
        const MessageManager _messageManager;
    };
}

#endif //CPP_BABEL_2020_REQUESTMANAGER_HPP
