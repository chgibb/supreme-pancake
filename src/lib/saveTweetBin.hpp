#pragma once

#include <string>

#include "tweetBin.hpp"

namespace PanCake
{
    [[nodiscard]] bool saveTweetBin(PanCake::TweetBin&,std::string);
}
