#include <algorithm>
#include <memory>
#include <iostream>
#include <experimental/filesystem>

#include <picosha2.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include "tweetStore.hpp"
#include "fileExists.hpp"
#include "directoryExists.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "loadJSON.hpp"
#include "loadTweetBin.hpp"
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

void PanCake::serializeTweetBucket(rapidjson::Value&value,rapidjson::Document::AllocatorType&allocator,std::vector<PanCake::Tweet>&bucket)
{
    std::for_each(bucket.begin(),bucket.end(),[&](const PanCake::Tweet&tweet) -> void {
        rapidjson::Value entry;

        entry.SetObject();

        entry.AddMember(
            rapidjson::StringRef("text"),
            rapidjson::StringRef(tweet.text.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("textHash"),
            rapidjson::StringRef(tweet.textHash.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("user"),
            rapidjson::StringRef(tweet.user.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("userHash"),
            rapidjson::StringRef(tweet.userHash.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("date"),
            rapidjson::StringRef(tweet.date.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("id"),
            rapidjson::StringRef(tweet.id.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("committed"),
            rapidjson::StringRef(tweet.committed.c_str()),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("isRetweet"),
            rapidjson::Value(tweet.isRetweet),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("isPinned"),
            rapidjson::Value(tweet.isPinned),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("isReplyTo"),
            rapidjson::Value(tweet.isReplyTo),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("replyCount"),
            rapidjson::Value(tweet.replyCount),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("reTweetCount"),
            rapidjson::Value(tweet.reTweetCount),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("favouriteCount"),
            rapidjson::Value(tweet.favouriteCount),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("sentimentScore"),
            rapidjson::Value(tweet.sentimentScore),
            allocator
        );

        entry.AddMember(
            rapidjson::StringRef("comparativeSentimentScore"),
            rapidjson::Value(tweet.comparativeSentimentScore),
            allocator
        );

        rapidjson::Value images(rapidjson::kArrayType);
        
        std::for_each(
            tweet.images.begin(),
            tweet.images.end(),
            [&images,&allocator](const PanCake::TweetImage&img) -> void {
                rapidjson::Value image;
                image.SetObject();

                image.AddMember(
                    rapidjson::StringRef("url"),
                    rapidjson::StringRef(img.url.c_str()),
                    allocator
                );

                image.AddMember(
                    rapidjson::StringRef("OCRText"),
                    rapidjson::StringRef(img.OCRText.c_str()),
                    allocator
                );

                images.PushBack(image,allocator);
        });

        entry.AddMember(
            rapidjson::StringRef("images"),
            images,
            allocator
        );

        value.PushBack(entry,allocator);
    });
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
        rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        
        rapidjson::Value bucket0(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket0,allocator,it->second.bucket0);
        doc.AddMember("bucket0",bucket0,allocator);

        rapidjson::Value bucket1(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket1,allocator,it->second.bucket1);
        doc.AddMember("bucket1",bucket1,allocator);

        rapidjson::Value bucket2(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket2,allocator,it->second.bucket2);
        doc.AddMember("bucket2",bucket2,allocator);

        rapidjson::Value bucket3(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket3,allocator,it->second.bucket3);
        doc.AddMember("bucket3",bucket3,allocator);

        rapidjson::Value bucket4(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket4,allocator,it->second.bucket4);
        doc.AddMember("bucket4",bucket4,allocator);

        rapidjson::Value bucket5(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket5,allocator,it->second.bucket5);
        doc.AddMember("bucket5",bucket5,allocator);

        rapidjson::Value bucket6(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket6,allocator,it->second.bucket6);
        doc.AddMember("bucket6",bucket6,allocator);

        rapidjson::Value bucket7(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket7,allocator,it->second.bucket7);
        doc.AddMember("bucket7",bucket7,allocator);

        rapidjson::Value bucket8(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket8,allocator,it->second.bucket8);
        doc.AddMember("bucket8",bucket8,allocator);

        rapidjson::Value bucket9(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucket9,allocator,it->second.bucket9);
        doc.AddMember("bucket9",bucket9,allocator);

        rapidjson::Value bucketa(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucketa,allocator,it->second.bucketa);
        doc.AddMember("bucketa",bucketa,allocator);

        rapidjson::Value bucketb(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucketb,allocator,it->second.bucketb);
        doc.AddMember("bucketb",bucketb,allocator);

        rapidjson::Value bucketc(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucketc,allocator,it->second.bucketc);
        doc.AddMember("bucketc",bucketc,allocator);

        rapidjson::Value bucketd(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucketd,allocator,it->second.bucketd);
        doc.AddMember("bucketd",bucketd,allocator);

        rapidjson::Value buckete(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(buckete,allocator,it->second.buckete);
        doc.AddMember("buckete",buckete,allocator);

        rapidjson::Value bucketf(rapidjson::kArrayType);
        PanCake::serializeTweetBucket(bucketf,allocator,it->second.bucketf);
        doc.AddMember("bucketf",bucketf,allocator);


        std::ofstream file(this->timePointPath+std::string("/")+it->first+".json");
        
        if(file.fail())
            return false;

        rapidjson::OStreamWrapper osw(file);
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
        if(!doc.Accept(writer))
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
