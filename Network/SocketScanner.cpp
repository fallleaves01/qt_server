#include "scanner.h"
//生成一个服务端对象，扫描固定的接口
SocketScanner::SocketScanner(int _port) : port(_port) {
    memset(&myaddr, 0, sizeof(myaddr));
    socketid = 0;

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

//发起连接
void SocketScanner::connect() {
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
void SocketScanner::work() {
    std::vector<std::future<int>> fpool;
    static SocketClient vec[100];
    int cnt = 0;
    while (true) {
        vec[++cnt] = SocketClient(socketid);
        fpool.emplace_back(std::async(
            std::launch::async, [&]() { return vec[cnt].workData(); }));
    }
}