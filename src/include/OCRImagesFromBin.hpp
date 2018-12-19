#pragma once

#include <vector>
#include <string>

#include "tweetBin.hpp"
#include "bulkOCRStatus.hpp"

namespace PanCake
{
    [[nodiscard]] PanCake::BulkOCRStatus OCRImagesFromBin(const char*,PanCake::TweetBin&bin);
}
