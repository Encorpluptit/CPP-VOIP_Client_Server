/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Source file for Database feature.
*/

#include "Debug.hpp"
#include "Database.hpp"
#include "ServerError.hpp"

using namespace BabelServer;
using namespace BabelNetwork;
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
            foreign_key(&MessageModel::senderID).references(&UserModel::id).on_update.cascade().on_delete.cascade(),
            foreign_key(&MessageModel::receiverID).references(&UserModel::id).on_update.cascade().on_delete.cascade()
        ),
        make_table("friend",
            make_column("id", &FriendModel::id, autoincrement(), primary_key()),
            make_column("user1", &FriendModel::user1ID),
            make_column("user2", &FriendModel::user2ID),
            foreign_key(&FriendModel::user1ID).references(&UserModel::id).on_update.cascade().on_delete.cascade(),
            foreign_key(&FriendModel::user2ID).references(&UserModel::id).on_update.cascade().on_delete.cascade()
        )
    );
    static bool init = true;

    if (init) {
        storage.sync_schema();
        init = false;
    }
    return storage;
}

UserResponse::ResponseCode Database::createUser(const std::string &login, const std::string &password)
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
        return UserResponse::LoginAlreadyTaken;
    } catch (...) {
        log = BabelUtils::format("Error in create User with login: {%s} and password: {%s} -> unknown exception",
            login.c_str(), password.c_str());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return UserResponse::UnknownUserError;
    }
    unlock();
    log = BabelUtils::format("User Created: id {%d}, login {%s}, password {%s}", id, user.login.c_str(),
        user.password.c_str());
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return UserResponse::AccountCreated;
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

UserResponse::ResponseCode Database::deleteUser(const std::string &login)
{
    std::string log;
    try {
        auto user = getUser(login);
        if (!user)
            return UserResponse::RequestedAccountDeleted;
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
        return UserResponse::UnknownUserError;
    } catch (...) {
        log = "Error in deleteUser(login): unknown exception";
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return UserResponse::UnknownUserError;
    }
    unlock();
    return UserResponse::AccountDeleted;
}

MessageResponse::ResponseCode Database::createMessage(
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
        if (!sender || !receiver) {
            log = BabelUtils::format(
                "Error in create Message : User not found -> {%s} or {%s}",
                senderName.c_str(), receiverName.c_str()
            );
            dbg("%s", log.c_str());
            _logger.logThis(log);
            return MessageResponse::UnknownUser;
        }
        lock();
        auto storage = getDatabase();
        auto message = MessageModel(sender->id, receiver->id, content, timestamp);
        storage.insert(message);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in create Message with param -> %s", e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return MessageResponse::UnknownError;
    } catch (...) {
        log = "Error in create Message -> unknown exception";
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return MessageResponse::UnknownError;
    }
    unlock();
    log = BabelUtils::format(
        "Message Created: senderid {%s}, receiverid {%s}, content {%s}",
        senderName.c_str(), receiverName.c_str(), content.c_str()
    );
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return MessageResponse::SendMessageOk;
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
                (is_equal(&MessageModel::senderID, sender->id) \
 and is_equal(&MessageModel::receiverID, receiver->id))\
 or (is_equal(&MessageModel::receiverID, sender->id)\
 and is_equal(&MessageModel::senderID, receiver->id))\
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

FriendResponse::ResponseCode Database::createFriendship(const std::string &senderName, const std::string &receiverName)
{
    std::string log;
    try {
        auto sender = getUser(senderName);
        auto receiver = getUser(receiverName);
        if (!sender || !receiver) {
            log = BabelUtils::format(
                "Error in create Message : User not found -> {%s} or {%s}",
                senderName.c_str(), receiverName.c_str()
            );
            dbg("%s", log.c_str());
            _logger.logThis(log);
            return FriendResponse::UnknownUser;
        }
        lock();
        auto storage = getDatabase();
        // TODO: check if users already friend
        auto friendship = FriendModel(sender->id, receiver->id);
        storage.insert(friendship);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in createFriendship (name: {%d}): %s", receiverName.c_str(), e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return FriendResponse::UnknownErrorOccur;
    } catch (...) {
        log = BabelUtils::format("Error in createFriendship (name: {%d}): unknown exception", receiverName.c_str());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        return FriendResponse::UnknownErrorOccur;
    }
    unlock();
    log = BabelUtils::format("Friendship Created: user_1: {%s}, user_2: {%s}", senderName.c_str(),
        receiverName.c_str());
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return FriendResponse::FriendAdded;
}

