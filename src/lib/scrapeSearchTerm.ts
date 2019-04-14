const streamToPromise = require("stream-to-promise");
const scrapeTwitter = require("scrape-twitter");

const {TweetStream} = scrapeTwitter;

import {Tweet} from "./interfaces/tweet";

export async function scrapeSearchTerm(term : string,limit : number) : Promise<Array<Tweet>>
{
    return new Promise<Array<Tweet>>(async (resolve : (value : any) => void) => 
    {
        const searchStream = new TweetStream(term,"latest",{count:limit});
        let scrapped : Array<Tweet> = await streamToPromise(searchStream);

        resolve(scrapped);
    });
}

