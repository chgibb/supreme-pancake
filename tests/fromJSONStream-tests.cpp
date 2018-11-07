#include <fstream>

#include <catch2/catch.hpp>

#include "../src/include/loadJSONFromStream.hpp"
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
    
    REQUIRE(res.at(0).date == "2008/02/07/23/59/59");
    REQUIRE(res.at(0).user == "newestdiscovery");
    REQUIRE(res.at(0).text == "www.newestdiscovery.com update: The Future of XML (How will you use XML in years to come? The wheels of progress turn slowly, but tu...)");
    REQUIRE(res.at(0).textHash == "3b2858570a2acde5c14efd3c2158393a601e8c918c232fc3ed3a818add569123");
    REQUIRE(res.at(0).id == "688736272");

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/fromJSONStream",res);
    REQUIRE(status.success);
    REQUIRE(status.duplicates == 400);
    REQUIRE(status.added == 800);

    PanCake::TweetStore sample("tests/rt/fromJSONStream","2016/12/01/23/59/59");

    REQUIRE(sample.loadBin('0') == false);
    REQUIRE(sample.loadBin('1') == true);
    REQUIRE(sample.loadBin('2') == false);
    REQUIRE(sample.loadBin('3') == false);
    REQUIRE(sample.loadBin('4') == false);
    REQUIRE(sample.loadBin('5') == false);
    REQUIRE(sample.loadBin('6') == false);
    REQUIRE(sample.loadBin('7') == false);
    REQUIRE(sample.loadBin('8') == false);
    REQUIRE(sample.loadBin('9') == false);
    REQUIRE(sample.loadBin('a') == false);
    REQUIRE(sample.loadBin('b') == false);
    REQUIRE(sample.loadBin('c') == false);
    REQUIRE(sample.loadBin('d') == false);
    REQUIRE(sample.loadBin('e') == false);
    REQUIRE(sample.loadBin('f') == false);

    REQUIRE(sample.bins['1'].bucket0.size() == 0);
    REQUIRE(sample.bins['1'].bucket1.size() == 1);
    REQUIRE(sample.bins['1'].bucket2.size() == 0);
    REQUIRE(sample.bins['1'].bucket3.size() == 0);
    REQUIRE(sample.bins['1'].bucket4.size() == 0);
    REQUIRE(sample.bins['1'].bucket5.size() == 0);
    REQUIRE(sample.bins['1'].bucket6.size() == 0);
    REQUIRE(sample.bins['1'].bucket7.size() == 0);
    REQUIRE(sample.bins['1'].bucket8.size() == 0);
    REQUIRE(sample.bins['1'].bucket9.size() == 1);
    REQUIRE(sample.bins['1'].bucketa.size() == 1);
    REQUIRE(sample.bins['1'].bucketb.size() == 0);
    REQUIRE(sample.bins['1'].bucketc.size() == 1);
    REQUIRE(sample.bins['1'].bucketd.size() == 0);
    REQUIRE(sample.bins['1'].buckete.size() == 0);
    REQUIRE(sample.bins['1'].bucketf.size() == 0);
}

/*
TEST_CASE("Should double save same set of search scrape tweets","[JSON")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto res = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/fromJSONStream",res);
    REQUIRE(status.success);
    REQUIRE(status.added == 800);

}*/