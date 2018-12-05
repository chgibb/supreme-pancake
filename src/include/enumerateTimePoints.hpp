#pragma once

#include <vector>
#include <string>

#include "tweetDate.hpp"

namespace PanCake
{
    [[nodiscard]] std::vector<std::string> enumerateTimePointPathString(PanCake::TweetDate);
    namespace Internal
    {
        class Hour
        {
            public:
                Hour() = default;
                Hour(int newHour) : numHour(newHour){}
                void increment();
                [[nodiscard]] bool hasOverFlowed();
                [[nodiscard]] std::string get();
            private:
                int numHour = 0;
                bool overFlowed = false;
        };

        class Minute
        {
            public:
                Minute() = default;
                Minute(int newMinute) : numMinute(newMinute){}
                void increment();
                [[nodiscard]] bool hasOverFlowed();
                [[nodiscard]] std::string get();
            private:
                int numMinute = 0;
                bool overFlowed = false;
        };
    }
}
