#include "scanner.h"

void SocketClient::sendFriendMessage(const Data &d) {
    DFriendMessage message(d);
    sendDataToUid(message.getReceiverUid(), message);
    ChatMessage msg(message.getSenderUid(), message.getReceiverUid(), message.getTime(), message.getContent());
    Database::getDatabase()->insertChatMsgTable(msg);
}

void SocketClient::sendGroupMessage(const Data &d) {
    DGroupMessage message(d);
    auto db = Database::getDatabase();
    ChatMessage msg(message.getSenderUid(), message.getReceiverUid(), message.getTime(), message.getContent());
    db->insertChatMsgTable(msg);
    auto members = db->getGroupMembersId(message.getGroupId());
    for (auto uid : *members) {
        sendDataToUid(uid, message);
    }
    delete members;
}