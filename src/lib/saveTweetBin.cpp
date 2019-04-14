#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include "saveTweetBin.hpp"
#include "serializeTweetBucket.hpp"

[[nodiscard]] bool PanCake::saveTweetBin(const char*dataDir,PanCake::TweetBin&bin,std::string path)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        
    rapidjson::Value bucket0(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket0,allocator,bin.bucket0))
        return false;
    doc.AddMember("bucket0",bucket0,allocator);

    rapidjson::Value bucket1(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket1,allocator,bin.bucket1))
        return false;
    doc.AddMember("bucket1",bucket1,allocator);

    rapidjson::Value bucket2(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket2,allocator,bin.bucket2))
        return false;
    doc.AddMember("bucket2",bucket2,allocator);

    rapidjson::Value bucket3(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket3,allocator,bin.bucket3))
        return false;
    doc.AddMember("bucket3",bucket3,allocator);

    rapidjson::Value bucket4(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket4,allocator,bin.bucket4))
        return false;
    doc.AddMember("bucket4",bucket4,allocator);

    rapidjson::Value bucket5(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket5,allocator,bin.bucket5))
        return false;
    doc.AddMember("bucket5",bucket5,allocator);

    rapidjson::Value bucket6(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket6,allocator,bin.bucket6))
        return false;
    doc.AddMember("bucket6",bucket6,allocator);

    rapidjson::Value bucket7(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket7,allocator,bin.bucket7))
        return false;
    doc.AddMember("bucket7",bucket7,allocator);

    rapidjson::Value bucket8(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket8,allocator,bin.bucket8))
        return false;
    doc.AddMember("bucket8",bucket8,allocator);

    rapidjson::Value bucket9(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucket9,allocator,bin.bucket9))
        return false;
    doc.AddMember("bucket9",bucket9,allocator);

    rapidjson::Value bucketa(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucketa,allocator,bin.bucketa))
        return false;
    doc.AddMember("bucketa",bucketa,allocator);

    rapidjson::Value bucketb(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucketb,allocator,bin.bucketb))
        return false;
    doc.AddMember("bucketb",bucketb,allocator);

    rapidjson::Value bucketc(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucketc,allocator,bin.bucketc))
        return false;
    doc.AddMember("bucketc",bucketc,allocator);

    rapidjson::Value bucketd(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucketd,allocator,bin.bucketd))
        return false;
    doc.AddMember("bucketd",bucketd,allocator);

    rapidjson::Value buckete(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,buckete,allocator,bin.buckete))
        return false;
    doc.AddMember("buckete",buckete,allocator);

    rapidjson::Value bucketf(rapidjson::kArrayType);
    if(!PanCake::serializeTweetBucket(dataDir,bucketf,allocator,bin.bucketf))
        return false;
    doc.AddMember("bucketf",bucketf,allocator);


    std::ofstream file(path.c_str());
        
    if(file.fail())
        return false;

    rapidjson::OStreamWrapper osw(file);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    
    return doc.Accept(writer);
}
