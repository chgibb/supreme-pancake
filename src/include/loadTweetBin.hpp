#pragma once

#include <fstream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "loadJSON.hpp"
#include "tweetBin.hpp"

namespace PanCake
{
    [[nodiscard]] PanCake::TweetBin*loadTweetBin(std::string);
}
