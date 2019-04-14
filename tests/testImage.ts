import {scrapeSearchTerm} from "../src/lib/scrapeSearchTerm";
import {analyzeScrappedTweets} from "../src/lib/analyzeScrappedTweet";
import {downloadAllImages} from "../src/lib/downloadImages";
import {bulkStoreTweets} from "../src/lib/bulkStoreTweets";
import {writeFileSync} from "fs";
(async function()
{

    let tweets = await scrapeSearchTerm("and",300);
    analyzeScrappedTweets(tweets);
    await downloadAllImages(tweets);

    writeFileSync("test.json",JSON.stringify(tweets,undefined,4));
})();