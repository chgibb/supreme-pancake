#pragma once

#include <vector>

#include <rapidjson/document.h>

#include "interfaces/tweet.hpp"

namespace PanCake
{
    void deserializeTweetBucket(rapidjson::Value&,rapidjson::Document::AllocatorType&,std::vector<PanCake::Tweet>&);
}
