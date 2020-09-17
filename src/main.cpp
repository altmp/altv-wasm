#include <SDK.h>
#include "WasmRuntime.hpp"

CAPI_EXPORT alt::IScriptRuntime* CreateWasmRuntime(alt::ICore* core)
{
    alt::ICore::SetInstance(core);

    Utilities::LogInfo("[WASM] Initializing runtime...");

    auto runtime = new WasmRuntime();
    if (!runtime->Init())
    {
        throw std::runtime_error("Runtime was not successfully initialized");
    }
        
    return runtime;
}
