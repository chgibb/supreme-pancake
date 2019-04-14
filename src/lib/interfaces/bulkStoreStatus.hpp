#pragma once

#include <vector>
#include <string>

namespace PanCake
{
    struct BulkStoreStatus
    {
        int added = 0;
        int duplicates = 0;
        int metaUpdates = 0;
        int savedImages = 0;
        bool success = false;
        std::vector<std::string> binsWithNewTweets;
    };
}
