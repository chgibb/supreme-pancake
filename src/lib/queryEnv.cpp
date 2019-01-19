#include <iostream>

#include "queryEnv.hpp"
#include "chunkableColumn.hpp"
#include "chunkableSentimentScore.hpp"
#include "chunkableText.hpp"
#include "chunkableUser.hpp"

namespace
{
    template<class T,class U>
    constexpr void maybeGetNextChunkFunction(U&u,std::vector<sol::function>&funcs,sol::state&lua)
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
    constexpr auto getColumnLoadFunction(sol::state&lua)
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

    template<class T,class U>
    constexpr void bindColumnToGlobal(sol::state&lua,U&u)
    {
        lua[std::string(T::contName)] = &u;
    }
}

[[nodiscard]] bool PanCake::setupEnv(PanCake::Query&q,sol::state&lua)
{
    bindColumnToGlobal<PanCake::ChunkableSentimentScore>(lua,q.sentimentScoreCol);
    bindColumnToGlobal<PanCake::ChunkableText>(lua,q.textCol);
    bindColumnToGlobal<PanCake::ChunkableUser>(lua,q.userCol);

    setupColumnLoadFunction<PanCake::ChunkableSentimentScore>(lua,q,q.sentimentScoreColPath);
    setupColumnLoadFunction<PanCake::ChunkableText>(lua,q,q.textColPath);
    setupColumnLoadFunction<PanCake::ChunkableUser>(lua,q,q.userColPath);

    return true;
}

[[nodiscard]] std::string PanCake::runQuery(PanCake::Query&q,sol::state&lua)
{
    callQueryEnvSetup(lua);
    std::vector<sol::function> nextChunks;

    maybeGetNextChunkFunction<PanCake::ChunkableSentimentScore>(q.sentimentScoreCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableText>(q.textCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableUser>(q.userCol,nextChunks,lua);

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
