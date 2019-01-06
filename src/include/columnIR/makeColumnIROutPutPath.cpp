#include "makeColumnIROutPutPath.hpp"

std::ofstream PanCake::makeColumnIROutPutPath(std::string prefix,PanCake::TweetDate&date,std::string suffix)
{
    return std::ofstream(
        (prefix != "" ? prefix + "/" : "")+std::string(date.year)+"-"+std::string(date.month)+"-"+std::string(date.day)+"-"+suffix+".lua",
        std::ios::out
    );
}
