#include <iostream>
#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "../src/lib/loadJSON.hpp"
#include "../src/lib/searchScrapeTweet.hpp"
#include "../src/lib/bulkTweetStore.hpp"
#include "../src/lib/OCR.hpp"

TEST_CASE("Parses and saves inline images","")
{
    std::ifstream tweetStream("tests/res/62ImagesInline.json");
    auto json = PanCake::loadJSONFromStream(tweetStream);
    REQUIRE(!json.HasParseError());
    
    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);

    PanCake::BulkStoreStatus status = PanCake::bulkStoreTweets("tests/rt/OCR",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 300);
    REQUIRE(status.duplicates == 0);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.savedImages == 62);
    REQUIRE(status.binsWithNewTweets.size() == 48);

    status = PanCake::bulkStoreTweets("tests/rt/OCR",tweets);

    REQUIRE(status.success == true);
    REQUIRE(status.added == 0);
    REQUIRE(status.duplicates == 300);
    REQUIRE(status.metaUpdates == 0);
    REQUIRE(status.savedImages == 0);
    REQUIRE(status.binsWithNewTweets.size() == 0);
}
  
TEST_CASE("Should OCR image","")
{
    std::string expectedOCRText = "Done\n"
  "What This World Needs\n"
  "Casting, C own: 7 TM: a ia 613 “a Ex:\n"
  "What this world needs is for us to stop hiding\n"
  "behind our relevance\n"
  "Blending in so well that people can't see the\n"
  "difference\n"
  "And it's the difference that sets the world free\n"
  "(spoken)\n"
  "People aren't confused by the Gospel.\n"
  "They're confused by us.\n"
  "Jesus is the only way to God, but we are not the\n"
  "only way to Jesus,\n"
  "This world doesn't need my tie, my hoodie, my\n"
  "denomination or my interpretation of the Bible.\n"
  "They just need Jesus.\n"
  "We can be passionate about what we believe,\n"
  "but we can't strap ourselves to the Gospel,\n"
  "because we are slowing it down.\n"
  "Jesus is going to save the world, but maybe the\n"
  "best thing we can do is just get out of the way.\n"
  "Jesus is our Savior, that's what this world needs\n"
  "Father's arms around you, that's what this world\n"
  "needs\n"
  "That’s what this world needs\n"
  "\n";
  
    REQUIRE(PanCake::Internal::OCR("tests/rt/OCR/2019/04/14/16/00/56/img/1117457721723375616_0.jpg") == expectedOCRText);
}   

