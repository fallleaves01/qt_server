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
void printChatMsg(Msg ref) {
	cout <<ref.getType()<<" " << ref.getSender() << " " << ref.getReceiver() << " " << ref.getTimeStemp() << " " << ref.getContent() << " " << endl;
}
int main()
{


	return 0;
}

