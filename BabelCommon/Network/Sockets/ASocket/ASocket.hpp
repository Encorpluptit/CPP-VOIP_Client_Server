/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ASocket.hpp]: Header file for ASocket feature.
*/

#ifndef CPP_BABEL_2020_ASOCKET_HPP
#define CPP_BABEL_2020_ASOCKET_HPP

#include <queue>
#include "Logger.hpp"
#include "Runnable/ARunnable.hpp"
#include "BoostThread.hpp"

namespace BabelNetwork {

class ASocket : virtual public BabelUtils::ARunnable {
        /* <- Class Enum -> */
    public:
        enum SocketType {
            TCP,
            UDP,
            QT
        };

        /* <- Constructor - Destructor -> */
    public:
        explicit ASocket(
            const std::string &address,
            const std::string &port,
            BabelUtils::Logger &logger
        );

        ~ASocket() override = default;

        /* <- Public Methods -> */
    public:

        /* <- Getters / Setters -> */
    public:

        [[nodiscard]] const NetworkInfos &getNetworkInfos() const;

        [[nodiscard]] const boost::shared_ptr<BabelUtils::AThread> &getThread() const;

        void setThread(const boost::shared_ptr<BabelUtils::AThread> &thread);

        /* <- Operators -> */
    public:
        bool operator==(const NetworkInfos &other) const;

        bool operator==(const ASocket &other) const;

        /* <- Attributes -> */
    protected:
        NetworkInfos _networkInfos;
        BabelUtils::Logger &_logger;
        boost::shared_ptr<BabelUtils::AThread> _thread;
    };

}

#endif /* CPP_BABEL_2020_ASOCKET_HPP */
