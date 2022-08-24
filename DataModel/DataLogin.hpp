#include "encoding.h"
using namespace Encoding;

class LoginMessage : public Data {
    std::string userName, password;

   public:
    //传入时间、用户名与密码，生成一个登陆信息的对象
    explicit LoginMessage(const std::string &_time,
                          const std::string &_userName,
                          const std::string &_password)
        : Data(Data::LOGIN_MESSAGE,
               0,
               0,
               _time,
               encodeStr(_userName) + encodeStr(_password)),
          userName(_userName),
          password(_password) {}

    //对应的解码函数
    explicit LoginMessage(const std::string &s) : Data(s) {
        DataStream ds(getContent());
        ds >> userName >> password;
    }
    explicit LoginMessage(const Data &d) : Data(d) {
        DataStream ds(getContent());
        ds >> userName >> password;
    }

    // get函数
    std::string getUserName() const { return userName; }
    std::string getPassword() const { return password; }
};

class LoginCheck : public Data {
    std::string userName;
    int state;

   public:
    //传入时间、用户名、用户ID与登录状态，生成一个关于登陆是否成功的检查信息
    explicit LoginCheck(const std::string &_time,
                        const std::string &_userName,
                        int _userId,
                        int _state)
        : Data(Data::LOGIN_CHECK,
               0,
               _userId,
               _time,
               encodeStr(_userName) + encodeInt(_state)),
          userName(_userName),
          state(_state) {}

    //对应的解码函数
    explicit LoginCheck(const std::string &s) : Data(s) {
        DataStream ds(getContent());
        ds >> userName >> state;
    }
    explicit LoginCheck(const Data &d) : Data(d) {
        DataStream ds(getContent());
        ds >> userName >> state;
    }

    //下面是用于表示状态的标识符
    static const int SUCCESS = 0;
    static const int USERNOTFOUND = 1;
    static const int WRONGPASSWORD = 2;

    // get函数
    std::string getUserName() const { return userName; }
    int getState() const { return state; }
};

class RegisterMessage : public Data {
    std::string userName, password;

   public:
    //传入三个参数，时间、用户名和密码
    explicit RegisterMessage(const std::string &_time,
                             const std::string &_userName,
                             const std::string &_password)
        : Data(Data::REGISTER_MESSAGE,
               0,
               0,
               _time,
               encodeStr(_userName) + encodeStr(_password)),
          userName(_userName),
          password(_password) {}

    //对应的解码函数
    explicit RegisterMessage(const std::string &s) : Data(s) {
        DataStream ds(getContent());
        ds >> userName >> password;
    }
    explicit RegisterMessage(const Data &d) : Data(d) {
        DataStream ds(getContent());
        ds >> userName >> password;
    }

    // get系列函数
    std::string getUserName() const { return userName; }
    std::string getPassword() const { return password; }
};