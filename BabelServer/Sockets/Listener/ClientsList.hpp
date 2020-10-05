//
// Created by encorpluptit on 9/28/20.
//

#ifndef CPP_BABEL_2020_CLIENTLIST_HPP
#define CPP_BABEL_2020_CLIENTLIST_HPP

#include <mutex>
#include "ClientSocket.hpp"
#include "SharedPtr.hpp"

#include <iostream>

namespace BabelServer {
    class ClientsList : virtual public std::mutex {
    public:
        ClientsList() = default;

        ~ClientsList() = default;

    public:
        void add_client(const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client)
        {
            lock();
            _clients.emplace_back(client);
            unlock();
        };

        void remove_client(const BabelNetwork::ClientSocket &target)
        {
            lock();
            auto end = _clients.end();
            for (auto it = _clients.begin(); it != end; ++it) {
                if (**it == target) {
                    std::cerr << "Client erase" << it->get()->describe() << std::endl;
                    _clients.erase(it);
                    break;
                }
            }
            unlock();
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
