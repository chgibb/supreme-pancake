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

            static constexpr const char* functionSuffix = "SentimentScore";
            static constexpr const char*contName = "sentimentScoreCol";

            void addItem(const PanCake::Tweet&tweet)
            {
                this->addValueToChunk(this->contName,tweet.sentimentScore);
            }

            void beginIR()
            {
                this->writeFunctionSignature(this->functionSuffix);
            }

            void writeTotalChunksFunction(const int&totalChunks)
            {
                this->_writeTotalChunksFunction(totalChunks,this->functionSuffix);
            }

            static std::ofstream makeOutPutPath(std::string prefix,PanCake::TweetDate&date)
            {
                return PanCake::makeColumnIROutPutPath(prefix,date,"sentimentScore");
            }
    };
}
