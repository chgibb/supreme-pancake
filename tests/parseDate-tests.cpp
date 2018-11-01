#include <catch2/catch.hpp>

#include "../src/include/dateParser.hpp"

TEST_CASE("Parse search scrape date", "[date]")
{
    auto firstDate = "2008-02-07T23:59:59";
    std::optional<PanCake::TweetDate> date = PanCake::parseSearchScrapeDate(firstDate);
    REQUIRE(date.has_value());
    REQUIRE(date->year == "2008");
    REQUIRE(date->month == "02");
    REQUIRE(date->day == "07");
    REQUIRE(date->hour == "23");
    REQUIRE(date->minute == "59");
    REQUIRE(date->second == "59");

    REQUIRE(PanCake::tweetDateToTimePointPathString(*date) == "2008/02/07/23/59/59");
}

TEST_CASE("Parse API search/get date components","[date]")
{
    auto day = PanCake::dayToNumber("Sun");
    REQUIRE(day.has_value());
    REQUIRE(*day == "01");

    auto month = PanCake::monthToNumber("Oct");
    REQUIRE(month.has_value());
    REQUIRE(*month == "10");
}

TEST_CASE("Parse API search/get date","[date]")
{
    auto firstDate = "Sun Feb 25 18:11:01 +0000 2018";
    std::optional<PanCake::TweetDate> date = PanCake::parseAPIGetSearchDate(firstDate);
    REQUIRE(date.has_value());
    REQUIRE(date->year == "2018");
    REQUIRE(date->month == "02");
    REQUIRE(date->day == "25");
    REQUIRE(date->hour == "18");
    REQUIRE(date->minute == "11");
    REQUIRE(date->second == "01");

    REQUIRE(PanCake::tweetDateToTimePointPathString(*date) == "2018/02/25/18/11/01");
}