std::vector<FriendModel> Database::getFriendships(const std::string &userName)
{
    std::string log;
    std::vector<FriendModel> friendships;

    try {
        auto user = getUser(userName);
        if (!user) {
            log = BabelUtils::format(
                "Error in getFriendship : User not found -> {%s}", userName.c_str());
            dbg("%s", log.c_str());
            _logger.logThis(log);
            throw ServerError(log);
        }
        lock();
        auto storage = getDatabase();
        friendships = storage.get_all<FriendModel>(
            where(is_equal(&FriendModel::user1ID, user->id) or is_equal(&FriendModel::user2ID, user->id))
        );
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in getFriendship (name: {%d}): %s", userName.c_str(), e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
        unlock();
        throw ServerError(log);
    }
    unlock();
    return friendships;
}

std::vector<FriendModel> Database::getFriendships(const int userid)
{
    std::string log;
    std::vector<FriendModel> friendships;

    try {
        lock();
        auto storage = getDatabase();
        friendships = storage.get_all<FriendModel>(
            where(is_equal(&FriendModel::user1ID, userid) or is_equal(&FriendModel::user2ID, userid))
        );
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in getFriendship (id: {%d}): %s", userid, e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (...) {
        log = BabelUtils::format("Error in getFriendship (id: {%d}): unknown exception", userid);
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    return friendships;
}

FriendResponse::ResponseCode Database::deleteFriendship(
    const std::string &senderName,
    const std::string &receiverName
)
{
    std::string log;

    try {
        auto sender = getUser(senderName);
        auto receiver = getUser(receiverName);
        if (!sender || !receiver) {
            log = BabelUtils::format(
                "Error in deleteFriendship : User not found -> {%s} or {%s}",
                senderName.c_str(), receiverName.c_str()
            );
            dbg("%s", log.c_str());
            _logger.logThis(log);
            return FriendResponse::UnknownUser;
        }
        lock();
        auto storage = getDatabase();
        auto friendships = storage.get_all<FriendModel>(
            where((is_equal(&FriendModel::user1ID, sender->id) and is_equal(&FriendModel::user2ID, receiver->id))
                or (is_equal(&FriendModel::user2ID, sender->id) and is_equal(&FriendModel::user1ID, receiver->id)))
        );
        if (friendships.size() > 1) {
            log = BabelUtils::format(
                "Too many Friendship found -> {%s} or {%s}",
                senderName.c_str(), receiverName.c_str()
            );
            dbg("%s", log.c_str());
            _logger.logThis(log);
            unlock();
            return FriendResponse::UnknownErrorOccur;
        }
        if (friendships.empty()) {
            log = BabelUtils::format(
                "No Friendship found -> {%s} or {%s}",
                senderName.c_str(), receiverName.c_str()
            );
            dbg("%s", log.c_str());
            _logger.logThis(log);
            unlock();
            return FriendResponse::FriendshipUnknown;
        }
        auto friendship = friendships.front();
        storage.remove<FriendModel>(friendship.id);
    } catch (const std::system_error &e) {
        log = BabelUtils::format("Error in deleteFriendship (name: {%d}): %s", receiverName.c_str(), e.what());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    } catch (...) {
        log = BabelUtils::format("Error in deleteFriendship (name: {%d}): unknown exception", receiverName.c_str());
        dbg("%s", log.c_str());
        _logger.logThis(log);
    }
    unlock();
    log = BabelUtils::format("Friendship Deleted: user_1: {%s}, user_2: {%s}", senderName.c_str(),
        receiverName.c_str());
    dbg("%s", log.c_str());
    _logger.logThis(log);
    return FriendResponse::FriendDeleted;
}
