#pragma once

#include <fstream>
#include <string>

#include "../tweetDate.hpp"

namespace PanCake
{
    std::ofstream makeColumnIROutPutPath(std::string,PanCake::TweetDate&,std::string);
}
