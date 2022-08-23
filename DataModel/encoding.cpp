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
      content(_content) {}

Encoding::Data::Data(const std::string &data) {
    DataStream ds(data.substr(4));
    ds >> type >> senderUid >> receiverUid >> time >> content;
}

std::string Encoding::Data::encode() const {
    DataStream ds("");
    ds << type << senderUid << receiverUid << time << content;
    int dataSize = ds.getStr().length() + 4;
    return encodeInt(dataSize) + ds.getStr();
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