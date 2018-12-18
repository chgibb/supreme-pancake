/// <reference types="jest" />

import {chunkArray} from "./../src/include/chunkArray";

it(`should chunk array equally`,() => {
    expect(chunkArray([1,2,3,4,5,6,7,8],3) == [[1,2,3],[4,5,6],[7,8]]);
});
