/// <reference types="jest" />

import {chunkEqual} from "./../src/lib/chunkEqual";

it(`should chunk array equally`,() => {
    expect(chunkEqual([1,2,3,4,5,6,7,8],2) == [[1,2,3,4],[5,6,7,8]]);
    expect(chunkEqual([1,2,3,4,5,6,7,8],3) == [[1,2,3],[5,6,7],[8]]);
    expect(chunkEqual([1,2,3,4,5,6,7,8,9,10,11,12],3) == [[1,2,3,4],[5,6,7,8],[9,10,11,12]]);
});
