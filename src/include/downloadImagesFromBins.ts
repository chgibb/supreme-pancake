import * as cp from "child_process";

export function downloadImagesFromBins(dataDir : string,binList : Array<string>,exeSearchPath = "") : Promise<void>
{
    return new Promise<void>((resolve : (value : undefined) => void,reject : (reason : string) => void) : void => {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let downloadImagesJob = cp.spawn(`${exeSearchPath}downloadImagesFromBins`,[`--dir=${dataDir}`]);

            downloadImagesJob.on("data",(data : string) : void => {
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
                        console.log(stdoutBuffer);
                        console.log(stdcerrBuffer);
                        return resolve(undefined);
                        //return resolve(JSON.parse(stdoutBuffer));
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