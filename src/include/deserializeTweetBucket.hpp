#pragma once

#include <vector>

#include <rapidjson/document.h>

#include "tweet.hpp"

namespace PanCake
{
    void deserializeTweetBucket(rapidjson::Value&,rapidjson::Document::AllocatorType&,std::vector<PanCake::Tweet>&);
}
