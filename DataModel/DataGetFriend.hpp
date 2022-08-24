#pragma once
#include "encoding.h"
#include "Message.hpp"
using namespace Encoding;

class GetUserInfo : public Data {
   public:
    GetUserInfo(int _senderUid, int _userId, const std::string& _time)
        : Data(Data::GET_USER_INFO, _senderUid, _userId, _time, "") {}
    GetUserInfo(const std::string& s) : Data(s) {}
    GetUserInfo(const Data& d) : Data(d) {}

    int getUserId() const { return getReceiverUid(); }
};

class DUserInfo : public Data {
    UserInfo info;

   public:
    DUserInfo(const UserInfo& _info, int _state)
        : Data(Data::USER_INFO, _info.getId(), _state, "", _info.getName()),
          info(_info) {}

    DUserInfo(const std::string s) : Data(s) {
        info = UserInfo(getSenderUid(), getContent());
    }
    DUserInfo(const Data &d) : Data(d) {
        info = UserInfo(getSenderUid(), getContent());
    }

    UserInfo getInfo() const {
        return info;
    }
    int getState() const {
        return getReceiverUid();
    }

    static const int OFFLINE = 0;
    static const int ONLINE = 1;
};

class GetFriendList : public Data {
    GetFriendList(int _senderUid, const std::string _time)
        : Data(Data::GET_FRIEND_LIST, _senderUid, 0, _time, "") {}
    
    GetFriendList(const std::string &s) : Data(s) {}
    GetFriendList(const Data &d) : Data(d) {}
};

class DFriendList : public Data {
    std::vector<UserInfo> friendList;
    DFriendList(int _uid, std::vector<UserInfo> _friendList)
        : Data(Data::FRIEND_LIST, _uid, 0, "", encodeArray(_friendList)), friendList(_friendList) {}

    DFriendList(const std::string &s) : Data(s) {
        friendList = decodeArray<UserInfo>(getContent());
    }
    DFriendList(const Data &d) : Data(d) {
        friendList = decodeArray<UserInfo>(getContent());
    }

    std::vector<UserInfo> getFriendList() {
        return friendList;
    }
};

class GetFriendMessage : public Data {
   public:
    GetFriendMessage(int _senderUid, int _friendUid, const std::string& _time)
        : Data(Data::GET_FRIEND_MESSAGE, _senderUid, _friendUid, _time, "") {}

    GetFriendMessage(const std::string& s) : Data(s) {}
    GetFriendMessage(const Data& d) : Data(d) {}

    int getFriendUid() const { return getReceiverUid(); }
};

class DFriendMessageList : public Data {
    std::vector<ChatMessage> message;

   public:
    DFriendMessageList(int _senderUid,
                       int _friendUid,
                       const std::vector<ChatMessage>& _message)
        : Data(Data::FRIEND_MESSAGE_LIST,
               _senderUid,
               _friendUid,
               "",
               encodeArray(_message)),
          message(_message) {}

    DFriendMessageList(const std::string &s) : Data(s) {
        ChatMessage tmp(0);
        message = decodeArray<ChatMessage>(getContent(), tmp);
    }
    DFriendMessageList(const Data &d) : Data(d) {
        ChatMessage tmp(0);
        message = decodeArray<ChatMessage>(getContent(), tmp);
    }

    std::vector<ChatMessage> getMessageList() const {
        return message;
    }
};