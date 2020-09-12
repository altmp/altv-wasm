#include "WasmRuntime.hpp"
#include "WasmResource.hpp"
#include "WasmExports.hpp"
#include "util.hpp"
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
        util::loge("[WASM] Failed to instantiate the wasm engine");
        return false;
    }
    store = wasm_store_new(engine);
    if (engine == nullptr)
    {
        util::loge("[WASM] Failed to instantiate the wasm engine");
        return false;
    }

    util::logi("[WASM] Initialized runtime");
    return true;
}

bool WasmRuntime::RequiresMain() const
{
    return true;
}

alt::IResource::Impl *WasmRuntime::CreateImpl(alt::IResource *resource)
{
    auto name = resource->GetName();
    auto main = resource->GetMain();

    if (main.IsEmpty())
    {
        util::loge("[WASM] 'client-main' has to be specified in resource.cfg");
        return nullptr;
    }

    auto pkg = resource->GetPackage();
    auto file = pkg->OpenFile(main);
    if (file == nullptr)
    {
        util::loge("[WASM] Could not open file " + main);
        return nullptr;
    }

    auto size = pkg->GetFileSize(file);
    wasm_byte_vec_t wasm;
    wasm_byte_vec_new_uninitialized(&wasm, size);

    auto readsize = pkg->ReadFile(file, wasm.data, size);
    pkg->CloseFile(file);

    if (readsize != size)
    {
        util::loge("[WASM] Could not read " + main + " appropriately");
        return nullptr;
    }

    wasmtime_error_t *error = nullptr;
    wasm_module_t *module = nullptr;

    error = wasmtime_module_new(engine, &wasm, &module);

    if (error != nullptr)
    {
        util::logwe("[WASM] Failed to compile module", error, nullptr);
        return nullptr;
    }

    wasm_functype_t *hello_ty = wasm_functype_new_0_0();
    wasm_func_t *hello = wasm_func_new(store, hello_ty, WasmExports::hello_callback);

    wasm_extern_t *imports[] = {wasm_func_as_extern(hello)};
    wasm_instance_t *instance = nullptr;
    wasm_trap_t *trap = nullptr;
    error = wasmtime_instance_new(store, module, imports, 1, &instance, &trap);
    if (error != nullptr)
    {
        util::logwe("[WASM] Failed to instantiate module", error, trap);
        return nullptr;
    } else if (instance == nullptr)
    {
        util::loge("[WASM] Failed to instantiate module [Instance is null]");
        return nullptr;
    }

    util::logi("[WASM] Creating a resource instance for " + name + "...");

    return new WasmResource(resource, instance, module);
}

void WasmRuntime::DestroyImpl(alt::IResource::Impl *impl)
{
    util::logi("[WASM] Removed resource");
}

void WasmRuntime::OnTick()
{
}

void WasmRuntime::OnDispose()
{
    util::loge("[WASM] RUNTIME DISPOSE");
}
