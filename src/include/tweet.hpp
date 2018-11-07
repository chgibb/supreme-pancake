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
            std::string date;
            std::string id;
            std::string committed;
    };

    class TweetBin
    {
        public:
            std::vector<Tweet> bucket0;
            std::vector<Tweet> bucket1;
            std::vector<Tweet> bucket2;
            std::vector<Tweet> bucket3;
            std::vector<Tweet> bucket4;
            std::vector<Tweet> bucket5;
            std::vector<Tweet> bucket6;
            std::vector<Tweet> bucket7;
            std::vector<Tweet> bucket8;
            std::vector<Tweet> bucket9;
            std::vector<Tweet> bucketa;
            std::vector<Tweet> bucketb;
            std::vector<Tweet> bucketc;
            std::vector<Tweet> bucketd;
            std::vector<Tweet> buckete;
            std::vector<Tweet> bucketf;
    };
}