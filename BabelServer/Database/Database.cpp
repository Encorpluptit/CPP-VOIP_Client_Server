/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Source file for Database feature.
*/

#include "Debug.hpp"
#include "Database.hpp"

using namespace BabelServer;
using namespace sqlite_orm;


// TODO: Adding Logger
Database::Database(BabelUtils::Logger &logger) : _logger(logger)
{
}

Database::~Database()
{
//    lock();
//    auto storage = getDatabase();
//    storage.close();
//    unlock();
}

auto &Database::getDatabase()
{
    static auto storage = make_storage("db.sqlite",
        make_table("users",
            make_column("id", &UserModel::id, autoincrement(), primary_key()),
            make_column("login", &UserModel::login, unique()),
            make_column("password", &UserModel::password)
        ),
        make_table("message",
            make_column("id", &MessageModel::id, autoincrement(), primary_key()),
            make_column("sender", &MessageModel::senderID),
            make_column("receiver", &MessageModel::receiverID),
            make_column("timestamp", &MessageModel::timestamp),
            make_column("content", &MessageModel::content),
            foreign_key(&MessageModel::senderID).references(&UserModel::id),
            foreign_key(&MessageModel::receiverID).references(&UserModel::id)
        )
    );
    storage.sync_schema();
    return storage;
}

int Database::createUser(const std::string &login, const std::string &password)
{
    std::string log;
    auto user = UserModel(login, password);
    lock();
    auto storage = getDatabase();
    int id = -1;
    try {
        id = storage.insert(user);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in create User with login: {%s} and password: {%s} -> %s", login.c_str(), password.c_str(), e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return id;
    } catch (...) {
        log = BabelUtils::format("Error in create User with login: {%s} and password: {%s} -> unknown exception", login.c_str(), password.c_str());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return id;
    }
    unlock();
    log = BabelUtils::format("User Created: id {%d}, login {%s}, password {%s}", user.id, user.login.c_str(), user.password.c_str());
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return id;
}

std::unique_ptr<UserModel> Database::getUser(const std::string &login)
{
    std::vector<UserModel> users{};
    std::string log;
    lock();
    auto storage = getDatabase();
    try {
        users = storage.get_all<UserModel>(where(c(&UserModel::login) == login));
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in getUser(login): %s", e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return nullptr;
    } catch (...) {
        log = "Error in getUser(login): unknown exception";
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return nullptr;
    }
    unlock();
    if (users.size() != 1)
        return nullptr;
    return std::make_unique<UserModel>(users.front());
}

std::unique_ptr<UserModel> Database::getUser(int id)
{
    std::string log;
    std::unique_ptr<UserModel> user = nullptr;
    lock();
    auto storage = getDatabase();
    try {
        user = storage.get_pointer<UserModel>(id);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in getUser(id: {%d}): %s", id, e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (...) {
        log = BabelUtils::format("Error in getUser(id): unknown exception");
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    return user;
}
