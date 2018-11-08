#include <fstream>
#include <iostream>

#include <catch2/catch.hpp>

#include "../src/include/directoryExists.hpp"
#include "../src/include/loadJSON.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/tweetStore.hpp"

TEST_CASE("Save select tweets to JSON","[JSON]")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    REQUIRE(PanCake::makeTweetTimePointPath("tests/rt/tweetStoreSave",tweets.at(0)) == "tests/rt/tweetStoreSave/2010/01/02/23/59/59");

    PanCake::TweetStore store("tests/rt/tweetStoreSave");

    REQUIRE(!PanCake::directoryExists("tests/rt/tweetStoreSave/2010/01/02/23/59/59"));

    auto res = store.add(tweets.at(0));

    REQUIRE(PanCake::directoryExists("tests/rt/tweetStoreSave/2010/01/02/23/59/59"));
    REQUIRE(res.duplicate == false);
    REQUIRE(res.invalid == false);    
    REQUIRE(res.success == true);

    REQUIRE(store.bins['b'].bucket7.at(0).date == "2010/01/02/23/59/59");
    REQUIRE(store.bins['b'].bucket7.at(0).user == "wAii2KoOl");
    REQUIRE(store.bins['b'].bucket7.at(0).text == "RT @mia_b_mia: Boys gettin fresh cuts AND new units?? HOL IT NA! its on! Won't be in THA house toniiiiight #RogerDat <\u00ac LOL #BleaDat");
    REQUIRE(store.bins['b'].bucket7.at(0).textHash == "75ff3feca8988c63ac04a06d6b9c857a2756dc05c923b9840b3ced591dc80a46");
    REQUIRE(store.bins['b'].bucket7.at(0).id == "7314112637");

    REQUIRE(store.saveBins() == true);
    {
        PanCake::TweetStore store2("tests/rt/tweetStoreSave","2010/01/02/23/59/59");

        REQUIRE(store2.loadBin('b') == true);
        REQUIRE(store2.bins['b'].bucket7.at(0).date == "2010/01/02/23/59/59");
        REQUIRE(store2.bins['b'].bucket7.at(0).user == "wAii2KoOl");
        REQUIRE(store2.bins['b'].bucket7.at(0).text == "RT @mia_b_mia: Boys gettin fresh cuts AND new units?? HOL IT NA! its on! Won't be in THA house toniiiiight #RogerDat <\u00ac LOL #BleaDat");
        REQUIRE(store2.bins['b'].bucket7.at(0).textHash == "75ff3feca8988c63ac04a06d6b9c857a2756dc05c923b9840b3ced591dc80a46");
        REQUIRE(store2.bins['b'].bucket7.at(0).id == "7314112637");
    }

    res = store.add(tweets.at(0));

    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == true);

    //make synthetic unique tweet
    PanCake::Tweet uniqTweet = store.bins['b'].bucket7.at(0);
    uniqTweet.textHash = "3b";

    res = store.add(uniqTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == true);
    REQUIRE(res.duplicate == false);

    REQUIRE(store.saveBins() == true);
}