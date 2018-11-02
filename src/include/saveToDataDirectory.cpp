#include <algorithm>
#include <experimental/filesystem>

#include "fileExists.hpp"
#include "makePath.hpp"
#include "saveToDataDirectory.hpp"

bool PanCake::saveTweetToDataDirectory(const char*path,::TweetT&tweet)
{
    bool exists = PanCake::fileExists(path);

    if(!exists)
    {
        PanCake::makePath((char*)path,S_IRWXU);
    }

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
    return std::string(path) + "/" + tweet.date + "/" + tweet.textHash[0] + ".fb";
}