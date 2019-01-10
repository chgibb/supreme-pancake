const fs = require("fs");
const path = require("path");

const glob = require("glob");
const arg = require("minimist")(process.argv.slice(2));

let noTests = arg.noTests;

let ccFlags = `-pedantic -Wall -Wextra -Wcast-align -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel -Werror -Wno-unused -std=c++17`;
let includeFlags = `-I src/vendor/rapidjson/include -I src/vendor/Catch2/single_include -I src/vendor/compile-time-regular-expressions/include -I src/vendor/PicoSHA2  -I src/vendor/lua-5.3.5/src -I src/vendor/sol2`;
let ldFlags = `-L src/vendor/lua-5.3.5/src -llua -lstdc++fs -lcurl -llept -ltesseract -lm -ldl`;
let optFlags = `-g -O1`;
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
        glob("src/include/**/*.cpp",{},function(err,matches){
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

                if(/\.test/.test(matches[i]))
                    continue;

                testBuildSteps += `build ${matches[i].split('.').slice(0, -1).join('.')}.out : link${trimExtension(matches[i])} ${makeObjectFilePath(matches[i])} | ${makeObjectFilePath(matches[i])} obj/tests-${trimExtension(matches[i])+`.test`}.o ${objFiles}${"\n"}`;
                testLinkRules += `rule link${trimExtension(matches[i])}${"\n"}`;
                testLinkRules += `  command = g++ obj/tests-${trimExtension(matches[i])+`.test`}.o ${objFiles} ${ldFlags} -o $out $in${"\n"}`;
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
    command = g++ -MMD -MF $out.d ${ccFlags} ${includeFlags} ${optFlags} -c $in -o $out
    description = Compiling $in

rule pch
    deps = gcc
    depfile = $out.d
    command = g++ -MMD -MF ${ccFlags.replace(`-Werror`,``)} ${optFlags} $in
    description = Precompiling $in

rule staticLib
    command = ar rcs $out $in

rule link
    command = g++ ${objFiles} ${ldFlags} -o $out $in
    description = Linking $out

rule copyLuac
    command = cp src/vendor/lua-5.3.5/src/luac out/luac
    description = Copying Luac

rule getLua
    command = bash scripts/getLua.bash
    description = Downloading Lua

rule buildLua
    command = cd src/vendor/lua-5.3.5; make linux;
    description = Building Lua

${testLinkRules}

build src/vendor/Catch2/single_include/catch2/catch.hpp.gch : pch src/vendor/Catch2/single_include/catch2/catch.hpp

build src/vendor/lua-5.3.5 : getLua
build src/vendor/lua-5.3.5/src/liblua.a : buildLua | src/vendor/lua-5.3.5 
build out/luac : copyLuac | src/vendor/lua-5.3.5 src/vendor/lua-5.3.5/src/liblua.a

${objFileBuildSteps}

${noTests ? "" : testBuildSteps}

${executableBuildSteps}
`;

    fs.writeFileSync("build.ninja",ninja);
 })().catch((err) => {
    console.log(err);
 });