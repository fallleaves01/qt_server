#include "scanner.h"

void SocketClient::getUserInfo(const Data &d) {
    GetUserInfo get(d);
    std::cerr << "get user info " << get.getUserId() << std::endl;
    auto db = Database::getDatabase();
    UserInfo info = db->getUserInfoById(get.getUserId());
    bool online = checkOnline(get.getUserId());
    int state = (online ? DUserInfo::ONLINE : DUserInfo::OFFLINE);
    DUserInfo ret(get.getSenderUid(), info, state);
    sendDataToUid(get.getSenderUid(), ret);
}

void SocketClient::getFriendList(const Data &d) {
    GetFriendList get(d);
    auto db = Database::getDatabase();
    auto friendsId = db->getFriendsId(get.getSenderUid());
    std::vector<UserInfo> friendList;
    for (auto uid : *friendsId) {
        friendList.emplace_back(db->getUserInfoById(uid));
    }
    std::cerr << get.getSenderUid() << " required friend list " << std::endl;
    DFriendList ret(get.getSenderUid(), get.getSenderUid(), friendList);
    sendDataToUid(get.getSenderUid(), ret);
    delete friendsId;
}

void SocketClient::getFriendMessage(const Data &d) {
    GetFriendMessage get(d);
    auto db = Database::getDatabase();
    auto message = db->getUserChatMessage(get.getSenderUid(), get.getFriendUid());
    DFriendMessageList ret(get.getSenderUid(), get.getFriendUid(), *message);
    sendDataToUid(get.getSenderUid(), ret);
    delete message;
}

void SocketClient::getGroupInfo(const Data &d) {
    GetGroupInfo get(d);
    auto db = Database::getDatabase();
    auto info = db->getGroupInfo(get.getGroupId());
    auto members = db->getGroupMembersId(info.getId());
    int cnt = members->size();
    delete members;
    DGroupInfo ret(get.getSenderUid(), info, cnt);
}

void SocketClient::getGroupList(const Data &d) {
    std::cerr << "get group list" << std::endl;
    GetGroupList get(d);
    auto db = Database::getDatabase();
    auto groupList = db->getGroupList(get.getSenderUid());
    std::cerr << "size " << groupList->size() << std::endl;
    DGroupList ret(get.getSenderUid(), *groupList);
    sendDataToUid(get.getSenderUid(), ret);
    delete groupList;
}

void SocketClient::getGroupUser(const Data &d) {
    GetGroupUser get(d);
    auto db = Database::getDatabase();
    auto members = db->getGroupMembersNoPwd(get.getGroupId());
    DGroupUser ret(get.getSenderUid(), get.getGroupId(), *members);
    sendDataToUid(get.getSenderUid(), ret);
    delete members;
}

void SocketClient::getGroupMessage(const Data &d) {
    GetGroupMessage get(d);
    auto db = Database::getDatabase();
    auto message = db->getGroupChatMessage(get.getGroupId());
    DGroupMessageList ret(get.getSenderUid(), get.getGroupId(), *message);
    sendDataToUid(get.getSenderUid(), ret);
    delete message;
}