#pragma once

#include "enumerateRawTweetsInDay.hpp"
#include "tweetDate.hpp"
#include "makeColumnIROutPutPath.hpp"

namespace PanCake
{
    bool generateChunkedIR(const char*,PanCake::TweetDate&,int,const char*);
    class IRGenerator
    {
        public:
            IRGenerator(const char*_dataDir,PanCake::TweetDate _date,int _chunkSize) : dataDir(_dataDir),date(_date),chunkSize(_chunkSize) {}
    
            template<class T>
            bool generateChunkedIR(T&col)
            {
                bool badStream = false;

                col.badStream(badStream);
                if(badStream)
                    return false;

                col.beginIR();

                int currentChunk = 0;
                int itemsInChunk = 0;
                int totalCount = 0;

                PanCake::enumerateRawTweetsInDay(
                    this->dataDir,
                    this->date,
                    [this,&col,&currentChunk,&itemsInChunk,&totalCount](const PanCake::Tweet&tweet) -> void {
                        totalCount++;
                        if(itemsInChunk >= this->chunkSize)
                        {
                            itemsInChunk = 0;
                            col.endChunk();
                            currentChunk++;
                        }

                        if(itemsInChunk == 0)
                        {
                            col.beginChunk(currentChunk);
                        }

                        col.addItem(tweet);
                        itemsInChunk++;
                    }
                );

                col.endChunk();
                col.endIR();

                auto totalChunksStream = PanCake::makeColumnIRChunkCountStream(this->dataDir,this->date);
                auto totalCountStream = PanCake::makeColumnIRTotalCountStream(this->dataDir,this->date);

                totalChunksStream<<currentChunk+1;
                totalCountStream<<totalCount;

                return true;
            }

        private:
            const char*dataDir;
            PanCake::TweetDate date;
            int chunkSize = 0;
    };
}
