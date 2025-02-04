#pragma once

#include <vector>

#include <rapidjson/document.h>

#include "tweet.hpp"

namespace PanCake
{
    [[nodiscard]] std::vector<PanCake::Tweet> parseSearchScrapeTweetsFromJSON(rapidjson::GenericDocument<rapidjson::UTF8<>>&);
}
