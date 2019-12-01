(async function () {
    const rollup = require("rollup");
    const resolve = require("rollup-plugin-node-resolve");
    const commonjs = require("rollup-plugin-commonjs");
    const replace = require("rollup-plugin-replace");

    let args = process.argv.slice(2);

    const inOpts = {
        input: args[0],
        plugins: [
            resolve({
                preferBuiltins: true
            }),
            (() => {
                return {
                    name: "verbose",
                    resolveId: (source: string): null => {
                        console.log(source);
                        return null;
                    },
                    load: (id: string): null => {
                        console.log(id);
                        return null;
                    }
                }
            })()
            //commonjs()
        ],
    };

    const outOpts = {
        file: args[0],
        format: "cjs",
        interop: false,
    };


    const bundle = await rollup.rollup(inOpts);
    await bundle.write(outOpts);
})();