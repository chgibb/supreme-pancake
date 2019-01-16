#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "enumerateRawTweetsInDay.hpp"
#include "enumerateTimePoints.hpp"
#include "makeTweetTimePointPaths.hpp"
#include "tweetBin.hpp"
#include "loadTweetBin.hpp"

void PanCake::enumerateRawTweetsInDay(const char*dataDir,PanCake::TweetDate&date,std::function<void(const PanCake::Tweet&)> func)
{
    std::vector<std::string> pathStrings = PanCake::enumerateTimePointPathStringForDay(date);

    std::for_each(
        pathStrings.begin(),
        pathStrings.end(),
        [&dataDir,&func](const std::string&timePointStr) -> void {
            std::vector<std::string> binStrings = PanCake::makeTweetBinPathsFromTimePointString(dataDir,timePointStr.c_str());
            std::for_each(
                binStrings.begin(),
                binStrings.end(),
                [&dataDir,&func](const std::string&binString) -> void {
                    PanCake::TweetBin*bin = PanCake::loadTweetBin(binString);
                    if(bin)
                    {
                        PanCake::forEachBucket(
                            *bin,
                            [&func](const std::vector<PanCake::Tweet>&bucket) -> void {
                                std::for_each(
                                    bucket.begin(),
                                    bucket.end(),
                                    [&func](const PanCake::Tweet&tweet) -> void {
                                        func(tweet);
                                    }
                                );
                            }
                        );

                        delete bin;
                    }
                }
            );
        }
    );
}
