#include <iostream>
#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/lib/loadJSON.hpp"
#include "../src/lib/searchScrapeTweet.hpp"
#include "../src/lib/bulkTweetStore.hpp"
#include "../src/lib/OCR.hpp"
#include "../src/lib/OCRTweetBin.hpp"

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

    REQUIRE(PanCake::OCRTweetBin("tests/rt/62ImagesInline","tests/rt/62ImagesInline/2019/04/14/16/00/56/d.json").attempted == 6);

    status = PanCake::bulkStoreTweets("tests/rt/62ImagesInline",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 0);
    REQUIRE(status.duplicates == 300);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.savedImages == 0);
    REQUIRE(status.binsWithNewTweets.size() == 0);
}

