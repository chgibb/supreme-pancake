#pragma once

#include <map>
#include <vector>
#include <string>

#include "../vendor/tweetBin_generated.h"

namespace PanCake
{
    bool saveTweetsToDataDirectory(const char*,std::vector<::TweetT>&);
    bool saveTweetToDataDirectory(const char*,::TweetT&);
    std::string makeTweetTimePointPath(const char*,::TweetT&);
    std::string makeTweetTimePointFBBinPath(const char*,::TweetT&);

    class TweetStore
    {
        public:
            TweetStore(const char*);

            struct StoreStatus
            {
                bool invalid = false;
                bool duplicate = false;
                bool success = false;
            };

            StoreStatus add(::TweetT&);
        private:
            const char*dataDirectory;
            std::string timePointPath;
            std::map<char,::TweetBinT> bins;
    };
}
