//
// Created by encorpluptit on 9/28/20.
//

#ifndef CPP_BABEL_2020_ASIOCLIENTLIST_H
#define CPP_BABEL_2020_ASIOCLIENTLIST_H

#include "AsioClientSocket.hpp"
#include "ClientsList.hpp"

namespace BabelServer {

    using AsioClientSocketList = std::vector<BabelUtils::SharedPtr<AsioClientSocket>>;

    class AsioClientsList final : virtual public ClientsList {
    public:
        void add_client(BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client) final
        {
            lock();
            _clients.emplace_back(client);
            unlock();
        };

        void remove_client(BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &client) final
        {
            lock();
            std::remove(_clients.begin(), _clients.end(), boost::dynamic_pointer_cast<AsioClientSocket>(client));
            unlock();
        };
    private:
//        AsioClientSocketList _clients;
    };

};

#endif //CPP_BABEL_2020_ASIOCLIENTLIST_H
