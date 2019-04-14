import {analyzeText} from "./analyzeText";
import {Tweet} from "./tweet";

export function analyzeScrappedTweet(tweet : Tweet) : void
{
    let res = analyzeText(tweet.text);
    tweet.lang = res.lang;
    tweet.sentimentScore = res.sentimentScore;
    tweet.comparativeSentimentScore = res.comparativeSentimentScore;
}

export function analyzeScrappedTweets(tweets : Array<Tweet>) : void
{
    for(let i = 0; i!= tweets.length; ++i)
    {
        analyzeScrappedTweet(tweets[i]);
    }
}
