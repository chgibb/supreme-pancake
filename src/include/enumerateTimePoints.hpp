#pragma once

#include <vector>
#include <string>

#include "tweetDate.hpp"

namespace PanCake
{
    std::vector<std::string> enumerateTimePointPathString(PanCake::TweetDate);
    namespace EnumerateTimePoints
    {
        class Hour
        {
            public:
                Hour() = default;
                Hour(int newHour) : numHour(newHour){}
                void increment();
                bool hasOverFlowed();
                std::string get();
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
                bool hasOverFlowed();
                std::string get();
            private:
                int numMinute = 0;
                bool overFlowed = false;
        };
    }
}
