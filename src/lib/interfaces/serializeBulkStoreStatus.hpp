#pragma once

#include <string>

#include "bulkStoreStatus.hpp"

namespace PanCake
{
    [[nodiscard]] std::string serializeBulkStoreStatus(PanCake::BulkStoreStatus&);
}

