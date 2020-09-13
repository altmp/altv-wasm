#pragma once

#include "Utilities.hpp"
#include <wasmtime.h>

namespace WasmExports
{
    static wasm_trap_t *hello_callback(void* env, const wasm_val_t args[], wasm_val_t results[])
    {
        Utilities::LogInfo("[WASM] hello_callback called");
        return nullptr;
    }
}