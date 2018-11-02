#pragma once

#include <vector>
#include <string>

#include "../vendor/tweetBin_generated.h"

namespace PanCake
{
    bool saveTweetsToDataDirectory(const char*,std::vector<::TweetT>&);
    bool saveTweetToDataDirectory(const char*,::TweetT&);
    std::string makeTweetTimePointFBBinPath(const char*,::TweetT&);
}
