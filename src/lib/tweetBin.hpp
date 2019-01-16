#pragma once

#include <vector>

#include "tweet.hpp"

namespace PanCake
{
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

    template<class F>
    void forEachBucket(TweetBin&bin,F f)
    {
        f(bin.bucket0);
        f(bin.bucket1);
        f(bin.bucket2);
        f(bin.bucket3);
        f(bin.bucket4);
        f(bin.bucket5);
        f(bin.bucket6);
        f(bin.bucket7);
        f(bin.bucket8);
        f(bin.bucket9);
        f(bin.bucketa);
        f(bin.bucketb);
        f(bin.bucketc);
        f(bin.bucketd);
        f(bin.buckete);
        f(bin.bucketf);
    }
}