/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [NetworkInfos.hpp]: Header file for NetworkInfos feature.
*/

#ifndef CPP_BABEL_2020_NETWORKINFOS_HPP
#define CPP_BABEL_2020_NETWORKINFOS_HPP

#include <string>
#include <boost/cstdint.hpp>

namespace BabelNetwork {
    #define DEFAULT_PORT() ("8080")

    class NetworkInfos {

        /* <- Constructor - Destructor -> */
    public:
//        explicit NetworkInfos(const std::string &port = DEFAULT_PORT());

        explicit NetworkInfos(std::string ip = "0.0.0.0", const std::string &port = DEFAULT_PORT());

        ~NetworkInfos() = default;

        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const NetworkInfos &connection);

        bool operator==(const NetworkInfos &other) const;


        /* <- Public Methods -> */
    public:

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] uint16_t getPort() const;

        void setPort(uint16_t port);

        [[nodiscard]] const std::string &getIp() const;

        void setIp(const std::string &ip);

        [[nodiscard]] const std::string &getPortStr() const;

        /* <- Attributes -> */
    private:
        std::string _ip;
        std::string _port_str;
        uint16_t _port;
    };

    /* <- Operators -> */
    std::ostream &operator<<(std::ostream &os, const NetworkInfos &connection);
}

#endif /* CPP_BABEL_2020_NETWORKINFOS_HPP */
