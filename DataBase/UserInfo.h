# pragma once
# include <string>
class UserInfo
{
private:
    int id;
    std::string name;
    std::string pwd;
public:
    explicit UserInfo(int id=0,std::string name="",std::string pwd="");
    //对于GroupInfo的QByteArray编码方式
    //  quint32 id|nameSize| Qstring name|pwdSize | QString pwd
    int getId();
    std::string getName();
    std::string getPwd();
};


