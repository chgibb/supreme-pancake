#include <algorithm>
#include <experimental/filesystem>

#include "fileExists.hpp"
#include "directoryExists.hpp"
#include "saveToDataDirectory.hpp"

bool PanCake::saveTweetToDataDirectory(const char*path,::TweetT&tweet)
{
    bool exists = PanCake::fileExists(path);

    

    return exists;
}

bool PanCake::saveTweetsToDataDirectory(const char*path,std::vector<::TweetT>&tweets)
{
    std::sort(tweets.begin(),tweets.end(),[](const::TweetT&lhs,const::TweetT&rhs) -> bool {
        return lhs.date < rhs.date;
    });

    return true;
}

std::string PanCake::makeTweetTimePointFBBinPath(const char*path,::TweetT&tweet)
{
    return std::string(path) + "/" + tweet.date;
}