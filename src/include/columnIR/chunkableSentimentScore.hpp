#pragma once

#include "chunkableColumn.hpp"
#include "makeColumnIROutPutPath.hpp"
#include "../tweet.hpp"
#include "../tweetDate.hpp"

namespace PanCake
{
    class ChunkableSentimentScore : public PanCake::ChunkableColumn
    {
        public:
            using PanCake::ChunkableColumn::ChunkableColumn;

            std::string functionSuffix = "SentimentScore";

            void addItem(const PanCake::Tweet&tweet)
            {
                this->addValueToChunk(tweet.sentimentScore);
            }

            void beginIR()
            {
                this->writeFunctionSignature(this->functionSuffix);
            }

            static std::ofstream makeOutPutPath(std::string prefix,PanCake::TweetDate&date)
            {
                return PanCake::makeColumnIROutPutPath(prefix,date,"sentimentScore");
            }
    };
}
