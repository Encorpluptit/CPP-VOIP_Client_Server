//
// Created by hobbit on 9/25/20.
//

#include "MessageManager.hpp"

using namespace BabelServer;
using namespace BabelNetwork;

void MessageManager::sendMessage(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<MessageResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    // TODO: check for login
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            switch (database.createMessage(
                response->getSender(), response->getReceiver(), response->getTimestamp(), response->getMessageData())) {
                case BabelNetwork::MessageResponse::SendMessageOk:
                    target->sendResponse(response);
                    clientSocket->sendResponse(MessageResponse::OkSendMessage(response));
                    return;
                case BabelNetwork::MessageResponse::UnknownUser:
                    clientSocket->sendResponse(MessageResponse::UserNotFound(response));
                    return;
                default:
                    clientSocket->sendResponse(MessageResponse::UnknownErrorAppend(response));
                    return;
            }
        }
    }
    clientSocket->sendResponse(MessageResponse::ReceiveMessageOk(response->getSender(), response->getReceiver()));
}
