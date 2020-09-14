#pragma once

#include <wasmtime.h>
#include "Utilities.hpp"

template <typename T>
class WasmPtr
{
public:
    i32 offset = 0;

    WasmPtr(const wasm_val_t& val) : offset(val.of.i32) {}
    WasmPtr(i32 val) : offset(val) {}

    T* get(wasm_memory_t* memory)
    {
        return (T*)(wasm_memory_data(memory) + offset);
    }
};