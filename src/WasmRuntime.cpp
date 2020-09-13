#include "WasmRuntime.hpp"
#include "WasmResource.hpp"
#include "WasmExports.hpp"
#include "Utilities.hpp"
#include "wasmtime.h"

WasmRuntime::WasmRuntime()
{
    Instance() = this;
}

bool WasmRuntime::Init()
{
    engine = wasm_engine_new();
    if (engine == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate the wasm engine");
        return false;
    }
    store = wasm_store_new(engine);
    if (store == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate the wasm store");
        return false;
    }

    Utilities::LogInfo("[WASM] Initialized runtime");
    return true;
}

bool WasmRuntime::RequiresMain() const
{
    return true;
}

alt::IResource::Impl *WasmRuntime::CreateImpl(alt::IResource *resource)
{
    Utilities::LogColored("~r~■~o~■~y~■~g~■~b~■~p~■~c~■");

    auto name = resource->GetName();
    auto main = resource->GetMain();

    if (main.IsEmpty())
    {
        Utilities::LogError("[WASM] 'client-main' has to be specified in resource.cfg");
        return nullptr;
    }

    auto pkg = resource->GetPackage();
    auto file = pkg->OpenFile(main);
    if (file == nullptr)
    {
        Utilities::LogError("[WASM] Could not open file " + main);
        return nullptr;
    }

    auto size = pkg->GetFileSize(file);
    wasm_byte_vec_t wasm;
    wasm_byte_vec_new_uninitialized(&wasm, size);

    auto readsize = pkg->ReadFile(file, wasm.data, size);
    pkg->CloseFile(file);

    if (readsize != size)
    {
        Utilities::LogError("[WASM] Could not read " + main + " properly");
        return nullptr;
    }

    wasmtime_error_t *error = nullptr;
    wasm_module_t *module = nullptr;
    error = wasmtime_module_new(engine, &wasm, &module);
    if (error != nullptr)
    {
        Utilities::LogWasmError("[WASM] Failed to compile module", error, nullptr);
        return nullptr;
    }

    auto wasmResource = new WasmResource(resource);

    wasm_functype_t *hello_ty = wasm_functype_new_0_0();
    wasm_func_t *hello = wasm_func_new_with_env(store, hello_ty, WasmExports::hello_callback, wasmResource, nullptr);

    wasm_extern_t *imports[] = {wasm_func_as_extern(hello)};
    wasm_instance_t *instance = nullptr;
    wasm_trap_t *trap = nullptr;
    error = wasmtime_instance_new(store, module, imports, 1, &instance, &trap);
    if (error != nullptr)
    {
        Utilities::LogWasmError("[WASM] Failed to instantiate module", error, trap);
        delete wasmResource;
        return nullptr;
    }
    else if (instance == nullptr)
    {
        Utilities::LogError("[WASM] Failed to instantiate module [Instance is null]");
        delete wasmResource;
        return nullptr;
    }

    Utilities::LogInfo("[WASM] Creating a resource instance for " + name + "...");

    wasm_exporttype_vec_t module_exports;
    wasm_extern_vec_t instance_exports;
    wasm_module_exports(module, &module_exports);
    wasm_instance_exports(instance, &instance_exports);

    if (module_exports.size != instance_exports.size) {
        Utilities::LogError("[WASM] Module and instance exports don't match");
        delete wasmResource;
        return nullptr;
    }

    for (int i = 0; i < module_exports.size; i++)
    {
        const wasm_name_t *name = wasm_exporttype_name(module_exports.data[i]);
        std::string funcName { name->data, name->size };
        wasmResource->exportsTable.emplace(funcName, wasm_extern_as_func(instance_exports.data[i]));
    }

    wasmResource->instance = instance;
    wasmResource->module = module;

    return wasmResource;
}

void WasmRuntime::DestroyImpl(alt::IResource::Impl *impl)
{
    Utilities::LogInfo("[WASM] Removed resource");
}

void WasmRuntime::OnTick()
{
}

void WasmRuntime::OnDispose()
{
    Utilities::LogError("[WASM] RUNTIME DISPOSE");
}
