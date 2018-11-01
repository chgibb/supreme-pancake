#pragma once

#include <string>
#include <string_view>

namespace PanCake
{
    struct TweetDate
    {
        std::string_view year;
        std::string_view month;
        std::string_view day;
        std::string_view hour;
        std::string_view minute;
        std::string_view second;
    };

    std::string tweetDateToTimePointPathString(PanCake::TweetDate&);
}