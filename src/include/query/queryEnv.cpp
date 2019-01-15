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

    template<class T>
    auto getColumnLoadFunction(sol::state&lua)
    {
        return lua[std::string(T::functionSuffix)+"Load"];
    }

    template<class T>
    void setupColumnLoadFunction(sol::state&lua,PanCake::Query&q,std::string path)
    {
        getColumnLoadFunction<T>(lua) = [&q,&lua,path]() -> void {
            sol::optional<int> exists = lua[T::functionName+std::string(T::functionSuffix)];
            if(exists == sol::nullopt)
            {
                lua.script_file(path);
                lua[std::string(T::functionName)+std::string(T::functionSuffix)](0);
            }
        };
    }
}

[[nodiscard]] bool PanCake::setupEnv(PanCake::Query&q,sol::state&lua)
{
    lua[std::string(PanCake::ChunkableSentimentScore::contName)] = &q.sentimentScoreCol;
    lua[std::string(PanCake::ChunkableText::contName)] = &q.textCol;

    setupColumnLoadFunction<PanCake::ChunkableSentimentScore>(lua,q,q.sentimentScoreColPath);
    setupColumnLoadFunction<PanCake::ChunkableText>(lua,q,q.textColPath);

    return true;
}

[[nodiscard]] std::string PanCake::runQuery(PanCake::Query&q,sol::state&lua)
{
    callQueryEnvSetup(lua);
    std::vector<sol::function> nextChunks;

    maybeGetNextChunkFunction<PanCake::ChunkableSentimentScore>(q.sentimentScoreCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableText>(q.textCol,nextChunks,lua);

    auto nextChunksEnd = nextChunks.end();
    
    int count = 0;

    for(int i = q.range.start; i != q.range.end; ++i)
    {
        int itCount = callQueryFunction(lua);
        count += itCount;

        if(i + 1 != q.range.end)
        {
            for(auto it = nextChunks.begin(); it != nextChunksEnd; ++it)
            {
                (*it)(i+1);
            }
        }
    }

    return std::to_string(count);
}
