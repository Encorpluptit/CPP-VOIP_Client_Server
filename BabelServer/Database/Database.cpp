/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Source file for Database feature.
*/

#include "Database.hpp"


#include <iostream>

using namespace BabelServer;
using namespace sqlite_orm;

//
//auto storage = make_storage("db.sqlite",
//    make_table("users",
//        make_column("id", &UserModel::id, autoincrement(), primary_key()),
//        make_column("login", &UserModel::login, unique()),
//        make_column("password", &UserModel::password)
//    )/*,
//            */
//);

// TODO: Adding Logger
Database::Database()
{
    std::cout << "LOLOL" << std::endl;
//    auto storage = getDatabase();
}

Database::~Database()
{
    lock();
    unlock();
}

//template<>
//struct statement_binder<UserModel> {
//    int bind(sqlite3_stmt *stmt, int index, const UserModel &value) {
////        if(auto str = GenderToString(value)) {
////            return statement_binder<std::string>().bind(stmt, index, *str);
////        } else {
//            return statement_binder<std::nullptr_t>().bind(stmt, index, nullptr);
////        }
//    }
//};

auto &Database::getDatabase()
{
    static auto storage = make_storage("db.sqlite",
        make_table("users",
            make_column("id", &UserModel::id, autoincrement(), primary_key()),
            make_column("login", &UserModel::login, unique()),
            make_column("password", &UserModel::password)
        )
        /*,
            */
    );
    storage.sync_schema();
    return storage;
}

int Database::createUser(const std::string &login, const std::string &password)
{
    auto user = UserModel(login, password);
    lock();
    auto storage = getDatabase();
    int id = -1;
    std::cout << "User:" << user.login << "|" << user.password << std::endl;
    try {
        id = storage.insert(user);
        std::cout << "User:" << user.login << "|" << user.password << "|" << id << std::endl;
    } catch (const std::system_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exeption" << std::endl;
    }
    unlock();
    return id;
}

std::unique_ptr<UserModel> Database::getUser(const std::string &login)
{
    lock();

    auto storage = getDatabase();
    auto users = storage.get_all<UserModel>(where(c(&UserModel::login) == login));
    for (const auto &user : users) {
        std::cout << "User Found: " << user.login << std::endl;
    }
//    auto user = storage.get_pointer<UserModel>(login);
    unlock();
    return nullptr;
//    return user;
//    return user;
}

std::unique_ptr<UserModel> Database::getUser(int id)
{
    lock();
    auto storage = getDatabase();
    auto user = storage.get_pointer<UserModel>(id);
    unlock();
    return user;
}
