import { scrapeSearchTerm } from "./lib/scrapeSearchTerm";
import { analyzeScrappedTweets } from "./lib/analyzeScrappedTweet";
import { downloadAllImages } from "./lib/downloadImages";
import { bulkStoreTweets } from "./lib/bulkStoreTweets";

(async function () {
    let tweets = await scrapeSearchTerm("the", 30);
    tweets = tweets.concat(await scrapeSearchTerm("of", 50));
    tweets = tweets.concat(await scrapeSearchTerm("and", 50));
    tweets = tweets.concat(await scrapeSearchTerm("a", 50));

    analyzeScrappedTweets(tweets);
    await downloadAllImages(tweets);

    let status = await bulkStoreTweets("tweets", JSON.stringify(tweets), "out/");

    console.log(JSON.stringify(status));
})();