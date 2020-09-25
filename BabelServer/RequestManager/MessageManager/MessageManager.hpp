//
// Created by hobbit on 9/25/20.
//

#ifndef CPP_BABEL_2020_MESSAGEMANAGER_HPP
#define CPP_BABEL_2020_MESSAGEMANAGER_HPP

#include "Listener.hpp"
#include "Logger.hpp"
#include "MessageResponse.hpp"
#include "Database.hpp"

namespace BabelServer {

    class MessageManager {
        using MessageManagerMethodProt = void(
            const MessageManager *,
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::MessageResponse> &,
            const BabelNetwork::ClientList &,
            BabelServer::Database &
        );
        using MessageResponseFPtr = std::tuple<BabelNetwork::MessageResponse::ResponseCode, std::function<MessageManagerMethodProt>>;

        /* <- Constructor - Destructor -> */
    public:
        explicit MessageManager(BabelUtils::Logger &logger) : _logger(logger) {};

        ~MessageManager() = default;

        /* <- Public Methods -> */
    private:
        void sendMessage(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::MessageResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const std::vector<MessageResponseFPtr> &getMessageResponsePtrTab() const {return MessageResponsePtrTab;};

        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        uint16_t _call_id = 0;
        const std::vector<std::tuple<BabelNetwork::MessageResponse::ResponseCode, std::function<MessageManagerMethodProt>>> MessageResponsePtrTab = {
            {BabelNetwork::MessageResponse::ResponseCode::RequestSendMessage,  &MessageManager::sendMessage},
//            {BabelNetwork::FriendResponse::ResponseCode::AddFriend, nullptr},
        };

    };

}

#endif //CPP_BABEL_2020_MESSAGEMANAGER_HPP
