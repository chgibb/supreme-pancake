#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/include/loadJSON.hpp"
#include "../src/include/searchScrapeTweet.hpp"
#include "../src/include/bulkTweetStore.hpp"
#include "../src/include/downloadImagesFromBin.hpp"
#include "../src/include/OCRImage.hpp"
#include "../src/include/tweetBin.hpp"
#include "../src/include/loadTweetBin.hpp"
#include "../src/include/saveTweetBin.hpp"

std::string expectedOCRText = "Your account has been limited until we hear from you\n"
"service@intl.paypal.com Tue, May 1, 2012, 1:48 PM\n"
"Dear Rui Gomes,\n"
"We need your help resolving an issue with your account. To give us time to\n"
"work together on this, we've temporarily limited what you can do with your\n"
"account until the issue is resolved.\n"
"We understand it may be frustrating not to have full access to your PayPal\n"
"account. We want to work with you to get your account back to normal as\n"
"quickly as possible.\n\n";

TEST_CASE("should OCR and update images","")
{
    std::ifstream tweetStream("tests/res/bulkStore.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());

    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/OCRImage1",tweets);

    REQUIRE(status.success == true);

    PanCake::TweetBin*bin = PanCake::loadTweetBin("tests/rt/OCRImage1/2018/11/08/22/34/22/e.json");

    PanCake::BulkImageDownloadStatus dlstatus = PanCake::downloadImagesFromBin("tests/rt/OCRImage1",*bin,&PanCake::OCRImage);

    REQUIRE(dlstatus.attempted == 1);
    REQUIRE(dlstatus.succeeded == 1);
    REQUIRE(dlstatus.failed == 0);

    REQUIRE(bin->bucketd.at(0).images.at(0).url == "https://pbs.twimg.com/media/Drg2f0uWsAIDCGo.jpg");

    REQUIRE(bin->bucketd.at(0).images.at(0).OCRText == expectedOCRText);

    REQUIRE(PanCake::saveTweetBin(*bin,"tests/rt/OCRImage1/2018/11/08/22/34/22/e.json") == true);
}

TEST_CASE("Should be able to read back OCRed text","")
{
    PanCake::TweetBin*bin = PanCake::loadTweetBin("tests/rt/OCRImage1/2018/11/08/22/34/22/e.json");

    REQUIRE(bin->bucketd.at(0).images.at(0).url == "https://pbs.twimg.com/media/Drg2f0uWsAIDCGo.jpg");

    REQUIRE(bin->bucketd.at(0).images.at(0).OCRText == expectedOCRText);
}
