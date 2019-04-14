export interface BulkStoreStatus
{
    added : number;
    duplicates : number;
    success : boolean;
    metaUpdates : number;
    savedImages: number;
    binsWithNewTweets : Array<string>;
}
