import * as cp from "child_process";

export function compileColumnIR(file : string,outFile : string,exeSearchPath = "") : Promise<void>
{
    return new Promise<void>((resolve : (value : void) => void,reject : (reason : string) => void) : void => 
    {
        try
        {
            let stdoutBuffer : string = "";
            let stdcerrBuffer : string = "";

            let compileColumnIRJob = cp.spawn(`${exeSearchPath}luac`,[
                "-s",
                "-o",
                `${outFile}`,
                `${file}`
            ]);

            compileColumnIRJob.stdout.on("data",(data : string) : void => 
            {
                stdoutBuffer += data;
            });

            compileColumnIRJob.stderr.on("data",(data : string) : void => 
            {
                stdcerrBuffer += data;
            });

            compileColumnIRJob.on("exit",(code : number,signal : string) : void => 
            {
                if(code != 0)
                {
                    reject(`${exeSearchPath}luac exited with ${signal}${"\n"}${stdcerrBuffer}`);
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
