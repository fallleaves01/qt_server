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
    //����GroupInfo��QByteArray���뷽ʽ
    //  quint32 id|nameSize| Qstring name|pwdSize | QString pwd
    int getId() const;
    std::string getName() const;
    std::string getPwd() const;
};


