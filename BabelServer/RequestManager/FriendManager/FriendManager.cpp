//
// Created by encorpluptit on 9/21/20.
//

#include "FriendManager.hpp"

using namespace BabelServer;

const std::vector<FriendManager::FriendResponseFPtr> &FriendManager::getFriendResponsePtrTab() const
{
    return FriendResponsePtrTab;
}
