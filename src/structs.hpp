#pragma once

#include "wasm.h"

struct WasmResource
{
    std::string name;
    wasm_instance_t *instance;
    wasm_module_t *module;

    WasmResource(const char* name, wasm_instance_t *instance, wasm_module_t *module)
        : name(name), instance(instance), module(module) {}

    static WasmResource *from(alt_IResource_Impl *res)
    {
        return (WasmResource*)alt_CAPIResource_Impl_GetExtra(res);
    }
};