#include "makeColumnIROutPutPath.hpp"

[[nodiscard]] std::ofstream PanCake::makeColumnIROutPutStream(std::string prefix,PanCake::TweetDate&date,std::string suffix)
{
    return std::ofstream(
        PanCake::makeColumnIROutputPath(prefix,date,suffix).c_str(),
        std::ios::out
    );
}

[[nodiscard]] std::string PanCake::makeColumnIROutputPath(std::string prefix,PanCake::TweetDate&date,std::string suffix)
{
    return (prefix != "" ? prefix + "/" : "")+std::string(date.year)+"-"+std::string(date.month)+"-"+std::string(date.day)+"-"+suffix+".lua";
}

[[nodiscard]] std::ofstream PanCake::makeColumnIRChunkCountStream(std::string prefix,PanCake::TweetDate&date)
{
    return std::ofstream(
        PanCake::makeColumnIRChunkCountPath(prefix,date).c_str(),
        std::ios::out  
    );
}

[[nodiscard]] std::string PanCake::makeColumnIRChunkCountPath(std::string prefix,PanCake::TweetDate&date)
{
    return (prefix != "" ? prefix + "/" : "")+std::string(date.year)+"-"+std::string(date.month)+"-"+std::string(date.day)+".chunkCount";
}

[[nodiscard]] std::ofstream PanCake::makeColumnIRTotalCountStream(std::string prefix,PanCake::TweetDate&date)
{
    return std::ofstream(
        PanCake::makeColumnIRTotalCountPath(prefix,date).c_str(),
        std::ios::out  
    );
}

[[nodiscard]] std::string PanCake::makeColumnIRTotalCountPath(std::string prefix,PanCake::TweetDate&date)
{
    return (prefix != "" ? prefix + "/" : "")+std::string(date.year)+"-"+std::string(date.month)+"-"+std::string(date.day)+".totalCount";
}
