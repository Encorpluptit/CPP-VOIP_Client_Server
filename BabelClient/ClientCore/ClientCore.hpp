/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [ClientCore.hpp]: Header file for ClientCore feature.
*/

#ifndef CPP_BABEL_2020_CLIENTCORE_HPP
#define CPP_BABEL_2020_CLIENTCORE_HPP

#include <QApplication>

#include "AsioClientSocket.hpp"
#include "AResponse.hpp"
#include "boost/shared_ptr.hpp"
#include "SharedPtr.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

namespace BabelClient {

    class ClientCore final : virtual public BabelUtils::ARunnable {
        /* <- Constructor - Destructor -> */
    public:
        ClientCore(int ac, char **av);

        ~ClientCore() final;

        /* <- Public Methods -> */
    public:
        void start() final;

        void stop() final;

        void run();

        void checkTypeResponse(std::shared_ptr<BabelNetwork::AResponse> response);
        void doUserResponse(std::shared_ptr<BabelNetwork::AResponse> response);
        void doCallResponse(std::shared_ptr<BabelNetwork::AResponse> response);
        void doFriendResponse(std::shared_ptr<BabelNetwork::AResponse> response);
        void doMessageResponse(std::shared_ptr<BabelNetwork::AResponse> response);
        void doUnknowTypeResponse(std::shared_ptr<BabelNetwork::AResponse> response);

        void LoggedIn(std::shared_ptr<BabelNetwork::UserResponse> response);
        void LoggedOut(std::shared_ptr<BabelNetwork::UserResponse> response);
        void AccountCreate(std::shared_ptr<BabelNetwork::UserResponse> response);
        void AccountDelete(std::shared_ptr<BabelNetwork::UserResponse> response);
        void UnknowUserError(std::shared_ptr<BabelNetwork::UserResponse> response);
        void WrongLogin(std::shared_ptr<BabelNetwork::UserResponse> response);
        void WrongPassword(std::shared_ptr<BabelNetwork::UserResponse> response);
        void LoginAlreadyTaken(std::shared_ptr<BabelNetwork::UserResponse> response);
        void AlreadyLoggedIn(std::shared_ptr<BabelNetwork::UserResponse> response);

        void CallStarted(std::shared_ptr<BabelNetwork::CallResponse> response);
        void CallLeft(std::shared_ptr<BabelNetwork::CallResponse> response);
        void IncomingCall(std::shared_ptr<BabelNetwork::CallResponse> response);
        void CallAccepted(std::shared_ptr<BabelNetwork::CallResponse> response);
        void CallRefused(std::shared_ptr<BabelNetwork::CallResponse> response);
        void UserDisconnected(std::shared_ptr<BabelNetwork::CallResponse> response);

        void AddFriend(std::shared_ptr<BabelNetwork::FriendResponse> response);
        void FriendRequest(std::shared_ptr<BabelNetwork::FriendResponse> response);
        void UnknowUser(std::shared_ptr<BabelNetwork::FriendResponse> response);

        void SendMessageOk(std::shared_ptr<BabelNetwork::MessageResponse> response);
        void ReceiveMessage(std::shared_ptr<BabelNetwork::MessageResponse> response);
        void UnknowUserMessage(std::shared_ptr<BabelNetwork::MessageResponse> response);

        /* <- Private Methods -> */
    private:
//        void init();

        void initSocket(char **av);

        /* <- Getters / Setters -> */
    public:
        BabelUtils::Logger _logger;
        BabelUtils::SharedPtr<BabelNetwork::ClientSocket> _socket;
    
    private:
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::AResponse>)>> dispatch_ptr = {&BabelClient::ClientCore::doUnknowTypeResponse, &BabelClient::ClientCore::doUserResponse, &BabelClient::ClientCore::doCallResponse, &BabelClient::ClientCore::doFriendResponse, &BabelClient::ClientCore::doMessageResponse};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::UserResponse>)>> user_ptr = {&BabelClient::ClientCore::LoggedIn, &BabelClient::ClientCore::LoggedOut, &BabelClient::ClientCore::AccountCreate, &BabelClient::ClientCore::AccountDelete, &BabelClient::ClientCore::WrongLogin, &BabelClient::ClientCore::WrongPassword, &BabelClient::ClientCore::LoginAlreadyTaken, &BabelClient::ClientCore::AlreadyLoggedIn};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::CallResponse>)>> call_ptr = {&BabelClient::ClientCore::CallStarted, &BabelClient::ClientCore::CallLeft, &BabelClient::ClientCore::IncomingCall, &BabelClient::ClientCore::CallAccepted, &BabelClient::ClientCore::CallRefused, &BabelClient::ClientCore::IncomingCall};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::FriendResponse>)>> friend_ptr = {&BabelClient::ClientCore::AddFriend, &BabelClient::ClientCore::FriendRequest, &BabelClient::ClientCore::UnknowUser};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::MessageResponse>)>> message_ptr = {&BabelClient::ClientCore::SendMessageOk, &BabelClient::ClientCore::ReceiveMessage, &BabelClient::ClientCore::UnknowUserMessage};
        bool logged;
        std::string name;
        std::vector<int> userCodeIdx = {100, 102, 110, 112, 113, 170, 171, 172, 173, 174};
        std::vector<int> callCodeIdx = {200, 202, 204, 205, 270, 271};
        std::vector<int> friendCodeIdx = {301, 302, 350};
        std::vector<int> messageCodeIdx = {402, 403, 450};
        QApplication _app;
    };

}

#endif /* CPP_BABEL_2020_CLIENTCORE_HPP */
