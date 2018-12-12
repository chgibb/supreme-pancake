#pragma once

#include <vector>
#include <string>

#include <tesseract/baseapi.h>

#include "tweet.hpp"
#include "tweetBin.hpp"

namespace PanCake
{
    struct BulkImageDownloadStatus
    {
        int succeeded = 0;
        int failed = 0;
        int attempted = 0;
    };

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
