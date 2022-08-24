#ifndef SCANNER_H
#define SCANNER_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <future>
#include <mutex>
#include <vector>
#include "../Utilities/worklog.hpp"
#include "../DataModel/DataModel.h"
#include "../DataBase/Database.h"

class SocketClient {
    int cid;
    sockaddr_in client;
    socklen_t clientSize;
    std::mutex sendLock;

   public:
    //对应一个连接到的客户端生成一个客户端对象
    explicit SocketClient(int socketid);
    //从客户端中读取一个数据包
    Encoding::Data readData();

    //向客户端发送一个数据包，单线程
    void sendData(const Encoding::Data &data);

    //按照数据包组织的格式读写数据
    int workData();

    //测试用，无格式读写数据
    int workPlainText();

    //以下是操作列表
    void workOnData(const Data&);
    void tryLogin(const Data&);
    void tryRegister(const Data&);
};

class SocketScanner {
    int socketid, port;
    sockaddr_in myaddr;

   public:
    //生成一个服务端对象，扫描固定的接口
    explicit SocketScanner(int _port);

    //发起连接
    void connect();
    void work();
};
#endif