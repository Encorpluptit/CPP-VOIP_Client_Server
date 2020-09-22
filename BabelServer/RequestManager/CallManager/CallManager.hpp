//
// Created by encorpluptit on 9/21/20.
//

#ifndef CPP_BABEL_2020_CALLMANAGER_HPP
#define CPP_BABEL_2020_CALLMANAGER_HPP

#include "Listener.hpp"
#include "Logger.hpp"
#include "CallResponse.hpp"
#include "Database.hpp"

namespace BabelServer {

    class CallManager {
        using CallManagerMethodProt = void(
            const CallManager *,
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &,
            const BabelNetwork::ClientList &,
            BabelServer::Database &
        );
        using CallResponseFPtr = std::tuple<BabelNetwork::CallResponse::ResponseCode, std::function<CallManagerMethodProt>>;

        /* <- Constructor - Destructor -> */
    public:
        explicit CallManager(BabelUtils::Logger &logger) : _logger(logger) {};

        ~CallManager() = default;

        /* <- Public Methods -> */
    private:
//        void requestCall(
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
        [[nodiscard]] const std::vector<CallResponseFPtr> &getCallResponsePtrTab() const;


        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        const std::vector<std::tuple<BabelNetwork::CallResponse::ResponseCode, std::function<CallManagerMethodProt>>> CallResponsePtrTab = {
            {BabelNetwork::CallResponse::ResponseCode::RequestCall, nullptr},
            {BabelNetwork::CallResponse::ResponseCode::CallRefused, nullptr},
            {BabelNetwork::CallResponse::ResponseCode::CallAccepted, nullptr},
//            {BabelNetwork::FriendResponse::ResponseCode::AddFriend, nullptr},
        };

    };

}
#endif //CPP_BABEL_2020_CALLMANAGER_HPP
