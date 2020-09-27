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

Database::Database(BabelUtils::Logger &logger)
    : _logger(logger)
{
}

Database::~Database() = default;

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
    static bool init = true;

    if (init) {
        storage.sync_schema();
        init = false;
    }
    return storage;
}

BabelNetwork::UserResponse::ResponseCode Database::createUser(const std::string &login, const std::string &password)
{
    std::string log;
    auto user = UserModel(login, password);
    lock();
    auto storage = getDatabase();
    int id = -1;
    try {
        id = storage.insert(user);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in create User with login: {%s} and password: {%s} -> %s", login.c_str(),
            password.c_str(), e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return BabelNetwork::UserResponse::LoginAlreadyTaken;
    } catch (...) {
        log = BabelUtils::format("Error in create User with login: {%s} and password: {%s} -> unknown exception",
            login.c_str(), password.c_str());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return BabelNetwork::UserResponse::UnknownUserError;
    }
    unlock();
    log = BabelUtils::format("User Created: id {%d}, login {%s}, password {%s}", id, user.login.c_str(),
        user.password.c_str());
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return BabelNetwork::UserResponse::AccountCreated;
}

std::shared_ptr<UserModel> Database::getUser(const std::string &login)
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
    return std::make_shared<UserModel>(users.front());
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
        log = BabelUtils::format("Error in getUser(id: {%d}): unknown exception", id);
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    return user;
}

BabelNetwork::UserResponse::ResponseCode Database::deleteUser(const std::string &login)
{
    std::string log;
    try {
        auto user = getUser(login);
        if (!user)
            return BabelNetwork::UserResponse::RequestedAccountDeleted;
        lock();
        auto storage = getDatabase();
        storage.remove<UserModel>(user->id);
        // TODO: ADD Function to remove friendship ?
        log = BabelUtils::format(
            "User Deleted: id {%d}, login {%s}, password {%s}",
            user->id, user->login.c_str(), user->password.c_str());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in deleteUser(login): %s", e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return BabelNetwork::UserResponse::UnknownUserError;
    } catch (...) {
        log = "Error in deleteUser(login): unknown exception";
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return BabelNetwork::UserResponse::UnknownUserError;
    }
    unlock();
    return BabelNetwork::UserResponse::AccountDeleted;
}


int Database::createMessage(
    const int &id,
    const int &senderid,
    const int &receiverid,
    const time_t &timestamp,
    const std::string &content)
{
    std::string log;
    auto message = MessageModel(senderid, receiverid, content, timestamp);
    lock();
    auto storage = getDatabase();
    int storage_id = -1;
    try {
        storage_id = storage.insert(message);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in create Message with param -> %s", e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return storage_id;
    } catch (...) {
        log = "Error in create Message -> unknown exception";
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return storage_id;
    }
    unlock();
    log = BabelUtils::format(
        "Message Created: senderid {%d}, receiverid {%d}, content {%s}",
        senderid, receiverid, content.c_str()
    );
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return storage_id;
}

BabelNetwork::MessageResponse::ResponseCode Database::createMessage(
    const std::string &senderName,
    const std::string &receiverName,
    const time_t timestamp,
    const std::string &content
)
{
    std::string log;
    try {
        auto sender = getUser(senderName);
        auto receiver = getUser(receiverName);
        lock();
        auto storage = getDatabase();
        if (!sender || !receiver) {
            log = BabelUtils::format("Error in create Message : User not found -> {%s} or {%s}",
                senderName.c_str(), receiverName.c_str()
            );
            dbg("%s", log.c_str());
            _logger.logThis(log);
            unlock();
            return BabelNetwork::MessageResponse::UnknownUser;
        }
        auto message = MessageModel(sender->id, receiver->id, content, timestamp);
        storage.insert(message);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in create Message with param -> %s", e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return BabelNetwork::MessageResponse::UnknownError;
    } catch (...) {
        log = "Error in create Message -> unknown exception";
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return BabelNetwork::MessageResponse::UnknownError;
    }
    unlock();
    log = BabelUtils::format(
        "Message Created: senderid {%s}, receiverid {%s}, content {%s}",
        senderName.c_str(), receiverName.c_str(), content.c_str()
    );
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return BabelNetwork::MessageResponse::SendMessageOk;
}

std::shared_ptr<MessageModel> Database::getOneMessage(const int id)
{
    std::string log;
    std::unique_ptr<MessageModel> message = nullptr;
    lock();
    auto storage = getDatabase();
    try {
        message = storage.get_pointer<MessageModel>(id);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in getOneMessage(id: {%d}): %s", id, e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (...) {
        log = BabelUtils::format("Error in getUser(id: {%d}): unknown exception", id);
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    return message;
}

std::vector<MessageModel> Database::GetConv(
    const int senderid,
    const int receiverid
)
{
    std::string log;
    std::vector<MessageModel> message;
    lock();
    auto storage = getDatabase();
    try {
        message = storage.get_all<MessageModel>();// message = storage.get_all<MessageModel>(senderid, receiverid);
        // std::cout << "ConvSize (" << message.size() << "):" << std::endl;
        // for(auto &mess : message) {
        //     std::cout << storage.dump(mess) << std::endl;
        // }
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in getConv(senderid: {%d}, receiverid: {%d}): %s", senderid, receiverid,
            e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (...) {
        log = BabelUtils::format("Error in getConv(senderid: {%d}, receiverid: {%d}): unknown exception", senderid,
            receiverid);
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    return message;
}

std::vector<MessageModel> Database::GetConv(const std::string &senderName, const std::string &receiverName)
{
    std::string log;
    std::vector<MessageModel> message;
    try {
        auto sender = getUser(senderName);
        auto receiver = getUser(receiverName);
        lock();
        auto storage = getDatabase();
        message = storage.get_all<MessageModel>(
            where(
                is_equal(&MessageModel::senderID, sender->id) \
 and is_equal(&MessageModel::receiverID, receiver->id)\
 or is_equal(&MessageModel::receiverID, sender->id)\
 and is_equal(&MessageModel::senderID, receiver->id)\
)
        );
    } catch (const std::system_error &e) {
        log = BabelUtils::format(
            "Error in getConv(sender: {%s}, receiver: {%s}): %s",
            senderName.c_str(), receiverName.c_str(), e.what()
        );
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (...) {
        log = BabelUtils::format(
            "Error in getConv(sender: {%s}, receiver: {%s}): unknown exception",
            senderName.c_str(), receiverName.c_str()
        );
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    return message;
}
