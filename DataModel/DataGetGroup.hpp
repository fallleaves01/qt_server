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
   public:
    DGroupInfo(int _groupId, const std::string& _groupName, int groupCnt)
        : Data(Data::GROUP_INFO, _groupId, groupCnt, "", _groupName) {}

    DGroupInfo(const std::string& s) : Data(s) {}
    DGroupInfo(const Data& d) : Data(d) {}

    int getGroupId() const { return getSenderUid(); }
    int getGroupCnt() const { return getReceiverUid(); }
    std::string getGroupName() const { return getContent(); }
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
    DGroupUser(int _groupId,
               const std::string& _time,
               const std::vector<UserInfo>& _userList)
        : Data(Data::GET_GROUP_USER,
               _groupId,
               0,
               _time,
               encodeArray(_userList)) {}

    DGroupUser(const std::string& s) : Data(s) {
        userList = decodeArray<UserInfo>(getContent());
    }
    DGroupUser(const Data& d) : Data(d) {
        userList = decodeArray<UserInfo>(getContent());
    }

    int getGroupId() const { return getSenderUid(); }
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
        message = decodeArray<ChatMessage>(getContent());
    }
    DGroupMessageList(const Data& d) : Data(d) {
        message = decodeArray<ChatMessage>(getContent());
    }

    std::vector<ChatMessage> getMessageList() const { return message; }
};