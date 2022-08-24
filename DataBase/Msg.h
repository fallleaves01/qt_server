#pragma once
# include "ChatMessage.h"
class Msg:public ChatMessage
{
public:
	Msg(int _type,int sender, int receiver = 0, const std::string time = " ", const std::string content = "")
		:ChatMessage(sender, receiver, time, content), type(_type)
	{

	}
private:
	int type;
public:
	int getType() const
	{
		return type;
	}
};

