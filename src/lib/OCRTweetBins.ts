import * as cp from "child_process";

import {BulkOCRResult} from "./bulkOCRResult";

export function OCRTweetBins(dataDir : string,binList : Array<string>,exeSearchPath = "") : Promise<BulkOCRResult>
{
    return new Promise<BulkOCRResult>((resolve : (value : BulkOCRResult) => void,reject : (reason : string) => void) : void => 
    {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let ocrTweetBinsJob = cp.spawn(`${exeSearchPath}OCRTweetBins`,[`--dir=${dataDir}`]);

            ocrTweetBinsJob.stdout.on("data",(data : string) : void => 
            {
                stdoutBuffer += data;
            });

            ocrTweetBinsJob.stderr.on("data",(data : string) : void => 
            {
                stdcerrBuffer += data;
            });

            ocrTweetBinsJob.on("exit",(code : number,signal : string) : void => 
            {
                if(code != 0)
                {
                    reject(`${exeSearchPath}OCRTweetBins exited with ${signal}${"\n"}${stdcerrBuffer}`);
                }

                else
                {
                    setTimeout(function()
                    {
                        if(!stdoutBuffer)
                        {
                            setTimeout(function()
                            {
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

            ocrTweetBinsJob.stdin.write(JSON.stringify(binList,undefined,0));
            ocrTweetBinsJob.stdin.end();
        }
        catch(err)
        {
            reject(err);
        }
    });
}
