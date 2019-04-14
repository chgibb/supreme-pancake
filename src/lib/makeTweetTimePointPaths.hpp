#pragma once

#include <vector>
#include <string>

#include "tweet.hpp"

namespace PanCake
{
    [[nodiscard]] std::string makeTweetTimePointPath(const char*,const PanCake::Tweet&);
    [[nodiscard]] std::string makeTweetTimePointBinPath(const char*,const PanCake::Tweet&);
    [[nodiscard]] std::string makeTweetImagePath(const char*,const PanCake::Tweet&);
    [[nodiscard]] std::string makeTweetImageFilePath(const char*,const PanCake::Tweet&,int);
    [[nodiscard]] std::vector<std::string> makeTweetImageFilePaths(const char*,const PanCake::Tweet&);
    [[nodiscard]] std::vector<std::string> makeTweetImageFilePathsForImageContent(const char*,const PanCake::Tweet&);
    [[nodiscard]] std::vector<std::string> makeTweetBinPathsFromTimePointString(const char*,const char*);
}
