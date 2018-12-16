#include <fstream>

#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "./../src/include/enumerateTimePoints.hpp"
#include "./../src/include/tweetDate.hpp"

TEST_CASE("Time point strings should be correct","[paths]")
{
    PanCake::TweetDate date;
    date.year = "2018";
    date.month = "01";
    date.day = "01";
    auto res = PanCake::enumerateTimePointPathString(date);

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
}
