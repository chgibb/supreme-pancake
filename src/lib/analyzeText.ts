const franc = require("franc");
const Sentiment = require("sentiment");
const sentiment = new Sentiment();

export interface AnalysisResult
{
    lang : string;
    comparativeSentimentScore : number;
    sentimentScore : number;
}

export function analyzeText(text : string) : AnalysisResult
{
    let res = {
        lang : "",
        comparativeSentimentScore : 0,
        sentimentScore : 0
    } as AnalysisResult;

    res.lang = franc(text);
    
    if(res.lang == "eng")
    {
        let scores = sentiment.analyze(text);
        res.sentimentScore = scores.score;
        res.comparativeSentimentScore = scores.comparative;
    }

    return res;
}
