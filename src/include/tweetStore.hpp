#pragma once

#include <map>
#include <vector>
#include <string>

#include <rapidjson/document.h>

#include "tweet.hpp"

namespace PanCake
{
    [[nodiscard]] std::string makeTweetTimePointPath(const char*,PanCake::Tweet&);
    [[nodiscard]] std::string makeTweetTimePointBinPath(const char*,PanCake::Tweet&);
    [[nodiscard]] std::vector<PanCake::Tweet>*getBinBucketByHash(PanCake::TweetBin&,PanCake::Tweet&) noexcept;
    void serializeTweetBucket(rapidjson::Value&,rapidjson::Document::AllocatorType&,std::vector<PanCake::Tweet>&);
    void deserializeTweetBucket(rapidjson::Value&,rapidjson::Document::AllocatorType&,std::vector<PanCake::Tweet>&);

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
                bool updatedMeta = false;
            };

            struct AddOrUpdateStatus
            {
                bool updatedMeta = false;
                bool added = false;
            };

            StoreStatus add(PanCake::Tweet&);
            [[nodiscard]] bool saveBins();
            [[nodiscard]] bool loadBin(const char);
            void printBins(std::ostream&);
            void printBucket(std::ostream&,std::vector<PanCake::Tweet>&);
        private:
            const char*dataDirectory;
            std::string timePointPath;
            [[nodiscard]] PanCake::TweetStore::AddOrUpdateStatus addOrUpdateTweet(std::vector<PanCake::Tweet>&,PanCake::Tweet&);
    };
}
