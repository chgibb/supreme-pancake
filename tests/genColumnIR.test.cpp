#include <fstream>
#include <iostream>
#include <algorithm>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/lib/loadJSON.hpp"
#include "../src/lib/fileExists.hpp"
#include "../src/lib/searchScrapeTweet.hpp"
#include "../src/lib/bulkTweetStore.hpp"
#include "../src/lib/tweetDate.hpp"
#include "../src/lib/IRGenerator.hpp"

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

    REQUIRE(PanCake::generateChunkedIR("tests/rt/columnIR1",date,10,"tests/rt/columnIR1") == true);

    REQUIRE(PanCake::fileExists("tests/rt/columnIR1/2018-11-06-sentimentScore.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIR1/2018-11-06-text.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIR1/2018-11-06.chunkCount"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIR1/2018-11-06.totalCount"));


    REQUIRE(PanCake::generateChunkedIR("tests/rt/columnIR1",date,10,"tests/rt/pathThatDoesntExist") == false);
}
