#pragma once
#include "encoding.h"
#include "Message.hpp"
using namespace Encoding;

class CreateGroupMessage : public Data {
    std::vector<int> userList;
    std::string groupName;

   public:
    //传入发起方uid,添加时间,群聊名称和拉进群聊的人员列表
    explicit CreateGroupMessage(int _createrId,
                                const std::string& _time,
                                const std::string& name,
                                std::vector<int> _memberUids)
        : Data(Data::CREATE_GROUP_MESSAGE,
               _createrId,
               0,
               _time,
               encodeStr(name) + encodeArray(_memberUids)),
          userList(_memberUids),
          groupName(name) {}

    //解码函数
    explicit CreateGroupMessage(const std::string& s) : Data(s) {
        DataStream ds(getContent());
        ds >> groupName;
        userList = decodeArray<int>(ds.getStr());
    }
    explicit CreateGroupMessage(const Data& d) : Data(d) {
        DataStream ds(getContent());
        ds >> groupName;
        userList = decodeArray<int>(ds.getStr());
    }

    // get系列函数
    int getCreaterUid() const { return getSenderUid(); }
    std::vector<int> getUserList() const { return userList; }
    std::string getGroupName() const { return groupName; }
};

class CreateGroupCheck : public Data {
   public:
    //传入群主id，群聊id和创建时间
    CreateGroupCheck(int _createrId, int groupId, std::string time)
        : Data(Data::CREATE_GROUP_CHECK, _createrId, groupId, time, "") {}

    //解码函数
    CreateGroupCheck(const std::string& s) : Data(s) {}
    CreateGroupCheck(const Data& d) : Data(d) {}

    // get系列函数
    int getCreaterId() const { return getSenderUid(); }
    int getGroupId() const { return getReceiverUid(); }
};

class AddGroupMessage : public Data {
   public:
    //传入加群人的id，群聊id，加群时间和备注
    explicit AddGroupMessage(int _userId,
                             int _groupId,
                             const std::string& _time,
                             std::string& _content)
        : Data(Data::ADD_GROUP_MESSAGE, _userId, _groupId, _time, _content) {}

    explicit AddGroupMessage(const std::string& s) : Data(s) {}
    explicit AddGroupMessage(const Data& d) : Data(d) {}

    int getUserId() const { return getSenderUid(); }
    int getGroupId() const { return getReceiverUid(); }
};

class AddGroupCheck : public Data {
    int state;

   public:
    //传入收到的加群信息和之后的加群状态
    explicit AddGroupCheck(const AddGroupMessage& message, int _state)
        : Data(Data::ADD_GROUP_CHECK,
               message.getUserId(),
               message.getGroupId(),
               message.getTime(),
               encodeInt(_state)),
          state(_state) {}

    //传入加群者id，群聊id，时间和状态
    explicit AddGroupCheck(int _userId,
                           int _groupId,
                           const std::string& _time,
                           int _state)
        : Data(Data::ADD_GROUP_CHECK,
               _userId,
               _groupId,
               _time,
               encodeInt(_state)),
          state(_state) {}

    explicit AddGroupCheck(const std::string& s) : Data(s) {
        state = decodeInt(getContent());
    }
    explicit AddGroupCheck(const Data& d) : Data(d) {
        state = decodeInt(getContent());
    }

    int getUserId() const { return getSenderUid(); }
    int getGroupId() const { return getReceiverUid(); }
    int getState() const { return state; }

    static const int REJECT = 0;
    static const int SUCCESS = 1;
};

class GroupInviteMessage : public Data {
    GroupInfo groupInfo;

   public:
    GroupInviteMessage(int _senderUid,
                       int _receiverUid,
                       const std::string& _time,
                       GroupInfo _info)
        : Data(Data::GROUP_INVITE_MESSAGE,
               _senderUid,
               _receiverUid,
               _time,
               encodeGroupInfo(_info)),
          groupInfo(_info) {}

    GroupInviteMessage(const std::string& s) : Data(s) {
        DataStream ds(getContent());
        ds >> groupInfo;
    }
    GroupInviteMessage(const Data& d) : Data(d) {
        DataStream ds(getContent());
        ds >> groupInfo;
    }

    GroupInfo getGroupInfo() const { return groupInfo; }
};