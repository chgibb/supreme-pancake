/// <reference types="jest" />

import {scrapeSearchTerm} from "../src/lib/scrapeSearchTerm";
import {downloadImages} from "../src/lib/downloadImages";

jest.setTimeout(10000);

it("should download all images for tweets",async () => 
{
    let res = await scrapeSearchTerm("the",20);
    expect(res.length).toBe(20);

    for(let i = 0; i != res.length; ++i)
    {
        if(res[i].images.length)
        {
            await downloadImages(res[i]);
        }
    }
});

