#include <algorithm>

#include "serializeTweetBucket.hpp"

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
