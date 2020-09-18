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

namespace BabelServer {
    struct UserModel {
        int id{};
        std::string login;
        std::string password;

        UserModel() = default;

        UserModel(std::string login, std::string password)
            : id(), login(std::move(login)), password(std::move(password)) {}
    };
    struct MessageModel {
        int id{};
        int senderID{};
        int receiverID{};
        time_t timestamp{};
        std::string content;
        MessageModel() = default;

        MessageModel(const int sender, const int receiver, std::string msg_content, const time_t msg_timestamp)
            : id(), senderID(sender), receiverID(receiver), timestamp(msg_timestamp), content(std::move(msg_content)) {}
    };

    class Database : virtual public std::mutex {
        /* <- Constructor - Destructor -> */
    public:
        explicit Database(BabelUtils::Logger &logger);

        ~Database();

        /* <- Public Methods -> */
    public:
        int createUser(const std::string &login, const std::string &password);

        std::unique_ptr<UserModel> getUser(const std::string &login);

        std::unique_ptr<UserModel> getUser(int id);
//        bool deleteUser(const std::string &login);
//        bool deleteUser(const int id);

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    private:
        static auto &getDatabase();

        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
    };

}

#endif //CPP_BABEL_2020_DATABASE_HPP
