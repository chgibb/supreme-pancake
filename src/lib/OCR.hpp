#pragma once

#include <string>

#include "OCRResult.hpp"

namespace PanCake
{
    namespace Internal
    {
        std::string OCR(const std::string&);
    }

    PanCake::OCRResult OCRImage(const std::string&);
}

