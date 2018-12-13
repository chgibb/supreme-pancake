#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include "saveTweetBin.hpp"
#include "serializeTweetBucket.hpp"

[[nodiscard]] bool PanCake::saveTweetBin(PanCake::TweetBin&bin,std::string path)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        
    rapidjson::Value bucket0(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket0,allocator,bin.bucket0);
    doc.AddMember("bucket0",bucket0,allocator);

    rapidjson::Value bucket1(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket1,allocator,bin.bucket1);
    doc.AddMember("bucket1",bucket1,allocator);

    rapidjson::Value bucket2(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket2,allocator,bin.bucket2);
    doc.AddMember("bucket2",bucket2,allocator);

    rapidjson::Value bucket3(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket3,allocator,bin.bucket3);
    doc.AddMember("bucket3",bucket3,allocator);

    rapidjson::Value bucket4(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket4,allocator,bin.bucket4);
    doc.AddMember("bucket4",bucket4,allocator);

    rapidjson::Value bucket5(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket5,allocator,bin.bucket5);
    doc.AddMember("bucket5",bucket5,allocator);

    rapidjson::Value bucket6(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket6,allocator,bin.bucket6);
    doc.AddMember("bucket6",bucket6,allocator);

    rapidjson::Value bucket7(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket7,allocator,bin.bucket7);
    doc.AddMember("bucket7",bucket7,allocator);

    rapidjson::Value bucket8(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket8,allocator,bin.bucket8);
    doc.AddMember("bucket8",bucket8,allocator);

    rapidjson::Value bucket9(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucket9,allocator,bin.bucket9);
    doc.AddMember("bucket9",bucket9,allocator);

    rapidjson::Value bucketa(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucketa,allocator,bin.bucketa);
    doc.AddMember("bucketa",bucketa,allocator);

    rapidjson::Value bucketb(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucketb,allocator,bin.bucketb);
    doc.AddMember("bucketb",bucketb,allocator);

    rapidjson::Value bucketc(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucketc,allocator,bin.bucketc);
    doc.AddMember("bucketc",bucketc,allocator);

    rapidjson::Value bucketd(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucketd,allocator,bin.bucketd);
    doc.AddMember("bucketd",bucketd,allocator);

    rapidjson::Value buckete(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(buckete,allocator,bin.buckete);
    doc.AddMember("buckete",buckete,allocator);

    rapidjson::Value bucketf(rapidjson::kArrayType);
    PanCake::serializeTweetBucket(bucketf,allocator,bin.bucketf);
    doc.AddMember("bucketf",bucketf,allocator);


    std::ofstream file(path.c_str());
        
    if(file.fail())
        return false;

    rapidjson::OStreamWrapper osw(file);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    
    return doc.Accept(writer);
}
