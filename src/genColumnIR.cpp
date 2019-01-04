#include <iostream>
#include <fstream>
#include <string>

#include "vendor/cxxopts/include/cxxopts.hpp"

#include "include/enumerateRawTweetsInDay.hpp"
#include "include/columnIR/aggregateChunkableColumns.hpp"
#include "include/columnIR/chunkableColumn.hpp"
#include "include/columnIR/chunkableSentimentScore.hpp"
#include "include/columnIR/chunkableText.hpp"
#include "include/columnIR/IRGenerator.hpp"

int main(int argc,char*argv[])
{
    cxxopts::Options options("genColumnIR", "");

    options.add_options()
    ("d,dir","Storage directory path",cxxopts::value<std::string>())
    ("o,outDir","Output directory path",cxxopts::value<std::string>())
    ("y,year","Year",cxxopts::value<std::string>())
    ("m,month","Month",cxxopts::value<std::string>())
    ("D,day","Day",cxxopts::value<std::string>())
    ("c,chunkSize","Chunk Size",cxxopts::value<int>());

    auto result = options.parse(argc,argv);

    std::string storageDir = result["dir"].as<std::string>();
    std::string outDir = result["outDir"].as<std::string>();
    std::string year = result["year"].as<std::string>();
    std::string month = result["month"].as<std::string>();
    std::string day = result["day"].as<std::string>();
    int chunkSize = result["chunkSize"].as<int>();

    PanCake::TweetDate date;
    date.year = year;
    date.month = month;
    date.day = day;

    auto sentimentScore = PanCake::ChunkableSentimentScore::makeOutPutPath(outDir,date);
    auto text = PanCake::ChunkableText::makeOutPutPath(outDir,date);

    PanCake::AggregateChunkableColumns<PanCake::ChunkableSentimentScore,PanCake::ChunkableText> cols(sentimentScore,text);

    PanCake::IRGenerator gen(storageDir.c_str(),date,chunkSize);
    
    gen.generateChunkedIR(cols);

    return 0;
}
