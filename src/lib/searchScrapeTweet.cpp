#include <picosha2.h>

#include <iostream>

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
        tweet.sentimentScore = (*it)["sentimentScore"].GetInt();
        tweet.comparativeSentimentScore = (*it)["comparativeSentimentScore"].GetFloat();

        for(auto&url : (*it)["images"].GetArray())
        {
            if(url.IsString())
            {
                tweet.images.push_back(url.GetString());
            }
        }

        if((*it).HasMember("imageContent"))
        {
            for(auto imgIt = (*it)["imageContent"].Begin(); imgIt != (*it)["imageContent"].End(); ++imgIt)
            {
                tweet.imageContent.push_back(PanCake::TweetImageContent(
                    (*imgIt)["url"].GetString(),
                    (*imgIt)["data"].GetString()
                ));
            }
        }

        res.push_back(tweet);
    }

    return res;
}
