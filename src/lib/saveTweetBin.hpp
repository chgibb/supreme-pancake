#pragma once

#include <string>

#include "tweetBin.hpp"

namespace PanCake
{
    [[nodiscard]] bool saveTweetBin(const char*,PanCake::TweetBin&,std::string);
}
