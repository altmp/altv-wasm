const altv_capi = require('../deps/altv-capi/capi/client/altv-capi.json');
const fs = require('fs');

const types = {
    // "signed char": "i8",
    // "short": "i16",
    // "int": "i32",
    // "long long": "i64",
    // "unsigned char": "u8",
    // "unsigned short": "u16",
    // "unsigned int": "u32",
    // "unsigned long long": "u64",
    // "float": "f32",
    // "double": "f64",
    "_Bool": "bool"
};

let definedStructs = [];
let queuedStructs = [];
let ignoreStructs = ['alt_CWebView'];

const tab = '    ';

let headerString = '#pragma once\n\n#include <altv-capi-client.h>\n#include "WasmPtr.hpp"\n\nnamespace Wasm\n{\n';

structLoop:
for (const structName in altv_capi.structs) {
    const structData = altv_capi.structs[structName];
    const newStructName = structName;

    let structString = `${tab}struct ${newStructName} \n${tab}{\n`;

    for (const [index, field] of structData.fields.entries()) {
        if (altv_capi.enums[field.type.name]) {
            structString += `${tab}${tab}${field.type.name} ${field.name};\n`;
            continue;
        }

        const fieldType = field.type.name;

        if (fieldType.startsWith('alt_') && !definedStructs.includes(fieldType.replace('*', ''))) {
            queuedStructs.push(structName);
            continue structLoop;
        }

        if (fieldType.includes('alt_') || fieldType.includes('*')) {
            const type = `WasmPtr<${fieldType.replace('*', '')}>`;
            structString += `${tab}${tab}${type} ${field.name};\n`;
            continue;
        }

        structString += `${tab}${tab}${types[fieldType] ? types[fieldType] : fieldType} ${field.name};\n`;
    }

    structString += `${tab}};\n`
    headerString += `${structString}\n`;

    definedStructs.push(newStructName);
}

while(queuedStructs.length !== ignoreStructs.length) {
    structLoop:
    for (let [index, structName] of queuedStructs.entries()) {

        const structData = altv_capi.structs[structName];
        const newStructName = structName;

        let structString = `${tab}struct ${newStructName} \n${tab}{\n`;

        for (const [index, field] of structData.fields.entries()) {
            if (altv_capi.enums[field.type.name]) {
                structString += `${tab}${tab}${field.type.name} ${field.name};\n`;
                continue;
            }

            const fieldType = field.type.name;

            if (fieldType.includes('alt_') || fieldType.includes('*')) {
                const type = `WasmPtr<${fieldType.replace('*', '')}>`;
                structString += `${tab}${tab}${type} ${field.name};\n`;
                continue;
            }

            if (fieldType.startsWith('alt_') && !definedStructs.includes(fieldType.replace('*', ''))) {
                continue structLoop;
            }

            structString += `${tab}${tab}${types[fieldType] ? types[fieldType] : fieldType} ${field.name};\n`;
        }

        structString += `${tab}};\n`
        headerString += `${structString}\n`;

        definedStructs.push(newStructName);
        queuedStructs.splice(index, 1);
    }
}

headerString += `}`;

fs.writeFileSync("../src/WasmStructs.hpp", headerString);

console.log(`Found ${Object.keys(altv_capi.structs).length} structs.`);
console.log(`Ignored ${ignoreStructs.length} structs.`);
console.log(`Defined ${definedStructs.length} structs.`);

