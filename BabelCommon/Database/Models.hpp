//
// Created by encorpluptit on 9/21/20.
//

#ifndef CPP_BABEL_2020_MODELS_HPP
#define CPP_BABEL_2020_MODELS_HPP

#include <string>

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

#endif //CPP_BABEL_2020_MODELS_HPP
