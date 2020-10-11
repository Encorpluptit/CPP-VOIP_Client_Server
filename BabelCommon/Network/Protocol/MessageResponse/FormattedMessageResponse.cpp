/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormattedMessageResponse.cpp]: Source file for FormattedMessageResponse feature.
*/

#include <iostream>
#include "MessageResponse.hpp"

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::RequestMessageSend(const std::string &sender, const std::string &receiver,
    const std::string &messageData)
{
    auto resp = std::make_shared<BabelNetwork::MessageResponse>(sender, receiver, messageData);
    resp->setCode(BabelNetwork::MessageResponse::ResponseCode::RequestSendMessage);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::OkSendMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    response->setCode(BabelNetwork::MessageResponse::ResponseCode::SendMessageOk);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::MessageReceive(const std::string &sender, const std::string &receiver,
    const std::string &messageData)
{
    auto resp = std::make_shared<BabelNetwork::MessageResponse>(sender, receiver, messageData);
    resp->setCode(BabelNetwork::MessageResponse::ResponseCode::ReceiveMessage);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::MessageReceive(const std::shared_ptr<BabelNetwork::MessageResponse> &resp)
{
    auto response = std::make_shared<BabelNetwork::MessageResponse>(
        resp->getSender(), resp->getReceiver(), resp->getMessageData());
    response->setCode(BabelNetwork::MessageResponse::ResponseCode::ReceiveMessage);
    if (!response->setTimestamp())
        return nullptr;
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::ReceiveMessageOk(const std::string &sender, const std::string &receiver)
{
    auto resp = std::make_shared<BabelNetwork::MessageResponse>(sender, receiver, "");
    resp->setCode(BabelNetwork::MessageResponse::ResponseCode::ReceiveOk);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::UserNotFound(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    response->setCode(BabelNetwork::MessageResponse::ResponseCode::UnknownUser);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::MessageResponse::UnknownErrorAppend(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    response->setCode(BabelNetwork::MessageResponse::ResponseCode::UnknownError);
    return response;
}
