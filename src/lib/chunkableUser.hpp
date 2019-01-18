#pragma once

#include "chunkableColumn.hpp"
#include "makeColumnIROutPutPath.hpp"
#include "tweet.hpp"
#include "tweetDate.hpp"

namespace PanCake
{
    class ChunkableUser : public PanCake::ChunkableColumn
    {
        public:
            using PanCake::ChunkableColumn::ChunkableColumn;

            static constexpr const char*functionSuffix = "User";
            static constexpr const char*contName = "userCol";

            void addItem(const PanCake::Tweet&tweet)
            {
                this->addQuotedValueToChunk(this->contName,tweet.user);
            }

            void beginIR()
            {
                this->writeFunctionSignature(this->functionSuffix);
            }

            static std::ofstream makeOutPutStream(std::string prefix,PanCake::TweetDate&date)
            {
                return std::ofstream(PanCake::ChunkableUser::makeOutPutPath(prefix,date),std::ios::out);
            }

            static std::string makeOutPutPath(std::string prefix,PanCake::TweetDate&date)
            {
                return PanCake::makeColumnIROutputPath(prefix,date,"user");
            }
    };
}
