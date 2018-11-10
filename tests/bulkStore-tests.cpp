#include <fstream>

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
    REQUIRE(status.added == 5039);
    REQUIRE(status.duplicates == 501);

    status = PanCake::bulkStoreTweets("tests/rt/bulkStore",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 0);
    REQUIRE(status.duplicates == 5540);
}