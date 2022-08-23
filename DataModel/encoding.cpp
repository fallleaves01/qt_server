#include "encoding.h"

Encoding::Data::Data(int _type,
                     int _senderUid,
                     int _receiverUid,
                     const std::string& _time,
                     const std::string& _content)
    : type(_type),
      senderUid(_senderUid),
      receiverUid(_receiverUid),
      time(_time),
      content(_content) {
}

Encoding::Data::Data(std::string data) {
    type = decode(data.substr(4, 4));
    senderUid = decode(data.substr(8, 4));
    receiverUid = decode(data.substr(12, 4));
    auto ptime = decodeStr(data.substr(16));
    int timeSize = ptime.first + 4;
    time = ptime.second;
    auto pcontent = decodeStr(data.substr(16 + timeSize));
    content = pcontent.second;
}

std::string Encoding::Data::encode() const {
    int dataSize = 24 + time.length() + content.length();
    std::string data = Encoding::encode(dataSize);
    data += Encoding::encode(type);
    data += Encoding::encode(senderUid);
    data += Encoding::encode(receiverUid);
    data += Encoding::encodeStr(time);
    data += Encoding::encodeStr(content);
    return data;
}

std::vector<std::string> Encoding::Data::splitDataPack() const {
    std::string data = this->encode();
    std::vector<std::string> dataPack;
    for (int i = 0; i < (int)data.length(); i += SplitLength) {
        dataPack.emplace_back(data.substr(i, SplitLength));
    }
    return dataPack;
}

int Encoding::Data::getType() const {
    return type;
}
int Encoding::Data::getSenderUid() const {
    return senderUid;
}
int Encoding::Data::getReceiverUid() const {
    return receiverUid;
}
std::string Encoding::Data::getTime() const {
    return time;
}
std::string Encoding::Data::getContent() const {
    return content;
}