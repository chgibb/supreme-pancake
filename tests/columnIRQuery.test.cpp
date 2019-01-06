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
#include "../src/include/columnIR/IRGenerator.hpp"
#include "../src/include/query/query.hpp"

TEST_CASE("should write test data","")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/columnIRQuery1",tweets);

    REQUIRE(status.success == true);
}

TEST_CASE("should generate IR 2018/11/06","")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "11";
    date.day = "06";

    REQUIRE(PanCake::generateChunkedIR("tests/rt/columnIRQuery1",date,10,"tests/rt/columnIRQuery1") == true);

    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-sentimentScore.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-text.lua"));
}

TEST_CASE("manually written query for 2018/11/06","")
{
    PanCake::Query q("tests/rt/columnIRQuery1/2018-11-06-sentimentScore.lua","tests/rt/columnIRQuery1/2018-11-06-text.lua");
    REQUIRE(q.runQueryFromFile("tests/res/manualFindNeutralTweets.lua") == "7");
}

TEST_CASE("should generate IR for 2018/11/09","")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "11";
    date.day = "09";

    REQUIRE(PanCake::generateChunkedIR("tests/rt/columnIRQuery1",date,1000,"tests/rt/columnIRQuery1") == true);

    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-sentimentScore.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-text.lua"));
}

TEST_CASE("manually written query for 2018/11/09","")
{
    PanCake::Query q("tests/rt/columnIRQuery1/2018-11-09-sentimentScore.lua","tests/rt/columnIRQuery1/2018-11-09-text.lua");
    REQUIRE(q.runQueryFromFile("tests/res/manualFindNeutralTweets.lua") == "1402");
}