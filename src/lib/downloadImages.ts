const request = require("request");

import {Tweet} from "./tweet";


export function downloadImage(tweet : Tweet,index : number) : Promise<Buffer>
{
    return new Promise<Buffer>((resolve : (value : Buffer) => void,reject : () => void) => 
    {
        request(tweet.images[index],{},(err : any,res : any,body : any) => 
        {
            res;
            if(err)
                throw new Error(err);
            if(body)
                return resolve(Buffer.from(body,"utf-8"));
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