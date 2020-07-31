/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ASocket.hpp]: Header file for ASocket feature.
*/

#ifndef CPP_BABEL_2020_ASOCKET_HPP
#define CPP_BABEL_2020_ASOCKET_HPP

#include <queue>
#include "ISocket.hpp"
#include "AResponse.hpp"
#include "BoostThread.hpp"

namespace BabelNetwork {

    class ASocket : virtual public ISocket {

        /* <- Constructor - Destructor -> */
    public:
        explicit ASocket(const NetworkInfos &networkInfos);

        ~ASocket() override = default;

        /* <- Public Methods -> */
    public:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] bool isReady() const;

        void setReady();

        [[nodiscard]] const NetworkInfos &getNetworkInfos() const;

        [[nodiscard]] const boost::shared_ptr<BabelUtils::BoostThread> &getThread() const;

        void setThread(const boost::shared_ptr<BabelUtils::BoostThread> &thread);

        /* <- Operators -> */
    public:
        bool operator==(const NetworkInfos &other) const;

        bool operator==(const ASocket &other) const;

        /* <- Attributes -> */
    protected:
        const NetworkInfos &_networkInfos;
        bool _ready = false;
        BabelNetwork::AResponse::ResponseHeader _hdr{};
        std::shared_ptr<AResponse> _read_msg = nullptr;
        std::queue<std::shared_ptr<BabelNetwork::AResponse>> _read_queue;
        std::queue<std::shared_ptr<BabelNetwork::AResponse>> _write_queue;
        boost::shared_ptr<BabelUtils::BoostThread> _thread;
    };

}

#endif /* CPP_BABEL_2020_ASOCKET_HPP */
