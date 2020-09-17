/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Source file for Database feature.
*/

//TODO: REMOVE
#include <iostream>

#include "Database.hpp"

using namespace BabelServer;
using namespace sqlite_orm;


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
    try {
        id = storage.insert(user);
    } catch (const std::system_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exeption" << std::endl;
    }
    unlock();
    // TODO: REMOVE
    std::cout << "User Created" << std::endl;
    return id;
}

std::unique_ptr<UserModel> Database::getUser(const std::string &login)
{
    std::vector<UserModel>users{};
    lock();
    auto storage = getDatabase();
    try {
        users = storage.get_all<UserModel>(where(c(&UserModel::login) == login));
    } catch (const std::system_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exeption" << std::endl;
    }
    unlock();
    if (users.size() != 1)
        return nullptr;
    return std::make_unique<UserModel>(users.front());
}

std::unique_ptr<UserModel> Database::getUser(int id)
{
    std::unique_ptr<UserModel> user = nullptr;
    lock();
    auto storage = getDatabase();
    try {
        user = storage.get_pointer<UserModel>(id);
    } catch (const std::system_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exeption" << std::endl;
    }
    unlock();
    return user;
}
