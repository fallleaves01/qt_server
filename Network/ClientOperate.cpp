#include "scanner.h"

void SocketClient::workOnData(const Data &d) {
    switch (d.getType()) {
        case (Data::LOGIN_MESSAGE):
            tryLogin(d);
            break;
        case (Data::REGISTER_MESSAGE):
            tryRegister(d);
            break;
    }
}

void SocketClient::tryLogin(const Data &d) {
    LoginMessage login(d);
    std::cerr << "user " << login.getUserName() << " tried to login" << std::endl;
    auto db = Database::getDatabase();
    auto users = db->getAllUserNoPwd();
    auto checkNameExists = [&]() {
        for (auto user : *users) {
            if (user.getName() == login.getUserName()) {
                std::cerr << "found user " << user.getName() << std::endl;
                auto userInfo = db->getUserInfo(user.getId());
                if (userInfo.getPwd() == login.getPassword()) {
                    LoginCheck ret(login.getTime(), user.getName(),
                                   user.getId(), LoginCheck::SUCCESS);
                    sendData(ret);
                } else {
                    LoginCheck ret(login.getTime(), user.getName(),
                                   user.getId(), LoginCheck::WRONGPASSWORD);
                    sendData(ret);
                }
                return true;
            }
        }
        return false;
    };
    if (!checkNameExists()) {
        std::cerr << "user not found" << std::endl;
        LoginCheck ret(login.getTime(), login.getUserName(), 0, LoginCheck::USERNOTFOUND);
        sendData(ret);
    }
    delete users;
}

void SocketClient::tryRegister(const Data &d) {
    RegisterMessage reg(d);
    std::cerr << "user " << reg.getUserName() << " tried to register" << std::endl;
    auto db = Database::getDatabase();
    auto users = db->getAllUserId();
    int uid = users->size() + 1;
    UserInfo user(uid, reg.getUserName(), reg.getPassword());
    delete users;
    db->insertUserTable(user);
    LoginCheck ret(reg.getTime(), user.getName(), user.getId(), LoginCheck::SUCCESS);
    sendData(ret);
}