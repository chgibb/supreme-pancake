import * as cp from "child_process";

export interface BulkStoreStatus
{
    added : number;
    duplicates : number;
    success : number;
}

export function bulkStoreTweets(dataDir : string,tweetStr : string,exeSearchPath = "") : Promise<BulkStoreStatus>
{
    return new Promise<BulkStoreStatus>((resolve : (value : BulkStoreStatus) => void,reject : (reason : string) => void) => {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let bulkStoreJob = cp.spawn(`${exeSearchPath}bulkStoreTweets`,[`--type=searchScrape`,`--dir=${dataDir}`]);

            bulkStoreJob.stdout.on("data",(data : string) => {
                stdoutBuffer += data;
            });

            bulkStoreJob.stderr.on("data",(data : string) => {
                stdcerrBuffer += data;
            });

            bulkStoreJob.on("exit",(code : number,signal : string) => {
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

            bulkStoreJob.stdin.write(tweetStr);
            bulkStoreJob.stdin.end();
        }
        catch(err)
        {
            reject(err);
        }
    });
}