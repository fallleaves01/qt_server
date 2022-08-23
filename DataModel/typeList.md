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
### 发起方
+ type          ：Data::LOGIN
+ senderUid     ：发起登录申请的Uid
+ receiverUid   ：0，代表服务端本身
+ time          ：登录时间
+ content       ：使用哈希算法加密后的密码

### 返回
+ type          ：Data::LOGIN
+ senderUid     ：0，代表服务端本身
+ receiverUid   ：发起登录申请的Uid
+ time          ：登录时间
+ content       ：登录状态，具体分为
    + DataLogin::SUCCESS ：成功登录
    + DataLogin::NOUSER ：找不到对应用户
    + DataLogin::WRONGPASSWORD ：密码错误

## 注册
### 发起方
+ type          ：Data::REGISTER
+ senderUid     ：0，未注册用户没有Uid
+ receiverUid   ：0，代表服务端本身
+ time          ：注册时间
+ userName      ：用户名
+ password      ：使用哈希算法加密后的密码

### 返回
+ type          ：Data::REGISTER
+ senderUid     ：0，代表服务端本身
+ receiverUid   ：为注册成功的用户分配的Uid
+ time          ：登录时间
+ content       ：注册成功固定为DataLogin::SUCCESS，代表成功登录

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