#pragma once
# include <string>

class ChatMessage
{
public:
    explicit ChatMessage(int sender, int receiver = 0,const std::string time=" ", const std::string content = ""); // ��ʾ���캯��
    int getSender() const;
    int getReceiver() const;
    std::string getTimeStemp() const; //�����Ϣ��ʱ���
    std::string getContent() const; //for images, store Img's baseName(with no Path)
private:
    int sender;     // ������Ϣ�ķ�����
    int receiver;   // ������Ϣ�Ľ�����
    std::string time_stemp; // ������Ϣ�ķ���ʱ��
    std::string content;    // ���͵���Ϣ����

};

