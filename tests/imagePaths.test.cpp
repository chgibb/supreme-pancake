#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "./../src/lib/makeTweetTimePointPaths.hpp"

TEST_CASE("Time point image strings should be correct","")
{
    PanCake::Tweet tweet;
    tweet.id = "1234567";
    tweet.date = "2018/01/01/00/00/00";
    tweet.images.push_back("123");
    tweet.images.push_back("1234");

    REQUIRE(PanCake::makeTweetImagePath("tests/rt/imgPaths",tweet) == "tests/rt/imgPaths/2018/01/01/00/00/00/img");

    REQUIRE(PanCake::makeTweetImageFilePath("tests/rt/imgPaths",tweet,0) == "tests/rt/imgPaths/2018/01/01/00/00/00/img/1234567_0.jpg");

    std::vector<std::string> filePaths = PanCake::makeTweetImageFilePaths("tests/rt/imgPaths",tweet);

    REQUIRE(filePaths[0] == "tests/rt/imgPaths/2018/01/01/00/00/00/img/1234567_0.jpg");
    REQUIRE(filePaths[1] == "tests/rt/imgPaths/2018/01/01/00/00/00/img/1234567_1.jpg");
}
