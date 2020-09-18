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
#include <tuple>

#include "ClientSocket.hpp"

#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

#include "Database.hpp"
#include "UserManager.hpp"

namespace BabelServer {
    class RequestManager {

        /* <- Constructor - Destructor -> */
    public:
        explicit RequestManager(BabelUtils::Logger& logger): _logger(logger), _userManager(logger){};

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
            const BabelNetwork::CallResponse &response
        );

        void manageFriend(
            const BabelNetwork::FriendResponse &response
        );

        void manageMessage(
            const BabelNetwork::MessageResponse &response
        );

        /* <- Attributes -> */
    private:
        BabelUtils::Logger & _logger;
        const UserManager _userManager;
//        const std::vector<AResponseTuple> AResponsePtrTab = {
//            (BabelNetwork::AResponse::ResponseType, ),
//
//        };
//        const std::vector<std::function<UserResponseProt >> UserResponsePtrTab = {
//        };
//        const std::vector<std::function<CallResponseProt >> CallResponsePtrTab = {
//        };
//        const std::vector<std::function<FriendResponseProt >> FriendResponsePtrTab = {
//        };
//        const std::vector<std::function<MessageResponseProt >> MessageResponsePtrTab = {
//        };
    };
}

#endif //CPP_BABEL_2020_REQUESTMANAGER_HPP
