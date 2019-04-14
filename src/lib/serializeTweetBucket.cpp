#include <algorithm>
#include <fstream>
#include <experimental/filesystem>

#include "base64.hpp"
#include "OCR.hpp"
#include "OCRResult.hpp"
#include "serializeOCRResult.hpp"
#include "serializeTweetBucket.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "directoryExists.hpp"
#include "fileExists.hpp"

[[nodiscard]] bool PanCake::serializeTweetBucket(
    const char*dataDir,
    rapidjson::Value&value,
    rapidjson::Document::AllocatorType&allocator,
    std::vector<PanCake::Tweet>&bucket
) {
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
            [&images,&allocator](const std::string&img) -> void {
                images.PushBack(rapidjson::StringRef(img.c_str()),allocator);
        });

        entry.AddMember(
            rapidjson::StringRef("images"),
            images,
            allocator
        );

        value.PushBack(entry,allocator);

        int i = 0;
        std::for_each(tweet.imageContent.begin(),tweet.imageContent.end(),[&](const PanCake::TweetImageContent&image) -> void {
            std::string dirPath = PanCake::makeTweetImagePath(dataDir,tweet);
            
            if(!PanCake::directoryExists(dirPath.c_str()))
                std::experimental::filesystem::create_directories(dirPath);

            std::string path = PanCake::makeTweetImageFilePath(dataDir,tweet,i);

            if(!PanCake::fileExists(path.c_str()))
            {
                std::ofstream file(path.c_str(),std::ios::out | std::ios::binary);

                std::string data = base64_decode(image.data);

                std::for_each(data.begin(),data.end(),[&](const char&byte) -> void {
                    file<<byte;
                });
            }

            ++i;
        });
    });

    return true;
}

