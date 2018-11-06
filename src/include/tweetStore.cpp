#include <algorithm>
#include <experimental/filesystem>

#include <picosha2.h>

#include "fileExists.hpp"
#include "directoryExists.hpp"
#include "tweetStore.hpp"

std::string PanCake::makeTweetTimePointPath(const char*path,::TweetT&tweet)
{
    return std::string(path) + "/" + tweet.date;
}

std::string PanCake::makeTweetTimePointFBBinPath(const char*path,::TweetT&tweet)
{
    return PanCake::makeTweetTimePointPath(path,tweet) + "/" + PanCake::getTweetUserHash(tweet)[0] + ".fb";
}

std::string PanCake::getTweetUserHash(::TweetT&tweet)
{
    return picosha2::hash256_hex_string(tweet.user.begin(),tweet.user.end());
}

std::vector<std::unique_ptr<::TweetT>>*PanCake::getBinBucketByHash(::TweetBinT&bin,::TweetT&tweet) noexcept
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
        return &bin.bucketA;
    else if(tweet.textHash[0] == 'b')
        return &bin.bucketB;
    else if(tweet.textHash[0] == 'c')
        return &bin.bucketC;
    else if(tweet.textHash[0] == 'd')
        return &bin.bucketD;
    else if(tweet.textHash[0] == 'e')
        return &bin.bucketE;
    else if(tweet.textHash[0] == 'f')
        return &bin.bucketF;
    return nullptr;
}

PanCake::TweetStore::TweetStore(const char*path)
{
    this->dataDirectory = path;
}

PanCake::TweetStore::~TweetStore()
{
    this->saveBins();
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

    if(!PanCake::fileExists(PanCake::makeTweetTimePointFBBinPath(this->dataDirectory,tweet).c_str()))
    {
        this->bins[PanCake::getTweetUserHash(tweet)[0]] = TweetBinT();
        PanCake::getBinBucketByHash(
            this->bins[PanCake::getTweetUserHash(tweet)[0]],tweet
        )->push_back(
            std::unique_ptr<::TweetT>(new TweetT(tweet))
        );
        res.success = true;
    }

    return res;
}

bool PanCake::TweetStore::saveBins()
{
    auto end = this->bins.end();
    for(auto it = this->bins.begin(); it != end; ++it)
    {
        ::TweetBinT*bin = &it->second;

        flatbuffers::FlatBufferBuilder fbb;
        ::TweetBinBuilder tbb(fbb);

        auto fbBin = tbb.Finish();

        ::CreateTweetBin(fbb,bin);
        
        fbb.Finish(fbBin);

        std::ofstream file(this->timePointPath+std::string("/")+it->first+".fb",std::ios::binary);
        if(file.bad())
            return false;
            
        file.write(reinterpret_cast<const char*>(fbb.GetBufferPointer()),fbb.GetSize());
    }
    return true;
}