# include "Database.h"

Database* Database::db = nullptr;

const std::string Database::path = "database.db";

Database::Database()
{
	initDB();
}

void Database::initDB()
{
	int val = sqlite3_open("database.db", &handler);
	if (val != SQLITE_OK) {
		std::cout << "open database.db error. " << std::endl;
		exit(0);
	}
	// 创建五张表
	createUserTable();
	createGroupTable();
	createChatMsgTable();
	createFeiendShipTable();
	createGroupShipTable();
	// 关闭数据库
	sqlite3_close(handler);
}
Database* Database::getDatabase()
{
	if (Database::db == nullptr) {
		Database::db = new Database();
	}
	return Database::db;
}
void Database::createUserTable()
{
	int val = sqlite3_exec(handler,
		"CREATE TABLE UserTable(\
			Id INTEGER PRIMARY KEY,\
			Name VARCHAR(20) NOT NULL,\
			Pwd VARCHAR(20)  NOT NULL);",
		NULL,
		NULL,
		&errormsg);
	if (val != SQLITE_OK) {
		std::cout << errormsg << std::endl;
	}
}
void Database::createGroupTable()
{
	int val = sqlite3_exec(handler,
		"CREATE TABLE GroupTable(\
		Id INTEGER PRIMARY KEY,\
		Name VARCHAR(20) NOT NULL); ",
		NULL,
		NULL,
		&errormsg);
	if (val != SQLITE_OK) {
		std::cout << errormsg << std::endl;
	}
}

void Database::createChatMsgTable()
{
	int val = sqlite3_exec(handler,
		"CREATE TABLE ChatMsgTable(\
		Sender INTEGER,\
		Receiver INTEGER,\
		Time VARCHAR(20),\
		Content VARCHAR(1024),\
		PRIMARY KEY (Sender,Receiver,Time));",
		NULL,
		NULL,
		&errormsg);
	if (val != SQLITE_OK) {
		std::cout << errormsg << std::endl;
	}
}
void Database::createFeiendShipTable()
{
	int val = sqlite3_exec(handler,
		"CREATE TABLE FriendShipTable(\
		Id1 INTEGER,\
		Id2 INTEGER,\
		PRIMARY KEY(Id1, Id2),\
		FOREIGN KEY (Id1) REFERENCES UserTable(Id),\
		FOREIGN KEY (Id2) REFERENCES UserTable(Id)); ",
		NULL,
		NULL,
		&errormsg);
	if (val != SQLITE_OK) {
		std::cout << errormsg << std::endl;
	}
}
void Database::createGroupShipTable()
{
	int val = sqlite3_exec(handler,
		"CREATE TABLE GroupShipTable(\
		GroupId INTEGER,\
		UserId INTEGER,\
		Permission INTEGER,\
		PRIMARY KEY(GroupId, UserId),\
		FOREIGN KEY (GroupId) REFERENCES GroupTable(Id),\
		FOREIGN KEY (UserId)  REFERENCES UserTable(Id)); ",
		NULL,
		NULL,
		&errormsg);
	if (val != SQLITE_OK) {
		std::cout << errormsg << std::endl;
	}
}
void Database::insertUserTable(UserInfo user)
{
	int id = user.getId();
	std::string name = user.getName();
	std::string pwd = user.getPwd();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "insert into UserTable values(?,?,?);";
		sqlite3_prepare_v2(handler, sql.c_str(),-1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, id);
		sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, pwd.c_str(), -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_finalize(stmt);
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::insertGroupTable(GroupInfo group)
{
	int id = group.getId();
	std::string name = group.getName();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "insert into GroupTable values(?,?);";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, id);
		sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::insertChatMsgTable(ChatMessage msg)
{
	int sender = msg.getSender(); 
	int receiver = msg.getReceiver();
	std::string time = msg.getTimeStemp();
	std::string content = msg.getContent();

	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {

		sqlite3_stmt* stmt;
		std::string sql = "insert into ChatMsgTable values(?,?,?,?);";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, sender);
		sqlite3_bind_int(stmt, 2, receiver);
		sqlite3_bind_text(stmt, 3, time.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 4, content.c_str(), -1, SQLITE_STATIC);

		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::insertFriendShipTable(int userId1, int userId2)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "insert into FriendShipTable values(?,?);";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId1);
		sqlite3_bind_int(stmt, 2, userId2);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::insertGroupShipTable(int groupid, int userId,int permission)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "insert into GroupShipTable values(?,?,?)";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupid);
		sqlite3_bind_int(stmt, 2, userId);
		sqlite3_bind_int(stmt, 3, permission);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}

