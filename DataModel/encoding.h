#ifndef ENCODING_H
#define ENCODING_H

#include <string>
#include <vector>

namespace Encoding {
//对于int的编码
inline std::string encodeInt(int val) {
    std::string s = "";
    for (int i = 0; i < 32; i += 8) {
        s += (unsigned char)((val >> i) & 0xff);
    }
    return s;
}
//对于int的解码
inline int decodeInt(const std::string &s) {
    int val = 0;
    for (int i = 0; i < 4; i++) {
        val |= (unsigned char)(s[i]) << (i * 8);
    }
    return val;
}
//对于std::string的编码
inline std::string encodeStr(const std::string &str) {
    int len = str.length();
    return encodeInt(len) + str;
}
//对于std::string的解码
inline std::pair<int, std::string> decodeStr(const std::string &s) {
    int len = decodeInt(s.substr(0, 4));
    return std::make_pair(len, s.substr(4, len));
}

//用于解析编码串的对象
class DataStream {
    std::string s;

   public:
    DataStream(std::string _s) : s(_s) {}
    std::string getStr() const {
        return s;
    }
    friend DataStream& operator>>(DataStream& in, int& val) {
        val = decodeInt(in.s);
        in.s = in.s.substr(4);
        return in;
    }
    friend DataStream& operator>>(DataStream& in, std::string& val) {
        auto ps = decodeStr(in.s);
        val = ps.second;
        in.s = in.s.substr(4 + ps.first);
        return in;
    }
    friend DataStream& operator<<(DataStream &out, const int &val) {
        out.s += encodeInt(val);
        return out;
    }
    friend DataStream& operator<<(DataStream &out, const std::string &val) {
        out.s += encodeStr(val);
        return out;
    }
};

class Data {
    /*
    使用tcp发送数据包的标准格式：
        | dataSize | type | senderUid | receiverUid | timeSize | time | contentSize | content |
        dataSize    ：  int，整个数据包的总大小
        type        ：  int，数据包的类型
        senderUid   ：  int，数据发送者的uid
        receiverUid ：  int，数据接受者的uid，  注意，服务端的uid默认为0
        timeSize    ：  int，时间标识串的长度
        time        ：  std::string，表示数据包发送时间的字符串
        contentSize ：  int，数据内容的长度
        content     ：  std::string，具体数据的内容
    */
    int type, senderUid, receiverUid;
    std::string time, content;

   public:
    //将数据包拆分成小段后每段的标准长度
    static const int SplitLength = 1024;
    
    //构造一个数据包的构造函数，其中dataSize和timeSize在构造函数内部自动计算
    //只需要提供type、senderUid、receiverUid、time和content即可
    explicit Data(int _type,
                  int _senderUid,
                  int _receiverUid,
                  const std::string& _time,
                  const std::string& _content);
    //从一个按照规定格式编码的二进制串中构造变量，相当于对串进行解码，构造后即可使用所有的get函数获取数据对象内容
    explicit Data(const std::string &data);
    //将一个对象进行编码，返回一个使用std::string存储的二进制串
    std::string encode() const;
    //将数据包按照规定大小切分，便于网络传输
    std::vector<std::string> splitDataPack() const;

    //一系列get函数，用于获取对象内部的private成员
    int getType() const;
    int getSenderUid() const;
    int getReceiverUid() const;
    std::string getTime() const;
    std::string getContent() const;

//下面是关于Data类的type的标识符
    static const int LOGIN_MESSAGE = 1;
    static const int LOGIN_CHECK = 2;
    static const int REGISTER_MESSAGE = 3;
};
}  // namespace Encoding

#endif //encoding.h