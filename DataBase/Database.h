# pragma once
# include "sqlite3.h"
# include <string>
# include "UserInfo.h"
# include "GroupInfo.h"
# include <iostream>
# include "ChatMessage.h"
# include <vector>
class Database
{
public:
	// �ṩ�����õ����ݿ�ʵ��
	static Database* getDatabase();

	// ������ṩ�����ݿ���ݺ���
	// �������
	void insertUserTable(UserInfo user);
	void insertGroupTable(GroupInfo group);
	void insertChatMsgTable(ChatMessage  msg);
	void insertFriendShipTable(int userId1,int userId2);
	void insertGroupShipTable(int groupid,int userId, int permission=2); // 0ΪȺ�� 1Ϊ����Ա 2 Ϊ��ͨ��Ա
	// ���Ҳ���

	// �õ�id ����
	std::vector<int>* getAllUserId();       // �õ������û��� id
	std::vector<int>* getAllGroupId();      // �õ�����Ⱥ�ĵ� id
	std::vector<int>* getFriendsId(int userId);  // �õ� �������ѵ� id
	std::vector<int>* getGroupMembersId(int groupId); // �õ�Ⱥ�ĳ�Ա�� id
	std::vector<int>* getGroupListId(int userId);     // �õ��û�����Ⱥ�� id
	// �õ����������
	UserInfo getUserInfo(int userId);       // �������
	UserInfo getUserInfoNoPwd(int userId);  // ���������
	GroupInfo getGroupInfo(int groupId);    // �õ�group ��Ϣ

	int getUserPermission(int userId, int groupId);                // �õ��û���Ⱥ���е�Ȩ��
	// �õ��������¼��ʱ����Ⱥ������������С��ʱ���
	std::vector<ChatMessage>* getUserChatMessage(int Id1,int Id2); // �õ������û��������¼
	std::vector<ChatMessage>* getGroupChatMessage(int groupId);    // �õ�Ⱥ�ĵ������¼
	std::vector<UserInfo>* getUserFriends(int userId);             // �õ��û���������Ϣ id+name
	std::vector<UserInfo>* getGroupMembersNoPwd(int groupId);      // �õ�Ⱥ�ĳ�Ա����Ϣ id+name
	std::vector<GroupInfo>* getGroupList(int userId);              // �õ��û�����Ⱥ����Ϣ id+name
	std::vector<UserInfo>* getAllUserNoPwd();                      // �õ������û�����Ϣ id+name
	std::vector<GroupInfo>* getAllGroup();                         // �õ�ȫ����Ⱥ��Ϣ id+name

	// ���²���
	
	void changeUserName(int userId,std::string newName);      // �����û�����
	void changeUserPwd(int userId, std::string newPwd);       // �����û�����
	void changeGroupName(int groupId, std::string newName);   // ����Ⱥ������
	void changeUserPermission(int userID,int groupId,int per);// �����û�Ȩ�� 0ΪȺ�� 1Ϊ����Ա 2Ϊ��ͨ��Ա
	                                                          // Ĭ�������Ϊ ��ͨ��Ա 2

	// ɾ������ 
	void delUser(int userId);                                 // ע���˻�                                   
	void delUserFriend(int userId1, int userId2);             // ɾ�����ѹ�ϵ
	void delGroupShip(int userId, int groupId);               // ɾ��Ⱥ�Ĺ�ϵ
	void delGroup(int groupId);                               // ע��Ⱥ��

private:
	void initDB();
	class DelClass
	{
	public:
		~DelClass() {
			if (Database::db != nullptr) {
				delete Database::db;
			}
		}
	};
	DelClass delClass;
	// ���캯��˽��
	Database();
	// ָ������ľ�ָ̬�룬��ȡΨһʵ��
	static Database* db;
	sqlite3* handler;
	char* errormsg;     // ��¼�������Ϣ
	static const std::string path;   // ��¼���ݿ����ڵ�λ��

	// ���崴����ĺ��� ˽��
	void createUserTable();
	void createGroupTable();
	void createChatMsgTable();
	void createFeiendShipTable();
	void createGroupShipTable();
};

