#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex.h>

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
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-favouriteCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-isPinned.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-isReplyTo.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-isRetweet.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-replyCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-06-reTweetCount.lua"));

    int qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindNeutralTweets.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 7);

    int manualCount = 0;

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount](const PanCake::Tweet&tweet) -> void {
        if(tweet.sentimentScore == 0)
            manualCount++;
    });

    REQUIRE(manualCount == 7);
    REQUIRE(manualCount == qCount);

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindTweetsFromUser1.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 6);

}

TEST_CASE("manualFindNeutralTweets","")
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
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-favouriteCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isPinned.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isReplyTo.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isRetweet.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-replyCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-reTweetCount.lua"));

    int qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindNeutralTweets.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 1402);

    int manualCount = 0;

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount](const PanCake::Tweet&tweet) -> void {
        if(tweet.sentimentScore == 0)
            manualCount++;
    });

    REQUIRE(manualCount == 1402);
    REQUIRE(manualCount == qCount);

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindTweetsFromUser1.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 4);
}

TEST_CASE("manualFindTotalRetweets","")
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
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-favouriteCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isPinned.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isReplyTo.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isRetweet.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-replyCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-reTweetCount.lua"));

    int qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindTotalRetweets.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 4);

    int manualCount = 0;

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount](const PanCake::Tweet&tweet) -> void {
        if(tweet.isRetweet)
            manualCount++;
    });

    REQUIRE(manualCount == 4);
    REQUIRE(manualCount == qCount);

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindTotalRetweets.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 4);
}

TEST_CASE("manualNumMentions1","")
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
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-favouriteCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isPinned.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isReplyTo.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isRetweet.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-replyCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-reTweetCount.lua"));

    int qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualNumMentions1.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 22);

    int manualCount = 0;

    ::regex_t reg;
    ::regcomp(&reg,"@realDonaldTrump",REG_ICASE);

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount,&reg](const PanCake::Tweet&tweet) -> void {
        if(::regexec(&reg,tweet.text.c_str(),0,NULL,0) == 0)
            manualCount++;
    });

    REQUIRE(manualCount == 22);
    REQUIRE(manualCount == qCount);

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindTotalRetweets.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 4);
}

TEST_CASE("manualAvgSentiment1","")
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
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-favouriteCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isPinned.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isReplyTo.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-isRetweet.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-replyCount.lua"));
    REQUIRE(PanCake::fileExists("tests/rt/columnIRQuery1/2018-11-09-reTweetCount.lua"));

    double qCount = std::stod(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualAvgSentiment1.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    int manualCount = 0;

    ::regex_t reg;
    ::regcomp(&reg,"@realDonaldTrump",REG_ICASE);

    double totalSentiment = 0;
    int matched = 0;

    PanCake::enumerateRawTweetsInDay("tests/rt/columnIRQuery1",date,[&manualCount,&totalSentiment,&matched,&reg](const PanCake::Tweet&tweet) -> void {
        if(::regexec(&reg,tweet.text.c_str(),0,NULL,0) == 0)
        {
            totalSentiment += tweet.sentimentScore;
            matched++;
        }
    });

    double avgSentiment = totalSentiment/matched;

    REQUIRE(matched == 22);
    REQUIRE(totalSentiment == -64.0);

    REQUIRE(std::to_string(avgSentiment) == std::to_string(qCount));

    qCount = std::atoi(PanCake::runQueryFromFile("tests/rt/columnIRQuery1",date,"tests/res/manualFindTotalRetweets.lua",PanCake::QueryExecutionPolicy::serial).c_str());

    REQUIRE(qCount == 4);
}
