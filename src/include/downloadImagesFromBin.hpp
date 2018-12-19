#pragma once

#include <vector>
#include <string>

#include "tweetBin.hpp"
#include "bulkImageDownloadStatus.hpp"

namespace PanCake
{
    [[nodiscard]] PanCake::BulkImageDownloadStatus downloadImagesFromBin(const char*,PanCake::TweetBin&);
}
