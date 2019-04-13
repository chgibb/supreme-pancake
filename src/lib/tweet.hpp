#pragma once

#include <string>
#include <vector>

namespace PanCake
{
    class TweetImageContent
    {
        public:
            std::string url;
            std::string data;
            TweetImageContent(std::string _url,std::string _data) : url(_url),data(_data) {}
            ~TweetImageContent() = default;
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
            std::vector<std::string> images;
            std::vector<PanCake::TweetImageContent> imageContent;
    };
}
