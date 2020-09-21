//
// Created by encorpluptit on 9/21/20.
//

#include "CallManager.hpp"

using namespace BabelServer;

const std::vector<CallManager::CallResponseFPtr> &CallManager::getCallResponsePtrTab() const
{
    return CallResponsePtrTab;
}
