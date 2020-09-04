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

#include "Listener.hpp"
#include "Logger.hpp"

namespace BabelServer {
    class Server final : public BabelUtils::ARunnable {

        /* <- Constructor - Destructor -> */
    public:
        explicit Server(int ac, char **av);

        ~Server() final;

        /* <- Public Methods -> */
    public:
        void start() final;

        void stop() final;

        /* <- Private Methods -> */
    private:
        void initServers(int ac, char **av);

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const BabelUtils::SharedPtr<BabelUtils::BoostThread> &getThread() const;

        void setThread(const BabelUtils::SharedPtr<BabelUtils::BoostThread> &thread);


        /* <- Attributes -> */
    private:
        BabelUtils::Logger _logger;
        std::vector<BabelUtils::SharedPtr<BabelServer::Listener>> _servers;
        BabelUtils::SharedPtr<BabelUtils::BoostThread> _thread;
        // TODO: Include Db
    };

}

#endif /* CPP_BABEL_2020_SERVER_HPP */
