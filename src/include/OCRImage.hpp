#pragma once

#include <vector>
#include <string>

#include "tweet.hpp"
#include "tweetBin.hpp"

namespace PanCake
{
    void OCRImage(std::vector<PanCake::Tweet>&,const PanCake::Tweet&,const int,const std::string&);
}
