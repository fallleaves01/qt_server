# include <iostream>
# include "Database.h"
# include "UserInfo.h"
# include "GroupInfo.h"
using namespace std;

void printUserInfo(UserInfo ref) {
	cout << ref.getId() << " " << ref.getName() << " " << ref.getPwd() << endl;;
}
void printGroupInfo(GroupInfo ref) {
	cout << ref.getId() << " " << ref.getName() << endl;
}
void printChatMsg(ChatMessage ref) {
	cout << ref.getSender() << " " << ref.getReceiver() << " " << ref.getTimeStemp() << " " << ref.getContent() << " " << endl;
}
int main()
{
	vector<ChatMessage>* msg = Database::getDatabase()->getUserChatMessage(1001,1003);
	for (int i = 0; i < msg->size(); ++i) {
		printChatMsg((* msg)[i]);
	}
	return 0;
}

