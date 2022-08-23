#include "encoding.h"
using namespace Encoding;

class FriendMessage : public Data {
   public:
    //传入发送者id，接收者id，时间和信息内容
    FriendMessage(int _senderUid,
                  int _receiverUid,
                  const std::string& _time,
                  const std::string& _content)
        : Data(Data::FRIEND_MESSAGE,
               _senderUid,
               _receiverUid,
               _time,
               _content) {}

    FriendMessage(const std::string &s) : Data(s) {}
    FriendMessage(const Data &d) : Data(d) {}
};

class GroupMessage : public Data {
   public:
    //传入发送者id，群聊id，时间和信息内容
    GroupMessage(int _senderUid,
                  int _groupId,
                  const std::string& _time,
                  const std::string& _content)
        : Data(Data::FRIEND_MESSAGE,
               _senderUid,
               _groupId,
               _time,
               _content) {}

    GroupMessage(const std::string &s) : Data(s) {}
    GroupMessage(const Data &d) : Data(d) {}

    int getGroupId() const {
        return getReceiverUid();
    }
};