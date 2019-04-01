/// <reference types="jest" />

import {scrapeSearchTerm} from "../src/lib/scrapeSearchTerm";

jest.setTimeout(20000);

it(`should scrape 100`,async() => {
    let res = await scrapeSearchTerm("but",100);
    expect(res.length).toBe(100);
});