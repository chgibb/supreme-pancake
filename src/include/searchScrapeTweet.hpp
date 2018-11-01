#pragma once

#include <vector>

#include <rapidjson/document.h>

#include "../vendor/tweetBin_generated.h"

namespace PanCake
{
    std::vector<::TweetT> parseSearchScrapeTweetsFromJSON(rapidjson::GenericDocument<rapidjson::UTF8<>>&);
}
