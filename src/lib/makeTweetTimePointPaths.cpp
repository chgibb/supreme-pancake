#include <algorithm>

#include "makeTweetTimePointPaths.hpp"
#include "tweetDate.hpp"

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
        [&tweet,&path,&res,&i](const std::string&img) -> void {
            res.push_back(PanCake::makeTweetImageFilePath(path,tweet,i));
            i++;
        }
    );

    return res;
}

[[nodiscard]] std::vector<std::string> PanCake::makeTweetBinPathsFromTimePointString(const char*dataDir,const char*timePointStr)
{
    std::vector<std::string> res;

    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/0.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/1.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/2.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/3.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/4.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/5.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/6.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/7.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/8.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/9.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/a.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/b.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/c.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/d.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/e.json");
    res.push_back(std::string(dataDir) + "/" + std::string(timePointStr) + "/f.json");

    return res;
}