#pragma once

#include <vector>
#include <string>

#include "interfaces/bulkStoreStatus.hpp"
#include "tweetStore.hpp"

namespace PanCake
{
    [[nodiscard]] BulkStoreStatus bulkStoreTweets(const char*,std::vector<PanCake::Tweet>&);
}
