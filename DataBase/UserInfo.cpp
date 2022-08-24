#include "UserInfo.h"

UserInfo::UserInfo(
    int id,
    std::string name,
    std::string pwd
): id(id), name(name), pwd(pwd)
{
}

// quint32 id |nameSize| Qstring name|pwdSize| pwd
int UserInfo::getId()
{
    return id;
}

std::string UserInfo::getPwd()
{
    return pwd;
}

std::string UserInfo::getName()
{
    return name;

}