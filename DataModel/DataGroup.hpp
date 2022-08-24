#pragma once
#include "encoding.h"
using namespace Encoding;

class CreateGroupMessage : public Data {
   public:
    std::vector<int> userList;
    //传入发起方uid,添加时间和拉近群聊的人员列表
    explicit CreateGroupMessage(int _createrId,
                                std::string _time,
                                std::vector<int> _memberUids)
        : Data(Data::CREATE_GROUP_MESSAGE,
               _createrId,
               0,
               _time,
               encodeArray(_memberUids)),
          userList(_memberUids) {}

    //解码函数
    explicit CreateGroupMessage(const std::string& s) : Data(s) {
        userList = decodeArray<int>(getContent());
    }
    explicit CreateGroupMessage(Data& d) : Data(d) {
        userList = decodeArray<int>(getContent());
    }

    // get系列函数
    int getCreaterUid() const { return getSenderUid(); }
    std::vector<int> getUserList() const { return userList; }
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