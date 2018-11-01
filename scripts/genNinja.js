const fs = require("fs");
const path = require("path");

const glob = require("glob");

let ccFlags = `-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Werror -Wno-unused -std=c++17`;
let includeFlags = `-I src/vendor/rapidjson/include -I src/vendor/Catch2/single_include -I src/vendor/compile-time-regular-expressions/include`;
let ldFlags = ``;
let debugFlags = `-g`;
let objFiles = "";
let objFileBuildSteps = "";
let testBuildSteps = "";

let testLinkRules = ``;

function makeObjectFilePath(file)
{
    return `obj/${path.basename(file).split('.').slice(0, -1).join('.')}.o`;
}

function trimExtension(file)
{
    return `${path.basename(file).split('.').slice(0, -1).join('.')}`;
}

 (async function(){
    await new Promise((resolve,reject) => {
        glob("src/include/*.cpp",{},function(err,matches){
            if(err)
                reject(err);
            for(let i = 0; i != matches.length; ++i)
            {
                let fileName = path.basename(matches[i]);
                objFileBuildSteps += `build ${makeObjectFilePath(matches[i])} : cc ${matches[i]}${"\n"}`;
                objFiles += `${makeObjectFilePath(matches[i])} `;
            }
            return resolve();
        });
    });

    await new Promise((resolve,reject) => {
        glob("tests/*.cpp",{},function(err,matches){
            if(err)
                reject(err);
            for(let i = 0; i != matches.length; ++i)
            {       
                testBuildSteps += `build ${makeObjectFilePath(matches[i])} : cc ${matches[i]}${"\n"}`;

                if(/-tests/.test(matches[i]))
                    continue;

                testBuildSteps += `build ${matches[i].split('.').slice(0, -1).join('.')}.out : link${trimExtension(matches[i])} ${makeObjectFilePath(matches[i])} | ${makeObjectFilePath(matches[i])} obj/${trimExtension(matches[i])+"-tests"}.o ${objFiles}${"\n"}`;
                testLinkRules += `rule link${trimExtension(matches[i])}${"\n"}`;
                testLinkRules += `  command = g++ ${ldFlags} obj/${trimExtension(matches[i])+"-tests"}.o ${objFiles} -o $out $in${"\n"}`;
            }
            return resolve();
        });
    });


let ninja =
`
rule cc
    deps = gcc
    depfile = $out.d
    command = g++ -MMD -MF $out.d ${ccFlags} ${includeFlags} ${debugFlags} -c $in -o $out

rule staticLib
    command = ar rcs $out $in

rule link
    command = g++ ${ldFlags} ${objFiles} -o $out $in${"\n"}

${testLinkRules}

${objFileBuildSteps}

${testBuildSteps}
`;

    fs.writeFileSync("build.ninja",ninja);
 })().catch((err) => {
    console.log(err);
 });