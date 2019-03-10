#pragma once

#include <vector>
#include <type_traits>
#include <assert.h>

#define SOL_PRINT_ERRORS 1
#include <sol.hpp>

#include "fileExists.hpp"
#include "tweet.hpp"
#include "tweetDate.hpp"

namespace PanCake
{
    enum class QueryExecutionPolicy
    {
        serial = 0
    };

    class ChunkRange
    {
        public:
            ChunkRange() = delete;
            ChunkRange(int _start,int _end) : start(_start),end(_end) {}

            int start;
            int end;
    };

    [[nodiscard]] std::string runQueryFromFile(const char*,PanCake::TweetDate&,std::string,PanCake::QueryExecutionPolicy);
    [[nodiscard]] std::string runQueryFromString(const char*,PanCake::TweetDate&,std::string,PanCake::QueryExecutionPolicy);

    class Query
    {
        public:
            Query() = delete;
            Query(
                std::string _sentimentScoreColPath,
                std::string _textColPath,
                std::string _userColPath,
                std::string _favouriteCountColPath,
                std::string _isPinnedColPath,
                std::string _isReplyToColPath,
                std::string _isRetweetColPath,
                std::string _replyCountColPath,
                std::string _reTweetCountColPath,
                PanCake::ChunkRange _range
            ) : sentimentScoreColPath(_sentimentScoreColPath),
                textColPath(_textColPath),
                userColPath(_userColPath),
                favouriteCountColPath(_favouriteCountColPath),
                isPinnedColPath(_isPinnedColPath),
                isReplyToColPath(_isReplyToColPath),
                isRetweetColPath(_isRetweetColPath),
                replyCountColPath(_replyCountColPath),
                reTweetCountColPath(_reTweetCountColPath),
                range(_range) 
                {
                    assert(PanCake::fileExists(this->sentimentScoreColPath.c_str()));
                    assert(PanCake::fileExists(this->textColPath.c_str()));
                    assert(PanCake::fileExists(this->userColPath.c_str()));
                    assert(PanCake::fileExists(this->favouriteCountColPath.c_str()));
                    assert(PanCake::fileExists(this->isPinnedColPath.c_str()));
                    assert(PanCake::fileExists(this->isReplyToColPath.c_str()));
                    assert(PanCake::fileExists(this->isRetweetColPath.c_str()));
                    assert(PanCake::fileExists(this->replyCountColPath.c_str()));
                    assert(PanCake::fileExists(this->reTweetCountColPath.c_str()));
                }

            friend std::string runQueryFromFile(const char*,PanCake::TweetDate&,std::string,PanCake::QueryExecutionPolicy);
            friend std::string runQueryFromString(const char*,PanCake::TweetDate&,std::string,PanCake::QueryExecutionPolicy);
            friend bool setupEnv(Query&,sol::state&);
            friend std::string runQuery(Query&,sol::state&);
            friend void printEnv(PanCake::Query&,sol::state&);

            friend class ChunkRange;

        private:
            [[nodiscard]] std::string runQueryFromFile(std::string);
            [[nodiscard]] std::string runQueryFromString(std::string);

            std::string sentimentScoreColPath;
            std::string textColPath;
            std::string userColPath;
            std::string favouriteCountColPath;
            std::string isPinnedColPath;
            std::string isReplyToColPath;
            std::string isRetweetColPath;
            std::string replyCountColPath;
            std::string reTweetCountColPath;

            PanCake::ChunkRange range;
            
            int currentChunk = 0;

            std::vector<decltype(PanCake::Tweet::sentimentScore)> sentimentScoreCol;
            std::vector<decltype(PanCake::Tweet::text)> textCol;
            std::vector<decltype(PanCake::Tweet::user)> userCol;
            std::vector<decltype(PanCake::Tweet::favouriteCount)> favouriteCountCol;
            std::vector<int> isPinnedCol;
            std::vector<int> isReplyToCol;
            std::vector<int> isRetweetCol;
            std::vector<decltype(PanCake::Tweet::replyCount)> replyCountCol;
            std::vector<decltype(PanCake::Tweet::reTweetCount)> reTweetCountCol;
    };
}
