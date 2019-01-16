#include <fstream>
#include <algorithm>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/lib/loadJSON.hpp"
#include "../src/lib/searchScrapeTweet.hpp"
#include "../src/lib/bulkTweetStore.hpp"
#include "../src/lib/downloadImagesFromBin.hpp"
#include "../src/lib/tweetBin.hpp"
#include "../src/lib/loadTweetBin.hpp"


TEST_CASE("Should not download anything from bins with no image urls","")
{
    std::ifstream tweetStream("tests/res/searchScrapeTweets.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/downloadImages1",tweets);
    REQUIRE(status.success == true);
    REQUIRE(status.binsWithNewTweets.size() == 9);

    PanCake::BulkImageDownloadStatus dlStatus;

    std::for_each(
        status.binsWithNewTweets.begin(),
        status.binsWithNewTweets.end(),
        [&dlStatus](const std::string&binFilePath) -> void {
            PanCake::TweetBin*bin = PanCake::loadTweetBin(binFilePath);

            PanCake::BulkImageDownloadStatus bindlStatus = PanCake::downloadImagesFromBin("tests/rt/downloadImages1",*bin);
            
            REQUIRE(bindlStatus.succeeded == 0);
            REQUIRE(bindlStatus.failed == 0);
            REQUIRE(bindlStatus.attempted == 0);

            dlStatus.succeeded += bindlStatus.succeeded;
            dlStatus.failed += bindlStatus.failed;
            dlStatus.attempted += bindlStatus.attempted;

            delete bin;
        }
    );

    REQUIRE(dlStatus.succeeded == 0);
    REQUIRE(dlStatus.failed == 0);   
    REQUIRE(dlStatus.attempted == 0);
}

TEST_CASE("Should not download deleted images or try to retry deleted images","")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/downloadImages2",tweets);
    REQUIRE(status.success == true);
    REQUIRE(status.binsWithNewTweets.size() == 996);

    PanCake::TweetBin*bin = PanCake::loadTweetBin("tests/rt/downloadImages2/2018/11/09/14/56/02/c.json");

    PanCake::BulkImageDownloadStatus dlStatus = PanCake::downloadImagesFromBin("tests/rt/downloadImages2",*bin);

    REQUIRE(dlStatus.succeeded == 0);
    REQUIRE(dlStatus.failed == 1);
    REQUIRE(dlStatus.attempted == 1);

    dlStatus = PanCake::downloadImagesFromBin("tests/rt/downloadImages2",*bin);

    REQUIRE(dlStatus.succeeded == 0);
    REQUIRE(dlStatus.failed == 0);
    REQUIRE(dlStatus.attempted == 0);

    delete bin;
}