#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <future>
#include <vector>
#include "worklog.hpp"

class SocketClient {
    int cid;
    sockaddr_in client;
    socklen_t clientSize;

   public:
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
    int work() {
        try {
            while (1) {
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
    explicit SocketScanner(int _port) : port(_port) {
        memset(this, 0, sizeof(*this));

        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(port);
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

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
            fpool.emplace_back(std::async(std::launch::async, [](SocketClient c) {
                c.work();
            }, client));
        }
    }
};
#endif