#pragma once

#include <wasmtime.h>
#include "Utilities.hpp"

namespace WasmExports
{
    struct WASM_alt_StringView {
        i32 data;
        u64 size;
    };

    static wasm_trap_t* hello_callback(void* env, const wasm_val_t args[], wasm_val_t results[])
    {
        Utilities::LogInfo("[WASM] hello_callback called");
        return nullptr;
    }

    static wasm_trap_t* ICore_LogInfo(void* env, const wasm_val_t args[], wasm_val_t results[])
    {
        auto wasmResource = static_cast<WasmResource*>(env);
        auto core = static_cast<alt_ICore*>(wasmResource->GetPointer(args[0].of.i32));

        wasm_memory_t* memory = wasmResource->FindExportedMemory("memory");

        char* data = wasm_memory_data(memory);
        auto ptr = (WASM_alt_StringView*)(data + args[1].of.i32);

        char* string = (char *)(data + ptr->data);

        alt_StringView stringView { string, ptr->size };
        alt_ICore_LogInfo(core, &stringView);

        return nullptr;
    }
}