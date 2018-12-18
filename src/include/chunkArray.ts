//adapted from https://ourcodeworld.com/articles/read/278/how-to-split-an-array-into-chunks-of-the-same-size-easily-in-javascript

export function chunkArray<T>(arr : Array<T>,size : number) : Array<Array<T>>
{
    let res = new Array<Array<T>>();

    for(let index = 0; index < arr.length; index += size)
    {
        res.push(arr.slice(index,index+size));
    }

    return res;
}
