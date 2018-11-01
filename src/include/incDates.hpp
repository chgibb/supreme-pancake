#pragma once

#include <vector>
#include <chrono>

#include <date/date.h>
#include <date/tz.h>

#include "tweetDate.hpp"

namespace PanCake
{
    std::vector<PanCake::TweetDate> incrementDays(PanCake::TweetDate&,int);
}