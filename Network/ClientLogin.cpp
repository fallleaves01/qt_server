#include "scanner.h"

bool SocketClient::checkOnline(int uid) {
    return userClient().count(uid);
}

void SocketClient::loginWithUid(int uid) {
    userUid = uid;
    userClient()[uid] = this;
}

void SocketClient::sendDataToUid(int uid, const Data &d) {
    if (checkOnline(uid)) {
        userClient()[uid]->sendData(d);
        std::cerr << "send data to " << uid;
    } else {
        //缓存消息
        std::cerr << "user " << uid << " offline";
    }
}