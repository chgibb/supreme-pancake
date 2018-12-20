#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/loadJSON.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/bulkTweetStore.hpp"
#include "../src/include/enumerateRawTweetsInDay.hpp"

TEST_CASE("should write test data","")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/enumerateRawTweetsInDay",tweets);

    REQUIRE(status.success == true);
}

TEST_CASE("should count number of tweets in day","")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "11";
    date.day = "09";

    int count = 0;
    PanCake::enumerateRawTweetsInDay(
        "tests/rt/enumerateRawTweetsInDay",
        date,
        [&count](const PanCake::Tweet&tweet) -> void {
            count++;
        }
    );

    REQUIRE(count == 4568);
}
