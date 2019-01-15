#pragma once

#include <fstream>
#include <string>

#include "../tweetDate.hpp"

namespace PanCake
{
    [[nodiscard]] std::ofstream makeColumnIROutPutStream(std::string,PanCake::TweetDate&,std::string);
    [[nodiscard]] std::string makeColumnIROutputPath(std::string,PanCake::TweetDate&,std::string);
    [[nodiscard]] std::ofstream makeColumnIRChunkCountStream(std::string,PanCake::TweetDate&);
    [[nodiscard]] std::string makeColumnIRChunkCountPath(std::string,PanCake::TweetDate&);
    [[nodiscard]] std::ofstream makeColumnIRTotalCountStream(std::string,PanCake::TweetDate&);
    [[nodiscard]] std::string makeColumnIRTotalCountPath(std::string,PanCake::TweetDate&);
}
