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
        tweet.user = (*it)["screenName"].GetString();
        tweet.userHash = picosha2::hash256_hex_string(tweet.user.begin(),tweet.user.end());
        PanCake::TweetDate date = *PanCake::parseSearchScrapeDate((*it)["time"].GetString());
        tweet.date = PanCake::tweetDateToTimePointPathString(date);
        tweet.isRetweet = (*it)["isRetweet"].GetBool();
        tweet.isPinned = (*it)["isPinned"].GetBool();
        tweet.isReplyTo = (*it)["isReplyTo"].GetBool();
        tweet.replyCount = (*it)["replyCount"].GetInt();
        tweet.reTweetCount = (*it)["retweetCount"].GetInt();
        tweet.favouriteCount = (*it)["favoriteCount"].GetInt();
        res.push_back(tweet);
    }

    return res;
}
