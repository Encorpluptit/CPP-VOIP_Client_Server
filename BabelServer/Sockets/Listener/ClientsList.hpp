//
// Created by encorpluptit on 9/28/20.
//

#ifndef CPP_BABEL_2020_CLIENTLIST_HPP
#define CPP_BABEL_2020_CLIENTLIST_HPP

#include <mutex>
#include "ClientSocket.hpp"
#include "SharedPtr.hpp"

namespace BabelServer {
//    class ClientsList : virtual public std::mutex {
    class ClientsList {
    public:
        ClientsList() = default;

        ~ClientsList() = default;

    public:
//        virtual void add_client(BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client) = 0;
//
//        virtual void remove_client(BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client) = 0;
        void add_client(const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client)
        {
//            lock();
            _clients.emplace_back(client);
//            unlock();
        };

        void remove_client(const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client)
        {
//            lock();
            std::remove(_clients.begin(), _clients.end(), client);
//            unlock();
        };

        [[nodiscard]] std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> getClients() const
        {
            return _clients;
        }

    protected:
        std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> _clients;
    };
};

#endif //CPP_BABEL_2020_CLIENTLIST_HPP
