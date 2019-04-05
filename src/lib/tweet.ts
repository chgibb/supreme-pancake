export interface Tweet
{
    screenName : string;
    id : string;
    time : string;
    isRetweet : boolean;
    isPinned : boolean;
    isReplyTo : boolean;
    text : string;
    userMentions: Array<string>;
    hashTags : Array<string>;
    images : Array<string>;
    urls : Array<string>;
    replyCount : number;
    reTweetCount : number;
    favouriteCount : number;

    //added fields
    lang : string
    comparativeSentimentScore : number;
    sentimentScore : number;
    imageContent? : Array<ImageContent>;
}

export interface ImageContent
{
    url : string;
    data : string;
}
