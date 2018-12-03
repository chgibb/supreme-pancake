#pragma once

#include <string>
#include <vector>

namespace PanCake
{
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
    };
}