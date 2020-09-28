//
// Created by encorpluptit on 9/28/20.
//

#ifndef CPP_BABEL_2020_CLIENTLIST_HPP
#define CPP_BABEL_2020_CLIENTLIST_HPP

#include <mutex>
#include "ClientSocket.hpp"
#include "SharedPtr.hpp"

namespace BabelServer {
    class ClientsList : virtual public std::mutex {
    public:
        ClientsList() = default;

        ~ClientsList() = default;

    public:
        virtual void add_client(BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client) = 0;

        virtual void remove_client(BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client) = 0;

        [[nodiscard]] const std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> &getClients() const
        {
            return _clients;
        }

    protected:
        std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> _clients;
    };
};

#endif //CPP_BABEL_2020_CLIENTLIST_HPP
