import * as cp from "child_process";

export function genColumnIR(dataDir : string,outDir : string,year : string,month : string,day : string,chunkSize : number,exeSearchPath = "") : Promise<void>
{
    return new Promise<void>((resolve : (value : void) => void,reject : (reason : string) => void) : void => {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let genColumnIRJob = cp.spawn(`${exeSearchPath}genColumnIR`,[
                `--dir=${dataDir}`,
                `--outDir=${outDir}`,
                `--year=${year}`,
                `--month=${month}`,
                `--day=${day}`,
                `--chunkSize=${chunkSize}`
            ]);

            genColumnIRJob.stdout.on("data",(data : string) : void => {
                stdoutBuffer += data;
            });

            genColumnIRJob.stderr.on("data",(data : string) : void => {
                stdcerrBuffer += data;
            });

            genColumnIRJob.on("exit",(code : number,signal : string) : void => {
                if(code != 0)
                {
                    reject(`${exeSearchPath}genColumnIR exited with ${signal}${"\n"}${stdcerrBuffer}`);
                }

                else
                {
                    return resolve(undefined);
                }
            });

        }
        catch(err)
        {
            reject(err);
        }
    });
}
