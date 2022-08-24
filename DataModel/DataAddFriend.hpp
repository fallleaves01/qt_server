#pragma once
#include "encoding.h"
using namespace Encoding;

class AddFriendMessage : public Data {
   public:
    //传入发起方、接收方的uid，添加的时间以及添加的备注
    explicit AddFriendMessage(int _senderUid,
                              int _receiverUid,
                              const std::string& _time,
                              const std::string& _content)
        : Data(Data::ADDFRIEND_MESSAGE,
               _senderUid,
               _receiverUid,
               _time,
               _content) {}

    //对应的解码函数
    explicit AddFriendMessage(const std::string& s) : Data(s) {}
    explicit AddFriendMessage(const Data& d) : Data(d) {}
};

class AddFriendCheck : public Data {
   public:
    int state;
    //传入添加好友信息和添加的状态
    explicit AddFriendCheck(const AddFriendMessage& message, int _state)
        : Data(Data::ADDFRIEND_CHECK,
               message.getSenderUid(),
               message.getReceiverUid(),
               message.getTime(),
               encodeInt(_state)),
          state(_state) {}

    //对应的解码函数
    explicit AddFriendCheck(const std::string& s) : Data(s) {
        DataStream ds(getContent());
        ds >> state;
    }
    explicit AddFriendCheck(const Data& d) : Data(d) {
        DataStream ds(getContent());
        ds >> state;
    }

    //下面是用于表示状态的标识符
    static const int REJECT = 0;
    static const int SUCCESS = 1;

    // get系列函数
    int getState() const { return state; }
};