const fs = require("fs");
const path = require("path");

const glob = require("glob");

let ccFlags = `-pedantic -Wall -Wextra -Wcast-align -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Werror -Wno-unused -std=c++17`;
let includeFlags = `-I src/vendor/rapidjson/include -I src/vendor/Catch2/single_include -I src/vendor/compile-time-regular-expressions/include -I src/vendor/PicoSHA2`;
let ldFlags = `-lstdc++fs`;
let debugFlags = `-g`;
let objFiles = "";
let objFileBuildSteps = "";
let testBuildSteps = "";
let executableBuildSteps ="";

let testLinkRules = ``;

function makeObjectFilePath(file)
{
    return `obj/${file.split("/").join("-")}.o`.split(".cpp").join("");
}

function makeExecutableFilePath(file)
{
    return `out/${trimExtension(file)}`;
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

                testBuildSteps += `build ${matches[i].split('.').slice(0, -1).join('.')}.out : link${trimExtension(matches[i])} ${makeObjectFilePath(matches[i])} | ${makeObjectFilePath(matches[i])} obj/tests-${trimExtension(matches[i])+"-tests"}.o ${objFiles}${"\n"}`;
                testLinkRules += `rule link${trimExtension(matches[i])}${"\n"}`;
                testLinkRules += `  command = g++ obj/tests-${trimExtension(matches[i])+"-tests"}.o ${objFiles} ${ldFlags} -o $out $in${"\n"}`;
                testLinkRules += `  description = Linking $out${"\n"}`;
            }
            return resolve();
        });
    });

    await new Promise((resolve,reject) => {
        glob("src/*.cpp",{},function(err,matches){
            if(err)
                reject(err);
            for(let i = 0; i != matches.length; ++i)
            {
                executableBuildSteps += `build ${makeObjectFilePath(matches[i])} : cc ${matches[i]}${"\n"}`;
                executableBuildSteps += `build ${makeExecutableFilePath(matches[i])} : link ${makeObjectFilePath(matches[i])} | ${objFiles}${"\n"}`;
                executableBuildSteps += `  description = Linking $out${"\n"}`;
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
    description = Compiling $in

rule staticLib
    command = ar rcs $out $in

rule link
    command = g++ ${objFiles} ${ldFlags} -o $out $in
    description = Linking $out

${testLinkRules}

${objFileBuildSteps}

${testBuildSteps}

${executableBuildSteps}
`;

    fs.writeFileSync("build.ninja",ninja);
 })().catch((err) => {
    console.log(err);
 });