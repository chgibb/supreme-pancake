#pragma once

#include "chunkableColumn.hpp"
#include "makeColumnIROutPutPath.hpp"
#include "tweet.hpp"
#include "tweetDate.hpp"

namespace PanCake
{
    class ChunkableSentimentScore : public PanCake::ChunkableColumn
    {
        public:
            using PanCake::ChunkableColumn::ChunkableColumn;

            static constexpr const char*functionSuffix = "SentimentScore";
            static constexpr const char*contName = "sentimentScoreCol";

            void addItem(const PanCake::Tweet&tweet)
            {
                this->addValueToChunk(this->contName,tweet.sentimentScore);
            }

            void beginIR()
            {
                this->writeFunctionSignature(this->functionSuffix);
            }

            static std::ofstream makeOutPutStream(std::string prefix,PanCake::TweetDate&date)
            {
                return std::ofstream(PanCake::ChunkableSentimentScore::makeOutPutPath(prefix,date),std::ios::out);
            }

            static std::string makeOutPutPath(std::string prefix,PanCake::TweetDate&date)
            {
                return PanCake::makeColumnIROutputPath(prefix,date,"sentimentScore");
            }
    };
}
