#pragma once

#include <string>

#include "loadJSON.hpp"
#include "tweetBin.hpp"

namespace PanCake
{
    [[nodiscard]] PanCake::TweetBin*loadTweetBin(std::string);
}
