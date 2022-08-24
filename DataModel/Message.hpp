#pragma once
#include "encoding.h"
#include "../DataBase/ChatMessage.h"
#include "../DataBase/UserInfo.h"
#include "../DataBase/GroupInfo.h"
using namespace Encoding;

class DFriendMessage : public Data {
   public:
    //传入发送者id，接收者id，时间和信息内容
    DFriendMessage(int _senderUid,
                   int _receiverUid,
                   const std::string& _time,
                   const std::string& _content)
        : Data(Data::FRIEND_MESSAGE,
               _senderUid,
               _receiverUid,
               _time,
               _content) {}
    //传入ChatMessage类
    DFriendMessage(const ChatMessage& message)
        : Data(Data::FRIEND_MESSAGE,
               message.getSender(),
               message.getReceiver(),
               message.getTimeStemp(),
               message.getContent()) {}

    DFriendMessage(const std::string& s) : Data(s) {}
    DFriendMessage(const Data& d) : Data(d) {}
};

class DGroupMessage : public Data {
   public:
    //传入发送者id，群聊id，时间和信息内容
    DGroupMessage(int _senderUid,
                  int _groupId,
                  const std::string& _time,
                  const std::string& _content)
        : Data(Data::FRIEND_MESSAGE,
               _senderUid,
               _groupId,
               _time,
               _content) {}
    //传入ChatMessage类
    DGroupMessage(const ChatMessage& message)
        : Data(Data::FRIEND_MESSAGE,
               message.getSender(),
               message.getReceiver(),
               message.getTimeStemp(),
               message.getContent()) {}

    DGroupMessage(const std::string &s) : Data(s) {}
    DGroupMessage(const Data &d) : Data(d) {}

    int getGroupId() const {
        return getReceiverUid();
    }
};

inline DataStream &operator<<(DataStream &ds, const UserInfo &info) {
    ds << info.getId() << info.getName();
    return ds;
}
inline DataStream &operator>>(DataStream &ds, UserInfo &info) {
    int id;
    std::string name;
    ds >> id >> name;
    info = UserInfo(id, name);
    return ds;
}

inline DataStream &operator<<(DataStream &ds, const GroupInfo &info) {
    ds << info.getId() << info.getName();
    return ds;
}
inline DataStream &operator>>(DataStream &ds, GroupInfo &info) {
    int id;
    std::string name;
    ds >> id >> name;
    info = GroupInfo(id, name);
    return ds;
}

inline DataStream &operator<<(DataStream &ds, const ChatMessage &message) {
    ds << message.getSender();
    ds << message.getReceiver();
    ds << message.getTimeStemp();
    ds << message.getContent();
    return ds;
}
inline DataStream &operator>>(DataStream &ds, ChatMessage &message) {
    int sender, receiver;
    std::string time, content;
    ds >> sender >> receiver >> time >> content;
    return ds;
}