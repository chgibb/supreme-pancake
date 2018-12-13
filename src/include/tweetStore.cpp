#include <algorithm>
#include <memory>
#include <iostream>
#include <experimental/filesystem>

#include <picosha2.h>

#include "tweetStore.hpp"
#include "fileExists.hpp"
#include "directoryExists.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "loadJSON.hpp"
#include "loadTweetBin.hpp"
#include "saveTweetBin.hpp"
#include "tweet.hpp"

[[nodiscard]] std::vector<PanCake::Tweet>*PanCake::getBinBucketByHash(PanCake::TweetBin&bin,PanCake::Tweet&tweet) noexcept
{
    if(tweet.textHash[0] == '0')
        return &bin.bucket0;
    else if(tweet.textHash[0] == '1')
        return &bin.bucket1;
    else if(tweet.textHash[0] == '2')
        return &bin.bucket2;
    else if(tweet.textHash[0] == '3')
        return &bin.bucket3;
    else if(tweet.textHash[0] == '4')
        return &bin.bucket4;
    else if(tweet.textHash[0] == '5')
        return &bin.bucket5;
    else if(tweet.textHash[0] == '6')
        return &bin.bucket6;
    else if(tweet.textHash[0] == '7')
        return &bin.bucket7;
    else if(tweet.textHash[0] == '8')
        return &bin.bucket8;
    else if(tweet.textHash[0] == '9')
        return &bin.bucket9;
    else if(tweet.textHash[0] == 'a')
        return &bin.bucketa;
    else if(tweet.textHash[0] == 'b')
        return &bin.bucketb;
    else if(tweet.textHash[0] == 'c')
        return &bin.bucketc;
    else if(tweet.textHash[0] == 'd')
        return &bin.bucketd;
    else if(tweet.textHash[0] == 'e')
        return &bin.buckete;
    else if(tweet.textHash[0] == 'f')
        return &bin.bucketf;
    return nullptr;
}

PanCake::TweetStore::TweetStore(const char*path)
{
    this->dataDirectory = path;
}

PanCake::TweetStore::TweetStore(const char*path,const char*timePointPath)
{
    this->dataDirectory = path;
    this->timePointPath = this->dataDirectory+std::string("/")+timePointPath;
}

[[nodiscard]] PanCake::TweetStore::StoreStatus PanCake::TweetStore::add(PanCake::Tweet&tweet)
{
    PanCake::TweetStore::StoreStatus res;
    char userHashFirstChar = tweet.userHash[0];

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

    bool isBinLoaded = false;

    //bin is already loaded
    if(this->bins.count(userHashFirstChar) != 0)
    {
        PanCake::TweetBin*bin = &this->bins[userHashFirstChar];
        std::vector<PanCake::Tweet>*bucket = getBinBucketByHash(*bin,tweet);

        PanCake::TweetStore::AddOrUpdateStatus addStatus = this->addOrUpdateTweet(*bucket,tweet);
        
        if(addStatus.added)
        {
            res.success = true;
            return res;
        }
        else if(!addStatus.added && !addStatus.updatedMeta)
        {
            res.duplicate = true;
            return res;
        }
        else if(!addStatus.added && addStatus.updatedMeta)
        {
            res.updatedMeta = true;
            return res;
        }
    }

    //bin is not loaded but exists on disk
    else if(PanCake::fileExists(PanCake::makeTweetTimePointBinPath(this->dataDirectory,tweet).c_str()))
    {
        bool loaded = this->loadBin(userHashFirstChar);
        if(!loaded)
        {
            res.invalid = true;
            return res;
        }

        PanCake::TweetBin*bin = &this->bins[userHashFirstChar];
        std::vector<PanCake::Tweet>*bucket = getBinBucketByHash(*bin,tweet);

        PanCake::TweetStore::AddOrUpdateStatus addStatus = this->addOrUpdateTweet(*bucket,tweet);
        
        if(addStatus.added)
        {
            res.success = true;
            return res;
        }
        else if(!addStatus.added && !addStatus.updatedMeta)
        {
            res.duplicate = true;
            return res;
        }
        else if(!addStatus.added && addStatus.updatedMeta)
        {
            res.updatedMeta = true;
            return res;
        }
    }

    //first time adding a tweet with this user hash
    //Bin does not exist in memory or on disk
    else if(!PanCake::fileExists(PanCake::makeTweetTimePointBinPath(this->dataDirectory,tweet).c_str()))
    {
        this->bins[userHashFirstChar] = PanCake::TweetBin();

        PanCake::getBinBucketByHash(
            this->bins[userHashFirstChar],tweet
        )->push_back(tweet);

        std::string bucketPath = PanCake::makeTweetTimePointBinPath(this->dataDirectory,tweet);
        this->binsWithNewTweets[bucketPath] = true;

        res.success = true;
    }

    return res;
}

