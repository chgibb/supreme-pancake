/// <reference types="jest" />

import * as fs from "fs";
import {bulkStoreTweets} from "../src/include/bulkStoreTweets";
import {downloadImagesFromBins} from "../src/include/downloadImagesFromBins";
import {downloadImagesFromBinsMulti} from "../src/include/downloadImagesFromBinsMulti";

jest.setTimeout(1200000);

it(`should save tweets and download images from changed bins`,async () => {
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();

    let tweetStatus = await bulkStoreTweets("tests/rt/downloadImages1",tweets,"out/");

    await downloadImagesFromBins("tests/rt/downloadImages1",tweetStatus.binsWithNewTweets,"out/");
});

it(`should save tweets and download images from changed bins`,async () => {
    let tweets = fs.readFileSync("tests/res/20Images.json").toString();

    let tweetStatus = await bulkStoreTweets("tests/rt/downloadImages20",tweets,"out/");

    let dlStatus = await downloadImagesFromBinsMulti("tests/rt/downloadImages20",tweetStatus.binsWithNewTweets,8,"out/");

    expect(dlStatus.attempted).toBe(20);
    expect(dlStatus.succeeded).toBe(19);
    expect(dlStatus.failed).toBe(1);
});


it(`should save tweets and download images from changed bins`,async () => {
    let tweets = fs.readFileSync("tests/res/50Images.json").toString();

    let tweetStatus = await bulkStoreTweets("tests/rt/downloadImages50",tweets,"out/");

    let dlStatus = await downloadImagesFromBinsMulti("tests/rt/downloadImages50",tweetStatus.binsWithNewTweets,20,"out/");

    expect(dlStatus.attempted).toBe(50);
    expect(dlStatus.succeeded).toBe(47);
    expect(dlStatus.failed).toBe(3);
});
