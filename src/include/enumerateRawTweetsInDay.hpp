#pragma once
#include <functional>

#include "tweetDate.hpp"
#include "tweet.hpp"

namespace PanCake
{
    void enumerateRawTweetsInDay(const char*,PanCake::TweetDate&,std::function<void(const PanCake::Tweet&)>);
}
