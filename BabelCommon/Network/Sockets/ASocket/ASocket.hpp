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
#include "ARunnable.hpp"
#include "SharedPtr.hpp"

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

        void setIp(const std::string &ip) { _networkInfos.setIp(ip); }

        void setPort(const uint16_t port) { _networkInfos.setPort(port); }

        [[nodiscard]] const std::string &getIp() { return _networkInfos.getIp(); };

        [[nodiscard]] uint16_t getPort() { return _networkInfos.getPort(); }

        /* <- Operators -> */
    public:
        bool operator==(const NetworkInfos &other) const;

        bool operator==(const ASocket &other) const;

        /* <- Attributes -> */
    protected:
        NetworkInfos _networkInfos;
        BabelUtils::Logger &_logger;
    };

}

#endif /* CPP_BABEL_2020_ASOCKET_HPP */
