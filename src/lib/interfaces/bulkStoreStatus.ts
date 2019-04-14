export interface BulkStoreStatus
{
    added : number;
    duplicates : number;
    success : number;
    metaUpdates : number;
    savedImages: number;
    binsWithNewTweets : Array<string>;
}
