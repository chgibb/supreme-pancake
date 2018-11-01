#pragma once

#include <string_view>
#include <optional>

#include <ctre.hpp>

#include "tweetDate.hpp"

namespace PanCake
{
    constexpr std::optional<std::string_view> dayToNumber(std::string_view str) noexcept
    {
        if(str == "Sun")
            return "01";
        else if(str == "Mon")
            return "02";
        else if(str == "Tue")
            return "03";
        else if(str == "Wed")
            return "04";
        else if(str == "Thu")
            return "05";
        else if(str == "Fri")
            return "06";
        else if(str == "Sat")
            return "07";
        return std::nullopt;
    }

    constexpr std::optional<std::string_view> monthToNumber(std::string_view str) noexcept
    {
        if(str == "Jan")
            return "01";
        else if(str == "Feb")
            return "02";
        else if(str == "Mar")
            return "03";
        else if(str == "Apr")
            return "04";
        else if(str == "May")
            return "05";
        else if(str == "Jun")
            return "06";
        else if(str == "Jul")
            return "07";
        else if(str == "Aug")
            return "08";
        else if(str == "Sep")
            return "09";
        else if(str == "Oct")
            return "10";
        else if(str == "Nov")
            return "11";
        else if(str == "Dec")
            return "12";
        return std::nullopt;
    }
    
    constexpr std::optional<PanCake::TweetDate> parseSearchScrapeDate(std::string_view str) noexcept
    {
        using namespace ctre::literals;
        if(auto [
            whole,
            year,
            month,
            day,
            hour,
            minute,
            second
            ] = "([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})"_ctre.match(str); whole){
            return PanCake::TweetDate{
                year.to_view(),
                month.to_view(),
                day.to_view(),
                hour.to_view(),
                minute.to_view(),
                second.to_view()
            };
        }
        return std::nullopt;
    }

    constexpr std::optional<PanCake::TweetDate> parseAPIGetSearchDate(std::string_view str) noexcept
    {
        using namespace ctre::literals;
        if(auto [
            whole,
            dayOfWeek,
            month,
            day,
            hour,
            minute,
            second,
            utcOffset,
            year

        ] = "([A-z]{3}) ([A-z]{3}) ([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}) (\\+[0-9]{4}) ([0-9]{4})"_ctre.match(str); whole){
            return PanCake::TweetDate{
                year.to_view(),
                *PanCake::monthToNumber(month.to_view()),
                day.to_view(),
                hour.to_view(),
                minute.to_view(),
                second.to_view()
            };
        }
        return std::nullopt;
    }
}
