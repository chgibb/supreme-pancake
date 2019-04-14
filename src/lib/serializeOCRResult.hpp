#pragma once

#include <string>

#include "OCRResult.hpp"

namespace PanCake
{
    [[nodiscard]] std::string serializeOCRResult(PanCake::OCRResult&);
}

