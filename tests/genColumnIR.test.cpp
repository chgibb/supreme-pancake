#include <fstream>
#include <iostream>
#include <algorithm>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/loadJSON.hpp"
#include "../src/include/fileExists.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/bulkTweetStore.hpp"
#include "../src/include/tweetDate.hpp"
#include "../src/include/columnIR/chunkableSentimentScore.hpp"
#include "../src/include/columnIR/chunkableText.hpp"
#include "../src/include/columnIR/aggregateChunkableColumns.hpp"
#include "../src/include/columnIR/IRGenerator.hpp"

TEST_CASE("should write test data","")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/columnIR1",tweets);

    REQUIRE(status.success == true);
}

TEST_CASE("should write column IR","")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "11";
    date.day = "06";

    auto sentimentScore = PanCake::ChunkableSentimentScore::makeOutPutPath("tests/rt/columnIR1",date);
    auto text = PanCake::ChunkableText::makeOutPutPath("tests/rt/columnIR1",date);

    PanCake::AggregateChunkableColumns<PanCake::ChunkableSentimentScore,PanCake::ChunkableText> cols(sentimentScore,text);

    PanCake::IRGenerator gen("tests/rt/columnIR1",date,10);
    
    gen.generateChunkedIR(cols);

    REQUIRE(PanCake::fileExists("tests/rt/columnIR1/2018-11-06-sentimentScore.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIR1/2018-11-06-text.lua"));
}
