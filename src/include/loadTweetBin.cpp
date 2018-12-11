#include "loadTweetBin.hpp"
#include "deserializeTweetBucket.hpp"

[[nodiscard]] PanCake::TweetBin*PanCake::loadTweetBin(std::string path)
{
    std::ifstream file(path);
    
    if(file.fail())
        return nullptr;
    
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc = PanCake::loadJSONFromStream(file);
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    PanCake::TweetBin*bin = new PanCake::TweetBin();

    PanCake::deserializeTweetBucket(doc["bucket0"],allocator,bin->bucket0);
    PanCake::deserializeTweetBucket(doc["bucket1"],allocator,bin->bucket1);
    PanCake::deserializeTweetBucket(doc["bucket2"],allocator,bin->bucket2);
    PanCake::deserializeTweetBucket(doc["bucket3"],allocator,bin->bucket3);
    PanCake::deserializeTweetBucket(doc["bucket4"],allocator,bin->bucket4);
    PanCake::deserializeTweetBucket(doc["bucket5"],allocator,bin->bucket5);
    PanCake::deserializeTweetBucket(doc["bucket6"],allocator,bin->bucket6);
    PanCake::deserializeTweetBucket(doc["bucket7"],allocator,bin->bucket7);
    PanCake::deserializeTweetBucket(doc["bucket8"],allocator,bin->bucket8);
    PanCake::deserializeTweetBucket(doc["bucket9"],allocator,bin->bucket9);
    PanCake::deserializeTweetBucket(doc["bucketa"],allocator,bin->bucketa);
    PanCake::deserializeTweetBucket(doc["bucketb"],allocator,bin->bucketb);
    PanCake::deserializeTweetBucket(doc["bucketc"],allocator,bin->bucketc);
    PanCake::deserializeTweetBucket(doc["bucketd"],allocator,bin->bucketd);
    PanCake::deserializeTweetBucket(doc["buckete"],allocator,bin->buckete);
    PanCake::deserializeTweetBucket(doc["bucketf"],allocator,bin->bucketf);

    return bin;
}