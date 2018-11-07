#include <fstream>
#include <iostream>

#include <catch2/catch.hpp>

#include "../src/include/directoryExists.hpp"
#include "../src/include/loadJSONFromStream.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/tweetStore.hpp"

TEST_CASE("Save select tweets to JSON","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    REQUIRE(PanCake::makeTweetTimePointPath("tests/rt/tweetStoreSave",tweets.at(0)) == "tests/rt/tweetStoreSave/2008/02/07/23/59/59");

    PanCake::TweetStore store("tests/rt/tweetStoreSave");

    REQUIRE(!PanCake::directoryExists("tests/rt/tweetStoreSave/2008/02/07/23/59/59"));

    auto res = store.add(tweets.at(0));

    REQUIRE(PanCake::directoryExists("tests/rt/tweetStoreSave/2008/02/07/23/59/59"));
    REQUIRE(res.duplicate == false);
    REQUIRE(res.invalid == false);    
    REQUIRE(res.success == true);

    REQUIRE(store.bins['5'].bucket3.at(0).date == "2008/02/07/23/59/59");
    REQUIRE(store.bins['5'].bucket3.at(0).user == "newestdiscovery");
    REQUIRE(store.bins['5'].bucket3.at(0).text == "www.newestdiscovery.com update: The Future of XML (How will you use XML in years to come? The wheels of progress turn slowly, but tu...)");
    REQUIRE(store.bins['5'].bucket3.at(0).textHash == "3b2858570a2acde5c14efd3c2158393a601e8c918c232fc3ed3a818add569123");
    REQUIRE(store.bins['5'].bucket3.at(0).id == "688736272");

    REQUIRE(store.saveBins() == true);
    {
        PanCake::TweetStore store2("tests/rt/tweetStoreSave","2008/02/07/23/59/59");

        REQUIRE(store2.loadBin('5') == true);
        REQUIRE(store2.bins['5'].bucket3.at(0).date == "2008/02/07/23/59/59");
        REQUIRE(store2.bins['5'].bucket3.at(0).user == "newestdiscovery");
        REQUIRE(store2.bins['5'].bucket3.at(0).text == "www.newestdiscovery.com update: The Future of XML (How will you use XML in years to come? The wheels of progress turn slowly, but tu...)");
        REQUIRE(store2.bins['5'].bucket3.at(0).textHash == "3b2858570a2acde5c14efd3c2158393a601e8c918c232fc3ed3a818add569123");
        REQUIRE(store2.bins['5'].bucket3.at(0).id == "688736272");
    }

    res = store.add(tweets.at(0));

    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == true);

    //make synthetic unique tweet
    PanCake::Tweet uniqTweet = store.bins['5'].bucket3.at(0);
    uniqTweet.textHash = "3b";

    res = store.add(uniqTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == true);
    REQUIRE(res.duplicate == false);

    REQUIRE(store.saveBins() == true);
}