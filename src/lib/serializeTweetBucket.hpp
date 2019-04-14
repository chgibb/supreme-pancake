#pragma once

#include <vector>
#include <string>

#include <rapidjson/document.h>

#include "interfaces/tweet.hpp"

namespace PanCake
{
    [[nodiscard]] bool serializeTweetBucket(
        const char*dataDir,
        rapidjson::Value&,
        rapidjson::Document::AllocatorType&,
        std::vector<PanCake::Tweet>&
    );
}

