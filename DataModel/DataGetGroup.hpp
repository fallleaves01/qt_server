#pragma once
#include "Message.hpp"
#include "encoding.h"

class GetGroupInfo : public Data {
   public:
    GetGroupInfo(int _senderUid, int _groupId, const std::string& time)
        : Data(Data::GET_GROUP_INFO, _senderUid, _groupId, time, "") {}

    GetGroupInfo(const std::string& s) : Data(s) {}
    GetGroupInfo(const Data& d) : Data(d) {}

    int getGroupId() const { return getReceiverUid(); }
};

class DGroupInfo : public Data {
    GroupInfo groupInfo;
   public:
    DGroupInfo(int _senderUid, const GroupInfo &_groupInfo, int groupCnt)
        : Data(Data::GROUP_INFO, _senderUid, groupCnt, "", encodeGroupInfo(_groupInfo)) {}

    DGroupInfo(const std::string& s) : Data(s) {
        DataStream ds(getContent());
        ds >> groupInfo;
    }
    DGroupInfo(const Data& d) : Data(d) {
        DataStream ds(getContent());
        ds >> groupInfo;
    }

    int getGroupCnt() const { return getReceiverUid(); }
    GroupInfo getGroupInfo() const { return groupInfo; }
};

class GetGroupList : public Data {
   public:
    GetGroupList(int _senderUid, std::string _time)
        : Data(Data::GET_GROUP_LIST, _senderUid, 0, _time, "") {}

    GetGroupList(const std::string& s) : Data(s) {}
    GetGroupList(const Data& d) : Data(d) {}
};

class DGroupList : public Data {
    std::vector<GroupInfo> groupList;

   public:
    DGroupList(int _senderUid, const std::vector<GroupInfo>& _groupList)
        : Data(Data::GROUP_LIST, _senderUid, 0, "", encodeArray(groupList)) {}

    DGroupList(const std::string& s) : Data(s) {
        groupList = decodeArray<GroupInfo>(getContent());
    }
    DGroupList(const Data& d) : Data(d) {
        groupList = decodeArray<GroupInfo>(getContent());
    }

    std::vector<GroupInfo> getGroupList() const { return groupList; }
};

class GetGroupUser : public Data {
   public:
    GetGroupUser(int _senderUid, int _groupId, const std::string& _time)
        : Data(Data::GET_GROUP_USER, _senderUid, _groupId, _time, "") {}

    GetGroupUser(const std::string& s) : Data(s) {}
    GetGroupUser(const Data& d) : Data(d) {}

    int getGroupId() const { return getReceiverUid(); }
};

class DGroupUser : public Data {
    std::vector<UserInfo> userList;

   public:
    DGroupUser(int _senderUid, int _groupId,
               const std::vector<UserInfo>& _userList)
        : Data(Data::GROUP_USER,
                _senderUid,
               _groupId,
               "",
               encodeArray(_userList)) {}

    DGroupUser(const std::string& s) : Data(s) {
        userList = decodeArray<UserInfo>(getContent());
    }
    DGroupUser(const Data& d) : Data(d) {
        userList = decodeArray<UserInfo>(getContent());
    }

    int getGroupId() const { return getReceiverUid(); }
    std::vector<UserInfo> getUserList() const { return userList; }
};

class GetGroupMessage : public Data {
   public:
    GetGroupMessage(int _senderUid, int _groupId, const std::string& _time)
        : Data(Data::GET_GROUP_MESSAGE, _senderUid, _groupId, _time, "") {}

    GetGroupMessage(const std::string& s) : Data(s) {}
    GetGroupMessage(const Data& d) : Data(d) {}

    int getGroupId() const { return getReceiverUid(); }
};

class DGroupMessageList : public Data {
    std::vector<ChatMessage> message;

   public:
    DGroupMessageList(int _senderUid,
                      int _groupId,
                      std::vector<ChatMessage> _message)
        : Data(Data::GROUP_MESSAGE_LIST,
               _senderUid,
               _groupId,
               "",
               encodeArray(_message)),
          message(_message) {}

    DGroupMessageList(const std::string& s) : Data(s) {
        ChatMessage tmp(0);
        message = decodeArray<ChatMessage>(getContent(), tmp);
    }
    DGroupMessageList(const Data& d) : Data(d) {
        ChatMessage tmp(0);
        message = decodeArray<ChatMessage>(getContent(), tmp);
    }

    std::vector<ChatMessage> getMessageList() const { return message; }
};