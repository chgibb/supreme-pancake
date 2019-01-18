#pragma once

#include <vector>

#include <sol.hpp>

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

    [[nodiscard]] std::string runQueryFromFile(const char*,PanCake::TweetDate&,PanCake::QueryExecutionPolicy,std::string);
    [[nodiscard]] std::string runQueryFromString(const char*,PanCake::TweetDate&,PanCake::QueryExecutionPolicy,std::string);

    class Query
    {
        public:
            Query() = delete;
            Query(
                std::string _sentimentScoreColPath,
                std::string _textColPath,
                std::string _userColPath,
                PanCake::ChunkRange _range
            ) : sentimentScoreColPath(_sentimentScoreColPath),
                textColPath(_textColPath),
                userColPath(_userColPath),
                range(_range) {}

            friend std::string runQueryFromFile(const char*,PanCake::TweetDate&,PanCake::QueryExecutionPolicy,std::string);
            friend std::string runQueryFromString(const char*,PanCake::TweetDate&,PanCake::QueryExecutionPolicy,std::string);
            friend bool setupEnv(Query&,sol::state&);
            friend std::string runQuery(Query&,sol::state&);

            friend class ChunkRange;

        private:
            [[nodiscard]] std::string runQueryFromFile(std::string);
            [[nodiscard]] std::string runQueryFromString(std::string);

            std::string sentimentScoreColPath;
            std::string textColPath;
            std::string userColPath;

            PanCake::ChunkRange range;
            
            int currentChunk = 0;

            std::vector<decltype(PanCake::Tweet::sentimentScore)> sentimentScoreCol;
            std::vector<decltype(PanCake::Tweet::text)> textCol;
            std::vector<decltype(PanCake::Tweet::user)> userCol;
    };
}
