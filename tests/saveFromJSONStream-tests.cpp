#include <fstream>

#include <catch2/catch.hpp>

#include "../src/include/loadJSONFromStream.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/tweetStore.hpp"

TEST_CASE("Save select tweets to flat buffers","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    REQUIRE(PanCake::makeTweetTimePointPath("saveFromJSONStream",tweets.at(0)) == "saveFromJSONStream/2008/02/07/23/59/59");

    REQUIRE(PanCake::makeTweetTimePointFBBinPath("saveFromJSONStream",tweets.at(0)) == "saveFromJSONStream/2008/02/07/23/59/59/5.fb");
    
}