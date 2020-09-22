//
// Created by encorpluptit on 9/16/20.
//

#ifndef CPP_BABEL_2020_USERMANAGER_HPP
#define CPP_BABEL_2020_USERMANAGER_HPP

#include "Listener.hpp"
#include "Logger.hpp"
#include "UserResponse.hpp"
#include "Database.hpp"

namespace BabelServer {

    class UserManager {
        using UserManagerMethodProt = void(
            const UserManager *,
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &,
            const BabelNetwork::ClientList &,
            BabelServer::Database &
        );
        using UserManagerFPtr = std::tuple<BabelNetwork::UserResponse::ResponseCode, std::function<UserManagerMethodProt>>;

        /* <- Constructor - Destructor -> */
    public:
        explicit UserManager(BabelUtils::Logger &logger) : _logger(logger) {};

        ~UserManager() = default;

        /* <- Public Methods -> */
    private:
        void createAccount(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        void Login(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        void Logout(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        void DeleteAccount(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &response,
            const BabelNetwork::ClientList &clientList,
            Database &database
        ) const;

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const std::vector<UserManagerFPtr> &getUserResponsePtrTab() const;


        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        const std::vector<std::tuple<BabelNetwork::UserResponse::ResponseCode, std::function<UserManagerMethodProt>>> UserResponsePtrTab = {
            {BabelNetwork::UserResponse::ResponseCode::RequestAccountCreation, &UserManager::createAccount},
            {BabelNetwork::UserResponse::ResponseCode::RequestLogin,           &UserManager::Login},
            {BabelNetwork::UserResponse::ResponseCode::RequestAccountDeletion, &UserManager::DeleteAccount},
        };


    };

}

#endif //CPP_BABEL_2020_USERMANAGER_HPP
