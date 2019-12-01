import { scrapeSearchTerm } from "./lib/scrapeSearchTerm";
import { analyzeScrappedTweets } from "./lib/analyzeScrappedTweet";
import { downloadAllImages } from "./lib/downloadImages";
import { bulkStoreTweets } from "./lib/bulkStoreTweets";
import { scrapeUser } from "./lib/scrapeUser";

(async function () {
    let tweets = await scrapeSearchTerm("the", 30);
    tweets = tweets.concat(await scrapeSearchTerm("of", 50));
    tweets = tweets.concat(await scrapeSearchTerm("and", 50));
    tweets = tweets.concat(await scrapeSearchTerm("a", 50));

    analyzeScrappedTweets(tweets);
    await downloadAllImages(tweets);

    let status = await bulkStoreTweets("tweets", JSON.stringify(tweets), "out/");

    console.log(JSON.stringify(status));

    let usernames = new Array<string>();

    for (let i = 0; i != tweets.length; ++i) {
        usernames.push(tweets[i].screenName);
    }

    for (let i = 0; i != usernames.length; ++i) {
        try {
            console.log("Scraping ", usernames[i]);
            tweets = await scrapeUser(usernames[i]);
            analyzeScrappedTweets(tweets);
            await downloadAllImages(tweets);

            status = await bulkStoreTweets("tweets", JSON.stringify(tweets), "out/");
            console.log(JSON.stringify(status));
        }
        catch (err) {
            console.log(err);
        }
    }
})();