import * as fs from "fs";

import {bulkStoreTweets} from "../../src/include/bulkStoreTweets";
import {BulkStoreStatus} from "../../src/include/bulkStoreStatus";
import {genColumnIR} from "../../src/include/genColumnIR";
import {compileColumnIR} from "../../src/include/compileColumnIR";

(async function(){
    let packs = fs.readdirSync("tests/res/10kPacs");
    let status : BulkStoreStatus = {
        added : 0,
        success : 0,
        duplicates : 0,
        metaUpdates : 0,
        binsWithNewTweets : []
    };
    for(let i = 0; i != packs.length; ++i)
    {
        let tweets = fs.readFileSync(`tests/res/10kPacs/${packs[i]}`).toString();

        let curStatus = await bulkStoreTweets("tests/rt/100k",tweets,"out/");
        status.added += curStatus.added;
        status.duplicates += curStatus.duplicates;
        status.success += curStatus.success;
        status.metaUpdates += curStatus.metaUpdates;
        console.log(status);
    }

    await genColumnIR("tests/rt/100k","tests/rt/100k","2018","12","31",10,"out/");
    await compileColumnIR("tests/rt/100k/2018-12-31-text.lua","tests/rt/100k/2018-12-31-text.byc","out/");

    await genColumnIR("tests/rt/100k","tests/rt/100k","2018","12","31",10,"out/");
    await compileColumnIR("tests/rt/100k/2018-12-31-sentimentScore.lua","tests/rt/100k/2018-12-31-sentimentScore.byc","out/");
})();
