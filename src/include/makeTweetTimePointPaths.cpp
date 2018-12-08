#include "makeTweetTimePointPaths.hpp"

[[nodiscard]] std::string PanCake::makeTweetTimePointPath(const char*path,PanCake::Tweet&tweet)
{
    return std::string(path) + "/" + tweet.date;
}

[[nodiscard]] std::string PanCake::makeTweetTimePointBinPath(const char*path,PanCake::Tweet&tweet)
{
    return PanCake::makeTweetTimePointPath(path,tweet) + "/" + tweet.userHash[0] + ".json";
}