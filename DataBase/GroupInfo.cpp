#include "GroupInfo.h"

GroupInfo::GroupInfo(
    int id,
    std::string name
) : id(id), name(name)
{
}

int GroupInfo::getId() const
{
    return id;
}


std::string GroupInfo::getName() const
{
    return name;
}