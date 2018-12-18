#pragma once

#include <vector>
#include <string>

#include <tesseract/baseapi.h>

#include "tweet.hpp"
#include "tweetBin.hpp"
#include "bulkImageDownloadStatus.hpp"

namespace PanCake
{
    [[nodiscard]] PanCake::BulkImageDownloadStatus downloadImagesFromBin(
        const char*,
        PanCake::TweetBin&,
        void(*const&)(
            std::vector<PanCake::Tweet>&,
            const PanCake::Tweet&,
            const int,
            const std::string&
        ) = nullptr
    );    
}
