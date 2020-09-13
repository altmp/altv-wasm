#include <SDK.h>
#include "WasmRuntime.hpp"
#include "wasmtime.h"
#include "Utilities.hpp"

CAPI_EXPORT alt::IScriptRuntime* CreateWasmRuntime(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    Utilities::LogInfo("[WASM] Initializing runtime...");

    auto runtime = new WasmRuntime();
    if(!runtime->Init())
        throw std::runtime_error("WasmRuntime was not successfully initialized");
        
    return runtime;
}
