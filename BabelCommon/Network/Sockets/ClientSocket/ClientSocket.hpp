/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/4/20).
** File description:
** [ClientSocket.hpp]: Header file for ClientSocket feature.
*/

#ifndef CPP_BABEL_2020_CLIENTSOCKET_HPP
#define CPP_BABEL_2020_CLIENTSOCKET_HPP

#include "ASocket.hpp"

namespace BabelNetwork {

    class ClientSocket : public ASocket {

        /* <- Constructor - Destructor -> */
    public:
        explicit ClientSocket(
            const std::string &address,
            const std::string &port,
            BabelUtils::Logger &logger
        ) : ASocket(address, port, logger) {};

        ~ClientSocket() override = default;

        /* <- Operators -> */
    public:
//        friend std::ostream &operator<<(std::ostream &os, const ClientSocket &client) = 0;

        /* <- Public Methods -> */
    public:
        [[nodiscard]] virtual bool sendResponse(const AResponse &response) = 0;

        [[nodiscard]] virtual bool sendResponse(const std::shared_ptr<AResponse> &response) = 0;

        [[nodiscard]] virtual std::shared_ptr<AResponse> popResponse() {
            if (_read_queue.empty())
                return nullptr;
            auto resp = _read_queue.front();
            _read_queue.pop();
            return resp;
        }

        [[nodiscard]] virtual std::string describe() = 0;

        virtual void connect() = 0;

        /* <- Attributes -> */
    protected:
        char _headerBuffer[AResponse::HeaderSize] = {0};
        std::shared_ptr<AResponse> _read_msg = nullptr;
        std::queue<std::shared_ptr<AResponse>> _read_queue;
        std::queue<std::shared_ptr<AResponse>> _write_queue;
    };
    /* <- Operators -> */
//    std::ostream &operator<<(std::ostream &os, const AResponse &response);

}

#endif /* CPP_BABEL_2020_CLIENTSOCKET_HPP */
