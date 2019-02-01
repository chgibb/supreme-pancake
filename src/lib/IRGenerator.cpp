#include "IRGenerator.hpp"
#include "aggregateChunkableColumns.hpp"
#include "chunkableSentimentScore.hpp"
#include "chunkableText.hpp"
#include "chunkableUser.hpp"
#include "chunkableReplyCount.hpp"
#include "chunkableReTweetCount.hpp"
#include "chunkableFavouriteCount.hpp"

bool PanCake::generateChunkedIR(const char*dataDir,PanCake::TweetDate&date,int chunkSize,const char*outDir)
{
    auto sentimentScore = PanCake::ChunkableSentimentScore::makeOutPutStream(outDir,date);
    auto text = PanCake::ChunkableText::makeOutPutStream(outDir,date);
    auto user = PanCake::ChunkableUser::makeOutPutStream(outDir,date);
    auto replyCount = PanCake::ChunkableReplyCount::makeOutPutStream(outDir,date);
    auto reTweetCount = PanCake::ChunkableReTweetCount::makeOutPutStream(outDir,date);
    auto favouriteCount = PanCake::ChunkableFavouriteCount::makeOutPutStream(outDir,date);

    PanCake::AggregateChunkableColumns<
        PanCake::ChunkableSentimentScore,
        PanCake::ChunkableText,
        PanCake::ChunkableUser,
        PanCake::ChunkableReplyCount,
        PanCake::ChunkableReTweetCount,
        PanCake::ChunkableFavouriteCount
    > cols(
        sentimentScore,
        text,
        user,
        replyCount,
        reTweetCount,
        favouriteCount
    );

    PanCake::IRGenerator gen(dataDir,date,chunkSize);

    return gen.generateChunkedIR(cols);
}
