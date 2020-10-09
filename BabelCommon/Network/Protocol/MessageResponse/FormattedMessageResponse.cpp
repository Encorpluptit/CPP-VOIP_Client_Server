/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormattedMessageResponse.cpp]: Source file for FormattedMessageResponse feature.
*/

#include <iostream>
#include "MessageResponse.hpp"

using namespace BabelNetwork;

std::shared_ptr<AResponse> MessageResponse::RequestMessageSend(const std::string &sender, const std::string &receiver,
    const std::string &messageData)
{
    auto resp = std::make_shared<MessageResponse>(sender, receiver, messageData);
    resp->setCode(MessageResponse::ResponseCode::RequestSendMessage);
    if (!resp->setMessageData(messageData) || !resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> MessageResponse::OkSendMessage(const std::shared_ptr<MessageResponse> &response)
{
    response->setCode(MessageResponse::ResponseCode::SendMessageOk);
    return response;
}

std::shared_ptr<AResponse>
MessageResponse::MessageReceive(const std::string &sender, const std::string &receiver, const std::string &messageData)
{
    auto resp = std::make_shared<MessageResponse>(sender, receiver, messageData);
    resp->setCode(MessageResponse::ResponseCode::ReceiveMessage);
    if (!resp->setMessageData(messageData) || !resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> MessageResponse::ReceiveMessageOk(const std::string &sender, const std::string &receiver)
{
    auto resp = std::make_shared<MessageResponse>(sender, receiver, "");
    resp->setCode(MessageResponse::ResponseCode::ReceiveOk);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> MessageResponse::UserNotFound(const std::shared_ptr<MessageResponse> &response)
{
    response->setCode(MessageResponse::ResponseCode::UnknownUser);
    return response;
}

std::shared_ptr<AResponse> MessageResponse::UnknownErrorAppend(const std::shared_ptr<MessageResponse> &response)
{
    response->setCode(MessageResponse::ResponseCode::UnknownUser);
    return response;
}
