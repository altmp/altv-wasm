#include <SDK.h>
#include "WasmRuntime.hpp"
#include "wasmtime.h"
#include "util.hpp"

CAPI_EXPORT alt::IScriptRuntime* altMain(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    util::logi("[WASM] Initializing runtime...");

    auto runtime = new WasmRuntime();
    if(!runtime->ok)
        throw std::runtime_error("WasmRuntime was not successfully initialized");
        
    return static_cast<alt::IScriptRuntime*>(runtime);
}
