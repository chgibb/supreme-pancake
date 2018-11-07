#pragma once

#include <map>
#include <vector>
#include <string>

#include <rapidjson/document.h>

#include "tweet.hpp"

namespace PanCake
{
    std::string makeTweetTimePointPath(const char*,PanCake::Tweet&);
    std::string makeTweetTimePointFBBinPath(const char*,PanCake::Tweet&);
    std::string getTweetUserHash(PanCake::Tweet&);
    std::vector<PanCake::Tweet>*getBinBucketByHash(PanCake::TweetBin&,PanCake::Tweet&) noexcept;
    void serializeBucket(rapidjson::Value&,rapidjson::Document::AllocatorType&,std::vector<PanCake::Tweet>&);
    void deserializeBucket(rapidjson::Value&,rapidjson::Document::AllocatorType&,std::vector<PanCake::Tweet>&);

    class TweetStore
    {
        public:
            std::map<char,PanCake::TweetBin> bins;

            TweetStore(const char*);
            TweetStore(const char*,const char*);
            ~TweetStore() = default;

            struct StoreStatus
            {
                bool invalid = false;
                bool duplicate = false;
                bool success = false;
            };

            StoreStatus add(PanCake::Tweet&);
            bool saveBins();
            bool loadBin(const char);
            void printBins(std::ostream&);
            void printBucket(std::ostream&,std::vector<PanCake::Tweet>&);
        private:
            const char*dataDirectory;
            std::string timePointPath;
            bool addTweetIfNotDup(std::vector<PanCake::Tweet>&,PanCake::Tweet&);
    };
}
