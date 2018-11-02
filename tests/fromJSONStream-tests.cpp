#include <fstream>

#include <catch2/catch.hpp>

#include "../src/include/loadJSONFromStream.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/saveToDataDirectory.hpp"

TEST_CASE("Load JSON from stream","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());
}

TEST_CASE("Parse search scrape tweets from JSON","[JSON")
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
}

TEST_CASE("Save select tweets to flat buffers","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    REQUIRE(PanCake::makeTweetTimePointFBBinPath("data",tweets.at(0)) == "data/2008/02/07/23/59/59/3.fb");

    bool saved = PanCake::saveTweetToDataDirectory("data",tweets.at(0));
}