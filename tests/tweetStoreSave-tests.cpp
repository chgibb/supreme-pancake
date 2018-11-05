#include <fstream>

#include <catch2/catch.hpp>

#include "../src/include/directoryExists.hpp"
#include "../src/include/loadJSONFromStream.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/tweetStore.hpp"

TEST_CASE("Save select tweets to flat buffers","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    REQUIRE(PanCake::makeTweetTimePointPath("tweetStoreSave",tweets.at(0)) == "tweetStoreSave/2008/02/07/23/59/59");

    PanCake::TweetStore store ("tweetStoreSave");

    REQUIRE(!PanCake::directoryExists("tweetStoreSave/2008/02/07/23/59/59"));

    auto res = store.add(tweets.at(0));

    REQUIRE(PanCake::directoryExists("tweetStoreSave/2008/02/07/23/59/59"));

    REQUIRE(res.duplicate == false);
    REQUIRE(res.invalid == false);    
    REQUIRE(res.success == true);
    
}