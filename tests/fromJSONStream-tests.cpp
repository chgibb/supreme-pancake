#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/loadJSON.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/bulkTweetStore.hpp"

TEST_CASE("Load JSON from stream","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());
}

TEST_CASE("Parse search scrape tweets from JSON and save","[JSON")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto res = PanCake::parseSearchScrapeTweetsFromJSON(json);
    
    REQUIRE(res.at(0).date == "2018/11/09/21/19/28");
    REQUIRE(res.at(0).user == "scotty8692");
    REQUIRE(res.at(0).text == "Same as Linfield fans at the Showgrounds when they weren't doing so well last season-poorest Blues crowd I've saw in my 15 years of going to games at the Showgrounds. The fairweather fans will always turn up and subsequently not turn up, for all teams.");
    REQUIRE(res.at(0).textHash == "a229b09b6ef6791968ac3e2fa2636a74c925e3e44b5077b95cee56ef66d014af");
    REQUIRE(res.at(0).id == "1061005372813647873");
    REQUIRE(res.at(0).replyCount == 0);
    REQUIRE(res.at(0).reTweetCount == 0);
    REQUIRE(res.at(0).favouriteCount == 0);
    REQUIRE(res.at(0).sentimentScore == 0);
    REQUIRE(res.at(0).comparativeSentimentScore == 0);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/fromJSONStream",res);
    REQUIRE(status.success);
    REQUIRE(status.duplicates == 0);
    REQUIRE(status.added == 10);

    PanCake::TweetStore sample("tests/rt/fromJSONStream","2018/11/09/21/19/28");

    REQUIRE(sample.loadBin('0') == false);
    REQUIRE(sample.loadBin('1') == true);
    REQUIRE(sample.loadBin('2') == true);
    REQUIRE(sample.loadBin('3') == true);
    REQUIRE(sample.loadBin('4') == true);
    REQUIRE(sample.loadBin('5') == false);
    REQUIRE(sample.loadBin('6') == true);
    REQUIRE(sample.loadBin('7') == false);
    REQUIRE(sample.loadBin('8') == false);
    REQUIRE(sample.loadBin('9') == false);
    REQUIRE(sample.loadBin('a') == true);
    REQUIRE(sample.loadBin('b') == false);
    REQUIRE(sample.loadBin('c') == true);
    REQUIRE(sample.loadBin('d') == true);
    REQUIRE(sample.loadBin('e') == false);
    REQUIRE(sample.loadBin('f') == true);

    REQUIRE(sample.bins['1'].bucket0.size() == 0);
    REQUIRE(sample.bins['1'].bucket1.size() == 0);
    REQUIRE(sample.bins['1'].bucket2.size() == 0);
    REQUIRE(sample.bins['1'].bucket3.size() == 0);
    REQUIRE(sample.bins['1'].bucket4.size() == 0);
    REQUIRE(sample.bins['1'].bucket5.size() == 0);
    REQUIRE(sample.bins['1'].bucket6.size() == 0);
    REQUIRE(sample.bins['1'].bucket7.size() == 0);
    REQUIRE(sample.bins['1'].bucket8.size() == 0);
    REQUIRE(sample.bins['1'].bucket9.size() == 0);
    REQUIRE(sample.bins['1'].bucketa.size() == 1);
    REQUIRE(sample.bins['1'].bucketb.size() == 0);
    REQUIRE(sample.bins['1'].bucketc.size() == 0);
    REQUIRE(sample.bins['1'].bucketd.size() == 0);
    REQUIRE(sample.bins['1'].buckete.size() == 0);
    REQUIRE(sample.bins['1'].bucketf.size() == 0);
}


TEST_CASE("Should not double save same set of search scrape tweets","[JSON")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto res = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/fromJSONStream",res);
    REQUIRE(status.success);
    REQUIRE(status.added == 0);
    REQUIRE(status.duplicates == 10);
}