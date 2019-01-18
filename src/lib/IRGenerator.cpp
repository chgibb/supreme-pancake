#include "IRGenerator.hpp"
#include "aggregateChunkableColumns.hpp"
#include "chunkableSentimentScore.hpp"
#include "chunkableText.hpp"
#include "chunkableUser.hpp"

bool PanCake::generateChunkedIR(const char*dataDir,PanCake::TweetDate&date,int chunkSize,const char*outDir)
{
    auto sentimentScore = PanCake::ChunkableSentimentScore::makeOutPutStream(outDir,date);
    auto text = PanCake::ChunkableText::makeOutPutStream(outDir,date);
    auto user = PanCake::ChunkableUser::makeOutPutStream(outDir,date);

    PanCake::AggregateChunkableColumns<
        PanCake::ChunkableSentimentScore,
        PanCake::ChunkableText,
        PanCake::ChunkableUser
    > cols(
        sentimentScore,
        text,
        user
    );

    PanCake::IRGenerator gen(dataDir,date,chunkSize);

    return gen.generateChunkedIR(cols);
}
