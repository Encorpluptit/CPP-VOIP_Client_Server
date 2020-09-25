//
// Created by hobbit on 9/25/20.
//

#include "MessageManager.hpp"

using namespace BabelServer;

void MessageManager::sendMessage(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::MessageResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            target->sendResponse(response);
            //TODO: Database -> save message && message delivered;
            return;
        }
    }
    clientSocket->sendResponse(BabelNetwork::CallResponse::DisconnectedUser(response->getSender(), response->getReceiver()));

}