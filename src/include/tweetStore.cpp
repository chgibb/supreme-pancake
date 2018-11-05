#include <algorithm>
#include <experimental/filesystem>

#include "fileExists.hpp"
#include "directoryExists.hpp"
#include "tweetStore.hpp"

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

PanCake::TweetStore::TweetStore(const char*path)
{
    this->dataDirectory = path;
}

PanCake::TweetStore::StoreStatus PanCake::TweetStore::add(::TweetT&tweet)
{
    PanCake::TweetStore::StoreStatus res;

    if(this->timePointPath == "")
    {
        this->timePointPath = PanCake::makeTweetTimePointFBBinPath(this->dataDirectory,tweet);
    }

    if(this->timePointPath != PanCake::makeTweetTimePointFBBinPath(this->dataDirectory,tweet))
    {
        res.invalid = true;
        return res;
    }

    return res;
}