[[nodiscard]] bool PanCake::TweetStore::saveBins()
{
    auto end = this->bins.end();
    for(auto it = this->bins.begin(); it != end; ++it)
    {   
        bool res = PanCake::saveTweetBin(it->second,this->timePointPath+std::string("/")+it->first+".json");
        if(!res)
            return false;
    }
    return true;
}

[[nodiscard]] bool PanCake::TweetStore::loadBin(char binHash)
{
    PanCake::TweetBin*bin = PanCake::loadTweetBin(this->timePointPath+std::string("/")+binHash+std::string(".json"));

    if(bin != nullptr)
    {
        this->bins[binHash] = *bin;
        delete bin;
        return true;
    }

    delete bin;
    return false;
}

void PanCake::TweetStore::printBins(std::ostream&stream)
{
    stream<<this->timePointPath<<std::endl;
    auto end = this->bins.end();
    for(auto it = this->bins.begin(); it != end; ++it)
    {
        stream<<it->first<<std::endl;
        stream<<"   bucket 0"<<std::endl;
        this->printBucket(stream,it->second.bucket0);
        stream<<"   bucket 1"<<std::endl;
        this->printBucket(stream,it->second.bucket1);
        stream<<"   bucket 2"<<std::endl;
        this->printBucket(stream,it->second.bucket2);
        stream<<"   bucket 3"<<std::endl;
        this->printBucket(stream,it->second.bucket3);
        stream<<"   bucket 4"<<std::endl;
        this->printBucket(stream,it->second.bucket4);
        stream<<"   bucket 5"<<std::endl;
        this->printBucket(stream,it->second.bucket5);
        stream<<"   bucket 6"<<std::endl;
        this->printBucket(stream,it->second.bucket6);
        stream<<"   bucket 7"<<std::endl;
        this->printBucket(stream,it->second.bucket7);
        stream<<"   bucket 8"<<std::endl;
        this->printBucket(stream,it->second.bucket8);
        stream<<"   bucket 9"<<std::endl;
        this->printBucket(stream,it->second.bucket9);
        stream<<"   bucket a"<<std::endl;
        this->printBucket(stream,it->second.bucketa);
        stream<<"   bucket b"<<std::endl;
        this->printBucket(stream,it->second.bucketb);
        stream<<"   bucket c"<<std::endl;
        this->printBucket(stream,it->second.bucketc);
        stream<<"   bucket d"<<std::endl;
        this->printBucket(stream,it->second.bucketd);
        stream<<"   bucket e"<<std::endl;
        this->printBucket(stream,it->second.buckete);
        stream<<"   bucket f"<<std::endl;
        this->printBucket(stream,it->second.bucketf);
    }
}

void PanCake::TweetStore::printBucket(std::ostream&stream,std::vector<PanCake::Tweet>&bucket)
{
    if(bucket.size() != 0)
    {
        auto end = bucket.end();
        for(auto it = bucket.begin(); it != end; ++it)
        {
            stream<<"        Tweet Hash: "<<it->textHash<<std::endl;
        }
    }
}

[[nodiscard]] PanCake::TweetStore::AddOrUpdateStatus PanCake::TweetStore::addOrUpdateTweet(std::vector<PanCake::Tweet>&bucket,PanCake::Tweet&tweet)
{
    PanCake::TweetStore::AddOrUpdateStatus res;
    auto end = bucket.end();
    for(auto it = bucket.begin(); it != end; ++it)
    {
        if(
            it->textHash == tweet.textHash &&
            it->userHash == tweet.userHash
        ) {
            if(
                it->isPinned != tweet.isPinned ||
                it->replyCount != tweet.replyCount ||
                it->reTweetCount != tweet.reTweetCount ||
                it->favouriteCount != tweet.favouriteCount 
            ) {
                *it = tweet;
                res.updatedMeta = true;
                return res;
            }
            
            else
            {
                res.added = false;
                return res;
            }
        }
    }
    bucket.push_back(tweet);
    
    std::string bucketPath = PanCake::makeTweetTimePointBinPath(this->dataDirectory,tweet);
    //if(!this->binsWithNewTweets.count(bucketPath))
    //{
        this->binsWithNewTweets[bucketPath] = true;
    //}
    /*int numImages = 1;
    std::for_each(
        tweet.images.begin(),
        tweet.images.end(),
        [this,&tweet,&numImages](const std::string&url) -> void {
            if(!PanCake::directoryExists(std::string(this->timePointPath+std::string("/img")).c_str()))
            {
                std::experimental::filesystem::create_directories(this->timePointPath+std::string("/img"));
            }

            std::string filePath = this->timePointPath+std::string("/img/")+std::string(tweet.id)+std::string("_")+std::to_string(numImages)+std::string(".jpg");
            PanCake::downloadImage(url,filePath);
        });*/

    res.added = true;
    return res;
}
