#include <algorithm>

#include "makeTweetTimePointPaths.hpp"

[[nodiscard]] std::string PanCake::makeTweetTimePointPath(const char*path,PanCake::Tweet&tweet)
{
    return std::string(path) + "/" + tweet.date;
}

[[nodiscard]] std::string PanCake::makeTweetTimePointBinPath(const char*path,PanCake::Tweet&tweet)
{
    return PanCake::makeTweetTimePointPath(path,tweet) + "/" + tweet.userHash[0] + ".json";
}

[[nodiscard]] std::string PanCake::makeTweetImagePath(const char*path,PanCake::Tweet&tweet)
{
    return PanCake::makeTweetTimePointPath(path,tweet)+"/img";
}

[[nodiscard]] std::string PanCake::makeTweetImageFilePath(const char*path,PanCake::Tweet&tweet,int index)
{
    return PanCake::makeTweetImagePath(path,tweet)+"/"+tweet.id+"_"+std::to_string(index)+".jpg";
}

[[nodiscard]] std::vector<std::string> PanCake::makeTweetImageFilePaths(const char*path,PanCake::Tweet&tweet)
{
    std::vector<std::string> res;

    int i = 0;
    std::for_each(
        tweet.images.begin(),
        tweet.images.end(),
        [&tweet,&path,&res,&i](const std::string&url) -> void {
            res.push_back(PanCake::makeTweetImageFilePath(path,tweet,i));
            i++;
        }
    );

    return res;
}
