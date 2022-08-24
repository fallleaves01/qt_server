#pragma once

# include <string>
class GroupInfo
{
private:
    int id;
    std::string name;
public:
    explicit GroupInfo(int id = 0, std::string name = "");
    //����GroupInfo��QByteArray���뷽ʽ
    int getId() const;
    std::string getName() const;

};

