#include <iostream>
#include <string>
#include <fstream>

#include "vendor/cxxopts/include/cxxopts.hpp"

#include "include/loadJSON.hpp"
#include "include/searchScrapeTweet.hpp"
#include "include/bulkTweetStore.hpp"

int main(int argc,char*argv[])
{
    cxxopts::Options options("bulkStoreTweets", "Merge an array of JSON tweets into a storage directory");

    options.add_options()("t,type","JSON source type",cxxopts::value<std::string>())("d,dir","Storage directory path",cxxopts::value<std::string>());

    auto result = options.parse(argc,argv);

    std::string type = result["type"].as<std::string>();
    std::string storageDir = result["dir"].as<std::string>();

    if(type != "searchScrape")
    {
        std::cerr<<"Type must be \"searchScrape\"\n";
    }

    std::string raw;

    std::getline(std::cin,raw);
    
    auto json = PanCake::loadJSONFromString(raw);    
    auto tweets = PanCake::parseSearchScrapeTweetsFromJSON(json);
    
    PanCake::BulkStoreStatus res = PanCake::bulkStoreTweets(storageDir.c_str(),tweets);

    std::string binsWithNewTweets = "\"binsWithNewTweets\":[";

    auto end = res.binsWithNewTweets.end();
    for(auto it = res.binsWithNewTweets.begin(); it != end; ++it)
    {
        binsWithNewTweets += "\"" + *it + "\"";
        if(it != end - 1)
            binsWithNewTweets += ",";   
    }

    binsWithNewTweets += "]";

    std::cout<<"{\"added\":"<<res.added<<",\"duplicates\":"<<res.duplicates<<",\"success\":"<<res.success<<",\"metaUpdates\":"<<res.metaUpdates<<","<<binsWithNewTweets<<"}";
    std::cout.flush();

    return 0;
}
