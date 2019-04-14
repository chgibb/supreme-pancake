#include <iostream>
#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/lib/loadJSON.hpp"
#include "../src/lib/searchScrapeTweet.hpp"
#include "../src/lib/bulkTweetStore.hpp"

TEST_CASE("Parses and saves inline images","")
{
    std::ifstream tweetStream("tests/res/62ImagesInline.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());
    
    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/62ImagesInline",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 300);
    REQUIRE(status.duplicates == 0);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.savedImages == 62);
    REQUIRE(status.binsWithNewTweets.size() == 48);

    status = PanCake::bulkStoreTweets("tests/rt/62ImagesInline",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 0);
    REQUIRE(status.duplicates == 300);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.savedImages == 0);
    REQUIRE(status.binsWithNewTweets.size() == 0);
}