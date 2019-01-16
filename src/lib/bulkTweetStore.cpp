#include <algorithm>
#include <map>
#include <string>
#include <iostream>

#include "bulkTweetStore.hpp"
#include "tweetStore.hpp"

[[nodiscard]] PanCake::BulkStoreStatus PanCake::bulkStoreTweets(const char*dataDir,std::vector<PanCake::Tweet>&tweets)
{
    PanCake::BulkStoreStatus res;

    std::map<std::string,PanCake::TweetStore> stores;

    std::sort(tweets.begin(),tweets.end(),[](const PanCake::Tweet&lhs,const PanCake::Tweet&rhs){
        return lhs.date < rhs.date;
    });

    auto end = tweets.end();
    for(auto it = tweets.begin(); it != end; ++it)
    {
        if(stores.count(it->date) == 0)
        {
            stores.insert(std::pair<std::string,PanCake::TweetStore>(
                it->date,
                PanCake::TweetStore(dataDir)
            ));
        }

        PanCake::TweetStore::StoreStatus storeRes = stores.at(it->date).add(*it);
        if(storeRes.invalid)
        {
            res.success = false;
            return res;
        }

        else if(storeRes.success)
            res.added++;
        else if(storeRes.duplicate)
            res.duplicates++;
        else if(storeRes.updatedMeta)
            res.metaUpdates++;
    }

    auto mapEnd = stores.end();
    for(auto it = stores.begin(); it != mapEnd; ++it)
    {
        if(!it->second.saveBins())
        {
            res.success = false;
            return res;
        }

        std::for_each(
            it->second.binsWithNewTweets.begin(),
            it->second.binsWithNewTweets.end(),
            [&res](const std::pair<std::string,bool>&binModStatus) -> void {
                if(binModStatus.second)
                    res.binsWithNewTweets.push_back(binModStatus.first);
            }
        );
        
    }

    res.success = true;
    return res;
}