#include <iostream>
#include <type_traits>

#include <ThreadPool.h>

#include "queryEnv.hpp"
#include "chunkableColumn.hpp"
#include "chunkableSentimentScore.hpp"
#include "chunkableText.hpp"
#include "chunkableUser.hpp"
#include "chunkableFavouriteCount.hpp"
#include "chunkableIsPinned.hpp"
#include "chunkableIsReplyTo.hpp"
#include "chunkableIsRetweet.hpp"
#include "chunkableReplyCount.hpp"
#include "chunkableReTweetCount.hpp"
#include "isStdContainer.hpp"
#include "isStdString.hpp"

namespace
{
    template<class T>
    constexpr typename std::enable_if<PanCake::isChunkable<T>::value,std::string>::type 
    getChunkFunctionName()
    {
        return std::string(T::functionName)+
               std::string(T::functionSuffix);
    }

    template<class T,class U>
    constexpr typename std::enable_if<PanCake::isStdContainer<U>::value && !PanCake::isStdString<U>::value,void>::type 
    maybeGetNextChunkFunction(U&u,std::vector<sol::function>&funcs,sol::state&lua)
    {
        if(u.size() != 0)
        {
            funcs.push_back(lua[
                getChunkFunctionName<T>()
            ]);
        }
    }

    void callQueryEnvSetup(sol::state&lua)
    {
        lua["env"]();
    }

    int callQueryFunction(sol::state&lua,int s,int e)
    {
        return lua["q"](s,e);
    }

    template<class T>
    constexpr typename std::enable_if<PanCake::isChunkable<T>::value,std::string>::type 
    getColumnLoadFunctionName()
    {
        return std::string(T::functionSuffix)+"Load";
    }

    template<class T>
    constexpr auto getColumnLoadFunction(sol::state&lua)
    {
        return lua[getColumnLoadFunctionName<T>()];
    }

    template<class T>
    constexpr typename std::enable_if<PanCake::isChunkable<T>::value,std::string>::type 
    getColumnGlobalName()
    {
        return std::string(T::contName);
    }

    template<class T>
    constexpr auto getColumnGlobal(sol::state&lua)
    {
         return lua[getColumnGlobalName<T>()];
    }

    template<class T>
    constexpr typename std::enable_if<PanCake::isChunkable<T>::value,void>::type 
    setupColumnLoadFunction(sol::state&lua,PanCake::Query&q,std::string path)
    {
        getColumnLoadFunction<T>(lua) = [&q,&lua,path]() -> void {
            sol::optional<int> exists = lua[getChunkFunctionName<T>()];
            if(exists == sol::nullopt)
            {
                lua.script_file(path);
                lua[getChunkFunctionName<T>()](0);
            }
        };
    }

    template<class T,class U>
    constexpr typename std::enable_if<PanCake::isChunkable<T>::value,void>::type 
    bindColumnToGlobal(sol::state&lua,U&u)
    {
        getColumnGlobal<T>(lua) = &u;
    }

    int getChunkLength(sol::state&lua)
    {
        return lua[std::string(PanCake::ChunkableColumn::chunkLength)];
    }
}

[[nodiscard]] bool PanCake::setupEnv(PanCake::Query&q,sol::state&lua)
{
    bindColumnToGlobal<PanCake::ChunkableSentimentScore>(lua,q.sentimentScoreCol);
    bindColumnToGlobal<PanCake::ChunkableText>(lua,q.textCol);
    bindColumnToGlobal<PanCake::ChunkableUser>(lua,q.userCol);
    bindColumnToGlobal<PanCake::ChunkableFavouriteCount>(lua,q.favouriteCountCol);
    bindColumnToGlobal<PanCake::ChunkableIsPinned>(lua,q.isPinnedCol);
    bindColumnToGlobal<PanCake::ChunkableIsReplyTo>(lua,q.isReplyToCol);
    bindColumnToGlobal<PanCake::ChunkableIsRetweet>(lua,q.isRetweetCol);

    setupColumnLoadFunction<PanCake::ChunkableSentimentScore>(lua,q,q.sentimentScoreColPath);
    setupColumnLoadFunction<PanCake::ChunkableText>(lua,q,q.textColPath);
    setupColumnLoadFunction<PanCake::ChunkableUser>(lua,q,q.userColPath);
    setupColumnLoadFunction<PanCake::ChunkableFavouriteCount>(lua,q,q.favouriteCountColPath);
    setupColumnLoadFunction<PanCake::ChunkableIsPinned>(lua,q,q.isPinnedColPath);
    setupColumnLoadFunction<PanCake::ChunkableIsReplyTo>(lua,q,q.isReplyToColPath);
    setupColumnLoadFunction<PanCake::ChunkableIsRetweet>(lua,q,q.isRetweetColPath);

    return true;
}

template<class T>
void printSymbol(sol::state&lua,T symbol)
{   
    lua.script("print([["+symbol+"]],"+symbol+")");
}


void PanCake::printEnv(PanCake::Query&q,sol::state&lua)
{
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableSentimentScore>());
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableText>());
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableUser>());
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableFavouriteCount>());
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableIsPinned>());
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableIsReplyTo>());
    printSymbol(lua,getColumnGlobalName<PanCake::ChunkableIsRetweet>());

    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableSentimentScore>());
    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableText>());
    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableUser>());
    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableFavouriteCount>());
    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableIsPinned>());
    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableIsReplyTo>());
    printSymbol(lua,getColumnLoadFunctionName<PanCake::ChunkableIsRetweet>());

    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableSentimentScore>());
    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableText>());
    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableUser>());
    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableFavouriteCount>());
    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableIsPinned>());
    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableIsReplyTo>());
    printSymbol(lua,getChunkFunctionName<PanCake::ChunkableIsRetweet>());

    printSymbol(lua,std::string(PanCake::ChunkableColumn::chunkLength));
}

[[nodiscard]] std::string PanCake::runQuery(PanCake::Query&q,sol::state&lua)
{
    callQueryEnvSetup(lua);
    std::vector<sol::function> nextChunks;

    maybeGetNextChunkFunction<PanCake::ChunkableSentimentScore>(q.sentimentScoreCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableText>(q.textCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableUser>(q.userCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableFavouriteCount>(q.favouriteCountCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableIsPinned>(q.isPinnedCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableIsReplyTo>(q.isReplyToCol,nextChunks,lua);
    maybeGetNextChunkFunction<PanCake::ChunkableIsRetweet>(q.isRetweetCol,nextChunks,lua);

    auto nextChunksEnd = nextChunks.end();
    
    int count = 0;

    ::ThreadPool pool(1);
    std::vector<std::future<int>> poolRes;

    for(int i = q.range.start; i != q.range.end; ++i)
    {   
        int chunkLength = getChunkLength(lua);

        poolRes.emplace_back(pool.enqueue([&lua,&chunkLength](){
            return callQueryFunction(lua,1,chunkLength);
        }));

        std::for_each(poolRes.begin(),poolRes.end(),[&count](std::future<int>&task) {
            if(!task.valid())
                return;
            task.wait();
            count += task.get();
        });

        q.clearColumns();

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

