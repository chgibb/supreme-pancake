/// <reference types="jest" />

import * as fs from "fs";

import {bulkStoreTweets} from "../src/lib/bulkStoreTweets";

jest.setTimeout(10000);

it("should generate directory and store tweets on first run",async () => 
{
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();

    let status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    
    expect(status.added).toBe(10);
    expect(status.duplicates).toBe(0);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(9);
});


it("should not add duplicates",async () => 
{
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();

    let status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(10);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);
});

it("should write bulk test data to its own directory",async () => 
{
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();

    let status = await bulkStoreTweets("tests/rt/bulkStoreTS2",tweets,"out/");

    expect(status.added).toBe(5040);
    expect(status.duplicates).toBe(500);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(996);
});

it("should merge bulk test data",async () => 
{
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();

    let status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");

    expect(status.added).toBe(5040);
    expect(status.duplicates).toBe(500);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(996);
});

it("should not add duplicates",async () => 
{
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();

    let status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(5540);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(5540);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);

    status = await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/");
    expect(status.added).toBe(0);
    expect(status.duplicates).toBe(5540);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.binsWithNewTweets.length).toBe(0);
});
