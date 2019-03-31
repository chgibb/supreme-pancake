#include <algorithm>
#include <stdexcept>

#include "regexProvider.hpp"

PanCake::RegexProvider::~RegexProvider()
{
    std::for_each(this->regexs.begin(),this->regexs.end(),[](::regex_t&reg) -> void {
        ::regfree(&reg);
    });
}

void PanCake::RegexProvider::addRegex(std::string pat)
{
    this->regexs.push_back(::regex_t());
    int res = ::regcomp(&this->regexs.back(),pat.c_str(),REG_ICASE);

    if(res)
    {
        char buff[256];
        ::regerror(res,&this->regexs.back(),buff,256);
        ::regfree(&this->regexs.back());
        throw new std::runtime_error("Regex compilation error trying to compile token "+pat+buff);
    }
}

bool PanCake::RegexProvider::match(int regIndex,std::string str)
{
    if(::regexec(&this->regexs[regIndex],str.c_str(),0,NULL,0) == 0)
        return true;
    return false;
}

