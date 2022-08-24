# 数据类型
## [功能型](#功能型说明)
+ [登录](#登录)
+ [注册](#注册)
+ [添加好友](#添加好友)
+ 创建群聊
+ 加入群聊
+ 邀请进入群聊

## 消息型
+ 私聊消息
+ 私聊表情
+ 群聊消息
+ 群聊表情

## 请求
+ 获取用户信息
+ 获取好友列表
+ 获取群聊信息
+ 获取群聊列表
+ 获取群聊成员
+ 获取聊天记录


# 功能型说明
## 登录
### 发起方 (LoginMessage): 传入时间、用户名和密码
+ type          ：Data::LOGIN_MESSAGE
+ senderUid     ：0，代表未登录用户
+ receiverUid   ：0，代表服务端本身
+ time          ：登录时间
+ userName      ：用户名
+ password      ：使用哈希算法加密后的密码

### 返回 (LoginCheck): 传入时间、用户名、用户Id和登陆状态
+ type          ：Data::LOGIN_CHECK
+ senderUid     ：0，代表服务端本身
+ receiverUid   ：若成功登陆，则为对应用户Id，否则为0
+ time          ：登录时间
+ userName      ：用户名
+ state         ：登录状态，具体分为
    + LoginCheck::SUCCESS ：成功登录
    + LoginCheck::USERNOTFOUND ：找不到对应用户
    + LoginCheck::WRONGPASSWORD ：密码错误

## 注册
### 发起方 (RegisterMessage) : 传入三个字符串：时间、用户名和密码
+ type          ：Data::REGISTER_MESSAGE
+ senderUid     ：0，未注册用户没有Uid
+ receiverUid   ：0，代表服务端本身
+ time          ：注册时间
+ userName      ：用户名
+ password      ：使用哈希算法加密后的密码

### 返回 ([LoginCheck](#返回-logincheck-传入时间用户名用户id和登陆状态))
+ type          ：Data::LOGIN_CHECK
+ senderUid     ：0，代表服务端本身
+ receiverUid   ：为该用户分配的uid
+ time          ：登录时间
+ userName      ：用户名
+ state         ：登录状态，具体分为
    + LoginCheck::SUCCESS ：成功登录 (成功注册用户默认为成功登陆)
    + LoginCheck::USERNOTFOUND ：找不到对应用户
    + LoginCheck::WRONGPASSWORD ：密码错误


## 添加好友
### 发起方 (AddFriendMessage) : 传入发起方、接收方的uid，添加时间和备注信息
+ type          ：Data::ADDFRIEND_MESSAGE
+ senderUid     ：添加方的Uid
+ receiverUid   ：被添加方的Uid
+ time          ：添加时间
+ content       ：备注信息
### 接收方 ([AddFriendMessage](#发起方-addfriendmessage--传入发起方接收方的uid添加时间和备注信息))
+ type          ：Data::ADDFRIEND_MESSAGE
+ senderUid     ：添加方的Uid
+ receiverUid   ：被添加方的Uid
+ time          ：注册时间
+ content       ：备注信息

### 返回 (AddFriendCheck) : 传入添加好友的数据（AddFriendMessage类），和添加的状态
+ type          ：Data::ADDFRIEND_CHECK
+ senderUid     ：添加方的Uid
+ receiverUid   ：被添加方的Uid
+ time          ：注册时间
+ state         ：添加好友的状态，分为：
    + AddFriendCheck::SUCCESS ：成功添加好友
    + AddFriendCheck::REJECT ：添加好友被拒绝

## 创建群聊
### 发起方 (CreateGroupMessage) : 传入发起方的uid，添加时间，群聊名称被拉进群聊的人员列表
+ type          ：Data::CREATE_GROUP_MESSAGE
+ createrUid    ：发起方的Uid
+ receiverUid   ：0，表示服务器
+ time          ：添加时间
+ groupName     ：群聊名称
+ userList      ：所有被拉入群聊的人员的Uid

### 返回 (CreateGroupCheck) : 传入群主id，群聊id和创建时间
+ type          ：Data::CREATE_GROUP_CHECK
+ createrUid    ：发起方的Uid
+ groupId       ：被创建出的群聊的Id
+ time          ：添加时间

## 加入群聊
### 发起方 (AddGroupMessage) : 传入加群者的uid，群聊id，加群时间和备注信息
+ type          ：Data::ADD_GROUP_MESSAGE
+ userId        ：加群方的Uid
+ groupId       ：群聊的id
+ time          ：添加时间
+ content       ：加群的备注信息

### 返回 (AddGroupCheck) : 传入加群信息和状态/传入加群者id，群聊id，加群时间和状态
+ type          ：Data::ADD_GROUP_CHECK
+ userId    ：加群方的Uid
+ groupId   ：群聊的id
+ time          ：添加时间
+ state         ：加群的状态，具体分为
    + AddGroupCheck::SUCCESS : 成功加入
    + AddGroupCheck::REJECT : 被拒绝

## 邀请进入群聊
### 发起方 (GroupInviteMessage) : 传入邀请者的uid，被邀请者的uid，添加时间和群聊信息
+ type          ：Data::GROUP_INVITE_MESSAGE
+ senderUid     ：邀请者的Uid
+ receiverUid   ：被邀请者的uid
+ time          ：添加时间
+ groupInfo     ：群聊的GroupInfo信息

### 返回 (AddGroupCheck) : 传入加群信息和状态
+ type          ：Data::ADD_GROUP_CHECK
+ userId    ：加群方的Uid
+ groupId   ：群聊的id
+ time          ：添加时间
+ state         ：加群的状态，具体分为
    + AddGroupCheck::SUCCESS : 成功加入
    + AddGroupCheck::REJECT : 被拒绝

# 消息型说明
## 私聊消息 (DFriendMessage) : 传入发送者id、接收者id、时间和信息内容或直接传入ChatMessage类
+ type          ：Data::DFRIEND_MESSAGE
+ senderUid     ：发送者的Uid
+ receiverUid   ：接收者的Uid
+ time          ：添加时间
+ content       ：信息内容
## 群聊消息 (DGroupMessage) ：传入发送者id，群聊id，时间和信息内容或直接传入ChatMessage类
+ type          ：Data::DGROUP_MESSAGE
+ senderUid     ：发送者的Uid
+ groupId       ：群聊的id
+ time          ：添加时间
+ content       ：消息具体内容

# 请求型说明
## 获取用户信息
### 请求方 (GetUserInfo): 传入请求者uid，目标用户uid和时间
+ type          ：Data::GET_USER_INFO
+ senderUid     ：请求者的Uid
+ userId        ：目标用户的Uid
+ time          ：时间

### 返回 (DUserInfo): 传入用户UserInfo，在线状态
+ type          ：Data::USER_INFO
+ userInfo      ：目标用户的UserInfo
+ onlineState   ：目标用户的在线状态，分为：
    + DUserInfo::ONLINE：在线
    + DUserInfo::OFFLINE：不在线

## 获取好友列表
### 请求方 (GetFriendList): 传入请求者uid和时间
+ type          ：Data::GET_FRIEND_LIST
+ senderUid     ：请求者的Uid
+ time          ：时间

### 返回 (DFriendList): 传入用户uid，好友列表
+ type          ：Data::FRIEND_LIST
+ userId        ：目标用户的Uid
+ friendList    ：目标用户的好友的uid数组

## 获取聊天记录
### 请求方 (GetFriendMessage): 传入请求者uid，目标好友uid和时间
+ type          ：Data::GET_FRIEND_MESSAGE
+ senderUid     ：请求者的Uid
+ friendId      ：目标好友的Uid
+ time          ：时间

### 返回 (DFriendMessageList): 传入请求者uid，好友uid和消息列表
+ type          ：Data::FRIEND_MESSAGE_LIST
+ senderUid     ：请求者的Uid
+ friendUid     ：目标好友的Uid
+ messageList   ：目标好友的ChatMessage数组

## 获取群聊信息
### 请求方 (GetGroupInfo): 传入请求者uid，目标群聊uid和时间
+ type          ：Data::GET_GROUP_INFO
+ senderUid     ：请求者的Uid
+ groupId       ：目标群聊的Uid
+ time          ：时间
### 返回 (DGroupInfo): 传入群聊id，群聊名称，人数
+ type          ：Data::GROUP_INFO
+ groupId       ：目标群聊的Uid
+ groupName     ：目标群聊的名字
+ userCnt       ：群聊人数

## 获取群聊列表
### 请求方 (GetGroupList): 传入请求者uid和时间
+ type          ：Data::GET_GROUP_LIST
+ senderUid     ：请求者的Uid
+ time          ：时间

### 返回 (DGroupList): 传入用户uid，时间，群聊列表
+ type          ：Data::GROUP_LIST
+ userId        ：目标用户的Uid
+ groupList     ：目标用户的群聊的GroupInfo数组

## 获取群聊成员
### 请求方 (GetGroupUser): 传入请求者uid，目标群聊uid和时间
+ type          ：Data::GET_GROUP_USER
+ senderUid     ：请求者的Uid
+ receiverUid   ：目标群聊的Uid
+ time          ：时间

### 返回 (DGroupUser): 传入群聊id，时间，成员列表
+ type          ：Data::GROUP_USER
+ groupId       ：目标群聊的Id
+ userList      ：目标群聊的成员UserInfo数组

## 获取群聊记录
### 请求方 (GetGroupMessage): 传入请求者uid，目标群聊uid和时间
+ type          ：Data::GET_GROUP_MESSAGE
+ senderUid     ：请求者的Uid
+ groupId   ：目标群聊的Uid
+ time          ：时间

### 返回 (DGroupMessageList): 传入请求者id，群聊id和消息列表
+ type          ：Data::GROUP_MESSAGE_LIST
+ senderUid     ：请求者的Uid
+ groupId       ：目标群聊的Id
+ messageList   ：目标群聊的GroupMessage数组