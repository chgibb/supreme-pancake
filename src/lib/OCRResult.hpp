#pragma once

#include <string>

namespace PanCake
{
    struct OCRResult
    {
        std::string text;
        std::string lang;
        float comparativeSentimentScore = 0;
        int sentimentScore = 0;
    };
}

