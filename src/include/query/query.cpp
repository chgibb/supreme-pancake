#include <iostream>
#include <fstream>

#include <sol.hpp>

#include "query.hpp"
#include "queryEnv.hpp"
#include "../columnIR/makeColumnIROutPutPath.hpp"
#include "../columnIR/chunkableSentimentScore.hpp"
#include "../columnIR/chunkableText.hpp"

namespace
{
    sol::state defualtLuaInit()
    {
        sol::state lua;
        lua.open_libraries(sol::lib::base);
        return lua;
    }
}

[[nodiscard]] std::string PanCake::runQueryFromFile(const char*dataDir,PanCake::TweetDate&date,PanCake::QueryExecutionPolicy pol,std::string fileName)
{
    std::string res = "";

    int totalChunks = 0;
    {
        std::ifstream totalChunksStream(PanCake::makeColumnIRChunkCountPath(dataDir,date),std::ios::in);
        std::string str = "";
        std::getline(totalChunksStream,str);
        totalChunks = std::atoi(str.c_str());
    }

    if(pol == PanCake::QueryExecutionPolicy::serial)
    {
        PanCake::Query q(
            PanCake::ChunkableSentimentScore::makeOutPutPath(dataDir,date),
            PanCake::ChunkableText::makeOutPutPath(dataDir,date),
            totalChunks
        );

        return q.runQueryFromFile(fileName);
    }

    return res;
}

[[nodiscard]] std::string PanCake::runQueryFromString(const char*dataDir,PanCake::TweetDate&date,PanCake::QueryExecutionPolicy pol,std::string fileName)
{
    std::string res = "";

    return res;
}

[[nodiscard]] std::string PanCake::Query::runQueryFromFile(std::string filePath)
{
    sol::state lua = defualtLuaInit();

    lua.script_file(filePath.c_str());

    if(!PanCake::setupEnv(*this,lua))
        return "";
    return PanCake::runQuery(*this,lua);
}

[[nodiscard]] std::string PanCake::Query::runQueryFromString(std::string filePath)
{
    sol::state lua = defualtLuaInit();

    lua.script(filePath.c_str());

    if(!PanCake::setupEnv(*this,lua))
        return "";
    return PanCake::runQuery(*this,lua);
}
