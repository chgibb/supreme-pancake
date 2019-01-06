/// <reference types="jest" />

import * as fs from "fs";

import {bulkStoreTweets} from "../src/include/bulkStoreTweets";
import {genColumnIR} from "../src/include/genColumnIR";
import {compileColumnIR} from "../src/include/compileColumnIR";

jest.setTimeout(10000);

it(`should generate correct IR for columns`,async () => {
    let tweets = fs.readFileSync("tests/res/bulkStore.json").toString();

    await bulkStoreTweets("tests/rt/columnIR2",tweets,"out/");

    await genColumnIR("tests/rt/columnIR2","tests/rt/columnIR2","2018","11","06",10,"out/");

    expect(fs.existsSync("tests/rt/columnIR2/2018-11-06-sentimentScore.lua")).toBe(true);
    expect(fs.existsSync("tests/rt/columnIR2/2018-11-06-text.lua")).toBe(true);
});

it(`should compile IR to bytecode images`,async () => {
    await compileColumnIR("tests/rt/columnIR2/2018-11-06-sentimentScore.lua","tests/rt/columnIR2/2018-11-06-sentimentScore.byc","out/");
    await compileColumnIR("tests/rt/columnIR2/2018-11-06-text.lua","tests/rt/columnIR2/2018-11-06-text.byc","out/");

    expect(fs.existsSync("tests/rt/columnIR2/2018-11-06-sentimentScore.byc")).toBe(true);
    expect(fs.existsSync("tests/rt/columnIR2/2018-11-06-text.byc")).toBe(true);
});