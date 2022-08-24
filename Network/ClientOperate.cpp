#include "scanner.h"

void SocketClient::workOnData(const Data &d) {
    switch (d.getType()) {
        case (Data::LOGIN_MESSAGE):
            tryLogin(d);
            break;
        case (Data::REGISTER_MESSAGE):
            tryRegister(d);
            break;
        case (Data::ADDFRIEND_MESSAGE):
            tryAddFriend(d);
            break;
        case (Data::ADDFRIEND_CHECK):
            addFriendCheck(d);
            break;
        case (Data::CREATE_GROUP_MESSAGE):
            tryCreateGroup(d);
            break;
        case (Data::ADD_GROUP_MESSAGE):
            tryAddGroup(d);
            break;
        case (Data::ADD_GROUP_CHECK):
            addGroupCheck(d);
            break;
        case (Data::GROUP_INVITE_MESSAGE):
            tryInviteGroup(d);
            break;
    }
}

void SocketClient::tryLogin(const Data &d) {
    LoginMessage login(d);
    std::cerr << "user " << login.getUserName() << " tried to login" << std::endl;
    auto db = Database::getDatabase();
    auto users = db->getAllUserNoPwd();
    auto checkNameExists = [&]() {
        for (auto user : *users) {
            if (user.getName() == login.getUserName()) {
                std::cerr << "found user " << user.getName() << std::endl;
                auto userInfo = db->getUserInfoById(user.getId());
                if (userInfo.getPwd() == login.getPassword()) {
                    LoginCheck ret(login.getTime(), user.getName(),
                                   user.getId(), LoginCheck::SUCCESS);
                    sendData(ret);
                    loginWithUid(user.getId());
                } else {
                    LoginCheck ret(login.getTime(), user.getName(),
                                   user.getId(), LoginCheck::WRONGPASSWORD);
                    sendData(ret);
                }
                return true;
            }
        }
        return false;
    };
    if (!checkNameExists()) {
        std::cerr << "user not found" << std::endl;
        LoginCheck ret(login.getTime(), login.getUserName(), 0, LoginCheck::USERNOTFOUND);
        sendData(ret);
    }
    delete users;
}

void SocketClient::tryRegister(const Data &d) {
    RegisterMessage reg(d);
    std::cerr << "user " << reg.getUserName() << " tried to register" << std::endl;
    auto db = Database::getDatabase();
    auto users = db->getAllUserId();
    int uid = users->size() + 1;
    UserInfo user(uid, reg.getUserName(), reg.getPassword());
    delete users;
    db->insertUserTable(user);
    LoginCheck ret(reg.getTime(), user.getName(), user.getId(), LoginCheck::SUCCESS);
    sendData(ret);
    loginWithUid(user.getId());
}

void SocketClient::tryAddFriend(const Data &d) {
    AddFriendMessage addf(d);
    sendDataToUid(addf.getReceiverUid(), addf);
}

void SocketClient::addFriendCheck(const Data &d) {
    AddFriendCheck addfc(d);
    if (addfc.getState() == AddFriendCheck::SUCCESS) {
        auto db = Database::getDatabase();
        db->insertFriendShipTable(addfc.getSenderUid(), addfc.getReceiverUid());
    }
    sendDataToUid(addfc.getSenderUid(), addfc);
}

void SocketClient::tryCreateGroup(const Data &d) {
    CreateGroupMessage gp(d);
    auto member = gp.getUserList();
    auto db = Database::getDatabase();
    auto gps = db->getAllGroupId();
    int groupId = gps->size() + 100000;

    std::string name = "群" + std::to_string(groupId);
    GroupInfo groupInfo(groupId, name);
    db->insertGroupTable(groupInfo);
    CreateGroupCheck ret(gp.getCreaterUid(), groupId, gp.getTime());
    sendData(ret);
    db->insertGroupShipTable(groupId, gp.getCreaterUid(), 0);

    for (auto uid : member) {
        if (uid != gp.getCreaterUid()) {
            db->insertGroupShipTable(groupId, uid, 2);
            AddGroupCheck ret(uid, groupId, gp.getTime(), AddGroupCheck::SUCCESS);
            sendDataToUid(uid, ret);
        }
    }
    delete gps;
}

void SocketClient::tryAddGroup(const Data &d) {
    AddGroupMessage add(d);
    auto db = Database::getDatabase();
    auto members = db->getGroupMembersId(add.getGroupId());
    for (auto uid : *members) {
        if (db->getUserPermission(uid, add.getGroupId()) <= 1) {
            sendDataToUid(uid, add);
        }
    }
    delete members;
}

void SocketClient::addGroupCheck(const Data &d) {
    AddGroupCheck chk(d);
    auto db = Database::getDatabase();
    int userId = chk.getUserId(), groupId = chk.getGroupId();
    int st = db->getUserPermission(userId, groupId);
    if (st != -1) {
        return;
    }
    if (chk.getState() == AddGroupCheck::SUCCESS) {
        db->insertGroupShipTable(groupId, userId, 2);
        auto members = db->getGroupMembersId(groupId);
        for (auto uid : *members) {
            sendDataToUid(uid, chk);
        }
        delete members;
    } else {
        sendDataToUid(chk.getUserId(), chk);
    }
}

void SocketClient::tryInviteGroup(const Data& d) {
    GroupInviteMessage inv(d);
    auto db = Database::getDatabase();
    auto groupInfo = inv.getGroupInfo();
    int st = db->getUserPermission(inv.getReceiverUid(), groupInfo.getId());
    if (st != -1) {
        return;
    }
    db->insertGroupShipTable(groupInfo.getId(), inv.getReceiverUid(), 2);
    auto members = db->getGroupMembersId(groupInfo.getId());
    AddGroupCheck chk(inv.getReceiverUid(), groupInfo.getId(), inv.getTime(),
                      AddGroupCheck::SUCCESS);
    for (auto uid : *members) {
        sendDataToUid(uid, chk);
    }
    delete members;
}