// 查找
UserInfo Database::getUserInfo(int userId)
{
	UserInfo temp;
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Id,Name,Pwd from UserTable where Id=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW){
			int id = sqlite3_column_int(stmt, 0);
			std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			std::string pwd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			temp = UserInfo(id,name,pwd);
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
UserInfo Database::getUserInfoNoPwd(int userId)
{
	UserInfo temp;
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Id,Name from UserTable where Id=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			temp = UserInfo(id, name);
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
GroupInfo Database::getGroupInfo(int groupId)
{
	GroupInfo temp;
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Id,Name from GroupTable where Id=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			temp = GroupInfo(id, name);
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<int>* Database::getAllUserId()
{
	std::vector<int>* temp = new std::vector<int>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Id from UserTable;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt)== SQLITE_ROW) {
			temp->push_back(sqlite3_column_int(stmt, 0));
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<int>* Database::getAllGroupId()
{
	std::vector<int>* temp = new std::vector<int>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {

		sqlite3_stmt* stmt;
		std::string sql = "select Id from GroupTable;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			temp->push_back(sqlite3_column_int(stmt, 0));
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}

	return temp;
}
// 只得到朋友的id 与 name pwd置为空字符串
std::vector<int>* Database::getFriendsId(int userId)
{
	std::vector<int>* temp = new std::vector<int>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Id1,Id2 from FriendShipTable where Id1=? or Id2=?";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt,1, userId);
		sqlite3_bind_int(stmt, 2, userId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id1 = sqlite3_column_int(stmt, 0);
			int id2 = sqlite3_column_int(stmt, 1);
			if (id1 != userId) {
				temp->push_back(id1);
			}
			else {
				temp->push_back(id2);
			}
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<int>* Database::getGroupMembersId(int groupId)
{
	std::vector<int>* temp = new std::vector<int>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select UserId from GroupShipTable where GroupId=? ;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt,1, groupId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			temp->push_back(id);
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<int>* Database::getGroupListId(int userId)
{
	std::vector<int>* temp = new std::vector<int>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {

		sqlite3_stmt* stmt;
		std::string sql = "select GroupId from GroupShipTable where UserId=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt,0);
			temp->push_back(id);
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
int Database::getUserPermission(int userId, int groupId)
{
	int per=2;
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Permission from GroupShipTable where GroupId=? and UserId=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupId);
		sqlite3_bind_int(stmt, 2, userId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			per = sqlite3_column_int(stmt, 0);
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return per;
}
std::vector<ChatMessage>* Database::getUserChatMessage(int Id1,int Id2)
{
	std::vector<ChatMessage>* temp = new std::vector<ChatMessage>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		int sender, receiver;
		std::string time, content;
		std::string sql = "select * from ChatMsgTable where (Sender=? and Receiver=?) or (Sender=? and Receiver=?);";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt,1, Id1);
		sqlite3_bind_int(stmt, 2, Id2);
		sqlite3_bind_int(stmt, 3, Id2);
		sqlite3_bind_int(stmt, 4, Id1);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			sender = sqlite3_column_int(stmt, 0);
			receiver= sqlite3_column_int(stmt, 1);
			time= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			content = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			temp->push_back(ChatMessage(sender,receiver,time,content));
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<ChatMessage>* Database::getGroupChatMessage(int groupId)
{
	std::vector<ChatMessage>* temp = new std::vector<ChatMessage>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		int sender, receiver;
		std::string time, content;
		std::string sql = "select * from ChatMsgTable where Receiver=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupId);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			sender = sqlite3_column_int(stmt, 0);
			receiver = sqlite3_column_int(stmt, 1);
			time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			content = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			temp->push_back(ChatMessage(sender, receiver, time, content));
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<UserInfo>* Database::getUserFriends(int userId) 
{
	std::vector<UserInfo>* temp = new std::vector<UserInfo>();
	std::vector<int>* id = Database::getDatabase()->getFriendsId(userId);
	for (int i = 0; i < (*id).size(); ++i) {
		temp->push_back(Database::getDatabase()->getUserInfoNoPwd((*id)[i]));
	}
	delete id;
	return temp;
}
std::vector<UserInfo>* Database::getGroupMembersNoPwd(int groupId)
{
	std::vector<UserInfo>* temp = new std::vector<UserInfo>();
	std::vector<int>* id = Database::getDatabase()->getGroupMembersId(groupId);
	for (int i = 0; i < (*id).size(); ++i) {
		temp->push_back(Database::getDatabase()->getUserInfoNoPwd((*id)[i]));
	}
	delete id;
	return temp;
}
std::vector<GroupInfo>* Database::getGroupList(int userId)
{
	std::vector<GroupInfo>* temp = new std::vector<GroupInfo>();
	std::vector<int>* id = Database::getDatabase()->getGroupListId(userId);
	for (int i = 0; i < (*id).size(); ++i) {
		temp->push_back(Database::getDatabase()->getGroupInfo((*id)[i]));
	}
	delete id;
	return temp;
}
std::vector<UserInfo>* Database::getAllUserNoPwd()
{
	std::vector<UserInfo>* temp = new std::vector<UserInfo>();
	int id;
	std::string name;
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "select Id,Name from UserTable;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			name= reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
			temp->push_back(UserInfo(id,name));
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
	return temp;
}
std::vector<GroupInfo>* Database::getAllGroup()
{
	int id;
	std::string name;
	std::vector<GroupInfo>* temp = new std::vector<GroupInfo>();
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {

		sqlite3_stmt* stmt;
		std::string sql = "select * from GroupTable;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		// 处理查找到的每一条信息
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			temp->push_back(GroupInfo(id, name));
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}

	return temp;
}

// 更新操作

void Database::changeUserName(int userId, std::string newName)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "update UserTable set Name=? where Id=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_text(stmt,1,newName.c_str(),-1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, userId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::changeUserPwd(int userId, std::string newPwd)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "update UserTable set Pwd=? where Id=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_text(stmt, 1, newPwd.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, userId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::changeGroupName(int groupId, std::string newName)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "update GroupTable set Name=? where Id=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, groupId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::changeUserPermission(int userID, int groupId, int per)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "update GroupShipTable set Permission=? where GroupId=? and UserId=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, per);
		sqlite3_bind_int(stmt, 2, groupId);
		sqlite3_bind_int(stmt, 3, userID);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}

// 删除操作 
void Database::delUser(int userId)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		// 删除该成员的所有好友信息
		std::string sql = "delete from FriendShipTable where Id1=? or Id2=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId);
		sqlite3_bind_int(stmt, 2, userId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_reset(stmt);
		// 删除群 与该成员的所有关系信息
		sql = "delete from GroupShipTable where UserId=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_reset(stmt);
		// 删除群信息
		sql = "delete from UserTable where Id=?";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::delUserFriend(int userId1, int userId2)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "delete from FriendShipTable where (Id1=? and Id2=?) or (Id1=? and Id2=?);";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, userId1);
		sqlite3_bind_int(stmt, 2, userId2);
		sqlite3_bind_int(stmt, 3, userId2);
		sqlite3_bind_int(stmt, 4, userId1);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::delGroupShip(int userId, int groupId)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		std::string sql = "delete from GroupShipTable where GroupId=? and UserId=? ;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupId);
		sqlite3_bind_int(stmt, 2, userId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}
void Database::delGroup(int groupId)
{
	if (sqlite3_open(path.c_str(), &handler) == SQLITE_OK) {
		sqlite3_stmt* stmt;
		// 删除群 与成员关系信息
		std::string sql = "delete from GroupShipTable where GroupId=?;";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}

		sqlite3_reset(stmt);
		// 删除群信息
		sql = "delete from GroupTable where Id=?";
		sqlite3_prepare_v2(handler, sql.c_str(), -1, &stmt, 0);
		sqlite3_bind_int(stmt, 1, groupId);
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cout << sqlite3_errmsg(handler) << std::endl;
		}
		sqlite3_close(handler);
	}
	else {
		std::cout << "open error. " << std::endl;
	}
}