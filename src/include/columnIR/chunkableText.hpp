#pragma once

#include "chunkableColumn.hpp"
#include "makeColumnIROutPutPath.hpp"
#include "../tweet.hpp"
#include "../tweetDate.hpp"

namespace PanCake
{
    class ChunkableText : public PanCake::ChunkableColumn
    {
        public:
            using PanCake::ChunkableColumn::ChunkableColumn;

            std::string functionSuffix = "Text";

            void addItem(const PanCake::Tweet&tweet)
            {
                this->addQuotedValueToChunk(tweet.text);
            }

            void beginIR()
            {
                this->writeFunctionSignature(this->functionSuffix);
            }

            static std::ofstream makeOutPutPath(std::string prefix,PanCake::TweetDate&date)
            {
                return PanCake::makeColumnIROutPutPath(prefix,date,"text");
            }
    };
}
