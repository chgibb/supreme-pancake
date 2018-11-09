/// <reference types="jest" />

import * as fs from "fs";

import {bulkStoreTweets,BulkStoreStatus} from "../src/include/bulkStoreTweets";

it(`should generate directory and store tweets on first run`,async () => {
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:10,duplicates:0,success:1});
});


it(`should not add duplicates`,async () => {
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1});
});

it(`should write bulk test data to its own directory`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS2",tweets,"out/")).toEqual(<BulkStoreStatus>{added:1082,duplicates:3318,success:1});
});

it(`should merge bulk test data`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:1072,duplicates:3328,success:1});
});

it(`should not add duplicates`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:4400,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:4400,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:4400,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:4400,success:1});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:4400,success:1});
});
