#pragma once

#include <vector>

#include <sol.hpp>

#include "../tweet.hpp"
#include "../tweetDate.hpp"

namespace PanCake
{
    enum class QueryExecutionPolicy
    {
        serial = 0
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
                int _totalChunks
            ) : sentimentScoreColPath(_sentimentScoreColPath),
                textColPath(_textColPath),
                totalChunks(_totalChunks) {}

            friend std::string runQueryFromFile(const char*,PanCake::TweetDate&,PanCake::QueryExecutionPolicy,std::string);
            friend std::string runQueryFromString(const char*,PanCake::TweetDate&,PanCake::QueryExecutionPolicy,std::string);
            friend bool setupEnv(Query&,sol::state&);
            friend std::string runQuery(Query&,sol::state&);

        private:
            [[nodiscard]] std::string runQueryFromFile(std::string);
            [[nodiscard]] std::string runQueryFromString(std::string);
            std::string sentimentScoreColPath;
            std::string textColPath;
            
            int currentChunk = 0;
            int totalChunks = 0;

            std::vector<decltype(PanCake::Tweet::sentimentScore)> sentimentScoreCol;
            std::vector<decltype(PanCake::Tweet::text)> textCol;
    };
}
