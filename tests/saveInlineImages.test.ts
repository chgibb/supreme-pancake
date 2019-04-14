/// <reference types="jest" />

import * as fs from "fs";

import {bulkStoreTweets} from "../src/lib/bulkStoreTweets";
import {OCRTweetBins} from "../src/lib/OCRTweetBins";

jest.setTimeout(15000);

it("should store tweets and OCR images",async () => 
{
    let tweets = fs.readFileSync("tests/res/62ImagesInline.json").toString();

    let status = await bulkStoreTweets("tests/rt/62ImagesInlineTS",tweets,"out/");

    expect(status.added).toBe(300);
    expect(status.duplicates).toBe(0);
    expect(status.success).toBe(1);
    expect(status.metaUpdates).toBe(0);
    expect(status.savedImages).toBe(62);
    expect(status.binsWithNewTweets.length).toBe(48);

    let OCRStatus = await OCRTweetBins("tests/rt/62ImagesInlineTS",status.binsWithNewTweets,"out/");
    
    expect(OCRStatus.attempted).toBe(62);
});

