import {downloadImagesFromBins} from "./downloadImagesFromBins";
import {BulkImageDownloadStatus} from "./bulkImageDownloadStatus";
import {chunkEqual} from "./chunkEqual";

export function downloadImagesFromBinsMulti(dataDir : string,binList : Array<string>,par : number,exeSearchPath = "") : Promise<BulkImageDownloadStatus>
{
    return new Promise<BulkImageDownloadStatus>(async (resolve : (value : BulkImageDownloadStatus) => void,reject : (reason : string) => void) : Promise<void> => {
        let promises = new Array<Promise<BulkImageDownloadStatus>>();

        try
        {
            let listChunks = chunkEqual(binList,par);

            for(let i = 0; i != listChunks.length; ++i)
            {
                promises.push(downloadImagesFromBins(dataDir,listChunks[i],exeSearchPath));
            }

            let res : BulkImageDownloadStatus = {
                succeeded : 0,
                failed : 0,
                attempted : 0
            };

            for(let i = 0; i != promises.length; ++i)
            {
                promises[i].then((status : BulkImageDownloadStatus) => {
                    res.succeeded += status.succeeded;
                    res.failed += status.failed;
                    res.attempted += status.attempted;
                });
            }

            await Promise.all(promises);

            return resolve(res);
        }
        catch(err)
        {
            return reject(err);
        }
    });
}
