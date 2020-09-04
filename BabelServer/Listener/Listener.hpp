//
// Created by encorpluptit on 9/3/20.
//

#ifndef TESTQT_LISTENER_HPP
#define TESTQT_LISTENER_HPP

#include "ASocket.hpp"
#include "AsioClientSocket.hpp"

namespace BabelServer {
    class Listener : virtual public BabelNetwork::ASocket {
        /* <- Constructor - Destructor -> */
    public:
        /* <- Public Methods -> */
    public:
//        virtual std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> getClientList() = 0;
        virtual std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> getClientList() = 0;
        /* <- Attributes -> */
    protected:
//        std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> _asioClients;
    };
}


#endif //TESTQT_LISTENER_HPP
