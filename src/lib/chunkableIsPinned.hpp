#pragma once

#include "chunkableColumn.hpp"
#include "makeColumnIROutPutPath.hpp"
#include "tweet.hpp"
#include "tweetDate.hpp"

namespace PanCake
{
    class ChunkableIsPinned : public PanCake::ChunkableColumn
    {
        public:
            using PanCake::ChunkableColumn::ChunkableColumn;

            static constexpr const char*functionSuffix = "IsPinned";
            static constexpr const char*contName = "isPinnedCol";

            void addItem(const PanCake::Tweet&tweet)
            {
                this->addValueToChunk(this->contName,tweet.isPinned);
            }

            void beginIR()
            {
                this->writeFunctionSignature(this->functionSuffix);
            }

            static std::ofstream makeOutPutStream(std::string prefix,PanCake::TweetDate&date)
            {
                return std::ofstream(PanCake::ChunkableIsPinned::makeOutPutPath(prefix,date),std::ios::out);
            }

            static std::string makeOutPutPath(std::string prefix,PanCake::TweetDate&date)
            {
                return PanCake::makeColumnIROutputPath(prefix,date,"isPinned");
            }
    };
}
