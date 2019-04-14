/// <reference types="jest" />

jest.setTimeout(15000);

import {scrapeSearchTerm} from "../src/lib/scrapeSearchTerm";
import {analyzeScrappedTweets} from "../src/lib/analyzeScrappedTweet";
import {downloadAllImages} from "../src/lib/downloadImages";
import {bulkStoreTweets} from "../src/lib/bulkStoreTweets";

it("should scrape and store tweets",async () =>
{
    let tweets = await scrapeSearchTerm("and",30);
    analyzeScrappedTweets(tweets);
    await downloadAllImages(tweets);

    expect(tweets.length).toBe(30);

    let status = await bulkStoreTweets("tests/rt/scrapeToStore1",JSON.stringify(tweets),"out/");
    
    expect(status.added).toBe(30);
    expect(status.duplicates).toBe(0);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBeGreaterThan(0);
});
