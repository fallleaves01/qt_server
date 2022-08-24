#include "scanner.h"

void SocketClient::sendFriendMessage(const Data &d) {
    DFriendMessage message(d);
    sendDataToUid(message.getReceiverUid(), message);
}

void SocketClient::sendGroupMessage(const Data &d) {
    DGroupMessage message(d);
    auto db = Database::getDatabase();
    auto members = db->getGroupMembersId(message.getGroupId());
    for (auto uid : *members) {
        sendDataToUid(uid, message);
    }
    delete members;
}