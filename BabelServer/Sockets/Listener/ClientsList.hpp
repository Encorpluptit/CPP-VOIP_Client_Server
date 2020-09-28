//
// Created by encorpluptit on 9/28/20.
//

#ifndef CPP_BABEL_2020_CLIENTLIST_HPP
#define CPP_BABEL_2020_CLIENTLIST_HPP

#include <mutex>
#include "ClientSocket.hpp"
#include "SharedPtr.hpp"

namespace BabelServer {
    class ClientsList {
    public:
        ClientsList() = default;

        ~ClientsList() = default;

    public:
        void add_client(const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client)
        {
            _clients.emplace_back(client);
        };

        void remove_client(const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client)
        {
            std::remove(_clients.begin(), _clients.end(), client);
        };

        [[nodiscard]] const std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> &getClients() const
        {
            return _clients;
        }

    protected:
        std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> _clients;
    };
};

#endif //CPP_BABEL_2020_CLIENTLIST_HPP
