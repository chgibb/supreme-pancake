#include <iostream>
#include <fstream>

#define SOL_PRINT_ERRORS 1
#include <sol.hpp>

#include "query.hpp"
#include "queryEnv.hpp"
#include "makeColumnIROutPutPath.hpp"
#include "chunkableSentimentScore.hpp"
#include "chunkableText.hpp"
#include "chunkableUser.hpp"
#include "chunkableFavouriteCount.hpp"
#include "chunkableIsPinned.hpp"
#include "chunkableIsReplyTo.hpp"
#include "chunkableIsRetweet.hpp"
#include "chunkableReplyCount.hpp"
#include "chunkableReTweetCount.hpp"

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
            PanCake::ChunkableUser::makeOutPutPath(dataDir,date),
            PanCake::ChunkableFavouriteCount::makeOutPutPath(dataDir,date),
            PanCake::ChunkableIsPinned::makeOutPutPath(dataDir,date),
            PanCake::ChunkableIsReplyTo::makeOutPutPath(dataDir,date),
            PanCake::ChunkableIsRetweet::makeOutPutPath(dataDir,date),
            PanCake::ChunkableReplyCount::makeOutPutPath(dataDir,date),
            PanCake::ChunkableReTweetCount::makeOutPutPath(dataDir,date),
            PanCake::ChunkRange(0,totalChunks)
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
