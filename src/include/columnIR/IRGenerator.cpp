#include "IRGenerator.hpp"
#include "aggregateChunkableColumns.hpp"
#include "chunkableSentimentScore.hpp"
#include "chunkableText.hpp"

bool PanCake::generateChunkedIR(const char*dataDir,PanCake::TweetDate&date,int chunkSize,const char*outDir)
{
    auto sentimentScore = PanCake::ChunkableSentimentScore::makeOutPutStream(outDir,date);
    auto text = PanCake::ChunkableText::makeOutPutStream(outDir,date);

    PanCake::AggregateChunkableColumns<PanCake::ChunkableSentimentScore,PanCake::ChunkableText> cols(sentimentScore,text);

    PanCake::IRGenerator gen(dataDir,date,chunkSize);

    return gen.generateChunkedIR(cols);
}
