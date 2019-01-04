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
            std::string text = "";
            std::string textHash = "";
            std::string user = "";
            std::string userHash = "";
            std::string date = "";
            std::string id = "";
            std::string committed = "";
            bool isRetweet = false;
            bool isPinned = false;
            bool isReplyTo = false;
            int replyCount = 0;
            int reTweetCount = 0;
            int favouriteCount = 0;
            int sentimentScore = 0;
            float comparativeSentimentScore = 0;
            std::vector<PanCake::TweetImage> images;
    };
}
