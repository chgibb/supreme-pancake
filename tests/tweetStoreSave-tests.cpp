#include <fstream>
#include <iostream>

#define CATCH_CONFIG_FAST_COMPILE
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

    REQUIRE(PanCake::makeTweetTimePointPath("tests/rt/tweetStoreSave",tweets.at(0)) == "tests/rt/tweetStoreSave/2018/11/09/21/19/28");

    PanCake::TweetStore store("tests/rt/tweetStoreSave");

    REQUIRE(!PanCake::directoryExists("tests/rt/tweetStoreSave/2018/11/09/21/19/28"));

    auto res = store.add(tweets.at(0));

    REQUIRE(PanCake::directoryExists("tests/rt/tweetStoreSave/2018/11/09/21/19/28"));
    REQUIRE(res.duplicate == false);
    REQUIRE(res.invalid == false);    
    REQUIRE(res.success == true);
    REQUIRE(res.updatedMeta == false);

    res = store.add(tweets.at(1));
    REQUIRE(res.duplicate == false);
    REQUIRE(res.invalid == false);    
    REQUIRE(res.success == true);
    REQUIRE(res.updatedMeta == false);

    REQUIRE(store.bins['1'].bucketa.at(0).date == "2018/11/09/21/19/28");
    REQUIRE(store.bins['1'].bucketa.at(0).user == "scotty8692");
    REQUIRE(store.bins['1'].bucketa.at(0).text == "Same as Linfield fans at the Showgrounds when they weren't doing so well last season-poorest Blues crowd I've saw in my 15 years of going to games at the Showgrounds. The fairweather fans will always turn up and subsequently not turn up, for all teams.");
    REQUIRE(store.bins['1'].bucketa.at(0).textHash == "a229b09b6ef6791968ac3e2fa2636a74c925e3e44b5077b95cee56ef66d014af");
    REQUIRE(store.bins['1'].bucketa.at(0).id == "1061005372813647873");
    REQUIRE(store.bins['1'].bucketa.at(0).isRetweet == false);
    REQUIRE(store.bins['1'].bucketa.at(0).isPinned == false);
    REQUIRE(store.bins['1'].bucketa.at(0).isReplyTo == true);
    REQUIRE(store.bins['1'].bucketa.at(0).replyCount == 0);
    REQUIRE(store.bins['1'].bucketa.at(0).reTweetCount == 0);
    REQUIRE(store.bins['1'].bucketa.at(0).favouriteCount == 0);
    REQUIRE(store.bins['1'].bucketa.at(0).sentimentScore == 0);
    REQUIRE(store.bins['1'].bucketa.at(0).comparativeSentimentScore == 0);

    REQUIRE(store.saveBins() == true);
    {
        PanCake::TweetStore store2("tests/rt/tweetStoreSave","2018/11/09/21/19/28");
        REQUIRE(store2.loadBin('1') == true);
        REQUIRE(store2.loadBin('d') == true);

        REQUIRE(store2.bins['1'].bucketa.at(0).date == "2018/11/09/21/19/28");
        REQUIRE(store2.bins['1'].bucketa.at(0).user == "scotty8692");
        REQUIRE(store2.bins['1'].bucketa.at(0).text == "Same as Linfield fans at the Showgrounds when they weren't doing so well last season-poorest Blues crowd I've saw in my 15 years of going to games at the Showgrounds. The fairweather fans will always turn up and subsequently not turn up, for all teams.");
        REQUIRE(store2.bins['1'].bucketa.at(0).textHash == "a229b09b6ef6791968ac3e2fa2636a74c925e3e44b5077b95cee56ef66d014af");
        REQUIRE(store2.bins['1'].bucketa.at(0).id == "1061005372813647873");
        REQUIRE(store2.bins['1'].bucketa.at(0).isRetweet == false);
        REQUIRE(store2.bins['1'].bucketa.at(0).isPinned == false);
        REQUIRE(store2.bins['1'].bucketa.at(0).isReplyTo == true);
        REQUIRE(store2.bins['1'].bucketa.at(0).replyCount == 0);
        REQUIRE(store2.bins['1'].bucketa.at(0).reTweetCount == 0);
        REQUIRE(store2.bins['1'].bucketa.at(0).favouriteCount == 0);
        REQUIRE(store2.bins['1'].bucketa.at(0).sentimentScore == 0);
        REQUIRE(store2.bins['1'].bucketa.at(0).comparativeSentimentScore == 0);

        REQUIRE(store2.bins['d'].bucket7.at(0).sentimentScore == -6);
        REQUIRE(store2.bins['d'].bucket7.at(0).comparativeSentimentScore == -0.15789473056793214);
    }

    res = store.add(tweets.at(0));

    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == true);
    REQUIRE(res.updatedMeta == false);

    //make synthetic unique tweet
    PanCake::Tweet uniqTweet = store.bins['1'].bucketa.at(0);
    uniqTweet.textHash = "3b";

    res = store.add(uniqTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == true);
    REQUIRE(res.duplicate == false);
    REQUIRE(res.updatedMeta == false);

    PanCake::Tweet updatedTweet = store.bins['1'].bucketa.at(0);
    updatedTweet.isPinned = true;
    res = store.add(updatedTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == false);
    REQUIRE(res.updatedMeta == true);

    updatedTweet.replyCount++;
    res = store.add(updatedTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == false);
    REQUIRE(res.updatedMeta == true);

    updatedTweet.reTweetCount++;
    res = store.add(updatedTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == false);
    REQUIRE(res.updatedMeta == true);

    updatedTweet.favouriteCount++;
    res = store.add(updatedTweet);
    REQUIRE(res.invalid == false);
    REQUIRE(res.success == false);
    REQUIRE(res.duplicate == false);
    REQUIRE(res.updatedMeta == true);

    REQUIRE(store.saveBins() == true);
}