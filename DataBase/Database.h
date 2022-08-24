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
	// 提供给外界得到数据库实例
	static Database* getDatabase();

	// 给外界提供的数据库操纵函数
	// 插入操作
	void insertUserTable(UserInfo user);
	void insertGroupTable(GroupInfo group);
	void insertChatMsgTable(ChatMessage  msg);
	void insertFriendShipTable(int userId1,int userId2);
	void insertGroupShipTable(int groupid,int userId, int permission=2); // 0为群主 1为管理员 2 为普通成员
	// 查找操作

	// 得到id 类型
	std::vector<int>* getAllUserId();       // 得到所有用户的 id
	std::vector<int>* getAllGroupId();      // 得到所有群聊的 id
	std::vector<int>* getFriendsId(int userId);  // 得到 所有朋友的 id
	std::vector<int>* getGroupMembersId(int groupId); // 得到群聊成员的 id
	std::vector<int>* getGroupListId(int userId);     // 得到用户所加群的 id
	// 得到具体的类型
	UserInfo getUserInfo(int userId);       // 带密码的
	UserInfo getUserInfoNoPwd(int userId);  // 不带密码的
	GroupInfo getGroupInfo(int groupId);    // 得到group 信息

	int getUserPermission(int userId, int groupId);                // 得到用户在群聊中的权限
	// 得到的聊天记录按时间的先后进行排序，坐标小的时间近
	std::vector<ChatMessage>* getUserChatMessage(int Id1,int Id2); // 得到两个用户的聊天记录
	std::vector<ChatMessage>* getGroupChatMessage(int groupId);    // 得到群聊的聊天记录
	std::vector<UserInfo>* getUserFriends(int userId);             // 得到用户的朋友信息 id+name
	std::vector<UserInfo>* getGroupMembersNoPwd(int groupId);      // 得到群聊成员的信息 id+name
	std::vector<GroupInfo>* getGroupList(int userId);              // 得到用户所加群的信息 id+name
	std::vector<UserInfo>* getAllUserNoPwd();                      // 得到所有用户的信息 id+name
	std::vector<GroupInfo>* getAllGroup();                         // 得到全部的群信息 id+name

	// 更新操作
	
	void changeUserName(int userId,std::string newName);      // 更改用户名字
	void changeUserPwd(int userId, std::string newPwd);       // 更爱用户密码
	void changeGroupName(int groupId, std::string newName);   // 更改群聊名字
	void changeUserPermission(int userID,int groupId,int per);// 更改用户权限 0为群主 1为管理员 2为普通成员
	                                                          // 默认情况下为 普通成员 2

	// 删除操作 
	void delUser(int userId);                                 // 注销账户                                   
	void delUserFriend(int userId1, int userId2);             // 删除好友关系
	void delGroupShip(int userId, int groupId);               // 删除群聊关系
	void delGroup(int groupId);                               // 注销群聊

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
	// 构造函数私有
	Database();
	// 指向自身的静态指针，获取唯一实例
	static Database* db;
	sqlite3* handler;
	char* errormsg;     // 记录错误的信息
	static const std::string path;   // 记录数据库所在的位置

	// 定义创建表的函数 私有
	void createUserTable();
	void createGroupTable();
	void createChatMsgTable();
	void createFeiendShipTable();
	void createGroupShipTable();
};

