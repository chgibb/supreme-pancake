const streamToPromise = require('stream-to-promise');
const scrapeTwitter = require("scrape-twitter");

const {TweetStream} = scrapeTwitter;

import {Tweet} from "./tweet";
import { analyzeScrappedTweet } from "./analyzeScrappedTweet";

export async function scrapeSearchTerm(term : string,limit : number) : Promise<Array<Tweet>>
{
    return new Promise<Array<Tweet>>(async (resolve : (value : any) => void) => {
        const searchStream = new TweetStream(term,"latest",{count:limit});
        let scrapped : Array<Tweet> = await streamToPromise(searchStream);

        for(let i = 0; i != scrapped.length; ++i)
        {
            analyzeScrappedTweet(scrapped[i]);
        }

        resolve(scrapped);
    });
}

