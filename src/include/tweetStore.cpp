#include <algorithm>
#include <memory>
#include <iostream>
#include <experimental/filesystem>

#include <picosha2.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include "fileExists.hpp"
#include "directoryExists.hpp"
#include "tweetStore.hpp"
#include "tweet.hpp"

std::string PanCake::makeTweetTimePointPath(const char*path,PanCake::Tweet&tweet)
{
    return std::string(path) + "/" + tweet.date;
}

std::string PanCake::makeTweetTimePointFBBinPath(const char*path,PanCake::Tweet&tweet)
{
    return PanCake::makeTweetTimePointPath(path,tweet) + "/" + PanCake::getTweetUserHash(tweet)[0] + ".fb";
}

std::string PanCake::getTweetUserHash(PanCake::Tweet&tweet)
{
    return picosha2::hash256_hex_string(tweet.user.begin(),tweet.user.end());
}

std::vector<PanCake::Tweet>*PanCake::getBinBucketByHash(PanCake::TweetBin&bin,PanCake::Tweet&tweet) noexcept
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

void PanCake::serializeBucket(rapidjson::Value&value,rapidjson::Document::AllocatorType&allocator,std::vector<PanCake::Tweet>&bucket)
{
    std::for_each(bucket.begin(),bucket.end(),[&](const PanCake::Tweet&tweet){
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

PanCake::TweetStore::StoreStatus PanCake::TweetStore::add(PanCake::Tweet&tweet)
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

    //first time adding a tweet with this user hash
    if(!PanCake::fileExists(PanCake::makeTweetTimePointFBBinPath(this->dataDirectory,tweet).c_str()))
    {
        this->bins[PanCake::getTweetUserHash(tweet)[0]] = PanCake::TweetBin();
        PanCake::getBinBucketByHash(
            this->bins[PanCake::getTweetUserHash(tweet)[0]],tweet
        )->push_back(tweet);
        res.success = true;
    }

    else
    {
        
        
    }

    return res;
}

bool PanCake::TweetStore::saveBins()
{
    auto end = this->bins.end();
    for(auto it = this->bins.begin(); it != end; ++it)
    {
        rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        
        rapidjson::Value bucket0(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket0,allocator,it->second.bucket0);
        doc.AddMember("bucket0",bucket0,allocator);

        rapidjson::Value bucket1(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket1,allocator,it->second.bucket1);
        doc.AddMember("bucket1",bucket1,allocator);

        rapidjson::Value bucket2(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket2,allocator,it->second.bucket2);
        doc.AddMember("bucket2",bucket2,allocator);

        rapidjson::Value bucket3(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket3,allocator,it->second.bucket3);
        doc.AddMember("bucket3",bucket3,allocator);

        rapidjson::Value bucket4(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket4,allocator,it->second.bucket4);
        doc.AddMember("bucket4",bucket4,allocator);

        rapidjson::Value bucket5(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket5,allocator,it->second.bucket5);
        doc.AddMember("bucket5",bucket5,allocator);

        rapidjson::Value bucket6(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket6,allocator,it->second.bucket6);
        doc.AddMember("bucket6",bucket6,allocator);

        rapidjson::Value bucket7(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket7,allocator,it->second.bucket7);
        doc.AddMember("bucket7",bucket7,allocator);

        rapidjson::Value bucket8(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket8,allocator,it->second.bucket8);
        doc.AddMember("bucket8",bucket8,allocator);

        rapidjson::Value bucket9(rapidjson::kArrayType);
        PanCake::serializeBucket(bucket9,allocator,it->second.bucket9);
        doc.AddMember("bucket9",bucket9,allocator);

        rapidjson::Value bucketa(rapidjson::kArrayType);
        PanCake::serializeBucket(bucketa,allocator,it->second.bucketa);
        doc.AddMember("bucketa",bucketa,allocator);

        rapidjson::Value bucketb(rapidjson::kArrayType);
        PanCake::serializeBucket(bucketb,allocator,it->second.bucketb);
        doc.AddMember("bucketb",bucketb,allocator);

        rapidjson::Value bucketc(rapidjson::kArrayType);
        PanCake::serializeBucket(bucketc,allocator,it->second.bucketc);
        doc.AddMember("bucketc",bucketc,allocator);

        rapidjson::Value bucketd(rapidjson::kArrayType);
        PanCake::serializeBucket(bucketd,allocator,it->second.bucketd);
        doc.AddMember("bucketd",bucketd,allocator);

        rapidjson::Value buckete(rapidjson::kArrayType);
        PanCake::serializeBucket(buckete,allocator,it->second.buckete);
        doc.AddMember("buckete",buckete,allocator);

        rapidjson::Value bucketf(rapidjson::kArrayType);
        PanCake::serializeBucket(bucketf,allocator,it->second.bucketf);
        doc.AddMember("bucketf",bucketf,allocator);


        std::ofstream file(this->timePointPath+std::string("/")+it->first+".json");
        
        if(file.fail())
            return false;

        rapidjson::OStreamWrapper osw(file);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        return doc.Accept(writer);
    }
    return true;
}

bool PanCake::TweetStore::loadBin(char binHash)
{
    std::cout<<this->timePointPath+std::string("/")+binHash+std::string(".json")<<std::endl;
    std::ifstream file(this->timePointPath+std::string("/")+binHash+std::string(".json"));
    
    if(file.fail())
        return false;
/*
    file.seekg(0,std::ios::end);
    int length = file.tellg();
    file.seekg(0,std::ios::beg);
    std::unique_ptr<char> data(new char[length]);
    file.read(data.get(),length);
    file.close();

    this->bins[binHash] = ::UnPackTweetBin(data.get());

    //auto binPtr = ::GetTweetBin(data.get());

  //  this->bins[binHash] = std::make_unique<PanCake::TweetBin>(new TweetBinT());
   // this->bins[binHash] = std::move(binPtr);

    flatbuffers::FlatBufferBuilder fbb;
    ::TweetBinBuilder tbb(fbb);
    std::cout<<"made fbb and tbb"<<std::endl;

    auto fbBin = tbb.Finish();
    std::cout<<"finished tbb"<<std::endl;

    fbb.PushFlatBuffer((const uint8_t*)data.get(),length);
    std::cout<<"pushed buffer"<<std::endl;

    fbb.Finish(fbBin);
    std::cout<<"finshed fbb"<<std::endl;        
        
    auto bin = ::CreateTweetBinDirect(fbb);   
    std::cout<<"created bin"<<std::endl;*/
    return true;
}

void PanCake::TweetStore::printBins(std::ostream&stream)
{
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
            stream<<"        "<<it->textHash<<std::endl;
        }
    }
}