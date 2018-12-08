#pragma once

#include <vector>
#include <string>

#include "tweetStore.hpp"

namespace PanCake
{
    struct BulkStoreStatus
    {
        int added = 0;
        int duplicates = 0;
        int metaUpdates = 0;
        bool success = false;
        std::vector<std::string> binsWithNewTweets;
    };

    [[nodiscard]] BulkStoreStatus bulkStoreTweets(const char*,std::vector<PanCake::Tweet>&);
}