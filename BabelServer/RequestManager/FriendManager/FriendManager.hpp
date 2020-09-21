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
        using UserManagerMethodProt = void(
            const FriendManager *,
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::UserResponse> &,
            const BabelNetwork::ClientList &,
            BabelServer::Database &
        );
        using UserResponseTuple = std::tuple<BabelNetwork::UserResponse::ResponseCode, std::function<UserManagerMethodProt>>;

    };
}

#endif //CPP_BABEL_2020_FRIENDMANAGER_HPP
