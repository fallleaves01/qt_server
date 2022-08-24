#include "UserInfo.h"

UserInfo::UserInfo(
    int id,
    std::string name,
    std::string pwd
): id(id), name(name), pwd(pwd)
{
}

// quint32 id |nameSize| Qstring name|pwdSize| pwd
int UserInfo::getId() const
{
    return id;
}

std::string UserInfo::getPwd() const
{
    return pwd;
}

std::string UserInfo::getName() const
{
    return name;

}