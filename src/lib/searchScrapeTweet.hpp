#pragma once

#include <vector>

#include <rapidjson/document.h>

#include "interfaces/tweet.hpp"

namespace PanCake
{
    [[nodiscard]] std::vector<PanCake::Tweet> parseSearchScrapeTweetsFromJSON(rapidjson::GenericDocument<rapidjson::UTF8<>>&);
}

