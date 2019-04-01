/// <reference types="jest" />

import {scrapeSearchTerm} from "../src/lib/scrapeSearchTerm";
import { analyzeScrappedTweets } from "../src/lib/analyzeScrappedTweet";

jest.setTimeout(20000);

it(`should scrape 100`,async() => {
    let res = await scrapeSearchTerm("but",100);
    expect(res.length).toBe(100);

    analyzeScrappedTweets(res);

    for(let i = 0; i != res.length; ++i)
    {
        expect(res[i].lang).toBeDefined();
        expect(res[i].sentimentScore).toBeDefined();
        expect(res[i].comparativeSentimentScore).toBeDefined();
    }
});

