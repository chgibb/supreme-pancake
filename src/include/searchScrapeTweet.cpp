#include <picosha2.h>

#include "searchScrapeTweet.hpp"
#include "dateParser.hpp"

[[nodiscard]] std::vector<PanCake::Tweet> PanCake::parseSearchScrapeTweetsFromJSON(rapidjson::GenericDocument<rapidjson::UTF8<>>&document)
{
    std::vector<PanCake::Tweet> res;

    for(auto it = document.Begin(); it != document.End(); ++it)
    {
        PanCake::Tweet tweet;
        tweet.text = (*it)["text"].GetString();
        tweet.textHash = picosha2::hash256_hex_string(tweet.text.begin(),tweet.text.end());
        tweet.id = (*it)["id"].GetString();
        tweet.user = (*it)["user"].GetString();
        PanCake::TweetDate date = *PanCake::parseSearchScrapeDate((*it)["timestamp"].GetString());
        tweet.date = PanCake::tweetDateToTimePointPathString(date);
        res.push_back(tweet);
    }

    return res;
}
