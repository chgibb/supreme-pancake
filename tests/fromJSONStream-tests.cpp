#include <fstream>

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
    
    REQUIRE(res.at(0).date == "2010/01/02/23/59/59");
    REQUIRE(res.at(0).user == "wAii2KoOl");
    REQUIRE(res.at(0).text == "RT @mia_b_mia: Boys gettin fresh cuts AND new units?? HOL IT NA! its on! Won't be in THA house toniiiiight #RogerDat <¬ LOL #BleaDat");
    REQUIRE(res.at(0).textHash == "75ff3feca8988c63ac04a06d6b9c857a2756dc05c923b9840b3ced591dc80a46");
    REQUIRE(res.at(0).id == "7314112637");

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/fromJSONStream",res);
    REQUIRE(status.success);
    REQUIRE(status.duplicates == 0);
    REQUIRE(status.added == 10);

    PanCake::TweetStore sample("tests/rt/fromJSONStream","2010/01/02/23/59/59");

    REQUIRE(sample.loadBin('0') == true);
    REQUIRE(sample.loadBin('1') == true);
    REQUIRE(sample.loadBin('2') == true);
    REQUIRE(sample.loadBin('3') == true);
    REQUIRE(sample.loadBin('4') == true);
    REQUIRE(sample.loadBin('5') == false);
    REQUIRE(sample.loadBin('6') == false);
    REQUIRE(sample.loadBin('7') == false);
    REQUIRE(sample.loadBin('8') == false);
    REQUIRE(sample.loadBin('9') == true);
    REQUIRE(sample.loadBin('a') == false);
    REQUIRE(sample.loadBin('b') == true);
    REQUIRE(sample.loadBin('c') == false);
    REQUIRE(sample.loadBin('d') == false);
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
    REQUIRE(sample.bins['1'].bucketa.size() == 0);
    REQUIRE(sample.bins['1'].bucketb.size() == 0);
    REQUIRE(sample.bins['1'].bucketc.size() == 0);
    REQUIRE(sample.bins['1'].bucketd.size() == 0);
    REQUIRE(sample.bins['1'].buckete.size() == 0);
    REQUIRE(sample.bins['1'].bucketf.size() == 1);
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