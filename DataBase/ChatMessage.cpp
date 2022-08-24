#include "ChatMessage.h"

// ������Ϣ�࣬ÿһ����Ϣ����һ��ʵ��

ChatMessage::ChatMessage(int sender, int receiver, const std::string time, const std::string content):
    sender(sender), receiver(receiver),time_stemp(time), content(content)
{
}

int ChatMessage::getSender() const {
    return sender;
}

int ChatMessage::getReceiver() const {
    return receiver;
}

std::string ChatMessage::getTimeStemp() const {
    return time_stemp;
}

std::string ChatMessage::getContent() const {
    return content;
}