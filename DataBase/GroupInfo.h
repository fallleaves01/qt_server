#pragma once

# include <string>
class GroupInfo
{
private:
    int id;
    std::string name;
public:
    explicit GroupInfo(int id = 0, std::string name = "");
    //对于GroupInfo的QByteArray编码方式
    int getId() const;
    std::string getName() const;

};

