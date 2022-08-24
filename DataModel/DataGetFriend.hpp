#include "encoding.h"
#include "../DataBase/UserInfo.h"
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

inline DataStream &operator<<(DataStream &ds, UserInfo info) {
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