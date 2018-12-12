#pragma once

#include <string>
#include <vector>

namespace PanCake
{
    class TweetImage
    {
        public:
            std::string url;
            std::string OCRText;
            TweetImage(std::string _url,std::string _OCRText) : url(_url),OCRText(_OCRText) {}
            ~TweetImage() = default;
    };

    class Tweet
    {
        public:
            std::string text;
            std::string textHash;
            std::string user;
            std::string userHash;
            std::string date;
            std::string id;
            std::string committed;
            bool isRetweet;
            bool isPinned;
            bool isReplyTo;
            int replyCount;
            int reTweetCount;
            int favouriteCount;
            int sentimentScore;
            float comparativeSentimentScore;
            std::vector<PanCake::TweetImage> images;
    };
}
