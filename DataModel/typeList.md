# 数据类型
## [功能型](#功能型说明)
+ [登录](#登录)
+ [注册](#注册)
+ 添加好友
+ 创建群聊
+ 添加群聊

## 消息型
+ 私聊消息
+ 私聊表情
+ 群聊消息
+ 群聊表情

## 请求
+ 获取好友列表
+ 获取群聊列表
+ 获取群聊成员
+ 获取聊天记录


# 功能型说明
## 登录
### 发起方 (LoginMessage: 传入时间、用户名和密码)
+ type          ：Data::LOGIN_MESSAGE
+ senderUid     ：0，代表未登录用户
+ receiverUid   ：0，代表服务端本身
+ time          ：登录时间
+ userName      ：用户名
+ password      ：使用哈希算法加密后的密码

### 返回 (LoginCheck: 传入时间、用户名、用户Id和登陆状态)
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
### 发起方 (RegisterMessage : 传入三个字符串：时间、用户名和密码)
+ type          ：Data::REGISTER_MESSAGE
+ senderUid     ：0，未注册用户没有Uid
+ receiverUid   ：0，代表服务端本身
+ time          ：注册时间
+ userName      ：用户名
+ password      ：使用哈希算法加密后的密码

### 返回 ([LoginCheck](#返回-logincheck))
+ type          ：Data::LOGIN_CHECK
+ senderUid     ：0，代表服务端本身
+ receiverUid   ：为该用户分配的uid
+ time          ：登录时间
+ userName      ：用户名
+ state         ：登录状态，具体分为
    + DataLogin::SUCCESS ：成功登录 (成功注册用户默认为成功登陆)
    + DataLogin::USERNOTFOUND ：找不到对应用户
    + DataLogin::WRONGPASSWORD ：密码错误


## 添加好友
### 发起方
+ type          ：Data::ADDFRIEND
+ senderUid     ：添加方的Uid
+ receiverUid   ：被添加方的Uid
+ time          ：添加时间
+ content       ：无
### 接收方
+ type          ：Data::ADDFRIEND
+ senderUid     ：添加方的Uid
+ receiverUid   ：被添加方的Uid
+ time          ：注册时间
+ content       ：