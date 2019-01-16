export interface BulkStoreStatus
{
    added : number;
    duplicates : number;
    success : number;
    metaUpdates : number;
    binsWithNewTweets : Array<string>;
}
