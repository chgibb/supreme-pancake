const franc = require("franc");
const Sentiment = require("sentiment");
const sentiment = new Sentiment();

import {Tweet} from "./tweet";

export function analyzeScrappedTweet(tweet : Tweet) : void
{
    tweet.lang = franc(tweet.text);
    
    if(tweet.lang == "eng")
    {
        let scores = sentiment.analyze(tweet.text);
        tweet.sentimentScore = scores.score;
        tweet.comparativeSentimentScore = scores.comparative;
    }

    else
    {
        tweet.sentimentScore = 0;
        tweet.comparativeSentimentScore = 0;
    }
}


export function analyzeScrappedTweets(tweets : Array<Tweet>) : void
{
    for(let i = 0; i!= tweets.length; ++i)
    {
        analyzeScrappedTweet(tweets[i]);
    }
}
