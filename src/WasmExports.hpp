#include "util.hpp"
#include "wasmtime.h"

namespace WasmExports
{


static wasm_trap_t *hello_callback(const wasm_val_t args[], wasm_val_t results[])
{
    util::logi("[WASM] hello_callback called");
    return nullptr;
}


}