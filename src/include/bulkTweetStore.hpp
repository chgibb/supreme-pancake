#pragma once

#include <vector>

#include "tweetStore.hpp"

namespace PanCake
{
    struct BulkStoreStatus
    {
        int added = 0;
        int duplicates = 0;
        bool success = false;
    };

    BulkStoreStatus bulkStoreTweets(const char*,std::vector<PanCake::Tweet>&);
}