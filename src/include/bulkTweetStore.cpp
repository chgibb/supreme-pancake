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
            stores.insert(std::pair<std::string,PanCake::TweetStore>(it->date,PanCake::TweetStore(dataDir)));
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
    }

    res.success = true;
    return res;
}