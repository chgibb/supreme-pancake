#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "./../src/include/enumerateTimePoints.hpp"
#include "./../src/include/makeTweetTimePointPaths.hpp"
#include "./../src/include/tweetDate.hpp"

TEST_CASE("Time point strings should be correct","[paths]")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "01";
    date.day = "01";
    auto res = PanCake::enumerateTimePointPathStringForDay(date);

    //beginning 
    REQUIRE(res.at(0) != "");
    REQUIRE(res.at(0) == "2018/01/01/00/00/00");

    //end
    REQUIRE(res.at(res.size() - 1) != "");
    REQUIRE(res.at(res.size() - 1) == "2018/01/01/23/59/59");
    REQUIRE(res.at(86399) == "2018/01/01/23/59/59");

    REQUIRE(res.at(60) == "2018/01/01/00/01/00");
    REQUIRE(res.at(120) == "2018/01/01/00/02/00");
    REQUIRE(res.at(121) == "2018/01/01/00/02/01");
    REQUIRE(res.at(3599) == "2018/01/01/00/59/59");
    REQUIRE(res.at(3600) == "2018/01/01/01/00/00");
    REQUIRE(res.at(18000) == "2018/01/01/05/00/00");
    REQUIRE(res.at(17970) == "2018/01/01/04/59/30");

    std::vector<std::string> binPaths = PanCake::makeTweetBinPathsFromTimePointString("tweets","2018/01/01/23/59/59");

    REQUIRE(binPaths[0] == "tweets/2018/01/01/23/59/59/0.json");
    REQUIRE(binPaths[1] == "tweets/2018/01/01/23/59/59/1.json");
    REQUIRE(binPaths[2] == "tweets/2018/01/01/23/59/59/2.json");
    REQUIRE(binPaths[3] == "tweets/2018/01/01/23/59/59/3.json");
    REQUIRE(binPaths[4] == "tweets/2018/01/01/23/59/59/4.json");
    REQUIRE(binPaths[5] == "tweets/2018/01/01/23/59/59/5.json");
    REQUIRE(binPaths[6] == "tweets/2018/01/01/23/59/59/6.json");
    REQUIRE(binPaths[7] == "tweets/2018/01/01/23/59/59/7.json");
    REQUIRE(binPaths[8] == "tweets/2018/01/01/23/59/59/8.json");
    REQUIRE(binPaths[9] == "tweets/2018/01/01/23/59/59/9.json");
    REQUIRE(binPaths[10] == "tweets/2018/01/01/23/59/59/a.json");
    REQUIRE(binPaths[11] == "tweets/2018/01/01/23/59/59/b.json");
    REQUIRE(binPaths[12] == "tweets/2018/01/01/23/59/59/c.json");
    REQUIRE(binPaths[13] == "tweets/2018/01/01/23/59/59/d.json");
    REQUIRE(binPaths[14] == "tweets/2018/01/01/23/59/59/e.json");
    REQUIRE(binPaths[15] == "tweets/2018/01/01/23/59/59/f.json");
}
