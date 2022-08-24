#include "scanner.h"

//对应一个连接到的客户端生成一个客户端对象
SocketClient::SocketClient(int socketid) : clientSize(sizeof(client)) {
    std::cerr << "waiting for the client" << std::endl;
    cid = accept(socketid, (sockaddr*)(&client), &clientSize);
    if (cid == -1) {
        throw Worklog("accept error");
    }
    std::cerr << "get client" << std::endl;
    std::cerr << "client address : " << inet_ntoa(client.sin_addr) << std::endl;
}

//从客户端中读取一个数据包
Encoding::Data SocketClient::readData() {
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
    return rec;
}

//向客户端发送一个数据包，单线程
void SocketClient::sendData(const Encoding::Data& data) {
    std::lock_guard<std::mutex> lock(sendLock);
    auto dataPack = data.splitDataPack();
    for (auto s : dataPack) {
        int tag = send(cid, s.c_str(), s.length(), 0);
        std::cerr << tag << std::endl;
    }
}

//按照数据包组织的格式读写数据
int SocketClient::workData() {
    try {
        while (true) {
            Encoding::Data message = readData();
            workOnData(message);
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
int SocketClient::workPlainText() {
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