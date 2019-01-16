export function chunkEqual<T>(arr : Array<T>,chunks : number) : Array<Array<T>>
{
    let res = new Array<Array<T>>();

    for(let i = 0; i != chunks; ++i)
    {
        res.push(new Array<T>());
    }

    let resIt = 0;
    for(let i = 0; i != arr.length; ++i)
    {
        if(resIt == res.length)
            resIt = 0;
        res[resIt].push(arr[i]);
        resIt++;
    }

    return res;
}