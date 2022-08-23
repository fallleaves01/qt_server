# 数据类型
## [功能型](#功能型说明)
+ [登录](#登录)
+ [注册](#注册)
+ [添加好友](#添加好友)
+ 创建群聊
+ 加入群聊

## 消息型
+ 私聊消息
+ 私聊表情
+ 群聊消息
+ 群聊表情

## 请求
+ 获取用户信息
+ 获取好友列表
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
    + DataLogin::SUCCESS ：成功登录
    + DataLogin::USERNOTFOUND ：找不到对应用户
    + DataLogin::WRONGPASSWORD ：密码错误

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
### 发起方 (CreateGroupMessage) : 传入发起方的uid，添加时间和被拉进群聊的人员列表
+ type          ：Data::CREATE_GROUP_MESSAGE
+ createrUid    ：发起方的Uid
+ receiverUid   ：0，表示服务器
+ time          ：添加时间
+ userList      ：所有被拉入群聊的人员的Uid

### 返回 (CreateGroupCheck)
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

### 返回 (AddGroupCheck) : 传入加群信息和状态
+ type          ：Data::ADD_GROUP_CHECK
+ createrUid    ：加群方的Uid
+ receiverUid   ：群聊的id
+ time          ：添加时间
+ state         ：加群的状态，具体分为
    + AddGroupCheck::SUCCESS : 成功加入
    + AddGroupCheck::REJECT : 被拒绝


# 消息型说明
## 私聊消息 (FriendMessage) : 传入发送者id、接收者id、时间和信息内容
+ type          ：Data::FRIEND_MESSAGE
+ senderUid     ：发送者的Uid
+ receiverUid   ：接收者的Uid
+ time          ：添加时间
+ content       ：信息内容
## 群聊消息 (GroupMessage) ：传入发送者id，群聊id，时间和信息内容
+ type          ：Data::GROUP_MESSAGE
+ senderUid     ：发送者的Uid
+ groupId       ：群聊的id
+ time          ：添加时间
+ content       ：消息具体内容