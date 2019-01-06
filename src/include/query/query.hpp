#pragma once

#include <vector>

#include <sol.hpp>

#include "../tweet.hpp"

namespace PanCake
{
    class Query
    {
        public:
            enum class Column
            {
                sentimentScore,
                text
            };

            Query() = delete;
            Query(
                std::string _sentimentScoreColPath,
                std::string _textColPath
            ) : sentimentScoreColPath(_sentimentScoreColPath),textColPath(_textColPath) {}

            [[nodiscard]] std::string runQueryFromFile(std::string);
            [[nodiscard]] std::string runQueryFromString(std::string);

            friend bool setupEnv(Query&,sol::state&);
            friend std::string runQuery(Query&,sol::state&);

        private:
            int currentChunk = 0;

            std::string sentimentScoreColPath;
            std::string textColPath;

            std::vector<decltype(PanCake::Tweet::sentimentScore)> sentimentScoreCol;
            std::vector<decltype(PanCake::Tweet::text)> textCol;
    };
}