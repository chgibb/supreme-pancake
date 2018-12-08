#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/loadJSON.hpp"
#include "../src/include/makeTweetTimePointPaths.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/tweetStore.hpp"

TEST_CASE("Save select tweets to flat buffers","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    REQUIRE(PanCake::makeTweetTimePointPath("saveFromJSONStream",tweets.at(0)) == "saveFromJSONStream/2018/11/09/21/19/28");    
}