#pragma once

#include <vector>
#include <string>

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
        const char*,PanCake::TweetBin&,void(*)(std::vector<PanCake::Tweet>&,const std::string&)
    );
    
}
