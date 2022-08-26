#include "scanner.h"

std::mutex SocketClient::sendLock;
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
SocketClient::SocketClient() {}
void SocketClient::operator=(const SocketClient &b) {
    cid = b.cid, userUid = b.userUid;
    client = b.client;
    clientSize = b.clientSize;
}

//从客户端中读取一个数据包
Encoding::Data SocketClient::readData() {
    static char buf[Encoding::Data::SplitLength];
    static std::string buffer = "";
    while (buffer.length() < 4) {
        memset(buf, 0, sizeof(buf));
        int len = recv(cid, buf, sizeof(buf), 0);
        if (len == 0) {
            throw Worklog("disconnected", 0);
        }
        buffer += std::string(buf, len);
    }
    int dataLen = Encoding::decodeInt(buffer.substr(0, 4));
    std::cerr << "received data length : " << dataLen << std::endl;
    while ((int)buffer.length() < dataLen) {
        memset(buf, 0, sizeof(buf));
        int len = recv(cid, buf, sizeof(buf), 0);
        if (len == 0) {
            throw Worklog("disconnected", 0);
        }
        buffer += std::string(buf, len);
    }
    Encoding::Data rec(buffer.substr(0, dataLen));
    buffer = buffer.substr(dataLen);
    std::cerr << "rest of buffer : " << buffer.length() << std::endl;
    return rec;
}

//向客户端发送一个数据包，单线程
void SocketClient::sendData(const Encoding::Data& data) {
    std::lock_guard<std::mutex> lock(sendLock);
    auto dataPack = data.splitDataPack();
    int len = 0;
    for (auto s : dataPack) {
        int tag = send(cid, s.c_str(), s.length(), 0);
        std::cerr << tag << std::endl;
        len += s.length();
    }
    std::cerr << "send data length : " << len << std::endl;
}

//按照数据包组织的格式读写数据
int SocketClient::workData() {
    try {
        while (true) {
            Encoding::Data message = readData();
            workOnData(message);
            //sendData(message);
        }
    } catch (Worklog e) {
        e.post();
        if (userUid != -1 && userClient().count(userUid)) {
            userClient().erase(userUid);
        }
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

std::map<int, SocketClient*>& SocketClient::userClient() {
    static std::map<int, SocketClient*> userC;
    return userC;
}