#include <algorithm>
#include <experimental/filesystem>

#include <picosha2.h>

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

std::string PanCake::makeTweetTimePointPath(const char*path,::TweetT&tweet)
{
    return std::string(path) + "/" + tweet.date;
}

std::string PanCake::makeTweetTimePointFBBinPath(const char*path,::TweetT&tweet)
{
    return PanCake::makeTweetTimePointPath(path,tweet) + "/" + picosha2::hash256_hex_string(tweet.user.begin(),tweet.user.end())[0] + ".fb";
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
        this->timePointPath = PanCake::makeTweetTimePointPath(this->dataDirectory,tweet);
    }

    if(this->timePointPath != PanCake::makeTweetTimePointPath(this->dataDirectory,tweet))
    {
        res.invalid = true;
        return res;
    }

    if(!PanCake::directoryExists(this->timePointPath.c_str()))
    {
        std::experimental::filesystem::create_directories(this->timePointPath);
    }

    return res;
}