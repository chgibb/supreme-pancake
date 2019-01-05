#pragma once

#include "../enumerateRawTweetsInDay.hpp"

namespace PanCake
{
    class IRGenerator
    {
        public:
            IRGenerator(const char*_dataDir,PanCake::TweetDate _date,int _chunkSize) : dataDir(_dataDir),date(_date),chunkSize(_chunkSize) {}
    
            template<class T>
            void generateChunkedIR(T&col)
            {
                col.beginIR();

                int currentChunk = 0;
                int itemsInChunk = 0;

                PanCake::enumerateRawTweetsInDay(
                    this->dataDir,
                    this->date,
                    [this,&col,&currentChunk,&itemsInChunk](const PanCake::Tweet&tweet) -> void {
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

                col.writeTotalChunksFunction(currentChunk+1);
            }

        private:
            const char*dataDir;
            PanCake::TweetDate date;
            int chunkSize = 0;
    };
}
