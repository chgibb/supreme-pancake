/// <reference types="jest" />

jest.setTimeout(45000);

import { scrapeSearchTerm } from "../src/lib/scrapeSearchTerm";
import { analyzeScrappedTweets } from "../src/lib/analyzeScrappedTweet";
import { downloadAllImages } from "../src/lib/downloadImages";
import { bulkStoreTweets } from "../src/lib/bulkStoreTweets";
import { scrapeUser } from "../src/lib/scrapeUser";

it("should scrape and store tweets recursively", async () => {
    let tweets = await scrapeSearchTerm("and", 30);
    analyzeScrappedTweets(tweets);
    await downloadAllImages(tweets);

    let status = await bulkStoreTweets("tests/rt/scrapeUserRecurs1", JSON.stringify(tweets), "out/");

    expect(status.success).toBe(1);

    let usernames = new Array<string>();

    for (let i = 0; i != tweets.length; ++i) {
        usernames.push(tweets[i].screenName);
    }

    for (let i = 0; i != usernames.length; ++i) {
        try {
            console.log("Scraping ",usernames[i]);
            tweets = await scrapeUser(usernames[i]);
            analyzeScrappedTweets(tweets);
            await downloadAllImages(tweets);

            status = await bulkStoreTweets("tests/rt/scrapeUserRecurs1", JSON.stringify(tweets), "out/");

            expect(status.success).toBe(1);
        }
        catch (err) {
            console.log(err);
        }
    }
});