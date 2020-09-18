/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Header file for Database feature.
*/

#ifndef CPP_BABEL_2020_DATABASE_HPP
#define CPP_BABEL_2020_DATABASE_HPP

#include <mutex>
#include <sqlite_orm.h>

namespace BabelServer {
    struct UserModel {
        int id{};
        std::string login;
        std::string password;
        UserModel() = default;
        UserModel(std::string login, std::string password)
            : id(), login(std::move(login)), password(std::move(password)) {}
    };

class Database : virtual public std::mutex {
        /* <- Constructor - Destructor -> */
    public:
        Database();

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
//        void lock() { _mtx.lock(); }
//
//        void unlock() { _mtx.unlock(); }

        /* <- Getters / Setters -> */
    private:
        static auto & getDatabase();

        /* <- Attributes -> */
    private:
//        std::mutex _mtx;
//        sqlite_orm::internal::transaction_guard_t _mtx2;
    };

}

#endif //CPP_BABEL_2020_DATABASE_HPP
