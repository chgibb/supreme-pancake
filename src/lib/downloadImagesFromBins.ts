import * as cp from "child_process";

import {BulkImageDownloadStatus} from "./bulkImageDownloadStatus";

export function downloadImagesFromBins(dataDir : string,binList : Array<string>,exeSearchPath = "") : Promise<BulkImageDownloadStatus>
{
    return new Promise<BulkImageDownloadStatus>((resolve : (value : BulkImageDownloadStatus) => void,reject : (reason : string) => void) : void => {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let downloadImagesJob = cp.spawn(`${exeSearchPath}downloadImagesFromBins`,[`--dir=${dataDir}`]);

            downloadImagesJob.stdout.on("data",(data : string) : void => {
                stdoutBuffer += data;
            });

            downloadImagesJob.stderr.on("data",(data : string) : void => {
                stdcerrBuffer += data;
            });

            downloadImagesJob.on("exit",(code : number,signal : string) : void => {
                if(code != 0)
                {
                    reject(`${exeSearchPath}downloadImagesFromBins exited with ${signal}${"\n"}${stdcerrBuffer}`);
                }

                else
                {
                    setTimeout(function(){
                        if(!stdoutBuffer)
                        {
                            setTimeout(function(){
                                return resolve(JSON.parse(stdoutBuffer));
                            },2000);
                        }
                        else
                        {
                            return resolve(JSON.parse(stdoutBuffer));
                        }
                    },10);
                }
            });

            downloadImagesJob.stdin.write(JSON.stringify(binList,undefined,0));
            downloadImagesJob.stdin.end();
        }
        catch(err)
        {
            reject(err);
        }
    });
}
