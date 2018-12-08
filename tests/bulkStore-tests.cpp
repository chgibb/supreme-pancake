#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/loadJSON.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/bulkTweetStore.hpp"

TEST_CASE("Parse bulk search scrape tweets with duplicates from JSON and save","[JSON")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/bulkStore",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 5040);
    REQUIRE(status.duplicates == 500);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.binsWithNewTweets.size() == 996);

    status = PanCake::bulkStoreTweets("tests/rt/bulkStore",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 0);
    REQUIRE(status.duplicates == 5540);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.binsWithNewTweets.size() == 0);
}

TEST_CASE("Image URLs should have been saved","")
{
    PanCake::TweetStore sample("tests/rt/bulkStore","2018/08/23/02/10/13");

    REQUIRE(sample.loadBin('e') == true);
    REQUIRE(sample.bins['e'].bucket5.size() == 1);

    PanCake::Tweet tweet = sample.bins['e'].bucket5.at(0);

    REQUIRE(tweet.images.size() == 4);
    REQUIRE(tweet.images.at(0) == "https://pbs.twimg.com/media/DlPum_HV4AA_jlk.png");
    REQUIRE(tweet.images.at(1) == "https://pbs.twimg.com/media/DlPwdMAUYAA8b_H.jpg");
    REQUIRE(tweet.images.at(2) == "https://pbs.twimg.com/media/DlPymmBUYAI-xjx.jpg");
    REQUIRE(tweet.images.at(3) == "https://pbs.twimg.com/media/DlP6sSaU8AA6GM9.jpg");

}