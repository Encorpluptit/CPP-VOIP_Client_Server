/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [ClientCore.hpp]: Header file for ClientCore feature.
*/

#ifndef CPP_BABEL_2020_CLIENTCORE_HPP
#define CPP_BABEL_2020_CLIENTCORE_HPP

#include "NetworkError.hpp"
#include "AsioClientSocket.hpp"
#include "AResponse.hpp"
#include "boost/shared_ptr.hpp"
#include "SharedPtr.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"
#include "QtSocket.hpp"
#include "IGraphics.hpp"
#include "Application.hpp"

namespace BabelClient {

    class ClientCore {
            /* <- Constructor - Destructor -> */
        public:
            ClientCore(int ac, char **av);

            ~ClientCore();

            void initSocket(const std::string &ip, int port);
            int init() {
                return (0);
            }
            void loop();

            /* <- Public Methods -> */
        public:
            void checkTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
            void doUserResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
            void doCallResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
            void doFriendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
            void doMessageResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
            void doUnknowTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);

            void LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void WrongLogin(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void WrongPassword(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void LoginAlreadyTaken(const std::shared_ptr<BabelNetwork::UserResponse> &response);
            void AlreadyLoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response);

            void CallStarted(const std::shared_ptr<BabelNetwork::CallResponse> &response);
            void CallLeft(const std::shared_ptr<BabelNetwork::CallResponse> &response);
            void IncomingCall(const std::shared_ptr<BabelNetwork::CallResponse> &response);
            void CallAccepted(const std::shared_ptr<BabelNetwork::CallResponse> &response);
            void CallRefused(const std::shared_ptr<BabelNetwork::CallResponse> &response);
            void UserDisconnected(const std::shared_ptr<BabelNetwork::CallResponse> &response);

            void AddFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response);
            void FriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response);
            void UnknowUser(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

            void SendMessageOk(const std::shared_ptr<BabelNetwork::MessageResponse> &response);
            void ReceiveMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response);
            void UnknowUserMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response);

            /* <- Public Attributs -> */
        public:
            ISocket *socket;
            IGraphics *gui;
            IGraphics *appli;

            /* <- Getters / Setters -> */
        public:
            BabelUtils::Logger _logger;

        private:
            std::vector<std::function<void(ClientCore*, const std::shared_ptr<BabelNetwork::AResponse> &)>> dispatch_ptr = {&BabelClient::ClientCore::doUnknowTypeResponse, &BabelClient::ClientCore::doUserResponse, &BabelClient::ClientCore::doCallResponse, &BabelClient::ClientCore::doFriendResponse, &BabelClient::ClientCore::doMessageResponse};
            std::vector<std::function<void(ClientCore*, const std::shared_ptr<BabelNetwork::UserResponse> &)>> user_ptr = {&BabelClient::ClientCore::LoggedIn, &BabelClient::ClientCore::LoggedOut, &BabelClient::ClientCore::AccountCreate, &BabelClient::ClientCore::AccountDelete, &BabelClient::ClientCore::WrongLogin, &BabelClient::ClientCore::WrongPassword, &BabelClient::ClientCore::LoginAlreadyTaken, &BabelClient::ClientCore::AlreadyLoggedIn};
            std::vector<std::function<void(ClientCore*, const std::shared_ptr<BabelNetwork::CallResponse> &)>> call_ptr = {&BabelClient::ClientCore::CallStarted, &BabelClient::ClientCore::CallLeft, &BabelClient::ClientCore::IncomingCall, &BabelClient::ClientCore::CallAccepted, &BabelClient::ClientCore::CallRefused, &BabelClient::ClientCore::IncomingCall};
            std::vector<std::function<void(ClientCore*, const std::shared_ptr<BabelNetwork::FriendResponse> &)>> friend_ptr = {&BabelClient::ClientCore::AddFriend, &BabelClient::ClientCore::FriendRequest, &BabelClient::ClientCore::UnknowUser};
            std::vector<std::function<void(ClientCore*, const std::shared_ptr<BabelNetwork::MessageResponse> &)>> message_ptr = {&BabelClient::ClientCore::SendMessageOk, &BabelClient::ClientCore::ReceiveMessage, &BabelClient::ClientCore::UnknowUserMessage};
            std::vector<int> userCodeIdx = {100, 102, 110, 112, 113, 170, 171, 172, 173, 174};
            std::vector<int> callCodeIdx = {200, 202, 204, 205, 270, 271};
            std::vector<int> friendCodeIdx = {301, 302, 350};
            std::vector<int> messageCodeIdx = {402, 403, 450};
    };

}

#endif /* CPP_BABEL_2020_CLIENTCORE_HPP */
