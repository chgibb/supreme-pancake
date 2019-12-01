const scrapeTwitter = require("scrape-twitter");

const { TimelineStream } = scrapeTwitter;

import { Tweet } from "./tweet";

export async function scrapeUser(user: string): Promise<Array<Tweet>> {
    return new Promise<Array<Tweet>>(async (resolve: (value: Array<Tweet>) => void, reject: (reason: any) => void) => {
        let stream = new TimelineStream(user, "list", 100);

        let res = new Array<Tweet>();

        stream.on("data", (data: Tweet) => {
            res.push(data);
        })

        stream.on("end", () => {
            return resolve(res);
        });

        stream.on("error", (err: any) => {
            return reject(err);
        });


    });
}