#include <fstream>

#include <catch2/catch.hpp>

#include "../src/include/loadJSONFromStream.hpp"
#include "../src/include/searchScrapeTweet.hpp"

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
    REQUIRE(res.at(0).id == "688736272");
}