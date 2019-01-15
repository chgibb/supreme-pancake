#include <iostream>

#include "queryEnv.hpp"
#include "../columnIR/chunkableColumn.hpp"
#include "../columnIR/chunkableSentimentScore.hpp"
#include "../columnIR/chunkableText.hpp"

namespace
{
    template<class T,class U>
    void maybeGetNextChunkFunction(U&u,std::vector<sol::function>&funcs,sol::state&lua)
    {
        if(u.size() != 0)
        {
            funcs.push_back(lua[
                std::string(PanCake::ChunkableColumn::functionName)+
                std::string(T::functionSuffix)
            ]);
        }
    }

    void callQueryEnvSetup(sol::state&lua)
    {
        lua["env"]();
    }

    int callQueryFunction(sol::state&lua)
    {
        return lua["q"]();
    }
}

[[nodiscard]] bool PanCake::setupEnv(PanCake::Query&q,sol::state&lua)
{
    lua[std::string(PanCake::ChunkableSentimentScore::contName)] = &q.sentimentScoreCol;
    lua[std::string(PanCake::ChunkableText::contName)] = &q.textCol;

    lua[std::string(PanCake::ChunkableSentimentScore::functionSuffix)+"Load"] = [&q,&lua]() -> void {
        sol::optional<int> exists = lua[PanCake::ChunkableColumn::functionName+std::string(PanCake::ChunkableSentimentScore::functionSuffix)];
        if(exists == sol::nullopt)
        {
            lua.script_file(q.sentimentScoreColPath);
            lua[std::string(PanCake::ChunkableColumn::functionName)+std::string(PanCake::ChunkableSentimentScore::functionSuffix)](0);
        }
    };

    return true;
}

[[nodiscard]] std::string PanCake::runQuery(PanCake::Query&q,sol::state&lua)
{
    callQueryEnvSetup(lua);
    std::vector<sol::function> nextChunks;

    maybeGetNextChunkFunction<PanCake::ChunkableSentimentScore>(q.sentimentScoreCol,nextChunks,lua);

    auto nextChunksEnd = nextChunks.end();
    
    int count = 0;

    for(int i = q.range.start; i != q.range.end; ++i)
    {
        int itCount = callQueryFunction(lua);
        count += itCount;

        if(i + 1 != q.totalChunks)
        {
            for(auto it = nextChunks.begin(); it != nextChunksEnd; ++it)
            {
                (*it)(i+1);
            }
        }
    }

    return std::to_string(count);
}
