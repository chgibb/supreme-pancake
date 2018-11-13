/// <reference types="jest" />

import * as fs from "fs";

import {bulkStoreTweets,BulkStoreStatus} from "../src/include/bulkStoreTweets";

jest.setTimeout(10000);

it(`should generate directory and store tweets on first run`,async () => {
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:10,duplicates:0,success:1,metaUpdates:0});
});


it(`should not add duplicates`,async () => {
    let tweets = fs.readFileSync("tests/res/searchScrapeTweets.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:10,success:1,metaUpdates:0});
});

it(`should write bulk test data to its own directory`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS2",tweets,"out/")).toEqual(<BulkStoreStatus>{added:5040,duplicates:500,success:1,metaUpdates:0});
});

it(`should merge bulk test data`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:5040,duplicates:500,success:1,metaUpdates:0});
});

it(`should not add duplicates`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:5540,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:5540,success:1,metaUpdates:0});
    expect(await bulkStoreTweets("tests/rt/bulkStoreTS",tweets,"out/")).toEqual(<BulkStoreStatus>{added:0,duplicates:5540,success:1,metaUpdates:0});
});
