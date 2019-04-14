#pragma once

#include <string>

#include "bulkOCRResult.hpp"

namespace PanCake
{
    [[nodiscard]] std::string serializeBulkOCRResult(PanCake::BulkOCRResult&);
}

