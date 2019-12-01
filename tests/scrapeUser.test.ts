/// <reference types="jest" />

import { scrapeUser } from "../src/lib/scrapeUser";
import { bulkStoreTweets } from "../src/lib/bulkStoreTweets";
import { analyzeScrappedTweets } from "../src/lib/analyzeScrappedTweet";
import { downloadAllImages } from "../src/lib/downloadImages";

jest.setTimeout(45000);

it("should scrape user and store tweets",async () =>{
   let tweets =  await scrapeUser("nouswaves");
   analyzeScrappedTweets(tweets);
    await downloadAllImages(tweets);

    let status = await bulkStoreTweets("tests/rt/scrapeUser1",JSON.stringify(tweets),"out/");

    expect(status.success).toBe(1);
});