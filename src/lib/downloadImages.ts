const request = require("request");

import {Tweet} from "./interfaces/tweet";

export function downloadImage(tweet : Tweet,index : number) : Promise<Buffer>
{
    return new Promise<Buffer>((resolve : (value : Buffer) => void,reject : () => void) => 
    {
        request(
            {
                url : tweet.images[index],
                method : "GET",
                encoding: null
            },
            (err : any,res : any) => 
            {
                if(err)
                    throw new Error(err);
                if(res.body)
                    return resolve(Buffer.from(res.body));
                else 
                    return reject();
            });
    });
}

export function downloadImages(tweet : Tweet) : Promise<void>
{
    return new Promise<void>(async (resolve : () => void) => 
    {
        for(let i = 0; i != tweet.images.length; ++i)
        {
            let res = await downloadImage(tweet,i);

            if(res)
            {
                if(!tweet.imageContent)
                {
                    tweet.imageContent = new Array();
                }

                tweet.imageContent.push({url : tweet.images[i],data:res.toString("base64")});
            }
        }
        return resolve();
    });
}

export function downloadAllImages(tweets : Array<Tweet>) : Promise<void>
{
    return new Promise<void>(async (resolve: () => void) => 
    {
        for(let i = 0; i != tweets.length; ++i)
        {
            if(tweets[i].images.length)
            {
                await downloadImages(tweets[i]);
            }
        }
        return resolve();
    });
}
