#include "deserializeTweetBucket.hpp"

void PanCake::deserializeTweetBucket(rapidjson::Value&value,rapidjson::Document::AllocatorType&allocator,std::vector<PanCake::Tweet>&bucket)
{
    for(auto it = value.Begin(); it != value.End(); ++it)
    {
        PanCake::Tweet tweet;
        tweet.text = (*it)["text"].GetString();
        tweet.textHash = (*it)["textHash"].GetString();
        tweet.user = (*it)["user"].GetString();
        tweet.userHash = (*it)["userHash"].GetString();
        tweet.date = (*it)["date"].GetString();
        tweet.id = (*it)["id"].GetString();
        tweet.committed = (*it)["committed"].GetString();
        tweet.isRetweet = (*it)["isRetweet"].GetBool();
        tweet.isPinned = (*it)["isPinned"].GetBool();
        tweet.isReplyTo = (*it)["isReplyTo"].GetBool();
        tweet.replyCount = (*it)["replyCount"].GetInt();
        tweet.reTweetCount = (*it)["reTweetCount"].GetInt();
        tweet.favouriteCount = (*it)["favouriteCount"].GetInt();
        tweet.sentimentScore = (*it)["sentimentScore"].GetInt();
        tweet.comparativeSentimentScore = (*it)["comparativeSentimentScore"].GetFloat();

        for(auto imgIt = (*it)["images"].Begin(); imgIt != (*it)["images"].End(); ++imgIt)
        {
            tweet.images.push_back(PanCake::TweetImage(
                (*imgIt)["url"].GetString(),
                (*imgIt)["OCRText"].GetString()
            ));
        }

        bucket.push_back(tweet);
    }
}
