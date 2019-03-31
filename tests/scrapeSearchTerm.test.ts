/// <reference types="jest" />

import {scrapeSearchTerm} from "../src/lib/scrapeSearchTerm";

jest.setTimeout(10000);

it(`should scrape 100`,async() => {
    let res = await scrapeSearchTerm("the",30);
    console.log(res);
    expect(res.length).toBe(30);

});
