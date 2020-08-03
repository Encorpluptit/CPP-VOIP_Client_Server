/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Server.hpp]: Header file for Server feature.
*/

/* <- Class Structure -> */
/* <- Class Enum -> */
/* <- Constructor - Destructor -> */
/* <- Operators -> */
/* <- Methods -> */
/* <- Getters / Setters -> */
/* <- Attributes -> */

#ifndef CPP_BABEL_2020_SERVER_HPP
#define CPP_BABEL_2020_SERVER_HPP

#include "AsioListener.hpp"
#include "Logger.hpp"

namespace BabelServer {
    class Server {

        /* <- Constructor - Destructor -> */
    public:
        explicit Server(int ac, char **av);

        ~Server();

        /* <- Public Methods -> */
    public:
        void run();

        /* <- Private Methods -> */
    private:
        void initServers(int ac, char **av);

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const boost::shared_ptr<BabelUtils::BoostThread> &getThread() const;

        void setThread(const boost::shared_ptr<BabelUtils::BoostThread> &thread);


        /* <- Attributes -> */
    private:
        BabelUtils::Logger _logger;
        std::vector<boost::shared_ptr<BabelServer::AsioListener>> _servers;
//        BabelServer::AsioListener _server;
        boost::shared_ptr<BabelUtils::BoostThread> _thread;
        //Db
    };

}

#endif /* CPP_BABEL_2020_SERVER_HPP */
