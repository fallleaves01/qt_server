#ifndef SCANNER_HPP
#define SCANNER_HPP

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
    explicit SocketClient(int socketid) : clientSize(sizeof(client)) {
        std::cerr << "waiting for the client" << std::endl;
        cid = accept(socketid, (sockaddr*)(&client), &clientSize);
        if (cid == -1) {
            throw Worklog("accept error");
        }
        std::cerr << "get client" << std::endl;
        std::cerr << "client address : " << inet_ntoa(client.sin_addr)
                  << std::endl;
    }
    //从客户端中读取一个数据包
    Encoding::Data readData() {
        static char buf[Encoding::Data::SplitLength];
        memset(buf, 0, sizeof(buf));
        int len = recv(cid, buf, sizeof(buf), 0);
        if (len == 0) {
            throw Worklog("disconnected", 0);
        }
        std::string dataStr(buf, len);
        int dataLen = Encoding::decodeInt(dataStr.substr(0, 4));
        std::cerr << "received dataPack of length " << dataLen << std::endl;
        while ((int)dataStr.length() < dataLen) {
            memset(buf, 0, sizeof(buf));
            int len = recv(cid, buf, sizeof(buf), 0);
            if (len == 0) {
                throw Worklog("disconnected", 0);
            }
            dataStr += std::string(buf, len);
        }
        Encoding::Data rec(dataStr);
        std::cerr << "received content : " << rec.getContent() << std::endl;
        if (rec.getType() == Encoding::Data::LOGIN_MESSAGE) {
            LoginMessage login(rec);
            std::cerr << "user " << login.getUserName() << " tried to login with password " << login.getPassword() << std::endl;
        }
        return rec;
    }

    //像客户端发送一个数据包，单线程
    void sendData(const Encoding::Data &data) {
        std::lock_guard<std::mutex> lock(sendLock);
        auto dataPack = data.splitDataPack();
        for (auto s : dataPack) {
            int tag = send(cid, s.c_str(), s.length(), 0);
            std::cerr << tag << std::endl;
        }
    }

    //按照数据包组织的格式读写数据
    int workData() {
        try {
            while (true) {
                Encoding::Data message = readData();
                sendData(message);
            }
        } catch (Worklog e) {
            e.post();
            if (e.has_error()) {
                e.exit();
            }
            return e.geteid();
        }
    }

    //测试用，无格式读写数据
    int workPlainText() {
        try {
            while (true) {
                static char buf[1024];
                memset(buf, 0, sizeof(buf));
                int len = recv(cid, buf, sizeof(buf), 0);
                if (len == 0) {
                    throw Worklog("disconnected", 0);
                }
                std::cerr << "received : " << buf << std::endl;
                int tag = send(cid, buf, len, 0);
                std::cerr << tag << std::endl;
            }
        } catch (Worklog e) {
            e.post();
            if (e.has_error()) {
                e.exit();
            }
            return e.geteid();
        }
    }
};

class SocketScanner {
    int socketid, port;
    sockaddr_in myaddr;

   public:
    //生成一个服务端对象，扫描固定的接口
    explicit SocketScanner(int _port) : port(_port) {
        memset(&myaddr, 0, sizeof(myaddr));
        socketid = 0;

        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(port);
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    //发起连接
    void connect() {
        socketid = socket(AF_INET, SOCK_STREAM, 0);
        if (socketid == -1) {
            throw Worklog("socket error");
        }
        if (bind(socketid, (sockaddr*)(&myaddr), sizeof(myaddr)) == -1) {
            throw Worklog("port bind error");
        }
        if (listen(socketid, 10) == -1) {
            throw Worklog("listen error");
        }
    }
    void work() {
        std::vector<std::future<int>> fpool;
        while (true) {
            SocketClient client(socketid);
            fpool.emplace_back(std::async(std::launch::async, [&client]() {
                return client.workData();
            }));
        }
    }
};
#endif