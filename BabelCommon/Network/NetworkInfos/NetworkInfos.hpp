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
    #define DEFAULT_PORT() ("5342")

    class NetworkInfos {

        /* <- Constructor - Destructor -> */
    public:
        explicit NetworkInfos(std::string ip, const std::string& port = DEFAULT_PORT());

        ~NetworkInfos() = default;

        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const NetworkInfos &connection);


        /* <- Methods -> */
    public:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] uint16_t getPort() const;

        void setPort(uint16_t port);

        [[nodiscard]] const std::string &getIp() const;

        void setIp(const std::string &ip);

        /* <- Attributes -> */
    private:
        boost::uint16_t _port;
        std::string _ip;
    };

    /* <- Operators -> */
    std::ostream &operator<<(std::ostream &os, const NetworkInfos &connection);

}

#endif /* CPP_BABEL_2020_NETWORKINFOS_HPP */
