/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Header file for Database feature.
*/

#ifndef CPP_BABEL_2020_DATABASE_HPP
#define CPP_BABEL_2020_DATABASE_HPP

#include <mutex>
#include <utility>
#include <sqlite_orm.h>
#include "Logger.hpp"
#include "Models.hpp"
#include "UserResponse.hpp"

namespace BabelServer {

    class Database : virtual public std::mutex {
        /* <- Constructor - Destructor -> */
    public:
        explicit Database(BabelUtils::Logger &logger);

        ~Database();

        /* <- Public Methods -> */
    public:
        BabelNetwork::UserResponse::ResponseCode createUser(const std::string &login, const std::string &password);

        std::shared_ptr<UserModel> getUser(const std::string &login);

        std::unique_ptr<UserModel> getUser(int id);

        BabelNetwork::UserResponse::ResponseCode deleteUser(const std::string &login);

        void createMessage(const int &id, const int &senderid, const int &receiverid, const time_t &timestamp, const std::string &content);

        // std::shared_ptr<MessageModel> getOneMessage(const int &id);

        // std::shared_ptr<[MessageModel]> GetConv(const int &senderid, const int &receiverid);

//        bool deleteUser(const int id);

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    private:
        static auto &getDatabase();

        /* <- Attributes -> */
    private:
        std::mutex _mtx;
        BabelUtils::Logger &_logger;
    };

}

#endif //CPP_BABEL_2020_DATABASE_HPP
