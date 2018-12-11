/// <reference types="jest" />

import * as fs from "fs";
import { bulkStoreTweets } from "../src/include/bulkStoreTweets";
import { downloadImagesFromBins } from "../src/include/downloadImagesFromBins";

jest.setTimeout(10000);

it(`should save tweets and download images from changed bins`,async () => {
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();

    let tweetStatus = await bulkStoreTweets("tests/rt/downloadImages1",tweets,"out/");

    await downloadImagesFromBins("tests/rt/downloadImages1",tweetStatus.binsWithNewTweets,"out/");
});