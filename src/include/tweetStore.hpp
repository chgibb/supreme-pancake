#pragma once

#include <map>
#include <vector>
#include <string>

#include "../vendor/tweetBin_generated.h"

namespace PanCake
{
    std::string makeTweetTimePointPath(const char*,::TweetT&);
    std::string makeTweetTimePointFBBinPath(const char*,::TweetT&);
    std::string getTweetUserHash(::TweetT&);
    std::vector<std::unique_ptr<::TweetT>>*getBinBucketByHash(::TweetBinT&,::TweetT&) noexcept;

    class TweetStore
    {
        public:
            std::map<char,::TweetBinT> bins;

            TweetStore(const char*);
            ~TweetStore();

            struct StoreStatus
            {
                bool invalid = false;
                bool duplicate = false;
                bool success = false;
            };

            StoreStatus add(::TweetT&);
            bool saveBins();
        private:
            const char*dataDirectory;
            std::string timePointPath;
    };
}
