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
#include "../src/lib/enumerateRawTweetsInDay.hpp"
#include "../src/lib/IRGenerator.hpp"
#include "../src/lib/query.hpp"

TEST_CASE("should write test data","")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/columnIRQuery1",tweets);

    REQUIRE(status.success == true);
}

TEST_CASE("manually written query for 2018/11/06","")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "11";
    date.day = "06";

    REQUIRE(PanCake::generateChunkedIR("tests/rt/columnIRQuery1",date,10,"tests/rt/columnIRQuery1") == true);

    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-sentimentScore.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-text.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-user.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06.chunkCount"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06.totalCount"));

    int qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,PanCake::QueryExecutionPolicy::serial,"tests/res/manualFindNeutralTweets.lua").c_str());

    REQUIRE(qCount == 7);

    int manualCount = 0;

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount](const PanCake::Tweet&tweet) -> void {
        if(tweet.sentimentScore == 0)
            manualCount++;
    });

    REQUIRE(manualCount == 7);
    REQUIRE(manualCount == qCount);

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,PanCake::QueryExecutionPolicy::serial,"tests/res/manualFindTweetsFromUser1.lua").c_str());

    REQUIRE(qCount == 6);

}

TEST_CASE("manually written query for 2018/11/09","")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "11";
    date.day = "09";

    REQUIRE(PanCake::generateChunkedIR("tests/rt/columnIRQuery1",date,1000,"tests/rt/columnIRQuery1") == true);

    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-sentimentScore.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-text.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-user.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09.chunkCount"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09.totalCount"));

    int qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,PanCake::QueryExecutionPolicy::serial,"tests/res/manualFindNeutralTweets.lua").c_str());

    REQUIRE(qCount == 1402);

    int manualCount = 0;

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount](const PanCake::Tweet&tweet) -> void {
        if(tweet.sentimentScore == 0)
            manualCount++;
    });

    REQUIRE(manualCount == 1402);
    REQUIRE(manualCount == qCount);

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,PanCake::QueryExecutionPolicy::serial,"tests/res/manualFindTweetsFromUser1.lua").c_str());

    REQUIRE(qCount == 4);
}
