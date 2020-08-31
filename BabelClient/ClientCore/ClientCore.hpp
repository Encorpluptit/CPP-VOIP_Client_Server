/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [ClientCore.hpp]: Header file for ClientCore feature.
*/

#ifndef CPP_BABEL_2020_CLIENTCORE_HPP
#define CPP_BABEL_2020_CLIENTCORE_HPP

#include "AsioClientSocket.hpp"
#include "AResponse.hpp"
#include "boost/shared_ptr.hpp"
#include "SharedPtr.hpp"

namespace BabelClient {

    class ClientCore final : virtual public BabelUtils::ARunnable {
        /* <- Constructor - Destructor -> */
    public:
        ClientCore(char **av);

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

        /* <- Private Methods -> */
    private:
        void init();

        void initSocket(char **av);

        /* <- Getters / Setters -> */
    public:
        BabelUtils::Logger _logger;
        BabelUtils::SharedPtr<BabelNetwork::ClientSocket> _socket;
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::AResponse>)>> dispatch_ptr = {&BabelClient::ClientCore::doUnknowTypeResponse, &BabelClient::ClientCore::doUserResponse, &BabelClient::ClientCore::doCallResponse, &BabelClient::ClientCore::doFriendResponse, &BabelClient::ClientCore::doMessageResponse};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::AResponse>)>> user_ptr = {};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::AResponse>)>> call_ptr = {};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::AResponse>)>> friend_ptr = {};
        std::vector<std::function<void(ClientCore*, std::shared_ptr<BabelNetwork::AResponse>)>> message_ptr = {};
    };

}

#endif /* CPP_BABEL_2020_CLIENTCORE_HPP */
