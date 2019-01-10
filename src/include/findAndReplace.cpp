#include "findAndReplace.hpp"

//adapted from https://stackoverflow.com/questions/1494399/how-do-i-search-find-and-replace-in-a-standard-string

std::string PanCake::findAndReplace(const std::string&src,const std::string&find,const std::string&replace)
{
    auto fLen = find.size();
    auto rLen = replace.size();
    auto res = src;
    for(std::size_t pos = 0; (pos = res.find(find,pos)) != std::string::npos; pos += rLen)
    {
        res.replace(pos,fLen,replace);
    }
    return res;
}
