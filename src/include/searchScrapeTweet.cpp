#include "searchScrapeTweet.hpp"
#include "dateParser.hpp"

std::vector<::TweetT> PanCake::parseSearchScrapeTweetsFromJSON(rapidjson::GenericDocument<rapidjson::UTF8<>>&document)
{
    std::vector<::TweetT> res;

    for(auto it = document.Begin(); it != document.End(); ++it)
    {
        ::TweetT tweet;
        tweet.text = (*it)["text"].GetString();
        tweet.id = (*it)["id"].GetString();
        tweet.user = (*it)["user"].GetString();
        PanCake::TweetDate date = *PanCake::parseSearchScrapeDate((*it)["timestamp"].GetString());
        tweet.date = PanCake::tweetDateToTimePointPathString(date);
        res.push_back(tweet);
    }

    return res;
}