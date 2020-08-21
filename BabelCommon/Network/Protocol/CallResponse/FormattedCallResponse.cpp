/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormattedCallResponse.cpp]: Source file for FormattedCallResponse feature.
*/

#include <iostream>
#include "CallResponse.hpp"

using namespace BabelNetwork;

std::shared_ptr<AResponse>
CallResponse::NewCallStarted(const std::string &sender, const std::string &receiver, const uint16_t call_id)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);
    resp->setCode(CallResponse::ResponseCode::CallStarted);
    if (!resp->setCallId(call_id) || !resp->setTimestamp())
        return nullptr;
    std::cout << resp->getTimestamp() << std::endl;
    return resp;
}
