import * as cp from "child_process";

export interface BulkStoreStatus
{
    added : number;
    duplicates : number;
    success : number;
    metaUpdates : number;
    binsWithNewTweets : Array<string>;
}

export function bulkStoreTweets(dataDir : string,tweetStr : string,exeSearchPath = "") : Promise<BulkStoreStatus>
{
    return new Promise<BulkStoreStatus>((resolve : (value : BulkStoreStatus) => void,reject : (reason : string) => void) : void => {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let bulkStoreJob = cp.spawn(`${exeSearchPath}bulkStoreTweets`,[`--type=searchScrape`,`--dir=${dataDir}`]);

            bulkStoreJob.stdout.on("data",(data : string) : void => {
                stdoutBuffer += data;
            });

            bulkStoreJob.stderr.on("data",(data : string) : void => {
                stdcerrBuffer += data;
            });

            bulkStoreJob.on("exit",(code : number,signal : string) : void => {
                if(code != 0)
                {
                    reject(`${exeSearchPath}bulkStoreTweets exited with ${signal}${"\n"}${stdcerrBuffer}`);
                }

                else
                {
                    setTimeout(function(){
                        return resolve(JSON.parse(stdoutBuffer));
                    },10);
                }
                
            });

            bulkStoreJob.stdin.write(JSON.stringify(JSON.parse(tweetStr),undefined,0));
            bulkStoreJob.stdin.end();
        }
        catch(err)
        {
            reject(err);
        }
    });
}