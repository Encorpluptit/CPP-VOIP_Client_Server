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
#include "AResponse.hpp"

//#include "


#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

namespace BabelServer {
    class RequestManager {

        using AResponseProt = void(BabelNetwork::ClientSocket*,const std::shared_ptr<BabelNetwork::AResponse> &/*, Database */);

        using UserResponseProt = void(BabelNetwork::ClientSocket*,const std::shared_ptr<BabelNetwork::UserResponse> &/*, Database */);

        using CallResponseProt = void(BabelNetwork::ClientSocket*,const std::shared_ptr<BabelNetwork::CallResponse> &/*, Database */);

        using FriendResponseProt = void(BabelNetwork::ClientSocket*,const std::shared_ptr<BabelNetwork::FriendResponse> &/*, Database */);

        using MessageResponseProt = void(BabelNetwork::ClientSocket*,const std::shared_ptr<BabelNetwork::FriendResponse> &/*, Database */);

        /* <- Constructor - Destructor -> */
    public:
        RequestManager() = default;

        /* <- Public Methods -> */
    public:

        /* <- Private Methods -> */
    private:
        [[nodiscard]] bool manage(std::shared_ptr<BabelNetwork::AResponse>);

        [[nodiscard]] bool manageUser(std::shared_ptr<BabelNetwork::UserResponse>);

        [[nodiscard]] bool manageCall(std::shared_ptr<BabelNetwork::CallResponse>);

        [[nodiscard]] bool manageFriend(std::shared_ptr<BabelNetwork::FriendResponse>);

        [[nodiscard]] bool manageMessage(std::shared_ptr<BabelNetwork::MessageResponse>);

        /* <- Attributes -> */
    private:
        const std::vector<std::function<AResponseProt>> AResponsePtrTab = {
        };
        const std::vector<std::function<UserResponseProt >> UserResponsePtrTab = {
        };
        const std::vector<std::function<CallResponseProt >> CallResponsePtrTab = {
        };
        const std::vector<std::function<FriendResponseProt >> FriendResponsePtrTab = {
        };
        const std::vector<std::function<MessageResponseProt >> MessageResponsePtrTab = {
        };
    };
}

#endif //CPP_BABEL_2020_REQUESTMANAGER_HPP
