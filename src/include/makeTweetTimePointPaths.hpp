#pragma once

#include <vector>
#include <string>

#include "tweet.hpp"

namespace PanCake
{
    [[nodiscard]] std::string makeTweetTimePointPath(const char*,PanCake::Tweet&);
    [[nodiscard]] std::string makeTweetTimePointBinPath(const char*,PanCake::Tweet&);
    [[nodiscard]] std::vector<std::string> makeTweetImagePaths(const char*,PanCake::Tweet&);
}
