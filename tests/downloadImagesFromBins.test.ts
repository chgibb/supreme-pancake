/// <reference types="jest" />

import * as fs from "fs";

import {bulkStoreTweets} from "../src/lib/bulkStoreTweets";
import {downloadImagesFromBins} from "../src/lib/downloadImagesFromBins";
import {downloadImagesFromBinsMulti} from "../src/lib/downloadImagesFromBinsMulti";

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

it(`should save tweets and download images from changed bins`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();

    let tweetStatus = await bulkStoreTweets("tests/rt/downloadImages877",tweets,"out/");

    let dlStatus = await downloadImagesFromBinsMulti("tests/rt/downloadImages877",tweetStatus.binsWithNewTweets,40,"out/");

    expect(dlStatus.attempted).toBe(732);
    expect(dlStatus.succeeded).toBe(691);
    expect(dlStatus.failed).toBe(41);
});
