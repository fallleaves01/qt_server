#pragma once
# include <string>

class ChatMessage
{
public:
    explicit ChatMessage(int sender, int receiver = 0,const std::string time=" ", const std::string content = ""); // 显示构造函数
    int getSender() const;
    int getReceiver() const;
    std::string getTimeStemp() const; //获得消息的时间戳
    std::string getContent() const; //for images, store Img's baseName(with no Path)
private:
    int sender;     // 聊天信息的发送者
    int receiver;   // 聊天信息的接收者
    std::string time_stemp; // 聊天信息的发送时间
    std::string content;    // 发送的信息内容

};

